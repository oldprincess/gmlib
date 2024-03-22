#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>

using namespace number::internal::common;

void test_uint256_common_bittest()
{
    uint256_t a;

    std::uint8_t a0_data[32]  = {0xb4,0x91,0x57,0x89,0x49,0x23,0x6b,0x9f,0xfe,0x2b,0xf6,0x76,0x3f,0x22,0xf4,0x7f,0x6b,0x25,0xed,0x38,0x9a,0x1e,0xfa,0x42,0x45,0xc1,0x39,0x57,0x0b,0x9c,0xc6,0x9f};
    bool         a0_bits[256] = {true,true,true,true,true,false,false,true,false,true,true,false,false,false,true,true,false,false,true,true,true,false,false,true,true,true,false,true,false,false,false,false,true,true,true,false,true,false,true,false,true,false,false,true,true,true,false,false,true,false,false,false,false,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,false,false,true,false,false,true,false,true,true,true,true,true,false,true,true,true,true,false,false,false,false,true,false,true,true,false,false,true,false,false,false,true,true,true,false,false,true,false,true,true,false,true,true,true,true,false,true,false,false,true,false,false,true,true,false,true,false,true,true,false,true,true,true,true,true,true,true,false,false,false,true,false,true,true,true,true,false,true,false,false,false,true,false,false,true,true,true,true,true,true,false,false,false,true,true,false,true,true,true,false,false,true,true,false,true,true,true,true,true,true,false,true,false,true,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,true,false,true,true,false,true,true,false,false,false,true,false,false,true,false,false,true,false,false,true,false,true,false,false,true,false,false,false,true,true,true,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,false,true,false,true,true,false,true};
    uint256_from_bytes(a, a0_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a0_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a1_data[32]  = {0x9e,0x49,0x5e,0x75,0xc4,0xc5,0x8b,0xb0,0x76,0x69,0x78,0x74,0x97,0xab,0x71,0x8f,0x92,0xae,0x45,0x13,0xaf,0x83,0x0d,0x4e,0x9d,0xde,0xec,0xb9,0x91,0x88,0x4f,0xef};
    bool         a1_bits[256] = {true,true,true,true,false,true,true,true,true,true,true,true,false,false,true,false,false,false,false,true,false,false,false,true,true,false,false,false,true,false,false,true,true,false,false,true,true,true,false,true,false,false,true,true,false,true,true,true,false,true,true,true,true,false,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,false,true,false,true,false,true,true,false,false,false,false,true,true,false,false,false,false,false,true,true,true,true,true,false,true,false,true,true,true,false,false,true,false,false,false,true,false,true,false,false,false,true,false,false,true,true,true,false,true,false,true,false,true,false,false,true,false,false,true,true,true,true,true,false,false,false,true,true,false,false,false,true,true,true,false,true,true,false,true,false,true,false,true,true,true,true,false,true,false,false,true,false,false,true,false,true,true,true,false,false,false,false,true,true,true,true,false,true,false,false,true,false,true,true,false,false,true,true,false,true,true,true,false,false,false,false,false,true,true,false,true,true,true,false,true,false,false,false,true,true,false,true,false,false,false,true,true,false,false,true,false,false,false,true,true,true,false,true,false,true,true,true,false,false,true,true,true,true,false,true,false,true,false,false,true,false,false,true,false,false,true,true,true,true,false,false,true};
    uint256_from_bytes(a, a1_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a1_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a2_data[32]  = {0x4d,0x75,0xa0,0xe1,0xd6,0x3a,0x7c,0x82,0x28,0xcd,0x98,0x1e,0x4e,0x76,0x71,0x3e,0x7f,0x8b,0x59,0xd6,0x21,0xc1,0x76,0x74,0xec,0x80,0x2d,0xcf,0x13,0x8e,0x20,0x26};
    bool         a2_bits[256] = {false,true,true,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,true,true,false,false,true,false,false,false,true,true,true,true,false,false,true,true,true,false,true,true,false,true,false,false,false,false,false,false,false,false,false,true,false,false,true,true,false,true,true,true,false,false,true,false,true,true,true,false,false,true,true,false,true,true,true,false,true,false,false,false,false,false,true,true,true,false,false,false,false,true,false,false,false,true,true,false,true,false,true,true,true,false,false,true,true,false,true,false,true,true,false,true,false,false,false,true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,false,false,true,false,false,false,true,true,true,false,false,true,true,false,true,true,true,false,false,true,true,true,false,false,true,false,false,true,true,true,true,false,false,false,false,false,false,true,true,false,false,true,true,false,true,true,false,false,true,true,false,false,false,true,false,true,false,false,false,true,false,false,false,false,false,true,false,false,true,true,true,true,true,false,false,true,false,true,true,true,false,false,false,true,true,false,true,false,true,true,true,false,false,false,false,true,true,true,false,false,false,false,false,true,false,true,true,false,true,false,true,true,true,false,true,false,true,true,false,false,true,false};
    uint256_from_bytes(a, a2_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a2_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a3_data[32]  = {0x58,0xfd,0x50,0xa7,0x53,0x89,0x6a,0xfb,0x7b,0xe7,0x12,0x93,0x85,0xee,0xc6,0x7c,0xd5,0xc6,0x37,0x4f,0x81,0xfd,0x45,0xad,0xf6,0xa0,0xdc,0x95,0x3f,0x14,0xac,0x74};
    bool         a3_bits[256] = {false,false,true,false,true,true,true,false,false,false,true,true,false,true,false,true,false,false,true,false,true,false,false,false,true,true,true,true,true,true,false,false,true,false,true,false,true,false,false,true,false,false,true,true,true,false,true,true,false,false,false,false,false,true,false,true,false,true,true,false,true,true,true,true,true,false,true,true,false,true,false,true,true,false,true,false,false,false,true,false,true,false,true,true,true,true,true,true,true,false,false,false,false,false,false,true,true,true,true,true,false,false,true,false,true,true,true,false,true,true,false,false,false,true,true,false,false,false,true,true,true,false,true,false,true,false,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,true,false,true,true,true,false,true,true,true,true,false,true,false,false,false,false,true,true,true,false,false,true,false,false,true,false,true,false,false,true,false,false,false,true,true,true,false,false,true,true,true,true,true,false,true,true,true,true,false,true,true,false,true,true,true,true,true,false,true,false,true,false,true,true,false,true,false,false,true,false,false,false,true,true,true,false,false,true,false,true,false,true,true,true,false,false,true,false,true,false,false,false,false,true,false,true,false,true,false,true,true,true,true,true,true,false,false,false,true,true,false,true,false};
    uint256_from_bytes(a, a3_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a3_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a4_data[32]  = {0xeb,0x3e,0xc3,0x86,0x99,0xe3,0x42,0xaf,0xea,0x8b,0xaf,0x13,0xeb,0xd2,0xb5,0xd0,0x95,0xbf,0x76,0xa4,0xc5,0xa0,0x53,0x5e,0x7f,0xc0,0x29,0x2d,0xb1,0x5c,0xc6,0xbd};
    bool         a4_bits[256] = {true,false,true,true,true,true,false,true,false,true,true,false,false,false,true,true,false,false,true,true,true,false,true,false,true,false,false,false,true,true,false,true,true,false,true,true,false,true,false,false,true,false,false,true,false,true,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,false,false,true,true,true,true,false,true,false,true,true,false,false,true,false,true,false,false,false,false,false,false,true,false,true,true,false,true,false,false,false,true,true,false,false,true,false,false,true,false,true,false,true,true,false,true,true,true,false,true,true,true,true,true,true,false,true,true,false,true,false,true,false,false,true,false,false,false,false,true,false,true,true,true,false,true,false,true,true,false,true,false,true,false,false,true,false,true,true,true,true,false,true,false,true,true,true,true,true,false,false,true,false,false,false,true,true,true,true,false,true,false,true,true,true,false,true,false,false,false,true,false,true,false,true,false,true,true,true,true,true,true,true,false,true,false,true,false,true,false,false,false,false,true,false,true,true,false,false,false,true,true,true,true,false,false,true,true,false,false,true,false,true,true,false,false,false,false,true,true,true,false,false,false,false,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,true,true};
    uint256_from_bytes(a, a4_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a4_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a5_data[32]  = {0xa7,0x6c,0x2a,0x35,0xb5,0x53,0x79,0xa5,0x5b,0x8a,0xe6,0xbb,0xe8,0x75,0xc8,0x67,0x4e,0x51,0xc9,0x1c,0x50,0x4c,0xf5,0x52,0xb2,0x7b,0xc5,0x9f,0xe6,0x6d,0x7e,0x38};
    bool         a5_bits[256] = {false,false,false,true,true,true,false,false,false,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,false,true,true,false,false,true,true,true,true,true,true,true,true,false,false,true,true,false,true,false,false,false,true,true,true,true,false,true,true,true,true,false,false,true,false,false,true,true,false,true,false,true,false,false,true,false,true,false,true,false,true,false,true,true,true,true,false,false,true,true,false,false,true,false,false,false,false,false,true,false,true,false,false,false,true,true,true,false,false,false,true,false,false,true,false,false,true,true,true,false,false,false,true,false,true,false,false,true,true,true,false,false,true,false,true,true,true,false,false,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,true,true,true,false,false,false,false,true,false,true,true,true,true,true,false,true,true,true,false,true,false,true,true,false,false,true,true,true,false,true,false,true,false,false,false,true,true,true,false,true,true,false,true,false,true,false,true,false,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,false,true,false,true,false,true,false,true,false,true,true,false,true,true,false,true,false,true,true,false,false,false,true,false,true,false,true,false,false,false,false,true,true,false,true,true,false,true,true,true,false,false,true,false,true};
    uint256_from_bytes(a, a5_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a5_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a6_data[32]  = {0x35,0x07,0x97,0x4b,0x51,0x49,0x81,0xe9,0x6e,0x0d,0x8f,0x3d,0x88,0xa6,0x84,0x25,0xcc,0xce,0x86,0xb6,0x16,0x0b,0x6f,0xb6,0x8d,0x41,0x0e,0x5d,0x2a,0x6f,0xa5,0x17};
    bool         a6_bits[256] = {true,true,true,false,true,false,false,false,true,false,true,false,false,true,false,true,true,true,true,true,false,true,true,false,false,true,false,true,false,true,false,false,true,false,true,true,true,false,true,false,false,true,true,true,false,false,false,false,true,false,false,false,false,false,true,false,true,false,true,true,false,false,false,true,false,true,true,false,true,true,false,true,true,true,true,true,false,true,true,false,true,true,false,true,false,false,false,false,false,true,true,false,true,false,false,false,false,true,true,false,true,true,false,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,true,false,false,true,true,false,false,true,true,true,false,true,false,false,true,false,false,false,false,true,false,false,false,false,true,false,true,true,false,false,true,false,true,false,false,false,true,false,false,false,true,true,false,true,true,true,true,false,false,true,true,true,true,false,false,false,true,true,false,true,true,false,false,false,false,false,true,true,true,false,true,true,false,true,false,false,true,false,true,true,true,true,false,false,false,false,false,false,true,true,false,false,true,false,false,true,false,true,false,false,false,true,false,true,false,true,true,false,true,false,false,true,false,true,true,true,false,true,false,false,true,true,true,true,false,false,false,false,false,true,false,true,false,true,true,false,false};
    uint256_from_bytes(a, a6_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a6_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a7_data[32]  = {0x08,0xba,0x4f,0x64,0x02,0xe7,0xf1,0x3b,0x2b,0x63,0xe9,0xb6,0x13,0xbb,0x5b,0x25,0x59,0xa3,0x2c,0xdf,0x01,0x4c,0x89,0xe2,0x68,0x1d,0x7f,0x9f,0x9e,0x1a,0x6d,0xab};
    bool         a7_bits[256] = {true,true,false,true,false,true,false,true,true,false,true,true,false,true,true,false,false,true,false,true,true,false,false,false,false,true,true,true,true,false,false,true,true,true,true,true,true,false,false,true,true,true,true,true,true,true,true,false,true,false,true,true,true,false,false,false,false,false,false,true,false,true,true,false,false,true,false,false,false,true,true,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,true,false,true,false,false,false,false,false,false,false,true,true,true,true,true,false,true,true,false,false,true,true,false,true,false,false,true,true,false,false,false,true,false,true,true,false,false,true,true,false,true,false,true,false,true,false,false,true,false,false,true,true,false,true,true,false,true,false,true,true,false,true,true,true,false,true,true,true,false,false,true,false,false,false,false,true,true,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,false,false,false,true,true,false,true,true,false,true,false,true,false,false,true,true,false,true,true,true,false,false,true,false,false,false,true,true,true,true,true,true,true,false,false,true,true,true,false,true,false,false,false,false,false,false,false,false,true,false,false,true,true,false,true,true,true,true,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,false,false,false,false};
    uint256_from_bytes(a, a7_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a7_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a8_data[32]  = {0xdf,0x4d,0x8a,0xa6,0x69,0x81,0x7c,0x31,0x7b,0x59,0xbe,0x78,0x99,0x4b,0xf7,0xad,0xdc,0x92,0xd1,0xcb,0xc8,0x84,0x1d,0x79,0x31,0x8b,0x65,0x71,0x88,0xdd,0x56,0x1d};
    bool         a8_bits[256] = {true,false,true,true,true,false,false,false,false,true,true,false,true,false,true,false,true,false,true,true,true,false,true,true,false,false,false,true,false,false,false,true,true,false,false,false,true,true,true,false,true,false,true,false,false,true,true,false,true,true,false,true,false,false,false,true,true,false,false,false,true,true,false,false,true,false,false,true,true,true,true,false,true,false,true,true,true,false,false,false,false,false,true,false,false,false,false,true,false,false,false,true,false,false,true,true,true,true,false,true,false,false,true,true,true,false,false,false,true,false,true,true,false,true,false,false,true,false,false,true,false,false,true,true,true,false,true,true,true,false,true,true,false,true,false,true,true,true,true,false,true,true,true,true,true,true,false,true,false,false,true,false,true,false,false,true,true,false,false,true,false,false,false,true,true,true,true,false,false,true,true,true,true,true,false,true,true,false,false,true,true,false,true,false,true,true,false,true,true,true,true,false,true,false,false,false,true,true,false,false,false,false,true,true,true,true,true,false,true,false,false,false,false,false,false,true,true,false,false,true,false,true,true,false,false,true,true,false,false,true,false,true,false,true,false,true,false,false,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,false,true,true};
    uint256_from_bytes(a, a8_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a8_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a9_data[32]  = {0x81,0x29,0x4a,0x23,0xdf,0xf8,0x1d,0x94,0x14,0xe4,0x98,0x85,0xcb,0x5e,0x1c,0xa4,0x27,0x12,0xd5,0xc0,0x98,0x6a,0x01,0xae,0x83,0x1d,0x22,0xcf,0xd1,0x8b,0x43,0x51};
    bool         a9_bits[256] = {true,false,false,false,true,false,true,false,true,true,false,false,false,false,true,false,true,true,false,true,false,false,false,true,true,false,false,false,true,false,true,true,true,true,true,true,false,false,true,true,false,true,false,false,false,true,false,false,true,false,true,true,true,false,false,false,true,true,false,false,false,false,false,true,false,true,true,true,false,true,false,true,true,false,false,false,false,false,false,false,false,true,false,true,false,true,true,false,false,false,false,true,true,false,false,true,false,false,false,false,false,false,true,true,true,false,true,false,true,false,true,true,false,true,false,false,true,false,false,false,true,true,true,false,false,true,false,false,false,false,true,false,false,true,false,true,false,false,true,true,true,false,false,false,false,true,true,true,true,false,true,false,true,true,false,true,false,false,true,true,true,false,true,false,false,false,false,true,false,false,false,true,true,false,false,true,false,false,true,false,false,true,true,true,false,false,true,false,true,false,false,false,false,false,true,false,true,false,false,true,true,false,true,true,true,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,false,false,false,true,false,false,false,true,false,true,false,false,true,false,true,false,false,true,false,true,false,false,true,false,false,false,false,false,false,true};
    uint256_from_bytes(a, a9_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a9_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a10_data[32]  = {0x06,0xb9,0x54,0xf8,0x21,0x20,0xaf,0x6e,0xe9,0x1d,0xb0,0x04,0xc5,0x2e,0x06,0x70,0x8c,0x6a,0xa5,0xf5,0x44,0xc5,0x65,0x57,0xfe,0xcc,0x88,0xf1,0x97,0x0a,0x3f,0x83};
    bool         a10_bits[256] = {true,true,false,false,false,false,false,true,true,true,true,true,true,true,false,false,false,true,false,true,false,false,false,false,true,true,true,false,true,false,false,true,true,false,false,false,true,true,true,true,false,false,false,true,false,false,false,true,false,false,true,true,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,false,true,false,true,false,true,false,true,false,false,true,true,false,true,false,true,false,false,false,true,true,false,false,true,false,false,false,true,false,true,false,true,false,true,true,true,true,true,false,true,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,true,true,false,false,false,true,false,false,false,false,true,true,true,false,false,true,true,false,false,false,false,false,false,true,true,true,false,true,false,false,true,false,true,false,false,false,true,true,false,false,true,false,false,false,false,false,false,false,false,false,true,true,false,true,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,false,true,false,false,false,false,false,true,false,false,true,false,false,false,false,true,false,false,false,false,false,true,true,true,true,true,false,false,true,false,true,false,true,false,true,false,false,true,true,true,false,true,false,true,true,false,false,false,false,false};
    uint256_from_bytes(a, a10_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a10_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a11_data[32]  = {0x98,0x1e,0xe9,0xdd,0x7e,0x1a,0x01,0xb7,0x40,0x86,0x90,0x99,0x03,0x96,0x9d,0xff,0x2a,0x7f,0x5b,0x8d,0xc9,0x13,0x3a,0x24,0xfa,0xc3,0xef,0x98,0xf5,0x07,0x7f,0x0d};
    bool         a11_bits[256] = {true,false,true,true,false,false,false,false,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,false,true,false,true,false,true,true,true,true,false,false,false,true,true,false,false,true,true,true,true,true,false,true,true,true,true,true,false,false,false,false,true,true,false,true,false,true,true,true,true,true,false,false,true,false,false,true,false,false,false,true,false,true,true,true,false,false,true,true,false,false,true,false,false,false,true,false,false,true,false,false,true,true,true,false,true,true,false,false,false,true,true,true,false,true,true,false,true,false,true,true,true,true,true,true,true,false,false,true,false,true,false,true,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,false,false,true,false,true,true,false,true,false,false,true,true,true,false,false,false,false,false,false,true,false,false,true,true,false,false,true,false,false,false,false,true,false,false,true,false,true,true,false,false,false,false,true,false,false,false,false,false,false,true,false,true,true,true,false,true,true,false,true,true,false,false,false,false,false,false,false,false,true,false,true,true,false,false,false,false,true,true,true,true,true,true,false,true,false,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,true,true,true,true,false,false,false,false,false,false,true,true,false,false,true};
    uint256_from_bytes(a, a11_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a11_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a12_data[32]  = {0xf6,0xd3,0xcc,0x44,0x98,0xfa,0x2a,0x90,0x4d,0xd8,0x6f,0x20,0x27,0x45,0x61,0x7e,0x31,0x26,0x27,0x2b,0x57,0x41,0x31,0x0f,0x30,0xb7,0x5f,0x6f,0xbc,0xf3,0xcf,0x86};
    bool         a12_bits[256] = {false,true,true,false,false,false,false,true,true,true,true,true,false,false,true,true,true,true,false,false,true,true,true,true,false,false,true,true,true,true,false,true,true,true,true,true,false,true,true,false,true,true,true,true,true,false,true,false,true,true,true,false,true,true,false,true,false,false,false,false,true,true,false,false,true,true,true,true,false,false,false,false,true,false,false,false,true,true,false,false,true,false,false,false,false,false,true,false,true,true,true,false,true,false,true,false,true,true,false,true,false,true,false,false,true,true,true,false,false,true,false,false,false,true,true,false,false,true,false,false,true,false,false,false,true,true,false,false,false,true,true,true,true,true,true,false,true,false,false,false,false,true,true,false,true,false,true,false,false,false,true,false,true,true,true,false,false,true,false,false,false,false,false,false,false,true,false,false,true,true,true,true,false,true,true,false,false,false,false,true,true,false,true,true,true,false,true,true,false,false,true,false,false,false,false,false,true,false,false,true,false,true,false,true,false,true,false,false,false,true,false,true,true,true,true,true,false,false,false,true,true,false,false,true,false,false,true,false,false,false,true,false,false,false,true,true,false,false,true,true,true,true,false,false,true,false,true,true,false,true,true,false,true,true,true,true};
    uint256_from_bytes(a, a12_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a12_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a13_data[32]  = {0x26,0xd6,0x35,0x34,0x51,0x17,0x2a,0x09,0xc5,0xd0,0x12,0x4f,0x7c,0x94,0xb9,0x61,0x54,0x7c,0x9b,0x23,0xd7,0xf6,0x8d,0x88,0x01,0x56,0xbd,0x94,0x5f,0xb3,0x1f,0x93};
    bool         a13_bits[256] = {true,true,false,false,true,false,false,true,true,true,true,true,true,false,false,false,true,true,false,false,true,true,false,true,true,true,true,true,true,false,true,false,false,false,true,false,true,false,false,true,true,false,true,true,true,true,false,true,false,true,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,false,false,false,true,false,true,true,false,true,true,true,true,true,true,true,false,true,false,true,true,true,true,false,false,false,true,false,false,true,true,false,true,true,false,false,true,false,false,true,true,true,true,true,false,false,false,true,false,true,false,true,false,true,false,false,false,false,true,true,false,true,false,false,true,true,true,false,true,false,false,true,false,true,false,false,true,false,false,true,true,true,true,true,false,true,true,true,true,false,false,true,false,false,true,false,false,true,false,false,false,false,false,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,false,false,true,false,false,false,false,false,true,false,true,false,true,false,false,true,true,true,false,true,false,false,false,true,false,false,false,true,false,true,false,false,false,true,false,true,true,false,false,true,false,true,false,true,true,false,false,false,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false};
    uint256_from_bytes(a, a13_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a13_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a14_data[32]  = {0xfa,0xc0,0x03,0xbb,0x84,0xb9,0x5d,0x47,0xc7,0x13,0x51,0xb2,0xa2,0xc7,0xd2,0xb1,0x5f,0x5c,0x59,0xc1,0x12,0xeb,0xdd,0x9b,0xdc,0x3b,0x3b,0x83,0xc4,0x53,0xd3,0x6a};
    bool         a14_bits[256] = {false,true,false,true,false,true,true,false,true,true,false,false,true,false,true,true,true,true,false,false,true,false,true,false,false,false,true,false,false,false,true,true,true,true,false,false,false,false,false,true,true,true,false,true,true,true,false,false,true,true,false,true,true,true,false,false,false,false,true,true,true,false,true,true,true,true,false,true,true,false,false,true,true,false,true,true,true,false,true,true,true,true,false,true,false,true,true,true,false,true,false,false,true,false,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,false,true,false,false,false,true,true,true,false,true,false,true,true,true,true,true,false,true,false,true,false,false,false,true,true,false,true,false,true,false,false,true,false,true,true,true,true,true,false,false,false,true,true,false,true,false,false,false,true,false,true,false,true,false,false,true,true,false,true,true,false,false,false,true,false,true,false,true,true,false,false,true,false,false,false,true,true,true,false,false,false,true,true,true,true,true,false,false,false,true,false,true,false,true,true,true,false,true,false,true,false,false,true,true,true,false,true,false,false,true,false,false,false,false,true,true,true,false,true,true,true,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,false,true,true,true,true,true};
    uint256_from_bytes(a, a14_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a14_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a15_data[32]  = {0x23,0x83,0x89,0xa1,0x97,0x1a,0xa1,0xb4,0x7e,0xf5,0x5d,0xf2,0x5e,0xe4,0xc3,0x60,0xb1,0xdd,0x70,0xed,0x19,0xb2,0xe2,0xb4,0x9c,0xe0,0x21,0x47,0x72,0x95,0xd1,0x7c};
    bool         a15_bits[256] = {false,false,true,true,true,true,true,false,true,false,false,false,true,false,true,true,true,false,true,false,true,false,false,true,false,true,false,false,true,true,true,false,true,true,true,false,false,false,true,false,true,false,false,false,false,true,false,false,false,false,false,false,false,true,true,true,false,false,true,true,true,false,false,true,false,false,true,false,true,true,false,true,false,true,false,false,false,true,true,true,false,true,false,false,true,true,false,true,true,false,false,true,true,false,false,false,true,false,true,true,false,true,true,true,false,false,false,false,true,true,true,false,true,false,true,true,true,false,true,true,true,false,false,false,true,true,false,true,false,false,false,false,false,true,true,false,true,true,false,false,false,false,true,true,false,false,true,false,false,true,true,true,false,true,true,true,true,false,true,false,false,true,false,false,true,true,true,true,true,false,true,true,true,false,true,false,true,false,true,false,true,true,true,true,false,true,true,true,true,true,true,false,false,false,true,false,true,true,false,true,true,false,false,false,false,true,false,true,false,true,false,true,true,false,false,false,true,true,true,false,true,false,false,true,true,false,false,false,false,true,false,true,true,false,false,true,false,false,false,true,true,true,false,false,false,false,false,true,true,true,false,false,false,true,false,false};
    uint256_from_bytes(a, a15_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a15_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a16_data[32]  = {0x5b,0x62,0x46,0x08,0x70,0x2e,0x9d,0xcd,0x63,0x9c,0x71,0xc6,0x4c,0x91,0x5d,0x69,0x7a,0xaf,0x9d,0x73,0x9c,0x2f,0x5d,0x06,0x94,0xd1,0x45,0x94,0x40,0x46,0x92,0x56};
    bool         a16_bits[256] = {false,true,true,false,true,false,true,false,false,true,false,false,true,false,false,true,false,true,true,false,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,false,true,false,false,true,true,false,true,false,false,false,true,false,true,false,false,false,true,false,true,true,false,false,true,false,true,false,false,true,false,true,true,false,false,false,false,false,true,false,true,true,true,false,true,false,true,true,true,true,false,true,false,false,false,false,true,true,true,false,false,true,true,true,false,false,true,true,true,false,true,false,true,true,true,false,false,true,true,true,true,true,false,true,false,true,false,true,false,true,true,true,true,false,true,false,false,true,false,true,true,false,true,false,true,true,true,false,true,false,true,false,false,false,true,false,false,true,false,false,true,true,false,false,true,false,false,true,true,false,false,false,true,true,true,false,false,false,true,true,true,false,false,false,true,true,true,false,false,true,true,true,false,false,false,true,true,false,true,false,true,true,false,false,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,true,false,false,false,false,false,false,true,true,true,false,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,false,false,true,false,false,false,true,true,false,true,true,false,true,true,false,true,false};
    uint256_from_bytes(a, a16_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a16_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a17_data[32]  = {0x29,0x1f,0x30,0x5d,0xd2,0xb8,0xc2,0xe9,0x3e,0x5d,0x16,0x50,0x34,0x8c,0x25,0xd6,0xde,0x7c,0xcb,0xaa,0x9c,0xca,0x90,0x1e,0x10,0x85,0x90,0x33,0xe5,0xb2,0xc7,0x42};
    bool         a17_bits[256] = {false,true,false,false,false,false,true,false,true,true,true,false,false,false,true,true,false,true,false,false,true,true,false,true,true,false,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,false,false,false,true,false,false,true,true,false,true,false,false,false,false,true,false,false,false,false,true,false,false,false,false,true,true,true,true,false,false,false,false,false,false,false,true,false,false,true,false,true,false,true,false,false,true,true,false,false,true,true,true,false,false,true,false,true,false,true,false,true,false,true,true,true,false,true,false,false,true,true,false,false,true,true,true,true,true,false,false,true,true,true,true,false,true,true,false,true,true,false,true,false,true,true,true,false,true,false,false,true,false,false,false,false,true,true,false,false,false,true,false,false,true,false,true,true,false,false,false,false,false,false,true,false,true,false,false,true,true,false,true,false,false,false,true,false,true,true,true,false,true,false,false,true,true,true,true,true,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,false,true,true,false,false,false,true,true,true,false,true,false,true,false,false,true,false,true,true,true,false,true,true,true,false,true,false,false,false,false,false,true,true,false,false,true,true,true,true,true,false,false,false,true,false,false,true,false,true,false,false};
    uint256_from_bytes(a, a17_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a17_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a18_data[32]  = {0x31,0xdb,0xc5,0xe0,0xc7,0x85,0x79,0x03,0x79,0xbf,0xf3,0x7e,0x45,0xd0,0x00,0x04,0xe8,0x61,0x20,0x9b,0x9b,0xe6,0xc1,0x19,0x44,0x4d,0x0a,0x9b,0x1f,0x0e,0xe0,0xb6};
    bool         a18_bits[256] = {false,true,true,false,true,true,false,true,false,false,false,false,false,true,true,true,false,true,true,true,false,false,false,false,true,true,true,true,true,false,false,false,true,true,false,true,true,false,false,true,false,true,false,true,false,false,false,false,true,false,true,true,false,false,true,false,false,false,true,false,false,false,true,false,true,false,false,true,true,false,false,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,true,true,true,true,false,true,true,false,false,true,true,true,false,true,true,false,false,true,false,false,false,false,false,true,false,false,true,false,false,false,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,false,true,false,false,false,true,false,false,true,true,true,true,true,true,false,true,true,false,false,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,false,false,false,false,false,true,false,false,true,true,true,true,false,true,false,true,false,false,false,false,true,true,true,true,false,false,false,true,true,false,false,false,false,false,true,true,true,true,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,false,false,true,true,false,false};
    uint256_from_bytes(a, a18_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a18_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a19_data[32]  = {0x97,0xfa,0x1d,0x89,0xe0,0xf8,0xef,0x48,0x59,0x94,0x55,0x63,0x52,0xe6,0xfa,0xd2,0xab,0x59,0x43,0x1c,0x55,0xd3,0xf6,0x64,0x33,0x06,0xab,0x70,0x78,0x65,0x4a,0x3b};
    bool         a19_bits[256] = {true,true,false,true,true,true,false,false,false,true,false,true,false,false,true,false,true,false,true,false,false,true,true,false,false,false,false,true,true,true,true,false,false,false,false,false,true,true,true,false,true,true,false,true,false,true,false,true,false,true,true,false,false,false,false,false,true,true,false,false,true,true,false,false,false,false,true,false,false,true,true,false,false,true,true,false,true,true,true,true,true,true,false,false,true,false,true,true,true,false,true,false,true,false,true,false,false,false,true,true,true,false,false,false,true,true,false,false,false,false,true,false,true,false,false,true,true,false,true,false,true,true,false,true,false,true,false,true,false,true,false,false,true,false,true,true,false,true,false,true,true,true,true,true,false,true,true,false,false,true,true,true,false,true,false,false,true,false,true,false,true,true,false,false,false,true,true,false,true,false,true,false,true,false,true,false,false,false,true,false,true,false,false,true,true,false,false,true,true,false,true,false,false,false,false,true,false,false,true,false,true,true,true,true,false,true,true,true,false,false,false,true,true,true,true,true,false,false,false,false,false,true,true,true,true,false,false,true,false,false,false,true,true,false,true,true,true,false,false,false,false,true,false,true,true,true,true,true,true,true,true,false,true,false,false,true};
    uint256_from_bytes(a, a19_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a19_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a20_data[32]  = {0x97,0x23,0xc6,0x70,0xfb,0xa7,0x59,0x88,0x66,0x47,0x3e,0x65,0xd8,0xcd,0x50,0x15,0xf5,0xd9,0xf7,0x4e,0xa4,0xeb,0x74,0x1d,0x4c,0x25,0xf1,0xf3,0xab,0x05,0xb8,0x9f};
    bool         a20_bits[256] = {true,true,true,true,true,false,false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,false,false,true,true,false,true,false,true,false,true,true,true,false,false,true,true,true,true,true,false,false,false,true,true,true,true,true,false,true,false,false,true,false,false,false,false,true,true,false,false,true,false,true,false,true,true,true,false,false,false,false,false,true,false,true,true,true,false,true,true,false,true,false,true,true,true,false,false,true,false,false,true,false,true,false,true,true,true,false,false,true,false,true,true,true,false,true,true,true,true,true,false,false,true,true,false,true,true,true,false,true,false,true,true,true,true,true,false,true,false,true,false,false,false,false,false,false,false,true,false,true,false,true,false,true,true,false,false,true,true,false,false,false,true,true,false,true,true,true,false,true,false,false,true,true,false,false,true,true,true,true,true,false,false,true,true,true,false,false,false,true,false,false,true,true,false,false,true,true,false,false,false,false,true,false,false,false,true,true,false,false,true,true,false,true,false,true,true,true,false,false,true,false,true,true,true,false,true,true,true,true,true,false,false,false,false,true,true,true,false,false,true,true,false,false,false,true,true,true,true,false,false,false,true,false,false,true,true,true,false,true,false,false,true};
    uint256_from_bytes(a, a20_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a20_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a21_data[32]  = {0x66,0x7c,0x00,0x89,0x2e,0x01,0x7c,0x7a,0x53,0xb4,0xd4,0xa1,0xce,0x34,0xa4,0xb2,0x12,0xaa,0xe0,0x1a,0x22,0x72,0x9e,0x40,0xe4,0x18,0xf0,0x1d,0x96,0xc7,0xb1,0x8e};
    bool         a21_bits[256] = {false,true,true,true,false,false,false,true,true,false,false,false,true,true,false,true,true,true,true,false,false,false,true,true,false,true,true,false,true,false,false,true,true,false,true,true,true,false,false,false,false,false,false,false,true,true,true,true,false,false,false,true,true,false,false,false,false,false,true,false,false,true,true,true,false,false,false,false,false,false,true,false,false,true,true,true,true,false,false,true,false,true,false,false,true,true,true,false,false,true,false,false,false,true,false,false,false,true,false,true,true,false,false,false,false,false,false,false,false,true,true,true,false,true,false,true,false,true,false,true,false,true,false,false,true,false,false,false,false,true,false,false,true,true,false,true,false,false,true,false,false,true,false,true,false,false,true,false,true,true,false,false,false,true,true,true,false,false,true,true,true,false,false,false,false,true,false,true,false,false,true,false,true,false,true,true,false,false,true,false,true,true,false,true,true,true,false,false,true,false,true,false,false,true,false,true,true,true,true,false,false,false,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,true,true,true,false,true,false,false,true,false,false,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,false,false,true,true,false,false,true,true,false};
    uint256_from_bytes(a, a21_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a21_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a22_data[32]  = {0x02,0xc6,0x52,0xb1,0x42,0xea,0x6a,0x57,0x55,0x49,0x20,0x51,0x9a,0xf3,0x53,0x7d,0xa7,0x93,0x9d,0xa8,0xf4,0xb0,0x05,0x9c,0xb9,0x2b,0x07,0x2d,0x45,0x0d,0x10,0xb7};
    bool         a22_bits[256] = {true,true,true,false,true,true,false,true,false,false,false,false,true,false,false,false,true,false,true,true,false,false,false,false,true,false,true,false,false,false,true,false,true,false,true,true,false,true,false,false,true,true,true,false,false,false,false,false,true,true,false,true,false,true,false,false,true,false,false,true,true,true,false,true,false,false,true,true,true,false,false,true,true,false,true,false,false,false,false,false,false,false,false,false,true,true,false,true,false,false,true,false,true,true,true,true,false,false,false,true,false,true,false,true,true,false,true,true,true,false,false,true,true,true,false,false,true,false,false,true,true,true,true,false,false,true,false,true,true,false,true,true,true,true,true,false,true,true,false,false,true,false,true,false,true,true,false,false,true,true,true,true,false,true,false,true,true,false,false,true,true,false,false,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,false,true,false,false,true,false,true,false,true,false,true,false,true,false,true,true,true,false,true,false,true,false,false,true,false,true,false,true,true,false,false,true,false,true,false,true,true,true,false,true,false,false,false,false,true,false,true,false,false,false,true,true,false,true,false,true,false,false,true,false,true,false,false,true,true,false,false,false,true,true,false,true,false,false,false,false,false,false};
    uint256_from_bytes(a, a22_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a22_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a23_data[32]  = {0x6b,0x4a,0xe9,0x4e,0xf0,0x58,0x25,0x7e,0x5e,0xca,0x80,0x70,0x53,0x88,0xdd,0xac,0x9b,0x5f,0xf0,0x27,0x2e,0x61,0x19,0x22,0x07,0x9e,0x66,0xa3,0x97,0x99,0xb9,0xd6};
    bool         a23_bits[256] = {false,true,true,false,true,false,true,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false,false,true,true,true,true,false,true,false,false,true,true,true,false,false,false,true,false,true,false,true,true,false,false,true,true,false,false,true,true,true,true,false,false,true,true,true,true,false,false,false,false,false,false,true,false,false,false,true,false,false,true,false,false,true,true,false,false,false,true,false,false,false,false,true,true,false,false,true,true,true,false,true,false,false,true,true,true,false,false,true,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false,true,true,false,true,false,true,true,false,true,true,true,false,true,true,false,false,false,true,false,false,false,true,true,true,false,false,true,false,true,false,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,true,false,true,false,true,false,false,true,true,false,true,true,true,true,false,true,false,false,true,true,true,true,true,true,false,true,false,true,false,false,true,false,false,false,false,false,true,true,false,true,false,false,false,false,false,true,true,true,true,false,true,true,true,false,false,true,false,true,false,false,true,false,true,true,true,false,true,false,true,false,false,true,false,true,true,false,true,false,true,true,false};
    uint256_from_bytes(a, a23_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a23_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a24_data[32]  = {0x2c,0x6b,0x2f,0x04,0xcb,0x5a,0xff,0x1c,0x9b,0x9a,0x4f,0x2a,0xfc,0x16,0x74,0x6f,0xbe,0xa8,0x61,0xbe,0xf1,0xf6,0x0c,0x02,0xa9,0x91,0xa6,0x11,0x1c,0x9b,0x90,0xf8};
    bool         a24_bits[256] = {false,false,false,true,true,true,true,true,false,false,false,false,true,false,false,true,true,true,false,true,true,false,false,true,false,false,true,true,true,false,false,false,true,false,false,false,true,false,false,false,false,true,true,false,false,true,false,true,true,false,false,false,true,false,false,true,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,true,false,false,false,false,false,true,true,false,true,true,true,true,true,false,false,false,true,true,true,true,false,true,true,true,true,true,false,true,true,false,false,false,false,true,true,false,false,false,false,true,false,true,false,true,false,true,true,true,true,true,false,true,true,true,true,true,false,true,true,false,false,false,true,false,true,true,true,false,false,true,true,false,true,false,false,false,false,false,true,true,true,true,true,true,false,true,false,true,false,true,false,false,true,true,true,true,false,false,true,false,false,true,false,true,true,false,false,true,true,true,false,true,true,false,false,true,false,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,false,true,true,false,true,false,false,true,true,false,false,true,false,false,false,false,false,true,true,true,true,false,true,false,false,true,true,false,true,false,true,true,false,false,false,true,true,false,true,false,false};
    uint256_from_bytes(a, a24_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a24_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a25_data[32]  = {0xcb,0x28,0x7d,0x26,0x64,0xe6,0x21,0xe7,0x65,0x69,0xf7,0xa1,0xe4,0xe3,0x7a,0x23,0x9d,0x4a,0xa9,0x5a,0xff,0x1d,0x31,0x1d,0xdb,0x96,0x59,0xd9,0x25,0xf3,0x4a,0x90};
    bool         a25_bits[256] = {false,false,false,false,true,false,false,true,false,true,false,true,false,false,true,false,true,true,false,false,true,true,true,true,true,false,true,false,false,true,false,false,true,false,false,true,true,false,true,true,true,false,false,true,true,false,true,false,false,true,true,false,true,false,false,true,true,true,false,true,true,false,true,true,true,false,true,true,true,false,false,false,true,false,false,false,true,true,false,false,true,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,false,true,false,false,true,false,true,false,true,false,true,false,true,false,false,true,false,true,false,true,true,true,false,false,true,true,true,false,false,false,true,false,false,false,true,false,true,true,true,true,false,true,true,false,false,false,true,true,true,false,false,true,false,false,true,true,true,true,false,false,false,false,true,false,true,true,true,true,false,true,true,true,true,true,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,true,true,true,false,false,true,true,true,true,false,false,false,false,true,false,false,false,true,true,false,false,true,true,true,false,false,true,false,false,true,true,false,false,true,true,false,false,true,false,false,true,false,true,true,true,true,true,false,false,false,false,true,false,true,false,false,true,true,false,true,false,false,true,true};
    uint256_from_bytes(a, a25_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a25_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a26_data[32]  = {0x05,0xe0,0xfe,0x6f,0xae,0x58,0x2c,0x4e,0xf4,0xbb,0x77,0x13,0x9b,0x9e,0x09,0x6b,0xad,0xdc,0x61,0x87,0xab,0xc3,0x8a,0xbc,0x65,0x23,0xc7,0x71,0xb5,0x94,0x53,0x11};
    bool         a26_bits[256] = {true,false,false,false,true,false,false,false,true,true,false,false,true,false,true,false,false,false,true,false,true,false,false,true,true,false,true,false,true,true,false,true,true,false,false,false,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,false,false,true,true,true,true,false,true,false,true,false,true,false,false,false,true,true,true,false,false,false,false,true,true,true,true,false,true,false,true,false,true,true,true,true,false,false,false,false,true,true,false,false,false,false,true,true,false,false,false,true,true,true,false,true,true,true,false,true,true,false,true,false,true,true,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,false,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,true,true,false,false,true,false,false,false,true,true,true,false,true,true,true,false,true,true,false,true,true,true,false,true,false,false,true,false,true,true,true,true,false,true,true,true,false,false,true,false,false,false,true,true,false,true,false,false,false,false,false,true,true,false,true,false,false,true,true,true,false,true,false,true,true,true,true,true,false,true,true,false,false,true,true,true,true,true,true,true,false,false,false,false,false,true,true,true,true,false,true,false,false,false,false,false};
    uint256_from_bytes(a, a26_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a26_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a27_data[32]  = {0x05,0xef,0xe6,0xec,0x23,0xb0,0xa8,0x11,0x19,0x07,0xbc,0x87,0x61,0x31,0xa1,0xef,0x0a,0x0e,0xf5,0xa0,0x69,0x81,0xf2,0x11,0x55,0x0e,0xaf,0x3b,0x41,0x06,0xc4,0x39};
    bool         a27_bits[256] = {true,false,false,true,true,true,false,false,false,false,true,false,false,false,true,true,false,true,true,false,false,false,false,false,true,false,false,false,false,false,true,false,true,true,false,true,true,true,false,false,true,true,true,true,false,true,false,true,false,true,true,true,false,false,false,false,true,false,true,false,true,false,true,false,true,false,false,false,true,false,false,false,false,true,false,false,true,true,true,true,true,false,false,false,false,false,false,true,true,false,false,true,false,true,true,false,false,false,false,false,false,true,false,true,true,false,true,false,true,true,true,true,false,true,true,true,false,false,false,false,false,true,false,true,false,false,false,false,true,true,true,true,false,true,true,true,true,false,false,false,false,true,false,true,true,false,false,false,true,true,false,false,true,false,false,false,false,true,true,false,true,true,true,false,false,false,false,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,false,false,true,false,false,true,true,false,false,false,true,false,false,false,true,false,false,false,false,false,false,true,false,true,false,true,false,false,false,false,true,true,false,true,true,true,false,false,false,true,false,false,false,false,true,true,false,true,true,true,false,true,true,false,false,true,true,true,true,true,true,true,false,true,true,true,true,false,true,false,false,false,false,false};
    uint256_from_bytes(a, a27_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a27_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a28_data[32]  = {0xec,0xb7,0xd4,0xc9,0xef,0x88,0x91,0x00,0xab,0xd2,0x80,0x27,0x0c,0x66,0xf0,0x37,0xac,0x85,0x6a,0x6d,0xdb,0x9b,0x53,0xf7,0x9e,0x1a,0xca,0xae,0x3c,0x66,0x88,0x27};
    bool         a28_bits[256] = {true,true,true,false,false,true,false,false,false,false,false,true,false,false,false,true,false,true,true,false,false,true,true,false,false,false,true,true,true,true,false,false,false,true,true,true,false,true,false,true,false,true,false,true,false,false,true,true,false,true,false,true,true,false,false,false,false,true,true,true,true,false,false,true,true,true,true,false,true,true,true,true,true,true,false,false,true,false,true,false,true,true,false,true,true,false,false,true,true,true,false,true,true,false,true,true,true,false,true,true,false,true,true,false,false,true,false,true,false,true,true,false,true,false,true,false,false,false,false,true,false,false,true,true,false,true,false,true,true,true,true,false,true,true,false,false,false,false,false,false,true,true,true,true,false,true,true,false,false,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,true,false,true,false,false,true,false,true,true,true,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,true,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true,true,true,true,true,false,true,true,true,true,false,false,true,false,false,true,true,false,false,true,false,true,false,true,true,true,true,true,false,true,true,false,true,false,false,true,true,false,true,true,true};
    uint256_from_bytes(a, a28_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a28_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a29_data[32]  = {0x6c,0xe5,0x31,0xa6,0x03,0xee,0xf6,0x07,0x2d,0x7d,0x34,0xe6,0x77,0x59,0x6a,0x6d,0x29,0x7c,0x6a,0x31,0x8f,0x8e,0xd5,0x00,0x1f,0xfe,0x62,0xa1,0xbb,0x93,0x2f,0xa3};
    bool         a29_bits[256] = {true,true,false,false,false,true,false,true,true,true,true,true,false,true,false,false,true,true,false,false,true,false,false,true,true,true,false,true,true,true,false,true,true,false,false,false,false,true,false,true,false,true,false,false,false,true,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,true,false,true,false,true,false,true,true,false,true,true,true,false,false,false,true,true,true,true,true,false,false,false,true,true,false,false,false,true,true,false,false,false,true,false,true,false,true,true,false,false,false,true,true,true,true,true,false,true,false,false,true,false,true,false,false,true,false,true,true,false,true,true,false,false,true,false,true,false,true,true,false,true,false,false,true,true,false,true,false,true,true,true,false,true,true,true,false,false,true,true,false,false,true,true,true,false,false,true,false,true,true,false,false,true,false,true,true,true,true,true,false,true,false,true,true,false,true,false,false,true,true,true,false,false,false,false,false,false,true,true,false,true,true,true,true,false,true,true,true,false,true,true,true,true,true,false,false,false,false,false,false,false,true,true,false,false,true,false,true,true,false,false,false,true,true,false,false,true,false,true,false,false,true,true,true,false,false,true,true,false,true,true,false};
    uint256_from_bytes(a, a29_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a29_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a30_data[32]  = {0x42,0xc3,0x10,0xd1,0xc2,0x72,0xc7,0x16,0xe6,0xb4,0xec,0x3e,0x73,0x5f,0xc8,0x27,0x08,0x3f,0x4f,0x83,0xec,0x67,0x1a,0xe8,0x47,0xf2,0x18,0x5c,0x81,0x0b,0x39,0xd0};
    bool         a30_bits[256] = {false,false,false,false,true,false,true,true,true,false,false,true,true,true,false,false,true,true,false,true,false,false,false,false,true,false,false,false,false,false,false,true,false,false,true,true,true,false,true,false,false,false,false,true,true,false,false,false,false,true,false,false,true,true,true,true,true,true,true,false,false,false,true,false,false,false,false,true,false,true,true,true,false,true,false,true,true,false,false,false,true,true,true,false,false,true,true,false,false,false,true,true,false,true,true,true,true,true,false,false,false,false,false,true,true,true,true,true,false,false,true,false,true,true,true,true,true,true,false,false,false,false,false,true,false,false,false,false,true,true,true,false,false,true,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,false,true,false,true,true,false,false,true,true,true,false,false,true,true,true,true,true,false,false,false,false,true,true,false,true,true,true,false,false,true,false,true,true,false,true,false,true,true,false,false,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,false,true,false,false,false,false,true,true,true,false,false,false,true,false,true,true,false,false,false,false,true,false,false,false,true,true,false,false,false,false,true,true,false,true,false,false,false,false,true,false};
    uint256_from_bytes(a, a30_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a30_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a31_data[32]  = {0xa9,0xb1,0xf6,0x36,0xfc,0xb6,0xd2,0x1d,0x14,0x82,0x7a,0xb7,0x9a,0x46,0x45,0xa1,0xce,0xd2,0x1f,0xd4,0xce,0x03,0x66,0xbe,0x67,0x40,0xb6,0xf1,0x03,0x4c,0xe2,0x9d};
    bool         a31_bits[256] = {true,false,true,true,true,false,false,true,false,true,false,false,false,true,true,true,false,false,true,true,false,false,true,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,false,true,false,false,false,false,false,false,true,false,true,true,true,false,false,true,true,false,false,true,true,true,true,true,false,true,false,true,true,false,false,true,true,false,true,true,false,false,false,false,false,false,false,true,true,true,false,false,true,true,false,false,true,false,true,false,true,true,true,true,true,true,true,false,false,false,false,true,false,false,true,false,true,true,false,true,true,true,false,false,true,true,true,false,false,false,false,true,false,true,true,false,true,false,false,false,true,false,false,true,true,false,false,false,true,false,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,true,false,true,false,true,true,true,true,false,false,true,false,false,false,false,false,true,false,false,true,false,true,false,false,false,true,false,true,true,true,false,false,false,false,true,false,false,true,false,true,true,false,true,true,false,true,true,false,true,false,false,true,true,true,true,true,true,false,true,true,false,true,true,false,false,false,true,true,false,true,true,true,true,true,false,false,false,true,true,false,true,true,false,false,true,false,true,false,true};
    uint256_from_bytes(a, a31_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a31_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a32_data[32]  = {0x6c,0x4b,0x93,0x35,0x1d,0x22,0x6e,0x6c,0x20,0xb2,0x91,0xbf,0x52,0xd6,0x9e,0x73,0x4a,0x97,0xcc,0xc8,0x84,0xa8,0xb2,0x2f,0x45,0xdb,0xd5,0x9b,0xe5,0x1a,0xc7,0xd3};
    bool         a32_bits[256] = {true,true,false,false,true,false,true,true,true,true,true,false,false,false,true,true,false,true,false,true,true,false,false,false,true,false,true,false,false,true,true,true,true,true,false,true,true,false,false,true,true,false,true,false,true,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,false,false,true,false,true,true,true,true,false,true,false,false,false,true,false,false,true,true,false,true,false,false,false,true,false,true,false,true,false,false,true,false,false,false,false,true,false,false,false,true,false,false,true,true,false,false,true,true,false,false,true,true,true,true,true,false,true,false,false,true,false,true,false,true,false,false,true,false,true,true,false,false,true,true,true,false,false,true,true,true,true,false,false,true,false,true,true,false,true,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true,true,true,false,true,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,false,false,false,true,false,false,false,false,true,true,false,true,true,false,false,true,true,true,false,true,true,false,false,true,false,false,false,true,false,false,true,false,true,true,true,false,false,false,true,false,true,false,true,true,false,false,true,true,false,false,true,false,false,true,true,true,false,true,false,false,true,false,false,false,true,true,false,true,true,false};
    uint256_from_bytes(a, a32_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a32_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a33_data[32]  = {0x35,0x70,0x62,0xa3,0xa8,0x01,0x21,0x8d,0x3e,0x8b,0x52,0xce,0x47,0xad,0x4d,0xc7,0xd3,0xf3,0x8d,0xc7,0x23,0xf6,0x1b,0xca,0xe1,0xa0,0x03,0x8a,0x63,0x16,0x68,0x79};
    bool         a33_bits[256] = {true,false,false,true,true,true,true,false,false,false,false,true,false,true,true,false,false,true,true,false,true,false,false,false,true,true,false,false,false,true,true,false,false,true,false,true,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,false,false,false,false,true,true,true,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,false,false,true,true,false,true,true,true,true,true,true,false,false,false,true,false,false,true,true,true,false,false,false,true,true,true,false,true,true,false,false,false,true,true,true,false,false,true,true,true,true,true,true,false,false,true,false,true,true,true,true,true,false,false,false,true,true,true,false,true,true,false,false,true,false,true,false,true,true,false,true,false,true,true,true,true,false,false,false,true,false,false,true,true,true,false,false,true,true,false,true,false,false,true,false,true,false,true,true,false,true,false,false,false,true,false,true,true,true,true,true,false,false,true,false,true,true,false,false,false,true,true,false,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,false,false,true,false,true,false,true,true,true,false,false,false,true,false,true,false,true,false,false,false,true,true,false,false,false,false,false,true,true,true,false,true,false,true,false,true,true,false,false};
    uint256_from_bytes(a, a33_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a33_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a34_data[32]  = {0x27,0x56,0x47,0x79,0xa3,0x1d,0x27,0xfc,0xdd,0x43,0xef,0x9c,0xc5,0x62,0x67,0x72,0x93,0x53,0x55,0x8b,0x4d,0xf3,0x36,0x2c,0xf9,0x35,0xdc,0xc8,0x61,0xd2,0x69,0x4c};
    bool         a34_bits[256] = {false,false,true,true,false,false,true,false,true,false,false,true,false,true,true,false,false,true,false,false,true,false,true,true,true,false,false,false,false,true,true,false,false,false,false,true,false,false,true,true,false,false,true,true,true,false,true,true,true,false,true,false,true,true,false,false,true,false,false,true,true,true,true,true,false,false,true,true,false,true,false,false,false,true,true,false,true,true,false,false,true,true,false,false,true,true,true,true,true,false,true,true,false,false,true,false,true,true,false,true,false,false,false,true,true,false,true,false,true,false,true,false,true,true,false,false,true,false,true,false,true,true,false,false,true,false,false,true,false,true,false,false,true,true,true,false,true,true,true,false,false,true,true,false,false,true,false,false,false,true,true,false,true,false,true,false,false,false,true,true,false,false,true,true,true,false,false,true,true,true,true,true,false,true,true,true,true,true,false,false,false,false,true,false,true,false,true,true,true,false,true,true,false,false,true,true,true,true,true,true,true,true,true,false,false,true,false,false,true,false,true,true,true,false,false,false,true,true,false,false,false,true,false,true,true,false,false,true,true,true,true,false,true,true,true,false,false,false,true,false,false,true,true,false,true,false,true,false,true,true,true,false,false,true,false,false};
    uint256_from_bytes(a, a34_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a34_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a35_data[32]  = {0x0f,0x27,0xa5,0x05,0xe1,0x2d,0xaf,0x93,0xa6,0x5c,0x2c,0xfe,0x92,0xa9,0x40,0x49,0x8f,0xd3,0x89,0xb0,0x0b,0xcd,0x1e,0x6b,0x90,0xf5,0xa6,0x5b,0x8c,0x8c,0x38,0x87};
    bool         a35_bits[256] = {true,true,true,false,false,false,false,true,false,false,false,true,true,true,false,false,false,false,true,true,false,false,false,true,false,false,true,true,false,false,false,true,true,true,false,true,true,false,true,false,false,true,true,false,false,true,false,true,true,false,true,false,true,true,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,true,true,false,false,true,true,true,true,false,false,false,true,false,true,true,false,false,true,true,true,true,false,true,false,false,false,false,false,false,false,false,true,true,false,true,true,false,false,true,false,false,false,true,true,true,false,false,true,false,true,true,true,true,true,true,false,false,false,true,true,false,false,true,false,false,true,false,false,false,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,false,true,false,false,true,false,true,true,true,true,true,true,true,false,false,true,true,false,true,false,false,false,false,true,true,true,false,true,false,false,true,true,false,false,true,false,true,true,true,false,false,true,false,false,true,true,true,true,true,false,true,false,true,true,false,true,true,false,true,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,false,false,false,true,false,true,false,false,true,false,true,true,true,true,false,false,true,false,false,true,true,true,true,false,false,false,false};
    uint256_from_bytes(a, a35_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a35_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a36_data[32]  = {0xf2,0xf8,0xa0,0x52,0x65,0x91,0x9c,0x98,0x00,0xc6,0x4f,0xda,0xa4,0x24,0x3e,0x03,0x59,0x41,0x85,0x50,0xad,0xea,0xbe,0x73,0xf9,0x78,0x2d,0x2d,0x48,0xaa,0x97,0xad};
    bool         a36_bits[256] = {true,false,true,true,false,true,false,true,true,true,true,false,true,false,false,true,false,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,true,false,true,true,false,true,false,false,true,false,true,true,false,true,false,false,false,false,false,true,true,true,true,false,true,false,false,true,true,true,true,true,true,true,false,false,true,true,true,false,false,true,true,true,true,true,false,true,false,true,false,true,false,true,true,true,true,false,true,true,false,true,false,true,false,false,false,false,true,false,true,false,true,false,true,false,false,false,false,true,true,false,false,false,false,false,true,false,true,false,false,true,true,false,true,false,true,true,false,false,false,false,false,false,false,true,true,true,true,true,false,false,false,false,true,false,false,true,false,false,false,false,true,false,false,true,false,true,false,true,false,true,true,false,true,true,true,true,true,true,false,false,true,false,false,true,true,false,false,false,true,true,false,false,false,false,false,false,false,false,false,false,false,true,true,false,false,true,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,true,true,false,true,false,false,true,true,false,false,true,false,false,true,false,true,false,false,false,false,false,false,true,false,true,false,false,false,true,true,true,true,true,false,true,false,false,true,true,true,true};
    uint256_from_bytes(a, a36_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a36_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a37_data[32]  = {0x0b,0xb2,0x34,0x4c,0xe8,0xd1,0x04,0x27,0x4e,0xfb,0x3b,0xed,0x5f,0xb1,0xfe,0xd8,0x0f,0xbe,0xec,0x76,0xc7,0x08,0x40,0xe1,0x5e,0x02,0xd5,0x2f,0x78,0xd5,0x89,0x22};
    bool         a37_bits[256] = {false,true,false,false,false,true,false,false,true,false,false,true,false,false,false,true,true,false,true,false,true,false,true,true,false,false,false,true,true,true,true,false,true,true,true,true,false,true,false,false,true,false,true,false,true,false,true,true,false,true,false,false,false,false,false,false,false,true,true,true,true,false,true,false,true,false,false,false,false,true,true,true,false,false,false,false,false,false,true,false,false,false,false,true,false,false,false,false,true,true,true,false,false,false,true,true,false,true,true,false,true,true,true,false,false,false,true,true,false,true,true,true,false,true,true,true,true,true,false,true,true,true,true,true,false,false,false,false,false,false,false,true,true,false,true,true,false,true,true,true,true,true,true,true,true,false,false,false,true,true,false,true,true,true,true,true,true,false,true,false,true,false,true,true,false,true,true,true,true,true,false,true,true,true,false,false,true,true,false,true,true,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,false,true,false,false,false,false,true,false,false,false,false,false,true,false,false,false,true,false,true,true,false,false,false,true,false,true,true,true,false,false,true,true,false,false,true,false,false,false,true,false,true,true,false,false,false,true,false,false,true,true,false,true,true,true,false,true,false,false,false,false};
    uint256_from_bytes(a, a37_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a37_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a38_data[32]  = {0x21,0x6c,0xba,0x0d,0x27,0x83,0x26,0xd1,0x7d,0x99,0x13,0x16,0x05,0x88,0xd0,0x73,0x41,0xc1,0x64,0xe5,0x7e,0xd8,0xff,0xf4,0x0b,0xf1,0x60,0x3e,0x2e,0xc6,0x6a,0xba};
    bool         a38_bits[256] = {false,true,false,true,true,true,false,true,false,true,false,true,false,true,true,false,false,true,true,false,false,false,true,true,false,true,true,true,false,true,false,false,false,true,true,true,true,true,false,false,false,false,false,false,false,true,true,false,true,false,false,false,true,true,true,true,true,true,false,true,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,true,true,false,true,true,false,true,true,true,true,true,true,false,true,false,true,false,false,true,true,true,false,false,true,false,false,true,true,false,true,false,false,false,false,false,true,true,true,false,false,false,false,false,true,false,true,true,false,false,true,true,true,false,false,false,false,false,true,false,true,true,false,false,false,true,false,false,false,true,true,false,true,false,false,false,false,false,false,true,true,false,true,false,false,false,true,true,false,false,true,false,false,false,true,false,false,true,true,false,false,true,true,false,true,true,true,true,true,false,true,false,false,false,true,false,true,true,false,true,true,false,false,true,false,false,true,true,false,false,false,false,false,true,true,true,true,false,false,true,false,false,true,false,true,true,false,false,false,false,false,true,false,true,true,true,false,true,false,false,true,true,false,true,true,false,true,false,false,false,false,true,false,false};
    uint256_from_bytes(a, a38_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a38_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a39_data[32]  = {0x62,0x53,0xfe,0x31,0x55,0x9f,0x55,0xd2,0xde,0xf7,0xcc,0x48,0xc7,0xc8,0x07,0xac,0x76,0x92,0xeb,0xe2,0x62,0xb3,0xb6,0x3a,0xfb,0x17,0xce,0x13,0x8f,0x5e,0xc7,0xf3};
    bool         a39_bits[256] = {true,true,false,false,true,true,true,true,true,true,true,false,false,false,true,true,false,true,true,true,true,false,true,false,true,true,true,true,false,false,false,true,true,true,false,false,true,false,false,false,false,true,true,true,false,false,true,true,true,true,true,false,true,false,false,false,true,true,false,true,true,true,true,true,false,true,false,true,true,true,false,false,false,true,true,false,true,true,false,true,true,true,false,false,true,true,false,true,false,true,false,false,false,true,true,false,false,true,false,false,false,true,true,true,true,true,false,true,false,true,true,true,false,true,false,false,true,false,false,true,false,true,true,false,true,true,true,false,false,false,true,true,false,true,false,true,true,true,true,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,false,false,false,true,true,false,false,false,true,false,false,true,false,false,false,true,true,false,false,true,true,true,true,true,false,true,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,true,false,true,true,true,false,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,false,true,false,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,false,true,false,true,false,false,true,false,false,false,true,true,false};
    uint256_from_bytes(a, a39_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a39_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a40_data[32]  = {0x51,0x38,0x37,0xa3,0x47,0x0c,0x29,0x8f,0x2b,0x53,0x99,0xb8,0xc5,0x37,0x3c,0x95,0x3e,0x72,0x9b,0x37,0x35,0x15,0xb6,0x58,0x4a,0xe6,0x9a,0x77,0xe1,0xda,0x98,0x55};
    bool         a40_bits[256] = {true,false,true,false,true,false,true,false,false,false,false,true,true,false,false,true,false,true,false,true,true,false,true,true,true,false,false,false,false,true,true,true,true,true,true,false,true,true,true,false,false,true,false,true,true,false,false,true,false,true,true,false,false,true,true,true,false,true,false,true,false,false,true,false,false,false,false,true,true,false,true,false,false,true,true,false,true,true,false,true,true,false,true,false,true,false,false,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false,true,true,false,false,true,false,true,false,false,true,true,true,false,false,true,true,true,true,true,false,false,true,false,true,false,true,false,false,true,false,false,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,false,true,false,false,false,true,true,false,false,false,true,true,true,false,true,true,false,false,true,true,false,false,true,true,true,false,false,true,false,true,false,true,true,false,true,false,true,false,false,true,true,true,true,false,false,false,true,true,false,false,true,false,true,false,false,false,false,true,true,false,false,false,false,true,true,true,false,false,false,true,false,true,true,false,false,false,true,false,true,true,true,true,false,true,true,false,false,false,false,false,true,true,true,false,false,true,false,false,false,true,false,true,false};
    uint256_from_bytes(a, a40_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a40_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a41_data[32]  = {0xc5,0x41,0xdb,0x70,0x85,0xab,0xea,0xc8,0x29,0x6a,0x10,0xe8,0x1b,0x83,0x89,0x32,0x58,0x22,0x0f,0x08,0x25,0x94,0xa3,0x91,0x33,0xeb,0x2d,0x95,0xa0,0x33,0x62,0x7b};
    bool         a41_bits[256] = {true,true,false,true,true,true,true,false,false,true,false,false,false,true,true,false,true,true,false,false,true,true,false,false,false,false,false,false,false,true,false,true,true,false,true,false,true,false,false,true,true,false,true,true,false,true,false,false,true,true,false,true,false,true,true,true,true,true,false,false,true,true,false,false,true,false,false,false,true,false,false,true,true,true,false,false,false,true,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,true,false,false,false,false,false,true,false,false,false,false,true,true,true,true,false,false,false,false,false,true,false,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,false,true,true,false,false,true,false,false,true,false,false,false,true,true,true,false,false,false,false,false,true,true,true,false,true,true,false,false,false,false,false,false,true,false,true,true,true,false,false,false,false,true,false,false,false,false,true,false,true,false,true,true,false,true,false,false,true,false,true,false,false,false,false,false,true,false,false,true,true,false,true,false,true,false,true,true,true,true,true,false,true,false,true,false,true,true,false,true,false,false,false,false,true,false,false,false,false,true,true,true,false,true,true,false,true,true,false,true,true,true,false,false,false,false,false,true,false,true,false,true,false,false,false,true,true};
    uint256_from_bytes(a, a41_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a41_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a42_data[32]  = {0x7e,0xba,0xec,0xc7,0x44,0xc9,0x39,0x9e,0x92,0x7b,0x7b,0x34,0x3e,0xe2,0x0a,0x2b,0x24,0xae,0xfc,0xff,0xfb,0x27,0x13,0x5a,0xf8,0x40,0xff,0x05,0xda,0xee,0x6a,0x2d};
    bool         a42_bits[256] = {true,false,true,true,false,true,false,false,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,true,false,true,false,true,true,false,true,true,true,false,true,false,false,false,false,false,true,true,true,true,true,true,true,true,false,false,false,false,false,false,true,false,false,false,false,true,true,true,true,true,false,true,false,true,true,false,true,false,true,true,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,true,false,true,true,true,false,true,false,true,false,false,true,false,false,true,false,false,true,true,false,true,false,true,false,false,false,true,false,true,false,false,false,false,false,true,false,false,false,true,true,true,false,true,true,true,true,true,false,false,false,false,true,false,true,true,false,false,true,true,false,true,true,true,true,false,true,true,false,true,true,true,true,false,false,true,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,false,false,true,true,true,false,false,true,false,false,true,false,false,true,true,false,false,true,false,false,false,true,false,true,true,true,false,false,false,true,true,false,false,true,true,false,true,true,true,false,true,false,true,true,true,false,true,false,true,true,true,true,true,true,false};
    uint256_from_bytes(a, a42_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a42_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a43_data[32]  = {0xb3,0x17,0x37,0x49,0x99,0x27,0x6f,0x0d,0xcd,0x35,0x2f,0xa5,0x48,0x7b,0x78,0x81,0x91,0x92,0x80,0x70,0xc4,0x8f,0x44,0xde,0x3b,0x4f,0x34,0xaa,0xed,0x84,0xeb,0xdf};
    bool         a43_bits[256] = {true,true,true,true,true,false,true,true,true,true,false,true,false,true,true,true,false,false,true,false,false,false,false,true,true,false,true,true,false,true,true,true,false,true,false,true,false,true,false,true,false,false,true,false,true,true,false,false,true,true,true,true,false,false,true,false,true,true,false,true,true,true,false,false,false,true,true,true,true,false,true,true,false,false,true,false,false,false,true,false,true,true,true,true,false,false,false,true,false,false,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,true,false,true,false,false,true,false,false,true,true,false,false,false,true,false,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,true,false,false,false,false,true,false,false,true,false,true,false,true,false,false,true,false,true,true,true,true,true,false,true,false,false,true,false,true,false,true,true,false,false,true,false,true,true,false,false,true,true,true,false,true,true,false,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,false,true,false,false,true,false,false,true,true,false,false,true,true,false,false,true,false,false,true,false,true,true,true,false,true,true,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,true,false,true};
    uint256_from_bytes(a, a43_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a43_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a44_data[32]  = {0xa8,0x8d,0x15,0x46,0x77,0x8e,0xe3,0x8c,0xb6,0xe6,0xb1,0x8f,0xa1,0x05,0xe9,0x36,0xbc,0x4f,0x1a,0xd1,0xa5,0x71,0x8c,0xb0,0xf0,0x7a,0xc3,0x39,0xaf,0x29,0xbc,0xde};
    bool         a44_bits[256] = {false,true,true,true,true,false,true,true,false,false,true,true,true,true,false,true,true,false,false,true,false,true,false,false,true,true,true,true,false,true,false,true,true,false,false,true,true,true,false,false,true,true,false,false,false,false,true,true,false,true,false,true,true,true,true,false,false,false,false,false,true,true,true,true,false,false,false,false,true,true,false,true,false,false,true,true,false,false,false,true,true,false,false,false,true,true,true,false,true,false,true,false,false,true,false,true,true,false,false,false,true,false,true,true,false,true,false,true,true,false,false,false,true,true,true,true,false,false,true,false,false,false,true,true,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false,true,false,true,true,true,true,false,true,false,false,false,false,false,true,false,false,false,false,true,false,true,true,true,true,true,false,false,false,true,true,false,false,false,true,true,false,true,false,true,true,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,true,true,false,false,false,true,true,true,false,false,false,true,true,true,false,true,true,true,false,false,false,true,true,true,true,false,true,true,true,false,false,true,true,false,false,false,true,false,true,false,true,false,true,false,false,false,true,false,true,true,false,false,false,true,false,false,false,true,false,true,false,true};
    uint256_from_bytes(a, a44_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a44_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a45_data[32]  = {0x98,0x31,0xad,0x52,0xda,0x4a,0x39,0x46,0x00,0x39,0xe9,0x3a,0x81,0x53,0xb6,0x57,0xc8,0x46,0xc2,0xd1,0x6e,0x54,0x8f,0xbe,0xa6,0x51,0xa3,0x52,0x05,0x6a,0xf4,0x1f};
    bool         a45_bits[256] = {true,true,true,true,true,false,false,false,false,false,true,false,true,true,true,true,false,true,false,true,false,true,true,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,true,false,true,true,false,false,false,true,false,true,true,false,false,false,true,false,true,false,false,true,true,false,false,true,false,true,false,true,true,true,true,true,false,true,true,true,true,true,false,false,false,true,false,false,true,false,true,false,true,false,false,true,true,true,false,true,true,false,true,false,false,false,true,false,true,true,false,true,false,false,false,false,true,true,false,true,true,false,false,false,true,false,false,false,false,true,false,false,true,true,true,true,true,false,true,false,true,false,false,true,true,false,true,true,false,true,true,true,false,false,true,false,true,false,true,false,false,false,false,false,false,true,false,true,false,true,true,true,false,false,true,false,false,true,false,true,true,true,true,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,true,false,true,false,false,true,true,true,false,false,false,true,false,true,false,false,true,false,false,true,false,true,true,false,true,true,false,true,false,false,true,false,true,false,true,false,true,true,false,true,false,true,true,false,false,false,true,true,false,false,false,false,false,true,true,false,false,true};
    uint256_from_bytes(a, a45_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a45_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a46_data[32]  = {0x61,0x7d,0x7c,0x1f,0xa8,0xfd,0x80,0xa2,0x59,0x8f,0x1d,0x1b,0xfb,0xb0,0xf9,0x03,0x5a,0xf3,0xfc,0xee,0xcb,0x1f,0x6b,0x9d,0x39,0x93,0x88,0x2c,0xf0,0xe9,0x69,0xb3};
    bool         a46_bits[256] = {true,true,false,false,true,true,false,true,true,false,false,true,false,true,true,false,true,false,false,true,false,true,true,true,false,false,false,false,true,true,true,true,false,false,true,true,false,true,false,false,false,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,false,false,true,true,true,false,false,true,false,true,true,true,false,false,true,true,true,false,true,false,true,true,false,true,true,true,true,true,false,false,false,true,true,false,true,false,false,true,true,false,true,true,true,false,true,true,true,false,false,true,true,true,true,true,true,true,true,false,false,true,true,true,true,false,true,false,true,true,false,true,false,true,true,false,false,false,false,false,false,true,false,false,true,true,true,true,true,false,false,false,false,true,true,false,true,true,true,false,true,true,true,true,true,true,true,false,true,true,false,false,false,true,false,true,true,true,false,false,false,true,true,true,true,false,false,false,true,true,false,false,true,true,false,true,false,false,true,false,false,false,true,false,true,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,false,false,false,true,false,true,false,true,true,true,true,true,true,false,false,false,false,false,true,true,true,true,true,false,true,false,true,true,true,true,true,false,true,false,false,false,false,true,true,false};
    uint256_from_bytes(a, a46_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a46_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a47_data[32]  = {0xa3,0x61,0x1e,0xb3,0x12,0xe7,0x1c,0xb3,0x8f,0x7c,0x27,0xe0,0xfa,0xb1,0x90,0xac,0x31,0xe5,0xb8,0x0d,0x06,0x78,0xa6,0xfd,0x9b,0xfc,0xfa,0xf5,0xff,0x1d,0x27,0xd3};
    bool         a47_bits[256] = {true,true,false,false,true,false,true,true,true,true,true,false,false,true,false,false,true,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,true,true,false,true,false,true,true,true,true,true,false,false,true,true,true,true,true,true,true,true,false,true,true,false,false,true,true,false,true,true,true,true,true,true,false,true,true,false,false,true,false,true,false,false,false,true,true,true,true,false,false,true,true,false,false,false,false,false,true,false,true,true,false,false,false,false,false,false,false,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,false,true,true,false,false,false,false,true,true,false,true,false,true,false,false,false,false,true,false,false,true,true,false,false,false,true,true,false,true,false,true,false,true,true,true,true,true,false,false,false,false,false,true,true,true,true,true,true,false,false,true,false,false,false,false,true,true,true,true,true,false,true,true,true,true,false,false,false,true,true,true,false,false,true,true,false,true,false,false,true,true,true,false,false,false,true,true,true,false,false,true,true,true,false,true,false,false,true,false,false,false,true,true,false,false,true,true,false,true,false,true,true,true,true,false,false,false,true,false,false,false,false,true,true,false,true,true,false,false,false,true,false,true};
    uint256_from_bytes(a, a47_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a47_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a48_data[32]  = {0x34,0xcf,0x77,0xe6,0xdc,0xcb,0xba,0x1b,0xdb,0x39,0x7d,0x6f,0xdb,0x85,0x77,0x76,0x9c,0x65,0x5c,0xe9,0xe5,0xc7,0xb3,0x54,0x29,0xf8,0xe1,0x27,0xea,0xdf,0xa8,0xd4};
    bool         a48_bits[256] = {false,false,true,false,true,false,true,true,false,false,false,true,false,true,false,true,true,true,true,true,true,false,true,true,false,true,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,false,false,false,false,true,true,true,false,false,false,true,true,true,true,true,true,false,false,true,false,true,false,false,false,false,true,false,true,false,true,false,true,true,false,false,true,true,false,true,true,true,true,false,false,false,true,true,true,false,true,false,false,true,true,true,true,false,false,true,false,true,true,true,false,false,true,true,true,false,true,false,true,false,true,false,false,true,true,false,false,false,true,true,true,false,false,true,false,true,true,false,true,true,true,false,true,true,true,false,true,true,true,false,true,false,true,false,false,false,false,true,true,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,true,false,true,true,true,true,true,false,true,false,false,true,true,true,false,false,true,true,false,true,true,false,true,true,true,true,false,true,true,false,false,false,false,true,false,true,true,true,false,true,true,true,false,true,false,false,true,true,false,false,true,true,true,false,true,true,false,true,true,false,false,true,true,true,true,true,true,false,true,true,true,false,true,true,true,true,false,false,true,true,false,false,true,false,true,true,false,false};
    uint256_from_bytes(a, a48_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a48_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a49_data[32]  = {0x66,0x25,0x68,0xa4,0x3a,0xeb,0x9d,0x89,0x7c,0xd8,0x21,0xbd,0x3d,0x0b,0x5b,0x33,0x29,0xd0,0x66,0x16,0x89,0xc0,0xfa,0x84,0x58,0x1f,0xd1,0x8d,0x11,0xf7,0x59,0x62};
    bool         a49_bits[256] = {false,true,false,false,false,true,true,false,true,false,false,true,true,false,true,false,true,true,true,false,true,true,true,true,true,false,false,false,true,false,false,false,true,false,true,true,false,false,false,true,true,false,false,false,true,false,true,true,true,true,true,true,true,false,false,false,false,false,false,true,true,false,true,false,false,false,true,false,false,false,false,true,false,true,false,true,true,true,true,true,false,false,false,false,false,false,true,true,true,false,false,true,false,false,false,true,false,true,true,false,true,false,false,false,false,true,true,false,false,true,true,false,false,false,false,false,true,false,true,true,true,false,false,true,false,true,false,false,true,true,false,false,true,true,false,false,true,true,false,true,true,false,true,false,true,true,false,true,false,false,false,false,true,false,true,true,true,true,false,false,true,false,true,true,true,true,false,true,true,false,false,false,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,true,true,true,true,false,true,false,false,true,false,false,false,true,true,false,true,true,true,false,false,true,true,true,false,true,false,true,true,true,false,true,false,true,true,true,false,false,false,false,true,false,false,true,false,true,false,false,false,true,false,true,true,false,true,false,true,false,false,true,false,false,false,true,true,false,false,true,true,false};
    uint256_from_bytes(a, a49_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a49_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a50_data[32]  = {0x5a,0x59,0x9c,0xc3,0x96,0x7a,0x01,0x29,0x69,0x35,0x5c,0xc9,0x90,0x5e,0x1d,0xc6,0x60,0xce,0x07,0xa3,0x08,0xf0,0x2f,0xae,0x39,0x01,0x4d,0x1a,0x59,0x7d,0x87,0xcb};
    bool         a50_bits[256] = {true,true,false,true,false,false,true,true,true,true,true,false,false,false,false,true,true,false,true,true,true,true,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,false,false,false,true,false,true,true,false,false,true,false,true,false,false,false,false,false,false,false,true,false,false,true,true,true,false,false,false,true,true,true,false,true,false,true,true,true,true,true,false,true,false,false,false,false,false,false,true,true,true,true,false,false,false,true,false,false,false,false,true,true,false,false,false,true,false,true,true,true,true,false,false,false,false,false,false,true,true,true,false,false,true,true,false,false,false,false,false,true,true,false,false,true,true,false,false,false,true,true,true,false,true,true,true,false,false,false,false,true,true,true,true,false,true,false,false,false,false,false,true,false,false,true,true,false,false,true,false,false,true,true,false,false,true,true,true,false,true,false,true,false,true,false,true,true,false,false,true,false,false,true,false,true,true,false,true,false,false,true,false,true,false,false,true,false,false,false,false,false,false,false,false,true,false,true,true,true,true,false,false,true,true,false,true,false,false,true,true,true,false,false,false,false,true,true,false,false,true,true,true,false,false,true,true,false,false,true,true,false,true,false,false,true,false,true,true,false,true,false};
    uint256_from_bytes(a, a50_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a50_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a51_data[32]  = {0x92,0x3d,0x97,0x5c,0x8f,0x63,0x16,0x05,0x84,0x47,0x59,0x9e,0xd4,0x20,0xa1,0xb9,0xaa,0x90,0x81,0xaf,0x59,0x24,0x3b,0xf7,0xa9,0xd4,0x16,0x12,0x02,0xa7,0x8f,0x20};
    bool         a51_bits[256] = {false,false,false,false,false,true,false,false,true,true,true,true,false,false,false,true,true,true,true,false,false,true,false,true,false,true,false,false,false,false,false,false,false,true,false,false,true,false,false,false,false,true,true,false,true,false,false,false,false,false,true,false,true,false,true,true,true,false,false,true,false,true,false,true,true,true,true,false,true,true,true,true,true,true,false,true,true,true,false,false,false,false,true,false,false,true,false,false,true,false,false,true,true,false,true,false,true,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,false,false,false,false,true,false,false,true,false,true,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,false,false,false,true,false,true,false,true,true,false,true,true,true,true,false,false,true,true,false,false,true,true,false,true,false,true,true,true,false,false,false,true,false,false,false,true,false,false,false,false,true,true,false,true,false,false,false,false,false,false,true,true,false,true,false,false,false,true,true,false,false,false,true,true,false,true,true,true,true,false,false,false,true,false,false,true,true,true,false,true,false,true,true,true,false,true,false,false,true,true,false,true,true,true,true,false,false,false,true,false,false,true,false,false,true};
    uint256_from_bytes(a, a51_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a51_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a52_data[32]  = {0xef,0x0b,0xdd,0x42,0xf0,0x1a,0xaf,0x3c,0x92,0x71,0x31,0x12,0xd5,0x03,0xe3,0x50,0x0b,0x7b,0xef,0xa7,0x96,0xf2,0xcb,0x90,0xe9,0xba,0xf9,0xf6,0xee,0x91,0xc1,0xae};
    bool         a52_bits[256] = {false,true,true,true,false,true,false,true,true,false,false,false,false,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,true,true,false,true,true,false,true,true,true,true,true,false,false,true,true,true,true,true,false,true,false,true,true,true,false,true,true,false,false,true,false,true,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,false,true,true,false,true,false,false,true,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,true,false,true,true,true,true,true,false,true,true,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,false,false,false,false,false,false,true,false,true,false,true,true,false,false,false,true,true,true,true,true,false,false,false,false,false,false,true,false,true,false,true,false,true,true,false,true,false,false,true,false,false,false,true,false,false,false,true,true,false,false,true,false,false,false,true,true,true,false,false,true,false,false,true,false,false,true,false,false,true,true,true,true,false,false,true,true,true,true,false,true,false,true,false,true,false,true,true,false,false,false,false,false,false,false,true,true,true,true,false,true,false,false,false,false,true,false,true,false,true,true,true,false,true,true,true,true,false,true,false,false,false,false,true,true,true,true,false,true,true,true};
    uint256_from_bytes(a, a52_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a52_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a53_data[32]  = {0xa1,0x3e,0xaa,0xc6,0x48,0x14,0xcb,0xe5,0x79,0x28,0x6d,0x8d,0xf0,0x74,0xd6,0x51,0x71,0x66,0x13,0xc5,0x8e,0x53,0xdc,0xdc,0x26,0x24,0xd4,0x89,0x2f,0x1a,0xc7,0xd9};
    bool         a53_bits[256] = {true,false,false,true,true,false,true,true,true,true,true,false,false,false,true,true,false,true,false,true,true,false,false,false,true,true,true,true,false,true,false,false,true,false,false,true,false,false,false,true,false,false,true,false,true,false,true,true,false,false,true,false,false,true,false,false,false,true,true,false,false,true,false,false,false,false,true,true,true,false,true,true,false,false,true,true,true,false,true,true,true,true,false,false,true,false,true,false,false,true,true,true,false,false,false,true,true,false,true,false,false,false,true,true,true,true,false,false,true,false,false,false,false,true,true,false,false,true,true,false,true,false,false,false,true,true,true,false,true,false,false,false,true,false,true,false,false,true,true,false,true,false,true,true,false,false,true,false,true,true,true,false,false,false,false,false,true,true,true,true,true,false,true,true,false,false,false,true,true,false,true,true,false,true,true,false,false,false,false,true,false,true,false,false,true,false,false,true,true,true,true,false,true,false,true,false,false,true,true,true,true,true,false,true,false,false,true,true,false,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,false,true,true,false,false,false,true,true,false,true,false,true,false,true,false,true,false,true,true,true,true,true,false,false,true,false,false,false,false,true,false,true};
    uint256_from_bytes(a, a53_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a53_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a54_data[32]  = {0x8c,0xff,0x25,0xad,0xbb,0x86,0x48,0x88,0xcc,0x42,0x7f,0xa6,0xdd,0xfe,0x38,0x85,0xd7,0x4f,0xcf,0x6c,0xcf,0xc3,0x3e,0x17,0x04,0xd8,0xfa,0x33,0x1b,0x64,0xb9,0x74};
    bool         a54_bits[256] = {false,false,true,false,true,true,true,false,true,false,false,true,true,true,false,true,false,false,true,false,false,true,true,false,true,true,false,true,true,false,false,false,true,true,false,false,true,true,false,false,false,true,false,true,true,true,true,true,false,false,false,true,true,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,true,false,false,false,false,true,true,true,true,true,false,false,true,true,false,false,false,false,true,true,true,true,true,true,false,false,true,true,false,false,true,true,false,true,true,false,true,true,true,true,false,false,true,true,true,true,true,true,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,true,true,true,true,true,true,true,false,true,true,true,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,true,false,false,false,true,true,false,false,true,true,false,false,false,true,false,false,false,true,false,false,false,true,false,false,true,false,false,true,true,false,false,false,false,true,true,true,false,true,true,true,false,true,true,false,true,true,false,true,false,true,true,false,true,false,false,true,false,false,true,true,true,true,true,true,true,true,false,false,true,true,false,false,false,true};
    uint256_from_bytes(a, a54_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a54_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a55_data[32]  = {0xb1,0x66,0x99,0x1f,0x20,0x80,0xfb,0x39,0x7a,0x43,0x7b,0xfa,0x8e,0xfd,0x39,0x8c,0xa4,0x50,0xc9,0xb7,0xf9,0x6c,0xce,0xae,0x7f,0xf7,0x77,0xef,0x97,0x30,0x3a,0xe8};
    bool         a55_bits[256] = {false,false,false,true,false,true,true,true,false,true,false,true,true,true,false,false,false,false,false,false,true,true,false,false,true,true,true,false,true,false,false,true,true,true,true,true,false,true,true,true,true,true,true,false,true,true,true,false,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,false,false,true,true,true,false,true,false,true,false,true,true,true,false,false,true,true,false,false,true,true,false,true,true,false,true,false,false,true,true,true,true,true,true,true,true,false,true,true,false,true,true,false,false,true,false,false,true,true,false,false,false,false,true,false,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,false,false,true,true,false,false,true,true,true,false,false,true,false,true,true,true,true,true,true,false,true,true,true,false,false,false,true,false,true,false,true,true,true,true,true,true,true,false,true,true,true,true,false,true,true,false,false,false,false,true,false,false,true,false,true,true,true,true,false,true,false,false,true,true,true,false,false,true,true,false,true,true,true,true,true,false,false,false,false,false,false,false,true,false,false,false,false,false,true,false,false,true,true,true,true,true,false,false,false,true,false,false,true,true,false,false,true,false,true,true,false,false,true,true,false,true,false,false,false,true,true,false,true};
    uint256_from_bytes(a, a55_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a55_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a56_data[32]  = {0x9e,0xe6,0x0d,0x47,0x06,0x3b,0xf0,0x1d,0x0e,0xff,0x18,0x67,0xf4,0x7d,0x5e,0x62,0x1e,0xcd,0x4a,0x8e,0x64,0x41,0x26,0x85,0x70,0x8a,0xcb,0xd0,0x21,0x99,0x72,0x80};
    bool         a56_bits[256] = {false,false,false,false,false,false,false,true,false,true,false,false,true,true,true,false,true,false,false,true,true,false,false,true,true,false,false,false,false,true,false,false,false,false,false,false,true,false,true,true,true,true,false,true,false,false,true,true,false,true,false,true,false,false,false,true,false,false,false,false,true,true,true,false,true,false,true,false,false,false,false,true,false,true,true,false,false,true,false,false,true,false,false,false,false,false,true,false,false,false,true,false,false,true,true,false,false,true,true,true,false,false,false,true,false,true,false,true,false,false,true,false,true,false,true,true,false,false,true,true,false,true,true,true,true,false,false,false,false,true,false,false,false,true,true,false,false,true,true,true,true,false,true,false,true,false,true,true,true,true,true,false,false,false,true,false,true,true,true,true,true,true,true,false,false,true,true,false,false,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,true,false,true,true,true,false,false,false,false,false,false,false,true,true,true,true,true,true,false,true,true,true,false,false,false,true,true,false,false,false,false,false,true,true,true,false,false,false,true,false,true,false,true,true,false,false,false,false,false,true,true,false,false,true,true,true,false,true,true,true,true,false,false,true};
    uint256_from_bytes(a, a56_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a56_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a57_data[32]  = {0x96,0xcd,0x36,0xc6,0xc0,0x05,0x99,0xeb,0xd8,0x26,0x0d,0xef,0x0b,0x32,0xa6,0xbf,0x9f,0x1f,0x40,0x72,0x22,0x46,0xd5,0x67,0x91,0x99,0x81,0xdd,0x74,0x0d,0x7a,0xc3};
    bool         a57_bits[256] = {true,true,false,false,false,false,true,true,false,true,false,true,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,true,true,false,false,false,false,false,false,true,true,false,false,true,true,false,false,true,true,false,false,false,true,false,false,true,true,true,true,false,false,true,true,false,true,false,true,false,true,false,true,true,false,true,true,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true,false,false,true,true,true,false,false,false,false,false,false,false,true,false,true,true,true,true,true,false,false,false,true,true,true,true,true,false,false,true,true,true,true,true,true,true,false,true,false,true,true,false,false,true,false,true,false,true,false,false,true,true,false,false,true,true,false,true,false,false,false,false,true,true,true,true,false,true,true,true,true,false,true,true,false,false,false,false,false,true,true,false,false,true,false,false,false,false,false,true,true,false,true,true,true,true,false,true,false,true,true,true,true,false,false,true,true,false,false,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,false,false,false,true,true,false,true,true,false,true,true,false,false,true,false,true,true,false,false,true,true,false,true,true,false,true,false,false,true};
    uint256_from_bytes(a, a57_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a57_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a58_data[32]  = {0xca,0xea,0x44,0x45,0xa2,0x2b,0x0d,0xe6,0xbf,0xf3,0xdf,0x20,0x19,0x1a,0x5e,0x71,0xee,0x25,0xc0,0x0c,0x97,0x98,0x7a,0xfe,0x9f,0x9a,0xd5,0xd3,0xbb,0x8d,0x2a,0x44};
    bool         a58_bits[256] = {false,false,true,false,false,false,true,false,false,true,false,true,false,true,false,false,true,false,true,true,false,false,false,true,true,true,false,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,true,false,true,false,true,true,false,true,false,true,true,false,false,true,true,true,true,true,true,false,false,true,false,true,true,true,true,true,true,true,false,true,false,true,true,true,true,false,false,false,false,true,true,false,false,true,true,true,true,false,true,false,false,true,false,false,true,true,false,false,false,false,false,false,false,false,false,false,true,true,true,false,true,false,false,true,false,false,false,true,true,true,false,true,true,true,true,false,false,false,true,true,true,false,false,true,true,true,true,false,true,false,false,true,false,true,true,false,false,false,true,false,false,true,true,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,false,true,true,true,true,false,false,true,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,false,true,true,true,true,false,true,true,false,false,false,false,true,true,false,true,false,true,false,false,false,true,false,false,false,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,false,false,true,false,false,true,false,true,false,true,true,true,false,true,false,true,false,false,true,true};
    uint256_from_bytes(a, a58_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a58_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a59_data[32]  = {0x10,0x5f,0xd9,0xb4,0x2a,0x4f,0x82,0x81,0xdf,0xc2,0x92,0xb2,0x0a,0xee,0x7c,0x15,0xc7,0x01,0x6f,0x5f,0x56,0xf7,0xb2,0xc1,0x16,0x26,0x82,0xcf,0x72,0xbf,0xfe,0x80};
    bool         a59_bits[256] = {false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,true,false,false,true,true,true,false,true,true,true,true,false,false,true,true,false,true,false,false,false,false,false,true,false,true,true,false,false,true,false,false,false,true,true,false,true,false,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,true,false,true,true,true,true,false,true,true,true,true,false,true,true,false,true,false,true,false,true,true,true,true,true,false,true,false,true,true,true,true,false,true,true,false,true,false,false,false,false,false,false,false,true,true,true,false,false,false,true,true,true,false,true,false,true,false,false,false,false,false,true,true,true,true,true,false,false,true,true,true,false,true,true,true,false,true,false,true,false,false,false,false,false,true,false,false,true,true,false,true,false,true,false,false,true,false,false,true,false,true,false,false,false,false,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,false,false,true,false,true,false,false,false,false,false,true,true,true,true,true,false,false,true,false,false,true,false,true,false,true,false,false,false,false,true,false,true,true,false,true,true,false,false,true,true,false,true,true,true,true,true,true,true,false,true,false,false,false,false,false,true,false,false,false};
    uint256_from_bytes(a, a59_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a59_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a60_data[32]  = {0xd5,0x2c,0xdd,0x97,0x49,0xf4,0xfd,0x25,0x75,0x9d,0x6f,0x0b,0x23,0x9e,0x67,0xfc,0xce,0x4a,0x7b,0xed,0xc1,0x2a,0x5e,0x62,0x06,0x02,0x4d,0xdb,0x9a,0x9c,0x9f,0x73};
    bool         a60_bits[256] = {true,true,false,false,true,true,true,false,true,true,true,true,true,false,false,true,false,false,true,true,true,false,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,false,true,true,true,false,true,true,false,false,true,false,false,true,false,false,false,false,false,false,false,true,true,false,false,false,false,false,false,true,false,false,false,true,true,false,false,true,true,true,true,false,true,false,false,true,false,true,false,true,false,false,true,false,false,false,false,false,true,true,true,false,true,true,false,true,true,true,true,true,false,true,true,true,true,false,false,true,false,true,false,false,true,false,false,true,true,true,false,false,true,true,false,false,true,true,true,true,true,true,true,true,true,false,false,true,true,false,false,true,true,true,true,false,false,true,true,true,false,false,false,true,false,false,true,true,false,true,false,false,false,false,true,true,true,true,false,true,true,false,true,false,true,true,true,false,false,true,true,false,true,false,true,true,true,false,true,false,true,false,false,true,false,false,true,false,true,true,true,true,true,true,false,false,true,false,true,true,true,true,true,false,false,true,false,false,true,false,true,true,true,false,true,false,false,true,true,false,true,true,true,false,true,true,false,false,true,true,false,true,false,false,true,false,true,false,true,false,true,true};
    uint256_from_bytes(a, a60_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a60_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a61_data[32]  = {0x16,0xd9,0xe3,0xb5,0x39,0xc1,0x1a,0x2e,0xf5,0x2d,0xb9,0x76,0x69,0x30,0xaa,0xcf,0xa5,0xd3,0xbb,0xb2,0x35,0xf8,0x2d,0x64,0x4b,0x60,0xbd,0xc3,0x15,0xdb,0xd4,0xf5};
    bool         a61_bits[256] = {true,false,true,false,true,true,true,true,false,false,true,false,true,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,true,false,false,false,true,true,false,false,false,false,true,true,true,false,true,true,true,true,false,true,false,false,false,false,false,true,true,false,true,true,false,true,false,false,true,false,false,false,true,false,false,true,true,false,true,false,true,true,false,true,false,false,false,false,false,true,true,true,true,true,true,false,true,false,true,true,false,false,false,true,false,false,true,true,false,true,true,true,false,true,true,true,false,true,true,true,false,false,true,false,true,true,true,false,true,false,false,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,false,true,false,true,false,false,false,false,true,true,false,false,true,false,false,true,false,true,true,false,false,true,true,false,true,true,true,false,true,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true,false,true,true,true,false,true,false,false,false,true,false,true,true,false,false,false,true,false,false,false,false,false,true,true,true,false,false,true,true,true,false,false,true,false,true,false,true,true,false,true,true,true,false,false,false,true,true,true,true,false,false,true,true,false,true,true,false,true,true,false,true,false,false,false};
    uint256_from_bytes(a, a61_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a61_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a62_data[32]  = {0x33,0x26,0x50,0xa3,0x26,0x92,0x81,0x1f,0xba,0xfd,0x0d,0x8b,0x32,0xea,0xd3,0x5b,0xc9,0x46,0x38,0x6e,0xa8,0xe4,0x5d,0x39,0x57,0x03,0x9d,0x40,0x8e,0xa3,0xea,0x4b};
    bool         a62_bits[256] = {true,true,false,true,false,false,true,false,false,true,false,true,false,true,true,true,true,true,false,false,false,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,false,false,true,false,true,false,true,true,true,false,false,true,true,true,false,false,false,false,false,false,true,true,true,false,true,false,true,false,true,false,false,true,true,true,false,false,true,false,true,true,true,false,true,false,false,false,true,false,false,true,true,true,false,false,false,true,false,true,false,true,false,true,true,true,false,true,true,false,false,false,false,true,true,true,false,false,false,true,true,false,false,false,true,false,true,false,false,true,false,false,true,true,true,true,false,true,true,false,true,false,true,true,false,false,true,false,true,true,false,true,false,true,false,true,true,true,false,true,false,false,true,true,false,false,true,true,false,true,false,false,false,true,true,false,true,true,false,false,false,false,true,false,true,true,true,true,true,true,false,true,false,true,true,true,false,true,true,true,true,true,true,false,false,false,true,false,false,false,false,false,false,true,false,true,false,false,true,false,false,true,false,true,true,false,false,true,false,false,true,true,false,false,false,true,false,true,false,false,false,false,true,false,true,false,false,true,true,false,false,true,false,false,true,true,false,false,true,true,false,false};
    uint256_from_bytes(a, a62_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a62_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a63_data[32]  = {0x74,0x1c,0xf4,0xc1,0x4a,0x7e,0x83,0x9f,0xd0,0x2d,0x25,0xab,0x58,0x24,0xdc,0x84,0x8f,0x04,0x8a,0x02,0xe4,0x35,0x1d,0x77,0xb8,0xb5,0xd0,0x38,0xe1,0xad,0xfd,0x55};
    bool         a63_bits[256] = {true,false,true,false,true,false,true,false,true,false,true,true,true,true,true,true,true,false,true,true,false,true,false,true,true,false,false,false,false,true,true,true,false,false,false,true,true,true,false,false,false,false,false,false,true,false,true,true,true,false,true,false,true,true,false,true,false,false,false,true,true,true,false,true,true,true,true,false,true,true,true,false,true,false,true,true,true,false,false,false,true,false,true,false,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,false,false,false,false,false,false,true,false,true,false,false,false,true,false,false,true,false,false,false,false,false,true,true,true,true,false,false,false,true,false,false,true,false,false,false,false,true,false,false,true,true,true,false,true,true,false,false,true,false,false,true,false,false,false,false,false,true,true,false,true,false,true,true,false,true,false,true,false,true,true,false,true,false,false,true,false,false,true,false,true,true,false,true,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,false,false,true,true,true,false,false,false,false,false,true,false,true,true,true,true,true,true,false,false,true,false,true,false,false,true,false,true,false,false,false,false,false,true,true,false,false,true,false,true,true,true,true,false,false,true,true,true,false,false,false,false,false,true,false,true,true,true,false};
    uint256_from_bytes(a, a63_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a63_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a64_data[32]  = {0x9b,0x4f,0x83,0x1c,0x8f,0x07,0x16,0xda,0x96,0x70,0x58,0xe1,0x01,0xde,0xd0,0x42,0xec,0x37,0x29,0x15,0x41,0x2a,0x30,0x80,0xb7,0x8f,0x91,0xea,0x6c,0x68,0xbe,0xab};
    bool         a64_bits[256] = {true,true,false,true,false,true,false,true,false,true,true,true,true,true,false,true,false,false,false,true,false,true,true,false,false,false,true,true,false,true,true,false,false,true,false,true,false,true,true,true,true,false,false,false,true,false,false,true,true,true,true,true,false,false,false,true,true,true,true,false,true,true,false,true,false,false,false,false,false,false,false,true,false,false,false,false,true,true,false,false,false,true,false,true,false,true,false,false,true,false,false,false,false,false,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,true,false,false,true,true,true,false,true,true,false,false,false,false,true,true,false,true,true,true,false,true,false,false,false,false,true,false,false,false,false,false,true,false,true,true,false,true,true,true,true,false,true,true,true,false,false,false,false,false,false,false,true,false,false,false,false,true,true,true,false,false,false,true,true,false,true,false,false,false,false,false,true,true,true,false,false,true,true,false,true,false,false,true,false,true,false,true,true,false,true,true,false,true,true,false,true,false,false,false,true,true,true,false,false,false,false,false,true,true,true,true,false,false,false,true,false,false,true,true,true,false,false,false,true,true,false,false,false,false,false,true,true,true,true,true,false,false,true,false,true,true,false,true,true,false,false,true};
    uint256_from_bytes(a, a64_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a64_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a65_data[32]  = {0x98,0x60,0xf3,0x4f,0xb3,0xf7,0xbf,0x4d,0x82,0x05,0x18,0x23,0x07,0x68,0x12,0xde,0xf4,0xfb,0xa7,0xca,0x2c,0xa5,0x70,0x8f,0xc3,0xc8,0x79,0x4a,0x4f,0x7c,0x98,0x96};
    bool         a65_bits[256] = {false,true,true,false,true,false,false,true,false,false,false,true,true,false,false,true,false,false,true,true,true,true,true,false,true,true,true,true,false,false,true,false,false,true,false,true,false,false,true,false,true,false,false,true,true,true,true,false,false,false,false,true,false,false,true,true,true,true,false,false,false,false,true,true,true,true,true,true,false,false,false,true,false,false,false,false,true,true,true,false,true,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,false,true,false,true,false,false,true,true,true,true,true,false,false,true,false,true,true,true,false,true,true,true,true,true,false,false,true,false,true,true,true,true,false,true,true,true,true,false,true,true,false,true,false,false,true,false,false,false,false,false,false,true,false,true,true,false,true,true,true,false,false,false,false,false,true,true,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,false,true,false,false,false,false,false,false,true,false,false,false,false,false,true,true,false,true,true,false,false,true,false,true,true,true,true,true,true,false,true,true,true,true,false,true,true,true,true,true,true,false,false,true,true,false,true,true,true,true,true,false,false,true,false,true,true,false,false,true,true,true,true,false,false,false,false,false,true,true,false,false,false,false,true,true,false,false,true};
    uint256_from_bytes(a, a65_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a65_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a66_data[32]  = {0x03,0x3d,0xfb,0xa5,0x18,0xd3,0x49,0xa8,0xc2,0x47,0xa1,0xad,0x41,0x9a,0x67,0x1e,0x5b,0xe7,0x22,0x94,0x38,0x0e,0x4c,0x4f,0xbc,0x8c,0x73,0x21,0x72,0x6b,0x79,0x29};
    bool         a66_bits[256] = {true,false,false,true,false,true,false,false,true,false,false,true,true,true,true,false,true,true,false,true,false,true,true,false,false,true,false,false,true,true,true,false,true,false,false,false,false,true,false,false,true,true,false,false,true,true,true,false,false,false,true,true,false,false,false,true,false,false,true,true,true,true,false,true,true,true,true,true,false,false,true,false,false,false,true,true,false,false,true,false,false,true,true,true,false,false,false,false,false,false,false,true,true,true,false,false,false,false,true,false,true,false,false,true,false,true,false,false,false,true,false,false,true,true,true,false,false,true,true,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,false,true,true,true,false,false,true,true,false,false,true,false,true,true,false,false,true,true,false,false,false,false,false,true,false,true,false,true,true,false,true,false,true,true,false,false,false,false,true,false,true,true,true,true,false,false,false,true,false,false,true,false,false,false,false,true,true,false,false,false,true,false,true,false,true,true,false,false,true,false,false,true,false,true,true,false,false,true,false,true,true,false,false,false,true,true,false,false,false,true,false,true,false,false,true,false,true,true,true,false,true,true,true,true,true,true,false,true,true,true,true,false,false,true,true,false,false,false,false,false,false};
    uint256_from_bytes(a, a66_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a66_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a67_data[32]  = {0xa6,0x69,0x78,0xa2,0xfe,0x2e,0xa7,0x98,0xd8,0xf6,0x5c,0xb5,0x6c,0x75,0x80,0x0e,0x63,0x8e,0xa0,0x92,0x2e,0xab,0x07,0xa2,0x74,0x32,0xc9,0x7d,0x29,0x9b,0x48,0x7d};
    bool         a67_bits[256] = {true,false,true,true,true,true,true,false,false,false,false,true,false,false,true,false,true,true,false,true,true,false,false,true,true,false,false,true,false,true,false,false,true,false,true,true,true,true,true,false,true,false,false,true,false,false,true,true,false,true,false,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,false,false,false,true,false,true,true,true,true,false,false,false,false,false,true,true,false,true,false,true,false,true,false,true,true,true,false,true,false,false,false,true,false,false,true,false,false,true,false,false,false,false,false,true,false,true,false,true,true,true,false,false,false,true,true,true,false,false,false,true,true,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,false,true,true,true,false,false,false,true,true,false,true,true,false,true,false,true,false,true,true,false,true,false,false,true,true,true,false,true,false,false,true,true,false,true,true,true,true,false,false,false,true,true,false,true,true,false,false,false,true,true,false,false,true,true,true,true,false,false,true,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,true,true,true,false,true,false,false,false,true,false,true,false,false,false,true,true,true,true,false,true,false,false,true,false,true,true,false,false,true,true,false,false,true,false,true};
    uint256_from_bytes(a, a67_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a67_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a68_data[32]  = {0x10,0xb8,0x81,0x07,0x70,0x3e,0xae,0xda,0xab,0x69,0x8c,0xf6,0x62,0x48,0x15,0x4f,0x40,0x1c,0x21,0x74,0x48,0xe3,0x3e,0x68,0xd9,0xb7,0xbb,0x41,0xdb,0x83,0x82,0x6f};
    bool         a68_bits[256] = {true,true,true,true,false,true,true,false,false,true,false,false,false,false,false,true,true,true,false,false,false,false,false,true,true,true,false,true,true,false,true,true,true,false,false,false,false,false,true,false,true,true,false,true,true,true,false,true,true,true,true,false,true,true,false,true,true,false,false,true,true,false,true,true,false,false,false,true,false,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,true,true,false,false,false,true,false,false,true,false,false,false,true,false,true,true,true,false,true,false,false,false,false,true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,false,false,true,false,true,false,true,false,true,false,false,false,false,false,false,true,false,false,true,false,false,true,false,false,false,true,true,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,false,true,true,false,false,true,false,true,true,false,true,true,false,true,false,true,false,true,false,true,false,true,true,false,true,true,false,true,true,true,false,true,false,true,false,true,true,true,true,true,false,false,false,false,false,false,true,true,true,false,true,true,true,false,false,false,false,false,true,false,false,false,false,false,false,true,false,false,false,true,true,true,false,true,false,false,false,false,true,false,false,false};
    uint256_from_bytes(a, a68_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a68_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a69_data[32]  = {0x72,0x2b,0x76,0x34,0x91,0x24,0x1a,0xcf,0xb4,0x65,0x89,0x89,0xb9,0xef,0x6e,0xca,0xb2,0x54,0xd9,0x66,0x03,0x46,0xee,0x0c,0xfa,0xb1,0xe3,0x55,0x12,0x7f,0xaf,0xf8};
    bool         a69_bits[256] = {false,false,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,true,true,true,true,true,true,false,false,true,false,false,true,false,false,false,true,false,true,false,true,false,true,false,true,true,false,false,false,true,true,true,true,false,false,false,true,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,false,false,false,false,false,true,true,true,false,true,true,true,false,true,true,false,false,false,true,false,true,true,false,false,false,false,false,false,false,true,true,false,false,true,true,false,true,false,false,true,true,false,true,true,false,false,true,false,true,false,true,false,false,true,false,false,true,true,false,true,false,true,false,true,false,false,true,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,false,false,false,true,true,false,false,true,false,false,false,true,true,false,true,false,false,true,true,false,false,false,true,false,true,true,false,true,true,true,true,true,false,false,true,true,false,true,false,true,true,false,false,false,false,false,true,false,false,true,false,false,true,false,false,false,true,false,false,true,false,false,true,false,true,true,false,false,false,true,true,false,true,true,true,false,true,true,false,true,false,true,false,false,false,true,false,false,true,true,true,false};
    uint256_from_bytes(a, a69_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a69_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a70_data[32]  = {0x80,0x42,0x33,0xe7,0x69,0x83,0x8f,0xc1,0xb6,0xa9,0xad,0xf8,0x8e,0xa3,0x0f,0xdc,0x81,0x01,0x07,0xb0,0x40,0x7b,0xcb,0x2d,0xc0,0x13,0x6c,0x43,0x5b,0xd8,0x0e,0x92};
    bool         a70_bits[256] = {false,true,false,false,true,false,false,true,false,true,true,true,false,false,false,false,false,false,false,true,true,false,true,true,true,true,false,true,true,false,true,false,true,true,false,false,false,false,true,false,false,false,true,true,false,true,true,false,true,true,false,false,true,false,false,false,false,false,false,false,false,false,true,true,true,false,true,true,false,true,false,false,true,true,false,true,false,false,true,true,true,true,false,true,true,true,true,false,false,false,false,false,false,false,true,false,false,false,false,false,true,true,false,true,true,true,true,false,false,false,false,false,true,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true,false,false,true,true,true,false,true,true,true,true,true,true,false,false,false,false,true,true,false,false,false,true,false,true,false,true,true,true,false,false,false,true,false,false,false,true,true,true,true,true,true,false,true,true,false,true,false,true,true,false,false,true,false,true,false,true,false,true,true,false,true,true,false,true,true,false,false,false,false,false,true,true,true,true,true,true,false,false,false,true,true,true,false,false,false,false,false,true,true,false,false,true,false,true,true,false,true,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,false,true,false,false,false,false,true,false,false,false,false,false,false,false,false,true};
    uint256_from_bytes(a, a70_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a70_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a71_data[32]  = {0xc7,0xf0,0x68,0x86,0x8a,0x30,0x41,0x4e,0x18,0x9c,0xbd,0xa8,0xbe,0x46,0xb3,0x5e,0xfa,0x6b,0x5e,0x1f,0xd7,0x16,0xf3,0x9d,0xa0,0xa6,0xd7,0xff,0x8f,0xb3,0xe5,0x91};
    bool         a71_bits[256] = {true,false,false,false,true,false,false,true,true,false,true,false,false,true,true,true,true,true,false,false,true,true,false,true,true,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,false,true,false,true,false,false,false,false,false,true,false,true,true,false,true,true,true,false,false,true,true,true,false,false,true,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,true,false,true,true,true,true,true,true,true,false,false,false,false,true,true,true,true,false,true,false,true,true,false,true,false,true,true,false,false,true,false,true,true,true,true,true,false,true,true,true,true,false,true,false,true,true,false,false,true,true,false,true,false,true,true,false,false,false,true,false,false,true,true,true,true,true,false,true,false,false,false,true,false,true,false,true,true,false,true,true,true,true,false,true,false,false,true,true,true,false,false,true,false,false,false,true,true,false,false,false,false,true,true,true,false,false,true,false,true,false,false,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,false,true,false,false,false,true,false,true,true,false,false,false,false,true,false,false,false,true,false,true,true,false,false,false,false,false,true,true,true,true,true,true,true,false,false,false,true,true};
    uint256_from_bytes(a, a71_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a71_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a72_data[32]  = {0xf4,0xa6,0x82,0x84,0x97,0x6d,0xa4,0x6d,0x6c,0x67,0x8a,0xdf,0x90,0x13,0xce,0xf4,0x0a,0x0a,0x71,0x56,0xc4,0x26,0x65,0xeb,0x56,0x6d,0xd6,0x9b,0x72,0x68,0x74,0x51};
    bool         a72_bits[256] = {true,false,false,false,true,false,true,false,false,false,true,false,true,true,true,false,false,false,false,true,false,true,true,false,false,true,false,false,true,true,true,false,true,true,false,true,true,false,false,true,false,true,true,false,true,false,true,true,true,false,true,true,false,true,true,false,false,true,true,false,true,false,true,false,true,true,false,true,false,true,true,true,true,false,true,false,false,true,true,false,false,true,true,false,false,true,false,false,false,false,true,false,false,false,true,true,false,true,true,false,true,false,true,false,true,false,false,false,true,true,true,false,false,true,false,true,false,false,false,false,false,true,false,true,false,false,false,false,false,false,true,false,true,true,true,true,false,true,true,true,false,false,true,true,true,true,false,false,true,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,false,true,true,false,true,false,true,false,false,false,true,true,true,true,false,false,true,true,false,false,false,true,true,false,true,true,false,true,false,true,true,false,true,true,false,false,false,true,false,false,true,false,true,true,false,true,true,false,true,true,false,true,true,true,false,true,false,false,true,false,false,true,false,false,false,false,true,false,true,false,false,false,false,false,true,false,true,true,false,false,true,false,true,false,false,true,false,true,true,true,true};
    uint256_from_bytes(a, a72_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a72_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a73_data[32]  = {0x02,0x2e,0x05,0x73,0x00,0xd8,0xa5,0x7e,0xea,0xb9,0x0e,0x92,0x78,0x79,0x4b,0xa9,0x10,0xff,0x9b,0xdb,0x86,0x3e,0x6d,0xfb,0x3b,0x7b,0xac,0x7b,0xb3,0xae,0xc3,0xf6};
    bool         a73_bits[256] = {false,true,true,false,true,true,true,true,true,true,false,false,false,false,true,true,false,true,true,true,false,true,false,true,true,true,false,false,true,true,false,true,true,true,false,true,true,true,true,false,false,false,true,true,false,true,false,true,true,true,false,true,true,true,true,false,true,true,false,true,true,true,false,false,true,true,false,true,true,true,true,true,true,false,true,true,false,true,true,false,false,true,true,true,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,false,false,true,true,true,true,true,true,true,true,true,false,false,false,false,true,false,false,false,true,false,false,true,false,true,false,true,true,true,false,true,false,false,true,false,true,false,false,true,true,true,true,false,false,false,false,true,true,true,true,false,false,true,false,false,true,false,false,true,false,true,true,true,false,false,false,false,true,false,false,true,true,true,false,true,false,true,false,true,false,true,true,true,false,true,true,true,true,true,true,false,true,false,true,false,false,true,false,true,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,false,true,true,false,false,true,true,true,false,true,false,true,false,false,false,false,false,false,true,true,true,false,true,false,false,false,true,false,false,false,false,false,false};
    uint256_from_bytes(a, a73_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a73_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a74_data[32]  = {0x57,0xb7,0x15,0x2a,0xd2,0x60,0x80,0x37,0x95,0x63,0xb3,0xdd,0xb5,0x87,0x4a,0xf6,0xf4,0xa2,0x99,0xaa,0x75,0x2e,0x58,0xf8,0x45,0xf8,0x60,0x9b,0x60,0x4e,0x2a,0xb9};
    bool         a74_bits[256] = {true,false,false,true,true,true,false,true,false,true,false,true,false,true,false,false,false,true,true,true,false,false,true,false,false,false,false,false,false,true,true,false,true,true,false,true,true,false,false,true,false,false,false,false,false,true,true,false,false,false,false,true,true,true,true,true,true,false,true,false,false,false,true,false,false,false,false,true,true,true,true,true,false,false,false,true,true,false,true,false,false,true,true,true,false,true,false,false,true,false,true,false,true,true,true,false,false,true,false,true,false,true,false,true,true,false,false,true,true,false,false,true,false,true,false,false,false,true,false,true,false,false,true,false,true,true,true,true,false,true,true,false,true,true,true,true,false,true,false,true,false,false,true,false,true,true,true,false,false,false,false,true,true,false,true,false,true,true,false,true,true,false,true,true,true,false,true,true,true,true,false,false,true,true,false,true,true,true,false,false,false,true,true,false,true,false,true,false,true,false,false,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,true,true,false,false,true,false,false,true,false,true,true,false,true,false,true,false,true,false,false,true,false,true,false,true,false,false,false,true,true,true,false,true,true,false,true,true,true,true,false,true,false,true,false};
    uint256_from_bytes(a, a74_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a74_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a75_data[32]  = {0x50,0xd4,0x6e,0x4f,0xf7,0x7b,0x65,0xb4,0xb9,0xd0,0x6c,0x3a,0x9d,0x3d,0x61,0x42,0x32,0xe6,0xfe,0x59,0xe5,0xbf,0xe2,0xe1,0x17,0x48,0xba,0x9f,0xfc,0xbe,0x2a,0xe3};
    bool         a75_bits[256] = {true,true,false,false,false,true,true,true,false,true,false,true,false,true,false,false,false,true,true,true,true,true,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,false,false,true,false,true,false,true,true,true,false,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,false,false,false,false,true,true,true,false,true,false,false,false,true,true,true,true,true,true,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,true,true,false,true,false,false,true,true,true,true,true,true,true,false,true,true,false,false,true,true,true,false,true,false,false,true,true,false,false,false,true,false,false,false,false,true,false,true,false,false,false,false,true,true,false,true,false,true,true,true,true,false,false,true,false,true,true,true,false,false,true,false,true,false,true,true,true,false,false,false,false,true,true,false,true,true,false,false,false,false,false,true,false,true,true,true,false,false,true,true,true,false,true,false,false,true,false,true,true,false,true,true,false,true,false,false,true,true,false,true,true,false,true,true,true,true,false,true,true,true,false,true,true,true,true,true,true,true,true,false,false,true,false,false,true,true,true,false,true,true,false,false,false,true,false,true,false,true,true,false,false,false,false,true,false,true,false};
    uint256_from_bytes(a, a75_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a75_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a76_data[32]  = {0x43,0x26,0x7f,0x3f,0x13,0xd3,0xde,0xff,0x91,0xc5,0xcc,0xd8,0x74,0xa6,0xa5,0xbd,0x2f,0xdf,0xfd,0xee,0x08,0x30,0x49,0x87,0x7c,0x26,0x45,0x9d,0x24,0x95,0x07,0x4c};
    bool         a76_bits[256] = {false,false,true,true,false,false,true,false,true,true,true,false,false,false,false,false,true,false,true,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,true,true,true,false,false,true,true,false,true,false,false,false,true,false,false,true,true,false,false,true,false,false,false,false,true,true,true,true,true,false,true,true,true,false,false,false,false,true,true,false,false,true,false,false,true,false,false,false,false,false,true,true,false,false,false,false,false,true,false,false,false,false,false,true,true,true,false,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,false,true,false,false,true,false,true,true,true,true,false,true,true,false,true,false,false,true,false,true,false,true,true,false,false,true,false,true,false,false,true,false,true,true,true,false,false,false,false,true,true,false,true,true,false,false,true,true,false,false,true,true,true,false,true,false,false,false,true,true,true,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,false,true,true,true,true,false,false,true,false,true,true,true,true,false,false,true,false,false,false,true,true,true,true,true,true,false,false,true,true,true,true,true,true,true,false,false,true,true,false,false,true,false,false,true,true,false,false,false,false,true,false};
    uint256_from_bytes(a, a76_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a76_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a77_data[32]  = {0x27,0xf7,0x3d,0x9e,0xff,0x8c,0x56,0xc7,0xc1,0x42,0xed,0x40,0xe7,0xfb,0xbf,0xdd,0xba,0x56,0xc6,0x91,0x94,0xba,0x12,0xec,0x40,0x72,0x7e,0x89,0x7e,0x7a,0xc8,0x9d};
    bool         a77_bits[256] = {true,false,true,true,true,false,false,true,false,false,false,true,false,false,true,true,false,true,false,true,true,true,true,false,false,true,true,true,true,true,true,false,true,false,false,true,false,false,false,true,false,true,true,true,true,true,true,false,false,true,false,false,true,true,true,false,false,false,false,false,false,false,true,false,false,false,true,true,false,true,true,true,false,true,false,false,true,false,false,false,false,true,false,true,true,true,false,true,false,false,true,false,true,false,false,true,true,false,false,false,true,false,false,true,false,true,true,false,false,false,true,true,false,true,true,false,true,false,true,false,false,true,false,true,true,true,false,true,true,false,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,true,false,true,true,true,true,true,true,true,true,false,false,true,true,true,false,false,false,false,false,false,true,false,true,false,true,true,false,true,true,true,false,true,false,false,false,false,true,false,true,false,false,false,false,false,true,true,true,true,true,false,false,false,true,true,false,true,true,false,true,false,true,false,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,false,false,true,true,false,true,true,true,true,false,false,true,true,true,false,true,true,true,true,true,true,true,false,false,true,false,false};
    uint256_from_bytes(a, a77_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a77_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a78_data[32]  = {0x69,0xd0,0xd1,0x7d,0x7d,0x1c,0x7f,0xfd,0x6e,0x53,0x5e,0x86,0x87,0xd0,0xe6,0x80,0x45,0x29,0xd9,0x76,0x62,0x78,0x2d,0xb9,0x9a,0x40,0x56,0x9f,0xaa,0xc1,0x8b,0x78};
    bool         a78_bits[256] = {false,false,false,true,true,true,true,false,true,true,false,true,false,false,false,true,true,false,false,false,false,false,true,true,false,true,false,true,false,true,false,true,true,true,true,true,true,false,false,true,false,true,true,false,true,false,true,false,false,false,false,false,false,false,true,false,false,true,false,true,true,false,false,true,true,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,false,false,false,true,true,true,true,false,false,true,false,false,false,true,true,false,false,true,true,false,true,true,true,false,true,false,false,true,true,false,true,true,true,false,false,true,false,true,false,false,true,false,true,false,false,false,true,false,false,false,false,false,false,false,false,true,false,true,true,false,false,true,true,true,false,false,false,false,true,false,true,true,true,true,true,false,false,false,false,true,false,true,true,false,false,false,false,true,false,true,true,true,true,false,true,false,true,true,false,false,true,false,true,false,false,true,true,true,false,true,true,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,true,true,true,false,false,false,true,false,true,true,true,true,true,false,true,false,true,true,true,true,true,false,true,false,false,false,true,false,true,true,false,false,false,false,true,false,true,true,true,false,false,true,false,true,true,false};
    uint256_from_bytes(a, a78_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a78_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a79_data[32]  = {0xcb,0xdb,0xe0,0x51,0x16,0xe2,0x3a,0xf2,0x20,0x30,0xd6,0x00,0x4d,0xaf,0xfa,0xd1,0x91,0xc5,0xbb,0x69,0x83,0xd2,0xcb,0xcd,0xcb,0x29,0x15,0x75,0xd3,0xaa,0x74,0x42};
    bool         a79_bits[256] = {false,true,false,false,false,false,true,false,false,false,true,false,true,true,true,false,false,true,false,true,false,true,false,true,true,true,false,false,true,false,true,true,true,false,true,false,true,true,true,false,true,false,true,false,true,false,false,false,true,false,false,true,false,true,false,false,true,true,false,true,false,false,true,true,true,false,true,true,false,false,true,true,true,true,false,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,false,false,false,false,false,true,true,false,false,true,false,true,true,false,true,true,false,true,true,true,false,true,true,false,true,false,false,false,true,true,true,false,false,false,true,false,false,true,true,false,false,false,true,false,true,true,false,true,false,true,true,true,true,true,true,true,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,true,true,false,true,false,true,true,false,false,false,false,true,true,false,false,false,false,false,false,false,true,false,false,false,true,false,false,true,true,true,true,false,true,false,true,true,true,false,false,false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,true,false,false,false,false,false,false,true,true,true,true,true,false,true,true,false,true,true,true,true,false,true,false,false,true,true};
    uint256_from_bytes(a, a79_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a79_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a80_data[32]  = {0x9d,0x4a,0x21,0x09,0x3a,0x24,0x7e,0x5b,0xd4,0x25,0xc5,0x18,0x0d,0xf1,0x6d,0xa1,0x94,0xd6,0xd0,0xee,0x8f,0x8f,0x6a,0x1a,0x40,0xee,0x46,0x8f,0x71,0x60,0x01,0xc0};
    bool         a80_bits[256] = {false,false,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,false,false,false,true,true,true,false,true,true,true,true,false,false,false,true,false,true,true,false,false,false,true,false,false,true,true,true,false,true,true,true,false,false,false,false,false,false,true,false,false,true,false,true,true,false,false,false,false,true,false,true,false,true,true,false,true,true,true,true,false,false,false,true,true,true,true,true,false,false,false,true,false,true,true,true,false,true,true,true,false,false,false,false,true,false,true,true,false,true,true,false,true,false,true,true,false,false,true,false,true,false,false,true,true,false,false,false,false,true,false,true,true,false,true,true,false,true,true,false,true,false,false,false,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,true,true,false,false,false,true,false,true,false,false,false,true,true,true,false,true,false,false,true,false,false,false,false,true,false,true,false,true,true,true,true,false,true,true,false,true,false,false,true,true,true,true,true,true,false,false,false,true,false,false,true,false,false,false,true,false,true,true,true,false,false,true,false,false,true,false,false,false,false,true,false,false,false,false,true,false,false,false,true,false,true,false,false,true,false,true,false,true,true,true,false,false,true};
    uint256_from_bytes(a, a80_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a80_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a81_data[32]  = {0x75,0xa5,0x10,0x73,0xea,0x8b,0xf5,0x2c,0xde,0xa7,0xdc,0x2b,0x54,0x8c,0x5a,0x89,0xc8,0xf3,0xb8,0x2c,0x5e,0x10,0x7b,0xf5,0x20,0x93,0xbd,0x6c,0xbe,0x81,0x3b,0xfe};
    bool         a81_bits[256] = {false,true,true,true,true,true,true,true,true,true,false,true,true,true,false,false,true,false,false,false,false,false,false,true,false,true,true,true,true,true,false,true,false,false,true,true,false,true,true,false,true,false,true,true,true,true,false,true,true,true,false,false,true,false,false,true,false,false,false,false,false,true,false,false,true,false,true,false,true,true,true,true,true,true,false,true,true,true,true,false,false,false,false,false,true,false,false,false,false,true,true,true,true,false,true,false,false,false,true,true,false,true,false,false,false,false,false,true,true,true,false,true,true,true,false,false,true,true,true,true,false,false,false,true,false,false,true,true,true,false,false,true,false,false,false,true,false,true,false,true,true,false,true,false,false,false,true,true,false,false,false,true,false,false,true,false,true,false,true,false,true,true,false,true,false,true,false,false,false,false,true,true,true,false,true,true,true,true,true,false,false,true,false,true,false,true,true,true,true,false,true,true,false,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true,true,true,false,true,false,false,false,true,false,true,false,true,false,true,true,true,true,true,false,false,true,true,true,false,false,false,false,false,true,false,false,false,true,false,true,false,false,true,false,true,true,false,true,false,true,true,true,false};
    uint256_from_bytes(a, a81_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a81_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a82_data[32]  = {0x90,0x7f,0xc7,0x9c,0x1c,0x02,0xd7,0xb9,0x1b,0x80,0xae,0x70,0x6c,0xa7,0xc2,0xef,0xf9,0xa7,0x5b,0x9e,0xaa,0x20,0xc4,0x35,0xf5,0x3f,0x72,0xc5,0x4f,0xd5,0x63,0x88};
    bool         a82_bits[256] = {false,false,false,true,false,false,false,true,true,true,false,false,false,true,true,false,true,false,true,false,true,false,true,true,true,true,true,true,false,false,true,false,true,false,true,false,false,false,true,true,false,true,false,false,true,true,true,false,true,true,true,true,true,true,false,false,true,false,true,false,true,true,true,true,true,false,true,false,true,true,false,false,false,false,true,false,false,false,true,true,false,false,false,false,false,true,false,false,false,true,false,true,false,true,false,true,false,true,true,true,true,false,false,true,true,true,false,true,true,false,true,false,true,true,true,false,false,true,false,true,true,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,false,true,false,false,false,false,true,true,true,true,true,false,false,true,false,true,false,false,true,true,false,true,true,false,false,false,false,false,true,true,true,false,false,true,true,true,false,true,false,true,false,false,false,false,false,false,false,true,true,true,false,true,true,false,false,false,true,false,false,true,true,true,false,true,true,true,true,false,true,false,true,true,false,true,false,false,false,false,false,false,false,false,true,true,true,false,false,false,false,false,true,true,true,false,false,true,true,true,true,false,false,false,true,true,true,true,true,true,true,true,true,false,false,false,false,false,true,false,false,true};
    uint256_from_bytes(a, a82_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a82_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a83_data[32]  = {0xc3,0x64,0x6b,0x2b,0xe2,0x35,0xae,0xe1,0xe3,0x2f,0xb4,0x21,0x58,0xd3,0x1d,0x56,0xe3,0xcf,0x47,0x93,0x7c,0x0c,0xa2,0xa8,0x34,0x82,0x80,0x33,0xbc,0x06,0xc3,0x20};
    bool         a83_bits[256] = {false,false,false,false,false,true,false,false,true,true,false,false,false,false,true,true,false,true,true,false,false,false,false,false,false,false,true,true,true,true,false,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false,false,true,false,true,false,false,false,false,false,true,false,false,true,false,true,true,false,false,false,false,false,true,false,true,false,true,false,true,false,false,false,true,false,true,false,false,true,true,false,false,false,false,false,false,true,true,true,true,true,false,true,true,false,false,true,false,false,true,true,true,true,false,false,false,true,false,true,true,true,true,false,false,true,true,true,true,false,false,false,true,true,true,false,true,true,false,true,false,true,false,true,false,true,true,true,false,false,false,true,true,false,false,true,false,true,true,false,false,false,true,true,false,true,false,true,false,false,false,false,true,false,false,false,false,true,false,true,true,false,true,true,true,true,true,false,true,false,false,true,true,false,false,false,true,true,true,true,false,false,false,false,true,true,true,false,true,true,true,false,true,false,true,true,false,true,false,true,true,false,false,false,true,false,false,false,true,true,true,true,true,false,true,false,true,false,false,true,true,false,true,false,true,true,false,false,false,true,false,false,true,true,false,true,true,false,false,false,false,true,true};
    uint256_from_bytes(a, a83_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a83_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a84_data[32]  = {0xd0,0x96,0xb1,0x12,0x0c,0x3d,0x9b,0xb2,0x7c,0x95,0x90,0xda,0x74,0x5f,0x37,0x40,0x6d,0xc2,0x21,0x1d,0x66,0xef,0x1d,0x10,0xc8,0xde,0x0d,0x4b,0x05,0xe6,0x72,0xf3};
    bool         a84_bits[256] = {true,true,false,false,true,true,true,true,false,true,false,false,true,true,true,false,false,true,true,false,false,true,true,true,true,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,true,false,true,true,false,false,false,false,false,true,true,true,true,false,true,true,false,false,false,true,false,false,true,true,false,false,false,false,true,false,false,false,true,false,true,true,true,false,false,false,true,true,true,true,false,true,true,true,false,true,true,false,false,true,true,false,true,false,true,true,true,false,false,false,true,false,false,false,false,true,false,false,false,true,false,false,false,false,true,true,true,false,true,true,false,true,true,false,false,false,false,false,false,false,true,false,true,true,true,false,true,true,false,false,true,true,true,true,true,false,true,false,false,false,true,false,true,true,true,false,false,true,false,true,true,false,true,true,false,false,false,false,true,false,false,true,true,false,true,false,true,false,false,true,false,false,true,true,true,true,true,false,false,true,false,false,true,true,false,true,true,true,false,true,true,false,false,true,true,false,true,true,true,true,false,false,false,false,true,true,false,false,false,false,false,true,false,false,true,false,false,false,true,false,false,false,true,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,true,false,true,true};
    uint256_from_bytes(a, a84_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a84_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a85_data[32]  = {0xdd,0xc8,0x08,0x26,0x15,0xa5,0xbf,0x6c,0x03,0xf7,0x07,0x99,0xee,0x0d,0xd4,0x8e,0xea,0x8c,0x90,0x77,0x71,0x00,0xe5,0xbf,0xf1,0x2b,0xcd,0x51,0x01,0x22,0xbb,0x7a};
    bool         a85_bits[256] = {false,true,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,true,false,false,false,true,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,false,true,false,true,false,true,true,false,false,true,true,true,true,false,true,false,true,false,false,true,false,false,false,true,true,true,true,true,true,true,true,true,true,false,true,true,false,true,false,false,true,true,true,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,true,true,true,false,true,true,true,false,false,false,false,false,true,false,false,true,false,false,true,true,false,false,false,true,false,true,false,true,false,true,true,true,false,true,true,true,false,false,false,true,false,false,true,false,true,false,true,true,true,false,true,true,false,false,false,false,false,true,true,true,false,true,true,true,true,false,false,true,true,false,false,true,true,true,true,false,false,false,false,false,true,true,true,false,true,true,true,true,true,true,false,false,false,false,false,false,false,false,true,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,true,false,false,true,false,true,true,false,true,false,true,false,false,false,false,true,true,false,false,true,false,false,false,false,false,true,false,false,false,false,false,false,false,true,false,false,true,true,true,false,true,true,true,false,true,true};
    uint256_from_bytes(a, a85_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a85_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a86_data[32]  = {0x74,0x62,0x9b,0xa5,0xe9,0x76,0x74,0xa7,0x42,0x60,0x0b,0x35,0x82,0xdb,0xa6,0x99,0xc1,0x97,0xe9,0x64,0x84,0x32,0xb6,0xc1,0x88,0x84,0x2b,0x9c,0x9d,0xce,0x48,0x93};
    bool         a86_bits[256] = {true,true,false,false,true,false,false,true,false,false,false,true,false,false,true,false,false,true,true,true,false,false,true,true,true,false,true,true,true,false,false,true,false,false,true,true,true,false,false,true,true,true,false,true,false,true,false,false,false,false,true,false,false,false,false,true,false,false,false,true,false,false,false,true,true,false,false,false,false,false,true,true,false,true,true,false,true,true,false,true,false,true,false,false,true,true,false,false,false,false,true,false,false,false,false,true,false,false,true,false,false,true,true,false,true,false,false,true,false,true,true,true,true,true,true,false,true,false,false,true,true,false,false,false,false,false,true,true,true,false,false,true,true,false,false,true,false,true,true,false,false,true,false,true,true,true,false,true,true,false,true,true,false,true,false,false,false,false,false,true,true,false,true,false,true,true,false,false,true,true,false,true,false,false,false,false,false,false,false,false,false,true,true,false,false,true,false,false,false,false,true,false,true,true,true,false,false,true,false,true,false,false,true,false,true,true,true,false,false,true,true,false,true,true,true,false,true,false,false,true,false,true,true,true,true,false,true,false,false,true,false,true,true,true,false,true,true,false,false,true,false,true,false,false,false,true,true,false,false,false,true,false,true,true,true,false};
    uint256_from_bytes(a, a86_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a86_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a87_data[32]  = {0xa4,0x00,0xd6,0xc9,0x25,0x21,0x09,0x5d,0x8f,0xd4,0xe4,0x50,0xb0,0x5a,0x8c,0xc7,0xa9,0x6e,0x67,0xac,0xb2,0xf8,0x6b,0xbf,0xbf,0x76,0x63,0x99,0xd4,0xcd,0x96,0xec};
    bool         a87_bits[256] = {false,false,true,true,false,true,true,true,false,true,true,false,true,false,false,true,true,false,true,true,false,false,true,true,false,false,true,false,true,false,true,true,true,false,false,true,true,false,false,true,true,true,false,false,false,true,true,false,false,true,true,false,true,true,true,false,true,true,true,true,true,true,false,true,true,true,true,true,true,true,false,true,true,true,false,true,false,true,true,false,false,false,false,true,true,true,true,true,false,true,false,false,true,true,false,true,false,false,true,true,false,true,false,true,true,true,true,false,false,true,true,false,false,true,true,true,false,true,true,false,true,false,false,true,false,true,false,true,true,true,true,false,false,false,true,true,false,false,true,true,false,false,false,true,false,true,false,true,true,false,true,false,false,false,false,false,true,true,false,true,false,false,false,false,true,false,true,false,false,false,true,false,false,true,true,true,false,false,true,false,true,false,true,true,true,true,true,true,false,false,false,true,true,false,true,true,true,false,true,false,true,false,false,true,false,false,false,false,true,false,false,false,false,true,false,false,true,false,true,false,false,true,false,false,true,false,false,true,false,false,true,true,false,true,true,false,true,false,true,true,false,false,false,false,false,false,false,false,false,false,true,false,false,true,false,true};
    uint256_from_bytes(a, a87_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a87_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a88_data[32]  = {0xd7,0xb0,0x4b,0x04,0x46,0x4b,0xdb,0x4e,0x36,0x75,0x49,0x7d,0x8b,0xfb,0x3c,0x8c,0x11,0xb4,0x21,0xbd,0xc8,0x14,0xa8,0xa7,0x82,0x0a,0xe7,0x28,0xc4,0x88,0x08,0xc4};
    bool         a88_bits[256] = {false,false,true,false,false,false,true,true,false,false,false,true,false,false,false,false,false,false,false,true,false,false,false,true,false,false,true,false,false,false,true,true,false,false,false,true,false,true,false,false,true,true,true,false,false,true,true,true,false,true,false,true,false,false,false,false,false,true,false,false,false,false,false,true,true,true,true,false,false,true,false,true,false,false,false,true,false,true,false,true,false,false,true,false,true,false,false,false,false,false,false,true,false,false,true,true,true,false,true,true,true,true,false,true,true,false,false,false,false,true,false,false,false,false,true,false,true,true,false,true,true,false,false,false,true,false,false,false,false,false,true,true,false,false,false,true,false,false,true,true,true,true,false,false,true,true,false,true,true,true,true,true,true,true,false,true,false,false,false,true,true,false,true,true,true,true,true,false,true,false,false,true,false,false,true,false,true,false,true,false,true,true,true,false,false,true,true,false,true,true,false,false,false,true,true,true,false,false,true,false,true,true,false,true,true,false,true,true,true,true,false,true,false,false,true,false,false,true,true,false,false,false,true,false,false,false,true,false,false,false,false,false,true,true,false,true,false,false,true,false,false,false,false,false,true,true,false,true,true,true,true,false,true,false,true,true};
    uint256_from_bytes(a, a88_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a88_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a89_data[32]  = {0xc8,0x3e,0x8f,0x13,0x31,0x77,0xdd,0x4e,0xbd,0x0c,0x3a,0x9a,0x96,0x77,0x2f,0x4f,0xf6,0x9e,0x75,0x00,0xc0,0xf8,0x34,0xb3,0x57,0xcb,0xe6,0x62,0xf5,0x4a,0x1c,0x01};
    bool         a89_bits[256] = {true,false,false,false,false,false,false,false,false,false,true,true,true,false,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,true,true,true,false,true,false,false,false,true,true,false,false,true,true,false,false,true,true,true,true,true,false,true,false,false,true,true,true,true,true,false,true,false,true,false,true,true,false,false,true,true,false,true,false,false,true,false,true,true,false,false,false,false,false,true,true,true,true,true,false,false,false,false,false,false,true,true,false,false,false,false,false,false,false,false,true,false,true,false,true,true,true,false,false,true,true,true,true,false,false,true,false,true,true,false,true,true,true,true,true,true,true,true,false,false,true,false,true,true,true,true,false,true,false,false,true,true,true,false,true,true,true,false,false,true,true,false,true,false,false,true,false,true,false,true,true,false,false,true,false,true,false,true,true,true,false,false,false,false,true,true,false,false,false,false,true,false,true,true,true,true,false,true,false,true,true,true,false,false,true,false,true,false,true,true,true,false,true,true,true,true,true,false,true,true,true,false,true,false,false,false,true,true,false,false,true,true,false,false,true,false,false,false,true,true,true,true,false,false,false,true,false,true,true,true,true,true,false,false,false,false,false,true,false,false,true,true};
    uint256_from_bytes(a, a89_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a89_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a90_data[32]  = {0xbe,0xed,0x0c,0x2d,0xc5,0xfe,0x9c,0x38,0xa6,0x47,0xe1,0x8b,0xf3,0x40,0x7e,0xf6,0xea,0x98,0xdc,0x02,0x15,0x99,0xef,0x30,0x68,0xc5,0xa6,0x08,0xbe,0xb3,0x7b,0x84};
    bool         a90_bits[256] = {false,false,true,false,false,false,false,true,true,true,false,true,true,true,true,false,true,true,false,false,true,true,false,true,false,true,true,true,true,true,false,true,false,false,false,true,false,false,false,false,false,true,true,false,false,true,false,true,true,false,true,false,false,false,true,true,false,false,false,true,false,true,true,false,false,false,false,false,true,true,false,false,true,true,true,true,false,true,true,true,true,false,false,true,true,false,false,true,true,false,true,false,true,false,false,false,false,true,false,false,false,false,false,false,false,false,true,true,true,false,true,true,false,false,false,true,true,false,false,true,false,true,false,true,false,true,true,true,false,true,true,false,true,true,true,true,false,true,true,true,true,true,true,false,false,false,false,false,false,false,true,false,true,true,false,false,true,true,true,true,true,true,false,true,false,false,false,true,true,false,false,false,false,true,true,true,true,true,true,false,false,false,true,false,false,true,true,false,false,true,false,true,false,false,false,true,true,true,false,false,false,false,true,true,true,false,false,true,false,true,true,true,true,true,true,true,true,false,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,false,true,true,false,false,false,false,true,false,true,true,false,true,true,true,false,true,true,true,true,true,false,true};
    uint256_from_bytes(a, a90_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a90_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a91_data[32]  = {0xb6,0x66,0xdf,0x30,0x91,0x9c,0x01,0x23,0xc3,0x3b,0xb1,0x41,0xdc,0xd5,0x06,0x86,0x21,0x3f,0xed,0xc0,0x40,0x05,0xd4,0x5a,0x9a,0x90,0xe4,0x47,0x6e,0xb2,0x07,0x54};
    bool         a91_bits[256] = {false,false,true,false,true,false,true,false,true,true,true,false,false,false,false,false,false,true,false,false,true,true,false,true,false,true,true,true,false,true,true,false,true,true,true,false,false,false,true,false,false,false,true,false,false,true,true,true,false,false,false,false,true,false,false,true,false,true,false,true,true,false,false,true,false,true,false,true,true,false,true,false,false,false,true,false,true,false,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true,true,true,false,true,true,false,true,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,true,false,false,false,true,true,false,false,false,false,true,false,true,true,false,false,false,false,false,true,false,true,false,true,false,true,true,false,false,true,true,true,false,true,true,true,false,false,false,false,false,true,false,true,false,false,false,true,true,false,true,true,true,false,true,true,true,false,false,true,true,false,false,false,false,true,true,true,true,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,false,true,true,true,false,false,true,true,false,false,false,true,false,false,true,false,false,false,false,true,true,false,false,true,true,true,true,true,false,true,true,false,true,true,false,false,true,true,false,false,true,true,false,true,true,false,true};
    uint256_from_bytes(a, a91_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a91_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a92_data[32]  = {0xcc,0xcd,0xa7,0x51,0x72,0x03,0xc9,0xed,0xf4,0xe4,0x36,0x78,0x1a,0xf4,0x89,0x76,0xb3,0x66,0xe4,0x70,0x12,0xd1,0x0f,0x85,0x40,0x84,0x0b,0xda,0xbf,0xc0,0x00,0xe1};
    bool         a92_bits[256] = {true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,false,true,false,true,false,true,true,false,true,true,true,true,false,true,false,false,false,false,false,false,true,false,false,false,false,true,false,false,false,false,false,false,true,false,true,false,true,false,false,false,false,true,true,true,true,true,false,false,false,false,true,false,false,false,true,false,true,true,false,true,false,false,true,false,false,false,false,false,false,false,true,true,true,false,false,false,true,false,false,true,true,true,false,true,true,false,false,true,true,false,true,true,false,false,true,true,false,true,false,true,true,false,true,true,true,false,true,false,false,true,false,false,false,true,false,false,true,false,true,true,true,true,false,true,false,true,true,false,false,false,false,false,false,true,true,true,true,false,false,true,true,false,true,true,false,false,false,false,true,false,false,true,true,true,false,false,true,false,true,true,true,true,true,false,true,true,false,true,true,true,true,false,false,true,false,false,true,true,true,true,false,false,false,false,false,false,false,true,false,false,true,true,true,false,true,false,false,false,true,false,true,false,true,true,true,false,false,true,false,true,true,false,true,true,false,false,true,true,false,false,true,true,false,false,true,true};
    uint256_from_bytes(a, a92_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a92_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a93_data[32]  = {0x83,0x37,0x31,0xc2,0x63,0x98,0xb1,0x99,0x42,0x34,0x5b,0x8c,0x6c,0xd7,0x0c,0x6b,0x87,0x69,0x7d,0xda,0xc1,0xea,0xfa,0x6f,0x04,0x97,0x53,0xe4,0xeb,0x39,0xc8,0x6f};
    bool         a93_bits[256] = {true,true,true,true,false,true,true,false,false,false,false,true,false,false,true,true,true,false,false,true,true,true,false,false,true,true,false,true,false,true,true,true,false,false,true,false,false,true,true,true,true,true,false,false,true,false,true,false,true,true,true,false,true,false,false,true,false,false,true,false,false,false,false,false,true,true,true,true,false,true,true,false,false,true,false,true,true,true,true,true,false,true,false,true,false,true,true,true,true,false,false,false,false,false,true,true,false,true,false,true,true,false,true,true,true,false,true,true,true,true,true,false,true,false,false,true,false,true,true,false,true,true,true,false,false,false,false,true,true,true,false,true,false,true,true,false,false,false,true,true,false,false,false,false,true,true,true,false,true,false,true,true,false,false,true,true,false,true,true,false,false,false,true,true,false,false,false,true,true,true,false,true,true,false,true,false,false,false,true,false,true,true,false,false,false,true,false,false,false,false,true,false,true,false,false,true,true,false,false,true,true,false,false,false,true,true,false,true,false,false,false,true,true,false,false,true,true,true,false,false,false,true,true,false,false,true,false,false,false,false,true,true,true,false,false,false,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false,false,false,false,false,true};
    uint256_from_bytes(a, a93_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a93_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a94_data[32]  = {0x13,0x3d,0x9b,0x03,0xac,0xb9,0x83,0xb5,0xd3,0x3e,0x67,0x28,0x3a,0x35,0xbf,0x1f,0x86,0x6f,0x7b,0x22,0x2d,0xbd,0x1d,0xf3,0xd1,0x94,0xb1,0x12,0xab,0x19,0xbe,0xad};
    bool         a94_bits[256] = {true,false,true,true,false,true,false,true,false,true,true,true,true,true,false,true,true,false,false,true,true,false,false,false,true,true,false,true,false,true,false,true,false,true,false,false,true,false,false,false,true,false,false,false,true,true,false,true,false,false,true,false,true,false,false,true,true,false,false,false,true,false,true,true,true,true,false,false,true,true,true,true,true,false,true,true,true,false,false,false,true,false,true,true,true,true,false,true,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,false,true,true,false,true,true,true,true,false,true,true,true,true,false,true,true,false,false,true,true,false,false,false,false,true,true,true,true,true,true,false,false,false,true,true,true,true,true,true,false,true,true,false,true,false,true,true,false,false,false,true,false,true,true,true,false,false,false,false,false,true,false,true,false,false,true,true,true,false,false,true,true,false,false,true,true,true,true,true,false,false,true,true,false,false,true,false,true,true,true,false,true,false,true,true,false,true,true,true,false,false,false,false,false,true,true,false,false,true,true,true,false,true,false,false,true,true,false,true,false,true,true,true,false,false,false,false,false,false,true,true,false,true,true,false,false,true,true,false,true,true,true,true,false,false,true,true,false,false,true,false,false,false};
    uint256_from_bytes(a, a94_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a94_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a95_data[32]  = {0x4d,0xc6,0x04,0x00,0x8d,0xa8,0x18,0x48,0x8a,0x17,0x7d,0x57,0x23,0x0b,0x27,0x17,0x80,0x4a,0x67,0xd7,0x9c,0xa9,0xb9,0xd9,0xa4,0x8e,0x69,0x1a,0x9b,0xf6,0x9f,0x83};
    bool         a95_bits[256] = {true,true,false,false,false,false,false,true,true,true,true,true,true,false,false,true,false,true,true,false,true,true,true,true,true,true,false,true,true,false,false,true,false,true,false,true,true,false,false,false,true,false,false,true,false,true,true,false,false,true,true,true,false,false,false,true,false,false,true,false,false,true,false,true,true,false,false,true,true,false,true,true,true,false,false,true,true,true,false,true,true,false,false,true,false,true,false,true,false,false,true,true,true,false,false,true,true,true,true,false,true,false,true,true,true,true,true,false,false,true,true,false,false,true,false,true,false,false,true,false,false,false,false,false,false,false,false,true,true,true,true,false,true,false,false,false,true,true,true,false,false,true,false,false,true,true,false,true,false,false,false,false,true,true,false,false,false,true,false,false,true,true,true,false,true,false,true,false,true,false,true,true,true,true,true,false,true,true,true,false,true,false,false,false,false,true,false,true,false,false,false,true,false,false,false,true,false,false,true,false,false,false,false,true,true,false,false,false,false,false,false,true,false,true,false,true,true,false,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,true,true,false,false,false,true,true,true,false,true,true,false,false,true,false};
    uint256_from_bytes(a, a95_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a95_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a96_data[32]  = {0xe2,0x1f,0x00,0x66,0x07,0xc9,0x69,0x36,0xcc,0xb5,0xdb,0xc4,0x84,0x15,0x3e,0x18,0x9f,0x17,0x48,0xe8,0xfc,0x1f,0xc7,0x42,0x5c,0x6e,0xfe,0x4e,0xb8,0x8b,0xb2,0x2c};
    bool         a96_bits[256] = {false,false,true,true,false,true,false,false,false,true,false,false,true,true,false,true,true,true,false,true,false,false,false,true,false,false,false,true,true,true,false,true,false,true,true,true,false,false,true,false,false,true,true,true,true,true,true,true,false,true,true,true,false,true,true,false,false,false,true,true,true,false,true,false,false,true,false,false,false,false,true,false,true,true,true,false,false,false,true,true,true,true,true,true,true,false,false,false,false,false,true,true,true,true,true,true,false,false,false,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,true,false,true,false,false,false,true,true,true,true,true,false,false,true,false,false,false,true,true,false,false,false,false,true,true,true,true,true,false,false,true,false,true,false,true,false,false,false,false,false,true,false,false,false,false,true,false,false,true,false,false,false,true,true,true,true,false,true,true,false,true,true,true,false,true,false,true,true,false,true,false,false,true,true,false,false,true,true,false,true,true,false,true,true,false,false,true,false,false,true,false,true,true,false,true,false,false,true,false,false,true,true,true,true,true,false,false,false,false,false,false,true,true,false,false,true,true,false,false,false,false,false,false,false,false,false,true,true,true,true,true,false,false,false,false,true,false,false,false,true,true,true};
    uint256_from_bytes(a, a96_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a96_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a97_data[32]  = {0x6b,0x7d,0x8e,0x24,0x13,0xb4,0x8e,0xb8,0x0c,0x96,0xfa,0x87,0x34,0x3b,0x32,0xa1,0x8f,0xb5,0xf5,0x7c,0xc4,0xfa,0x02,0xe7,0x96,0xe3,0xcb,0xdc,0xd0,0xea,0xb0,0xa5};
    bool         a97_bits[256] = {true,false,true,false,false,true,false,true,false,false,false,false,true,true,false,true,false,true,false,true,false,true,true,true,false,false,false,false,true,false,true,true,false,false,true,true,true,false,true,true,true,true,false,true,false,false,true,true,true,true,false,false,false,true,true,true,false,true,true,false,true,false,false,true,true,true,true,false,false,true,true,true,false,true,false,false,false,false,false,false,false,true,false,true,true,true,true,true,false,false,true,false,false,false,true,true,false,false,true,true,true,true,true,false,true,false,true,false,true,true,true,true,true,false,true,false,true,true,false,true,true,true,true,true,false,false,false,true,true,false,false,false,false,true,false,true,false,true,false,false,true,true,false,false,true,true,false,true,true,true,false,false,false,false,true,false,true,true,false,false,true,true,true,false,false,false,false,true,false,true,false,true,true,true,true,true,false,true,true,false,true,false,false,true,false,false,true,true,false,false,false,false,false,false,false,true,true,true,false,true,false,true,true,true,false,false,false,true,false,false,true,false,true,true,false,true,true,true,false,false,true,false,false,false,false,false,true,false,false,true,false,false,false,true,true,true,false,false,false,true,true,false,true,true,true,true,true,false,true,true,false,true,false,true,true,false};
    uint256_from_bytes(a, a97_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a97_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a98_data[32]  = {0x0f,0xdb,0x8b,0xe6,0x75,0xb7,0x56,0x28,0x1d,0xaa,0x5c,0x25,0x36,0x32,0x1a,0xd1,0xb5,0x52,0x89,0xb5,0xb2,0x7a,0x94,0xc5,0xcd,0x09,0xbb,0x9f,0x66,0xe6,0xcc,0x87};
    bool         a98_bits[256] = {true,true,true,false,false,false,false,true,false,false,true,true,false,false,true,true,false,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false,true,true,true,true,true,false,false,true,true,true,false,true,true,true,false,true,true,false,false,true,false,false,false,false,true,false,true,true,false,false,true,true,true,false,true,false,false,false,true,true,false,false,true,false,true,false,false,true,false,true,false,true,true,true,true,false,false,true,false,false,true,true,false,true,true,false,true,false,true,true,false,true,true,false,false,true,false,false,false,true,false,true,false,false,true,false,true,false,true,false,true,false,true,true,false,true,true,false,false,false,true,false,true,true,false,true,false,true,true,false,false,false,false,true,false,false,true,true,false,false,false,true,true,false,true,true,false,false,true,false,true,false,false,true,false,false,false,false,true,true,true,false,true,false,false,true,false,true,false,true,false,true,true,false,true,true,true,false,false,false,false,false,false,true,false,true,false,false,false,true,true,false,true,false,true,false,true,true,true,false,true,true,false,true,true,false,true,false,true,true,true,false,false,true,true,false,false,true,true,true,true,true,false,true,false,false,false,true,true,true,false,true,true,false,true,true,true,true,true,true,false,false,false,false};
    uint256_from_bytes(a, a98_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a98_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }

    std::uint8_t a99_data[32]  = {0xe3,0xd1,0x16,0xc0,0xd1,0x4d,0x03,0x33,0x88,0xc8,0x2a,0x5b,0x72,0x64,0x05,0xe9,0xcc,0xf1,0xe0,0xcb,0x9f,0x65,0xe7,0x26,0x7a,0x9c,0x83,0xa3,0x37,0xfe,0xac,0x3e};
    bool         a99_bits[256] = {false,true,true,true,true,true,false,false,false,false,true,true,false,true,false,true,false,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,true,true,false,false,false,true,false,true,true,true,false,false,false,false,false,true,false,false,true,true,true,false,false,true,false,true,false,true,true,true,true,false,false,true,true,false,false,true,false,false,true,true,true,false,false,true,true,true,true,false,true,false,false,true,true,false,true,true,true,true,true,false,false,true,true,true,false,true,false,false,true,true,false,false,false,false,false,true,true,true,true,false,false,false,true,true,true,true,false,false,true,true,false,false,true,true,true,false,false,true,false,true,true,true,true,false,true,false,false,false,false,false,false,false,true,false,false,true,true,false,false,true,false,false,true,true,true,false,true,true,false,true,true,false,true,false,false,true,false,true,false,true,false,false,false,false,false,true,false,false,true,true,false,false,false,true,false,false,false,true,true,true,false,false,true,true,false,false,true,true,false,false,false,false,false,false,true,false,true,true,false,false,true,false,true,false,false,false,true,false,true,true,false,false,false,false,false,false,true,true,false,true,true,false,true,false,false,false,true,false,false,false,true,false,true,true,true,true,false,false,false,true,true,true};
    uint256_from_bytes(a, a99_data);
    for (int i = 0; i < 256; i++)
    {
        if (uint256_bittest(a, i) != a99_bits[i])
        {
            throw std::runtime_error("err in uint256_common_bittest");
        }
    }
}