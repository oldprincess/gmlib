/**
 * part of the code is "derived from
 * https://sfjs.cacrnet.org.cn/site/term/list_76_1.html"
 *
 * WU W L, ZHANG L, ZHENG Y F, LI L C. The block cipher uBlock[J]. Journal of
 * Cryptologic Research, 2019, 6(6): 690-703.
 */
#if defined(CPU_FLAG_SSSE3)
#include <gmlib/ublock/internal/ublock_standard.h>
#include <immintrin.h>

namespace ublock::internal::standard {

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

static void uBlock_128128_KeySchedule(std::uint8_t       sub_key[17][32],
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

    _mm_storeu_si128((__m128i *)sub_key[0], state1);
    _mm_storeu_si128((__m128i *)(sub_key[0] + 16), state2);

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

        _mm_storeu_si128((__m128i *)sub_key[i], state1);
        _mm_storeu_si128((__m128i *)(sub_key[i] + 16), state2);
    }
}

static void uBlock_128128_Encrypt(const std::uint8_t sub_key[17][32],
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

    state2 = _mm_loadu_si128((__m128i *)plaintext);
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
        k      = _mm_loadu_si128((__m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_loadu_si128((__m128i *)(sub_key[i] + 16));
        state2 = _mm_xor_si128(state2, k);

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

    k      = _mm_loadu_si128((__m128i *)sub_key[16]);
    state1 = _mm_xor_si128(state1, k);
    k      = _mm_loadu_si128((__m128i *)(sub_key[16] + 16));
    state2 = _mm_xor_si128(state2, k);

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

static void uBlock_128128_Decrypt(const std::uint8_t sub_key[17][32],
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

    state2 = _mm_loadu_si128((__m128i *)ciphertext);
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
        k      = _mm_loadu_si128((__m128i *)sub_key[i]);
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_loadu_si128((__m128i *)(sub_key[i] + 16));
        state2 = _mm_xor_si128(state2, k);

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

    k      = _mm_loadu_si128((__m128i *)sub_key[0]);
    state1 = _mm_xor_si128(state1, k);
    k      = _mm_loadu_si128((__m128i *)(sub_key[0] + 16));
    state2 = _mm_xor_si128(state2, k);

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

static void uBlock_128256_KeySchedule(std::uint8_t       sub_key[25][32],
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

    state2 = _mm_loadu_si128((__m128i *)user_key);
    state1 = _mm_srli_epi16(state2, 4);
    state1 = _mm_and_si128(state1, con);
    state2 = _mm_and_si128(state2, con);
    t1     = _mm_shuffle_epi8(state1, c1);
    t2     = _mm_shuffle_epi8(state2, c2);
    t3     = _mm_shuffle_epi8(state1, c3);
    t4     = _mm_shuffle_epi8(state2, c4);
    state1 = _mm_xor_si128(t1, t2);
    state2 = _mm_xor_si128(t3, t4);

    state4 = _mm_loadu_si128((__m128i *)(user_key + 16));
    state3 = _mm_srli_epi16(state4, 4);
    state3 = _mm_and_si128(state3, con);
    state4 = _mm_and_si128(state4, con);
    t1     = _mm_shuffle_epi8(state3, c1);
    t2     = _mm_shuffle_epi8(state4, c2);
    t3     = _mm_shuffle_epi8(state3, c3);
    t4     = _mm_shuffle_epi8(state4, c4);
    state3 = _mm_xor_si128(t1, t2);
    state4 = _mm_xor_si128(t3, t4);

    _mm_storeu_si128((__m128i *)sub_key[0], state1);
    _mm_storeu_si128((__m128i *)(sub_key[0] + 16), state2);

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

        _mm_storeu_si128((__m128i *)sub_key[i], state1);
        _mm_storeu_si128((__m128i *)(sub_key[i] + 16), state2);
    }

    return;
}

static void uBlock_128256_Encrypt(const std::uint8_t sub_key[25][32],
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
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 16));
        state2 = _mm_xor_si128(state2, k);

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
    state1 = _mm_xor_si128(state1, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[24] + 16));
    state2 = _mm_xor_si128(state2, k);

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

static void uBlock_128256_Decrypt(const std::uint8_t sub_key[25][32],
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
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 16));
        state2 = _mm_xor_si128(state2, k);

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
    state1 = _mm_xor_si128(state1, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[0] + 16));
    state2 = _mm_xor_si128(state2, k);

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

static void uBlock_256256_KeySchedule(std::uint8_t       sub_key[25][64],
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

    _mm_storeu_si128((__m128i *)sub_key[0], state1);
    _mm_storeu_si128((__m128i *)(sub_key[0] + 16), state2);
    _mm_storeu_si128((__m128i *)(sub_key[0] + 32), state3);
    _mm_storeu_si128((__m128i *)(sub_key[0] + 48), state4);

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

        _mm_storeu_si128((__m128i *)sub_key[i], state1);
        _mm_storeu_si128((__m128i *)(sub_key[i] + 16), state2);
        _mm_storeu_si128((__m128i *)(sub_key[i] + 32), state3);
        _mm_storeu_si128((__m128i *)(sub_key[i] + 48), state4);
    }

    return;
}

static void uBlock_256256_Encrypt(const std::uint8_t  sub_key[25][64],
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
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 16));
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 32));
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 48));
        state4 = _mm_xor_si128(state4, k);

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
    state1 = _mm_xor_si128(state1, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[24] + 16));
    state2 = _mm_xor_si128(state2, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[24] + 32));
    state3 = _mm_xor_si128(state3, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[24] + 48));
    state4 = _mm_xor_si128(state4, k);

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

static void uBlock_256256_Decrypt(const std::uint8_t  sub_key[25][64],
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
        state1 = _mm_xor_si128(state1, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 16));
        state2 = _mm_xor_si128(state2, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 32));
        state3 = _mm_xor_si128(state3, k);
        k      = _mm_loadu_si128((const __m128i *)(sub_key[i] + 48));
        state4 = _mm_xor_si128(state4, k);

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
    state1 = _mm_xor_si128(state1, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[0] + 16));
    state2 = _mm_xor_si128(state2, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[0] + 32));
    state3 = _mm_xor_si128(state3, k);
    k      = _mm_loadu_si128((const __m128i *)(sub_key[0] + 48));
    state4 = _mm_xor_si128(state4, k);

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

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************* UBLOCK CIPHER API ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

// ****************************************
// ********** uBlock 128/128 **************
// ****************************************

void ublock128128_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept
{
    uBlock_128128_KeySchedule(ctx->m.sub_key128128, user_key);
}

void ublock128128_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept
{
    uBlock_128128_KeySchedule(ctx->m.sub_key128128, user_key);
}

void ublock128128_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept
{
    uBlock_128128_Encrypt(ctx->m.sub_key128128, ciphertext, plaintext);
}

void ublock128128_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept
{
    uBlock_128128_Decrypt(ctx->m.sub_key128128, plaintext, ciphertext);
}

void ublock128128_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        uBlock_128128_Encrypt(ctx->m.sub_key128128, ciphertext, plaintext);
        ciphertext += 16, plaintext += 16, block_num--;
    }
}

void ublock128128_dec_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        uBlock_128128_Decrypt(ctx->m.sub_key128128, plaintext, ciphertext);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** uBlock 128/256 **************
// ****************************************

void ublock128256_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    uBlock_128256_KeySchedule(ctx->m.sub_key128256, user_key);
}

void ublock128256_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    uBlock_128256_KeySchedule(ctx->m.sub_key128256, user_key);
}

void ublock128256_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept
{
    uBlock_128256_Encrypt(ctx->m.sub_key128256, ciphertext, plaintext);
}

void ublock128256_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept
{
    uBlock_128256_Decrypt(ctx->m.sub_key128256, plaintext, ciphertext);
}

void ublock128256_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        uBlock_128256_Encrypt(ctx->m.sub_key128256, ciphertext, plaintext);
        ciphertext += 16, plaintext += 16, block_num--;
    }
}

void ublock128256_dec_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        uBlock_128256_Decrypt(ctx->m.sub_key128256, plaintext, ciphertext);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** uBlock 256/256 **************
// ****************************************

void ublock256256_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    uBlock_256256_KeySchedule(ctx->m.sub_key256256, user_key);
}

void ublock256256_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    uBlock_256256_KeySchedule(ctx->m.sub_key256256, user_key);
}

void ublock256256_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[32],
                            const std::uint8_t plaintext[32]) noexcept
{
    uBlock_256256_Encrypt(ctx->m.sub_key256256, ciphertext, plaintext);
}

void ublock256256_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[32],
                            const std::uint8_t ciphertext[32]) noexcept
{
    uBlock_256256_Decrypt(ctx->m.sub_key256256, plaintext, ciphertext);
}

void ublock256256_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        uBlock_256256_Encrypt(ctx->m.sub_key256256, ciphertext, plaintext);
        ciphertext += 32, plaintext += 32, block_num--;
    }
}

void ublock256256_dec_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        uBlock_256256_Decrypt(ctx->m.sub_key256256, plaintext, ciphertext);
        plaintext += 32, ciphertext += 32, block_num--;
    }
}
}; // namespace ublock::internal::standard
#endif