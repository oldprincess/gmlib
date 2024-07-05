#if defined(CPU_FLAG_SHA) && defined(CPU_FLAG_SSE4_1)

#ifndef SHA1_INTERNAL_SHA1_SHA_H
#define SHA1_INTERNAL_SHA1_SHA_H

#include <cstddef>
#include <cstdint>

namespace sha1::internal::sha {

constexpr std::size_t SHA1_BLOCK_SIZE        = 64;
constexpr std::size_t SHA1_DIGEST_SIZE       = 20;
constexpr std::size_t SHA1_SECURITY_STRENGTH = 10;

typedef struct Sha1CTX
{
    std::uint32_t state[5];
    std::uint64_t data_bits;
} Sha1CTX;

void sha1_init(Sha1CTX* ctx) noexcept;

void sha1_reset(Sha1CTX* ctx) noexcept;

int sha1_update_blocks(Sha1CTX*            ctx,
                       const std::uint8_t* in,
                       std::size_t         block_num) noexcept;

int sha1_final_block(Sha1CTX*            ctx,
                     std::uint8_t        digest[32],
                     const std::uint8_t* in,
                     std::size_t         inl) noexcept;

} // namespace sha1::internal::sha

#endif

#endif