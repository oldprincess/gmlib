#include <gmlib/sm2/internal/sm2p256v1.h>

#include <cstdio>

#include "sm2_p256v1_tb.inc"

namespace sm2::internal {

const std::uint8_t SM2_DEFAULT_ID[16] = {
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
};
// 16
const std::size_t SM2_DEFAULT_ID_LEN = sizeof(SM2_DEFAULT_ID);
// 0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff
const std::uint8_t SM2_CURVE_P[32] = {
    0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
// -3
const std::uint8_t SM2_CURVE_A[32] = {
    0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
};
// 0x28e9fa9e9d9f5e344d5a9e4bcf6509a7f39789f515ab8f92ddbcbd414d940e93
const std::uint8_t SM2_CURVE_B[32] = {
    0x28, 0xe9, 0xfa, 0x9e, 0x9d, 0x9f, 0x5e, 0x34, 0x4d, 0x5a, 0x9e,
    0x4b, 0xcf, 0x65, 0x09, 0xa7, 0xf3, 0x97, 0x89, 0xf5, 0x15, 0xab,
    0x8f, 0x92, 0xdd, 0xbc, 0xbd, 0x41, 0x4d, 0x94, 0x0e, 0x93,
};
// 0xfffffffe_ffffffff_ffffffff_ffffffff_7203df6b_21c6052b_53bbf409_39d54123
const std::uint8_t SM2_CURVE_N[32] = {
    0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x72, 0x03, 0xdf, 0x6b, 0x21, 0xc6,
    0x05, 0x2b, 0x53, 0xbb, 0xf4, 0x09, 0x39, 0xd5, 0x41, 0x23,
};
// 0x32c4ae2c1f1981195f9904466a39c9948fe30bbff2660be1715a4589334c74c7
const std::uint8_t SM2_CURVE_GX[32] = {
    0x32, 0xc4, 0xae, 0x2c, 0x1f, 0x19, 0x81, 0x19, 0x5f, 0x99, 0x04,
    0x46, 0x6a, 0x39, 0xc9, 0x94, 0x8f, 0xe3, 0x0b, 0xbf, 0xf2, 0x66,
    0x0b, 0xe1, 0x71, 0x5a, 0x45, 0x89, 0x33, 0x4c, 0x74, 0xc7,
};
// 0xbc3736a2f4f6779c59bdcee36b692153d0a9877cc62a474002df32e52139f0a0
const std::uint8_t SM2_CURVE_GY[32] = {
    0xbc, 0x37, 0x36, 0xa2, 0xf4, 0xf6, 0x77, 0x9c, 0x59, 0xbd, 0xce,
    0xe3, 0x6b, 0x69, 0x21, 0x53, 0xd0, 0xa9, 0x87, 0x7c, 0xc6, 0x2a,
    0x47, 0x40, 0x02, 0xdf, 0x32, 0xe5, 0x21, 0x39, 0xf0, 0xa0,
};

class SM2P256V1CtxProvider
{
private:
    std::uint8_t P_[32], P_SUB2_[32], FP_R_[32], FP_R_POW2_[32], FP_MONT_N_[32];
    std::uint8_t N_[32], N_SUB2_[32], FN_R_[32], FN_R_POW2_[32], FN_MONT_N_[32];
    std::uint8_t P_SUB3_DIV4_ADD1_[32];
    std::uint8_t N_SUB1_[32];
    number::Mont256CTX FP_MONT_CTX_;
    number::Mont256CTX FN_MONT_CTX_;

public:
    static const SM2P256V1CtxProvider& instance() noexcept
    {
        static SM2P256V1CtxProvider m;
        return m;
    }

public:
    SM2P256V1CtxProvider() noexcept
    {
        static const std::uint8_t P_SUB2_DATA[32] = {
            0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
            0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
        };
        static const std::uint8_t FP_R_DATA[32] = {
            0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
            0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        };
        static const std::uint8_t FP_R_POW2_DATA[32] = {
            0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff,
            0xff, 0xff, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03,
        };
        static const std::uint8_t FP_MONT_N_DATA[32] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        };

        static const std::uint8_t P_SUB3_DIV4_ADD1_DATA[32] = {
            0x3f, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00,
            0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        };

        static const std::uint8_t N_SUB1_DATA[32] = {
            0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0x72, 0x03, 0xdf, 0x6b, 0x21, 0xc6,
            0x05, 0x2b, 0x53, 0xbb, 0xf4, 0x09, 0x39, 0xd5, 0x41, 0x22,
        };
        static const std::uint8_t N_SUB2_DATA[32] = {
            0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0x72, 0x03, 0xdf, 0x6b, 0x21, 0xc6,
            0x05, 0x2b, 0x53, 0xbb, 0xf4, 0x09, 0x39, 0xd5, 0x41, 0x21,
        };
        static const std::uint8_t FN_R_DATA[32] = {
            0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x8d, 0xfc, 0x20, 0x94, 0xde, 0x39,
            0xfa, 0xd4, 0xac, 0x44, 0x0b, 0xf6, 0xc6, 0x2a, 0xbe, 0xdd,
        };
        static const std::uint8_t FN_R_POW2_DATA[32] = {
            0x1e, 0xb5, 0xe4, 0x12, 0xa2, 0x2b, 0x3d, 0x3b, 0x62, 0x0f, 0xc8,
            0x4c, 0x3a, 0xff, 0xe0, 0xd4, 0x34, 0x64, 0x50, 0x4a, 0xde, 0x6f,
            0xa2, 0xfa, 0x90, 0x11, 0x92, 0xaf, 0x7c, 0x11, 0x4f, 0x20,
        };
        static const std::uint8_t FN_MONT_N_DATA[32] = {
            0x6f, 0x39, 0x13, 0x2f, 0x82, 0xe4, 0xc7, 0xbc, 0x2b, 0x00, 0x68,
            0xd3, 0xb0, 0x89, 0x41, 0xd4, 0xdf, 0x1e, 0x8d, 0x34, 0xfc, 0x83,
            0x19, 0xa5, 0x32, 0x7f, 0x9e, 0x88, 0x72, 0x35, 0x09, 0x75,
        };

        number::uint256_from_bytes(P_, SM2_CURVE_P);
        number::uint256_from_bytes(P_SUB2_, P_SUB2_DATA);
        number::uint256_from_bytes(P_SUB3_DIV4_ADD1_, P_SUB3_DIV4_ADD1_DATA);
        number::uint256_from_bytes(FP_R_, FP_R_DATA);
        number::uint256_from_bytes(FP_R_POW2_, FP_R_POW2_DATA);
        number::uint256_from_bytes(FP_MONT_N_, FP_MONT_N_DATA);

        number::uint256_from_bytes(N_, SM2_CURVE_N);
        number::uint256_from_bytes(N_SUB1_, N_SUB1_DATA);
        number::uint256_from_bytes(N_SUB2_, N_SUB2_DATA);
        number::uint256_from_bytes(FN_R_, FN_R_DATA);
        number::uint256_from_bytes(FN_R_POW2_, FN_R_POW2_DATA);
        number::uint256_from_bytes(FN_MONT_N_, FN_MONT_N_DATA);

        FP_MONT_CTX_.P      = P_;
        FP_MONT_CTX_.P_SUB2 = P_SUB2_;
        FP_MONT_CTX_.R      = FP_R_;
        FP_MONT_CTX_.R_POW2 = FP_R_POW2_;
        FP_MONT_CTX_.N_     = FP_MONT_N_;

        FN_MONT_CTX_.P      = N_;
        FN_MONT_CTX_.P_SUB2 = N_SUB2_;
        FN_MONT_CTX_.R      = FN_R_;
        FN_MONT_CTX_.R_POW2 = FN_R_POW2_;
        FN_MONT_CTX_.N_     = FN_MONT_N_;
    }

    const number::Mont256CTX* FP_MONT_CTX() const noexcept
    {
        return &FP_MONT_CTX_;
    }

    const number::Mont256CTX* FN_MONT_CTX() const noexcept
    {
        return &FN_MONT_CTX_;
    }

    const std::uint8_t* P() const noexcept
    {
        return P_;
    }
    const std::uint8_t* P_SUB3_DIV4_ADD1() const noexcept
    {
        return P_SUB3_DIV4_ADD1_;
    }
    const std::uint8_t* N() const noexcept
    {
        return N_;
    }
    const std::uint8_t* N_SUB1() const noexcept
    {
        return N_SUB1_;
    }
    const std::uint8_t* N_SUB2() const noexcept
    {
        return N_SUB2_;
    }
};

int sm2_bn_cmp(const sm2_bn_t a, const sm2_bn_t b) noexcept
{
    return number::uint256_cmp(a, b);
}

void sm2_bn_cpy(sm2_bn_t r, const sm2_bn_t a) noexcept
{
    number::uint256_cpy(r, a);
}

bool sm2_bn_equal_zero(const sm2_bn_t a) noexcept
{
    return number::uint256_equal_zero(a);
}

int sm2_bn_add_uint32(sm2_bn_t r, const sm2_bn_t a, std::uint32_t b) noexcept
{
    return number::uint256_add_carry_uint32(r, a, b);
}

void sm2_bn_mod_n_sub1(sm2_bn_t a) noexcept
{
    const auto N_SUB1 = SM2P256V1CtxProvider::instance().N_SUB1();
    if (number::uint256_cmp(a, N_SUB1) >= 0)
    {
        number::uint256_sub_borrow(a, a, N_SUB1);
    }
}

void sm2_bn_mod_n_sub2(sm2_bn_t a) noexcept
{
    const auto N_SUB2 = SM2P256V1CtxProvider::instance().N_SUB2();
    if (number::uint256_cmp(a, N_SUB2) >= 0)
    {
        number::uint256_sub_borrow(a, a, N_SUB2);
    }
}

void sm2_bn_from_bytes(sm2_bn_t r, const std::uint8_t in[32]) noexcept
{
    number::uint256_from_bytes(r, in);
}

void sm2_bn_to_bytes(std::uint8_t out[32], const sm2_bn_t a) noexcept
{
    number::uint256_to_bytes(out, a);
}

void sm2_fp_add(sm2_fp_t r, const sm2_fp_t a, const sm2_fp_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_add(ctx, r, a, b);
}

void sm2_fp_dbl(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_dbl(ctx, r, a);
}

void sm2_fp_tpl(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_tpl(ctx, r, a);
}

void sm2_fp_sub(sm2_fp_t r, const sm2_fp_t a, const sm2_fp_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_sub(ctx, r, a, b);
}

void sm2_fp_mul(sm2_fp_t r, const sm2_fp_t a, const sm2_fp_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_mul(ctx, r, a, b);
}

void sm2_fp_sqr(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_sqr(ctx, r, a);
}

int sm2_fp_sqrt(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    auto&    instance = SM2P256V1CtxProvider::instance();
    auto     ctx      = instance.FP_MONT_CTX();
    sm2_fp_t t, t2;
    number::mont256_pow(ctx, t, a, instance.P_SUB3_DIV4_ADD1());
    number::mont256_sqr(ctx, t2, t);
    if (!number::mont256_equal(ctx, a, t2))
    {
        return -1;
    }
    number::mont256_cpy(ctx, r, t);
    return 0;
}

void sm2_fp_neg(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_neg(ctx, r, a);
}

void sm2_fp_inv(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_inv(ctx, r, a);
}

bool sm2_fp_equal(const sm2_fp_t a, const sm2_fp_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    return number::mont256_equal(ctx, a, b);
}

bool sm2_fp_equal_zero(const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    return number::mont256_equal_zero(ctx, a);
}

bool sm2_fp_equal_one(const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    return number::mont256_equal_one(ctx, a);
}

void sm2_fp_cpy(sm2_fp_t r, const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_cpy(ctx, r, a);
}

void sm2_fp_set_zero(sm2_fp_t r) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_set_zero(ctx, r);
}

void sm2_fp_set_one(sm2_fp_t r) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_set_one(ctx, r);
}

void sm2_fp_from_bytes(sm2_fp_t r, const std::uint8_t in[32]) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_from_bytes(ctx, r, in);
}

void sm2_fp_to_bytes(std::uint8_t out[32], const sm2_fp_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FP_MONT_CTX();
    number::mont256_to_bytes(ctx, out, a);
}

// =============================================================================
// =================================== n =======================================
// = 0xfffffffe_ffffffff_ffffffff_ffffffff_7203df6b_21c6052b_53bbf409_39d54123 =
// =============================================================================

void sm2_fn_add(sm2_fn_t r, const sm2_fn_t a, const sm2_fn_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_add(ctx, r, a, b);
}

void sm2_fn_sub(sm2_fn_t r, const sm2_fn_t a, const sm2_fn_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_sub(ctx, r, a, b);
}

void sm2_fn_mul(sm2_fn_t r, const sm2_fn_t a, const sm2_fn_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_mul(ctx, r, a, b);
}

void sm2_fn_sqr(sm2_fn_t r, const sm2_fn_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_sqr(ctx, r, a);
}

void sm2_fn_inv(sm2_fn_t r, const sm2_fn_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_inv(ctx, r, a);
}

bool sm2_fn_equal(const sm2_fn_t a, const sm2_fn_t b) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    return number::mont256_equal(ctx, a, b);
}

bool sm2_fn_equal_zero(const sm2_fn_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    return number::mont256_equal_zero(ctx, a);
}

bool sm2_fn_equal_one(const sm2_fn_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    return number::mont256_equal_one(ctx, a);
}

void sm2_fn_cpy(sm2_fn_t r, const sm2_fn_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_cpy(ctx, r, a);
}

void sm2_fn_set_zero(sm2_fn_t r) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_set_zero(ctx, r);
}

void sm2_fn_set_one(sm2_fn_t r) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_set_one(ctx, r);
}

void sm2_fn_from_bytes(sm2_fn_t r, const std::uint8_t in[32]) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_from_bytes(ctx, r, in);
}

void sm2_fn_from_bytes_ex(sm2_fn_t            r,
                          const std::uint8_t* in,
                          std::size_t         inl) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_from_bytes_ex(ctx, r, in, inl);
}

void sm2_fn_to_bytes(std::uint8_t out[32], const sm2_fn_t a) noexcept
{
    auto ctx = SM2P256V1CtxProvider::instance().FN_MONT_CTX();
    number::mont256_to_bytes(ctx, out, a);
}

void sm2_fp_to_bn(sm2_bn_t r, const sm2_fp_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fp_to_bytes(buf, a);
    sm2_bn_from_bytes(r, buf);
}

void sm2_fp_from_bn(sm2_fp_t r, const sm2_bn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_bn_to_bytes(buf, a);
    sm2_fp_from_bytes(r, buf);
}

void sm2_fn_to_bn(sm2_bn_t r, const sm2_fn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fn_to_bytes(buf, a);
    sm2_bn_from_bytes(r, buf);
}

void sm2_fn_from_bn(sm2_fn_t r, const sm2_bn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_bn_to_bytes(buf, a);
    sm2_fn_from_bytes(r, buf);
}

void sm2_fn_from_fp(sm2_fn_t r, const sm2_fp_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fp_to_bytes(buf, a);
    sm2_fn_from_bytes(r, buf);
}

void sm2_fn_to_fp(sm2_fp_t r, const sm2_fn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fn_to_bytes(buf, a);
    sm2_fp_from_bytes(r, buf);
}

void sm2_ec_a_cpy(sm2_ec_a R, const sm2_ec_a P) noexcept
{
    sm2_fp_cpy(R[0], P[0]);
    sm2_fp_cpy(R[1], P[1]);
}

bool sm2_ec_a_check(const sm2_ec_a P) noexcept
{
    // y^2 = x^3 + ax + b
    sm2_fp_t left, right, t;
    sm2_fp_sqr(left, P[1]);
    sm2_fp_from_bytes(right, SM2_CURVE_B);
    sm2_fp_from_bytes(t, SM2_CURVE_A);
    sm2_fp_mul(t, t, P[0]);
    sm2_fp_add(right, right, t);
    sm2_fp_sqr(t, P[0]);
    sm2_fp_mul(t, t, P[0]);
    sm2_fp_add(right, right, t);
    return sm2_fp_equal(left, right);
}

void sm2_ec_a_neg(sm2_ec_a R, const sm2_ec_a P) noexcept
{
    sm2_fp_cpy(R[0], P[0]);
    sm2_fp_neg(R[1], P[1]);
}

void sm2_ec_a_to_bytes04(std::uint8_t out[64], const sm2_ec_a P) noexcept
{
    sm2_fp_to_bytes(out + 0, P[0]);
    sm2_fp_to_bytes(out + 32, P[1]);
}

void sm2_ec_a_from_bytes04(sm2_ec_a R, const std::uint8_t in[64]) noexcept
{
    sm2_fp_from_bytes(R[0], in + 0);
    sm2_fp_from_bytes(R[1], in + 32);
}

void sm2_ec_a_to_bytes_uncompressed(std::uint8_t   out[65],
                                    const sm2_ec_a P) noexcept
{
    out[0] = 0x04;
    sm2_ec_a_to_bytes04(out + 1, P);
}

void sm2_ec_a_to_bytes_compressed(std::uint8_t   out[33],
                                  const sm2_ec_a P) noexcept
{
    sm2_fp_to_bytes(out + 1, P[1]);
    out[0] = ((out[32] & 1) == 0) ? 0x02 : 0x03;
    sm2_fp_to_bytes(out + 1, P[0]);
}

void sm2_ec_a_to_bytes_mix(std::uint8_t out[65], const sm2_ec_a P) noexcept
{
    sm2_ec_a_to_bytes04(out + 1, P);
    out[0] = ((out[64] & 1) == 0) ? 0x06 : 0x07;
}

static int sm2_ec_recover_y(sm2_fp_t y, const sm2_fp_t x, int y_hat) noexcept
{
    // y^2 = x^3 + ax + b
    sm2_fp_t     y2, t;
    std::uint8_t buf[32];
    sm2_fp_from_bytes(y2, SM2_CURVE_B);
    sm2_fp_from_bytes(t, SM2_CURVE_A);
    sm2_fp_mul(t, t, x);
    sm2_fp_add(y2, y2, t);
    sm2_fp_sqr(t, x);
    sm2_fp_mul(t, t, x);
    sm2_fp_add(y2, y2, t);
    if (sm2_fp_sqrt(y, y2))
    {
        return -1;
    }
    sm2_fp_to_bytes(buf, y);
    int lsb_y = buf[31] & 1;
    if (lsb_y != y_hat)
    {
        sm2_fp_neg(y, y);
    }
    return 0;
}

int sm2_ec_a_from_bytes(sm2_ec_a            R,
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
        sm2_ec_a_from_bytes04(R, in + 1);
    }
    else if (in[0] == 0x02 || in[0] == 0x03)
    {
        *read_n = 33;
        sm2_fp_from_bytes(R[0], in + 1);
        int y_hat = in[0] == 0x02 ? 0 : 1;
        if (sm2_ec_recover_y(R[1], R[0], y_hat))
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return sm2_ec_a_check(R) ? 0 : -1;
}

void sm2_ec_j_cpy(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    sm2_fp_cpy(R[0], P[0]);
    sm2_fp_cpy(R[1], P[1]);
    sm2_fp_cpy(R[2], P[2]);
}

bool sm2_ec_j_is_inf(const sm2_ec_j P) noexcept
{
    return sm2_fp_equal_zero(P[2]);
}

void sm2_ec_j_set_inf(sm2_ec_j R) noexcept
{
    // 1,1,0
    sm2_fp_set_one(R[0]);
    sm2_fp_set_one(R[1]);
    sm2_fp_set_zero(R[2]);
}

void sm2_ec_j_neg(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    sm2_fp_cpy(R[0], P[0]);
    sm2_fp_neg(R[1], P[1]);
    sm2_fp_cpy(R[2], P[2]);
}

void sm2_ec_j_add(sm2_ec_j R, const sm2_ec_j P, const sm2_ec_j Q) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-3.html#addition-add-2007-bl
    // Cost: 11M + 5S + 9add + 4*2.

#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]
#define X2 Q[0]
#define Y2 Q[1]
#define Z2 Q[2]

    sm2_fp_t Z1Z1, Z2Z2, U1, U2, S1, S2, H, I, J, r, V;
    sm2_fp_sqr(Z1Z1, Z1);
    sm2_fp_sqr(Z2Z2, Z2);
    sm2_fp_mul(U1, X1, Z2Z2);
    sm2_fp_mul(U2, X2, Z1Z1);
    sm2_fp_mul(S1, Y1, Z2);
    sm2_fp_mul(S1, S1, Z2Z2);
    sm2_fp_mul(S2, Y2, Z1);
    sm2_fp_mul(S2, S2, Z1Z1);

    if (sm2_fp_equal(U1, U2))
    {
        if (sm2_fp_equal(S1, S2))
        {
            sm2_ec_j_dbl(R, P);
        }
        else
        {
            sm2_ec_j_set_inf(R);
        }
        return;
    }

    sm2_fp_sub(H, U2, U1);
    sm2_fp_dbl(I, H);
    sm2_fp_sqr(I, I);
    sm2_fp_mul(J, H, I);
    sm2_fp_sub(r, S2, S1);
    sm2_fp_dbl(r, r);
    sm2_fp_mul(V, U1, I);

    // X3 = r2-J-2*V
    sm2_fp_sqr(X3, r);
    sm2_fp_sub(X3, X3, J);
    sm2_fp_sub(X3, X3, V);
    sm2_fp_sub(X3, X3, V);
    // Y3 = r*(V-X3)-2*S1*J
    sm2_fp_sub(Y3, V, X3);
    sm2_fp_mul(Y3, Y3, r);
    sm2_fp_mul(V, S1, J); // use V as tmp
    sm2_fp_dbl(V, V);
    sm2_fp_sub(Y3, Y3, V);
    // Z3 = ((Z1+Z2)^2-Z1Z1-Z2Z2)*H
    sm2_fp_add(Z3, Z1, Z2);
    sm2_fp_sqr(Z3, Z3);
    sm2_fp_sub(Z3, Z3, Z1Z1);
    sm2_fp_sub(Z3, Z3, Z2Z2);
    sm2_fp_mul(Z3, Z3, H);
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

void sm2_ec_j_add_a(sm2_ec_j R, const sm2_ec_j P, const sm2_ec_a Q) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-3.html#addition-madd-2007-bl
    // Cost: 7M + 4S + 9add + 3*2 + 1*4.
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]
#define X2 Q[0]
#define Y2 Q[1]

    sm2_fp_t Z1Z1, U2, S2, H, HH, I, J, r, V;

    sm2_fp_sqr(Z1Z1, Z1);     // Z1Z1 = Z1^2
    sm2_fp_mul(U2, X2, Z1Z1); //  U2 = X2*Z1Z1
    sm2_fp_mul(S2, Y2, Z1);
    sm2_fp_mul(S2, S2, Z1Z1); //  S2 = Y2*Z1*Z1Z1
    sm2_fp_sub(H, U2, X1);    // H = U2-X1
    sm2_fp_sqr(HH, H);        // HH = H^2
    sm2_fp_dbl(I, HH);
    sm2_fp_dbl(I, I);    // I = 4*HH
    sm2_fp_mul(J, H, I); // J = H*I
    sm2_fp_sub(r, S2, Y1);
    sm2_fp_dbl(r, r);     // r = 2*(S2-Y1)
    sm2_fp_mul(V, X1, I); // V = X1*I
    // X3 = r^2-J-2*V
    sm2_fp_sqr(X3, r);
    sm2_fp_sub(X3, X3, J);
    sm2_fp_sub(X3, X3, V);
    sm2_fp_sub(X3, X3, V);
    // Y3 = r*(V-X3)-2*Y1*J
    sm2_fp_sub(V, V, X3);
    sm2_fp_mul(V, r, V);
    sm2_fp_mul(Y3, Y1, J);
    sm2_fp_dbl(Y3, Y3);
    sm2_fp_sub(Y3, V, Y3);
    // Z3 = (Z1+H)^2-Z1Z1-HH
    sm2_fp_add(Z3, Z1, H);
    sm2_fp_sqr(Z3, Z3);
    sm2_fp_sub(Z3, Z3, Z1Z1);
    sm2_fp_sub(Z3, Z3, HH);

#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef X3
#undef Y3
#undef Z3
}

void sm2_ec_j_dbl(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-3.html#doubling-dbl-2001-b
    // Cost: 3M + 5S + 8add + 1*3 + 1*4 + 2*8.
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]

    sm2_fp_t delta, gamma, beta, alpha;
    // delta = Z1^2, gamma = Y1^2
    sm2_fp_sqr(delta, Z1);
    sm2_fp_sqr(gamma, Y1);
    // alpha = 3*(X1-delta)*(X1+delta), use 'beta' as tmp
    sm2_fp_sub(alpha, X1, delta);
    sm2_fp_add(beta, X1, delta);
    sm2_fp_mul(alpha, alpha, beta);
    sm2_fp_tpl(alpha, alpha);
    // beta = X1*gamma
    sm2_fp_mul(beta, X1, gamma);

    // X3 = alpha^2-8*beta
    sm2_fp_sqr(X3, alpha);
    sm2_fp_dbl(beta, beta);
    sm2_fp_dbl(beta, beta);
    sm2_fp_sub(X3, X3, beta);
    sm2_fp_sub(X3, X3, beta);
    // Z3 = (Y1+Z1)^2-gamma-delta
    sm2_fp_add(Z3, Y1, Z1);
    sm2_fp_sqr(Z3, Z3);
    sm2_fp_sub(Z3, Z3, gamma);
    sm2_fp_sub(Z3, Z3, delta);
    // Y3 = alpha*(4*beta-X3)-8*gamma^2
    sm2_fp_sub(Y3, beta, X3);
    sm2_fp_mul(Y3, Y3, alpha);
    sm2_fp_dbl(gamma, gamma);
    sm2_fp_sqr(gamma, gamma);
    sm2_fp_dbl(gamma, gamma);
    sm2_fp_sub(Y3, Y3, gamma);

#undef X1
#undef Y1
#undef Z1
#undef X3
#undef Y3
#undef Z3
}

void sm2_ec_j_mul_a(sm2_ec_j           R,
                    const std::uint8_t k[32],
                    const sm2_ec_a     P) noexcept
{
    // number::uint256_t e;
    // number::uint256_from_bytes(e, k);
    // if (number::uint256_cmp(e, N.v) >= 0)
    // {
    //     number::uint256_sub_borrow(e, e, N.v);
    // }
    // if (number::uint256_equal_zero(e))
    // {
    //     sm2_ec_j_set_inf(R);
    //     return;
    // }
    // int i = 255;
    // while (!number::uint256_bittest(e, i)) i--;
    // sm2_ec_j T;
    // sm2_ec_j_from_a(T, P);
    // i--;
    // for (; i >= 0; i--)
    // {
    //     sm2_ec_j_dbl(T, T);
    //     if (number::uint256_bittest(e, i))
    //     {
    //         sm2_ec_j_add_a(T, T, P);
    //     }
    // }
    // sm2_ec_j_cpy(R, T);

    // add-sub method
    const std::uint8_t* N = SM2P256V1CtxProvider::instance().N();
    number::uint256_t   e, e3;
    number::uint256_from_bytes(e, k);
    if (number::uint256_cmp(e, N) >= 0)
    {
        number::uint256_sub_borrow(e, e, N);
    }
    if (number::uint256_equal_zero(e))
    {
        sm2_ec_j_set_inf(R);
        return;
    }
    sm2_ec_j T;
    sm2_ec_a P_neg;
    int      i;
    int      c = number::uint256_tpl_carry(e3, e);
    sm2_ec_j_from_a(T, P);
    sm2_ec_a_neg(P_neg, P);
    if (c == 1)
    {
        i = 255;
    }
    else if (c == 2)
    {
        i = 255;
        sm2_ec_j_dbl(T, T);
    }
    else // c=0
    {
        i = 255;
        while (!number::uint256_bittest(e3, i)) i--;
        i--;
    }
    for (; i >= 1; i--)
    {
        sm2_ec_j_dbl(T, T);
        int ei  = number::uint256_bittest(e, i) ? 1 : 0;
        int e3i = number::uint256_bittest(e3, i) ? 1 : 0;
        if (e3i == 1 && ei == 0)
        {
            sm2_ec_j_add_a(T, T, P);
        }
        else if (e3i == 0 && ei == 1)
        {
            sm2_ec_j_add_a(T, T, P_neg);
        }
    }
    sm2_ec_j_cpy(R, T);
}

void sm2_ec_j_mul_g(sm2_ec_j R, const std::uint8_t k[32]) noexcept
{
    // sm2_ec_a G;
    // sm2_fp_from_bytes(G[0], SM2_CURVE_GX);
    // sm2_fp_from_bytes(G[1], SM2_CURVE_GY);
    // sm2_ec_j_mul_a(R, k, G);

    // lut optimize
    int i = 0;
    while (i < 32 && k[i] == 0) i++;
    if (i == 32)
    {
        sm2_ec_j_set_inf(R);
        return;
    }
    sm2_ec_a T;
    sm2_ec_a_from_bytes04(T, (unsigned char*)SM2_P256V1_TB[i][k[i]]);
    sm2_ec_j_from_a(R, T);
    i++;
    for (; i < 32; i++)
    {
        if (k[i] != 0)
        {
            sm2_ec_a_from_bytes04(T, (unsigned char*)SM2_P256V1_TB[i][k[i]]);
            sm2_ec_j_add_a(R, R, T);
        }
    }
}

void sm2_ec_j_from_a(sm2_ec_j R, const sm2_ec_a P) noexcept
{
    sm2_fp_cpy(R[0], P[0]);
    sm2_fp_cpy(R[1], P[1]);
    sm2_fp_set_one(R[2]);
}

void sm2_ec_j_to_a(sm2_ec_a R, const sm2_ec_j P) noexcept
{
    // x = X/Z^2, y = Y/Z^3
    sm2_fp_t inv2, inv3;
    sm2_fp_inv(inv3, P[2]);
    sm2_fp_sqr(inv2, inv3);
    sm2_fp_mul(inv3, inv3, inv2);
    sm2_fp_mul(R[0], P[0], inv2);
    sm2_fp_mul(R[1], P[1], inv3);
}

void sm2_ec_j_normal(sm2_ec_j R, const sm2_ec_j P) noexcept
{
    if (sm2_ec_j_is_inf(P))
    {
        sm2_ec_j_set_inf(R);
        return;
    }
    // x = X/Z^2, y = Y/Z^3
    sm2_fp_t inv2, inv3;
    sm2_fp_inv(inv3, P[2]);
    sm2_fp_sqr(inv2, inv3);
    sm2_fp_mul(inv3, inv3, inv2);
    sm2_fp_mul(R[0], P[0], inv2);
    sm2_fp_mul(R[1], P[1], inv3);
    sm2_fp_set_one(R[2]);
}

bool sm2_ec_j_equal(const sm2_ec_j P, const sm2_ec_j Q) noexcept
{
    // Xp * Zq^2 = Xq * Zp^2
    // Yp * Zq^3 = Yq * Zp^3
    sm2_fp_t Zq2, Zq3, Zp2, Zp3, t1, t2;
    sm2_fp_sqr(Zp2, P[2]);
    sm2_fp_mul(Zp3, Zp2, P[2]);
    sm2_fp_sqr(Zq2, Q[2]);
    sm2_fp_mul(Zq3, Zq2, Q[2]);
    sm2_fp_mul(t1, P[0], Zq2);
    sm2_fp_mul(t2, Q[0], Zp2);
    if (!sm2_fp_equal(t1, t2))
    {
        return false;
    }
    sm2_fp_mul(t1, P[1], Zq3);
    sm2_fp_mul(t2, Q[1], Zp3);
    if (!sm2_fp_equal(t1, t2))
    {
        return false;
    }
    return true;
}

}; // namespace sm2::internal