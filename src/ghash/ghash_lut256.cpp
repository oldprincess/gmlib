#include <gmlib/ghash/internal/ghash_lut256.h>

namespace ghash::internal::lut256 {

#define MEM_LOAD64BE(src)                       \
    (((uint64_t)(((uint8_t*)(src))[0]) << 56) | \
     ((uint64_t)(((uint8_t*)(src))[1]) << 48) | \
     ((uint64_t)(((uint8_t*)(src))[2]) << 40) | \
     ((uint64_t)(((uint8_t*)(src))[3]) << 32) | \
     ((uint64_t)(((uint8_t*)(src))[4]) << 24) | \
     ((uint64_t)(((uint8_t*)(src))[5]) << 16) | \
     ((uint64_t)(((uint8_t*)(src))[6]) << 8) |  \
     ((uint64_t)(((uint8_t*)(src))[7]) << 0))

#define MEM_STORE64BE(dst, a)                             \
    (((uint8_t*)(dst))[0] = ((uint64_t)(a) >> 56) & 0xFF, \
     ((uint8_t*)(dst))[1] = ((uint64_t)(a) >> 48) & 0xFF, \
     ((uint8_t*)(dst))[2] = ((uint64_t)(a) >> 40) & 0xFF, \
     ((uint8_t*)(dst))[3] = ((uint64_t)(a) >> 32) & 0xFF, \
     ((uint8_t*)(dst))[4] = ((uint64_t)(a) >> 24) & 0xFF, \
     ((uint8_t*)(dst))[5] = ((uint64_t)(a) >> 16) & 0xFF, \
     ((uint8_t*)(dst))[6] = ((uint64_t)(a) >> 8) & 0xFF,  \
     ((uint8_t*)(dst))[7] = ((uint64_t)(a) >> 0) & 0xFF)

static const uint16_t REDUCE_TABLE[256] = {
    0x0000, 0x01c2, 0x0384, 0x0246, 0x0708, 0x06ca, 0x048c, 0x054e, 0x0e10,
    0x0fd2, 0x0d94, 0x0c56, 0x0918, 0x08da, 0x0a9c, 0x0b5e, 0x1c20, 0x1de2,
    0x1fa4, 0x1e66, 0x1b28, 0x1aea, 0x18ac, 0x196e, 0x1230, 0x13f2, 0x11b4,
    0x1076, 0x1538, 0x14fa, 0x16bc, 0x177e, 0x3840, 0x3982, 0x3bc4, 0x3a06,
    0x3f48, 0x3e8a, 0x3ccc, 0x3d0e, 0x3650, 0x3792, 0x35d4, 0x3416, 0x3158,
    0x309a, 0x32dc, 0x331e, 0x2460, 0x25a2, 0x27e4, 0x2626, 0x2368, 0x22aa,
    0x20ec, 0x212e, 0x2a70, 0x2bb2, 0x29f4, 0x2836, 0x2d78, 0x2cba, 0x2efc,
    0x2f3e, 0x7080, 0x7142, 0x7304, 0x72c6, 0x7788, 0x764a, 0x740c, 0x75ce,
    0x7e90, 0x7f52, 0x7d14, 0x7cd6, 0x7998, 0x785a, 0x7a1c, 0x7bde, 0x6ca0,
    0x6d62, 0x6f24, 0x6ee6, 0x6ba8, 0x6a6a, 0x682c, 0x69ee, 0x62b0, 0x6372,
    0x6134, 0x60f6, 0x65b8, 0x647a, 0x663c, 0x67fe, 0x48c0, 0x4902, 0x4b44,
    0x4a86, 0x4fc8, 0x4e0a, 0x4c4c, 0x4d8e, 0x46d0, 0x4712, 0x4554, 0x4496,
    0x41d8, 0x401a, 0x425c, 0x439e, 0x54e0, 0x5522, 0x5764, 0x56a6, 0x53e8,
    0x522a, 0x506c, 0x51ae, 0x5af0, 0x5b32, 0x5974, 0x58b6, 0x5df8, 0x5c3a,
    0x5e7c, 0x5fbe, 0xe100, 0xe0c2, 0xe284, 0xe346, 0xe608, 0xe7ca, 0xe58c,
    0xe44e, 0xef10, 0xeed2, 0xec94, 0xed56, 0xe818, 0xe9da, 0xeb9c, 0xea5e,
    0xfd20, 0xfce2, 0xfea4, 0xff66, 0xfa28, 0xfbea, 0xf9ac, 0xf86e, 0xf330,
    0xf2f2, 0xf0b4, 0xf176, 0xf438, 0xf5fa, 0xf7bc, 0xf67e, 0xd940, 0xd882,
    0xdac4, 0xdb06, 0xde48, 0xdf8a, 0xddcc, 0xdc0e, 0xd750, 0xd692, 0xd4d4,
    0xd516, 0xd058, 0xd19a, 0xd3dc, 0xd21e, 0xc560, 0xc4a2, 0xc6e4, 0xc726,
    0xc268, 0xc3aa, 0xc1ec, 0xc02e, 0xcb70, 0xcab2, 0xc8f4, 0xc936, 0xcc78,
    0xcdba, 0xcffc, 0xce3e, 0x9180, 0x9042, 0x9204, 0x93c6, 0x9688, 0x974a,
    0x950c, 0x94ce, 0x9f90, 0x9e52, 0x9c14, 0x9dd6, 0x9898, 0x995a, 0x9b1c,
    0x9ade, 0x8da0, 0x8c62, 0x8e24, 0x8fe6, 0x8aa8, 0x8b6a, 0x892c, 0x88ee,
    0x83b0, 0x8272, 0x8034, 0x81f6, 0x84b8, 0x857a, 0x873c, 0x86fe, 0xa9c0,
    0xa802, 0xaa44, 0xab86, 0xaec8, 0xaf0a, 0xad4c, 0xac8e, 0xa7d0, 0xa612,
    0xa454, 0xa596, 0xa0d8, 0xa11a, 0xa35c, 0xa29e, 0xb5e0, 0xb422, 0xb664,
    0xb7a6, 0xb2e8, 0xb32a, 0xb16c, 0xb0ae, 0xbbf0, 0xba32, 0xb874, 0xb9b6,
    0xbcf8, 0xbd3a, 0xbf7c, 0xbebe,
};

// 0b1100_1001 -> 0b1001_0011
static const int REV_U8[256] = {
    0,  128, 64, 192, 32, 160, 96,  224, 16, 144, 80, 208, 48, 176, 112, 240,
    8,  136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248,
    4,  132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244,
    12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252,
    2,  130, 66, 194, 34, 162, 98,  226, 18, 146, 82, 210, 50, 178, 114, 242,
    10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250,
    6,  134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246,
    14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254,
    1,  129, 65, 193, 33, 161, 97,  225, 17, 145, 81, 209, 49, 177, 113, 241,
    9,  137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249,
    5,  133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245,
    13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253,
    3,  131, 67, 195, 35, 163, 99,  227, 19, 147, 83, 211, 51, 179, 115, 243,
    11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251,
    7,  135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247,
    15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255,
};

static void gf128_init_lut_table(std::uint64_t      T[256][2],
                                 const std::uint8_t H[16]) noexcept
{
    uint64_t Hh, Hl;
    Hh = MEM_LOAD64BE(H);
    Hl = MEM_LOAD64BE(H + 8);
    // init HTable[0], HTable[1]
    T[0][0] = 0, T[0][1] = 0;
    T[REV_U8[1]][0] = Hh, T[REV_U8[1]][1] = Hl;
    for (int i = 2; i < 256; i++)
    {
        // odd: M(i) = M(i-1) + M(1)
        if (i & 1)
        {
            T[REV_U8[i]][0] = T[REV_U8[i - 1]][0] ^ T[REV_U8[1]][0];
            T[REV_U8[i]][1] = T[REV_U8[i - 1]][1] ^ T[REV_U8[1]][1];
        }
        // even: M(i) = M(i/2) * x
        else
        {
            uint64_t* m = T[REV_U8[i / 2]];
            // R = 1110 0001 | 0(120)
            uint64_t Rh = (uint64_t)0b11100001 << (64 - 8);
            //  >> 1
            T[REV_U8[i]][1] = (m[0] << 63) | (m[1] >> 1);
            T[REV_U8[i]][0] = m[0] >> 1;
            // mod
            if (m[1] & 1)
            {
                T[REV_U8[i]][0] ^= Rh;
            }
        }
    }
}

void ghash_init(GHashCTX* ctx, const std::uint8_t H[16]) noexcept
{
    ctx->state[0] = 0;
    ctx->state[1] = 0;
    gf128_init_lut_table(ctx->T, H);
}

void ghash_reset(GHashCTX* ctx) noexcept
{
    ctx->state[0] = 0;
    ctx->state[1] = 0;
}

void ghash_update_blocks(GHashCTX*           ctx,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept
{
    std::uint64_t X[2], R[2];
    const std::uint64_t(*T)[2] = ctx->T;
    while (block_num)
    {
#define GMUL128_ROUND(s)                                                      \
    do                                                                        \
    {                                                                         \
        std::uint8_t rem;                                                     \
        rem  = R[1] & 0xFF;                                                   \
        R[1] = (R[0] << 56) | (R[1] >> 8);                                    \
        R[0] = (R[0] >> 8) ^ ((std::uint64_t)REDUCE_TABLE[rem] << (64 - 16)); \
        R[0] ^= T[(X[1 - (s / 8)] >> (8 * (s % 8))) & 0xFF][0];               \
        R[1] ^= T[(X[1 - (s / 8)] >> (8 * (s % 8))) & 0xFF][1];               \
    } while (0)

        X[0] = ctx->state[0] ^ MEM_LOAD64BE(in);
        X[1] = ctx->state[1] ^ MEM_LOAD64BE(in + 8);

        R[0] = T[X[1] & 0xFF][0];
        R[1] = T[X[1] & 0xFF][1];
        GMUL128_ROUND(1);
        GMUL128_ROUND(2);
        GMUL128_ROUND(3);
        GMUL128_ROUND(4);
        GMUL128_ROUND(5);
        GMUL128_ROUND(6);
        GMUL128_ROUND(7);
        GMUL128_ROUND(8);
        GMUL128_ROUND(9);
        GMUL128_ROUND(10);
        GMUL128_ROUND(11);
        GMUL128_ROUND(12);
        GMUL128_ROUND(13);
        GMUL128_ROUND(14);
        GMUL128_ROUND(15);

        ctx->state[0] = R[0];
        ctx->state[1] = R[1];
#undef GMUL128_ROUND
        in += 16, block_num--;
    }
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
    MEM_STORE64BE(digest, ctx->state[0]);
    MEM_STORE64BE(digest + 8, ctx->state[1]);
    return 0;
}

} // namespace ghash::internal::lut256
