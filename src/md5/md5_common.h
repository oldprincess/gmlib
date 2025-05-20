#ifndef MD5_INTERNAL_MD5_COMMON_H
#define MD5_INTERNAL_MD5_COMMON_H

#include <cstddef>
#include <cstdint>

namespace md5::internal::common {

constexpr const char* MD5_ALGO_NAME = "common";

constexpr std::size_t MD5_BLOCK_SIZE        = 64;
constexpr std::size_t MD5_DIGEST_SIZE       = 16;
constexpr std::size_t MD5_SECURITY_STRENGTH = 8;

void md5_init(std::uint32_t state[4], std::uint64_t* data_bits) noexcept;

void md5_reset(std::uint32_t state[4], std::uint64_t* data_bits) noexcept;

void md5_update_blocks(std::uint32_t       state[4],
                       std::uint64_t*      data_bits,
                       const std::uint8_t* in,
                       std::size_t         block_num) noexcept;

void md5_final_block(std::uint32_t       state[4],
                     std::uint64_t*      data_bits,
                     std::uint8_t        digest[16],
                     const std::uint8_t* in,
                     std::size_t         inl) noexcept;

} // namespace md5::internal::common

#endif