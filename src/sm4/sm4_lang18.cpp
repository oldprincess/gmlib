#if defined(SUPPORT_SM4_LANG18)

#include "sm4_lang18.h"

#include <immintrin.h>

#include "sm4_lang18_tb.h"

namespace sm4::internal::lang18 {

using namespace sm4::internal::lang18_tables;

#pragma region "Params And Define"

static inline std::uint32_t MEM_LOAD32BE(const void *src)
{
    return ((std::uint32_t)(((const std::uint8_t *)src)[0]) << 24) |
           ((std::uint32_t)(((const std::uint8_t *)src)[1]) << 16) |
           ((std::uint32_t)(((const std::uint8_t *)src)[2]) << 8) |
           ((std::uint32_t)(((const std::uint8_t *)src)[3]) << 0);
}

static inline void MEM_STORE32BE(void *dst, std::uint32_t a)
{
    ((std::uint8_t *)dst)[0] = ((std::uint32_t)a >> 24) & 0xFF;
    ((std::uint8_t *)dst)[1] = ((std::uint32_t)a >> 16) & 0xFF;
    ((std::uint8_t *)dst)[2] = ((std::uint32_t)a >> 8) & 0xFF;
    ((std::uint8_t *)dst)[3] = ((std::uint32_t)a >> 0) & 0xFF;
}

static inline std::uint32_t rotl(std::uint32_t n, int s)
{
    return (n << s) | (n >> (32 - s));
}

static const std::uint32_t FK[4] = {
    0xa3b1bac6,
    0x56aa3350,
    0x677d9197,
    0xb27022dc,
};

static const std::uint32_t CK[32] = {
    0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269, 0x70777e85, 0x8c939aa1,
    0xa8afb6bd, 0xc4cbd2d9, 0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
    0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9, 0xc0c7ced5, 0xdce3eaf1,
    0xf8ff060d, 0x141b2229, 0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
    0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209, 0x10171e25, 0x2c333a41,
    0x484f565d, 0x646b7279,
};

#pragma endregion

#pragma region "Core Func"

/**
 * @brief               SM4 key schedule
 * @param round_key     32-dword round key
 * @param user_key      16-byte secret key
 * @param enc           encryption(1) / decrytion(0)
 */
static void sm4_key_init(std::uint32_t      round_key[32],
                         const std::uint8_t user_key[16],
                         int                enc) noexcept
{
    std::uint32_t k[4], tmp, tmp1;
    // load key as big endian
    k[0] = MEM_LOAD32BE(user_key + 0) ^ FK[0];
    k[1] = MEM_LOAD32BE(user_key + 4) ^ FK[1];
    k[2] = MEM_LOAD32BE(user_key + 8) ^ FK[2];
    k[3] = MEM_LOAD32BE(user_key + 12) ^ FK[3];
    // 32 round
    int pos = (enc) ? 0 : 31, step = (enc) ? 1 : -1;
    for (int i = 0; i < 32; i++)
    {
        // Xor
        tmp = k[1] ^ k[2] ^ k[3] ^ CK[i];
        // Sbox + L
        tmp1 = KT0[(tmp >> 24) & 0xFF];
        tmp1 ^= KT1[(tmp >> 16) & 0xFF];
        tmp1 ^= KT2[(tmp >> 8) & 0xFF];
        tmp1 ^= KT3[(tmp >> 0) & 0xFF];
        round_key[pos] = k[0] ^ tmp1;

        k[0] = k[1];
        k[1] = k[2];
        k[2] = k[3];
        k[3] = round_key[pos];

        pos += step;
    }
}

/**
 * @brief       SM4 round function, X0=X0^T(X1^X2^X3^RK)
 * @param X0    dword data
 * @param X1    dword data
 * @param X2    dword data
 * @param X3    dword data
 * @param RK    dword encryption/decryption round key
 */
#define SM4_ROUND(X0, X1, X2, X3, RK) \
    do                                \
    {                                 \
        std::uint32_t tmp;            \
        tmp = X1 ^ X2 ^ X3 ^ RK;      \
        X0 ^= T0[(tmp >> 24) & 0xFF]; \
        X0 ^= T1[(tmp >> 16) & 0xFF]; \
        X0 ^= T2[(tmp >> 8) & 0xFF];  \
        X0 ^= T3[(tmp >> 0) & 0xFF];  \
    } while (0)

/**
 * @brief               SM4 block encryption/decryption
 * @param round_key     32-dword encryption/decryption round key
 * @param out           16-byte output block
 * @param in            16-byte input block
 */
static void sm4_compute_block(const std::uint32_t round_key[32],
                              std::uint8_t        out[16],
                              const std::uint8_t  in[16]) noexcept
{
    std::uint32_t x[4];
    // load input as big endian
    x[0] = MEM_LOAD32BE(in + 0);
    x[1] = MEM_LOAD32BE(in + 4);
    x[2] = MEM_LOAD32BE(in + 8);
    x[3] = MEM_LOAD32BE(in + 12);
    // 32 round
    for (int i = 0; i < 32; i += 4)
    {
        SM4_ROUND(x[0], x[1], x[2], x[3], round_key[i]);
        SM4_ROUND(x[1], x[2], x[3], x[0], round_key[i + 1]);
        SM4_ROUND(x[2], x[3], x[0], x[1], round_key[i + 2]);
        SM4_ROUND(x[3], x[0], x[1], x[2], round_key[i + 3]);
    }
    // store output
    MEM_STORE32BE(out, x[3]);
    MEM_STORE32BE(out + 4, x[2]);
    MEM_STORE32BE(out + 8, x[1]);
    MEM_STORE32BE(out + 12, x[0]);
}

/**
 * @brief               SM4 block encryption/decryption, 4 parallel
 * @param round_key     32-dword encryption/decryption round key
 * @param out           4x16-byte output blocks
 * @param in            4x16-byte input blocks
 */
static void sm4_compute_blocks_x4(const std::uint32_t round_key[32],
                                  std::uint8_t        out[64],
                                  const std::uint8_t  in[64]) noexcept
{
    std::uint32_t x[4 * 4], tmp[4];
    // load input as big endian
    x[0]  = MEM_LOAD32BE(in + 0);
    x[1]  = MEM_LOAD32BE(in + 4);
    x[2]  = MEM_LOAD32BE(in + 8);
    x[3]  = MEM_LOAD32BE(in + 12);
    x[4]  = MEM_LOAD32BE(in + 16);
    x[5]  = MEM_LOAD32BE(in + 20);
    x[6]  = MEM_LOAD32BE(in + 24);
    x[7]  = MEM_LOAD32BE(in + 28);
    x[8]  = MEM_LOAD32BE(in + 32);
    x[9]  = MEM_LOAD32BE(in + 36);
    x[10] = MEM_LOAD32BE(in + 40);
    x[11] = MEM_LOAD32BE(in + 44);
    x[12] = MEM_LOAD32BE(in + 48);
    x[13] = MEM_LOAD32BE(in + 52);
    x[14] = MEM_LOAD32BE(in + 56);
    x[15] = MEM_LOAD32BE(in + 60);
    // 32 round
    for (int i = 0; i < 32; i += 4)
    {
        // ====================== 0 ======================
        tmp[0] = x[1] ^ x[2] ^ x[3] ^ round_key[i];
        tmp[1] = x[1 + 4] ^ x[2 + 4] ^ x[3 + 4] ^ round_key[i];
        tmp[2] = x[1 + 8] ^ x[2 + 8] ^ x[3 + 8] ^ round_key[i];
        tmp[3] = x[1 + 12] ^ x[2 + 12] ^ x[3 + 12] ^ round_key[i];

        x[0] ^= T0[(tmp[0] >> 24) & 0xFF];
        x[0] ^= T1[(tmp[0] >> 16) & 0xFF];
        x[0] ^= T2[(tmp[0] >> 8) & 0xFF];
        x[0] ^= T3[(tmp[0] >> 0) & 0xFF];

        x[0 + 4] ^= T0[(tmp[1] >> 24) & 0xFF];
        x[0 + 4] ^= T1[(tmp[1] >> 16) & 0xFF];
        x[0 + 4] ^= T2[(tmp[1] >> 8) & 0xFF];
        x[0 + 4] ^= T3[(tmp[1] >> 0) & 0xFF];

        x[0 + 8] ^= T0[(tmp[2] >> 24) & 0xFF];
        x[0 + 8] ^= T1[(tmp[2] >> 16) & 0xFF];
        x[0 + 8] ^= T2[(tmp[2] >> 8) & 0xFF];
        x[0 + 8] ^= T3[(tmp[2] >> 0) & 0xFF];

        x[0 + 12] ^= T0[(tmp[3] >> 24) & 0xFF];
        x[0 + 12] ^= T1[(tmp[3] >> 16) & 0xFF];
        x[0 + 12] ^= T2[(tmp[3] >> 8) & 0xFF];
        x[0 + 12] ^= T3[(tmp[3] >> 0) & 0xFF];

        // ====================== 1 ======================
        tmp[0] = x[2] ^ x[3] ^ x[0] ^ round_key[i + 1];
        tmp[1] = x[2 + 4] ^ x[3 + 4] ^ x[0 + 4] ^ round_key[i + 1];
        tmp[2] = x[2 + 8] ^ x[3 + 8] ^ x[0 + 8] ^ round_key[i + 1];
        tmp[3] = x[2 + 12] ^ x[3 + 12] ^ x[0 + 12] ^ round_key[i + 1];

        x[1] ^= T0[(tmp[0] >> 24) & 0xFF];
        x[1] ^= T1[(tmp[0] >> 16) & 0xFF];
        x[1] ^= T2[(tmp[0] >> 8) & 0xFF];
        x[1] ^= T3[(tmp[0] >> 0) & 0xFF];

        x[1 + 4] ^= T0[(tmp[1] >> 24) & 0xFF];
        x[1 + 4] ^= T1[(tmp[1] >> 16) & 0xFF];
        x[1 + 4] ^= T2[(tmp[1] >> 8) & 0xFF];
        x[1 + 4] ^= T3[(tmp[1] >> 0) & 0xFF];

        x[1 + 8] ^= T0[(tmp[2] >> 24) & 0xFF];
        x[1 + 8] ^= T1[(tmp[2] >> 16) & 0xFF];
        x[1 + 8] ^= T2[(tmp[2] >> 8) & 0xFF];
        x[1 + 8] ^= T3[(tmp[2] >> 0) & 0xFF];

        x[1 + 12] ^= T0[(tmp[3] >> 24) & 0xFF];
        x[1 + 12] ^= T1[(tmp[3] >> 16) & 0xFF];
        x[1 + 12] ^= T2[(tmp[3] >> 8) & 0xFF];
        x[1 + 12] ^= T3[(tmp[3] >> 0) & 0xFF];

        // ====================== 2 ======================
        tmp[0] = x[3] ^ x[0] ^ x[1] ^ round_key[i + 2];
        tmp[1] = x[3 + 4] ^ x[0 + 4] ^ x[1 + 4] ^ round_key[i + 2];
        tmp[2] = x[3 + 8] ^ x[0 + 8] ^ x[1 + 8] ^ round_key[i + 2];
        tmp[3] = x[3 + 12] ^ x[0 + 12] ^ x[1 + 12] ^ round_key[i + 2];

        x[2] ^= T0[(tmp[0] >> 24) & 0xFF];
        x[2] ^= T1[(tmp[0] >> 16) & 0xFF];
        x[2] ^= T2[(tmp[0] >> 8) & 0xFF];
        x[2] ^= T3[(tmp[0] >> 0) & 0xFF];

        x[2 + 4] ^= T0[(tmp[1] >> 24) & 0xFF];
        x[2 + 4] ^= T1[(tmp[1] >> 16) & 0xFF];
        x[2 + 4] ^= T2[(tmp[1] >> 8) & 0xFF];
        x[2 + 4] ^= T3[(tmp[1] >> 0) & 0xFF];

        x[2 + 8] ^= T0[(tmp[2] >> 24) & 0xFF];
        x[2 + 8] ^= T1[(tmp[2] >> 16) & 0xFF];
        x[2 + 8] ^= T2[(tmp[2] >> 8) & 0xFF];
        x[2 + 8] ^= T3[(tmp[2] >> 0) & 0xFF];

        x[2 + 12] ^= T0[(tmp[3] >> 24) & 0xFF];
        x[2 + 12] ^= T1[(tmp[3] >> 16) & 0xFF];
        x[2 + 12] ^= T2[(tmp[3] >> 8) & 0xFF];
        x[2 + 12] ^= T3[(tmp[3] >> 0) & 0xFF];

        // ====================== 3 ======================
        tmp[0] = x[0] ^ x[1] ^ x[2] ^ round_key[i + 3];
        tmp[1] = x[0 + 4] ^ x[1 + 4] ^ x[2 + 4] ^ round_key[i + 3];
        tmp[2] = x[0 + 8] ^ x[1 + 8] ^ x[2 + 8] ^ round_key[i + 3];
        tmp[3] = x[0 + 12] ^ x[1 + 12] ^ x[2 + 12] ^ round_key[i + 3];

        x[3] ^= T0[(tmp[0] >> 24) & 0xFF];
        x[3] ^= T1[(tmp[0] >> 16) & 0xFF];
        x[3] ^= T2[(tmp[0] >> 8) & 0xFF];
        x[3] ^= T3[(tmp[0] >> 0) & 0xFF];

        x[3 + 4] ^= T0[(tmp[1] >> 24) & 0xFF];
        x[3 + 4] ^= T1[(tmp[1] >> 16) & 0xFF];
        x[3 + 4] ^= T2[(tmp[1] >> 8) & 0xFF];
        x[3 + 4] ^= T3[(tmp[1] >> 0) & 0xFF];

        x[3 + 8] ^= T0[(tmp[2] >> 24) & 0xFF];
        x[3 + 8] ^= T1[(tmp[2] >> 16) & 0xFF];
        x[3 + 8] ^= T2[(tmp[2] >> 8) & 0xFF];
        x[3 + 8] ^= T3[(tmp[2] >> 0) & 0xFF];

        x[3 + 12] ^= T0[(tmp[3] >> 24) & 0xFF];
        x[3 + 12] ^= T1[(tmp[3] >> 16) & 0xFF];
        x[3 + 12] ^= T2[(tmp[3] >> 8) & 0xFF];
        x[3 + 12] ^= T3[(tmp[3] >> 0) & 0xFF];
    }
    // store output
    MEM_STORE32BE(out, x[3]);
    MEM_STORE32BE(out + 4, x[2]);
    MEM_STORE32BE(out + 8, x[1]);
    MEM_STORE32BE(out + 12, x[0]);

    MEM_STORE32BE(out + 16, x[3 + 4]);
    MEM_STORE32BE(out + 20, x[2 + 4]);
    MEM_STORE32BE(out + 24, x[1 + 4]);
    MEM_STORE32BE(out + 28, x[0 + 4]);

    MEM_STORE32BE(out + 32, x[3 + 8]);
    MEM_STORE32BE(out + 36, x[2 + 8]);
    MEM_STORE32BE(out + 40, x[1 + 8]);
    MEM_STORE32BE(out + 44, x[0 + 8]);

    MEM_STORE32BE(out + 48, x[3 + 12]);
    MEM_STORE32BE(out + 52, x[2 + 12]);
    MEM_STORE32BE(out + 56, x[1 + 12]);
    MEM_STORE32BE(out + 60, x[0 + 12]);
}

/**
 * @brief               SM4 block encryption/decryption
 * @param round_key     32-dword encryption/decryption round key
 * @param out           output blocks, length of 16 x block_num bytes
 * @param in            input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
static void sm4_compute_blocks(const std::uint32_t round_key[32],
                               std::uint8_t       *out,
                               const std::uint8_t *in,
                               std::size_t         block_num) noexcept
{
    while (block_num >= 4)
    {
        sm4_compute_blocks_x4(round_key, out, in);
        out += 16 * 4, in += 16 * 4, block_num -= 4;
    }
    while (block_num)
    {
        sm4_compute_block(round_key, out, in);
        out += 16, in += 16, block_num -= 1;
    }
}

#pragma endregion

void sm4_enc_key_init(SM4Context *ctx, const uint8_t user_key[16]) noexcept
{
    sm4_key_init(ctx->round_key, user_key, 1);
}

void sm4_dec_key_init(SM4Context *ctx, const uint8_t user_key[16]) noexcept
{
    sm4_key_init(ctx->round_key, user_key, 0);
}

void sm4_enc_block(const SM4Context  *ctx,
                   std::uint8_t       ciphertext[16],
                   const std::uint8_t plaintext[16]) noexcept
{
    sm4_compute_block(ctx->round_key, ciphertext, plaintext);
}

void sm4_dec_block(const SM4Context  *ctx,
                   std::uint8_t       plaintext[16],
                   const std::uint8_t ciphertext[16]) noexcept
{
    sm4_compute_block(ctx->round_key, plaintext, ciphertext);
}

void sm4_enc_blocks(const SM4Context   *ctx,
                    std::uint8_t       *ciphertext,
                    const std::uint8_t *plaintext,
                    std::size_t         block_num) noexcept
{
    sm4_compute_blocks(ctx->round_key, ciphertext, plaintext, block_num);
}

void sm4_dec_blocks(const SM4Context   *ctx,
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept
{
    sm4_compute_blocks(ctx->round_key, plaintext, ciphertext, block_num);
}

}; // namespace sm4::internal::lang18
#endif
