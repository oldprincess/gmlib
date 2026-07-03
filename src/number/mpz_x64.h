#if defined(NUMBER_IMPL_X64)

#ifndef NUMBER_INTERNAL_MPZ_X64_H
#define NUMBER_INTERNAL_MPZ_X64_H

#include <cstddef>
#include <cstdint>

namespace number::internal::x64 {

int mpz_add_carry(std::uint64_t*       r,
                  const std::uint64_t* a,
                  const std::uint64_t* b,
                  int                  carry,
                  std::size_t          bits) noexcept;

int mpz_sub_borrow(std::uint64_t*       r,
                   const std::uint64_t* a,
                   const std::uint64_t* b,
                   int                  borrow,
                   std::size_t          bits) noexcept;

void mpz_mul(std::uint64_t*       r,
             const std::uint64_t* a,
             const std::uint64_t* b,
             std::size_t          bits) noexcept;

int mpz_cmp(const std::uint64_t* a,
            const std::uint64_t* b,
            std::size_t          bits) noexcept;

void mpz_cpy(std::uint64_t*       r,
             const std::uint64_t* a,
             std::size_t          bits) noexcept;

void mpz_from_bytes(std::uint64_t*      r,
                    const std::uint8_t* src,
                    std::size_t         bits) noexcept;

void mpz_to_bytes(std::uint8_t*        r,
                  const std::uint64_t* src,
                  std::size_t          bits) noexcept;

} // namespace number::internal::x64

#endif
#endif
