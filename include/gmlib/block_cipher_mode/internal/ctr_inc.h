#ifndef BLOCK_CIPHER_MODE_INTERNAL_CTR_INC_H
#define BLOCK_CIPHER_MODE_INTERNAL_CTR_INC_H

#include <gmlib/memory_utils/endian.h>

#include <cstddef>

namespace block_cipher_mode {
namespace internal {

static inline void ctr_inc8(std::uint8_t* out, const std::uint8_t* in) noexcept
{
    uint64_t tmp = 1;
    tmp += memory_utils::load32_be(in + 4);
    memory_utils::store32_be(out + 4, tmp & UINT32_MAX);
    tmp = memory_utils::load32_be(in + 0) + (tmp >> 32);
    memory_utils::store32_be(out + 0, tmp & UINT32_MAX);
}

static inline void ctr_inc16(std::uint8_t* out, const std::uint8_t* in) noexcept
{
    uint64_t tmp = 1;
    tmp += memory_utils::load32_be(in + 12);
    memory_utils::store32_be(out + 12, tmp & UINT32_MAX);
    tmp = memory_utils::load32_be(in + 8) + (tmp >> 32);
    memory_utils::store32_be(out + 8, tmp & UINT32_MAX);
    tmp = memory_utils::load32_be(in + 4) + (tmp >> 32);
    memory_utils::store32_be(out + 4, tmp & UINT32_MAX);
    tmp = memory_utils::load32_be(in + 0) + (tmp >> 32);
    memory_utils::store32_be(out + 0, tmp & UINT32_MAX);
}

static void ctr_inc_n(std::uint8_t*       out,
                      const std::uint8_t* in,
                      std::size_t         n) noexcept
{
    std::uint16_t t = 1;
    for (std::size_t i = 0; i < n; i++)
    {
        std::size_t pos = n - 1 - i;
        t += (std::uint16_t)in[pos];
        out[pos] = t & 0xFF;
        t >>= 8;
    }
}

template <std::size_t BLOCK_SIZE>
static inline void ctr_inc(std::uint8_t* out, const std::uint8_t* in) noexcept
{
    if constexpr (BLOCK_SIZE == 16)
    {
        ctr_inc16(out, in);
        return;
    }
    if constexpr (BLOCK_SIZE == 8)
    {
        ctr_inc8(out, in);
        return;
    }
    ctr_inc_n(out, in, BLOCK_SIZE);
}

} // namespace internal
} // namespace block_cipher_mode

#endif