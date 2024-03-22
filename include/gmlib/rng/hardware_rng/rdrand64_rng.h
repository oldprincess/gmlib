#if defined(CPU_FLAG_RDRAND)
#ifndef RNG_HARDWARE_RNG_RDRAND64_RNG_H
#define RNG_HARDWARE_RNG_RDRAND64_RNG_H

#include <gmlib/rng/rng.h>
#include <immintrin.h>

#include <stdexcept>

#if defined(_MSC_VER)

#else
#define _rdrand64_step(ptr) _rdrand64_step((unsigned long long *)(ptr))
#endif

namespace rng::hardware_rng {

// compile with -mrdrnd

template <unsigned int RDRAND_RETRIES = 10>
class RdrandRng_64 : public Rng
{
public:
    const char *name() const noexcept override
    {
        return "RdrandRng_64(RDRAND)";
    }

private:
    // Intel Digital Random Number Generator(DRNG), Revision 2.1, 2018-10-17

    // Read a hardware generated 64-bit random value and store the result in
    // val. Return 1 if a random value was generated, and 0 otherwise.
    static inline int rdrand64_retry(unsigned int   retries,
                                     std::uint64_t *val) noexcept
    {
        if (_rdrand64_step(val) == 1)
        {
            return 1;
        }
        while (retries)
        {
            if (_rdrand64_step(val) == 1)
            {
                return 1;
            }
            retries--;
        }
        return 0;
    }

public:
    void gen(void *out, std::size_t len) override
    {
        std::uint8_t *out_u8 = (std::uint8_t *)out;
        while (len >= 8)
        {
            if (rdrand64_retry(RDRAND_RETRIES, (std::uint64_t *)(out_u8)) != 1)
            {
                throw std::runtime_error("Err in call _rdrand64_step");
            }
            out_u8 += 8, len -= 8;
        }
        if (len)
        {
            std::uint64_t val;
            if (rdrand64_retry(RDRAND_RETRIES, &val) != 1)
            {
                throw std::runtime_error("Err in call _rdrand64_step");
            }
            while (len)
            {
                *out_u8 = val & 0xFF;
                out_u8++, len--, val >>= 8;
            }
        }
    }
};

}; // namespace rng::hardware_rng

#if defined(_MSC_VER)

#else
#undef _rdrand64_step
#endif

#endif // !RNG_HARDWARE_RNG_RDRAND64_RNG_H
#endif