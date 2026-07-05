#if defined(SUPPORT_SHA2_SHA)

#ifndef SHA224_256_SHA_H
#define SHA224_256_SHA_H

#include <cstddef>
#include <cstdint>

namespace sha2 {
namespace internal {
namespace sha {

constexpr const char* SHA2_ALGO_NAME = "sha";

constexpr std::size_t SHA224_BLOCK_SIZE        = 64;
constexpr std::size_t SHA224_DIGEST_SIZE       = 28;
constexpr std::size_t SHA224_SECURITY_STRENGTH = 14;

constexpr std::size_t SHA256_BLOCK_SIZE        = 64;
constexpr std::size_t SHA256_DIGEST_SIZE       = 32;
constexpr std::size_t SHA256_SECURITY_STRENGTH = 16;

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

} // namespace sha
} // namespace internal
} // namespace sha2

#endif

#endif
