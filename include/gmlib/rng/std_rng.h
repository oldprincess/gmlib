#ifndef RNG_STD_RNG_H
#define RNG_STD_RNG_H

#include <gmlib/rng/rng.h>

#include <cstdlib>
#include <ctime>

namespace rng {

class StdRng : public Rng
{
private:
    std::random_device device_;

public:
    StdRng() noexcept = default;

    const char* name() const noexcept override
    {
        return "StdRng(std::random_device)";
    }

public:
    void gen(void* out, std::size_t len) override
    {
        std::uint8_t* out_u8 = (std::uint8_t*)out;
        while (len)
        {
            *out_u8 = (std::uint8_t)device_();
            out_u8 += 1, len -= 1;
        }
    }
};

} // namespace rng

#endif
