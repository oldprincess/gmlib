#include <gmlib/number/uint256.h>

#include <stdexcept>

using namespace number;

void test_uint256_bittest()
{
    uint256_t a;

    std::uint8_t a0_data[32]  = {0x09,0x99,0x50,0xd8,0x36,0xf6,0x75,0xcc,0x81,0xe7,0x4e,0xf5,0xe8,0xe2,0x5d,0x94,0x0e,0xd9,0x04,0x75,0x95,0x31,0x98,0x5d,0x5d,0x9d,0xc9,0xf8,0x18,0x18,0xe8,0x11};
    bool         a0_bits[256] = {true,false,false,false,true,false,false,false,false,false,false,true,false,true,true,true,false,false,false,true,true,false,false,false,false,false,false,true,true,false,false,false,false,false,false,true,true,true,true,true,true,false,false,true,false,false,true,true,true,false,true,true,true,false,false,true,true,false,true,true,true,false,true,false,true,false,true,true,true,false,true,false,false,false,false,true,true,false,false,true,true,false,false,false,true,true,false,false,true,false,true,false,true,false,false,true,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,false,true,false,false,true,true,false,true,true,false,true,true,true,false,false,false,false,false,false,true,false,true,false,false,true,true,false,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,false,false,true,false,true,true,true,true,false,true,false,true,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,false,true,true,true,true,false,false,false,false,false,false,true,false,false,true,true,false,false,true,true,true,false,true,false,true,true,true,false,false,true,true,false,true,true,true,true,false,true,true,false,true,true,false,false,false,false,false,true,true,false,true,true,false,false,false,false,true,false,true,false,true,false,false,true,true,false,false,true,true,false,false,true,false,false,false,false};
    uint256_from_bytes(a, a0_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a0_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a1_data[32]  = {0xf2,0x9d,0x0d,0xa9,0x95,0x3f,0x48,0xf1,0xa0,0x9f,0x76,0xb5,0xa1,0x70,0xb3,0x38,0x39,0x26,0x30,0x59,0xf2,0x8c,0x10,0x5d,0x1f,0xb1,0x7c,0x23,0x90,0xc1,0x92,0xcf};
    bool         a1_bits[256] = {true,true,true,true,false,false,true,true,false,true,false,false,true,false,false,true,true,false,false,false,false,false,true,true,false,false,false,false,true,false,false,true,true,true,false,false,false,true,false,false,false,false,true,true,true,true,true,false,true,false,false,false,true,true,false,true,true,true,true,true,true,false,false,false,true,false,true,true,true,false,true,false,false,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,false,true,false,false,true,true,true,true,true,false,false,true,true,false,true,false,false,false,false,false,true,true,false,false,false,true,true,false,false,true,false,false,true,false,false,true,true,true,false,false,false,false,false,true,true,true,false,false,true,true,false,false,true,true,false,true,false,false,false,false,true,true,true,false,true,false,false,false,false,true,false,true,true,false,true,false,true,true,false,true,false,true,true,false,true,true,true,false,true,true,true,true,true,false,false,true,false,false,false,false,false,true,false,true,true,false,false,false,true,true,true,true,false,false,false,true,false,false,true,false,true,true,true,true,true,true,false,false,true,false,true,false,true,false,false,true,true,false,false,true,false,true,false,true,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,false,true,false,false,true,true,true,true};
    uint256_from_bytes(a, a1_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a1_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a2_data[32]  = {0x30,0x18,0x50,0xc5,0xa3,0x8f,0xd5,0x47,0x92,0x3a,0x73,0x69,0x94,0xe3,0xbf,0x91,0x1a,0x61,0xdb,0xe2,0x2e,0x44,0x15,0x8b,0xae,0x97,0xba,0x94,0xd0,0xed,0xa8,0x2f};
    bool         a2_bits[256] = {true,true,true,true,false,true,false,false,false,false,false,true,false,true,false,true,true,false,true,true,false,true,true,true,false,false,false,false,true,false,true,true,false,false,true,false,true,false,false,true,false,true,false,true,true,true,false,true,true,true,true,false,true,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,false,false,true,true,false,true,false,true,false,false,false,false,false,true,false,false,false,true,false,false,true,true,true,false,true,false,false,false,true,false,false,false,true,true,true,true,true,false,true,true,false,true,true,true,false,false,false,false,true,true,false,false,true,false,true,true,false,false,false,true,false,false,false,true,false,false,true,true,true,true,true,true,true,false,true,true,true,false,false,false,true,true,true,false,false,true,false,true,false,false,true,true,false,false,true,false,true,true,false,true,true,false,false,true,true,true,false,false,true,false,true,true,true,false,false,false,true,false,false,true,false,false,true,true,true,true,false,false,false,true,false,true,false,true,false,true,false,true,true,true,true,true,true,false,false,false,true,true,true,false,false,false,true,false,true,true,false,true,false,false,false,true,true,false,false,false,false,true,false,true,false,false,false,false,true,true,false,false,false,false,false,false,false,true,true,false,false};
    uint256_from_bytes(a, a2_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a2_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a3_data[32]  = {0x34,0xb9,0xb5,0xdf,0x9e,0x77,0x69,0xb1,0x0f,0x42,0x05,0xb4,0x90,0x7a,0x70,0xc3,0x10,0x12,0xf0,0x37,0xb6,0x4c,0xe4,0x22,0x8c,0x38,0xfb,0x29,0x18,0xf1,0x35,0xd2};
    bool         a3_bits[256] = {false,true,false,false,true,false,true,true,true,false,true,false,true,true,false,false,true,false,false,false,true,true,true,true,false,false,false,true,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,true,true,true,true,true,false,false,false,true,true,true,false,false,false,false,true,true,false,false,false,true,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,true,false,false,true,true,false,false,true,false,false,true,true,false,true,true,false,true,true,true,true,false,true,true,false,false,false,false,false,false,true,true,true,true,false,true,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,true,false,false,false,false,true,true,false,false,false,false,true,true,true,false,false,true,false,true,true,true,true,false,false,false,false,false,true,false,false,true,false,false,true,false,true,true,false,true,true,false,true,false,false,false,false,false,false,true,false,false,false,false,true,false,true,true,true,true,false,false,false,false,true,false,false,false,true,true,false,true,true,false,false,true,false,true,true,false,true,true,true,false,true,true,true,false,false,true,true,true,true,false,false,true,true,true,true,true,true,false,true,true,true,false,true,false,true,true,false,true,true,false,false,true,true,true,false,true,false,false,true,false,true,true,false,false};
    uint256_from_bytes(a, a3_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a3_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a4_data[32]  = {0xec,0x66,0xa7,0x87,0x95,0xe7,0x61,0xd1,0x77,0x31,0xaf,0x10,0x50,0x6b,0xf2,0xef,0xc6,0xf8,0x77,0x18,0x6d,0x76,0xb0,0x7e,0x88,0x1e,0xd1,0x62,0xae,0x2e,0xb1,0x54};
    bool         a4_bits[256] = {false,false,true,false,true,false,true,false,true,false,false,false,true,true,false,true,false,true,true,true,false,true,false,false,false,true,true,true,false,true,false,true,false,true,false,false,false,true,true,false,true,false,false,false,true,false,true,true,false,true,true,true,true,false,false,false,false,false,false,true,false,false,false,true,false,true,true,true,true,true,true,false,false,false,false,false,true,true,false,true,false,true,true,false,true,true,true,false,true,false,true,true,false,true,true,false,false,false,false,true,true,false,false,false,true,true,true,false,true,true,true,false,false,false,false,true,true,true,true,true,false,true,true,false,false,false,true,true,true,true,true,true,false,true,true,true,false,true,false,false,true,true,true,true,true,true,false,true,false,true,true,false,false,false,false,false,true,false,true,false,false,false,false,false,true,false,false,false,true,true,true,true,false,true,false,true,true,false,false,false,true,true,false,false,true,true,true,false,true,true,true,false,true,false,false,false,true,false,true,true,true,false,false,false,false,true,true,false,true,true,true,false,false,true,true,true,true,false,true,false,true,false,false,true,true,true,true,false,false,false,false,true,true,true,true,false,false,true,false,true,false,true,true,false,false,true,true,false,false,false,true,true,false,true,true,true};
    uint256_from_bytes(a, a4_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a4_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a5_data[32]  = {0x3e,0x7d,0x1b,0xfb,0xc7,0xa2,0xea,0x20,0xb2,0xf1,0x4c,0x94,0x2e,0x05,0x31,0x9a,0xcb,0x5c,0x74,0x27,0x3f,0x98,0xe2,0x77,0x4c,0xbd,0x87,0xad,0x5c,0x90,0xa9,0x58};
    bool         a5_bits[256] = {false,false,false,true,true,false,true,false,true,false,false,true,false,true,false,true,false,false,false,false,true,false,false,true,false,false,true,true,true,false,true,false,true,false,true,true,false,true,false,true,true,true,true,false,false,false,false,true,true,false,true,true,true,true,false,true,false,false,true,true,false,false,true,false,true,true,true,false,true,true,true,false,false,true,false,false,false,true,true,true,false,false,false,true,true,false,false,true,true,true,true,true,true,true,false,false,true,true,true,false,false,true,false,false,false,false,true,false,true,true,true,false,false,false,true,true,true,false,true,false,true,true,false,true,false,false,true,true,false,true,false,true,true,false,false,true,true,false,false,false,true,true,false,false,true,false,true,false,false,false,false,false,false,true,true,true,false,true,false,false,false,false,true,false,true,false,false,true,false,false,true,true,false,false,true,false,true,false,false,false,true,true,true,true,false,true,false,false,true,true,false,true,false,false,false,false,false,true,false,false,false,true,false,true,false,true,true,true,false,true,false,false,false,true,false,true,true,true,true,false,false,false,true,true,true,true,false,true,true,true,true,true,true,true,false,true,true,false,false,false,true,false,true,true,true,true,true,false,false,true,true,true,true,true,false,false};
    uint256_from_bytes(a, a5_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a5_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a6_data[32]  = {0x72,0xe6,0xcc,0x3a,0xba,0xbc,0xed,0x20,0x57,0xee,0x05,0xcd,0xe0,0x09,0x02,0xc7,0x7e,0xbf,0xf2,0x06,0x86,0x73,0x47,0x21,0x4c,0xdd,0x20,0x55,0x93,0x0d,0x6e,0xaf};
    bool         a6_bits[256] = {true,true,true,true,false,true,false,true,false,true,true,true,false,true,true,false,true,false,true,true,false,false,false,false,true,true,false,false,true,false,false,true,true,false,true,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,true,true,true,false,true,true,false,false,true,true,false,false,true,false,true,false,false,false,false,true,false,false,true,true,true,false,false,false,true,false,true,true,false,false,true,true,true,false,false,true,true,false,false,false,false,true,false,true,true,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,false,true,false,true,true,true,true,true,true,false,true,true,true,false,false,false,true,true,false,true,false,false,false,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,false,true,true,true,true,false,true,true,false,false,true,true,true,false,true,false,false,false,false,false,false,true,true,true,false,true,true,true,true,true,true,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,true,true,false,true,true,true,false,false,true,true,true,true,false,true,false,true,false,true,true,true,false,true,false,true,false,true,true,true,false,false,false,false,true,true,false,false,true,true,false,true,true,false,false,true,true,true,false,true,false,false,true,true,true,false};
    uint256_from_bytes(a, a6_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a6_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a7_data[32]  = {0xc1,0xd3,0xfc,0xff,0x2a,0x3a,0xf4,0xd4,0x6b,0x0a,0x18,0xe8,0x83,0x0e,0x07,0xbc,0x1e,0x39,0x8f,0x10,0x12,0xbd,0x4a,0xce,0xfa,0xec,0xbd,0x38,0x9b,0xe4,0xbc,0xfc};
    bool         a7_bits[256] = {false,false,true,true,true,true,true,true,false,false,true,true,true,true,false,true,false,false,true,false,false,true,true,true,true,true,false,true,true,false,false,true,false,false,false,true,true,true,false,false,true,false,true,true,true,true,false,true,false,false,true,true,false,true,true,true,false,true,false,true,true,true,true,true,false,true,true,true,false,false,true,true,false,true,false,true,false,false,true,false,true,false,true,true,true,true,false,true,false,true,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,true,true,true,false,false,false,true,true,false,false,true,true,true,false,false,false,true,true,true,true,false,false,false,false,false,true,true,true,true,false,true,true,true,true,false,false,false,false,false,false,true,true,true,false,false,false,false,true,true,false,false,false,false,false,true,false,false,false,true,false,true,true,true,false,false,false,true,true,false,false,false,false,true,false,true,false,false,false,false,true,true,false,true,false,true,true,false,false,false,true,false,true,false,true,true,false,false,true,false,true,true,true,true,false,true,false,true,true,true,false,false,false,true,false,true,false,true,false,false,true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,true,true,true,false,false,true,false,true,true,true,false,false,false,false,false,true,true};
    uint256_from_bytes(a, a7_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a7_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a8_data[32]  = {0xb1,0xfe,0xe0,0x8f,0x57,0x12,0x42,0x42,0x50,0x51,0xc1,0xcc,0xd1,0x7f,0x9a,0xca,0xe0,0x1f,0x50,0x57,0xca,0x02,0x13,0x5e,0x92,0xb1,0xd3,0xf2,0x8e,0xde,0x0d,0x7a};
    bool         a8_bits[256] = {false,true,false,true,true,true,true,false,true,false,true,true,false,false,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,false,false,true,false,true,false,false,true,true,true,true,true,true,false,false,true,false,true,true,true,false,false,false,true,true,false,true,false,true,false,false,true,false,false,true,false,true,true,true,true,false,true,false,true,true,false,false,true,false,false,false,false,true,false,false,false,false,false,false,false,true,false,true,false,false,true,true,true,true,true,false,true,false,true,false,false,false,false,false,true,false,true,false,true,true,true,true,true,false,false,false,false,false,false,false,false,true,true,true,false,true,false,true,false,false,true,true,false,true,false,true,true,false,false,true,true,true,true,true,true,true,true,false,true,false,false,false,true,false,true,true,false,false,true,true,false,false,true,true,true,false,false,false,false,false,true,true,true,false,false,false,true,false,true,false,false,false,false,false,true,false,true,false,false,true,false,false,false,false,true,false,false,true,false,false,false,false,true,false,false,true,false,false,true,false,false,false,true,true,true,false,true,false,true,false,true,true,true,true,false,false,false,true,false,false,false,false,false,true,true,true,false,true,true,true,true,true,true,true,true,false,false,false,true,true,false,true};
    uint256_from_bytes(a, a8_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a8_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a9_data[32]  = {0xb3,0x94,0xfb,0x36,0xbb,0x2d,0x42,0x0f,0x0f,0x88,0x08,0x0b,0x10,0xa3,0xd6,0xb2,0xaa,0x05,0xe1,0x1a,0xb2,0x71,0x59,0x45,0x79,0x5e,0x82,0x29,0x45,0x1a,0xbd,0x81};
    bool         a9_bits[256] = {true,false,false,false,false,false,false,true,true,false,true,true,true,true,false,true,false,true,false,true,true,false,false,false,true,false,true,false,false,false,true,false,true,false,false,true,false,true,false,false,false,true,false,false,false,false,false,true,false,true,true,true,true,false,true,false,true,false,false,true,true,true,true,false,true,false,true,false,false,false,true,false,true,false,false,true,true,false,true,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,false,true,false,true,false,true,true,false,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,false,false,false,false,true,false,true,false,true,false,true,false,true,false,false,true,true,false,true,false,true,true,false,true,false,true,true,true,true,false,false,false,true,false,true,false,false,false,false,true,false,false,false,true,true,false,true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,true,true,true,true,false,false,false,false,true,true,true,true,false,false,false,false,false,true,false,false,false,false,true,false,true,false,true,true,false,true,false,false,true,true,false,true,true,true,false,true,false,true,true,false,true,true,false,false,true,true,false,true,true,true,true,true,false,false,true,false,true,false,false,true,true,true,false,false,true,true,false,true};
    uint256_from_bytes(a, a9_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a9_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a10_data[32]  = {0xb7,0x74,0xeb,0x52,0x48,0xdb,0x40,0xaf,0x72,0x15,0x83,0x70,0xd2,0x69,0xa9,0xa5,0xae,0x65,0x8f,0x33,0xfe,0x3b,0x89,0x0b,0x93,0xf4,0x48,0xb3,0xa5,0xaa,0x3c,0x81};
    bool         a10_bits[256] = {true,false,false,false,false,false,false,true,false,false,true,true,true,true,false,false,false,true,false,true,false,true,false,true,true,false,true,false,false,true,false,true,true,true,false,false,true,true,false,true,false,false,false,true,false,false,true,false,false,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,true,true,false,true,false,false,false,false,true,false,false,true,false,false,false,true,true,true,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,false,true,true,false,false,true,true,true,true,false,false,false,true,true,false,true,false,false,true,true,false,false,true,true,true,false,true,false,true,true,false,true,false,false,true,false,true,true,false,false,true,false,true,false,true,true,false,false,true,false,true,true,false,false,true,false,false,true,false,true,true,false,false,false,false,true,true,true,false,true,true,false,false,false,false,false,true,true,false,true,false,true,false,false,false,false,true,false,false,true,true,true,false,true,true,true,true,false,true,false,true,false,false,false,false,false,false,true,false,true,true,false,true,true,false,true,true,false,false,false,true,false,false,true,false,false,true,false,false,true,false,true,false,true,true,false,true,false,true,true,true,false,false,true,false,true,true,true,false,true,true,true,false,true,true,false,true};
    uint256_from_bytes(a, a10_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a10_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a11_data[32]  = {0xbd,0x05,0x61,0xe6,0x21,0x1c,0x70,0xcf,0x49,0x95,0x23,0x99,0xc4,0xaa,0xea,0xc1,0x37,0xdc,0x76,0xfb,0x0f,0x17,0xa3,0x00,0x7e,0x62,0xaa,0x0a,0x1d,0xf9,0xfd,0x78};
    bool         a11_bits[256] = {false,false,false,true,true,true,true,false,true,false,true,true,true,true,true,true,true,false,false,true,true,true,true,true,true,false,true,true,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,true,false,true,false,true,false,true,false,false,false,true,true,false,false,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,true,true,false,false,false,true,false,true,true,true,true,false,true,false,false,false,true,true,true,true,false,false,false,false,true,true,false,true,true,true,true,true,false,true,true,false,true,true,true,false,false,false,true,true,true,false,true,true,true,true,true,false,true,true,false,false,true,false,false,false,false,false,true,true,false,true,false,true,false,true,true,true,false,true,false,true,false,true,false,true,false,false,true,false,false,false,true,true,true,false,false,true,true,false,false,true,true,true,false,false,false,true,false,false,true,false,true,false,true,false,false,true,true,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,false,false,false,false,true,true,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,false,true,true,false,false,true,true,true,true,false,false,false,false,true,true,false,true,false,true,false,false,false,false,false,true,false,true,true,true,true,false,true};
    uint256_from_bytes(a, a11_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a11_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a12_data[32]  = {0x72,0xfd,0xf2,0x02,0x2a,0x96,0xfb,0x1a,0x14,0xa0,0xf9,0xe7,0x7f,0x1b,0x10,0x3c,0xdf,0x15,0x82,0xb0,0xea,0xb4,0x77,0xd2,0x64,0x15,0x47,0x9c,0x65,0xdc,0x9f,0x50};
    bool         a12_bits[256] = {false,false,false,false,true,false,true,false,true,true,true,true,true,false,false,true,false,false,true,true,true,false,true,true,true,false,true,false,false,true,true,false,false,false,true,true,true,false,false,true,true,true,true,false,false,false,true,false,true,false,true,false,true,false,false,false,false,false,true,false,false,true,true,false,false,true,false,false,true,false,true,true,true,true,true,false,true,true,true,false,false,false,true,false,true,true,false,true,false,true,false,true,false,true,true,true,false,false,false,false,true,true,false,true,false,true,false,false,false,false,false,true,true,false,true,false,true,false,false,false,true,true,true,true,true,false,true,true,false,false,true,true,true,true,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,false,false,false,true,true,true,true,true,true,true,false,true,true,true,false,false,true,true,true,true,false,false,true,true,true,true,true,false,false,false,false,false,true,false,true,false,false,true,false,true,false,false,false,false,true,false,true,true,false,false,false,true,true,false,true,true,true,true,true,false,true,true,false,true,false,false,true,false,true,false,true,false,true,false,false,false,true,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,false,true,true,true,true,true,true,false,true,false,false,true,true,true,false};
    uint256_from_bytes(a, a12_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a12_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a13_data[32]  = {0x8c,0xdb,0x30,0x5f,0xdd,0x2e,0x16,0x09,0x6e,0x36,0xaa,0xb0,0xd1,0xbc,0x52,0xd9,0x23,0x0d,0x97,0x7e,0xe2,0x25,0x71,0x59,0x47,0x20,0x77,0x1f,0x8c,0xa8,0x18,0x11};
    bool         a13_bits[256] = {true,false,false,false,true,false,false,false,false,false,false,true,true,false,false,false,false,false,false,true,false,true,false,true,false,false,true,true,false,false,false,true,true,true,true,true,true,false,false,false,true,true,true,false,true,true,true,false,false,false,false,false,false,true,false,false,true,true,true,false,false,false,true,false,true,false,false,true,true,false,true,false,true,false,false,false,true,true,true,false,true,false,true,false,false,true,false,false,false,true,false,false,false,true,true,true,false,true,true,true,true,true,true,false,true,true,true,false,true,false,false,true,true,false,true,true,false,false,false,false,true,true,false,false,false,true,false,false,true,false,false,true,true,false,true,true,false,true,false,false,true,false,true,false,false,false,true,true,true,true,false,true,true,false,false,false,true,false,true,true,false,false,false,false,true,true,false,true,false,true,false,true,false,true,false,true,false,true,true,false,true,true,false,false,false,true,true,true,false,true,true,false,true,false,false,true,false,false,false,false,false,true,true,false,true,false,false,false,false,true,true,true,false,true,false,false,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,false,false,false,false,false,true,true,false,false,true,true,false,true,true,false,true,true,false,false,true,true,false,false,false,true};
    uint256_from_bytes(a, a13_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a13_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a14_data[32]  = {0xf5,0x2d,0xdf,0x5d,0x61,0x64,0x99,0xc9,0xe2,0x5a,0x76,0x05,0xae,0xc6,0xf0,0x24,0x5b,0xd8,0x6d,0x40,0xfc,0x89,0x1b,0x4a,0x6a,0x50,0xdf,0x4d,0xb4,0xd6,0x6a,0x3a};
    bool         a14_bits[256] = {false,true,false,true,true,true,false,false,false,true,false,true,false,true,true,false,false,true,true,false,true,false,true,true,false,false,true,false,true,true,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,false,true,true,false,false,false,false,true,false,true,false,false,true,false,true,false,true,true,false,false,true,false,true,false,false,true,false,true,true,false,true,true,false,false,false,true,false,false,true,false,false,false,true,false,false,true,true,true,true,true,true,false,false,false,false,false,false,true,false,true,false,true,true,false,true,true,false,false,false,false,true,true,false,true,true,true,true,false,true,true,false,true,false,false,false,true,false,false,true,false,false,false,false,false,false,true,true,true,true,false,true,true,false,false,false,true,true,false,true,true,true,false,true,false,true,true,false,true,false,false,false,false,false,false,true,true,false,true,true,true,false,false,true,false,true,true,false,true,false,false,true,false,false,false,true,true,true,true,false,false,true,false,false,true,true,true,false,false,true,true,false,false,true,false,false,true,false,false,true,true,false,true,false,false,false,false,true,true,false,true,false,true,true,true,false,true,false,true,true,true,true,true,false,true,true,true,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true};
    uint256_from_bytes(a, a14_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a14_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a15_data[32]  = {0x03,0x16,0x90,0x9e,0x3b,0xbb,0xe9,0xea,0xa8,0x94,0x8c,0x89,0x3b,0x61,0x86,0x76,0x26,0xbb,0x7d,0xbd,0x2d,0x1c,0x9a,0xf0,0x15,0x3e,0x7c,0x2a,0x26,0xa2,0xc0,0xbd};
    bool         a15_bits[256] = {true,false,true,true,true,true,false,true,false,false,false,false,false,false,true,true,false,true,false,false,false,true,false,true,false,true,true,false,false,true,false,false,false,true,false,true,false,true,false,false,false,false,true,true,true,true,true,false,false,true,true,true,true,true,false,false,true,false,true,false,true,false,false,false,false,false,false,false,true,true,true,true,false,true,false,true,true,false,false,true,false,false,true,true,true,false,false,false,true,false,true,true,false,true,false,false,true,false,true,true,true,true,false,true,true,false,true,true,true,true,true,false,true,true,false,true,true,true,false,true,false,true,true,false,false,true,false,false,false,true,true,false,true,true,true,false,false,true,true,false,false,false,false,true,true,false,false,false,false,true,true,false,true,true,false,true,true,true,false,false,true,false,false,true,false,false,false,true,false,false,true,true,false,false,false,true,false,false,true,false,true,false,false,true,false,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,true,false,false,true,false,true,true,true,true,true,false,true,true,true,false,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,false,true,false,false,false,false,true,false,false,true,false,true,true,false,true,false,false,false,true,true,false,false,false,false,false,false};
    uint256_from_bytes(a, a15_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a15_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a16_data[32]  = {0x65,0xe7,0xe4,0x23,0x64,0x72,0xf1,0xa3,0x8f,0x2c,0x6e,0xc8,0xcc,0x41,0x69,0xa3,0xae,0x3a,0x2b,0x7f,0xdf,0xe0,0x18,0x93,0xf3,0xae,0xd0,0xb6,0xc7,0xac,0x14,0x91};
    bool         a16_bits[256] = {true,false,false,false,true,false,false,true,false,false,true,false,true,false,false,false,false,false,true,true,false,true,false,true,true,true,true,false,false,false,true,true,false,true,true,false,true,true,false,true,false,false,false,false,true,false,true,true,false,true,true,true,false,true,false,true,true,true,false,false,true,true,true,true,true,true,false,false,true,false,false,true,false,false,false,true,true,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,false,true,true,false,true,false,true,false,false,false,true,false,true,true,true,false,false,false,true,true,true,false,true,false,true,true,true,false,false,false,true,false,true,true,false,false,true,false,true,true,false,true,false,false,false,false,false,true,false,false,false,true,true,false,false,true,true,false,false,false,true,false,false,true,true,false,true,true,true,false,true,true,false,false,false,true,true,false,true,false,false,true,true,true,true,false,false,false,true,true,true,false,false,false,true,false,true,true,false,false,false,true,true,true,true,false,true,false,false,true,true,true,false,false,false,true,false,false,true,true,false,true,true,false,false,false,true,false,false,false,false,true,false,false,true,true,true,true,true,true,false,false,true,true,true,true,false,true,false,false,true,true,false};
    uint256_from_bytes(a, a16_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a16_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a17_data[32]  = {0x1a,0x35,0x8c,0xa0,0x0d,0x75,0x98,0x5d,0x99,0xc9,0x43,0x09,0x57,0x0d,0xc1,0x95,0x1c,0x24,0x42,0xf9,0x29,0x8c,0xb3,0xa5,0x70,0xcc,0xec,0x31,0x35,0x71,0x81,0x0a};
    bool         a17_bits[256] = {false,true,false,true,false,false,false,false,true,false,false,false,false,false,false,true,true,false,false,false,true,true,true,false,true,false,true,false,true,true,false,false,true,false,false,false,true,true,false,false,false,false,true,true,false,true,true,true,false,false,true,true,false,false,true,true,false,false,false,false,true,true,true,false,true,false,true,false,false,true,false,true,true,true,false,false,true,true,false,true,false,false,true,true,false,false,false,true,true,false,false,true,false,true,false,false,true,false,false,true,true,true,true,true,false,true,false,false,false,false,true,false,false,false,true,false,false,true,false,false,false,false,true,true,true,false,false,false,true,false,true,false,true,false,false,true,true,false,false,false,false,false,true,true,true,false,true,true,false,false,false,false,true,true,true,false,true,false,true,false,true,false,false,true,false,false,false,false,true,true,false,false,false,false,true,false,true,false,false,true,false,false,true,true,true,false,false,true,true,false,false,true,true,false,true,true,true,false,true,false,false,false,false,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,true,false,false,false,true,true,false,true,false,true,true,false,false,false,true,false,true,true,false,false,false};
    uint256_from_bytes(a, a17_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a17_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a18_data[32]  = {0x06,0x87,0x39,0xfa,0x9d,0x1d,0xe2,0xa0,0x5d,0x15,0x8a,0x2f,0xf2,0xee,0x4e,0x45,0x19,0xf9,0x91,0x9c,0x89,0x5f,0xd7,0xb3,0x26,0xb9,0x4c,0x7f,0x91,0x18,0xbb,0x16};
    bool         a18_bits[256] = {false,true,true,false,true,false,false,false,true,true,false,true,true,true,false,true,false,false,false,true,true,false,false,false,true,false,false,false,true,false,false,true,true,true,true,true,true,true,true,false,false,false,true,true,false,false,true,false,true,false,false,true,true,true,false,true,false,true,true,false,false,true,false,false,true,true,false,false,true,true,false,true,true,true,true,false,true,false,true,true,true,true,true,true,true,false,true,false,true,false,false,true,false,false,false,true,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,true,true,false,false,true,true,true,true,true,true,false,false,true,true,false,false,false,true,false,true,false,false,false,true,false,false,true,true,true,false,false,true,false,false,true,true,true,false,true,true,true,false,true,false,false,true,true,true,true,true,true,true,true,false,true,false,false,false,true,false,true,false,false,false,true,true,false,true,false,true,false,false,false,true,false,true,true,true,false,true,false,false,false,false,false,false,true,false,true,false,true,false,false,false,true,true,true,true,false,true,true,true,false,false,false,true,false,true,true,true,false,false,true,false,true,false,true,true,true,true,true,true,false,false,true,true,true,false,false,true,true,true,false,false,false,false,true,false,true,true,false,false,false,false,false};
    uint256_from_bytes(a, a18_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a18_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a19_data[32]  = {0xf4,0x99,0x8d,0x7c,0x40,0x93,0xf6,0xde,0xa2,0x68,0xaa,0x87,0x26,0x07,0x67,0x9d,0x60,0x50,0x91,0x4a,0x9d,0x33,0xa0,0x1c,0x35,0x3c,0x63,0x1c,0xdf,0xd4,0x3f,0x37};
    bool         a19_bits[256] = {true,true,true,false,true,true,false,false,true,true,true,true,true,true,false,false,false,false,true,false,true,false,true,true,true,true,true,true,true,false,true,true,false,false,true,true,true,false,false,false,true,true,false,false,false,true,true,false,false,false,true,true,true,true,false,false,true,false,true,false,true,true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,true,false,true,true,true,false,false,true,true,false,false,true,false,true,true,true,false,false,true,false,true,false,true,false,false,true,false,true,false,false,false,true,false,false,true,false,false,false,false,true,false,true,false,false,false,false,false,false,true,true,false,true,false,true,true,true,false,false,true,true,true,true,false,false,true,true,false,true,true,true,false,false,false,false,false,false,true,true,false,false,true,false,false,true,true,true,false,false,false,false,true,false,true,false,true,false,true,false,true,false,false,false,true,false,true,true,false,false,true,false,false,false,true,false,true,false,true,true,true,true,false,true,true,false,true,true,false,true,true,true,true,true,true,false,false,true,false,false,true,false,false,false,false,false,false,true,false,false,false,true,true,true,true,true,false,true,false,true,true,false,false,false,true,true,false,false,true,true,false,false,true,false,false,true,false,true,true,true,true};
    uint256_from_bytes(a, a19_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a19_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a20_data[32]  = {0xbf,0xea,0xa1,0x55,0x1a,0x28,0xf7,0xb3,0x24,0xe4,0xe2,0x5a,0x15,0xfc,0x89,0x9e,0x4f,0xd5,0x8d,0xbe,0x7b,0xdc,0x96,0x8b,0x7a,0xfb,0x2c,0x68,0x77,0x4b,0x15,0xd7};
    bool         a20_bits[256] = {true,true,true,false,true,false,true,true,true,false,true,false,true,false,false,false,true,true,false,true,false,false,true,false,true,true,true,false,true,true,true,false,false,false,false,true,false,true,true,false,false,false,true,true,false,true,false,false,true,true,false,true,true,true,true,true,false,true,false,true,true,true,true,false,true,true,false,true,false,false,false,true,false,true,true,false,true,false,false,true,false,false,true,true,true,false,true,true,true,true,false,true,true,true,true,false,false,true,true,true,true,true,false,true,true,false,true,true,false,false,false,true,true,false,true,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,true,true,true,false,false,true,true,false,false,true,false,false,false,true,false,false,true,true,true,true,true,true,true,false,true,false,true,false,false,false,false,true,false,true,true,false,true,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,true,false,false,true,false,false,true,false,false,true,true,false,false,true,true,false,true,true,true,true,false,true,true,true,true,false,false,false,true,false,true,false,false,false,true,false,true,true,false,false,false,true,false,true,false,true,false,true,false,true,false,false,false,false,true,false,true,false,true,false,true,false,true,true,true,true,true,true,true,true,true,false,true};
    uint256_from_bytes(a, a20_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a20_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a21_data[32]  = {0x05,0xe9,0x99,0xf3,0x84,0x2e,0x7f,0xc2,0x29,0x54,0x0a,0x6e,0xb1,0x2a,0xa1,0xf6,0xd4,0x2f,0xdd,0xbb,0x7a,0x86,0xf7,0xa2,0x43,0xc7,0x1b,0x9a,0xbd,0x87,0xa8,0x65};
    bool         a21_bits[256] = {true,false,true,false,false,true,true,false,false,false,false,true,false,true,false,true,true,true,true,false,false,false,false,true,true,false,true,true,true,true,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,false,false,false,true,true,true,false,false,false,true,true,true,true,false,false,false,false,true,false,false,true,false,false,false,true,false,true,true,true,true,false,true,true,true,true,false,true,true,false,false,false,false,true,false,true,false,true,true,true,true,false,true,true,false,true,true,true,false,true,true,false,true,true,true,false,true,true,true,true,true,true,false,true,false,false,false,false,true,false,true,false,true,true,false,true,true,false,true,true,true,true,true,false,false,false,false,true,false,true,false,true,false,true,false,true,false,false,true,false,false,false,true,true,false,true,false,true,true,true,false,true,true,false,false,true,false,true,false,false,false,false,false,false,true,false,true,false,true,false,true,false,false,true,false,true,false,false,false,true,false,false,false,false,true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,true,false,false,false,false,true,false,false,false,false,true,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,true,true,false,false,true,false,true,true,true,true,false,true,false,false,false,false,false};
    uint256_from_bytes(a, a21_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a21_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a22_data[32]  = {0xea,0x05,0x75,0x43,0x8b,0x0d,0x59,0x0b,0xb0,0xa8,0x44,0xe5,0x25,0x87,0xbe,0x6b,0x5c,0x9b,0xcf,0x35,0x87,0x3b,0xe0,0x78,0xf3,0xb7,0xa5,0x0d,0xf3,0x73,0xca,0x53};
    bool         a22_bits[256] = {true,true,false,false,true,false,true,false,false,true,false,true,false,false,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,true,true,true,true,false,true,true,false,false,false,false,true,false,true,false,false,true,false,true,true,true,true,false,true,true,false,true,true,true,false,false,true,true,true,true,false,false,false,true,true,true,true,false,false,false,false,false,false,true,true,true,true,true,false,true,true,true,false,false,true,true,true,false,false,false,false,true,true,false,true,false,true,true,false,false,true,true,true,true,false,false,true,true,true,true,false,true,true,false,false,true,false,false,true,true,true,false,true,false,true,true,false,true,false,true,true,false,false,true,true,true,true,true,false,true,true,true,true,false,false,false,false,true,true,false,true,false,false,true,false,false,true,false,true,false,false,true,true,true,false,false,true,false,false,false,true,false,false,false,false,true,false,true,false,true,false,false,false,false,true,true,false,true,true,true,false,true,false,false,false,false,true,false,false,true,true,false,true,false,true,false,true,true,false,false,false,false,true,true,false,true,false,false,false,true,true,true,false,false,false,false,true,false,true,false,true,false,true,true,true,false,true,false,true,false,false,false,false,false,false,true,false,true,false,true,true,true};
    uint256_from_bytes(a, a22_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a22_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a23_data[32]  = {0x56,0x75,0xf6,0xad,0x32,0x5b,0x55,0xdd,0x78,0x57,0x29,0x76,0x3a,0x12,0x91,0x7c,0x1a,0x26,0xf8,0x89,0x38,0x70,0x38,0x00,0x14,0x9e,0x25,0x9b,0x5d,0x58,0xc7,0x05};
    bool         a23_bits[256] = {true,false,true,false,false,false,false,false,true,true,true,false,false,false,true,true,false,false,false,true,true,false,true,false,true,false,true,true,true,false,true,false,true,true,false,true,true,false,false,true,true,false,true,false,false,true,false,false,false,true,true,true,true,false,false,true,false,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,false,false,false,false,true,true,true,false,false,false,false,true,true,true,false,false,true,false,false,true,false,false,false,true,false,false,false,true,true,true,true,true,false,true,true,false,false,true,false,false,false,true,false,true,true,false,false,false,false,false,true,true,true,true,true,false,true,false,false,false,true,false,false,true,false,true,false,false,true,false,false,false,false,true,false,true,true,true,false,false,false,true,true,false,true,true,true,false,true,false,false,true,false,true,false,false,true,true,true,false,true,false,true,false,false,false,false,true,true,true,true,false,true,false,true,true,true,false,true,true,true,false,true,false,true,false,true,false,true,true,false,true,true,false,true,false,false,true,false,false,true,true,false,false,true,false,true,true,false,true,false,true,false,true,true,false,true,true,true,true,true,false,true,false,true,true,true,false,false,true,true,false,true,false,true,false};
    uint256_from_bytes(a, a23_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a23_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a24_data[32]  = {0x2d,0xb3,0x99,0x7f,0xe3,0x96,0x39,0xbe,0x7a,0x60,0x5a,0x91,0x33,0x06,0x98,0xa1,0xc0,0x09,0x34,0x92,0xb6,0x24,0x67,0x71,0xc8,0x45,0x00,0x70,0x63,0x77,0x14,0x07};
    bool         a24_bits[256] = {true,true,true,false,false,false,false,false,false,false,true,false,true,false,false,false,true,true,true,false,true,true,true,false,true,true,false,false,false,true,true,false,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,true,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,true,false,false,false,true,true,true,false,true,true,true,false,false,true,true,false,false,false,true,false,false,true,false,false,false,true,true,false,true,true,false,true,false,true,false,false,true,false,false,true,false,false,true,false,true,true,false,false,true,false,false,true,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,false,false,true,false,true,false,false,false,true,true,false,false,true,false,true,true,false,false,false,false,false,true,true,false,false,true,true,false,false,true,false,false,false,true,false,false,true,false,true,false,true,true,false,true,false,false,false,false,false,false,true,true,false,false,true,false,true,true,true,true,false,false,true,true,true,true,true,false,true,true,false,false,true,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,true,false,true,false,false,true,true,false,false,true,true,true,false,false,true,true,false,true,true,false,true,true,false,true,false,false};
    uint256_from_bytes(a, a24_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a24_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a25_data[32]  = {0xb8,0xc9,0x81,0x7a,0xf8,0xbe,0x88,0x31,0xf2,0x37,0xe4,0x5a,0xcd,0x02,0xc5,0xe1,0x16,0x35,0x3d,0x03,0x55,0x1f,0xd8,0xf9,0xa2,0xc6,0x8e,0x45,0xca,0x04,0xc7,0x9f};
    bool         a25_bits[256] = {true,true,true,true,true,false,false,true,true,true,true,false,false,false,true,true,false,false,true,false,false,false,false,false,false,true,false,true,false,false,true,true,true,false,true,false,false,false,true,false,false,true,true,true,false,false,false,true,false,true,true,false,false,false,true,true,false,true,false,false,false,true,false,true,true,false,false,true,true,true,true,true,false,false,false,true,true,false,true,true,true,true,true,true,true,false,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,false,false,false,true,false,true,true,true,true,false,false,true,false,true,false,true,true,false,false,false,true,true,false,true,false,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,false,true,true,false,true,false,false,false,false,false,false,true,false,true,true,false,false,true,true,false,true,false,true,true,false,true,false,false,false,true,false,false,true,true,true,true,true,true,false,true,true,false,false,false,true,false,false,true,true,true,true,true,false,false,false,true,true,false,false,false,false,false,true,false,false,false,true,false,true,true,true,true,true,false,true,false,false,false,true,true,true,true,true,false,true,false,true,true,true,true,false,true,false,false,false,false,false,false,true,true,false,false,true,false,false,true,true,false,false,false,true,true,true,false,true};
    uint256_from_bytes(a, a25_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a25_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a26_data[32]  = {0xa7,0xe6,0x52,0x9b,0xce,0x76,0xe9,0xf4,0x77,0x21,0x6e,0x9e,0xe7,0xa4,0x63,0x09,0x97,0x3f,0x79,0x86,0x26,0xb1,0xcf,0xfc,0x07,0x0d,0x71,0x09,0x20,0x85,0x96,0x34};
    bool         a26_bits[256] = {false,false,true,false,true,true,false,false,false,true,true,false,true,false,false,true,true,false,true,false,false,false,false,true,false,false,false,false,false,true,false,false,true,false,false,true,false,false,false,false,true,false,false,false,true,true,true,false,true,false,true,true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,false,false,true,true,false,true,false,true,true,false,false,true,false,false,false,true,true,false,false,false,false,true,true,false,false,true,true,true,true,false,true,true,true,true,true,true,false,false,true,true,true,false,true,false,false,true,true,false,false,true,false,false,false,false,true,true,false,false,false,true,true,false,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,true,false,true,true,true,true,false,false,true,false,true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,true,true,true,false,true,true,true,false,false,false,true,false,true,true,true,true,true,false,false,true,false,true,true,true,false,true,true,false,true,true,true,false,false,true,true,true,false,false,true,true,true,true,false,true,true,false,false,true,false,true,false,false,true,false,true,false,false,true,true,false,false,true,true,true,true,true,true,false,false,true,false,true};
    uint256_from_bytes(a, a26_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a26_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a27_data[32]  = {0x59,0xb4,0x4e,0x92,0xef,0xfd,0xde,0xea,0xa8,0x42,0xbc,0x19,0x79,0x6f,0x74,0xad,0xfa,0xf5,0x54,0x96,0x98,0x8a,0xf3,0xfb,0xd3,0x96,0x30,0xd6,0x9c,0x90,0x11,0xef};
    bool         a27_bits[256] = {true,true,true,true,false,true,true,true,true,false,false,false,true,false,false,false,false,false,false,false,true,false,false,true,false,false,true,true,true,false,false,true,false,true,true,false,true,false,true,true,false,false,false,false,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,false,true,false,true,true,true,true,false,true,true,true,true,true,true,true,false,false,true,true,true,true,false,true,false,true,false,false,false,true,false,false,false,true,true,false,false,true,false,true,true,false,true,false,false,true,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,true,false,true,false,true,true,true,true,true,true,false,true,true,false,true,false,true,false,false,true,false,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,true,false,false,true,true,false,false,false,false,false,true,true,true,true,false,true,false,true,false,false,false,false,true,false,false,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,false,true,true,true,true,false,true,true,true,false,true,true,true,true,true,true,true,true,true,true,false,true,true,true,false,true,false,false,true,false,false,true,false,true,true,true,false,false,true,false,false,false,true,false,true,true,false,true,true,false,false,true,true,false,true,false};
    uint256_from_bytes(a, a27_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a27_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a28_data[32]  = {0xdf,0x2a,0x8b,0x79,0xfc,0x8e,0x80,0xb3,0x6f,0x0e,0x22,0x89,0x23,0xa5,0xef,0x88,0xef,0x02,0x09,0x0b,0xbf,0xde,0xfc,0x15,0x86,0xce,0x03,0xf9,0x1a,0x4f,0x44,0xf9};
    bool         a28_bits[256] = {true,false,false,true,true,true,true,true,false,false,true,false,false,false,true,false,true,true,true,true,false,false,true,false,false,true,false,true,true,false,false,false,true,false,false,true,true,true,true,true,true,true,false,false,false,false,false,false,false,true,true,true,false,false,true,true,false,true,true,false,false,false,false,true,true,false,true,false,true,false,false,false,false,false,true,true,true,true,true,true,false,true,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,true,false,true,false,false,false,false,true,false,false,true,false,false,false,false,false,true,false,false,false,false,false,false,true,true,true,true,false,true,true,true,false,false,false,true,false,false,false,true,true,true,true,true,false,true,true,true,true,false,true,false,false,true,false,true,true,true,false,false,false,true,false,false,true,false,false,true,false,false,false,true,false,true,false,false,false,true,false,false,false,true,true,true,false,false,false,false,true,true,true,true,false,true,true,false,true,true,false,false,true,true,false,true,false,false,false,false,false,false,false,true,false,true,true,true,false,false,false,true,false,false,true,true,true,true,true,true,true,false,false,true,true,true,true,false,true,true,false,true,false,false,false,true,false,true,false,true,false,true,false,false,true,true,true,true,true,false,true,true};
    uint256_from_bytes(a, a28_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a28_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a29_data[32]  = {0x80,0x4c,0x25,0xd6,0x4a,0xff,0xdc,0xd1,0x36,0x78,0xbc,0x8d,0x40,0x78,0x3f,0x0a,0x07,0x2a,0x98,0xd2,0x36,0x06,0xde,0xfc,0xdf,0xb8,0x5c,0x0d,0xd3,0x7e,0xe9,0x15};
    bool         a29_bits[256] = {true,false,true,false,true,false,false,false,true,false,false,true,false,true,true,true,false,true,true,true,true,true,true,false,true,true,false,false,true,false,true,true,true,false,true,true,false,false,false,false,false,false,true,true,true,false,true,false,false,false,false,true,true,true,false,true,true,true,true,true,true,false,true,true,false,false,true,true,true,true,true,true,false,true,true,true,true,false,true,true,false,true,true,false,false,false,false,false,false,true,true,false,true,true,false,false,false,true,false,false,true,false,true,true,false,false,false,true,true,false,false,true,false,true,false,true,false,true,false,false,true,true,true,false,false,false,false,false,false,true,false,true,false,false,false,false,true,true,true,true,true,true,false,false,false,false,false,true,true,true,true,false,false,false,false,false,false,false,true,false,true,false,true,true,false,false,false,true,false,false,true,true,true,true,false,true,false,false,false,true,true,true,true,false,false,true,true,false,true,true,false,false,true,false,false,false,true,false,true,true,false,false,true,true,true,false,true,true,true,true,true,true,true,true,true,true,false,true,false,true,false,false,true,false,false,true,true,false,true,false,true,true,true,false,true,false,false,true,false,false,false,false,true,true,false,false,true,false,false,false,false,false,false,false,false,true};
    uint256_from_bytes(a, a29_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a29_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a30_data[32]  = {0x21,0x8e,0x0b,0x7b,0xd5,0x8d,0xcd,0xb4,0x6b,0x44,0x68,0x06,0x8b,0x5a,0xb3,0xee,0x42,0x65,0xbb,0x31,0x53,0x74,0x09,0x02,0x96,0x20,0xbf,0x0d,0xc3,0x80,0x84,0xa0};
    bool         a30_bits[256] = {false,false,false,false,false,true,false,true,false,false,true,false,false,false,false,true,false,false,false,false,false,false,false,true,true,true,false,false,false,false,true,true,true,false,true,true,false,false,false,false,true,true,true,true,true,true,false,true,false,false,false,false,false,true,false,false,false,true,true,false,true,false,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,false,false,false,false,false,true,false,true,true,true,false,true,true,false,false,true,false,true,false,true,false,false,false,true,true,false,false,true,true,false,true,true,true,false,true,true,false,true,false,false,true,true,false,false,true,false,false,false,false,true,false,false,true,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,true,false,true,false,true,true,false,true,false,false,false,true,false,true,true,false,false,false,false,false,false,false,false,true,false,true,true,false,false,false,true,false,false,false,true,false,true,true,false,true,false,true,true,false,false,false,true,false,true,true,false,true,true,false,true,true,false,false,true,true,true,false,true,true,false,false,false,true,true,false,true,false,true,false,true,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,false,false,false,true,true,true,false,false,false,true,true,false,false,false,false,true,false,false};
    uint256_from_bytes(a, a30_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a30_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a31_data[32]  = {0x88,0x25,0xae,0x56,0x21,0x79,0xb3,0x7d,0x80,0x6c,0x10,0xb5,0xe0,0xcf,0xab,0x4c,0xea,0xef,0xc4,0xd2,0xd3,0xbf,0x6d,0x01,0x6b,0xae,0x4b,0x5b,0x84,0x4a,0x70,0x34};
    bool         a31_bits[256] = {false,false,true,false,true,true,false,false,false,false,false,false,true,true,true,false,false,true,false,true,false,false,true,false,false,false,true,false,false,false,false,true,true,true,false,true,true,false,true,false,true,true,false,true,false,false,true,false,false,true,true,true,false,true,false,true,true,true,false,true,false,true,true,false,true,false,false,false,false,false,false,false,true,false,true,true,false,true,true,false,true,true,true,true,true,true,false,true,true,true,false,false,true,false,true,true,false,true,false,false,true,false,true,true,false,false,true,false,false,false,true,true,true,true,true,true,false,true,true,true,false,true,false,true,false,true,true,true,false,false,true,true,false,false,true,false,true,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,false,false,false,false,false,true,true,true,true,false,true,false,true,true,false,true,false,false,false,false,true,false,false,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,false,true,true,false,false,true,true,false,true,true,false,false,true,true,true,true,false,true,false,false,false,false,true,false,false,false,true,true,false,true,false,true,false,false,true,true,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,false,true,false,false,false,true};
    uint256_from_bytes(a, a31_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a31_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a32_data[32]  = {0x9b,0xca,0x3c,0xb7,0x2e,0xe0,0x28,0x9d,0xc6,0xc9,0x1b,0x92,0x70,0xac,0x06,0xac,0xdf,0x70,0x30,0x17,0x04,0xc9,0xd7,0x8d,0x82,0xb3,0x35,0x99,0x86,0x04,0x87,0x19};
    bool         a32_bits[256] = {true,false,false,true,true,false,false,false,true,true,true,false,false,false,false,true,false,false,true,false,false,false,false,false,false,true,true,false,false,false,false,true,true,false,false,true,true,false,false,true,true,false,true,false,true,true,false,false,true,true,false,false,true,true,false,true,false,true,false,false,false,false,false,true,true,false,true,true,false,false,false,true,true,true,true,false,true,false,true,true,true,false,false,true,false,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,true,false,false,false,false,false,false,false,true,true,false,false,false,false,false,false,true,true,true,false,true,true,true,true,true,false,true,true,false,false,true,true,false,true,false,true,false,true,true,false,false,false,false,false,false,false,true,true,false,true,false,true,false,false,false,false,true,true,true,false,false,true,false,false,true,false,false,true,true,true,false,true,true,false,false,false,true,false,false,true,false,false,true,true,false,true,true,false,false,false,true,true,true,false,true,true,true,false,false,true,false,false,false,true,false,true,false,false,false,false,false,false,false,true,true,true,false,true,true,true,false,true,false,false,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,true};
    uint256_from_bytes(a, a32_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a32_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a33_data[32]  = {0xb9,0xa6,0x44,0x2e,0x9e,0x7d,0x6b,0x37,0x79,0x36,0xd5,0x36,0x24,0x3d,0x35,0x70,0x2c,0x1e,0xea,0x1f,0x26,0x59,0x74,0xa7,0xcc,0x96,0x6f,0x46,0xc6,0xaa,0x7d,0x55};
    bool         a33_bits[256] = {true,false,true,false,true,false,true,false,true,false,true,true,true,true,true,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,true,true,false,true,true,false,false,false,true,false,true,true,true,true,false,true,true,false,false,true,true,false,true,false,false,true,false,false,true,true,false,false,true,true,true,true,true,false,false,true,false,true,false,false,true,false,true,true,true,false,true,false,false,true,true,false,true,false,false,true,true,false,false,true,false,false,true,true,true,true,true,false,false,false,false,true,false,true,false,true,true,true,false,true,true,true,true,false,false,false,false,false,true,true,false,true,false,false,false,false,false,false,true,true,true,false,true,false,true,false,true,true,false,false,true,false,true,true,true,true,false,false,false,false,true,false,false,true,false,false,false,true,true,false,true,true,false,false,true,false,true,false,true,false,true,true,false,true,true,false,true,true,false,false,true,false,false,true,true,true,true,false,true,true,true,false,true,true,false,false,true,true,false,true,false,true,true,false,true,false,true,true,true,true,true,false,false,true,true,true,true,false,false,true,false,true,true,true,false,true,false,false,false,false,true,false,false,false,true,false,false,true,true,false,false,true,false,true,true,false,false,true,true,true,false,true};
    uint256_from_bytes(a, a33_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a33_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a34_data[32]  = {0x46,0xe4,0x09,0x90,0x30,0xf9,0x70,0x58,0x3f,0x9d,0x52,0xf9,0x0e,0x8b,0xec,0x94,0x8f,0x6f,0x91,0x5f,0xe2,0x1b,0x37,0xca,0x1b,0x29,0xfc,0x99,0xc6,0xc8,0x0e,0x2b};
    bool         a34_bits[256] = {true,true,false,true,false,true,false,false,false,true,true,true,false,false,false,false,false,false,false,true,false,false,true,true,false,true,true,false,false,false,true,true,true,false,false,true,true,false,false,true,false,false,true,true,true,true,true,true,true,false,false,true,false,true,false,false,true,true,false,true,true,false,false,false,false,true,false,true,false,false,true,true,true,true,true,false,true,true,false,false,true,true,false,true,true,false,false,false,false,true,false,false,false,true,true,true,true,true,true,true,true,false,true,false,true,false,false,false,true,false,false,true,true,true,true,true,false,true,true,false,true,true,true,true,false,false,false,true,false,false,true,false,true,false,false,true,false,false,true,true,false,true,true,true,true,true,false,true,false,false,false,true,false,true,true,true,false,false,false,false,true,false,false,true,true,true,true,true,false,true,false,false,true,false,true,false,true,false,true,true,true,false,false,true,true,true,true,true,true,true,false,false,false,false,false,true,true,false,true,false,false,false,false,false,true,true,true,false,true,false,false,true,true,true,true,true,false,false,false,false,true,true,false,false,false,false,false,false,true,false,false,true,true,false,false,true,false,false,false,false,false,false,true,false,false,true,true,true,false,true,true,false,false,false,true,false};
    uint256_from_bytes(a, a34_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a34_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a35_data[32]  = {0x83,0x1d,0x03,0xbf,0x9b,0x2b,0xd6,0xc0,0x81,0x6b,0xee,0x06,0xf9,0x2e,0x23,0x39,0x9c,0xce,0xa0,0x98,0x53,0x5b,0x6a,0x43,0x71,0x78,0xba,0x0a,0x10,0x38,0xf0,0xb5};
    bool         a35_bits[256] = {true,false,true,false,true,true,false,true,false,false,false,false,true,true,true,true,false,false,false,true,true,true,false,false,false,false,false,false,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,false,true,false,false,false,true,true,true,false,true,true,false,false,false,false,true,false,false,true,false,true,false,true,true,false,true,true,false,true,true,false,true,false,true,true,false,false,true,false,true,false,false,false,false,true,true,false,false,true,false,false,false,false,false,true,false,true,false,true,true,true,false,false,true,true,false,false,true,true,true,false,false,true,true,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,false,true,true,true,false,true,false,false,true,false,false,true,true,true,true,true,false,true,true,false,false,false,false,false,false,true,true,true,false,true,true,true,true,true,false,true,false,true,true,false,true,false,false,false,false,false,false,true,false,false,false,false,false,false,true,true,false,true,true,false,true,false,true,true,true,true,false,true,false,true,false,false,true,true,false,true,true,false,false,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,false,false,true,false,true,true,true,false,false,false,true,true,false,false,false,false,false,true};
    uint256_from_bytes(a, a35_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a35_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a36_data[32]  = {0x6a,0xa8,0xb9,0xe0,0x23,0x1b,0x3e,0x14,0x72,0x91,0x35,0xbd,0xd7,0x0a,0x39,0xd1,0x33,0xdc,0xd7,0x7f,0xf1,0x79,0xf2,0xd2,0xe4,0x8b,0x96,0x62,0x8f,0x3c,0x4b,0xe3};
    bool         a36_bits[256] = {true,true,false,false,false,true,true,true,true,true,false,true,false,false,true,false,false,false,true,true,true,true,false,false,true,true,true,true,false,false,false,true,false,true,false,false,false,true,true,false,false,true,true,false,true,false,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,true,true,true,false,true,false,false,true,false,true,true,false,true,false,false,true,true,true,true,true,false,false,true,true,true,true,false,true,false,false,false,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,false,true,false,true,true,false,false,true,true,true,false,true,true,true,true,false,false,true,true,false,false,true,false,false,false,true,false,true,true,true,false,false,true,true,true,false,false,false,true,false,true,false,false,false,false,true,true,true,false,true,false,true,true,true,false,true,true,true,true,false,true,true,false,true,false,true,true,false,false,true,false,false,false,true,false,false,true,false,true,false,false,true,true,true,false,false,false,true,false,true,false,false,false,false,true,true,true,true,true,false,false,true,true,false,true,true,false,false,false,true,true,false,false,false,true,false,false,false,false,false,false,false,true,true,true,true,false,false,true,true,true,false,true,false,false,false,true,false,true,false,true,false,true,false,true,false,true,true,false};
    uint256_from_bytes(a, a36_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a36_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a37_data[32]  = {0x12,0xb8,0x0a,0xed,0x6d,0xa7,0x9a,0x87,0x3d,0x9a,0x80,0x79,0xab,0xd0,0xd7,0xfb,0x12,0x92,0x61,0x85,0x50,0xe4,0x0d,0x54,0x71,0x2e,0xa6,0xb3,0x64,0x71,0xfd,0xe4};
    bool         a37_bits[256] = {false,false,true,false,false,true,true,true,true,false,true,true,true,true,true,true,true,false,false,false,true,true,true,false,false,false,true,false,false,true,true,false,true,true,false,false,true,true,false,true,false,true,true,false,false,true,false,true,false,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,false,false,false,true,false,false,true,true,true,false,false,false,false,true,false,true,false,true,false,true,false,false,false,false,true,true,false,false,false,false,true,true,false,false,true,false,false,true,false,false,true,false,true,false,false,true,false,false,false,true,true,false,true,true,true,true,true,true,true,true,false,true,false,true,true,false,false,false,false,true,false,true,true,true,true,false,true,false,true,false,true,true,false,false,true,true,true,true,false,false,false,false,false,false,false,false,true,false,true,false,true,true,false,false,true,true,false,true,true,true,true,false,false,true,true,true,false,false,false,false,true,false,true,false,true,true,false,false,true,true,true,true,false,false,true,false,true,true,false,true,true,false,true,true,false,true,false,true,true,false,true,true,true,false,true,false,true,false,false,false,false,false,false,false,true,true,true,false,true,false,true,false,false,true,false,false,false};
    uint256_from_bytes(a, a37_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a37_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a38_data[32]  = {0xf7,0xb1,0x03,0xdf,0x23,0x23,0x1e,0x1e,0xe2,0x01,0x55,0x22,0x40,0xcb,0xac,0xd0,0x24,0x9a,0x45,0x84,0x5d,0xbe,0x30,0x23,0xa9,0x06,0x92,0x2f,0xa4,0xb9,0xa9,0xc4};
    bool         a38_bits[256] = {false,false,true,false,false,false,true,true,true,false,false,true,false,true,false,true,true,false,false,true,true,true,false,true,false,false,true,false,false,true,false,true,true,true,true,true,false,true,false,false,false,true,false,false,true,false,false,true,false,true,true,false,false,false,false,false,true,false,false,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,false,false,true,true,false,false,false,true,true,true,true,true,false,true,true,false,true,true,true,false,true,false,false,false,true,false,false,false,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,false,false,true,false,false,true,false,false,true,false,false,false,false,false,false,true,false,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,false,true,true,false,false,false,false,false,false,true,false,false,true,false,false,false,true,false,false,true,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,true,true,true,true,false,false,false,false,true,true,true,true,false,false,false,true,true,false,false,false,true,false,false,true,true,false,false,false,true,false,false,true,true,true,true,true,false,true,true,true,true,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,true,true,false,true,true,true,true};
    uint256_from_bytes(a, a38_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a38_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a39_data[32]  = {0x83,0xfe,0xb1,0x7b,0xfe,0x7b,0x8a,0xe4,0x6e,0x78,0x36,0xa4,0xb4,0xd1,0x9e,0xc1,0x29,0x55,0xd6,0xf0,0x39,0x45,0x33,0x6b,0xd5,0x1b,0x18,0x15,0xaa,0xf7,0x19,0xf3};
    bool         a39_bits[256] = {true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,true,true,false,true,true,true,true,false,true,false,true,false,true,false,true,true,false,true,false,true,false,false,false,false,false,false,true,true,false,false,false,true,true,false,true,true,false,false,false,true,false,true,false,true,false,true,true,true,true,false,true,false,true,true,false,true,true,false,false,true,true,false,false,true,false,true,false,false,false,true,false,true,false,false,true,true,true,false,false,false,false,false,false,true,true,true,true,false,true,true,false,true,false,true,true,true,false,true,false,true,false,true,false,true,false,false,true,false,true,false,false,true,false,false,false,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,false,true,false,true,true,false,false,true,false,true,true,false,true,false,false,true,false,false,true,false,true,false,true,true,false,true,true,false,false,false,false,false,true,true,true,true,false,false,true,true,true,false,true,true,false,false,false,true,false,false,true,true,true,false,true,false,true,false,false,false,true,true,true,false,true,true,true,true,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,false,true,false,false,false,true,true,false,true,false,true,true,true,true,true,true,true,true,true,false,false,false,false,false,true};
    uint256_from_bytes(a, a39_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a39_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a40_data[32]  = {0x5d,0xaf,0x10,0x6d,0xb8,0xde,0xe0,0x81,0x17,0x9a,0x07,0x1e,0x51,0x8a,0xe4,0x52,0x5b,0x4b,0x1b,0x75,0x32,0x1c,0x52,0x96,0x6b,0xd8,0xc6,0x76,0x56,0xd0,0x50,0xcd};
    bool         a40_bits[256] = {true,false,true,true,false,false,true,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,true,true,false,true,true,false,true,false,true,false,false,true,true,false,true,true,true,false,false,true,true,false,false,false,true,true,false,false,false,true,true,false,true,true,true,true,false,true,false,true,true,false,false,true,true,false,true,false,false,true,false,true,false,false,true,false,true,false,false,false,true,true,true,false,false,false,false,true,false,false,true,true,false,false,true,false,true,false,true,true,true,false,true,true,false,true,true,false,false,false,true,true,false,true,false,false,true,false,true,true,false,true,true,false,true,false,false,true,false,false,true,false,true,false,false,false,true,false,false,true,true,true,false,true,false,true,false,false,false,true,true,false,false,false,true,false,true,false,false,true,true,true,true,false,false,false,true,true,true,false,false,false,false,false,false,true,false,true,true,false,false,true,true,true,true,false,true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,false,false,true,true,true,false,true,true,true,true,false,true,true,false,false,false,true,true,true,false,true,true,false,true,true,false,true,true,false,false,false,false,false,true,false,false,false,true,true,true,true,false,true,false,true,true,false,true,true,true,false,true,false};
    uint256_from_bytes(a, a40_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a40_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a41_data[32]  = {0xa2,0x6a,0xa0,0xae,0x04,0x4f,0x15,0x74,0xf0,0x37,0xaf,0xc6,0x44,0xd8,0x2a,0x53,0x12,0x89,0xba,0xfa,0xe5,0x31,0x69,0x60,0x6c,0xe1,0x93,0xc2,0x2e,0xef,0xa2,0x79};
    bool         a41_bits[256] = {true,false,false,true,true,true,true,false,false,true,false,false,false,true,false,true,true,true,true,true,false,true,true,true,false,true,true,true,false,true,false,false,false,true,false,false,false,false,true,true,true,true,false,false,true,false,false,true,true,false,false,false,false,true,true,true,false,false,true,true,false,true,true,false,false,false,false,false,false,true,true,false,true,false,false,true,false,true,true,false,true,false,false,false,true,true,false,false,true,false,true,false,false,true,true,true,false,true,false,true,true,true,true,true,false,true,false,true,true,true,false,true,true,false,false,true,false,false,false,true,false,true,false,false,true,false,false,false,true,true,false,false,true,false,true,false,false,true,false,true,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,false,true,true,true,true,true,true,false,true,false,true,true,true,true,false,true,true,false,false,false,false,false,false,true,true,true,true,false,false,true,false,true,true,true,false,true,false,true,false,true,false,false,false,true,true,true,true,false,false,true,false,false,false,true,false,false,false,false,false,false,true,true,true,false,true,false,true,false,false,false,false,false,true,false,true,false,true,false,true,false,true,true,false,false,true,false,false,false,true,false,true};
    uint256_from_bytes(a, a41_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a41_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a42_data[32]  = {0xf0,0x29,0x05,0x31,0x3d,0x0a,0x27,0x0b,0xb5,0xa4,0x32,0xcf,0x86,0xe3,0xe7,0x26,0x0b,0x0f,0x87,0x3b,0x21,0x14,0xe0,0x68,0x9f,0x27,0xf5,0x2c,0x44,0x92,0x74,0xd2};
    bool         a42_bits[256] = {false,true,false,false,true,false,true,true,false,false,true,false,true,true,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,false,true,false,false,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true,true,true,true,false,false,true,false,false,true,true,true,true,true,false,false,true,false,false,false,true,false,true,true,false,false,false,false,false,false,true,true,true,false,false,true,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,false,true,true,true,false,false,true,true,true,false,false,false,false,true,true,true,true,true,false,false,false,false,true,true,false,true,false,false,false,false,false,true,true,false,false,true,false,false,true,true,true,false,false,true,true,true,true,true,false,false,false,true,true,true,false,true,true,false,false,false,false,true,true,true,true,true,false,false,true,true,false,true,false,false,true,true,false,false,false,false,true,false,false,true,false,true,true,false,true,false,true,true,false,true,true,true,false,true,false,false,false,false,true,true,true,false,false,true,false,false,false,true,false,true,false,false,false,false,true,false,true,true,true,true,false,false,true,false,false,false,true,true,false,false,true,false,true,false,false,false,false,false,true,false,false,true,false,true,false,false,false,false,false,false,true,true,true,true};
    uint256_from_bytes(a, a42_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a42_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a43_data[32]  = {0xac,0x12,0x7e,0x93,0x80,0x05,0xce,0x74,0x72,0x18,0x88,0xff,0x4a,0x3a,0xdf,0x99,0x34,0xb3,0xff,0x60,0xc2,0x6e,0x7a,0x42,0x87,0xf5,0x3d,0xdd,0x4e,0x14,0xd5,0x71};
    bool         a43_bits[256] = {true,false,false,false,true,true,true,false,true,false,true,false,true,false,true,true,false,false,true,false,true,false,false,false,false,true,true,true,false,false,true,false,true,false,true,true,true,false,true,true,true,false,true,true,true,true,false,false,true,false,true,false,true,true,true,true,true,true,true,false,false,false,false,true,false,true,false,false,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,false,false,false,false,true,true,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,false,false,true,true,false,true,false,false,true,false,true,true,false,false,true,false,false,true,true,false,false,true,true,true,true,true,true,false,true,true,false,true,false,true,true,true,false,false,false,true,false,true,false,false,true,false,true,true,true,true,true,true,true,true,false,false,false,true,false,false,false,true,false,false,false,true,true,false,false,false,false,true,false,false,true,true,true,false,false,false,true,false,true,true,true,false,false,true,true,true,false,false,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,true,false,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,false,false,false,false,false,true,true,false,true,false,true};
    uint256_from_bytes(a, a43_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a43_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a44_data[32]  = {0x03,0xed,0xb9,0x20,0x09,0x75,0x83,0x40,0x40,0x1d,0x68,0xfb,0xfe,0x97,0x7c,0x56,0x04,0xa6,0x56,0x51,0xcd,0xbd,0xe7,0x47,0x58,0xd5,0x0f,0x1b,0x45,0x40,0xf4,0x26};
    bool         a44_bits[256] = {false,true,true,false,false,true,false,false,false,false,true,false,true,true,true,true,false,false,false,false,false,false,true,false,true,false,true,false,false,false,true,false,true,true,false,true,true,false,false,false,true,true,true,true,false,false,false,false,true,false,true,false,true,false,true,true,false,false,false,true,true,false,true,false,true,true,true,false,false,false,true,false,true,true,true,false,false,true,true,true,true,false,true,true,true,true,false,true,true,false,true,true,false,false,true,true,true,false,false,false,true,false,true,false,false,true,true,false,true,false,true,false,false,true,true,false,false,true,false,true,false,false,true,false,false,false,false,false,false,true,true,false,true,false,true,false,false,false,true,true,true,true,true,false,true,true,true,false,true,false,false,true,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,false,false,false,true,false,true,true,false,true,false,true,true,true,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true,false,true,true,false,false,false,false,false,true,true,false,true,false,true,true,true,false,true,false,false,true,false,false,false,false,false,false,false,false,false,true,false,false,true,false,false,true,true,true,false,true,true,false,true,true,false,true,true,true,true,true,false,false,false,false,false,false};
    uint256_from_bytes(a, a44_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a44_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a45_data[32]  = {0xa2,0xcf,0x62,0xba,0xba,0x95,0x88,0x10,0xb4,0xeb,0xf4,0xb6,0xe1,0xc6,0x0a,0xa3,0xd5,0x10,0xbb,0x04,0x32,0xd9,0x0d,0xcd,0x57,0xbb,0x7d,0x97,0x3a,0xc4,0xda,0x9a};
    bool         a45_bits[256] = {false,true,false,true,true,false,false,true,false,true,false,true,true,false,true,true,false,false,true,false,false,false,true,true,false,true,false,true,true,true,false,false,true,true,true,false,true,false,false,true,true,false,true,true,true,true,true,false,true,true,false,true,true,true,false,true,true,true,true,false,true,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,false,false,false,false,true,false,false,true,true,false,true,true,false,true,false,false,true,true,false,false,false,false,true,false,false,false,false,false,true,true,false,true,true,true,false,true,false,false,false,false,true,false,false,false,true,false,true,false,true,false,true,true,true,true,false,false,false,true,false,true,false,true,false,true,false,false,false,false,false,true,true,false,false,false,true,true,true,false,false,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,true,false,true,true,true,true,true,true,false,true,false,true,true,true,false,false,true,false,true,true,false,true,false,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true,true,false,true,false,true,false,false,true,false,true,false,true,true,true,false,true,false,true,false,true,true,true,false,true,false,true,false,false,false,true,true,false,true,true,true,true,false,false,true,true,false,true,false,false,false,true,false,true};
    uint256_from_bytes(a, a45_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a45_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a46_data[32]  = {0x03,0xa6,0x39,0x66,0x21,0x3b,0xca,0x7f,0xd6,0x44,0xde,0x2f,0x0d,0xec,0x68,0x23,0xfb,0x5c,0x9d,0x56,0x58,0xf9,0x2d,0xea,0xfd,0x4b,0xd0,0x30,0x67,0x9a,0x44,0xdd};
    bool         a46_bits[256] = {true,false,true,true,true,false,true,true,false,false,true,false,false,false,true,false,false,true,false,true,true,false,false,true,true,true,true,false,false,true,true,false,false,false,false,false,true,true,false,false,false,false,false,false,true,false,true,true,true,true,false,true,false,false,true,false,true,false,true,true,true,true,true,true,false,true,false,true,false,true,true,true,true,false,true,true,false,true,false,false,true,false,false,true,true,true,true,true,false,false,false,true,true,false,true,false,false,true,true,false,true,false,true,false,true,false,true,true,true,false,false,true,false,false,true,true,true,false,true,false,true,true,false,true,true,true,true,true,true,true,false,false,false,true,false,false,false,false,false,true,false,true,true,false,false,false,true,true,false,true,true,true,true,false,true,true,false,false,false,false,true,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,false,true,false,false,false,true,false,false,true,true,false,true,false,true,true,true,true,true,true,true,true,true,false,false,true,false,true,false,false,true,true,true,true,false,true,true,true,false,false,true,false,false,false,false,true,false,false,false,true,true,false,false,true,true,false,true,false,false,true,true,true,false,false,false,true,true,false,false,true,false,true,true,true,false,false,false,false,false,false};
    uint256_from_bytes(a, a46_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a46_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a47_data[32]  = {0x99,0x49,0x8a,0xc4,0x48,0x2c,0xc7,0x8e,0xf8,0x8e,0xde,0x10,0xab,0xa8,0xb9,0xb3,0x81,0x85,0x79,0x7c,0xde,0xdb,0x91,0x09,0x61,0x81,0x77,0xff,0xd7,0x5d,0x67,0x69};
    bool         a47_bits[256] = {true,false,false,true,false,true,true,false,true,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,false,true,false,false,false,false,false,false,true,true,false,false,false,false,true,true,false,true,false,false,true,false,false,false,false,true,false,false,false,true,false,false,true,true,true,false,true,true,false,true,true,false,true,true,true,true,false,true,true,false,false,true,true,true,true,true,false,true,false,false,true,true,true,true,false,true,false,true,false,false,false,false,true,true,false,false,false,false,false,false,true,true,true,false,false,true,true,false,true,true,false,false,true,true,true,false,true,false,false,false,true,false,true,false,true,true,true,false,true,false,true,false,true,false,false,false,false,true,false,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,false,false,true,false,false,false,true,true,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,false,false,true,true,false,false,true,true,false,true,false,false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true,true,false,true,false,true,false,false,false,true,true,false,false,true,false,false,true,false,true,false,false,true,true,false,false,true};
    uint256_from_bytes(a, a47_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a47_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a48_data[32]  = {0x72,0x21,0x8f,0xdc,0x44,0xdf,0x96,0xff,0x28,0x54,0x14,0x24,0x2f,0x73,0x3b,0x05,0x75,0x9e,0xb5,0x59,0x0b,0x94,0xaf,0x3a,0x4b,0x05,0xe1,0xae,0xb1,0x53,0xd6,0x9c};
    bool         a48_bits[256] = {false,false,true,true,true,false,false,true,false,true,true,false,true,false,true,true,true,true,false,false,true,false,true,false,true,false,false,false,true,true,false,true,false,true,true,true,false,true,false,true,true,false,false,false,false,true,true,true,true,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,false,true,false,true,true,true,false,false,true,true,true,true,false,true,false,true,false,false,true,false,true,false,false,true,true,true,false,true,false,false,false,false,true,false,false,true,true,false,true,false,true,false,true,false,true,true,false,true,false,true,true,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,true,false,false,false,false,false,true,true,false,true,true,true,false,false,true,true,false,false,true,true,true,false,true,true,true,true,false,true,false,false,false,false,true,false,false,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,true,false,true,false,false,false,false,true,false,true,false,false,true,true,true,true,true,true,true,true,false,true,true,false,true,false,false,true,true,true,true,true,true,false,true,true,false,false,true,false,false,false,true,false,false,false,true,true,true,false,true,true,true,true,true,true,false,false,false,true,true,false,false,false,false,true,false,false,false,true,false,false,true,true,true,false};
    uint256_from_bytes(a, a48_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a48_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a49_data[32]  = {0x52,0xd3,0x1e,0x1b,0x8c,0x0d,0x00,0x33,0xfc,0x23,0x25,0xa9,0xf8,0xfd,0xd2,0x08,0x54,0x34,0x81,0x56,0xf6,0x37,0xa4,0x68,0x5d,0x38,0x5e,0x06,0x43,0x63,0xe5,0xd9};
    bool         a49_bits[256] = {true,false,false,true,true,false,true,true,true,false,true,false,false,true,true,true,true,true,false,false,false,true,true,false,true,true,false,false,false,false,true,false,false,true,true,false,false,false,false,false,false,true,true,true,true,false,true,false,false,false,false,true,true,true,false,false,true,false,true,true,true,false,true,false,false,false,false,true,false,true,true,false,false,false,true,false,false,true,false,true,true,true,true,false,true,true,false,false,false,true,true,false,true,true,true,true,false,true,true,false,true,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,true,true,false,false,false,false,true,false,true,false,true,false,false,false,false,true,false,false,false,false,false,true,false,false,true,false,true,true,true,false,true,true,true,true,true,true,false,false,false,true,true,true,true,true,true,false,false,true,false,true,false,true,true,false,true,false,false,true,false,false,true,true,false,false,false,true,false,false,false,false,true,true,true,true,true,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false,false,false,true,false,true,true,false,false,false,false,false,false,true,true,false,false,false,true,true,true,false,true,true,false,false,false,false,true,true,true,true,false,false,false,true,true,false,false,true,false,true,true,false,true,false,false,true,false,true,false};
    uint256_from_bytes(a, a49_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a49_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a50_data[32]  = {0x00,0x46,0x0d,0x69,0x2e,0xd6,0x54,0x11,0x5b,0x49,0x15,0x61,0x37,0xc6,0x0e,0x98,0x4f,0x3e,0x88,0x5e,0xe1,0xe4,0x37,0xb7,0xf7,0x35,0xef,0xe6,0x08,0xd1,0x80,0x11};
    bool         a50_bits[256] = {true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,true,false,true,true,false,false,false,true,false,false,false,false,false,true,true,false,false,true,true,true,true,true,true,true,false,true,true,true,true,false,true,false,true,true,false,false,true,true,true,false,true,true,true,true,true,true,true,false,true,true,false,true,true,true,true,false,true,true,false,false,false,false,true,false,false,true,true,true,true,false,false,false,false,true,true,true,false,true,true,true,true,false,true,false,false,false,false,true,false,false,false,true,false,true,true,true,true,true,false,false,true,true,true,true,false,false,true,false,false,false,false,true,true,false,false,true,false,true,true,true,false,false,false,false,false,true,true,false,false,false,true,true,true,true,true,false,true,true,false,false,true,false,false,false,false,true,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,false,true,false,true,true,false,true,true,false,true,false,true,false,false,false,true,false,false,false,false,false,true,false,true,false,true,false,false,true,true,false,true,false,true,true,false,true,true,true,false,true,false,false,true,false,false,true,false,true,true,false,true,false,true,true,false,false,false,false,false,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false};
    uint256_from_bytes(a, a50_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a50_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a51_data[32]  = {0x7e,0x83,0x49,0x04,0xfc,0x17,0x34,0x98,0xb8,0x7e,0x4e,0x2b,0x53,0x7d,0x91,0x28,0xc3,0xa9,0xe8,0x89,0x63,0xb7,0x59,0xf5,0x98,0xb8,0x1c,0x66,0xe1,0x0c,0x16,0x7d};
    bool         a51_bits[256] = {true,false,true,true,true,true,true,false,false,true,true,false,true,false,false,false,false,false,true,true,false,false,false,false,true,false,false,false,false,true,true,true,false,true,true,false,false,true,true,false,false,false,true,true,true,false,false,false,false,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,true,false,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,true,true,false,true,true,false,true,true,true,false,false,false,true,true,false,true,false,false,true,false,false,false,true,false,false,false,true,false,true,true,true,true,false,false,true,false,true,false,true,true,true,false,false,false,false,true,true,false,false,false,true,false,true,false,false,true,false,false,false,true,false,false,true,true,false,true,true,true,true,true,false,true,true,false,false,true,false,true,false,true,true,false,true,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,true,true,true,true,false,false,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,false,true,false,true,true,false,false,true,true,true,false,true,false,false,false,false,false,true,true,true,true,true,true,false,false,true,false,false,false,false,false,true,false,false,true,false,false,true,false,true,true,false,false,false,false,false,true,false,true,true,true,true,true,true,false};
    uint256_from_bytes(a, a51_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a51_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a52_data[32]  = {0x81,0x6b,0x23,0x32,0xcf,0xed,0x94,0x3b,0xb3,0x78,0x3a,0x7c,0xbb,0xdd,0xbb,0x9b,0x6d,0xe2,0xfb,0x1f,0xa0,0x98,0xd6,0x91,0x83,0x52,0xbc,0x85,0xe4,0x56,0x55,0x9c};
    bool         a52_bits[256] = {false,false,true,true,true,false,false,true,true,false,true,false,true,false,true,false,false,true,true,false,true,false,true,false,false,false,true,false,false,true,true,true,true,false,true,false,false,false,false,true,false,false,true,true,true,true,false,true,false,true,false,false,true,false,true,false,true,true,false,false,false,false,false,true,true,false,false,false,true,false,false,true,false,true,true,false,true,false,true,true,false,false,false,true,true,false,false,true,false,false,false,false,false,true,false,true,true,true,true,true,true,false,false,false,true,true,false,true,true,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,false,true,true,true,false,true,true,true,false,true,true,false,true,true,true,false,true,true,true,true,false,true,true,true,false,true,false,false,true,true,true,true,true,false,false,true,false,true,true,true,false,false,false,false,false,true,true,true,true,false,true,true,false,false,true,true,false,true,true,true,false,true,true,true,false,false,false,false,true,false,true,false,false,true,true,false,true,true,false,true,true,true,true,true,true,true,false,false,true,true,false,true,false,false,true,true,false,false,true,true,false,false,false,true,false,false,true,true,false,true,false,true,true,false,true,false,false,false,false,false,false,true};
    uint256_from_bytes(a, a52_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a52_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a53_data[32]  = {0xcd,0xff,0x5a,0x1c,0xd0,0x1a,0x91,0x4c,0xd5,0xbe,0x78,0x5a,0x91,0x87,0xdf,0x42,0x81,0x1e,0x76,0x16,0xc0,0xbb,0xe6,0xed,0x86,0x14,0xf5,0x04,0xe8,0xee,0x65,0xa1};
    bool         a53_bits[256] = {true,false,false,false,false,true,false,true,true,false,true,false,false,true,true,false,false,true,true,true,false,true,true,true,false,false,false,true,false,true,true,true,false,false,true,false,false,false,false,false,true,false,true,false,true,true,true,true,false,false,true,false,true,false,false,false,false,true,true,false,false,false,false,true,true,false,true,true,false,true,true,true,false,true,true,false,false,true,true,true,true,true,false,true,true,true,false,true,false,false,false,false,false,false,true,true,false,true,true,false,true,false,false,false,false,true,true,false,true,true,true,false,false,true,true,true,true,false,false,false,true,false,false,false,false,false,false,true,false,true,false,false,false,false,true,false,true,true,true,true,true,false,true,true,true,true,true,false,false,false,false,true,true,false,false,false,true,false,false,true,false,true,false,true,true,false,true,false,false,false,false,true,true,true,true,false,false,true,true,true,true,true,false,true,true,false,true,false,true,false,true,true,false,false,true,true,false,false,true,false,true,false,false,false,true,false,false,true,false,true,false,true,true,false,false,false,false,false,false,false,true,false,true,true,false,false,true,true,true,false,false,false,false,true,false,true,true,false,true,false,true,true,true,true,true,true,true,true,true,false,true,true,false,false,true,true};
    uint256_from_bytes(a, a53_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a53_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a54_data[32]  = {0xcc,0x35,0xe8,0x34,0x74,0xfa,0x94,0x12,0x00,0xd9,0x35,0x34,0x43,0x87,0xee,0x7b,0x7d,0x42,0x64,0x6f,0x3e,0x9b,0x76,0x8f,0xae,0x40,0x01,0xe3,0x88,0x0c,0xb4,0x01};
    bool         a54_bits[256] = {true,false,false,false,false,false,false,false,false,false,true,false,true,true,false,true,false,false,true,true,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,false,true,false,true,true,true,true,true,false,false,false,true,false,true,true,false,true,true,true,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,false,false,true,true,true,true,false,true,true,false,false,false,true,false,false,true,true,false,false,true,false,false,false,false,true,false,true,false,true,true,true,true,true,false,true,true,false,true,true,true,true,false,false,true,true,true,false,true,true,true,true,true,true,false,false,false,false,true,true,true,false,false,false,false,true,false,false,false,true,false,true,true,false,false,true,false,true,false,true,true,false,false,true,false,false,true,true,false,true,true,false,false,false,false,false,false,false,false,false,true,false,false,true,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,true,true,true,true,false,false,true,false,true,true,true,false,false,false,true,false,true,true,false,false,false,false,false,true,false,true,true,true,true,false,true,false,true,true,false,false,false,false,true,true,false,false,true,true};
    uint256_from_bytes(a, a54_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a54_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a55_data[32]  = {0x86,0xa7,0x4a,0x63,0xa8,0xc7,0xd9,0xe0,0x17,0x89,0x81,0x9f,0x89,0x02,0xda,0xfc,0xe5,0xd9,0xfe,0x81,0x80,0xc2,0xb5,0xf1,0xee,0xb8,0x9f,0xf1,0xbf,0x8e,0x51,0xaa};
    bool         a55_bits[256] = {false,true,false,true,false,true,false,true,true,false,false,false,true,false,true,false,false,true,true,true,false,false,false,true,true,true,true,true,true,true,false,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,false,true,false,false,false,true,true,true,false,true,false,true,true,true,false,true,true,true,true,false,false,false,true,true,true,true,true,false,true,false,true,true,false,true,false,true,false,false,false,false,true,true,false,false,false,false,false,false,false,true,true,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,false,false,true,true,false,true,true,true,false,true,false,false,true,true,true,false,false,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,true,false,false,false,false,false,false,true,false,false,true,false,false,false,true,true,true,true,true,true,false,false,true,true,false,false,false,false,false,false,true,true,false,false,true,false,false,false,true,true,true,true,false,true,false,false,false,false,false,false,false,false,true,true,true,true,false,false,true,true,false,true,true,true,true,true,false,false,false,true,true,false,false,false,true,false,true,false,true,true,true,false,false,false,true,true,false,false,true,false,true,false,false,true,false,true,true,true,false,false,true,false,true,false,true,true,false,false,false,false,true};
    uint256_from_bytes(a, a55_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a55_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a56_data[32]  = {0x43,0xfb,0x9f,0xbc,0xd8,0x9c,0x36,0xb2,0x13,0x0f,0x27,0xb2,0xcf,0x28,0xf6,0x5e,0x40,0x8f,0xc1,0x46,0x79,0x4e,0xc9,0x26,0xbc,0x9e,0x28,0xea,0xbe,0xe8,0x06,0x26};
    bool         a56_bits[256] = {false,true,true,false,false,true,false,false,false,true,true,false,false,false,false,false,false,false,false,true,false,true,true,true,false,true,true,true,true,true,false,true,false,true,false,true,false,true,true,true,false,false,false,true,false,true,false,false,false,true,true,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,true,false,false,true,false,false,true,false,false,true,false,false,true,true,false,true,true,true,false,false,true,false,true,false,false,true,true,true,true,false,false,true,true,false,false,false,true,false,true,false,false,false,false,false,true,true,true,true,true,true,false,false,false,true,false,false,false,false,false,false,true,false,false,true,true,true,true,false,true,false,false,true,true,false,true,true,true,true,false,false,false,true,false,true,false,false,true,true,true,true,false,false,true,true,false,true,false,false,true,true,false,true,true,true,true,false,false,true,false,false,true,true,true,true,false,false,false,false,true,true,false,false,true,false,false,false,false,true,false,false,true,true,false,true,false,true,true,false,true,true,false,false,false,false,true,true,true,false,false,true,false,false,false,true,true,false,true,true,false,false,true,true,true,true,false,true,true,true,true,true,true,false,false,true,true,true,false,true,true,true,true,true,true,true,false,false,false,false,true,false};
    uint256_from_bytes(a, a56_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a56_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a57_data[32]  = {0x75,0xd8,0xd8,0xa4,0xf9,0xc9,0xc6,0x79,0xa6,0x61,0xf6,0x2c,0xbd,0x65,0x68,0x0c,0x3b,0x11,0x85,0xd9,0x34,0x89,0x22,0xd7,0xc1,0xa6,0x24,0xdc,0xba,0xb5,0xb3,0x73};
    bool         a57_bits[256] = {true,true,false,false,true,true,true,false,true,true,false,false,true,true,false,true,true,false,true,false,true,true,false,true,false,true,false,true,true,true,false,true,false,false,true,true,true,false,true,true,false,false,true,false,false,true,false,false,false,true,true,false,false,true,false,true,true,false,false,false,false,false,true,true,true,true,true,false,true,false,true,true,false,true,false,false,false,true,false,false,true,false,false,true,false,false,false,true,false,false,true,false,true,true,false,false,true,false,false,true,true,false,true,true,true,false,true,false,false,false,false,true,true,false,false,false,true,false,false,false,true,true,false,true,true,true,false,false,false,false,true,true,false,false,false,false,false,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,true,false,true,true,true,true,false,true,false,false,true,true,false,true,false,false,false,true,true,false,true,true,true,true,true,false,false,false,false,true,true,false,false,true,true,false,false,true,false,true,true,false,false,true,true,true,true,false,false,true,true,false,false,false,true,true,true,false,false,true,false,false,true,true,true,false,false,true,true,true,true,true,false,false,true,false,false,true,false,true,false,false,false,true,true,false,true,true,false,false,false,true,true,false,true,true,true,false,true,false,true,true,true,false};
    uint256_from_bytes(a, a57_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a57_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a58_data[32]  = {0xc4,0x58,0x27,0x2f,0x49,0x8d,0xbf,0xa8,0xaf,0x06,0xbc,0xf7,0xe9,0x14,0x57,0xdb,0x7a,0xa0,0x68,0xf1,0x13,0xa5,0x39,0x7f,0x61,0xef,0x7b,0xd1,0xd8,0x74,0xbc,0x79};
    bool         a58_bits[256] = {true,false,false,true,true,true,true,false,false,false,true,true,true,true,false,true,false,false,true,false,true,true,true,false,false,false,false,true,true,false,true,true,true,false,false,false,true,false,true,true,true,true,false,true,true,true,true,false,true,true,true,true,false,true,true,true,true,false,false,false,false,true,true,false,true,true,true,true,true,true,true,false,true,false,false,true,true,true,false,false,true,false,true,false,false,true,false,true,true,true,false,false,true,false,false,false,true,false,false,false,true,true,true,true,false,false,false,true,false,true,true,false,false,false,false,false,false,true,false,true,false,true,false,true,true,true,true,false,true,true,false,true,true,false,true,true,true,true,true,false,true,false,true,false,false,false,true,false,true,false,false,false,true,false,false,true,false,true,true,true,true,true,true,false,true,true,true,true,false,false,true,true,true,true,false,true,false,true,true,false,false,false,false,false,true,true,true,true,false,true,false,true,false,false,false,true,false,true,false,true,true,true,true,true,true,true,false,true,true,false,true,true,false,false,false,true,true,false,false,true,false,false,true,false,true,true,true,true,false,true,false,false,true,true,true,false,false,true,false,false,false,false,false,true,true,false,true,false,false,false,true,false,false,false,true,true};
    uint256_from_bytes(a, a58_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a58_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a59_data[32]  = {0x54,0xef,0x12,0x5a,0x25,0xbd,0xa6,0x59,0x99,0x86,0x48,0xe0,0x13,0xd5,0x31,0x6f,0x32,0xc3,0x24,0x44,0xa4,0x8c,0x1d,0x5c,0xa1,0xfe,0xb6,0x24,0x9d,0xf2,0x02,0x5f};
    bool         a59_bits[256] = {true,true,true,true,true,false,true,false,false,true,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,false,true,true,true,false,false,true,false,false,true,false,false,true,false,false,false,true,true,false,true,true,false,true,false,true,true,true,true,true,true,true,true,false,false,false,false,true,false,true,false,false,true,true,true,false,true,false,true,false,true,true,true,false,false,false,false,false,true,true,false,false,false,true,false,false,true,false,false,true,false,true,false,false,true,false,false,false,true,false,false,false,true,false,false,true,false,false,true,true,false,false,false,false,true,true,false,true,false,false,true,true,false,false,true,true,true,true,false,true,true,false,true,false,false,false,true,true,false,false,true,false,true,false,true,false,true,true,true,true,false,false,true,false,false,false,false,false,false,false,false,true,true,true,false,false,false,true,false,false,true,false,false,true,true,false,false,false,false,true,true,false,false,true,true,false,false,true,true,false,false,true,true,false,true,false,false,true,true,false,false,true,false,true,true,false,true,true,true,true,false,true,true,false,true,false,false,true,false,false,false,true,false,true,true,false,true,false,false,true,false,false,true,false,false,false,true,true,true,true,false,true,true,true,false,false,true,false,true,false,true,false};
    uint256_from_bytes(a, a59_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a59_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a60_data[32]  = {0x03,0x31,0x2e,0xad,0x22,0x29,0x30,0xae,0x91,0x58,0xd4,0xa8,0x9f,0x03,0xbc,0x5a,0x4d,0xee,0x48,0x12,0xb1,0x61,0x07,0xf1,0xbe,0x43,0x7c,0x7b,0xa6,0xca,0xf4,0xa3};
    bool         a60_bits[256] = {true,true,false,false,false,true,false,true,false,false,true,false,true,true,true,true,false,true,false,true,false,false,true,true,false,true,true,false,false,true,false,true,true,true,false,true,true,true,true,false,false,false,true,true,true,true,true,false,true,true,false,false,false,false,true,false,false,true,true,true,true,true,false,true,true,false,false,false,true,true,true,true,true,true,true,false,false,false,false,false,true,false,false,false,false,true,true,false,true,false,false,false,true,true,false,true,false,true,false,false,true,false,false,false,false,false,false,true,false,false,true,false,false,true,true,true,false,true,true,true,true,false,true,true,false,false,true,false,false,true,false,true,true,false,true,false,false,false,true,true,true,true,false,true,true,true,false,false,false,false,false,false,true,true,true,true,true,false,false,true,false,false,false,true,false,true,false,true,false,false,true,false,true,false,true,true,false,false,false,true,true,false,true,false,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,true,false,false,false,false,true,true,false,false,true,false,false,true,false,true,false,false,false,true,false,false,false,true,false,false,true,false,true,true,false,true,false,true,false,true,true,true,false,true,false,false,true,false,false,false,true,true,false,false,true,true,false,false,false,false,false,false};
    uint256_from_bytes(a, a60_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a60_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a61_data[32]  = {0xee,0x37,0x9c,0x65,0xf2,0x12,0x01,0xe4,0xea,0xa3,0x55,0x6c,0x35,0xb7,0xe4,0x48,0x63,0x08,0x7e,0x52,0x44,0xc6,0xb8,0x95,0xfe,0x74,0x9e,0x67,0x73,0x0f,0x37,0xf1};
    bool         a61_bits[256] = {true,false,false,false,true,true,true,true,true,true,true,false,true,true,false,false,true,true,true,true,false,false,false,false,true,true,false,false,true,true,true,false,true,true,true,false,false,true,true,false,false,true,true,true,true,false,false,true,false,false,true,false,true,true,true,false,false,true,true,true,true,true,true,true,true,false,true,false,true,false,false,true,false,false,false,true,true,true,false,true,false,true,true,false,false,false,true,true,false,false,true,false,false,false,true,false,false,true,false,false,true,false,true,false,false,true,true,true,true,true,true,false,false,false,false,true,false,false,false,false,true,true,false,false,false,true,true,false,false,false,false,true,false,false,true,false,false,false,true,false,false,true,true,true,true,true,true,false,true,true,false,true,true,false,true,false,true,true,false,false,false,false,true,true,false,true,true,false,true,false,true,false,true,false,true,false,true,true,false,false,false,true,false,true,false,true,false,true,false,true,true,true,false,false,true,false,false,true,true,true,true,false,false,false,false,false,false,false,false,true,false,false,true,false,false,false,false,true,false,false,true,true,true,true,true,false,true,false,false,true,true,false,false,false,true,true,true,false,false,true,true,true,true,false,true,true,false,false,false,true,true,true,false,true,true,true};
    uint256_from_bytes(a, a61_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a61_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a62_data[32]  = {0xf3,0xe6,0xca,0x73,0x43,0x05,0xe9,0x86,0x86,0x29,0x2b,0xb5,0xbf,0x5b,0x41,0x1b,0x24,0x49,0x1d,0xf6,0x17,0x1e,0x1a,0x8c,0x94,0xdb,0x5f,0x8f,0x13,0x19,0xd4,0x24};
    bool         a62_bits[256] = {false,false,true,false,false,true,false,false,false,false,true,false,true,false,true,true,true,false,false,true,true,false,false,false,true,true,false,false,true,false,false,false,true,true,true,true,false,false,false,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,true,true,false,false,true,false,true,false,false,true,false,false,true,true,false,false,false,true,false,true,false,true,true,false,false,false,false,true,true,true,true,false,false,false,true,true,true,false,true,false,false,false,false,true,true,false,true,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,false,true,false,false,false,true,false,false,true,false,false,true,true,false,true,true,false,false,false,true,false,false,false,false,false,true,false,true,true,false,true,true,false,true,false,true,true,true,true,true,true,false,true,true,false,true,false,true,true,false,true,true,true,false,true,false,true,false,false,true,false,false,true,false,true,false,false,false,true,true,false,false,false,false,true,false,true,true,false,false,false,false,true,true,false,false,true,false,true,true,true,true,false,true,false,false,false,false,false,true,true,false,false,false,false,true,false,true,true,false,false,true,true,true,false,false,true,false,true,false,false,true,true,false,true,true,false,false,true,true,true,true,true,false,false,true,true,true,true};
    uint256_from_bytes(a, a62_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a62_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a63_data[32]  = {0x06,0x5b,0x8c,0x35,0x64,0xe2,0x76,0x02,0x7c,0x73,0xb6,0xc9,0xe0,0x4b,0x0d,0xce,0xe5,0xd0,0x0a,0x4d,0x7f,0x75,0x95,0xb5,0x3b,0x3b,0xf4,0xbf,0x5d,0x7c,0xfe,0xd1};
    bool         a63_bits[256] = {true,false,false,false,true,false,true,true,false,true,true,true,true,true,true,true,false,false,true,true,true,true,true,false,true,false,true,true,true,false,true,false,true,true,true,true,true,true,false,true,false,false,true,false,true,true,true,true,true,true,false,true,true,true,false,false,true,true,false,true,true,true,false,false,true,false,true,false,true,true,false,true,true,false,true,false,true,false,false,true,true,false,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,false,true,true,false,false,true,false,false,true,false,true,false,false,false,false,false,false,false,false,true,false,true,true,true,false,true,false,false,true,true,true,false,true,true,true,false,false,true,true,true,false,true,true,false,false,false,false,true,true,false,true,false,false,true,false,false,false,false,false,false,true,true,true,true,false,false,true,false,false,true,true,false,true,true,false,true,true,false,true,true,true,false,false,true,true,true,false,false,false,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false,true,true,false,true,true,true,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,false,true,false,true,false,true,true,false,false,false,false,true,true,false,false,false,true,true,true,false,true,true,false,true,false,false,true,true,false,false,false,false,false};
    uint256_from_bytes(a, a63_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a63_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a64_data[32]  = {0xba,0x28,0xa6,0x79,0x4d,0x4c,0xa9,0xc7,0x67,0xc9,0x8f,0xb9,0x73,0x65,0x06,0xec,0xae,0x7c,0x8f,0x09,0x7d,0xdf,0xcb,0xc9,0xf3,0x30,0x8c,0xe5,0x00,0xeb,0x4e,0x11};
    bool         a64_bits[256] = {true,false,false,false,true,false,false,false,false,true,true,true,false,false,true,false,true,true,false,true,false,true,true,true,false,false,false,false,false,false,false,false,true,false,true,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,false,false,true,true,false,false,true,true,false,false,true,true,true,true,true,false,false,true,false,false,true,true,true,true,false,true,false,false,true,true,true,true,true,true,true,false,true,true,true,false,true,true,true,true,true,false,true,false,false,true,false,false,false,false,true,true,true,true,false,false,false,true,false,false,true,true,true,true,true,false,false,true,true,true,false,true,false,true,false,false,true,true,false,true,true,true,false,true,true,false,false,false,false,false,true,false,true,false,false,true,true,false,true,true,false,false,true,true,true,false,true,false,false,true,true,true,false,true,true,true,true,true,false,false,false,true,true,false,false,true,false,false,true,true,true,true,true,false,false,true,true,false,true,true,true,false,false,false,true,true,true,false,false,true,false,true,false,true,false,false,true,true,false,false,true,false,true,false,true,true,false,false,true,false,true,false,false,true,true,true,true,false,false,true,true,false,false,true,false,true,false,false,false,true,false,true,false,false,false,true,false,true,true,true,false,true};
    uint256_from_bytes(a, a64_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a64_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a65_data[32]  = {0x00,0x72,0x1f,0x84,0x54,0xd1,0xac,0x6b,0xd7,0x19,0x61,0x89,0x1e,0xf3,0xea,0x44,0x50,0xea,0x7d,0xa7,0x60,0x48,0x7e,0x15,0x58,0x0d,0xc5,0xab,0x6a,0x8a,0xd9,0xcb};
    bool         a65_bits[256] = {true,true,false,true,false,false,true,true,true,false,false,true,true,false,true,true,false,true,false,true,false,false,false,true,false,true,false,true,false,true,true,false,true,true,false,true,false,true,false,true,true,false,true,false,false,false,true,true,true,false,true,true,false,false,false,false,false,false,false,true,true,false,true,false,true,false,true,false,true,false,false,false,false,true,true,true,true,true,true,false,false,false,false,true,false,false,true,false,false,false,false,false,false,true,true,false,true,true,true,false,false,true,false,true,true,false,true,true,true,true,true,false,false,true,false,true,false,true,true,true,false,false,false,false,true,false,true,false,false,false,true,false,false,false,true,false,false,true,false,true,false,true,true,true,true,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,true,false,false,true,false,false,false,true,true,false,false,false,false,true,true,false,true,false,false,true,true,false,false,false,true,true,true,false,true,false,true,true,true,true,false,true,false,true,true,false,false,false,true,true,false,true,false,true,true,false,false,false,true,false,true,true,false,false,true,false,true,false,true,false,false,false,true,false,false,false,false,true,true,true,true,true,true,false,false,false,false,true,false,false,true,true,true,false,false,false,false,false,false,false,false,false};
    uint256_from_bytes(a, a65_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a65_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a66_data[32]  = {0x64,0x95,0x0d,0xc2,0x10,0xa2,0x5b,0x19,0x5f,0x49,0xf0,0xfc,0x40,0xd2,0x84,0x06,0x4a,0x32,0x7e,0x2d,0xbd,0x6a,0x99,0x6d,0xe6,0xcd,0x10,0xf1,0x03,0x00,0x30,0x05};
    bool         a66_bits[256] = {true,false,true,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,true,true,false,false,false,false,true,false,false,false,true,false,true,true,false,false,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,true,false,true,false,false,true,true,false,false,true,false,true,false,true,false,true,true,false,true,false,true,true,true,true,false,true,true,false,true,true,false,true,false,false,false,true,true,true,true,true,true,false,false,true,false,false,true,true,false,false,false,true,false,true,false,false,true,false,false,true,true,false,false,false,false,false,false,false,true,false,false,false,false,true,false,true,false,false,true,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,true,true,true,true,false,false,false,false,true,true,true,true,true,false,false,true,false,false,true,false,true,true,true,true,true,false,true,false,true,false,false,true,true,false,false,false,true,true,false,true,true,false,true,false,false,true,false,false,false,true,false,true,false,false,false,false,true,false,false,false,false,true,false,false,false,false,true,true,true,false,true,true,false,false,false,false,true,false,true,false,true,false,false,true,false,false,true,false,false,true,true,false};
    uint256_from_bytes(a, a66_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a66_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a67_data[32]  = {0xc1,0x72,0xb2,0x98,0x6d,0x94,0xdd,0x6d,0xec,0xe8,0x07,0x99,0x5c,0x57,0x72,0x2e,0x13,0x8e,0xfe,0xf9,0x96,0xd4,0x48,0x0f,0xde,0xb6,0x7a,0xe7,0xff,0xb0,0xdd,0x9e};
    bool         a67_bits[256] = {false,true,true,true,true,false,false,true,true,false,true,true,true,false,true,true,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,true,false,true,true,true,true,false,false,true,true,false,true,true,false,true,false,true,true,true,true,false,true,true,true,true,true,true,false,false,false,false,false,false,false,true,false,false,true,false,false,false,true,false,true,false,true,true,false,true,true,false,true,false,false,true,true,false,false,true,true,true,true,true,false,true,true,true,true,true,true,true,false,true,true,true,false,false,false,true,true,true,false,false,true,false,false,false,false,true,true,true,false,true,false,false,false,true,false,false,true,true,true,false,true,true,true,false,true,false,true,false,false,false,true,true,true,false,true,false,true,false,false,true,true,false,false,true,true,true,true,false,false,false,false,false,false,false,false,true,false,true,true,true,false,false,true,true,false,true,true,true,true,false,true,true,false,true,true,false,true,false,true,true,true,false,true,true,false,false,true,false,true,false,false,true,true,false,true,true,false,true,true,false,false,false,false,true,true,false,false,true,false,true,false,false,true,true,false,true,false,true,false,false,true,true,true,false,true,false,false,false,false,false,true,true};
    uint256_from_bytes(a, a67_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a67_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a68_data[32]  = {0x50,0xcb,0x40,0x7a,0x82,0xce,0x78,0x6f,0x6f,0xad,0x79,0x36,0x44,0x06,0xc0,0x53,0xf8,0x95,0xfc,0x55,0x3f,0xd3,0xbe,0x98,0x26,0x1f,0x40,0xdf,0xef,0x82,0xd1,0xa3};
    bool         a68_bits[256] = {true,true,false,false,false,true,false,true,true,false,false,false,true,false,true,true,false,true,false,false,false,false,false,true,true,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,true,false,true,true,true,true,true,false,false,false,false,true,true,false,false,true,false,false,false,false,false,true,true,false,false,true,false,true,true,true,true,true,false,true,true,true,false,false,true,false,true,true,true,true,true,true,true,true,false,false,true,false,true,false,true,false,true,false,false,false,true,true,true,true,true,true,true,false,true,false,true,false,false,true,false,false,false,true,true,true,true,true,true,true,false,false,true,false,true,false,false,false,false,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,true,false,false,false,true,false,false,true,true,false,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,true,false,true,false,true,true,true,true,true,false,true,true,false,true,true,true,true,false,true,true,false,false,false,false,true,true,true,true,false,false,true,true,true,false,false,true,true,false,true,false,false,false,false,false,true,false,true,false,true,true,true,true,false,false,false,false,false,false,false,true,false,true,true,false,true,false,false,true,true,false,false,false,false,true,false,true,false};
    uint256_from_bytes(a, a68_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a68_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a69_data[32]  = {0xc0,0xae,0xd9,0xc5,0x9d,0x6b,0x02,0x3f,0x73,0x6b,0x96,0xa0,0x69,0x2f,0xd3,0x60,0xbb,0x7b,0x73,0x8e,0xee,0xf7,0x95,0xcd,0x0c,0xaa,0x76,0x12,0x14,0xa0,0xb0,0x0b};
    bool         a69_bits[256] = {true,true,false,true,false,false,false,false,false,false,false,false,true,true,false,true,false,false,false,false,false,true,false,true,false,false,true,false,true,false,false,false,false,true,false,false,true,false,false,false,false,true,true,false,true,true,true,false,false,true,false,true,false,true,false,true,false,false,true,true,false,false,false,false,true,false,true,true,false,false,true,true,true,false,true,false,true,false,false,true,true,true,true,false,true,true,true,true,false,true,true,true,false,true,true,true,false,true,true,true,false,false,false,true,true,true,false,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,true,false,true,false,false,true,false,false,true,false,true,true,false,false,false,false,false,false,true,false,true,false,true,true,false,true,false,false,true,true,true,false,true,false,true,true,false,true,true,false,false,true,true,true,false,true,true,true,true,true,true,false,false,false,true,false,false,false,false,false,false,true,true,false,true,false,true,true,false,true,false,true,true,true,false,false,true,true,false,true,false,false,false,true,true,true,false,false,true,true,false,true,true,false,true,true,true,false,true,false,true,false,false,false,false,false,false,true,true};
    uint256_from_bytes(a, a69_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a69_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a70_data[32]  = {0x8c,0xd3,0xe4,0x18,0xed,0x41,0x42,0xba,0xe9,0x72,0x9f,0x3f,0x0c,0x89,0xc0,0x01,0x7c,0x4e,0xa6,0x03,0x49,0x44,0xf2,0xce,0xde,0x96,0x2a,0x6d,0xa4,0xfd,0x57,0xc5};
    bool         a70_bits[256] = {true,false,true,false,false,false,true,true,true,true,true,false,true,false,true,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,false,true,true,false,true,true,false,true,true,false,false,true,false,true,false,true,false,false,false,true,true,false,true,false,false,true,false,true,true,true,true,false,true,true,false,true,true,true,false,false,true,true,false,true,false,false,true,true,true,true,false,false,true,false,false,false,true,false,true,false,false,true,false,false,true,false,true,true,false,false,false,false,false,false,false,true,true,false,false,true,false,true,false,true,true,true,false,false,true,false,false,false,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,false,false,true,true,true,true,true,true,false,false,true,true,true,true,true,false,false,true,false,true,false,false,true,true,true,false,true,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,true,false,true,true,false,true,true,true,false,false,false,true,true,false,false,false,false,false,true,false,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,false,true};
    uint256_from_bytes(a, a70_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a70_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a71_data[32]  = {0x17,0x39,0x10,0xe3,0x3e,0x7c,0x65,0x67,0x31,0x41,0x97,0x75,0x8c,0x3b,0xa8,0x59,0x23,0xbc,0x91,0x52,0x6d,0x6b,0x98,0x7a,0x73,0x30,0x9b,0x95,0xc2,0x5e,0x11,0x4f};
    bool         a71_bits[256] = {true,true,true,true,false,false,true,false,true,false,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,true,false,false,false,false,true,true,true,false,true,false,true,false,false,true,true,true,false,true,true,false,false,true,false,false,false,false,true,true,false,false,true,true,false,false,true,true,true,false,false,true,false,true,true,true,true,false,false,false,false,true,true,false,false,true,true,true,false,true,false,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false,true,false,true,false,true,false,false,false,true,false,false,true,false,false,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,false,true,true,false,true,false,false,false,false,true,false,true,false,true,true,true,false,true,true,true,false,false,false,false,true,true,false,false,false,true,true,false,true,false,true,true,true,false,true,true,true,false,true,false,false,true,true,false,false,false,false,false,true,false,true,false,false,false,true,true,false,false,true,true,true,false,false,true,true,false,true,false,true,false,false,true,true,false,false,false,true,true,true,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,true,true,false,false,false,false,true,false,false,false,true,false,false,true,true,true,false,false,true,true,true,false,true,false,false,false};
    uint256_from_bytes(a, a71_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a71_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a72_data[32]  = {0x7f,0x86,0x7d,0x5f,0x0f,0xe3,0x21,0xec,0xc0,0x8a,0x58,0xd7,0x56,0x94,0x7a,0x7a,0x45,0x2e,0x70,0x4d,0x60,0x7a,0x47,0x32,0x35,0xc2,0xe2,0x29,0x86,0x2f,0xe2,0x31};
    bool         a72_bits[256] = {true,false,false,false,true,true,false,false,false,true,false,false,false,true,true,true,true,true,true,true,false,true,false,false,false,true,true,false,false,false,false,true,true,false,false,true,false,true,false,false,false,true,false,false,false,true,true,true,false,true,false,false,false,false,true,true,true,false,true,false,true,true,false,false,false,true,false,false,true,true,false,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,true,false,false,false,false,false,false,true,true,false,true,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,true,false,true,false,false,true,false,true,false,false,false,true,false,false,true,false,true,true,true,true,false,false,true,false,true,true,true,true,false,false,false,true,false,true,false,false,true,false,true,true,false,true,false,true,false,true,true,true,false,true,false,true,true,false,false,false,true,true,false,true,false,false,true,false,true,false,false,false,true,false,false,false,false,false,false,true,true,false,false,true,true,false,true,true,true,true,false,false,false,false,true,false,false,true,true,false,false,false,true,true,true,true,true,true,true,false,false,false,false,true,true,true,true,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,false,false,false,false,true,true,true,true,true,true,true,true,false};
    uint256_from_bytes(a, a72_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a72_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a73_data[32]  = {0x62,0x72,0x92,0xf8,0x3f,0x9a,0xa8,0x84,0xe5,0x94,0x09,0xc1,0x45,0x61,0x9f,0xc0,0x17,0xb4,0x83,0x4c,0x37,0x49,0x5c,0x5e,0xd9,0x3f,0xf7,0x16,0xdc,0xe4,0x7b,0x21};
    bool         a73_bits[256] = {true,false,false,false,false,true,false,false,true,true,false,true,true,true,true,false,false,false,true,false,false,true,true,true,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,false,true,true,true,false,true,true,true,true,true,true,true,true,true,true,false,false,true,false,false,true,true,false,true,true,false,true,true,true,true,false,true,false,false,false,true,true,true,false,true,false,true,false,false,true,false,false,true,false,true,true,true,false,true,true,false,false,false,false,true,true,false,false,true,false,true,true,false,false,false,false,false,true,false,false,true,false,true,true,false,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,false,false,true,true,false,false,false,false,true,true,false,true,false,true,false,false,false,true,false,true,false,false,false,false,false,true,true,true,false,false,true,false,false,false,false,false,false,true,false,true,false,false,true,true,false,true,false,false,true,true,true,false,false,true,false,false,false,false,true,false,false,false,true,false,true,false,true,false,true,false,true,true,false,false,true,true,true,true,true,true,true,false,false,false,false,false,true,true,true,true,true,false,true,false,false,true,false,false,true,false,true,false,false,true,true,true,false,false,true,false,false,false,true,true,false};
    uint256_from_bytes(a, a73_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a73_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a74_data[32]  = {0xcd,0xe3,0x47,0xab,0xe5,0x4c,0x5d,0xe6,0xc3,0x81,0x3c,0xe6,0xb5,0xa2,0x90,0x61,0x6c,0xd9,0xe6,0x2a,0x08,0x41,0x1c,0x07,0x20,0x93,0x42,0xca,0x05,0x95,0x5f,0xb9};
    bool         a74_bits[256] = {true,false,false,true,true,true,false,true,true,true,true,true,true,false,true,false,true,false,true,false,true,false,false,true,true,false,true,false,false,false,false,false,false,true,false,true,false,false,true,true,false,true,false,false,false,false,true,false,true,true,false,false,true,false,false,true,false,false,false,false,false,true,false,false,true,true,true,false,false,false,false,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,true,false,false,false,false,true,false,false,false,false,false,true,false,true,false,true,false,false,false,true,true,false,false,true,true,true,true,false,false,true,true,false,true,true,false,false,true,true,false,true,true,false,true,false,false,false,false,true,true,false,false,false,false,false,true,false,false,true,false,true,false,false,false,true,false,true,true,false,true,false,true,true,false,true,false,true,true,false,false,true,true,true,false,false,true,true,true,true,false,false,true,false,false,false,false,false,false,true,true,true,false,false,false,false,true,true,false,true,true,false,false,true,true,true,true,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,true,false,true,false,false,true,true,true,true,true,false,true,false,true,false,true,true,true,true,false,false,false,true,false,true,true,false,false,false,true,true,true,true,false,true,true,false,false,true,true};
    uint256_from_bytes(a, a74_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a74_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a75_data[32]  = {0xc8,0x79,0xb6,0x63,0x3f,0x9b,0x6b,0xb2,0x72,0xee,0x6a,0x2e,0xf8,0xe4,0xcb,0x5c,0x77,0xd8,0xc5,0x69,0xda,0xff,0x9a,0x0b,0x87,0x21,0xec,0xf8,0xd3,0x59,0xd0,0x7a};
    bool         a75_bits[256] = {false,true,false,true,true,true,true,false,false,false,false,false,true,false,true,true,true,false,false,true,true,false,true,false,true,true,false,false,true,false,true,true,false,false,false,true,true,true,true,true,false,false,true,true,false,true,true,true,true,false,false,false,false,true,false,false,true,true,true,false,false,false,false,true,true,true,false,true,false,false,false,false,false,true,false,true,true,false,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,true,true,false,false,true,false,true,true,false,true,false,true,false,false,false,true,true,false,false,false,true,true,false,true,true,true,true,true,false,true,true,true,false,false,false,true,true,true,false,true,false,true,true,false,true,false,false,true,true,false,false,true,false,false,true,true,true,false,false,false,true,true,true,true,true,false,true,true,true,false,true,false,false,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,true,false,true,false,false,true,true,true,false,false,true,false,false,true,true,false,true,true,true,false,true,false,true,true,false,true,true,false,true,true,false,false,true,true,true,true,true,true,true,false,false,true,true,false,false,false,true,true,false,false,true,true,false,true,true,false,true,true,false,false,true,true,true,true,false,false,false,false,true,false,false,true,true};
    uint256_from_bytes(a, a75_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a75_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a76_data[32]  = {0xeb,0x7f,0xe2,0x6b,0x91,0xc3,0x09,0x8c,0x3b,0x8a,0x27,0xba,0x20,0x2a,0xb6,0xfa,0xc8,0x44,0xb8,0xfd,0x00,0x59,0x86,0x5a,0x0a,0x1f,0xb4,0x3b,0xc6,0xe0,0x67,0x3a};
    bool         a76_bits[256] = {false,true,false,true,true,true,false,false,true,true,true,false,false,true,true,false,false,false,false,false,false,true,true,true,false,true,true,false,false,false,true,true,true,true,false,true,true,true,false,false,false,false,true,false,true,true,false,true,true,true,true,true,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,true,true,false,true,false,false,true,true,false,false,false,false,true,true,false,false,true,true,false,true,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,false,false,false,true,true,true,false,true,false,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,false,true,false,true,true,true,true,true,false,true,true,false,true,true,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,true,false,false,false,true,false,true,true,true,false,true,true,true,true,false,false,true,false,false,false,true,false,true,false,false,false,true,true,true,false,true,true,true,false,false,false,false,true,true,false,false,false,true,true,false,false,true,false,false,false,false,true,true,false,false,false,false,true,true,true,false,false,false,true,false,false,true,true,true,false,true,false,true,true,false,false,true,false,false,false,true,true,true,true,true,true,true,true,true,true,false,true,true,false,true,false,true,true,true};
    uint256_from_bytes(a, a76_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a76_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a77_data[32]  = {0x00,0x4b,0x7f,0xd0,0x99,0xdf,0x20,0x9b,0xca,0x5d,0x5e,0x7d,0x39,0x3c,0xbc,0xdd,0x42,0xc9,0x27,0xb9,0x63,0x59,0x56,0xbe,0x31,0x13,0x5d,0xe9,0x95,0x38,0x57,0xd7};
    bool         a77_bits[256] = {true,true,true,false,true,false,true,true,true,true,true,false,true,false,true,false,false,false,false,true,true,true,false,false,true,false,true,false,true,false,false,true,true,false,false,true,false,true,true,true,true,false,true,true,true,false,true,false,true,true,false,false,true,false,false,false,true,false,false,false,true,true,false,false,false,true,true,true,true,true,false,true,false,true,true,false,true,false,true,false,true,false,false,true,true,false,true,false,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,true,true,true,true,false,false,true,false,false,true,false,false,true,false,false,true,true,false,true,false,false,false,false,true,false,true,false,true,true,true,false,true,true,false,false,true,true,true,true,false,true,false,false,true,true,true,true,false,false,true,false,false,true,true,true,false,false,true,false,true,true,true,true,true,false,false,true,true,true,true,false,true,false,true,false,true,true,true,false,true,false,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,true,false,false,false,false,false,true,false,false,true,true,true,true,true,false,true,true,true,false,false,true,true,false,false,true,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,false,true,true,false,true,false,false,true,false,false,false,false,false,false,false,false,false};
    uint256_from_bytes(a, a77_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a77_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a78_data[32]  = {0x6b,0xa9,0x9d,0x01,0xb7,0xe4,0x9f,0x36,0x56,0x8a,0x8c,0x29,0xb2,0x21,0x71,0x39,0x08,0xba,0x9b,0xd9,0x7e,0x31,0x8a,0xd6,0x3a,0x0e,0xa6,0xe1,0x5e,0xc6,0x9b,0xe3};
    bool         a78_bits[256] = {true,true,false,false,false,true,true,true,true,true,false,true,true,false,false,true,false,true,true,false,false,false,true,true,false,true,true,true,true,false,true,false,true,false,false,false,false,true,true,true,false,true,true,false,false,true,false,true,false,true,true,true,false,false,false,false,false,true,false,true,true,true,false,false,false,true,true,false,true,false,true,true,false,true,false,true,false,false,false,true,true,false,false,false,true,true,false,false,false,true,true,true,true,true,true,false,true,false,false,true,true,false,true,true,true,true,false,true,true,false,false,true,false,true,false,true,true,true,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,true,false,false,true,false,false,false,true,true,true,false,true,false,false,false,false,true,false,false,false,true,false,false,true,true,false,true,true,false,false,true,false,true,false,false,false,false,true,true,false,false,false,true,false,true,false,true,false,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,true,true,false,false,true,true,true,true,true,false,false,true,false,false,true,false,false,true,true,true,true,true,true,false,true,true,false,true,true,false,false,false,false,false,false,false,true,false,true,true,true,false,false,true,true,false,false,true,false,true,false,true,true,true,false,true,false,true,true,false};
    uint256_from_bytes(a, a78_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a78_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a79_data[32]  = {0xd1,0xeb,0xd0,0x86,0xc4,0x0f,0x36,0x09,0x4f,0xcc,0x9a,0x5c,0x33,0x4e,0x51,0xaf,0xf8,0x48,0xa9,0x56,0x7e,0xe5,0xe8,0x57,0x34,0x89,0x34,0x98,0x11,0x43,0x40,0xff};
    bool         a79_bits[256] = {true,true,true,true,true,true,true,true,false,false,false,false,false,false,true,false,true,true,false,false,false,false,true,false,true,false,false,false,true,false,false,false,false,false,false,true,true,false,false,true,false,false,true,false,true,true,false,false,true,false,false,true,false,false,false,true,false,false,true,false,true,true,false,false,true,true,true,false,true,false,true,false,false,false,false,true,false,true,true,true,true,false,true,false,false,true,true,true,false,true,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,false,false,true,false,true,false,true,false,false,false,true,false,false,true,false,false,false,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,false,false,true,false,true,false,false,true,true,true,false,false,true,false,true,true,false,false,true,true,false,false,false,false,true,true,true,false,true,false,false,true,false,true,true,false,false,true,false,false,true,true,false,false,true,true,true,true,true,true,false,false,true,false,true,false,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,true,true,true,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,false,false,false,false,true,false,false,false,false,true,false,true,true,true,true,false,true,false,true,true,true,true,false,false,false,true,false,true,true};
    uint256_from_bytes(a, a79_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a79_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a80_data[32]  = {0x0d,0xea,0x6e,0x4e,0x64,0xb9,0xcb,0x1c,0xec,0x03,0x2e,0x6b,0x25,0x79,0x5c,0x18,0x98,0x44,0xf4,0x76,0xf2,0xe2,0x05,0x4d,0x0e,0x71,0x59,0x7a,0xaa,0x50,0xb9,0x6f};
    bool         a80_bits[256] = {true,true,true,true,false,true,true,false,true,false,false,true,true,true,false,true,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,true,false,true,false,false,true,true,false,true,false,true,false,false,false,true,true,true,false,false,true,true,true,false,false,false,false,true,false,true,true,false,false,true,false,true,false,true,false,false,false,false,false,false,true,false,false,false,true,true,true,false,true,false,false,true,true,true,true,false,true,true,false,true,true,true,false,false,false,true,false,true,true,true,true,false,false,true,false,false,false,true,false,false,false,false,true,true,false,false,true,false,false,false,true,true,false,false,false,false,false,true,true,true,false,true,false,true,false,false,true,true,true,true,false,true,false,true,false,false,true,false,false,true,true,false,true,false,true,true,false,false,true,true,true,false,true,false,false,true,true,false,false,false,false,false,false,false,false,true,true,false,true,true,true,false,false,true,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,false,true,true,true,false,true,false,false,true,false,false,true,true,false,false,true,true,true,false,false,true,false,false,true,true,true,false,true,true,false,false,true,false,true,false,true,true,true,true,false,true,true,false,false,false,false};
    uint256_from_bytes(a, a80_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a80_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a81_data[32]  = {0x0f,0x65,0x06,0x38,0xb5,0xb9,0x4a,0xf3,0x0d,0x45,0x6b,0xe0,0x6a,0x56,0xaa,0xc3,0x24,0x54,0x48,0xc8,0x98,0x9b,0xc9,0xdc,0xf9,0x5f,0xe8,0xa0,0x06,0x0c,0x88,0x04};
    bool         a81_bits[256] = {false,false,true,false,false,false,false,false,false,false,false,true,false,false,false,true,false,false,true,true,false,false,false,false,false,true,true,false,false,false,false,false,false,false,false,false,false,true,false,true,false,false,false,true,false,true,true,true,true,true,true,true,true,false,true,false,true,false,false,true,true,true,true,true,false,false,true,true,true,false,true,true,true,false,false,true,false,false,true,true,true,true,false,true,true,false,false,true,false,false,false,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,false,true,false,false,true,false,false,false,true,false,true,false,true,false,false,false,true,false,false,true,false,false,true,true,false,false,false,false,true,true,false,true,false,true,false,true,false,true,false,true,true,false,true,false,true,false,false,true,false,true,false,true,true,false,false,false,false,false,false,true,true,true,true,true,false,true,false,true,true,false,true,false,true,false,false,false,true,false,true,false,true,true,false,false,false,false,true,true,false,false,true,true,true,true,false,true,false,true,false,false,true,false,true,false,false,true,true,true,false,true,true,false,true,false,true,true,false,true,false,false,false,true,true,true,false,false,false,true,true,false,false,false,false,false,true,false,true,false,false,true,true,false,true,true,true,true,false,false,false,false};
    uint256_from_bytes(a, a81_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a81_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a82_data[32]  = {0xd6,0xd1,0x06,0xfb,0x60,0xed,0x33,0xa0,0xb9,0xb2,0x53,0xe3,0xaa,0x18,0x13,0x45,0x4f,0xd3,0xe7,0x58,0x08,0x2a,0x2f,0x4d,0x77,0xb5,0xab,0xcb,0xbf,0x0e,0x11,0xe0};
    bool         a82_bits[256] = {false,false,false,false,false,true,true,true,true,false,false,false,true,false,false,false,false,true,true,true,false,false,false,false,true,true,true,true,true,true,false,true,true,true,false,true,false,false,true,true,true,true,false,true,false,true,false,true,true,false,true,false,true,true,false,true,true,true,true,false,true,true,true,false,true,false,true,true,false,false,true,false,true,true,true,true,false,true,false,false,false,true,false,true,false,true,false,false,false,false,false,true,false,false,false,false,false,false,false,true,true,false,true,false,true,true,true,false,false,true,true,true,true,true,false,false,true,false,true,true,true,true,true,true,false,false,true,false,true,false,true,false,false,false,true,false,true,true,false,false,true,false,false,false,false,false,false,true,true,false,false,false,false,true,false,true,false,true,false,true,true,true,false,false,false,true,true,true,true,true,false,false,true,false,true,false,false,true,false,false,true,true,false,true,true,false,false,true,true,true,false,true,false,false,false,false,false,true,false,true,true,true,false,false,true,true,false,false,true,false,true,true,false,true,true,true,false,false,false,false,false,true,true,false,true,true,false,true,true,true,true,true,false,true,true,false,false,false,false,false,true,false,false,false,true,false,true,true,false,true,true,false,true,false,true,true};
    uint256_from_bytes(a, a82_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a82_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a83_data[32]  = {0x47,0xa1,0x64,0xe4,0x14,0x07,0xab,0x33,0x00,0xbc,0x22,0xcb,0x1b,0xe4,0xa5,0xdb,0x2b,0x54,0xaf,0x77,0x71,0x43,0x6e,0x1d,0x54,0xea,0x20,0x61,0xfc,0x27,0xd6,0x83};
    bool         a83_bits[256] = {true,true,false,false,false,false,false,true,false,true,true,false,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,true,true,true,true,true,true,false,false,false,false,true,true,false,false,false,false,false,false,true,false,false,false,true,false,true,false,true,true,true,false,false,true,false,true,false,true,false,true,false,true,true,true,false,false,false,false,true,true,true,false,true,true,false,true,true,false,false,false,false,true,false,true,false,false,false,true,true,true,false,true,true,true,false,true,true,true,false,true,true,true,true,false,true,false,true,false,false,true,false,true,false,true,false,true,true,false,true,false,true,false,false,true,true,false,true,true,false,true,true,true,false,true,false,false,true,false,true,false,false,true,false,false,true,true,true,true,true,false,true,true,false,false,false,true,true,false,true,false,false,true,true,false,true,false,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,false,false,false,false,false,false,true,true,false,false,true,true,false,false,true,true,false,true,false,true,false,true,true,true,true,false,false,false,false,false,false,false,true,false,true,false,false,false,false,false,true,false,false,true,true,true,false,false,true,false,false,true,true,false,true,false,false,false,false,true,false,true,true,true,true,false,false,false,true,false};
    uint256_from_bytes(a, a83_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a83_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a84_data[32]  = {0xc2,0x41,0x0a,0xd1,0xf6,0xda,0x7a,0x63,0x8f,0xa6,0x24,0xf7,0x1f,0xab,0x58,0x84,0xe2,0x9a,0xac,0xea,0xf4,0x9c,0x9e,0xba,0x6b,0x91,0x1f,0x97,0x59,0xf9,0xbb,0x79};
    bool         a84_bits[256] = {true,false,false,true,true,true,true,false,true,true,false,true,true,true,false,true,true,false,false,true,true,true,true,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,false,true,true,true,true,true,true,false,false,false,true,false,false,false,true,false,false,true,true,true,false,true,false,true,true,false,false,true,false,true,true,true,false,true,false,true,true,true,true,false,false,true,false,false,true,true,true,false,false,true,false,false,true,false,true,true,true,true,false,true,false,true,false,true,true,true,false,false,true,true,false,true,false,true,false,true,false,true,true,false,false,true,false,true,false,false,false,true,true,true,false,false,true,false,false,false,false,true,false,false,false,true,true,false,true,false,true,true,false,true,false,true,false,true,true,true,true,true,true,false,false,false,true,true,true,false,true,true,true,true,false,false,true,false,false,true,false,false,false,true,true,false,false,true,false,true,true,true,true,true,false,false,false,true,true,true,false,false,false,true,true,false,false,true,false,true,true,true,true,false,false,true,false,true,true,false,true,true,false,true,true,false,true,true,true,true,true,false,false,false,true,false,true,true,false,true,false,true,false,false,false,false,true,false,false,false,false,false,true,false,false,true,false,false,false,false,true,true};
    uint256_from_bytes(a, a84_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a84_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a85_data[32]  = {0x6e,0xb4,0xff,0xf8,0xcd,0xce,0xc4,0x08,0xd2,0x6f,0x1d,0x76,0x4f,0x06,0xe9,0x5a,0xd2,0x52,0xa6,0x17,0xc4,0xcb,0xa0,0x38,0x5b,0x4c,0x0d,0x73,0x61,0x50,0x2d,0xee};
    bool         a85_bits[256] = {false,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,false,false,false,false,true,false,true,false,true,false,false,false,false,true,true,false,true,true,false,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,true,false,false,true,false,true,true,false,true,true,false,true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,true,false,true,true,true,false,true,false,false,true,true,false,false,true,false,false,false,true,true,true,true,true,false,true,false,false,false,false,true,true,false,false,true,false,true,false,true,false,false,true,false,true,false,false,true,false,false,true,false,true,true,false,true,false,true,true,false,true,false,true,false,false,true,false,true,true,true,false,true,true,false,false,false,false,false,true,true,true,true,false,false,true,false,false,true,true,false,true,true,true,false,true,false,true,true,true,false,false,false,true,true,true,true,false,true,true,false,false,true,false,false,true,false,true,true,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,false,true,true,false,true,false,true,true,true,false,true,true,false};
    uint256_from_bytes(a, a85_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a85_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a86_data[32]  = {0x72,0x43,0xd4,0x7c,0xeb,0x64,0xc5,0xc4,0x8a,0xa1,0xa5,0x9c,0x5f,0x6a,0x35,0xd9,0x32,0x1a,0x6e,0xc1,0x79,0x34,0xf0,0xb8,0xb4,0x8b,0xb0,0x75,0x0c,0x9c,0x20,0xef};
    bool         a86_bits[256] = {true,true,true,true,false,true,true,true,false,false,false,false,false,true,false,false,false,false,true,true,true,false,false,true,false,false,true,true,false,false,false,false,true,false,true,false,true,true,true,false,false,false,false,false,true,true,false,true,true,true,false,true,false,false,false,true,false,false,true,false,true,true,false,true,false,false,false,true,true,true,false,true,false,false,false,false,true,true,true,true,false,false,true,false,true,true,false,false,true,false,false,true,true,true,true,false,true,false,false,false,false,false,true,true,false,true,true,true,false,true,true,false,false,true,false,true,true,false,false,false,false,true,false,false,true,true,false,false,true,false,false,true,true,false,true,true,true,false,true,false,true,true,false,false,false,true,false,true,false,true,true,false,true,true,true,true,true,false,true,false,false,false,true,true,true,false,false,true,true,false,true,false,false,true,false,true,true,false,false,false,false,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,false,true,true,false,true,true,false,true,false,true,true,true,false,false,true,true,true,true,true,false,false,false,true,false,true,false,true,true,true,true,false,false,false,false,true,false,false,true,false,false,true,true,true,false};
    uint256_from_bytes(a, a86_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a86_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a87_data[32]  = {0x69,0x2a,0x4f,0x0e,0xa1,0xb4,0x9b,0xf7,0x07,0xc0,0x90,0x9c,0x79,0x7b,0x15,0x38,0xe5,0xa1,0x5b,0x79,0xbc,0xc0,0xfd,0x98,0x5d,0x3f,0x69,0xce,0x52,0xc4,0x64,0x1b};
    bool         a87_bits[256] = {true,true,false,true,true,false,false,false,false,false,true,false,false,true,true,false,false,false,true,false,false,false,true,true,false,true,false,false,true,false,true,false,false,true,true,true,false,false,true,true,true,false,false,true,false,true,true,false,true,true,true,true,true,true,false,false,true,false,true,true,true,false,true,false,false,false,false,true,true,false,false,true,true,false,true,true,true,true,true,true,false,false,false,false,false,false,true,true,false,false,true,true,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,true,false,true,false,true,false,false,false,false,true,false,true,true,false,true,false,false,true,true,true,false,false,false,true,true,true,false,false,true,false,true,false,true,false,false,false,true,true,false,true,true,true,true,false,true,false,false,true,true,true,true,false,false,false,true,true,true,false,false,true,false,false,false,false,true,false,false,true,false,false,false,false,false,false,true,true,true,true,true,false,false,false,false,false,true,true,true,false,true,true,true,true,true,true,false,true,true,false,false,true,false,false,true,false,true,true,false,true,true,false,false,false,false,true,false,true,false,true,true,true,false,false,false,false,true,true,true,true,false,false,true,false,false,true,false,true,false,true,false,false,true,false,false,true,false,true,true,false};
    uint256_from_bytes(a, a87_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a87_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a88_data[32]  = {0x76,0xcc,0x05,0x73,0x08,0xec,0x37,0x9a,0x60,0x25,0x33,0xdc,0x0a,0x68,0x01,0x3d,0x67,0x9f,0x2d,0x9e,0xc4,0x44,0x5a,0xae,0xa0,0x1a,0xc2,0x3a,0xcf,0xd3,0xbb,0x74};
    bool         a88_bits[256] = {false,false,true,false,true,true,true,false,true,true,false,true,true,true,false,true,true,true,false,false,true,false,true,true,true,true,true,true,false,false,true,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,false,true,false,true,true,false,false,false,false,false,false,false,false,true,false,true,false,true,true,true,false,true,false,true,false,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,false,false,true,false,false,false,true,true,false,true,true,true,true,false,false,true,true,false,true,true,false,true,false,false,true,true,true,true,true,false,false,true,true,true,true,false,false,true,true,false,true,false,true,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,true,false,true,true,false,false,true,false,true,false,false,false,false,false,false,true,true,true,false,true,true,true,true,false,false,true,true,false,false,true,false,true,false,false,true,false,false,false,false,false,false,false,true,true,false,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,false,false,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,false,false,true,true,true,false,true,false,true,false,false,false,false,false,false,false,true,true,false,false,true,true,false,true,true,false,true,true,true,false};
    uint256_from_bytes(a, a88_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a88_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a89_data[32]  = {0x0b,0x28,0x6c,0x70,0x9d,0xf2,0x4d,0x5e,0xf4,0x29,0xc6,0x22,0xf5,0x2b,0x25,0x49,0x55,0xc0,0xa7,0x4d,0x45,0xb6,0x69,0xf7,0x5c,0xeb,0xe2,0x13,0x56,0xcd,0x42,0xd2};
    bool         a89_bits[256] = {false,true,false,false,true,false,true,true,false,true,false,false,false,false,true,false,true,false,true,true,false,false,true,true,false,true,true,false,true,false,true,false,true,true,false,false,true,false,false,false,false,true,false,false,false,true,true,true,true,true,false,true,false,true,true,true,false,false,true,true,true,false,true,false,true,true,true,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,true,false,true,true,false,true,true,false,true,false,false,false,true,false,true,false,true,true,false,false,true,false,true,true,true,false,false,true,false,true,false,false,false,false,false,false,true,true,true,false,true,false,true,false,true,false,true,false,false,true,false,false,true,false,true,false,true,false,false,true,false,false,true,true,false,true,false,true,false,false,true,false,true,false,true,true,true,true,false,true,false,false,false,true,false,false,false,true,true,false,false,false,true,true,true,false,false,true,false,true,false,false,false,false,true,false,true,true,true,true,false,true,true,true,true,false,true,false,true,false,true,true,false,false,true,false,false,true,false,false,true,true,true,true,true,false,true,true,true,false,false,true,false,false,false,false,true,true,true,false,false,false,true,true,false,true,true,false,false,false,false,true,false,true,false,false,true,true,false,true,false,false,false,false};
    uint256_from_bytes(a, a89_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a89_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a90_data[32]  = {0x10,0xb9,0x9a,0xc9,0xf1,0x78,0xd7,0x7f,0xf2,0x4d,0x04,0xfd,0xa2,0x4c,0x84,0x07,0xce,0x3f,0xa0,0x28,0xea,0x9d,0x18,0xb2,0x98,0x77,0x27,0x90,0xc1,0x72,0x6f,0x06};
    bool         a90_bits[256] = {false,true,true,false,false,false,false,false,true,true,true,true,false,true,true,false,false,true,false,false,true,true,true,false,true,false,false,false,false,false,true,true,false,false,false,false,true,false,false,true,true,true,true,false,false,true,false,false,true,true,true,false,true,true,true,false,false,false,false,true,true,false,false,true,false,true,false,false,true,true,false,true,false,false,false,true,true,false,false,false,true,false,true,true,true,false,false,true,false,true,false,true,false,true,true,true,false,false,false,true,false,true,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,false,false,false,true,true,true,false,false,true,true,true,true,true,false,false,false,false,false,false,false,true,false,false,false,false,true,false,false,true,true,false,false,true,false,false,true,false,false,false,true,false,true,true,false,true,true,true,true,true,true,false,false,true,false,false,false,false,false,true,false,true,true,false,false,true,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,false,true,false,true,true,false,false,false,true,true,true,true,false,true,false,false,false,true,true,true,true,true,false,false,true,false,false,true,true,false,true,false,true,true,false,false,true,true,false,false,true,true,true,false,true,false,false,false,false,true,false,false,false};
    uint256_from_bytes(a, a90_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a90_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a91_data[32]  = {0x75,0xf5,0xc1,0xa0,0x51,0xcd,0xf2,0xf9,0xdc,0x7a,0x61,0x5d,0x53,0xea,0xb0,0x31,0x3c,0x73,0xd5,0xf4,0x9b,0x75,0x03,0x62,0x26,0xbc,0x98,0x58,0xc5,0xd6,0xd5,0xe9};
    bool         a91_bits[256] = {true,false,false,true,false,true,true,true,true,false,true,false,true,false,true,true,false,true,true,false,true,false,true,true,true,false,true,false,false,false,true,true,false,false,false,true,true,false,true,false,false,false,false,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,true,false,false,true,false,false,false,true,false,false,false,true,true,false,true,true,false,false,false,false,false,false,true,false,true,false,true,true,true,false,true,true,false,true,true,false,false,true,false,false,true,false,true,true,true,true,true,false,true,false,true,false,true,true,true,true,false,false,true,true,true,false,false,false,true,true,true,true,false,false,true,false,false,false,true,true,false,false,false,false,false,false,true,true,false,true,false,true,false,true,false,true,true,true,true,true,false,false,true,false,true,false,true,false,true,true,true,false,true,false,true,false,false,false,false,true,true,false,false,true,false,true,true,true,true,false,false,false,true,true,true,false,true,true,true,false,false,true,true,true,true,true,false,true,false,false,true,true,true,true,true,false,true,true,false,false,true,true,true,false,false,false,true,false,true,false,false,false,false,false,false,true,false,true,true,false,false,false,false,false,true,true,true,false,true,false,true,true,true,true,true,false,true,false,true,true,true,false};
    uint256_from_bytes(a, a91_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a91_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a92_data[32]  = {0xc0,0xbd,0x1d,0x84,0x64,0x45,0x7e,0xa4,0x32,0x83,0x06,0x89,0x83,0x0a,0xe1,0x9e,0x14,0x3a,0x51,0x80,0x98,0x80,0xe8,0x8b,0xc8,0x41,0x72,0x1e,0xc8,0xa9,0x48,0x14};
    bool         a92_bits[256] = {false,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,true,false,false,true,false,true,false,true,false,false,false,true,false,false,true,true,false,true,true,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,false,false,false,false,true,false,false,false,false,true,false,false,true,true,true,true,false,true,false,false,false,true,false,false,false,true,false,true,true,true,false,false,false,false,false,false,false,true,false,false,false,true,true,false,false,true,false,false,false,false,false,false,false,true,true,false,false,false,true,false,true,false,false,true,false,true,true,true,false,false,false,false,true,false,true,false,false,false,false,true,true,true,true,false,false,true,true,false,false,false,false,true,true,true,false,true,false,true,false,false,false,false,true,true,false,false,false,false,false,true,true,false,false,true,false,false,false,true,false,true,true,false,false,false,false,false,true,true,false,false,false,false,false,true,false,true,false,false,true,true,false,false,false,false,true,false,false,true,false,true,false,true,true,true,true,true,true,false,true,false,true,false,false,false,true,false,false,false,true,false,false,true,true,false,false,false,true,false,false,false,false,true,true,false,true,true,true,false,false,false,true,false,true,true,true,true,false,true,false,false,false,false,false,false,true,true};
    uint256_from_bytes(a, a92_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a92_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a93_data[32]  = {0x8b,0x6b,0xfe,0xae,0x8d,0x76,0xd7,0xa1,0x7b,0x50,0x07,0x9e,0x08,0xab,0x4a,0xe4,0xa6,0x48,0xa5,0x8c,0x10,0x92,0x57,0xf7,0x68,0x62,0xbf,0x79,0x3f,0x4f,0x8b,0x9d};
    bool         a93_bits[256] = {true,false,true,true,true,false,false,true,true,true,false,true,false,false,false,true,true,true,true,true,false,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,true,true,true,false,true,true,true,true,true,true,false,true,false,true,false,false,false,true,true,false,false,false,false,true,false,true,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,false,true,false,false,true,false,false,true,false,false,true,false,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,true,false,true,false,false,true,false,true,false,false,false,true,false,false,true,false,false,true,true,false,false,true,false,true,false,false,true,false,false,true,true,true,false,true,false,true,false,false,true,false,true,true,false,true,false,true,false,true,false,false,false,true,false,false,false,false,false,true,true,true,true,false,false,true,true,true,true,false,false,false,false,false,false,false,false,false,true,false,true,false,true,true,false,true,true,true,true,false,true,false,false,false,false,true,false,true,true,true,true,false,true,false,true,true,false,true,true,false,true,true,true,false,true,false,true,true,false,false,false,true,false,true,true,true,false,true,false,true,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,true,false,false,false,true};
    uint256_from_bytes(a, a93_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a93_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a94_data[32]  = {0xf8,0xdc,0xa3,0x09,0xb5,0xb3,0x90,0x23,0xfd,0x09,0xe3,0x7c,0x7f,0x9c,0x13,0x21,0x6b,0xca,0x9b,0x3f,0x18,0xaf,0x26,0x6c,0x35,0x55,0xd6,0xae,0x15,0x86,0x6f,0xfb};
    bool         a94_bits[256] = {true,true,false,true,true,true,true,true,true,true,true,true,false,true,true,false,false,true,true,false,false,false,false,true,true,false,true,false,true,false,false,false,false,true,true,true,false,true,false,true,false,true,true,false,true,false,true,true,true,false,true,false,true,false,true,false,true,false,true,false,true,true,false,false,false,false,true,true,false,true,true,false,false,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,false,false,false,true,true,false,false,false,true,true,true,true,true,true,false,false,true,true,false,true,true,false,false,true,false,true,false,true,false,false,true,true,true,true,false,true,false,true,true,false,true,false,false,false,false,true,false,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,true,true,true,true,true,true,false,false,false,true,true,true,true,true,false,true,true,false,false,false,true,true,true,true,false,false,true,false,false,false,false,true,false,true,true,true,true,true,true,true,true,false,false,false,true,false,false,false,false,false,false,true,false,false,true,true,true,false,false,true,true,false,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false,false,false,true,true,false,false,false,true,false,true,false,false,true,true,true,false,true,true,false,false,false,true,true,true,true,true};
    uint256_from_bytes(a, a94_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a94_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a95_data[32]  = {0xac,0x92,0x61,0xf1,0xe4,0x29,0xc8,0x7c,0x9e,0xcc,0x7b,0x5f,0x75,0xff,0x19,0x9d,0x6a,0xb6,0x11,0x4f,0x22,0x07,0xc6,0xc0,0x3b,0xf4,0x49,0xfd,0x2c,0x56,0x4d,0x56};
    bool         a95_bits[256] = {false,true,true,false,true,false,true,false,true,false,true,true,false,false,true,false,false,true,true,false,true,false,true,false,false,false,true,true,false,true,false,false,true,false,true,true,true,true,true,true,true,false,false,true,false,false,true,false,false,false,true,false,true,true,true,true,true,true,false,true,true,true,false,false,false,false,false,false,false,false,true,true,false,true,true,false,false,false,true,true,true,true,true,false,false,false,false,false,false,true,false,false,false,true,false,false,true,true,true,true,false,false,true,false,true,false,false,false,true,false,false,false,false,true,true,false,true,true,false,true,false,true,false,true,false,true,true,false,true,false,true,true,true,false,false,true,true,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,true,false,true,true,true,true,true,false,true,false,true,true,false,true,true,true,true,false,false,false,true,true,false,false,true,true,false,true,true,true,true,false,false,true,false,false,true,true,true,true,true,false,false,false,false,true,false,false,true,true,true,false,false,true,false,true,false,false,false,false,true,false,false,true,true,true,true,false,false,false,true,true,true,true,true,false,false,false,false,true,true,false,false,true,false,false,true,false,false,true,false,false,true,true,false,true,false,true};
    uint256_from_bytes(a, a95_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a95_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a96_data[32]  = {0xbc,0xf1,0xfc,0xb5,0x41,0x09,0xd8,0xd6,0x5f,0x7b,0x07,0xb8,0x44,0x85,0xc0,0x4f,0x91,0x1f,0x52,0xdc,0x47,0x86,0x8e,0x4a,0x4b,0x35,0x4e,0x93,0x4b,0x3e,0x90,0xb7};
    bool         a96_bits[256] = {true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,true,false,true,true,true,true,true,false,false,true,true,false,true,false,false,true,false,true,true,false,false,true,false,false,true,false,true,true,true,false,false,true,false,true,false,true,false,true,true,false,false,true,true,false,true,false,false,true,false,false,true,false,true,false,false,true,false,false,true,true,true,false,false,false,true,false,true,true,false,false,false,false,true,true,true,true,false,false,false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true,true,false,false,false,true,false,false,false,true,false,false,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false,true,true,true,false,true,false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,false,true,true,true,false,true,true,true,true,false,false,false,false,false,true,true,false,true,true,true,true,false,true,true,true,true,true,false,true,false,false,true,true,false,true,false,true,true,false,false,false,true,true,false,true,true,true,false,false,true,false,false,false,false,true,false,false,false,false,false,true,false,true,false,true,false,true,true,false,true,false,false,true,true,true,true,true,true,true,false,false,false,true,true,true,true,false,false,true,true,true,true,false,true};
    uint256_from_bytes(a, a96_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a96_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a97_data[32]  = {0xfe,0x11,0x1e,0xbc,0x40,0x6c,0x61,0x32,0x65,0x64,0xd1,0x34,0x10,0x97,0x00,0x46,0x53,0x8a,0xe1,0xc1,0x30,0x31,0x29,0x32,0x94,0x0a,0x35,0x37,0xe8,0x56,0x64,0x31};
    bool         a97_bits[256] = {true,false,false,false,true,true,false,false,false,false,true,false,false,true,true,false,false,true,true,false,true,false,true,false,false,false,false,true,false,true,true,true,true,true,true,false,true,true,false,false,true,false,true,false,true,true,false,false,false,true,false,true,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,false,true,true,false,false,true,false,false,true,false,true,false,false,true,false,false,false,true,true,false,false,false,false,false,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,false,false,false,true,true,true,false,true,false,true,false,false,false,true,true,true,false,false,true,false,true,false,false,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,true,true,true,false,true,false,false,true,false,false,false,false,true,false,false,false,false,false,true,false,true,true,false,false,true,false,false,false,true,false,true,true,false,false,true,false,false,true,true,false,true,false,true,false,false,true,true,false,false,true,false,false,true,true,false,false,true,false,false,false,false,true,true,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,true,false,false,false,true,true,true,true,false,true,false,true,true,true,true,false,false,false,true,false,false,false,true,false,false,false,false,true,true,true,true,true,true,true};
    uint256_from_bytes(a, a97_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a97_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a98_data[32]  = {0xd7,0x2e,0xb3,0xa1,0x3b,0x2a,0x42,0x1a,0xd1,0xb0,0xb7,0x0b,0xe2,0x00,0xd2,0x18,0x79,0x8a,0x0d,0x59,0x01,0x26,0x64,0xf6,0x1a,0x32,0x75,0x37,0x09,0x7a,0x59,0x42};
    bool         a98_bits[256] = {false,true,false,false,false,false,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,false,true,false,false,true,false,false,false,false,true,true,true,false,true,true,false,false,true,false,true,false,true,true,true,false,false,true,false,false,true,true,false,false,false,true,false,true,true,false,false,false,false,true,true,false,true,true,true,true,false,false,true,false,false,true,true,false,false,true,true,false,false,true,false,false,true,false,false,false,false,false,false,false,true,false,false,true,true,false,true,false,true,false,true,true,false,false,false,false,false,true,false,true,false,false,false,true,true,false,false,true,true,true,true,false,false,false,false,true,true,false,false,false,false,true,false,false,true,false,true,true,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,true,true,false,true,false,false,false,false,true,true,true,false,true,true,false,true,false,false,false,false,true,true,false,true,true,false,false,false,true,false,true,true,false,true,false,true,true,false,false,false,false,true,false,false,false,false,true,false,false,true,false,true,false,true,false,false,true,true,false,true,true,true,false,false,true,false,false,false,false,true,false,true,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,false,true,true,true,false,true,false,true,true};
    uint256_from_bytes(a, a98_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a98_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
    std::uint8_t a99_data[32]  = {0x0c,0xe6,0x6f,0x73,0x1e,0x84,0xfb,0x36,0x3b,0x9e,0xda,0xcb,0x4b,0x2e,0x72,0x45,0xe0,0x7b,0x59,0xd8,0x0a,0x55,0x27,0xa2,0x5f,0xb6,0x5b,0x55,0xea,0x14,0x84,0x3a};
    bool         a99_bits[256] = {false,true,false,true,true,true,false,false,false,false,true,false,false,false,false,true,false,false,true,false,true,false,false,false,false,true,false,true,false,true,true,true,true,false,true,false,true,false,true,false,true,true,false,true,true,false,true,false,false,true,true,false,true,true,false,true,true,true,true,true,true,false,true,false,false,true,false,false,false,true,false,true,true,true,true,false,false,true,false,false,true,false,true,false,true,false,true,false,false,true,false,true,false,false,false,false,false,false,false,true,true,false,true,true,true,false,false,true,true,false,true,false,true,true,false,true,true,true,true,false,false,false,false,false,false,true,true,true,true,false,true,false,false,false,true,false,false,true,false,false,true,true,true,false,false,true,true,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,false,true,false,false,true,true,false,true,false,true,true,false,true,true,false,true,true,true,true,false,false,true,true,true,false,true,true,true,false,false,false,true,true,false,true,true,false,false,true,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,false,true,true,true,true,false,false,false,true,true,false,false,true,true,true,false,true,true,true,true,false,true,true,false,false,true,true,false,false,true,true,true,false,false,true,true,false,false,false,false};
    uint256_from_bytes(a, a99_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a99_bits[i])
        {
            throw std::runtime_error("err in uint256_bittest");
        }
    }
}
