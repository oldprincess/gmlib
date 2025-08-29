#ifndef NUMBER_INTERNAL_MPZ_COMMON_H
#define NUMBER_INTERNAL_MPZ_COMMON_H

#include "config.h"

#if defined(NUMBER_IMPL_COMMON)

#include <cstddef>
#include <cstdint>

namespace number::internal::common {

int mpz_add_carry(std::uint32_t*       r,
                  const std::uint32_t* a,
                  const std::uint32_t* b,
                  int                  carry,
                  std::size_t          bits) noexcept;

int mpz_sub_borrow(std::uint32_t*       r,
                   const std::uint32_t* a,
                   const std::uint32_t* b,
                   int                  borrow,
                   std::size_t          bits) noexcept;

void mpz_mul(std::uint32_t*       r,
             const std::uint32_t* a,
             const std::uint32_t* b,
             std::size_t          bits) noexcept;

int mpz_cmp(const std::uint32_t* a,
            const std::uint32_t* b,
            std::size_t          bits) noexcept;

void mpz_cpy(std::uint32_t*       r,
             const std::uint32_t* a,
             std::size_t          bits) noexcept;

void mpz_from_bytes(std::uint32_t*      r,
                    const std::uint8_t* src,
                    std::size_t         bits) noexcept;

void mpz_to_bytes(std::uint8_t*        r,
                  const std::uint32_t* src,
                  std::size_t          bits) noexcept;

} // namespace number::internal::common

#endif
#endif