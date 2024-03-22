#if defined(CPU_FLAG_AES) && defined(CPU_FLAG_SSE2)
#include <gmlib/aes/internal/aes_aesni.h>
#include <immintrin.h>

namespace aes::internal::aesni {

#define _mm_shuffle_epi64(a, b, imm8) \
    _mm_castpd_si128(                 \
        _mm_shuffle_pd(_mm_castsi128_pd(a), _mm_castsi128_pd(b), imm8))

/**
 * Starting from here, until the next similar comment declaration.
 * the code is
 * "derived from Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp"
 */

/**
 * MIT License. Copyright (c) 2023 Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp
 */
static inline __m128i AES_128_ASSIST(__m128i temp1, __m128i temp2) noexcept
{
    __m128i temp3;
    temp2 = _mm_shuffle_epi32(temp2, 0xff);
    temp3 = _mm_slli_si128(temp1, 0x4);
    temp1 = _mm_xor_si128(temp1, temp3);
    temp3 = _mm_slli_si128(temp3, 0x4);
    temp1 = _mm_xor_si128(temp1, temp3);
    temp3 = _mm_slli_si128(temp3, 0x4);
    temp1 = _mm_xor_si128(temp1, temp3);
    temp1 = _mm_xor_si128(temp1, temp2);
    return temp1;
}

/**
 * MIT License. Copyright (c) 2023 Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp
 */
static void AES_128_Key_Expansion(const unsigned char* userkey,
                                  unsigned char*       key) noexcept
{
    __m128i  temp1, temp2;
    __m128i* Key_Schedule = (__m128i*)key;

    temp1            = _mm_loadu_si128((__m128i*)userkey);
    Key_Schedule[0]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x1);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[1]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x2);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[2]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x4);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[3]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x8);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[4]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x10);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[5]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x20);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[6]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x40);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[7]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x80);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[8]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x1b);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[9]  = temp1;
    temp2            = _mm_aeskeygenassist_si128(temp1, 0x36);
    temp1            = AES_128_ASSIST(temp1, temp2);
    Key_Schedule[10] = temp1;
}

/**
 * MIT License. Copyright (c) 2023 Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp
 */
static inline void KEY_192_ASSIST(__m128i* temp1,
                                  __m128i* temp2,
                                  __m128i* temp3) noexcept
{
    __m128i temp4;
    *temp2 = _mm_shuffle_epi32(*temp2, 0x55);
    temp4  = _mm_slli_si128(*temp1, 0x4);
    *temp1 = _mm_xor_si128(*temp1, temp4);
    temp4  = _mm_slli_si128(temp4, 0x4);
    *temp1 = _mm_xor_si128(*temp1, temp4);
    temp4  = _mm_slli_si128(temp4, 0x4);
    *temp1 = _mm_xor_si128(*temp1, temp4);
    *temp1 = _mm_xor_si128(*temp1, *temp2);
    *temp2 = _mm_shuffle_epi32(*temp1, 0xff);
    temp4  = _mm_slli_si128(*temp3, 0x4);
    *temp3 = _mm_xor_si128(*temp3, temp4);
    *temp3 = _mm_xor_si128(*temp3, *temp2);
}

/**
 * MIT License. Copyright (c) 2023 Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp
 */
static void AES_192_Key_Expansion(const unsigned char* userkey,
                                  unsigned char*       key) noexcept
{
    __m128i  temp1, temp2, temp3;
    __m128i* Key_Schedule = (__m128i*)key;
    temp1                 = _mm_loadu_si128((__m128i*)userkey);
    temp3                 = _mm_loadu_si128((__m128i*)(userkey + 16));
    Key_Schedule[0]       = temp1;
    Key_Schedule[1]       = temp3;
    temp2                 = _mm_aeskeygenassist_si128(temp3, 0x1);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[1] = _mm_shuffle_epi64(Key_Schedule[1], temp1, 0);
    Key_Schedule[2] = _mm_shuffle_epi64(temp1, temp3, 1);
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x2);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[3] = temp1;
    Key_Schedule[4] = temp3;
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x4);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[4] = _mm_shuffle_epi64(Key_Schedule[4], temp1, 0);
    Key_Schedule[5] = _mm_shuffle_epi64(temp1, temp3, 1);
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x8);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[6] = temp1;
    Key_Schedule[7] = temp3;
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x10);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[7] = _mm_shuffle_epi64(Key_Schedule[7], temp1, 0);
    Key_Schedule[8] = _mm_shuffle_epi64(temp1, temp3, 1);
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x20);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[9]  = temp1;
    Key_Schedule[10] = temp3;
    temp2            = _mm_aeskeygenassist_si128(temp3, 0x40);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[10] = _mm_shuffle_epi64(Key_Schedule[10], temp1, 0);
    Key_Schedule[11] = _mm_shuffle_epi64(temp1, temp3, 1);
    temp2            = _mm_aeskeygenassist_si128(temp3, 0x80);
    KEY_192_ASSIST(&temp1, &temp2, &temp3);
    Key_Schedule[12] = temp1;
}

/**
 * MIT License. Copyright (c) 2023 Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp
 */
static inline void KEY_256_ASSIST_1(__m128i* temp1, __m128i* temp2) noexcept
{
    __m128i temp4;
    *temp2 = _mm_shuffle_epi32(*temp2, 0xff);
    temp4  = _mm_slli_si128(*temp1, 0x4);
    *temp1 = _mm_xor_si128(*temp1, temp4);
    temp4  = _mm_slli_si128(temp4, 0x4);
    *temp1 = _mm_xor_si128(*temp1, temp4);
    temp4  = _mm_slli_si128(temp4, 0x4);
    *temp1 = _mm_xor_si128(*temp1, temp4);
    *temp1 = _mm_xor_si128(*temp1, *temp2);
}

/**
 * MIT License. Copyright (c) 2023 Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp
 */
static inline void KEY_256_ASSIST_2(__m128i* temp1, __m128i* temp3) noexcept
{
    __m128i temp2, temp4;
    temp4  = _mm_aeskeygenassist_si128(*temp1, 0x0);
    temp2  = _mm_shuffle_epi32(temp4, 0xaa);
    temp4  = _mm_slli_si128(*temp3, 0x4);
    *temp3 = _mm_xor_si128(*temp3, temp4);
    temp4  = _mm_slli_si128(temp4, 0x4);
    *temp3 = _mm_xor_si128(*temp3, temp4);
    temp4  = _mm_slli_si128(temp4, 0x4);
    *temp3 = _mm_xor_si128(*temp3, temp4);
    *temp3 = _mm_xor_si128(*temp3, temp2);
}

/**
 * MIT License. Copyright (c) 2023 Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp
 */
static void AES_256_Key_Expansion(const unsigned char* userkey,
                                  unsigned char*       key) noexcept
{
    __m128i  temp1, temp2, temp3;
    __m128i* Key_Schedule = (__m128i*)key;
    temp1                 = _mm_loadu_si128((__m128i*)userkey);
    temp3                 = _mm_loadu_si128((__m128i*)(userkey + 16));
    Key_Schedule[0]       = temp1;
    Key_Schedule[1]       = temp3;
    temp2                 = _mm_aeskeygenassist_si128(temp3, 0x01);
    KEY_256_ASSIST_1(&temp1, &temp2);
    Key_Schedule[2] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    Key_Schedule[3] = temp3;
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x02);
    KEY_256_ASSIST_1(&temp1, &temp2);
    Key_Schedule[4] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    Key_Schedule[5] = temp3;
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x04);
    KEY_256_ASSIST_1(&temp1, &temp2);
    Key_Schedule[6] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    Key_Schedule[7] = temp3;
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x08);
    KEY_256_ASSIST_1(&temp1, &temp2);
    Key_Schedule[8] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    Key_Schedule[9] = temp3;
    temp2           = _mm_aeskeygenassist_si128(temp3, 0x10);
    KEY_256_ASSIST_1(&temp1, &temp2);
    Key_Schedule[10] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    Key_Schedule[11] = temp3;
    temp2            = _mm_aeskeygenassist_si128(temp3, 0x20);
    KEY_256_ASSIST_1(&temp1, &temp2);
    Key_Schedule[12] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    Key_Schedule[13] = temp3;
    temp2            = _mm_aeskeygenassist_si128(temp3, 0x40);
    KEY_256_ASSIST_1(&temp1, &temp2);
    Key_Schedule[14] = temp1;
}

/**
 * Ending here, to the previous similar comment declaration.
 * the code is
 * "derived from Jubal Mordecai Velasco,
 * https://github.com/mrdcvlsc/AES/blob/main/AES.hpp"
 */

// ****************************************
// ************* AES 128 ******************
// ****************************************

void aes128_enc_key_init(Aes128CTX*         ctx,
                         const std::uint8_t user_key[16]) noexcept
{
    __m128i rk[11];
    AES_128_Key_Expansion(user_key, (unsigned char*)rk);
    _mm_storeu_si128((__m128i*)(ctx->round_key[0]), rk[0]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[1]), rk[1]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[2]), rk[2]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[3]), rk[3]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[4]), rk[4]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[5]), rk[5]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[6]), rk[6]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[7]), rk[7]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[8]), rk[8]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[9]), rk[9]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[10]), rk[10]);
}

void aes128_dec_key_init(Aes128CTX*         ctx,
                         const std::uint8_t user_key[16]) noexcept
{
    __m128i rk[11];
    AES_128_Key_Expansion(user_key, (unsigned char*)rk);
    _mm_storeu_si128((__m128i*)(ctx->round_key[0]), rk[10]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[1]), _mm_aesimc_si128(rk[9]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[2]), _mm_aesimc_si128(rk[8]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[3]), _mm_aesimc_si128(rk[7]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[4]), _mm_aesimc_si128(rk[6]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[5]), _mm_aesimc_si128(rk[5]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[6]), _mm_aesimc_si128(rk[4]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[7]), _mm_aesimc_si128(rk[3]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[8]), _mm_aesimc_si128(rk[2]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[9]), _mm_aesimc_si128(rk[1]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[10]), rk[0]);
}

void aes128_enc_blocks(const Aes128CTX*    ctx,
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept
{
    __m128i        round_key[11], state;
    const __m128i* rk = (const __m128i*)(ctx->round_key);

    round_key[0]  = _mm_loadu_si128(rk + 0);
    round_key[1]  = _mm_loadu_si128(rk + 1);
    round_key[2]  = _mm_loadu_si128(rk + 2);
    round_key[3]  = _mm_loadu_si128(rk + 3);
    round_key[4]  = _mm_loadu_si128(rk + 4);
    round_key[5]  = _mm_loadu_si128(rk + 5);
    round_key[6]  = _mm_loadu_si128(rk + 6);
    round_key[7]  = _mm_loadu_si128(rk + 7);
    round_key[8]  = _mm_loadu_si128(rk + 8);
    round_key[9]  = _mm_loadu_si128(rk + 9);
    round_key[10] = _mm_loadu_si128(rk + 10);
    while (block_num)
    {
        state = _mm_loadu_si128((const __m128i*)plaintext);
        state = _mm_xor_si128(state, round_key[0]);
        state = _mm_aesenc_si128(state, round_key[1]);
        state = _mm_aesenc_si128(state, round_key[2]);
        state = _mm_aesenc_si128(state, round_key[3]);
        state = _mm_aesenc_si128(state, round_key[4]);
        state = _mm_aesenc_si128(state, round_key[5]);
        state = _mm_aesenc_si128(state, round_key[6]);
        state = _mm_aesenc_si128(state, round_key[7]);
        state = _mm_aesenc_si128(state, round_key[8]);
        state = _mm_aesenc_si128(state, round_key[9]);
        state = _mm_aesenclast_si128(state, round_key[10]);
        _mm_storeu_si128((__m128i*)ciphertext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes128_dec_blocks(const Aes128CTX*    ctx,
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept
{
    __m128i        round_key[11], state;
    const __m128i* rk = (const __m128i*)(ctx->round_key);

    round_key[0]  = _mm_loadu_si128(rk + 0);
    round_key[1]  = _mm_loadu_si128(rk + 1);
    round_key[2]  = _mm_loadu_si128(rk + 2);
    round_key[3]  = _mm_loadu_si128(rk + 3);
    round_key[4]  = _mm_loadu_si128(rk + 4);
    round_key[5]  = _mm_loadu_si128(rk + 5);
    round_key[6]  = _mm_loadu_si128(rk + 6);
    round_key[7]  = _mm_loadu_si128(rk + 7);
    round_key[8]  = _mm_loadu_si128(rk + 8);
    round_key[9]  = _mm_loadu_si128(rk + 9);
    round_key[10] = _mm_loadu_si128(rk + 10);
    while (block_num)
    {
        state = _mm_loadu_si128((const __m128i*)ciphertext);
        state = _mm_xor_si128(state, round_key[0]);
        state = _mm_aesdec_si128(state, round_key[1]);
        state = _mm_aesdec_si128(state, round_key[2]);
        state = _mm_aesdec_si128(state, round_key[3]);
        state = _mm_aesdec_si128(state, round_key[4]);
        state = _mm_aesdec_si128(state, round_key[5]);
        state = _mm_aesdec_si128(state, round_key[6]);
        state = _mm_aesdec_si128(state, round_key[7]);
        state = _mm_aesdec_si128(state, round_key[8]);
        state = _mm_aesdec_si128(state, round_key[9]);
        state = _mm_aesdeclast_si128(state, round_key[10]);
        _mm_storeu_si128((__m128i*)plaintext, state);

        plaintext += 16, ciphertext += 16, block_num -= 1;
    }
}

void aes128_enc_block(const Aes128CTX*   ctx,
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept
{
    aes128_enc_blocks(ctx, ciphertext, plaintext, 1);
}

void aes128_dec_block(const Aes128CTX*   ctx,
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept
{
    aes128_dec_blocks(ctx, plaintext, ciphertext, 1);
}

// ****************************************
// ************* AES 192 ******************
// ****************************************

void aes192_enc_key_init(Aes192CTX*         ctx,
                         const std::uint8_t user_key[24]) noexcept
{
    __m128i rk[13];
    AES_192_Key_Expansion(user_key, (unsigned char*)rk);
    _mm_storeu_si128((__m128i*)(ctx->round_key[0]), rk[0]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[1]), rk[1]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[2]), rk[2]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[3]), rk[3]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[4]), rk[4]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[5]), rk[5]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[6]), rk[6]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[7]), rk[7]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[8]), rk[8]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[9]), rk[9]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[10]), rk[10]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[11]), rk[11]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[12]), rk[12]);
}

void aes192_dec_key_init(Aes192CTX*         ctx,
                         const std::uint8_t user_key[24]) noexcept
{
    __m128i rk[13];
    AES_192_Key_Expansion(user_key, (unsigned char*)rk);
    _mm_storeu_si128((__m128i*)(ctx->round_key[0]), rk[12]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[1]), _mm_aesimc_si128(rk[11]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[2]), _mm_aesimc_si128(rk[10]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[3]), _mm_aesimc_si128(rk[9]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[4]), _mm_aesimc_si128(rk[8]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[5]), _mm_aesimc_si128(rk[7]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[6]), _mm_aesimc_si128(rk[6]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[7]), _mm_aesimc_si128(rk[5]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[8]), _mm_aesimc_si128(rk[4]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[9]), _mm_aesimc_si128(rk[3]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[10]), _mm_aesimc_si128(rk[2]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[11]), _mm_aesimc_si128(rk[1]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[12]), rk[0]);
}

void aes192_enc_blocks(const Aes192CTX*    ctx,
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept
{
    __m128i        round_key[13], state;
    const __m128i* rk = (const __m128i*)(ctx->round_key);

    round_key[0]  = _mm_loadu_si128(rk + 0);
    round_key[1]  = _mm_loadu_si128(rk + 1);
    round_key[2]  = _mm_loadu_si128(rk + 2);
    round_key[3]  = _mm_loadu_si128(rk + 3);
    round_key[4]  = _mm_loadu_si128(rk + 4);
    round_key[5]  = _mm_loadu_si128(rk + 5);
    round_key[6]  = _mm_loadu_si128(rk + 6);
    round_key[7]  = _mm_loadu_si128(rk + 7);
    round_key[8]  = _mm_loadu_si128(rk + 8);
    round_key[9]  = _mm_loadu_si128(rk + 9);
    round_key[10] = _mm_loadu_si128(rk + 10);
    round_key[11] = _mm_loadu_si128(rk + 11);
    round_key[12] = _mm_loadu_si128(rk + 12);
    while (block_num)
    {
        state = _mm_loadu_si128((const __m128i*)plaintext);
        state = _mm_xor_si128(state, round_key[0]);
        state = _mm_aesenc_si128(state, round_key[1]);
        state = _mm_aesenc_si128(state, round_key[2]);
        state = _mm_aesenc_si128(state, round_key[3]);
        state = _mm_aesenc_si128(state, round_key[4]);
        state = _mm_aesenc_si128(state, round_key[5]);
        state = _mm_aesenc_si128(state, round_key[6]);
        state = _mm_aesenc_si128(state, round_key[7]);
        state = _mm_aesenc_si128(state, round_key[8]);
        state = _mm_aesenc_si128(state, round_key[9]);
        state = _mm_aesenc_si128(state, round_key[10]);
        state = _mm_aesenc_si128(state, round_key[11]);
        state = _mm_aesenclast_si128(state, round_key[12]);
        _mm_storeu_si128((__m128i*)ciphertext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes192_dec_blocks(const Aes192CTX*    ctx,
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept
{
    __m128i        round_key[13], state;
    const __m128i* rk = (const __m128i*)(ctx->round_key);

    round_key[0]  = _mm_loadu_si128(rk + 0);
    round_key[1]  = _mm_loadu_si128(rk + 1);
    round_key[2]  = _mm_loadu_si128(rk + 2);
    round_key[3]  = _mm_loadu_si128(rk + 3);
    round_key[4]  = _mm_loadu_si128(rk + 4);
    round_key[5]  = _mm_loadu_si128(rk + 5);
    round_key[6]  = _mm_loadu_si128(rk + 6);
    round_key[7]  = _mm_loadu_si128(rk + 7);
    round_key[8]  = _mm_loadu_si128(rk + 8);
    round_key[9]  = _mm_loadu_si128(rk + 9);
    round_key[10] = _mm_loadu_si128(rk + 10);
    round_key[11] = _mm_loadu_si128(rk + 11);
    round_key[12] = _mm_loadu_si128(rk + 12);
    while (block_num)
    {
        state = _mm_loadu_si128((const __m128i*)ciphertext);
        state = _mm_xor_si128(state, round_key[0]);
        state = _mm_aesdec_si128(state, round_key[1]);
        state = _mm_aesdec_si128(state, round_key[2]);
        state = _mm_aesdec_si128(state, round_key[3]);
        state = _mm_aesdec_si128(state, round_key[4]);
        state = _mm_aesdec_si128(state, round_key[5]);
        state = _mm_aesdec_si128(state, round_key[6]);
        state = _mm_aesdec_si128(state, round_key[7]);
        state = _mm_aesdec_si128(state, round_key[8]);
        state = _mm_aesdec_si128(state, round_key[9]);
        state = _mm_aesdec_si128(state, round_key[10]);
        state = _mm_aesdec_si128(state, round_key[11]);
        state = _mm_aesdeclast_si128(state, round_key[12]);
        _mm_storeu_si128((__m128i*)plaintext, state);

        plaintext += 16, ciphertext += 16, block_num -= 1;
    }
}

void aes192_enc_block(const Aes192CTX*   ctx,
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept
{
    aes192_enc_blocks(ctx, ciphertext, plaintext, 1);
}

void aes192_dec_block(const Aes192CTX*   ctx,
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept
{
    aes192_dec_blocks(ctx, plaintext, ciphertext, 1);
}

// ****************************************
// ************* AES 256 ******************
// ****************************************

void aes256_enc_key_init(Aes256CTX*         ctx,
                         const std::uint8_t user_key[32]) noexcept
{
    __m128i rk[15];
    AES_256_Key_Expansion(user_key, (unsigned char*)rk);
    _mm_storeu_si128((__m128i*)(ctx->round_key[0]), rk[0]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[1]), rk[1]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[2]), rk[2]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[3]), rk[3]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[4]), rk[4]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[5]), rk[5]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[6]), rk[6]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[7]), rk[7]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[8]), rk[8]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[9]), rk[9]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[10]), rk[10]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[11]), rk[11]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[12]), rk[12]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[13]), rk[13]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[14]), rk[14]);
}

void aes256_dec_key_init(Aes256CTX*         ctx,
                         const std::uint8_t user_key[32]) noexcept
{
    __m128i rk[15];
    AES_256_Key_Expansion(user_key, (unsigned char*)rk);
    _mm_storeu_si128((__m128i*)(ctx->round_key[0]), rk[14]);
    _mm_storeu_si128((__m128i*)(ctx->round_key[1]), _mm_aesimc_si128(rk[13]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[2]), _mm_aesimc_si128(rk[12]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[3]), _mm_aesimc_si128(rk[11]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[4]), _mm_aesimc_si128(rk[10]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[5]), _mm_aesimc_si128(rk[9]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[6]), _mm_aesimc_si128(rk[8]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[7]), _mm_aesimc_si128(rk[7]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[8]), _mm_aesimc_si128(rk[6]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[9]), _mm_aesimc_si128(rk[5]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[10]), _mm_aesimc_si128(rk[4]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[11]), _mm_aesimc_si128(rk[3]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[12]), _mm_aesimc_si128(rk[2]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[13]), _mm_aesimc_si128(rk[1]));
    _mm_storeu_si128((__m128i*)(ctx->round_key[14]), rk[0]);
}

void aes256_enc_blocks(const Aes256CTX*    ctx,
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept
{
    __m128i        round_key[15], state;
    const __m128i* rk = (const __m128i*)(ctx->round_key);

    round_key[0]  = _mm_loadu_si128(rk + 0);
    round_key[1]  = _mm_loadu_si128(rk + 1);
    round_key[2]  = _mm_loadu_si128(rk + 2);
    round_key[3]  = _mm_loadu_si128(rk + 3);
    round_key[4]  = _mm_loadu_si128(rk + 4);
    round_key[5]  = _mm_loadu_si128(rk + 5);
    round_key[6]  = _mm_loadu_si128(rk + 6);
    round_key[7]  = _mm_loadu_si128(rk + 7);
    round_key[8]  = _mm_loadu_si128(rk + 8);
    round_key[9]  = _mm_loadu_si128(rk + 9);
    round_key[10] = _mm_loadu_si128(rk + 10);
    round_key[11] = _mm_loadu_si128(rk + 11);
    round_key[12] = _mm_loadu_si128(rk + 12);
    round_key[13] = _mm_loadu_si128(rk + 13);
    round_key[14] = _mm_loadu_si128(rk + 14);
    while (block_num)
    {
        state = _mm_loadu_si128((const __m128i*)plaintext);
        state = _mm_xor_si128(state, round_key[0]);
        state = _mm_aesenc_si128(state, round_key[1]);
        state = _mm_aesenc_si128(state, round_key[2]);
        state = _mm_aesenc_si128(state, round_key[3]);
        state = _mm_aesenc_si128(state, round_key[4]);
        state = _mm_aesenc_si128(state, round_key[5]);
        state = _mm_aesenc_si128(state, round_key[6]);
        state = _mm_aesenc_si128(state, round_key[7]);
        state = _mm_aesenc_si128(state, round_key[8]);
        state = _mm_aesenc_si128(state, round_key[9]);
        state = _mm_aesenc_si128(state, round_key[10]);
        state = _mm_aesenc_si128(state, round_key[11]);
        state = _mm_aesenc_si128(state, round_key[12]);
        state = _mm_aesenc_si128(state, round_key[13]);
        state = _mm_aesenclast_si128(state, round_key[14]);
        _mm_storeu_si128((__m128i*)ciphertext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes256_dec_blocks(const Aes256CTX*    ctx,
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept
{
    __m128i        round_key[15], state;
    const __m128i* rk = (const __m128i*)(ctx->round_key);

    round_key[0]  = _mm_loadu_si128(rk + 0);
    round_key[1]  = _mm_loadu_si128(rk + 1);
    round_key[2]  = _mm_loadu_si128(rk + 2);
    round_key[3]  = _mm_loadu_si128(rk + 3);
    round_key[4]  = _mm_loadu_si128(rk + 4);
    round_key[5]  = _mm_loadu_si128(rk + 5);
    round_key[6]  = _mm_loadu_si128(rk + 6);
    round_key[7]  = _mm_loadu_si128(rk + 7);
    round_key[8]  = _mm_loadu_si128(rk + 8);
    round_key[9]  = _mm_loadu_si128(rk + 9);
    round_key[10] = _mm_loadu_si128(rk + 10);
    round_key[11] = _mm_loadu_si128(rk + 11);
    round_key[12] = _mm_loadu_si128(rk + 12);
    round_key[13] = _mm_loadu_si128(rk + 13);
    round_key[14] = _mm_loadu_si128(rk + 14);
    while (block_num)
    {
        state = _mm_loadu_si128((const __m128i*)ciphertext);
        state = _mm_xor_si128(state, round_key[0]);
        state = _mm_aesdec_si128(state, round_key[1]);
        state = _mm_aesdec_si128(state, round_key[2]);
        state = _mm_aesdec_si128(state, round_key[3]);
        state = _mm_aesdec_si128(state, round_key[4]);
        state = _mm_aesdec_si128(state, round_key[5]);
        state = _mm_aesdec_si128(state, round_key[6]);
        state = _mm_aesdec_si128(state, round_key[7]);
        state = _mm_aesdec_si128(state, round_key[8]);
        state = _mm_aesdec_si128(state, round_key[9]);
        state = _mm_aesdec_si128(state, round_key[10]);
        state = _mm_aesdec_si128(state, round_key[11]);
        state = _mm_aesdec_si128(state, round_key[12]);
        state = _mm_aesdec_si128(state, round_key[13]);
        state = _mm_aesdeclast_si128(state, round_key[14]);
        _mm_storeu_si128((__m128i*)plaintext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes256_enc_block(const Aes256CTX*   ctx,
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept
{
    aes256_enc_blocks(ctx, ciphertext, plaintext, 1);
}

void aes256_dec_block(const Aes256CTX*   ctx,
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept
{
    aes256_dec_blocks(ctx, plaintext, ciphertext, 1);
}

}; // namespace aes::internal::aesni
#endif