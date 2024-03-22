# -*- coding: utf-8 -*-
#
#     Copyright (c) 2024 Anders Høst
#

from __future__ import print_function

import platform
import os
import ctypes
from ctypes import c_uint32, c_long, c_ulong, c_size_t, c_void_p, POINTER, CFUNCTYPE

# Posix x86_64:
# Three first call registers : RDI, RSI, RDX
# Volatile registers         : RAX, RCX, RDX, RSI, RDI, R8-11

# Windows x86_64:
# Three first call registers : RCX, RDX, R8
# Volatile registers         : RAX, RCX, RDX, R8-11

# cdecl 32 bit:
# Three first call registers : Stack (%esp)
# Volatile registers         : EAX, ECX, EDX

_POSIX_64_OPC = [
        0x53,                    # push   %rbx
        0x89, 0xf0,              # mov    %esi,%eax
        0x89, 0xd1,              # mov    %edx,%ecx
        0x0f, 0xa2,              # cpuid
        0x89, 0x07,              # mov    %eax,(%rdi)
        0x89, 0x5f, 0x04,        # mov    %ebx,0x4(%rdi)
        0x89, 0x4f, 0x08,        # mov    %ecx,0x8(%rdi)
        0x89, 0x57, 0x0c,        # mov    %edx,0xc(%rdi)
        0x5b,                    # pop    %rbx
        0xc3                     # retq
]

_WINDOWS_64_OPC = [
        0x53,                    # push   %rbx
        0x89, 0xd0,              # mov    %edx,%eax
        0x49, 0x89, 0xc9,        # mov    %rcx,%r9
        0x44, 0x89, 0xc1,        # mov    %r8d,%ecx
        0x0f, 0xa2,              # cpuid
        0x41, 0x89, 0x01,        # mov    %eax,(%r9)
        0x41, 0x89, 0x59, 0x04,  # mov    %ebx,0x4(%r9)
        0x41, 0x89, 0x49, 0x08,  # mov    %ecx,0x8(%r9)
        0x41, 0x89, 0x51, 0x0c,  # mov    %edx,0xc(%r9)
        0x5b,                    # pop    %rbx
        0xc3                     # retq
]

_CDECL_32_OPC = [
        0x53,                    # push   %ebx
        0x57,                    # push   %edi
        0x8b, 0x7c, 0x24, 0x0c,  # mov    0xc(%esp),%edi
        0x8b, 0x44, 0x24, 0x10,  # mov    0x10(%esp),%eax
        0x8b, 0x4c, 0x24, 0x14,  # mov    0x14(%esp),%ecx
        0x0f, 0xa2,              # cpuid
        0x89, 0x07,              # mov    %eax,(%edi)
        0x89, 0x5f, 0x04,        # mov    %ebx,0x4(%edi)
        0x89, 0x4f, 0x08,        # mov    %ecx,0x8(%edi)
        0x89, 0x57, 0x0c,        # mov    %edx,0xc(%edi)
        0x5f,                    # pop    %edi
        0x5b,                    # pop    %ebx
        0xc3                     # ret
]

is_windows = os.name == "nt"
is_64bit = ctypes.sizeof(ctypes.c_voidp) == 8


class CPUID_struct(ctypes.Structure):
    _register_names = ("eax", "ebx", "ecx", "edx")
    _fields_ = [(r, c_uint32) for r in _register_names]

    def __getitem__(self, item):
        if item not in self._register_names:
            raise KeyError(item)
        return getattr(self, item)

    def __repr__(self):
        return "eax=0x{:x}, ebx=0x{:x}, ecx=0x{:x}, edx=0x{:x}".format(self.eax, self.ebx, self.ecx, self.edx)


class CPUID(object):
    def __init__(self):
        if platform.machine() not in ("AMD64", "x86_64", "x86", "i686"):
            raise SystemError("Only available for x86")

        if is_windows:
            if is_64bit:
                # VirtualAlloc seems to fail under some weird
                # circumstances when ctypes.windll.kernel32 is
                # used under 64 bit Python. CDLL fixes this.
                self.win = ctypes.CDLL("kernel32.dll")
                opc = _WINDOWS_64_OPC
            else:
                # Here ctypes.windll.kernel32 is needed to get the
                # right DLL. Otherwise it will fail when running
                # 32 bit Python on 64 bit Windows.
                self.win = ctypes.windll.kernel32
                opc = _CDECL_32_OPC
        else:
            opc = _POSIX_64_OPC if is_64bit else _CDECL_32_OPC

        size = len(opc)
        code = (ctypes.c_ubyte * size)(*opc)

        if is_windows:
            self.win.VirtualAlloc.restype = c_void_p
            self.win.VirtualAlloc.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_ulong, ctypes.c_ulong]
            self.addr = self.win.VirtualAlloc(None, size, 0x1000, 0x40)
            if not self.addr:
                raise MemoryError("Could not allocate RWX memory")
            ctypes.memmove(self.addr, code, size)
        else:
            from mmap import (
                mmap,
                MAP_PRIVATE,
                MAP_ANONYMOUS,
                PROT_WRITE,
                PROT_READ,
                PROT_EXEC,
            )
            self.mm = mmap(
                -1,
                size,
                flags=MAP_PRIVATE | MAP_ANONYMOUS,
                prot=PROT_WRITE | PROT_READ | PROT_EXEC,
            )
            self.mm.write(code)
            self.addr = ctypes.addressof(ctypes.c_int.from_buffer(self.mm))

        func_type = CFUNCTYPE(None, POINTER(CPUID_struct), c_uint32, c_uint32)
        self.func_ptr = func_type(self.addr)

    def __call__(self, eax, ecx=0):
        struct = self.registers_for(eax=eax, ecx=ecx)
        return struct.eax, struct.ebx, struct.ecx, struct.edx

    def registers_for(self, eax, ecx=0):
        """Calls cpuid with eax and ecx set as the input arguments, and returns a structure
        containing eax, ebx, ecx, and edx.
        """
        struct = CPUID_struct()
        self.func_ptr(struct, eax, ecx)
        return struct

    def __del__(self):
        if is_windows:
            self.win.VirtualFree.restype = c_long
            self.win.VirtualFree.argtypes = [c_void_p, c_size_t, c_ulong]
            self.win.VirtualFree(self.addr, 0, 0x8000)
        else:
            self.mm.close()


# -*- coding: utf-8 -*-
#
#     Copyright (c) 2024 Anders Høst
#

import struct


def cpu_vendor(cpu):
    _, b, c, d = cpu(0)
    return struct.pack("III", b, d, c).decode("utf-8")


def cpu_name(cpu):
    name = "".join((struct.pack("IIII", *cpu(0x80000000 + i)).decode("utf-8")
                    for i in range(2, 5)))

    return name.split('\x00', 1)[0]


def is_set(cpu, leaf, subleaf, reg_idx, bit):
    """
    @param {leaf} %eax
    @param {sublead} %ecx, 0 in most cases
    @param {reg_idx} idx of [%eax, %ebx, %ecx, %edx], 0-based
    @param {bit} bit of reg selected by {reg_idx}, 0-based
    """

    regs = cpu(leaf, subleaf)

    if (1 << bit) & regs[reg_idx]:
        return "Yes"
    else:
        return "--"


def support_flag() -> tuple:
    """_summary_

    Returns:
        tuple: support_flag_list, compile_options_list
    """
    cpu = CPUID()
    support_flag_list = []
    compile_options_list = []
    if is_set(cpu, 1, 0, 3, 26) == "Yes":
        support_flag_list.append("SSE2")
        compile_options_list.append("-msse2")
    if is_set(cpu, 7, 0, 1, 5) == "Yes":
        support_flag_list.append("AVX2")
        compile_options_list.append("-mavx2")
    if is_set(cpu, 1, 0, 2, 25) == "Yes":
        support_flag_list.append("AES")
        compile_options_list.append("-maes")
    if is_set(cpu, 1, 0, 2, 22) == "Yes":
        support_flag_list.append("MOVBE")
        compile_options_list.append("-mmovbe")
    if is_set(cpu, 7, 0, 1, 8) == "Yes":
        support_flag_list.append("BMI2")
        compile_options_list.append("-mbmi2")
    if is_set(cpu, 7, 0, 1, 18) == "Yes":
        support_flag_list.append("RDSEED")
        compile_options_list.append("-mrdseed")
    if is_set(cpu, 1, 0, 2, 30) == "Yes":
        support_flag_list.append("RDRAND")
        compile_options_list.append("-mrdrnd")
    if is_set(cpu, 1, 0, 2, 1) == "Yes":
        support_flag_list.append("PCLMUL")
        compile_options_list.append("-mpclmul")
    return support_flag_list, compile_options_list


if __name__ == "__main__":
    flags, options = support_flag()
    for flag in flags:
        print("add_definitions(-DCPU_FLAG_{})".format(flag))
    print("add_definitions(-DSUPPORT_SM3_YANG15)")
    print("add_definitions(-DSUPPORT_SM4_LANG18)")
    
    print("set(PROJECT_COMPILE_OPTIONS {})".format(" ".join(options)))