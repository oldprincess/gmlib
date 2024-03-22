#if defined(CPU_FLAG_PCLMUL) && defined(CPU_FLAG_SSE2)
#ifndef GHASH_INTERNAL_GHASH_PCLMUL_H
#define GHASH_INTERNAL_GHASH_PCLMUL_H

#include <cstddef>
#include <cstdint>

namespace ghash::internal::pclmul {

constexpr std::size_t GHASH_BLOCK_SIZE  = 16;
constexpr std::size_t GHASH_DIGEST_SIZE = 16;

typedef struct GHashCTX
{
    std::uint8_t H[16];
    std::uint8_t state[16];
} GHashCTX;

void ghash_init(GHashCTX* ctx, const std::uint8_t H[16]) noexcept;

void ghash_reset(GHashCTX* ctx) noexcept;

void ghash_update_blocks(GHashCTX*           ctx,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept;

int ghash_final_block(const GHashCTX*     ctx,
                      std::uint8_t        digest[16],
                      const std::uint8_t* in,
                      std::size_t         inl) noexcept;

} // namespace ghash::internal::pclmul
#endif
#endif