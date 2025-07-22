#include <gmlib/info.h>

#include <cstdint>
#include <cstdio>

static const char* INFO_LIST[] = {
// x86-64 CPU FLAG
#if defined(CPU_FLAG_INTEL_AES)
    "CPU_FLAG_INTEL_AES",
#endif
#if defined(CPU_FLAG_INTEL_AVX2)
    "CPU_FLAG_INTEL_AVX2",
#endif
#if defined(CPU_FLAG_INTEL_BMI2)
    "CPU_FLAG_INTEL_BMI2",
#endif
#if defined(CPU_FLAG_INTEL_MOVBE)
    "CPU_FLAG_INTEL_MOVBE",
#endif
#if defined(CPU_FLAG_INTEL_PCLMUL)
    "CPU_FLAG_INTEL_PCLMUL",
#endif
#if defined(CPU_FLAG_INTEL_RDRAND)
    "CPU_FLAG_INTEL_RDRAND",
#endif
#if defined(CPU_FLAG_INTEL_RDSEED)
    "CPU_FLAG_INTEL_RDSEED",
#endif
#if defined(CPU_FLAG_INTEL_SHA)
    "CPU_FLAG_INTEL_SHA",
#endif
#if defined(CPU_FLAG_INTEL_SSE2)
    "CPU_FLAG_INTEL_SSE2",
#endif
#if defined(CPU_FLAG_INTEL_SSE4_1)
    "CPU_FLAG_INTEL_SSE4_1",
#endif
#if defined(CPU_FLAG_INTEL_SSSE3)
    "CPU_FLAG_INTEL_SSSE3",
#endif
// some optimization
#ifdef SUPPORT_BASE64_CHROMIUM
    "SUPPORT_BASE64_CHROMIUM",
#endif
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