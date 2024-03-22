#ifndef SM2_INTERNAL_SM2P256V1_H
#define SM2_INTERNAL_SM2P256V1_H

#include <gmlib/number/mont256.h>
#include <gmlib/number/uint256.h>

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

extern const std::uint8_t SM2_DEFAULT_ID[];
extern const std::size_t  SM2_DEFAULT_ID_LEN;
extern const std::uint8_t SM2_CURVE_P[];  // 32-byte length
extern const std::uint8_t SM2_CURVE_A[];  // 32-byte length
extern const std::uint8_t SM2_CURVE_B[];  // 32-byte length
extern const std::uint8_t SM2_CURVE_N[];  // 32-byte length
extern const std::uint8_t SM2_CURVE_GX[]; // 32-byte length
extern const std::uint8_t SM2_CURVE_GY[]; // 32-byte length

int  sm2_bn_cmp(const sm2_bn_t a, const sm2_bn_t b) noexcept;
void sm2_bn_cpy(sm2_bn_t r, const sm2_bn_t a) noexcept;
bool sm2_bn_equal_zero(const sm2_bn_t a) noexcept;
int  sm2_bn_add_uint32(sm2_bn_t r, const sm2_bn_t a, std::uint32_t b) noexcept;
void sm2_bn_mod_n_sub1(sm2_bn_t a) noexcept;
void sm2_bn_mod_n_sub2(sm2_bn_t a) noexcept;
void sm2_bn_from_bytes(sm2_bn_t r, const std::uint8_t in[32]) noexcept;
void sm2_bn_to_bytes(std::uint8_t out[32], const sm2_bn_t a) noexcept;

void sm2_fp_add(sm2_fp_t r, const sm2_fp_t a, const sm2_fp_t b) noexcept;
void sm2_fp_dbl(sm2_fp_t r, const sm2_fp_t a) noexcept;
void sm2_fp_tpl(sm2_fp_t r, const sm2_fp_t a) noexcept;
void sm2_fp_sub(sm2_fp_t r, const sm2_fp_t a, const sm2_fp_t b) noexcept;
void sm2_fp_mul(sm2_fp_t r, const sm2_fp_t a, const sm2_fp_t b) noexcept;
void sm2_fp_sqr(sm2_fp_t r, const sm2_fp_t a) noexcept;
void sm2_fp_neg(sm2_fp_t r, const sm2_fp_t a) noexcept;
int  sm2_fp_sqrt(sm2_fp_t r, const sm2_fp_t a) noexcept;
void sm2_fp_inv(sm2_fp_t r, const sm2_fp_t a) noexcept;
bool sm2_fp_equal(const sm2_fp_t a, const sm2_fp_t b) noexcept;
bool sm2_fp_equal_zero(const sm2_fp_t a) noexcept;
bool sm2_fp_equal_one(const sm2_fp_t a) noexcept;
void sm2_fp_cpy(sm2_fp_t r, const sm2_fp_t a) noexcept;
void sm2_fp_set_zero(sm2_fp_t r) noexcept;
void sm2_fp_set_one(sm2_fp_t r) noexcept;
void sm2_fp_from_bytes(sm2_fp_t r, const std::uint8_t in[32]) noexcept;
void sm2_fp_to_bytes(std::uint8_t out[32], const sm2_fp_t a) noexcept;

// =============================================================================
// =================================== n =======================================
// = 0xfffffffe_ffffffff_ffffffff_ffffffff_7203df6b_21c6052b_53bbf409_39d54123 =
// =============================================================================

void sm2_fn_add(sm2_fn_t r, const sm2_fn_t a, const sm2_fn_t b) noexcept;
void sm2_fn_sub(sm2_fn_t r, const sm2_fn_t a, const sm2_fn_t b) noexcept;
void sm2_fn_mul(sm2_fn_t r, const sm2_fn_t a, const sm2_fn_t b) noexcept;
void sm2_fn_sqr(sm2_fn_t r, const sm2_fn_t a) noexcept;
void sm2_fn_inv(sm2_fn_t r, const sm2_fn_t a) noexcept;
bool sm2_fn_equal(const sm2_fn_t a, const sm2_fn_t b) noexcept;
bool sm2_fn_equal_zero(const sm2_fn_t a) noexcept;
bool sm2_fn_equal_one(const sm2_fn_t a) noexcept;
void sm2_fn_cpy(sm2_fn_t r, const sm2_fn_t a) noexcept;
void sm2_fn_set_zero(sm2_fn_t r) noexcept;
void sm2_fn_set_one(sm2_fn_t r) noexcept;
void sm2_fn_from_bytes(sm2_fn_t r, const std::uint8_t in[32]) noexcept;
void sm2_fn_from_bytes_ex(sm2_fn_t            r,
                          const std::uint8_t* in,
                          std::size_t         inl) noexcept;
void sm2_fn_to_bytes(std::uint8_t out[32], const sm2_fn_t a) noexcept;

void sm2_fp_to_bn(sm2_bn_t r, const sm2_fp_t a) noexcept;
void sm2_fp_from_bn(sm2_fp_t r, const sm2_bn_t a) noexcept;
void sm2_fn_to_bn(sm2_bn_t r, const sm2_fn_t a) noexcept;
void sm2_fn_from_bn(sm2_fn_t r, const sm2_bn_t a) noexcept;
void sm2_fn_from_fp(sm2_fn_t r, const sm2_fp_t a) noexcept;
void sm2_fn_to_fp(sm2_fp_t r, const sm2_fn_t a) noexcept;

void sm2_ec_a_cpy(sm2_ec_a R, const sm2_ec_a P) noexcept;
bool sm2_ec_a_check(const sm2_ec_a P) noexcept;
void sm2_ec_a_neg(sm2_ec_a R, const sm2_ec_a P) noexcept;
void sm2_ec_a_to_bytes04(std::uint8_t out[64], const sm2_ec_a P) noexcept;
void sm2_ec_a_from_bytes04(sm2_ec_a R, const std::uint8_t in[64]) noexcept;
void sm2_ec_a_to_bytes_uncompressed(std::uint8_t   out[65],
                                    const sm2_ec_a P) noexcept;
void sm2_ec_a_to_bytes_compressed(std::uint8_t   out[33],
                                  const sm2_ec_a P) noexcept;
void sm2_ec_a_to_bytes_mix(std::uint8_t out[65], const sm2_ec_a P) noexcept;
int  sm2_ec_a_from_bytes(sm2_ec_a            R,
                         std::size_t*        read_n,
                         const std::uint8_t* in,
                         std::size_t         inl) noexcept;

void sm2_ec_j_cpy(sm2_ec_j R, const sm2_ec_j P) noexcept;
bool sm2_ec_j_is_inf(const sm2_ec_j P) noexcept;
void sm2_ec_j_set_inf(sm2_ec_j R) noexcept;
void sm2_ec_j_neg(sm2_ec_j R, const sm2_ec_j P) noexcept;
void sm2_ec_j_add(sm2_ec_j R, const sm2_ec_j P, const sm2_ec_j Q) noexcept;
void sm2_ec_j_add_a(sm2_ec_j R, const sm2_ec_j P, const sm2_ec_a Q) noexcept;
void sm2_ec_j_dbl(sm2_ec_j R, const sm2_ec_j P) noexcept;
void sm2_ec_j_mul_a(sm2_ec_j           R,
                    const std::uint8_t k[32],
                    const sm2_ec_a     P) noexcept;
void sm2_ec_j_mul_g(sm2_ec_j R, const std::uint8_t k[32]) noexcept;
void sm2_ec_j_from_a(sm2_ec_j R, const sm2_ec_a P) noexcept;
void sm2_ec_j_to_a(sm2_ec_a R, const sm2_ec_j P) noexcept;
void sm2_ec_j_normal(sm2_ec_j R, const sm2_ec_j P) noexcept;
bool sm2_ec_j_equal(const sm2_ec_j P, const sm2_ec_j Q) noexcept;

} // namespace sm2::internal

#endif