#include <gmlib/sm3/internal/sm3_common.h>

#include <cstring>

namespace sm3::internal::common {

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
#define T00           0x79cc4519U
#define T16           0x7a879d8aU

#define R(A, B, C, D, E, F, G, H, xx)                                         \
    do                                                                        \
    {                                                                         \
        std::uint32_t SS1 = rotl((rotl(A, 12) + E + rotl(T##xx, j % 32)), 7); \
        std::uint32_t SS2 = SS1 ^ rotl(A, 12);                                \
        std::uint32_t TT1 = FF##xx(A, B, C) + D + SS2 + W_[j];                \
        std::uint32_t TT2 = GG##xx(E, F, G) + H + SS1 + W[j];                 \
        D                 = C;                                                \
        C                 = rotl(B, 9);                                       \
        B                 = A;                                                \
        A                 = TT1;                                              \
        H                 = G;                                                \
        G                 = rotl(F, 19);                                      \
        F                 = E;                                                \
        E                 = P0(TT2);                                          \
    } while (0)

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
    std::uint32_t W[68], W_[64];

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
    for (int j = 0; j < 64; j++)
    {
        W_[j] = W[j] ^ W[j + 4];
    }

    for (int j = 0; j < 16; j++)
    {
        R(A, B, C, D, E, F, G, H, 00);
    }
    for (int j = 16; j < 64; j++)
    {
        R(A, B, C, D, E, F, G, H, 16);
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

}; // namespace sm3::internal::common
