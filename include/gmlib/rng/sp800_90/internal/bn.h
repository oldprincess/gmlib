#ifndef RNG_SP800_90_INTERNAL_BN_H
#define RNG_SP800_90_INTERNAL_BN_H

#include <cstddef>
#include <cstdint>

namespace rng::sp800_90::internal {

/**
 * @brief                       self += other
 * @param[in]   self            self data prt, in big endian
 * @param[in]   self_length     self data length (in bytes)
 * @param[in]   other           other data prt, in big endian
 * @param[in]   other_length    other data length (in bytes)
 * @return                      update length (in bytes)
 */
static std::size_t bn_self_add(std::uint8_t*  self,
                               std::size_t    self_length,
                               const uint8_t* other,
                               std::size_t    other_length) noexcept
{
    std::uint16_t tmp = 0;
    std::size_t   i;
    std::size_t   s_idx = self_length - 1;
    std::size_t   o_idx = other_length - 1;
    for (i = 0; i < other_length; i++, s_idx--, o_idx--)
    {
        tmp = tmp + (std::uint16_t)self[s_idx] + (std::uint16_t)other[o_idx];
        self[s_idx] = (std::uint8_t)(tmp & 0xFF);
        tmp         = tmp >> 8;
    }
    for (; i < self_length; i++, s_idx--, o_idx--)
    {
        if (tmp == 0)
        {
            break;
        }
        tmp         = tmp + (std::uint16_t)self[s_idx];
        self[s_idx] = (std::uint8_t)(tmp & 0xFF);
        tmp         = tmp >> 8;
    }
    return i;
}

} // namespace rng::sp800_90::internal

#endif