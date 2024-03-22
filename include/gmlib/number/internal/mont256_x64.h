#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#ifndef NUMBER_INTERNAL_MONT256_X64_H
#define NUMBER_INTERNAL_MONT256_X64_H

#include <cstddef>
#include <cstdint>

namespace number::internal::x64 {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************** UINT256 Montgeomery ***************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct Mont256CTX
{
    const std::uint64_t* P;      // p
    const std::uint64_t* P_SUB2; // p - 2
    const std::uint64_t* R;      // 2^256 mod p
    const std::uint64_t* R_POW2; // R^2 mod p
    std::uint64_t        N_;     // N':N'*p=-1 mod B, B=2^64, R=B^4
} Mont256CTX;

typedef std::uint64_t mont256_t[4];

/**
 * @brief compute Montgeomery Params N': N'*P=-1 mod B
 * @param P0 lowest limb of P
 * @return N'
 */
static constexpr std::uint64_t mont_compute_N_(std::uint64_t P0) noexcept
{
    // ex gcd
    std::uint64_t a  = P0;
    std::uint64_t b  = (~P0) + 1; // -P0; avoid warning C4146
    std::uint64_t x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    std::uint64_t q = 0, r = 0, tmp = 0;
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