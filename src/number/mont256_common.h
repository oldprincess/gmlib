#ifndef NUMBER_INTERNAL_MONT256_COMMON_H
#define NUMBER_INTERNAL_MONT256_COMMON_H

#include <gmlib/number/mont256.h>

#include "config.h"

#if defined(NUMBER_IMPL_COMMON)

#include <cstddef>
#include <cstdint>

namespace number::internal::common {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************** UINT256 Montgeomery ***************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

// ****************************************
// ************ Arithmetic ****************
// ****************************************

void mont256_add(const Mont256CTX*   ctx,
                 std::uint32_t       sum[8],
                 const std::uint32_t augend[8],
                 const std::uint32_t addend[8]) noexcept;

void mont256_sub(const Mont256CTX*   ctx,
                 std::uint32_t       difference[8],
                 const std::uint32_t minuend[8],
                 const std::uint32_t subtrahend[8]) noexcept;

void mont256_dbl(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8]) noexcept;

void mont256_tpl(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8]) noexcept;

void mont256_neg(const Mont256CTX*   ctx,
                 std::uint32_t       ret[8],
                 const std::uint32_t num[8]) noexcept;

void mont256_mul(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8],
                 const std::uint32_t multiplicand[8]) noexcept;

void mont256_sqr(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8]) noexcept;

void mont256_div2(const Mont256CTX*   ctx,
                  std::uint32_t       quotient[8],
                  const std::uint32_t dividend[8]) noexcept;

void mont256_pow(const Mont256CTX*   ctx,
                 std::uint32_t       power[8],
                 const std::uint32_t base[8],
                 const std::uint32_t exponent[8]) noexcept;

void mont256_inv(const Mont256CTX*   ctx,
                 std::uint32_t       inverse[8],
                 const std::uint32_t num[8]) noexcept;

// ****************************************
// *************** Compare ****************
// ****************************************

bool mont256_equal(const Mont256CTX*   ctx,
                   const std::uint32_t a[8],
                   const std::uint32_t b[8]) noexcept;

bool mont256_equal_zero(const Mont256CTX*   ctx,
                        const std::uint32_t a[8]) noexcept;

bool mont256_equal_one(const Mont256CTX*   ctx,
                       const std::uint32_t a[8]) noexcept;

// ****************************************
// ************* Set & Move ***************
// ****************************************

void mont256_cpy(const Mont256CTX*   ctx,
                 std::uint32_t       ret[8],
                 const std::uint32_t num[8]) noexcept;

void mont256_set_zero(const Mont256CTX* ctx, std::uint32_t num[8]) noexcept;

void mont256_set_one(const Mont256CTX* ctx, std::uint32_t num[8]) noexcept;

void mont256_set_uint32(const Mont256CTX* ctx,
                        std::uint32_t     ret[8],
                        std::uint32_t     num) noexcept;

void mont256_set_uint64(const Mont256CTX* ctx,
                        std::uint32_t     ret[8],
                        std::uint64_t     num) noexcept;

// ****************************************
// *************** Convert ****************
// ****************************************

void mont256_from_bytes(const Mont256CTX*  ctx,
                        std::uint32_t      num[8],
                        const std::uint8_t bytes[32]) noexcept;

void mont256_to_bytes(const Mont256CTX*   ctx,
                      std::uint8_t        bytes[32],
                      const std::uint32_t num[8]) noexcept;

void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                           std::uint32_t       num[8],
                           const std::uint8_t* bytes,
                           std::size_t         bytes_len) noexcept;

} // namespace number::internal::common

#endif
#endif