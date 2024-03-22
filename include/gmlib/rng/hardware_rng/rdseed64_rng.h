#if defined(CPU_FLAG_RDSEED)
#ifndef RNG_HARDWARE_RNG_RDSEED64_RNG_H
#define RNG_HARDWARE_RNG_RDSEED64_RNG_H

#include <gmlib/rng/rng.h>
#include <immintrin.h>

#include <stdexcept>

#if defined(_MSC_VER)

#else
#define _rdseed64_step(ptr) _rdseed64_step((unsigned long long *)(ptr))
#endif

namespace rng::hardware_rng {

// compile with -mrdseed

template <unsigned int RDSEED_RETRIES = 10>
class RdseedRng_64 : public Rng
{
public:
    const char *name() const noexcept override
    {
        return "RdseedRng_64(RDSEED)";
    }

private:
    // Intel Digital Random Number Generator(DRNG), Revision 2.1, 2018-10-17

    static inline int rdseed64_retry(unsigned int   retries,
                                     std::uint64_t *val) noexcept
    {
        if (_rdseed64_step(val) == 1)
        {
            return 1;
        }
        while (retries)
        {
            if (_rdseed64_step(val) == 1)
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
            if (rdseed64_retry(RDSEED_RETRIES, (std::uint64_t *)(out_u8)) != 1)
            {
                throw std::runtime_error("Err in call _rdseed64_step");
            }
            out_u8 += 8, len -= 8;
        }
        if (len)
        {
            std::uint64_t val;
            if (rdseed64_retry(RDSEED_RETRIES, &val) != 1)
            {
                throw std::runtime_error("Err in call _rdseed64_step");
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
#undef _rdseed64_step
#endif

#endif // !RNG_HARDWARE_RNG_RDSEED64_RNG_H
#endif