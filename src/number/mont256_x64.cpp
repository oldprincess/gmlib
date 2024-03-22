#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/mont256_x64.h>
#include <gmlib/number/internal/uint256_x64.h>
#include <immintrin.h>

#if defined(_MSC_VER)
#include <intrin.h>
#else

#define _mulx_u64(a, b, c) _mulx_u64(a, b, (long long unsigned int*)c)
#define _addcarry_u64(a, b, c, d) \
    _addcarry_u64(a, b, c, (long long unsigned int*)d)
#define _subborrow_u64(a, b, c, d) \
    _subborrow_u64(a, b, c, (long long unsigned int*)d)

#endif

namespace number::internal::x64 {

static void mont256_redc(const Mont256CTX* ctx,
                         std::uint64_t     r[4],
                         std::uint64_t     T[8]) noexcept
{
    unsigned char CF; // carry flag

    std::uint64_t T8;              // T = multiplier x multiplicand
    std::uint64_t m, m_times_p[5]; // m * P
    std::uint64_t hi[4];           // product higher

    // *****************************************************
    // ***************** Mont Reduce ***********************
    // *****************************************************
    T8 = 0;
    // step 1
    m            = (std::uint64_t)(T[0] * ctx->N_);
    m_times_p[0] = _mulx_u64(ctx->P[0], m, &hi[0]);
    m_times_p[1] = _mulx_u64(ctx->P[1], m, &hi[1]);
    m_times_p[2] = _mulx_u64(ctx->P[2], m, &hi[2]);
    m_times_p[3] = _mulx_u64(ctx->P[3], m, &hi[3]);

    CF = _addcarry_u64(0, m_times_p[1], hi[0], &m_times_p[1]);
    CF = _addcarry_u64(CF, m_times_p[2], hi[1], &m_times_p[2]);
    CF = _addcarry_u64(CF, m_times_p[3], hi[2], &m_times_p[3]);
    _addcarry_u64(CF, 0, hi[3], &m_times_p[4]); // drop CF

    CF = _addcarry_u64(0, T[0], m_times_p[0], &T[0]);
    CF = _addcarry_u64(CF, T[1], m_times_p[1], &T[1]);
    CF = _addcarry_u64(CF, T[2], m_times_p[2], &T[2]);
    CF = _addcarry_u64(CF, T[3], m_times_p[3], &T[3]);
    CF = _addcarry_u64(CF, T[4], m_times_p[4], &T[4]);
    CF = _addcarry_u64(CF, T[5], 0, &T[5]);
    CF = _addcarry_u64(CF, T[6], 0, &T[6]);
    CF = _addcarry_u64(CF, T[7], 0, &T[7]);
    _addcarry_u64(CF, T8, 0, &T8);

    // step 2
    m            = (std::uint64_t)(T[1] * ctx->N_);
    m_times_p[0] = _mulx_u64(ctx->P[0], m, &hi[0]);
    m_times_p[1] = _mulx_u64(ctx->P[1], m, &hi[1]);
    m_times_p[2] = _mulx_u64(ctx->P[2], m, &hi[2]);
    m_times_p[3] = _mulx_u64(ctx->P[3], m, &hi[3]);

    CF = _addcarry_u64(0, m_times_p[1], hi[0], &m_times_p[1]);
    CF = _addcarry_u64(CF, m_times_p[2], hi[1], &m_times_p[2]);
    CF = _addcarry_u64(CF, m_times_p[3], hi[2], &m_times_p[3]);
    _addcarry_u64(CF, 0, hi[3], &m_times_p[4]); // drop CF

    CF = _addcarry_u64(0, T[1], m_times_p[0], &T[1]);
    CF = _addcarry_u64(CF, T[2], m_times_p[1], &T[2]);
    CF = _addcarry_u64(CF, T[3], m_times_p[2], &T[3]);
    CF = _addcarry_u64(CF, T[4], m_times_p[3], &T[4]);
    CF = _addcarry_u64(CF, T[5], m_times_p[4], &T[5]);
    CF = _addcarry_u64(CF, T[6], 0, &T[6]);
    CF = _addcarry_u64(CF, T[7], 0, &T[7]);
    _addcarry_u64(CF, T8, 0, &T8);

    // step 3
    m            = (std::uint64_t)(T[2] * ctx->N_);
    m_times_p[0] = _mulx_u64(ctx->P[0], m, &hi[0]);
    m_times_p[1] = _mulx_u64(ctx->P[1], m, &hi[1]);
    m_times_p[2] = _mulx_u64(ctx->P[2], m, &hi[2]);
    m_times_p[3] = _mulx_u64(ctx->P[3], m, &hi[3]);

    CF = _addcarry_u64(0, m_times_p[1], hi[0], &m_times_p[1]);
    CF = _addcarry_u64(CF, m_times_p[2], hi[1], &m_times_p[2]);
    CF = _addcarry_u64(CF, m_times_p[3], hi[2], &m_times_p[3]);
    _addcarry_u64(CF, 0, hi[3], &m_times_p[4]); // drop CF

    CF = _addcarry_u64(0, T[2], m_times_p[0], &T[2]);
    CF = _addcarry_u64(CF, T[3], m_times_p[1], &T[3]);
    CF = _addcarry_u64(CF, T[4], m_times_p[2], &T[4]);
    CF = _addcarry_u64(CF, T[5], m_times_p[3], &T[5]);
    CF = _addcarry_u64(CF, T[6], m_times_p[4], &T[6]);
    CF = _addcarry_u64(CF, T[7], 0, &T[7]);
    _addcarry_u64(CF, T8, 0, &T8);

    // step 4
    m            = (std::uint64_t)(T[3] * ctx->N_);
    m_times_p[0] = _mulx_u64(ctx->P[0], m, &hi[0]);
    m_times_p[1] = _mulx_u64(ctx->P[1], m, &hi[1]);
    m_times_p[2] = _mulx_u64(ctx->P[2], m, &hi[2]);
    m_times_p[3] = _mulx_u64(ctx->P[3], m, &hi[3]);

    CF = _addcarry_u64(0, m_times_p[1], hi[0], &m_times_p[1]);
    CF = _addcarry_u64(CF, m_times_p[2], hi[1], &m_times_p[2]);
    CF = _addcarry_u64(CF, m_times_p[3], hi[2], &m_times_p[3]);
    _addcarry_u64(CF, 0, hi[3], &m_times_p[4]); // drop CF

    CF = _addcarry_u64(0, T[3], m_times_p[0], &T[3]);
    CF = _addcarry_u64(CF, T[4], m_times_p[1], &T[4]);
    CF = _addcarry_u64(CF, T[5], m_times_p[2], &T[5]);
    CF = _addcarry_u64(CF, T[6], m_times_p[3], &T[6]);
    CF = _addcarry_u64(CF, T[7], m_times_p[4], &T[7]);
    _addcarry_u64(CF, T8, 0, &T8);

    r[0] = T[4], r[1] = T[5], r[2] = T[6], r[3] = T[7];
    if (T8 || uint256_cmp(r, ctx->P) >= 0)
    {
        CF = _subborrow_u64(0, r[0], ctx->P[0], &r[0]);
        CF = _subborrow_u64(CF, r[1], ctx->P[1], &r[1]);
        CF = _subborrow_u64(CF, r[2], ctx->P[2], &r[2]);
        _subborrow_u64(CF, r[3], ctx->P[3], &r[3]);
    }
}

static void uint256_to_mont(const Mont256CTX*   ctx,
                            std::uint64_t       r[4],
                            const std::uint64_t a[4]) noexcept
{
    mont256_mul(ctx, r, a, ctx->R_POW2);
}

static void uint256_from_mont(const Mont256CTX*   ctx,
                              std::uint64_t       r[4],
                              const std::uint64_t a[4]) noexcept
{
    std::uint64_t t[8];
    t[0] = a[0], t[1] = a[1], t[2] = a[2], t[3] = a[3];
    t[4] = t[5] = t[6] = t[7] = 0;
    mont256_redc(ctx, r, t);
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

void mont256_add(const Mont256CTX*   ctx,
                 std::uint64_t       sum[4],
                 const std::uint64_t augend[4],
                 const std::uint64_t addend[4]) noexcept
{
    unsigned char c;
    c = _addcarry_u64(0, augend[0], addend[0], &sum[0]);
    c = _addcarry_u64(c, augend[1], addend[1], &sum[1]);
    c = _addcarry_u64(c, augend[2], addend[2], &sum[2]);
    c = _addcarry_u64(c, augend[3], addend[3], &sum[3]);
    if (c || uint256_cmp(sum, ctx->P) >= 0)
    {
        c = _subborrow_u64(0, sum[0], ctx->P[0], &sum[0]);
        c = _subborrow_u64(c, sum[1], ctx->P[1], &sum[1]);
        c = _subborrow_u64(c, sum[2], ctx->P[2], &sum[2]);
        c = _subborrow_u64(c, sum[3], ctx->P[3], &sum[3]);
    }
}

void mont256_sub(const Mont256CTX*   ctx,
                 std::uint64_t       difference[4],
                 const std::uint64_t minuend[4],
                 const std::uint64_t subtrahend[4]) noexcept
{
    unsigned char c;
    c = _subborrow_u64(0, minuend[0], subtrahend[0], &difference[0]);
    c = _subborrow_u64(c, minuend[1], subtrahend[1], &difference[1]);
    c = _subborrow_u64(c, minuend[2], subtrahend[2], &difference[2]);
    c = _subborrow_u64(c, minuend[3], subtrahend[3], &difference[3]);
    if (c || uint256_cmp(difference, ctx->P) >= 0)
    {
        c = _addcarry_u64(0, difference[0], ctx->P[0], &difference[0]);
        c = _addcarry_u64(c, difference[1], ctx->P[1], &difference[1]);
        c = _addcarry_u64(c, difference[2], ctx->P[2], &difference[2]);
        c = _addcarry_u64(c, difference[3], ctx->P[3], &difference[3]);
    }
}

void mont256_dbl(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4]) noexcept
{
    unsigned char c;
    c = _addcarry_u64(0, multiplier[0], multiplier[0], &product[0]);
    c = _addcarry_u64(c, multiplier[1], multiplier[1], &product[1]);
    c = _addcarry_u64(c, multiplier[2], multiplier[2], &product[2]);
    c = _addcarry_u64(c, multiplier[3], multiplier[3], &product[3]);
    if (c || uint256_cmp(product, ctx->P) >= 0)
    {
        c = _subborrow_u64(0, product[0], ctx->P[0], &product[0]);
        c = _subborrow_u64(c, product[1], ctx->P[1], &product[1]);
        c = _subborrow_u64(c, product[2], ctx->P[2], &product[2]);
        c = _subborrow_u64(c, product[3], ctx->P[3], &product[3]);
    }
}

void mont256_tpl(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4]) noexcept
{
    std::uint64_t t[4];
    mont256_dbl(ctx, t, multiplier);
    mont256_add(ctx, product, t, multiplier);
}

void mont256_neg(const Mont256CTX*   ctx,
                 std::uint64_t       ret[4],
                 const std::uint64_t num[4]) noexcept
{
    if (uint256_equal_zero(num))
    {
        uint256_set_zero(ret);
        return;
    }
    uint256_sub_borrow(ret, ctx->P, num);
}

void mont256_mul(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4],
                 const std::uint64_t multiplicand[4]) noexcept
{
    std::uint64_t T[8];
    uint256_mul(T, multiplier, multiplicand);
    mont256_redc(ctx, product, T);
}

void mont256_sqr(const Mont256CTX*   ctx,
                 std::uint64_t       product[4],
                 const std::uint64_t multiplier[4]) noexcept
{
    std::uint64_t T[8];
    uint256_sqr(T, multiplier);
    mont256_redc(ctx, product, T);
}

void mont256_pow(const Mont256CTX*   ctx,
                 std::uint64_t       power[4],
                 const std::uint64_t base[4],
                 const std::uint64_t exponent[4]) noexcept
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
    std::uint64_t mont_t[4], lut_table[16 - 2][4]; // j: base^(j+2)
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

void mont256_div2(const Mont256CTX*   ctx,
                  std::uint64_t       quotient[4],
                  const std::uint64_t dividend[4]) noexcept
{
    int                  c   = 0;
    const std::uint64_t* ref = dividend;
    if (dividend[0] & 1)
    {
        c   = uint256_add_carry(quotient, dividend, ctx->P);
        ref = quotient;
    }
    for (int i = 0; i < 3; i++)
    {
        quotient[i] = (ref[i + 1] << 63) | (ref[i] >> 1);
    }
    quotient[3] = ((std::uint64_t)c << 63) | (ref[3] >> 1);
}

void mont256_inv(const Mont256CTX*   ctx,
                 std::uint64_t       inverse[4],
                 const std::uint64_t num[4]) noexcept
{
    mont256_pow(ctx, inverse, num, ctx->P_SUB2);
}

// ****************************************
// *************** Compare ****************
// ****************************************

bool mont256_equal(const Mont256CTX*   ctx,
                   const std::uint64_t a[4],
                   const std::uint64_t b[4]) noexcept
{
    return uint256_equal(a, b);
}

bool mont256_equal_zero(const Mont256CTX*   ctx,
                        const std::uint64_t a[4]) noexcept
{
    return uint256_equal_zero(a);
}

bool mont256_equal_one(const Mont256CTX* ctx, const std::uint64_t a[4]) noexcept
{
    return uint256_equal(a, ctx->R);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void mont256_cpy(const Mont256CTX*   ctx,
                 std::uint64_t       ret[4],
                 const std::uint64_t num[4]) noexcept
{
    uint256_cpy(ret, num);
}

void mont256_set_zero(const Mont256CTX* ctx, std::uint64_t num[4]) noexcept
{
    uint256_set_zero(num);
}

void mont256_set_one(const Mont256CTX* ctx, std::uint64_t num[4]) noexcept
{
    uint256_cpy(num, ctx->R);
}

void mont256_set_uint64(const Mont256CTX* ctx,
                        std::uint64_t     ret[4],
                        uint64_t          num) noexcept
{
    uint256_set_uint64(ret, num);
    uint256_to_mont(ctx, ret, ret);
}

// ****************************************
// *************** Convert ****************
// ****************************************

void mont256_from_bytes(const Mont256CTX*  ctx,
                        std::uint64_t      num[4],
                        const std::uint8_t bytes[32]) noexcept
{
    uint256_from_bytes(num, bytes);
    uint256_to_mont(ctx, num, num);
}

void mont256_to_bytes(const Mont256CTX*   ctx,
                      std::uint8_t        bytes[32],
                      const std::uint64_t num[4]) noexcept
{
    std::uint64_t t[4];
    uint256_from_mont(ctx, t, num);
    uint256_to_bytes(bytes, t);
}

void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                           std::uint64_t       num[4],
                           const std::uint8_t* bytes,
                           std::size_t         bytes_len) noexcept
{
    std::uint64_t t[4];
    uint256_mod(t, bytes, bytes_len, ctx->P);
    uint256_to_mont(ctx, num, t);
}

} // namespace number::internal::x64

#endif