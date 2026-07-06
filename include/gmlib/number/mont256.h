#ifndef NUMBER_MONT256_H
#define NUMBER_MONT256_H

#include <gmlib/number/provider.h>

#include <cassert>
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

static inline const char* mont256_fetch_impl_algo() noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    return provider->algo_name;
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

static inline void mont256_add(const Mont256CTX*  ctx,
                               std::uint8_t       sum[32],
                               const std::uint8_t augend[32],
                               const std::uint8_t addend[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_add != nullptr);
    provider->mont256_add(ctx, sum, augend, addend);
}

static inline void mont256_sub(const Mont256CTX*  ctx,
                               std::uint8_t       difference[32],
                               const std::uint8_t minuend[32],
                               const std::uint8_t subtrahend[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_sub != nullptr);
    provider->mont256_sub(ctx, difference, minuend, subtrahend);
}

static inline void mont256_dbl(const Mont256CTX*  ctx,
                               std::uint8_t       product[32],
                               const std::uint8_t multiplier[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_dbl != nullptr);
    provider->mont256_dbl(ctx, product, multiplier);
}

static inline void mont256_tpl(const Mont256CTX*  ctx,
                               std::uint8_t       product[32],
                               const std::uint8_t multiplier[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_tpl != nullptr);
    provider->mont256_tpl(ctx, product, multiplier);
}

static inline void mont256_neg(const Mont256CTX*  ctx,
                               std::uint8_t       ret[32],
                               const std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_neg != nullptr);
    provider->mont256_neg(ctx, ret, num);
}

static inline void mont256_mul(const Mont256CTX*  ctx,
                               std::uint8_t       product[32],
                               const std::uint8_t multiplier[32],
                               const std::uint8_t multiplicand[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_mul != nullptr);
    provider->mont256_mul(ctx, product, multiplier, multiplicand);
}

static inline void mont256_sqr(const Mont256CTX*  ctx,
                               std::uint8_t       product[32],
                               const std::uint8_t multiplier[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_sqr != nullptr);
    provider->mont256_sqr(ctx, product, multiplier);
}

static inline void mont256_pow(const Mont256CTX*  ctx,
                               std::uint8_t       power[32],
                               const std::uint8_t base[32],
                               const std::uint8_t exponent[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_pow != nullptr);
    provider->mont256_pow(ctx, power, base, exponent);
}

static inline void mont256_div2(const Mont256CTX*  ctx,
                                std::uint8_t       quotient[32],
                                const std::uint8_t dividend[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_div2 != nullptr);
    provider->mont256_div2(ctx, quotient, dividend);
}

static inline void mont256_inv(const Mont256CTX*  ctx,
                               std::uint8_t       inverse[32],
                               const std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_inv != nullptr);
    provider->mont256_inv(ctx, inverse, num);
}

// ****************************************
// *************** Compare ****************
// ****************************************

static inline bool mont256_equal(const Mont256CTX*  ctx,
                                 const std::uint8_t a[32],
                                 const std::uint8_t b[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_equal != nullptr);
    return provider->mont256_equal(ctx, a, b);
}

static inline bool mont256_equal_zero(const Mont256CTX*  ctx,
                                      const std::uint8_t a[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_equal_zero != nullptr);
    return provider->mont256_equal_zero(ctx, a);
}

static inline bool mont256_equal_one(const Mont256CTX*  ctx,
                                     const std::uint8_t a[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_equal_one != nullptr);
    return provider->mont256_equal_one(ctx, a);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

static inline void mont256_cpy(const Mont256CTX*  ctx,
                               std::uint8_t       ret[32],
                               const std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_cpy != nullptr);
    provider->mont256_cpy(ctx, ret, num);
}

static inline void mont256_set_zero(const Mont256CTX* ctx,
                                    std::uint8_t      num[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_set_zero != nullptr);
    provider->mont256_set_zero(ctx, num);
}

static inline void mont256_set_one(const Mont256CTX* ctx,
                                   std::uint8_t      num[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_set_one != nullptr);
    provider->mont256_set_one(ctx, num);
}

static inline void mont256_set_uint32(const Mont256CTX* ctx,
                                      std::uint8_t      ret[32],
                                      std::uint32_t     num) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_set_uint32 != nullptr);
    provider->mont256_set_uint32(ctx, ret, num);
}

static inline void mont256_set_uint64(const Mont256CTX* ctx,
                                      std::uint8_t      ret[32],
                                      std::uint64_t     num) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_set_uint64 != nullptr);
    provider->mont256_set_uint64(ctx, ret, num);
}

// ****************************************
// *************** Convert ****************
// ****************************************

static inline void mont256_from_bytes(const Mont256CTX*  ctx,
                                      std::uint8_t       num[32],
                                      const std::uint8_t bytes[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes != nullptr);
    provider->mont256_from_bytes(ctx, num, bytes);
}

static inline void mont256_to_bytes(const Mont256CTX*  ctx,
                                    std::uint8_t       bytes[32],
                                    const std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_to_bytes != nullptr);
    provider->mont256_to_bytes(ctx, bytes, num);
}

static inline void mont256_from_bytes_ex(const Mont256CTX*   ctx,
                                         std::uint8_t        num[32],
                                         const std::uint8_t* bytes,
                                         std::size_t         bytes_len) noexcept
{
    const NumberProvider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes_ex != nullptr);
    provider->mont256_from_bytes_ex(ctx, num, bytes, bytes_len);
}

} // namespace number

#endif
