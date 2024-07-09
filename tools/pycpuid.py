# The MIT License (MIT)

# Copyright (c) 2024 oldprincess, https://github.com/oldprincess/pycpuid.git

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
# OR OTHER DEALINGS IN THE SOFTWARE.

import platform
import os
import ctypes
from ctypes import c_uint32, c_long, c_ulong, c_size_t, c_void_p, POINTER, CFUNCTYPE
import struct


# part of this copy from https://github.com/flababah/cpuid.py
# Copyright (c) 2014 Anders Høst

# -------------------------------------------------------
# The MIT License (MIT)

# Copyright (c) 2014 Anders Høst

# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
    0x53,  # push   %rbx
    0x89,
    0xF0,  # mov    %esi,%eax
    0x89,
    0xD1,  # mov    %edx,%ecx
    0x0F,
    0xA2,  # cpuid
    0x89,
    0x07,  # mov    %eax,(%rdi)
    0x89,
    0x5F,
    0x04,  # mov    %ebx,0x4(%rdi)
    0x89,
    0x4F,
    0x08,  # mov    %ecx,0x8(%rdi)
    0x89,
    0x57,
    0x0C,  # mov    %edx,0xc(%rdi)
    0x5B,  # pop    %rbx
    0xC3,  # retq
]

_WINDOWS_64_OPC = [
    0x53,  # push   %rbx
    0x89,
    0xD0,  # mov    %edx,%eax
    0x49,
    0x89,
    0xC9,  # mov    %rcx,%r9
    0x44,
    0x89,
    0xC1,  # mov    %r8d,%ecx
    0x0F,
    0xA2,  # cpuid
    0x41,
    0x89,
    0x01,  # mov    %eax,(%r9)
    0x41,
    0x89,
    0x59,
    0x04,  # mov    %ebx,0x4(%r9)
    0x41,
    0x89,
    0x49,
    0x08,  # mov    %ecx,0x8(%r9)
    0x41,
    0x89,
    0x51,
    0x0C,  # mov    %edx,0xc(%r9)
    0x5B,  # pop    %rbx
    0xC3,  # retq
]

_CDECL_32_OPC = [
    0x53,  # push   %ebx
    0x57,  # push   %edi
    0x8B,
    0x7C,
    0x24,
    0x0C,  # mov    0xc(%esp),%edi
    0x8B,
    0x44,
    0x24,
    0x10,  # mov    0x10(%esp),%eax
    0x8B,
    0x4C,
    0x24,
    0x14,  # mov    0x14(%esp),%ecx
    0x0F,
    0xA2,  # cpuid
    0x89,
    0x07,  # mov    %eax,(%edi)
    0x89,
    0x5F,
    0x04,  # mov    %ebx,0x4(%edi)
    0x89,
    0x4F,
    0x08,  # mov    %ecx,0x8(%edi)
    0x89,
    0x57,
    0x0C,  # mov    %edx,0xc(%edi)
    0x5F,  # pop    %edi
    0x5B,  # pop    %ebx
    0xC3,  # ret
]

is_windows = os.name == "nt"
is_64bit = ctypes.sizeof(ctypes.c_voidp) == 8


class CPUID_struct(ctypes.Structure):
    _register_names = ("eax", "ebx", "ecx", "edx")
    _fields_ = [(r, c_uint32) for r in _register_names]

    def __getitem__(self, item: str):
        if item not in self._register_names:
            raise KeyError(item)
        return getattr(self, item)

    def __repr__(self):
        return "eax=0x{:x}, ebx=0x{:x}, ecx=0x{:x}, edx=0x{:x}".format(
            self.eax, self.ebx, self.ecx, self.edx
        )


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
            self.win.VirtualAlloc.argtypes = [
                ctypes.c_void_p,
                ctypes.c_size_t,
                ctypes.c_ulong,
                ctypes.c_ulong,
            ]
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

    def __call__(self, eax: int, ecx: int = 0):
        struct = self._registers_for(eax=eax, ecx=ecx)
        return struct.eax, struct.ebx, struct.ecx, struct.edx

    def _registers_for(self, eax: int, ecx: int = 0):
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


# ----------------------------------------------

# part of this refer to https://learn.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-170


def _bit_test(n: int, idx: int) -> bool:
    return (n & (1 << idx)) != 0


class InstructionSet(object):
    class InstructionSet_Internal(object):
        def __init__(self) -> None:
            self.f_1_ECX = 0
            self.f_1_EDX = 0
            self.f_7_EBX = 0
            self.f_7_ECX = 0
            self.f_81_ECX = 0
            self.f_81_EDX = 0
            self.vendor = ""
            self.brand = ""
            self.isIntel = False
            self.isAMD = False

            __cpuidex = CPUID()
            # Calling __cpuid with 0x0 as the function_id argument
            # gets the number of the highest valid function ID.
            cpui = __cpuidex(0)
            nIds = cpui[0]
            # Capture vendor string
            self.vendor = struct.pack("III", cpui[1], cpui[3], cpui[2]).decode("utf-8")
            if self.vendor == "GenuineIntel":
                self.isIntel = True
            if self.vendor == "AuthenticAMD":
                self.isAMD = True
            # load bitset with flags for function 0x00000001
            if nIds >= 1:
                cpui = __cpuidex(1)
                self.f_1_ECX = cpui[2]
                self.f_1_EDX = cpui[3]
            # load bitset with flags for function 0x00000007
            if nIds >= 7:
                cpui = __cpuidex(7)
                self.f_7_EBX = cpui[1]
                self.f_7_ECX = cpui[2]

            # Calling __cpuid with 0x80000000 as the function_id argument
            # gets the number of the highest valid extended ID.
            cpui = __cpuidex(0x80000000)
            nExIds = cpui[0]
            # load bitset with flags for function 0x80000001
            if nExIds >= 0x80000001:
                cpui = __cpuidex(0x80000001)
                self.f_81_ECX = cpui[2]
                self.f_81_EDX = cpui[3]
            # Interpret CPU brand string if reported
            if nExIds >= 0x80000004:
                brand = "".join(
                    [
                        struct.pack("IIII", *__cpuidex(0x80000000 + i)).decode("utf-8")
                        for i in range(2, 5)
                    ]
                )
                self.brand = brand.split("\x00", 1)[0]

    def __init__(self) -> None:
        self._CPU_Rep = self.InstructionSet_Internal()

    def Vendor(self) -> str:
        return self._CPU_Rep.vendor

    def Brand(self) -> str:
        return self._CPU_Rep.brand

    def SSE3(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 0)

    def PCLMULQDQ(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 1)

    def MONITOR(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 3)

    def SSSE3(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 9)

    def FMA(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 12)

    def CMPXCHG16B(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 13)

    def SSE41(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 19)

    def SSE42(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 20)

    def MOVBE(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 22)

    def POPCNT(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 23)

    def AES(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 25)

    def AES(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 25)

    def XSAVE(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 26)

    def OSXSAVE(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 27)

    def AVX(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 28)

    def F16C(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 29)

    def RDRAND(self):
        return _bit_test(self._CPU_Rep.f_1_ECX, 30)

    def MSR(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 5)

    def CX8(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 8)

    def SEP(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 11)

    def CMOV(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 15)

    def CLFSH(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 19)

    def MMX(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 23)

    def FXSR(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 24)

    def SSE(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 25)

    def SSE2(self):
        return _bit_test(self._CPU_Rep.f_1_EDX, 26)

    def FSGSBASE(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 0)

    def BMI1(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 3)

    def HLE(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 4) and self._CPU_Rep.isIntel

    def AVX2(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 5)

    def BMI2(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 8)

    def ERMS(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 9)

    def INVPCID(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 10)

    def RTM(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 11) and self._CPU_Rep.isIntel

    def AVX512F(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 16)

    def RDSEED(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 18)

    def ADX(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 19)

    def AVX512PF(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 26)

    def AVX512ER(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 27)

    def AVX512CD(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 28)

    def SHA(self):
        return _bit_test(self._CPU_Rep.f_7_EBX, 29)

    def PREFETCHWT1(self):
        return _bit_test(self._CPU_Rep.f_7_ECX, 0)

    def LAHF(self):
        return _bit_test(self._CPU_Rep.f_81_ECX, 0)

    def LZCNT(self):
        return _bit_test(self._CPU_Rep.f_81_ECX, 5) and self._CPU_Rep.isIntel

    def ABM(self):
        return _bit_test(self._CPU_Rep.f_81_ECX, 5) and self._CPU_Rep.isAMD

    def SSE4a(self):
        return _bit_test(self._CPU_Rep.f_81_ECX, 6) and self._CPU_Rep.isAMD

    def XOP(self):
        return _bit_test(self._CPU_Rep.f_81_ECX, 11) and self._CPU_Rep.isAMD

    def TBM(self):
        return _bit_test(self._CPU_Rep.f_81_ECX, 21) and self._CPU_Rep.isAMD

    def SYSCALL(self):
        return _bit_test(self._CPU_Rep.f_81_EDX, 11) and self._CPU_Rep.isIntel

    def MMXEXT(self):
        return _bit_test(self._CPU_Rep.f_81_EDX, 22) and self._CPU_Rep.isAMD

    def RDTSCP(self):
        return _bit_test(self._CPU_Rep.f_81_EDX, 27) and self._CPU_Rep.isIntel

    def _3DNOWEXT(self):
        return _bit_test(self._CPU_Rep.f_81_EDX, 30) and self._CPU_Rep.isAMD

    def _3DNOW(self):
        return _bit_test(self._CPU_Rep.f_81_EDX, 31) and self._CPU_Rep.isAMD
