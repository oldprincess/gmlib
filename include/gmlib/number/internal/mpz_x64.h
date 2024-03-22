#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)

#ifndef NUMBER_INTERNAL_MPZ_X64_H
#define NUMBER_INTERNAL_MPZ_X64_H

#include <cstddef>
#include <cstdint>

namespace number::internal::x64 {

template <std::size_t LIMB_SIZE>
struct mpz_st
{
    std::uint64_t v[LIMB_SIZE] = {0};
};

template <class... Args>
constexpr auto mpz_set_epi8(Args... args) noexcept
{
    auto joint64 = [](std::uint8_t e7, std::uint8_t e6, std::uint8_t e5,
                      std::uint8_t e4, std::uint8_t e3, std::uint8_t e2,
                      std::uint8_t e1, std::uint8_t e0) constexpr {
        return (std::uint64_t)e7 << 56 | (std::uint64_t)e6 << 48 |
               (std::uint64_t)e5 << 40 | (std::uint64_t)e4 << 32 |
               (std::uint64_t)e3 << 24 | (std::uint64_t)e2 << 16 |
               (std::uint64_t)e1 << 8 | (std::uint64_t)e0;
    };

    static_assert(sizeof...(args) % 8 == 0 && sizeof...(args) != 0,
                  "invalid param");
    constexpr std::size_t LIMB_SIZE = sizeof...(args) / 8;
    mpz_st<LIMB_SIZE>     ret;
    std::uint8_t          a[] = {static_cast<std::uint8_t>(args)...};
    for (std::size_t i = 0; i < LIMB_SIZE; i++)
    {
        ret.v[LIMB_SIZE - 1 - i] =
            joint64(a[8 * i], a[8 * i + 1], a[8 * i + 2], a[8 * i + 3],
                    a[8 * i + 4], a[8 * i + 5], a[8 * i + 6], a[8 * i + 7]);
    }
    return ret;
}

int mpz_add_carry(std::uint64_t*       r,
                  const std::uint64_t* a,
                  const std::uint64_t* b,
                  int                  carry,
                  std::size_t          limb_size) noexcept;

int mpz_sub_borrow(std::uint64_t*       r,
                   const std::uint64_t* a,
                   const std::uint64_t* b,
                   int                  borrow,
                   std::size_t          limb_size) noexcept;

void mpz_mul(std::uint64_t*       r,
             const std::uint64_t* a,
             const std::uint64_t* b,
             std::size_t          limb_size) noexcept;

int mpz_cmp(const std::uint64_t* a,
            const std::uint64_t* b,
            std::size_t          limb_size) noexcept;

void mpz_cpy(std::uint64_t*       r,
             const std::uint64_t* a,
             std::size_t          limb_size) noexcept;

void mpz_from_bytes(std::uint64_t*      r,
                    const std::uint8_t* src,
                    std::size_t         limb_size) noexcept;

void mpz_to_bytes(std::uint8_t*        r,
                  const std::uint64_t* src,
                  std::size_t          limb_size) noexcept;

} // namespace number::internal::x64

#endif
#endif