#include <gmlib/info.h>

#include <cstdint>
#include <cstdio>

// # add_definitions(-DCPU_FLAG_SSE2)
// # add_definitions(-DCPU_FLAG_SSSE3)
// # add_definitions(-DCPU_FLAG_AVX2)
// # add_definitions(-DCPU_FLAG_AES)
// # add_definitions(-DCPU_FLAG_MOVBE)
// # add_definitions(-DCPU_FLAG_BMI2)
// # add_definitions(-DCPU_FLAG_RDSEED)
// # add_definitions(-DCPU_FLAG_RDRAND)
// # add_definitions(-DCPU_FLAG_PCLMUL)
// # add_definitions(-DSUPPORT_SM3_YANG15)
// # add_definitions(-DSUPPORT_SM4_LANG18)

static const char* INFO_LIST[] = {
#ifdef CPU_FLAG_SSE2
    "CPU_FLAG_SSE2",
#endif
#ifdef CPU_FLAG_SSSE3
    "CPU_FLAG_SSSE3",
#endif
#ifdef CPU_FLAG_AVX2
    "CPU_FLAG_AVX2",
#endif
#ifdef CPU_FLAG_AES
    "CPU_FLAG_AES",
#endif
#ifdef CPU_FLAG_MOVBE
    "CPU_FLAG_MOVBE",
#endif
#ifdef CPU_FLAG_BMI2
    "CPU_FLAG_BMI2",
#endif
#ifdef CPU_FLAG_RDSEED
    "CPU_FLAG_RDSEED",
#endif
#ifdef CPU_FLAG_RDRAND
    "CPU_FLAG_RDRAND",
#endif
#ifdef CPU_FLAG_PCLMUL
    "CPU_FLAG_PCLMUL",
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