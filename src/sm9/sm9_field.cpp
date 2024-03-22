#include <gmlib/number/mpz.h>
#include <gmlib/sm9/internal/sm9_field.h>

namespace sm9::internal {
// y^2 = x^3 + 5
// 0xb640000002a3a6f1d603ab4ff58ec74521f2934b1a7aeedbe56f9b27e351457d
const std::uint8_t SM9_CURVE_P[32] = {
    0xb6, 0x40, 0x00, 0x00, 0x02, 0xa3, 0xa6, 0xf1, 0xd6, 0x03, 0xab,
    0x4f, 0xf5, 0x8e, 0xc7, 0x45, 0x21, 0xf2, 0x93, 0x4b, 0x1a, 0x7a,
    0xee, 0xdb, 0xe5, 0x6f, 0x9b, 0x27, 0xe3, 0x51, 0x45, 0x7d,
};
// A=0
static const std::uint8_t SM9_CURVE_A[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// B=5
static const std::uint8_t SM9_CURVE_B[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
};
// 0xb640000002a3a6f1d603ab4ff58ec74449f2934b18ea8beee56ee19cd69ecf25
const std::uint8_t SM9_CURVE_N[32] = {
    0xb6, 0x40, 0x00, 0x00, 0x02, 0xa3, 0xa6, 0xf1, 0xd6, 0x03, 0xab,
    0x4f, 0xf5, 0x8e, 0xc7, 0x44, 0x49, 0xf2, 0x93, 0x4b, 0x18, 0xea,
    0x8b, 0xee, 0xe5, 0x6e, 0xe1, 0x9c, 0xd6, 0x9e, 0xcf, 0x25,
};
// G.X 0x93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD
const std::uint8_t SM9_CURVE_GX[32] = {
    0x93, 0xde, 0x05, 0x1d, 0x62, 0xbf, 0x71, 0x8f, 0xf5, 0xed, 0x07,
    0x04, 0x48, 0x7d, 0x01, 0xd6, 0xe1, 0xe4, 0x08, 0x69, 0x09, 0xdc,
    0x32, 0x80, 0xe8, 0xc4, 0xe4, 0x81, 0x7c, 0x66, 0xdd, 0xdd,
};
// G.Y 0x21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616
const std::uint8_t SM9_CURVE_GY[32] = {
    0x21, 0xfe, 0x8d, 0xda, 0x4f, 0x21, 0xe6, 0x07, 0x63, 0x10, 0x65,
    0x12, 0x5c, 0x39, 0x5b, 0xbc, 0x1c, 0x1c, 0x00, 0xcb, 0xfa, 0x60,
    0x24, 0x35, 0x0c, 0x46, 0x4c, 0xd7, 0x0a, 0x3e, 0xa6, 0x16,
};

// G.x =    85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141 u +
//          3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B
const std::uint8_t SM9_CURVE2_GX[64] = {
    0x85, 0xae, 0xf3, 0xd0, 0x78, 0x64, 0x0c, 0x98, 0x59, 0x7b, 0x60,
    0x27, 0xb4, 0x41, 0xa0, 0x1f, 0xf1, 0xdd, 0x2c, 0x19, 0x0f, 0x5e,
    0x93, 0xc4, 0x54, 0x80, 0x6c, 0x11, 0xd8, 0x80, 0x61, 0x41, // u
    0x37, 0x22, 0x75, 0x52, 0x92, 0x13, 0x0b, 0x08, 0xd2, 0xaa, 0xb9,
    0x7f, 0xd3, 0x4e, 0xc1, 0x20, 0xee, 0x26, 0x59, 0x48, 0xd1, 0x9c,
    0x17, 0xab, 0xf9, 0xb7, 0x21, 0x3b, 0xaf, 0x82, 0xd6, 0x5b,
};

// G.y =    17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96 u +
//          A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7
const std::uint8_t SM9_CURVE2_GY[64] = {
    0x17, 0x50, 0x9b, 0x09, 0x2e, 0x84, 0x5c, 0x12, 0x66, 0xba, 0x0d,
    0x26, 0x2c, 0xbe, 0xe6, 0xed, 0x07, 0x36, 0xa9, 0x6f, 0xa3, 0x47,
    0xc8, 0xbd, 0x85, 0x6d, 0xc7, 0x6b, 0x84, 0xeb, 0xeb, 0x96, // u
    0xa7, 0xcf, 0x28, 0xd5, 0x19, 0xbe, 0x3d, 0xa6, 0x5f, 0x31, 0x70,
    0x15, 0x3d, 0x27, 0x8f, 0xf2, 0x47, 0xef, 0xba, 0x98, 0xa7, 0x1a,
    0x08, 0x11, 0x62, 0x15, 0xbb, 0xa5, 0xc9, 0x99, 0xa7, 0xc7,
};

#define P_DATA                                                              \
    0xb6, 0x40, 0x00, 0x00, 0x02, 0xa3, 0xa6, 0xf1, 0xd6, 0x03, 0xab, 0x4f, \
        0xf5, 0x8e, 0xc7, 0x45, 0x21, 0xf2, 0x93, 0x4b, 0x1a, 0x7a, 0xee,   \
        0xdb, 0xe5, 0x6f, 0x9b, 0x27, 0xe3, 0x51, 0x45, 0x7d

#define P_SUB2_DATA                                                         \
    0xb6, 0x40, 0x00, 0x00, 0x02, 0xa3, 0xa6, 0xf1, 0xd6, 0x03, 0xab, 0x4f, \
        0xf5, 0x8e, 0xc7, 0x45, 0x21, 0xf2, 0x93, 0x4b, 0x1a, 0x7a, 0xee,   \
        0xdb, 0xe5, 0x6f, 0x9b, 0x27, 0xe3, 0x51, 0x45, 0x7b

#define FP_R_DATA                                                           \
    0x49, 0xbf, 0xff, 0xff, 0xfd, 0x5c, 0x59, 0x0e, 0x29, 0xfc, 0x54, 0xb0, \
        0x0a, 0x71, 0x38, 0xba, 0xde, 0x0d, 0x6c, 0xb4, 0xe5, 0x85, 0x11,   \
        0x24, 0x1a, 0x90, 0x64, 0xd8, 0x1c, 0xae, 0xba, 0x83

#define FP_R_POW2_DATA                                                      \
    0x2e, 0xa7, 0x95, 0xa6, 0x56, 0xf6, 0x2f, 0xbd, 0xe4, 0x79, 0xb5, 0x22, \
        0xd6, 0x70, 0x6e, 0x7b, 0x88, 0xf8, 0x10, 0x5f, 0xae, 0x1a, 0x5d,   \
        0x3f, 0x27, 0xde, 0xa3, 0x12, 0xb4, 0x17, 0xe2, 0xd2

static const auto       P         = number::mpz_set_epi8(P_DATA);
static const auto       P_SUB2    = number::mpz_set_epi8(P_SUB2_DATA);
static const auto       FP_R      = number::mpz_set_epi8(FP_R_DATA);
static const auto       FP_R_POW2 = number::mpz_set_epi8(FP_R_POW2_DATA);
constexpr std::uint64_t FP_N_     = 0x892bc42c2f2ee42bULL;

#define N_DATA                                                              \
    0xb6, 0x40, 0x00, 0x00, 0x02, 0xa3, 0xa6, 0xf1, 0xd6, 0x03, 0xab, 0x4f, \
        0xf5, 0x8e, 0xc7, 0x44, 0x49, 0xf2, 0x93, 0x4b, 0x18, 0xea, 0x8b,   \
        0xee, 0xe5, 0x6e, 0xe1, 0x9c, 0xd6, 0x9e, 0xcf, 0x25

#define N_SUB2_DATA                                                         \
    0xb6, 0x40, 0x00, 0x00, 0x02, 0xa3, 0xa6, 0xf1, 0xd6, 0x03, 0xab, 0x4f, \
        0xf5, 0x8e, 0xc7, 0x44, 0x49, 0xf2, 0x93, 0x4b, 0x18, 0xea, 0x8b,   \
        0xee, 0xe5, 0x6e, 0xe1, 0x9c, 0xd6, 0x9e, 0xcf, 0x23

#define N_SUB3_DATA                                                         \
    0xb6, 0x40, 0x00, 0x00, 0x02, 0xa3, 0xa6, 0xf1, 0xd6, 0x03, 0xab, 0x4f, \
        0xf5, 0x8e, 0xc7, 0x44, 0x49, 0xf2, 0x93, 0x4b, 0x18, 0xea, 0x8b,   \
        0xee, 0xe5, 0x6e, 0xe1, 0x9c, 0xd6, 0x9e, 0xcf, 0x22

#define FN_R_DATA                                                           \
    0x49, 0xbf, 0xff, 0xff, 0xfd, 0x5c, 0x59, 0x0e, 0x29, 0xfc, 0x54, 0xb0, \
        0x0a, 0x71, 0x38, 0xbb, 0xb6, 0x0d, 0x6c, 0xb4, 0xe7, 0x15, 0x74,   \
        0x11, 0x1a, 0x91, 0x1e, 0x63, 0x29, 0x61, 0x30, 0xdb

#define FN_R_POW2_DATA                                                      \
    0x88, 0x94, 0xf5, 0xd1, 0x63, 0x69, 0x5d, 0x0e, 0xbf, 0xee, 0x4b, 0xae, \
        0x7d, 0x78, 0xa1, 0xf9, 0xe4, 0xa0, 0x81, 0x10, 0xbb, 0x6d, 0xae,   \
        0xab, 0x75, 0x98, 0xcd, 0x79, 0xcd, 0x75, 0x0c, 0x35

static const auto       N         = number::mpz_set_epi8(N_DATA);
static const auto       N_SUB2    = number::mpz_set_epi8(N_SUB2_DATA);
static const auto       N_SUB3    = number::mpz_set_epi8(N_SUB3_DATA);
static const auto       FN_R      = number::mpz_set_epi8(FN_R_DATA);
static const auto       FN_R_POW2 = number::mpz_set_epi8(FN_R_POW2_DATA);
constexpr std::uint64_t FN_N_     = 0x1d02662351974b53ULL;

static const number::Mont256CTX FP_MONT_CTX = {
    P.v, P_SUB2.v, FP_R.v, FP_R_POW2.v, number::mont_compute_N_(P.v[0]),
};

static const number::Mont256CTX FN_MONT_CTX = {
    N.v, N_SUB2.v, FN_R.v, FN_R_POW2.v, number::mont_compute_N_(N.v[0]),
};

#pragma region "SM9 BN"

int sm9_bn_cmp(const sm9_bn_t a, const sm9_bn_t b) noexcept
{
    return number::uint256_cmp(a, b);
}

void sm9_bn_cpy(sm9_bn_t r, const sm9_bn_t a) noexcept
{
    number::uint256_cpy(r, a);
}

bool sm9_bn_equal_zero(const sm9_bn_t a) noexcept
{
    return number::uint256_equal_zero(a);
}

int sm9_bn_add_uint32(sm9_bn_t r, const sm9_bn_t a, std::uint32_t b) noexcept
{
    return number::uint256_add_carry_uint32(r, a, b);
}

void sm9_bn_mod_n_sub1(sm9_bn_t a) noexcept
{
    number::uint256_t n_sub1;
    number::uint256_sub_borrow_uint32(n_sub1, N.v, 1);
    if (number::uint256_cmp(a, n_sub1) >= 0)
    {
        number::uint256_sub_borrow(a, a, n_sub1);
    }
}

void sm9_bn_mod_n_sub1_ex(sm9_bn_t            a,
                          const std::uint8_t* data,
                          std::size_t         data_len) noexcept
{
    number::uint256_t n_sub1;
    number::uint256_sub_borrow_uint32(n_sub1, N.v, 1);
    number::uint256_mod(a, data, data_len, n_sub1);
}

void sm9_bn_mod_n_sub2(sm9_bn_t a) noexcept
{
    if (number::uint256_cmp(a, N_SUB2.v) >= 0)
    {
        number::uint256_sub_borrow(a, a, N_SUB2.v);
    }
}

void sm9_bn_mod_n_sub3(sm9_bn_t a) noexcept
{
    if (number::uint256_cmp(a, N_SUB3.v) >= 0)
    {
        number::uint256_sub_borrow(a, a, N_SUB3.v);
    }
}

void sm9_bn_from_bytes(sm9_bn_t r, const std::uint8_t in[32]) noexcept
{
    number::uint256_from_bytes(r, in);
}

void sm9_bn_to_bytes(std::uint8_t out[32], const sm9_bn_t a) noexcept
{
    number::uint256_to_bytes(out, a);
}

#pragma endregion

// =============================================================================
// =================================== n =======================================
// === 0xb640000002a3a6f1d603ab4ff58ec74449f2934b18ea8beee56ee19cd69ecf25 =====
// =============================================================================

#pragma region "SM9 FN ALGO"

void sm9_fn_add(sm9_fn_t r, const sm9_fn_t a, const sm9_fn_t b) noexcept
{
    number::mont256_add(&FN_MONT_CTX, r, a, b);
}

void sm9_fn_sub(sm9_fn_t r, const sm9_fn_t a, const sm9_fn_t b) noexcept
{
    number::mont256_sub(&FN_MONT_CTX, r, a, b);
}

void sm9_fn_mul(sm9_fn_t r, const sm9_fn_t a, const sm9_fn_t b) noexcept
{
    number::mont256_mul(&FN_MONT_CTX, r, a, b);
}

void sm9_fn_sqr(sm9_fn_t r, const sm9_fn_t a) noexcept
{
    number::mont256_sqr(&FN_MONT_CTX, r, a);
}

void sm9_fn_inv(sm9_fn_t r, const sm9_fn_t a) noexcept
{
    number::mont256_inv(&FN_MONT_CTX, r, a);
}

bool sm9_fn_equal(const sm9_fn_t a, const sm9_fn_t b) noexcept
{
    return number::mont256_equal(&FN_MONT_CTX, a, b);
}

bool sm9_fn_equal_zero(const sm9_fn_t a) noexcept
{
    return number::mont256_equal_zero(&FN_MONT_CTX, a);
}

bool sm9_fn_equal_one(const sm9_fn_t a) noexcept
{
    return number::mont256_equal_one(&FN_MONT_CTX, a);
}

void sm9_fn_cpy(sm9_fn_t r, const sm9_fn_t a) noexcept
{
    number::mont256_cpy(&FN_MONT_CTX, r, a);
}

void sm9_fn_set_zero(sm9_fn_t r) noexcept
{
    return number::mont256_set_zero(&FN_MONT_CTX, r);
}

void sm9_fn_set_one(sm9_fn_t r) noexcept
{
    return number::mont256_set_one(&FN_MONT_CTX, r);
}

void sm9_fn_from_bytes(sm9_fn_t r, const std::uint8_t in[32]) noexcept
{
    number::mont256_from_bytes(&FN_MONT_CTX, r, in);
}

void sm9_fn_from_bytes_ex(sm9_fn_t            r,
                          const std::uint8_t* in,
                          std::size_t         inl) noexcept
{
    number::mont256_from_bytes_ex(&FN_MONT_CTX, r, in, inl);
}

void sm9_fn_to_bytes(std::uint8_t out[32], const sm9_fn_t a) noexcept
{
    number::mont256_to_bytes(&FN_MONT_CTX, out, a);
}

#pragma endregion

// ======================================================================
// ============================== p =====================================
// = 0xb640000002a3a6f1d603ab4ff58ec74521f2934b1a7aeedbe56f9b27e351457d =
// ======================================================================

#pragma region "SM9 FP ALGO"

void sm9_fp_add(sm9_fp_t r, const sm9_fp_t a, const sm9_fp_t b) noexcept
{
    number::mont256_add(&FP_MONT_CTX, r, a, b);
}

void sm9_fp_dbl(sm9_fp_t r, const sm9_fp_t a) noexcept
{
    number::mont256_dbl(&FP_MONT_CTX, r, a);
}

void sm9_fp_tpl(sm9_fp_t r, const sm9_fp_t a) noexcept
{
    number::mont256_tpl(&FP_MONT_CTX, r, a);
}

void sm9_fp_sub(sm9_fp_t r, const sm9_fp_t a, const sm9_fp_t b) noexcept
{
    number::mont256_sub(&FP_MONT_CTX, r, a, b);
}

void sm9_fp_mul(sm9_fp_t r, const sm9_fp_t a, const sm9_fp_t b) noexcept
{
    number::mont256_mul(&FP_MONT_CTX, r, a, b);
}

void sm9_fp_sqr(sm9_fp_t r, const sm9_fp_t a) noexcept
{
    number::mont256_sqr(&FP_MONT_CTX, r, a);
}

int sm9_fp_sqrt(sm9_fp_t r, const sm9_fp_t a) noexcept
{
    // p = 8u+5
    // z = a^(2u+1)
    // if z=1:  return g^(u+1)
    // if z=-1: return 2^(2u+1) * g^(u+1)
    // other:   return false

    static const auto U_ADD1 = number::mpz_set_epi8(
        0x16, 0xc8, 0x00, 0x00, 0x00, 0x54, 0x74, 0xde, 0x3a, 0xc0, 0x75, 0x69,
        0xfe, 0xb1, 0xd8, 0xe8, 0xa4, 0x3e, 0x52, 0x69, 0x63, 0x4f, 0x5d, 0xdb,
        0x7c, 0xad, 0xf3, 0x64, 0xfc, 0x6a, 0x28, 0xb0);
    static const auto U_MUL2_ADD1 = number::mpz_set_epi8(
        0x2d, 0x90, 0x00, 0x00, 0x00, 0xa8, 0xe9, 0xbc, 0x75, 0x80, 0xea, 0xd3,
        0xfd, 0x63, 0xb1, 0xd1, 0x48, 0x7c, 0xa4, 0xd2, 0xc6, 0x9e, 0xbb, 0xb6,
        0xf9, 0x5b, 0xe6, 0xc9, 0xf8, 0xd4, 0x51, 0x5f);
    static const std::uint8_t TWO_POW_2U1_DATA[32] = {
        0x49, 0xdb, 0x72, 0x1a, 0x26, 0x99, 0x67, 0xc4, 0xe0, 0xa8, 0xde,
        0xbc, 0x07, 0x83, 0x18, 0x2f, 0x82, 0x55, 0x52, 0x33, 0x13, 0x9e,
        0x9d, 0x63, 0xef, 0xbd, 0x7b, 0x54, 0x09, 0x2c, 0x75, 0x6c,
    };
    number::mont256_t z;
    number::mont256_t neg1;
    number::mont256_set_one(&FP_MONT_CTX, neg1);
    number::mont256_neg(&FP_MONT_CTX, neg1, neg1);
    // z = a^(2u+1)
    number::mont256_pow(&FP_MONT_CTX, z, a, U_MUL2_ADD1.v);
    // if z=1:  return g^(u+1)
    // if z=-1: return 2^(2u+1) * g^(u+1)
    // other:   return false
    if (!number::mont256_equal_one(&FP_MONT_CTX, z) &&
        !number::mont256_equal(&FP_MONT_CTX, z, neg1))
    {
        return -1;
    }
    number::mont256_pow(&FP_MONT_CTX, r, a, U_ADD1.v);
    if (number::mont256_equal(&FP_MONT_CTX, z, neg1))
    {
        number::mont256_from_bytes(&FP_MONT_CTX, z, TWO_POW_2U1_DATA);
        number::mont256_mul(&FP_MONT_CTX, r, r, z);
    }
    return 0;
}

void sm9_fp_neg(sm9_fp_t r, const sm9_fp_t a) noexcept
{
    number::mont256_neg(&FP_MONT_CTX, r, a);
}

void sm9_fp_inv(sm9_fp_t r, const sm9_fp_t a) noexcept
{
    number::mont256_inv(&FP_MONT_CTX, r, a);
}

bool sm9_fp_equal(const sm9_fp_t a, const sm9_fp_t b) noexcept
{
    return number::mont256_equal(&FP_MONT_CTX, a, b);
}

bool sm9_fp_equal_zero(const sm9_fp_t a) noexcept
{
    return number::mont256_equal_zero(&FP_MONT_CTX, a);
}

bool sm9_fp_equal_one(const sm9_fp_t a) noexcept
{
    return number::mont256_equal_one(&FP_MONT_CTX, a);
}

void sm9_fp_cpy(sm9_fp_t r, const sm9_fp_t a) noexcept
{
    number::mont256_cpy(&FP_MONT_CTX, r, a);
}

void sm9_fp_set_zero(sm9_fp_t r) noexcept
{
    number::mont256_set_zero(&FP_MONT_CTX, r);
}

void sm9_fp_set_one(sm9_fp_t r) noexcept
{
    number::mont256_set_one(&FP_MONT_CTX, r);
}

void sm9_fp_from_bytes(sm9_fp_t r, const std::uint8_t in[32]) noexcept
{
    number::mont256_from_bytes(&FP_MONT_CTX, r, in);
}

void sm9_fp_to_bytes(std::uint8_t out[32], const sm9_fp_t a) noexcept
{
    number::mont256_to_bytes(&FP_MONT_CTX, out, a);
}

#pragma endregion

#pragma region "SM9 FP FN BN CAST"

void sm9_fp_to_bn(sm9_bn_t r, const sm9_fp_t a) noexcept
{
    std::uint8_t buf[32];
    sm9_fp_to_bytes(buf, a);
    sm9_bn_from_bytes(r, buf);
}

void sm9_fp_from_bn(sm9_fp_t r, const sm9_bn_t a) noexcept
{
    std::uint8_t buf[32];
    sm9_bn_to_bytes(buf, a);
    sm9_fp_from_bytes(r, buf);
}

void sm9_fn_to_bn(sm9_bn_t r, const sm9_fn_t a) noexcept
{
    std::uint8_t buf[32];
    sm9_fn_to_bytes(buf, a);
    sm9_bn_from_bytes(r, buf);
}

void sm9_fn_from_bn(sm9_fn_t r, const sm9_bn_t a) noexcept
{
    std::uint8_t buf[32];
    sm9_bn_to_bytes(buf, a);
    sm9_fn_from_bytes(r, buf);
}

void sm9_fn_from_fp(sm9_fn_t r, const sm9_fp_t a) noexcept
{
    std::uint8_t buf[32];
    sm9_fp_to_bytes(buf, a);
    sm9_fn_from_bytes(r, buf);
}

void sm9_fn_to_fp(sm9_fp_t r, const sm9_fn_t a) noexcept
{
    std::uint8_t buf[32];
    sm9_fn_to_bytes(buf, a);
    sm9_fp_from_bytes(r, buf);
}

#pragma endregion

#pragma region "SM9 FP2 ALGO"

void sm9_fp2_to_bytes(std::uint8_t dst[64], const sm9_fp2_t a) noexcept
{
    sm9_fp_to_bytes(dst, a[1]);
    sm9_fp_to_bytes(dst + 32, a[0]);
}

void sm9_fp2_from_bytes(sm9_fp2_t r, const std::uint8_t src[64]) noexcept
{
    sm9_fp_from_bytes(r[1], src);
    sm9_fp_from_bytes(r[0], src + 32);
}

void sm9_fp2_cpy(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    sm9_fp_cpy(r[0], a[0]);
    sm9_fp_cpy(r[1], a[1]);
}

bool sm9_fp2_equal(const sm9_fp2_t a, const sm9_fp2_t b) noexcept
{
    return sm9_fp_equal(a[0], b[0]) && sm9_fp_equal(a[1], b[1]);
}

bool sm9_fp2_equal_zero(const sm9_fp2_t a) noexcept
{
    return sm9_fp_equal_zero(a[0]) && sm9_fp_equal_zero(a[1]);
}

bool sm9_fp2_equal_one(const sm9_fp2_t a) noexcept
{
    return sm9_fp_equal_one(a[0]) && sm9_fp_equal_zero(a[1]);
}

void sm9_fp2_set_zero(sm9_fp2_t r) noexcept
{
    sm9_fp_set_zero(r[0]);
    sm9_fp_set_zero(r[1]);
}

void sm9_fp2_set_one(sm9_fp2_t r) noexcept
{
    sm9_fp_set_one(r[0]);
    sm9_fp_set_zero(r[1]);
}

void sm9_fp2_add(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp2_t b) noexcept
{
    sm9_fp_add(r[0], a[0], b[0]);
    sm9_fp_add(r[1], a[1], b[1]);
}

void sm9_fp2_dbl(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    sm9_fp_dbl(r[0], a[0]);
    sm9_fp_dbl(r[1], a[1]);
}

void sm9_fp2_tpl(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    sm9_fp_tpl(r[0], a[0]);
    sm9_fp_tpl(r[1], a[1]);
}

void sm9_fp2_neg(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    sm9_fp_neg(r[0], a[0]);
    sm9_fp_neg(r[1], a[1]);
}

void sm9_fp2_sub(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp2_t b) noexcept
{
    sm9_fp_sub(r[0], a[0], b[0]);
    sm9_fp_sub(r[1], a[1], b[1]);
}

void sm9_fp2_mul(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp2_t b) noexcept
{
    // (a0 + a1 u) * (b0 + b1 u) = (a0b0 - 2 a1b1) + (a0b1 + a1b0) u
    // = (a0b0 - 2 a1b1) + ( (a0 + a1) * (b0 + b1) - a0b0 - a1b1) u
    sm9_fp_t a0b0, a1b1, t;
    sm9_fp_mul(a0b0, a[0], b[0]);
    sm9_fp_mul(a1b1, a[1], b[1]);
    // r1 = (a0 + a1) * (b0 + b1) - a0b0 - a1b1
    sm9_fp_add(t, a[0], a[1]);
    sm9_fp_add(r[1], b[0], b[1]);
    sm9_fp_mul(r[1], t, r[1]);
    sm9_fp_sub(r[1], r[1], a0b0);
    sm9_fp_sub(r[1], r[1], a1b1);
    // r0 = a0b0 - 2 a1b1
    sm9_fp_dbl(t, a1b1);
    sm9_fp_sub(r[0], a0b0, t);
}

void sm9_fp2_mul_u(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    // (a0 + a1 u) * u = a1 u^2 + a0 u = -2 a1 + a0 u
    sm9_fp_t t;
    sm9_fp_dbl(t, a[1]);
    sm9_fp_cpy(r[1], a[0]);
    sm9_fp_neg(r[0], t);
}

void sm9_fp2_mul_fp(sm9_fp2_t r, const sm9_fp2_t a, const sm9_fp_t b) noexcept
{
    sm9_fp_mul(r[0], a[0], b);
    sm9_fp_mul(r[1], a[1], b);
}

void sm9_fp2_sqr(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    // (a0 + a1 u)^2 = (a0^2 - 2 a1^2) + ( (a0 + a1) * 2 - a0^2 - a1^2) u
    sm9_fp_t a0a0, a1a1;
    sm9_fp_sqr(a0a0, a[0]);
    sm9_fp_sqr(a1a1, a[1]);

    sm9_fp_add(r[1], a[0], a[1]);
    sm9_fp_sqr(r[1], r[1]);
    sm9_fp_sub(r[1], r[1], a0a0);
    sm9_fp_sub(r[1], r[1], a1a1);

    sm9_fp_dbl(a1a1, a1a1);
    sm9_fp_sub(r[0], a0a0, a1a1);
}

void sm9_fp2_inv(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    // (a0 + a1 u)^-1 = (a0 - a1 u) / (a0^2 - a1^2 u^2) = (a0 - a1 u) / (a0^2 +
    // 2 a1^2)
    sm9_fp_t t0, t1;
    sm9_fp_sqr(t0, a[0]);
    sm9_fp_sqr(t1, a[1]);
    sm9_fp_dbl(t1, t1);
    sm9_fp_add(t0, t0, t1);
    sm9_fp_inv(t0, t0);

    sm9_fp_mul(r[0], a[0], t0);
    sm9_fp_mul(r[1], a[1], t0);
    sm9_fp_neg(r[1], r[1]);
}

#pragma endregion

#pragma region "SM9 FP4 ALGO"

void sm9_fp4_to_bytes(std::uint8_t dst[128], const sm9_fp4_t a) noexcept
{
    sm9_fp2_to_bytes(dst, a[1]);
    sm9_fp2_to_bytes(dst + 64, a[0]);
}

void sm9_fp4_from_bytes(sm9_fp4_t r, const std::uint8_t src[128]) noexcept
{
    sm9_fp2_from_bytes(r[1], src);
    sm9_fp2_from_bytes(r[0], src + 64);
}

void sm9_fp4_cpy(sm9_fp4_t r, const sm9_fp4_t a) noexcept
{
    sm9_fp2_cpy(r[0], a[0]);
    sm9_fp2_cpy(r[1], a[1]);
}

bool sm9_fp4_equal(const sm9_fp4_t a, const sm9_fp4_t b) noexcept
{
    return sm9_fp2_equal(a[0], b[0]) && sm9_fp2_equal(a[1], b[1]);
}

bool sm9_fp4_equal_zero(const sm9_fp4_t a) noexcept
{
    return sm9_fp2_equal_zero(a[0]) && sm9_fp2_equal_zero(a[1]);
}

bool sm9_fp4_equal_one(const sm9_fp4_t a) noexcept
{
    return sm9_fp2_equal_one(a[0]) && sm9_fp2_equal_zero(a[1]);
}

void sm9_fp4_set_zero(sm9_fp4_t r) noexcept
{
    sm9_fp2_set_zero(r[0]);
    sm9_fp2_set_zero(r[1]);
}

void sm9_fp4_set_one(sm9_fp4_t r) noexcept
{
    sm9_fp2_set_one(r[0]);
    sm9_fp2_set_zero(r[1]);
}

void sm9_fp4_add(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp4_t b) noexcept
{
    sm9_fp2_add(r[0], a[0], b[0]);
    sm9_fp2_add(r[1], a[1], b[1]);
}

void sm9_fp4_neg(sm9_fp4_t r, const sm9_fp4_t a) noexcept
{
    sm9_fp2_neg(r[0], a[0]);
    sm9_fp2_neg(r[1], a[1]);
}

void sm9_fp4_sub(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp4_t b) noexcept
{
    sm9_fp2_sub(r[0], a[0], b[0]);
    sm9_fp2_sub(r[1], a[1], b[1]);
}

void sm9_fp4_mul(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp4_t b) noexcept
{
    // (a0 + a1 v) * (b0 + b1 v) = (a0b0 + a1b1 u) + (a0b1 + a1b0) v
    // = (a0b0 + a1b1 u) + ( (a0 + a1) * (b0 + b1) - a0b0 - a1b1) v
    sm9_fp2_t a0b0, a1b1, t;
    sm9_fp2_mul(a0b0, a[0], b[0]);
    sm9_fp2_mul(a1b1, a[1], b[1]);
    // r1 = (a0 + a1) * (b0 + b1) - a0b0 - a1b1
    sm9_fp2_add(t, a[0], a[1]);
    sm9_fp2_add(r[1], b[0], b[1]);
    sm9_fp2_mul(r[1], t, r[1]);
    sm9_fp2_sub(r[1], r[1], a0b0);
    sm9_fp2_sub(r[1], r[1], a1b1);
    // r0 = a0b0 + a1b1 u
    sm9_fp2_mul_u(t, a1b1);
    sm9_fp2_add(r[0], a0b0, t);
}

void sm9_fp4_mul_v(sm9_fp4_t r, const sm9_fp4_t a) noexcept
{
    // (a0 + a1 v) * v = a1 v^2 + a0 v = a1 u + a0 v
    sm9_fp2_t t;
    sm9_fp2_mul_u(t, a[1]);
    sm9_fp2_cpy(r[1], a[0]);
    sm9_fp2_cpy(r[0], t);
}

void sm9_fp4_mul_fp(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp_t b) noexcept
{
    sm9_fp_mul(r[0][0], a[0][0], b);
    sm9_fp_mul(r[0][1], a[0][1], b);
    sm9_fp_mul(r[1][0], a[1][0], b);
    sm9_fp_mul(r[1][1], a[1][1], b);
}

void sm9_fp4_mul_fp2(sm9_fp4_t r, const sm9_fp4_t a, const sm9_fp2_t b) noexcept
{
    sm9_fp2_mul(r[0], a[0], b);
    sm9_fp2_mul(r[1], a[1], b);
}

void sm9_fp4_sqr(sm9_fp4_t r, const sm9_fp4_t a) noexcept
{
    // (a0 + a1 v)^2 = (a0^2 + a1^2 u) + ( (a0 + a1) * 2 - a0^2 - a1^2) v
    sm9_fp2_t a0a0, a1a1;
    sm9_fp2_sqr(a0a0, a[0]);
    sm9_fp2_sqr(a1a1, a[1]);

    sm9_fp2_add(r[1], a[0], a[1]);
    sm9_fp2_sqr(r[1], r[1]);
    sm9_fp2_sub(r[1], r[1], a0a0);
    sm9_fp2_sub(r[1], r[1], a1a1);

    sm9_fp2_mul_u(a1a1, a1a1);
    sm9_fp2_add(r[0], a0a0, a1a1);
}

void sm9_fp4_inv(sm9_fp4_t r, const sm9_fp4_t a) noexcept
{
    // (a0 + a1 v)^-1 = (a0 - a1 v) / (a0^2 - a1^2 v^2) = (a0 - a1 v) / (a0^2 -
    // a1^2 u)
    sm9_fp2_t t0, t1;
    sm9_fp2_sqr(t0, a[0]);
    sm9_fp2_sqr(t1, a[1]);
    sm9_fp2_mul_u(t1, t1);
    sm9_fp2_sub(t0, t0, t1);
    sm9_fp2_inv(t0, t0);

    sm9_fp2_mul(r[0], a[0], t0);
    sm9_fp2_mul(r[1], a[1], t0);
    sm9_fp2_neg(r[1], r[1]);
}

#pragma endregion

#pragma region "SM9 FP12 ALGO"

void sm9_fp12_to_bytes(std::uint8_t dst[384], const sm9_fp12_t a) noexcept
{
    sm9_fp4_to_bytes(dst, a[2]);
    sm9_fp4_to_bytes(dst + 128, a[1]);
    sm9_fp4_to_bytes(dst + 256, a[0]);
}

void sm9_fp12_from_bytes(sm9_fp12_t r, const std::uint8_t src[384]) noexcept
{
    sm9_fp4_from_bytes(r[2], src);
    sm9_fp4_from_bytes(r[1], src + 128);
    sm9_fp4_from_bytes(r[0], src + 256);
}

void sm9_fp12_cpy(sm9_fp12_t r, const sm9_fp12_t a) noexcept
{
    sm9_fp4_cpy(r[0], a[0]);
    sm9_fp4_cpy(r[1], a[1]);
    sm9_fp4_cpy(r[2], a[2]);
}

bool sm9_fp12_equal(const sm9_fp12_t a, const sm9_fp12_t b) noexcept
{
    return sm9_fp4_equal(a[0], b[0]) && sm9_fp4_equal(a[1], b[1]) &&
           sm9_fp4_equal(a[2], b[2]);
}

bool sm9_fp12_equal_zero(const sm9_fp12_t a) noexcept
{
    return sm9_fp4_equal_zero(a[0]) && sm9_fp4_equal_zero(a[1]) &&
           sm9_fp4_equal_zero(a[2]);
}

bool sm9_fp12_equal_one(const sm9_fp12_t a) noexcept
{
    return sm9_fp4_equal_one(a[0]) && sm9_fp4_equal_zero(a[1]) &&
           sm9_fp4_equal_zero(a[2]);
}

void sm9_fp12_set_zero(sm9_fp12_t r) noexcept
{
    sm9_fp4_set_zero(r[0]);
    sm9_fp4_set_zero(r[1]);
    sm9_fp4_set_zero(r[2]);
}

void sm9_fp12_set_one(sm9_fp12_t r) noexcept
{
    sm9_fp4_set_one(r[0]);
    sm9_fp4_set_zero(r[1]);
    sm9_fp4_set_zero(r[2]);
}

void sm9_fp12_add(sm9_fp12_t r, const sm9_fp12_t a, const sm9_fp12_t b) noexcept
{
    sm9_fp4_add(r[0], a[0], b[0]);
    sm9_fp4_add(r[1], a[1], b[1]);
    sm9_fp4_add(r[2], a[2], b[2]);
}

void sm9_fp12_neg(sm9_fp12_t r, const sm9_fp12_t a) noexcept
{
    sm9_fp4_neg(r[0], a[0]);
    sm9_fp4_neg(r[1], a[1]);
    sm9_fp4_neg(r[2], a[2]);
}
void sm9_fp12_sub(sm9_fp12_t r, const sm9_fp12_t a, const sm9_fp12_t b) noexcept
{
    sm9_fp4_sub(r[0], a[0], b[0]);
    sm9_fp4_sub(r[1], a[1], b[1]);
    sm9_fp4_sub(r[2], a[2], b[2]);
}

void sm9_fp12_mul(sm9_fp12_t r, const sm9_fp12_t a, const sm9_fp12_t b) noexcept
{
    // (a0 + a1w + a2 w^2)( b0 + b1w + b2 w^2)
    //  = a0b0 + ( (a1 + a2) (b1 + b2) - a1b1 - a2b2) v + ( (a0 + a1) (b0 + b1)
    //  - a0b0 - a1b1 + a2b2 v) w
    // 	  + ( (a0 + a2) (b0 + b2) - a0b0 - a2b2 + a1b1) w^2

    sm9_fp4_t a0b0, a1b1, a2b2;
    sm9_fp4_t a1_add_a2, a0_add_a1, a0_add_a2;
    sm9_fp4_t b1_add_b2, b0_add_b1, b0_add_b2;

    sm9_fp4_mul(a0b0, a[0], b[0]);
    sm9_fp4_mul(a1b1, a[1], b[1]);
    sm9_fp4_mul(a2b2, a[2], b[2]);

    sm9_fp4_add(a1_add_a2, a[1], a[2]);
    sm9_fp4_add(a0_add_a1, a[0], a[1]);
    sm9_fp4_add(a0_add_a2, a[0], a[2]);

    sm9_fp4_add(b1_add_b2, b[1], b[2]);
    sm9_fp4_add(b0_add_b1, b[0], b[1]);
    sm9_fp4_add(b0_add_b2, b[0], b[2]);
    // r0 = a0b0 + ( (a1 + a2) (b1 + b2) - a1b1 - a2b2) v
    sm9_fp4_mul(r[0], a1_add_a2, b1_add_b2);
    sm9_fp4_sub(r[0], r[0], a1b1);
    sm9_fp4_sub(r[0], r[0], a2b2);
    sm9_fp4_mul_v(r[0], r[0]);
    sm9_fp4_add(r[0], r[0], a0b0);
    // r2 = ( (a0 + a2) (b0 + b2) - a0b0 - a2b2 + a1b1)
    sm9_fp4_mul(r[2], a0_add_a2, b0_add_b2);
    sm9_fp4_sub(r[2], r[2], a0b0);
    sm9_fp4_sub(r[2], r[2], a2b2);
    sm9_fp4_add(r[2], r[2], a1b1);
    // r1 = ( (a0 + a1) (b0 + b1) - a0b0 - a1b1 + a2b2 v)
    sm9_fp4_mul(r[1], a0_add_a1, b0_add_b1);
    sm9_fp4_sub(r[1], r[1], a0b0);
    sm9_fp4_sub(r[1], r[1], a1b1);
    sm9_fp4_mul_v(a2b2, a2b2); // use a2b2 as tmp
    sm9_fp4_add(r[1], r[1], a2b2);
}

void sm9_fp12_mul_fp4(sm9_fp12_t       r,
                      const sm9_fp12_t a,
                      const sm9_fp4_t  b) noexcept
{
    sm9_fp4_mul(r[0], a[0], b);
    sm9_fp4_mul(r[1], a[1], b);
    sm9_fp4_mul(r[2], a[2], b);
}

void sm9_fp12_sqr(sm9_fp12_t r, const sm9_fp12_t a) noexcept
{
    sm9_fp12_mul(r, a, a);
}

void sm9_fp12_inv(sm9_fp12_t r, const sm9_fp12_t a) noexcept
{
    // (a0 + a1 w + a2 w^2)^(-1)=(A + B w + C w^2) / ( a0 A + (a1 C + a2 B) v )
    // A = a0^2 - a1 a2 v, B = a2^2 v- a0a1, C = a1^2 - a0a2
    sm9_fp4_t A, B, C, t0, t1;

    // A = a0^2 - a1 a2 v
    sm9_fp4_sqr(A, a[0]);
    sm9_fp4_mul(t0, a[1], a[2]);
    sm9_fp4_mul_v(t0, t0);
    sm9_fp4_sub(A, A, t0);
    // B = a2^2 v- a0a1
    sm9_fp4_sqr(B, a[2]);
    sm9_fp4_mul_v(B, B);
    sm9_fp4_mul(t0, a[0], a[1]);
    sm9_fp4_sub(B, B, t0);
    // C = a1^2 - a0a2
    sm9_fp4_sqr(C, a[1]);
    sm9_fp4_mul(t0, a[0], a[2]);
    sm9_fp4_sub(C, C, t0);

    // i = a0 A + (a1 C + a2 B) v
    sm9_fp4_mul(t0, a[1], C);
    sm9_fp4_mul(t1, a[2], B);
    sm9_fp4_add(t0, t0, t1);
    sm9_fp4_mul_v(t0, t0);
    sm9_fp4_mul(t1, a[0], A);
    sm9_fp4_add(t0, t0, t1);

    sm9_fp4_inv(t0, t0);
    // (a0 + a1 w + a2 w^2)^(-1)=(A + B w + C w^2) * i
    sm9_fp4_mul(r[0], A, t0);
    sm9_fp4_mul(r[1], B, t0);
    sm9_fp4_mul(r[2], C, t0);
}

void sm9_fp12_pow(sm9_fp12_t         r,
                  const sm9_fp12_t   a,
                  const std::uint8_t e_u8[32]) noexcept
{
    if (sm9_fp12_equal_zero(a))
    {
        sm9_fp12_set_zero(r);
        return;
    }

    sm9_fp12_t t, lut_table[16 - 2]; // j: base^(j+2)
    int        i = 0;

    // init lut table
    sm9_fp12_sqr(lut_table[0], a);
    for (int j = 1; j < 14; j++)
    {
        sm9_fp12_mul(lut_table[j], lut_table[j - 1], a);
    }
    // compute power
    while (e_u8[i] == 0) i++;
    if (e_u8[i] > 0xF)
    {
        int index = (e_u8[i] >> 4) & 0xF;
        sm9_fp12_cpy(t, (index == 1) ? a : lut_table[index - 2]);

        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        index = e_u8[i] & 0xF;
        if (index != 0)
        {
            sm9_fp12_mul(t, t, (index == 1) ? a : lut_table[index - 2]);
        }
    }
    else
    {
        int index = e_u8[i] & 0xF;
        sm9_fp12_cpy(t, (index == 1) ? a : lut_table[index - 2]);
    }
    i++;
    for (; i < 32; i++)
    {
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        if (((e_u8[i] >> 4) & 0xF) != 0)
        {
            int index = (e_u8[i] >> 4) & 0xF;
            sm9_fp12_mul(t, t, (index == 1) ? a : lut_table[index - 2]);
        }
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        sm9_fp12_sqr(t, t);
        if ((e_u8[i] & 0xF) != 0)
        {
            int index = e_u8[i] & 0xF;
            sm9_fp12_mul(t, t, (index == 1) ? a : lut_table[index - 2]);
        }
    }
    sm9_fp12_cpy(r, t);
}

#pragma endregion

#pragma region "SM9 EC"

void sm9_ec_a_cpy(sm9_ec_a R, const sm9_ec_a P) noexcept
{
    sm9_fp_cpy(R[0], P[0]);
    sm9_fp_cpy(R[1], P[1]);
}

bool sm9_ec_a_check(const sm9_ec_a P) noexcept
{
    // y^2 = x^3 + ax + b
    sm9_fp_t left, right, t;
    sm9_fp_sqr(left, P[1]);
    sm9_fp_from_bytes(right, SM9_CURVE_B);
    sm9_fp_sqr(t, P[0]);
    sm9_fp_mul(t, t, P[0]);
    sm9_fp_add(right, right, t);
    return sm9_fp_equal(left, right);
}

void sm9_ec_a_neg(sm9_ec_a R, const sm9_ec_a P) noexcept
{
    sm9_fp_cpy(R[0], P[0]);
    sm9_fp_neg(R[1], P[1]);
}

void sm9_ec_a_to_bytes04(std::uint8_t out[64], const sm9_ec_a P) noexcept
{
    sm9_fp_to_bytes(out + 0, P[0]);
    sm9_fp_to_bytes(out + 32, P[1]);
}

void sm9_ec_a_from_bytes04(sm9_ec_a R, const std::uint8_t in[64]) noexcept
{
    sm9_fp_from_bytes(R[0], in + 0);
    sm9_fp_from_bytes(R[1], in + 32);
}

void sm9_ec_a_to_bytes_uncompressed(std::uint8_t   out[65],
                                    const sm9_ec_a P) noexcept
{
    out[0] = 0x04;
    sm9_ec_a_to_bytes04(out + 1, P);
}

void sm9_ec_a_to_bytes_compressed(std::uint8_t   out[33],
                                  const sm9_ec_a P) noexcept
{
    sm9_fp_to_bytes(out + 1, P[1]);
    out[0] = ((out[32] & 1) == 0) ? 0x02 : 0x03;
    sm9_fp_to_bytes(out + 1, P[0]);
}

void sm9_ec_a_to_bytes_mix(std::uint8_t out[65], const sm9_ec_a P) noexcept
{
    sm9_ec_a_to_bytes04(out + 1, P);
    out[0] = ((out[64] & 1) == 0) ? 0x06 : 0x07;
}

static int sm9_ec_recover_y(sm9_fp_t y, const sm9_fp_t x, int y_hat) noexcept
{
    // y^2 = x^3  + b
    sm9_fp_t     y2, t;
    std::uint8_t buf[32];
    sm9_fp_from_bytes(y2, SM9_CURVE_B);
    sm9_fp_sqr(t, x);
    sm9_fp_mul(t, t, x);
    sm9_fp_add(y2, y2, t);
    if (sm9_fp_sqrt(y, y2))
    {
        return -1;
    }
    sm9_fp_to_bytes(buf, y);
    int lsb_y = buf[31] & 1;
    if (lsb_y != y_hat)
    {
        sm9_fp_neg(y, y);
    }
    return 0;
}

int sm9_ec_a_from_bytes(sm9_ec_a            R,
                        std::size_t*        read_n,
                        const std::uint8_t* in,
                        std::size_t         inl) noexcept
{
    if (inl == 0)
    {
        return -1;
    }
    if (in[0] == 0x04 || in[0] == 0x06 || in[0] == 0x07)
    {
        *read_n = 65;
        sm9_ec_a_from_bytes04(R, in + 1);
    }
    else if (in[0] == 0x02 || in[0] == 0x03)
    {
        *read_n = 33;
        sm9_fp_from_bytes(R[0], in + 1);
        int y_hat = in[0] == 0x02 ? 0 : 1;
        if (sm9_ec_recover_y(R[1], R[0], y_hat))
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return sm9_ec_a_check(R) ? 0 : -1;
}

void sm9_ec_j_cpy(sm9_ec_j R, const sm9_ec_j P) noexcept
{
    sm9_fp_cpy(R[0], P[0]);
    sm9_fp_cpy(R[1], P[1]);
    sm9_fp_cpy(R[2], P[2]);
}

bool sm9_ec_j_is_inf(const sm9_ec_j P) noexcept
{
    return sm9_fp_equal_zero(P[2]);
}

void sm9_ec_j_set_inf(sm9_ec_j R) noexcept
{
    // 1,1,0
    sm9_fp_set_one(R[0]);
    sm9_fp_set_one(R[1]);
    sm9_fp_set_zero(R[2]);
}

void sm9_ec_j_neg(sm9_ec_j R, const sm9_ec_j P) noexcept
{
    sm9_fp_cpy(R[0], P[0]);
    sm9_fp_neg(R[1], P[1]);
    sm9_fp_cpy(R[2], P[2]);
}

void sm9_ec_j_add(sm9_ec_j R, const sm9_ec_j P, const sm9_ec_j Q) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#addition-add-2007-bl
    // Cost: 11M + 5S + 9add + 4*2.
    sm9_fp_t Z1Z1, Z2Z2, U1, U2, S1, S2, H, I, J, r, V;
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]
#define X2 Q[0]
#define Y2 Q[1]
#define Z2 Q[2]

    sm9_fp_sqr(Z1Z1, Z1);
    sm9_fp_sqr(Z2Z2, Z2);
    sm9_fp_mul(U1, X1, Z2Z2);
    sm9_fp_mul(U2, X2, Z1Z1);
    sm9_fp_mul(S1, Y1, Z2);
    sm9_fp_mul(S1, S1, Z2Z2);
    sm9_fp_mul(S2, Y2, Z1);
    sm9_fp_mul(S2, S2, Z1Z1);

    if (sm9_fp_equal(U1, U2))
    {
        if (sm9_fp_equal(S1, S2))
        {
            sm9_ec_j_dbl(R, P);
        }
        else
        {
            sm9_ec_j_set_inf(R);
        }
        return;
    }

    sm9_fp_sub(H, U2, U1);
    sm9_fp_dbl(I, H);
    sm9_fp_sqr(I, I);
    sm9_fp_mul(J, H, I);
    sm9_fp_sub(r, S2, S1);
    sm9_fp_dbl(r, r);
    sm9_fp_mul(V, U1, I);

    // X3 = r2-J-2*V
    sm9_fp_sqr(X3, r);
    sm9_fp_sub(X3, X3, J);
    sm9_fp_sub(X3, X3, V);
    sm9_fp_sub(X3, X3, V);
    // Y3 = r*(V-X3)-2*S1*J
    sm9_fp_sub(Y3, V, X3);
    sm9_fp_mul(Y3, Y3, r);
    sm9_fp_mul(V, S1, J); // use V as tmp
    sm9_fp_dbl(V, V);
    sm9_fp_sub(Y3, Y3, V);
    // Z3 = ((Z1+Z2)^2-Z1Z1-Z2Z2)*H
    sm9_fp_add(Z3, Z1, Z2);
    sm9_fp_sqr(Z3, Z3);
    sm9_fp_sub(Z3, Z3, Z1Z1);
    sm9_fp_sub(Z3, Z3, Z2Z2);
    sm9_fp_mul(Z3, Z3, H);
#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef Z2
#undef X3
#undef Y3
#undef Z3
}

void sm9_ec_j_add_a(sm9_ec_j R, const sm9_ec_j P, const sm9_ec_a Q) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#addition-madd-2007-bl
    // Cost: 7M + 4S + 9add + 3*2 + 1*4.
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]
#define X2 Q[0]
#define Y2 Q[1]

    sm9_fp_t Z1Z1, U2, S2, H, HH, I, J, r, V;

    sm9_fp_sqr(Z1Z1, Z1);     // Z1Z1 = Z1^2
    sm9_fp_mul(U2, X2, Z1Z1); //  U2 = X2*Z1Z1
    sm9_fp_mul(S2, Y2, Z1);
    sm9_fp_mul(S2, S2, Z1Z1); //  S2 = Y2*Z1*Z1Z1
    sm9_fp_sub(H, U2, X1);    // H = U2-X1
    sm9_fp_sqr(HH, H);        // HH = H^2
    sm9_fp_dbl(I, HH);
    sm9_fp_dbl(I, I);    // I = 4*HH
    sm9_fp_mul(J, H, I); // J = H*I
    sm9_fp_sub(r, S2, Y1);
    sm9_fp_dbl(r, r);     // r = 2*(S2-Y1)
    sm9_fp_mul(V, X1, I); // V = X1*I
    // X3 = r^2-J-2*V
    sm9_fp_sqr(X3, r);
    sm9_fp_sub(X3, X3, J);
    sm9_fp_sub(X3, X3, V);
    sm9_fp_sub(X3, X3, V);
    // Y3 = r*(V-X3)-2*Y1*J
    sm9_fp_sub(V, V, X3);
    sm9_fp_mul(V, r, V);
    sm9_fp_mul(Y3, Y1, J);
    sm9_fp_dbl(Y3, Y3);
    sm9_fp_sub(Y3, V, Y3);
    // Z3 = (Z1+H)^2-Z1Z1-HH
    sm9_fp_add(Z3, Z1, H);
    sm9_fp_sqr(Z3, Z3);
    sm9_fp_sub(Z3, Z3, Z1Z1);
    sm9_fp_sub(Z3, Z3, HH);
#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef X3
#undef Y3
#undef Z3
}

void sm9_ec_j_dbl(sm9_ec_j R, const sm9_ec_j P) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#doubling-dbl-2009-l
    // Cost: 2M + 5S + 6add + 3*2 + 1*3 + 1*8.
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]

    sm9_fp_t A, B, C, D, E, F;

    sm9_fp_sqr(A, X1); // A = X1^2
    sm9_fp_sqr(B, Y1); // B = Y1^2
    sm9_fp_sqr(C, B);  // C = B^2
    sm9_fp_add(D, X1, B);
    sm9_fp_sqr(D, D);
    sm9_fp_sub(D, D, A);
    sm9_fp_sub(D, D, C);
    sm9_fp_dbl(D, D); // D = 2*( (X1+B)^2 -A -C )
    sm9_fp_tpl(E, A);
    sm9_fp_sqr(F, E);

    // X3 = F - 2 * D
    sm9_fp_sub(X3, F, D);
    sm9_fp_sub(X3, X3, D);
    // Z3 = 2 * Y1 * Z1
    sm9_fp_mul(Z3, Y1, Z1);
    sm9_fp_dbl(Z3, Z3);
    // Y3 = E * (D - X3) - 8 * C
    sm9_fp_sub(Y3, D, X3);
    sm9_fp_mul(Y3, Y3, E);
    sm9_fp_dbl(C, C);
    sm9_fp_dbl(C, C);
    sm9_fp_dbl(C, C);
    sm9_fp_sub(Y3, Y3, C);

#undef X1
#undef Y1
#undef Z1
#undef X3
#undef Y3
#undef Z3
}

void sm9_ec_j_mul_a(sm9_ec_j           R,
                    const std::uint8_t k[32],
                    const sm9_ec_a     P) noexcept
{
    // add-sub method
    number::uint256_t e, e3;
    number::uint256_from_bytes(e, k);
    if (number::uint256_cmp(e, N.v) >= 0)
    {
        number::uint256_sub_borrow(e, e, N.v);
    }
    if (number::uint256_equal_zero(e))
    {
        sm9_ec_j_set_inf(R);
        return;
    }
    sm9_ec_j T;
    sm9_ec_a P_neg;
    int      i;
    int      c = number::uint256_tpl_carry(e3, e);
    sm9_ec_j_from_a(T, P);
    sm9_ec_a_neg(P_neg, P);
    if (c == 1)
    {
        i = 255;
    }
    else if (c == 2)
    {
        i = 255;
        sm9_ec_j_dbl(T, T);
    }
    else // c=0
    {
        i = 255;
        while (!number::uint256_bittest(e3, i)) i--;
        i--;
    }
    for (; i >= 1; i--)
    {
        sm9_ec_j_dbl(T, T);
        int ei  = number::uint256_bittest(e, i) ? 1 : 0;
        int e3i = number::uint256_bittest(e3, i) ? 1 : 0;
        if (e3i == 1 && ei == 0)
        {
            sm9_ec_j_add_a(T, T, P);
        }
        else if (e3i == 0 && ei == 1)
        {
            sm9_ec_j_add_a(T, T, P_neg);
        }
    }
    sm9_ec_j_cpy(R, T);
}

void sm9_ec_j_mul_g(sm9_ec_j R, const std::uint8_t k[32]) noexcept
{
    sm9_ec_a G;
    sm9_fp_from_bytes(G[0], SM9_CURVE_GX);
    sm9_fp_from_bytes(G[1], SM9_CURVE_GY);
    sm9_ec_j_mul_a(R, k, G);
}

void sm9_ec_j_from_a(sm9_ec_j R, const sm9_ec_a P) noexcept
{
    sm9_fp_cpy(R[0], P[0]);
    sm9_fp_cpy(R[1], P[1]);
    sm9_fp_set_one(R[2]);
}

void sm9_ec_j_to_a(sm9_ec_a R, const sm9_ec_j P) noexcept
{
    // x = X/Z^2, y = Y/Z^3
    sm9_fp_t inv2, inv3;
    sm9_fp_inv(inv3, P[2]);
    sm9_fp_sqr(inv2, inv3);
    sm9_fp_mul(inv3, inv3, inv2);
    sm9_fp_mul(R[0], P[0], inv2);
    sm9_fp_mul(R[1], P[1], inv3);
}

void sm9_ec_j_normal(sm9_ec_j R, const sm9_ec_j P) noexcept
{
    if (sm9_ec_j_is_inf(P))
    {
        sm9_ec_j_set_inf(R);
        return;
    }
    // x = X/Z^2, y = Y/Z^3
    sm9_fp_t inv2, inv3;
    sm9_fp_inv(inv3, P[2]);
    sm9_fp_sqr(inv2, inv3);
    sm9_fp_mul(inv3, inv3, inv2);
    sm9_fp_mul(R[0], P[0], inv2);
    sm9_fp_mul(R[1], P[1], inv3);
    sm9_fp_set_one(R[2]);
}

bool sm9_ec_j_equal(const sm9_ec_j P, const sm9_ec_j Q) noexcept
{
    // Xp * Zq^2 = Xq * Zp^2
    // Yp * Zq^3 = Yq * Zp^3
    sm9_fp_t Zq2, Zq3, Zp2, Zp3, t1, t2;
    sm9_fp_sqr(Zp2, P[2]);
    sm9_fp_mul(Zp3, Zp2, P[2]);
    sm9_fp_sqr(Zq2, Q[2]);
    sm9_fp_mul(Zq3, Zq2, Q[2]);
    sm9_fp_mul(t1, P[0], Zq2);
    sm9_fp_mul(t2, Q[0], Zp2);
    if (!sm9_fp_equal(t1, t2))
    {
        return false;
    }
    sm9_fp_mul(t1, P[1], Zq3);
    sm9_fp_mul(t2, Q[1], Zp3);
    if (!sm9_fp_equal(t1, t2))
    {
        return false;
    }
    return true;
}

#pragma endregion

#pragma region "SM9 EC2"

void sm9_ec2_a_cpy(sm9_ec2_a R, const sm9_ec2_a P) noexcept
{
    sm9_fp2_cpy(R[0], P[0]);
    sm9_fp2_cpy(R[1], P[1]);
}

bool sm9_ec2_a_check(const sm9_ec2_a P) noexcept
{
    // y^2 = x^3 + ax + b
    sm9_fp2_t left, right, t;
    sm9_fp2_sqr(left, P[1]);
    sm9_fp_from_bytes(right[1], SM9_CURVE_B);
    sm9_fp_set_zero(right[0]);
    sm9_fp2_sqr(t, P[0]);
    sm9_fp2_mul(t, t, P[0]);
    sm9_fp2_add(right, right, t);
    return sm9_fp2_equal(left, right);
}

void sm9_ec2_a_neg(sm9_ec2_a R, const sm9_ec2_a P) noexcept
{
    sm9_fp2_cpy(R[0], P[0]);
    sm9_fp2_neg(R[1], P[1]);
}

void sm9_ec2_a_to_bytes04(std::uint8_t out[128], const sm9_ec2_a P) noexcept
{
    sm9_fp2_to_bytes(out + 0, P[0]);
    sm9_fp2_to_bytes(out + 32, P[1]);
}

void sm9_ec2_a_from_bytes04(sm9_ec2_a R, const std::uint8_t in[128]) noexcept
{
    sm9_fp2_from_bytes(R[0], in + 0);
    sm9_fp2_from_bytes(R[1], in + 32);
}

void sm9_ec2_a_to_bytes_uncompressed(std::uint8_t    out[129],
                                     const sm9_ec2_a P) noexcept
{
    out[0] = 0x04;
    sm9_ec2_a_to_bytes04(out + 1, P);
}

void sm9_ec2_a_to_bytes_compressed(std::uint8_t    out[65],
                                   const sm9_ec2_a P) noexcept
{
    sm9_fp2_to_bytes(out + 1, P[1]);
    out[0] = ((out[32] & 1) == 0) ? 0x02 : 0x03;
    sm9_fp2_to_bytes(out + 1, P[0]);
}

void sm9_ec2_a_to_bytes_mix(std::uint8_t out[129], const sm9_ec2_a P) noexcept
{
    sm9_ec2_a_to_bytes04(out + 1, P);
    out[0] = ((out[64] & 1) == 0) ? 0x06 : 0x07;
}

int sm9_ec2_a_from_bytes(sm9_ec2_a           R,
                         std::size_t*        read_n,
                         const std::uint8_t* in,
                         std::size_t         inl) noexcept
{
    if (inl == 0)
    {
        return -1;
    }
    if (in[0] == 0x04 || in[0] == 0x06 || in[0] == 0x07)
    {
        *read_n = 129;
        sm9_ec2_a_from_bytes04(R, in + 1);
        return 0;
    }
    else if (in[0] == 0x02 || in[0] == 0x03)
    {
        return -1;
    }
    else
    {
        return -1;
    }
}

void sm9_ec2_j_cpy(sm9_ec2_j R, const sm9_ec2_j P) noexcept
{
    sm9_fp2_cpy(R[0], P[0]);
    sm9_fp2_cpy(R[1], P[1]);
    sm9_fp2_cpy(R[2], P[2]);
}

bool sm9_ec2_j_is_inf(const sm9_ec2_j P) noexcept
{
    return sm9_fp2_equal_zero(P[2]);
}

void sm9_ec2_j_set_inf(sm9_ec2_j R) noexcept
{
    // 1,1,0
    sm9_fp2_set_one(R[0]);
    sm9_fp2_set_one(R[1]);
    sm9_fp2_set_zero(R[2]);
}

void sm9_ec2_j_neg(sm9_ec2_j R, const sm9_ec2_j P) noexcept
{
    sm9_fp2_cpy(R[0], P[0]);
    sm9_fp2_neg(R[1], P[1]);
    sm9_fp2_cpy(R[2], P[2]);
}

void sm9_ec2_j_add(sm9_ec2_j R, const sm9_ec2_j P, const sm9_ec2_j Q) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#addition-add-2007-bl
    // Cost: 11M + 5S + 9add + 4*2.
    sm9_fp2_t Z1Z1, Z2Z2, U1, U2, S1, S2, H, I, J, r, V;
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]
#define X2 Q[0]
#define Y2 Q[1]
#define Z2 Q[2]

    sm9_fp2_sqr(Z1Z1, Z1);
    sm9_fp2_sqr(Z2Z2, Z2);
    sm9_fp2_mul(U1, X1, Z2Z2);
    sm9_fp2_mul(U2, X2, Z1Z1);
    sm9_fp2_mul(S1, Y1, Z2);
    sm9_fp2_mul(S1, S1, Z2Z2);
    sm9_fp2_mul(S2, Y2, Z1);
    sm9_fp2_mul(S2, S2, Z1Z1);

    if (sm9_fp2_equal(U1, U2))
    {
        if (sm9_fp2_equal(S1, S2))
        {
            sm9_ec2_j_dbl(R, P);
        }
        else
        {
            sm9_ec2_j_set_inf(R);
        }
        return;
    }

    sm9_fp2_sub(H, U2, U1);
    sm9_fp2_dbl(I, H);
    sm9_fp2_sqr(I, I);
    sm9_fp2_mul(J, H, I);
    sm9_fp2_sub(r, S2, S1);
    sm9_fp2_dbl(r, r);
    sm9_fp2_mul(V, U1, I);

    // X3 = r2-J-2*V
    sm9_fp2_sqr(X3, r);
    sm9_fp2_sub(X3, X3, J);
    sm9_fp2_sub(X3, X3, V);
    sm9_fp2_sub(X3, X3, V);
    // Y3 = r*(V-X3)-2*S1*J
    sm9_fp2_sub(Y3, V, X3);
    sm9_fp2_mul(Y3, Y3, r);
    sm9_fp2_mul(V, S1, J); // use V as tmp
    sm9_fp2_dbl(V, V);
    sm9_fp2_sub(Y3, Y3, V);
    // Z3 = ((Z1+Z2)^2-Z1Z1-Z2Z2)*H
    sm9_fp2_add(Z3, Z1, Z2);
    sm9_fp2_sqr(Z3, Z3);
    sm9_fp2_sub(Z3, Z3, Z1Z1);
    sm9_fp2_sub(Z3, Z3, Z2Z2);
    sm9_fp2_mul(Z3, Z3, H);
#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef Z2
#undef X3
#undef Y3
#undef Z3
}

void sm9_ec2_j_add_a(sm9_ec2_j R, const sm9_ec2_j P, const sm9_ec2_a Q) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#addition-madd-2007-bl
    // Cost: 7M + 4S + 9add + 3*2 + 1*4.
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]
#define X2 Q[0]
#define Y2 Q[1]

    sm9_fp2_t Z1Z1, U2, S2, H, HH, I, J, r, V;

    sm9_fp2_sqr(Z1Z1, Z1);     // Z1Z1 = Z1^2
    sm9_fp2_mul(U2, X2, Z1Z1); //  U2 = X2*Z1Z1
    sm9_fp2_mul(S2, Y2, Z1);
    sm9_fp2_mul(S2, S2, Z1Z1); //  S2 = Y2*Z1*Z1Z1
    sm9_fp2_sub(H, U2, X1);    // H = U2-X1
    sm9_fp2_sqr(HH, H);        // HH = H^2
    sm9_fp2_dbl(I, HH);
    sm9_fp2_dbl(I, I);    // I = 4*HH
    sm9_fp2_mul(J, H, I); // J = H*I
    sm9_fp2_sub(r, S2, Y1);
    sm9_fp2_dbl(r, r);     // r = 2*(S2-Y1)
    sm9_fp2_mul(V, X1, I); // V = X1*I
    // X3 = r^2-J-2*V
    sm9_fp2_sqr(X3, r);
    sm9_fp2_sub(X3, X3, J);
    sm9_fp2_sub(X3, X3, V);
    sm9_fp2_sub(X3, X3, V);
    // Y3 = r*(V-X3)-2*Y1*J
    sm9_fp2_sub(V, V, X3);
    sm9_fp2_mul(V, r, V);
    sm9_fp2_mul(Y3, Y1, J);
    sm9_fp2_dbl(Y3, Y3);
    sm9_fp2_sub(Y3, V, Y3);
    // Z3 = (Z1+H)^2-Z1Z1-HH
    sm9_fp2_add(Z3, Z1, H);
    sm9_fp2_sqr(Z3, Z3);
    sm9_fp2_sub(Z3, Z3, Z1Z1);
    sm9_fp2_sub(Z3, Z3, HH);
#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef X3
#undef Y3
#undef Z3
}

void sm9_ec2_j_dbl(sm9_ec2_j R, const sm9_ec2_j P) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#doubling-dbl-2009-l
    // Cost: 2M + 5S + 6add + 3*2 + 1*3 + 1*8.
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]

    sm9_fp2_t A, B, C, D, E, F;

    sm9_fp2_sqr(A, X1); // A = X1^2
    sm9_fp2_sqr(B, Y1); // B = Y1^2
    sm9_fp2_sqr(C, B);  // C = B^2
    sm9_fp2_add(D, X1, B);
    sm9_fp2_sqr(D, D);
    sm9_fp2_sub(D, D, A);
    sm9_fp2_sub(D, D, C);
    sm9_fp2_dbl(D, D); // D = 2*( (X1+B)^2 -A -C )
    sm9_fp2_tpl(E, A);
    sm9_fp2_sqr(F, E);

    // X3 = F - 2 * D
    sm9_fp2_sub(X3, F, D);
    sm9_fp2_sub(X3, X3, D);
    // Z3 = 2 * Y1 * Z1
    sm9_fp2_mul(Z3, Y1, Z1);
    sm9_fp2_dbl(Z3, Z3);
    // Y3 = E * (D - X3) - 8 * C
    sm9_fp2_sub(Y3, D, X3);
    sm9_fp2_mul(Y3, Y3, E);
    sm9_fp2_dbl(C, C);
    sm9_fp2_dbl(C, C);
    sm9_fp2_dbl(C, C);
    sm9_fp2_sub(Y3, Y3, C);

#undef X1
#undef Y1
#undef Z1
#undef X3
#undef Y3
#undef Z3
}

void sm9_ec2_j_mul_a(sm9_ec2_j          R,
                     const std::uint8_t k[32],
                     const sm9_ec2_a    P) noexcept
{
    // add-sub method
    number::uint256_t e, e3;
    number::uint256_from_bytes(e, k);
    if (number::uint256_cmp(e, N.v) >= 0)
    {
        number::uint256_sub_borrow(e, e, N.v);
    }
    if (number::uint256_equal_zero(e))
    {
        sm9_ec2_j_set_inf(R);
        return;
    }
    sm9_ec2_j T;
    sm9_ec2_a P_neg;
    int       i;
    int       c = number::uint256_tpl_carry(e3, e);
    sm9_ec2_j_from_a(T, P);
    sm9_ec2_a_neg(P_neg, P);
    if (c == 1)
    {
        i = 255;
    }
    else if (c == 2)
    {
        i = 255;
        sm9_ec2_j_dbl(T, T);
    }
    else // c=0
    {
        i = 255;
        while (!number::uint256_bittest(e3, i)) i--;
        i--;
    }
    for (; i >= 1; i--)
    {
        sm9_ec2_j_dbl(T, T);
        int ei  = number::uint256_bittest(e, i) ? 1 : 0;
        int e3i = number::uint256_bittest(e3, i) ? 1 : 0;
        if (e3i == 1 && ei == 0)
        {
            sm9_ec2_j_add_a(T, T, P);
        }
        else if (e3i == 0 && ei == 1)
        {
            sm9_ec2_j_add_a(T, T, P_neg);
        }
    }
    sm9_ec2_j_cpy(R, T);
}

void sm9_ec2_j_mul_g(sm9_ec2_j R, const std::uint8_t k[32]) noexcept
{
    sm9_ec2_a G;
    sm9_fp2_from_bytes(G[0], SM9_CURVE2_GX);
    sm9_fp2_from_bytes(G[1], SM9_CURVE2_GY);
    sm9_ec2_j_mul_a(R, k, G);
}

void sm9_ec2_j_from_a(sm9_ec2_j R, const sm9_ec2_a P) noexcept
{
    sm9_fp2_cpy(R[0], P[0]);
    sm9_fp2_cpy(R[1], P[1]);
    sm9_fp2_set_one(R[2]);
}

void sm9_ec2_j_to_a(sm9_ec2_a R, const sm9_ec2_j P) noexcept
{
    // x = X/Z^2, y = Y/Z^3
    sm9_fp2_t inv2, inv3;
    sm9_fp2_inv(inv3, P[2]);
    sm9_fp2_sqr(inv2, inv3);
    sm9_fp2_mul(inv3, inv3, inv2);
    sm9_fp2_mul(R[0], P[0], inv2);
    sm9_fp2_mul(R[1], P[1], inv3);
}

void sm9_ec2_j_normal(sm9_ec2_j R, const sm9_ec2_j P) noexcept
{
    if (sm9_ec2_j_is_inf(P))
    {
        sm9_ec2_j_set_inf(R);
        return;
    }
    // x = X/Z^2, y = Y/Z^3
    sm9_fp2_t inv2, inv3;
    sm9_fp2_inv(inv3, P[2]);
    sm9_fp2_sqr(inv2, inv3);
    sm9_fp2_mul(inv3, inv3, inv2);
    sm9_fp2_mul(R[0], P[0], inv2);
    sm9_fp2_mul(R[1], P[1], inv3);
    sm9_fp2_set_one(R[2]);
}

bool sm9_ec2_j_equal(const sm9_ec2_j P, const sm9_ec2_j Q) noexcept
{
    // Xp * Zq^2 = Xq * Zp^2
    // Yp * Zq^3 = Yq * Zp^3
    sm9_fp2_t Zq2, Zq3, Zp2, Zp3, t1, t2;
    sm9_fp2_sqr(Zp2, P[2]);
    sm9_fp2_mul(Zp3, Zp2, P[2]);
    sm9_fp2_sqr(Zq2, Q[2]);
    sm9_fp2_mul(Zq3, Zq2, Q[2]);
    sm9_fp2_mul(t1, P[0], Zq2);
    sm9_fp2_mul(t2, Q[0], Zp2);
    if (!sm9_fp2_equal(t1, t2))
    {
        return false;
    }
    sm9_fp2_mul(t1, P[1], Zq3);
    sm9_fp2_mul(t2, Q[1], Zp3);
    if (!sm9_fp2_equal(t1, t2))
    {
        return false;
    }
    return true;
}

#pragma endregion

#pragma region "SM9 PAIRING"

static void sm9_fp2_conjugate(sm9_fp2_t r, const sm9_fp2_t a) noexcept
{
    sm9_fp_cpy(r[0], a[0]);
    sm9_fp_neg(r[1], a[1]);
}

static void sm9_ec2_j_frobenius_a(sm9_ec2_j R, const sm9_ec2_a Q) noexcept
{
    // (X', Y', Z') = (X, Y, Z * beta^(1/6))
    // pi[p](X', Y', Z') -> (X'^p, Y'^p, Z'^p)
    // (a0 + a1 u)^p = a0^p + a1^p u^p = a0 - a1 u

    // c = beta^(p/6) / beta^(1/6) = (-2)^((p-1)/12)) mod p
    // c = 0x3f23ea58e5720bdb843c6cfa9c08674947c5c86e0ddd04eda91d8354377b698b
    static const std::uint8_t C[32] = {
        0x3f, 0x23, 0xea, 0x58, 0xe5, 0x72, 0x0b, 0xdb, 0x84, 0x3c, 0x6c,
        0xfa, 0x9c, 0x08, 0x67, 0x49, 0x47, 0xc5, 0xc8, 0x6e, 0x0d, 0xdd,
        0x04, 0xed, 0xa9, 0x1d, 0x83, 0x54, 0x37, 0x7b, 0x69, 0x8b,
    };
    sm9_fp2_conjugate(R[0], Q[0]);
    sm9_fp2_conjugate(R[1], Q[1]);
    sm9_fp_set_zero(R[2][1]);
    sm9_fp_from_bytes(R[2][0], C);
}

static void sm9_ec2_j_frobenius2_a(sm9_ec2_j R, const sm9_ec2_a Q) noexcept
{
    // pi[p^2] = pi[p] * pi[p]
    // c = 0xf300000002a3a6f2780272354f8b78f4d5fc11967be65334
    static const std::uint8_t C[32] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x00, 0x00,
        0x00, 0x02, 0xa3, 0xa6, 0xf2, 0x78, 0x02, 0x72, 0x35, 0x4f, 0x8b,
        0x78, 0xf4, 0xd5, 0xfc, 0x11, 0x96, 0x7b, 0xe6, 0x53, 0x34,
    };
    sm9_fp2_cpy(R[0], Q[0]);
    sm9_fp2_cpy(R[1], Q[1]);
    sm9_fp_set_zero(R[2][1]);
    sm9_fp_from_bytes(R[2][0], C);
}

static void sm9_pairing_g_tangent_ja(sm9_fp12_t      f,
                                     sm9_fp4_t       d,
                                     const sm9_ec2_j T,
                                     const sm9_ec_a  P) noexcept
{
#define XT T[0]
#define YT T[1]
#define ZT T[2]
#define xP P[0]
#define yP P[1]
#define a0 f[0][0]
#define a1 f[0][1]
#define a4 f[2][0]
#define b1 d[1]
#define t0 f[1][0]
#define t1 f[1][1]
#define t2 f[2][1]

    // fi6(x, y) -> ( x * beta^(-1/3), y * beta^(-1/2) ), beta = (-2)^(1/2)
    // fi6(X, Y, Z) -> ( X, Y, Z * beta^(1/6) )
    // beta = u, beta^(1/2) = v, beta^(1/6) = w

    // g = k(xP - xT') - (yP-yT'), k = (3 xT'^2) / (2 yT')
    // xT = XT / ZT^2, yT = YT / ZT^3, (xT', yT') = fi6(xT, yT)

    // g = f / d, f = (a0, a1), (0, 0)w, (a4, 0)w^2, d = (0, b1)w
    // a0 = 2 YT^2 - 3 XT^3
    // a1 = -2 ZT^3 * YT * yP
    // a4 = 3 XT^2 * xP * ZT^2
    // b1 = 2 ZT^3 * YT
    sm9_fp2_sqr(t0, ZT);
    sm9_fp2_mul(t1, t0, ZT);
    sm9_fp2_mul(b1, t1, YT);
    sm9_fp2_dbl(b1, b1);

    sm9_fp2_mul_fp(t2, b1, yP);
    sm9_fp2_neg(a1, t2);

    sm9_fp2_sqr(t1, XT);
    sm9_fp2_mul(t0, t0, t1);
    sm9_fp2_mul_fp(t0, t0, xP);
    sm9_fp2_tpl(a4, t0);

    sm9_fp2_mul(t1, t1, XT);
    sm9_fp2_tpl(t1, t1);
    sm9_fp2_sqr(t0, YT);
    sm9_fp2_dbl(t0, t0);
    sm9_fp2_sub(a0, t0, t1);

    // clear
    sm9_fp2_set_zero(t0);
    sm9_fp2_set_zero(t1);
    sm9_fp2_set_zero(t2);

#undef XT
#undef YT
#undef ZT
#undef xP
#undef yP
#undef a0
#undef a1
#undef a4
#undef b1
#undef t0
#undef t1
#undef t2
}

// copy from GMSSL
static void sm9_pairing_g_line_jja(sm9_fp12_t      f,
                                   sm9_fp4_t       d,
                                   const sm9_ec2_j T,
                                   const sm9_ec2_j Q,
                                   const sm9_ec_a  P) noexcept
{
#define XT T[0]
#define YT T[1]
#define ZT T[2]
#define XQ Q[0]
#define YQ Q[1]
#define ZQ Q[2]
#define xP P[0]
#define yP P[1]
#define a0 f[0][0]
#define a1 f[0][1]
#define a4 f[2][0]
#define b1 d[1]
#define t0 f[1][0]
#define t1 f[1][1]
#define t2 f[2][1]
#define t3 d[0]

    // GMSSL
    sm9_fp2_sqr(t0, ZQ);
    sm9_fp2_mul(t1, t0, XT);
    sm9_fp2_mul(t0, t0, ZQ);
    sm9_fp2_sqr(t2, ZT);
    sm9_fp2_mul(t3, t2, XQ);
    sm9_fp2_mul(t2, t2, ZT);
    sm9_fp2_mul(t2, t2, YQ);
    sm9_fp2_sub(t1, t1, t3);

    sm9_fp2_mul(t1, t1, ZT);
    sm9_fp2_mul(t1, t1, ZQ);
    sm9_fp2_mul(b1, t1, t0);
    sm9_fp2_mul(t1, t1, YQ);
    sm9_fp2_mul(t3, t0, YT);
    sm9_fp2_sub(t3, t3, t2);
    sm9_fp2_mul(t0, t0, t3);
    sm9_fp2_mul_fp(t0, t0, xP);
    sm9_fp2_cpy(a4, t0);
    sm9_fp2_mul(t3, t3, XQ);
    sm9_fp2_mul(t3, t3, ZQ);
    sm9_fp2_sub(t1, t1, t3);
    sm9_fp2_cpy(a0, t1);
    sm9_fp2_mul_fp(t2, b1, yP);
    sm9_fp2_neg(t2, t2);
    sm9_fp2_cpy(a1, t2);

    // clear
    sm9_fp2_set_zero(t0);
    sm9_fp2_set_zero(t1);
    sm9_fp2_set_zero(t2);
    sm9_fp2_set_zero(t3);

#undef XT
#undef YT
#undef ZT
#undef XQ
#undef YQ
#undef ZQ
#undef xP
#undef yP
#undef a0
#undef a1
#undef a4
#undef b1
#undef t0
#undef t1
#undef t2
#undef t3
}

// copy from GMSSL
static void sm9_pairing_g_line_jaa(sm9_fp12_t      f,
                                   sm9_fp4_t       d,
                                   const sm9_ec2_j T,
                                   const sm9_ec2_a Q,
                                   const sm9_ec_a  P) noexcept
{
#define XT T[0]
#define YT T[1]
#define ZT T[2]
#define XQ Q[0]
#define YQ Q[1]
#define xP P[0]
#define yP P[1]
#define a0 f[0][0]
#define a1 f[0][1]
#define a4 f[2][0]
#define b1 d[1]
#define t0 f[1][0]
#define t1 f[1][1]
#define t2 f[2][1]
#define t3 d[0]

    // GMSSL
    sm9_fp2_sqr(t2, ZT);
    sm9_fp2_mul(t3, t2, XQ);
    sm9_fp2_mul(t2, t2, ZT);
    sm9_fp2_mul(t2, t2, YQ);
    sm9_fp2_sub(t1, XT, t3);

    sm9_fp2_mul(t1, t1, ZT);
    sm9_fp2_cpy(b1, t1);
    sm9_fp2_mul(t1, t1, YQ);
    sm9_fp2_cpy(t3, YT);
    sm9_fp2_sub(t3, t3, t2);
    sm9_fp2_mul_fp(t0, t3, xP);
    sm9_fp2_cpy(a4, t0);
    sm9_fp2_mul(t3, t3, XQ);
    sm9_fp2_sub(t1, t1, t3);
    sm9_fp2_cpy(a0, t1);
    sm9_fp2_mul_fp(t2, b1, yP);
    sm9_fp2_neg(t2, t2);
    sm9_fp2_cpy(a1, t2);

    // clear
    sm9_fp2_set_zero(t0);
    sm9_fp2_set_zero(t1);
    sm9_fp2_set_zero(t2);
    sm9_fp2_set_zero(t3);

#undef XT
#undef YT
#undef ZT
#undef XQ
#undef YQ
#undef xP
#undef yP
#undef a0
#undef a1
#undef a4
#undef b1
#undef t0
#undef t1
#undef t2
#undef t3
}

// beta   = 0x6c648de5dc0a3f2cf55acc93ee0baf159f9d411806dc5177f5b21fd3da24d011
static const std::uint8_t SM9_BETA_DATA[32] = {
    0x6c, 0x64, 0x8d, 0xe5, 0xdc, 0x0a, 0x3f, 0x2c, 0xf5, 0x5a, 0xcc,
    0x93, 0xee, 0x0b, 0xaf, 0x15, 0x9f, 0x9d, 0x41, 0x18, 0x06, 0xdc,
    0x51, 0x77, 0xf5, 0xb2, 0x1f, 0xd3, 0xda, 0x24, 0xd0, 0x11,
};
// alpha1 = 0x3f23ea58e5720bdb843c6cfa9c08674947c5c86e0ddd04eda91d8354377b698b
static const std::uint8_t SM9_ALPHA1_DATA[32] = {
    0x3f, 0x23, 0xea, 0x58, 0xe5, 0x72, 0x0b, 0xdb, 0x84, 0x3c, 0x6c,
    0xfa, 0x9c, 0x08, 0x67, 0x49, 0x47, 0xc5, 0xc8, 0x6e, 0x0d, 0xdd,
    0x04, 0xed, 0xa9, 0x1d, 0x83, 0x54, 0x37, 0x7b, 0x69, 0x8b,
};
// alpha2 = 0xf300000002a3a6f2780272354f8b78f4d5fc11967be65334
static const std::uint8_t SM9_ALPHA2_DATA[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x00, 0x00,
    0x00, 0x02, 0xa3, 0xa6, 0xf2, 0x78, 0x02, 0x72, 0x35, 0x4f, 0x8b,
    0x78, 0xf4, 0xd5, 0xfc, 0x11, 0x96, 0x7b, 0xe6, 0x53, 0x34,
};
// alpha3 = 0x6c648de5dc0a3f2cf55acc93ee0baf159f9d411806dc5177f5b21fd3da24d011
static const std::uint8_t SM9_ALPHA3_DATA[32] = {
    0x6c, 0x64, 0x8d, 0xe5, 0xdc, 0x0a, 0x3f, 0x2c, 0xf5, 0x5a, 0xcc,
    0x93, 0xee, 0x0b, 0xaf, 0x15, 0x9f, 0x9d, 0x41, 0x18, 0x06, 0xdc,
    0x51, 0x77, 0xf5, 0xb2, 0x1f, 0xd3, 0xda, 0x24, 0xd0, 0x11,
};
// alpha4 = 0xf300000002a3a6f2780272354f8b78f4d5fc11967be65333
static const std::uint8_t SM9_ALPHA4_DATA[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x00, 0x00,
    0x00, 0x02, 0xa3, 0xa6, 0xf2, 0x78, 0x02, 0x72, 0x35, 0x4f, 0x8b,
    0x78, 0xf4, 0xd5, 0xfc, 0x11, 0x96, 0x7b, 0xe6, 0x53, 0x33,
};
// alpha5 = 0x2d40a38cf6983351711e5f99520347cc57d778a9f8ff4c8a4c949c7fa2a96686
static const std::uint8_t SM9_ALPHA5_DATA[32] = {
    0x2d, 0x40, 0xa3, 0x8c, 0xf6, 0x98, 0x33, 0x51, 0x71, 0x1e, 0x5f,
    0x99, 0x52, 0x03, 0x47, 0xcc, 0x57, 0xd7, 0x78, 0xa9, 0xf8, 0xff,
    0x4c, 0x8a, 0x4c, 0x94, 0x9c, 0x7f, 0xa2, 0xa9, 0x66, 0x86,
};

static void sm9_fp12_frobenius(sm9_fp12_t r, const sm9_fp12_t x) noexcept
{
    const sm9_fp2_t* x0 = x[0];
    const sm9_fp2_t* x1 = x[1];
    const sm9_fp2_t* x2 = x[2];
    sm9_fp4_t        r1, r2, r3;
    sm9_fp_t         t;

    sm9_fp2_conjugate(r1[0], x0[0]);
    sm9_fp2_conjugate(r1[1], x0[1]);
    sm9_fp_from_bytes(t, SM9_ALPHA3_DATA);
    sm9_fp2_mul_fp(r1[1], r1[1], t);

    sm9_fp2_conjugate(r2[0], x1[0]);
    sm9_fp_from_bytes(t, SM9_ALPHA1_DATA);
    sm9_fp2_mul_fp(r2[0], r2[0], t);
    sm9_fp2_conjugate(r2[1], x1[1]);
    sm9_fp_from_bytes(t, SM9_ALPHA4_DATA);
    sm9_fp2_mul_fp(r2[1], r2[1], t);

    sm9_fp2_conjugate(r3[0], x2[0]);
    sm9_fp_from_bytes(t, SM9_ALPHA2_DATA);
    sm9_fp2_mul_fp(r3[0], r3[0], t);
    sm9_fp2_conjugate(r3[1], x2[1]);
    sm9_fp_from_bytes(t, SM9_ALPHA5_DATA);
    sm9_fp2_mul_fp(r3[1], r3[1], t);

    sm9_fp4_cpy(r[0], r1);
    sm9_fp4_cpy(r[1], r2);
    sm9_fp4_cpy(r[2], r3);
}

static void sm9_fp4_conjugate(sm9_fp4_t r, const sm9_fp4_t a) noexcept
{
    sm9_fp2_cpy(r[0], a[0]);
    sm9_fp2_neg(r[1], a[1]);
}

static void sm9_fp12_frobenius2(sm9_fp12_t r, const sm9_fp12_t x) noexcept
{
    sm9_fp4_t a;
    sm9_fp4_t b;
    sm9_fp4_t c;
    sm9_fp_t  t;

    sm9_fp4_conjugate(a, x[0]);
    sm9_fp4_conjugate(b, x[1]);
    sm9_fp_from_bytes(t, SM9_ALPHA2_DATA);
    sm9_fp4_mul_fp(b, b, t);
    sm9_fp4_conjugate(c, x[2]);
    sm9_fp_from_bytes(t, SM9_ALPHA4_DATA);
    sm9_fp4_mul_fp(c, c, t);

    sm9_fp4_cpy(r[0], a);
    sm9_fp4_cpy(r[1], b);
    sm9_fp4_cpy(r[2], c);
}

static void sm9_fp12_frobenius3(sm9_fp12_t r, const sm9_fp12_t x) noexcept
{
    const sm9_fp2_t* xa = x[0];
    const sm9_fp2_t* xb = x[1];
    const sm9_fp2_t* xc = x[2];
    sm9_fp4_t        ra, rb, rc;
    sm9_fp_t         SM9_BETA;
    sm9_fp_from_bytes(SM9_BETA, SM9_BETA_DATA);

    sm9_fp2_conjugate(ra[0], xa[0]);
    sm9_fp2_conjugate(ra[1], xa[1]);
    sm9_fp2_mul_fp(ra[1], ra[1], SM9_BETA);
    sm9_fp2_neg(ra[1], ra[1]);

    sm9_fp2_conjugate(rb[0], xb[0]);
    sm9_fp2_mul_fp(rb[0], rb[0], SM9_BETA);
    sm9_fp2_conjugate(rb[1], xb[1]);

    sm9_fp2_conjugate(rc[0], xc[0]);
    sm9_fp2_neg(rc[0], rc[0]);
    sm9_fp2_conjugate(rc[1], xc[1]);
    sm9_fp2_mul_fp(rc[1], rc[1], SM9_BETA);

    sm9_fp4_cpy(r[0], ra);
    sm9_fp4_cpy(r[1], rb);
    sm9_fp4_cpy(r[2], rc);
}

static void sm9_fp12_frobenius6(sm9_fp12_t r, const sm9_fp12_t x) noexcept
{
    sm9_fp4_t a;
    sm9_fp4_t b;
    sm9_fp4_t c;

    sm9_fp4_cpy(a, x[0]);
    sm9_fp4_cpy(b, x[1]);
    sm9_fp4_cpy(c, x[2]);

    sm9_fp4_conjugate(a, a);
    sm9_fp4_conjugate(b, b);
    sm9_fp4_neg(b, b);
    sm9_fp4_conjugate(c, c);

    sm9_fp4_cpy(r[0], a);
    sm9_fp4_cpy(r[1], b);
    sm9_fp4_cpy(r[2], c);
}

static void sm9_pairing_final_exp_hard_part(sm9_fp12_t       r,
                                            const sm9_fp12_t f) noexcept
{
    // a2 = 0xd8000000019062ed0000b98b0cb27659
    // a3 = 0x2400000000215d941
    static const std::uint8_t A2[32] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x00, 0x00, 0x00, 0x01, 0x90,
        0x62, 0xed, 0x00, 0x00, 0xb9, 0x8b, 0x0c, 0xb2, 0x76, 0x59,
    };
    static const std::uint8_t A3[32] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x02, 0x15, 0xd9, 0x41,
    };

    sm9_fp12_t t0, t1, t2, t3, t4;

    sm9_fp12_pow(t0, f, A3);
    sm9_fp12_inv(t0, t0);
    sm9_fp12_frobenius(t1, t0);
    sm9_fp12_mul(t1, t0, t1);

    sm9_fp12_mul(t0, t0, t1);
    sm9_fp12_frobenius(t2, f);
    sm9_fp12_mul(t3, t2, f);

    sm9_fp12_sqr(t4, t3);
    sm9_fp12_sqr(t4, t4);
    sm9_fp12_sqr(t4, t4);
    sm9_fp12_mul(t3, t4, t3);
    // sm9_fp12_pow(t3, t3, nine);

    sm9_fp12_mul(t0, t0, t3);
    sm9_fp12_sqr(t3, f);
    sm9_fp12_sqr(t3, t3);
    sm9_fp12_mul(t0, t0, t3);
    sm9_fp12_sqr(t2, t2);
    sm9_fp12_mul(t2, t2, t1);
    sm9_fp12_frobenius2(t1, f);
    sm9_fp12_mul(t1, t1, t2);

    sm9_fp12_pow(t2, t1, A2);
    sm9_fp12_mul(t0, t2, t0);
    sm9_fp12_frobenius3(t1, f);
    sm9_fp12_mul(t1, t1, t0);

    sm9_fp12_cpy(r, t1);
}

/**
 * GmSSL
 */
static void sm9_pairing_final_exp(sm9_fp12_t r, const sm9_fp12_t f) noexcept
{
    sm9_fp12_t t0, t1;

    sm9_fp12_frobenius6(t0, f);
    sm9_fp12_inv(t1, f);
    sm9_fp12_mul(t0, t0, t1);
    sm9_fp12_frobenius2(t1, t0);
    sm9_fp12_mul(t0, t0, t1);
    sm9_pairing_final_exp_hard_part(t0, t0);

    sm9_fp12_cpy(r, t0);
}

void sm9_pairing(sm9_fp12_t r, const sm9_ec_a P, const sm9_ec2_a Q) noexcept
{
    static const char* naf_a =
        "100100000000000000000000000000000000000010000101100020200101000020";
    static const int naf_len = 66;

    sm9_ec2_j  T;
    sm9_ec2_t  _Q;
    sm9_fp12_t f, f0;
    sm9_fp4_t  d, d0;

    sm9_fp12_set_one(f);
    sm9_fp4_set_one(d);
    sm9_ec2_j_from_a(T, Q);
    sm9_ec2_a_neg(_Q.a, Q);
    for (int i = 1; i < naf_len; i++)
    {
        // f = f^2 * g[T,T](P)
        sm9_fp12_sqr(f, f);
        sm9_pairing_g_tangent_ja(f0, d0, T, P);
        sm9_fp12_mul(f, f, f0);
        // T = [2]T
        sm9_ec2_j_dbl(T, T);
        if (naf_a[i] == '1')
        {
            // f = f * g[T,Q](P)
            sm9_pairing_g_line_jaa(f0, d0, T, Q, P);
            sm9_fp12_mul(f, f, f0);
            // T = T + Q
            sm9_ec2_j_add_a(T, T, Q);
        }
        else if (naf_a[i] == '2')
        {
            // f = f * g[T,-Q](P)
            sm9_pairing_g_line_jaa(f0, d0, T, _Q.a, P);
            sm9_fp12_mul(f, f, f0);
            // T = T - Q
            sm9_ec2_j_add_a(T, T, _Q.a);
        }
    }
    // Q1 = pi[p](Q)
    sm9_ec2_j_frobenius_a(_Q.j, Q);
    sm9_pairing_g_line_jja(f0, d0, T, _Q.j, P);
    sm9_fp12_mul(f, f, f0);
    sm9_ec2_j_add(T, T, _Q.j);
    // Q2 = -pi[p^2](Q)
    sm9_ec2_j_frobenius2_a(_Q.j, Q);
    sm9_ec2_j_neg(_Q.j, _Q.j);
    sm9_pairing_g_line_jja(f0, d0, T, _Q.j, P);
    sm9_fp12_mul(f, f, f0);
    // final exp
    sm9_pairing_final_exp(r, f);
}

void sm9_pairing_P1_Q(sm9_fp12_t r, const sm9_ec2_a Q) noexcept
{
    sm9_ec_a P1;
    sm9_fp_from_bytes(P1[0], SM9_CURVE_GX);
    sm9_fp_from_bytes(P1[1], SM9_CURVE_GY);
    sm9_pairing(r, P1, Q);
}

void sm9_pairing_P_P2(sm9_fp12_t r, const sm9_ec_a P) noexcept
{
    sm9_ec2_a P2;
    sm9_fp2_from_bytes(P2[0], SM9_CURVE2_GX);
    sm9_fp2_from_bytes(P2[1], SM9_CURVE2_GY);
    sm9_pairing(r, P, P2);
}

#pragma endregion

} // namespace sm9::internal
