#ifndef RNG_SP800_90_INTERNAL_ENTROPY_H
#define RNG_SP800_90_INTERNAL_ENTROPY_H

#include <random>

namespace rng::sp800_90::internal {

inline void get_entropy(void* entropy, std::size_t entropy_length)
{
    using T = std::random_device::result_type;

    std::random_device rng_device;
    std::uint8_t*      data_entropy = (std::uint8_t*)entropy;
    while (entropy_length >= sizeof(T))
    {
        *(T*)data_entropy = rng_device();
        data_entropy += sizeof(T), entropy_length -= sizeof(T);
    }
    while (entropy_length)
    {
        *data_entropy = (std::uint8_t)rng_device();
        data_entropy++, entropy_length--;
    }
}

} // namespace rng::sp800_90::internal

#endif