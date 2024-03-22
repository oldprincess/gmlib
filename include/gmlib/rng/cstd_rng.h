#ifndef RNG_CSTD_RNG_H
#define RNG_CSTD_RNG_H

#include <gmlib/rng/rng.h>

#include <cstdlib>
#include <ctime>

namespace rng {

class CstdRng : public Rng
{
public:
    CstdRng() noexcept
    {
        std::srand((unsigned int)std::time(nullptr));
    }

public:
    const char* name() const noexcept
    {
        return "CstdRng(std::rand)";
    }

public:
    void gen(void* out, std::size_t len) noexcept
    {
        std::uint8_t* data = (std::uint8_t*)out;
        while (len)
        {
            *data = (std::uint8_t)std::rand();
            data += 1, len -= 1;
        }
    }
};

} // namespace rng

#endif