#include <gmlib/ublock/internal/ublock_common.h>

namespace ublock::internal::common {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ********* UBLOCK COMMON Params And Define ********
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

#define MEM_LOAD32BE(src)                                  \
    (((std::uint32_t)(((std::uint8_t *)(src))[0]) << 24) | \
     ((std::uint32_t)(((std::uint8_t *)(src))[1]) << 16) | \
     ((std::uint32_t)(((std::uint8_t *)(src))[2]) << 8) |  \
     ((std::uint32_t)(((std::uint8_t *)(src))[3]) << 0))

#define MEM_STORE32BE(dst, a)                                        \
    (((std::uint8_t *)(dst))[0] = ((std::uint32_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t *)(dst))[1] = ((std::uint32_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t *)(dst))[2] = ((std::uint32_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t *)(dst))[3] = ((std::uint32_t)(a) >> 0) & 0xFF)

#define MEM_LOAD64BE(src)                                  \
    (((std::uint64_t)(((std::uint8_t *)(src))[0]) << 56) | \
     ((std::uint64_t)(((std::uint8_t *)(src))[1]) << 48) | \
     ((std::uint64_t)(((std::uint8_t *)(src))[2]) << 40) | \
     ((std::uint64_t)(((std::uint8_t *)(src))[3]) << 32) | \
     ((std::uint64_t)(((std::uint8_t *)(src))[4]) << 24) | \
     ((std::uint64_t)(((std::uint8_t *)(src))[5]) << 16) | \
     ((std::uint64_t)(((std::uint8_t *)(src))[6]) << 8) |  \
     ((std::uint64_t)(((std::uint8_t *)(src))[7]) << 0))

#define MEM_STORE64BE(dst, a)                                        \
    (((std::uint8_t *)(dst))[0] = ((std::uint64_t)(a) >> 56) & 0xFF, \
     ((std::uint8_t *)(dst))[1] = ((std::uint64_t)(a) >> 48) & 0xFF, \
     ((std::uint8_t *)(dst))[2] = ((std::uint64_t)(a) >> 40) & 0xFF, \
     ((std::uint8_t *)(dst))[3] = ((std::uint64_t)(a) >> 32) & 0xFF, \
     ((std::uint8_t *)(dst))[4] = ((std::uint64_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t *)(dst))[5] = ((std::uint64_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t *)(dst))[6] = ((std::uint64_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t *)(dst))[7] = ((std::uint64_t)(a) >> 0) & 0xFF)

#define u64_get_epi4(n, pos) (((n) >> (60 - 4 * (pos))) & 0xF)
#define u64_get_epi8(n, pos) (((n) >> (56 - 8 * (pos))) & 0xFF)

static std::uint32_t RC_u32[24] = {
    0x988cc9dd, 0xf0e4a1b5, 0x21357064, 0x8397d2c6, 0xc7d39682, 0x4f5b1e0a,
    0x5e4a0f1b, 0x7c682d39, 0x392d687c, 0xb3a7e2f6, 0xa7b3f6e2, 0x8e9adfcb,
    0xdcc88d99, 0x786c293d, 0x30246175, 0xa1b5f0e4, 0x8296d3c7, 0xc5d19480,
    0x4a5e1b0f, 0x55410410, 0x6b7f3a2e, 0x17034652, 0xeffbbeaa, 0x1f0b4e5a,
};
static std::uint64_t RC_u64[24] = {
    0x988cc9dd00000000ULL, 0xf0e4a1b500000000ULL, 0x2135706400000000ULL,
    0x8397d2c600000000ULL, 0xc7d3968200000000ULL, 0x4f5b1e0a00000000ULL,
    0x5e4a0f1b00000000ULL, 0x7c682d3900000000ULL, 0x392d687c00000000ULL,
    0xb3a7e2f600000000ULL, 0xa7b3f6e200000000ULL, 0x8e9adfcb00000000ULL,
    0xdcc88d9900000000ULL, 0x786c293d00000000ULL, 0x3024617500000000ULL,
    0xa1b5f0e400000000ULL, 0x8296d3c700000000ULL, 0xc5d1948000000000ULL,
    0x4a5e1b0f00000000ULL, 0x5541041000000000ULL, 0x6b7f3a2e00000000ULL,
    0x1703465200000000ULL, 0xeffbbeaa00000000ULL, 0x1f0b4e5a00000000ULL,
};
static std::uint8_t SBOX[16] = {
    0x7, 0x4, 0x9, 0xc, 0xb, 0xa, 0xd, 0x8,
    0xf, 0xe, 0x1, 0x6, 0x0, 0x3, 0x2, 0x5,
};
static std::uint8_t SBOXI[16] = {
    0xc, 0xa, 0xe, 0xd, 0x1, 0xf, 0xb, 0x0,
    0x7, 0x2, 0x5, 0x4, 0x3, 0x6, 0x9, 0x8,
};
static std::uint8_t MUL2T[16] = {
    0, 2, 4, 6, 8, 0xa, 0xc, 0xe, 3, 1, 7, 5, 0xb, 9, 0xf, 0xd,
};
static int PK1T[16] = {
    6, 0, 8, 13, 1, 15, 5, 10, 4, 9, 12, 2, 11, 3, 7, 14,
};
static int PK2T[32] = {
    10, 5,  15, 0,  2,  7,  8,  13, 14, 6,  4,  12, 1,  3,  11, 9,
    24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23,
};
static int PK2T_H[16] = {
    10, 5, 15, 0, 2, 7, 8, 13, 14, 6, 4, 12, 1, 3, 11, 9,
};
static int PK2T_L[16] = {
    24 - 16, 25 - 16, 26 - 16, 27 - 16, 28 - 16, 29 - 16, 30 - 16, 31 - 16,
    16 - 16, 17 - 16, 18 - 16, 19 - 16, 20 - 16, 21 - 16, 22 - 16, 23 - 16,
};
static int PK3T[32] = {
    10, 5,  15, 0,  2,  7,  8,  13, 1,  14, 4,  12, 9,  11, 3,  6,
    24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23,
};
static int PK3T_H[16] = {
    10, 5, 15, 0, 2, 7, 8, 13, 1, 14, 4, 12, 9, 11, 3, 6,
};
static int PK3T_L[16] = {
    24 - 16, 25 - 16, 26 - 16, 27 - 16, 28 - 16, 29 - 16, 30 - 16, 31 - 16,
    16 - 16, 17 - 16, 18 - 16, 19 - 16, 20 - 16, 21 - 16, 22 - 16, 23 - 16,
};
static int PL128T[8] = {
    1, 3, 4, 6, 0, 2, 7, 5,
};
static int PR128T[8] = {
    2, 7, 5, 0, 1, 6, 4, 3,
};
static int PL256T[16] = {
    2, 7, 8, 13, 3, 6, 9, 12, 1, 4, 15, 10, 14, 11, 5, 0,
};
static int PR256T[16] = {
    6, 11, 1, 12, 9, 4, 2, 15, 7, 0, 13, 10, 14, 3, 8, 5,
};
static int PL128IT[8] = {
    4, 0, 5, 1, 2, 7, 3, 6,
};
static int PR128IT[8] = {
    3, 4, 0, 7, 6, 2, 5, 1,
};
static int PL256IT[16] = {
    15, 8, 0, 4, 9, 14, 5, 1, 2, 6, 11, 13, 7, 3, 12, 10,
};
static int PR256IT[16] = {
    9, 2, 6, 13, 5, 15, 0, 8, 14, 4, 11, 1, 3, 10, 12, 7,
};

static inline std::uint64_t lut_u64_epi4(std::uint64_t      n,
                                         const std::uint8_t T[16]) noexcept
{
    std::uint64_t ret;
    ret = (std::uint64_t)T[(n >> 60) & 0xF] << 60;
    ret |= (std::uint64_t)T[(n >> 56) & 0xF] << 56;
    ret |= (std::uint64_t)T[(n >> 52) & 0xF] << 52;
    ret |= (std::uint64_t)T[(n >> 48) & 0xF] << 48;
    ret |= (std::uint64_t)T[(n >> 44) & 0xF] << 44;
    ret |= (std::uint64_t)T[(n >> 40) & 0xF] << 40;
    ret |= (std::uint64_t)T[(n >> 36) & 0xF] << 36;
    ret |= (std::uint64_t)T[(n >> 32) & 0xF] << 32;
    ret |= (std::uint64_t)T[(n >> 28) & 0xF] << 28;
    ret |= (std::uint64_t)T[(n >> 24) & 0xF] << 24;
    ret |= (std::uint64_t)T[(n >> 20) & 0xF] << 20;
    ret |= (std::uint64_t)T[(n >> 16) & 0xF] << 16;
    ret |= (std::uint64_t)T[(n >> 12) & 0xF] << 12;
    ret |= (std::uint64_t)T[(n >> 8) & 0xF] << 8;
    ret |= (std::uint64_t)T[(n >> 4) & 0xF] << 4;
    ret |= (std::uint64_t)T[(n >> 0) & 0xF] << 0;
    return ret;
}

static inline std::uint32_t Sk_u32(std::uint32_t n) noexcept
{
    std::uint32_t ret;
    ret = (std::uint32_t)SBOX[(n >> 28) & 0xF] << 28;
    ret |= (std::uint32_t)SBOX[(n >> 24) & 0xF] << 24;
    ret |= (std::uint32_t)SBOX[(n >> 20) & 0xF] << 20;
    ret |= (std::uint32_t)SBOX[(n >> 16) & 0xF] << 16;
    ret |= (std::uint32_t)SBOX[(n >> 12) & 0xF] << 12;
    ret |= (std::uint32_t)SBOX[(n >> 8) & 0xF] << 8;
    ret |= (std::uint32_t)SBOX[(n >> 4) & 0xF] << 4;
    ret |= (std::uint32_t)SBOX[(n >> 0) & 0xF] << 0;
    return ret;
}
static inline std::uint64_t Sk_u64(std::uint64_t n) noexcept
{
    return lut_u64_epi4(n, SBOX);
}
static inline std::uint64_t SIk_u64(std::uint64_t n) noexcept
{
    return lut_u64_epi4(n, SBOXI);
}
static inline std::uint32_t Tk_u32(std::uint32_t n) noexcept
{
    std::uint32_t ret;
    ret = MUL2T[(n >> 28) & 0xF] << 28;
    ret |= MUL2T[(n >> 24) & 0xF] << 24;
    ret |= MUL2T[(n >> 20) & 0xF] << 20;
    ret |= MUL2T[(n >> 16) & 0xF] << 16;
    ret |= MUL2T[(n >> 12) & 0xF] << 12;
    ret |= MUL2T[(n >> 8) & 0xF] << 8;
    ret |= MUL2T[(n >> 4) & 0xF] << 4;
    ret |= MUL2T[(n >> 0) & 0xF] << 0;
    return ret;
}
static inline std::uint64_t Tk_u64(std::uint64_t n) noexcept
{
    std::uint64_t ret;
    ret = (std::uint64_t)MUL2T[(n >> 60) & 0xF] << 60;
    ret |= (std::uint64_t)MUL2T[(n >> 56) & 0xF] << 56;
    ret |= (std::uint64_t)MUL2T[(n >> 52) & 0xF] << 52;
    ret |= (std::uint64_t)MUL2T[(n >> 48) & 0xF] << 48;
    ret |= (std::uint64_t)MUL2T[(n >> 44) & 0xF] << 44;
    ret |= (std::uint64_t)MUL2T[(n >> 40) & 0xF] << 40;
    ret |= (std::uint64_t)MUL2T[(n >> 36) & 0xF] << 36;
    ret |= (std::uint64_t)MUL2T[(n >> 32) & 0xF] << 32;
    ret |= (std::uint64_t)MUL2T[(n >> 28) & 0xF] << 28;
    ret |= (std::uint64_t)MUL2T[(n >> 24) & 0xF] << 24;
    ret |= (std::uint64_t)MUL2T[(n >> 20) & 0xF] << 20;
    ret |= (std::uint64_t)MUL2T[(n >> 16) & 0xF] << 16;
    ret |= (std::uint64_t)MUL2T[(n >> 12) & 0xF] << 12;
    ret |= (std::uint64_t)MUL2T[(n >> 8) & 0xF] << 8;
    ret |= (std::uint64_t)MUL2T[(n >> 4) & 0xF] << 4;
    ret |= (std::uint64_t)MUL2T[(n >> 0) & 0xF] << 0;
    return ret;
}
static inline std::uint64_t shuffle_u64_epi4(std::uint64_t n,
                                             const int     T[16]) noexcept
{
    std::uint64_t ret;
    ret = u64_get_epi4(n, T[0]) << 60;
    ret |= u64_get_epi4(n, T[1]) << 56;
    ret |= u64_get_epi4(n, T[2]) << 52;
    ret |= u64_get_epi4(n, T[3]) << 48;
    ret |= u64_get_epi4(n, T[4]) << 44;
    ret |= u64_get_epi4(n, T[5]) << 40;
    ret |= u64_get_epi4(n, T[6]) << 36;
    ret |= u64_get_epi4(n, T[7]) << 32;
    ret |= u64_get_epi4(n, T[8]) << 28;
    ret |= u64_get_epi4(n, T[9]) << 24;
    ret |= u64_get_epi4(n, T[10]) << 20;
    ret |= u64_get_epi4(n, T[11]) << 16;
    ret |= u64_get_epi4(n, T[12]) << 12;
    ret |= u64_get_epi4(n, T[13]) << 8;
    ret |= u64_get_epi4(n, T[14]) << 4;
    ret |= u64_get_epi4(n, T[15]) << 0;
    return ret;
}
static inline std::uint64_t shuffle_u64_epi8(std::uint64_t n,
                                             const int     T[8]) noexcept
{
    std::uint64_t ret;
    ret = u64_get_epi8(n, T[0]) << 56;
    ret |= u64_get_epi8(n, T[1]) << 48;
    ret |= u64_get_epi8(n, T[2]) << 40;
    ret |= u64_get_epi8(n, T[3]) << 32;
    ret |= u64_get_epi8(n, T[4]) << 24;
    ret |= u64_get_epi8(n, T[5]) << 16;
    ret |= u64_get_epi8(n, T[6]) << 8;
    ret |= u64_get_epi8(n, T[7]) << 0;
    return ret;
}
static inline void shuffle_u128_epi8(std::uint64_t n[2],
                                     const int     T[16]) noexcept
{
#define u128_get_epi8(n, i) u64_get_epi8(n[(i) / 8], (i) % 8)

    std::uint64_t r[2];
    r[0] = u128_get_epi8(n, T[0]) << 56;
    r[0] |= u128_get_epi8(n, T[1]) << 48;
    r[0] |= u128_get_epi8(n, T[2]) << 40;
    r[0] |= u128_get_epi8(n, T[3]) << 32;
    r[0] |= u128_get_epi8(n, T[4]) << 24;
    r[0] |= u128_get_epi8(n, T[5]) << 16;
    r[0] |= u128_get_epi8(n, T[6]) << 8;
    r[0] |= u128_get_epi8(n, T[7]) << 0;

    r[1] = u128_get_epi8(n, T[8]) << 56;
    r[1] |= u128_get_epi8(n, T[9]) << 48;
    r[1] |= u128_get_epi8(n, T[10]) << 40;
    r[1] |= u128_get_epi8(n, T[11]) << 32;
    r[1] |= u128_get_epi8(n, T[12]) << 24;
    r[1] |= u128_get_epi8(n, T[13]) << 16;
    r[1] |= u128_get_epi8(n, T[14]) << 8;
    r[1] |= u128_get_epi8(n, T[15]) << 0;

    n[0] = r[0], n[1] = r[1];
#undef u128_get_epi8
}
static inline std::uint64_t rotl_u64_epi32(std::uint64_t n, int s) noexcept
{
    std::uint32_t n0 = (std::uint32_t)(n >> 32);
    std::uint32_t n1 = (std::uint32_t)(n & UINT32_MAX);
    std::uint32_t r0 = (n0 << s) | (n0 >> (32 - s));
    std::uint32_t r1 = (n1 << s) | (n1 >> (32 - s));
    return ((std::uint64_t)r0 << 32) | (std::uint64_t)r1;
}
static inline void PK1_u64(std::uint32_t *K0, std::uint32_t *K1) noexcept
{
    std::uint64_t K0K1 = (std::uint64_t)(*K0) << 32 | (std::uint64_t)(*K1);
    std::uint64_t ret  = shuffle_u64_epi4(K0K1, PK1T);
    *K0                = (std::uint32_t)(ret >> 32);
    *K1                = (std::uint32_t)(ret & UINT32_MAX);
}
static inline void PK2_u128(std::uint64_t *K0, std::uint64_t *K1) noexcept
{
    *K0 = shuffle_u64_epi4(*K0, PK2T_H);
    *K1 = shuffle_u64_epi4(*K1, PK2T_L);
}
static inline void PK3_u128(std::uint64_t *K0, std::uint64_t *K1) noexcept
{
    *K0 = shuffle_u64_epi4(*K0, PK3T_H);
    *K1 = shuffle_u64_epi4(*K1, PK3T_L);
}
static inline std::uint64_t PL128_u64(std::uint64_t n) noexcept
{
    return shuffle_u64_epi8(n, PL128T);
}
static inline std::uint64_t PR128_u64(std::uint64_t n) noexcept
{
    return shuffle_u64_epi8(n, PR128T);
}
static inline std::uint64_t PL128I_u64(std::uint64_t n) noexcept
{
    return shuffle_u64_epi8(n, PL128IT);
}
static inline std::uint64_t PR128I_u64(std::uint64_t n) noexcept
{
    return shuffle_u64_epi8(n, PR128IT);
}
static inline void PL256_u128(std::uint64_t n[2]) noexcept
{
    shuffle_u128_epi8(n, PL256T);
}
static inline void PR256_u128(std::uint64_t n[2]) noexcept
{
    shuffle_u128_epi8(n, PR256T);
}
static inline void PL256I_u128(std::uint64_t n[2]) noexcept
{
    shuffle_u128_epi8(n, PL256IT);
}
static inline void PR256I_u128(std::uint64_t n[2]) noexcept
{
    shuffle_u128_epi8(n, PR256IT);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************ UBLOCK COMMON CORE FUNC *************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

static void ublock128128_key_init(std::uint64_t      round_key[17][2],
                                  const std::uint8_t user_key[16]) noexcept
{
    std::uint32_t K[4];
    K[0] = MEM_LOAD32BE(user_key + 0);
    K[1] = MEM_LOAD32BE(user_key + 4);
    K[2] = MEM_LOAD32BE(user_key + 8);
    K[3] = MEM_LOAD32BE(user_key + 12);
    // RK0 = K[0:127]
    round_key[0][0] = ((std::uint64_t)K[0] << 32) | K[1];
    round_key[0][1] = ((std::uint64_t)K[2] << 32) | K[3];
    for (int i = 1; i <= 16; i++)
    {
        // K0||K1||K2||K3 <- K
        std::uint32_t K0 = K[0], K1 = K[1], K2 = K[2], K3 = K[3];
        PK1_u64(&K0, &K1);                    // K0||K1 <- PKt(K0||K1)
        K2 = K2 ^ Sk_u32(K0 ^ RC_u32[i - 1]); // K2 <- K2 ^ Sk(K0 ^ RCi)
        K3 = K3 ^ Tk_u32(K1);                 // K3 <- Tk(K1)
        // K <- K2||K3||K1||K0
        K[0] = K2, K[1] = K3, K[2] = K1, K[3] = K0;
        // RKi = K[0:127]
        round_key[i][0] = ((std::uint64_t)K[0] << 32) | K[1];
        round_key[i][1] = ((std::uint64_t)K[2] << 32) | K[3];
    }
}

static void ublock128256_key_init(std::uint64_t      round_key[25][2],
                                  const std::uint8_t user_key[32]) noexcept
{
    std::uint64_t K[4];
    K[0] = MEM_LOAD64BE(user_key + 0);
    K[1] = MEM_LOAD64BE(user_key + 8);
    K[2] = MEM_LOAD64BE(user_key + 16);
    K[3] = MEM_LOAD64BE(user_key + 24);
    // RK0 = K[0:127]
    round_key[0][0] = K[0], round_key[0][1] = K[1];
    for (int i = 1; i <= 24; i++)
    {
        // K0||K1||K2||K3 <- K
        std::uint64_t K0 = K[0], K1 = K[1], K2 = K[2], K3 = K[3];
        PK2_u128(&K0, &K1);                   // K0||K1 <- PKt(K0||K1)
        K2 = K2 ^ Sk_u64(K0 ^ RC_u64[i - 1]); // K2 <- K2 ^ Sk(K0 ^ RCi)
        K3 = K3 ^ Tk_u64(K1);                 // K3 <- Tk(K1)
        // K <- K2||K3||K1||K0
        K[0] = K2, K[1] = K3, K[2] = K1, K[3] = K0;
        // RKi = K[0:127]
        round_key[i][0] = K[0], round_key[i][1] = K[1];
    }
}

static void ublock256256_key_init(std::uint64_t      round_key[25][4],
                                  const std::uint8_t user_key[32]) noexcept
{
    std::uint64_t K[4];
    K[0] = MEM_LOAD64BE(user_key + 0);
    K[1] = MEM_LOAD64BE(user_key + 8);
    K[2] = MEM_LOAD64BE(user_key + 16);
    K[3] = MEM_LOAD64BE(user_key + 24);
    // RK0 = K[0:255]
    round_key[0][0] = K[0], round_key[0][1] = K[1];
    round_key[0][2] = K[2], round_key[0][3] = K[3];
    for (int i = 1; i <= 24; i++)
    {
        // K0||K1||K2||K3 <- K
        std::uint64_t K0 = K[0], K1 = K[1], K2 = K[2], K3 = K[3];
        PK3_u128(&K0, &K1);                   // K0||K1 <- PKt(K0||K1)
        K2 = K2 ^ Sk_u64(K0 ^ RC_u64[i - 1]); // K2 <- K2 ^ Sk(K0 ^ RCi)
        K3 = K3 ^ Tk_u64(K1);                 // K3 <- Tk(K1)
        // K <- K2||K3||K1||K0
        K[0] = K2, K[1] = K3, K[2] = K1, K[3] = K0;
        // RKi = K[0:255]
        round_key[i][0] = K[0], round_key[i][1] = K[1];
        round_key[i][2] = K[2], round_key[i][3] = K[3];
    }
}

static void ublock128128_enc_block(const std::uint64_t round_key[17][2],
                                   std::uint8_t        out[16],
                                   const std::uint8_t  in[16]) noexcept
{
    // X0||X1 <- X
    std::uint64_t X0 = MEM_LOAD64BE(in + 0);
    std::uint64_t X1 = MEM_LOAD64BE(in + 8);
    std::uint64_t RK0, RK1;
    for (int i = 0; i < 16; i++)
    {
        RK0 = round_key[i][0], RK1 = round_key[i][1];
        X0 = Sk_u64(X0 ^ RK0);
        X1 = Sk_u64(X1 ^ RK1);
        X1 = X1 ^ X0;
        X0 = X0 ^ rotl_u64_epi32(X1, 4);
        X1 = X1 ^ rotl_u64_epi32(X0, 8);
        X0 = X0 ^ rotl_u64_epi32(X1, 8);
        X1 = X1 ^ rotl_u64_epi32(X0, 20);
        X0 = X0 ^ X1;
        X0 = PL128_u64(X0);
        X1 = PR128_u64(X1);
    }
    // Y <- RKr ^ (X0||X1)
    std::uint64_t Y0 = round_key[16][0] ^ X0;
    std::uint64_t Y1 = round_key[16][1] ^ X1;
    MEM_STORE64BE(out + 0, Y0);
    MEM_STORE64BE(out + 8, Y1);
}

static void ublock128128_dec_block(const std::uint64_t round_key[17][2],
                                   std::uint8_t        out[16],
                                   const std::uint8_t  in[16]) noexcept
{
    // Y0||Y1 <- Y
    std::uint64_t Y0 = MEM_LOAD64BE(in + 0);
    std::uint64_t Y1 = MEM_LOAD64BE(in + 8);
    std::uint64_t RK0, RK1;
    for (int i = 16; i >= 1; i--)
    {
        RK0 = round_key[i][0], RK1 = round_key[i][1];
        Y0 = Y0 ^ RK0;
        Y1 = Y1 ^ RK1;
        Y0 = PL128I_u64(Y0);
        Y1 = PR128I_u64(Y1);
        Y0 = Y0 ^ Y1;
        Y1 = Y1 ^ rotl_u64_epi32(Y0, 20);
        Y0 = Y0 ^ rotl_u64_epi32(Y1, 8);
        Y1 = Y1 ^ rotl_u64_epi32(Y0, 8);
        Y0 = Y0 ^ rotl_u64_epi32(Y1, 4);
        Y1 = Y1 ^ Y0;
        Y0 = SIk_u64(Y0);
        Y1 = SIk_u64(Y1);
    }
    // X <- RK0 ^ (Y0||Y1)
    std::uint64_t X0 = round_key[0][0] ^ Y0;
    std::uint64_t X1 = round_key[0][1] ^ Y1;
    MEM_STORE64BE(out + 0, X0);
    MEM_STORE64BE(out + 8, X1);
}

static void ublock128256_enc_block(const std::uint64_t round_key[25][2],
                                   std::uint8_t        out[16],
                                   const std::uint8_t  in[16]) noexcept
{
    // X0||X1 <- X
    std::uint64_t X0 = MEM_LOAD64BE(in + 0);
    std::uint64_t X1 = MEM_LOAD64BE(in + 8);
    std::uint64_t RK0, RK1;
    for (int i = 0; i < 24; i++)
    {
        RK0 = round_key[i][0], RK1 = round_key[i][1];
        X0 = Sk_u64(X0 ^ RK0);
        X1 = Sk_u64(X1 ^ RK1);
        X1 = X1 ^ X0;
        X0 = X0 ^ rotl_u64_epi32(X1, 4);
        X1 = X1 ^ rotl_u64_epi32(X0, 8);
        X0 = X0 ^ rotl_u64_epi32(X1, 8);
        X1 = X1 ^ rotl_u64_epi32(X0, 20);
        X0 = X0 ^ X1;
        X0 = PL128_u64(X0);
        X1 = PR128_u64(X1);
    }
    // Y <- RKr ^ (X0||X1)
    std::uint64_t Y0 = round_key[24][0] ^ X0;
    std::uint64_t Y1 = round_key[24][1] ^ X1;
    MEM_STORE64BE(out + 0, Y0);
    MEM_STORE64BE(out + 8, Y1);
}

static void ublock128256_dec_block(const std::uint64_t round_key[25][2],
                                   std::uint8_t        out[16],
                                   const std::uint8_t  in[16]) noexcept
{
    // Y0||Y1 <- Y
    std::uint64_t Y0 = MEM_LOAD64BE(in + 0);
    std::uint64_t Y1 = MEM_LOAD64BE(in + 8);
    std::uint64_t RK0, RK1;
    for (int i = 24; i >= 1; i--)
    {
        RK0 = round_key[i][0], RK1 = round_key[i][1];
        Y0 = Y0 ^ RK0;
        Y1 = Y1 ^ RK1;
        Y0 = PL128I_u64(Y0);
        Y1 = PR128I_u64(Y1);
        Y0 = Y0 ^ Y1;
        Y1 = Y1 ^ rotl_u64_epi32(Y0, 20);
        Y0 = Y0 ^ rotl_u64_epi32(Y1, 8);
        Y1 = Y1 ^ rotl_u64_epi32(Y0, 8);
        Y0 = Y0 ^ rotl_u64_epi32(Y1, 4);
        Y1 = Y1 ^ Y0;
        Y0 = SIk_u64(Y0);
        Y1 = SIk_u64(Y1);
    }
    // X <- RK0 ^ (Y0||Y1)
    std::uint64_t X0 = round_key[0][0] ^ Y0;
    std::uint64_t X1 = round_key[0][1] ^ Y1;
    MEM_STORE64BE(out + 0, X0);
    MEM_STORE64BE(out + 8, X1);
}

static void ublock256256_enc_block(const std::uint64_t round_key[25][4],
                                   std::uint8_t        out[32],
                                   const std::uint8_t  in[32]) noexcept
{
    std::uint64_t X0[2], X1[2];
    X0[0] = MEM_LOAD64BE(in + 0);
    X0[1] = MEM_LOAD64BE(in + 8);
    X1[0] = MEM_LOAD64BE(in + 16);
    X1[1] = MEM_LOAD64BE(in + 24);
    for (int i = 0; i < 24; i++)
    {
        // X0 <- Sn(X0 ^ RK0)
        // X1 <- Sn(X1 ^ RK1)
        X0[0] = Sk_u64(X0[0] ^ round_key[i][0]);
        X0[1] = Sk_u64(X0[1] ^ round_key[i][1]);
        X1[0] = Sk_u64(X1[0] ^ round_key[i][2]);
        X1[1] = Sk_u64(X1[1] ^ round_key[i][3]);

        X1[0] = X1[0] ^ X0[0], X1[1] = X1[1] ^ X0[1];
        X0[0] = X0[0] ^ rotl_u64_epi32(X1[0], 4),
        X0[1] = X0[1] ^ rotl_u64_epi32(X1[1], 4);
        X1[0] = X1[0] ^ rotl_u64_epi32(X0[0], 8),
        X1[1] = X1[1] ^ rotl_u64_epi32(X0[1], 8);
        X0[0] = X0[0] ^ rotl_u64_epi32(X1[0], 8),
        X0[1] = X0[1] ^ rotl_u64_epi32(X1[1], 8);
        X1[0] = X1[0] ^ rotl_u64_epi32(X0[0], 20),
        X1[1] = X1[1] ^ rotl_u64_epi32(X0[1], 20);
        X0[0] = X0[0] ^ X1[0], X0[1] = X0[1] ^ X1[1];
        PL256_u128(X0);
        PR256_u128(X1);
    }
    std::uint64_t Y0[2], Y1[2];
    Y0[0] = X0[0] ^ round_key[24][0];
    Y0[1] = X0[1] ^ round_key[24][1];
    Y1[0] = X1[0] ^ round_key[24][2];
    Y1[1] = X1[1] ^ round_key[24][3];
    MEM_STORE64BE(out + 0, Y0[0]);
    MEM_STORE64BE(out + 8, Y0[1]);
    MEM_STORE64BE(out + 16, Y1[0]);
    MEM_STORE64BE(out + 24, Y1[1]);
}

static void ublock256256_dec_block(const std::uint64_t round_key[25][4],
                                   std::uint8_t        out[32],
                                   const std::uint8_t  in[32]) noexcept
{
    std::uint64_t Y0[2], Y1[2];
    Y0[0] = MEM_LOAD64BE(in + 0);
    Y0[1] = MEM_LOAD64BE(in + 8);
    Y1[0] = MEM_LOAD64BE(in + 16);
    Y1[1] = MEM_LOAD64BE(in + 24);
    for (int i = 24; i >= 1; i--)
    {
        Y0[0] = Y0[0] ^ round_key[i][0];
        Y0[1] = Y0[1] ^ round_key[i][1];
        Y1[0] = Y1[0] ^ round_key[i][2];
        Y1[1] = Y1[1] ^ round_key[i][3];
        PL256I_u128(Y0);
        PR256I_u128(Y1);

        Y0[0] = Y0[0] ^ Y1[0], Y0[1] = Y0[1] ^ Y1[1];
        Y1[0] = Y1[0] ^ rotl_u64_epi32(Y0[0], 20),
        Y1[1] = Y1[1] ^ rotl_u64_epi32(Y0[1], 20);
        Y0[0] = Y0[0] ^ rotl_u64_epi32(Y1[0], 8),
        Y0[1] = Y0[1] ^ rotl_u64_epi32(Y1[1], 8);
        Y1[0] = Y1[0] ^ rotl_u64_epi32(Y0[0], 8),
        Y1[1] = Y1[1] ^ rotl_u64_epi32(Y0[1], 8);
        Y0[0] = Y0[0] ^ rotl_u64_epi32(Y1[0], 4),
        Y0[1] = Y0[1] ^ rotl_u64_epi32(Y1[1], 4);
        Y1[0] = Y1[0] ^ Y0[0], Y1[1] = Y1[1] ^ Y0[1];

        Y0[0] = SIk_u64(Y0[0]);
        Y0[1] = SIk_u64(Y0[1]);
        Y1[0] = SIk_u64(Y1[0]);
        Y1[1] = SIk_u64(Y1[1]);
    }
    std::uint64_t X0[2], X1[2];
    X0[0] = Y0[0] ^ round_key[0][0];
    X0[1] = Y0[1] ^ round_key[0][1];
    X1[0] = Y1[0] ^ round_key[0][2];
    X1[1] = Y1[1] ^ round_key[0][3];
    MEM_STORE64BE(out + 0, X0[0]);
    MEM_STORE64BE(out + 8, X0[1]);
    MEM_STORE64BE(out + 16, X1[0]);
    MEM_STORE64BE(out + 24, X1[1]);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************** UBLOCK COMMON API *****************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

// ****************************************
// ********** uBlock 128/128 **************
// ****************************************

void ublock128128_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept
{
    ublock128128_key_init(ctx->m.sub_key128128, user_key);
}

void ublock128128_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept
{
    ublock128128_key_init(ctx->m.sub_key128128, user_key);
}

void ublock128128_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept
{
    ublock128128_enc_block(ctx->m.sub_key128128, ciphertext, plaintext);
}

void ublock128128_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept
{
    ublock128128_dec_block(ctx->m.sub_key128128, plaintext, ciphertext);
}

void ublock128128_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        ublock128128_enc_block(ctx->m.sub_key128128, ciphertext, plaintext);
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
        ublock128128_dec_block(ctx->m.sub_key128128, plaintext, ciphertext);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** uBlock 128/256 **************
// ****************************************

void ublock128256_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    ublock128256_key_init(ctx->m.sub_key128256, user_key);
}

void ublock128256_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    ublock128256_key_init(ctx->m.sub_key128256, user_key);
}

void ublock128256_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept
{
    ublock128256_enc_block(ctx->m.sub_key128256, ciphertext, plaintext);
}

void ublock128256_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept
{
    ublock128256_dec_block(ctx->m.sub_key128256, plaintext, ciphertext);
}

void ublock128256_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        ublock128256_enc_block(ctx->m.sub_key128256, ciphertext, plaintext);
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
        ublock128256_dec_block(ctx->m.sub_key128256, plaintext, ciphertext);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** uBlock 256/256 **************
// ****************************************

void ublock256256_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    ublock256256_key_init(ctx->m.sub_key256256, user_key);
}

void ublock256256_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept
{
    ublock256256_key_init(ctx->m.sub_key256256, user_key);
}

void ublock256256_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[32],
                            const std::uint8_t plaintext[32]) noexcept
{
    ublock256256_enc_block(ctx->m.sub_key256256, ciphertext, plaintext);
}

void ublock256256_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[32],
                            const std::uint8_t ciphertext[32]) noexcept
{
    ublock256256_dec_block(ctx->m.sub_key256256, plaintext, ciphertext);
}

void ublock256256_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        ublock256256_enc_block(ctx->m.sub_key256256, ciphertext, plaintext);
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
        ublock256256_dec_block(ctx->m.sub_key256256, plaintext, ciphertext);
        plaintext += 32, ciphertext += 32, block_num--;
    }
}

} // namespace ublock::internal::common
