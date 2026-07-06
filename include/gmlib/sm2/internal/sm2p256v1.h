#ifndef SM2_INTERNAL_SM2P256V1_H
#define SM2_INTERNAL_SM2P256V1_H

#include <gmlib/number/mont256.h>
#include <gmlib/number/uint256.h>
#include <gmlib/sm2/internal/sm2p256v1_provider.h>

#include <cassert>

namespace sm2::internal {

using sm2_fp_t = number::mont256_t;
using sm2_fn_t = number::mont256_t;
using sm2_bn_t = number::uint256_t;
using sm2_ec_a = sm2_fp_t[2];
using sm2_ec_j = sm2_fp_t[3];

typedef union sm2_num_t
{
    sm2_bn_t bn;
    sm2_fp_t fp;
    sm2_fn_t fn;
} sm2_num_t;

typedef union sm2_ec_t
{
    sm2_ec_a a;
    sm2_ec_j j;
} sm2_ec_t;

static inline int sm2_bn_cmp(const sm2_bn_t a, const sm2_bn_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_cmp != nullptr);
    return provider->sm2_bn_cmp(provider->context, a, b);
}

static inline void sm2_bn_cpy(sm2_bn_t r, const sm2_bn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_cpy != nullptr);
    provider->sm2_bn_cpy(provider->context, r, a);
}

static inline bool sm2_bn_equal_zero(const sm2_bn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_equal_zero != nullptr);
    return provider->sm2_bn_equal_zero(provider->context, a);
}

static inline int sm2_bn_add_uint32(sm2_bn_t       r,
                                    const sm2_bn_t a,
                                    std::uint32_t  b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_add_uint32 != nullptr);
    return provider->sm2_bn_add_uint32(provider->context, r, a, b);
}

static inline void sm2_bn_mod_n_sub1(sm2_bn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_mod_n_sub1 != nullptr);
    provider->sm2_bn_mod_n_sub1(provider->context, a);
}

static inline void sm2_bn_mod_n_sub2(sm2_bn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_mod_n_sub2 != nullptr);
    provider->sm2_bn_mod_n_sub2(provider->context, a);
}

static inline void sm2_bn_from_bytes(sm2_bn_t           r,
                                     const std::uint8_t in[32]) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_from_bytes != nullptr);
    provider->sm2_bn_from_bytes(provider->context, r, in);
}

static inline void sm2_bn_to_bytes(std::uint8_t   out[32],
                                   const sm2_bn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_bn_to_bytes != nullptr);
    provider->sm2_bn_to_bytes(provider->context, out, a);
}

static inline void sm2_fp_add(sm2_fp_t       r,
                              const sm2_fp_t a,
                              const sm2_fp_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_add != nullptr);
    provider->sm2_fp_add(provider->context, r, a, b);
}

static inline void sm2_fp_dbl(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_dbl != nullptr);
    provider->sm2_fp_dbl(provider->context, r, a);
}

static inline void sm2_fp_tpl(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_tpl != nullptr);
    provider->sm2_fp_tpl(provider->context, r, a);
}

static inline void sm2_fp_sub(sm2_fp_t       r,
                              const sm2_fp_t a,
                              const sm2_fp_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_sub != nullptr);
    provider->sm2_fp_sub(provider->context, r, a, b);
}

static inline void sm2_fp_mul(sm2_fp_t       r,
                              const sm2_fp_t a,
                              const sm2_fp_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_mul != nullptr);
    provider->sm2_fp_mul(provider->context, r, a, b);
}

static inline void sm2_fp_sqr(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_sqr != nullptr);
    provider->sm2_fp_sqr(provider->context, r, a);
}

static inline void sm2_fp_neg(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_neg != nullptr);
    provider->sm2_fp_neg(provider->context, r, a);
}

static inline int sm2_fp_sqrt(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_sqrt != nullptr);
    return provider->sm2_fp_sqrt(provider->context, r, a);
}

static inline void sm2_fp_inv(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_inv != nullptr);
    provider->sm2_fp_inv(provider->context, r, a);
}

static inline bool sm2_fp_equal(const sm2_fp_t a, const sm2_fp_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_equal != nullptr);
    return provider->sm2_fp_equal(provider->context, a, b);
}

static inline bool sm2_fp_equal_zero(const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_equal_zero != nullptr);
    return provider->sm2_fp_equal_zero(provider->context, a);
}

static inline bool sm2_fp_equal_one(const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_equal_one != nullptr);
    return provider->sm2_fp_equal_one(provider->context, a);
}

static inline void sm2_fp_cpy(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_cpy != nullptr);
    provider->sm2_fp_cpy(provider->context, r, a);
}

static inline void sm2_fp_set_zero(sm2_fp_t r) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_set_zero != nullptr);
    provider->sm2_fp_set_zero(provider->context, r);
}

static inline void sm2_fp_set_one(sm2_fp_t r) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_set_one != nullptr);
    provider->sm2_fp_set_one(provider->context, r);
}

static inline void sm2_fp_from_bytes(sm2_fp_t           r,
                                     const std::uint8_t in[32]) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_from_bytes != nullptr);
    provider->sm2_fp_from_bytes(provider->context, r, in);
}

static inline void sm2_fp_to_bytes(std::uint8_t   out[32],
                                   const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_to_bytes != nullptr);
    provider->sm2_fp_to_bytes(provider->context, out, a);
}

static inline void sm2_fn_add(sm2_fn_t       r,
                              const sm2_fn_t a,
                              const sm2_fn_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_add != nullptr);
    provider->sm2_fn_add(provider->context, r, a, b);
}

static inline void sm2_fn_sub(sm2_fn_t       r,
                              const sm2_fn_t a,
                              const sm2_fn_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_sub != nullptr);
    provider->sm2_fn_sub(provider->context, r, a, b);
}

static inline void sm2_fn_mul(sm2_fn_t       r,
                              const sm2_fn_t a,
                              const sm2_fn_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_mul != nullptr);
    provider->sm2_fn_mul(provider->context, r, a, b);
}

static inline void sm2_fn_sqr(sm2_fn_t r, const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_sqr != nullptr);
    provider->sm2_fn_sqr(provider->context, r, a);
}

static inline void sm2_fn_inv(sm2_fn_t r, const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_inv != nullptr);
    provider->sm2_fn_inv(provider->context, r, a);
}

static inline bool sm2_fn_equal(const sm2_fn_t a, const sm2_fn_t b) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_equal != nullptr);
    return provider->sm2_fn_equal(provider->context, a, b);
}

static inline bool sm2_fn_equal_zero(const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_equal_zero != nullptr);
    return provider->sm2_fn_equal_zero(provider->context, a);
}

static inline bool sm2_fn_equal_one(const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_equal_one != nullptr);
    return provider->sm2_fn_equal_one(provider->context, a);
}

static inline void sm2_fn_cpy(sm2_fn_t r, const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_cpy != nullptr);
    provider->sm2_fn_cpy(provider->context, r, a);
}

static inline void sm2_fn_set_zero(sm2_fn_t r) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_set_zero != nullptr);
    provider->sm2_fn_set_zero(provider->context, r);
}

static inline void sm2_fn_set_one(sm2_fn_t r) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_set_one != nullptr);
    provider->sm2_fn_set_one(provider->context, r);
}

static inline void sm2_fn_from_bytes(sm2_fn_t           r,
                                     const std::uint8_t in[32]) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_from_bytes != nullptr);
    provider->sm2_fn_from_bytes(provider->context, r, in);
}

static inline void sm2_fn_from_bytes_ex(sm2_fn_t            r,
                                        const std::uint8_t* in,
                                        std::size_t         inl) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_from_bytes_ex != nullptr);
    provider->sm2_fn_from_bytes_ex(provider->context, r, in, inl);
}

static inline void sm2_fn_to_bytes(std::uint8_t   out[32],
                                   const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_to_bytes != nullptr);
    provider->sm2_fn_to_bytes(provider->context, out, a);
}

static inline void sm2_fp_to_bn(sm2_bn_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_to_bn != nullptr);
    provider->sm2_fp_to_bn(provider->context, r, a);
}

static inline void sm2_fp_from_bn(sm2_fp_t r, const sm2_bn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fp_from_bn != nullptr);
    provider->sm2_fp_from_bn(provider->context, r, a);
}

static inline void sm2_fn_to_bn(sm2_bn_t r, const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_to_bn != nullptr);
    provider->sm2_fn_to_bn(provider->context, r, a);
}

static inline void sm2_fn_from_bn(sm2_fn_t r, const sm2_bn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_from_bn != nullptr);
    provider->sm2_fn_from_bn(provider->context, r, a);
}

static inline void sm2_fn_from_fp(sm2_fn_t r, const sm2_fp_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_from_fp != nullptr);
    provider->sm2_fn_from_fp(provider->context, r, a);
}

static inline void sm2_fn_to_fp(sm2_fp_t r, const sm2_fn_t a) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_fn_to_fp != nullptr);
    provider->sm2_fn_to_fp(provider->context, r, a);
}

static inline void sm2_ec_a_cpy(sm2_ec_a R, const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_cpy != nullptr);
    provider->sm2_ec_a_cpy(provider->context, R, P);
}

static inline bool sm2_ec_a_check(const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_check != nullptr);
    return provider->sm2_ec_a_check(provider->context, P);
}

static inline void sm2_ec_a_neg(sm2_ec_a R, const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_neg != nullptr);
    provider->sm2_ec_a_neg(provider->context, R, P);
}

static inline void sm2_ec_a_to_bytes04(std::uint8_t   out[64],
                                       const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_to_bytes04 != nullptr);
    provider->sm2_ec_a_to_bytes04(provider->context, out, P);
}

static inline void sm2_ec_a_from_bytes04(sm2_ec_a           R,
                                         const std::uint8_t in[64]) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_from_bytes04 != nullptr);
    provider->sm2_ec_a_from_bytes04(provider->context, R, in);
}

static inline void sm2_ec_a_to_bytes_uncompressed(std::uint8_t   out[65],
                                                  const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_to_bytes_uncompressed != nullptr);
    provider->sm2_ec_a_to_bytes_uncompressed(provider->context, out, P);
}

static inline void sm2_ec_a_to_bytes_compressed(std::uint8_t   out[33],
                                                const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_to_bytes_compressed != nullptr);
    provider->sm2_ec_a_to_bytes_compressed(provider->context, out, P);
}

static inline void sm2_ec_a_to_bytes_mix(std::uint8_t   out[65],
                                         const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_to_bytes_mix != nullptr);
    provider->sm2_ec_a_to_bytes_mix(provider->context, out, P);
}

static inline int sm2_ec_a_from_bytes(sm2_ec_a            R,
                                      std::size_t*        read_n,
                                      const std::uint8_t* in,
                                      std::size_t         inl) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_a_from_bytes != nullptr);
    return provider->sm2_ec_a_from_bytes(provider->context, R, read_n, in, inl);
}

static inline void sm2_ec_j_cpy(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_cpy != nullptr);
    provider->sm2_ec_j_cpy(provider->context, R, P);
}

static inline bool sm2_ec_j_is_inf(const sm2_ec_j P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_is_inf != nullptr);
    return provider->sm2_ec_j_is_inf(provider->context, P);
}

static inline void sm2_ec_j_set_inf(sm2_ec_j R) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_set_inf != nullptr);
    provider->sm2_ec_j_set_inf(provider->context, R);
}

static inline void sm2_ec_j_neg(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_neg != nullptr);
    provider->sm2_ec_j_neg(provider->context, R, P);
}

static inline void sm2_ec_j_add(sm2_ec_j       R,
                                const sm2_ec_j P,
                                const sm2_ec_j Q) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_add != nullptr);
    provider->sm2_ec_j_add(provider->context, R, P, Q);
}

static inline void sm2_ec_j_add_a(sm2_ec_j       R,
                                  const sm2_ec_j P,
                                  const sm2_ec_a Q) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_add_a != nullptr);
    provider->sm2_ec_j_add_a(provider->context, R, P, Q);
}

static inline void sm2_ec_j_dbl(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_dbl != nullptr);
    provider->sm2_ec_j_dbl(provider->context, R, P);
}

static inline void sm2_ec_j_mul_a(sm2_ec_j           R,
                                  const std::uint8_t k[32],
                                  const sm2_ec_a     P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_mul_a != nullptr);
    provider->sm2_ec_j_mul_a(provider->context, R, k, P);
}

static inline void sm2_ec_j_mul_g(sm2_ec_j R, const std::uint8_t k[32]) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_mul_g != nullptr);
    provider->sm2_ec_j_mul_g(provider->context, R, k);
}

static inline void sm2_ec_j_from_a(sm2_ec_j R, const sm2_ec_a P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_from_a != nullptr);
    provider->sm2_ec_j_from_a(provider->context, R, P);
}

static inline void sm2_ec_j_to_a(sm2_ec_a R, const sm2_ec_j P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_to_a != nullptr);
    provider->sm2_ec_j_to_a(provider->context, R, P);
}

static inline void sm2_ec_j_normal(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_normal != nullptr);
    provider->sm2_ec_j_normal(provider->context, R, P);
}

static inline bool sm2_ec_j_equal(const sm2_ec_j P, const sm2_ec_j Q) noexcept
{
    const SM2P256V1Provider* provider = get_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->context != nullptr);
    assert(provider->sm2_ec_j_equal != nullptr);
    return provider->sm2_ec_j_equal(provider->context, P, Q);
}

} // namespace sm2::internal

#endif
