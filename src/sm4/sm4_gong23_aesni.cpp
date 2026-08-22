#if defined(SUPPORT_SM4_GONG23_AESNI)

#include "sm4_gong23_aesni.h"

#include <immintrin.h>

#define MM_XOR2(a, b)             _mm_xor_si128(a, b)
#define MM_XOR3(a, b, c)          MM_XOR2(a, MM_XOR2(b, c))
#define MM_XOR4(a, b, c, d)       MM_XOR2(a, MM_XOR3(b, c, d))
#define MM_XOR5(a, b, c, d, e)    MM_XOR2(a, MM_XOR4(b, c, d, e))
#define MM_XOR6(a, b, c, d, e, f) MM_XOR2(a, MM_XOR5(b, c, d, e, f))

#define MM_PACK0_EPI32(a, b, c, d) \
    _mm_unpacklo_epi64(_mm_unpacklo_epi32(a, b), _mm_unpacklo_epi32(c, d))
#define MM_PACK1_EPI32(a, b, c, d) \
    _mm_unpackhi_epi64(_mm_unpacklo_epi32(a, b), _mm_unpacklo_epi32(c, d))
#define MM_PACK2_EPI32(a, b, c, d) \
    _mm_unpacklo_epi64(_mm_unpackhi_epi32(a, b), _mm_unpackhi_epi32(c, d))
#define MM_PACK3_EPI32(a, b, c, d) \
    _mm_unpackhi_epi64(_mm_unpackhi_epi32(a, b), _mm_unpackhi_epi32(c, d))

namespace sm4::internal::gong23_aesni {

static inline std::uint32_t MEM_LOAD32BE(const void *src)
{
    return ((std::uint32_t)(((std::uint8_t *)src)[0]) << 24) |
           ((std::uint32_t)(((std::uint8_t *)src)[1]) << 16) |
           ((std::uint32_t)(((std::uint8_t *)src)[2]) << 8) |
           ((std::uint32_t)(((std::uint8_t *)src)[3]) << 0);
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

static const std::uint8_t SM4_SBOX[256] = {
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
    std::uint32_t k[4], tmp;
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
        std::uint32_t tmp;                                             \
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
    // reverse, and store output as big endian
    MEM_STORE32BE(out, x[3]);
    MEM_STORE32BE(out + 4, x[2]);
    MEM_STORE32BE(out + 8, x[1]);
    MEM_STORE32BE(out + 12, x[0]);
}

static const std::uint8_t MATRIX_A_HIGH[16] = {
    0x00, 0xb8, 0x99, 0x21, 0xee, 0x56, 0x77, 0xcf,
    0x64, 0xdc, 0xfd, 0x45, 0x8a, 0x32, 0x13, 0xab,
};
static const std::uint8_t MATRIX_A_LOW[16] = {
    0x00, 0x58, 0xdb, 0x83, 0x06, 0x5e, 0xdd, 0x85,
    0x53, 0x0b, 0x88, 0xd0, 0x55, 0x0d, 0x8e, 0xd6,
};
static const std::uint8_t MATRIX_B_HIGH[16] = {
    0x00, 0x7f, 0x49, 0x36, 0x92, 0xed, 0xdb, 0xa4,
    0xfe, 0x81, 0xb7, 0xc8, 0x6c, 0x13, 0x25, 0x5a,
};
static const std::uint8_t MATRIX_B_LOW[16] = {
    0x00, 0x8a, 0x94, 0x1e, 0xe9, 0x63, 0x7d, 0xf7,
    0x52, 0xd8, 0xc6, 0x4c, 0xbb, 0x31, 0x2f, 0xa5,
};
static const std::uint8_t AES_INV_SHIFT_ROW[16] = {
    0x00, 0x0d, 0x0a, 0x07, 0x04, 0x01, 0x0e, 0x0b,
    0x08, 0x05, 0x02, 0x0f, 0x0c, 0x09, 0x06, 0x03,
};
static const std::uint8_t MATRIX_M_HIGH[16] = {
    0x00, 0x7a, 0x38, 0x42, 0x20, 0x5a, 0x18, 0x62,
    0x40, 0x3a, 0x78, 0x02, 0x60, 0x1a, 0x58, 0x22,
};
static const std::uint8_t MATRIX_M_LOW[16] = {
    0x00, 0xca, 0x77, 0xbd, 0x8b, 0x41, 0xfc, 0x36,
    0xd4, 0x1e, 0xa3, 0x69, 0x5f, 0x95, 0x28, 0xe2,
};
static const std::uint8_t INV_MATRIX_M_HIGH[16] = {
    0x00, 0x2e, 0x40, 0x6e, 0x80, 0xae, 0xc0, 0xee,
    0x7f, 0x51, 0x3f, 0x11, 0xff, 0xd1, 0xbf, 0x91,
};
static const std::uint8_t INV_MATRIX_M_LOW[16] = {
    0x00, 0x85, 0xb0, 0x35, 0xd9, 0x5c, 0x69, 0xec,
    0x4e, 0xcb, 0xfe, 0x7b, 0x97, 0x12, 0x27, 0xa2,
};

static void sm4_round_key_trans(std::uint32_t       out[32],
                                const std::uint32_t in[32])
{
    __m128i C1            = _mm_set1_epi8(0b00100011);
    __m128i and_mask      = _mm_set1_epi8(0x0F);
    __m128i matrix_m_high = _mm_loadu_si128((const __m128i *)MATRIX_M_HIGH);
    __m128i matrix_m_low  = _mm_loadu_si128((const __m128i *)MATRIX_M_LOW);
    __m128i rk0, rk1, t1, t2, t3, t4;
    for (int i = 0; i < (32 * 4) / 16; i += 2)
    {
        rk0 = _mm_loadu_si128((const __m128i *)in + i);
        rk1 = _mm_loadu_si128((const __m128i *)in + i + 1);
        t2  = _mm_srli_epi16(rk0, 4);
        t4  = _mm_srli_epi16(rk1, 4);
        t1  = _mm_and_si128(rk0, and_mask);
        t3  = _mm_and_si128(rk1, and_mask);
        t2  = _mm_and_si128(t2, and_mask);
        t4  = _mm_and_si128(t4, and_mask);
        rk0 = _mm_xor_si128(_mm_shuffle_epi8(matrix_m_high, t2),
                            _mm_shuffle_epi8(matrix_m_low, t1));
        rk1 = _mm_xor_si128(_mm_shuffle_epi8(matrix_m_high, t4),
                            _mm_shuffle_epi8(matrix_m_low, t3));
        rk0 = _mm_xor_si128(rk0, C1);
        rk1 = _mm_xor_si128(rk1, C1);
        _mm_storeu_si128((__m128i *)out + i, rk0);
        _mm_storeu_si128((__m128i *)out + i + 1, rk1);
    }
}

static void sm4_compute_block_x16(const std::uint32_t rk[32],
                                  std::uint8_t        out[16 * 16],
                                  const std::uint8_t  in[16 * 16])
{
    static const std::uint8_t PACK_SHUFFLE[16] = {
        0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15,
    };

    __m128i x[4][4];
    __m128i t[4], xa[4], xb[4], t1, t2;

    __m128i and_mask      = _mm_set1_epi8(0x0F);
    __m128i vindex        = _mm_loadu_si128((const __m128i *)PACK_SHUFFLE);
    __m128i matrix_m_high = _mm_loadu_si128((const __m128i *)MATRIX_M_HIGH);
    __m128i matrix_m_low  = _mm_loadu_si128((const __m128i *)MATRIX_M_LOW);
    __m128i inv_matrix_m_h =
        _mm_loadu_si128((const __m128i *)INV_MATRIX_M_HIGH);
    __m128i inv_matrix_m_l = _mm_loadu_si128((const __m128i *)INV_MATRIX_M_LOW);
    __m128i matrix_a_high  = _mm_loadu_si128((const __m128i *)MATRIX_A_HIGH);
    __m128i matrix_a_low   = _mm_loadu_si128((const __m128i *)MATRIX_A_LOW);
    __m128i matrix_b_high  = _mm_loadu_si128((const __m128i *)MATRIX_B_HIGH);
    __m128i matrix_b_low   = _mm_loadu_si128((const __m128i *)MATRIX_B_LOW);
    __m128i aes_i_shift_r = _mm_loadu_si128((const __m128i *)AES_INV_SHIFT_ROW);
    __m128i C2            = _mm_set1_epi8(0b00111101);

    for (int j = 0; j < 4; j++)
    {
        // bytes_idx(block_idx)
        // load: [0(0), 1(0), 2(0), 3(0), ..., 12(0), 13(0), 14(0), 15(0)]
        // load: [0(1), 1(1), 2(1), 3(1), ..., 12(1), 13(1), 14(1), 15(1)]
        // load: [0(2), 1(2), 2(2), 3(2), ..., 12(2), 13(2), 14(2), 15(2)]
        // load: [0(3), 1(3), 2(3), 3(3), ..., 12(3), 13(3), 14(3), 15(3)]
        x[0][j] = _mm_loadu_si128((const __m128i *)(in + 16 * (4 * j + 0)));
        x[1][j] = _mm_loadu_si128((const __m128i *)(in + 16 * (4 * j + 1)));
        x[2][j] = _mm_loadu_si128((const __m128i *)(in + 16 * (4 * j + 2)));
        x[3][j] = _mm_loadu_si128((const __m128i *)(in + 16 * (4 * j + 3)));
        // unpacklo_epi32: [0-3(0), 0-3(1), 4-7(0), 4-7(1)]
        // unpacklo_epi32: [0-3(2), 0-3(3), 4-7(2), 4-7(3)]
        // unpackhi_epi32: [8-11(0), 8-11(1), 12-15(0), 12-15(1)]
        // unpackhi_epi32: [8-11(2), 8-11(3), 12-15(2), 12-15(3)]
        t[0] = _mm_unpacklo_epi32(x[0][j], x[1][j]);
        t[1] = _mm_unpacklo_epi32(x[2][j], x[3][j]);
        t[2] = _mm_unpackhi_epi32(x[0][j], x[1][j]);
        t[3] = _mm_unpackhi_epi32(x[2][j], x[3][j]);
        // unpacklo_epi64: [0-3(0), 0-3(1), 0-3(2), 0-3(3)]
        // unpackhi_epi64: [4-7(0), 4-7(1), 4-7(2), 4-7(3)]
        // unpacklo_epi64: [8-11(0), 8-11(1), 8-11(2), 8-11(3)]
        // unpackhi_epi64: [12-15(0), 12-15(1), 12-15(2), 12-15(3)]
        x[0][j] = _mm_unpacklo_epi64(t[0], t[1]);
        x[1][j] = _mm_unpackhi_epi64(t[0], t[1]);
        x[2][j] = _mm_unpacklo_epi64(t[2], t[3]);
        x[3][j] = _mm_unpackhi_epi64(t[2], t[3]);
    }

    for (int j = 0; j < 4; j++)
    {
        // shuffle_epi8: [0(0-3), 1(0-3), 2(0-3), 3(0-3)]
        // shuffle_epi8: [0(4-7), 1(4-7), 2(4-7), 3(4-7)]
        // shuffle_epi8: [0(8-11), 1(8-11), 2(8-11), 3(8-11)]
        // shuffle_epi8: [0(12-15), 1(12-15), 2(12-15), 3(12-15)]
        x[j][0] = _mm_shuffle_epi8(x[j][0], vindex);
        x[j][1] = _mm_shuffle_epi8(x[j][1], vindex);
        x[j][2] = _mm_shuffle_epi8(x[j][2], vindex);
        x[j][3] = _mm_shuffle_epi8(x[j][3], vindex);
        // unpacklo_epi32: [0(0-7),1(0-7)]
        // unpacklo_epi32: [0(8-11),1(12-15)]
        // unpacklo_epi32: [2(0-7),3(0-7)]
        // unpacklo_epi32: [2(8-11),3(8-11)]
        t[0] = _mm_unpacklo_epi32(x[j][0], x[j][1]);
        t[1] = _mm_unpacklo_epi32(x[j][2], x[j][3]);
        t[2] = _mm_unpackhi_epi32(x[j][0], x[j][1]);
        t[3] = _mm_unpackhi_epi32(x[j][2], x[j][3]);

        x[j][0] = _mm_unpacklo_epi64(t[0], t[1]);
        x[j][1] = _mm_unpackhi_epi64(t[0], t[1]);
        x[j][2] = _mm_unpacklo_epi64(t[2], t[3]);
        x[j][3] = _mm_unpackhi_epi64(t[2], t[3]);

        t2      = _mm_srli_epi16(x[j][0], 4);
        t1      = _mm_and_si128(x[j][0], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][0] = _mm_xor_si128(_mm_shuffle_epi8(matrix_m_high, t2),
                                _mm_shuffle_epi8(matrix_m_low, t1));

        t2      = _mm_srli_epi16(x[j][1], 4);
        t1      = _mm_and_si128(x[j][1], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][1] = _mm_xor_si128(_mm_shuffle_epi8(matrix_m_high, t2),
                                _mm_shuffle_epi8(matrix_m_low, t1));

        t2      = _mm_srli_epi16(x[j][2], 4);
        t1      = _mm_and_si128(x[j][2], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][2] = _mm_xor_si128(_mm_shuffle_epi8(matrix_m_high, t2),
                                _mm_shuffle_epi8(matrix_m_low, t1));

        t2      = _mm_srli_epi16(x[j][3], 4);
        t1      = _mm_and_si128(x[j][3], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][3] = _mm_xor_si128(_mm_shuffle_epi8(matrix_m_high, t2),
                                _mm_shuffle_epi8(matrix_m_low, t1));
    }

    for (int i = 0; i < 32; i++)
    {
        // t = rk[i] ^ x[1] ^ x[2] ^ x[3]
        t[0] = _mm_set1_epi8((rk[i + 0] >> 24) & 0xFF);
        t[1] = _mm_set1_epi8((rk[i + 0] >> 16) & 0xFF);
        t[2] = _mm_set1_epi8((rk[i + 0] >> 8) & 0xFF);
        t[3] = _mm_set1_epi8((rk[i + 0] >> 0) & 0xFF);

        t[0] = MM_XOR4(x[1][0], x[2][0], x[3][0], t[0]);
        t[1] = MM_XOR4(x[1][1], x[2][1], x[3][1], t[1]);
        t[2] = MM_XOR4(x[1][2], x[2][2], x[3][2], t[2]);
        t[3] = MM_XOR4(x[1][3], x[2][3], x[3][3], t[3]);

        t[0] = _mm_shuffle_epi8(t[0], aes_i_shift_r);
        t[1] = _mm_shuffle_epi8(t[1], aes_i_shift_r);
        t[2] = _mm_shuffle_epi8(t[2], aes_i_shift_r);
        t[3] = _mm_shuffle_epi8(t[3], aes_i_shift_r);
        t[0] = _mm_aesenclast_si128(t[0], C2);
        t[1] = _mm_aesenclast_si128(t[1], C2);
        t[2] = _mm_aesenclast_si128(t[2], C2);
        t[3] = _mm_aesenclast_si128(t[3], C2);

        for (int j = 0; j < 4; j++)
        {
            t2    = _mm_srli_epi16(t[j], 4);
            t1    = _mm_and_si128(t[j], and_mask);
            t2    = _mm_and_si128(t2, and_mask);
            xa[j] = _mm_xor_si128(_mm_shuffle_epi8(matrix_a_high, t2),
                                  _mm_shuffle_epi8(matrix_a_low, t1));
            xb[j] = _mm_xor_si128(_mm_shuffle_epi8(matrix_b_high, t2),
                                  _mm_shuffle_epi8(matrix_b_low, t1));
        }
        t[0] = MM_XOR4(xa[0], xb[1], xb[2], MM_XOR2(xa[3], xb[3]));
        t[1] = MM_XOR4(MM_XOR2(xa[0], xb[0]), xa[1], xb[2], xb[3]);
        t[2] = MM_XOR4(xb[0], MM_XOR2(xa[1], xb[1]), xa[2], xb[3]);
        t[3] = MM_XOR4(xb[0], xb[1], MM_XOR2(xa[2], xb[2]), xa[3]);

        // x[4] = x[0] ^ t
        t[0] = MM_XOR2(x[0][0], t[0]);
        t[1] = MM_XOR2(x[0][1], t[1]);
        t[2] = MM_XOR2(x[0][2], t[2]);
        t[3] = MM_XOR2(x[0][3], t[3]);

        x[0][0] = x[1][0], x[0][1] = x[1][1];
        x[0][2] = x[1][2], x[0][3] = x[1][3];

        x[1][0] = x[2][0], x[1][1] = x[2][1];
        x[1][2] = x[2][2], x[1][3] = x[2][3];

        x[2][0] = x[3][0], x[2][1] = x[3][1];
        x[2][2] = x[3][2], x[2][3] = x[3][3];

        x[3][0] = t[0], x[3][1] = t[1];
        x[3][2] = t[2], x[3][3] = t[3];
    }

    for (int j = 0; j < 4; j++)
    {
        t2      = _mm_srli_epi16(x[j][0], 4);
        t1      = _mm_and_si128(x[j][0], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][0] = _mm_xor_si128(_mm_shuffle_epi8(inv_matrix_m_h, t2),
                                _mm_shuffle_epi8(inv_matrix_m_l, t1));

        t2      = _mm_srli_epi16(x[j][1], 4);
        t1      = _mm_and_si128(x[j][1], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][1] = _mm_xor_si128(_mm_shuffle_epi8(inv_matrix_m_h, t2),
                                _mm_shuffle_epi8(inv_matrix_m_l, t1));

        t2      = _mm_srli_epi16(x[j][2], 4);
        t1      = _mm_and_si128(x[j][2], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][2] = _mm_xor_si128(_mm_shuffle_epi8(inv_matrix_m_h, t2),
                                _mm_shuffle_epi8(inv_matrix_m_l, t1));

        t2      = _mm_srli_epi16(x[j][3], 4);
        t1      = _mm_and_si128(x[j][3], and_mask);
        t2      = _mm_and_si128(t2, and_mask);
        x[j][3] = _mm_xor_si128(_mm_shuffle_epi8(inv_matrix_m_h, t2),
                                _mm_shuffle_epi8(inv_matrix_m_l, t1));

        t[0] = _mm_unpacklo_epi32(x[j][0], x[j][1]);
        t[1] = _mm_unpacklo_epi32(x[j][2], x[j][3]);
        t[2] = _mm_unpackhi_epi32(x[j][0], x[j][1]);
        t[3] = _mm_unpackhi_epi32(x[j][2], x[j][3]);

        x[j][0] = _mm_unpacklo_epi64(t[0], t[1]);
        x[j][1] = _mm_unpackhi_epi64(t[0], t[1]);
        x[j][2] = _mm_unpacklo_epi64(t[2], t[3]);
        x[j][3] = _mm_unpackhi_epi64(t[2], t[3]);
    }

    for (int j = 0; j < 4; j++)
    {
        x[0][j] = _mm_shuffle_epi8(x[0][j], vindex);
        x[1][j] = _mm_shuffle_epi8(x[1][j], vindex);
        x[2][j] = _mm_shuffle_epi8(x[2][j], vindex);
        x[3][j] = _mm_shuffle_epi8(x[3][j], vindex);

        t[0] = _mm_unpacklo_epi32(x[3][j], x[2][j]);
        t[1] = _mm_unpacklo_epi32(x[1][j], x[0][j]);
        t[2] = _mm_unpackhi_epi32(x[3][j], x[2][j]);
        t[3] = _mm_unpackhi_epi32(x[1][j], x[0][j]);

        x[0][j] = _mm_unpacklo_epi64(t[0], t[1]);
        x[1][j] = _mm_unpackhi_epi64(t[0], t[1]);
        x[2][j] = _mm_unpacklo_epi64(t[2], t[3]);
        x[3][j] = _mm_unpackhi_epi64(t[2], t[3]);

        _mm_storeu_si128((__m128i *)(out + (4 * j + 0) * 16), x[0][j]);
        _mm_storeu_si128((__m128i *)(out + (4 * j + 1) * 16), x[1][j]);
        _mm_storeu_si128((__m128i *)(out + (4 * j + 2) * 16), x[2][j]);
        _mm_storeu_si128((__m128i *)(out + (4 * j + 3) * 16), x[3][j]);
    }
}

// ==============================================

void sm4_enc_key_init(SM4Context *ctx, const std::uint8_t user_key[16]) noexcept
{
    sm4_key_init(ctx->round_key, user_key, 1);
    sm4_round_key_trans(ctx->trans_rk, ctx->round_key);
}

void sm4_dec_key_init(SM4Context *ctx, const std::uint8_t user_key[16]) noexcept
{
    sm4_key_init(ctx->round_key, user_key, 0);
    sm4_round_key_trans(ctx->trans_rk, ctx->round_key);
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
    while (block_num >= 16)
    {
        sm4_compute_block_x16(ctx->trans_rk, ciphertext, plaintext);
        plaintext += 16 * 16;
        ciphertext += 16 * 16;
        block_num -= 16;
    }
    while (block_num)
    {
        sm4_compute_block(ctx->round_key, ciphertext, plaintext);
        plaintext += 16;
        ciphertext += 16;
        block_num--;
    }
}

void sm4_dec_blocks(const SM4Context   *ctx,
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept
{
    while (block_num >= 16)
    {
        sm4_compute_block_x16(ctx->trans_rk, plaintext, ciphertext);
        plaintext += 16 * 16;
        ciphertext += 16 * 16;
        block_num -= 16;
    }
    while (block_num)
    {
        sm4_compute_block(ctx->round_key, plaintext, ciphertext);
        plaintext += 16;
        ciphertext += 16;
        block_num--;
    }
}

} // namespace sm4::internal::gong23_aesni

#endif
