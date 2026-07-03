#ifndef SHA2_COMMON_H
#define SHA2_COMMON_H

#include <cstddef>
#include <cstdint>

namespace sha2 {
namespace internal {
namespace common {

constexpr const char* SHA2_ALGO_NAME = "common";

constexpr std::size_t SHA224_BLOCK_SIZE        = 64;
constexpr std::size_t SHA224_DIGEST_SIZE       = 28;
constexpr std::size_t SHA224_SECURITY_STRENGTH = 14;

constexpr std::size_t SHA256_BLOCK_SIZE        = 64;
constexpr std::size_t SHA256_DIGEST_SIZE       = 32;
constexpr std::size_t SHA256_SECURITY_STRENGTH = 16;

constexpr std::size_t SHA384_BLOCK_SIZE        = 128;
constexpr std::size_t SHA384_DIGEST_SIZE       = 48;
constexpr std::size_t SHA384_SECURITY_STRENGTH = 24;

constexpr std::size_t SHA512_BLOCK_SIZE        = 128;
constexpr std::size_t SHA512_DIGEST_SIZE       = 64;
constexpr std::size_t SHA512_SECURITY_STRENGTH = 32;

void sha224_init(std::uint8_t state[32], std::uint64_t* data_bits) noexcept;

void sha224_reset(std::uint8_t state[32], std::uint64_t* data_bits) noexcept;

int sha224_update_blocks(std::uint8_t        state[32],
                         std::uint64_t*      data_bits,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept;

int sha224_final_block(std::uint8_t        state[32],
                       std::uint64_t*      data_bits,
                       std::uint8_t        digest[28],
                       const std::uint8_t* in,
                       std::size_t         inl) noexcept;

void sha256_init(std::uint8_t state[32], std::uint64_t* data_bits) noexcept;

void sha256_reset(std::uint8_t state[32], std::uint64_t* data_bits) noexcept;

int sha256_update_blocks(std::uint8_t        state[32],
                         std::uint64_t*      data_bits,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept;

int sha256_final_block(std::uint8_t        state[32],
                       std::uint64_t*      data_bits,
                       std::uint8_t        digest[32],
                       const std::uint8_t* in,
                       std::size_t         inl) noexcept;

void sha384_init(std::uint8_t   state[64],
                 std::uint64_t* data_bits_h,
                 std::uint64_t* data_bits_l) noexcept;

void sha384_reset(std::uint8_t   state[64],
                  std::uint64_t* data_bits_h,
                  std::uint64_t* data_bits_l) noexcept;

int sha384_update_blocks(std::uint8_t        state[64],
                         std::uint64_t*      data_bits_h,
                         std::uint64_t*      data_bits_l,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept;

int sha384_final_block(std::uint8_t        state[64],
                       std::uint64_t*      data_bits_h,
                       std::uint64_t*      data_bits_l,
                       std::uint8_t        digest[48],
                       const std::uint8_t* in,
                       std::size_t         inl) noexcept;

void sha512_init(std::uint8_t   state[64],
                 std::uint64_t* data_bits_h,
                 std::uint64_t* data_bits_l) noexcept;

void sha512_reset(std::uint8_t   state[64],
                  std::uint64_t* data_bits_h,
                  std::uint64_t* data_bits_l) noexcept;

int sha512_update_blocks(std::uint8_t        state[64],
                         std::uint64_t*      data_bits_h,
                         std::uint64_t*      data_bits_l,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept;

int sha512_final_block(std::uint8_t        state[64],
                       std::uint64_t*      data_bits_h,
                       std::uint64_t*      data_bits_l,
                       std::uint8_t        digest[64],
                       const std::uint8_t* in,
                       std::size_t         inl) noexcept;

} // namespace common
} // namespace internal
} // namespace sha2

#endif
