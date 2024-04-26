#if defined(SUPPORT_SM3_YANG15)
#ifndef SM3_INTERNAL_SM3_YANG15_H
#define SM3_INTERNAL_SM3_YANG15_H

#include <cstddef>
#include <cstdint>

namespace sm3::internal::yang15 {

constexpr std::size_t SM3_BLOCK_SIZE        = 64;
constexpr std::size_t SM3_DIGEST_SIZE       = 32;
constexpr std::size_t SM3_SECURITY_STRENGTH = 16;

typedef struct Sm3CTX
{
    std::uint32_t state[8];
    std::uint64_t data_bits;
} Sm3CTX;

void sm3_init(Sm3CTX* ctx) noexcept;

void sm3_reset(Sm3CTX* ctx) noexcept;

int sm3_update_blocks(Sm3CTX*             ctx,
                      const std::uint8_t* in,
                      std::size_t         block_num) noexcept;

int sm3_final_block(Sm3CTX*             ctx,
                    std::uint8_t        digest[32],
                    const std::uint8_t* in,
                    std::size_t         inl) noexcept;

} // namespace sm3::internal::yang15

#endif
#endif