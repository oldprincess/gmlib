#ifndef NUMBER_INTERNAL_MONT256_X64_H
#define NUMBER_INTERNAL_MONT256_X64_H

#include <gmlib/number/mont256.h>

#include "config.h"

#if defined(NUMBER_IMPL_X64)

#include <cstddef>
#include <cstdint>

namespace number::internal::x64 {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************** UINT256 Montgeomery ***************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

// ****************************************
// ************ Arithmetic ****************
// ****************************************

void mont256_add(const Mont256CTX*   ctx,
                 std::uint64_t       sum[4],
                 const std::uint64_t augend[4],
                 const std::uint64_t addend[4]) noexcept;

void mont256_sub(const Mont256CTX*   ctx,
                 std::uint64_t       difference[4],
                 const std::uint64_t minuend[4],
                 const std::uint64_t subtrahend[4]) noexcept;

void mont256_dbl(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4]) noexcept;

void mont256_tpl(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4]) noexcept;

void mont256_neg(const Mont256CTX*   ctx,
                 std::uint64_t       ret[4],
                 const std::uint64_t num[4]) noexcept;

void mont256_mul(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4],
                 const std::uint64_t multiplicand[4]) noexcept;

void mont256_sqr(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4]) noexcept;

void mont256_pow(const Mont256CTX*   ctx,
                 std::uint64_t       power[4],
                 const std::uint64_t base[4],
                 const std::uint64_t exponent[4]) noexcept;

void mont256_div2(const Mont256CTX*   ctx,
                  std::uint64_t       quotient[4],
                  const std::uint64_t dividend[4]) noexcept;

void mont256_inv(const Mont256CTX*   ctx,
                 std::uint64_t       inverse[4],
                 const std::uint64_t num[4]) noexcept;

// ****************************************
// *************** Compare ****************
// ****************************************

bool mont256_equal(const Mont256CTX*   ctx,
                   const std::uint64_t a[4],
                   const std::uint64_t b[4]) noexcept;

bool mont256_equal_zero(const Mont256CTX*   ctx,
                        const std::uint64_t a[4]) noexcept;

bool mont256_equal_one(const Mont256CTX*   ctx,
                       const std::uint64_t a[4]) noexcept;

// ****************************************
// ************* Set & Move ***************
// ****************************************

void mont256_cpy(const Mont256CTX*   ctx,
                 std::uint64_t       ret[4],
                 const std::uint64_t num[4]) noexcept;

void mont256_set_zero(const Mont256CTX* ctx, std::uint64_t num[4]) noexcept;

void mont256_set_one(const Mont256CTX* ctx, std::uint64_t num[4]) noexcept;

void mont256_set_uint32(const Mont256CTX* ctx,
                        std::uint64_t     ret[4],
                        std::uint32_t     num) noexcept;

void mont256_set_uint64(const Mont256CTX* ctx,
                        std::uint64_t     ret[4],
                        std::uint64_t     num) noexcept;

// ****************************************
// *************** Convert ****************
// ****************************************

void mont256_from_bytes(const Mont256CTX*  ctx,
                        std::uint64_t      num[4],
                        const std::uint8_t bytes[32]) noexcept;

void mont256_to_bytes(const Mont256CTX*   ctx,
                      std::uint8_t        bytes[32],
                      const std::uint64_t num[4]) noexcept;

void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                           std::uint64_t       num[4],
                           const std::uint8_t* bytes,
                           std::size_t         bytes_len) noexcept;

} // namespace number::internal::x64

#endif
#endif