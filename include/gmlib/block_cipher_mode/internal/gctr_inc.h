#ifndef BLOCK_CIPHER_MODE_INTERNAL_GCM_ALG_H
#define BLOCK_CIPHER_MODE_INTERNAL_GCM_ALG_H

#include <gmlib/memory_utils/endian.h>

namespace block_cipher_mode::internal {

static inline void gctr_inc(std::uint8_t       out[16],
                            const std::uint8_t in[16]) noexcept
{
    ((std::uint32_t *)out)[0] = ((const std::uint32_t *)in)[0];
    ((std::uint32_t *)out)[1] = ((const std::uint32_t *)in)[1];
    ((std::uint32_t *)out)[2] = ((const std::uint32_t *)in)[2];
    std::uint32_t tmp         = memory_utils::load32_be(in + 12) + 1;
    memory_utils::store32_be(out + 12, tmp);
}

} // namespace block_cipher_mode::internal

#endif