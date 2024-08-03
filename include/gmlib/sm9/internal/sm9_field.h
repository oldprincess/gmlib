#ifndef SM9_INTERNAL_SM9_FIELD_H
#define SM9_INTERNAL_SM9_FIELD_H

#include <gmlib/number/mont256.h>
#include <gmlib/number/uint256.h>

namespace sm9::internal {

extern const std::uint8_t SM9_CURVE_P[];   // 32-byte length
extern const std::uint8_t SM9_CURVE_N[];   // 32-byte length
extern const std::uint8_t SM9_CURVE_GX[];  // 32-byte length
extern const std::uint8_t SM9_CURVE_GY[];  // 32-byte length
extern const std::uint8_t SM9_CURVE2_GX[]; // 64-byte length
extern const std::uint8_t SM9_CURVE2_GY[]; // 64-byte length

using sm9_bn_t   = number::uint256_t;
using sm9_fn_t   = number::mont256_t;
using sm9_fp_t   = number::mont256_t;
using sm9_fp2_t  = sm9_fp_t[2];
using sm9_fp4_t  = sm9_fp2_t[2];
using sm9_fp12_t = sm9_fp4_t[3];

using sm9_ec_a  = sm9_fp_t[2];
using sm9_ec_j  = sm9_fp_t[3];
using sm9_ec2_a = sm9_fp2_t[2];
using sm9_ec2_j = sm9_fp2_t[3];

typedef union sm9_num_t
{
    sm9_bn_t bn;
    sm9_fp_t fp;
    sm9_fn_t fn;
} sm9_num_t;
typedef union sm9_ec_t
{
    sm9_ec_a a;
    sm9_ec_j j;
} sm9_ec_t;
typedef union sm9_ec2_t
{
    sm9_ec2_a a;
    sm9_ec2_j j;
} sm9_ec2_t;

int  sm9_bn_cmp(const sm9_bn_t a, const sm9_bn_t b) noexcept;
void sm9_bn_cpy(sm9_bn_t r, const sm9_bn_t a) noexcept;
bool sm9_bn_equal_zero(const sm9_bn_t a) noexcept;
int  sm9_bn_add_uint32(sm9_bn_t r, const sm9_bn_t a, std::uint32_t b) noexcept;
void sm9_bn_mod_n_sub1(sm9_bn_t a) noexcept;
void sm9_bn_mod_n_sub1_ex(sm9_bn_t            a,
                          const std::uint8_t* data,
                          std::size_t         data_len) noexcept;
void sm9_bn_mod_n_sub2(sm9_bn_t a) noexcept;
void sm9_bn_mod_n_sub3(sm9_bn_t a) noexcept;
void sm9_bn_from_bytes(sm9_bn_t r, const std::uint8_t in[32]) noexcept;
void sm9_bn_to_bytes(std::uint8_t out[32], const sm9_bn_t a) noexcept;

// =============================================================================
// =================================== n =======================================
// === 0xb640000002a3a6f1d603ab4ff58ec74449f2934b18ea8beee56ee19cd69ecf25 =====
// =============================================================================

void sm9_fn_add(sm9_fn_t r, const sm9_fn_t a, const sm9_fn_t b) noexcept;
void sm9_fn_sub(sm9_fn_t r, const sm9_fn_t a, const sm9_fn_t b) noexcept;
void sm9_fn_mul(sm9_fn_t r, const sm9_fn_t a, const sm9_fn_t b) noexcept;
void sm9_fn_sqr(sm9_fn_t r, const sm9_fn_t a) noexcept;
void sm9_fn_inv(sm9_fn_t r, const sm9_fn_t a) noexcept;
bool sm9_fn_equal(const sm9_fn_t a, const sm9_fn_t b) noexcept;
bool sm9_fn_equal_zero(const sm9_fn_t a) noexcept;
bool sm9_fn_equal_one(const sm9_fn_t a) noexcept;
void sm9_fn_cpy(sm9_fn_t r, const sm9_fn_t a) noexcept;
void sm9_fn_set_zero(sm9_fn_t r) noexcept;
void sm9_fn_set_one(sm9_fn_t r) noexcept;
void sm9_fn_from_bytes(sm9_fn_t r, const std::uint8_t in[32]) noexcept;
void sm9_fn_from_bytes_ex(sm9_fn_t            r,
                          const std::uint8_t* in,
                          std::size_t         inl) noexcept;
void sm9_fn_to_bytes(std::uint8_t out[32], const sm9_fn_t a) noexcept;

// ======================================================================
// ============================== p =====================================
// = 0xb640000002a3a6f1d603ab4ff58ec74521f2934b1a7aeedbe56f9b27e351457d =
// ======================================================================

void sm9_fp_to_bytes(std::uint8_t dst[32], const sm9_fp_t a) noexcept;
void sm9_fp_from_bytes(sm9_fp_t r, const std::uint8_t src[32]) noexcept;
void sm9_fp_cpy(sm9_fp_t r, const sm9_fp_t a) noexcept;
bool sm9_fp_equal(const sm9_fp_t a, const sm9_fp_t b) noexcept;
bool sm9_fp_equal_zero(const sm9_fp_t a) noexcept;
bool sm9_fp_equal_one(const sm9_fp_t a) noexcept;
void sm9_fp_set_zero(sm9_fp_t r) noexcept;
void sm9_fp_set_one(sm9_fp_t r) noexcept;
void sm9_fp_add(sm9_fp_t r, const sm9_fp_t a, const sm9_fp_t b) noexcept;
void sm9_fp_dbl(sm9_fp_t r, const sm9_fp_t a) noexcept;
void sm9_fp_tpl(sm9_fp_t r, const sm9_fp_t a) noexcept;
void sm9_fp_neg(sm9_fp_t r, const sm9_fp_t a) noexcept;
void sm9_fp_sub(sm9_fp_t r, const sm9_fp_t a, const sm9_fp_t b) noexcept;
void sm9_fp_mul(sm9_fp_t r, const sm9_fp_t a, const sm9_fp_t b) noexcept;
void sm9_fp_sqr(sm9_fp_t r, const sm9_fp_t a) noexcept;
int  sm9_fp_sqrt(sm9_fp_t r, const sm9_fp_t a) noexcept;
void sm9_fp_inv(sm9_fp_t r, const sm9_fp_t a) noexcept;

void sm9_fp_to_bn(sm9_bn_t r, const sm9_fp_t a) noexcept;
void sm9_fp_from_bn(sm9_fp_t r, const sm9_bn_t a) noexcept;
void sm9_fn_to_bn(sm9_bn_t r, const sm9_fn_t a) noexcept;
void sm9_fn_from_bn(sm9_fn_t r, const sm9_bn_t a) noexcept;
void sm9_fn_from_fp(sm9_fn_t r, const sm9_fp_t a) noexcept;
void sm9_fn_to_fp(sm9_fp_t r, const sm9_fn_t a) noexcept;

void sm9_fp2_to_bytes(std::uint8_t dst[64], const sm9_fp2_t a) noexcept;
void sm9_fp2_from_bytes(sm9_fp2_t r, const std::uint8_t src[64]) noexcept;
void sm9_fp2_cpy(sm9_fp2_t r, const sm9_fp2_t a) noexcept;
bool sm9_fp2_equal(const sm9_fp2_t a, const sm9_fp2_t b) noexcept;
bool sm9_fp2_equal_zero(const sm9_fp2_t a) noexcept;
bool sm9_fp2_equal_one(const sm9_fp2_t a) noexcept;
void sm9_fp2_set_zero(sm9_fp2_t r) noexcept;
void sm9_fp2_set_one(sm9_fp2_t r) noexcept;
void sm9_fp2_add(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp2_t b) noexcept;
void sm9_fp2_dbl(sm9_fp2_t r, const sm9_fp2_t a) noexcept;
void sm9_fp2_tpl(sm9_fp2_t r, const sm9_fp2_t a) noexcept;
void sm9_fp2_neg(sm9_fp2_t r, const sm9_fp2_t a) noexcept;
void sm9_fp2_sub(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp2_t b) noexcept;
void sm9_fp2_mul(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp2_t b) noexcept;
void sm9_fp2_mul_u(sm9_fp2_t r, const sm9_fp2_t a) noexcept;
void sm9_fp2_mul_fp(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp_t b) noexcept;
void sm9_fp2_sqr(sm9_fp2_t r, const sm9_fp2_t a) noexcept;
void sm9_fp2_inv(sm9_fp2_t r, const sm9_fp2_t a) noexcept;

void sm9_fp4_to_bytes(std::uint8_t dst[128], const sm9_fp4_t a) noexcept;
void sm9_fp4_from_bytes(sm9_fp4_t r, const std::uint8_t src[128]) noexcept;
void sm9_fp4_cpy(sm9_fp4_t r, const sm9_fp4_t a) noexcept;
bool sm9_fp4_equal(const sm9_fp4_t a, const sm9_fp4_t b) noexcept;
bool sm9_fp4_equal_zero(const sm9_fp4_t a) noexcept;
bool sm9_fp4_equal_one(const sm9_fp4_t a) noexcept;
void sm9_fp4_set_zero(sm9_fp4_t r) noexcept;
void sm9_fp4_set_one(sm9_fp4_t r) noexcept;
void sm9_fp4_add(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp4_t b) noexcept;
void sm9_fp4_neg(sm9_fp4_t r, const sm9_fp4_t a) noexcept;
void sm9_fp4_sub(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp4_t b) noexcept;
void sm9_fp4_mul(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp4_t b) noexcept;
void sm9_fp4_mul_v(sm9_fp4_t r, const sm9_fp4_t a) noexcept;
void sm9_fp4_mul_fp(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp_t b) noexcept;
void sm9_fp4_mul_fp2(sm9_fp4_t       r,
                     const sm9_fp4_t a,
                     const sm9_fp2_t b) noexcept;
void sm9_fp4_sqr(sm9_fp4_t r, const sm9_fp4_t a) noexcept;
void sm9_fp4_inv(sm9_fp4_t r, const sm9_fp4_t a) noexcept;

void sm9_fp12_to_bytes(std::uint8_t dst[384], const sm9_fp12_t a) noexcept;
void sm9_fp12_from_bytes(sm9_fp12_t r, const std::uint8_t src[384]) noexcept;
void sm9_fp12_cpy(sm9_fp12_t r, const sm9_fp12_t a) noexcept;
bool sm9_fp12_equal(const sm9_fp12_t a, const sm9_fp12_t b) noexcept;
bool sm9_fp12_equal_zero(const sm9_fp12_t a) noexcept;
bool sm9_fp12_equal_one(const sm9_fp12_t a) noexcept;
void sm9_fp12_set_zero(sm9_fp12_t r) noexcept;
void sm9_fp12_set_one(sm9_fp12_t r) noexcept;
void sm9_fp12_add(sm9_fp12_t       r,
                  const sm9_fp12_t a,
                  const sm9_fp12_t b) noexcept;
void sm9_fp12_neg(sm9_fp12_t r, const sm9_fp12_t a) noexcept;
void sm9_fp12_sub(sm9_fp12_t       r,
                  const sm9_fp12_t a,
                  const sm9_fp12_t b) noexcept;
void sm9_fp12_mul(sm9_fp12_t       r,
                  const sm9_fp12_t a,
                  const sm9_fp12_t b) noexcept;
void sm9_fp12_mul_fp4(sm9_fp12_t       r,
                      const sm9_fp12_t a,
                      const sm9_fp4_t  b) noexcept;
void sm9_fp12_sqr(sm9_fp12_t r, const sm9_fp12_t a) noexcept;
void sm9_fp12_inv(sm9_fp12_t r, const sm9_fp12_t a) noexcept;
void sm9_fp12_pow(sm9_fp12_t         r,
                  const sm9_fp12_t   a,
                  const std::uint8_t e_u8[32]) noexcept;

// ======================================

void sm9_ec_a_cpy(sm9_ec_a R, const sm9_ec_a P) noexcept;
bool sm9_ec_a_check(const sm9_ec_a P) noexcept;
void sm9_ec_a_neg(sm9_ec_a R, const sm9_ec_a P) noexcept;
void sm9_ec_a_to_bytes04(std::uint8_t out[64], const sm9_ec_a P) noexcept;
void sm9_ec_a_from_bytes04(sm9_ec_a R, const std::uint8_t in[64]) noexcept;
void sm9_ec_a_to_bytes_uncompressed(std::uint8_t   out[65],
                                    const sm9_ec_a P) noexcept;
void sm9_ec_a_to_bytes_compressed(std::uint8_t   out[33],
                                  const sm9_ec_a P) noexcept;
void sm9_ec_a_to_bytes_mix(std::uint8_t out[65], const sm9_ec_a P) noexcept;
int  sm9_ec_a_from_bytes(sm9_ec_a            R,
                         std::size_t*        read_n,
                         const std::uint8_t* in,
                         std::size_t         inl) noexcept;
void sm9_ec_j_cpy(sm9_ec_j R, const sm9_ec_j P) noexcept;
bool sm9_ec_j_is_inf(const sm9_ec_j P) noexcept;
void sm9_ec_j_set_inf(sm9_ec_j R) noexcept;
void sm9_ec_j_neg(sm9_ec_j R, const sm9_ec_j P) noexcept;
void sm9_ec_j_add(sm9_ec_j R, const sm9_ec_j P, const sm9_ec_j Q) noexcept;
void sm9_ec_j_add_a(sm9_ec_j R, const sm9_ec_j P, const sm9_ec_a Q) noexcept;
void sm9_ec_j_dbl(sm9_ec_j R, const sm9_ec_j P) noexcept;
void sm9_ec_j_mul_a(sm9_ec_j           R,
                    const std::uint8_t k[32],
                    const sm9_ec_a     P) noexcept;
void sm9_ec_j_mul_g(sm9_ec_j R, const std::uint8_t k[32]) noexcept;
void sm9_ec_j_mul_j(sm9_ec_j           R,
                    const std::uint8_t k[32],
                    const sm9_ec_j     P) noexcept;
void sm9_ec_j_from_a(sm9_ec_j R, const sm9_ec_a P) noexcept;
void sm9_ec_j_to_a(sm9_ec_a R, const sm9_ec_j P) noexcept;
void sm9_ec_j_normal(sm9_ec_j R, const sm9_ec_j P) noexcept;
bool sm9_ec_j_equal(const sm9_ec_j P, const sm9_ec_j Q) noexcept;

void sm9_ec2_a_cpy(sm9_ec2_a R, const sm9_ec2_a P) noexcept;
bool sm9_ec2_a_check(const sm9_ec2_a P) noexcept;
void sm9_ec2_a_neg(sm9_ec2_a R, const sm9_ec2_a P) noexcept;
void sm9_ec2_a_to_bytes04(std::uint8_t out[128], const sm9_ec2_a P) noexcept;
void sm9_ec2_a_from_bytes04(sm9_ec2_a R, const std::uint8_t in[128]) noexcept;
void sm9_ec2_a_to_bytes_uncompressed(std::uint8_t    out[129],
                                     const sm9_ec2_a P) noexcept;
void sm9_ec2_a_to_bytes_compressed(std::uint8_t    out[65],
                                   const sm9_ec2_a P) noexcept;
void sm9_ec2_a_to_bytes_mix(std::uint8_t out[129], const sm9_ec2_a P) noexcept;
int  sm9_ec2_a_from_bytes(sm9_ec2_a           R,
                          std::size_t*        read_n,
                          const std::uint8_t* in,
                          std::size_t         inl) noexcept;
void sm9_ec2_j_cpy(sm9_ec2_j R, const sm9_ec2_j P) noexcept;
bool sm9_ec2_j_is_inf(const sm9_ec2_j P) noexcept;
void sm9_ec2_j_set_inf(sm9_ec2_j R) noexcept;
void sm9_ec2_j_neg(sm9_ec2_j R, const sm9_ec2_j P) noexcept;
void sm9_ec2_j_add(sm9_ec2_j R, const sm9_ec2_j P, const sm9_ec2_j Q) noexcept;
void sm9_ec2_j_add_a(sm9_ec2_j       R,
                     const sm9_ec2_j P,
                     const sm9_ec2_a Q) noexcept;
void sm9_ec2_j_dbl(sm9_ec2_j R, const sm9_ec2_j P) noexcept;
void sm9_ec2_j_mul_a(sm9_ec2_j          R,
                     const std::uint8_t k[32],
                     const sm9_ec2_a    P) noexcept;
void sm9_ec2_j_mul_g(sm9_ec2_j R, const std::uint8_t k[32]) noexcept;
void sm9_ec2_j_mul_j(sm9_ec2_j          R,
                     const std::uint8_t k[32],
                     const sm9_ec2_j    P) noexcept;
void sm9_ec2_j_from_a(sm9_ec2_j R, const sm9_ec2_a P) noexcept;
void sm9_ec2_j_to_a(sm9_ec2_a R, const sm9_ec2_j P) noexcept;
void sm9_ec2_j_normal(sm9_ec2_j R, const sm9_ec2_j P) noexcept;
bool sm9_ec2_j_equal(const sm9_ec2_j P, const sm9_ec2_j Q) noexcept;

// ===============================

void sm9_pairing(sm9_fp12_t r, const sm9_ec_a P, const sm9_ec2_a Q) noexcept;

void sm9_pairing_P1_Q(sm9_fp12_t r, const sm9_ec2_a Q) noexcept;

void sm9_pairing_P_P2(sm9_fp12_t r, const sm9_ec_a P) noexcept;

} // namespace sm9::internal

#endif