#ifndef SHA1_INTERNAL_SHA1_COMMON_H
#define SHA1_INTERNAL_SHA1_COMMON_H

#include <cstddef>
#include <cstdint>

namespace sha1::internal::common {

constexpr const char* SHA1_ALGO_NAME = "common";

constexpr std::size_t SHA1_BLOCK_SIZE        = 64;
constexpr std::size_t SHA1_DIGEST_SIZE       = 20;
constexpr std::size_t SHA1_SECURITY_STRENGTH = 10;

void sha1_init(std::uint32_t state[5], std::uint64_t* data_bits) noexcept;

void sha1_reset(std::uint32_t state[5], std::uint64_t* data_bits) noexcept;

int sha1_update_blocks(std::uint32_t       state[5],
                       std::uint64_t*      data_bits,
                       const std::uint8_t* in,
                       std::size_t         block_num) noexcept;

int sha1_final_block(std::uint32_t       state[5],
                     std::uint64_t*      data_bits,
                     std::uint8_t        digest[32],
                     const std::uint8_t* in,
                     std::size_t         inl) noexcept;

} // namespace sha1::internal::common

#endif
