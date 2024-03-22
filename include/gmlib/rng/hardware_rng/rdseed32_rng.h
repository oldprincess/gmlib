#if defined(CPU_FLAG_RDSEED)
#ifndef RNG_HARDWARE_RNG_RDSEED32_RNG_H
#define RNG_HARDWARE_RNG_RDSEED32_RNG_H

#include <gmlib/rng/rng.h>
#include <immintrin.h>

#include <stdexcept>

namespace rng::hardware_rng {

// compile with -mrdseed

template <unsigned int RDSEED_RETRIES = 10>
class RdseedRng_32 : public Rng
{
public:
    const char *name() const noexcept override
    {
        return "RdseedRng_32(RDSEED)";
    }

private:
    // Intel Digital Random Number Generator(DRNG), Revision 2.1, 2018-10-17

    // Read a hardware generated 32-bit random value and store the result in
    // val. Return 1 if a random value was generated, and 0 otherwise.
    static inline int rdseed32_retry(unsigned int   retries,
                                     std::uint32_t *val) noexcept
    {
        if (_rdseed32_step(val) == 1)
        {
            return 1;
        }
        while (retries)
        {
            if (_rdseed32_step(val) == 1)
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
        while (len >= 4)
        {
            if (rdseed32_retry(RDSEED_RETRIES, (std::uint32_t *)(out_u8)) != 1)
            {
                throw std::runtime_error("Err in call _rdseed32_step");
            }
            out_u8 += 4, len -= 4;
        }
        if (len)
        {
            std::uint32_t val;
            if (rdseed32_retry(RDSEED_RETRIES, &val) != 1)
            {
                throw std::runtime_error("Err in call _rdseed32_step");
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

#endif // !RNG_HARDWARE_RNG_RDSEED32_RNG_H
#endif