#ifndef GHASH_INTERNAL_GHASH_LUT256_H
#define GHASH_INTERNAL_GHASH_LUT256_H

#include <cstddef>
#include <cstdint>

namespace ghash::internal::lut256 {

constexpr std::size_t GHASH_BLOCK_SIZE  = 16;
constexpr std::size_t GHASH_DIGEST_SIZE = 16;

typedef struct GHashCTX
{
    std::uint64_t T[256][2];
    std::uint64_t state[2];
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

} // namespace ghash::internal::lut256

#endif