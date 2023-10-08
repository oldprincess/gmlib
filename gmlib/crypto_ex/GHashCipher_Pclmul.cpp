/*
The MIT License (MIT)

Copyright (c) 2023 oldprincess, https://github.com/oldprincess/gmlib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "GHashCipher_Pclmul.h"
#include <stdexcept>
#include <immintrin.h>
#include <string.h>

using GHashPclmulCTX = gmlib::GHashCipher_Pclmul::GHashPclmulCTX;

#pragma region "GHASH PCLMUL CORE"

/**
 * @cite Intrinsics for Carry-less Multiplication Instruction and Advanced
 * Encryption Standard Instructions
 *
 * https://www.intel.com/content/dam/develop/external/us/en/documents/clmul-wp-rev-2-02-2014-04-20.pdf
 */
static inline __m128i reflect_xmm(__m128i X)
{
    __m128i tmp1, tmp2;
    __m128i AND_MASK =
        _mm_set_epi32(0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f);
    __m128i LOWER_MASK =
        _mm_set_epi32(0x0f070b03, 0x0d050901, 0x0e060a02, 0x0c040800);
    __m128i HIGHER_MASK =
        _mm_set_epi32(0xf070b030, 0xd0509010, 0xe060a020, 0xc0408000);
    tmp2 = _mm_srli_epi16(X, 4);
    tmp1 = _mm_and_si128(X, AND_MASK);
    tmp2 = _mm_and_si128(tmp2, AND_MASK);
    tmp1 = _mm_shuffle_epi8(HIGHER_MASK, tmp1);
    tmp2 = _mm_shuffle_epi8(LOWER_MASK, tmp2);
    tmp1 = _mm_xor_si128(tmp1, tmp2);
    return tmp1;
}

/**
 * @cite Intrinsics for Carry-less Multiplication Instruction and Advanced
 * Encryption Standard Instructions
 *
 * https://www.intel.com/content/dam/develop/external/us/en/documents/clmul-wp-rev-2-02-2014-04-20.pdf
 */
static inline void gfmul(__m128i a, __m128i b, __m128i* res)
{
    __m128i tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11, tmp12;
    __m128i XMMMASK = _mm_setr_epi32(0xffffffff, 0x0, 0x0, 0x0);

    tmp3  = _mm_clmulepi64_si128(a, b, 0x00);
    tmp6  = _mm_clmulepi64_si128(a, b, 0x11);
    tmp4  = _mm_shuffle_epi32(a, 78);
    tmp5  = _mm_shuffle_epi32(b, 78);
    tmp4  = _mm_xor_si128(tmp4, a);
    tmp5  = _mm_xor_si128(tmp5, b);
    tmp4  = _mm_clmulepi64_si128(tmp4, tmp5, 0x00);
    tmp4  = _mm_xor_si128(tmp4, tmp3);
    tmp4  = _mm_xor_si128(tmp4, tmp6);
    tmp5  = _mm_slli_si128(tmp4, 8);
    tmp4  = _mm_srli_si128(tmp4, 8);
    tmp3  = _mm_xor_si128(tmp3, tmp5);
    tmp6  = _mm_xor_si128(tmp6, tmp4);
    tmp7  = _mm_srli_epi32(tmp6, 31);
    tmp8  = _mm_srli_epi32(tmp6, 30);
    tmp9  = _mm_srli_epi32(tmp6, 25);
    tmp7  = _mm_xor_si128(tmp7, tmp8);
    tmp7  = _mm_xor_si128(tmp7, tmp9);
    tmp8  = _mm_shuffle_epi32(tmp7, 147);
    tmp7  = _mm_and_si128(XMMMASK, tmp8);
    tmp8  = _mm_andnot_si128(XMMMASK, tmp8);
    tmp3  = _mm_xor_si128(tmp3, tmp8);
    tmp6  = _mm_xor_si128(tmp6, tmp7);
    tmp10 = _mm_slli_epi32(tmp6, 1);
    tmp3  = _mm_xor_si128(tmp3, tmp10);
    tmp11 = _mm_slli_epi32(tmp6, 2);
    tmp3  = _mm_xor_si128(tmp3, tmp11);
    tmp12 = _mm_slli_epi32(tmp6, 7);
    tmp3  = _mm_xor_si128(tmp3, tmp12);
    *res  = _mm_xor_si128(tmp3, tmp6);
}

static void ghash_pclmul_update_block(GHashPclmulCTX* ctx, const uint8_t in[16])
{
    __m128i H     = _mm_loadu_si128((const __m128i*)(ctx->H));
    __m128i state = _mm_loadu_si128((const __m128i*)(ctx->state));
    __m128i X     = _mm_loadu_si128((const __m128i*)in);

    state = _mm_xor_si128(state, reflect_xmm(X));
    gfmul(state, H, &state);
    _mm_storeu_si128((__m128i*)(ctx->state), state);
}

static void ghash_pclmul_init(GHashPclmulCTX* ctx, const uint8_t H[16])
{
    __m128i _H = reflect_xmm(_mm_loadu_si128((const __m128i*)H));
    _mm_storeu_si128((__m128i*)(ctx->H), _H);
    _mm_storeu_si128((__m128i*)(ctx->state), _mm_setzero_si128());
    ctx->buf_size = 0;
}

static void ghash_pclmul_reset(GHashPclmulCTX* ctx)
{
    _mm_storeu_si128((__m128i*)(ctx->state), _mm_setzero_si128());
    ctx->buf_size = 0;
}

static void ghash_pclmul_update(GHashPclmulCTX* ctx,
                                const uint8_t*  in,
                                size_t          inl)
{
    if (ctx->buf_size == 0)
    {
        size_t block_num = inl / 16;
        while (block_num)
        {
            ghash_pclmul_update_block(ctx, in);
            in += 16, inl -= 16, block_num--;
        }
    }
    while (inl)
    {
        size_t size = 16 - ctx->buf_size;
        if (size > inl)
        {
            size = inl;
        }
        memcpy(ctx->buf + ctx->buf_size, in, size);
        in += size, inl -= size, ctx->buf_size += size;

        if (ctx->buf_size == 16)
        {
            ghash_pclmul_update_block(ctx, ctx->buf);
            ctx->buf_size = 0;
        }
    }
}

static int ghash_pclmul_final(const GHashPclmulCTX* ctx, uint8_t digest[16])
{
    if (ctx->buf_size) return -1;
    __m128i state = _mm_loadu_si128((const __m128i*)(ctx->state));
    _mm_storeu_si128((__m128i*)digest, reflect_xmm(state));
    return 0;
}

#pragma endregion

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ***************** GHASH Cipher ********************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

namespace gmlib {

GHashCipher_Pclmul::GHashCipher_Pclmul(const uint8_t H[16]) noexcept
{
    ghash_pclmul_init(&this->ctx, H);
}

void GHashCipher_Pclmul::set_key(const uint8_t H[16]) noexcept
{
    ghash_pclmul_init(&this->ctx, H);
}

void GHashCipher_Pclmul::reset() noexcept
{
    ghash_pclmul_reset(&this->ctx);
}

void GHashCipher_Pclmul::update(const uint8_t* in, size_t inl) noexcept
{
    ghash_pclmul_update(&this->ctx, in, inl);
}

void GHashCipher_Pclmul::final(uint8_t digest[16])
{
    int err = ghash_pclmul_final(&this->ctx, digest);
    if (err)
    {
        throw std::runtime_error("invalid data length");
    }
}

}; // namespace gmlib
