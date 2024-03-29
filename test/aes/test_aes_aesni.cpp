#include <gmlib/aes/internal/aes_aesni.h>
#include <stdexcept>
#include <cstring>

#if !(defined(CPU_FLAG_AES) && defined(CPU_FLAG_SSE2))
void test_aes_aesni()
{
}
#else

static std::uint8_t user_key[32] = {
    0x04, 0xb5, 0xf0, 0x47, 0x03, 0xe2, 0x02, 0x5f, 0x5d, 0x08, 0x46,
    0xc8, 0x0a, 0x68, 0x19, 0xa0, 0x04, 0xb5, 0xf0, 0x47, 0x03, 0xe2,
    0x02, 0x5f, 0x5d, 0x08, 0x46, 0xc8, 0x0a, 0x68, 0x19, 0xa0,
};

static std::uint8_t pt[] = {
    0x13, 0xf1, 0xdb, 0xd4, 0x4e, 0x92, 0x3a, 0x83, 0xd0, 0x23, 0x29, 0x7d,
    0xb0, 0x72, 0x59, 0x22, 0x12, 0x9f, 0x6f, 0xff, 0xc1, 0x85, 0x11, 0xde,
    0x69, 0xcf, 0xca, 0x6f, 0x9a, 0xf5, 0xdc, 0x42, 0xcf, 0x85, 0x56, 0x0a,
    0x54, 0x42, 0xdd, 0x96, 0x36, 0x6b, 0x80, 0x22, 0x6d, 0x23, 0x19, 0x36,
    0xa4, 0x88, 0x3d, 0xc9, 0x7a, 0x46, 0x88, 0x4d, 0x6f, 0x2a, 0xd6, 0x83,
    0xc9, 0xbd, 0xa5, 0x29, 0x02, 0x20, 0xaa, 0xb3, 0x8c, 0xaa, 0xa2, 0x71,
    0x45, 0x0b, 0x23, 0x1b, 0x6b, 0x26, 0x7d, 0x8a, 0x37, 0x7d, 0x77, 0xb0,
    0xfd, 0xbb, 0x90, 0xaf, 0x98, 0xc5, 0xda, 0xdd, 0x18, 0x63, 0x0d, 0x02,
    0xe8, 0x7a, 0x07, 0x58, 0xe4, 0xda, 0x47, 0x7c, 0x24, 0xe2, 0x9a, 0x99,
    0xfd, 0xd8, 0x20, 0x4e, 0x8a, 0x77, 0xeb, 0x77, 0xbf, 0x47, 0x0b, 0x23,
    0xaf, 0xd1, 0x20, 0x4c, 0xc8, 0xfa, 0x8b, 0x71,
};

static std::uint8_t ct128[] = {
    0x05, 0x82, 0x59, 0x7a, 0xc7, 0x32, 0xc6, 0xaf, 0x3a, 0x0f, 0xee, 0xe1,
    0x8d, 0xd1, 0x32, 0xa5, 0x6f, 0x86, 0x9e, 0x2b, 0x33, 0xa4, 0xe7, 0x88,
    0xc7, 0xbc, 0x40, 0xd4, 0xd7, 0x71, 0x78, 0x18, 0x60, 0x46, 0x5e, 0x44,
    0x70, 0x86, 0x1e, 0x08, 0x1b, 0xc6, 0xa6, 0x09, 0x25, 0xe9, 0x7c, 0xf3,
    0xc4, 0x7a, 0x21, 0x79, 0xf4, 0x71, 0x3c, 0xb9, 0xc5, 0x3a, 0xed, 0xf4,
    0x35, 0x9f, 0x4c, 0x09, 0xc1, 0x45, 0xaa, 0x6d, 0xc0, 0x94, 0x6f, 0xf2,
    0xee, 0x29, 0xa6, 0xb5, 0xd6, 0xab, 0x6d, 0xf7, 0x46, 0x6c, 0xb9, 0x8d,
    0x13, 0x1b, 0xeb, 0x81, 0xdd, 0x76, 0xd3, 0x2d, 0xab, 0x39, 0xc4, 0x32,
    0x71, 0xb8, 0x68, 0xc3, 0x4e, 0x5f, 0x14, 0x3b, 0xad, 0xbe, 0x36, 0x8b,
    0x0a, 0x11, 0x7d, 0x05, 0x85, 0xe7, 0x6c, 0x00, 0x83, 0xf4, 0x09, 0x90,
    0x35, 0xf5, 0xf4, 0xce, 0x98, 0xe8, 0x5d, 0x79,
};

static std::uint8_t ct192[] = {
    0xd6, 0xb2, 0x9a, 0x9c, 0x59, 0x86, 0xd8, 0xe5, 0x02, 0xfd, 0xa2, 0x45,
    0x92, 0xdd, 0x2d, 0x3e, 0x23, 0xe8, 0x91, 0x8a, 0xa8, 0x13, 0xd3, 0x1d,
    0x48, 0xb5, 0x24, 0xdc, 0x77, 0x2c, 0xe5, 0xcd, 0xf2, 0xbc, 0xf5, 0xce,
    0xcb, 0x2b, 0x70, 0x94, 0x1d, 0x6c, 0xe8, 0x5f, 0xbc, 0xef, 0x9d, 0x21,
    0x56, 0xc6, 0x39, 0x5e, 0xcc, 0x07, 0xde, 0x20, 0xc7, 0xf5, 0xb7, 0x10,
    0x8b, 0x08, 0x5b, 0x15, 0x71, 0x7b, 0x79, 0x7d, 0x41, 0x01, 0xc8, 0xd5,
    0x94, 0xd1, 0x73, 0x02, 0x58, 0x1c, 0xbc, 0x64, 0x8e, 0x0e, 0xc8, 0x4d,
    0x29, 0xd9, 0x30, 0xdb, 0x57, 0x4d, 0xd5, 0x46, 0xd1, 0x0a, 0xd1, 0x3c,
    0x82, 0x67, 0x4f, 0x46, 0xb7, 0x6f, 0x03, 0x78, 0xba, 0x65, 0x69, 0x0d,
    0x33, 0x0e, 0xf5, 0xe7, 0x4e, 0xc7, 0x35, 0xb7, 0xcb, 0x2d, 0xb3, 0x7b,
    0xa4, 0x7e, 0xe9, 0x75, 0xa0, 0x7f, 0xe9, 0x1b,
};

static std::uint8_t ct256[] = {
    0xb8, 0x7b, 0xc6, 0xea, 0x26, 0x48, 0x03, 0x4c, 0x6d, 0xf5, 0xfa, 0x38,
    0x0b, 0x7f, 0xb3, 0x30, 0x8f, 0xf9, 0xd4, 0xd0, 0xeb, 0x83, 0xd5, 0x97,
    0xce, 0x62, 0xb6, 0xe6, 0x80, 0x89, 0xd8, 0xca, 0x5c, 0x94, 0x6c, 0x46,
    0x1c, 0x74, 0x50, 0xaa, 0xb1, 0x7e, 0x44, 0x17, 0x63, 0xad, 0xf1, 0x69,
    0x2e, 0xd1, 0x6f, 0xbe, 0x95, 0x67, 0x44, 0x91, 0xae, 0x15, 0x49, 0x6c,
    0xca, 0xc5, 0xb2, 0x79, 0x87, 0x5e, 0x9b, 0xb2, 0x1f, 0x96, 0xc8, 0xd0,
    0xcf, 0xbf, 0x20, 0x67, 0x37, 0xfe, 0xe6, 0x24, 0x1f, 0xa3, 0xa3, 0x41,
    0xad, 0x6a, 0xb6, 0x4f, 0x83, 0xa9, 0xf9, 0xa3, 0x64, 0x0f, 0x38, 0x24,
    0xac, 0x0b, 0x17, 0x11, 0xe3, 0x2e, 0xac, 0x2b, 0x23, 0x5d, 0x72, 0xc8,
    0x4b, 0x61, 0x45, 0x37, 0x52, 0x90, 0xca, 0xb3, 0xed, 0x47, 0x3c, 0xb2,
    0x90, 0x84, 0xae, 0xf2, 0x60, 0x1d, 0xaa, 0xdf,
};

using namespace aes::internal::aesni;

static void test_aes128_aesni()
{
    std::uint8_t out[sizeof(pt)];

    Aes128CTX ctx128;
    aes128_enc_key_init(&ctx128, user_key);
    aes128_enc_blocks(&ctx128, out, pt, sizeof(pt) / AES128_BLOCK_SIZE);
    if (std::memcmp(out, ct128, sizeof(ct128)) != 0)
    {
        throw std::runtime_error("err in aes128 aesni");
    }
    aes128_dec_key_init(&ctx128, user_key);
    aes128_dec_blocks(&ctx128, out, ct128, sizeof(ct128) / AES128_BLOCK_SIZE);
    if (std::memcmp(out, pt, sizeof(pt)) != 0)
    {
        throw std::runtime_error("err in aes128 aesni");
    }
}

static void test_aes192_aesni()
{
    std::uint8_t out[sizeof(pt)];

    Aes192CTX ctx192;
    aes192_enc_key_init(&ctx192, user_key);
    aes192_enc_blocks(&ctx192, out, pt, sizeof(pt) / AES192_BLOCK_SIZE);
    if (std::memcmp(out, ct192, sizeof(ct192)) != 0)
    {
        throw std::runtime_error("err in aes192 aesni enc");
    }
    aes192_dec_key_init(&ctx192, user_key);
    aes192_dec_blocks(&ctx192, out, ct192, sizeof(ct192) / AES192_BLOCK_SIZE);
    if (std::memcmp(out, pt, sizeof(pt)) != 0)
    {
        throw std::runtime_error("err in aes192 aesni dec");
    }
}

static void test_aes256_aesni()
{
    std::uint8_t out[sizeof(pt)];

    Aes256CTX ctx256;
    aes256_enc_key_init(&ctx256, user_key);
    aes256_enc_blocks(&ctx256, out, pt, sizeof(pt) / AES256_BLOCK_SIZE);
    if (std::memcmp(out, ct256, sizeof(ct256)) != 0)
    {
        throw std::runtime_error("err in aes256 aesni");
    }
    aes256_dec_key_init(&ctx256, user_key);
    aes256_dec_blocks(&ctx256, out, ct256, sizeof(ct256) / AES256_BLOCK_SIZE);
    if (std::memcmp(out, pt, sizeof(pt)) != 0)
    {
        throw std::runtime_error("err in aes256 aesni");
    }
}

void test_aes_aesni()
{
    test_aes128_aesni();
    test_aes192_aesni();
    test_aes256_aesni();
}
#endif