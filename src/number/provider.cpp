#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/number/mont256.h>
#include <gmlib/number/uint256.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "mont256_common.h"
#include "mont256_x64.h"
#include "mpz_common.h"
#include "mpz_x64.h"
#include "uint256_common.h"
#include "uint256_x64.h"

namespace number {

struct NumberProvider
{
    bool (*available)();

    const char* algo_name;

    void (*uint256_add_carry)(void);
    void (*uint256_sub_borrow)(void);
    void (*uint256_dbl_carry)(void);
    void (*uint256_tpl_carry)(void);
    void (*uint256_mul)(void);
    void (*uint256_sqr)(void);
    void (*uint256_add_carry_uint32)(void);
    void (*uint256_add_carry_uint64)(void);
    void (*uint256_sub_borrow_uint32)(void);
    void (*uint256_sub_borrow_uint64)(void);
    void (*uint256_mul_carry_uint32)(void);
    void (*uint256_mul_carry_uint64)(void);
    void (*uint256_div_uint32)(void);
    void (*uint256_div_uint64)(void);
    void (*uint256_mod_add)(void);
    void (*uint256_mod_sub)(void);
    void (*uint256_mod)(void);
    void (*uint256_cmp)(void);
    void (*uint256_cmp_uint32)(void);
    void (*uint256_cmp_uint64)(void);
    void (*uint256_equal)(void);
    void (*uint256_equal_zero)(void);
    void (*uint256_equal_one)(void);
    void (*uint256_cpy)(void);
    void (*uint256_set_zero)(void);
    void (*uint256_set_one)(void);
    void (*uint256_set_uint32)(void);
    void (*uint256_set_uint64)(void);
    void (*uint256_from_bytes)(void);
    void (*uint256_to_bytes)(void);
    void (*uint256_bittest)(void);

    void (*mont256_add)(void);
    void (*mont256_sub)(void);
    void (*mont256_dbl)(void);
    void (*mont256_tpl)(void);
    void (*mont256_neg)(void);
    void (*mont256_mul)(void);
    void (*mont256_sqr)(void);
    void (*mont256_pow)(void);
    void (*mont256_div2)(void);
    void (*mont256_inv)(void);
    void (*mont256_equal)(void);
    void (*mont256_equal_zero)(void);
    void (*mont256_equal_one)(void);
    void (*mont256_cpy)(void);
    void (*mont256_set_zero)(void);
    void (*mont256_set_one)(void);
    void (*mont256_set_uint32)(void);
    void (*mont256_set_uint64)(void);
    void (*mont256_from_bytes)(void);
    void (*mont256_to_bytes)(void);
    void (*mont256_from_bytes_ex)(void);

    void (*mpz_add_carry)(void);
    void (*mpz_sub_borrow)(void);
    void (*mpz_mul)(void);
    void (*mpz_cmp)(void);
    void (*mpz_cpy)(void);
    void (*mpz_from_bytes)(void);
    void (*mpz_to_bytes)(void);
};

static const NumberProvider number_providers[] = {

#if defined(SUPPORT_NUMBER_X64)
    {
        []() {
            static bool available = cpuinfo::x86_64::cpu_supports_bmi2() &&
                                    cpuinfo::x86_64::cpu_supports_movbe();
            return available;
        },
        "x64",
        (void (*)(void))internal::x64::uint256_add_carry,
        (void (*)(void))internal::x64::uint256_sub_borrow,
        (void (*)(void))internal::x64::uint256_dbl_carry,
        (void (*)(void))internal::x64::uint256_tpl_carry,
        (void (*)(void))internal::x64::uint256_mul,
        (void (*)(void))internal::x64::uint256_sqr,
        (void (*)(void))internal::x64::uint256_add_carry_uint32,
        (void (*)(void))internal::x64::uint256_add_carry_uint64,
        (void (*)(void))internal::x64::uint256_sub_borrow_uint32,
        (void (*)(void))internal::x64::uint256_sub_borrow_uint64,
        (void (*)(void))internal::x64::uint256_mul_carry_uint32,
        (void (*)(void))internal::x64::uint256_mul_carry_uint64,
        (void (*)(void))internal::x64::uint256_div_uint32,
        (void (*)(void))internal::x64::uint256_div_uint64,
        (void (*)(void))internal::x64::uint256_mod_add,
        (void (*)(void))internal::x64::uint256_mod_sub,
        (void (*)(void))internal::x64::uint256_mod,
        (void (*)(void))internal::x64::uint256_cmp,
        (void (*)(void))internal::x64::uint256_cmp_uint32,
        (void (*)(void))internal::x64::uint256_cmp_uint64,
        (void (*)(void))internal::x64::uint256_equal,
        (void (*)(void))internal::x64::uint256_equal_zero,
        (void (*)(void))internal::x64::uint256_equal_one,
        (void (*)(void))internal::x64::uint256_cpy,
        (void (*)(void))internal::x64::uint256_set_zero,
        (void (*)(void))internal::x64::uint256_set_one,
        (void (*)(void))internal::x64::uint256_set_uint32,
        (void (*)(void))internal::x64::uint256_set_uint64,
        (void (*)(void))internal::x64::uint256_from_bytes,
        (void (*)(void))internal::x64::uint256_to_bytes,
        (void (*)(void))internal::x64::uint256_bittest,

        (void (*)(void))internal::x64::mont256_add,
        (void (*)(void))internal::x64::mont256_sub,
        (void (*)(void))internal::x64::mont256_dbl,
        (void (*)(void))internal::x64::mont256_tpl,
        (void (*)(void))internal::x64::mont256_neg,
        (void (*)(void))internal::x64::mont256_mul,
        (void (*)(void))internal::x64::mont256_sqr,
        (void (*)(void))internal::x64::mont256_pow,
        (void (*)(void))internal::x64::mont256_div2,
        (void (*)(void))internal::x64::mont256_inv,
        (void (*)(void))internal::x64::mont256_equal,
        (void (*)(void))internal::x64::mont256_equal_zero,
        (void (*)(void))internal::x64::mont256_equal_one,
        (void (*)(void))internal::x64::mont256_cpy,
        (void (*)(void))internal::x64::mont256_set_zero,
        (void (*)(void))internal::x64::mont256_set_one,
        (void (*)(void))internal::x64::mont256_set_uint32,
        (void (*)(void))internal::x64::mont256_set_uint64,
        (void (*)(void))internal::x64::mont256_from_bytes,
        (void (*)(void))internal::x64::mont256_to_bytes,
        (void (*)(void))internal::x64::mont256_from_bytes_ex,

        (void (*)(void))internal::x64::mpz_add_carry,
        (void (*)(void))internal::x64::mpz_sub_borrow,
        (void (*)(void))internal::x64::mpz_mul,
        (void (*)(void))internal::x64::mpz_cmp,
        (void (*)(void))internal::x64::mpz_cpy,
        (void (*)(void))internal::x64::mpz_from_bytes,
        (void (*)(void))internal::x64::mpz_to_bytes,
    },
#endif

    {
        []() { return true; },
        "common",
        (void (*)(void))internal::common::uint256_add_carry,
        (void (*)(void))internal::common::uint256_sub_borrow,
        (void (*)(void))internal::common::uint256_dbl_carry,
        (void (*)(void))internal::common::uint256_tpl_carry,
        (void (*)(void))internal::common::uint256_mul,
        (void (*)(void))internal::common::uint256_sqr,
        (void (*)(void))internal::common::uint256_add_carry_uint32,
        (void (*)(void))internal::common::uint256_add_carry_uint64,
        (void (*)(void))internal::common::uint256_sub_borrow_uint32,
        (void (*)(void))internal::common::uint256_sub_borrow_uint64,
        (void (*)(void))internal::common::uint256_mul_carry_uint32,
        (void (*)(void))internal::common::uint256_mul_carry_uint64,
        (void (*)(void))internal::common::uint256_div_uint32,
        (void (*)(void))internal::common::uint256_div_uint64,
        (void (*)(void))internal::common::uint256_mod_add,
        (void (*)(void))internal::common::uint256_mod_sub,
        (void (*)(void))internal::common::uint256_mod,
        (void (*)(void))internal::common::uint256_cmp,
        (void (*)(void))internal::common::uint256_cmp_uint32,
        (void (*)(void))internal::common::uint256_cmp_uint64,
        (void (*)(void))internal::common::uint256_equal,
        (void (*)(void))internal::common::uint256_equal_zero,
        (void (*)(void))internal::common::uint256_equal_one,
        (void (*)(void))internal::common::uint256_cpy,
        (void (*)(void))internal::common::uint256_set_zero,
        (void (*)(void))internal::common::uint256_set_one,
        (void (*)(void))internal::common::uint256_set_uint32,
        (void (*)(void))internal::common::uint256_set_uint64,
        (void (*)(void))internal::common::uint256_from_bytes,
        (void (*)(void))internal::common::uint256_to_bytes,
        (void (*)(void))internal::common::uint256_bittest,

        (void (*)(void))internal::common::mont256_add,
        (void (*)(void))internal::common::mont256_sub,
        (void (*)(void))internal::common::mont256_dbl,
        (void (*)(void))internal::common::mont256_tpl,
        (void (*)(void))internal::common::mont256_neg,
        (void (*)(void))internal::common::mont256_mul,
        (void (*)(void))internal::common::mont256_sqr,
        (void (*)(void))internal::common::mont256_pow,
        (void (*)(void))internal::common::mont256_div2,
        (void (*)(void))internal::common::mont256_inv,
        (void (*)(void))internal::common::mont256_equal,
        (void (*)(void))internal::common::mont256_equal_zero,
        (void (*)(void))internal::common::mont256_equal_one,
        (void (*)(void))internal::common::mont256_cpy,
        (void (*)(void))internal::common::mont256_set_zero,
        (void (*)(void))internal::common::mont256_set_one,
        (void (*)(void))internal::common::mont256_set_uint32,
        (void (*)(void))internal::common::mont256_set_uint64,
        (void (*)(void))internal::common::mont256_from_bytes,
        (void (*)(void))internal::common::mont256_to_bytes,
        (void (*)(void))internal::common::mont256_from_bytes_ex,

        (void (*)(void))internal::common::mpz_add_carry,
        (void (*)(void))internal::common::mpz_sub_borrow,
        (void (*)(void))internal::common::mpz_mul,
        (void (*)(void))internal::common::mpz_cmp,
        (void (*)(void))internal::common::mpz_cpy,
        (void (*)(void))internal::common::mpz_from_bytes,
        (void (*)(void))internal::common::mpz_to_bytes,
    },
    {nullptr},
};
static const NumberProvider* get_provider(const NumberProvider* providers,
                                          const char* name = nullptr) noexcept
{
    std::size_t idx = 0;
    while (providers[idx].algo_name != nullptr)
    {
        if (providers[idx].available())
        {
            if (name == nullptr)
            {
                return &providers[idx];
            }

            if (std::strcmp(providers[idx].algo_name, name) == 0)
            {
                return &providers[idx];
            }
        }
        idx += 1;
    }
    std::printf("[uBlock PROVIDER] Provider %s is not available. %s:%d\n",
                name ? name : "", __FILE__, __LINE__);
    std::exit(-1);
}

#define NUMBER_PROVIDER get_provider(number_providers, nullptr)

} // namespace number

namespace number {

const char* uint256_fetch_impl_algo() noexcept
{
    return NUMBER_PROVIDER->algo_name;
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

int uint256_add_carry(std::uint8_t       sum[32],
                      const std::uint8_t augend[32],
                      const std::uint8_t addend[32]) noexcept
{
    using fn_t = int (*)(void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_add_carry);
    return fn(sum, augend, addend);
}

int uint256_sub_borrow(std::uint8_t       difference[32],
                       const std::uint8_t minuend[32],
                       const std::uint8_t subtrahend[32]) noexcept
{
    using fn_t = int (*)(void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_sub_borrow);
    return fn(difference, minuend, subtrahend);
}

int uint256_dbl_carry(std::uint8_t       product[32],
                      const std::uint8_t multiplier[32]) noexcept
{
    using fn_t = int (*)(void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_dbl_carry);
    return fn(product, multiplier);
}

int uint256_tpl_carry(std::uint8_t       product[32],
                      const std::uint8_t multiplier[32]) noexcept
{
    using fn_t = int (*)(void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_tpl_carry);
    return fn(product, multiplier);
}

void uint256_mul(std::uint8_t       product[64],
                 const std::uint8_t multiplier[32],
                 const std::uint8_t multiplicand[32]) noexcept
{
    using fn_t = void (*)(void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_mul);
    fn(product, multiplier, multiplicand);
}

void uint256_sqr(std::uint8_t       product[64],
                 const std::uint8_t multiplier[32]) noexcept
{
    using fn_t = void (*)(void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_sqr);
    fn(product, multiplier);
}

int uint256_add_carry_uint32(std::uint8_t       sum[32],
                             const std::uint8_t augend[32],
                             std::uint32_t      addend) noexcept
{
    using fn_t = int (*)(void*, const void*, std::uint32_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_add_carry_uint32);
    return fn(sum, augend, addend);
}

int uint256_add_carry_uint64(std::uint8_t       sum[32],
                             const std::uint8_t augend[32],
                             std::uint64_t      addend) noexcept
{
    using fn_t = int (*)(void*, const void*, std::uint64_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_add_carry_uint64);
    return fn(sum, augend, addend);
}

int uint256_sub_borrow_uint32(std::uint8_t       difference[32],
                              const std::uint8_t minuend[32],
                              std::uint32_t      subtrahend) noexcept
{
    using fn_t = int (*)(void*, const void*, std::uint32_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_sub_borrow_uint32);
    return fn(difference, minuend, subtrahend);
}

int uint256_sub_borrow_uint64(std::uint8_t       difference[32],
                              const std::uint8_t minuend[32],
                              std::uint64_t      subtrahend) noexcept
{
    using fn_t = int (*)(void*, const void*, std::uint64_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_sub_borrow_uint64);
    return fn(difference, minuend, subtrahend);
}

std::uint32_t uint256_mul_carry_uint32(std::uint8_t       product[32],
                                       const std::uint8_t multiplier[32],
                                       std::uint32_t      multiplicand) noexcept
{
    using fn_t = std::uint32_t (*)(void*, const void*, std::uint32_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_mul_carry_uint32);
    return fn(product, multiplier, multiplicand);
}

std::uint64_t uint256_mul_carry_uint64(std::uint8_t       product[32],
                                       const std::uint8_t multiplier[32],
                                       std::uint64_t      multiplicand) noexcept
{
    using fn_t = std::uint64_t (*)(void*, const void*, std::uint64_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_mul_carry_uint64);
    return fn(product, multiplier, multiplicand);
}

std::uint32_t uint256_div_uint32(std::uint8_t       quotient[32],
                                 const std::uint8_t dividend[32],
                                 std::uint32_t      divisor) noexcept
{
    using fn_t = std::uint32_t (*)(void*, const void*, std::uint32_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_div_uint32);
    return fn(quotient, dividend, divisor);
}

std::uint64_t uint256_div_uint64(std::uint8_t       quotient[32],
                                 const std::uint8_t dividend[32],
                                 std::uint64_t      divisor) noexcept
{
    using fn_t = std::uint64_t (*)(void*, const void*, std::uint64_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_div_uint64);
    return fn(quotient, dividend, divisor);
}

void uint256_mod_add(std::uint8_t       sum[32],
                     const std::uint8_t augend[32],
                     const std::uint8_t addend[32],
                     const std::uint8_t divisor[32]) noexcept
{
    using fn_t = void (*)(void*, const void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_mod_add);
    fn(sum, augend, addend, divisor);
}

void uint256_mod_sub(std::uint8_t       difference[32],
                     const std::uint8_t minuend[32],
                     const std::uint8_t subtrahend[32],
                     const std::uint8_t divisor[32]) noexcept
{
    using fn_t = void (*)(void*, const void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_mod_sub);
    fn(difference, minuend, subtrahend, divisor);
}

void uint256_mod(std::uint8_t        remainder[32],
                 const std::uint8_t* data,
                 std::size_t         data_len,
                 const std::uint8_t  divisor[32]) noexcept
{
    using fn_t = void (*)(void*, const void*, std::size_t, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_mod);
    fn(remainder, data, data_len, divisor);
}

// ****************************************
// *************** Compare ****************
// ****************************************

int uint256_cmp(const std::uint8_t a[32], const std::uint8_t b[32]) noexcept
{
    using fn_t = int (*)(const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_cmp);
    return fn(a, b);
}

int uint256_cmp_uint32(const std::uint8_t a[32], std::uint32_t b) noexcept
{
    using fn_t = int (*)(const void*, std::uint32_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_cmp_uint32);
    return fn(a, b);
}

int uint256_cmp_uint64(const std::uint8_t a[32], std::uint64_t b) noexcept
{
    using fn_t = int (*)(const void*, std::uint64_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_cmp_uint64);
    return fn(a, b);
}

bool uint256_equal(const std::uint8_t a[32], const std::uint8_t b[32]) noexcept
{
    using fn_t = bool (*)(const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_equal);
    return fn(a, b);
}

bool uint256_equal_zero(const std::uint8_t a[32]) noexcept
{
    using fn_t = bool (*)(const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_equal_zero);
    return fn(a);
}

bool uint256_equal_one(const std::uint8_t a[32]) noexcept
{
    using fn_t = bool (*)(const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_equal_one);
    return fn(a);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void uint256_cpy(std::uint8_t ret[32], const std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_cpy);
    fn(ret, num);
}

void uint256_set_zero(std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_set_zero);
    fn(num);
}

void uint256_set_one(std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_set_one);
    fn(num);
}

void uint256_set_uint32(std::uint8_t ret[32], std::uint32_t num) noexcept
{
    using fn_t = void (*)(void*, std::uint32_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_set_uint32);
    fn(ret, num);
}

void uint256_set_uint64(std::uint8_t ret[32], std::uint64_t num) noexcept
{
    using fn_t = void (*)(void*, std::uint64_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_set_uint64);
    fn(ret, num);
}

// ****************************************
// *************** Convert ****************
// ****************************************

void uint256_from_bytes(std::uint8_t       ret[32],
                        const std::uint8_t bytes[32]) noexcept
{
    using fn_t = void (*)(void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_from_bytes);
    fn(ret, bytes);
}

void uint256_to_bytes(std::uint8_t       bytes[32],
                      const std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_to_bytes);
    fn(bytes, num);
}

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

bool uint256_bittest(const std::uint8_t num[32], int i) noexcept
{
    using fn_t = bool (*)(const void*, int);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->uint256_bittest);
    return fn(num, i);
}

} // namespace number

namespace number {

const char* mont256_fetch_impl_algo() noexcept
{
    return NUMBER_PROVIDER->algo_name;
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

void mont256_add(const Mont256CTX*  ctx,
                 std::uint8_t       sum[32],
                 const std::uint8_t augend[32],
                 const std::uint8_t addend[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_add);
    fn(ctx, sum, augend, addend);
}

void mont256_sub(const Mont256CTX*  ctx,
                 std::uint8_t       difference[32],
                 const std::uint8_t minuend[32],
                 const std::uint8_t subtrahend[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_sub);
    fn(ctx, difference, minuend, subtrahend);
}

void mont256_dbl(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_dbl);
    fn(ctx, product, multiplier);
}

void mont256_tpl(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_tpl);
    fn(ctx, product, multiplier);
}

void mont256_neg(const Mont256CTX*  ctx,
                 std::uint8_t       ret[32],
                 const std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_neg);
    fn(ctx, ret, num);
}

void mont256_mul(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32],
                 const std::uint8_t multiplicand[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_mul);
    fn(ctx, product, multiplier, multiplicand);
}

void mont256_sqr(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_sqr);
    fn(ctx, product, multiplier);
}

void mont256_pow(const Mont256CTX*  ctx,
                 std::uint8_t       power[32],
                 const std::uint8_t base[32],
                 const std::uint8_t exponent[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_pow);
    fn(ctx, power, base, exponent);
}

void mont256_div2(const Mont256CTX*  ctx,
                  std::uint8_t       quotient[32],
                  const std::uint8_t dividend[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_div2);
    fn(ctx, quotient, dividend);
}

void mont256_inv(const Mont256CTX*  ctx,
                 std::uint8_t       inverse[32],
                 const std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_inv);
    fn(ctx, inverse, num);
}

// ****************************************
// *************** Compare ****************
// ****************************************

bool mont256_equal(const Mont256CTX*  ctx,
                   const std::uint8_t a[32],
                   const std::uint8_t b[32]) noexcept
{
    using fn_t = bool (*)(const Mont256CTX*, const void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_equal);
    return fn(ctx, a, b);
}

bool mont256_equal_zero(const Mont256CTX*  ctx,
                        const std::uint8_t a[32]) noexcept
{
    using fn_t = bool (*)(const Mont256CTX*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_equal_zero);
    return fn(ctx, a);
}

bool mont256_equal_one(const Mont256CTX* ctx, const std::uint8_t a[32]) noexcept
{
    using fn_t = bool (*)(const Mont256CTX*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_equal_one);
    return fn(ctx, a);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void mont256_cpy(const Mont256CTX*  ctx,
                 std::uint8_t       ret[32],
                 const std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_cpy);
    fn(ctx, ret, num);
}

void mont256_set_zero(const Mont256CTX* ctx, std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_set_zero);
    fn(ctx, num);
}

void mont256_set_one(const Mont256CTX* ctx, std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_set_one);
    fn(ctx, num);
}

void mont256_set_uint32(const Mont256CTX* ctx,
                        std::uint8_t      ret[32],
                        std::uint32_t     num) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, std::uint32_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_set_uint32);
    fn(ctx, ret, num);
}

void mont256_set_uint64(const Mont256CTX* ctx,
                        std::uint8_t      ret[32],
                        std::uint64_t     num) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, std::uint64_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_set_uint64);
    fn(ctx, ret, num);
}

// ****************************************
// *************** Convert ****************
// ****************************************

void mont256_from_bytes(const Mont256CTX*  ctx,
                        std::uint8_t       num[32],
                        const std::uint8_t bytes[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_from_bytes);
    fn(ctx, num, bytes);
}

void mont256_to_bytes(const Mont256CTX*  ctx,
                      std::uint8_t       bytes[32],
                      const std::uint8_t num[32]) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_to_bytes);
    fn(ctx, bytes, num);
}

void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                           std::uint8_t        num[32],
                           const std::uint8_t* bytes,
                           std::size_t         bytes_len) noexcept
{
    using fn_t = void (*)(const Mont256CTX*, void*, const void*, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mont256_from_bytes_ex);
    fn(ctx, num, bytes, bytes_len);
}
} // namespace number

namespace number {

int mpz_add_carry(std::uint8_t*       r,
                  const std::uint8_t* a,
                  const std::uint8_t* b,
                  int                 carry,
                  std::size_t         bits) noexcept
{
    using fn_t = int (*)(void*, const void*, const void*, int, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mpz_add_carry);
    return fn(r, a, b, carry, bits);
}

int mpz_sub_borrow(std::uint8_t*       r,
                   const std::uint8_t* a,
                   const std::uint8_t* b,
                   int                 borrow,
                   std::size_t         bits) noexcept
{
    using fn_t = int (*)(void*, const void*, const void*, int, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mpz_sub_borrow);
    return fn(r, a, b, borrow, bits);
}

void mpz_mul(std::uint8_t*       r,
             const std::uint8_t* a,
             const std::uint8_t* b,
             std::size_t         bits) noexcept
{
    using fn_t = void (*)(void*, const void*, const void*, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mpz_mul);
    fn(r, a, b, bits);
}

int mpz_cmp(const std::uint8_t* a,
            const std::uint8_t* b,
            std::size_t         bits) noexcept
{
    using fn_t = int (*)(const void*, const void*, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mpz_cmp);
    return fn(a, b, bits);
}

void mpz_cpy(std::uint8_t* r, const std::uint8_t* a, std::size_t bits) noexcept
{
    using fn_t = void (*)(void*, const void*, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mpz_cpy);
    fn(r, a, bits);
}

void mpz_from_bytes(std::uint8_t*       r,
                    const std::uint8_t* src,
                    std::size_t         bits) noexcept
{
    using fn_t = void (*)(void*, const void*, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mpz_from_bytes);
    fn(r, src, bits);
}

void mpz_to_bytes(std::uint8_t*       r,
                  const std::uint8_t* src,
                  std::size_t         bits) noexcept
{
    using fn_t = void (*)(void*, const void*, std::size_t);
    fn_t fn    = (fn_t)(NUMBER_PROVIDER->mpz_to_bytes);
    fn(r, src, bits);
}

} // namespace  number
