#include <gmlib/number/internal/mont256_common.h>
#include <gmlib/number/internal/uint256_common.h>

namespace number::internal::common {

/// @brief r = a + b + carry
/// @return (1/0)
static inline int _add_carry(std::uint32_t* r,
                             std::uint32_t  a,
                             std::uint32_t  b,
                             int            carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a + (std::uint64_t)b + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r += n * mulVal + carry
/// @return [0,2^32)
static inline std::uint32_t _add_mul_carry(std::uint32_t* r,
                                           std::uint32_t  n,
                                           std::uint32_t  mulVal,
                                           std::uint32_t  carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)n * (std::uint64_t)mulVal + *r + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

static void mont256_redc(const Mont256CTX* ctx,
                         std::uint32_t     r[8],
                         std::uint32_t     t[16]) noexcept
{
    const std::uint32_t N_ = ctx->N_; // N':N'*N=-1 mod B, B=2^32, R=B^8

    std::uint32_t t16 = 0; // overflow
    for (int i = 0; i < 8; i++)
    {
        std::uint32_t carry = 0;
        std::uint32_t m     = (std::uint32_t)(t[i] * N_);

        carry = _add_mul_carry(&t[i + 0], m, ctx->P[0], 0);
        carry = _add_mul_carry(&t[i + 1], m, ctx->P[1], carry);
        carry = _add_mul_carry(&t[i + 2], m, ctx->P[2], carry);
        carry = _add_mul_carry(&t[i + 3], m, ctx->P[3], carry);
        carry = _add_mul_carry(&t[i + 4], m, ctx->P[4], carry);
        carry = _add_mul_carry(&t[i + 5], m, ctx->P[5], carry);
        carry = _add_mul_carry(&t[i + 6], m, ctx->P[6], carry);
        carry = _add_mul_carry(&t[i + 7], m, ctx->P[7], carry);

        int c = _add_carry(&t[i + 8], t[i + 8], carry, 0);
        for (int j = 9; j < 8 + 8 - i && c != 0; j++)
        {
            c = _add_carry(&t[i + j], t[i + j], 0, c);
        }
        t16 += c;
    }
    uint256_cpy(r, t + 8);
    if (t16 || uint256_cmp(r, ctx->P) >= 0)
    {
        uint256_sub_borrow(r, r, ctx->P);
    }
}

static void uint256_to_mont(const Mont256CTX*   ctx,
                            std::uint32_t       r[8],
                            const std::uint32_t a[8]) noexcept
{
    mont256_mul(ctx, r, a, ctx->R_POW2);
}

static void uint256_from_mont(const Mont256CTX*   ctx,
                              std::uint32_t       r[8],
                              const std::uint32_t a[8]) noexcept
{
    std::uint32_t t[16];
    t[0] = a[0], t[1] = a[1], t[2] = a[2], t[3] = a[3];
    t[4] = a[4], t[5] = a[5], t[6] = a[6], t[7] = a[7];
    t[8] = t[9] = t[10] = t[11] = t[12] = t[13] = t[14] = t[15] = 0;
    mont256_redc(ctx, r, t);
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

void mont256_add(const Mont256CTX*   ctx,
                 std::uint32_t       sum[8],
                 const std::uint32_t augend[8],
                 const std::uint32_t addend[8]) noexcept
{
    // int carry = uint256_add_carry(sum, augend, addend);
    // if (carry || uint256_cmp(sum, ctx->P) >= 0)
    // {
    //     uint256_sub_borrow(sum, sum, ctx->P);
    // }
    uint256_mod_add(sum, augend, addend, ctx->P);
}

void mont256_sub(const Mont256CTX*   ctx,
                 std::uint32_t       difference[8],
                 const std::uint32_t minuend[8],
                 const std::uint32_t subtrahend[8]) noexcept
{
    // int borrow = uint256_sub_borrow(difference, minuend, subtrahend);
    // if (borrow || uint256_cmp(difference, ctx->P) >= 0)
    // {
    //     uint256_add_carry(difference, difference, ctx->P);
    // }
    uint256_mod_sub(difference, minuend, subtrahend, ctx->P);
}

void mont256_dbl(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8]) noexcept
{
    int carry = uint256_dbl_carry(product, multiplier);
    if (carry || uint256_cmp(product, ctx->P) >= 0)
    {
        uint256_sub_borrow(product, product, ctx->P);
    }
}

void mont256_tpl(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8]) noexcept
{
    int carry = uint256_tpl_carry(product, multiplier);
    while (carry)
    {
        carry += uint256_sub_borrow(product, product, ctx->P);
    }
    if (uint256_cmp(product, ctx->P) >= 0)
    {
        uint256_sub_borrow(product, product, ctx->P);
    }
}

void mont256_neg(const Mont256CTX*   ctx,
                 std::uint32_t       ret[8],
                 const std::uint32_t num[8]) noexcept
{
    if (uint256_equal_zero(num))
    {
        uint256_set_zero(ret);
    }
    uint256_sub_borrow(ret, ctx->P, num);
}

void mont256_mul(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8],
                 const std::uint32_t multiplicand[8]) noexcept
{
    std::uint32_t T[16];
    uint256_mul(T, multiplier, multiplicand);
    mont256_redc(ctx, product, T);
}

void mont256_sqr(const Mont256CTX*   ctx,
                 std::uint32_t       product[8],
                 const std::uint32_t multiplier[8]) noexcept
{
    std::uint32_t T[16];
    uint256_sqr(T, multiplier);
    mont256_redc(ctx, product, T);
}

void mont256_div2(const Mont256CTX*   ctx,
                  std::uint32_t       quotient[8],
                  const std::uint32_t dividend[8]) noexcept
{
    int                  c   = 0;
    const std::uint32_t* ref = dividend;
    if (dividend[0] & 1)
    {
        c   = uint256_add_carry(quotient, dividend, ctx->P);
        ref = quotient;
    }
    for (int i = 0; i < 7; i++)
    {
        quotient[i] = (ref[i + 1] << 31) | (ref[i] >> 1);
    }
    quotient[7] = (c << 31) | (ref[7] >> 1);
}

void mont256_pow(const Mont256CTX*   ctx,
                 std::uint32_t       power[8],
                 const std::uint32_t base[8],
                 const std::uint32_t exponent[8]) noexcept
{
    if (uint256_equal_zero(base))
    {
        uint256_set_zero(power);
        return;
    }
    if (uint256_equal_zero(exponent))
    {
        uint256_set_one(power);
        return;
    }

    std::uint8_t  e_u8[32];
    std::uint32_t mont_t[8], lut_table[16 - 2][8]; // j: base^(j+2)
    int           i = 0;

    // init lut table
    mont256_sqr(ctx, lut_table[0], base);
    for (int j = 1; j < 14; j++)
    {
        mont256_mul(ctx, lut_table[j], lut_table[j - 1], base);
    }
    // compute power
    uint256_to_bytes(e_u8, exponent);
    while (e_u8[i] == 0) i++;
    if (e_u8[i] > 0xF)
    {
        int index = (e_u8[i] >> 4) & 0xF;
        mont256_cpy(ctx, mont_t, (index == 1) ? base : lut_table[index - 2]);

        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        index = e_u8[i] & 0xF;
        if (index != 0)
        {
            mont256_mul(ctx, mont_t, mont_t,
                        (index == 1) ? base : lut_table[index - 2]);
        }
    }
    else
    {
        int index = e_u8[i] & 0xF;
        mont256_cpy(ctx, mont_t, (index == 1) ? base : lut_table[index - 2]);
    }
    i++;
    for (; i < 32; i++)
    {
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        if (((e_u8[i] >> 4) & 0xF) != 0)
        {
            int index = (e_u8[i] >> 4) & 0xF;
            mont256_mul(ctx, mont_t, mont_t,
                        (index == 1) ? base : lut_table[index - 2]);
        }
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        mont256_sqr(ctx, mont_t, mont_t);
        if ((e_u8[i] & 0xF) != 0)
        {
            int index = e_u8[i] & 0xF;
            mont256_mul(ctx, mont_t, mont_t,
                        (index == 1) ? base : lut_table[index - 2]);
        }
    }
    mont256_cpy(ctx, power, mont_t);
}

void mont256_inv(const Mont256CTX*   ctx,
                 std::uint32_t       inverse[8],
                 const std::uint32_t num[8]) noexcept
{
    mont256_pow(ctx, inverse, num, ctx->P_SUB2);
}

// ****************************************
// *************** Compare ****************
// ****************************************

bool mont256_equal(const Mont256CTX*   ctx,
                   const std::uint32_t a[8],
                   const std::uint32_t b[8]) noexcept
{
    return uint256_equal(a, b);
}

bool mont256_equal_zero(const Mont256CTX*   ctx,
                        const std::uint32_t a[8]) noexcept
{
    return uint256_equal_zero(a);
}

bool mont256_equal_one(const Mont256CTX* ctx, const std::uint32_t a[8]) noexcept
{
    return uint256_equal(a, ctx->R);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void mont256_cpy(const Mont256CTX*   ctx,
                 std::uint32_t       ret[8],
                 const std::uint32_t num[8]) noexcept
{
    uint256_cpy(ret, num);
}

void mont256_set_zero(const Mont256CTX* ctx, std::uint32_t num[8]) noexcept
{
    uint256_set_zero(num);
}

void mont256_set_one(const Mont256CTX* ctx, std::uint32_t ret[8]) noexcept
{
    uint256_cpy(ret, ctx->R);
}

void mont256_set_uint32(const Mont256CTX* ctx,
                        std::uint32_t     ret[8],
                        std::uint32_t     num) noexcept
{
    uint256_set_uint32(ret, num);
    uint256_to_mont(ctx, ret, ret);
}

// ****************************************
// *************** Convert ****************
// ****************************************

void mont256_from_bytes(const Mont256CTX*  ctx,
                        std::uint32_t      num[8],
                        const std::uint8_t bytes[32]) noexcept
{
    uint256_from_bytes(num, bytes);
    uint256_to_mont(ctx, num, num);
}

void mont256_to_bytes(const Mont256CTX*   ctx,
                      std::uint8_t        bytes[32],
                      const std::uint32_t num[8]) noexcept
{
    std::uint32_t t[8];
    uint256_from_mont(ctx, t, num);
    uint256_to_bytes(bytes, t);
}

void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                           std::uint32_t       num[8],
                           const std::uint8_t* bytes,
                           std::size_t         bytes_len) noexcept
{
    uint32_t t[8];
    uint256_mod(t, bytes, bytes_len, ctx->P);
    uint256_to_mont(ctx, num, t);
}

}; // namespace number::internal::common