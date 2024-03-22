#ifndef NUMBER_INTERNAL_MPZ_COMMON_H
#define NUMBER_INTERNAL_MPZ_COMMON_H

#include <cstddef>
#include <cstdint>

namespace number::internal::common {

template <std::size_t LIMB_SIZE>
struct mpz_st
{
    std::uint32_t v[LIMB_SIZE] = {0};
};

template <class... Args>
constexpr auto mpz_set_epi8(Args... args) noexcept
{
    auto joint32 = [](std::uint8_t e3, std::uint8_t e2, std::uint8_t e1,
                      std::uint8_t e0) constexpr {
        return (std::uint32_t)e3 << 24 | (std::uint32_t)e2 << 16 |
               (std::uint32_t)e1 << 8 | (std::uint32_t)e0;
    };

    static_assert(sizeof...(args) % 4 == 0 && sizeof...(args) != 0,
                  "invalid param");
    constexpr std::size_t LIMB_SIZE = sizeof...(args) / 4;
    mpz_st<LIMB_SIZE>     ret;
    std::uint8_t          a[] = {static_cast<std::uint8_t>(args)...};
    for (std::size_t i = 0; i < LIMB_SIZE; i++)
    {
        ret.v[LIMB_SIZE - 1 - i] =
            joint32(a[4 * i], a[4 * i + 1], a[4 * i + 2], a[4 * i + 3]);
    }
    return ret;
}

int mpz_add_carry(std::uint32_t*       r,
                  const std::uint32_t* a,
                  const std::uint32_t* b,
                  int                  carry,
                  std::size_t          limb_size) noexcept;

int mpz_sub_borrow(std::uint32_t*       r,
                   const std::uint32_t* a,
                   const std::uint32_t* b,
                   int                  borrow,
                   std::size_t          limb_size) noexcept;

void mpz_mul(std::uint32_t*       r,
             const std::uint32_t* a,
             const std::uint32_t* b,
             std::size_t          limb_size) noexcept;

int mpz_cmp(const std::uint32_t* a,
            const std::uint32_t* b,
            std::size_t          limb_size) noexcept;

void mpz_cpy(std::uint32_t*       r,
             const std::uint32_t* a,
             std::size_t          limb_size) noexcept;

void mpz_from_bytes(std::uint32_t*      r,
                    const std::uint8_t* src,
                    std::size_t         limb_size) noexcept;

void mpz_to_bytes(std::uint8_t*        r,
                  const std::uint32_t* src,
                  std::size_t          limb_size) noexcept;

} // namespace number::internal::common

#endif