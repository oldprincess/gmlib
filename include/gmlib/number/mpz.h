#ifndef NUMBER_MPZ_H
#define NUMBER_MPZ_H

#include <cstddef>
#include <cstdint>

namespace number {

int mpz_add_carry(std::uint8_t*       r,
                  const std::uint8_t* a,
                  const std::uint8_t* b,
                  int                 carry,
                  std::size_t         bits) noexcept;

int mpz_sub_borrow(std::uint8_t*       r,
                   const std::uint8_t* a,
                   const std::uint8_t* b,
                   int                 borrow,
                   std::size_t         bits) noexcept;

void mpz_mul(std::uint8_t*       r,
             const std::uint8_t* a,
             const std::uint8_t* b,
             std::size_t         bits) noexcept;

int mpz_cmp(const std::uint8_t* a,
            const std::uint8_t* b,
            std::size_t         bits) noexcept;

void mpz_cpy(std::uint8_t*       r,
             const std::uint8_t* a,
             std::size_t         bits) noexcept;

void mpz_from_bytes(std::uint8_t*       r,
                    const std::uint8_t* src,
                    std::size_t         bits) noexcept;

void mpz_to_bytes(std::uint8_t*       r,
                  const std::uint8_t* src,
                  std::size_t         bits) noexcept;

} // namespace number

#endif