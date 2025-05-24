#include <gmlib/number/mont256.h>

#include "config.h"

#if defined(NUMBER_IMPL_MONT256_X64)
#include "mont256_x64.h"
namespace number {
namespace alg = internal::x64;
typedef std::uint64_t limb_t;

static const char* MONT256_ALGO_NAME = "x64";

}; // namespace number
#else
#include "mont256_common.h"
namespace number {
namespace alg = internal::common;
typedef std::uint32_t limb_t;

static const char* MONT256_ALGO_NAME = "common";

}; // namespace number
#endif

namespace number {

const char* mont256_fetch_impl_algo() noexcept
{
    return MONT256_ALGO_NAME;
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

void mont256_add(const Mont256CTX*  ctx,
                 std::uint8_t       sum[32],
                 const std::uint8_t augend[32],
                 const std::uint8_t addend[32]) noexcept
{
    return alg::mont256_add(ctx,                    //
                            (limb_t*)sum,           //
                            (const limb_t*)augend,  //
                            (const limb_t*)addend); //
}

void mont256_sub(const Mont256CTX*  ctx,
                 std::uint8_t       difference[32],
                 const std::uint8_t minuend[32],
                 const std::uint8_t subtrahend[32]) noexcept
{
    return alg::mont256_sub(ctx,                        //
                            (limb_t*)difference,        //
                            (const limb_t*)minuend,     //
                            (const limb_t*)subtrahend); //
}

void mont256_dbl(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept
{
    return alg::mont256_dbl(ctx, (limb_t*)product, (const limb_t*)multiplier);
}

void mont256_tpl(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept
{
    return alg::mont256_tpl(ctx, (limb_t*)product, (const limb_t*)multiplier);
}

void mont256_neg(const Mont256CTX*  ctx,
                 std::uint8_t       ret[32],
                 const std::uint8_t num[32]) noexcept
{
    return alg::mont256_neg(ctx, (limb_t*)ret, (const limb_t*)num);
}

void mont256_mul(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32],
                 const std::uint8_t multiplicand[32]) noexcept
{
    return alg::mont256_mul(ctx,                          //
                            (limb_t*)product,             //
                            (const limb_t*)multiplier,    //
                            (const limb_t*)multiplicand); //
}

void mont256_sqr(const Mont256CTX*  ctx,
                 std::uint8_t       product[32],
                 const std::uint8_t multiplier[32]) noexcept
{
    return alg::mont256_sqr(ctx, (limb_t*)product, (const limb_t*)multiplier);
}

void mont256_pow(const Mont256CTX*  ctx,
                 std::uint8_t       power[32],
                 const std::uint8_t base[32],
                 const std::uint8_t exponent[32]) noexcept
{
    return alg::mont256_pow(ctx,                      //
                            (limb_t*)power,           //
                            (const limb_t*)base,      //
                            (const limb_t*)exponent); //
}

void mont256_div2(const Mont256CTX*  ctx,
                  std::uint8_t       quotient[32],
                  const std::uint8_t dividend[32]) noexcept
{
    return alg::mont256_div2(ctx, (limb_t*)quotient, (const limb_t*)dividend);
}

void mont256_inv(const Mont256CTX*  ctx,
                 std::uint8_t       inverse[32],
                 const std::uint8_t num[32]) noexcept
{
    return alg::mont256_inv(ctx, (limb_t*)inverse, (const limb_t*)num);
}

// ****************************************
// *************** Compare ****************
// ****************************************

bool mont256_equal(const Mont256CTX*  ctx,
                   const std::uint8_t a[32],
                   const std::uint8_t b[32]) noexcept
{
    return alg::mont256_equal(ctx, (const limb_t*)a, (const limb_t*)b);
}

bool mont256_equal_zero(const Mont256CTX*  ctx,
                        const std::uint8_t a[32]) noexcept
{
    return alg::mont256_equal_zero(ctx, (const limb_t*)a);
}

bool mont256_equal_one(const Mont256CTX* ctx, const std::uint8_t a[32]) noexcept
{
    return alg::mont256_equal_one(ctx, (const limb_t*)a);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void mont256_cpy(const Mont256CTX*  ctx,
                 std::uint8_t       ret[32],
                 const std::uint8_t num[32]) noexcept
{
    return alg::mont256_cpy(ctx, (limb_t*)ret, (const limb_t*)num);
}

void mont256_set_zero(const Mont256CTX* ctx, std::uint8_t num[32]) noexcept
{
    return alg::mont256_set_zero(ctx, (limb_t*)num);
}

void mont256_set_one(const Mont256CTX* ctx, std::uint8_t num[32]) noexcept
{
    return alg::mont256_set_one(ctx, (limb_t*)num);
}

void mont256_set_uint32(const Mont256CTX* ctx,
                        std::uint8_t      ret[32],
                        std::uint32_t     num) noexcept
{
    return alg::mont256_set_uint32(ctx, (limb_t*)ret, num);
}

void mont256_set_uint64(const Mont256CTX* ctx,
                        std::uint8_t      ret[32],
                        std::uint64_t     num) noexcept
{
    return alg::mont256_set_uint64(ctx, (limb_t*)ret, num);
}

// ****************************************
// *************** Convert ****************
// ****************************************

void mont256_from_bytes(const Mont256CTX*  ctx,
                        std::uint8_t       num[32],
                        const std::uint8_t bytes[32]) noexcept
{
    return alg::mont256_from_bytes(ctx, (limb_t*)num, bytes);
}

void mont256_to_bytes(const Mont256CTX*  ctx,
                      std::uint8_t       bytes[32],
                      const std::uint8_t num[32]) noexcept
{
    return alg::mont256_to_bytes(ctx, bytes, (const limb_t*)num);
}

void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                           std::uint8_t        num[32],
                           const std::uint8_t* bytes,
                           std::size_t         bytes_len) noexcept
{
    return alg::mont256_from_bytes_ex(ctx, (limb_t*)num, bytes, bytes_len);
}

} // namespace number