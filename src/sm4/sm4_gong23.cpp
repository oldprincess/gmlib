#include "sm4_gong23.h"

#if defined(SM4_IMPL_GONG23)

#include <immintrin.h>

#pragma region "SM4 GFNI"

namespace sm4::internal::gong23::gfni {

static uint8_t Matrix_A1[64] = {
    0x0d,                                           // 0, 0, 0, 0, 1, 1, 0, 1
    0x9b,                                           // 1, 0, 0, 1, 1, 0, 1, 1
    0x72,                                           // 0, 1, 1, 1, 0, 0, 1, 0
    0x3a,                                           // 0, 0, 1, 1, 1, 0, 1, 0
    0x35,                                           // 0, 0, 1, 1, 0, 1, 0, 1
    0x0a,                                           // 0, 0, 0, 0, 1, 0, 1, 0
    0x17,                                           // 0, 0, 0, 1, 0, 1, 1, 1
    0x06,                                           // 0, 0, 0, 0, 0, 1, 1, 0
    0x0d, 0x9b, 0x72, 0x3a, 0x35, 0x0a, 0x17, 0x06, //
    0x0d, 0x9b, 0x72, 0x3a, 0x35, 0x0a, 0x17, 0x06, //
    0x0d, 0x9b, 0x72, 0x3a, 0x35, 0x0a, 0x17, 0x06, //
    0x0d, 0x9b, 0x72, 0x3a, 0x35, 0x0a, 0x17, 0x06, //
    0x0d, 0x9b, 0x72, 0x3a, 0x35, 0x0a, 0x17, 0x06, //
    0x0d, 0x9b, 0x72, 0x3a, 0x35, 0x0a, 0x17, 0x06, //
    0x0d, 0x9b, 0x72, 0x3a, 0x35, 0x0a, 0x17, 0x06, //
};

// A1^-1
static uint8_t Matrix_A1_inv[64] = {
    0x47,                                           // 0, 1, 0, 0, 0, 1, 1, 1
    0xac,                                           // 1, 0, 1, 0, 1, 1, 0, 0
    0x92,                                           // 1, 0, 0, 1, 0, 0, 1, 0
    0x86,                                           // 1, 0, 0, 0, 0, 1, 1, 0
    0x9c,                                           // 1, 0, 0, 1, 1, 1, 0, 0
    0x99,                                           // 1, 0, 0, 1, 1, 0, 0, 1
    0x98,                                           // 1, 0, 0, 1, 1, 0, 0, 0
    0x85,                                           // 1, 0, 0, 0, 0, 1, 0, 1
    0x47, 0xac, 0x92, 0x86, 0x9c, 0x99, 0x98, 0x85, //
    0x47, 0xac, 0x92, 0x86, 0x9c, 0x99, 0x98, 0x85, //
    0x47, 0xac, 0x92, 0x86, 0x9c, 0x99, 0x98, 0x85, //
    0x47, 0xac, 0x92, 0x86, 0x9c, 0x99, 0x98, 0x85, //
    0x47, 0xac, 0x92, 0x86, 0x9c, 0x99, 0x98, 0x85, //
    0x47, 0xac, 0x92, 0x86, 0x9c, 0x99, 0x98, 0x85, //
    0x47, 0xac, 0x92, 0x86, 0x9c, 0x99, 0x98, 0x85, //
};

#define Matrix_C1 0b00100011 // [0, 0, 1, 0, 0, 0, 1, 1]^T

static uint8_t Matrix_LA[64] = {
    0xbe,                                           // 1, 0, 1, 1, 1, 1, 1, 0
    0x19,                                           // 0, 0, 0, 1, 1, 0, 0, 1
    0x9b,                                           // 1, 0, 0, 1, 1, 0, 1, 1
    0xbc,                                           // 1, 0, 1, 1, 1, 1, 0, 0
    0x4f,                                           // 0, 1, 0, 0, 1, 1, 1, 1
    0x43,                                           // 0, 1, 0, 0, 0, 0, 1, 1
    0xd7,                                           // 1, 1, 0, 1, 0, 1, 1, 1
    0x52,                                           // 0, 1, 0, 1, 0, 0, 1, 0
    0xbe, 0x19, 0x9b, 0xbc, 0x4f, 0x43, 0xd7, 0x52, //
    0xbe, 0x19, 0x9b, 0xbc, 0x4f, 0x43, 0xd7, 0x52, //
    0xbe, 0x19, 0x9b, 0xbc, 0x4f, 0x43, 0xd7, 0x52, //
    0xbe, 0x19, 0x9b, 0xbc, 0x4f, 0x43, 0xd7, 0x52, //
    0xbe, 0x19, 0x9b, 0xbc, 0x4f, 0x43, 0xd7, 0x52, //
    0xbe, 0x19, 0x9b, 0xbc, 0x4f, 0x43, 0xd7, 0x52, //
    0xbe, 0x19, 0x9b, 0xbc, 0x4f, 0x43, 0xd7, 0x52, //
};

static uint8_t Matrix_LB[64] = {
    0x51,                                           // 0, 1, 0, 1, 0, 0, 0, 1
    0x91,                                           // 1, 0, 0, 1, 0, 0, 0, 1
    0x20,                                           // 0, 0, 1, 0, 0, 0, 0, 0
    0xf7,                                           // 1, 1, 1, 1, 0, 1, 1, 1
    0xef,                                           // 1, 1, 1, 0, 1, 1, 1, 1
    0x04,                                           // 0, 0, 0, 0, 0, 1, 0, 0
    0xe5,                                           // 1, 1, 1, 0, 0, 1, 0, 1
    0xe6,                                           // 1, 1, 1, 0, 0, 1, 1, 0
    0x51, 0x91, 0x20, 0xf7, 0xef, 0x04, 0xe5, 0xe6, //
    0x51, 0x91, 0x20, 0xf7, 0xef, 0x04, 0xe5, 0xe6, //
    0x51, 0x91, 0x20, 0xf7, 0xef, 0x04, 0xe5, 0xe6, //
    0x51, 0x91, 0x20, 0xf7, 0xef, 0x04, 0xe5, 0xe6, //
    0x51, 0x91, 0x20, 0xf7, 0xef, 0x04, 0xe5, 0xe6, //
    0x51, 0x91, 0x20, 0xf7, 0xef, 0x04, 0xe5, 0xe6, //
    0x51, 0x91, 0x20, 0xf7, 0xef, 0x04, 0xe5, 0xe6, //
};

// LD = LA + LB, never use
static uint8_t Matrix_LD[64] = {
    0xef,                                           // 1, 1, 1, 0, 1, 1, 1, 1
    0x88,                                           // 1, 0, 0, 0, 1, 0, 0, 0
    0xbb,                                           // 1, 0, 1, 1, 1, 0, 1, 1
    0x4b,                                           // 0, 1, 0, 0, 1, 0, 1, 1
    0xa0,                                           // 1, 0, 1, 0, 0, 0, 0, 0
    0x47,                                           // 0, 1, 0, 0, 0, 1, 1, 1
    0x32,                                           // 0, 0, 1, 1, 0, 0, 1, 0
    0xb4,                                           // 1, 0, 1, 1, 0, 1, 0, 0
    0xef, 0x88, 0xbb, 0x4b, 0xa0, 0x47, 0x32, 0xb4, //
    0xef, 0x88, 0xbb, 0x4b, 0xa0, 0x47, 0x32, 0xb4, //
    0xef, 0x88, 0xbb, 0x4b, 0xa0, 0x47, 0x32, 0xb4, //
    0xef, 0x88, 0xbb, 0x4b, 0xa0, 0x47, 0x32, 0xb4, //
    0xef, 0x88, 0xbb, 0x4b, 0xa0, 0x47, 0x32, 0xb4, //
    0xef, 0x88, 0xbb, 0x4b, 0xa0, 0x47, 0x32, 0xb4, //
    0xef, 0x88, 0xbb, 0x4b, 0xa0, 0x47, 0x32, 0xb4, //
};

#define Matrix_L_C2 0b11000010 // [1, 1, 0, 0, 0, 0, 1, 0]^T

static uint8_t Shuffle_Endian[64] = {
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, //
};

static uint8_t Reshape_epi8[64] = {
    0, 4, 8,  12,                                          //
    1, 5, 9,  13,                                          //
    2, 6, 10, 14,                                          //
    3, 7, 11, 15,                                          //
    0, 4, 8,  12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, //
    0, 4, 8,  12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, //
    0, 4, 8,  12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, //
};

static uint8_t Shuffle_ROTL24[64] = {
    1,  2,  3,  0,                                            //
    5,  6,  7,  4,                                            //
    9,  10, 11, 8,                                            //
    13, 14, 15, 12,                                           //
    1,  2,  3,  0,  5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12, //
    1,  2,  3,  0,  5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12, //
    1,  2,  3,  0,  5, 6, 7, 4, 9, 10, 11, 8, 13, 14, 15, 12, //
};

static uint8_t Shuffle_ROTL16[64] = {
    2,  3,  0,  1,                                            //
    6,  7,  4,  5,                                            //
    10, 11, 8,  9,                                            //
    14, 15, 12, 13,                                           //
    2,  3,  0,  1,  6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13, //
    2,  3,  0,  1,  6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13, //
    2,  3,  0,  1,  6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13, //
};

static uint8_t Shuffle_ROTL8[64] = {
    3,  0,  1,  2,                                            //
    7,  4,  5,  6,                                            //
    11, 8,  9,  10,                                           //
    15, 12, 13, 14,                                           //
    3,  0,  1,  2,  7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
    3,  0,  1,  2,  7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
    3,  0,  1,  2,  7, 4, 5, 6, 11, 8, 9, 10, 15, 12, 13, 14, //
};

#define vector __m512i

#define VECTOR_LOAD(P)     _mm512_loadu_si512((const vector *)(P))
#define VECTOR_STORE(P, B) _mm512_storeu_si512((vector *)(P), B)

#define PACK_HI_EPI32 _mm512_unpackhi_epi32
#define PACK_LO_EPI32 _mm512_unpacklo_epi32
#define PACK_HI_EPI64 _mm512_unpackhi_epi64
#define PACK_LO_EPI64 _mm512_unpacklo_epi64

#define XOR_EPI32              _mm512_xor_si512
#define XOR3_EPI32(a, b, c)    _mm512_ternarylogic_epi32(a, b, c, 150)
#define XOR4_EPI32(a, b, c, d) XOR3_EPI32(a, b, XOR_EPI32(c, d))

// #define XOR3_EPI32(a, b, c) XOR_EPI32(XOR_EPI32(a, b), c)

#define GF2_AFFINE_INV _mm512_gf2p8affineinv_epi64_epi8
#define GF2_AFFINE     _mm512_gf2p8affine_epi64_epi8

#define VECTOR_SET1_EPI8    _mm512_set1_epi8
#define VECTOR_SET1_EPI32   _mm512_set1_epi32
#define VECTOR_SHUFFLE_EPI8 _mm512_shuffle_epi8
#define ROTL_EPI32          _mm512_rol_epi32
// out = A1 * rk + C1
static inline void sm4_gfni_v2_trans_key(std::uint32_t       *out,
                                         const std::uint32_t *rk)
{
    vector A1 = VECTOR_LOAD(Matrix_A1);
    for (int i = 0; i < 32 * 4; i += sizeof(vector))
    {
        vector t = VECTOR_LOAD((uint8_t *)rk + i);
        t        = GF2_AFFINE(t, A1, (Matrix_C1));
        VECTOR_STORE((uint8_t *)out + i, t);
    }
}

#define PACK_0_EPI32(x0, x1, x2, x3) \
    PACK_HI_EPI64(PACK_HI_EPI32(x3, x2), PACK_HI_EPI32(x1, x0))
#define PACK_1_EPI32(x0, x1, x2, x3) \
    PACK_LO_EPI64(PACK_HI_EPI32(x3, x2), PACK_HI_EPI32(x1, x0))
#define PACK_2_EPI32(x0, x1, x2, x3) \
    PACK_HI_EPI64(PACK_LO_EPI32(x3, x2), PACK_LO_EPI32(x1, x0))
#define PACK_3_EPI32(x0, x1, x2, x3) \
    PACK_LO_EPI64(PACK_LO_EPI32(x3, x2), PACK_LO_EPI32(x1, x0))

static void sm4_gfni_avx512_crypt(const std::uint32_t *rk,
                                  std::uint8_t        *out,
                                  const std::uint8_t  *in)
{
    // trans key: compare to sm4-round-func, this cost very small
    uint32_t trk[32];
    sm4_gfni_v2_trans_key(trk, rk);

    vector x[4];
    vector t[4]; // tmp
    vector t1, t2, t3, t4, t5;
    // load and pack 32bit patch
    t1 = VECTOR_LOAD(Shuffle_Endian); // shuffle vindex

    // load vector
    t[0] = VECTOR_LOAD((vector *)in + 0);
    t[1] = VECTOR_LOAD((vector *)in + 1);
    t[2] = VECTOR_LOAD((vector *)in + 2);
    t[3] = VECTOR_LOAD((vector *)in + 3);
    // shuffle endian
    t[0] = VECTOR_SHUFFLE_EPI8(t[0], t1);
    t[1] = VECTOR_SHUFFLE_EPI8(t[1], t1);
    t[2] = VECTOR_SHUFFLE_EPI8(t[2], t1);
    t[3] = VECTOR_SHUFFLE_EPI8(t[3], t1);
    // pack 32bit data
    x[0] = PACK_0_EPI32(t[0], t[1], t[2], t[3]);
    x[1] = PACK_1_EPI32(t[0], t[1], t[2], t[3]);
    x[2] = PACK_2_EPI32(t[0], t[1], t[2], t[3]);
    x[3] = PACK_3_EPI32(t[0], t[1], t[2], t[3]);
    // init(A1 * x)
    t2   = VECTOR_LOAD(Matrix_A1);
    x[0] = GF2_AFFINE(x[0], t2, 0);
    x[1] = GF2_AFFINE(x[1], t2, 0);
    x[2] = GF2_AFFINE(x[2], t2, 0);
    x[3] = GF2_AFFINE(x[3], t2, 0);

    // 32 round
    t1 = VECTOR_LOAD(Matrix_LA);
    t2 = VECTOR_LOAD(Matrix_LB);

    t3 = VECTOR_LOAD(Shuffle_ROTL8);
    t4 = VECTOR_LOAD(Shuffle_ROTL16);
    t5 = VECTOR_LOAD(Shuffle_ROTL24);
    for (int i = 0; i < 32; i += 4)
    {
        t[0] = VECTOR_SET1_EPI32(trk[i]);
        t[0] = XOR4_EPI32(x[1], x[2], x[3], t[0]);
        t[1] = GF2_AFFINE_INV(t[0], t1, Matrix_L_C2);
        t[2] = GF2_AFFINE_INV(t[0], t2, Matrix_L_C2);
        x[0] = XOR_EPI32(x[0], XOR4_EPI32(               //
                                   t[1],                 //
                                   ROTL_EPI32(t[2], 8),  //
                                   ROTL_EPI32(t[2], 16), //
                                   ROTL_EPI32(XOR_EPI32(t[1], t[2]), 24)));

        t[0] = VECTOR_SET1_EPI32(trk[i + 1]);
        t[0] = XOR4_EPI32(x[2], x[3], x[0], t[0]);
        t[1] = GF2_AFFINE_INV(t[0], t1, Matrix_L_C2);
        t[2] = GF2_AFFINE_INV(t[0], t2, Matrix_L_C2);
        x[1] = XOR_EPI32(x[1], XOR4_EPI32(               //
                                   t[1],                 //
                                   ROTL_EPI32(t[2], 8),  //
                                   ROTL_EPI32(t[2], 16), //
                                   ROTL_EPI32(XOR_EPI32(t[1], t[2]), 24)));

        t[0] = VECTOR_SET1_EPI32(trk[i + 2]);
        t[0] = XOR4_EPI32(x[3], x[0], x[1], t[0]);
        t[1] = GF2_AFFINE_INV(t[0], t1, Matrix_L_C2);
        t[2] = GF2_AFFINE_INV(t[0], t2, Matrix_L_C2);
        x[2] = XOR_EPI32(x[2], XOR4_EPI32(               //
                                   t[1],                 //
                                   ROTL_EPI32(t[2], 8),  //
                                   ROTL_EPI32(t[2], 16), //
                                   ROTL_EPI32(XOR_EPI32(t[1], t[2]), 24)));

        t[0] = VECTOR_SET1_EPI32(trk[i + 3]);
        t[0] = XOR4_EPI32(x[0], x[1], x[2], t[0]);
        t[1] = GF2_AFFINE_INV(t[0], t1, Matrix_L_C2);
        t[2] = GF2_AFFINE_INV(t[0], t2, Matrix_L_C2);
        x[3] = XOR_EPI32(x[3], XOR4_EPI32(               //
                                   t[1],                 //
                                   ROTL_EPI32(t[2], 8),  //
                                   ROTL_EPI32(t[2], 16), //
                                   ROTL_EPI32(XOR_EPI32(t[1], t[2]), 24)));
    }
    // unpack 8bit and invert(A1^-1 * x)
    t2   = VECTOR_LOAD(Matrix_A1_inv);
    x[0] = GF2_AFFINE(x[0], t2, 0);
    x[1] = GF2_AFFINE(x[1], t2, 0);
    x[2] = GF2_AFFINE(x[2], t2, 0);
    x[3] = GF2_AFFINE(x[3], t2, 0);

    // unpack 32bit patch and store
    t1   = VECTOR_LOAD(Shuffle_Endian); // shuffle vindex
    t[0] = PACK_0_EPI32(x[3], x[2], x[1], x[0]);
    t[1] = PACK_1_EPI32(x[3], x[2], x[1], x[0]);
    t[2] = PACK_2_EPI32(x[3], x[2], x[1], x[0]);
    t[3] = PACK_3_EPI32(x[3], x[2], x[1], x[0]);
    // shuffle endian
    t[0] = VECTOR_SHUFFLE_EPI8(t[0], t1);
    t[1] = VECTOR_SHUFFLE_EPI8(t[1], t1);
    t[2] = VECTOR_SHUFFLE_EPI8(t[2], t1);
    t[3] = VECTOR_SHUFFLE_EPI8(t[3], t1);
    // store data
    VECTOR_STORE((vector *)out + 0, t[0]);
    VECTOR_STORE((vector *)out + 1, t[1]);
    VECTOR_STORE((vector *)out + 2, t[2]);
    VECTOR_STORE((vector *)out + 3, t[3]);
}

static void sm4_gfni_v2_avx512_crypt(const std::uint32_t *trk,
                                     std::uint8_t        *out,
                                     const std::uint8_t  *in)
{
    // trans key: compare to sm4-round-func, this cost very small
    uint32_t rk[32];
    sm4_gfni_v2_trans_key(rk, trk);

    vector zmm[32];
#define ZMM0  zmm[0]
#define ZMM1  zmm[1]
#define ZMM2  zmm[2]
#define ZMM3  zmm[3]
#define ZMM4  zmm[4]
#define ZMM5  zmm[5]
#define ZMM6  zmm[6]
#define ZMM7  zmm[7]
#define ZMM8  zmm[8]
#define ZMM9  zmm[9]
#define ZMM10 zmm[10]
#define ZMM11 zmm[11]
#define ZMM12 zmm[12]
#define ZMM13 zmm[13]
#define ZMM14 zmm[14]
#define ZMM15 zmm[15]
#define ZMM16 zmm[16]
#define ZMM17 zmm[17]
#define ZMM18 zmm[18]
#define ZMM19 zmm[19]
#define ZMM20 zmm[20]
#define ZMM21 zmm[21]
#define ZMM22 zmm[22]
#define ZMM23 zmm[23]
#define ZMM24 zmm[24]
#define ZMM25 zmm[25]
#define ZMM26 zmm[26]
#define ZMM27 zmm[27]
#define ZMM28 zmm[28]
#define ZMM29 zmm[29]
#define ZMM30 zmm[30]
#define ZMM31 zmm[31]

    // ==== load const data =====
    ZMM17 = VECTOR_LOAD(Reshape_epi8);  // shuffle
    ZMM18 = VECTOR_LOAD(Matrix_A1);     // A
    ZMM19 = VECTOR_LOAD(Matrix_A1_inv); // A^-1

    ZMM20 = VECTOR_LOAD(Matrix_LA);
    ZMM21 = VECTOR_LOAD(Matrix_LB);

#define ZMM_SHUFFLE_ENDIAN ZMM16 // never use
#define ZMM_RESHAPE_EPI8   ZMM17
#define ZMM_MATRIX_A1      ZMM18
#define ZMM_MATRIX_A1_INV  ZMM19
#define ZMM_MATRIX_LA      ZMM20
#define ZMM_MATRIX_LB      ZMM21

    {
        // ==== load input ==========
        ZMM0  = VECTOR_LOAD((vector *)in);
        ZMM4  = VECTOR_LOAD((vector *)in + 1);
        ZMM8  = VECTOR_LOAD((vector *)in + 2);
        ZMM12 = VECTOR_LOAD((vector *)in + 3);

        ZMM1  = VECTOR_LOAD((vector *)in + 4);
        ZMM5  = VECTOR_LOAD((vector *)in + 5);
        ZMM9  = VECTOR_LOAD((vector *)in + 6);
        ZMM13 = VECTOR_LOAD((vector *)in + 7);

        ZMM2  = VECTOR_LOAD((vector *)in + 8);
        ZMM6  = VECTOR_LOAD((vector *)in + 9);
        ZMM10 = VECTOR_LOAD((vector *)in + 10);
        ZMM14 = VECTOR_LOAD((vector *)in + 11);

        ZMM3  = VECTOR_LOAD((vector *)in + 12);
        ZMM7  = VECTOR_LOAD((vector *)in + 13);
        ZMM11 = VECTOR_LOAD((vector *)in + 14);
        ZMM15 = VECTOR_LOAD((vector *)in + 15);
        // // shuffle endian
        // ZMM0 = VECTOR_SHUFFLE_EPI8(ZMM0, ZMM_SHUFFLE_ENDIAN);
        // ZMM4 = VECTOR_SHUFFLE_EPI8(ZMM4, ZMM_SHUFFLE_ENDIAN);
        // ZMM8 = VECTOR_SHUFFLE_EPI8(ZMM8, ZMM_SHUFFLE_ENDIAN);
        // ZMM12 = VECTOR_SHUFFLE_EPI8(ZMM12, ZMM_SHUFFLE_ENDIAN);

        // ZMM1 = VECTOR_SHUFFLE_EPI8(ZMM1, ZMM_SHUFFLE_ENDIAN);
        // ZMM5 = VECTOR_SHUFFLE_EPI8(ZMM5, ZMM_SHUFFLE_ENDIAN);
        // ZMM9 = VECTOR_SHUFFLE_EPI8(ZMM9, ZMM_SHUFFLE_ENDIAN);
        // ZMM13 = VECTOR_SHUFFLE_EPI8(ZMM13, ZMM_SHUFFLE_ENDIAN);

        // ZMM2 = VECTOR_SHUFFLE_EPI8(ZMM2, ZMM_SHUFFLE_ENDIAN);
        // ZMM6 = VECTOR_SHUFFLE_EPI8(ZMM6, ZMM_SHUFFLE_ENDIAN);
        // ZMM10 = VECTOR_SHUFFLE_EPI8(ZMM10, ZMM_SHUFFLE_ENDIAN);
        // ZMM14 = VECTOR_SHUFFLE_EPI8(ZMM14, ZMM_SHUFFLE_ENDIAN);

        // ZMM3 = VECTOR_SHUFFLE_EPI8(ZMM3, ZMM_SHUFFLE_ENDIAN);
        // ZMM7 = VECTOR_SHUFFLE_EPI8(ZMM7, ZMM_SHUFFLE_ENDIAN);
        // ZMM11 = VECTOR_SHUFFLE_EPI8(ZMM11, ZMM_SHUFFLE_ENDIAN);
        // ZMM15 = VECTOR_SHUFFLE_EPI8(ZMM15, ZMM_SHUFFLE_ENDIAN);
        // pack 1
        ZMM22 = PACK_HI_EPI32(ZMM12, ZMM8);
        ZMM23 = PACK_HI_EPI32(ZMM4, ZMM0);
        ZMM24 = PACK_LO_EPI32(ZMM12, ZMM8);
        ZMM25 = PACK_LO_EPI32(ZMM4, ZMM0);

        ZMM0  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM4  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM8  = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM12 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM13, ZMM9);
        ZMM23 = PACK_HI_EPI32(ZMM5, ZMM1);
        ZMM24 = PACK_LO_EPI32(ZMM13, ZMM9);
        ZMM25 = PACK_LO_EPI32(ZMM5, ZMM1);

        ZMM1  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM5  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM9  = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM13 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM14, ZMM10);
        ZMM23 = PACK_HI_EPI32(ZMM6, ZMM2);
        ZMM24 = PACK_LO_EPI32(ZMM14, ZMM10);
        ZMM25 = PACK_LO_EPI32(ZMM6, ZMM2);

        ZMM2  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM6  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM10 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM14 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM15, ZMM11);
        ZMM23 = PACK_HI_EPI32(ZMM7, ZMM3);
        ZMM24 = PACK_LO_EPI32(ZMM15, ZMM11);
        ZMM25 = PACK_LO_EPI32(ZMM7, ZMM3);

        ZMM3  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM7  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM11 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM15 = PACK_LO_EPI64(ZMM24, ZMM25);
        // ==========================================================

        // RESHAPE
        ZMM0  = VECTOR_SHUFFLE_EPI8(ZMM0, ZMM_RESHAPE_EPI8);
        ZMM1  = VECTOR_SHUFFLE_EPI8(ZMM1, ZMM_RESHAPE_EPI8);
        ZMM2  = VECTOR_SHUFFLE_EPI8(ZMM2, ZMM_RESHAPE_EPI8);
        ZMM3  = VECTOR_SHUFFLE_EPI8(ZMM3, ZMM_RESHAPE_EPI8);
        ZMM4  = VECTOR_SHUFFLE_EPI8(ZMM4, ZMM_RESHAPE_EPI8);
        ZMM5  = VECTOR_SHUFFLE_EPI8(ZMM5, ZMM_RESHAPE_EPI8);
        ZMM6  = VECTOR_SHUFFLE_EPI8(ZMM6, ZMM_RESHAPE_EPI8);
        ZMM7  = VECTOR_SHUFFLE_EPI8(ZMM7, ZMM_RESHAPE_EPI8);
        ZMM8  = VECTOR_SHUFFLE_EPI8(ZMM8, ZMM_RESHAPE_EPI8);
        ZMM9  = VECTOR_SHUFFLE_EPI8(ZMM9, ZMM_RESHAPE_EPI8);
        ZMM10 = VECTOR_SHUFFLE_EPI8(ZMM10, ZMM_RESHAPE_EPI8);
        ZMM11 = VECTOR_SHUFFLE_EPI8(ZMM11, ZMM_RESHAPE_EPI8);
        ZMM12 = VECTOR_SHUFFLE_EPI8(ZMM12, ZMM_RESHAPE_EPI8);
        ZMM13 = VECTOR_SHUFFLE_EPI8(ZMM13, ZMM_RESHAPE_EPI8);
        ZMM14 = VECTOR_SHUFFLE_EPI8(ZMM14, ZMM_RESHAPE_EPI8);
        ZMM15 = VECTOR_SHUFFLE_EPI8(ZMM15, ZMM_RESHAPE_EPI8);
        // PACK
        ZMM22 = PACK_HI_EPI32(ZMM3, ZMM2);
        ZMM23 = PACK_HI_EPI32(ZMM1, ZMM0);
        ZMM24 = PACK_LO_EPI32(ZMM3, ZMM2);
        ZMM25 = PACK_LO_EPI32(ZMM1, ZMM0);

        ZMM0 = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM1 = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM2 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM3 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM7, ZMM6);
        ZMM23 = PACK_HI_EPI32(ZMM5, ZMM4);
        ZMM24 = PACK_LO_EPI32(ZMM7, ZMM6);
        ZMM25 = PACK_LO_EPI32(ZMM5, ZMM4);

        ZMM4 = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM5 = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM6 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM7 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM11, ZMM10);
        ZMM23 = PACK_HI_EPI32(ZMM9, ZMM8);
        ZMM24 = PACK_LO_EPI32(ZMM11, ZMM10);
        ZMM25 = PACK_LO_EPI32(ZMM9, ZMM8);

        ZMM8  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM9  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM10 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM11 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM15, ZMM14);
        ZMM23 = PACK_HI_EPI32(ZMM13, ZMM12);
        ZMM24 = PACK_LO_EPI32(ZMM15, ZMM14);
        ZMM25 = PACK_LO_EPI32(ZMM13, ZMM12);

        ZMM12 = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM13 = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM14 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM15 = PACK_LO_EPI64(ZMM24, ZMM25);

        // AFFINE
        ZMM0  = GF2_AFFINE(ZMM0, ZMM_MATRIX_A1, 0);
        ZMM1  = GF2_AFFINE(ZMM1, ZMM_MATRIX_A1, 0);
        ZMM2  = GF2_AFFINE(ZMM2, ZMM_MATRIX_A1, 0);
        ZMM3  = GF2_AFFINE(ZMM3, ZMM_MATRIX_A1, 0);
        ZMM4  = GF2_AFFINE(ZMM4, ZMM_MATRIX_A1, 0);
        ZMM5  = GF2_AFFINE(ZMM5, ZMM_MATRIX_A1, 0);
        ZMM6  = GF2_AFFINE(ZMM6, ZMM_MATRIX_A1, 0);
        ZMM7  = GF2_AFFINE(ZMM7, ZMM_MATRIX_A1, 0);
        ZMM8  = GF2_AFFINE(ZMM8, ZMM_MATRIX_A1, 0);
        ZMM9  = GF2_AFFINE(ZMM9, ZMM_MATRIX_A1, 0);
        ZMM10 = GF2_AFFINE(ZMM10, ZMM_MATRIX_A1, 0);
        ZMM11 = GF2_AFFINE(ZMM11, ZMM_MATRIX_A1, 0);
        ZMM12 = GF2_AFFINE(ZMM12, ZMM_MATRIX_A1, 0);
        ZMM13 = GF2_AFFINE(ZMM13, ZMM_MATRIX_A1, 0);
        ZMM14 = GF2_AFFINE(ZMM14, ZMM_MATRIX_A1, 0);
        ZMM15 = GF2_AFFINE(ZMM15, ZMM_MATRIX_A1, 0);
    }
// bytes endian shape
#undef ZMM0
#undef ZMM1
#undef ZMM2
#undef ZMM3
#undef ZMM4
#undef ZMM5
#undef ZMM6
#undef ZMM7
#undef ZMM8
#undef ZMM9
#undef ZMM10
#undef ZMM11
#undef ZMM12
#undef ZMM13
#undef ZMM14
#undef ZMM15
#define ZMM0  zmm[15]
#define ZMM1  zmm[14]
#define ZMM2  zmm[13]
#define ZMM3  zmm[12]
#define ZMM4  zmm[11]
#define ZMM5  zmm[10]
#define ZMM6  zmm[9]
#define ZMM7  zmm[8]
#define ZMM8  zmm[7]
#define ZMM9  zmm[6]
#define ZMM10 zmm[5]
#define ZMM11 zmm[4]
#define ZMM12 zmm[3]
#define ZMM13 zmm[2]
#define ZMM14 zmm[1]
#define ZMM15 zmm[0]

    // ==============
    for (int i = 0; i < 32; i += 4)
    {
        // =========== 0 ===========
        // load roundkey
        ZMM22 = VECTOR_SET1_EPI8((rk[i] >> 24) & 0xff);
        ZMM23 = VECTOR_SET1_EPI8((rk[i] >> 16) & 0xff);
        ZMM24 = VECTOR_SET1_EPI8((rk[i] >> 8) & 0xff);
        ZMM25 = VECTOR_SET1_EPI8((rk[i] >> 0) & 0xff);
        // xor
        ZMM26 = XOR_EPI32(ZMM22, ZMM4);
        ZMM27 = XOR_EPI32(ZMM23, ZMM5);
        ZMM28 = XOR_EPI32(ZMM24, ZMM6);
        ZMM29 = XOR_EPI32(ZMM25, ZMM7);

        ZMM22 = XOR3_EPI32(ZMM26, ZMM8, ZMM12);  // t0
        ZMM23 = XOR3_EPI32(ZMM27, ZMM9, ZMM13);  // t1
        ZMM24 = XOR3_EPI32(ZMM28, ZMM10, ZMM14); // t2
        ZMM25 = XOR3_EPI32(ZMM29, ZMM11, ZMM15); // t3
                                                 // S + L

        zmm[26] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LA, Matrix_L_C2); // 00
        zmm[27] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LB, Matrix_L_C2); // 11
        zmm[28] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LB, Matrix_L_C2); // 12
        zmm[29] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LA, Matrix_L_C2); // 03
        zmm[30] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LB, Matrix_L_C2); // 13

        zmm[25] = XOR3_EPI32(ZMM0, zmm[26], zmm[27]);
        zmm[31] = XOR3_EPI32(zmm[28], zmm[29], zmm[30]);
        ZMM0    = XOR_EPI32(zmm[25], zmm[31]);

        zmm[31] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LA, Matrix_L_C2); // 01
        zmm[25] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LB, Matrix_L_C2); // 10

        zmm[22] = XOR3_EPI32(ZMM1, zmm[31], zmm[28]);
        zmm[23] = XOR3_EPI32(zmm[25], zmm[30], zmm[26]);
        ZMM1    = XOR_EPI32(zmm[22], zmm[23]);

        zmm[26] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LA, Matrix_L_C2); // 02

        zmm[22] = XOR3_EPI32(ZMM2, zmm[26], zmm[30]);
        zmm[23] = XOR3_EPI32(zmm[25], zmm[31], zmm[27]);
        ZMM2    = XOR_EPI32(zmm[22], zmm[23]);

        zmm[24] = XOR3_EPI32(ZMM3, zmm[29], zmm[25]);
        zmm[22] = XOR3_EPI32(zmm[27], zmm[26], zmm[28]);
        ZMM3    = XOR_EPI32(zmm[24], zmm[22]);

        // ZMM26 = GF2_AFFINE_INV(ZMM22, ZMM_MATRIX_LA, Matrix_L_C2);  // 00
        // ZMM27 = GF2_AFFINE_INV(ZMM22, ZMM_MATRIX_LB, Matrix_L_C2);  // 10

        // ZMM28 = GF2_AFFINE_INV(ZMM23, ZMM_MATRIX_LA, Matrix_L_C2);  // 01
        // ZMM29 = GF2_AFFINE_INV(ZMM23, ZMM_MATRIX_LB, Matrix_L_C2);  // 11

        // ZMM30 = GF2_AFFINE_INV(ZMM24, ZMM_MATRIX_LA, Matrix_L_C2);  // 02
        // ZMM31 = GF2_AFFINE_INV(ZMM24, ZMM_MATRIX_LB, Matrix_L_C2);  // 12

        // ZMM22 = GF2_AFFINE_INV(ZMM25, ZMM_MATRIX_LA, Matrix_L_C2);  // 03
        // ZMM23 = GF2_AFFINE_INV(ZMM25, ZMM_MATRIX_LB, Matrix_L_C2);  // 13

        // ZMM24 = XOR3_EPI32(ZMM0, ZMM26, ZMM29);   // 00 11
        // ZMM25 = XOR3_EPI32(ZMM31, ZMM22, ZMM23);  // 12 03 13
        // ZMM0 = XOR_EPI32(ZMM24, ZMM25);

        // ZMM24 = XOR3_EPI32(ZMM1, ZMM28, ZMM31);   // 01 12
        // ZMM25 = XOR3_EPI32(ZMM23, ZMM26, ZMM27);  // 13 00 10
        // ZMM1 = XOR_EPI32(ZMM24, ZMM25);

        // ZMM24 = XOR3_EPI32(ZMM2, ZMM30, ZMM23);   // 02 13
        // ZMM25 = XOR3_EPI32(ZMM27, ZMM28, ZMM29);  // 10 01 11
        // ZMM2 = XOR_EPI32(ZMM24, ZMM25);

        // ZMM24 = XOR3_EPI32(ZMM3, ZMM22, ZMM27);   // 03 10
        // ZMM25 = XOR3_EPI32(ZMM29, ZMM30, ZMM31);  // 11 02 12
        // ZMM3 = XOR_EPI32(ZMM24, ZMM25);
        // =========== 1 ===========
        // load roundkey
        ZMM22 = VECTOR_SET1_EPI8((rk[i + 1] >> 24) & 0xff);
        ZMM23 = VECTOR_SET1_EPI8((rk[i + 1] >> 16) & 0xff);
        ZMM24 = VECTOR_SET1_EPI8((rk[i + 1] >> 8) & 0xff);
        ZMM25 = VECTOR_SET1_EPI8((rk[i + 1] >> 0) & 0xff);
        // xor
        ZMM26 = XOR_EPI32(ZMM22, ZMM8);
        ZMM27 = XOR_EPI32(ZMM23, ZMM9);
        ZMM28 = XOR_EPI32(ZMM24, ZMM10);
        ZMM29 = XOR_EPI32(ZMM25, ZMM11);

        ZMM22 = XOR3_EPI32(ZMM26, ZMM12, ZMM0); // t0
        ZMM23 = XOR3_EPI32(ZMM27, ZMM13, ZMM1); // t1
        ZMM24 = XOR3_EPI32(ZMM28, ZMM14, ZMM2); // t2
        ZMM25 = XOR3_EPI32(ZMM29, ZMM15, ZMM3); // t3
        // S + L

        zmm[26] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LA, Matrix_L_C2); // 00
        zmm[27] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LB, Matrix_L_C2); // 11
        zmm[28] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LB, Matrix_L_C2); // 12
        zmm[29] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LA, Matrix_L_C2); // 03
        zmm[30] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LB, Matrix_L_C2); // 13

        zmm[25] = XOR3_EPI32(ZMM4, zmm[26], zmm[27]);
        zmm[31] = XOR3_EPI32(zmm[28], zmm[29], zmm[30]);
        ZMM4    = XOR_EPI32(zmm[25], zmm[31]);

        zmm[31] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LA, Matrix_L_C2); // 01
        zmm[25] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LB, Matrix_L_C2); // 10

        zmm[22] = XOR3_EPI32(ZMM5, zmm[31], zmm[28]);
        zmm[23] = XOR3_EPI32(zmm[25], zmm[30], zmm[26]);
        ZMM5    = XOR_EPI32(zmm[22], zmm[23]);

        zmm[26] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LA, Matrix_L_C2); // 02

        zmm[22] = XOR3_EPI32(ZMM6, zmm[26], zmm[30]);
        zmm[23] = XOR3_EPI32(zmm[25], zmm[31], zmm[27]);
        ZMM6    = XOR_EPI32(zmm[22], zmm[23]);

        zmm[24] = XOR3_EPI32(ZMM7, zmm[29], zmm[25]);
        zmm[22] = XOR3_EPI32(zmm[27], zmm[26], zmm[28]);
        ZMM7    = XOR_EPI32(zmm[24], zmm[22]);

        // =========== 2 ===========
        // load roundkey
        ZMM22 = VECTOR_SET1_EPI8((rk[i + 2] >> 24) & 0xff);
        ZMM23 = VECTOR_SET1_EPI8((rk[i + 2] >> 16) & 0xff);
        ZMM24 = VECTOR_SET1_EPI8((rk[i + 2] >> 8) & 0xff);
        ZMM25 = VECTOR_SET1_EPI8((rk[i + 2] >> 0) & 0xff);
        // xor
        ZMM26 = XOR_EPI32(ZMM22, ZMM12);
        ZMM27 = XOR_EPI32(ZMM23, ZMM13);
        ZMM28 = XOR_EPI32(ZMM24, ZMM14);
        ZMM29 = XOR_EPI32(ZMM25, ZMM15);

        ZMM22 = XOR3_EPI32(ZMM26, ZMM0, ZMM4); // t0
        ZMM23 = XOR3_EPI32(ZMM27, ZMM1, ZMM5); // t1
        ZMM24 = XOR3_EPI32(ZMM28, ZMM2, ZMM6); // t2
        ZMM25 = XOR3_EPI32(ZMM29, ZMM3, ZMM7); // t3

        // S + L
        ZMM26 = GF2_AFFINE_INV(ZMM22, ZMM_MATRIX_LA, Matrix_L_C2); // 00
        ZMM27 = GF2_AFFINE_INV(ZMM22, ZMM_MATRIX_LB, Matrix_L_C2); // 10

        ZMM28 = GF2_AFFINE_INV(ZMM23, ZMM_MATRIX_LA, Matrix_L_C2); // 01
        ZMM29 = GF2_AFFINE_INV(ZMM23, ZMM_MATRIX_LB, Matrix_L_C2); // 11

        ZMM30 = GF2_AFFINE_INV(ZMM24, ZMM_MATRIX_LA, Matrix_L_C2); // 02
        ZMM31 = GF2_AFFINE_INV(ZMM24, ZMM_MATRIX_LB, Matrix_L_C2); // 12

        ZMM22 = GF2_AFFINE_INV(ZMM25, ZMM_MATRIX_LA, Matrix_L_C2); // 03
        ZMM23 = GF2_AFFINE_INV(ZMM25, ZMM_MATRIX_LB, Matrix_L_C2); // 13

        ZMM24 = XOR3_EPI32(ZMM8, ZMM26, ZMM29);  // 00 11
        ZMM25 = XOR3_EPI32(ZMM31, ZMM22, ZMM23); // 12 03 13
        ZMM8  = XOR_EPI32(ZMM24, ZMM25);

        ZMM24 = XOR3_EPI32(ZMM9, ZMM28, ZMM31);  // 01 12
        ZMM25 = XOR3_EPI32(ZMM23, ZMM26, ZMM27); // 13 00 10
        ZMM9  = XOR_EPI32(ZMM24, ZMM25);

        ZMM24 = XOR3_EPI32(ZMM10, ZMM30, ZMM23); // 02 13
        ZMM25 = XOR3_EPI32(ZMM27, ZMM28, ZMM29); // 10 01 11
        ZMM10 = XOR_EPI32(ZMM24, ZMM25);

        ZMM24 = XOR3_EPI32(ZMM11, ZMM22, ZMM27); // 03 10
        ZMM25 = XOR3_EPI32(ZMM29, ZMM30, ZMM31); // 11 02 12
        ZMM11 = XOR_EPI32(ZMM24, ZMM25);
        // zmm[26] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LA, Matrix_L_C2);  // 00
        // zmm[27] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LB, Matrix_L_C2);  // 11
        // zmm[28] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LB, Matrix_L_C2);  // 12
        // zmm[29] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LA, Matrix_L_C2);  // 03
        // zmm[30] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LB, Matrix_L_C2);  // 13

        // zmm[25] = XOR3_EPI32(ZMM8, zmm[26], zmm[27]);
        // zmm[31] = XOR3_EPI32(zmm[28], zmm[29], zmm[30]);
        // ZMM8 = XOR_EPI32(zmm[25], zmm[31]);

        // zmm[31] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LA, Matrix_L_C2);  // 01
        // zmm[25] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LB, Matrix_L_C2);  // 10

        // zmm[22] = XOR3_EPI32(ZMM9, zmm[31], zmm[28]);
        // zmm[23] = XOR3_EPI32(zmm[25], zmm[30], zmm[26]);
        // ZMM9 = XOR_EPI32(zmm[22], zmm[23]);

        // zmm[26] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LA, Matrix_L_C2);  // 02

        // zmm[22] = XOR3_EPI32(ZMM10, zmm[26], zmm[30]);
        // zmm[23] = XOR3_EPI32(zmm[25], zmm[31], zmm[27]);
        // ZMM10 = XOR_EPI32(zmm[22], zmm[23]);

        // zmm[24] = XOR3_EPI32(ZMM11, zmm[29], zmm[25]);
        // zmm[22] = XOR3_EPI32(zmm[27], zmm[26], zmm[28]);
        // ZMM11 = XOR_EPI32(zmm[24], zmm[22]);
        // =========== 3 ===========
        // load roundkey
        ZMM22 = VECTOR_SET1_EPI8((rk[i + 3] >> 24) & 0xff);
        ZMM23 = VECTOR_SET1_EPI8((rk[i + 3] >> 16) & 0xff);
        ZMM24 = VECTOR_SET1_EPI8((rk[i + 3] >> 8) & 0xff);
        ZMM25 = VECTOR_SET1_EPI8((rk[i + 3] >> 0) & 0xff);
        // xor
        ZMM26 = XOR_EPI32(ZMM22, ZMM0);
        ZMM27 = XOR_EPI32(ZMM23, ZMM1);
        ZMM28 = XOR_EPI32(ZMM24, ZMM2);
        ZMM29 = XOR_EPI32(ZMM25, ZMM3);

        ZMM22 = XOR3_EPI32(ZMM26, ZMM4, ZMM8);  // t0
        ZMM23 = XOR3_EPI32(ZMM27, ZMM5, ZMM9);  // t1
        ZMM24 = XOR3_EPI32(ZMM28, ZMM6, ZMM10); // t2
        ZMM25 = XOR3_EPI32(ZMM29, ZMM7, ZMM11); // t3

        // S + L
        ZMM26 = GF2_AFFINE_INV(ZMM22, ZMM_MATRIX_LA, Matrix_L_C2); // 00
        ZMM27 = GF2_AFFINE_INV(ZMM22, ZMM_MATRIX_LB, Matrix_L_C2); // 10

        ZMM28 = GF2_AFFINE_INV(ZMM23, ZMM_MATRIX_LA, Matrix_L_C2); // 01
        ZMM29 = GF2_AFFINE_INV(ZMM23, ZMM_MATRIX_LB, Matrix_L_C2); // 11

        ZMM30 = GF2_AFFINE_INV(ZMM24, ZMM_MATRIX_LA, Matrix_L_C2); // 02
        ZMM31 = GF2_AFFINE_INV(ZMM24, ZMM_MATRIX_LB, Matrix_L_C2); // 12

        ZMM22 = GF2_AFFINE_INV(ZMM25, ZMM_MATRIX_LA, Matrix_L_C2); // 03
        ZMM23 = GF2_AFFINE_INV(ZMM25, ZMM_MATRIX_LB, Matrix_L_C2); // 13

        ZMM24 = XOR3_EPI32(ZMM12, ZMM26, ZMM29); // 00 11
        ZMM25 = XOR3_EPI32(ZMM31, ZMM22, ZMM23); // 12 03 13
        ZMM12 = XOR_EPI32(ZMM24, ZMM25);

        ZMM24 = XOR3_EPI32(ZMM13, ZMM28, ZMM31); // 01 12
        ZMM25 = XOR3_EPI32(ZMM23, ZMM26, ZMM27); // 13 00 10
        ZMM13 = XOR_EPI32(ZMM24, ZMM25);

        ZMM24 = XOR3_EPI32(ZMM14, ZMM30, ZMM23); // 02 13
        ZMM25 = XOR3_EPI32(ZMM27, ZMM28, ZMM29); // 10 01 11
        ZMM14 = XOR_EPI32(ZMM24, ZMM25);

        ZMM24 = XOR3_EPI32(ZMM15, ZMM22, ZMM27); // 03 10
        ZMM25 = XOR3_EPI32(ZMM29, ZMM30, ZMM31); // 11 02 12
        ZMM15 = XOR_EPI32(ZMM24, ZMM25);

        // zmm[26] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LA, Matrix_L_C2);  // 00
        // zmm[27] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LB, Matrix_L_C2);  // 11
        // zmm[28] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LB, Matrix_L_C2);  // 12
        // zmm[29] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LA, Matrix_L_C2);  // 03
        // zmm[30] = GF2_AFFINE_INV(zmm[25], ZMM_MATRIX_LB, Matrix_L_C2);  // 13

        // zmm[25] = XOR3_EPI32(ZMM12, zmm[26], zmm[27]);
        // zmm[31] = XOR3_EPI32(zmm[28], zmm[29], zmm[30]);
        // ZMM12 = XOR_EPI32(zmm[25], zmm[31]);

        // zmm[31] = GF2_AFFINE_INV(zmm[23], ZMM_MATRIX_LA, Matrix_L_C2);  // 01
        // zmm[25] = GF2_AFFINE_INV(zmm[22], ZMM_MATRIX_LB, Matrix_L_C2);  // 10

        // zmm[22] = XOR3_EPI32(ZMM13, zmm[31], zmm[28]);
        // zmm[23] = XOR3_EPI32(zmm[25], zmm[30], zmm[26]);
        // ZMM13 = XOR_EPI32(zmm[22], zmm[23]);

        // zmm[26] = GF2_AFFINE_INV(zmm[24], ZMM_MATRIX_LA, Matrix_L_C2);  // 02

        // zmm[22] = XOR3_EPI32(ZMM14, zmm[26], zmm[30]);
        // zmm[23] = XOR3_EPI32(zmm[25], zmm[31], zmm[27]);
        // ZMM14 = XOR_EPI32(zmm[22], zmm[23]);

        // zmm[24] = XOR3_EPI32(ZMM15, zmm[29], zmm[25]);
        // zmm[22] = XOR3_EPI32(zmm[27], zmm[26], zmm[28]);
        // ZMM15 = XOR_EPI32(zmm[24], zmm[22]);
    }
#undef ZMM0
#undef ZMM1
#undef ZMM2
#undef ZMM3
#undef ZMM4
#undef ZMM5
#undef ZMM6
#undef ZMM7
#undef ZMM8
#undef ZMM9
#undef ZMM10
#undef ZMM11
#undef ZMM12
#undef ZMM13
#undef ZMM14
#undef ZMM15
#define ZMM0  zmm[0]
#define ZMM1  zmm[1]
#define ZMM2  zmm[2]
#define ZMM3  zmm[3]
#define ZMM4  zmm[4]
#define ZMM5  zmm[5]
#define ZMM6  zmm[6]
#define ZMM7  zmm[7]
#define ZMM8  zmm[8]
#define ZMM9  zmm[9]
#define ZMM10 zmm[10]
#define ZMM11 zmm[11]
#define ZMM12 zmm[12]
#define ZMM13 zmm[13]
#define ZMM14 zmm[14]
#define ZMM15 zmm[15]
    {
        // ==============
        ZMM0  = GF2_AFFINE(ZMM0, ZMM_MATRIX_A1_INV, 0);
        ZMM1  = GF2_AFFINE(ZMM1, ZMM_MATRIX_A1_INV, 0);
        ZMM2  = GF2_AFFINE(ZMM2, ZMM_MATRIX_A1_INV, 0);
        ZMM3  = GF2_AFFINE(ZMM3, ZMM_MATRIX_A1_INV, 0);
        ZMM4  = GF2_AFFINE(ZMM4, ZMM_MATRIX_A1_INV, 0);
        ZMM5  = GF2_AFFINE(ZMM5, ZMM_MATRIX_A1_INV, 0);
        ZMM6  = GF2_AFFINE(ZMM6, ZMM_MATRIX_A1_INV, 0);
        ZMM7  = GF2_AFFINE(ZMM7, ZMM_MATRIX_A1_INV, 0);
        ZMM8  = GF2_AFFINE(ZMM8, ZMM_MATRIX_A1_INV, 0);
        ZMM9  = GF2_AFFINE(ZMM9, ZMM_MATRIX_A1_INV, 0);
        ZMM10 = GF2_AFFINE(ZMM10, ZMM_MATRIX_A1_INV, 0);
        ZMM11 = GF2_AFFINE(ZMM11, ZMM_MATRIX_A1_INV, 0);
        ZMM12 = GF2_AFFINE(ZMM12, ZMM_MATRIX_A1_INV, 0);
        ZMM13 = GF2_AFFINE(ZMM13, ZMM_MATRIX_A1_INV, 0);
        ZMM14 = GF2_AFFINE(ZMM14, ZMM_MATRIX_A1_INV, 0);
        ZMM15 = GF2_AFFINE(ZMM15, ZMM_MATRIX_A1_INV, 0);
        // pack
        ZMM22 = PACK_HI_EPI32(ZMM3, ZMM2);
        ZMM23 = PACK_HI_EPI32(ZMM1, ZMM0);
        ZMM24 = PACK_LO_EPI32(ZMM3, ZMM2);
        ZMM25 = PACK_LO_EPI32(ZMM1, ZMM0);

        ZMM0 = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM1 = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM2 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM3 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM7, ZMM6);
        ZMM23 = PACK_HI_EPI32(ZMM5, ZMM4);
        ZMM24 = PACK_LO_EPI32(ZMM7, ZMM6);
        ZMM25 = PACK_LO_EPI32(ZMM5, ZMM4);

        ZMM4 = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM5 = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM6 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM7 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM11, ZMM10);
        ZMM23 = PACK_HI_EPI32(ZMM9, ZMM8);
        ZMM24 = PACK_LO_EPI32(ZMM11, ZMM10);
        ZMM25 = PACK_LO_EPI32(ZMM9, ZMM8);

        ZMM8  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM9  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM10 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM11 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM15, ZMM14);
        ZMM23 = PACK_HI_EPI32(ZMM13, ZMM12);
        ZMM24 = PACK_LO_EPI32(ZMM15, ZMM14);
        ZMM25 = PACK_LO_EPI32(ZMM13, ZMM12);

        ZMM12 = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM13 = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM14 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM15 = PACK_LO_EPI64(ZMM24, ZMM25);
        // reshape
        ZMM0  = VECTOR_SHUFFLE_EPI8(ZMM0, ZMM_RESHAPE_EPI8);
        ZMM1  = VECTOR_SHUFFLE_EPI8(ZMM1, ZMM_RESHAPE_EPI8);
        ZMM2  = VECTOR_SHUFFLE_EPI8(ZMM2, ZMM_RESHAPE_EPI8);
        ZMM3  = VECTOR_SHUFFLE_EPI8(ZMM3, ZMM_RESHAPE_EPI8);
        ZMM4  = VECTOR_SHUFFLE_EPI8(ZMM4, ZMM_RESHAPE_EPI8);
        ZMM5  = VECTOR_SHUFFLE_EPI8(ZMM5, ZMM_RESHAPE_EPI8);
        ZMM6  = VECTOR_SHUFFLE_EPI8(ZMM6, ZMM_RESHAPE_EPI8);
        ZMM7  = VECTOR_SHUFFLE_EPI8(ZMM7, ZMM_RESHAPE_EPI8);
        ZMM8  = VECTOR_SHUFFLE_EPI8(ZMM8, ZMM_RESHAPE_EPI8);
        ZMM9  = VECTOR_SHUFFLE_EPI8(ZMM9, ZMM_RESHAPE_EPI8);
        ZMM10 = VECTOR_SHUFFLE_EPI8(ZMM10, ZMM_RESHAPE_EPI8);
        ZMM11 = VECTOR_SHUFFLE_EPI8(ZMM11, ZMM_RESHAPE_EPI8);
        ZMM12 = VECTOR_SHUFFLE_EPI8(ZMM12, ZMM_RESHAPE_EPI8);
        ZMM13 = VECTOR_SHUFFLE_EPI8(ZMM13, ZMM_RESHAPE_EPI8);
        ZMM14 = VECTOR_SHUFFLE_EPI8(ZMM14, ZMM_RESHAPE_EPI8);
        ZMM15 = VECTOR_SHUFFLE_EPI8(ZMM15, ZMM_RESHAPE_EPI8);
        // pack AND shuf

        ZMM22 = PACK_HI_EPI32(ZMM0, ZMM4);
        ZMM23 = PACK_HI_EPI32(ZMM8, ZMM12);
        ZMM24 = PACK_LO_EPI32(ZMM0, ZMM4);
        ZMM25 = PACK_LO_EPI32(ZMM8, ZMM12);

        ZMM0  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM4  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM8  = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM12 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM1, ZMM5);
        ZMM23 = PACK_HI_EPI32(ZMM9, ZMM13);
        ZMM24 = PACK_LO_EPI32(ZMM1, ZMM5);
        ZMM25 = PACK_LO_EPI32(ZMM9, ZMM13);

        ZMM1  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM5  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM9  = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM13 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM2, ZMM6);
        ZMM23 = PACK_HI_EPI32(ZMM10, ZMM14);
        ZMM24 = PACK_LO_EPI32(ZMM2, ZMM6);
        ZMM25 = PACK_LO_EPI32(ZMM10, ZMM14);

        ZMM2  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM6  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM10 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM14 = PACK_LO_EPI64(ZMM24, ZMM25);

        ZMM22 = PACK_HI_EPI32(ZMM3, ZMM7);
        ZMM23 = PACK_HI_EPI32(ZMM11, ZMM15);
        ZMM24 = PACK_LO_EPI32(ZMM3, ZMM7);
        ZMM25 = PACK_LO_EPI32(ZMM11, ZMM15);

        ZMM3  = PACK_HI_EPI64(ZMM22, ZMM23);
        ZMM7  = PACK_LO_EPI64(ZMM22, ZMM23);
        ZMM11 = PACK_HI_EPI64(ZMM24, ZMM25);
        ZMM15 = PACK_LO_EPI64(ZMM24, ZMM25);

        // // shuffle endian
        // ZMM0 = VECTOR_SHUFFLE_EPI8(ZMM0, ZMM_SHUFFLE_ENDIAN);
        // ZMM4 = VECTOR_SHUFFLE_EPI8(ZMM4, ZMM_SHUFFLE_ENDIAN);
        // ZMM8 = VECTOR_SHUFFLE_EPI8(ZMM8, ZMM_SHUFFLE_ENDIAN);
        // ZMM12 = VECTOR_SHUFFLE_EPI8(ZMM12, ZMM_SHUFFLE_ENDIAN);

        // ZMM1 = VECTOR_SHUFFLE_EPI8(ZMM1, ZMM_SHUFFLE_ENDIAN);
        // ZMM5 = VECTOR_SHUFFLE_EPI8(ZMM5, ZMM_SHUFFLE_ENDIAN);
        // ZMM9 = VECTOR_SHUFFLE_EPI8(ZMM9, ZMM_SHUFFLE_ENDIAN);
        // ZMM13 = VECTOR_SHUFFLE_EPI8(ZMM13, ZMM_SHUFFLE_ENDIAN);

        // ZMM2 = VECTOR_SHUFFLE_EPI8(ZMM2, ZMM_SHUFFLE_ENDIAN);
        // ZMM6 = VECTOR_SHUFFLE_EPI8(ZMM6, ZMM_SHUFFLE_ENDIAN);
        // ZMM10 = VECTOR_SHUFFLE_EPI8(ZMM10, ZMM_SHUFFLE_ENDIAN);
        // ZMM14 = VECTOR_SHUFFLE_EPI8(ZMM14, ZMM_SHUFFLE_ENDIAN);

        // ZMM3 = VECTOR_SHUFFLE_EPI8(ZMM3, ZMM_SHUFFLE_ENDIAN);
        // ZMM7 = VECTOR_SHUFFLE_EPI8(ZMM7, ZMM_SHUFFLE_ENDIAN);
        // ZMM11 = VECTOR_SHUFFLE_EPI8(ZMM11, ZMM_SHUFFLE_ENDIAN);
        // ZMM15 = VECTOR_SHUFFLE_EPI8(ZMM15, ZMM_SHUFFLE_ENDIAN);
        // out
        VECTOR_STORE((vector *)out, ZMM0);
        VECTOR_STORE((vector *)out + 1, ZMM4);
        VECTOR_STORE((vector *)out + 2, ZMM8);
        VECTOR_STORE((vector *)out + 3, ZMM12);

        VECTOR_STORE((vector *)out + 4, ZMM1);
        VECTOR_STORE((vector *)out + 5, ZMM5);
        VECTOR_STORE((vector *)out + 6, ZMM9);
        VECTOR_STORE((vector *)out + 7, ZMM13);

        VECTOR_STORE((vector *)out + 8, ZMM2);
        VECTOR_STORE((vector *)out + 9, ZMM6);
        VECTOR_STORE((vector *)out + 10, ZMM10);
        VECTOR_STORE((vector *)out + 11, ZMM14);

        VECTOR_STORE((vector *)out + 12, ZMM3);
        VECTOR_STORE((vector *)out + 13, ZMM7);
        VECTOR_STORE((vector *)out + 14, ZMM11);
        VECTOR_STORE((vector *)out + 15, ZMM15);
    }
}

} // namespace sm4::internal::gong23::gfni

#pragma endregion

namespace sm4::internal::gong23 {

#pragma region "SM4 Params"

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

#pragma endregion

#pragma region "SM4 CORE"

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

#pragma endregion

void sm4_enc_key_init(std::uint8_t       round_key[128],
                      const std::uint8_t user_key[16]) noexcept
{
    sm4_key_init((std::uint32_t *)round_key, user_key, 1);
}

void sm4_dec_key_init(std::uint8_t       round_key[128],
                      const std::uint8_t user_key[16]) noexcept
{
    sm4_key_init((std::uint32_t *)round_key, user_key, 0);
}

void sm4_enc_block(const std::uint8_t round_key[128],
                   std::uint8_t       ciphertext[16],
                   const std::uint8_t plaintext[16]) noexcept
{
    sm4_enc_blocks(round_key, ciphertext, plaintext, 1);
}

void sm4_dec_block(const std::uint8_t round_key[128],
                   std::uint8_t       plaintext[16],
                   const std::uint8_t ciphertext[16]) noexcept
{
    sm4_dec_blocks(round_key, plaintext, ciphertext, 1);
}

void sm4_enc_blocks(const std::uint8_t  round_key[128],
                    std::uint8_t       *ciphertext,
                    const std::uint8_t *plaintext,
                    std::size_t         block_num) noexcept
{
    while (block_num >= 64)
    {
        gfni::sm4_gfni_v2_avx512_crypt((const std::uint32_t *)round_key,
                                       ciphertext, plaintext);
        ciphertext += 64 * 16, plaintext += 64 * 16, block_num -= 64;
    }
    while (block_num >= 16)
    {
        gfni::sm4_gfni_avx512_crypt((const std::uint32_t *)round_key,
                                    ciphertext, plaintext);
        ciphertext += 16 * 16, plaintext += 16 * 16, block_num -= 16;
    }
    while (block_num)
    {
        sm4_compute_block((const std::uint32_t *)round_key, ciphertext,
                          plaintext);
        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void sm4_dec_blocks(const std::uint8_t  round_key[128],
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept
{
    while (block_num >= 64)
    {
        gfni::sm4_gfni_v2_avx512_crypt((const std::uint32_t *)round_key,
                                       plaintext, ciphertext);
        ciphertext += 64 * 16, plaintext += 64 * 16, block_num -= 64;
    }
    while (block_num >= 16)
    {
        gfni::sm4_gfni_avx512_crypt((const std::uint32_t *)round_key, plaintext,
                                    ciphertext);
        ciphertext += 16 * 16, plaintext += 16 * 16, block_num -= 16;
    }
    while (block_num)
    {
        sm4_compute_block((const std::uint32_t *)round_key, plaintext,
                          ciphertext);
        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

} // namespace sm4::internal::gong23

#endif