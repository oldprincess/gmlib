#ifndef NUMBER_INTERNAL_MONT256_COMMON_H
#define NUMBER_INTERNAL_MONT256_COMMON_H

#include <cstddef>
#include <cstdint>

namespace number::internal::common {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************** UINT256 Montgeomery ***************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct Mont256CTX
{
    const std::uint32_t* P;      // 8x32-bit: p
    const std::uint32_t* P_SUB2; // 8x32-bit: p - 2
    const std::uint32_t* R;      // 8x32-bit: 2^256 mod p
    const std::uint32_t* R_POW2; // 8x32-bit: R^2 mod p
    std::uint32_t        N_;     // 8x32-bit: N':N'*p=-1 mod B, B=2^32, R=B^8
} Mont256CTX;

typedef std::uint32_t mont256_t[8];

/**
 * @brief compute Montgeomery Params N': N'*P=-1 mod B
 * @param P0 lowest limb of P
 * @return N'
 */
static constexpr std::uint32_t mont_compute_N_(std::uint32_t P0) noexcept
{
    // ex gcd
    std::uint32_t a  = P0;
    std::uint32_t b  = (~P0) + 1; // -P0; avoid warning C4146
    std::uint32_t x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    std::uint32_t q = 0, r = 0, tmp = 0;
    while (b != 0)
    {
        q = a / b, r = a % b;
        a = b;
        b = r;

        tmp = x1 - q * x2;
        x1  = x2;
        x2  = tmp;

        tmp = y1 - q * y2;
        y1  = y2;
        y2  = tmp;
    }
    // 1 = x1 * P0 + y1 * (B-P0)
    // => 1 = (x1 - y1) * P0 + y1 * B
    // => -(x1 - y1) * P0 mod B = -1
    return ~(x1 - y1) + 1;
}

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