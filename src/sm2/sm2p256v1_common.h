#ifndef SM2_SM2P256V1_COMMON_H
#define SM2_SM2P256V1_COMMON_H

#include <gmlib/number/mont256.h>
#include <gmlib/number/provider.h>

#include <cstddef>
#include <cstdint>

namespace sm2::internal::common {

struct CommonContext
{
    const number::NumberProvider* number_provider;
    std::uint8_t p[32], p_sub2[32], fp_r[32], fp_r_pow2[32], fp_mont_n[32];
    std::uint8_t n[32], n_sub2[32], fn_r[32], fn_r_pow2[32], fn_mont_n[32];
    std::uint8_t p_sub3_div4_add1[32];
    std::uint8_t n_sub1[32];
    number::Mont256CTX fp_mont_ctx;
    number::Mont256CTX fn_mont_ctx;

    CommonContext() noexcept;
};

// BN
int  sm2_bn_cmp(const CommonContext* ctx,
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept;
void sm2_bn_cpy(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
bool sm2_bn_equal_zero(const CommonContext* ctx,
                       const std::uint8_t   a[32]) noexcept;
int  sm2_bn_add_uint32(const CommonContext* ctx,
                       std::uint8_t         r[32],
                       const std::uint8_t   a[32],
                       std::uint32_t        b) noexcept;
void sm2_bn_mod_n_sub1(const CommonContext* ctx, std::uint8_t a[32]) noexcept;
void sm2_bn_mod_n_sub2(const CommonContext* ctx, std::uint8_t a[32]) noexcept;
void sm2_bn_from_bytes(const CommonContext* ctx,
                       std::uint8_t         r[32],
                       const std::uint8_t   in[32]) noexcept;
void sm2_bn_to_bytes(const CommonContext* ctx,
                     std::uint8_t         out[32],
                     const std::uint8_t   a[32]) noexcept;

// FP
void sm2_fp_add(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept;
void sm2_fp_dbl(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
void sm2_fp_tpl(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
void sm2_fp_sub(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept;
void sm2_fp_mul(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept;
void sm2_fp_sqr(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
int  sm2_fp_sqrt(const CommonContext* ctx,
                 std::uint8_t         r[32],
                 const std::uint8_t   a[32]) noexcept;
void sm2_fp_neg(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
void sm2_fp_inv(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
bool sm2_fp_equal(const CommonContext* ctx,
                  const std::uint8_t   a[32],
                  const std::uint8_t   b[32]) noexcept;
bool sm2_fp_equal_zero(const CommonContext* ctx,
                       const std::uint8_t   a[32]) noexcept;
bool sm2_fp_equal_one(const CommonContext* ctx,
                      const std::uint8_t   a[32]) noexcept;
void sm2_fp_cpy(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
void sm2_fp_set_zero(const CommonContext* ctx, std::uint8_t r[32]) noexcept;
void sm2_fp_set_one(const CommonContext* ctx, std::uint8_t r[32]) noexcept;
void sm2_fp_from_bytes(const CommonContext* ctx,
                       std::uint8_t         r[32],
                       const std::uint8_t   in[32]) noexcept;
void sm2_fp_to_bytes(const CommonContext* ctx,
                     std::uint8_t         out[32],
                     const std::uint8_t   a[32]) noexcept;

// FN
void sm2_fn_add(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept;
void sm2_fn_sub(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept;
void sm2_fn_mul(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept;
void sm2_fn_sqr(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
void sm2_fn_inv(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
bool sm2_fn_equal(const CommonContext* ctx,
                  const std::uint8_t   a[32],
                  const std::uint8_t   b[32]) noexcept;
bool sm2_fn_equal_zero(const CommonContext* ctx,
                       const std::uint8_t   a[32]) noexcept;
bool sm2_fn_equal_one(const CommonContext* ctx,
                      const std::uint8_t   a[32]) noexcept;
void sm2_fn_cpy(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept;
void sm2_fn_set_zero(const CommonContext* ctx, std::uint8_t r[32]) noexcept;
void sm2_fn_set_one(const CommonContext* ctx, std::uint8_t r[32]) noexcept;
void sm2_fn_from_bytes(const CommonContext* ctx,
                       std::uint8_t         r[32],
                       const std::uint8_t   in[32]) noexcept;
void sm2_fn_from_bytes_ex(const CommonContext* ctx,
                          std::uint8_t         r[32],
                          const std::uint8_t*  in,
                          std::size_t          inl) noexcept;
void sm2_fn_to_bytes(const CommonContext* ctx,
                     std::uint8_t         out[32],
                     const std::uint8_t   a[32]) noexcept;

// Conversions
void sm2_fp_to_bn(const CommonContext* ctx,
                  std::uint8_t         r[32],
                  const std::uint8_t   a[32]) noexcept;
void sm2_fp_from_bn(const CommonContext* ctx,
                    std::uint8_t         r[32],
                    const std::uint8_t   a[32]) noexcept;
void sm2_fn_to_bn(const CommonContext* ctx,
                  std::uint8_t         r[32],
                  const std::uint8_t   a[32]) noexcept;
void sm2_fn_from_bn(const CommonContext* ctx,
                    std::uint8_t         r[32],
                    const std::uint8_t   a[32]) noexcept;
void sm2_fn_from_fp(const CommonContext* ctx,
                    std::uint8_t         r[32],
                    const std::uint8_t   a[32]) noexcept;
void sm2_fn_to_fp(const CommonContext* ctx,
                  std::uint8_t         r[32],
                  const std::uint8_t   a[32]) noexcept;

// EC affine
void sm2_ec_a_cpy(const CommonContext* ctx,
                  std::uint8_t         R[2][32],
                  const std::uint8_t   P[2][32]) noexcept;
bool sm2_ec_a_check(const CommonContext* ctx,
                    const std::uint8_t   P[2][32]) noexcept;
void sm2_ec_a_neg(const CommonContext* ctx,
                  std::uint8_t         R[2][32],
                  const std::uint8_t   P[2][32]) noexcept;
void sm2_ec_a_to_bytes04(const CommonContext* ctx,
                         std::uint8_t         out[64],
                         const std::uint8_t   P[2][32]) noexcept;
void sm2_ec_a_from_bytes04(const CommonContext* ctx,
                           std::uint8_t         R[2][32],
                           const std::uint8_t   in[64]) noexcept;
void sm2_ec_a_to_bytes_uncompressed(const CommonContext* ctx,
                                    std::uint8_t         out[65],
                                    const std::uint8_t   P[2][32]) noexcept;
void sm2_ec_a_to_bytes_compressed(const CommonContext* ctx,
                                  std::uint8_t         out[33],
                                  const std::uint8_t   P[2][32]) noexcept;
void sm2_ec_a_to_bytes_mix(const CommonContext* ctx,
                           std::uint8_t         out[65],
                           const std::uint8_t   P[2][32]) noexcept;
int  sm2_ec_a_from_bytes(const CommonContext* ctx,
                         std::uint8_t         R[2][32],
                         std::size_t*         read_n,
                         const std::uint8_t*  in,
                         std::size_t          inl) noexcept;

// EC jacobian
void sm2_ec_j_cpy(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32]) noexcept;
bool sm2_ec_j_is_inf(const CommonContext* ctx,
                     const std::uint8_t   P[3][32]) noexcept;
void sm2_ec_j_set_inf(const CommonContext* ctx, std::uint8_t R[3][32]) noexcept;
void sm2_ec_j_neg(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32]) noexcept;
void sm2_ec_j_add(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32],
                  const std::uint8_t   Q[3][32]) noexcept;
void sm2_ec_j_add_a(const CommonContext* ctx,
                    std::uint8_t         R[3][32],
                    const std::uint8_t   P[3][32],
                    const std::uint8_t   Q[2][32]) noexcept;
void sm2_ec_j_dbl(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32]) noexcept;
void sm2_ec_j_mul_a(const CommonContext* ctx,
                    std::uint8_t         R[3][32],
                    const std::uint8_t   k[32],
                    const std::uint8_t   P[2][32]) noexcept;
void sm2_ec_j_mul_g(const CommonContext* ctx,
                    std::uint8_t         R[3][32],
                    const std::uint8_t   k[32]) noexcept;
void sm2_ec_j_from_a(const CommonContext* ctx,
                     std::uint8_t         R[3][32],
                     const std::uint8_t   P[2][32]) noexcept;
void sm2_ec_j_to_a(const CommonContext* ctx,
                   std::uint8_t         R[2][32],
                   const std::uint8_t   P[3][32]) noexcept;
void sm2_ec_j_normal(const CommonContext* ctx,
                     std::uint8_t         R[3][32],
                     const std::uint8_t   P[3][32]) noexcept;
bool sm2_ec_j_equal(const CommonContext* ctx,
                    const std::uint8_t   P[3][32],
                    const std::uint8_t   Q[3][32]) noexcept;

// Internal helpers
int sm2_ec_recover_y(const CommonContext* ctx,
                     std::uint8_t         y[32],
                     const std::uint8_t   x[32],
                     int                  y_hat) noexcept;

} // namespace sm2::internal::common

#endif
