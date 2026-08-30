#if defined(SUPPORT_SM4_SM4NI)

#include "sm4_sm4ni.h"

#include <immintrin.h>

namespace sm4::internal::sm4ni {

/* Operations */
/* Rotate Left 32-bit number */
#define ROTL32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

static const std::uint32_t sm4_ck[32] = {
    0x00070E15, 0x1C232A31, 0x383F464D, 0x545B6269, 0x70777E85, 0x8C939AA1,
    0xA8AFB6BD, 0xC4CBD2D9, 0xE0E7EEF5, 0xFC030A11, 0x181F262D, 0x343B4249,
    0x50575E65, 0x6C737A81, 0x888F969D, 0xA4ABB2B9, 0xC0C7CED5, 0xDCE3EAF1,
    0xF8FF060D, 0x141B2229, 0x30373E45, 0x4C535A61, 0x686F767D, 0x848B9299,
    0xA0A7AEB5, 0xBCC3CAD1, 0xD8DFE6ED, 0xF4FB0209, 0x10171E25, 0x2C333A41,
    0x484F565D, 0x646B7279};

static const std::uint8_t sm4_sbox[256] = {
    0xD6, 0x90, 0xE9, 0xFE, 0xCC, 0xE1, 0x3D, 0xB7, 0x16, 0xB6, 0x14, 0xC2,
    0x28, 0xFB, 0x2C, 0x05, 0x2B, 0x67, 0x9A, 0x76, 0x2A, 0xBE, 0x04, 0xC3,
    0xAA, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99, 0x9C, 0x42, 0x50, 0xF4,
    0x91, 0xEF, 0x98, 0x7A, 0x33, 0x54, 0x0B, 0x43, 0xED, 0xCF, 0xAC, 0x62,
    0xE4, 0xB3, 0x1C, 0xA9, 0xC9, 0x08, 0xE8, 0x95, 0x80, 0xDF, 0x94, 0xFA,
    0x75, 0x8F, 0x3F, 0xA6, 0x47, 0x07, 0xA7, 0xFC, 0xF3, 0x73, 0x17, 0xBA,
    0x83, 0x59, 0x3C, 0x19, 0xE6, 0x85, 0x4F, 0xA8, 0x68, 0x6B, 0x81, 0xB2,
    0x71, 0x64, 0xDA, 0x8B, 0xF8, 0xEB, 0x0F, 0x4B, 0x70, 0x56, 0x9D, 0x35,
    0x1E, 0x24, 0x0E, 0x5E, 0x63, 0x58, 0xD1, 0xA2, 0x25, 0x22, 0x7C, 0x3B,
    0x01, 0x21, 0x78, 0x87, 0xD4, 0x00, 0x46, 0x57, 0x9F, 0xD3, 0x27, 0x52,
    0x4C, 0x36, 0x02, 0xE7, 0xA0, 0xC4, 0xC8, 0x9E, 0xEA, 0xBF, 0x8A, 0xD2,
    0x40, 0xC7, 0x38, 0xB5, 0xA3, 0xF7, 0xF2, 0xCE, 0xF9, 0x61, 0x15, 0xA1,
    0xE0, 0xAE, 0x5D, 0xA4, 0x9B, 0x34, 0x1A, 0x55, 0xAD, 0x93, 0x32, 0x30,
    0xF5, 0x8C, 0xB1, 0xE3, 0x1D, 0xF6, 0xE2, 0x2E, 0x82, 0x66, 0xCA, 0x60,
    0xC0, 0x29, 0x23, 0xAB, 0x0D, 0x53, 0x4E, 0x6F, 0xD5, 0xDB, 0x37, 0x45,
    0xDE, 0xFD, 0x8E, 0x2F, 0x03, 0xFF, 0x6A, 0x72, 0x6D, 0x6C, 0x5B, 0x51,
    0x8D, 0x1B, 0xAF, 0x92, 0xBB, 0xDD, 0xBC, 0x7F, 0x11, 0xD9, 0x5C, 0x41,
    0x1F, 0x10, 0x5A, 0xD8, 0x0A, 0xC1, 0x31, 0x88, 0xA5, 0xCD, 0x7B, 0xBD,
    0x2D, 0x74, 0xD0, 0x12, 0xB8, 0xE5, 0xB4, 0xB0, 0x89, 0x69, 0x97, 0x4A,
    0x0C, 0x96, 0x77, 0x7E, 0x65, 0xB9, 0xF1, 0x09, 0xC5, 0x6E, 0xC6, 0x84,
    0x18, 0xF0, 0x7D, 0xEC, 0x3A, 0xDC, 0x4D, 0x20, 0x79, 0xEE, 0x5F, 0x3E,
    0xD7, 0xCB, 0x39, 0x48};

static const std::uint32_t sm4_fk[4] = {0xA3B1BAC6, 0x56AA3350, 0x677D9197,
                                        0xB27022DC};

static std::uint32_t load_u32_be(const std::uint8_t *b, std::uint32_t n)
{
    return ((std::uint32_t)b[4 * n] << 24) |
           ((std::uint32_t)b[4 * n + 1] << 16) |
           ((std::uint32_t)b[4 * n + 2] << 8) | ((std::uint32_t)b[4 * n + 3]);
}

static void store_u32_be(std::uint32_t v, std::uint8_t *b)
{
    b[0] = (std::uint8_t)(v >> 24);
    b[1] = (std::uint8_t)(v >> 16);
    b[2] = (std::uint8_t)(v >> 8);
    b[3] = (std::uint8_t)(v);
}

static void sm4_key_schedule(const std::uint8_t key[], std::uint32_t rk[])
{
    std::uint32_t t, x, k[36];
    int           i;

    for (i = 0; i < 4; i++)
    {
        k[i] = load_u32_be(key, i) ^ sm4_fk[i];
    }

    /* T' */
    for (i = 0; i < 32; ++i)
    {
        x = k[i + 1] ^ k[i + 2] ^ k[i + 3] ^ sm4_ck[i];

        /* Nonlinear operation tau */
        t = ((std::uint32_t)sm4_sbox[(std::uint8_t)(x >> 24)]) << 24 |
            ((std::uint32_t)sm4_sbox[(std::uint8_t)(x >> 16)]) << 16 |
            ((std::uint32_t)sm4_sbox[(std::uint8_t)(x >> 8)]) << 8 |
            ((std::uint32_t)sm4_sbox[(std::uint8_t)(x)]);

        /* Linear operation L' */
        k[i + 4] = k[i] ^ (t ^ ROTL32(t, 13) ^ ROTL32(t, 23));
        rk[i]    = k[i + 4];
    }
}

#define SM4_ROUNDS(k0, k1, k2, k3, F)   \
    do                                  \
    {                                   \
        x0 ^= F(x1 ^ x2 ^ x3 ^ rk[k0]); \
        x1 ^= F(x0 ^ x2 ^ x3 ^ rk[k1]); \
        x2 ^= F(x0 ^ x1 ^ x3 ^ rk[k2]); \
        x3 ^= F(x0 ^ x1 ^ x2 ^ rk[k3]); \
    } while (0)

static std::uint32_t sm4_t(std::uint32_t x)
{
    std::uint32_t t = 0;

    t |= ((std::uint32_t)sm4_sbox[(std::uint8_t)(x >> 24)]) << 24;
    t |= ((std::uint32_t)sm4_sbox[(std::uint8_t)(x >> 16)]) << 16;
    t |= ((std::uint32_t)sm4_sbox[(std::uint8_t)(x >> 8)]) << 8;
    t |= sm4_sbox[(std::uint8_t)x];

    /*
     * L linear transform
     */
    return t ^ ROTL32(t, 2) ^ ROTL32(t, 10) ^ ROTL32(t, 18) ^ ROTL32(t, 24);
}

static void sm4_compute(const std::uint32_t rk[32],
                        const std::uint8_t *plaintext,
                        std::uint8_t       *ciphertext)
{
    std::uint32_t x0, x1, x2, x3;

    x0 = load_u32_be(plaintext, 0);
    x1 = load_u32_be(plaintext, 1);
    x2 = load_u32_be(plaintext, 2);
    x3 = load_u32_be(plaintext, 3);

    SM4_ROUNDS(0, 1, 2, 3, sm4_t);
    SM4_ROUNDS(4, 5, 6, 7, sm4_t);
    SM4_ROUNDS(8, 9, 10, 11, sm4_t);
    SM4_ROUNDS(12, 13, 14, 15, sm4_t);
    SM4_ROUNDS(16, 17, 18, 19, sm4_t);
    SM4_ROUNDS(20, 21, 22, 23, sm4_t);
    SM4_ROUNDS(24, 25, 26, 27, sm4_t);
    SM4_ROUNDS(28, 29, 30, 31, sm4_t);

    store_u32_be(x3, ciphertext);
    store_u32_be(x2, ciphertext + 4);
    store_u32_be(x1, ciphertext + 8);
    store_u32_be(x0, ciphertext + 12);
}

static void sm4_compute4(const uint32_t rk[32], const void *src, void *dst)
{
    // nibble mask
    static const std::uint64_t c0f_data[2] = {
        0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F,
    };
    // flip all bytes in all 32-bit words
    static const std::uint64_t flp_data[2] = {
        0x0405060700010203,
        0x0C0D0E0F08090A0B,
    };
    // inverse shift rows
    static const std::uint64_t shr_data[2] = {
        0x0B0E0104070A0D00,
        0x0306090C0F020508,
    };

    __m128i c0f = _mm_loadu_si128((const __m128i *)c0f_data);
    __m128i flp = _mm_loadu_si128((const __m128i *)flp_data);
    __m128i shr = _mm_loadu_si128((const __m128i *)shr_data);

    // Affine transform 1 (low and high hibbles)
    static const std::uint64_t m1l_data[2] = {
        0x9197E2E474720701,
        0xC7C1B4B222245157,
    };
    static const std::uint64_t m1h_data[2] = {
        0xE240AB09EB49A200,
        0xF052B91BF95BB012,
    };

    __m128i m1l = _mm_loadu_si128((const __m128i *)m1l_data);
    __m128i m1h = _mm_loadu_si128((const __m128i *)m1h_data);

    // Affine transform 2 (low and high hibbles)
    static const std::uint64_t m2l_data[2] = {
        0x5B67F2CEA19D0834,
        0xEDD14478172BBE82,
    };
    static const std::uint64_t m2h_data[2] = {
        0xAE7201DD73AFDC00,
        0x11CDBE62CC1063BF,
    };

    __m128i m2l = _mm_loadu_si128((const __m128i *)m2l_data);
    __m128i m2h = _mm_loadu_si128((const __m128i *)m2h_data);

    // left rotations of 32-bit words by 8-bit increments
    static const std::uint64_t r08_data[2] = {
        0x0605040702010003,
        0x0E0D0C0F0A09080B,
    };
    static const std::uint64_t r16_data[2] = {
        0x0504070601000302,
        0x0D0C0F0E09080B0A,
    };
    static const std::uint64_t r24_data[2] = {
        0x0407060500030201,
        0x0C0F0E0D080B0A09,
    };

    __m128i r08 = _mm_loadu_si128((const __m128i *)r08_data);
    __m128i r16 = _mm_loadu_si128((const __m128i *)r16_data);
    __m128i r24 = _mm_loadu_si128((const __m128i *)r24_data);

    __m128i x, y, t0, t1, t2, t3;

    std::uint32_t        k, *p32, v[4];
    const std::uint32_t *src32;
    int                  i;

    src32 = (const std::uint32_t *)src;
    t0    = _mm_set_epi32(src32[12], src32[8], src32[4], src32[0]);
    t0    = _mm_shuffle_epi8(t0, flp);
    t1    = _mm_set_epi32(src32[13], src32[9], src32[5], src32[1]);
    t1    = _mm_shuffle_epi8(t1, flp);
    t2    = _mm_set_epi32(src32[14], src32[10], src32[6], src32[2]);
    t2    = _mm_shuffle_epi8(t2, flp);
    t3    = _mm_set_epi32(src32[15], src32[11], src32[7], src32[3]);
    t3    = _mm_shuffle_epi8(t3, flp);

#define SM4_TAU_L1                                                        \
    {                                                                     \
        y = _mm_and_si128(x, c0f);                                        \
        y = _mm_shuffle_epi8(m1l, y);                                     \
        x = _mm_srli_epi64(x, 4);                                         \
        x = _mm_and_si128(x, c0f);                                        \
        x = _mm_xor_si128(_mm_shuffle_epi8(m1h, x), y);                   \
        x = _mm_shuffle_epi8(x, shr);                                     \
        x = _mm_aesenclast_si128(x, c0f);                                 \
        y = _mm_andnot_si128(x, c0f);                                     \
        y = _mm_shuffle_epi8(m2l, y);                                     \
        x = _mm_srli_epi64(x, 4);                                         \
        x = _mm_and_si128(x, c0f);                                        \
        x = _mm_xor_si128(_mm_shuffle_epi8(m2h, x), y);                   \
        y = _mm_xor_si128(x, _mm_xor_si128(_mm_shuffle_epi8(x, r08),      \
                                           _mm_shuffle_epi8(x, r16)));    \
        y = _mm_xor_si128(_mm_slli_epi32(y, 2), _mm_srli_epi32(y, 30));   \
        x = _mm_xor_si128(x, _mm_xor_si128(y, _mm_shuffle_epi8(x, r24))); \
    }

    for (i = 0; i < 32;)
    {
        k = rk[i++];
        x = _mm_xor_si128(_mm_xor_si128(t1, t2),
                          _mm_xor_si128(t3, _mm_set_epi32(k, k, k, k)));
        SM4_TAU_L1
        t0 = _mm_xor_si128(t0, x);

        k = rk[i++];
        x = _mm_xor_si128(_mm_xor_si128(t0, t2),
                          _mm_xor_si128(t3, _mm_set_epi32(k, k, k, k)));
        SM4_TAU_L1
        t1 = _mm_xor_si128(t1, x);

        k = rk[i++];
        x = _mm_xor_si128(_mm_xor_si128(t0, t1),
                          _mm_xor_si128(t3, _mm_set_epi32(k, k, k, k)));
        SM4_TAU_L1
        t2 = _mm_xor_si128(t2, x);

        k = rk[i++];
        x = _mm_xor_si128(_mm_xor_si128(t0, t1),
                          _mm_xor_si128(t2, _mm_set_epi32(k, k, k, k)));
        SM4_TAU_L1
        t3 = _mm_xor_si128(t3, x);
    }

    p32 = (std::uint32_t *)dst;

    _mm_storeu_si128((__m128i *)v, _mm_shuffle_epi8(t3, flp));
    p32[0]  = v[0];
    p32[4]  = v[1];
    p32[8]  = v[2];
    p32[12] = v[3];

    _mm_storeu_si128((__m128i *)v, _mm_shuffle_epi8(t2, flp));
    p32[1]  = v[0];
    p32[5]  = v[1];
    p32[9]  = v[2];
    p32[13] = v[3];

    _mm_storeu_si128((__m128i *)v, _mm_shuffle_epi8(t1, flp));
    p32[2]  = v[0];
    p32[6]  = v[1];
    p32[10] = v[2];
    p32[14] = v[3];

    _mm_storeu_si128((__m128i *)v, _mm_shuffle_epi8(t0, flp));
    p32[3]  = v[0];
    p32[7]  = v[1];
    p32[11] = v[2];
    p32[15] = v[3];
}

// ==================================================

void sm4_enc_key_init(SM4Context *ctx, const std::uint8_t user_key[16]) noexcept
{
    sm4_key_schedule(user_key, ctx->round_key);
}

void sm4_dec_key_init(SM4Context *ctx, const std::uint8_t user_key[16]) noexcept
{
    sm4_key_schedule(user_key, ctx->round_key);
    std::uint32_t *rk_u32 = ctx->round_key;
    for (int i = 0; i < 16; i++)
    {
        std::uint32_t tmp = rk_u32[i];
        rk_u32[i]         = rk_u32[31 - i];
        rk_u32[31 - i]    = tmp;
    }
}

void sm4_enc_block(const SM4Context  *ctx,
                   std::uint8_t       ciphertext[16],
                   const std::uint8_t plaintext[16]) noexcept
{
    sm4_compute(ctx->round_key, plaintext, ciphertext);
}

void sm4_dec_block(const SM4Context  *ctx,
                   std::uint8_t       plaintext[16],
                   const std::uint8_t ciphertext[16]) noexcept
{
    sm4_compute(ctx->round_key, ciphertext, plaintext);
}

static void sm4_compute_blocks(const SM4Context   *ctx,
                               std::uint8_t       *ciphertext,
                               const std::uint8_t *plaintext,
                               std::size_t         block_num) noexcept
{
    while (block_num >= 4)
    {
        sm4_compute4(ctx->round_key,          //
                     (const void *)plaintext, //
                     (void *)ciphertext       //
        );                                    //
        plaintext += 16 * 4;
        ciphertext += 16 * 4;
        block_num -= 4;
    }
    while (block_num--)
    {
        sm4_compute(ctx->round_key, plaintext, ciphertext);
        plaintext += 16;
        ciphertext += 16;
    }
}

void sm4_enc_blocks(const SM4Context   *ctx,
                    std::uint8_t       *ciphertext,
                    const std::uint8_t *plaintext,
                    std::size_t         block_num) noexcept
{
    sm4_compute_blocks(ctx, ciphertext, plaintext, block_num);
}

void sm4_dec_blocks(const SM4Context   *ctx,
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept
{
    sm4_compute_blocks(ctx, plaintext, ciphertext, block_num);
}

} // namespace sm4::internal::sm4ni

#endif
