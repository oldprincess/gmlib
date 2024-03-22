#ifndef BLOCK_CIPHER_MODE_SM4_H
#define BLOCK_CIPHER_MODE_SM4_H

#include <gmlib/block_cipher_mode/block_cipher.h>

namespace sm4_internal {

/**
 * @brief SM4 cipher context of commom implementation
 */
typedef struct Sm4CommonCTX
{
    uint32_t round_key[32]; // 32x32-bit round key
} Sm4CommonCTX;

#pragma region "SM4 Params"

static inline uint32_t MEM_LOAD32BE(const void *src)
{
    return ((uint32_t)(((uint8_t *)src)[0]) << 24) |
           ((uint32_t)(((uint8_t *)src)[1]) << 16) |
           ((uint32_t)(((uint8_t *)src)[2]) << 8) |
           ((uint32_t)(((uint8_t *)src)[3]) << 0);
}

static inline void MEM_STORE32BE(void *dst, uint32_t a)
{
    ((uint8_t *)dst)[0] = ((uint32_t)a >> 24) & 0xFF;
    ((uint8_t *)dst)[1] = ((uint32_t)a >> 16) & 0xFF;
    ((uint8_t *)dst)[2] = ((uint32_t)a >> 8) & 0xFF;
    ((uint8_t *)dst)[3] = ((uint32_t)a >> 0) & 0xFF;
}

static const uint8_t SM4_SBOX[256] = {
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
    0xD7, 0xCB, 0x39, 0x48,
};

static const uint32_t FK[4] = {0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc};

static const uint32_t CK[32] = {
    0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269, 0x70777e85, 0x8c939aa1,
    0xa8afb6bd, 0xc4cbd2d9, 0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
    0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9, 0xc0c7ced5, 0xdce3eaf1,
    0xf8ff060d, 0x141b2229, 0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
    0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209, 0x10171e25, 0x2c333a41,
    0x484f565d, 0x646b7279,
};

#define rotl(n, s) ((n) << (s) | (n) >> (32 - (s)))

#pragma endregion

#pragma region "SM4 CORE"

/**
 * @brief               SM4 key schedule
 * @param round_key     32-dword round key
 * @param user_key      16-byte secret key
 * @param enc           encryption(1) / decrytion(0)
 */
static void sm4_common_key_init(uint32_t      round_key[32],
                                const uint8_t user_key[16],
                                int           enc)
{
    uint32_t k[4], tmp;
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
        // SBox
        tmp = (SM4_SBOX[(tmp >> 24) & 0xFF] << 24) |
              (SM4_SBOX[(tmp >> 16) & 0xFF] << 16) |
              (SM4_SBOX[(tmp >> 8) & 0xFF] << 8) |
              (SM4_SBOX[(tmp >> 0) & 0xFF] << 0);
        // L
        round_key[pos] = k[0] ^ tmp ^ rotl(tmp, 13) ^ rotl(tmp, 23);

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
#define SM4_ROUND(X0, X1, X2, X3, RK)                                  \
    do                                                                 \
    {                                                                  \
        uint32_t tmp;                                                  \
        tmp = X1 ^ X2 ^ X3 ^ RK;                                       \
        tmp = (SM4_SBOX[(tmp >> 24) & 0xFF] << 24) |                   \
              (SM4_SBOX[(tmp >> 16) & 0xFF] << 16) |                   \
              (SM4_SBOX[(tmp >> 8) & 0xFF] << 8) |                     \
              (SM4_SBOX[(tmp >> 0) & 0xFF] << 0);                      \
        X0 = X0 ^ tmp ^ rotl(tmp, 2) ^ rotl(tmp, 10) ^ rotl(tmp, 18) ^ \
             rotl(tmp, 24);                                            \
    } while (0)

/**
 * @brief               SM4 block encryption/decryption
 * @param round_key     32-dword encryption/decryption round key
 * @param out           16-byte output block
 * @param in            16-byte input block
 */
static void sm4_common_compute_block(const uint32_t round_key[32],
                                     uint8_t        out[16],
                                     const uint8_t  in[16])
{
    uint32_t x[4];
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
    // reverse, and store output as big endian
    MEM_STORE32BE(out, x[3]);
    MEM_STORE32BE(out + 4, x[2]);
    MEM_STORE32BE(out + 8, x[1]);
    MEM_STORE32BE(out + 12, x[0]);
}

#pragma endregion

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// **************** SM4 CIPHER **********************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

static void sm4_common_enc_key_init(Sm4CommonCTX *ctx,
                                    const uint8_t user_key[16])
{
    sm4_common_key_init(ctx->round_key, user_key, 1);
}

static void sm4_common_dec_key_init(Sm4CommonCTX *ctx,
                                    const uint8_t user_key[16])
{
    sm4_common_key_init(ctx->round_key, user_key, 0);
}

static void sm4_common_enc_block(const Sm4CommonCTX *ctx,
                                 uint8_t             ciphertext[16],
                                 const uint8_t       plaintext[16])
{
    sm4_common_compute_block(ctx->round_key, ciphertext, plaintext);
}

static void sm4_common_dec_block(const Sm4CommonCTX *ctx,
                                 uint8_t             plaintext[16],
                                 const uint8_t       ciphertext[16])
{
    sm4_common_compute_block(ctx->round_key, plaintext, ciphertext);
}

static void sm4_common_enc_blocks(const Sm4CommonCTX *ctx,
                                  uint8_t            *ciphertext,
                                  const uint8_t      *plaintext,
                                  size_t              block_num)
{
    while (block_num)
    {
        sm4_common_enc_block(ctx, ciphertext, plaintext);
        ciphertext += 16;
        plaintext += 16;
        block_num -= 1;
    }
}

static void sm4_common_dec_blocks(const Sm4CommonCTX *ctx,
                                  uint8_t            *plaintext,
                                  const uint8_t      *ciphertext,
                                  size_t              block_num)
{
    while (block_num)
    {
        sm4_common_dec_block(ctx, plaintext, ciphertext);
        plaintext += 16;
        ciphertext += 16;
        block_num -= 1;
    }
}

}; // namespace sm4_internal

class SM4 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = 16;
    static constexpr std::size_t USER_KEY_LEN = 16;
    static constexpr std::size_t PARALLEL_NUM = 1;

private:
    sm4_internal::Sm4CommonCTX ctx_;
    int                        enc_;

public:
    SM4() = default;

public:
    void set_key(const std::uint8_t *user_key, int enc) override
    {
        enc_ = enc;
        if (enc == SM4::ENCRYPTION)
        {
            sm4_internal::sm4_common_enc_key_init(&ctx_, user_key);
        }
        else
        {
            sm4_internal::sm4_common_dec_key_init(&ctx_, user_key);
        }
    }

    void encrypt_block(std::uint8_t *out, const std::uint8_t *in) const override
    {
        sm4_internal::sm4_common_enc_block(&ctx_, out, in);
    }

    void decrypt_block(std::uint8_t *out, const std::uint8_t *in) const override
    {
        sm4_internal::sm4_common_dec_block(&ctx_, out, in);
    }

    void encrypt_blocks(std::uint8_t       *out,
                        const std::uint8_t *in,
                        std::size_t         block_num) const override
    {
        sm4_internal::sm4_common_enc_blocks(&ctx_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t       *out,
                        const std::uint8_t *in,
                        std::size_t         block_num) const override
    {
        sm4_internal::sm4_common_dec_blocks(&ctx_, out, in, block_num);
    }
};

#endif