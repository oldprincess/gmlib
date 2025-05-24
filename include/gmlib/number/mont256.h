#ifndef NUMBER_MONT256_H
#define NUMBER_MONT256_H

#include <cstddef>
#include <cstdint>

namespace number {

typedef struct Mont256CTX
{
    const std::uint8_t* P;      // 256bits p
    const std::uint8_t* P_SUB2; // 256bits p - 2
    const std::uint8_t* R;      // 256bits 2^256 mod p
    const std::uint8_t* R_POW2; // 256bits R^2 mod p
    const std::uint8_t* N_;     // 256bits N':N'*p=-1 mod 2^256
} Mont256CTX;

typedef std::uint8_t mont256_t[32];

const char* mont256_fetch_impl_algo() noexcept;

// ****************************************
// ************ Arithmetic ****************
// ****************************************

void mont256_add(const Mont256CTX*  ctx,
                 std::uint8_t       sum[32],
                 const std::uint8_t augend[32],
                 const std::uint8_t addend[32]) noexcept;

void mont256_sub(const Mont256CTX*  ctx,
                 std::uint8_t       difference[32],
                 const std::uint8_t minuend[32],
                 const std::uint8_t subtrahend[32]) noexcept;

void mont256_dbl(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept;

void mont256_tpl(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept;

void mont256_neg(const Mont256CTX*  ctx,
                 std::uint8_t       ret[32],
                 const std::uint8_t num[32]) noexcept;

void mont256_mul(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32],
                 const std::uint8_t multiplicand[32]) noexcept;

void mont256_sqr(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept;

void mont256_pow(const Mont256CTX*  ctx,
                 std::uint8_t       power[32],
                 const std::uint8_t base[32],
                 const std::uint8_t exponent[32]) noexcept;

void mont256_div2(const Mont256CTX*  ctx,
                  std::uint8_t       quotient[32],
                  const std::uint8_t dividend[32]) noexcept;

void mont256_inv(const Mont256CTX*  ctx,
                 std::uint8_t       inverse[32],
                 const std::uint8_t num[32]) noexcept;

// ****************************************
// *************** Compare ****************
// ****************************************

bool mont256_equal(const Mont256CTX*  ctx,
                   const std::uint8_t a[32],
                   const std::uint8_t b[32]) noexcept;

bool mont256_equal_zero(const Mont256CTX*  ctx,
                        const std::uint8_t a[32]) noexcept;

bool mont256_equal_one(const Mont256CTX*  ctx,
                       const std::uint8_t a[32]) noexcept;

// ****************************************
// ************* Set & Move ***************
// ****************************************

void mont256_cpy(const Mont256CTX*  ctx,
                 std::uint8_t       ret[32],
                 const std::uint8_t num[32]) noexcept;

void mont256_set_zero(const Mont256CTX* ctx, std::uint8_t num[32]) noexcept;

void mont256_set_one(const Mont256CTX* ctx, std::uint8_t num[32]) noexcept;

void mont256_set_uint32(const Mont256CTX* ctx,
                        std::uint8_t      ret[32],
                        std::uint32_t     num) noexcept;

void mont256_set_uint64(const Mont256CTX* ctx,
                        std::uint8_t      ret[32],
                        std::uint64_t     num) noexcept;

// ****************************************
// *************** Convert ****************
// ****************************************

void mont256_from_bytes(const Mont256CTX*  ctx,
                        std::uint8_t       num[32],
                        const std::uint8_t bytes[32]) noexcept;

void mont256_to_bytes(const Mont256CTX*  ctx,
                      std::uint8_t       bytes[32],
                      const std::uint8_t num[32]) noexcept;

void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                           std::uint8_t        num[32],
                           const std::uint8_t* bytes,
                           std::size_t         bytes_len) noexcept;

} // namespace number

#endif