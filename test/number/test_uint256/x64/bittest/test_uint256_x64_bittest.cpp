#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>

using namespace number::internal::x64;

void test_uint256_x64_bittest()
{
    uint256_t a;

    std::uint8_t a0_data[32]  = {0x73,0x00,0xb3,0x86,0x38,0x72,0x37,0xc0,0xbd,0x48,0xfd,0xed,0x20,0xc0,0xb0,0x37,0x32,0x5f,0x44,0x89,0x79,0x41,0x94,0xec,0x16,0xd3,0x2f,0x29,0x5a,0x39,0x37,0x00};
    bool         a0_bits[256] = {false,false,false,false,false,false,false,false,true,true,true,false,true,true,false,false,true,false,false,true,true,true,false,false,false,true,false,true,true,false,true,false,true,false,false,true,false,true,false,false,true,true,true,true,false,true,false,false,true,true,false,false,true,false,true,true,false,true,true,false,true,false,false,false,false,false,true,true,false,true,true,true,false,false,true,false,true,false,false,true,true,false,false,false,false,false,true,false,true,false,false,true,true,true,true,false,true,false,false,true,false,false,false,true,false,false,true,false,false,false,true,false,true,true,true,true,true,false,true,false,false,true,false,false,true,true,false,false,true,true,true,false,true,true,false,false,false,false,false,false,true,true,false,true,false,false,false,false,false,false,true,true,false,false,false,false,false,true,false,false,true,false,true,true,false,true,true,true,true,false,true,true,true,true,true,true,false,false,false,true,false,false,true,false,true,false,true,true,true,true,false,true,false,false,false,false,false,false,true,true,true,true,true,false,true,true,false,false,false,true,false,false,true,true,true,false,false,false,false,true,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,true,true,false,true,false,false,false,false,false,false,false,false,true,true,false,false,true,true,true,false};
    uint256_from_bytes(a, a0_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a0_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a1_data[32]  = {0x92,0x19,0x0d,0x6f,0xa6,0x69,0xe5,0x26,0x4b,0x80,0xb2,0x97,0x4d,0x22,0x9e,0xd6,0xd2,0x1e,0x91,0x36,0x1b,0xf6,0x9f,0xea,0x6a,0xca,0x33,0x82,0x1e,0xaa,0xc5,0x7e};
    bool         a1_bits[256] = {false,true,true,true,true,true,true,false,true,false,true,false,false,false,true,true,false,true,false,true,false,true,false,true,false,true,true,true,true,false,false,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,false,false,false,true,false,true,false,false,true,true,false,true,false,true,false,true,true,false,false,true,false,true,false,true,true,true,true,true,true,true,true,false,false,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,false,false,false,true,true,false,true,true,false,false,true,false,false,false,true,false,false,true,false,true,true,true,true,false,false,false,false,true,false,false,true,false,true,true,false,true,true,false,true,false,true,true,false,true,true,true,true,false,false,true,false,true,false,false,false,true,false,false,true,false,true,true,false,false,true,false,true,true,true,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,false,false,false,false,false,true,true,true,false,true,false,false,true,false,false,true,true,false,false,true,false,false,true,false,true,false,false,true,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,true,false,true,true,true,true,true,false,true,true,false,true,false,true,true,false,false,false,false,true,false,false,true,true,false,false,false,false,true,false,false,true,false,false,true};
    uint256_from_bytes(a, a1_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a1_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a2_data[32]  = {0xa2,0x67,0x04,0x99,0x0a,0x18,0x27,0x1f,0x38,0xe4,0x9f,0x61,0x97,0xef,0x18,0x97,0x1e,0xc1,0x01,0x9a,0x72,0xa7,0x9d,0x47,0xbf,0x47,0xc7,0x3b,0x59,0x39,0xcf,0x62};
    bool         a2_bits[256] = {false,true,false,false,false,true,true,false,true,true,true,true,false,false,true,true,true,false,false,true,true,true,false,false,true,false,false,true,true,false,true,false,true,true,false,true,true,true,false,false,true,true,true,false,false,false,true,true,true,true,true,false,false,false,true,false,true,true,true,true,true,true,false,true,true,true,true,false,false,false,true,false,true,false,true,true,true,false,false,true,true,true,true,false,false,true,false,true,false,true,false,false,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,false,false,false,false,false,true,false,false,false,false,false,true,true,false,true,true,true,true,false,false,false,true,true,true,false,true,false,false,true,false,false,false,true,true,false,false,false,true,true,true,true,false,true,true,true,true,true,true,false,true,false,false,true,true,false,false,false,false,true,true,false,true,true,true,true,true,false,false,true,false,false,true,false,false,true,true,true,false,false,false,true,true,true,false,false,true,true,true,true,true,false,false,false,true,true,true,false,false,true,false,false,false,false,false,true,true,false,false,false,false,true,false,true,false,false,false,false,true,false,false,true,true,false,false,true,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,false,false,true,false,false,false,true,false,true};
    uint256_from_bytes(a, a2_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a2_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a3_data[32]  = {0x3f,0x27,0xda,0xb5,0x6c,0x51,0x5a,0xc8,0x86,0xa5,0x1a,0x10,0xdd,0x93,0x19,0x48,0xd4,0x51,0x0e,0x3a,0x3a,0x6f,0xae,0x08,0xbc,0xa9,0x8c,0x7e,0x21,0x71,0x9c,0xd5};
    bool         a3_bits[256] = {true,false,true,false,true,false,true,true,false,false,true,true,true,false,false,true,true,false,false,false,true,true,true,false,true,false,false,false,false,true,false,false,false,true,true,true,true,true,true,false,false,false,true,true,false,false,false,true,true,false,false,true,false,true,false,true,false,false,true,true,true,true,false,true,false,false,false,true,false,false,false,false,false,true,true,true,false,true,false,true,true,true,true,true,false,true,true,false,false,true,false,true,true,true,false,false,false,true,false,true,true,true,false,false,false,true,true,true,false,false,false,false,true,false,false,false,true,false,true,false,false,false,true,false,true,false,true,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,false,false,true,true,false,false,true,false,false,true,true,false,true,true,true,false,true,true,false,false,false,false,true,false,false,false,false,true,false,true,true,false,false,false,true,false,true,false,false,true,false,true,false,true,true,false,false,false,false,true,false,false,false,true,false,false,true,true,false,true,false,true,true,false,true,false,true,false,false,false,true,false,true,false,false,false,true,true,false,true,true,false,true,false,true,false,true,true,false,true,false,true,false,true,true,false,true,true,true,true,true,false,false,true,false,false,true,true,true,true,true,true,false,false};
    uint256_from_bytes(a, a3_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a3_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a4_data[32]  = {0xfc,0x20,0xcf,0xbd,0x3d,0xc8,0xbc,0x14,0xeb,0x7a,0xbc,0x04,0x20,0x53,0x25,0x67,0x90,0x78,0xcd,0xb4,0x42,0x00,0x82,0x0e,0x2d,0xf0,0xe5,0x75,0xd0,0x16,0x8d,0x74};
    bool         a4_bits[256] = {false,false,true,false,true,true,true,false,true,false,true,true,false,false,false,true,false,true,true,false,true,false,false,false,false,false,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,true,false,false,true,true,true,false,false,false,false,true,true,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,false,false,false,false,true,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,true,false,false,false,false,true,false,false,false,true,false,true,true,false,true,true,false,true,true,false,false,true,true,false,false,false,true,true,true,true,false,false,false,false,false,true,false,false,true,true,true,true,false,false,true,true,false,true,false,true,false,false,true,false,false,true,true,false,false,true,false,true,false,false,false,false,false,false,true,false,false,false,false,true,false,false,false,false,false,false,false,true,true,true,true,false,true,false,true,false,true,true,true,true,false,true,true,false,true,false,true,true,true,false,false,true,false,true,false,false,false,false,false,true,true,true,true,false,true,false,false,false,true,false,false,true,true,true,false,true,true,true,true,false,false,true,false,true,true,true,true,false,true,true,true,true,true,false,false,true,true,false,false,false,false,false,true,false,false,false,false,true,true,true,true,true,true};
    uint256_from_bytes(a, a4_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a4_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a5_data[32]  = {0x63,0xcf,0x3d,0x20,0x15,0x01,0x4a,0x40,0x8a,0x1f,0x4a,0x65,0x8f,0x36,0xcf,0x96,0x6d,0xe0,0x06,0x56,0x93,0x4c,0xb9,0xe0,0x27,0x1b,0xbf,0xb7,0xed,0xd9,0x13,0x33};
    bool         a5_bits[256] = {true,true,false,false,true,true,false,false,true,true,false,false,true,false,false,false,true,false,false,true,true,false,true,true,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,true,true,true,true,true,true,true,false,true,true,true,false,true,true,false,false,false,true,true,true,false,false,true,false,false,false,false,false,false,false,true,true,true,true,false,false,true,true,true,false,true,false,false,true,true,false,false,true,false,true,true,false,false,true,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,false,false,false,false,false,false,false,false,false,true,true,true,true,false,true,true,false,true,true,false,false,true,true,false,true,false,false,true,true,true,true,true,false,false,true,true,false,true,true,false,true,true,false,false,true,true,true,true,false,false,false,true,true,false,true,false,false,true,true,false,false,true,false,true,false,false,true,false,true,true,true,true,true,false,false,false,false,true,false,true,false,false,false,true,false,false,false,false,false,false,true,false,false,true,false,true,false,false,true,false,true,false,false,false,false,false,false,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,true,true,false,false,true,true,true,true,false,false,false,true,true,false};
    uint256_from_bytes(a, a5_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a5_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a6_data[32]  = {0xdd,0x6d,0x82,0x41,0x1f,0x15,0x8e,0x19,0xf5,0x2d,0x7c,0x43,0xf1,0xaf,0x4b,0x3d,0xf6,0xc2,0x0e,0xe5,0x38,0x0e,0x05,0xce,0xa2,0x79,0xb6,0xe0,0x30,0xdf,0x36,0x1a};
    bool         a6_bits[256] = {false,true,false,true,true,false,false,false,false,true,true,false,true,true,false,false,true,true,true,true,true,false,true,true,false,false,false,false,true,true,false,false,false,false,false,false,false,true,true,true,false,true,true,false,true,true,false,true,true,false,false,true,true,true,true,false,false,true,false,false,false,true,false,true,false,true,true,true,false,false,true,true,true,false,true,false,false,false,false,false,false,true,true,true,false,false,false,false,false,false,false,true,true,true,false,false,true,false,true,false,false,true,true,true,false,true,true,true,false,false,false,false,false,true,false,false,false,false,true,true,false,true,true,false,true,true,true,true,true,false,true,true,true,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,false,true,false,true,true,false,false,false,true,true,true,true,true,true,false,false,false,false,true,false,false,false,true,true,true,true,true,false,true,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true,true,false,false,true,true,false,false,false,false,true,true,true,false,false,false,true,true,false,true,false,true,false,false,false,true,true,true,true,true,false,false,false,true,false,false,false,false,false,true,false,false,true,false,false,false,false,false,true,true,false,true,true,false,true,true,false,true,false,true,true,true,false,true,true};
    uint256_from_bytes(a, a6_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a6_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a7_data[32]  = {0xb4,0xd1,0xd7,0xfa,0xd3,0x2d,0x39,0x21,0x65,0x8b,0x14,0x32,0x47,0x56,0xad,0x79,0x9d,0x34,0x7f,0x93,0xc5,0x40,0xf4,0xa8,0x40,0xc2,0x0f,0x1c,0xcc,0x2d,0x7e,0x25};
    bool         a7_bits[256] = {true,false,true,false,false,true,false,false,false,true,true,true,true,true,true,false,true,false,true,true,false,true,false,false,false,false,true,true,false,false,true,true,false,false,true,true,true,false,false,false,true,true,true,true,false,false,false,false,false,true,false,false,false,false,true,true,false,false,false,false,false,false,true,false,false,false,false,true,false,true,false,true,false,false,true,false,true,true,true,true,false,false,false,false,false,false,true,false,true,false,true,false,false,false,true,true,true,true,false,false,true,false,false,true,true,true,true,true,true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,true,true,false,false,true,true,false,false,true,true,true,true,false,true,false,true,true,false,true,false,true,false,true,true,false,true,false,true,false,true,true,true,false,false,false,true,false,false,true,false,false,true,true,false,false,false,false,true,false,true,false,false,false,true,true,false,true,false,false,false,true,true,false,true,false,false,true,true,false,true,false,false,false,false,true,false,false,true,false,false,true,true,true,false,false,true,false,true,true,false,true,false,false,true,true,false,false,true,false,true,true,false,true,false,true,true,true,true,true,true,true,true,false,true,false,true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,true,false,true};
    uint256_from_bytes(a, a7_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a7_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a8_data[32]  = {0x8e,0x9c,0xa8,0x70,0x2c,0x5d,0x31,0x85,0xe2,0xb7,0xea,0xe5,0x40,0x3a,0x3e,0x9f,0x1f,0x48,0x50,0xb9,0x38,0x85,0x95,0xa1,0xd2,0xc6,0xad,0x47,0x8a,0x71,0x57,0xc8};
    bool         a8_bits[256] = {false,false,false,true,false,false,true,true,true,true,true,false,true,false,true,false,true,false,false,false,true,true,true,false,false,true,false,true,false,false,false,true,true,true,true,false,false,false,true,false,true,false,true,true,false,true,false,true,false,true,true,false,false,false,true,true,false,true,false,false,true,false,true,true,true,false,false,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,true,false,false,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,true,false,true,false,false,false,false,true,false,true,false,false,false,false,true,false,false,true,false,true,true,true,true,true,false,false,false,true,true,true,true,true,false,false,true,false,true,true,true,true,true,false,false,false,true,false,true,true,true,false,false,false,false,false,false,false,false,true,false,true,false,true,false,false,true,true,true,false,true,false,true,false,true,true,true,true,true,true,false,true,true,false,true,false,true,false,false,false,true,true,true,true,false,true,false,false,false,false,true,true,false,false,false,true,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,false,true,false,false,false,false,false,false,true,true,true,false,false,false,false,true,false,true,false,true,false,false,true,true,true,false,false,true,false,true,true,true,false,false,false,true};
    uint256_from_bytes(a, a8_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a8_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a9_data[32]  = {0x1e,0x4d,0xb7,0x1e,0xec,0xe0,0x6a,0x2b,0xda,0x11,0x01,0xe8,0x31,0xab,0x63,0x84,0x68,0x9e,0x23,0xd7,0x5c,0xea,0xe6,0xbf,0xaa,0x24,0xb5,0xb4,0x5c,0xbc,0x24,0x2e};
    bool         a9_bits[256] = {false,true,true,true,false,true,false,false,false,false,true,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,true,true,true,false,true,false,false,false,true,false,true,true,false,true,true,false,true,false,true,true,false,true,false,false,true,false,false,true,false,false,false,true,false,true,false,true,false,true,true,true,true,true,true,true,false,true,false,true,true,false,false,true,true,true,false,true,false,true,false,true,true,true,false,false,true,true,true,false,true,false,true,true,true,false,true,false,true,true,true,true,false,false,false,true,false,false,false,true,true,true,true,false,false,true,false,false,false,true,false,true,true,false,false,false,true,false,false,false,false,true,true,true,false,false,false,true,true,false,true,true,false,true,false,true,false,true,true,false,false,false,true,true,false,false,false,false,false,true,false,true,true,true,true,false,false,false,false,false,false,false,true,false,false,false,true,false,false,false,false,true,false,true,true,false,true,true,true,true,false,true,false,true,false,false,false,true,false,true,false,true,true,false,false,false,false,false,false,true,true,true,false,false,true,true,false,true,true,true,false,true,true,true,true,false,false,false,true,true,true,false,true,true,false,true,true,false,true,true,false,false,true,false,false,true,true,true,true,false,false,false};
    uint256_from_bytes(a, a9_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a9_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a10_data[32]  = {0xe8,0xc0,0x34,0xd9,0x6e,0xb1,0x35,0x3e,0x59,0xbd,0x4d,0x18,0x82,0x90,0xd1,0x9e,0x8c,0x43,0x15,0x2c,0x02,0xe1,0x48,0x05,0x09,0x66,0xde,0x16,0x06,0x80,0xf0,0xec};
    bool         a10_bits[256] = {false,false,true,true,false,true,true,true,false,false,false,false,true,true,true,true,false,false,false,false,false,false,false,true,false,true,true,false,false,false,false,false,false,true,true,false,true,false,false,false,false,true,true,true,true,false,true,true,false,true,true,false,false,true,true,false,true,false,false,true,false,false,false,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,true,false,true,false,false,false,false,true,true,true,false,true,false,false,false,false,false,false,false,false,true,true,false,true,false,false,true,false,true,false,true,false,false,false,true,true,false,false,false,false,true,false,false,false,true,true,false,false,false,true,false,true,true,true,true,false,false,true,true,false,false,false,true,false,true,true,false,false,false,false,true,false,false,true,false,true,false,false,false,false,false,true,false,false,false,true,true,false,false,false,true,false,true,true,false,false,true,false,true,false,true,true,true,true,false,true,true,false,false,true,true,false,true,false,false,true,true,true,true,true,false,false,true,false,true,false,true,true,false,false,true,false,false,false,true,true,false,true,false,true,true,true,false,true,true,false,true,false,false,true,true,false,true,true,false,false,true,false,true,true,false,false,false,false,false,false,false,false,true,true,false,false,false,true,false,true,true,true};
    uint256_from_bytes(a, a10_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a10_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a11_data[32]  = {0x56,0x6e,0x48,0x27,0x71,0x7c,0x5d,0x9f,0x6c,0xa6,0x66,0xaf,0x7b,0x25,0x52,0x80,0x07,0xdc,0xbd,0x6b,0x47,0xc0,0xeb,0x60,0xdd,0x43,0x9a,0xb4,0x7b,0xb0,0xca,0x68};
    bool         a11_bits[256] = {false,false,false,true,false,true,true,false,false,true,false,true,false,false,true,true,false,false,false,false,true,true,false,true,true,true,false,true,true,true,true,false,false,false,true,false,true,true,false,true,false,true,false,true,true,false,false,true,true,true,false,false,false,false,true,false,true,false,true,true,true,false,true,true,false,false,false,false,false,true,true,false,true,true,false,true,false,true,true,true,false,false,false,false,false,false,true,true,true,true,true,false,false,false,true,false,true,true,false,true,false,true,true,false,true,false,true,true,true,true,false,true,false,false,true,true,true,false,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,true,false,false,true,true,false,true,true,true,true,false,true,true,true,true,false,true,false,true,false,true,true,false,false,true,true,false,false,true,true,false,false,true,false,true,false,false,true,true,false,true,true,false,true,true,true,true,true,false,false,true,true,false,true,true,true,false,true,false,false,false,true,true,true,true,true,false,true,false,false,false,true,true,true,false,true,true,true,false,false,true,false,false,false,false,false,true,false,false,true,false,false,true,true,true,false,true,true,false,false,true,true,false,true,false,true,false};
    uint256_from_bytes(a, a11_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a11_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a12_data[32]  = {0xb1,0x7e,0x01,0x6a,0xc6,0x08,0x6e,0xd6,0x74,0x6f,0x0c,0x0b,0xf6,0x73,0x0b,0x51,0x84,0xb3,0xfa,0x81,0x1f,0xa2,0x84,0xb4,0x88,0x33,0x00,0x88,0x67,0x7b,0x57,0x77};
    bool         a12_bits[256] = {true,true,true,false,true,true,true,false,true,true,true,false,true,false,true,false,true,true,false,true,true,true,true,false,true,true,true,false,false,true,true,false,false,false,false,true,false,false,false,true,false,false,false,false,false,false,false,false,true,true,false,false,true,true,false,false,false,false,false,true,false,false,false,true,false,false,true,false,true,true,false,true,false,false,true,false,false,false,false,true,false,true,false,false,false,true,false,true,true,true,true,true,true,false,false,false,true,false,false,false,false,false,false,true,false,true,false,true,true,true,true,true,true,true,false,false,true,true,false,true,false,false,true,false,false,false,false,true,true,false,false,false,true,false,true,false,true,true,false,true,false,false,false,false,true,true,false,false,true,true,true,false,false,true,true,false,true,true,true,true,true,true,false,true,false,false,false,false,false,false,true,true,false,false,false,false,true,true,true,true,false,true,true,false,false,false,true,false,true,true,true,false,false,true,true,false,true,false,true,true,false,true,true,true,false,true,true,false,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,true,false,true,false,true,false,true,true,false,true,false,false,false,false,false,false,false,false,true,true,true,true,true,true,false,true,false,false,false,true,true,false,true};
    uint256_from_bytes(a, a12_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a12_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a13_data[32]  = {0xc2,0x40,0x95,0xe1,0xd5,0xe1,0xc5,0xc4,0x8e,0x50,0x36,0x82,0x3c,0xb7,0x8f,0x8d,0x30,0x09,0xa7,0xc3,0x64,0x70,0xc7,0xac,0x79,0xc1,0x33,0xdf,0xaa,0x78,0xc4,0x1f};
    bool         a13_bits[256] = {true,true,true,true,true,false,false,false,false,false,true,false,false,false,true,true,false,false,false,true,true,true,true,false,false,true,false,true,false,true,false,true,true,true,true,true,true,false,true,true,true,true,false,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,true,true,false,false,false,true,true,false,true,false,true,true,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,false,true,false,false,true,true,false,true,true,false,false,false,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,false,false,false,false,false,false,false,false,true,true,false,false,true,false,true,true,false,false,false,true,true,true,true,true,false,false,false,true,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,false,true,false,false,false,false,false,true,false,true,true,false,true,true,false,false,false,false,false,false,true,false,true,false,false,true,true,true,false,false,false,true,false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,true,true,false,false,false,false,true,true,true,true,false,true,false,true,false,true,true,true,false,false,false,false,true,true,true,true,false,true,false,true,false,false,true,false,false,false,false,false,false,true,false,false,true,false,false,false,false,true,true};
    uint256_from_bytes(a, a13_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a13_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a14_data[32]  = {0x87,0x3a,0x1b,0xe6,0x00,0x8c,0x5f,0x3d,0x39,0xc4,0xaa,0xec,0xe3,0x95,0x0e,0xbd,0x09,0xf4,0x57,0xb0,0x42,0x90,0xab,0xf8,0x6a,0x32,0x06,0xab,0xcd,0x82,0xc0,0xd4};
    bool         a14_bits[256] = {false,false,true,false,true,false,true,true,false,false,false,false,false,false,true,true,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,true,true,true,false,true,false,true,false,true,false,true,true,false,false,false,false,false,false,true,false,false,true,true,false,false,false,true,false,true,false,true,true,false,false,false,false,true,true,true,true,true,true,true,false,true,false,true,false,true,false,false,false,false,true,false,false,true,false,true,false,false,false,false,true,false,false,false,false,false,true,true,false,true,true,true,true,false,true,false,true,false,false,false,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,false,true,true,true,true,false,true,false,true,true,true,false,false,false,false,true,false,true,false,true,false,false,true,true,true,false,false,false,true,true,true,false,false,true,true,false,true,true,true,false,true,false,true,false,true,false,true,false,false,true,false,false,false,true,true,true,false,false,true,true,true,false,false,true,false,true,true,true,true,false,false,true,true,true,true,true,false,true,false,false,false,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,true,true,false,false,true,true,true,true,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,true,true,false,false,false,false,true};
    uint256_from_bytes(a, a14_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a14_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a15_data[32]  = {0xa9,0x7a,0x3b,0x36,0xe8,0xca,0xc9,0xd7,0xfa,0xf2,0x7b,0x1b,0xc7,0x64,0x1c,0x0f,0x6c,0xc5,0x88,0x60,0x2b,0xec,0x11,0xf9,0x9a,0x70,0x8e,0xa1,0xd5,0x3e,0xc4,0xfb};
    bool         a15_bits[256] = {true,true,false,true,true,true,true,true,false,false,true,false,false,false,true,true,false,true,true,true,true,true,false,false,true,false,true,false,true,false,true,true,true,false,false,false,false,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,true,true,true,true,true,true,false,false,false,true,false,false,false,false,false,true,true,false,true,true,true,true,true,false,true,false,true,false,false,false,false,false,false,false,true,true,false,false,false,false,true,false,false,false,true,true,false,true,false,false,false,true,true,false,false,true,true,false,true,true,false,true,true,true,true,false,false,false,false,false,false,true,true,true,false,false,false,false,false,true,false,false,true,true,false,true,true,true,false,false,false,true,true,true,true,false,true,true,false,false,false,true,true,false,true,true,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,true,true,true,true,true,true,true,false,true,false,true,true,true,false,false,true,false,false,true,true,false,true,false,true,false,false,true,true,false,false,false,true,false,true,true,true,false,true,true,false,true,true,false,false,true,true,false,true,true,true,false,false,false,true,false,true,true,true,true,false,true,false,false,true,false,true,false,true};
    uint256_from_bytes(a, a15_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a15_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a16_data[32]  = {0x3c,0x51,0x0e,0xf7,0x91,0x83,0xce,0x5e,0x76,0x71,0x27,0x43,0x27,0xbc,0xa0,0x02,0xeb,0xa9,0x73,0x36,0xed,0x90,0x2c,0xa2,0x74,0xd8,0xe8,0x68,0x30,0xd2,0x8f,0x89};
    bool         a16_bits[256] = {true,false,false,true,false,false,false,true,true,true,true,true,false,false,false,true,false,true,false,false,true,false,true,true,false,false,false,false,true,true,false,false,false,false,false,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,false,true,true,false,true,true,false,false,true,false,true,true,true,false,false,true,false,false,false,true,false,true,false,false,true,true,false,true,false,false,false,false,false,false,true,false,false,true,true,false,true,true,false,true,true,true,false,true,true,false,true,true,false,false,true,true,false,false,true,true,true,false,true,false,false,true,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,true,true,true,false,true,true,true,true,false,false,true,false,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,false,false,true,false,false,false,true,true,true,false,false,true,true,false,true,true,true,false,false,true,true,true,true,false,true,false,false,true,true,true,false,false,true,true,true,true,false,false,false,false,false,true,true,false,false,false,true,false,false,true,true,true,true,false,true,true,true,true,false,true,true,true,false,false,false,false,true,false,false,false,true,false,true,false,false,false,true,true,true,true,false,false};
    uint256_from_bytes(a, a16_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a16_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a17_data[32]  = {0x56,0xdb,0xbf,0xdf,0xf9,0x6b,0x25,0x18,0x53,0x86,0xe8,0x20,0x75,0x25,0x72,0x1f,0x56,0x25,0xf9,0xd9,0x65,0xf0,0x33,0x7a,0xe7,0xb4,0x18,0xa9,0x86,0x3e,0x76,0xe3};
    bool         a17_bits[256] = {true,true,false,false,false,true,true,true,false,true,true,false,true,true,true,false,false,true,true,true,true,true,false,false,false,true,true,false,false,false,false,true,true,false,false,true,false,true,false,true,false,false,false,true,true,false,false,false,false,false,true,false,true,true,false,true,true,true,true,false,false,true,true,true,false,true,false,true,true,true,true,false,true,true,false,false,true,true,false,false,false,false,false,false,true,true,true,true,true,false,true,false,false,true,true,false,true,false,false,true,true,false,true,true,true,false,false,true,true,true,true,true,true,false,true,false,false,true,false,false,false,true,true,false,true,false,true,false,true,true,true,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,true,false,false,true,false,false,true,false,true,false,true,true,true,false,false,false,false,false,false,true,false,false,false,false,false,true,false,true,true,true,false,true,true,false,false,false,false,true,true,true,false,false,true,false,true,false,false,false,false,true,true,false,false,false,true,false,true,false,false,true,false,false,true,true,false,true,false,true,true,false,true,false,false,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,true,false,true,true,false,true,true,false,true,true,false,true,false,true,false};
    uint256_from_bytes(a, a17_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a17_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a18_data[32]  = {0xce,0xea,0xa9,0x03,0xb7,0x28,0x8b,0x45,0xe9,0x78,0xc3,0x30,0x76,0x20,0x6b,0xa3,0xa5,0x96,0x40,0xcc,0x98,0xc6,0x5d,0x98,0x6b,0xa1,0xc8,0xcf,0x8f,0x71,0x67,0xb0};
    bool         a18_bits[256] = {false,false,false,false,true,true,false,true,true,true,true,false,false,true,true,false,true,false,false,false,true,true,true,false,true,true,true,true,false,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,false,false,true,true,true,false,false,false,false,true,false,true,true,true,false,true,false,true,true,false,false,false,false,true,true,false,false,true,true,false,true,true,true,false,true,false,false,true,true,false,false,false,true,true,false,false,false,true,true,false,false,true,false,false,true,true,false,false,true,true,false,false,false,false,false,false,true,false,false,true,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,true,false,false,false,true,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,true,false,false,false,false,false,true,true,false,false,true,true,false,false,false,false,true,true,false,false,false,true,true,true,true,false,true,false,false,true,false,true,true,true,true,false,true,false,false,false,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,true,false,false,true,true,true,false,true,true,false,true,true,true,false,false,false,false,false,false,true,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,false,true,true,true,false,false,true,true};
    uint256_from_bytes(a, a18_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a18_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a19_data[32]  = {0x10,0x4b,0x0d,0x2a,0x0c,0x84,0x93,0xea,0xf5,0x70,0x84,0x30,0xaf,0x74,0xc0,0xd5,0x41,0x23,0xc5,0xd1,0xd3,0xa3,0xa4,0x0b,0x21,0x9a,0xaa,0x73,0x07,0x0c,0x50,0xfc};
    bool         a19_bits[256] = {false,false,true,true,true,true,true,true,false,false,false,false,true,false,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,false,false,false,true,true,false,false,true,true,true,false,false,true,false,true,false,true,false,true,false,true,false,true,true,false,false,true,true,false,false,false,false,true,false,false,true,true,false,true,false,false,false,false,false,false,true,false,false,true,false,true,true,true,false,false,false,true,false,true,true,true,false,false,true,false,true,true,true,false,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,false,false,true,false,false,true,false,false,false,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,false,false,false,true,true,false,false,true,false,true,true,true,false,true,true,true,true,false,true,false,true,false,false,false,false,true,true,false,false,false,false,true,false,false,false,false,true,false,false,false,false,true,true,true,false,true,false,true,false,true,true,true,true,false,true,false,true,false,true,true,true,true,true,false,false,true,false,false,true,false,false,true,false,false,false,false,true,false,false,true,true,false,false,false,false,false,true,false,true,false,true,false,false,true,false,true,true,false,false,false,false,true,true,false,true,false,false,true,false,false,false,false,false,true,false,false,false};
    uint256_from_bytes(a, a19_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a19_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a20_data[32]  = {0xff,0x8f,0x46,0x4f,0x02,0x6e,0x15,0xdc,0xa2,0x1e,0x70,0x2f,0x33,0x89,0x24,0xa3,0xe6,0xfd,0x2c,0xa7,0x4c,0x20,0x36,0x7e,0xde,0x6f,0x86,0xac,0xfd,0x2b,0xb2,0xf7};
    bool         a20_bits[256] = {true,true,true,false,true,true,true,true,false,true,false,false,true,true,false,true,true,true,false,true,false,true,false,false,true,false,true,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,true,false,false,false,false,true,true,true,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,true,true,true,true,true,false,false,true,true,false,true,true,false,false,false,false,false,false,false,true,false,false,false,false,true,true,false,false,true,false,true,true,true,false,false,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,true,true,false,true,true,false,false,true,true,true,true,true,false,false,false,true,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,false,true,true,true,false,false,true,true,false,false,true,true,true,true,false,true,false,false,false,false,false,false,true,true,true,false,false,true,true,true,true,false,false,false,false,true,false,false,false,true,false,true,false,false,true,true,true,false,true,true,true,false,true,false,true,false,false,false,false,true,true,true,false,true,true,false,false,true,false,false,false,false,false,false,true,true,true,true,false,false,true,false,false,true,true,false,false,false,true,false,true,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true};
    uint256_from_bytes(a, a20_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a20_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a21_data[32]  = {0x93,0x69,0x9c,0xa1,0x16,0x77,0x52,0x51,0x77,0x02,0x9d,0x0b,0xef,0x8a,0xbc,0xdd,0x0d,0xd0,0x4d,0xeb,0x69,0x1c,0x00,0xd0,0x01,0xf4,0x5f,0x9a,0x3f,0xd4,0x95,0xbd};
    bool         a21_bits[256] = {true,false,true,true,true,true,false,true,true,false,true,false,true,false,false,true,false,false,true,false,true,false,true,true,true,true,true,true,true,true,false,false,false,true,false,true,true,false,false,true,true,true,true,true,true,false,true,false,false,false,true,false,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,false,true,false,false,true,false,true,true,false,true,true,false,true,false,true,true,true,true,false,true,true,false,false,true,false,false,false,false,false,true,false,true,true,true,false,true,true,false,false,false,false,true,false,true,true,true,false,true,true,false,false,true,true,true,true,false,true,false,true,false,true,false,false,false,true,true,true,true,true,false,true,true,true,true,true,false,true,false,false,false,false,true,false,true,true,true,false,false,true,false,true,false,false,false,false,false,false,true,true,true,false,true,true,true,false,true,false,false,false,true,false,true,false,false,true,false,false,true,false,true,false,true,true,true,false,true,true,true,false,false,true,true,false,true,false,false,false,true,false,false,false,false,true,false,true,false,false,true,true,true,false,false,true,true,false,false,true,false,true,true,false,true,true,false,false,true,false,false,true};
    uint256_from_bytes(a, a21_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a21_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a22_data[32]  = {0xc4,0x19,0xec,0x83,0xee,0x71,0xe4,0x81,0x50,0x60,0xc8,0x9b,0x0a,0x77,0x7e,0xde,0x96,0x64,0xf5,0x77,0x5b,0x79,0xbc,0x30,0x8e,0xa1,0x87,0xb1,0x68,0x31,0x5a,0x8b};
    bool         a22_bits[256] = {true,true,false,true,false,false,false,true,false,true,false,true,true,false,true,false,true,false,false,false,true,true,false,false,false,false,false,true,false,true,true,false,true,false,false,false,true,true,false,true,true,true,true,false,false,false,false,true,true,false,false,false,false,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,false,false,false,false,true,true,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,true,false,true,false,true,true,true,false,true,true,true,false,true,false,true,false,true,true,true,true,false,false,true,false,false,true,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,false,true,true,false,true,true,true,true,true,true,false,true,true,true,false,true,true,true,false,false,true,false,true,false,false,false,false,true,true,false,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,false,false,false,true,true,false,false,false,false,false,true,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,false,true,true,true,true,false,false,false,true,true,true,false,false,true,true,true,false,true,true,true,true,true,false,false,false,false,false,true,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,false,false,false,true,false,false,false,true,true};
    uint256_from_bytes(a, a22_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a22_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a23_data[32]  = {0x7d,0x00,0x0d,0x88,0xce,0x19,0x5a,0x52,0x3f,0x3c,0x0e,0x94,0xc9,0xff,0x2b,0xd9,0x51,0xba,0x82,0x49,0x46,0x22,0xd5,0xd7,0xe7,0xdb,0x30,0x67,0x12,0x5f,0x83,0xdd};
    bool         a23_bits[256] = {true,false,true,true,true,false,true,true,true,true,false,false,false,false,false,true,true,true,true,true,true,false,true,false,false,true,false,false,true,false,false,false,true,true,true,false,false,true,true,false,false,false,false,false,true,true,false,false,true,true,false,true,true,false,true,true,true,true,true,false,false,true,true,true,true,true,true,false,true,false,true,true,true,false,true,false,true,false,true,true,false,true,false,false,false,true,false,false,false,true,true,false,false,false,true,false,true,false,false,true,false,false,true,false,false,true,false,false,false,false,false,true,false,true,false,true,true,true,false,true,true,false,false,false,true,false,true,false,true,false,false,true,true,false,true,true,true,true,false,true,false,true,false,false,true,true,true,true,true,true,true,true,true,false,false,true,false,false,true,true,false,false,true,false,true,false,false,true,false,true,true,true,false,false,false,false,false,false,true,true,true,true,false,false,true,true,true,true,true,true,false,false,false,true,false,false,true,false,true,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,false,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,false};
    uint256_from_bytes(a, a23_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a23_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a24_data[32]  = {0x79,0x90,0x6e,0x3a,0xaa,0x2a,0x46,0xb6,0xfe,0x98,0xf3,0x85,0x5f,0x39,0x41,0xef,0x3c,0x3e,0x57,0xa5,0x16,0x4b,0x8c,0x53,0x1a,0x8b,0x23,0xfc,0xb9,0x5e,0x90,0xf2};
    bool         a24_bits[256] = {false,true,false,false,true,true,true,true,false,false,false,false,true,false,false,true,false,true,true,true,true,false,true,false,true,false,false,true,true,true,false,true,false,false,true,true,true,true,true,true,true,true,false,false,false,true,false,false,true,true,false,true,false,false,false,true,false,true,false,true,true,false,false,false,true,true,false,false,true,false,true,false,false,false,true,true,false,false,false,true,true,true,false,true,false,false,true,false,false,true,true,false,true,false,false,false,true,false,true,false,false,true,false,true,true,true,true,false,true,false,true,false,false,true,true,true,true,true,false,false,false,false,true,true,true,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,false,false,true,false,true,false,false,true,true,true,false,false,true,true,true,true,true,false,true,false,true,false,true,false,false,false,false,true,true,true,false,false,true,true,true,true,false,false,false,true,true,false,false,true,false,true,true,true,true,true,true,true,false,true,true,false,true,true,false,true,false,true,true,false,false,false,true,false,false,true,false,true,false,true,false,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,false,false,false,true,true,true,false,true,true,false,false,false,false,false,true,false,false,true,true,false,false,true,true,true,true,false};
    uint256_from_bytes(a, a24_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a24_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a25_data[32]  = {0xcc,0xdc,0x63,0x0d,0x84,0x36,0xc5,0x46,0x5e,0x45,0xce,0xa6,0x7b,0x01,0x00,0x91,0x37,0x95,0x21,0xe8,0xa7,0x41,0x69,0x71,0x4f,0xc3,0x28,0x48,0x3c,0x90,0x1c,0x23};
    bool         a25_bits[256] = {true,true,false,false,false,true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,true,false,false,true,false,false,true,true,true,true,false,false,false,false,false,true,false,false,true,false,false,false,false,true,false,true,false,false,true,true,false,false,false,false,true,true,true,true,true,true,false,false,true,false,true,false,false,false,true,true,true,false,true,false,false,true,false,true,true,false,true,false,false,false,false,false,true,false,true,true,true,false,false,true,false,true,false,false,false,true,false,true,true,true,true,false,false,false,false,true,false,false,true,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,true,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,true,false,true,false,true,true,true,false,false,true,true,true,false,true,false,false,false,true,false,false,true,true,true,true,false,true,false,false,true,true,false,false,false,true,false,true,false,true,false,false,false,true,true,false,true,true,false,true,true,false,false,false,false,true,false,false,false,false,true,true,false,true,true,false,false,false,false,true,true,false,false,false,true,true,false,false,false,true,true,true,false,true,true,false,false,true,true,false,false,true,true};
    uint256_from_bytes(a, a25_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a25_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a26_data[32]  = {0x6c,0xe6,0x4c,0xa4,0x78,0xee,0x16,0xd6,0x5f,0x23,0x55,0x94,0x82,0xa3,0x04,0x7c,0x01,0xbc,0x67,0xb3,0xc9,0x3c,0x82,0xc9,0x17,0xd9,0xb3,0x9a,0x46,0x6f,0xfd,0x9f};
    bool         a26_bits[256] = {true,true,true,true,true,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,true,true,false,false,false,true,false,false,true,false,true,true,false,false,true,true,true,false,false,true,true,false,true,true,false,false,true,true,false,true,true,true,true,true,false,true,false,false,false,true,false,false,true,false,false,true,true,false,true,false,false,false,false,false,true,false,false,true,true,true,true,false,false,true,false,false,true,false,false,true,true,true,true,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,false,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,true,true,true,true,true,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,false,true,false,true,false,false,false,false,false,true,false,false,true,false,true,false,false,true,true,false,true,false,true,false,true,false,true,true,false,false,false,true,false,false,true,true,true,true,true,false,true,false,false,true,true,false,true,false,true,true,false,true,true,false,true,false,false,false,false,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,false,true,false,false,true,true,false,false,true,true,true,false,false,true,true,false,true,true,false};
    uint256_from_bytes(a, a26_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a26_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a27_data[32]  = {0x05,0x51,0xf4,0xd5,0x9d,0x8d,0x87,0x80,0xd0,0x58,0xd0,0xc2,0x34,0x79,0xef,0xea,0x74,0x2d,0xf6,0x89,0xa6,0x10,0x6c,0xdf,0x03,0x21,0x43,0x32,0xa8,0x13,0xd6,0x65};
    bool         a27_bits[256] = {true,false,true,false,false,true,true,false,false,true,true,false,true,false,true,true,true,true,false,false,true,false,false,false,false,false,false,true,false,true,false,true,false,true,false,false,true,true,false,false,true,true,false,false,false,false,true,false,true,false,false,false,false,true,false,false,true,true,false,false,false,false,false,false,true,true,true,true,true,false,true,true,false,false,true,true,false,true,true,false,false,false,false,false,true,false,false,false,false,true,true,false,false,true,false,true,true,false,false,true,false,false,false,true,false,true,true,false,true,true,true,true,true,false,true,true,false,true,false,false,false,false,true,false,true,true,true,false,false,true,false,true,false,true,true,true,true,true,true,true,false,true,true,true,true,false,false,true,true,true,true,false,false,false,true,false,true,true,false,false,false,true,false,false,false,false,true,true,false,false,false,false,true,false,true,true,false,false,false,true,true,false,true,false,false,false,false,false,true,false,true,true,false,false,false,false,false,false,false,true,true,true,true,false,false,false,false,true,true,false,true,true,false,false,false,true,true,false,true,true,true,false,false,true,true,false,true,false,true,false,true,true,false,false,true,false,true,true,true,true,true,false,false,false,true,false,true,false,true,false,true,false,false,false,false,false};
    uint256_from_bytes(a, a27_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a27_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a28_data[32]  = {0x66,0x0d,0xe9,0xe5,0x8d,0xf2,0x80,0xce,0x5d,0x6e,0x38,0x82,0x72,0x7d,0x00,0xd8,0x22,0xa5,0x02,0xf7,0xd2,0xca,0x21,0x6f,0x35,0x31,0xe1,0x1d,0x8b,0xa9,0x06,0xcb};
    bool         a28_bits[256] = {true,true,false,true,false,false,true,true,false,true,true,false,false,false,false,false,true,false,false,true,false,true,false,true,true,true,false,true,false,false,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,true,true,false,false,false,true,true,false,false,true,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,false,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,true,false,true,true,true,true,false,true,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,false,false,true,false,false,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,false,false,true,false,false,true,true,true,false,false,true,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,true,true,false,true,true,false,true,false,true,true,true,false,true,false,false,true,true,true,false,false,true,true,false,false,false,false,false,false,false,true,false,true,false,false,true,true,true,true,true,false,true,true,false,false,false,true,true,false,true,false,false,true,true,true,true,false,false,true,false,true,true,true,true,false,true,true,false,false,false,false,false,true,true,false,false,true,true,false};
    uint256_from_bytes(a, a28_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a28_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a29_data[32]  = {0xf9,0x9e,0xe8,0x82,0x45,0x46,0xb2,0xcd,0x71,0x3a,0xd2,0x2d,0x6f,0x8f,0x49,0x61,0xbc,0x21,0x97,0xef,0xa8,0x5d,0x47,0x30,0x53,0xf9,0x70,0x9a,0x70,0xbf,0xe5,0x92};
    bool         a29_bits[256] = {false,true,false,false,true,false,false,true,true,false,true,false,false,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,true,true,true,false,false,true,false,true,true,false,false,true,false,false,false,false,true,true,true,false,true,false,false,true,true,true,true,true,true,true,false,false,true,false,true,false,false,false,false,false,true,true,false,false,true,true,true,false,false,false,true,false,true,false,true,true,true,false,true,false,false,false,false,true,false,true,false,true,true,true,true,true,false,true,true,true,true,true,true,false,true,false,false,true,true,false,false,false,false,true,false,false,false,false,true,true,true,true,false,true,true,false,false,false,false,true,true,false,true,false,false,true,false,false,true,false,true,true,true,true,false,false,false,true,true,true,true,true,false,true,true,false,true,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,false,true,false,true,true,true,false,false,true,false,false,false,true,true,true,false,true,false,true,true,false,false,true,true,false,true,false,false,true,true,false,true,false,true,true,false,false,false,true,false,true,false,true,false,false,false,true,false,false,true,false,false,false,false,false,true,false,false,false,true,false,true,true,true,false,true,true,true,true,false,false,true,true,false,false,true,true,true,true,true};
    uint256_from_bytes(a, a29_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a29_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a30_data[32]  = {0x1e,0x7c,0xc4,0xbc,0x7e,0x3a,0x52,0xe2,0xe0,0xfe,0x9b,0xbc,0x1d,0xd0,0x6e,0x33,0x7d,0xc5,0xd5,0x8a,0xc2,0x24,0x97,0xca,0x4d,0x64,0x1f,0x06,0xca,0xaa,0xa3,0x81};
    bool         a30_bits[256] = {true,false,false,false,false,false,false,true,true,true,false,false,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,false,true,true,false,true,true,false,false,false,false,false,true,true,true,true,true,false,false,false,false,false,true,false,false,true,true,false,true,false,true,true,false,false,true,false,false,true,false,true,false,false,true,true,true,true,true,false,true,false,false,true,false,false,true,false,false,true,false,false,false,true,false,false,false,false,true,true,false,true,false,true,false,false,false,true,true,false,true,false,true,false,true,true,true,false,true,false,false,false,true,true,true,false,true,true,true,true,true,false,true,true,false,false,true,true,false,false,false,true,true,true,false,true,true,false,false,false,false,false,true,false,true,true,true,false,true,true,true,false,false,false,false,false,true,true,true,true,false,true,true,true,false,true,true,false,false,true,false,true,true,true,true,true,true,true,false,false,false,false,false,true,true,true,false,true,false,false,false,true,true,true,false,true,false,false,true,false,true,false,false,true,false,true,true,true,false,false,false,true,true,true,true,true,true,false,false,false,true,true,true,true,false,true,false,false,true,false,false,false,true,true,false,false,true,true,true,true,true,false,false,true,true,true,true,false,false,false};
    uint256_from_bytes(a, a30_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a30_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a31_data[32]  = {0x32,0x3d,0x85,0x9c,0xcd,0x7c,0xe1,0x44,0x5b,0x31,0x89,0x83,0x19,0xa7,0x77,0x51,0xfb,0x8f,0x32,0x7b,0xbb,0x64,0x10,0xdc,0xbc,0xdc,0xa6,0x1e,0xf0,0xfe,0x99,0xaa};
    bool         a31_bits[256] = {false,true,false,true,false,true,false,true,true,false,false,true,true,false,false,true,false,true,true,true,true,true,true,true,false,false,false,false,true,true,true,true,false,true,true,true,true,false,false,false,false,true,true,false,false,true,false,true,false,false,true,true,true,false,true,true,false,false,true,true,true,true,false,true,false,false,true,true,true,false,true,true,false,false,false,false,true,false,false,false,false,false,true,false,false,true,true,false,true,true,false,true,true,true,false,true,true,true,false,true,true,true,true,false,false,true,false,false,true,true,false,false,true,true,true,true,false,false,false,true,true,true,false,true,true,true,true,true,true,false,false,false,true,false,true,false,true,true,true,false,true,true,true,false,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,false,true,true,false,false,false,false,false,true,true,false,false,true,false,false,false,true,true,false,false,false,true,true,false,false,true,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,true,false,false,false,false,true,true,true,false,false,true,true,true,true,true,false,true,false,true,true,false,false,true,true,false,false,true,true,true,false,false,true,true,false,true,false,false,false,false,true,true,false,true,true,true,true,false,false,false,true,false,false,true,true,false,false};
    uint256_from_bytes(a, a31_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a31_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a32_data[32]  = {0xbe,0xb3,0x8a,0xa5,0x3e,0xa3,0x70,0x17,0xd0,0xa2,0x4b,0xaa,0x44,0x46,0xb1,0xe3,0x28,0xdd,0x7f,0xba,0xc1,0xb7,0x68,0xb2,0x53,0x9f,0xa9,0xfb,0xc4,0x59,0x4a,0x1d};
    bool         a32_bits[256] = {true,false,true,true,true,false,false,false,false,true,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,false,true,false,false,false,true,true,true,true,false,true,true,true,true,true,true,false,false,true,false,true,false,true,true,true,true,true,true,false,false,true,true,true,false,false,true,false,true,false,false,true,false,false,true,true,false,true,false,false,false,true,false,true,true,false,true,true,true,false,true,true,false,true,true,false,false,false,false,false,true,true,false,true,false,true,true,true,false,true,true,true,true,true,true,true,true,false,true,false,true,true,true,false,true,true,false,false,false,true,false,true,false,false,true,true,false,false,false,true,true,true,true,false,false,false,true,true,false,true,false,true,true,false,false,false,true,false,false,false,true,false,false,false,true,false,false,true,false,true,false,true,false,true,true,true,false,true,false,false,true,false,false,true,false,false,false,true,false,true,false,false,false,false,true,false,true,true,true,true,true,false,true,false,false,false,false,false,false,false,true,true,true,false,true,true,false,false,false,true,false,true,false,true,true,true,true,true,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,true,true,true,false,false,true,true,false,true,false,true,true,true,true,true,false,true};
    uint256_from_bytes(a, a32_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a32_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a33_data[32]  = {0xd4,0x33,0x60,0xb6,0xaa,0xeb,0x6b,0xfc,0xcd,0xad,0xff,0x1d,0x4c,0x5d,0xa8,0x4b,0x32,0xbc,0xf4,0xdd,0x91,0x64,0xbe,0x12,0xb0,0x6f,0x4c,0x6f,0x28,0x98,0x5a,0x33};
    bool         a33_bits[256] = {true,true,false,false,true,true,false,false,false,true,false,true,true,false,true,false,false,false,false,true,true,false,false,true,false,false,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,false,true,true,false,false,true,false,true,true,true,true,false,true,true,false,false,false,false,false,true,true,false,true,false,true,false,false,true,false,false,false,false,true,true,true,true,true,false,true,false,false,true,false,false,true,true,false,true,false,false,false,true,false,false,true,true,false,true,true,true,false,true,true,false,false,true,false,true,true,true,true,false,false,true,true,true,true,false,true,false,true,false,false,true,true,false,false,true,true,false,true,false,false,true,false,false,false,false,true,false,true,false,true,true,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,true,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,true,true,false,true,false,true,true,false,true,true,false,false,true,true,false,false,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,true,false,true,true,true,false,true,false,true,false,true,false,true,false,true,true,false,true,true,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,true,false,false,false,false,true,false,true,false,true,true};
    uint256_from_bytes(a, a33_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a33_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a34_data[32]  = {0x53,0x2d,0x31,0x6a,0x55,0x76,0xcb,0x7f,0xf9,0x0a,0x34,0x67,0x9a,0xb1,0x17,0x06,0x66,0x35,0x59,0x7e,0xc1,0xb5,0xe3,0x80,0x26,0xe8,0x5a,0x71,0xd2,0xe2,0xc6,0x10};
    bool         a34_bits[256] = {false,false,false,false,true,false,false,false,false,true,true,false,false,false,true,true,false,true,false,false,false,true,true,true,false,true,false,false,true,false,true,true,true,false,false,false,true,true,true,false,false,true,false,true,true,false,true,false,false,false,false,true,false,true,true,true,false,true,true,false,false,true,false,false,false,false,false,false,false,false,false,true,true,true,false,false,false,true,true,true,true,false,true,false,true,true,false,true,true,false,false,false,false,false,true,true,false,true,true,true,true,true,true,false,true,false,false,true,true,false,true,false,true,false,true,false,true,true,false,false,false,true,true,false,false,true,true,false,false,true,true,false,false,false,false,false,true,true,true,false,true,false,false,false,true,false,false,false,true,true,false,true,false,true,false,true,true,false,false,true,true,true,true,false,false,true,true,false,false,false,true,false,true,true,false,false,false,true,false,true,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,true,false,false,true,true,false,true,true,false,true,true,true,false,true,false,true,false,true,false,true,false,false,true,false,true,false,true,true,false,true,false,false,false,true,true,false,false,true,false,true,true,false,true,false,false,true,true,false,false,true,false,true,false};
    uint256_from_bytes(a, a34_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a34_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a35_data[32]  = {0xa4,0x0d,0xc0,0x5f,0x7a,0x13,0x28,0x8d,0xd5,0xc1,0x66,0xb8,0xbd,0x5c,0x9b,0x9c,0x29,0x60,0xf8,0x48,0x56,0x97,0x26,0x95,0x1d,0x3b,0x85,0x83,0x93,0xac,0x68,0xa1};
    bool         a35_bits[256] = {true,false,false,false,false,true,false,true,false,false,false,true,false,true,true,false,false,false,true,true,false,true,false,true,true,true,false,false,true,false,false,true,true,true,false,false,false,false,false,true,true,false,true,false,false,false,false,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,false,false,true,false,true,false,true,false,false,true,false,true,true,false,false,true,false,false,true,true,true,false,true,false,false,true,false,true,true,false,true,false,true,false,false,false,false,true,false,false,true,false,false,false,false,true,true,true,true,true,false,false,false,false,false,true,true,false,true,false,false,true,false,true,false,false,false,false,true,true,true,false,false,true,true,true,false,true,true,false,false,true,false,false,true,true,true,false,true,false,true,false,true,true,true,true,false,true,false,false,false,true,true,true,false,true,false,true,true,false,false,true,true,false,true,false,false,false,false,false,true,true,true,false,true,false,true,false,true,true,true,false,true,true,false,false,false,true,false,false,false,true,false,true,false,false,true,true,false,false,true,false,false,false,false,true,false,true,true,true,true,false,true,true,true,true,true,false,true,false,false,false,false,false,false,false,true,true,true,false,true,true,false,false,false,false,false,false,true,false,false,true,false,true};
    uint256_from_bytes(a, a35_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a35_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a36_data[32]  = {0x86,0xa1,0x74,0xa4,0x17,0x84,0xbb,0x96,0xd3,0x82,0x73,0xad,0x06,0x1f,0xcb,0x0f,0x64,0x89,0x22,0xb9,0xb1,0x39,0xbb,0x8a,0x91,0x3a,0x54,0x3c,0xb6,0x22,0xfc,0x00};
    bool         a36_bits[256] = {false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,false,true,false,false,false,true,false,false,false,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,false,false,true,false,true,false,true,false,false,true,false,true,true,true,false,false,true,false,false,false,true,false,false,true,false,true,false,true,false,false,false,true,true,true,false,true,true,true,false,true,true,false,false,true,true,true,false,false,true,false,false,false,true,true,false,true,true,false,false,true,true,true,false,true,false,true,false,false,false,true,false,false,true,false,false,true,false,false,false,true,false,false,true,false,false,true,true,false,true,true,true,true,false,false,false,false,true,true,false,true,false,false,true,true,true,true,true,true,true,false,false,false,false,true,true,false,false,false,false,false,true,false,true,true,false,true,false,true,true,true,false,false,true,true,true,false,false,true,false,false,false,false,false,true,true,true,false,false,true,false,true,true,false,true,true,false,true,false,false,true,true,true,false,true,true,true,false,true,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,false,false,false,true,false,false,true,false,true,false,false,true,false,true,true,true,false,true,false,false,false,false,true,false,true,false,true,true,false,false,false,false,true};
    uint256_from_bytes(a, a36_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a36_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a37_data[32]  = {0x84,0x43,0xbf,0xf2,0xf5,0x45,0x18,0xe8,0x2c,0x6c,0x27,0xdc,0xcd,0x02,0x92,0xdb,0xd1,0xf0,0xe5,0xef,0xb7,0x06,0x69,0xe3,0x56,0x58,0x44,0xc0,0x36,0x3a,0x73,0x98};
    bool         a37_bits[256] = {false,false,false,true,true,false,false,true,true,true,false,false,true,true,true,false,false,true,false,true,true,true,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,false,true,true,false,false,true,false,false,false,true,false,false,false,false,true,true,false,true,false,false,true,true,false,true,false,true,false,true,true,false,false,false,true,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,false,false,false,true,true,true,false,true,true,false,true,true,true,true,true,false,true,true,true,true,false,true,false,false,true,true,true,false,false,false,false,true,true,true,true,true,false,false,false,true,false,true,true,true,true,false,true,true,false,true,true,false,true,false,false,true,false,false,true,false,true,false,false,false,false,false,false,true,false,true,true,false,false,true,true,false,false,true,true,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,true,false,true,true,false,false,false,true,true,false,true,false,false,false,false,false,true,false,true,true,true,false,false,false,true,true,false,false,false,true,false,true,false,false,false,true,false,true,false,true,false,true,true,true,true,false,true,false,false,true,true,true,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,true,false,false,false,true,false,false,false,false,true};
    uint256_from_bytes(a, a37_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a37_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a38_data[32]  = {0xb6,0x91,0xe9,0xf7,0xc5,0x30,0x6c,0x18,0x5e,0xbc,0x69,0xd8,0x40,0xba,0x0e,0x6f,0x44,0x0e,0x77,0x78,0xdf,0xb7,0x9b,0x4b,0x37,0xa7,0x3d,0x24,0x35,0x6c,0xb9,0xff};
    bool         a38_bits[256] = {true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,true,false,false,true,true,false,true,true,false,true,false,true,false,true,true,false,false,false,false,true,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,true,false,false,true,false,true,true,true,true,false,true,true,false,false,true,true,false,true,false,false,true,false,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,false,false,true,true,true,true,false,true,true,true,false,true,true,true,false,false,true,true,true,false,false,false,false,false,false,true,false,false,false,true,false,true,true,true,true,false,true,true,false,false,true,true,true,false,false,false,false,false,true,false,true,true,true,false,true,false,false,false,false,false,false,true,false,false,false,false,true,true,false,true,true,true,false,false,true,false,true,true,false,false,false,true,true,true,true,false,true,false,true,true,true,true,false,true,false,false,false,false,true,true,false,false,false,false,false,true,true,false,true,true,false,false,false,false,false,true,true,false,false,true,false,true,false,false,false,true,true,true,true,true,false,true,true,true,true,true,false,false,true,false,true,true,true,true,false,false,false,true,false,false,true,false,true,true,false,true,true,false,true};
    uint256_from_bytes(a, a38_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a38_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a39_data[32]  = {0xf6,0x10,0x59,0x91,0x66,0x8a,0xcc,0x52,0xa6,0x6a,0x2f,0xe0,0xc4,0xba,0x4a,0x1f,0x19,0xf2,0x60,0xab,0xc4,0x33,0x16,0x74,0xc6,0x47,0xd2,0xc4,0x98,0xb8,0x47,0x75};
    bool         a39_bits[256] = {true,false,true,false,true,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,false,true,false,false,false,true,true,false,true,false,false,true,false,true,true,true,true,true,false,false,false,true,false,false,true,true,false,false,false,true,true,false,false,true,false,true,true,true,false,false,true,true,false,true,false,false,false,true,true,false,false,true,true,false,false,false,false,true,false,false,false,true,true,true,true,false,true,false,true,false,true,false,false,false,false,false,true,true,false,false,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,true,true,true,true,false,false,false,false,true,false,true,false,false,true,false,false,true,false,true,true,true,false,true,false,false,true,false,false,false,true,true,false,false,false,false,false,true,true,true,true,true,true,true,false,true,false,false,false,true,false,true,false,true,true,false,false,true,true,false,false,true,false,true,false,true,false,false,true,false,true,false,false,false,true,true,false,false,true,true,false,true,false,true,false,false,false,true,false,true,true,false,false,true,true,false,true,false,false,false,true,false,false,true,true,false,false,true,true,false,true,false,false,false,false,false,true,false,false,false,false,true,true,false,true,true,true,true};
    uint256_from_bytes(a, a39_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a39_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a40_data[32]  = {0xf9,0xc6,0xca,0x9b,0xee,0xd8,0x81,0xae,0x3d,0x78,0x42,0x09,0x14,0x9d,0x17,0xbb,0x0a,0x64,0xe3,0xed,0x83,0xbb,0xfa,0xdb,0x0a,0x50,0xa8,0xfd,0x25,0xf5,0x1d,0x96};
    bool         a40_bits[256] = {false,true,true,false,true,false,false,true,true,false,true,true,true,false,false,false,true,false,true,false,true,true,true,true,true,false,true,false,false,true,false,false,true,false,true,true,true,true,true,true,false,false,false,true,false,true,false,true,false,false,false,false,true,false,true,false,false,true,false,true,false,false,false,false,true,true,false,true,true,false,true,true,false,true,false,true,true,true,true,true,true,true,false,true,true,true,false,true,true,true,false,false,false,false,false,true,true,false,true,true,false,true,true,true,true,true,false,false,false,true,true,true,false,false,true,false,false,true,true,false,false,true,false,true,false,false,false,false,true,true,false,true,true,true,false,true,true,true,true,false,true,false,false,false,true,false,true,true,true,false,false,true,false,false,true,false,true,false,false,false,true,false,false,true,false,false,false,false,false,true,false,false,false,false,true,false,false,false,false,true,true,true,true,false,true,false,true,true,true,true,false,false,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,false,true,true,true,false,true,true,true,true,true,false,true,true,false,false,true,false,true,false,true,false,false,true,true,false,true,true,false,false,false,true,true,true,false,false,true,true,true,true,true};
    uint256_from_bytes(a, a40_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a40_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a41_data[32]  = {0xdc,0xf3,0xb6,0xf3,0xd2,0x0d,0xb1,0x9e,0x35,0xa4,0x66,0x73,0xcd,0xe4,0x1a,0x3c,0x4a,0x92,0xb1,0x04,0xa0,0x40,0xf5,0x91,0x14,0x7d,0x03,0x76,0x92,0xbe,0xbb,0xce};
    bool         a41_bits[256] = {false,true,true,true,false,false,true,true,true,true,false,true,true,true,false,true,false,true,true,true,true,true,false,true,false,true,false,false,true,false,false,true,false,true,true,false,true,true,true,false,true,true,false,false,false,false,false,false,true,false,true,true,true,true,true,false,false,false,true,false,true,false,false,false,true,false,false,false,true,false,false,true,true,false,true,false,true,true,true,true,false,false,false,false,false,false,true,false,false,false,false,false,false,true,false,true,false,false,true,false,false,false,false,false,true,false,false,false,true,true,false,true,false,true,false,false,true,false,false,true,false,true,false,true,false,false,true,false,false,false,true,true,true,true,false,false,false,true,false,true,true,false,false,false,false,false,true,false,false,true,true,true,true,false,true,true,false,false,true,true,true,true,false,false,true,true,true,false,false,true,true,false,false,true,true,false,false,false,true,false,false,true,false,true,true,false,true,false,true,true,false,false,false,true,true,true,true,false,false,true,true,false,false,false,true,true,false,true,true,false,true,true,false,false,false,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,true,true,false,true,true,false,true,true,false,true,true,true,false,false,true,true,true,true,false,false,true,true,true,false,true,true};
    uint256_from_bytes(a, a41_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a41_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a42_data[32]  = {0x6c,0xcb,0x13,0x5d,0x9b,0x2e,0xb9,0x09,0xe6,0x34,0x85,0x1c,0x0d,0x71,0xe6,0x0d,0x33,0xda,0x33,0xe7,0x0e,0xe4,0x58,0x4a,0x85,0x6a,0x11,0x77,0xf4,0x62,0x15,0xfe};
    bool         a42_bits[256] = {false,true,true,true,true,true,true,true,true,false,true,false,true,false,false,false,false,true,false,false,false,true,true,false,false,false,true,false,true,true,true,true,true,true,true,false,true,true,true,false,true,false,false,false,true,false,false,false,false,true,false,true,false,true,true,false,true,false,true,false,false,false,false,true,false,true,false,true,false,false,true,false,false,false,false,true,true,false,true,false,false,false,true,false,false,true,true,true,false,true,true,true,false,false,false,false,true,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,false,true,true,false,true,true,true,true,false,false,true,true,false,false,true,false,true,true,false,false,false,false,false,true,true,false,false,true,true,true,true,false,false,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,true,true,false,false,false,true,false,true,false,false,false,false,true,false,false,true,false,true,true,false,false,false,true,true,false,false,true,true,true,true,false,false,true,false,false,false,false,true,false,false,true,true,true,false,true,false,true,true,true,false,true,false,false,true,true,false,true,true,false,false,true,true,false,true,true,true,false,true,false,true,true,false,false,true,false,false,false,true,true,false,true,false,false,true,true,false,false,true,true,false,true,true,false};
    uint256_from_bytes(a, a42_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a42_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a43_data[32]  = {0xd8,0xd8,0x3c,0xb0,0x81,0xe0,0xcf,0x39,0xb2,0x21,0x8b,0x98,0xd0,0xe2,0x8f,0xaa,0x70,0xb5,0xae,0xef,0x50,0xb6,0x59,0x7e,0x90,0x96,0x7d,0xe0,0x40,0x82,0xc7,0x23};
    bool         a43_bits[256] = {true,true,false,false,false,true,false,false,true,true,true,false,false,false,true,true,false,true,false,false,false,false,false,true,false,false,false,false,false,false,true,false,false,false,false,false,false,true,true,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,false,true,false,false,false,false,true,false,false,true,false,true,true,true,true,true,true,false,true,false,false,true,true,false,true,false,false,true,true,false,true,true,false,true,false,false,false,false,true,false,true,false,true,true,true,true,false,true,true,true,false,true,true,true,false,true,false,true,true,false,true,false,true,true,false,true,false,false,false,false,true,true,true,false,false,true,false,true,false,true,false,true,true,true,true,true,false,false,false,true,false,true,false,false,false,true,true,true,false,false,false,false,true,false,true,true,false,false,false,true,true,false,false,true,true,true,false,true,false,false,false,true,true,false,false,false,false,true,false,false,false,true,false,false,true,true,false,true,true,false,false,true,true,true,false,false,true,true,true,true,false,false,true,true,false,false,false,false,false,true,true,true,true,false,false,false,false,false,false,true,false,false,false,false,true,true,false,true,false,false,true,true,true,true,false,false,false,false,false,true,true,false,true,true,false,false,false,true,true,false,true,true};
    uint256_from_bytes(a, a43_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a43_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a44_data[32]  = {0x6f,0x32,0x27,0x27,0xfc,0x1b,0xf5,0xeb,0x79,0xa2,0xcc,0x4c,0x1e,0x23,0xca,0x0b,0xd0,0xd4,0x25,0x25,0x6d,0x91,0x94,0x43,0x83,0x99,0x43,0xa0,0x96,0xbb,0xc5,0x6d};
    bool         a44_bits[256] = {true,false,true,true,false,true,true,false,true,false,true,false,false,false,true,true,true,true,false,true,true,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,false,true,false,true,true,true,false,false,false,false,true,false,true,false,false,true,true,false,false,true,true,true,false,false,false,false,false,true,true,true,false,false,false,false,true,false,false,false,true,false,true,false,false,true,true,false,false,false,true,false,false,true,true,false,true,true,false,true,true,false,true,false,true,false,false,true,false,false,true,false,true,false,false,true,false,false,false,false,true,false,true,false,true,true,false,false,false,false,true,false,true,true,true,true,false,true,false,false,false,false,false,true,false,true,false,false,true,true,true,true,false,false,false,true,false,false,false,true,true,true,true,false,false,false,false,false,true,true,false,false,true,false,false,false,true,true,false,false,true,true,false,true,false,false,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,false,true,true,true,true,false,true,false,true,true,true,true,true,true,false,true,true,false,false,false,false,false,true,true,true,true,true,true,true,true,true,false,false,true,false,false,true,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,true,true,true,true,false,true,true,false};
    uint256_from_bytes(a, a44_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a44_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a45_data[32]  = {0x62,0xfc,0x04,0x8b,0xac,0xda,0xa4,0x55,0x89,0xb4,0x59,0xea,0x0f,0x28,0x31,0xb2,0x61,0x01,0x89,0x91,0xdc,0xde,0x57,0x4c,0xd3,0xe7,0xfb,0x18,0x0b,0x6e,0x3e,0x41};
    bool         a45_bits[256] = {true,false,false,false,false,false,true,false,false,true,true,true,true,true,false,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,false,false,false,false,false,true,true,false,false,false,true,true,false,true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,true,false,true,true,true,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,true,true,true,false,true,true,true,false,false,false,true,false,false,true,true,false,false,true,false,false,false,true,true,false,false,false,false,false,false,false,true,false,false,false,false,true,true,false,false,true,false,false,true,true,false,true,true,false,false,false,true,true,false,false,false,false,false,true,false,true,false,false,true,true,true,true,false,false,false,false,false,true,false,true,false,true,true,true,true,false,false,true,true,false,true,false,false,false,true,false,true,true,false,true,true,false,false,true,false,false,false,true,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,true,false,true,false,true,true,false,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,false,false,false,false,false,true,true,true,true,true,true,false,true,false,false,false,true,true,false};
    uint256_from_bytes(a, a45_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a45_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a46_data[32]  = {0x41,0x50,0x93,0xe7,0x43,0x68,0x90,0x0c,0x0a,0x53,0xb3,0xd3,0x47,0xd8,0x8b,0xd8,0x2c,0xfc,0x03,0x5c,0xe3,0xd5,0x5d,0x19,0xec,0x90,0x0a,0xdb,0x51,0x27,0x90,0x4f};
    bool         a46_bits[256] = {true,true,true,true,false,false,true,false,false,false,false,false,true,false,false,true,true,true,true,false,false,true,false,false,true,false,false,false,true,false,true,false,true,true,false,true,true,false,true,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,true,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,false,true,false,true,true,true,false,true,false,true,false,true,false,true,false,true,true,true,true,false,false,false,true,true,true,false,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,false,false,true,true,true,true,true,true,false,false,true,true,false,true,false,false,false,false,false,true,true,false,true,true,true,true,false,true,false,false,false,true,false,false,false,true,true,false,true,true,true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,true,true,true,false,false,true,true,false,true,true,true,false,false,true,false,true,false,false,true,false,true,false,false,false,false,false,false,true,true,false,false,false,false,false,false,false,false,true,false,false,true,false,false,false,true,false,true,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,true,true,true,true,false,false,true,false,false,true,false,false,false,false,true,false,true,false,true,false,false,false,false,false,true,false};
    uint256_from_bytes(a, a46_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a46_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a47_data[32]  = {0xeb,0xae,0x14,0xea,0xd3,0x39,0xff,0xd3,0xed,0x0f,0x5c,0x03,0x19,0x5d,0x5e,0xe5,0xa3,0x44,0xe1,0xf8,0x59,0x49,0x7f,0x77,0x51,0x7d,0x7c,0xb1,0x1e,0x4f,0xf1,0xfb};
    bool         a47_bits[256] = {true,true,false,true,true,true,true,true,true,false,false,false,true,true,true,true,true,true,true,true,false,false,true,false,false,true,true,true,true,false,false,false,true,false,false,false,true,true,false,true,false,false,true,true,true,true,true,false,true,false,true,true,true,true,true,false,true,false,false,false,true,false,true,false,true,true,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,false,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,false,false,true,true,true,true,true,true,false,false,false,false,true,true,true,false,false,true,false,false,false,true,false,true,true,false,false,false,true,false,true,true,false,true,false,false,true,true,true,false,true,true,true,true,false,true,false,true,false,true,true,true,false,true,false,true,false,false,true,true,false,false,false,true,true,false,false,false,false,false,false,false,false,true,true,true,false,true,false,true,true,true,true,false,false,false,false,true,false,true,true,false,true,true,true,true,true,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,false,true,true,false,false,true,false,true,true,false,true,false,true,false,true,true,true,false,false,true,false,true,false,false,false,false,true,true,true,false,true,false,true,true,true,false,true,false,true,true,true};
    uint256_from_bytes(a, a47_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a47_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a48_data[32]  = {0x77,0x11,0x62,0x88,0xb7,0xef,0xb4,0x81,0x67,0xfa,0x01,0xe0,0xc4,0xde,0x03,0x9f,0xaa,0x81,0x91,0xac,0x90,0xba,0xce,0x21,0x02,0xd8,0x51,0xc1,0x34,0x8b,0xef,0xa2};
    bool         a48_bits[256] = {false,true,false,false,false,true,false,true,true,true,true,true,false,true,true,true,true,true,false,true,false,false,false,true,false,false,true,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,false,false,true,false,true,false,false,false,false,true,true,false,true,true,false,true,false,false,false,false,false,false,true,false,false,false,false,true,false,false,false,true,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,false,false,false,true,false,false,true,false,false,true,true,false,true,false,true,true,false,false,false,true,false,false,true,true,false,false,false,false,false,false,true,false,true,false,true,false,true,false,true,true,true,true,true,true,false,false,true,true,true,false,false,false,false,false,false,false,true,true,true,true,false,true,true,false,false,true,false,false,false,true,true,false,false,false,false,false,true,true,true,true,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,false,false,true,true,false,true,false,false,false,false,false,false,true,false,false,true,false,true,true,false,true,true,true,true,true,false,true,true,true,true,true,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,true,false,false,false,true,true,false,true,false,false,false,true,false,false,false,true,true,true,false,true,true,true,false};
    uint256_from_bytes(a, a48_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a48_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a49_data[32]  = {0x06,0xf9,0xa3,0xdd,0x48,0x3f,0x97,0xe9,0x16,0x4f,0x95,0xcd,0x83,0xd7,0xe6,0xe2,0x54,0xc1,0x82,0x44,0x87,0x88,0x1b,0x16,0x9c,0x01,0xae,0xea,0x09,0x15,0xe9,0x19};
    bool         a49_bits[256] = {true,false,false,true,true,false,false,false,true,false,false,true,false,true,true,true,true,false,true,false,true,false,false,false,true,false,false,true,false,false,false,false,false,true,false,true,false,true,true,true,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,false,false,false,true,true,true,false,false,true,false,true,true,false,true,false,false,false,true,true,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,true,true,false,false,false,false,true,false,false,true,false,false,false,true,false,false,true,false,false,false,false,false,true,true,false,false,false,false,false,true,true,false,false,true,false,true,false,true,false,false,true,false,false,false,true,true,true,false,true,true,false,false,true,true,true,true,true,true,false,true,false,true,true,true,true,false,false,false,false,false,true,true,false,true,true,false,false,true,true,true,false,true,false,true,false,false,true,true,true,true,true,false,false,true,false,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,true,true,true,true,false,true,false,false,true,true,true,true,true,true,true,false,false,false,false,false,true,false,false,true,false,true,false,true,true,true,false,true,true,true,true,false,false,false,true,false,true,true,false,false,true,true,true,true,true,false,true,true,false,false,false,false,false};
    uint256_from_bytes(a, a49_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a49_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a50_data[32]  = {0x25,0x24,0xc5,0xc4,0x71,0x01,0x1d,0x9b,0xd4,0x40,0xa2,0x51,0x69,0x85,0xf0,0x7c,0xbf,0xe0,0x8b,0x5f,0x76,0x59,0xa4,0xf1,0x15,0x28,0xe8,0x27,0x2b,0xb3,0x65,0x8b};
    bool         a50_bits[256] = {true,true,false,true,false,false,false,true,true,false,true,false,false,true,true,false,true,true,false,false,true,true,false,true,true,true,false,true,false,true,false,false,true,true,true,false,false,true,false,false,false,false,false,true,false,true,true,true,false,false,false,true,false,true,false,false,true,false,true,false,true,false,false,false,true,false,false,false,true,true,true,true,false,false,true,false,false,true,false,true,true,false,false,true,true,false,true,false,false,true,true,false,true,true,true,false,true,true,true,true,true,false,true,false,true,true,false,true,false,false,false,true,false,false,false,false,false,true,true,true,true,true,true,true,true,true,false,true,false,false,true,true,true,true,true,false,false,false,false,false,true,true,true,true,true,false,true,false,false,false,false,true,true,false,false,true,false,true,true,false,true,false,false,false,true,false,true,false,false,true,false,false,false,true,false,true,false,false,false,false,false,false,true,false,false,false,true,false,true,false,true,true,true,true,false,true,true,false,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,false,true,false,false,true,false,true,false,false,true,false,false};
    uint256_from_bytes(a, a50_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a50_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a51_data[32]  = {0x93,0x8a,0xc2,0x36,0x68,0xe6,0xe0,0xc2,0x5a,0xe1,0x34,0xb1,0x82,0x1b,0x5c,0x53,0x47,0xe2,0xb4,0x8e,0xfd,0x44,0x48,0x68,0x78,0xf1,0xd5,0x70,0x25,0x2f,0xfe,0xfe};
    bool         a51_bits[256] = {false,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,true,false,true,false,false,true,false,false,false,false,false,false,true,true,true,false,true,false,true,false,true,false,true,true,true,false,false,false,true,true,true,true,false,false,false,true,true,true,true,false,false,false,false,true,false,true,true,false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true,false,true,false,true,true,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,false,true,false,true,false,false,false,true,true,true,true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,false,false,false,true,true,true,false,true,false,true,true,false,true,true,false,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,true,false,true,false,false,true,false,true,true,false,false,true,false,false,false,false,true,true,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,true,true,false,false,false,false,false,true,true,true,false,true,true,false,false,true,true,true,false,false,false,true,false,true,true,false,false,true,true,false,true,true,false,false,false,true,false,false,false,false,true,true,false,true,false,true,false,false,false,true,true,true,false,false,true,false,false,true};
    uint256_from_bytes(a, a51_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a51_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a52_data[32]  = {0xdc,0x03,0xb9,0x50,0x26,0x12,0x04,0xc2,0xa7,0xba,0x14,0x21,0xe2,0x6f,0x37,0xc7,0x33,0x7f,0xff,0x45,0xb2,0x19,0x35,0xfc,0x36,0xdb,0x2f,0xad,0x07,0xc2,0x72,0xe2};
    bool         a52_bits[256] = {false,true,false,false,false,true,true,true,false,true,false,false,true,true,true,false,false,true,false,false,false,false,true,true,true,true,true,false,false,false,false,false,true,false,true,true,false,true,false,true,true,true,true,true,false,true,false,false,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,false,false,false,true,true,true,true,true,true,true,false,true,false,true,true,false,false,true,false,false,true,true,false,false,false,false,true,false,false,true,true,false,true,true,false,true,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,true,true,false,false,true,true,true,false,false,false,true,true,true,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,false,true,false,false,false,true,true,true,true,false,false,false,false,true,false,false,false,false,true,false,true,false,false,false,false,true,false,true,true,true,false,true,true,true,true,false,false,true,false,true,false,true,false,false,false,false,true,true,false,false,true,false,false,false,false,false,false,true,false,false,true,false,false,false,false,true,true,false,false,true,false,false,false,false,false,false,true,false,true,false,true,false,false,true,true,true,false,true,true,true,false,false,false,false,false,false,false,false,true,true,true,false,true,true};
    uint256_from_bytes(a, a52_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a52_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a53_data[32]  = {0xb5,0x38,0x3e,0x5c,0x06,0xf8,0x4a,0x42,0x88,0xe6,0xc9,0x13,0xc3,0x33,0xd8,0x87,0x7c,0xfe,0x12,0x27,0x6e,0x22,0x76,0x49,0xab,0xd8,0xb7,0x46,0x42,0x82,0xa6,0xc6};
    bool         a53_bits[256] = {false,true,true,false,false,false,true,true,false,true,true,false,false,true,false,true,false,true,false,false,false,false,false,true,false,true,false,false,false,false,true,false,false,true,true,false,false,false,true,false,true,true,true,false,true,true,false,true,false,false,false,true,true,false,true,true,true,true,false,true,false,true,false,true,true,false,false,true,false,false,true,false,false,true,true,false,true,true,true,false,false,true,false,false,false,true,false,false,false,true,true,true,false,true,true,false,true,true,true,false,false,true,false,false,false,true,false,false,true,false,false,false,false,true,true,true,true,true,true,true,false,false,true,true,true,true,true,false,true,true,true,false,false,false,false,true,false,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,true,true,false,false,false,false,true,true,true,true,false,false,true,false,false,false,true,false,false,true,false,false,true,true,false,true,true,false,false,true,true,true,false,false,false,true,false,false,false,true,false,true,false,false,false,false,true,false,false,true,false,true,false,false,true,false,false,false,false,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,true,true,true,false,true,false,false,true,true,true,true,true,false,false,false,false,false,true,true,true,false,false,true,false,true,false,true,true,false,true};
    uint256_from_bytes(a, a53_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a53_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a54_data[32]  = {0x0b,0x72,0xc7,0xc2,0xb2,0xe8,0x05,0x99,0x83,0xb5,0x71,0xf7,0x34,0x04,0xb5,0x24,0x21,0x7c,0x79,0x30,0x4c,0xea,0xd5,0x28,0xfc,0x4d,0x44,0x32,0xe2,0xf1,0xc9,0xda};
    bool         a54_bits[256] = {false,true,false,true,true,false,true,true,true,false,false,true,false,false,true,true,true,false,false,false,true,true,true,true,false,true,false,false,false,true,true,true,false,true,false,false,true,true,false,false,false,false,true,false,false,false,true,false,true,false,true,true,false,false,true,false,false,false,true,true,true,true,true,true,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,true,false,true,false,true,false,true,true,true,false,false,true,true,false,false,true,false,false,false,false,false,true,true,false,false,true,false,false,true,true,true,true,false,false,false,true,true,true,true,true,false,true,false,false,false,false,true,false,false,false,false,true,false,false,true,false,false,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,false,false,false,true,false,true,true,false,false,true,true,true,false,true,true,true,true,true,false,false,false,true,true,true,false,true,false,true,false,true,true,false,true,true,true,false,false,false,false,false,true,true,false,false,true,true,false,false,true,true,false,true,false,false,false,false,false,false,false,false,true,false,true,true,true,false,true,false,false,true,true,false,true,false,true,false,false,false,false,true,true,true,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,true,true,false,true,false,false,false,false};
    uint256_from_bytes(a, a54_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a54_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a55_data[32]  = {0xa4,0xd1,0x40,0x72,0xfc,0xb1,0x66,0x4f,0xe8,0x8d,0x74,0x61,0x28,0x81,0x3c,0x61,0x31,0x96,0x15,0x8d,0x26,0xe0,0xff,0xc8,0x64,0x2d,0xca,0x08,0xe4,0x5c,0x9e,0x37};
    bool         a55_bits[256] = {true,true,true,false,true,true,false,false,false,true,true,true,true,false,false,true,false,false,true,true,true,false,true,false,false,false,true,false,false,true,true,true,false,false,false,true,false,false,false,false,false,true,false,true,false,false,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,true,true,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,true,true,true,false,true,true,false,false,true,false,false,true,false,true,true,false,false,false,true,true,false,true,false,true,false,false,false,false,true,true,false,true,false,false,true,true,false,false,false,true,true,false,false,true,false,false,false,false,true,true,false,false,false,true,true,true,true,false,false,true,false,false,false,false,false,false,true,false,false,false,true,false,true,false,false,true,false,false,false,false,true,true,false,false,false,true,false,true,true,true,false,true,false,true,true,false,false,false,true,false,false,false,true,false,true,true,true,true,true,true,true,false,false,true,false,false,true,true,false,false,true,true,false,true,false,false,false,true,true,false,true,false,false,true,true,true,true,true,true,false,true,false,false,true,true,true,false,false,false,false,false,false,false,true,false,true,false,false,false,true,false,true,true,false,false,true,false,false,true,false,true};
    uint256_from_bytes(a, a55_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a55_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a56_data[32]  = {0x13,0x8c,0x98,0x16,0xd9,0x28,0xad,0xd0,0x4d,0x21,0x06,0x8d,0x49,0x3e,0x09,0xc8,0xaf,0x11,0x8f,0xad,0x44,0x9f,0xa7,0xf6,0xdc,0x5a,0x84,0x48,0x72,0x82,0x79,0x4d};
    bool         a56_bits[256] = {true,false,true,true,false,false,true,false,true,false,false,true,true,true,true,false,false,true,false,false,false,false,false,true,false,true,false,false,true,true,true,false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,false,true,false,true,false,true,true,false,true,false,false,false,true,true,true,false,true,true,false,true,true,false,true,true,true,true,true,true,true,false,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,false,false,false,true,false,true,false,true,true,false,true,false,true,true,true,true,true,false,false,false,true,true,false,false,false,true,false,false,false,true,true,true,true,false,true,false,true,false,false,false,true,false,false,true,true,true,false,false,true,false,false,false,false,false,true,true,true,true,true,false,false,true,false,false,true,false,false,true,false,true,false,true,true,false,false,false,true,false,true,true,false,false,false,false,false,true,false,false,false,false,true,false,false,true,false,true,true,false,false,true,false,false,false,false,false,true,false,true,true,true,false,true,true,false,true,false,true,false,false,false,true,false,true,false,false,true,false,false,true,true,false,true,true,false,true,true,false,true,false,false,false,false,false,false,true,true,false,false,true,false,false,true,true,false,false,false,true,true,true,false,false,true,false,false,false};
    uint256_from_bytes(a, a56_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a56_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a57_data[32]  = {0x0a,0x6c,0xeb,0x02,0x07,0x2e,0x01,0xbe,0x76,0x81,0x62,0x60,0x40,0xfd,0x96,0x4e,0x23,0x8c,0xa9,0x8b,0xee,0x1c,0xbd,0x0f,0xc7,0x41,0xe7,0x77,0x99,0xf5,0x54,0x1a};
    bool         a57_bits[256] = {false,true,false,true,true,false,false,false,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,false,false,true,true,true,true,false,true,true,true,false,true,true,true,false,false,true,true,true,true,false,false,false,false,false,true,false,true,true,true,false,false,false,true,true,true,true,true,true,false,false,false,false,true,false,true,true,true,true,false,true,false,false,true,true,true,false,false,false,false,true,true,true,false,true,true,true,true,true,false,true,false,false,false,true,true,false,false,true,false,true,false,true,false,false,true,true,false,false,false,true,true,true,false,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,false,true,false,false,true,true,false,true,true,true,true,true,true,false,false,false,false,false,false,true,false,false,false,false,false,false,true,true,false,false,true,false,false,false,true,true,false,true,false,false,false,false,false,false,true,false,true,true,false,true,true,true,false,false,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,true,true,true,false,true,false,false,true,true,true,false,false,false,false,false,false,true,false,false,false,false,false,false,true,true,false,true,false,true,true,true,false,false,true,true,false,true,true,false,false,true,false,true,false,false,false,false};
    uint256_from_bytes(a, a57_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a57_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a58_data[32]  = {0xa8,0x69,0xfa,0x31,0xa1,0xbc,0x0e,0x08,0xab,0xb4,0x1b,0x0b,0xe0,0x82,0x02,0x63,0x47,0x4b,0xf4,0x8b,0x6e,0x18,0xb2,0x91,0x15,0xa1,0xbe,0x93,0xb6,0x32,0xf8,0x4a};
    bool         a58_bits[256] = {false,true,false,true,false,false,true,false,false,false,false,true,true,true,true,true,false,true,false,false,true,true,false,false,false,true,true,false,true,true,false,true,true,true,false,false,true,false,false,true,false,true,true,true,true,true,false,true,true,false,false,false,false,true,false,true,true,false,true,false,true,false,false,false,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,false,true,true,false,false,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,true,true,true,true,false,true,false,false,true,false,true,true,true,false,false,false,true,false,true,true,false,false,false,true,true,false,false,true,false,false,false,false,false,false,false,true,false,false,false,false,false,true,false,false,false,false,false,true,true,true,true,true,false,true,false,false,false,false,true,true,false,true,true,false,false,false,false,false,true,false,true,true,false,true,true,true,false,true,false,true,false,true,false,false,false,true,false,false,false,false,false,true,true,true,false,false,false,false,false,false,true,true,true,true,false,true,true,false,false,false,false,true,false,true,true,false,false,false,true,true,false,false,false,true,false,true,true,true,true,true,true,false,false,true,false,true,true,false,false,false,false,true,false,true,false,true};
    uint256_from_bytes(a, a58_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a58_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a59_data[32]  = {0x7b,0x96,0x63,0x1d,0x4e,0xa3,0x33,0xf5,0x32,0x2e,0xb9,0x07,0x3b,0xb6,0x73,0xce,0x2b,0x83,0xbf,0xd7,0xce,0x78,0xa0,0xfc,0x94,0x7c,0x3c,0x5a,0x56,0xce,0x9f,0x83};
    bool         a59_bits[256] = {true,true,false,false,false,false,false,true,true,true,true,true,true,false,false,true,false,true,true,true,false,false,true,true,false,true,true,false,true,false,true,false,false,true,false,true,true,false,true,false,false,false,true,true,true,true,false,false,false,false,true,true,true,true,true,false,false,false,true,false,true,false,false,true,false,false,true,true,true,true,true,true,false,false,false,false,false,true,false,true,false,false,false,true,true,true,true,false,false,true,true,true,false,false,true,true,true,true,true,false,true,false,true,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,false,true,true,true,false,true,false,true,false,false,false,true,true,true,false,false,true,true,true,true,false,false,true,true,true,false,false,true,true,false,true,true,false,true,true,true,false,true,true,true,false,false,true,true,true,false,false,false,false,false,true,false,false,true,true,true,false,true,false,true,true,true,false,true,false,false,false,true,false,false,true,true,false,false,true,false,true,false,true,true,true,true,true,true,false,false,true,true,false,false,true,true,false,false,false,true,false,true,false,true,true,true,false,false,true,false,true,false,true,true,true,false,false,false,true,true,false,false,false,true,true,false,false,true,true,false,true,false,false,true,true,true,false,true,true,true,true,false};
    uint256_from_bytes(a, a59_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a59_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a60_data[32]  = {0x0b,0x05,0x57,0x8c,0x35,0x74,0x11,0x8a,0x90,0x8f,0x8b,0x77,0x53,0x14,0x92,0x0f,0x3e,0x13,0x6b,0xa9,0x29,0xef,0x7e,0xde,0xb6,0xb9,0x57,0x44,0x72,0x55,0x9b,0x94};
    bool         a60_bits[256] = {false,false,true,false,true,false,false,true,true,true,false,true,true,false,false,true,true,false,true,false,true,false,true,false,false,true,false,false,true,true,true,false,false,false,true,false,false,false,true,false,true,true,true,false,true,false,true,false,true,false,false,true,true,true,false,true,false,true,true,false,true,true,false,true,false,true,true,true,true,false,true,true,false,true,true,true,true,true,true,false,true,true,true,true,false,true,true,true,true,false,false,true,false,true,false,false,true,false,false,true,false,true,false,true,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false,false,false,true,true,true,true,true,false,false,true,true,true,true,false,false,false,false,false,true,false,false,true,false,false,true,false,false,true,false,true,false,false,false,true,true,false,false,true,false,true,false,true,true,true,false,true,true,true,false,true,true,false,true,false,false,false,true,true,true,true,true,false,false,false,true,false,false,false,false,true,false,false,true,false,true,false,true,false,false,false,true,true,false,false,false,true,false,false,false,false,false,true,false,true,true,true,false,true,false,true,false,true,true,false,false,false,false,true,true,false,false,false,true,true,true,true,false,true,false,true,false,true,false,true,false,false,false,false,false,true,true,false,true,false,false,false,false};
    uint256_from_bytes(a, a60_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a60_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a61_data[32]  = {0x54,0xc9,0xa4,0x92,0x7b,0x86,0xb4,0xf7,0x86,0x0a,0xad,0x51,0x1e,0x5c,0x38,0x39,0x0c,0x1f,0xe0,0x3b,0x1f,0x87,0x90,0xc7,0xcc,0x4b,0xf5,0xd5,0x0c,0x50,0xb0,0x4f};
    bool         a61_bits[256] = {true,true,true,true,false,false,true,false,false,false,false,false,true,true,false,true,false,false,false,false,true,false,true,false,false,false,true,true,false,false,false,false,true,false,true,false,true,false,true,true,true,false,true,false,true,true,true,true,true,true,false,true,false,false,true,false,false,false,true,true,false,false,true,true,true,true,true,false,false,false,true,true,false,false,false,false,true,false,false,true,true,true,true,false,false,false,false,true,true,true,true,true,true,false,false,false,true,true,false,true,true,true,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,false,false,false,false,false,true,true,false,false,false,false,true,false,false,true,true,true,false,false,false,false,false,true,true,true,false,false,false,false,true,true,true,false,true,false,false,true,true,true,true,false,false,false,true,false,false,false,true,false,true,false,true,false,true,true,false,true,false,true,false,true,false,true,false,false,false,false,false,true,true,false,false,false,false,true,true,true,true,false,true,true,true,true,false,false,true,false,true,true,false,true,false,true,true,false,false,false,false,true,true,true,false,true,true,true,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,true,true,false,false,true,false,false,true,true,false,false,true,false,true,false,true,false};
    uint256_from_bytes(a, a61_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a61_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a62_data[32]  = {0xc0,0x0e,0x3e,0x58,0x97,0xf3,0xf1,0x20,0xf7,0xb4,0x62,0x4d,0xdf,0x59,0x9d,0x22,0x04,0xb2,0x34,0xca,0x16,0x00,0xfc,0xea,0x42,0x93,0xea,0x89,0xf0,0xc0,0x39,0x95};
    bool         a62_bits[256] = {true,false,true,false,true,false,false,true,true,false,false,true,true,true,false,false,false,false,false,false,false,false,true,true,false,false,false,false,true,true,true,true,true,false,false,true,false,false,false,true,false,true,false,true,false,true,true,true,true,true,false,false,true,false,false,true,false,true,false,false,false,false,true,false,false,true,false,true,false,true,true,true,false,false,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,true,true,false,true,false,false,false,false,true,false,true,false,false,true,true,false,false,true,false,true,true,false,false,false,true,false,false,true,true,false,true,false,false,true,false,false,false,false,false,false,true,false,false,false,true,false,false,true,false,true,true,true,false,false,true,true,false,false,true,true,false,true,false,true,true,true,true,true,false,true,true,true,false,true,true,false,false,true,false,false,true,false,false,false,true,true,false,false,false,true,false,true,true,false,true,true,true,true,false,true,true,true,true,false,false,false,false,false,true,false,false,true,false,false,false,true,true,true,true,true,true,false,false,true,true,true,true,true,true,true,false,true,false,false,true,false,false,false,true,true,false,true,false,false,true,true,true,true,true,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,true,true};
    uint256_from_bytes(a, a62_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a62_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a63_data[32]  = {0x2a,0x5c,0x31,0x54,0x8e,0xa3,0x98,0x95,0x88,0xa5,0x77,0xf5,0x0a,0x84,0x81,0xe6,0x7c,0x57,0xc1,0x68,0xe5,0xb1,0x19,0x6a,0xd5,0x2a,0x5d,0x5b,0x62,0xad,0xe6,0xa6};
    bool         a63_bits[256] = {false,true,true,false,false,true,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,false,true,false,true,false,false,false,true,true,false,true,true,false,true,true,false,true,false,true,false,true,true,true,false,true,false,false,true,false,true,false,true,false,false,true,false,true,false,true,false,true,true,false,true,false,true,false,true,true,false,true,false,false,true,true,false,false,false,true,false,false,false,true,true,false,true,true,false,true,false,false,true,true,true,false,false,false,true,false,true,true,false,true,false,false,false,false,false,true,true,true,true,true,false,true,false,true,false,false,false,true,true,true,true,true,false,false,true,true,false,false,true,true,true,true,false,false,false,false,false,false,true,false,false,true,false,false,false,false,true,false,true,false,true,false,false,false,false,true,false,true,false,true,true,true,true,true,true,true,false,true,true,true,false,true,false,true,false,false,true,false,true,false,false,false,true,false,false,false,true,true,false,true,false,true,false,false,true,false,false,false,true,true,false,false,true,true,true,false,false,false,true,false,true,false,true,true,true,false,false,false,true,false,false,true,false,true,false,true,false,true,false,false,false,true,true,false,false,false,false,true,true,true,false,true,false,false,true,false,true,false,true,false,false};
    uint256_from_bytes(a, a63_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a63_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a64_data[32]  = {0x7f,0x89,0x57,0xe8,0x3f,0x52,0xa8,0x7b,0xfc,0x96,0x0e,0x58,0xe2,0x0b,0x45,0xda,0xa2,0x41,0x47,0x00,0xf5,0xac,0xe7,0x42,0x02,0x12,0x37,0x16,0xd3,0xf6,0xe5,0x20};
    bool         a64_bits[256] = {false,false,false,false,false,true,false,false,true,false,true,false,false,true,true,true,false,true,true,false,true,true,true,true,true,true,false,false,true,false,true,true,false,true,true,false,true,false,false,false,true,true,true,false,true,true,false,false,false,true,false,false,true,false,false,false,false,true,false,false,false,false,false,false,false,true,false,false,false,false,true,false,true,true,true,false,false,true,true,true,false,false,true,true,false,true,false,true,true,false,true,false,true,true,true,true,false,false,false,false,false,false,false,false,true,true,true,false,false,false,true,false,true,false,false,false,false,false,true,false,false,true,false,false,false,true,false,true,false,true,false,true,true,false,true,true,true,false,true,false,false,false,true,false,true,true,false,true,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,false,false,false,false,true,true,false,true,false,false,true,false,false,true,true,true,true,true,true,true,true,false,true,true,true,true,false,false,false,false,true,false,true,false,true,false,true,false,false,true,false,true,false,true,true,true,true,true,true,false,false,false,false,false,true,false,true,true,true,true,true,true,false,true,false,true,false,true,false,false,true,false,false,false,true,true,true,true,true,true,true,true,false};
    uint256_from_bytes(a, a64_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a64_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a65_data[32]  = {0x07,0x88,0x30,0xbf,0x4d,0x85,0xdd,0xff,0xed,0x5b,0xc5,0x33,0x6c,0x4c,0xdd,0xc2,0xf1,0x76,0x4a,0xd0,0xa3,0xeb,0x46,0x78,0x00,0xe7,0xf7,0x0a,0xd9,0xf4,0x56,0x56};
    bool         a65_bits[256] = {false,true,true,false,true,false,true,false,false,true,true,false,true,false,true,false,false,false,true,false,true,true,true,true,true,false,false,true,true,false,true,true,false,true,false,true,false,false,false,false,true,true,true,false,true,true,true,true,true,true,true,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,false,false,true,true,false,false,false,true,false,true,true,false,true,false,true,true,true,true,true,false,false,false,true,false,true,false,false,false,false,true,false,true,true,false,true,false,true,false,false,true,false,false,true,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,false,false,false,false,true,true,true,false,true,true,true,false,true,true,false,false,true,true,false,false,true,false,false,false,true,true,false,true,true,false,true,true,false,false,true,true,false,false,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,false,true,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,false,true,true,true,false,true,false,false,false,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,true,false,true,false,false,false,false,true,true,false,false,false,false,false,true,false,false,false,true,true,true,true,false,false,false,false,false};
    uint256_from_bytes(a, a65_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a65_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a66_data[32]  = {0x31,0x74,0xde,0xc4,0x44,0xb9,0xd3,0xda,0xb5,0xd7,0x7f,0x7b,0x00,0xdf,0x34,0x66,0xe6,0xfb,0x5e,0xed,0x35,0xc3,0xb3,0x86,0x7c,0x65,0xe1,0xd8,0xec,0xd8,0xe5,0x2b};
    bool         a66_bits[256] = {true,true,false,true,false,true,false,false,true,false,true,false,false,true,true,true,false,false,false,true,true,false,true,true,false,false,true,true,false,true,true,true,false,false,false,true,true,false,true,true,true,false,false,false,false,true,true,true,true,false,true,false,false,true,true,false,false,false,true,true,true,true,true,false,false,true,true,false,false,false,false,true,true,true,false,false,true,true,false,true,true,true,false,false,false,false,true,true,true,false,true,false,true,true,false,false,true,false,true,true,false,true,true,true,false,true,true,true,true,false,true,false,true,true,false,true,true,true,true,true,false,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false,false,false,true,false,true,true,false,false,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,false,true,true,true,true,true,true,true,false,true,true,true,false,true,false,true,true,true,false,true,false,true,true,false,true,false,true,false,true,true,false,true,true,true,true,false,false,true,false,true,true,true,false,false,true,true,true,false,true,false,false,true,false,false,false,true,false,false,false,true,false,false,false,true,true,false,true,true,true,true,false,true,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,false,false};
    uint256_from_bytes(a, a66_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a66_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a67_data[32]  = {0x9e,0x38,0x16,0x9e,0xdf,0x6a,0x21,0x38,0xfa,0x95,0x7b,0xf3,0x04,0x86,0xe6,0xe6,0x01,0x14,0xe3,0xf0,0x72,0x15,0x34,0x76,0x5b,0xa9,0x10,0xf2,0x88,0xf6,0xc2,0x2a};
    bool         a67_bits[256] = {false,true,false,true,false,true,false,false,false,true,false,false,false,false,true,true,false,true,true,false,true,true,true,true,false,false,false,true,false,false,false,true,false,true,false,false,true,true,true,true,false,false,false,false,true,false,false,false,true,false,false,true,false,true,false,true,true,true,false,true,true,false,true,false,false,true,true,false,true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,false,true,false,false,false,false,true,false,false,true,true,true,false,false,false,false,false,true,true,true,true,true,true,false,false,false,true,true,true,false,false,true,false,true,false,false,false,true,false,false,false,false,false,false,false,false,true,true,false,false,true,true,true,false,true,true,false,false,true,true,true,false,true,true,false,false,false,false,true,false,false,true,false,false,false,false,false,true,true,false,false,true,true,true,true,true,true,false,true,true,true,true,false,true,false,true,false,true,false,false,true,false,true,false,true,true,true,true,true,false,false,false,true,true,true,false,false,true,false,false,false,false,true,false,false,false,true,false,true,false,true,true,false,true,true,true,true,true,false,true,true,false,true,true,true,true,false,false,true,false,true,true,false,true,false,false,false,false,false,false,true,true,true,false,false,false,true,true,true,true,false,false,true};
    uint256_from_bytes(a, a67_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a67_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a68_data[32]  = {0xe3,0xf6,0xaa,0x97,0x0d,0xbb,0xdd,0xad,0x5d,0xa4,0xbf,0x44,0x9a,0x85,0xff,0xdb,0x44,0x13,0x86,0xe3,0xb4,0x84,0x95,0x41,0xce,0xc3,0x9f,0xe3,0x57,0x4c,0x2c,0xb2};
    bool         a68_bits[256] = {false,true,false,false,true,true,false,true,false,false,true,true,false,true,false,false,false,false,true,true,false,false,true,false,true,true,true,false,true,false,true,false,true,true,false,false,false,true,true,true,true,true,true,true,true,false,false,true,true,true,false,false,false,false,true,true,false,true,true,true,false,false,true,true,true,false,false,false,false,false,true,false,true,false,true,false,true,false,false,true,false,false,true,false,false,false,false,true,false,false,true,false,true,true,false,true,true,true,false,false,false,true,true,true,false,true,true,false,false,false,false,true,true,true,false,false,true,false,false,false,false,false,true,false,false,false,true,false,true,true,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,true,false,true,false,true,true,false,false,true,false,false,true,false,false,false,true,false,true,true,true,true,true,true,false,true,false,false,true,false,false,true,false,true,true,false,true,true,true,false,true,false,true,false,true,true,false,true,false,true,true,false,true,true,true,false,true,true,true,true,false,true,true,true,false,true,true,false,true,true,false,false,false,false,true,true,true,false,true,false,false,true,false,true,false,true,false,true,false,true,false,true,true,false,true,true,true,true,true,true,false,false,false,true,true,true};
    uint256_from_bytes(a, a68_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a68_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a69_data[32]  = {0xd2,0x71,0x1b,0xf7,0xc7,0xd6,0x55,0xc7,0xe1,0x51,0xae,0x3f,0xcd,0xdc,0x12,0xfd,0x85,0x75,0xd1,0x7b,0x66,0x55,0xf7,0xec,0x4b,0xe0,0x13,0xaa,0x4d,0x7f,0x5a,0xf7};
    bool         a69_bits[256] = {true,true,true,false,true,true,true,true,false,true,false,true,true,false,true,false,true,true,true,true,true,true,true,false,true,false,true,true,false,false,true,false,false,true,false,true,false,true,false,true,true,true,false,false,true,false,false,false,false,false,false,false,false,true,true,true,true,true,false,true,false,false,true,false,false,false,true,true,false,true,true,true,true,true,true,false,true,true,true,true,true,false,true,false,true,false,true,false,false,true,true,false,false,true,true,false,true,true,false,true,true,true,true,false,true,false,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,true,false,false,false,false,true,true,false,true,true,true,true,true,true,false,true,false,false,true,false,false,false,false,false,true,true,true,false,true,true,true,false,true,true,false,false,true,true,true,true,true,true,true,true,false,false,false,true,true,true,false,true,false,true,true,false,false,false,true,false,true,false,true,false,false,false,false,true,true,true,true,true,true,false,false,false,true,true,true,false,true,false,true,false,true,false,false,true,true,false,true,false,true,true,true,true,true,false,false,false,true,true,true,true,true,false,true,true,true,true,true,true,false,true,true,false,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,false,true,true};
    uint256_from_bytes(a, a69_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a69_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a70_data[32]  = {0xb9,0xf7,0xd9,0x68,0x71,0xe8,0x68,0x47,0x30,0x2d,0x58,0x9c,0x02,0xbc,0x98,0xd7,0x8e,0xf8,0x95,0x7a,0xe2,0xe3,0x5c,0xd4,0xd5,0xb1,0x89,0xbd,0x29,0x14,0xd5,0x61};
    bool         a70_bits[256] = {true,false,false,false,false,true,true,false,true,false,true,false,true,false,true,true,false,false,true,false,true,false,false,false,true,false,false,true,false,true,false,false,true,false,true,true,true,true,false,true,true,false,false,true,false,false,false,true,true,false,false,false,true,true,false,true,true,false,true,false,true,false,true,true,false,false,true,false,true,false,true,true,false,false,true,true,true,false,true,false,true,true,false,false,false,true,true,true,false,true,false,false,false,true,true,true,false,true,false,true,true,true,true,false,true,false,true,false,true,false,false,true,false,false,false,true,true,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,true,false,true,true,false,false,false,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,false,false,false,false,false,false,false,false,true,true,true,false,false,true,false,false,false,true,true,false,true,false,true,false,true,true,false,true,false,false,false,false,false,false,true,true,false,false,true,true,true,false,false,false,true,false,false,false,false,true,false,true,true,false,false,false,false,true,false,true,true,true,true,false,false,false,true,true,true,false,false,false,false,true,false,true,true,false,true,false,false,true,true,false,true,true,true,true,true,false,true,true,true,true,true,false,false,true,true,true,false,true};
    uint256_from_bytes(a, a70_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a70_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a71_data[32]  = {0x10,0xa5,0x37,0x34,0xc9,0x4d,0x37,0x70,0xc9,0x1f,0x0d,0xaa,0x1b,0x10,0x50,0x00,0xdc,0xdb,0x05,0xeb,0xe7,0x95,0x9f,0x71,0x95,0xbe,0x8a,0x42,0x00,0x08,0xe0,0x85};
    bool         a71_bits[256] = {true,false,true,false,false,false,false,true,false,false,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,true,false,false,true,false,true,false,false,false,true,false,true,true,true,true,true,false,true,true,false,true,false,true,false,false,true,true,false,false,false,true,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,false,false,true,true,true,true,false,false,true,true,true,true,true,false,true,false,true,true,true,true,false,true,false,false,false,false,false,true,true,false,true,true,false,true,true,false,false,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,false,false,false,true,false,false,false,true,true,false,true,true,false,false,false,false,true,false,true,false,true,false,true,true,false,true,true,false,false,false,false,true,true,true,true,true,false,false,false,true,false,false,true,false,false,true,true,false,false,false,false,true,true,true,false,true,true,true,false,true,true,false,false,true,false,true,true,false,false,true,false,true,false,false,true,false,false,true,true,false,false,true,false,true,true,false,false,true,true,true,false,true,true,false,false,true,false,true,false,false,true,false,true,false,false,false,false,true,false,false,false};
    uint256_from_bytes(a, a71_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a71_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a72_data[32]  = {0x68,0x3e,0x70,0xb2,0x47,0x4a,0x16,0x0b,0x46,0x95,0x30,0x3c,0xde,0x23,0x3e,0xdb,0x7f,0x86,0xc2,0x11,0xd6,0x49,0x95,0x11,0xb8,0x3a,0x1a,0x39,0xed,0xd8,0xa6,0x3e};
    bool         a72_bits[256] = {false,true,true,true,true,true,false,false,false,true,true,false,false,true,false,true,false,false,false,true,true,false,true,true,true,false,true,true,false,true,true,true,true,false,false,true,true,true,false,false,false,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,false,false,false,true,true,true,false,true,true,false,false,false,true,false,false,false,true,false,true,false,true,false,false,true,true,false,false,true,false,false,true,false,false,true,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,false,false,true,true,false,true,true,false,false,false,false,true,true,true,true,true,true,true,true,false,true,true,false,true,true,false,true,true,false,true,true,true,true,true,false,false,true,true,false,false,false,true,false,false,false,true,true,true,true,false,true,true,false,false,true,true,true,true,false,false,false,false,false,false,true,true,false,false,true,false,true,false,true,false,false,true,false,true,true,false,false,false,true,false,true,true,false,true,false,false,false,false,false,true,true,false,true,false,false,false,false,true,false,true,false,false,true,false,true,true,true,false,false,false,true,false,false,true,false,false,true,true,false,true,false,false,false,false,true,true,true,false,false,true,true,true,true,true,false,false,false,false,false,true,false,true,true,false};
    uint256_from_bytes(a, a72_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a72_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a73_data[32]  = {0x1d,0x19,0x2f,0xd1,0x72,0x2a,0x93,0x8f,0xad,0x51,0x24,0xf1,0xb8,0xbd,0x97,0x89,0x5e,0x6d,0x6a,0x28,0xeb,0xbd,0xbe,0x44,0x45,0xd7,0x18,0xec,0x27,0x26,0x1e,0x71};
    bool         a73_bits[256] = {true,false,false,false,true,true,true,false,false,true,true,true,true,false,false,false,false,true,true,false,false,true,false,false,true,true,true,false,false,true,false,false,false,false,true,true,false,true,true,true,false,false,false,true,true,false,false,false,true,true,true,false,true,false,true,true,true,false,true,false,false,false,true,false,false,false,true,false,false,false,true,false,false,true,true,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,false,true,false,true,true,true,false,false,false,true,false,true,false,false,false,true,false,true,false,true,true,false,true,false,true,true,false,true,true,false,false,true,true,true,true,false,true,false,true,false,false,true,false,false,false,true,true,true,true,false,true,false,false,true,true,false,true,true,true,true,false,true,false,false,false,true,true,true,false,true,true,false,false,false,true,true,true,true,false,false,true,false,false,true,false,false,true,false,false,false,true,false,true,false,true,false,true,true,false,true,false,true,true,true,true,true,false,false,false,true,true,true,false,false,true,false,false,true,false,true,false,true,false,true,false,false,false,true,false,false,true,true,true,false,true,false,false,false,true,false,true,true,true,true,true,true,false,true,false,false,true,false,false,true,true,false,false,false,true,false,true,true,true,false,false,false};
    uint256_from_bytes(a, a73_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a73_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a74_data[32]  = {0x26,0x3f,0xd9,0x6e,0x7f,0xc5,0x33,0xed,0x18,0x56,0x9d,0x72,0xab,0x0c,0xa2,0x90,0x1b,0xb7,0xcd,0x96,0x37,0x95,0xf0,0xfa,0xec,0x34,0x84,0x09,0xa9,0xee,0xdf,0xb5};
    bool         a74_bits[256] = {true,false,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,true,true,true,false,true,true,true,true,false,false,true,false,true,false,true,true,false,false,true,false,false,false,false,false,false,true,false,false,false,false,true,false,false,true,false,true,true,false,false,false,false,true,true,false,true,true,true,false,true,false,true,true,true,true,true,false,false,false,false,true,true,true,true,true,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,false,true,true,false,true,false,false,true,true,false,true,true,false,false,true,true,true,true,true,false,true,true,false,true,true,true,false,true,true,false,false,false,false,false,false,false,true,false,false,true,false,true,false,false,false,true,false,true,false,false,true,true,false,false,false,false,true,true,false,true,false,true,false,true,false,true,false,false,true,true,true,false,true,false,true,true,true,false,false,true,false,true,true,false,true,false,true,false,false,false,false,true,true,false,false,false,true,false,true,true,false,true,true,true,true,true,false,false,true,true,false,false,true,false,true,false,false,false,true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,true,true,false,true,false,false,true,true,false,true,true,true,true,true,true,true,true,false,false,false,true,true,false,false,true,false,false};
    uint256_from_bytes(a, a74_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a74_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a75_data[32]  = {0x4f,0xf1,0x9e,0x62,0x3a,0x25,0xe8,0x6a,0x15,0x2c,0x3a,0x31,0x97,0x2d,0xc9,0x70,0x3c,0x38,0xf1,0xdf,0x8d,0x24,0x18,0x5a,0x20,0x1d,0x17,0x19,0x50,0x27,0x72,0xec};
    bool         a75_bits[256] = {false,false,true,true,false,true,true,true,false,true,false,false,true,true,true,false,true,true,true,false,false,true,false,false,false,false,false,false,true,false,true,false,true,false,false,true,true,false,false,false,true,true,true,false,true,false,false,false,true,false,true,true,true,false,false,false,false,false,false,false,false,true,false,false,false,true,false,true,true,false,true,false,false,false,false,true,true,false,false,false,false,false,true,false,false,true,false,false,true,false,true,true,false,false,false,true,true,true,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,false,false,true,true,true,false,false,false,false,true,true,true,true,false,false,false,false,false,false,true,true,true,false,true,false,false,true,false,false,true,true,true,false,true,true,false,true,false,false,true,true,true,false,true,false,false,true,true,false,false,false,true,true,false,false,false,true,false,true,true,true,false,false,false,false,true,true,false,true,false,false,true,false,true,false,true,false,false,false,false,true,false,true,false,true,true,false,false,false,false,true,false,true,true,true,true,false,true,false,false,true,false,false,false,true,false,true,true,true,false,false,false,true,false,false,false,true,true,false,false,true,true,true,true,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,false,false,true,false};
    uint256_from_bytes(a, a75_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a75_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a76_data[32]  = {0xa7,0xb0,0x78,0x56,0xbb,0xb5,0xc9,0x67,0xbb,0xe8,0x3f,0xd2,0xcf,0x58,0x39,0x53,0x86,0x3a,0xc0,0x46,0xff,0xec,0xa2,0x1f,0xee,0x31,0x16,0xd1,0x3b,0xd4,0xc4,0xbc};
    bool         a76_bits[256] = {false,false,true,true,true,true,false,true,false,false,true,false,false,false,true,true,false,false,true,false,true,false,true,true,true,true,false,true,true,true,false,false,true,false,false,false,true,false,true,true,false,true,true,false,true,false,false,false,true,false,false,false,true,true,false,false,false,true,true,true,false,true,true,true,true,true,true,true,true,false,false,false,false,true,false,false,false,true,false,true,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,false,true,false,false,false,false,false,false,false,true,true,false,true,false,true,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,true,false,true,false,true,false,false,true,true,true,false,false,false,false,false,true,true,false,true,false,true,true,true,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,true,true,true,true,false,false,false,false,false,true,false,true,true,true,true,true,false,true,true,true,false,true,true,true,true,false,false,true,true,false,true,false,false,true,false,false,true,true,true,false,true,false,true,true,false,true,true,true,false,true,true,true,false,true,false,true,true,false,true,false,true,false,false,false,false,true,true,true,true,false,false,false,false,false,true,true,false,true,true,true,true,false,false,true,false,true};
    uint256_from_bytes(a, a76_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a76_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a77_data[32]  = {0x23,0xe5,0x43,0x31,0x9b,0xd1,0x9f,0x61,0x23,0x28,0x1b,0xc4,0x77,0x3b,0x21,0x18,0x88,0x95,0x1a,0xe5,0x21,0x11,0x38,0x9a,0xef,0x2c,0x11,0x08,0x9e,0xea,0xcf,0xbb};
    bool         a77_bits[256] = {true,true,false,true,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,true,true,false,true,true,true,true,false,false,true,false,false,false,true,false,false,false,false,true,false,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,true,true,true,false,true,true,true,false,true,false,true,true,false,false,true,false,false,false,true,true,true,false,false,true,false,false,false,true,false,false,false,true,false,false,false,false,true,false,false,true,false,true,false,false,true,true,true,false,true,false,true,true,false,false,false,true,false,true,false,true,false,false,true,false,false,false,true,false,false,false,true,false,false,false,true,true,false,false,false,true,false,false,false,false,true,false,false,true,true,false,true,true,true,false,false,true,true,true,false,true,true,true,false,false,false,true,false,false,false,true,true,true,true,false,true,true,false,false,false,false,false,false,true,false,true,false,false,true,true,false,false,false,true,false,false,true,false,false,false,false,true,true,false,true,true,true,true,true,false,false,true,true,false,false,false,true,false,true,true,true,true,false,true,true,false,false,true,true,false,false,false,true,true,false,false,true,true,false,false,false,false,true,false,true,false,true,false,false,true,true,true,true,true,false,false,false,true,false,false};
    uint256_from_bytes(a, a77_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a77_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a78_data[32]  = {0x4d,0x3f,0x11,0x79,0xcf,0x97,0xd3,0x7a,0x7b,0xc5,0x1a,0xff,0xe3,0x24,0x02,0xea,0xa2,0x38,0x93,0x79,0xdb,0x0f,0xaa,0x6f,0xeb,0xe7,0xaf,0xde,0xe2,0xf1,0x0a,0xfb};
    bool         a78_bits[256] = {true,true,false,true,true,true,true,true,false,true,false,true,false,false,false,false,true,false,false,false,true,true,true,true,false,true,false,false,false,true,true,true,false,true,true,true,true,false,true,true,true,true,true,true,false,true,false,true,true,true,true,false,false,true,true,true,true,true,false,true,false,true,true,true,true,true,true,true,false,true,true,false,false,true,false,true,false,true,false,true,true,true,true,true,false,false,false,false,true,true,false,true,true,false,true,true,true,false,false,true,true,true,true,false,true,true,false,false,true,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,true,false,true,false,true,false,true,false,true,true,true,false,true,false,false,false,false,false,false,false,false,true,false,false,true,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,false,false,true,false,true,false,false,false,true,true,true,true,false,true,true,true,true,false,false,true,false,true,true,true,true,false,true,true,false,false,true,false,true,true,true,true,true,false,true,false,false,true,true,true,true,true,false,false,true,true,true,false,false,true,true,true,true,false,true,false,false,false,true,false,false,false,true,true,true,true,true,true,false,false,true,false,true,true,false,false,true,false};
    uint256_from_bytes(a, a78_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a78_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a79_data[32]  = {0xf4,0xc0,0x8c,0x9e,0xa6,0x80,0x48,0x61,0xea,0xe4,0x84,0x77,0x4a,0xfb,0xa4,0xd3,0x3f,0x27,0xa9,0xb6,0x9b,0xd0,0xce,0x94,0x37,0xc3,0xeb,0x41,0x4c,0x67,0xbc,0x45};
    bool         a79_bits[256] = {true,false,true,false,false,false,true,false,false,false,true,true,true,true,false,true,true,true,true,false,false,true,true,false,false,false,true,true,false,false,true,false,true,false,false,false,false,false,true,false,true,true,false,true,false,true,true,true,true,true,false,false,false,false,true,true,true,true,true,false,true,true,false,false,false,false,true,false,true,false,false,true,false,true,true,true,false,false,true,true,false,false,false,false,true,false,true,true,true,true,false,true,true,false,false,true,false,true,true,false,true,true,false,true,true,false,false,true,false,true,false,true,true,true,true,false,false,true,false,false,true,true,true,true,true,true,false,false,true,true,false,false,true,false,true,true,false,false,true,false,false,true,false,true,true,true,false,true,true,true,true,true,false,true,false,true,false,false,true,false,true,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,true,false,false,true,true,true,false,true,false,true,false,true,true,true,true,false,false,false,false,true,true,false,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,true,false,true,true,false,false,true,false,true,false,true,true,true,true,false,false,true,false,false,true,true,false,false,false,true,false,false,false,false,false,false,true,true,false,false,true,false,true,true,true,true};
    uint256_from_bytes(a, a79_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a79_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a80_data[32]  = {0x23,0xc0,0x06,0xaa,0x6f,0x1c,0x3c,0x1d,0x0a,0x1f,0xd1,0x66,0x6b,0x05,0x93,0x27,0xd2,0xc6,0x3c,0x77,0x00,0x21,0x25,0xb5,0xdd,0x44,0x8c,0x83,0xca,0x31,0xd7,0x55};
    bool         a80_bits[256] = {true,false,true,false,true,false,true,false,true,true,true,false,true,false,true,true,true,false,false,false,true,true,false,false,false,true,false,true,false,false,true,true,true,true,false,false,false,false,false,true,false,false,true,true,false,false,false,true,false,false,true,false,false,false,true,false,true,false,true,true,true,false,true,true,true,false,true,false,true,true,false,true,true,false,true,false,false,true,false,false,true,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,false,false,true,true,false,false,false,true,true,false,true,false,false,true,false,true,true,true,true,true,false,false,true,false,false,true,true,false,false,true,false,false,true,true,false,true,false,false,false,false,false,true,true,false,true,false,true,true,false,false,true,true,false,false,true,true,false,true,false,false,false,true,false,true,true,true,true,true,true,true,false,false,false,false,true,false,true,false,false,false,false,true,false,true,true,true,false,false,false,false,false,true,true,true,true,false,false,false,false,true,true,true,false,false,false,true,true,true,true,false,true,true,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,false,false,false,true,false,false};
    uint256_from_bytes(a, a80_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a80_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a81_data[32]  = {0x7e,0xa0,0xba,0xf6,0xe2,0xde,0x3b,0xba,0x39,0x52,0xc1,0x2f,0x17,0x3e,0x96,0xc5,0x76,0x3b,0xb8,0xe5,0xb9,0x17,0x3d,0x2c,0x2e,0xf2,0x1e,0x51,0x01,0x9f,0x61,0x4f};
    bool         a81_bits[256] = {true,true,true,true,false,false,true,false,true,false,false,false,false,true,true,false,true,true,true,true,true,false,false,true,true,false,false,false,false,false,false,false,true,false,false,false,true,false,true,false,false,true,true,true,true,false,false,false,false,true,false,false,true,true,true,true,false,true,true,true,false,true,false,false,false,false,true,true,false,true,false,false,true,false,true,true,true,true,false,false,true,true,true,false,true,false,false,false,true,false,false,true,true,true,false,true,true,false,true,false,false,true,true,true,false,false,false,true,true,true,false,true,true,true,false,true,true,true,false,false,false,true,true,false,true,true,true,false,true,false,true,false,false,false,true,true,false,true,true,false,true,false,false,true,false,true,true,true,true,true,false,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,true,false,true,false,false,true,true,true,false,false,false,true,false,true,true,true,false,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,true,true,false,true,true,true,true,false,true,false,true,true,true,false,true,false,false,false,false,false,true,false,true,false,true,true,true,true,true,true,false};
    uint256_from_bytes(a, a81_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a81_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a82_data[32]  = {0x62,0xd6,0xcf,0x59,0x93,0x80,0x9d,0x69,0x7d,0x97,0x84,0x37,0x11,0xc3,0x04,0x39,0x86,0x6d,0xb9,0x91,0xd5,0x6e,0x1c,0x53,0x40,0xe0,0x97,0xbc,0x07,0xa5,0xad,0x7e};
    bool         a82_bits[256] = {false,true,true,true,true,true,true,false,true,false,true,true,false,true,false,true,true,false,true,false,false,true,false,true,true,true,true,false,false,false,false,false,false,false,true,true,true,true,false,true,true,true,true,false,true,false,false,true,false,false,false,false,false,true,true,true,false,false,false,false,false,false,true,false,true,true,false,false,true,false,true,false,false,false,true,true,true,false,false,false,false,true,true,true,false,true,true,false,true,false,true,false,true,false,true,true,true,false,false,false,true,false,false,true,true,false,false,true,true,true,false,true,true,false,true,true,false,true,true,false,false,true,true,false,false,false,false,true,true,false,false,true,true,true,false,false,false,false,true,false,false,false,false,false,true,true,false,false,false,false,true,true,true,false,false,false,true,false,false,false,true,true,true,false,true,true,false,false,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,true,true,false,true,true,true,true,true,false,true,false,false,true,false,true,true,false,true,false,true,true,true,false,false,true,false,false,false,false,false,false,false,true,true,true,false,false,true,false,false,true,true,false,false,true,true,false,true,false,true,true,true,true,false,false,true,true,false,true,true,false,true,false,true,true,false,true,false,false,false,true,true,false};
    uint256_from_bytes(a, a82_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a82_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a83_data[32]  = {0x52,0x1e,0x57,0xf6,0xf6,0xec,0x4a,0xc1,0x9e,0xf7,0x8e,0xb9,0x39,0x9a,0x1c,0x94,0x05,0xdb,0x69,0x49,0x9c,0x49,0x74,0x83,0xcd,0x69,0xb5,0x58,0x8a,0x8d,0x90,0xdc};
    bool         a83_bits[256] = {false,false,true,true,true,false,true,true,false,false,false,false,true,false,false,true,true,false,true,true,false,false,false,true,false,true,false,true,false,false,false,true,false,false,false,true,true,false,true,false,true,false,true,false,true,true,false,true,true,false,false,true,false,true,true,false,true,false,true,true,false,false,true,true,true,true,false,false,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,true,false,false,true,false,false,false,true,true,true,false,false,true,true,false,false,true,false,false,true,false,true,false,false,true,false,true,true,false,true,true,false,true,true,false,true,true,true,false,true,false,false,false,false,false,false,false,true,false,true,false,false,true,false,false,true,true,true,false,false,false,false,true,false,true,true,false,false,true,true,false,false,true,true,true,false,false,true,false,false,true,true,true,false,true,false,true,true,true,false,false,false,true,true,true,true,false,true,true,true,true,false,true,true,true,true,false,false,true,true,false,false,false,false,false,true,true,false,true,false,true,false,false,true,false,false,false,true,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,false,true,true,true,true,true,true,true,false,true,false,true,false,false,true,true,true,true,false,false,false,false,true,false,false,true,false,true,false};
    uint256_from_bytes(a, a83_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a83_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a84_data[32]  = {0x35,0xd2,0x60,0x1e,0x8e,0x45,0x48,0xaa,0x72,0x8b,0xa3,0x7f,0x59,0xfc,0x04,0x47,0x4a,0xf7,0x28,0x00,0x86,0x40,0x9d,0x26,0x9b,0x82,0xf6,0xe6,0x9f,0x05,0xa8,0x5f};
    bool         a84_bits[256] = {true,true,true,true,true,false,true,false,false,false,false,true,false,true,false,true,true,false,true,false,false,false,false,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,true,true,false,true,true,false,true,true,true,true,false,true,false,false,false,false,false,true,true,true,false,true,true,false,false,true,false,true,true,false,false,true,false,false,true,false,true,true,true,false,false,true,false,false,false,false,false,false,true,false,false,true,true,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,true,true,false,true,true,true,true,false,true,false,true,false,false,true,false,true,true,true,false,false,false,true,false,false,false,true,false,false,false,false,false,false,false,true,true,true,true,true,true,true,false,false,true,true,false,true,false,true,true,true,true,true,true,true,false,true,true,false,false,false,true,false,true,true,true,false,true,false,false,false,true,false,true,false,false,true,true,true,false,false,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,true,false,true,false,false,false,true,false,false,true,true,true,false,false,false,true,false,true,true,true,true,false,false,false,false,false,false,false,false,true,true,false,false,true,false,false,true,false,true,true,true,false,true,false,true,true,false,false};
    uint256_from_bytes(a, a84_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a84_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a85_data[32]  = {0x6d,0xca,0xa3,0xfd,0xb1,0x14,0x46,0xf4,0x48,0x2c,0x46,0x8c,0x1f,0xf3,0xef,0x1f,0xa1,0x54,0x41,0x52,0x97,0xa9,0x34,0xb0,0x05,0x12,0x2e,0x43,0x55,0x07,0xbf,0x16};
    bool         a85_bits[256] = {false,true,true,false,true,false,false,false,true,true,true,true,true,true,false,true,true,true,true,false,false,false,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,false,true,false,true,false,false,false,false,false,false,false,false,false,true,true,false,true,false,false,true,false,true,true,false,false,true,false,false,true,false,true,false,true,true,true,true,false,true,false,false,true,false,true,false,false,true,false,true,false,true,false,false,false,false,false,true,false,false,false,true,false,true,false,true,false,true,false,false,false,false,true,false,true,true,true,true,true,true,false,false,false,true,true,true,true,false,true,true,true,true,true,false,false,true,true,true,true,true,true,true,true,true,false,false,false,false,false,true,true,false,false,false,true,false,true,true,false,false,false,true,false,false,false,true,true,false,true,false,false,false,false,false,true,false,false,true,false,false,false,true,false,true,true,true,true,false,true,true,false,false,false,true,false,false,false,true,false,true,false,false,false,true,false,false,false,true,true,false,true,true,false,true,true,true,true,true,true,true,true,false,false,false,true,false,true,false,true,false,true,false,false,true,true,true,false,true,true,false,true,true,false};
    uint256_from_bytes(a, a85_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a85_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a86_data[32]  = {0x38,0xb1,0x7d,0x97,0xd1,0xe5,0x68,0x77,0xf0,0xd0,0xb8,0x63,0x09,0x23,0xd6,0x81,0xe8,0x58,0xfa,0x28,0x18,0x72,0x4c,0x3a,0x73,0x5a,0x90,0x39,0x52,0xdc,0x2c,0xc9};
    bool         a86_bits[256] = {true,false,false,true,false,false,true,true,false,false,true,true,false,true,false,false,false,false,true,true,true,false,true,true,false,true,false,false,true,false,true,false,true,false,false,true,true,true,false,false,false,false,false,false,true,false,false,true,false,true,false,true,true,false,true,false,true,true,false,false,true,true,true,false,false,true,false,true,true,true,false,false,false,false,true,true,false,false,true,false,false,true,false,false,true,true,true,false,false,false,false,true,true,false,false,false,false,false,false,true,false,true,false,false,false,true,false,true,true,true,true,true,false,false,false,true,true,false,true,false,false,false,false,true,false,true,true,true,true,false,false,false,false,false,false,true,false,true,true,false,true,false,true,true,true,true,false,false,false,true,false,false,true,false,false,true,false,false,false,false,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,true,false,false,false,false,true,false,true,true,false,false,false,false,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,true,false,true,true,false,true,false,true,false,false,true,true,true,true,false,false,false,true,false,true,true,true,true,true,false,true,false,false,true,true,false,true,true,true,true,true,false,true,false,false,false,true,true,false,true,false,false,false,true,true,true,false,false};
    uint256_from_bytes(a, a86_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a86_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a87_data[32]  = {0x9d,0x4f,0xa2,0x14,0x14,0x8a,0xd8,0x97,0x19,0xdc,0x69,0x65,0xcd,0xeb,0xd4,0xa1,0x5a,0x01,0xa6,0x1f,0x42,0x4d,0x53,0x2a,0x23,0x38,0xf5,0xbd,0x71,0x83,0xe9,0xe4};
    bool         a87_bits[256] = {false,false,true,false,false,true,true,true,true,false,false,true,false,true,true,true,true,true,false,false,false,false,false,true,true,false,false,false,true,true,true,false,true,false,true,true,true,true,false,true,true,false,true,false,true,true,true,true,false,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,false,true,false,true,false,true,false,false,true,true,false,false,true,false,true,false,true,false,true,true,false,false,true,false,false,true,false,false,false,false,true,false,true,true,true,true,true,false,false,false,false,true,true,false,false,true,false,true,true,false,false,false,false,false,false,false,false,true,false,true,true,false,true,false,true,false,false,false,false,true,false,true,false,false,true,false,true,false,true,true,true,true,false,true,false,true,true,true,true,false,true,true,false,false,true,true,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,false,false,false,true,true,true,false,true,true,true,false,false,true,true,false,false,false,true,true,true,false,true,false,false,true,false,false,false,true,true,false,true,true,false,true,false,true,false,false,false,true,false,false,true,false,true,false,false,false,false,false,true,false,true,false,false,false,false,true,false,false,false,true,false,true,true,true,true,true,false,false,true,false,true,false,true,true,true,false,false,true};
    uint256_from_bytes(a, a87_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a87_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a88_data[32]  = {0x0a,0xcb,0x11,0x3b,0x49,0x8a,0x3d,0x40,0x7a,0x0b,0x5e,0x6a,0x58,0xaa,0x7a,0x02,0x05,0x2b,0xde,0x9c,0x0d,0xf4,0xce,0x0c,0xda,0xb6,0xca,0xd2,0x2c,0x03,0x3a,0x2a};
    bool         a88_bits[256] = {false,true,false,true,false,true,false,false,false,true,false,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,true,true,false,true,true,false,true,false,true,false,true,true,false,true,true,false,false,true,true,false,false,false,false,false,true,true,true,false,false,true,true,false,false,true,false,true,true,true,true,true,false,true,true,false,false,false,false,false,false,true,true,true,false,false,true,false,true,true,true,true,false,true,true,true,true,false,true,false,true,false,false,true,false,true,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true,false,true,true,true,true,false,false,true,false,true,false,true,false,true,false,false,false,true,true,false,true,false,false,true,false,true,false,true,true,false,false,true,true,true,true,false,true,false,true,true,false,true,false,false,false,false,false,true,false,true,true,true,true,false,false,false,false,false,false,false,true,false,true,false,true,true,true,true,false,false,false,true,false,true,false,false,false,true,true,false,false,true,false,false,true,false,true,true,false,true,true,true,false,false,true,false,false,false,true,false,false,false,true,true,false,true,false,false,true,true,false,true,false,true,false,false,false,false};
    uint256_from_bytes(a, a88_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a88_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a89_data[32]  = {0x4f,0x57,0x16,0x41,0x14,0x44,0x37,0xeb,0x1c,0xbb,0xf0,0xf8,0x22,0xd0,0x36,0x16,0xc0,0x9c,0x3b,0x05,0x5c,0x20,0x93,0x13,0x01,0xe7,0x43,0x5b,0xf6,0x93,0x47,0xeb};
    bool         a89_bits[256] = {true,true,false,true,false,true,true,true,true,true,true,false,false,false,true,false,true,true,false,false,true,false,false,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,true,true,true,false,false,false,false,false,false,false,true,true,false,false,true,false,false,false,true,true,false,false,true,false,false,true,false,false,false,false,false,true,false,false,false,false,true,true,true,false,true,false,true,false,true,false,false,false,false,false,true,true,false,true,true,true,false,false,false,false,true,true,true,false,false,true,false,false,false,false,false,false,true,true,false,true,true,false,true,false,false,false,false,true,true,false,true,true,false,false,false,false,false,false,true,false,true,true,false,true,false,false,false,true,false,false,false,false,false,true,true,true,true,true,false,false,false,false,true,true,true,true,true,true,false,true,true,true,false,true,false,false,true,true,true,false,false,false,true,true,false,true,false,true,true,true,true,true,true,false,true,true,false,false,false,false,true,false,false,false,true,false,false,false,true,false,true,false,false,false,true,false,false,false,false,false,true,false,false,true,true,false,true,false,false,false,true,true,true,false,true,false,true,false,true,true,true,true,false,false,true,false};
    uint256_from_bytes(a, a89_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a89_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a90_data[32]  = {0x3c,0xd7,0x93,0xfa,0xd1,0x2f,0xf9,0xe2,0x2d,0x12,0x0c,0xf9,0xaf,0x48,0xb5,0xaf,0x35,0xae,0xd2,0x0e,0x29,0xbd,0x9d,0x33,0xe9,0x1c,0xd0,0xd4,0xbb,0x86,0x53,0x47};
    bool         a90_bits[256] = {true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,false,false,true,true,false,false,false,false,true,true,true,false,true,true,true,false,true,false,false,true,false,true,false,true,true,false,false,false,false,true,false,true,true,false,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,true,true,false,false,true,true,false,false,true,false,true,true,true,false,false,true,true,false,true,true,true,true,false,true,true,false,false,true,false,true,false,false,false,true,true,true,false,false,false,false,false,true,false,false,true,false,true,true,false,true,true,true,false,true,false,true,true,false,true,false,true,true,false,false,true,true,true,true,false,true,false,true,true,false,true,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,true,true,false,true,false,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,false,false,true,false,false,true,false,false,false,true,false,true,true,false,true,false,false,false,true,false,false,false,true,true,true,true,false,false,true,true,true,true,true,true,true,true,true,false,true,false,false,true,false,false,false,true,false,true,true,false,true,false,true,true,true,true,true,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,true,false,false,true,true,true,true,false,false};
    uint256_from_bytes(a, a90_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a90_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a91_data[32]  = {0xe8,0x8c,0x89,0xc0,0xe8,0x1a,0xe3,0xb6,0x2d,0x57,0x0e,0xac,0x03,0x25,0xbc,0xd3,0x1e,0x42,0x2b,0x03,0x71,0x3f,0x38,0xda,0xd4,0xd1,0xcd,0x44,0x2b,0xef,0x06,0x04};
    bool         a91_bits[256] = {false,false,true,false,false,false,false,false,false,true,true,false,false,false,false,false,true,true,true,true,false,true,true,true,true,true,false,true,false,true,false,false,false,false,true,false,false,false,true,false,true,false,true,true,false,false,true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,false,true,true,false,true,false,true,true,false,true,true,false,false,false,true,true,true,false,false,true,true,true,true,true,true,false,false,true,false,false,false,true,true,true,false,true,true,false,false,false,false,false,false,true,true,false,true,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,true,true,false,false,false,true,true,false,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,false,false,true,false,false,true,true,false,false,false,false,false,false,false,false,true,true,false,true,false,true,false,true,true,true,false,false,false,false,true,true,true,false,true,false,true,false,true,false,true,true,false,true,false,false,false,true,true,false,true,true,false,true,true,true,false,false,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,false,true,true,true,false,false,false,false,false,false,true,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,false,true,false,false,false,true,false,true,true,true};
    uint256_from_bytes(a, a91_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a91_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a92_data[32]  = {0x1f,0x07,0x48,0xb5,0xaa,0xda,0x54,0x1b,0xb5,0x1f,0x06,0x85,0xc3,0xc5,0x2a,0x44,0x4e,0x18,0xf6,0xe9,0x66,0x72,0x71,0xf5,0x16,0xb9,0xfd,0x7b,0x0c,0xe0,0x82,0x1a};
    bool         a92_bits[256] = {false,true,false,true,true,false,false,false,false,true,false,false,false,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,false,false,false,false,true,true,false,true,true,true,true,false,true,false,true,true,true,true,true,true,true,false,false,true,true,true,false,true,false,true,true,false,true,false,false,false,true,false,true,false,true,true,true,true,true,false,false,false,true,true,true,false,false,true,false,false,true,true,true,false,false,true,true,false,false,true,true,false,true,false,false,true,false,true,true,true,false,true,true,false,true,true,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,true,false,false,false,true,false,false,false,true,false,false,true,false,true,false,true,false,false,true,false,true,false,false,false,true,true,true,true,false,false,false,false,true,true,true,false,true,false,false,false,false,true,false,true,true,false,false,false,false,false,true,true,true,true,true,false,false,false,true,false,true,false,true,true,false,true,true,true,false,true,true,false,false,false,false,false,true,false,true,false,true,false,false,true,false,true,true,false,true,true,false,true,false,true,false,true,false,true,true,false,true,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,true,false,false,false,false,false,true,true,true,true,true,false,false,false};
    uint256_from_bytes(a, a92_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a92_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a93_data[32]  = {0x41,0x17,0x84,0xb3,0x3c,0x24,0xd3,0x32,0x39,0xc7,0x92,0x91,0x9a,0x7c,0x25,0x4b,0x39,0xe4,0x8d,0x47,0x97,0x95,0x3f,0xfc,0xcb,0x66,0x5b,0x58,0xca,0x4d,0xec,0x85};
    bool         a93_bits[256] = {true,false,true,false,false,false,false,true,false,false,true,true,false,true,true,true,true,false,true,true,false,false,true,false,false,true,false,true,false,false,true,true,false,false,false,true,true,false,true,false,true,true,false,true,true,false,true,false,false,true,true,false,false,true,true,false,true,true,false,true,false,false,true,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,false,true,false,true,false,false,true,true,true,true,false,true,false,false,true,true,true,true,false,false,false,true,false,true,false,true,true,false,false,false,true,false,false,true,false,false,true,true,true,true,false,false,true,true,true,false,false,true,true,false,true,false,false,true,false,true,false,true,false,false,true,false,false,false,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,false,true,false,false,true,false,true,false,false,true,false,false,true,true,true,true,false,false,false,true,true,true,false,false,true,true,true,false,false,false,true,false,false,true,true,false,false,true,true,false,false,true,false,true,true,false,false,true,false,false,true,false,false,false,false,true,true,true,true,false,false,true,true,false,false,true,true,false,true,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,false,true,false,false,false,false,false,true,false};
    uint256_from_bytes(a, a93_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a93_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a94_data[32]  = {0xfb,0x60,0xeb,0xed,0x65,0xca,0xb2,0x48,0x8c,0xe2,0xcb,0xf7,0x6f,0x3a,0xa0,0xb9,0x30,0xc5,0x90,0x88,0x5a,0x9c,0xda,0x6f,0xda,0xd0,0x96,0xb1,0x33,0x52,0x12,0xb1};
    bool         a94_bits[256] = {true,false,false,false,true,true,false,true,false,true,false,false,true,false,false,false,false,true,false,false,true,false,true,false,true,true,false,false,true,true,false,false,true,false,false,false,true,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,true,false,true,true,false,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,false,true,false,true,true,false,true,true,false,false,true,true,true,false,false,true,false,true,false,true,true,false,true,false,false,false,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,false,true,false,false,false,true,true,false,false,false,false,true,true,false,false,true,false,false,true,true,true,false,true,false,false,false,false,false,true,false,true,false,true,false,true,true,true,false,false,true,true,true,true,false,true,true,false,true,true,true,false,true,true,true,true,true,true,false,true,false,false,true,true,false,true,false,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,false,true,false,false,true,false,false,true,false,false,true,true,false,true,false,true,false,true,false,false,true,true,true,false,true,false,false,true,true,false,true,false,true,true,false,true,true,true,true,true,false,true,false,true,true,true,false,false,false,false,false,true,true,false,true,true,false,true,true,true,true,true};
    uint256_from_bytes(a, a94_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a94_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a95_data[32]  = {0xa7,0x66,0x52,0x98,0xe4,0xa5,0x87,0xc2,0xf4,0x32,0x1e,0x8b,0xe7,0x64,0x1b,0xfb,0xec,0xfb,0x7a,0xa7,0xca,0xd8,0x9d,0xb4,0x8d,0x7c,0x8b,0xff,0x45,0xa6,0xdf,0x0e};
    bool         a95_bits[256] = {false,true,true,true,false,false,false,false,true,true,true,true,true,false,true,true,false,true,true,false,false,true,false,true,true,false,true,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,true,false,false,true,true,true,true,true,false,true,false,true,true,false,false,false,true,false,false,true,false,true,true,false,true,true,false,true,true,true,false,false,true,false,false,false,true,true,false,true,true,false,true,false,true,false,false,true,true,true,true,true,false,false,true,false,true,false,true,false,true,true,true,true,false,true,true,false,true,true,true,true,true,false,false,true,true,false,true,true,true,true,true,false,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,true,false,false,true,true,false,true,true,true,false,false,true,true,true,true,true,false,true,false,false,false,true,false,true,true,true,true,false,false,false,false,true,false,false,true,true,false,false,false,false,true,false,true,true,true,true,false,true,false,false,false,false,true,true,true,true,true,false,false,false,false,true,true,false,true,false,false,true,false,true,false,false,true,false,false,true,true,true,false,false,false,true,true,false,false,true,false,true,false,false,true,false,true,false,false,true,true,false,false,true,true,false,true,true,true,false,false,true,false,true};
    uint256_from_bytes(a, a95_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a95_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a96_data[32]  = {0xa7,0x42,0x57,0xcc,0x12,0xb1,0x36,0x66,0x95,0x87,0x5d,0x07,0x00,0xcf,0x4f,0x1e,0x49,0x8e,0x32,0x6f,0x96,0x16,0x47,0xa3,0xd4,0xdb,0xeb,0x7a,0x2d,0xf4,0x6e,0xf6};
    bool         a96_bits[256] = {false,true,true,false,true,true,true,true,false,true,true,true,false,true,true,false,false,false,true,false,true,true,true,true,true,false,true,true,false,true,false,false,false,true,false,true,true,true,true,false,true,true,false,true,false,true,true,true,true,true,false,true,true,false,true,true,false,false,true,false,true,false,true,true,true,true,false,false,false,true,false,true,true,true,true,false,false,false,true,false,false,true,true,false,true,false,false,false,false,true,true,false,true,false,false,true,true,true,true,true,false,true,true,false,false,true,false,false,true,true,false,false,false,true,true,true,false,false,false,true,true,false,false,true,false,false,true,false,false,true,true,true,true,false,false,false,true,true,true,true,false,false,true,false,true,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false,true,true,true,false,false,false,false,false,true,false,true,true,true,false,true,false,true,true,true,false,false,false,false,true,true,false,true,false,true,false,false,true,false,true,true,false,false,true,true,false,false,true,true,false,true,true,false,false,true,false,false,false,true,true,false,true,false,true,false,false,true,false,false,false,false,false,true,true,false,false,true,true,true,true,true,false,true,false,true,false,false,true,false,false,false,false,true,false,true,true,true,false,false,true,false,true};
    uint256_from_bytes(a, a96_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a96_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a97_data[32]  = {0x1b,0x29,0x94,0x02,0x8d,0x6e,0x24,0x88,0x01,0xce,0xfa,0x16,0xe8,0x3f,0x21,0x7f,0x88,0xe0,0x79,0xea,0x53,0x17,0x03,0x00,0x3b,0x9d,0x84,0x74,0x1a,0x28,0xa1,0xa5};
    bool         a97_bits[256] = {true,false,true,false,false,true,false,true,true,false,false,false,false,true,false,true,false,false,false,true,false,true,false,false,false,true,false,true,true,false,false,false,false,false,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,false,true,true,true,false,false,true,true,true,false,true,true,true,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,true,false,false,true,false,true,false,true,true,true,true,false,false,true,true,true,true,false,false,false,false,false,false,true,true,true,false,false,false,true,false,false,false,true,true,true,true,true,true,true,true,false,true,false,false,false,false,true,false,false,true,true,true,true,true,true,false,false,false,false,false,true,false,true,true,true,false,true,true,false,true,false,false,false,false,true,false,true,true,true,true,true,false,true,true,true,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,false,false,true,false,false,true,false,false,false,true,true,true,false,true,true,false,true,false,true,true,false,false,false,true,false,true,false,false,false,false,false,false,false,false,true,false,true,false,false,true,true,false,false,true,false,true,false,false,true,true,false,true,true,false,false,false};
    uint256_from_bytes(a, a97_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a97_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a98_data[32]  = {0x08,0x1f,0xa1,0xa4,0xeb,0x3e,0xcd,0x17,0x0a,0xc0,0x6d,0xb8,0x22,0xd0,0xca,0xa6,0x3e,0x72,0x99,0xd6,0x66,0xf8,0x75,0x87,0xaa,0x0b,0xbe,0x12,0x77,0x09,0x57,0xef};
    bool         a98_bits[256] = {true,true,true,true,false,true,true,true,true,true,true,false,true,false,true,false,true,false,false,true,false,false,false,false,true,true,true,false,true,true,true,false,false,true,false,false,true,false,false,false,false,true,true,true,true,true,false,true,true,true,false,true,false,false,false,false,false,true,false,true,false,true,false,true,true,true,true,false,false,false,false,true,true,false,true,false,true,true,true,false,false,false,false,true,true,true,true,true,false,true,true,false,false,true,true,false,false,true,true,false,true,false,true,true,true,false,false,true,true,false,false,true,false,true,false,false,true,true,true,false,false,true,true,true,true,true,false,false,false,true,true,false,false,true,false,true,false,true,false,true,false,false,true,true,false,false,false,false,true,false,true,true,false,true,false,false,false,true,false,false,false,false,false,true,true,true,false,true,true,false,true,true,false,true,true,false,false,false,false,false,false,false,true,true,false,true,false,true,false,false,false,false,true,true,true,false,true,false,false,false,true,false,true,true,false,false,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,true,true,false,false,true,false,false,true,false,true,true,false,false,false,false,true,false,true,true,true,true,true,true,false,false,false,false,false,false,true,false,false,false,false};
    uint256_from_bytes(a, a98_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a98_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }

    std::uint8_t a99_data[32]  = {0xd4,0xca,0x3a,0x58,0x24,0xf0,0x24,0xe1,0x9e,0x6e,0x1b,0xa7,0xaf,0xbc,0xd2,0x0d,0xdc,0xe0,0x4d,0x3e,0xb4,0xf4,0x4a,0x44,0x77,0x85,0x27,0x68,0xa7,0x5a,0x27,0x86};
    bool         a99_bits[256] = {false,true,true,false,false,false,false,true,true,true,true,false,false,true,false,false,false,true,false,true,true,false,true,false,true,true,true,false,false,true,false,true,false,false,false,true,false,true,true,false,true,true,true,false,false,true,false,false,true,false,true,false,false,false,false,true,true,true,true,false,true,true,true,false,false,false,true,false,false,false,true,false,false,true,false,true,false,false,true,false,false,false,true,false,true,true,true,true,false,false,true,false,true,true,false,true,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,false,false,false,false,false,false,true,true,true,false,false,true,true,true,false,true,true,true,false,true,true,false,false,false,false,false,true,false,false,true,false,true,true,false,false,true,true,true,true,false,true,true,true,true,true,false,true,false,true,true,true,true,false,false,true,false,true,true,true,false,true,true,false,false,false,false,true,true,true,false,true,true,false,false,true,true,true,true,false,false,true,true,false,false,false,false,true,true,true,false,false,true,false,false,true,false,false,false,false,false,false,true,true,true,true,false,false,true,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,true,true,true,false,false,false,true,false,true,false,false,true,true,false,false,true,false,true,false,true,true};
    uint256_from_bytes(a, a99_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a99_bits[i])
        {
            throw std::runtime_error("err in uint256_x64_bittest");
        }
    }
}
#else
void test_uint256_x64_bittest()
{
}
#endif