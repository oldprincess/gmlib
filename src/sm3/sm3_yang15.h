#if defined(SUPPORT_SM3_YANG15)

#ifndef SM3_INTERNAL_SM3_YANG15_H
#define SM3_INTERNAL_SM3_YANG15_H

#include <cstddef>
#include <cstdint>

namespace sm3::internal::yang15 {

constexpr const char* SM3_ALGO_NAME = "yang15";

constexpr std::size_t SM3_BLOCK_SIZE        = 64;
constexpr std::size_t SM3_DIGEST_SIZE       = 32;
constexpr std::size_t SM3_SECURITY_STRENGTH = 16;

void sm3_init(std::uint32_t state[8], std::uint64_t* data_bits) noexcept;

void sm3_reset(std::uint32_t state[8], std::uint64_t* data_bits) noexcept;

int sm3_update_blocks(std::uint32_t       state[8],
                      std::uint64_t*      data_bits,
                      const std::uint8_t* in,
                      std::size_t         block_num) noexcept;

int sm3_final_block(std::uint32_t       state[8],
                    std::uint64_t*      data_bits,
                    std::uint8_t        digest[32],
                    const std::uint8_t* in,
                    std::size_t         inl) noexcept;

} // namespace sm3::internal::yang15

#endif
#endif
