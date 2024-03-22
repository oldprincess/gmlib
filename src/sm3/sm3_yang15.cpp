#if defined(SUPPORT_SM3_YANG15)
#include <gmlib/sm3/internal/sm3_yang15.h>

#include <cstring>

namespace sm3::internal::yang15 {

#define MEM_LOAD32BE(src)                                 \
    (((std::uint32_t)(((std::uint8_t*)(src))[0]) << 24) | \
     ((std::uint32_t)(((std::uint8_t*)(src))[1]) << 16) | \
     ((std::uint32_t)(((std::uint8_t*)(src))[2]) << 8) |  \
     ((std::uint32_t)(((std::uint8_t*)(src))[3]) << 0))

#define MEM_STORE32BE(dst, a)                                       \
    (((std::uint8_t*)(dst))[0] = ((std::uint32_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t*)(dst))[1] = ((std::uint32_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t*)(dst))[2] = ((std::uint32_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t*)(dst))[3] = ((std::uint32_t)(a) >> 0) & 0xFF)

#define MEM_STORE64BE(dst, a)                                       \
    (((std::uint8_t*)(dst))[0] = ((std::uint64_t)(a) >> 56) & 0xFF, \
     ((std::uint8_t*)(dst))[1] = ((std::uint64_t)(a) >> 48) & 0xFF, \
     ((std::uint8_t*)(dst))[2] = ((std::uint64_t)(a) >> 40) & 0xFF, \
     ((std::uint8_t*)(dst))[3] = ((std::uint64_t)(a) >> 32) & 0xFF, \
     ((std::uint8_t*)(dst))[4] = ((std::uint64_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t*)(dst))[5] = ((std::uint64_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t*)(dst))[6] = ((std::uint64_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t*)(dst))[7] = ((std::uint64_t)(a) >> 0) & 0xFF)

static inline std::uint32_t rotl(std::uint32_t x, int n) noexcept
{
    return (x << n) | (x >> (32 - n));
}

static inline std::uint32_t P0(std::uint32_t x) noexcept
{
    return x ^ rotl(x, 9) ^ rotl(x, 17);
}

static inline std::uint32_t P1(std::uint32_t x) noexcept
{
    return x ^ rotl(x, 15) ^ rotl(x, 23);
}

#define FF00(x, y, z) ((x) ^ (y) ^ (z))
#define FF16(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define GG00(x, y, z) ((x) ^ (y) ^ (z))
#define GG16(x, y, z) ((((y) ^ (z)) & (x)) ^ (z))

#define R(A, B, C, D, E, F, G, H, xx)                                      \
    do                                                                     \
    {                                                                      \
        std::uint32_t SS1 = rotl((rotl(A, 12) + E + T[j]), 7);             \
        std::uint32_t SS2 = SS1 ^ rotl(A, 12);                             \
        std::uint32_t TT1 = FF##xx(A, B, C) + D + SS2 + (W[j] ^ W[j + 4]); \
        std::uint32_t TT2 = GG##xx(E, F, G) + H + SS1 + W[j];              \
        B                 = rotl(B, 9);                                    \
        D                 = TT1;                                           \
        F                 = rotl(F, 19);                                   \
        H                 = P0(TT2);                                       \
        j++;                                                               \
    } while (0)

#define R4(A, B, C, D, E, F, G, H, xx) \
    R(A, B, C, D, E, F, G, H, xx);     \
    R(D, A, B, C, H, E, F, G, xx);     \
    R(C, D, A, B, G, H, E, F, xx);     \
    R(B, C, D, A, F, G, H, E, xx)

static const std::uint32_t T[64] = {
    0x79cc4519U, 0xf3988a32U, 0xe7311465U, 0xce6228cbU, 0x9cc45197U,
    0x3988a32fU, 0x7311465eU, 0xe6228cbcU, 0xcc451979U, 0x988a32f3U,
    0x311465e7U, 0x6228cbceU, 0xc451979cU, 0x88a32f39U, 0x11465e73U,
    0x228cbce6U, 0x9d8a7a87U, 0x3b14f50fU, 0x7629ea1eU, 0xec53d43cU,
    0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U, 0xc53d43ceU, 0x8a7a879dU,
    0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU, 0xa7a879d8U, 0x4f50f3b1U,
    0x9ea1e762U, 0x3d43cec5U, 0x7a879d8aU, 0xf50f3b14U, 0xea1e7629U,
    0xd43cec53U, 0xa879d8a7U, 0x50f3b14fU, 0xa1e7629eU, 0x43cec53dU,
    0x879d8a7aU, 0x0f3b14f5U, 0x1e7629eaU, 0x3cec53d4U, 0x79d8a7a8U,
    0xf3b14f50U, 0xe7629ea1U, 0xcec53d43U, 0x9d8a7a87U, 0x3b14f50fU,
    0x7629ea1eU, 0xec53d43cU, 0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U,
    0xc53d43ceU, 0x8a7a879dU, 0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU,
    0xa7a879d8U, 0x4f50f3b1U, 0x9ea1e762U, 0x3d43cec5U,
};

void sm3_init(Sm3CTX* ctx) noexcept
{
    static const std::uint32_t SM3_INIT_DIGEST[8] = {
        0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600,
        0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E,
    };
    ctx->state[0]  = SM3_INIT_DIGEST[0];
    ctx->state[1]  = SM3_INIT_DIGEST[1];
    ctx->state[2]  = SM3_INIT_DIGEST[2];
    ctx->state[3]  = SM3_INIT_DIGEST[3];
    ctx->state[4]  = SM3_INIT_DIGEST[4];
    ctx->state[5]  = SM3_INIT_DIGEST[5];
    ctx->state[6]  = SM3_INIT_DIGEST[6];
    ctx->state[7]  = SM3_INIT_DIGEST[7];
    ctx->data_bits = 0;
}

void sm3_reset(Sm3CTX* ctx) noexcept
{
    sm3_init(ctx);
}

static void sm3_compress_block(std::uint32_t      state[8],
                               const std::uint8_t data[64]) noexcept
{
    std::uint32_t A, B, C, D, E, F, G, H;
    std::uint32_t W[68];

    A = state[0];
    B = state[1];
    C = state[2];
    D = state[3];
    E = state[4];
    F = state[5];
    G = state[6];
    H = state[7];

    for (int i = 0; i < 16; i++)
    {
        W[i] = MEM_LOAD32BE(data + 4 * i);
    }
    for (int j = 16; j < 68; j++)
    {
        W[j] = P1(W[j - 16] ^ W[j - 9] ^ rotl(W[j - 3], 15)) ^
               rotl(W[j - 13], 7) ^ W[j - 6];
    }

    int j = 0;
    for (int t = 0; t < 4; t++)
    {
        R4(A, B, C, D, E, F, G, H, 00);
    }
    for (int t = 0; t < 12; t++)
    {
        R4(A, B, C, D, E, F, G, H, 16);
    }
    state[0] ^= A;
    state[1] ^= B;
    state[2] ^= C;
    state[3] ^= D;
    state[4] ^= E;
    state[5] ^= F;
    state[6] ^= G;
    state[7] ^= H;
}

int sm3_update_blocks(Sm3CTX*             ctx,
                      const std::uint8_t* data,
                      std::size_t         block_num) noexcept
{
    if (block_num > UINT64_MAX / 512)
    {
        return -1;
    }
    std::uint64_t nxt_bits = block_num * 512 + ctx->data_bits;
    if (nxt_bits < ctx->data_bits)
    {
        return -1;
    }
    ctx->data_bits = nxt_bits;
    while (block_num)
    {
        sm3_compress_block(ctx->state, data);
        data += 64, block_num -= 1;
    }
    return 0;
}

int sm3_final_block(Sm3CTX*             ctx,
                    std::uint8_t        digest[32],
                    const std::uint8_t* in,
                    std::size_t         inl) noexcept
{
    std::uint64_t nxt_bits = inl * 8 + ctx->data_bits;
    if (nxt_bits < ctx->data_bits)
    {
        return -1;
    }
    ctx->data_bits = nxt_bits;

    std::size_t  pad_num = (64ULL + 56 - 1 - inl) % 64;
    std::uint8_t buf[64 * 2];
    std::size_t  buf_size = 0;
    std::memcpy(buf, in, inl);
    buf_size += inl;                               // update
    buf[buf_size] = 0x80;                          // 10..0
    buf_size += 1;                                 // update
    std::memset(buf + buf_size, 0, pad_num);       // pad 0
    buf_size += pad_num;                           // update
    MEM_STORE64BE(buf + buf_size, ctx->data_bits); //
    buf_size += 8;                                 // update
    // compress
    for (std::size_t i = 0; i < buf_size; i += 64)
    {
        sm3_compress_block(ctx->state, buf + i);
    }
    // output digest
    for (int i = 0; i < 8; i++)
    {
        MEM_STORE32BE(digest + 4 * i, ctx->state[i]);
    }
    return 0;
}

}; // namespace sm3::internal::yang15
#endif