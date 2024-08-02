#ifndef MD5_INTERNAL_MD5_COMMON_H
#define MD5_INTERNAL_MD5_COMMON_H

#include <cstddef>
#include <cstdint>

namespace md5::internal::common {

constexpr std::size_t MD5_BLOCK_SIZE        = 64;
constexpr std::size_t MD5_DIGEST_SIZE       = 16;
constexpr std::size_t MD5_SECURITY_STRENGTH = 8;

typedef struct Md5CTX
{
    std::uint32_t state[4];
    std::uint64_t data_bits;
} Md5CTX;

void md5_init(Md5CTX* ctx) noexcept;

void md5_reset(Md5CTX* ctx) noexcept;

void md5_update_blocks(Md5CTX*             ctx,
                       const std::uint8_t* in,
                       std::size_t         block_num) noexcept;

void md5_final_block(Md5CTX*             ctx,
                     std::uint8_t        digest[16],
                     const std::uint8_t* in,
                     std::size_t         inl) noexcept;

} // namespace md5::internal::common

#endif