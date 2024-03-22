#include <gmlib/ghash/internal/ghash_common.h>

namespace ghash::internal::common {

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

void ghash_init(GHashCTX* ctx, const std::uint8_t H[16]) noexcept
{
    ctx->H[0]     = MEM_LOAD64BE(H);
    ctx->H[1]     = MEM_LOAD64BE(H + 8);
    ctx->state[0] = 0;
    ctx->state[1] = 0;
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
    constexpr std::uint64_t Rh = 0xE100000000000000ULL;
    while (block_num)
    {
        std::uint64_t Xh = ctx->state[0] ^ MEM_LOAD64BE(in);
        std::uint64_t Xl = ctx->state[1] ^ MEM_LOAD64BE(in + 8);
        std::uint64_t Vh = ctx->H[0], Vl = ctx->H[1];
        std::uint64_t Zh = 0, Zl = 0, MASK;
        for (int i = 63; i >= 0; i--)
        {
            // IF X_bit[i] IS 1: Z = Z xor V
            if (Xh & 0x8000000000000000ULL)
            {
                Zh ^= Vh, Zl ^= Vl;
            }
            Xh <<= 1;
            MASK = (std::uint64_t)(-(std::int64_t)(Vl & 1));
            Vl   = (Vh << 63) | (Vl >> 1);
            Vh   = (Rh & MASK) ^ (Vh >> 1);
        }
        for (int i = 63; i >= 0; i--)
        {
            // IF X_bit[i] IS 1: Z = Z xor V
            if (Xl & 0x8000000000000000ULL)
            {
                Zh ^= Vh, Zl ^= Vl;
            }
            Xl <<= 1;
            MASK = (std::uint64_t)(-(std::int64_t)(Vl & 1));
            Vl   = (Vh << 63) | (Vl >> 1);
            Vh   = (Rh & MASK) ^ (Vh >> 1);
        }
        ctx->state[0] = Zh;
        ctx->state[1] = Zl;

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

} // namespace ghash::internal::common
