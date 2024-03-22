#ifndef RNG_RNG_H
#define RNG_RNG_H

#include <cstddef>
#include <cstdint>
#include <random>
#include <type_traits>

namespace rng {

class Rng
{
protected:
    Rng()                 = default;
    Rng(const Rng& other) = default;

public:
    virtual ~Rng() = default;

public:
    virtual const char* name() const = 0;

public:
    virtual void gen(void* out, std::size_t len) = 0;

    template <typename T>
    T rand()
    {
        static_assert(std::is_pod<T>::value, "only support POD type");
        T r;
        this->gen((void*)(&r), sizeof(T));
        return r;
    }
};

} // namespace rng

#endif