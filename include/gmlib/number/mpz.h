#ifndef NUMBER_MPZ_H
#define NUMBER_MPZ_H

#include <gmlib/number/provider.h>

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace number {

static inline int mpz_add_carry(std::uint8_t*       r,
                                const std::uint8_t* a,
                                const std::uint8_t* b,
                                int                 carry,
                                std::size_t         bits) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mpz_add_carry != nullptr);
    return provider->mpz_add_carry(r, a, b, carry, bits);
}

static inline int mpz_sub_borrow(std::uint8_t*       r,
                                 const std::uint8_t* a,
                                 const std::uint8_t* b,
                                 int                 borrow,
                                 std::size_t         bits) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mpz_sub_borrow != nullptr);
    return provider->mpz_sub_borrow(r, a, b, borrow, bits);
}

static inline void mpz_mul(std::uint8_t*       r,
                           const std::uint8_t* a,
                           const std::uint8_t* b,
                           std::size_t         bits) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mpz_mul != nullptr);
    provider->mpz_mul(r, a, b, bits);
}

static inline int mpz_cmp(const std::uint8_t* a,
                          const std::uint8_t* b,
                          std::size_t         bits) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mpz_cmp != nullptr);
    return provider->mpz_cmp(a, b, bits);
}

static inline void mpz_cpy(std::uint8_t*       r,
                           const std::uint8_t* a,
                           std::size_t         bits) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mpz_cpy != nullptr);
    provider->mpz_cpy(r, a, bits);
}

static inline void mpz_from_bytes(std::uint8_t*       r,
                                  const std::uint8_t* src,
                                  std::size_t         bits) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mpz_from_bytes != nullptr);
    provider->mpz_from_bytes(r, src, bits);
}

static inline void mpz_to_bytes(std::uint8_t*       r,
                                const std::uint8_t* src,
                                std::size_t         bits) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mpz_to_bytes != nullptr);
    provider->mpz_to_bytes(r, src, bits);
}

} // namespace number

#endif
