#if defined(SUPPORT_UBLOCK_GONG25)

#include "ublock_gong25.h"

#include <immintrin.h>

namespace ublock {
namespace internal {
namespace gong25 {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************* UBLOCK CIPHER CORE *****************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * Starting from here, until the next similar comment declaration.
 *
 * the code is "derived from
 * https://sfjs.cacrnet.org.cn/site/term/list_76_1.html"
 *
 * WU W L, ZHANG L, ZHENG Y F, LI L C. The block cipher uBlock[J]. Journal of
 * Cryptologic Research, 2019, 6(6): 690-703.
 */

static std::uint8_t RC[24 * 16] = {
    0x9, 0x8, 0x8, 0xc, 0xc, 0x9, 0xd, 0xd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0x0, 0xe, 0x4, 0xa, 0x1, 0xb, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x2, 0x1, 0x3, 0x5, 0x7, 0x0, 0x6, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x8, 0x3, 0x9, 0x7, 0xd, 0x2, 0xc, 0x6, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xc, 0x7, 0xd, 0x3, 0x9, 0x6, 0x8, 0x2, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0xf, 0x5, 0xb, 0x1, 0xe, 0x0, 0xa, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0xe, 0x4, 0xa, 0x0, 0xf, 0x1, 0xb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xc, 0x6, 0x8, 0x2, 0xd, 0x3, 0x9,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x9, 0x2, 0xd, 0x6, 0x8, 0x7,
    0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xb, 0x3, 0xa, 0x7, 0xe, 0x2,
    0xf, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0x7, 0xb, 0x3, 0xf,
    0x6, 0xe, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xe, 0x9, 0xa,
    0xd, 0xf, 0xc, 0xb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0xc, 0xc,
    0x8, 0x8, 0xd, 0x9, 0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x8,
    0x6, 0xc, 0x2, 0x9, 0x3, 0xd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3,
    0x0, 0x2, 0x4, 0x6, 0x1, 0x7, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xa, 0x1, 0xb, 0x5, 0xf, 0x0, 0xe, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8, 0x2, 0x9, 0x6, 0xd, 0x3, 0xc, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xc, 0x5, 0xd, 0x1, 0x9, 0x4, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4, 0xa, 0x5, 0xe, 0x1, 0xb, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x5, 0x5, 0x4, 0x1, 0x0, 0x4, 0x1, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0xb, 0x7, 0xf, 0x3, 0xa, 0x2, 0xe, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x7, 0x0, 0x3, 0x4, 0x6, 0x5, 0x2, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xf, 0xf, 0xb, 0xb, 0xe, 0xa, 0xa,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xf, 0x0, 0xb, 0x4, 0xe, 0x5,
    0xa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};
static const std::uint8_t DATA_SK[16] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
    0x03, 0x01, 0x07, 0x05, 0x0b, 0x09, 0x0f, 0x0d,
};
static const std::uint8_t DATA_con[16] = {
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
};
static const std::uint8_t DATA_S[16] = {
    0x07, 0x04, 0x09, 0x0c, 0x0b, 0x0a, 0x0d, 0x08,
    0x0f, 0x0e, 0x01, 0x06, 0x00, 0x03, 0x02, 0x05,
};
static const std::uint8_t DATA_S_Inv[16] = {
    0x0c, 0x0a, 0x0e, 0x0d, 0x01, 0x0f, 0x0b, 0x00,
    0x07, 0x02, 0x05, 0x04, 0x03, 0x06, 0x09, 0x08,
};
static const std::uint8_t DATA_A1[16] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00,
    0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x08,
};
static const std::uint8_t DATA_A2[16] = {
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x01,
    0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x08, 0x09,
};
static const std::uint8_t DATA_A3[16] = {
    0x05, 0x06, 0x07, 0x00, 0x01, 0x02, 0x03, 0x04,
    0x0d, 0x0e, 0x0f, 0x08, 0x09, 0x0a, 0x0b, 0x0c,
};
static const std::uint8_t DATA_c1[16] = {
    0x00, 0x80, 0x01, 0x80, 0x02, 0x80, 0x03, 0x80,
    0x04, 0x80, 0x05, 0x80, 0x06, 0x80, 0x07, 0x80,
};
static const std::uint8_t DATA_c2[16] = {
    0x80, 0x00, 0x80, 0x01, 0x80, 0x02, 0x80, 0x03,
    0x80, 0x04, 0x80, 0x05, 0x80, 0x06, 0x80, 0x07,
};
static const std::uint8_t DATA_c3[16] = {
    0x08, 0x80, 0x09, 0x80, 0x0a, 0x80, 0x0b, 0x80,
    0x0c, 0x80, 0x0d, 0x80, 0x0e, 0x80, 0x0f, 0x80,
};
static const std::uint8_t DATA_c4[16] = {
    0x80, 0x08, 0x80, 0x09, 0x80, 0x0a, 0x80, 0x0b,
    0x80, 0x0c, 0x80, 0x0d, 0x80, 0x0e, 0x80, 0x0f,
};

// ****************************************
// ********** uBlock 128/128 **************
// ****************************************

static void uBlock_128128_KeySchedule(std::uint8_t       sub_key[17][16],
                                      const std::uint8_t user_key[16]) noexcept
{
    static const std::uint8_t DATA_c5[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c6[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    };
    static const std::uint8_t DATA_c7[16] = {
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    };
    static const std::uint8_t DATA_c8[16] = {
        0x06, 0x00, 0x08, 0x0d, 0x01, 0x0f, 0x05, 0x0a,
        0x04, 0x09, 0x0c, 0x02, 0x0b, 0x03, 0x07, 0x0e,
    };

    __m128i con = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i S   = _mm_loadu_si128((const __m128i *)DATA_S);
    __m128i SK  = _mm_loadu_si128((const __m128i *)DATA_SK);
    __m128i c1  = _mm_loadu_si128((const __m128i *)DATA_c1);
    __m128i c2  = _mm_loadu_si128((const __m128i *)DATA_c2);
    __m128i c3  = _mm_loadu_si128((const __m128i *)DATA_c3);
    __m128i c4  = _mm_loadu_si128((const __m128i *)DATA_c4);
    __m128i c5  = _mm_loadu_si128((const __m128i *)DATA_c5);
    __m128i c6  = _mm_loadu_si128((const __m128i *)DATA_c6);
    __m128i c7  = _mm_loadu_si128((const __m128i *)DATA_c7);
    __m128i c8  = _mm_loadu_si128((const __m128i *)DATA_c8);
    __m128i state1, state2, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)user_key);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    t1 = _mm_xor_si128(_mm_slli_epi32(state2, 4), state1);
    _mm_storeu_si128((__m128i *)sub_key[0], t1);

    for (int i = 1; i <= 16; i++)
    {
        state1 = _mm_shuffle_epi8(state1, c8);

        k  = _mm_loadu_si128((const __m128i *)(RC + 16 * (i - 1)));
        k  = _mm_xor_si128(k, state1);
        t1 = _mm_shuffle_epi8(S, k);
        t2 = _mm_shuffle_epi8(SK, k);
        t3 = _mm_shuffle_epi8(t1, c5);
        t4 = _mm_shuffle_epi8(t2, c6);
        k  = _mm_xor_si128(t3, t4);

        k      = _mm_xor_si128(k, state2);
        state2 = _mm_shuffle_epi8(state1, c7);
        state1 = k;

        t1 = _mm_xor_si128(_mm_slli_epi32(state2, 4), state1);
        _mm_storeu_si128((__m128i *)sub_key[i], t1);
    }
}

static void uBlock_128128_Encrypt(const std::uint8_t sub_key[17][16],
                                  std::uint8_t       ciphertext[16],
                                  const std::uint8_t plaintext[16]) noexcept
{
    static const std::uint8_t DATA_c5[16] = {
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c6[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
    };
    static const std::uint8_t DATA_c7[16] = {
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c8[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
    };
    static const std::uint8_t DATA_L1[16] = {
        0x02, 0x03, 0x06, 0x07, 0x08, 0x09, 0x0c, 0x0d,
        0x00, 0x01, 0x04, 0x05, 0x0e, 0x0f, 0x0a, 0x0b,
    };
    static const std::uint8_t DATA_L2[16] = {
        0x04, 0x05, 0x0e, 0x0f, 0x0a, 0x0b, 0x00, 0x01,
        0x02, 0x03, 0x0c, 0x0d, 0x08, 0x09, 0x06, 0x07,
    };

    __m128i S   = _mm_loadu_si128((const __m128i *)DATA_S);
    __m128i con = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i A1  = _mm_loadu_si128((const __m128i *)DATA_A1);
    __m128i A2  = _mm_loadu_si128((const __m128i *)DATA_A2);
    __m128i A3  = _mm_loadu_si128((const __m128i *)DATA_A3);
    __m128i L1  = _mm_loadu_si128((const __m128i *)DATA_L1);
    __m128i L2  = _mm_loadu_si128((const __m128i *)DATA_L2);
    __m128i c1  = _mm_loadu_si128((const __m128i *)DATA_c1);
    __m128i c2  = _mm_loadu_si128((const __m128i *)DATA_c2);
    __m128i c3  = _mm_loadu_si128((const __m128i *)DATA_c3);
    __m128i c4  = _mm_loadu_si128((const __m128i *)DATA_c4);
    __m128i c5  = _mm_loadu_si128((const __m128i *)DATA_c5);
    __m128i c6  = _mm_loadu_si128((const __m128i *)DATA_c6);
    __m128i c7  = _mm_loadu_si128((const __m128i *)DATA_c7);
    __m128i c8  = _mm_loadu_si128((const __m128i *)DATA_c8);
    __m128i state1, state2, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)plaintext);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    for (int i = 0; i < 16; i++)
    {
        k      = _mm_loadu_si128((const __m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

        state1 = _mm_shuffle_epi8(S, state1);
        state2 = _mm_shuffle_epi8(S, state2);

        state2 = _mm_xor_si128(state2, state1);
        k      = _mm_shuffle_epi8(state2, A1);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state1, A2);
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_shuffle_epi8(state2, A2);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state1, A3);
        state2 = _mm_xor_si128(state2, k);
        state1 = _mm_xor_si128(state1, state2);

        state1 = _mm_shuffle_epi8(state1, L1);
        state2 = _mm_shuffle_epi8(state2, L2);
    }

    k      = _mm_loadu_si128((const __m128i *)sub_key[16]);
    state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

    t1 = _mm_shuffle_epi8(state1, c5);
    t2 = _mm_shuffle_epi8(state2, c6);
    t3 = _mm_shuffle_epi8(state1, c7);
    t4 = _mm_shuffle_epi8(state2, c8);

    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state1 = _mm_slli_epi16(state1, 4);
    state1 = _mm_xor_si128(state1, state2);

    _mm_storeu_si128((__m128i *)ciphertext, state1);
}

static void uBlock_128128_Decrypt(const std::uint8_t sub_key[17][16],
                                  std::uint8_t       plaintext[16],
                                  const std::uint8_t ciphertext[16]) noexcept
{
    static const std::uint8_t DATA_c5[16] = {
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c6[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
    };
    static const std::uint8_t DATA_c7[16] = {
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c8[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
    };
    static const std::uint8_t DATA_L1[16] = {
        0x08, 0x09, 0x00, 0x01, 0x0a, 0x0b, 0x02, 0x03,
        0x04, 0x05, 0x0e, 0x0f, 0x06, 0x07, 0x0c, 0x0d,
    };
    static const std::uint8_t DATA_L2[16] = {
        0x06, 0x07, 0x08, 0x09, 0x00, 0x01, 0x0e, 0x0f,
        0x0c, 0x0d, 0x04, 0x05, 0x0a, 0x0b, 0x02, 0x03,
    };

    __m128i S_Inv = _mm_loadu_si128((const __m128i *)DATA_S_Inv);
    __m128i con   = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i A1    = _mm_loadu_si128((const __m128i *)DATA_A1);
    __m128i A2    = _mm_loadu_si128((const __m128i *)DATA_A2);
    __m128i A3    = _mm_loadu_si128((const __m128i *)DATA_A3);
    __m128i L1    = _mm_loadu_si128((const __m128i *)DATA_L1);
    __m128i L2    = _mm_loadu_si128((const __m128i *)DATA_L2);
    __m128i c1    = _mm_loadu_si128((const __m128i *)DATA_c1);
    __m128i c2    = _mm_loadu_si128((const __m128i *)DATA_c2);
    __m128i c3    = _mm_loadu_si128((const __m128i *)DATA_c3);
    __m128i c4    = _mm_loadu_si128((const __m128i *)DATA_c4);
    __m128i c5    = _mm_loadu_si128((const __m128i *)DATA_c5);
    __m128i c6    = _mm_loadu_si128((const __m128i *)DATA_c6);
    __m128i c7    = _mm_loadu_si128((const __m128i *)DATA_c7);
    __m128i c8    = _mm_loadu_si128((const __m128i *)DATA_c8);
    __m128i state1, state2, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)ciphertext);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    for (int i = 16; i > 0; i--)
    {
        k      = _mm_loadu_si128((const __m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

        state1 = _mm_shuffle_epi8(state1, L1);
        state2 = _mm_shuffle_epi8(state2, L2);

        state1 = _mm_xor_si128(state1, state2);
        k      = _mm_shuffle_epi8(state1, A3);
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_shuffle_epi8(state2, A2);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state1, A2);
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_shuffle_epi8(state2, A1);
        state1 = _mm_xor_si128(state1, k);
        state2 = _mm_xor_si128(state2, state1);

        state1 = _mm_shuffle_epi8(S_Inv, state1);
        state2 = _mm_shuffle_epi8(S_Inv, state2);
    }

    k      = _mm_loadu_si128((const __m128i *)sub_key[0]);
    state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

    t1 = _mm_shuffle_epi8(state1, c5);
    t2 = _mm_shuffle_epi8(state2, c6);
    t3 = _mm_shuffle_epi8(state1, c7);
    t4 = _mm_shuffle_epi8(state2, c8);

    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state1 = _mm_slli_epi16(state1, 4);
    state1 = _mm_xor_si128(state1, state2);

    _mm_storeu_si128((__m128i *)plaintext, state1);
}

// ****************************************
// ********** uBlock 128/256 **************
// ****************************************

static void uBlock_128256_KeySchedule(std::uint8_t       sub_key[25][16],
                                      const std::uint8_t user_key[32]) noexcept
{
    __m128i con = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i S   = _mm_loadu_si128((const __m128i *)DATA_S);
    __m128i SK  = _mm_loadu_si128((const __m128i *)DATA_SK);

    __m128i c1 = _mm_loadu_si128((const __m128i *)DATA_c1);
    __m128i c2 = _mm_loadu_si128((const __m128i *)DATA_c2);
    __m128i c3 = _mm_loadu_si128((const __m128i *)DATA_c3);
    __m128i c4 = _mm_loadu_si128((const __m128i *)DATA_c4);

    __m128i c5 =
        _mm_setr_epi8(10, 5, 15, 0, 2, 7, 8, 13, 14, 6, 4, 12, 1, 3, 11, 9);
    __m128i c6 =
        _mm_setr_epi8(8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7);

    __m128i state1, state2, state3, state4, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)user_key);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state4 = _mm_loadu_si128((const __m128i *)(user_key + 16));
    state3 = _mm_srli_epi16(state4, 4);
    state3 = _mm_and_si128(state3, con);
    state4 = _mm_and_si128(state4, con);
    t1     = _mm_shuffle_epi8(state3, c1);
    t2     = _mm_shuffle_epi8(state4, c2);
    t3     = _mm_shuffle_epi8(state3, c3);
    t4     = _mm_shuffle_epi8(state4, c4);
    state3 = _mm_xor_si128(t1, t2);
    state4 = _mm_xor_si128(t3, t4);

    t1 = _mm_xor_si128(_mm_slli_epi32(state2, 4), state1);
    _mm_storeu_si128((__m128i *)sub_key[0], t1);

    for (int i = 1; i <= 24; i++)
    {
        state1 = _mm_shuffle_epi8(state1, c5);
        state2 = _mm_shuffle_epi8(state2, c6);

        k      = _mm_loadu_si128((const __m128i *)(RC + 16 * (i - 1)));
        k      = _mm_xor_si128(k, state1);
        k      = _mm_shuffle_epi8(S, k);
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_shuffle_epi8(SK, state2);
        k      = _mm_xor_si128(k, state4);

        state4 = state1;
        state1 = state3;
        state3 = state2;
        state2 = k;

        t1 = _mm_xor_si128(_mm_slli_epi32(state2, 4), state1);
        _mm_storeu_si128((__m128i *)sub_key[i], t1);
    }

    return;
}

static void uBlock_128256_Encrypt(const std::uint8_t sub_key[25][16],
                                  std::uint8_t       ciphertext[16],
                                  const std::uint8_t plaintext[16]) noexcept
{
    static const std::uint8_t DATA_c5[16] = {
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c6[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
    };
    static const std::uint8_t DATA_L1[16] = {
        0x02, 0x03, 0x06, 0x07, 0x08, 0x09, 0x0c, 0x0d,
        0x00, 0x01, 0x04, 0x05, 0x0e, 0x0f, 0x0a, 0x0b,
    };
    static const std::uint8_t DATA_L2[16] = {
        0x04, 0x05, 0x0e, 0x0f, 0x0a, 0x0b, 0x00, 0x01,
        0x02, 0x03, 0x0c, 0x0d, 0x08, 0x09, 0x06, 0x07,
    };
    static const std::uint8_t DATA_c7[16] = {
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c8[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
    };
    __m128i S   = _mm_loadu_si128((const __m128i *)DATA_S);
    __m128i con = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i A1  = _mm_loadu_si128((const __m128i *)DATA_A1);
    __m128i A2  = _mm_loadu_si128((const __m128i *)DATA_A2);
    __m128i A3  = _mm_loadu_si128((const __m128i *)DATA_A3);
    __m128i L1  = _mm_loadu_si128((const __m128i *)DATA_L1);
    __m128i L2  = _mm_loadu_si128((const __m128i *)DATA_L2);

    __m128i c1 = _mm_loadu_si128((const __m128i *)DATA_c1);
    __m128i c2 = _mm_loadu_si128((const __m128i *)DATA_c2);
    __m128i c3 = _mm_loadu_si128((const __m128i *)DATA_c3);
    __m128i c4 = _mm_loadu_si128((const __m128i *)DATA_c4);
    __m128i c5 = _mm_loadu_si128((const __m128i *)DATA_c5);
    __m128i c6 = _mm_loadu_si128((const __m128i *)DATA_c6);
    __m128i c7 = _mm_loadu_si128((const __m128i *)DATA_c7);
    __m128i c8 = _mm_loadu_si128((const __m128i *)DATA_c8);

    __m128i state1, state2, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)plaintext);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    for (int i = 0; i < 24; i++)
    {
        k      = _mm_loadu_si128((const __m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

        state1 = _mm_shuffle_epi8(S, state1);
        state2 = _mm_shuffle_epi8(S, state2);

        state2 = _mm_xor_si128(state2, state1);
        k      = _mm_shuffle_epi8(state2, A1);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state1, A2);
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_shuffle_epi8(state2, A2);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state1, A3);
        state2 = _mm_xor_si128(state2, k);
        state1 = _mm_xor_si128(state1, state2);

        state1 = _mm_shuffle_epi8(state1, L1);
        state2 = _mm_shuffle_epi8(state2, L2);
    }

    k      = _mm_loadu_si128((const __m128i *)sub_key[24]);
    state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

    t1 = _mm_shuffle_epi8(state1, c5);
    t2 = _mm_shuffle_epi8(state2, c6);
    t3 = _mm_shuffle_epi8(state1, c7);
    t4 = _mm_shuffle_epi8(state2, c8);

    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state1 = _mm_slli_epi16(state1, 4);
    state1 = _mm_xor_si128(state1, state2);

    _mm_storeu_si128((__m128i *)ciphertext, state1);

    return;
}

static void uBlock_128256_Decrypt(const std::uint8_t sub_key[25][16],
                                  std::uint8_t       plaintext[16],
                                  const std::uint8_t ciphertext[16]) noexcept
{
    static const std::uint8_t DATA_c5[16] = {
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c6[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
    };
    static const std::uint8_t DATA_c7[16] = {
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    };
    static const std::uint8_t DATA_c8[16] = {
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f,
    };
    static const std::uint8_t DATA_L1[16] = {
        0x08, 0x09, 0x00, 0x01, 0x0a, 0x0b, 0x02, 0x03,
        0x04, 0x05, 0x0e, 0x0f, 0x06, 0x07, 0x0c, 0x0d,
    };
    static const std::uint8_t DATA_L2[16] = {
        0x06, 0x07, 0x08, 0x09, 0x00, 0x01, 0x0e, 0x0f,
        0x0c, 0x0d, 0x04, 0x05, 0x0a, 0x0b, 0x02, 0x03,
    };

    __m128i S_Inv = _mm_loadu_si128((const __m128i *)DATA_S_Inv);
    __m128i con   = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i A1    = _mm_loadu_si128((const __m128i *)DATA_A1);
    __m128i A2    = _mm_loadu_si128((const __m128i *)DATA_A2);
    __m128i A3    = _mm_loadu_si128((const __m128i *)DATA_A3);
    __m128i L1    = _mm_loadu_si128((const __m128i *)DATA_L1);
    __m128i L2    = _mm_loadu_si128((const __m128i *)DATA_L2);
    __m128i c1    = _mm_loadu_si128((const __m128i *)DATA_c1);
    __m128i c2    = _mm_loadu_si128((const __m128i *)DATA_c2);
    __m128i c3    = _mm_loadu_si128((const __m128i *)DATA_c3);
    __m128i c4    = _mm_loadu_si128((const __m128i *)DATA_c4);
    __m128i c5    = _mm_loadu_si128((const __m128i *)DATA_c5);
    __m128i c6    = _mm_loadu_si128((const __m128i *)DATA_c6);
    __m128i c7    = _mm_loadu_si128((const __m128i *)DATA_c7);
    __m128i c8    = _mm_loadu_si128((const __m128i *)DATA_c8);
    __m128i state1, state2, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)ciphertext);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    for (int i = 24; i > 0; i--)
    {
        k      = _mm_loadu_si128((const __m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

        state1 = _mm_shuffle_epi8(state1, L1);
        state2 = _mm_shuffle_epi8(state2, L2);

        state1 = _mm_xor_si128(state1, state2);
        k      = _mm_shuffle_epi8(state1, A3);
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_shuffle_epi8(state2, A2);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state1, A2);
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_shuffle_epi8(state2, A1);
        state1 = _mm_xor_si128(state1, k);
        state2 = _mm_xor_si128(state2, state1);

        state1 = _mm_shuffle_epi8(S_Inv, state1);
        state2 = _mm_shuffle_epi8(S_Inv, state2);
    }

    k      = _mm_loadu_si128((const __m128i *)sub_key[0]);
    state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));

    t1 = _mm_shuffle_epi8(state1, c5);
    t2 = _mm_shuffle_epi8(state2, c6);
    t3 = _mm_shuffle_epi8(state1, c7);
    t4 = _mm_shuffle_epi8(state2, c8);

    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state1 = _mm_slli_epi16(state1, 4);
    state1 = _mm_xor_si128(state1, state2);

    _mm_storeu_si128((__m128i *)plaintext, state1);
}

// ****************************************
// ********** uBlock 256/256 **************
// ****************************************

static void uBlock_256256_KeySchedule(std::uint8_t       sub_key[25][32],
                                      const std::uint8_t user_key[32]) noexcept
{
    __m128i con = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i S   = _mm_loadu_si128((const __m128i *)DATA_S);
    __m128i SK  = _mm_loadu_si128((const __m128i *)DATA_SK);
    __m128i c1  = _mm_loadu_si128((const __m128i *)DATA_c1);
    __m128i c2  = _mm_loadu_si128((const __m128i *)DATA_c2);
    __m128i c3  = _mm_loadu_si128((const __m128i *)DATA_c3);
    __m128i c4  = _mm_loadu_si128((const __m128i *)DATA_c4);

    __m128i c5 =
        _mm_setr_epi8(10, 5, 15, 0, 2, 7, 8, 13, 1, 14, 4, 12, 9, 11, 3, 6);
    __m128i c6 =
        _mm_setr_epi8(8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7);

    __m128i state1, state2, state3, state4, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)user_key);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state4 = _mm_loadu_si128((const __m128i *)(user_key + 16));
    state3 = _mm_srli_epi16(state4, 4);
    state3 = _mm_and_si128(state3, con);
    state4 = _mm_and_si128(state4, con);
    t1     = _mm_shuffle_epi8(state3, c1);
    t2     = _mm_shuffle_epi8(state4, c2);
    t3     = _mm_shuffle_epi8(state3, c3);
    t4     = _mm_shuffle_epi8(state4, c4);
    state3 = _mm_xor_si128(t1, t2);
    state4 = _mm_xor_si128(t3, t4);

    t1 = _mm_xor_si128(_mm_slli_epi32(state2, 4), state1);
    t2 = _mm_xor_si128(_mm_slli_epi32(state4, 4), state3);
    _mm_storeu_si128((__m128i *)sub_key[0], t1);
    _mm_storeu_si128((__m128i *)(sub_key[0] + 16), t2);

    for (int i = 1; i <= 24; i++)
    {
        state1 = _mm_shuffle_epi8(state1, c5);
        state2 = _mm_shuffle_epi8(state2, c6);

        k      = _mm_loadu_si128((const __m128i *)(RC + 16 * (i - 1)));
        k      = _mm_xor_si128(k, state1);
        k      = _mm_shuffle_epi8(S, k);
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_shuffle_epi8(SK, state2);
        k      = _mm_xor_si128(k, state4);

        state4 = state1;
        state1 = state3;
        state3 = state2;
        state2 = k;

        t1 = _mm_xor_si128(_mm_slli_epi32(state2, 4), state1);
        t2 = _mm_xor_si128(_mm_slli_epi32(state4, 4), state3);
        _mm_storeu_si128((__m128i *)sub_key[i], t1);
        _mm_storeu_si128((__m128i *)(sub_key[i] + 16), t2);
    }

    return;
}

static void uBlock_256256_Encrypt(const std::uint8_t  sub_key[25][32],
                                  std::uint8_t       *ciphertext,
                                  const std::uint8_t *plaintext) noexcept
{
    __m128i S   = _mm_loadu_si128((const __m128i *)DATA_S);
    __m128i con = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i A1  = _mm_loadu_si128((const __m128i *)DATA_A1);
    __m128i A2  = _mm_loadu_si128((const __m128i *)DATA_A2);
    __m128i A3  = _mm_loadu_si128((const __m128i *)DATA_A3);

    int     i;
    __m128i L1 = _mm_setr_epi8(4, 5, 14, 15, -1, -1, -1, -1, 6, 7, 12, 13, -1,
                               -1, -1, -1);
    __m128i L2 =
        _mm_setr_epi8(-1, -1, -1, -1, 0, 1, 10, 11, -1, -1, -1, -1, 2, 3, 8, 9);
    __m128i L3 =
        _mm_setr_epi8(2, 3, 8, 9, -1, -1, -1, -1, -1, -1, -1, -1, 10, 11, 0, 1);
    __m128i L4 = _mm_setr_epi8(-1, -1, -1, -1, 14, 15, 4, 5, 12, 13, 6, 7, -1,
                               -1, -1, -1);
    __m128i L5 =
        _mm_setr_epi8(12, 13, -1, -1, 2, 3, -1, -1, -1, -1, 8, 9, 4, 5, -1, -1);
    __m128i L6 =
        _mm_setr_epi8(-1, -1, 6, 7, -1, -1, 8, 9, 2, 3, -1, -1, -1, -1, 14, 15);
    __m128i L7 = _mm_setr_epi8(14, 15, 0, 1, -1, -1, -1, -1, -1, -1, 6, 7, -1,
                               -1, 10, 11);
    __m128i L8 = _mm_setr_epi8(-1, -1, -1, -1, 10, 11, 4, 5, 12, 13, -1, -1, 0,
                               1, -1, -1);

    __m128i c1 =
        _mm_setr_epi8(0, -1, 1, -1, 2, -1, 3, -1, 4, -1, 5, -1, 6, -1, 7, -1);
    __m128i c2 =
        _mm_setr_epi8(-1, 0, -1, 1, -1, 2, -1, 3, -1, 4, -1, 5, -1, 6, -1, 7);
    __m128i c3 = _mm_setr_epi8(8, -1, 9, -1, 10, -1, 11, -1, 12, -1, 13, -1, 14,
                               -1, 15, -1);
    __m128i c4 = _mm_setr_epi8(-1, 8, -1, 9, -1, 10, -1, 11, -1, 12, -1, 13, -1,
                               14, -1, 15);

    __m128i c5 = _mm_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -1, -1, -1, -1, -1,
                               -1, -1, -1);
    __m128i c6 = _mm_setr_epi8(-1, -1, -1, -1, -1, -1, -1, -1, 0, 2, 4, 6, 8,
                               10, 12, 14);
    __m128i c7 = _mm_setr_epi8(1, 3, 5, 7, 9, 11, 13, 15, -1, -1, -1, -1, -1,
                               -1, -1, -1);
    __m128i c8 = _mm_setr_epi8(-1, -1, -1, -1, -1, -1, -1, -1, 1, 3, 5, 7, 9,
                               11, 13, 15);

    __m128i state1, state2, state3, state4, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)plaintext);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state4 = _mm_loadu_si128((const __m128i *)(plaintext + 16));
    state3 = _mm_srli_epi16(state4, 4);
    state3 = _mm_and_si128(state3, con);
    state4 = _mm_and_si128(state4, con);
    t1     = _mm_shuffle_epi8(state3, c1);
    t2     = _mm_shuffle_epi8(state4, c2);
    t3     = _mm_shuffle_epi8(state3, c3);
    t4     = _mm_shuffle_epi8(state4, c4);
    state3 = _mm_xor_si128(t1, t2);
    state4 = _mm_xor_si128(t3, t4);

    for (i = 0; i < 24; i++)
    {
        k      = _mm_loadu_si128((const __m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 16));
        state3 = _mm_xor_si128(state3, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state4 = _mm_xor_si128(state4, _mm_and_si128(k, con));

        state1 = _mm_shuffle_epi8(S, state1);
        state2 = _mm_shuffle_epi8(S, state2);
        state3 = _mm_shuffle_epi8(S, state3);
        state4 = _mm_shuffle_epi8(S, state4);

        state3 = _mm_xor_si128(state3, state1);
        state4 = _mm_xor_si128(state4, state2);

        k      = _mm_shuffle_epi8(state3, A1);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state4, A1);
        state2 = _mm_xor_si128(state2, k);

        k      = _mm_shuffle_epi8(state1, A2);
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_shuffle_epi8(state2, A2);
        state4 = _mm_xor_si128(state4, k);

        k      = _mm_shuffle_epi8(state3, A2);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state4, A2);
        state2 = _mm_xor_si128(state2, k);

        k      = _mm_shuffle_epi8(state1, A3);
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_shuffle_epi8(state2, A3);
        state4 = _mm_xor_si128(state4, k);

        state1 = _mm_xor_si128(state1, state3);
        state2 = _mm_xor_si128(state2, state4);

        t1     = _mm_shuffle_epi8(state1, L1);
        t2     = _mm_shuffle_epi8(state2, L2);
        t3     = _mm_shuffle_epi8(state1, L3);
        t4     = _mm_shuffle_epi8(state2, L4);
        state1 = _mm_xor_si128(t1, t2);
        state2 = _mm_xor_si128(t3, t4);

        t1     = _mm_shuffle_epi8(state3, L5);
        t2     = _mm_shuffle_epi8(state4, L6);
        t3     = _mm_shuffle_epi8(state3, L7);
        t4     = _mm_shuffle_epi8(state4, L8);
        state3 = _mm_xor_si128(t1, t2);
        state4 = _mm_xor_si128(t3, t4);
    }

    k      = _mm_loadu_si128((const __m128i *)sub_key[24]);
    state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));
    k      = _mm_loadu_si128((const __m128i *)(sub_key[24] + 16));
    state3 = _mm_xor_si128(state3, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state4 = _mm_xor_si128(state4, _mm_and_si128(k, con));

    t1     = _mm_shuffle_epi8(state1, c5);
    t2     = _mm_shuffle_epi8(state2, c6);
    t3     = _mm_shuffle_epi8(state1, c7);
    t4     = _mm_shuffle_epi8(state2, c8);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);
    state1 = _mm_slli_epi16(state1, 4);
    state1 = _mm_xor_si128(state1, state2);

    t1     = _mm_shuffle_epi8(state3, c5);
    t2     = _mm_shuffle_epi8(state4, c6);
    t3     = _mm_shuffle_epi8(state3, c7);
    t4     = _mm_shuffle_epi8(state4, c8);
    state3 = _mm_xor_si128(t1, t2);
    state4 = _mm_xor_si128(t3, t4);
    state3 = _mm_slli_epi16(state3, 4);
    state3 = _mm_xor_si128(state3, state4);

    _mm_storeu_si128((__m128i *)ciphertext, state1);
    _mm_storeu_si128((__m128i *)(ciphertext + 16), state3);

    return;
}

static void uBlock_256256_Decrypt(const std::uint8_t  sub_key[25][32],
                                  std::uint8_t       *plaintext,
                                  const std::uint8_t *ciphertext) noexcept
{
    __m128i S_Inv = _mm_loadu_si128((const __m128i *)DATA_S_Inv);
    __m128i con   = _mm_loadu_si128((const __m128i *)DATA_con);
    __m128i A1    = _mm_loadu_si128((const __m128i *)DATA_A1);
    __m128i A2    = _mm_loadu_si128((const __m128i *)DATA_A2);
    __m128i A3    = _mm_loadu_si128((const __m128i *)DATA_A3);

    int     i;
    __m128i L1 =
        _mm_setr_epi8(-1, -1, -1, -1, 0, 1, 8, 9, -1, -1, -1, -1, 10, 11, 2, 3);
    __m128i L2 = _mm_setr_epi8(14, 15, 0, 1, -1, -1, -1, -1, 2, 3, 12, 13, -1,
                               -1, -1, -1);
    __m128i L3 = _mm_setr_epi8(4, 5, 12, 13, -1, -1, -1, -1, 14, 15, 6, 7, -1,
                               -1, -1, -1);
    __m128i L4 =
        _mm_setr_epi8(-1, -1, -1, -1, 6, 7, 10, 11, -1, -1, -1, -1, 8, 9, 4, 5);
    __m128i L5 = _mm_setr_epi8(-1, -1, 4, 5, 12, 13, -1, -1, 10, 11, -1, -1, 0,
                               1, -1, -1);
    __m128i L6 = _mm_setr_epi8(2, 3, -1, -1, -1, -1, 10, 11, -1, -1, 14, 15, -1,
                               -1, 0, 1);
    __m128i L7 =
        _mm_setr_epi8(-1, -1, 8, 9, -1, -1, 2, 3, 6, 7, -1, -1, -1, -1, 14, 15);
    __m128i L8 =
        _mm_setr_epi8(12, 13, -1, -1, 6, 7, -1, -1, -1, -1, 4, 5, 8, 9, -1, -1);

    __m128i c1 =
        _mm_setr_epi8(0, -1, 1, -1, 2, -1, 3, -1, 4, -1, 5, -1, 6, -1, 7, -1);
    __m128i c2 =
        _mm_setr_epi8(-1, 0, -1, 1, -1, 2, -1, 3, -1, 4, -1, 5, -1, 6, -1, 7);
    __m128i c3 = _mm_setr_epi8(8, -1, 9, -1, 10, -1, 11, -1, 12, -1, 13, -1, 14,
                               -1, 15, -1);
    __m128i c4 = _mm_setr_epi8(-1, 8, -1, 9, -1, 10, -1, 11, -1, 12, -1, 13, -1,
                               14, -1, 15);

    __m128i c5 = _mm_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -1, -1, -1, -1, -1,
                               -1, -1, -1);
    __m128i c6 = _mm_setr_epi8(-1, -1, -1, -1, -1, -1, -1, -1, 0, 2, 4, 6, 8,
                               10, 12, 14);
    __m128i c7 = _mm_setr_epi8(1, 3, 5, 7, 9, 11, 13, 15, -1, -1, -1, -1, -1,
                               -1, -1, -1);
    __m128i c8 = _mm_setr_epi8(-1, -1, -1, -1, -1, -1, -1, -1, 1, 3, 5, 7, 9,
                               11, 13, 15);

    __m128i state1, state2, state3, state4, k, t1, t2, t3, t4;

    state2 = _mm_loadu_si128((const __m128i *)ciphertext);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state4 = _mm_loadu_si128((const __m128i *)(ciphertext + 16));
    state3 = _mm_srli_epi16(state4, 4);
    state3 = _mm_and_si128(state3, con);
    state4 = _mm_and_si128(state4, con);
    t1     = _mm_shuffle_epi8(state3, c1);
    t2     = _mm_shuffle_epi8(state4, c2);
    t3     = _mm_shuffle_epi8(state3, c3);
    t4     = _mm_shuffle_epi8(state4, c4);
    state3 = _mm_xor_si128(t1, t2);
    state4 = _mm_xor_si128(t3, t4);

    for (i = 24; i > 0; i--)
    {
        k      = _mm_loadu_si128((const __m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 16));
        state3 = _mm_xor_si128(state3, _mm_and_si128(k, con));
        k      = _mm_srli_epi32(k, 4);
        state4 = _mm_xor_si128(state4, _mm_and_si128(k, con));

        t1     = _mm_shuffle_epi8(state1, L1);
        t2     = _mm_shuffle_epi8(state2, L2);
        t3     = _mm_shuffle_epi8(state1, L3);
        t4     = _mm_shuffle_epi8(state2, L4);
        state1 = _mm_xor_si128(t1, t2);
        state2 = _mm_xor_si128(t3, t4);

        t1     = _mm_shuffle_epi8(state3, L5);
        t2     = _mm_shuffle_epi8(state4, L6);
        t3     = _mm_shuffle_epi8(state3, L7);
        t4     = _mm_shuffle_epi8(state4, L8);
        state3 = _mm_xor_si128(t1, t2);
        state4 = _mm_xor_si128(t3, t4);

        state1 = _mm_xor_si128(state1, state3);
        state2 = _mm_xor_si128(state2, state4);

        k      = _mm_shuffle_epi8(state1, A3);
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_shuffle_epi8(state2, A3);
        state4 = _mm_xor_si128(state4, k);

        k      = _mm_shuffle_epi8(state3, A2);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state4, A2);
        state2 = _mm_xor_si128(state2, k);

        k      = _mm_shuffle_epi8(state1, A2);
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_shuffle_epi8(state2, A2);
        state4 = _mm_xor_si128(state4, k);

        k      = _mm_shuffle_epi8(state3, A1);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_shuffle_epi8(state4, A1);
        state2 = _mm_xor_si128(state2, k);

        state3 = _mm_xor_si128(state3, state1);
        state4 = _mm_xor_si128(state4, state2);

        state1 = _mm_shuffle_epi8(S_Inv, state1);
        state2 = _mm_shuffle_epi8(S_Inv, state2);
        state3 = _mm_shuffle_epi8(S_Inv, state3);
        state4 = _mm_shuffle_epi8(S_Inv, state4);
    }

    k      = _mm_loadu_si128((const __m128i *)sub_key[0]);
    state1 = _mm_xor_si128(state1, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state2 = _mm_xor_si128(state2, _mm_and_si128(k, con));
    k      = _mm_loadu_si128((const __m128i *)(sub_key[0] + 16));
    state3 = _mm_xor_si128(state3, _mm_and_si128(k, con));
    k      = _mm_srli_epi32(k, 4);
    state4 = _mm_xor_si128(state4, _mm_and_si128(k, con));

    t1     = _mm_shuffle_epi8(state1, c5);
    t2     = _mm_shuffle_epi8(state2, c6);
    t3     = _mm_shuffle_epi8(state1, c7);
    t4     = _mm_shuffle_epi8(state2, c8);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);
    state1 = _mm_slli_epi16(state1, 4);
    state1 = _mm_xor_si128(state1, state2);

    t1     = _mm_shuffle_epi8(state3, c5);
    t2     = _mm_shuffle_epi8(state4, c6);
    t3     = _mm_shuffle_epi8(state3, c7);
    t4     = _mm_shuffle_epi8(state4, c8);
    state3 = _mm_xor_si128(t1, t2);
    state4 = _mm_xor_si128(t3, t4);
    state3 = _mm_slli_epi16(state3, 4);
    state3 = _mm_xor_si128(state3, state4);

    _mm_storeu_si128((__m128i *)plaintext, state1);
    _mm_storeu_si128((__m128i *)(plaintext + 16), state3);

    return;
}

/**
 * Ending here, to the previous similar comment declaration.
 *
 * the code is "derived from
 * https://sfjs.cacrnet.org.cn/site/term/list_76_1.html"
 *
 * WU W L, ZHANG L, ZHENG Y F, LI L C. The block cipher uBlock[J]. Journal of
 * Cryptologic Research, 2019, 6(6): 690-703.
 */

#define XOR2            _mm256_xor_si256
#define OR2             _mm256_or_si256
#define AND2            _mm256_and_si256
#define ANDNOT2         _mm256_andnot_si256
#define NOT1(x)         XOR2(x, _mm256_set1_epi8(-1))
#define SLL_EPI32       _mm256_slli_epi32
#define SRL_EPI32       _mm256_srli_epi32
#define ROL_EPI32(a, s) XOR2(SLL_EPI32(a, s), SRL_EPI32(a, 32 - s))

#define UBLOCK_ISBOX(X)                  \
    X[2] = XOR2(X[2], OR2(X[0], X[3]));  \
    X[1] = XOR2(X[1], AND2(X[3], X[2])); \
    X[3] = XOR2(X[3], OR2(X[0], X[1]));  \
    X[1] = NOT1(X[1]);                   \
    X[0] = XOR2(X[0], OR2(X[1], X[2]))

#define SWAPMOVE(matrix, mask, r, k, j, t, t1, t2)              \
    do                                                          \
    {                                                           \
        t             = ANDNOT2(mask[j], matrix[r + k]);        \
        t             = SRL_EPI32(t, k);                        \
        t             = OR2(ANDNOT2(mask[j], matrix[r]), t);    \
        t1            = SLL_EPI32(AND2(matrix[r], mask[j]), k); \
        t2            = AND2(matrix[r + k], mask[j]);           \
        matrix[r]     = t;                                      \
        matrix[r + k] = OR2(t1, t2);                            \
    } while (0)

static inline void _ublock128data_load(__m256i            X[8],
                                       const std::uint8_t data[256])
{
    static const uint8_t ENDIAN[32] = {
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
    };

    __m256i mask[2] = {
        _mm256_set1_epi16(0x5555), // 0101...0101
        _mm256_set1_epi16(0x3333), // 0011...0011
    };
    __m256i t, t1, t2;
    __m256i ENDIAN_IDX = _mm256_loadu_si256((const __m256i *)ENDIAN);
    // load data
    X[0] = _mm256_loadu_si256((const __m256i *)(data + 32 * 0));
    X[1] = _mm256_loadu_si256((const __m256i *)(data + 32 * 1));
    X[2] = _mm256_loadu_si256((const __m256i *)(data + 32 * 2));
    X[3] = _mm256_loadu_si256((const __m256i *)(data + 32 * 3));
    X[4] = _mm256_loadu_si256((const __m256i *)(data + 32 * 4));
    X[5] = _mm256_loadu_si256((const __m256i *)(data + 32 * 5));
    X[6] = _mm256_loadu_si256((const __m256i *)(data + 32 * 6));
    X[7] = _mm256_loadu_si256((const __m256i *)(data + 32 * 7));
    // tans endian
    X[0] = _mm256_shuffle_epi8(X[0], ENDIAN_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], ENDIAN_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], ENDIAN_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], ENDIAN_IDX);
    X[4] = _mm256_shuffle_epi8(X[4], ENDIAN_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], ENDIAN_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], ENDIAN_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], ENDIAN_IDX);
    // pack64-bit
    t1   = _mm256_unpackhi_epi64(X[4], X[0]);
    t2   = _mm256_unpacklo_epi64(X[4], X[0]);
    X[0] = t1, X[4] = t2;
    t1   = _mm256_unpackhi_epi64(X[5], X[1]);
    t2   = _mm256_unpacklo_epi64(X[5], X[1]);
    X[1] = t1, X[5] = t2;
    t1   = _mm256_unpackhi_epi64(X[6], X[2]);
    t2   = _mm256_unpacklo_epi64(X[6], X[2]);
    X[2] = t1, X[6] = t2;
    t1   = _mm256_unpackhi_epi64(X[7], X[3]);
    t2   = _mm256_unpacklo_epi64(X[7], X[3]);
    X[3] = t1, X[7] = t2;
    // BIT SLICE 8
    SWAPMOVE(X, mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE(X, mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE(X, mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE(X, mask, 1, 2, 1, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE((X + 4), mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE((X + 4), mask, 1, 2, 1, t, t1, t2);
}

static inline void _ublock128data_store(std::uint8_t data[256], __m256i X[8])
{
    static const uint8_t ENDIAN[32] = {
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
    };

    __m256i ENDIAN_IDX = _mm256_loadu_si256((const __m256i *)ENDIAN);

    // BIT SLICE 8
    __m256i mask[3] = {
        _mm256_set1_epi16(0x5555), // 0101...0101
        _mm256_set1_epi16(0x3333)  // 0011...0011
    };
    __m256i t, t1, t2;
    SWAPMOVE(X, mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE(X, mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE(X, mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE(X, mask, 1, 2, 1, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE((X + 4), mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE((X + 4), mask, 1, 2, 1, t, t1, t2);
    // pack64-bit
    t1   = _mm256_unpackhi_epi64(X[4], X[0]);
    t2   = _mm256_unpacklo_epi64(X[4], X[0]);
    X[0] = t1, X[4] = t2;
    t1   = _mm256_unpackhi_epi64(X[5], X[1]);
    t2   = _mm256_unpacklo_epi64(X[5], X[1]);
    X[1] = t1, X[5] = t2;
    t1   = _mm256_unpackhi_epi64(X[6], X[2]);
    t2   = _mm256_unpacklo_epi64(X[6], X[2]);
    X[2] = t1, X[6] = t2;
    t1   = _mm256_unpackhi_epi64(X[7], X[3]);
    t2   = _mm256_unpacklo_epi64(X[7], X[3]);
    X[3] = t1, X[7] = t2;
    // tans endian
    X[0] = _mm256_shuffle_epi8(X[0], ENDIAN_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], ENDIAN_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], ENDIAN_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], ENDIAN_IDX);
    X[4] = _mm256_shuffle_epi8(X[4], ENDIAN_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], ENDIAN_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], ENDIAN_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], ENDIAN_IDX);
    // store
    _mm256_storeu_si256((__m256i *)(data + 32 * 0), X[0]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 1), X[1]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 2), X[2]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 3), X[3]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 4), X[4]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 5), X[5]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 6), X[6]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 7), X[7]);
}

static inline void _ublock128_enc_round(__m256i X[8], const __m256i subkey[8])
{
    static const uint8_t ROTL8_EPI32[32] = {
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
    };
    static const uint8_t PL_EPI64[32] = {
        2, 0, 5, 7, 1, 3, 4, 6, 10, 8, 13, 15, 9, 11, 12, 14, //
        2, 0, 5, 7, 1, 3, 4, 6, 10, 8, 13, 15, 9, 11, 12, 14, //
    };
    static const uint8_t PR_EPI64[32] = {
        4, 3, 1, 6, 7, 2, 0, 5, 12, 11, 9, 14, 15, 10, 8, 13, //
        4, 3, 1, 6, 7, 2, 0, 5, 12, 11, 9, 14, 15, 10, 8, 13, //
    };
    __m256i ROL8_EPI32_IDX = _mm256_loadu_si256((const __m256i *)ROTL8_EPI32);
    __m256i PL_EPI64_IDX   = _mm256_loadu_si256((const __m256i *)PL_EPI64);
    __m256i PR_EPI64_IDX   = _mm256_loadu_si256((const __m256i *)PR_EPI64);

    // sub key xor
    X[0] = XOR2(X[0], subkey[0]);
    X[1] = XOR2(X[1], subkey[1]);
    X[2] = XOR2(X[2], subkey[2]);
    X[3] = XOR2(X[3], subkey[3]);
    X[4] = XOR2(X[4], subkey[4]);
    X[5] = XOR2(X[5], subkey[5]);
    X[6] = XOR2(X[6], subkey[6]);
    X[7] = XOR2(X[7], subkey[7]);
    // sbox: 0-3
    X[0] = XOR2(X[0], OR2(X[2], X[1]));
    X[1] = NOT1(X[1]);
    X[3] = XOR2(X[3], OR2(X[0], X[1]));
    X[1] = XOR2(X[1], AND2(X[2], X[3]));
    X[2] = XOR2(X[2], OR2(X[0], X[3]));
    // sbox: 4-7
    X[4] = XOR2(X[4], OR2(X[6], X[5]));
    X[5] = NOT1(X[5]);
    X[7] = XOR2(X[7], OR2(X[4], X[5]));
    X[5] = XOR2(X[5], AND2(X[6], X[7]));
    X[6] = XOR2(X[6], OR2(X[4], X[7]));
    // B: X1 = X1 ^ X0
    X[4] = XOR2(X[4], X[0]);
    X[5] = XOR2(X[5], X[1]);
    X[6] = XOR2(X[6], X[2]);
    X[7] = XOR2(X[7], X[3]);
    // B: X0 = X0 ^ X1 << 4
    X[0] = XOR2(X[0], ROL_EPI32(X[4], 4));
    X[1] = XOR2(X[1], ROL_EPI32(X[5], 4));
    X[2] = XOR2(X[2], ROL_EPI32(X[6], 4));
    X[3] = XOR2(X[3], ROL_EPI32(X[7], 4));
    // B: X1 = X1 ^ X0 << 8
    X[4] = XOR2(X[4], _mm256_shuffle_epi8(X[0], ROL8_EPI32_IDX));
    X[5] = XOR2(X[5], _mm256_shuffle_epi8(X[1], ROL8_EPI32_IDX));
    X[6] = XOR2(X[6], _mm256_shuffle_epi8(X[2], ROL8_EPI32_IDX));
    X[7] = XOR2(X[7], _mm256_shuffle_epi8(X[3], ROL8_EPI32_IDX));
    // B: X0 = X0 ^ X1 << 8
    X[0] = XOR2(X[0], _mm256_shuffle_epi8(X[4], ROL8_EPI32_IDX));
    X[1] = XOR2(X[1], _mm256_shuffle_epi8(X[5], ROL8_EPI32_IDX));
    X[2] = XOR2(X[2], _mm256_shuffle_epi8(X[6], ROL8_EPI32_IDX));
    X[3] = XOR2(X[3], _mm256_shuffle_epi8(X[7], ROL8_EPI32_IDX));
    // B: X1 = X1 ^ X0 << 20
    X[4] = XOR2(X[4], ROL_EPI32(X[0], 20));
    X[5] = XOR2(X[5], ROL_EPI32(X[1], 20));
    X[6] = XOR2(X[6], ROL_EPI32(X[2], 20));
    X[7] = XOR2(X[7], ROL_EPI32(X[3], 20));
    // B: X0 = X0 ^ X1
    X[0] = XOR2(X[0], X[4]);
    X[1] = XOR2(X[1], X[5]);
    X[2] = XOR2(X[2], X[6]);
    X[3] = XOR2(X[3], X[7]);
    // PL
    X[0] = _mm256_shuffle_epi8(X[0], PL_EPI64_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], PL_EPI64_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], PL_EPI64_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], PL_EPI64_IDX);
    // PR
    X[4] = _mm256_shuffle_epi8(X[4], PR_EPI64_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], PR_EPI64_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], PR_EPI64_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], PR_EPI64_IDX);
}

static inline void _ublock128_dec_round(__m256i X[8], const __m256i subkey[8])
{
    static const uint8_t ROTL8_EPI32[32] = {
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
    };
    static const uint8_t IPL_EPI64[32] = {
        1, 4, 0, 5, 6, 2, 7, 3, 9, 12, 8, 13, 14, 10, 15, 11, //
        1, 4, 0, 5, 6, 2, 7, 3, 9, 12, 8, 13, 14, 10, 15, 11, //
    };
    static const uint8_t IPR_EPI64[32] = {
        6, 2, 5, 1, 0, 7, 3, 4, 14, 10, 13, 9, 8, 15, 11, 12, //
        6, 2, 5, 1, 0, 7, 3, 4, 14, 10, 13, 9, 8, 15, 11, 12, //
    };
    __m256i ROL8_EPI32_IDX = _mm256_loadu_si256((const __m256i *)ROTL8_EPI32);
    __m256i IPL_EPI64_IDX  = _mm256_loadu_si256((const __m256i *)IPL_EPI64);
    __m256i IPR_EPI64_IDX  = _mm256_loadu_si256((const __m256i *)IPR_EPI64);

    // sub key xor
    X[0] = XOR2(X[0], subkey[0]);
    X[1] = XOR2(X[1], subkey[1]);
    X[2] = XOR2(X[2], subkey[2]);
    X[3] = XOR2(X[3], subkey[3]);
    X[4] = XOR2(X[4], subkey[4]);
    X[5] = XOR2(X[5], subkey[5]);
    X[6] = XOR2(X[6], subkey[6]);
    X[7] = XOR2(X[7], subkey[7]);
    // PL
    X[0] = _mm256_shuffle_epi8(X[0], IPL_EPI64_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], IPL_EPI64_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], IPL_EPI64_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], IPL_EPI64_IDX);
    // PR
    X[4] = _mm256_shuffle_epi8(X[4], IPR_EPI64_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], IPR_EPI64_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], IPR_EPI64_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], IPR_EPI64_IDX);
    // B: X0 = X0 ^ X1
    X[0] = XOR2(X[0], X[4]);
    X[1] = XOR2(X[1], X[5]);
    X[2] = XOR2(X[2], X[6]);
    X[3] = XOR2(X[3], X[7]);
    // B: X1 = X1 ^ X0 << 20
    X[4] = XOR2(X[4], ROL_EPI32(X[0], 20));
    X[5] = XOR2(X[5], ROL_EPI32(X[1], 20));
    X[6] = XOR2(X[6], ROL_EPI32(X[2], 20));
    X[7] = XOR2(X[7], ROL_EPI32(X[3], 20));
    // B: X0 = X0 ^ X1 << 8
    X[0] = XOR2(X[0], _mm256_shuffle_epi8(X[4], ROL8_EPI32_IDX));
    X[1] = XOR2(X[1], _mm256_shuffle_epi8(X[5], ROL8_EPI32_IDX));
    X[2] = XOR2(X[2], _mm256_shuffle_epi8(X[6], ROL8_EPI32_IDX));
    X[3] = XOR2(X[3], _mm256_shuffle_epi8(X[7], ROL8_EPI32_IDX));
    // B: X1 = X1 ^ X0 << 8
    X[4] = XOR2(X[4], _mm256_shuffle_epi8(X[0], ROL8_EPI32_IDX));
    X[5] = XOR2(X[5], _mm256_shuffle_epi8(X[1], ROL8_EPI32_IDX));
    X[6] = XOR2(X[6], _mm256_shuffle_epi8(X[2], ROL8_EPI32_IDX));
    X[7] = XOR2(X[7], _mm256_shuffle_epi8(X[3], ROL8_EPI32_IDX));
    // B: X0 = X0 ^ X1 << 4
    X[0] = XOR2(X[0], ROL_EPI32(X[4], 4));
    X[1] = XOR2(X[1], ROL_EPI32(X[5], 4));
    X[2] = XOR2(X[2], ROL_EPI32(X[6], 4));
    X[3] = XOR2(X[3], ROL_EPI32(X[7], 4));
    // B: X1 = X1 ^ X0
    X[4] = XOR2(X[4], X[0]);
    X[5] = XOR2(X[5], X[1]);
    X[6] = XOR2(X[6], X[2]);
    X[7] = XOR2(X[7], X[3]);
    // isbox: 0-3
    X[2] = XOR2(X[2], OR2(X[0], X[3]));
    X[1] = XOR2(X[1], AND2(X[3], X[2]));
    X[3] = XOR2(X[3], OR2(X[0], X[1]));
    X[1] = NOT1(X[1]);
    X[0] = XOR2(X[0], OR2(X[1], X[2]));
    // isbox: 4-7
    X[6] = XOR2(X[6], OR2(X[4], X[7]));
    X[5] = XOR2(X[5], AND2(X[7], X[6]));
    X[7] = XOR2(X[7], OR2(X[4], X[5]));
    X[5] = NOT1(X[5]);
    X[4] = XOR2(X[4], OR2(X[5], X[6]));
}

static inline void _ublock256data_load(__m256i            X[8],
                                       const std::uint8_t data[256])
{
    static const uint8_t ENDIAN[32] = {
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
    };

    __m256i mask[2] = {
        _mm256_set1_epi16(0x5555), // 0101...0101
        _mm256_set1_epi16(0x3333), // 0011...0011
    };
    __m256i t, t1, t2;
    __m256i ENDIAN_IDX = _mm256_loadu_si256((const __m256i *)ENDIAN);
    // load data
    X[0] = _mm256_loadu_si256((const __m256i *)(data + 32 * 0));
    X[1] = _mm256_loadu_si256((const __m256i *)(data + 32 * 1));
    X[2] = _mm256_loadu_si256((const __m256i *)(data + 32 * 2));
    X[3] = _mm256_loadu_si256((const __m256i *)(data + 32 * 3));
    X[4] = _mm256_loadu_si256((const __m256i *)(data + 32 * 4));
    X[5] = _mm256_loadu_si256((const __m256i *)(data + 32 * 5));
    X[6] = _mm256_loadu_si256((const __m256i *)(data + 32 * 6));
    X[7] = _mm256_loadu_si256((const __m256i *)(data + 32 * 7));
    // tans endian
    X[0] = _mm256_shuffle_epi8(X[0], ENDIAN_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], ENDIAN_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], ENDIAN_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], ENDIAN_IDX);
    X[4] = _mm256_shuffle_epi8(X[4], ENDIAN_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], ENDIAN_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], ENDIAN_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], ENDIAN_IDX);
    // pack64-bit
    t1   = _mm256_permute2x128_si256(X[0], X[4], 0x20);
    t2   = _mm256_permute2x128_si256(X[0], X[4], 0x31);
    X[0] = t1, X[4] = t2;
    t1   = _mm256_permute2x128_si256(X[1], X[5], 0x20);
    t2   = _mm256_permute2x128_si256(X[1], X[5], 0x31);
    X[1] = t1, X[5] = t2;
    t1   = _mm256_permute2x128_si256(X[2], X[6], 0x20);
    t2   = _mm256_permute2x128_si256(X[2], X[6], 0x31);
    X[2] = t1, X[6] = t2;
    t1   = _mm256_permute2x128_si256(X[3], X[7], 0x20);
    t2   = _mm256_permute2x128_si256(X[3], X[7], 0x31);
    X[3] = t1, X[7] = t2;
    // BIT SLICE 8
    SWAPMOVE(X, mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE(X, mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE(X, mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE(X, mask, 1, 2, 1, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE((X + 4), mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE((X + 4), mask, 1, 2, 1, t, t1, t2);
}

static inline void _ublock256data_store(std::uint8_t data[256], __m256i X[8])
{
    static const uint8_t ENDIAN[32] = {
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
    };

    __m256i ENDIAN_IDX = _mm256_loadu_si256((const __m256i *)ENDIAN);

    // BIT SLICE 8
    __m256i mask[3] = {
        _mm256_set1_epi16(0x5555), // 0101...0101
        _mm256_set1_epi16(0x3333)  // 0011...0011
    };
    __m256i t, t1, t2;
    SWAPMOVE(X, mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE(X, mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE(X, mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE(X, mask, 1, 2, 1, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 1, 0, t, t1, t2);
    SWAPMOVE((X + 4), mask, 2, 1, 0, t, t1, t2);

    SWAPMOVE((X + 4), mask, 0, 2, 1, t, t1, t2);
    SWAPMOVE((X + 4), mask, 1, 2, 1, t, t1, t2);
    // pack64-bit
    t1   = _mm256_permute2x128_si256(X[0], X[4], 0x20);
    t2   = _mm256_permute2x128_si256(X[0], X[4], 0x31);
    X[0] = t1, X[4] = t2;
    t1   = _mm256_permute2x128_si256(X[1], X[5], 0x20);
    t2   = _mm256_permute2x128_si256(X[1], X[5], 0x31);
    X[1] = t1, X[5] = t2;
    t1   = _mm256_permute2x128_si256(X[2], X[6], 0x20);
    t2   = _mm256_permute2x128_si256(X[2], X[6], 0x31);
    X[2] = t1, X[6] = t2;
    t1   = _mm256_permute2x128_si256(X[3], X[7], 0x20);
    t2   = _mm256_permute2x128_si256(X[3], X[7], 0x31);
    X[3] = t1, X[7] = t2;
    // tans endian
    X[0] = _mm256_shuffle_epi8(X[0], ENDIAN_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], ENDIAN_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], ENDIAN_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], ENDIAN_IDX);
    X[4] = _mm256_shuffle_epi8(X[4], ENDIAN_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], ENDIAN_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], ENDIAN_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], ENDIAN_IDX);
    // store
    _mm256_storeu_si256((__m256i *)(data + 32 * 0), X[0]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 1), X[1]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 2), X[2]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 3), X[3]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 4), X[4]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 5), X[5]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 6), X[6]);
    _mm256_storeu_si256((__m256i *)(data + 32 * 7), X[7]);
}

static inline void _ublock256256_enc_round(__m256i       X[16],
                                           const __m256i subkey[16])
{
    static const uint8_t ROTL8_EPI32[32] = {
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
    };
    static const uint8_t PL_EPI128[32] = {
        15, 10, 4, 1, 5, 0, 11, 14, 3, 6, 9, 12, 2, 7, 8, 13, //
        15, 10, 4, 1, 5, 0, 11, 14, 3, 6, 9, 12, 2, 7, 8, 13, //
    };
    static const uint8_t PR_EPI128[32] = {
        10, 7, 12, 1, 5, 2, 15, 8, 0, 13, 11, 6, 3, 14, 4, 9, //
        10, 7, 12, 1, 5, 2, 15, 8, 0, 13, 11, 6, 3, 14, 4, 9, //
    };

    __m256i ROL8_EPI32_IDX = _mm256_loadu_si256((const __m256i *)ROTL8_EPI32);
    __m256i PL_EPI128_IDX  = _mm256_loadu_si256((const __m256i *)PL_EPI128);
    __m256i PR_EPI128_IDX  = _mm256_loadu_si256((const __m256i *)PR_EPI128);
    // sub key xor
    X[0] = _mm256_xor_si256(X[0], subkey[0]);
    X[1] = _mm256_xor_si256(X[1], subkey[1]);
    X[2] = _mm256_xor_si256(X[2], subkey[2]);
    X[3] = _mm256_xor_si256(X[3], subkey[3]);
    X[4] = _mm256_xor_si256(X[4], subkey[4]);
    X[5] = _mm256_xor_si256(X[5], subkey[5]);
    X[6] = _mm256_xor_si256(X[6], subkey[6]);
    X[7] = _mm256_xor_si256(X[7], subkey[7]);
    // sbox: 0-3
    X[0] = XOR2(X[0], OR2(X[2], X[1]));
    X[1] = NOT1(X[1]);
    X[3] = XOR2(X[3], OR2(X[0], X[1]));
    X[1] = XOR2(X[1], AND2(X[2], X[3]));
    X[2] = XOR2(X[2], OR2(X[0], X[3]));
    // sbox: 4-7
    X[4] = XOR2(X[4], OR2(X[6], X[5]));
    X[5] = NOT1(X[5]);
    X[7] = XOR2(X[7], OR2(X[4], X[5]));
    X[5] = XOR2(X[5], AND2(X[6], X[7]));
    X[6] = XOR2(X[6], OR2(X[4], X[7]));
    // B: X1 = X1 ^ X0
    X[4] = _mm256_xor_si256(X[4], X[0]);
    X[5] = _mm256_xor_si256(X[5], X[1]);
    X[6] = _mm256_xor_si256(X[6], X[2]);
    X[7] = _mm256_xor_si256(X[7], X[3]);
    // B: X0 = X0 ^ X1 << 4
    X[0] = _mm256_xor_si256(X[0], ROL_EPI32(X[4], 4));
    X[1] = _mm256_xor_si256(X[1], ROL_EPI32(X[5], 4));
    X[2] = _mm256_xor_si256(X[2], ROL_EPI32(X[6], 4));
    X[3] = _mm256_xor_si256(X[3], ROL_EPI32(X[7], 4));
    // B: X1 = X1 ^ X0 << 8
    X[4] = _mm256_xor_si256(X[4], _mm256_shuffle_epi8(X[0], ROL8_EPI32_IDX));
    X[5] = _mm256_xor_si256(X[5], _mm256_shuffle_epi8(X[1], ROL8_EPI32_IDX));
    X[6] = _mm256_xor_si256(X[6], _mm256_shuffle_epi8(X[2], ROL8_EPI32_IDX));
    X[7] = _mm256_xor_si256(X[7], _mm256_shuffle_epi8(X[3], ROL8_EPI32_IDX));
    // B: X0 = X0 ^ X1 << 8
    X[0] = _mm256_xor_si256(X[0], _mm256_shuffle_epi8(X[4], ROL8_EPI32_IDX));
    X[1] = _mm256_xor_si256(X[1], _mm256_shuffle_epi8(X[5], ROL8_EPI32_IDX));
    X[2] = _mm256_xor_si256(X[2], _mm256_shuffle_epi8(X[6], ROL8_EPI32_IDX));
    X[3] = _mm256_xor_si256(X[3], _mm256_shuffle_epi8(X[7], ROL8_EPI32_IDX));
    // B: X1 = X1 ^ X0 << 20
    X[4] = _mm256_xor_si256(X[4], ROL_EPI32(X[0], 20));
    X[5] = _mm256_xor_si256(X[5], ROL_EPI32(X[1], 20));
    X[6] = _mm256_xor_si256(X[6], ROL_EPI32(X[2], 20));
    X[7] = _mm256_xor_si256(X[7], ROL_EPI32(X[3], 20));
    // B: X0 = X0 ^ X1
    X[0] = _mm256_xor_si256(X[0], X[4]);
    X[1] = _mm256_xor_si256(X[1], X[5]);
    X[2] = _mm256_xor_si256(X[2], X[6]);
    X[3] = _mm256_xor_si256(X[3], X[7]);
    // PL
    X[0] = _mm256_shuffle_epi8(X[0], PL_EPI128_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], PL_EPI128_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], PL_EPI128_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], PL_EPI128_IDX);
    // PR
    X[4] = _mm256_shuffle_epi8(X[4], PR_EPI128_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], PR_EPI128_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], PR_EPI128_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], PR_EPI128_IDX);
}

static inline void _ublock256256_dec_round(__m256i       X[16],
                                           const __m256i subkey[16])
{
    static const uint8_t ROTL8_EPI32[32] = {
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
        3, 0, 1, 2, 7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
    };
    static const uint8_t IPL_EPI128[32] = {
        5, 3, 12, 8, 2, 4, 9, 13, 14, 10, 1, 6, 11, 15, 7, 0, //
        5, 3, 12, 8, 2, 4, 9, 13, 14, 10, 1, 6, 11, 15, 7, 0, //
    };
    static const uint8_t IPR_EPI128[32] = {
        8, 3, 5, 12, 14, 4, 11, 1, 7, 15, 0, 10, 2, 9, 13, 6, //
        8, 3, 5, 12, 14, 4, 11, 1, 7, 15, 0, 10, 2, 9, 13, 6, //
    };
    __m256i ROL8_EPI32_IDX = _mm256_loadu_si256((const __m256i *)ROTL8_EPI32);
    __m256i IPL_EPI128_IDX = _mm256_loadu_si256((const __m256i *)IPL_EPI128);
    __m256i IPR_EPI128_IDX = _mm256_loadu_si256((const __m256i *)IPR_EPI128);

    // sub key xor
    X[0] = XOR2(X[0], subkey[0]);
    X[1] = XOR2(X[1], subkey[1]);
    X[2] = XOR2(X[2], subkey[2]);
    X[3] = XOR2(X[3], subkey[3]);
    X[4] = XOR2(X[4], subkey[4]);
    X[5] = XOR2(X[5], subkey[5]);
    X[6] = XOR2(X[6], subkey[6]);
    X[7] = XOR2(X[7], subkey[7]);
    // PL
    X[0] = _mm256_shuffle_epi8(X[0], IPL_EPI128_IDX);
    X[1] = _mm256_shuffle_epi8(X[1], IPL_EPI128_IDX);
    X[2] = _mm256_shuffle_epi8(X[2], IPL_EPI128_IDX);
    X[3] = _mm256_shuffle_epi8(X[3], IPL_EPI128_IDX);
    // PR
    X[4] = _mm256_shuffle_epi8(X[4], IPR_EPI128_IDX);
    X[5] = _mm256_shuffle_epi8(X[5], IPR_EPI128_IDX);
    X[6] = _mm256_shuffle_epi8(X[6], IPR_EPI128_IDX);
    X[7] = _mm256_shuffle_epi8(X[7], IPR_EPI128_IDX);
    // B: X0 = X0 ^ X1
    X[0] = XOR2(X[0], X[4]);
    X[1] = XOR2(X[1], X[5]);
    X[2] = XOR2(X[2], X[6]);
    X[3] = XOR2(X[3], X[7]);
    // B: X1 = X1 ^ X0 << 20
    X[4] = XOR2(X[4], ROL_EPI32(X[0], 20));
    X[5] = XOR2(X[5], ROL_EPI32(X[1], 20));
    X[6] = XOR2(X[6], ROL_EPI32(X[2], 20));
    X[7] = XOR2(X[7], ROL_EPI32(X[3], 20));
    // B: X0 = X0 ^ X1 << 8
    X[0] = XOR2(X[0], _mm256_shuffle_epi8(X[4], ROL8_EPI32_IDX));
    X[1] = XOR2(X[1], _mm256_shuffle_epi8(X[5], ROL8_EPI32_IDX));
    X[2] = XOR2(X[2], _mm256_shuffle_epi8(X[6], ROL8_EPI32_IDX));
    X[3] = XOR2(X[3], _mm256_shuffle_epi8(X[7], ROL8_EPI32_IDX));
    // B: X1 = X1 ^ X0 << 8
    X[4] = XOR2(X[4], _mm256_shuffle_epi8(X[0], ROL8_EPI32_IDX));
    X[5] = XOR2(X[5], _mm256_shuffle_epi8(X[1], ROL8_EPI32_IDX));
    X[6] = XOR2(X[6], _mm256_shuffle_epi8(X[2], ROL8_EPI32_IDX));
    X[7] = XOR2(X[7], _mm256_shuffle_epi8(X[3], ROL8_EPI32_IDX));
    // B: X0 = X0 ^ X1 << 4
    X[0] = XOR2(X[0], ROL_EPI32(X[4], 4));
    X[1] = XOR2(X[1], ROL_EPI32(X[5], 4));
    X[2] = XOR2(X[2], ROL_EPI32(X[6], 4));
    X[3] = XOR2(X[3], ROL_EPI32(X[7], 4));
    // B: X1 = X1 ^ X0
    X[4] = XOR2(X[4], X[0]);
    X[5] = XOR2(X[5], X[1]);
    X[6] = XOR2(X[6], X[2]);
    X[7] = XOR2(X[7], X[3]);
    // isbox: 0-3
    X[2] = XOR2(X[2], OR2(X[0], X[3]));
    X[1] = XOR2(X[1], AND2(X[3], X[2]));
    X[3] = XOR2(X[3], OR2(X[0], X[1]));
    X[1] = NOT1(X[1]);
    X[0] = XOR2(X[0], OR2(X[1], X[2]));
    // isbox: 4-7
    X[6] = XOR2(X[6], OR2(X[4], X[7]));
    X[5] = XOR2(X[5], AND2(X[7], X[6]));
    X[7] = XOR2(X[7], OR2(X[4], X[5]));
    X[5] = NOT1(X[5]);
    X[4] = XOR2(X[4], OR2(X[5], X[6]));
}

static inline void _ublock128_bs_key_init(std::uint8_t m256i_subkey[8][32],
                                          const std::uint8_t round_key[16])
{
    static const std::uint8_t SHUFFLE_DATA[16] = {
        15, 13, 11, 9, 7, 5, 3, 1, 14, 12, 10, 8, 6, 4, 2, 0,
    };
    __m128i k, state1, state2, t;
    __m128i con1 = _mm_set1_epi8(0xF);
    __m128i con2 = _mm_loadu_si128((const __m128i *)SHUFFLE_DATA);
    __m128i con3 = _mm_set1_epi8(0x11);

    __m128i s1, s0, s;
    __m256i t1, t0;
    k      = _mm_loadu_si128((const __m128i *)round_key);
    state1 = _mm_and_si128(k, con1);
    k      = _mm_srli_epi32(k, 4);
    state2 = _mm_and_si128(k, con1);

    state1 = _mm_shuffle_epi8(state1, con2);
    state2 = _mm_shuffle_epi8(state2, con2);

    s1 = _mm_unpackhi_epi64(state2, state1);
    s0 = _mm_unpacklo_epi64(state2, state1);
    t  = _mm_xor_si128(_mm_slli_epi64(s1, 4), s0);

    s  = _mm_and_si128(t, con3);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 1), s);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 2), s);
    t1 = _mm256_broadcastq_epi64(_mm_srli_si128(s, 8));
    t0 = _mm256_broadcastq_epi64(s);
    _mm256_storeu_si256((__m256i *)m256i_subkey[3], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[7], t0);

    t  = _mm_srli_epi32(t, 1);
    s  = _mm_and_si128(t, con3);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 1), s);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 2), s);
    t1 = _mm256_broadcastq_epi64(_mm_srli_si128(s, 8));
    t0 = _mm256_broadcastq_epi64(s);
    _mm256_storeu_si256((__m256i *)m256i_subkey[2], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[6], t0);

    t  = _mm_srli_epi32(t, 1);
    s  = _mm_and_si128(t, con3);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 1), s);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 2), s);
    t1 = _mm256_broadcastq_epi64(_mm_srli_si128(s, 8));
    t0 = _mm256_broadcastq_epi64(s);
    _mm256_storeu_si256((__m256i *)m256i_subkey[1], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[5], t0);

    t  = _mm_srli_epi32(t, 1);
    s  = _mm_and_si128(t, con3);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 1), s);
    s  = _mm_xor_si128(_mm_slli_epi64(s, 2), s);
    t1 = _mm256_broadcastq_epi64(_mm_srli_si128(s, 8));
    t0 = _mm256_broadcastq_epi64(s);
    _mm256_storeu_si256((__m256i *)m256i_subkey[0], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[4], t0);
}

static inline void _ublock256_bs_key_init(std::uint8_t m256i_subkey[8][32],
                                          const std::uint8_t round_key[32])
{
    static const std::uint8_t SHUFFLE_ENDIAN_DATA[32] = {
        15, 13, 11, 9, 7, 5, 3, 1, 14, 12, 10, 8, 6, 4, 2, 0,
        15, 13, 11, 9, 7, 5, 3, 1, 14, 12, 10, 8, 6, 4, 2, 0,
    };
    __m256i k, state1, state2;
    __m256i con1 = _mm256_set1_epi8(0xF);
    __m256i con2 = _mm256_loadu_si256((const __m256i *)SHUFFLE_ENDIAN_DATA);
    __m256i con3 = _mm256_set1_epi8(0x11);
    k            = _mm256_loadu_si256((const __m256i *)round_key);
    state1       = _mm256_and_si256(k, con1);
    k            = _mm256_srli_epi32(k, 4);
    state2       = _mm256_and_si256(k, con1);

    __m256i t1, t0, t, s;
    state1 = _mm256_shuffle_epi8(state1, con2);
    state2 = _mm256_shuffle_epi8(state2, con2);

    t1 = _mm256_unpackhi_epi64(state2, state1);
    t0 = _mm256_unpacklo_epi64(state2, state1);
    t  = _mm256_xor_si256(_mm256_slli_epi64(t1, 4), t0);
    t  = _mm256_permute2x128_si256(t, t, 0x01);

    s  = AND2(t, con3);
    s  = XOR2(SLL_EPI32(s, 1), s);
    s  = XOR2(SLL_EPI32(s, 2), s);
    t1 = _mm256_permute2x128_si256(s, s, 0x11);
    t0 = _mm256_permute2x128_si256(s, s, 0x00);
    _mm256_storeu_si256((__m256i *)m256i_subkey[3], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[7], t0);

    t  = SRL_EPI32(t, 1);
    s  = AND2(t, con3);
    s  = XOR2(SLL_EPI32(s, 1), s);
    s  = XOR2(SLL_EPI32(s, 2), s);
    t1 = _mm256_permute2x128_si256(s, s, 0x11);
    t0 = _mm256_permute2x128_si256(s, s, 0x00);
    _mm256_storeu_si256((__m256i *)m256i_subkey[2], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[6], t0);

    t  = SRL_EPI32(t, 1);
    s  = AND2(t, con3);
    s  = XOR2(SLL_EPI32(s, 1), s);
    s  = XOR2(SLL_EPI32(s, 2), s);
    t1 = _mm256_permute2x128_si256(s, s, 0x11);
    t0 = _mm256_permute2x128_si256(s, s, 0x00);
    _mm256_storeu_si256((__m256i *)m256i_subkey[1], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[5], t0);

    t  = SRL_EPI32(t, 1);
    s  = AND2(t, con3);
    s  = XOR2(SLL_EPI32(s, 1), s);
    s  = XOR2(SLL_EPI32(s, 2), s);
    t1 = _mm256_permute2x128_si256(s, s, 0x11);
    t0 = _mm256_permute2x128_si256(s, s, 0x00);
    _mm256_storeu_si256((__m256i *)m256i_subkey[0], t1);
    _mm256_storeu_si256((__m256i *)m256i_subkey[4], t0);
}

static void _ublock128128_enc_block_x16(
    const std::uint8_t bs_round_key[17][8][32],
    std::uint8_t       out[256],
    const std::uint8_t in[256])
{
    __m256i X[8];
    __m256i subkey[8];
    _ublock128data_load(X, in);
    for (int i = 0; i < 16; i++)
    {
        subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][0]);
        subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][1]);
        subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][2]);
        subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][3]);
        subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][4]);
        subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][5]);
        subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][6]);
        subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][7]);
        _ublock128_enc_round(X, subkey);
    }
    // final subkey xor
    subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][0]);
    subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][1]);
    subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][2]);
    subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][3]);
    subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][4]);
    subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][5]);
    subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][6]);
    subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[16][7]);
    X[0]      = _mm256_xor_si256(X[0], subkey[0]);
    X[1]      = _mm256_xor_si256(X[1], subkey[1]);
    X[2]      = _mm256_xor_si256(X[2], subkey[2]);
    X[3]      = _mm256_xor_si256(X[3], subkey[3]);
    X[4]      = _mm256_xor_si256(X[4], subkey[4]);
    X[5]      = _mm256_xor_si256(X[5], subkey[5]);
    X[6]      = _mm256_xor_si256(X[6], subkey[6]);
    X[7]      = _mm256_xor_si256(X[7], subkey[7]);
    _ublock128data_store(out, X);
}

static void _ublock128128_dec_block_x16(
    const std::uint8_t bs_round_key[17][8][32],
    std::uint8_t       out[256],
    const std::uint8_t in[256])
{
    __m256i X[8];
    __m256i subkey[8];
    _ublock128data_load(X, in);
    for (int i = 16; i >= 1; i--)
    {
        subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][0]);
        subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][1]);
        subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][2]);
        subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][3]);
        subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][4]);
        subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][5]);
        subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][6]);
        subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][7]);
        _ublock128_dec_round(X, subkey);
    }
    // final subkey xor
    subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][0]);
    subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][1]);
    subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][2]);
    subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][3]);
    subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][4]);
    subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][5]);
    subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][6]);
    subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][7]);
    X[0]      = _mm256_xor_si256(X[0], subkey[0]);
    X[1]      = _mm256_xor_si256(X[1], subkey[1]);
    X[2]      = _mm256_xor_si256(X[2], subkey[2]);
    X[3]      = _mm256_xor_si256(X[3], subkey[3]);
    X[4]      = _mm256_xor_si256(X[4], subkey[4]);
    X[5]      = _mm256_xor_si256(X[5], subkey[5]);
    X[6]      = _mm256_xor_si256(X[6], subkey[6]);
    X[7]      = _mm256_xor_si256(X[7], subkey[7]);
    _ublock128data_store(out, X);
}

static void _ublock128256_enc_block_x16(
    const std::uint8_t bs_round_key[25][8][32],
    std::uint8_t       out[256],
    const std::uint8_t in[256])
{
    __m256i subkey[8];
    __m256i X[8];
    _ublock128data_load(X, in);
    for (int i = 0; i < 24; i++)
    {
        subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][0]);
        subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][1]);
        subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][2]);
        subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][3]);
        subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][4]);
        subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][5]);
        subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][6]);
        subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][7]);
        _ublock128_enc_round(X, subkey);
    }
    // final subkey xor
    subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][0]);
    subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][1]);
    subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][2]);
    subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][3]);
    subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][4]);
    subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][5]);
    subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][6]);
    subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][7]);
    X[0]      = _mm256_xor_si256(X[0], subkey[0]);
    X[1]      = _mm256_xor_si256(X[1], subkey[1]);
    X[2]      = _mm256_xor_si256(X[2], subkey[2]);
    X[3]      = _mm256_xor_si256(X[3], subkey[3]);
    X[4]      = _mm256_xor_si256(X[4], subkey[4]);
    X[5]      = _mm256_xor_si256(X[5], subkey[5]);
    X[6]      = _mm256_xor_si256(X[6], subkey[6]);
    X[7]      = _mm256_xor_si256(X[7], subkey[7]);
    _ublock128data_store(out, X);
}

static void _ublock128256_dec_block_x16(
    const std::uint8_t bs_round_key[25][8][32],
    std::uint8_t       out[256],
    const std::uint8_t in[256])
{
    __m256i subkey[8];
    __m256i X[8];
    _ublock128data_load(X, in);
    for (int i = 24; i >= 1; i--)
    {
        subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][0]);
        subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][1]);
        subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][2]);
        subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][3]);
        subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][4]);
        subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][5]);
        subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][6]);
        subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][7]);
        _ublock128_dec_round(X, subkey);
    }
    // final subkey xor
    subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][0]);
    subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][1]);
    subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][2]);
    subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][3]);
    subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][4]);
    subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][5]);
    subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][6]);
    subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][7]);
    X[0]      = _mm256_xor_si256(X[0], subkey[0]);
    X[1]      = _mm256_xor_si256(X[1], subkey[1]);
    X[2]      = _mm256_xor_si256(X[2], subkey[2]);
    X[3]      = _mm256_xor_si256(X[3], subkey[3]);
    X[4]      = _mm256_xor_si256(X[4], subkey[4]);
    X[5]      = _mm256_xor_si256(X[5], subkey[5]);
    X[6]      = _mm256_xor_si256(X[6], subkey[6]);
    X[7]      = _mm256_xor_si256(X[7], subkey[7]);
    _ublock128data_store(out, X);
}

static void _ublock256256_enc_block_x8(
    const std::uint8_t bs_round_key[25][8][32],
    std::uint8_t       out[256],
    const std::uint8_t in[256])
{
    __m256i subkey[8];
    __m256i X[8];
    _ublock256data_load(X, in);
    for (int i = 0; i < 24; i++)
    {
        subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][0]);
        subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][1]);
        subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][2]);
        subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][3]);
        subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][4]);
        subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][5]);
        subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][6]);
        subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][7]);
        _ublock256256_enc_round(X, subkey);
    }
    // final subkey xor
    subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][0]);
    subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][1]);
    subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][2]);
    subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][3]);
    subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][4]);
    subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][5]);
    subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][6]);
    subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[24][7]);
    X[0]      = _mm256_xor_si256(X[0], subkey[0]);
    X[1]      = _mm256_xor_si256(X[1], subkey[1]);
    X[2]      = _mm256_xor_si256(X[2], subkey[2]);
    X[3]      = _mm256_xor_si256(X[3], subkey[3]);
    X[4]      = _mm256_xor_si256(X[4], subkey[4]);
    X[5]      = _mm256_xor_si256(X[5], subkey[5]);
    X[6]      = _mm256_xor_si256(X[6], subkey[6]);
    X[7]      = _mm256_xor_si256(X[7], subkey[7]);
    _ublock256data_store(out, X);
}

static void _ublock256256_dec_block_x8(
    const std::uint8_t bs_round_key[25][8][32],
    std::uint8_t       out[256],
    const std::uint8_t in[256])
{
    __m256i subkey[8];
    __m256i X[8];
    _ublock256data_load(X, in);
    for (int i = 24; i >= 1; i--)
    {
        subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][0]);
        subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][1]);
        subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][2]);
        subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][3]);
        subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][4]);
        subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][5]);
        subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][6]);
        subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[i][7]);
        _ublock256256_dec_round(X, subkey);
    }
    // final subkey xor
    subkey[0] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][0]);
    subkey[1] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][1]);
    subkey[2] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][2]);
    subkey[3] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][3]);
    subkey[4] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][4]);
    subkey[5] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][5]);
    subkey[6] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][6]);
    subkey[7] = _mm256_loadu_si256((const __m256i *)bs_round_key[0][7]);
    X[0]      = _mm256_xor_si256(X[0], subkey[0]);
    X[1]      = _mm256_xor_si256(X[1], subkey[1]);
    X[2]      = _mm256_xor_si256(X[2], subkey[2]);
    X[3]      = _mm256_xor_si256(X[3], subkey[3]);
    X[4]      = _mm256_xor_si256(X[4], subkey[4]);
    X[5]      = _mm256_xor_si256(X[5], subkey[5]);
    X[6]      = _mm256_xor_si256(X[6], subkey[6]);
    X[7]      = _mm256_xor_si256(X[7], subkey[7]);
    _ublock256data_store(out, X);
}

// ========================================================

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************* UBLOCK CIPHER API ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

// ****************************************
// ********** uBlock 128/128 **************
// ****************************************

void ublock128128_enc_key_init(UBlock128128RoundKey *round_key,
                               const std::uint8_t    user_key[16]) noexcept
{
    uBlock_128128_KeySchedule(round_key->round_key, user_key);
    for (int i = 0; i < 17; i++)
    {
        _ublock128_bs_key_init(round_key->bs_round_key[i],
                               round_key->round_key[i]);
    }
}

void ublock128128_dec_key_init(UBlock128128RoundKey *round_key,
                               const std::uint8_t    user_key[16]) noexcept
{
    uBlock_128128_KeySchedule(round_key->round_key, user_key);
    for (int i = 0; i < 17; i++)
    {
        _ublock128_bs_key_init(round_key->bs_round_key[i],
                               round_key->round_key[i]);
    }
}

void ublock128128_enc_block(const UBlock128128RoundKey *round_key,
                            std::uint8_t                ciphertext[16],
                            const std::uint8_t          plaintext[16]) noexcept
{
    uBlock_128128_Encrypt(round_key->round_key, ciphertext, plaintext);
}

void ublock128128_dec_block(const UBlock128128RoundKey *round_key,
                            std::uint8_t                plaintext[16],
                            const std::uint8_t          ciphertext[16]) noexcept
{
    uBlock_128128_Decrypt(round_key->round_key, plaintext, ciphertext);
}

void ublock128128_enc_blocks(const UBlock128128RoundKey *round_key,
                             std::uint8_t               *ciphertext,
                             const std::uint8_t         *plaintext,
                             std::size_t                 block_num) noexcept
{
    while (block_num >= 16)
    {
        _ublock128128_enc_block_x16(round_key->bs_round_key, ciphertext,
                                    plaintext);
        ciphertext += 16 * 16, plaintext += 16 * 16, block_num -= 16;
    }
    while (block_num)
    {
        uBlock_128128_Encrypt(round_key->round_key, ciphertext, plaintext);
        ciphertext += 16, plaintext += 16, block_num--;
    }
}

void ublock128128_dec_blocks(const UBlock128128RoundKey *round_key,
                             std::uint8_t               *plaintext,
                             const std::uint8_t         *ciphertext,
                             std::size_t                 block_num) noexcept
{
    while (block_num >= 16)
    {
        _ublock128128_dec_block_x16(round_key->bs_round_key, plaintext,
                                    ciphertext);
        plaintext += 16 * 16, ciphertext += 16 * 16, block_num -= 16;
    }
    while (block_num)
    {
        uBlock_128128_Decrypt(round_key->round_key, plaintext, ciphertext);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** uBlock 128/256 **************
// ****************************************

void ublock128256_enc_key_init(UBlock128256RoundKey *round_key,
                               const std::uint8_t    user_key[32]) noexcept
{
    uBlock_128256_KeySchedule(round_key->round_key, user_key);
    for (int i = 0; i < 25; i++)
    {
        _ublock128_bs_key_init(round_key->bs_round_key[i],
                               round_key->round_key[i]);
    }
}

void ublock128256_dec_key_init(UBlock128256RoundKey *round_key,
                               const std::uint8_t    user_key[32]) noexcept
{
    uBlock_128256_KeySchedule(round_key->round_key, user_key);
    for (int i = 0; i < 25; i++)
    {
        _ublock128_bs_key_init(round_key->bs_round_key[i],
                               round_key->round_key[i]);
    }
}

void ublock128256_enc_block(const UBlock128256RoundKey *round_key,
                            std::uint8_t                ciphertext[16],
                            const std::uint8_t          plaintext[16]) noexcept
{
    uBlock_128256_Encrypt(round_key->round_key, ciphertext, plaintext);
}

void ublock128256_dec_block(const UBlock128256RoundKey *round_key,
                            std::uint8_t                plaintext[16],
                            const std::uint8_t          ciphertext[16]) noexcept
{
    uBlock_128256_Decrypt(round_key->round_key, plaintext, ciphertext);
}

void ublock128256_enc_blocks(const UBlock128256RoundKey *round_key,
                             std::uint8_t               *ciphertext,
                             const std::uint8_t         *plaintext,
                             std::size_t                 block_num) noexcept
{
    while (block_num >= 16)
    {
        _ublock128256_enc_block_x16(round_key->bs_round_key, ciphertext,
                                    plaintext);
        ciphertext += 16 * 16, plaintext += 16 * 16, block_num -= 16;
    }
    while (block_num)
    {
        uBlock_128256_Encrypt(round_key->round_key, ciphertext, plaintext);
        ciphertext += 16, plaintext += 16, block_num--;
    }
}

void ublock128256_dec_blocks(const UBlock128256RoundKey *round_key,
                             std::uint8_t               *plaintext,
                             const std::uint8_t         *ciphertext,
                             std::size_t                 block_num) noexcept
{
    while (block_num >= 16)
    {
        _ublock128256_dec_block_x16(round_key->bs_round_key, plaintext,
                                    ciphertext);
        plaintext += 16 * 16, ciphertext += 16 * 16, block_num -= 16;
    }
    while (block_num)
    {
        uBlock_128256_Decrypt(round_key->round_key, plaintext, ciphertext);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** uBlock 256/256 **************
// ****************************************

void ublock256256_enc_key_init(UBlock256256RoundKey *round_key,
                               const std::uint8_t    user_key[32]) noexcept
{
    uBlock_256256_KeySchedule(round_key->round_key, user_key);
    for (int i = 0; i < 25; i++)
    {
        _ublock256_bs_key_init(round_key->bs_round_key[i],
                               round_key->round_key[i]);
    }
}

void ublock256256_dec_key_init(UBlock256256RoundKey *round_key,
                               const std::uint8_t    user_key[32]) noexcept
{
    uBlock_256256_KeySchedule(round_key->round_key, user_key);
    for (int i = 0; i < 25; i++)
    {
        _ublock256_bs_key_init(round_key->bs_round_key[i],
                               round_key->round_key[i]);
    }
}

void ublock256256_enc_block(const UBlock256256RoundKey *round_key,
                            std::uint8_t                ciphertext[32],
                            const std::uint8_t          plaintext[32]) noexcept
{
    uBlock_256256_Encrypt(round_key->round_key, ciphertext, plaintext);
}

void ublock256256_dec_block(const UBlock256256RoundKey *round_key,
                            std::uint8_t                plaintext[32],
                            const std::uint8_t          ciphertext[32]) noexcept
{
    uBlock_256256_Decrypt(round_key->round_key, plaintext, ciphertext);
}

void ublock256256_enc_blocks(const UBlock256256RoundKey *round_key,
                             std::uint8_t               *ciphertext,
                             const std::uint8_t         *plaintext,
                             std::size_t                 block_num) noexcept
{
    while (block_num >= 8)
    {
        _ublock256256_enc_block_x8(round_key->bs_round_key, ciphertext,
                                   plaintext);
        ciphertext += 32 * 8, plaintext += 32 * 8, block_num -= 8;
    }
    while (block_num)
    {
        uBlock_256256_Encrypt(round_key->round_key, ciphertext, plaintext);
        ciphertext += 32, plaintext += 32, block_num--;
    }
}

void ublock256256_dec_blocks(const UBlock256256RoundKey *round_key,
                             std::uint8_t               *plaintext,
                             const std::uint8_t         *ciphertext,
                             std::size_t                 block_num) noexcept
{
    while (block_num >= 8)
    {
        _ublock256256_dec_block_x8(round_key->bs_round_key, plaintext,
                                   ciphertext);
        plaintext += 32 * 8, ciphertext += 32 * 8, block_num -= 8;
    }
    while (block_num)
    {
        uBlock_256256_Decrypt(round_key->round_key, plaintext, ciphertext);
        plaintext += 32, ciphertext += 32, block_num--;
    }
}

} // namespace gong25
} // namespace internal
} // namespace ublock

#endif
