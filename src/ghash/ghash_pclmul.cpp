#if defined(CPU_FLAG_PCLMUL) && defined(CPU_FLAG_SSE2)
#include <gmlib/ghash/internal/ghash_pclmul.h>
#include <immintrin.h>

namespace ghash::internal::pclmul {

/**
 * Copyright (c) 2010 Intel Corporation. All rights reserved.
 *
 * derived from <Intrinsics for Carry-less Multiplication Instruction and
 * Advanced Encryption Standard Instructions>
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
 * Copyright (c) 2010 Intel Corporation. All rights reserved.
 *
 * derived from <Intrinsics for Carry-less Multiplication Instruction and
 * Advanced Encryption Standard Instructions>
 */
static inline void gfmul(__m128i a, __m128i b, __m128i* res) noexcept
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

void ghash_init(GHashCTX* ctx, const std::uint8_t H[16]) noexcept
{
    __m128i _H = reflect_xmm(_mm_loadu_si128((const __m128i*)H));
    _mm_storeu_si128((__m128i*)(ctx->H), _H);
    _mm_storeu_si128((__m128i*)(ctx->state), _mm_setzero_si128());
}

void ghash_reset(GHashCTX* ctx) noexcept
{
    _mm_storeu_si128((__m128i*)(ctx->state), _mm_setzero_si128());
}

void ghash_update_blocks(GHashCTX*           ctx,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept
{
    __m128i H     = _mm_loadu_si128((const __m128i*)(ctx->H));
    __m128i state = _mm_loadu_si128((const __m128i*)(ctx->state));
    __m128i X;
    while (block_num)
    {
        X     = _mm_loadu_si128((const __m128i*)in);
        state = _mm_xor_si128(state, reflect_xmm(X));
        gfmul(state, H, &state);

        in += 16, block_num--;
    }
    _mm_storeu_si128((__m128i*)(ctx->state), state);
}

int ghash_final_block(const GHashCTX*     ctx,
                      std::uint8_t        digest[16],
                      const std::uint8_t* in,
                      std::size_t         inl) noexcept
{
    if (inl != 0)
    {
        return -1;
    }
    __m128i state = _mm_loadu_si128((const __m128i*)(ctx->state));
    _mm_storeu_si128((__m128i*)digest, reflect_xmm(state));
    return 0;
}

}; // namespace ghash::internal::pclmul
#endif