#include <gmlib/des/internal/des_common.h>

namespace des::internal::common {

#pragma region "DES CORE"

#define MEM_LOAD64BE(src)                        \
    (((uint64_t)(((uint8_t *)(src))[0]) << 56) | \
     ((uint64_t)(((uint8_t *)(src))[1]) << 48) | \
     ((uint64_t)(((uint8_t *)(src))[2]) << 40) | \
     ((uint64_t)(((uint8_t *)(src))[3]) << 32) | \
     ((uint64_t)(((uint8_t *)(src))[4]) << 24) | \
     ((uint64_t)(((uint8_t *)(src))[5]) << 16) | \
     ((uint64_t)(((uint8_t *)(src))[6]) << 8) |  \
     ((uint64_t)(((uint8_t *)(src))[7]) << 0))

#define MEM_STORE64BE(dst, a)                              \
    (((uint8_t *)(dst))[0] = ((uint64_t)(a) >> 56) & 0xFF, \
     ((uint8_t *)(dst))[1] = ((uint64_t)(a) >> 48) & 0xFF, \
     ((uint8_t *)(dst))[2] = ((uint64_t)(a) >> 40) & 0xFF, \
     ((uint8_t *)(dst))[3] = ((uint64_t)(a) >> 32) & 0xFF, \
     ((uint8_t *)(dst))[4] = ((uint64_t)(a) >> 24) & 0xFF, \
     ((uint8_t *)(dst))[5] = ((uint64_t)(a) >> 16) & 0xFF, \
     ((uint8_t *)(dst))[6] = ((uint64_t)(a) >> 8) & 0xFF,  \
     ((uint8_t *)(dst))[7] = ((uint64_t)(a) >> 0) & 0xFF)

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************* DES CIPHER CORE ********************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

#define DES_MASK_4  0xF
#define DES_MASK_6  0x7F
#define DES_MASK_28 0xFFFFFFFU
#define DES_MASK_56 0xFFFFFFFFFFFFFFULL

/* IP 64bit->64bit */
static uint64_t ip_trans(uint64_t input)
{
    // IP
    static uint16_t ip_table[64] = {
        58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
    uint64_t output = 0;
    for (int i = 0; i < 64; i++)
        output = (output << 1) | ((input >> (64 - ip_table[i])) & 1);
    return output;
}

/* IP INV 64bit->64bit */
static uint64_t ip_i_trans(uint64_t input)
{
    static uint16_t ip_i_table[64] = {
        40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25};
    uint64_t output = 0;
    for (int i = 0; i < 64; i++)
        output = (output << 1) | ((input >> (64 - ip_i_table[i])) & 1);
    return output;
}

/* E 32bit->48bit */
static uint64_t expand(uint32_t input)
{
    uint8_t  split[8] = {0};
    uint64_t output   = 0;
    for (int i = 7; i >= 0; i--)
    {
        split[i] = (uint8_t)(input & DES_MASK_4);
        input >>= 4;
    }
    uint8_t temp = 0;
    temp         = ((split[7] & 1) << 5) | (split[0] << 1) | (split[1] >> 3);
    output       = (output << 6) | temp;
    temp         = ((split[0] & 1) << 5) | (split[1] << 1) | (split[2] >> 3);
    output       = (output << 6) | temp;
    temp         = ((split[1] & 1) << 5) | (split[2] << 1) | (split[3] >> 3);
    output       = (output << 6) | temp;
    temp         = ((split[2] & 1) << 5) | (split[3] << 1) | (split[4] >> 3);
    output       = (output << 6) | temp;
    temp         = ((split[3] & 1) << 5) | (split[4] << 1) | (split[5] >> 3);
    output       = (output << 6) | temp;
    temp         = ((split[4] & 1) << 5) | (split[5] << 1) | (split[6] >> 3);
    output       = (output << 6) | temp;
    temp         = ((split[5] & 1) << 5) | (split[6] << 1) | (split[7] >> 3);
    output       = (output << 6) | temp;
    temp         = ((split[6] & 1) << 5) | (split[7] << 1) | (split[0] >> 3);
    output       = (output << 6) | temp;

    return output;
}

/* P 32bit->32bit */
static uint32_t p_trans(uint32_t input)
{
    static const uint8_t p_table[32] = {
        16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
        2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25,
    };
    uint32_t output = 0;
    for (int i = 0; i < 32; i++)
        output = (output << 1) | ((input >> (32 - p_table[i])) & 1);
    return output;
}

/* 64bit->64bit */
static uint32_t sbox(uint64_t input)
{
    static const uint8_t box[8][4][16] = {
        {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
         {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
         {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
         {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
        {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
         {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
         {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
         {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
        {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
         {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
         {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
         {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
        {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
         {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
         {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
         {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
        {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
         {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
         {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
         {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
        {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
         {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
         {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
         {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
        {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
         {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
         {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
         {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
        {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
         {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
         {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
         {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
    uint32_t output   = 0;
    uint8_t  split[8] = {0};
    for (int i = 7; i >= 0; i--)
    {
        split[i] = (uint8_t)(input & DES_MASK_6);
        input >>= 6;
    }
    for (int i = 0; i < 8; i++)
    {
        int row = (split[i] & 1) | ((split[i] >> 4) & 0b10);
        int col = (split[i] >> 1 & 0xF);
        output  = (output << 4) | box[i][row][col];
    }
    return output;
}

/* PC1 64bit->56bit */
static uint64_t pc_trans_1(uint64_t input)
{
    static const uint8_t pc_1_table[56] = {
        57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34, 26, 18,
        10, 2,  59, 51, 43, 35, 27, 19, 11, 3,  60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15, 7,  62, 54, 46, 38, 30, 22,
        14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12, 4,
    };
    uint64_t output = 0;
    for (int i = 0; i < 56; i++)
        output = (output << 1) | ((input >> (64 - pc_1_table[i])) & 1);
    return output;
}

/* PC2 56bit->48bit */
static uint64_t pc_trans_2(uint64_t input)
{
    static const uint8_t pc_2_table[48] = {
        14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10, 23, 19, 12, 4,
        26, 8,  16, 7,  27, 20, 13, 2,  41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32,
    };
    uint64_t output = 0;
    for (int i = 0; i < 48; i++)
        output = (output << 1) | ((input >> (56 - pc_2_table[i])) & 1);
    return output;
}

static void key_generate(uint64_t *key_rounds, uint64_t key, int enc)
{
    static uint8_t const k_move[16] = {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1,
    };
    key           = pc_trans_1(key);
    uint32_t key1 = (uint32_t)(key >> 28) & DES_MASK_28;
    uint32_t key2 = (uint32_t)(key & DES_MASK_28);
    int      cur = enc ? 0 : 15, step = enc ? 1 : -1;
    for (int i = 0; i < 16; i++)
    {
        key1 = ((key1 << k_move[i]) | (key1 >> (28 - k_move[i]))) & DES_MASK_28;
        key2 = ((key2 << k_move[i]) | (key2 >> (28 - k_move[i]))) & DES_MASK_28;
        key_rounds[cur] =
            pc_trans_2((((uint64_t)key1) << 28) | key2) & DES_MASK_56;
        cur += step;
    }
}

static uint64_t des_crypt(const uint64_t *key_rounds, uint64_t text)
{
    text           = ip_trans(text);
    uint32_t text1 = (uint32_t)(text >> 32), text2 = (uint32_t)text;
    for (int i = 0; i < 16; i++)
    {
        uint64_t sbox_input  = expand(text2) ^ key_rounds[i];
        uint32_t sbox_output = sbox(sbox_input);
        uint32_t temp        = text2;
        text2                = text1 ^ p_trans(sbox_output);
        text1                = temp;
    }
    uint64_t output = (((uint64_t)text2) << 32) | text1;
    return ip_i_trans(output);
}
#pragma endregion

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// **************** DES CIPHER **********************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

void des_enc_key_init(DesCTX *ctx, const std::uint8_t user_key[8]) noexcept
{
    std::uint64_t key = MEM_LOAD64BE(user_key);
    key_generate(ctx->round_key, key, 1);
}

void des_dec_key_init(DesCTX *ctx, const std::uint8_t user_key[8]) noexcept
{
    std::uint64_t key = MEM_LOAD64BE(user_key);
    key_generate(ctx->round_key, key, 0);
}

void des_enc_block(const DesCTX      *ctx,
                   std::uint8_t       ciphertext[8],
                   const std::uint8_t plaintext[8]) noexcept
{
    std::uint64_t pt = MEM_LOAD64BE(plaintext);
    std::uint64_t ct = des_crypt(ctx->round_key, pt);
    MEM_STORE64BE(ciphertext, ct);
}

void des_dec_block(const DesCTX      *ctx,
                   std::uint8_t       plaintext[8],
                   const std::uint8_t ciphertext[8]) noexcept
{
    std::uint64_t ct = MEM_LOAD64BE(ciphertext);
    std::uint64_t pt = des_crypt(ctx->round_key, ct);
    MEM_STORE64BE(plaintext, pt);
}

void des_enc_blocks(const DesCTX       *ctx,
                    std::uint8_t       *ciphertext,
                    const std::uint8_t *plaintext,
                    std::size_t         block_num) noexcept
{
    while (block_num)
    {
        des_enc_block(ctx, ciphertext, plaintext);
        ciphertext += 8;
        plaintext += 8;
        block_num -= 1;
    }
}

void des_dec_blocks(const DesCTX       *ctx,
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept
{
    while (block_num)
    {
        des_dec_block(ctx, plaintext, ciphertext);
        plaintext += 8;
        ciphertext += 8;
        block_num -= 1;
    }
}

}; // namespace des::internal::common