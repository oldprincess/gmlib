#include <gmlib/ghash/internal/ghash_lut256.h>

#include <cstring>
#include <stdexcept>

using namespace ghash::internal::lut256;

static std::uint8_t msg0[256] = {
    0xf9, 0x21, 0xec, 0x91, 0xbd, 0x1e, 0x66, 0xdf, 0xed, 0xa0, 0xe4, 0xad,
    0x69, 0x59, 0xdf, 0xa4, 0xda, 0xd5, 0x9c, 0x49, 0xe7, 0x6e, 0x54, 0xa6,
    0xa6, 0x66, 0x5f, 0xb0, 0x5c, 0x84, 0x99, 0xd8, 0xe6, 0x38, 0xa6, 0x4d,
    0xe4, 0x6e, 0x5f, 0xe7, 0x2f, 0xc8, 0x37, 0xdd, 0xe7, 0xb1, 0x2f, 0xa2,
    0xd7, 0xc0, 0x72, 0x8c, 0x43, 0x5b, 0xc0, 0x12, 0xb6, 0xa1, 0xc4, 0xd0,
    0x8a, 0xf2, 0x7f, 0xce, 0x4f, 0x8a, 0x9f, 0x6c, 0xaf, 0x92, 0x78, 0xc3,
    0x4b, 0x54, 0xd6, 0xab, 0x4e, 0xc3, 0x06, 0x28, 0x5c, 0x9a, 0xc1, 0x2e,
    0x50, 0x62, 0x76, 0xbc, 0xd8, 0x7a, 0xf1, 0x88, 0xda, 0xc3, 0x2c, 0xca,
    0xb7, 0xa0, 0xf1, 0xef, 0x84, 0x0d, 0x2e, 0x1a, 0x35, 0xe7, 0x36, 0x9a,
    0x16, 0xc9, 0xe6, 0x6a, 0x5c, 0x19, 0x12, 0x9b, 0x7a, 0x0a, 0xf1, 0x5c,
    0x85, 0xad, 0xc3, 0x1f, 0xd5, 0x0c, 0xb7, 0xa4, 0x1b, 0x5e, 0xe6, 0x40,
    0xcd, 0x63, 0x83, 0x64, 0x82, 0xe3, 0xa6, 0xa9, 0x42, 0x11, 0x06, 0x90,
    0xac, 0x44, 0x81, 0x09, 0x60, 0xe6, 0x93, 0x93, 0xb2, 0x8b, 0x08, 0xf5,
    0x7d, 0x58, 0x25, 0xbd, 0x60, 0x7f, 0xb1, 0x77, 0xe8, 0x8a, 0xa0, 0x23,
    0x92, 0x4e, 0xfe, 0x84, 0xa9, 0x14, 0xca, 0xd7, 0xd1, 0xf5, 0xd2, 0x49,
    0xf5, 0x13, 0x01, 0x71, 0x28, 0x5c, 0xff, 0x3a, 0xd7, 0xfd, 0xf3, 0x86,
    0x12, 0x07, 0xdb, 0x9a, 0x03, 0x5e, 0x67, 0x06, 0x4c, 0xaf, 0x33, 0x77,
    0xf9, 0x86, 0x4b, 0xeb, 0x6a, 0x9b, 0x44, 0x7c, 0xd0, 0x38, 0xee, 0x50,
    0x59, 0xd6, 0x8a, 0xe9, 0x73, 0x0b, 0x00, 0x9f, 0xde, 0x20, 0xf9, 0x86,
    0xac, 0x35, 0x3d, 0x88, 0x72, 0x7d, 0x78, 0xac, 0x22, 0x09, 0x11, 0x0f,
    0xcf, 0x13, 0x46, 0x10, 0x8a, 0x89, 0x95, 0x35, 0x41, 0xc1, 0x6c, 0x4b,
    0xc4, 0x06, 0x6e, 0x89,
};
static std::uint8_t H0[16] = {
    0x48, 0xd3, 0xe8, 0x4d, 0x36, 0x62, 0xcc, 0xf7,
    0x2a, 0x2b, 0xbb, 0x7d, 0x88, 0x7e, 0x38, 0xbb,
};
static std::uint8_t digest0[16] = {
    0x0c, 0xcc, 0xaf, 0xfd, 0xd6, 0x34, 0xad, 0x87,
    0xcd, 0x81, 0xcb, 0xa4, 0xf0, 0x46, 0x30, 0x2d,
};
static std::uint8_t msg1[256] = {
    0xce, 0x41, 0x2d, 0xff, 0x34, 0x3c, 0x21, 0x5a, 0xa5, 0xcd, 0x3e, 0x01,
    0xc2, 0x63, 0xd2, 0x29, 0x90, 0x4e, 0x07, 0xe3, 0xa7, 0xea, 0xa4, 0x06,
    0xea, 0x67, 0x9a, 0x93, 0xd1, 0x2e, 0x02, 0xa5, 0x8b, 0xb8, 0x0c, 0x49,
    0x87, 0x90, 0x42, 0xfd, 0x60, 0x6f, 0xd0, 0x51, 0x7e, 0x38, 0x7e, 0x6f,
    0xde, 0xd0, 0xd6, 0x32, 0x54, 0x62, 0x27, 0xc5, 0x17, 0x17, 0xbc, 0xeb,
    0x62, 0x3a, 0xd8, 0xe5, 0x4a, 0xa6, 0x94, 0xfe, 0xef, 0x76, 0x54, 0x73,
    0x91, 0xb7, 0x5f, 0x85, 0xb6, 0x66, 0xdd, 0x6c, 0xc8, 0xfc, 0xaa, 0x9b,
    0x13, 0xbc, 0x35, 0x25, 0x1c, 0xb5, 0x4e, 0xa3, 0x1d, 0x0e, 0x14, 0xfb,
    0x3d, 0x57, 0xe6, 0x44, 0x90, 0xff, 0xa9, 0xc0, 0x12, 0x67, 0x9a, 0x2e,
    0x11, 0xb1, 0x3d, 0xa4, 0x8a, 0x28, 0x90, 0x53, 0x26, 0xf3, 0x9b, 0xea,
    0xa2, 0xbf, 0x0a, 0xe0, 0xf4, 0x29, 0x6e, 0x50, 0x13, 0x7f, 0x71, 0x44,
    0x4c, 0x95, 0x8d, 0x4d, 0xad, 0xe2, 0x99, 0x28, 0xe8, 0x57, 0x24, 0x6b,
    0x6b, 0x9c, 0xff, 0x2f, 0xea, 0x24, 0xf6, 0x10, 0xb2, 0x5a, 0xf2, 0x32,
    0xed, 0x05, 0x6a, 0x68, 0xa9, 0x26, 0x96, 0x84, 0xe8, 0x05, 0x20, 0x46,
    0x68, 0x36, 0x50, 0x39, 0xde, 0x1c, 0x95, 0x42, 0xf8, 0xef, 0x6f, 0x86,
    0x4e, 0x33, 0xfa, 0xe6, 0xce, 0xdd, 0x83, 0x83, 0x50, 0x19, 0x17, 0x90,
    0x3c, 0x61, 0x91, 0x20, 0x3c, 0x19, 0xde, 0xd7, 0x6b, 0x22, 0x4e, 0xe7,
    0x51, 0x88, 0x7c, 0x86, 0x81, 0x34, 0x80, 0x01, 0x7e, 0x23, 0x93, 0xa8,
    0x86, 0x54, 0x9b, 0x35, 0xa1, 0x17, 0xe9, 0x6e, 0x2a, 0x51, 0xe6, 0x02,
    0x1a, 0xa1, 0x92, 0x7d, 0x95, 0x5d, 0x38, 0x18, 0x67, 0xf7, 0xf8, 0x68,
    0x04, 0x24, 0xa3, 0xc8, 0xec, 0x12, 0x54, 0xfc, 0x94, 0xfc, 0x67, 0xb3,
    0x27, 0xa0, 0x14, 0xcb,
};
static std::uint8_t H1[16] = {
    0xfe, 0x15, 0x02, 0x91, 0x0d, 0x0f, 0x87, 0xcd,
    0x78, 0x3a, 0xa3, 0x25, 0xc0, 0x52, 0xd5, 0xb0,
};
static std::uint8_t digest1[16] = {
    0x72, 0xbc, 0xef, 0x91, 0x0f, 0x02, 0xda, 0xa1,
    0x70, 0xdb, 0xb7, 0x69, 0x49, 0xe2, 0xaa, 0xd9,
};

void test_ghash_lut256()
{
    std::uint8_t out[GHASH_DIGEST_SIZE];
    GHashCTX     ctx;

    ghash_init(&ctx, H0);
    ghash_update_blocks(&ctx, msg0, sizeof(msg0) / GHASH_BLOCK_SIZE);
    if (ghash_final_block(&ctx, out, nullptr, 0))
    {
        throw std::runtime_error("err in ghash lut256");
    }
    if (std::memcmp(digest0, out, GHASH_DIGEST_SIZE) != 0)
    {
        throw std::runtime_error("err in ghash lut256");
    }

    ghash_init(&ctx, H1);
    ghash_update_blocks(&ctx, msg1, sizeof(msg1) / GHASH_BLOCK_SIZE);
    if (ghash_final_block(&ctx, out, nullptr, 0))
    {
        throw std::runtime_error("err in ghash lut256");
    }
    if (std::memcmp(digest1, out, GHASH_DIGEST_SIZE) != 0)
    {
        throw std::runtime_error("err in ghash lut256");
    }
}