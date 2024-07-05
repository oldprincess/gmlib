#include <gmlib/info.h>

#include <cstdint>
#include <cstdio>

static const char* INFO_LIST[] = {
// x86-64 CPU FLAG
#if defined(CPU_FLAG_3DNOW)
    "CPU_FLAG_3DNOW",
#endif
#if defined(CPU_FLAG_3DNOWEXT)
    "CPU_FLAG_3DNOWEXT",
#endif
#if defined(CPU_FLAG_ABM)
    "CPU_FLAG_ABM",
#endif
#if defined(CPU_FLAG_ADX)
    "CPU_FLAG_ADX",
#endif
#if defined(CPU_FLAG_AES)
    "CPU_FLAG_AES",
#endif
#if defined(CPU_FLAG_AVX)
    "CPU_FLAG_AVX",
#endif
#if defined(CPU_FLAG_AVX2)
    "CPU_FLAG_AVX2",
#endif
#if defined(CPU_FLAG_AVX512CD)
    "CPU_FLAG_AVX512CD",
#endif
#if defined(CPU_FLAG_AVX512ER)
    "CPU_FLAG_AVX512ER",
#endif
#if defined(CPU_FLAG_AVX512F)
    "CPU_FLAG_AVX512F",
#endif
#if defined(CPU_FLAG_AVX512PF)
    "CPU_FLAG_AVX512PF",
#endif
#if defined(CPU_FLAG_BMI1)
    "CPU_FLAG_BMI1",
#endif
#if defined(CPU_FLAG_BMI2)
    "CPU_FLAG_BMI2",
#endif
#if defined(CPU_FLAG_CLFSH)
    "CPU_FLAG_CLFSH",
#endif
#if defined(CPU_FLAG_CMPXCHG16B)
    "CPU_FLAG_CMPXCHG16B",
#endif
#if defined(CPU_FLAG_CX8)
    "CPU_FLAG_CX8",
#endif
#if defined(CPU_FLAG_ERMS)
    "CPU_FLAG_ERMS",
#endif
#if defined(CPU_FLAG_F16C)
    "CPU_FLAG_F16C",
#endif
#if defined(CPU_FLAG_FMA)
    "CPU_FLAG_FMA",
#endif
#if defined(CPU_FLAG_FSGSBASE)
    "CPU_FLAG_FSGSBASE",
#endif
#if defined(CPU_FLAG_FXSR)
    "CPU_FLAG_FXSR",
#endif
#if defined(CPU_FLAG_HLE)
    "CPU_FLAG_HLE",
#endif
#if defined(CPU_FLAG_INVPCID)
    "CPU_FLAG_INVPCID",
#endif
#if defined(CPU_FLAG_LAHF)
    "CPU_FLAG_LAHF",
#endif
#if defined(CPU_FLAG_LZCNT)
    "CPU_FLAG_LZCNT",
#endif
#if defined(CPU_FLAG_MMX)
    "CPU_FLAG_MMX",
#endif
#if defined(CPU_FLAG_MMXEXT)
    "CPU_FLAG_MMXEXT",
#endif
#if defined(CPU_FLAG_MONITOR)
    "CPU_FLAG_MONITOR",
#endif
#if defined(CPU_FLAG_MOVBE)
    "CPU_FLAG_MOVBE",
#endif
#if defined(CPU_FLAG_MSR)
    "CPU_FLAG_MSR",
#endif
#if defined(CPU_FLAG_OSXSAVE)
    "CPU_FLAG_OSXSAVE",
#endif
#if defined(CPU_FLAG_PCLMULQDQ)
    "CPU_FLAG_PCLMULQDQ",
#endif
#if defined(CPU_FLAG_POPCNT)
    "CPU_FLAG_POPCNT",
#endif
#if defined(CPU_FLAG_PREFETCHWT1)
    "CPU_FLAG_PREFETCHWT1",
#endif
#if defined(CPU_FLAG_RDRAND)
    "CPU_FLAG_RDRAND",
#endif
#if defined(CPU_FLAG_RDSEED)
    "CPU_FLAG_RDSEED",
#endif
#if defined(CPU_FLAG_RDTSCP)
    "CPU_FLAG_RDTSCP",
#endif
#if defined(CPU_FLAG_RTM)
    "CPU_FLAG_RTM",
#endif
#if defined(CPU_FLAG_SEP)
    "CPU_FLAG_SEP",
#endif
#if defined(CPU_FLAG_SHA)
    "CPU_FLAG_SHA",
#endif
#if defined(CPU_FLAG_SSE)
    "CPU_FLAG_SSE",
#endif
#if defined(CPU_FLAG_SSE2)
    "CPU_FLAG_SSE2",
#endif
#if defined(CPU_FLAG_SSE3)
    "CPU_FLAG_SSE3",
#endif
#if defined(CPU_FLAG_SSE4_1)
    "CPU_FLAG_SSE4_1",
#endif
#if defined(CPU_FLAG_SSE4_2)
    "CPU_FLAG_SSE4_2",
#endif
#if defined(CPU_FLAG_SSE4a)
    "CPU_FLAG_SSE4a",
#endif
#if defined(CPU_FLAG_SSSE3)
    "CPU_FLAG_SSSE3",
#endif
#if defined(CPU_FLAG_SYSCALL)
    "CPU_FLAG_SYSCALL",
#endif
#if defined(CPU_FLAG_TBM)
    "CPU_FLAG_TBM",
#endif
#if defined(CPU_FLAG_XOP)
    "CPU_FLAG_XOP",
#endif
#if defined(CPU_FLAG_XSAVE)
    "CPU_FLAG_XSAVE",
#endif
// some optimization
#ifdef SUPPORT_SM3_YANG15
    "SUPPORT_SM3_YANG15",
#endif
#ifdef SUPPORT_SM4_LANG18
    "SUPPORT_SM4_LANG18",
#endif
    nullptr,
};

const char** gmlib_get_config()
{
    return INFO_LIST;
}

void gmlib_print_config_def()
{
    std::size_t info_list_len = sizeof(INFO_LIST) / sizeof(INFO_LIST[0]);
    for (std::size_t i = 0; i < info_list_len - 1; i++)
    {
        std::printf("#define %s\n", INFO_LIST[i]);
    }
}

void gmlib_print_config_undef()
{
    std::size_t info_list_len = sizeof(INFO_LIST) / sizeof(INFO_LIST[0]);
    for (std::size_t i = 1; i < info_list_len; i++)
    {
        std::printf("#undef %s\n", INFO_LIST[info_list_len - 1 - i]);
    }
}