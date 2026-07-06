#include <gmlib/number/provider.h>
#include <gmlib/sm2/internal/sm2_const.h>
#include <gmlib/sm2/internal/sm2p256v1.h>

#include <cassert>
#include <cstdio>
#include <cstring>

#include "sm2_p256v1_tb.inc"

namespace sm2::internal {

struct SM2P256V1CommonContext
{
    const number::NumberProvider* number_provider;
    std::uint8_t p[32], p_sub2[32], fp_r[32], fp_r_pow2[32], fp_mont_n[32];
    std::uint8_t n[32], n_sub2[32], fn_r[32], fn_r_pow2[32], fn_mont_n[32];
    std::uint8_t p_sub3_div4_add1[32];
    std::uint8_t n_sub1[32];
    number::Mont256CTX fp_mont_ctx;
    number::Mont256CTX fn_mont_ctx;

    SM2P256V1CommonContext() noexcept
    {
        number_provider = number::get_provider(nullptr);
        assert(number_provider != nullptr);
        assert(number_provider->uint256_from_bytes != nullptr);

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

        number_provider->uint256_from_bytes(p, SM2_CURVE_P);
        number_provider->uint256_from_bytes(p_sub2, P_SUB2_DATA);
        number_provider->uint256_from_bytes(p_sub3_div4_add1,
                                            P_SUB3_DIV4_ADD1_DATA);
        number_provider->uint256_from_bytes(fp_r, FP_R_DATA);
        number_provider->uint256_from_bytes(fp_r_pow2, FP_R_POW2_DATA);
        number_provider->uint256_from_bytes(fp_mont_n, FP_MONT_N_DATA);

        number_provider->uint256_from_bytes(n, SM2_CURVE_N);
        number_provider->uint256_from_bytes(n_sub1, N_SUB1_DATA);
        number_provider->uint256_from_bytes(n_sub2, N_SUB2_DATA);
        number_provider->uint256_from_bytes(fn_r, FN_R_DATA);
        number_provider->uint256_from_bytes(fn_r_pow2, FN_R_POW2_DATA);
        number_provider->uint256_from_bytes(fn_mont_n, FN_MONT_N_DATA);

        fp_mont_ctx.P      = p;
        fp_mont_ctx.P_SUB2 = p_sub2;
        fp_mont_ctx.R      = fp_r;
        fp_mont_ctx.R_POW2 = fp_r_pow2;
        fp_mont_ctx.N_     = fp_mont_n;

        fn_mont_ctx.P      = n;
        fn_mont_ctx.P_SUB2 = n_sub2;
        fn_mont_ctx.R      = fn_r;
        fn_mont_ctx.R_POW2 = fn_r_pow2;
        fn_mont_ctx.N_     = fn_mont_n;
    }
};

static void sm2_ec_j_dbl_common(const void*    context,
                                sm2_ec_j       R,
                                const sm2_ec_j P) noexcept;

static void sm2_ec_j_from_a_common(const void*    context,
                                   sm2_ec_j       R,
                                   const sm2_ec_a P) noexcept;

static int sm2_bn_cmp_common(const void*    context,
                             const sm2_bn_t a,
                             const sm2_bn_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_cmp != nullptr);
    return provider->uint256_cmp(a, b);
}

static void sm2_bn_cpy_common(const void*    context,
                              sm2_bn_t       r,
                              const sm2_bn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_cpy != nullptr);
    provider->uint256_cpy(r, a);
}

static bool sm2_bn_equal_zero_common(const void*    context,
                                     const sm2_bn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_equal_zero != nullptr);
    return provider->uint256_equal_zero(a);
}

static int sm2_bn_add_uint32_common(const void*    context,
                                    sm2_bn_t       r,
                                    const sm2_bn_t a,
                                    std::uint32_t  b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_add_carry_uint32 != nullptr);
    return provider->uint256_add_carry_uint32(r, a, b);
}

static void sm2_bn_mod_n_sub1_common(const void* context, sm2_bn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_cmp != nullptr);
    assert(provider->uint256_sub_borrow != nullptr);
    const auto N_SUB1 = ctx->n_sub1;
    if (provider->uint256_cmp(a, N_SUB1) >= 0)
    {
        provider->uint256_sub_borrow(a, a, N_SUB1);
    }
}

static void sm2_bn_mod_n_sub2_common(const void* context, sm2_bn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_cmp != nullptr);
    assert(provider->uint256_sub_borrow != nullptr);
    const auto N_SUB2 = ctx->n_sub2;
    if (provider->uint256_cmp(a, N_SUB2) >= 0)
    {
        provider->uint256_sub_borrow(a, a, N_SUB2);
    }
}

static void sm2_bn_from_bytes_common(const void*        context,
                                     sm2_bn_t           r,
                                     const std::uint8_t in[32]) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_from_bytes != nullptr);
    provider->uint256_from_bytes(r, in);
}

static void sm2_bn_to_bytes_common(const void*    context,
                                   std::uint8_t   out[32],
                                   const sm2_bn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_to_bytes != nullptr);
    provider->uint256_to_bytes(out, a);
}

static void sm2_fp_add_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a,
                              const sm2_fp_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_add != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_add(mont_ctx, r, a, b);
}

static void sm2_fp_dbl_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_dbl != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_dbl(mont_ctx, r, a);
}

static void sm2_fp_tpl_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_tpl != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_tpl(mont_ctx, r, a);
}

static void sm2_fp_sub_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a,
                              const sm2_fp_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sub != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_sub(mont_ctx, r, a, b);
}

static void sm2_fp_mul_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a,
                              const sm2_fp_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_mul != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_mul(mont_ctx, r, a, b);
}

static void sm2_fp_sqr_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sqr != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_sqr(mont_ctx, r, a);
}

static int sm2_fp_sqrt_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_pow != nullptr);
    assert(provider->mont256_sqr != nullptr);
    assert(provider->mont256_equal != nullptr);
    assert(provider->mont256_cpy != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    sm2_fp_t    t, t2;
    provider->mont256_pow(mont_ctx, t, a, ctx->p_sub3_div4_add1);
    provider->mont256_sqr(mont_ctx, t2, t);
    if (!provider->mont256_equal(mont_ctx, a, t2))
    {
        return -1;
    }
    provider->mont256_cpy(mont_ctx, r, t);
    return 0;
}

static void sm2_fp_neg_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_neg != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_neg(mont_ctx, r, a);
}

static void sm2_fp_inv_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_inv != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_inv(mont_ctx, r, a);
}

static bool sm2_fp_equal_common(const void*    context,
                                const sm2_fp_t a,
                                const sm2_fp_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    return provider->mont256_equal(mont_ctx, a, b);
}

static bool sm2_fp_equal_zero_common(const void*    context,
                                     const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_zero != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    return provider->mont256_equal_zero(mont_ctx, a);
}

static bool sm2_fp_equal_one_common(const void*    context,
                                    const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_one != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    return provider->mont256_equal_one(mont_ctx, a);
}

static void sm2_fp_cpy_common(const void*    context,
                              sm2_fp_t       r,
                              const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_cpy != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_cpy(mont_ctx, r, a);
}

static void sm2_fp_set_zero_common(const void* context, sm2_fp_t r) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_zero != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_set_zero(mont_ctx, r);
}

static void sm2_fp_set_one_common(const void* context, sm2_fp_t r) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_one != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_set_one(mont_ctx, r);
}

static void sm2_fp_from_bytes_common(const void*        context,
                                     sm2_fp_t           r,
                                     const std::uint8_t in[32]) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_from_bytes(mont_ctx, r, in);
}

static void sm2_fp_to_bytes_common(const void*    context,
                                   std::uint8_t   out[32],
                                   const sm2_fp_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_to_bytes != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_to_bytes(mont_ctx, out, a);
}

// =============================================================================
// =================================== n =======================================
// = 0xfffffffe_ffffffff_ffffffff_ffffffff_7203df6b_21c6052b_53bbf409_39d54123 =
// =============================================================================

static void sm2_fn_add_common(const void*    context,
                              sm2_fn_t       r,
                              const sm2_fn_t a,
                              const sm2_fn_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_add != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_add(mont_ctx, r, a, b);
}

static void sm2_fn_sub_common(const void*    context,
                              sm2_fn_t       r,
                              const sm2_fn_t a,
                              const sm2_fn_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sub != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_sub(mont_ctx, r, a, b);
}

static void sm2_fn_mul_common(const void*    context,
                              sm2_fn_t       r,
                              const sm2_fn_t a,
                              const sm2_fn_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_mul != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_mul(mont_ctx, r, a, b);
}

static void sm2_fn_sqr_common(const void*    context,
                              sm2_fn_t       r,
                              const sm2_fn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sqr != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_sqr(mont_ctx, r, a);
}

static void sm2_fn_inv_common(const void*    context,
                              sm2_fn_t       r,
                              const sm2_fn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_inv != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_inv(mont_ctx, r, a);
}

static bool sm2_fn_equal_common(const void*    context,
                                const sm2_fn_t a,
                                const sm2_fn_t b) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    return provider->mont256_equal(mont_ctx, a, b);
}

static bool sm2_fn_equal_zero_common(const void*    context,
                                     const sm2_fn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_zero != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    return provider->mont256_equal_zero(mont_ctx, a);
}

static bool sm2_fn_equal_one_common(const void*    context,
                                    const sm2_fn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_one != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    return provider->mont256_equal_one(mont_ctx, a);
}

static void sm2_fn_cpy_common(const void*    context,
                              sm2_fn_t       r,
                              const sm2_fn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_cpy != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_cpy(mont_ctx, r, a);
}

static void sm2_fn_set_zero_common(const void* context, sm2_fn_t r) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_zero != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_set_zero(mont_ctx, r);
}

static void sm2_fn_set_one_common(const void* context, sm2_fn_t r) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_one != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_set_one(mont_ctx, r);
}

static void sm2_fn_from_bytes_common(const void*        context,
                                     sm2_fn_t           r,
                                     const std::uint8_t in[32]) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_from_bytes(mont_ctx, r, in);
}

static void sm2_fn_from_bytes_ex_common(const void*         context,
                                        sm2_fn_t            r,
                                        const std::uint8_t* in,
                                        std::size_t         inl) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes_ex != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_from_bytes_ex(mont_ctx, r, in, inl);
}

static void sm2_fn_to_bytes_common(const void*    context,
                                   std::uint8_t   out[32],
                                   const sm2_fn_t a) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_to_bytes != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_to_bytes(mont_ctx, out, a);
}

static void sm2_fp_to_bn_common(const void*    context,
                                sm2_bn_t       r,
                                const sm2_fp_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fp_to_bytes_common(context, buf, a);
    sm2_bn_from_bytes_common(context, r, buf);
}

static void sm2_fp_from_bn_common(const void*    context,
                                  sm2_fp_t       r,
                                  const sm2_bn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_bn_to_bytes_common(context, buf, a);
    sm2_fp_from_bytes_common(context, r, buf);
}

static void sm2_fn_to_bn_common(const void*    context,
                                sm2_bn_t       r,
                                const sm2_fn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fn_to_bytes_common(context, buf, a);
    sm2_bn_from_bytes_common(context, r, buf);
}

static void sm2_fn_from_bn_common(const void*    context,
                                  sm2_fn_t       r,
                                  const sm2_bn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_bn_to_bytes_common(context, buf, a);
    sm2_fn_from_bytes_common(context, r, buf);
}

static void sm2_fn_from_fp_common(const void*    context,
                                  sm2_fn_t       r,
                                  const sm2_fp_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fp_to_bytes_common(context, buf, a);
    sm2_fn_from_bytes_common(context, r, buf);
}

static void sm2_fn_to_fp_common(const void*    context,
                                sm2_fp_t       r,
                                const sm2_fn_t a) noexcept
{
    std::uint8_t buf[32];
    sm2_fn_to_bytes_common(context, buf, a);
    sm2_fp_from_bytes_common(context, r, buf);
}

static void sm2_ec_a_cpy_common(const void*    context,
                                sm2_ec_a       R,
                                const sm2_ec_a P) noexcept
{
    sm2_fp_cpy_common(context, R[0], P[0]);
    sm2_fp_cpy_common(context, R[1], P[1]);
}

static bool sm2_ec_a_check_common(const void*    context,
                                  const sm2_ec_a P) noexcept
{
    // y^2 = x^3 + ax + b
    sm2_fp_t left, right, t;
    sm2_fp_sqr_common(context, left, P[1]);
    sm2_fp_from_bytes_common(context, right, SM2_CURVE_B);
    sm2_fp_from_bytes_common(context, t, SM2_CURVE_A);
    sm2_fp_mul_common(context, t, t, P[0]);
    sm2_fp_add_common(context, right, right, t);
    sm2_fp_sqr_common(context, t, P[0]);
    sm2_fp_mul_common(context, t, t, P[0]);
    sm2_fp_add_common(context, right, right, t);
    return sm2_fp_equal_common(context, left, right);
}

static void sm2_ec_a_neg_common(const void*    context,
                                sm2_ec_a       R,
                                const sm2_ec_a P) noexcept
{
    sm2_fp_cpy_common(context, R[0], P[0]);
    sm2_fp_neg_common(context, R[1], P[1]);
}

static void sm2_ec_a_to_bytes04_common(const void*    context,
                                       std::uint8_t   out[64],
                                       const sm2_ec_a P) noexcept
{
    sm2_fp_to_bytes_common(context, out + 0, P[0]);
    sm2_fp_to_bytes_common(context, out + 32, P[1]);
}

static void sm2_ec_a_from_bytes04_common(const void*        context,
                                         sm2_ec_a           R,
                                         const std::uint8_t in[64]) noexcept
{
    sm2_fp_from_bytes_common(context, R[0], in + 0);
    sm2_fp_from_bytes_common(context, R[1], in + 32);
}

static void sm2_ec_a_to_bytes_uncompressed_common(const void*    context,
                                                  std::uint8_t   out[65],
                                                  const sm2_ec_a P) noexcept
{
    out[0] = 0x04;
    sm2_ec_a_to_bytes04_common(context, out + 1, P);
}

static void sm2_ec_a_to_bytes_compressed_common(const void*    context,
                                                std::uint8_t   out[33],
                                                const sm2_ec_a P) noexcept
{
    sm2_fp_to_bytes_common(context, out + 1, P[1]);
    out[0] = ((out[32] & 1) == 0) ? 0x02 : 0x03;
    sm2_fp_to_bytes_common(context, out + 1, P[0]);
}

static void sm2_ec_a_to_bytes_mix_common(const void*    context,
                                         std::uint8_t   out[65],
                                         const sm2_ec_a P) noexcept
{
    sm2_ec_a_to_bytes04_common(context, out + 1, P);
    out[0] = ((out[64] & 1) == 0) ? 0x06 : 0x07;
}

static int sm2_ec_recover_y(const void*    context,
                            sm2_fp_t       y,
                            const sm2_fp_t x,
                            int            y_hat) noexcept
{
    // y^2 = x^3 + ax + b
    sm2_fp_t     y2, t;
    std::uint8_t buf[32];
    sm2_fp_from_bytes_common(context, y2, SM2_CURVE_B);
    sm2_fp_from_bytes_common(context, t, SM2_CURVE_A);
    sm2_fp_mul_common(context, t, t, x);
    sm2_fp_add_common(context, y2, y2, t);
    sm2_fp_sqr_common(context, t, x);
    sm2_fp_mul_common(context, t, t, x);
    sm2_fp_add_common(context, y2, y2, t);
    if (sm2_fp_sqrt_common(context, y, y2))
    {
        return -1;
    }
    sm2_fp_to_bytes_common(context, buf, y);
    int lsb_y = buf[31] & 1;
    if (lsb_y != y_hat)
    {
        sm2_fp_neg_common(context, y, y);
    }
    return 0;
}

static int sm2_ec_a_from_bytes_common(const void*         context,
                                      sm2_ec_a            R,
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
        sm2_ec_a_from_bytes04_common(context, R, in + 1);
    }
    else if (in[0] == 0x02 || in[0] == 0x03)
    {
        *read_n = 33;
        sm2_fp_from_bytes_common(context, R[0], in + 1);
        int y_hat = in[0] == 0x02 ? 0 : 1;
        if (sm2_ec_recover_y(context, R[1], R[0], y_hat))
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return sm2_ec_a_check_common(context, R) ? 0 : -1;
}

static void sm2_ec_j_cpy_common(const void*    context,
                                sm2_ec_j       R,
                                const sm2_ec_j P) noexcept
{
    sm2_fp_cpy_common(context, R[0], P[0]);
    sm2_fp_cpy_common(context, R[1], P[1]);
    sm2_fp_cpy_common(context, R[2], P[2]);
}

static bool sm2_ec_j_is_inf_common(const void*    context,
                                   const sm2_ec_j P) noexcept
{
    return sm2_fp_equal_zero_common(context, P[2]);
}

static void sm2_ec_j_set_inf_common(const void* context, sm2_ec_j R) noexcept
{
    // 1,1,0
    sm2_fp_set_one_common(context, R[0]);
    sm2_fp_set_one_common(context, R[1]);
    sm2_fp_set_zero_common(context, R[2]);
}

static void sm2_ec_j_neg_common(const void*    context,
                                sm2_ec_j       R,
                                const sm2_ec_j P) noexcept
{
    sm2_fp_cpy_common(context, R[0], P[0]);
    sm2_fp_neg_common(context, R[1], P[1]);
    sm2_fp_cpy_common(context, R[2], P[2]);
}

static void sm2_ec_j_add_common(const void*    context,
                                sm2_ec_j       R,
                                const sm2_ec_j P,
                                const sm2_ec_j Q) noexcept
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
    sm2_fp_sqr_common(context, Z1Z1, Z1);
    sm2_fp_sqr_common(context, Z2Z2, Z2);
    sm2_fp_mul_common(context, U1, X1, Z2Z2);
    sm2_fp_mul_common(context, U2, X2, Z1Z1);
    sm2_fp_mul_common(context, S1, Y1, Z2);
    sm2_fp_mul_common(context, S1, S1, Z2Z2);
    sm2_fp_mul_common(context, S2, Y2, Z1);
    sm2_fp_mul_common(context, S2, S2, Z1Z1);

    if (sm2_fp_equal_common(context, U1, U2))
    {
        if (sm2_fp_equal_common(context, S1, S2))
        {
            sm2_ec_j_dbl_common(context, R, P);
        }
        else
        {
            sm2_ec_j_set_inf_common(context, R);
        }
        return;
    }

    sm2_fp_sub_common(context, H, U2, U1);
    sm2_fp_dbl_common(context, I, H);
    sm2_fp_sqr_common(context, I, I);
    sm2_fp_mul_common(context, J, H, I);
    sm2_fp_sub_common(context, r, S2, S1);
    sm2_fp_dbl_common(context, r, r);
    sm2_fp_mul_common(context, V, U1, I);

    // X3 = r2-J-2*V
    sm2_fp_sqr_common(context, X3, r);
    sm2_fp_sub_common(context, X3, X3, J);
    sm2_fp_sub_common(context, X3, X3, V);
    sm2_fp_sub_common(context, X3, X3, V);
    // Y3 = r*(V-X3)-2*S1*J
    sm2_fp_sub_common(context, Y3, V, X3);
    sm2_fp_mul_common(context, Y3, Y3, r);
    sm2_fp_mul_common(context, V, S1, J); // use V as tmp
    sm2_fp_dbl_common(context, V, V);
    sm2_fp_sub_common(context, Y3, Y3, V);
    // Z3 = ((Z1+Z2)^2-Z1Z1-Z2Z2)*H
    sm2_fp_add_common(context, Z3, Z1, Z2);
    sm2_fp_sqr_common(context, Z3, Z3);
    sm2_fp_sub_common(context, Z3, Z3, Z1Z1);
    sm2_fp_sub_common(context, Z3, Z3, Z2Z2);
    sm2_fp_mul_common(context, Z3, Z3, H);
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

static void sm2_ec_j_add_a_common(const void*    context,
                                  sm2_ec_j       R,
                                  const sm2_ec_j P,
                                  const sm2_ec_a Q) noexcept
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

    sm2_fp_sqr_common(context, Z1Z1, Z1);     // Z1Z1 = Z1^2
    sm2_fp_mul_common(context, U2, X2, Z1Z1); //  U2 = X2*Z1Z1
    sm2_fp_mul_common(context, S2, Y2, Z1);
    sm2_fp_mul_common(context, S2, S2, Z1Z1); //  S2 = Y2*Z1*Z1Z1
    sm2_fp_sub_common(context, H, U2, X1);    // H = U2-X1
    sm2_fp_sqr_common(context, HH, H);        // HH = H^2
    sm2_fp_dbl_common(context, I, HH);
    sm2_fp_dbl_common(context, I, I);    // I = 4*HH
    sm2_fp_mul_common(context, J, H, I); // J = H*I
    sm2_fp_sub_common(context, r, S2, Y1);
    sm2_fp_dbl_common(context, r, r);     // r = 2*(S2-Y1)
    sm2_fp_mul_common(context, V, X1, I); // V = X1*I
    // X3 = r^2-J-2*V
    sm2_fp_sqr_common(context, X3, r);
    sm2_fp_sub_common(context, X3, X3, J);
    sm2_fp_sub_common(context, X3, X3, V);
    sm2_fp_sub_common(context, X3, X3, V);
    // Y3 = r*(V-X3)-2*Y1*J
    sm2_fp_sub_common(context, V, V, X3);
    sm2_fp_mul_common(context, V, r, V);
    sm2_fp_mul_common(context, Y3, Y1, J);
    sm2_fp_dbl_common(context, Y3, Y3);
    sm2_fp_sub_common(context, Y3, V, Y3);
    // Z3 = (Z1+H)^2-Z1Z1-HH
    sm2_fp_add_common(context, Z3, Z1, H);
    sm2_fp_sqr_common(context, Z3, Z3);
    sm2_fp_sub_common(context, Z3, Z3, Z1Z1);
    sm2_fp_sub_common(context, Z3, Z3, HH);

#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef X3
#undef Y3
#undef Z3
}

static void sm2_ec_j_dbl_common(const void*    context,
                                sm2_ec_j       R,
                                const sm2_ec_j P) noexcept
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
    sm2_fp_sqr_common(context, delta, Z1);
    sm2_fp_sqr_common(context, gamma, Y1);
    // alpha = 3*(X1-delta)*(X1+delta), use 'beta' as tmp
    sm2_fp_sub_common(context, alpha, X1, delta);
    sm2_fp_add_common(context, beta, X1, delta);
    sm2_fp_mul_common(context, alpha, alpha, beta);
    sm2_fp_tpl_common(context, alpha, alpha);
    // beta = X1*gamma
    sm2_fp_mul_common(context, beta, X1, gamma);

    // X3 = alpha^2-8*beta
    sm2_fp_sqr_common(context, X3, alpha);
    sm2_fp_dbl_common(context, beta, beta);
    sm2_fp_dbl_common(context, beta, beta);
    sm2_fp_sub_common(context, X3, X3, beta);
    sm2_fp_sub_common(context, X3, X3, beta);
    // Z3 = (Y1+Z1)^2-gamma-delta
    sm2_fp_add_common(context, Z3, Y1, Z1);
    sm2_fp_sqr_common(context, Z3, Z3);
    sm2_fp_sub_common(context, Z3, Z3, gamma);
    sm2_fp_sub_common(context, Z3, Z3, delta);
    // Y3 = alpha*(4*beta-X3)-8*gamma^2
    sm2_fp_sub_common(context, Y3, beta, X3);
    sm2_fp_mul_common(context, Y3, Y3, alpha);
    sm2_fp_dbl_common(context, gamma, gamma);
    sm2_fp_sqr_common(context, gamma, gamma);
    sm2_fp_dbl_common(context, gamma, gamma);
    sm2_fp_sub_common(context, Y3, Y3, gamma);

#undef X1
#undef Y1
#undef Z1
#undef X3
#undef Y3
#undef Z3
}

static void sm2_ec_j_mul_a_common(const void*        context,
                                  sm2_ec_j           R,
                                  const std::uint8_t k[32],
                                  const sm2_ec_a     P) noexcept
{
    const auto* ctx = static_cast<const SM2P256V1CommonContext*>(context);
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_from_bytes != nullptr);
    assert(provider->uint256_cmp != nullptr);
    assert(provider->uint256_sub_borrow != nullptr);
    assert(provider->uint256_equal_zero != nullptr);
    assert(provider->uint256_tpl_carry != nullptr);
    assert(provider->uint256_bittest != nullptr);
    // number::uint256_t e;
    // provider->uint256_from_bytes(e, k);
    // if (provider->uint256_cmp(e, N.v) >= 0)
    // {
    //     provider->uint256_sub_borrow(e, e,
    //     N.v);
    // }
    // if (provider->uint256_equal_zero(e))
    // {
    //     sm2_ec_j_set_inf_common(context, R);
    //     return;
    // }
    // int i = 255;
    // while (!provider->uint256_bittest(e, i))
    // i--; sm2_ec_j T; sm2_ec_j_from_a_common(context, T, P); i--; for (; i >=
    // 0; i--)
    // {
    //     sm2_ec_j_dbl_common(context, T, T);
    //     if (provider->uint256_bittest(e, i))
    //     {
    //         sm2_ec_j_add_a_common(context, T, T, P);
    //     }
    // }
    // sm2_ec_j_cpy_common(context, R, T);

    // add-sub method
    const std::uint8_t* N = ctx->n;
    number::uint256_t   e, e3;
    provider->uint256_from_bytes(e, k);
    if (provider->uint256_cmp(e, N) >= 0)
    {
        provider->uint256_sub_borrow(e, e, N);
    }
    if (provider->uint256_equal_zero(e))
    {
        sm2_ec_j_set_inf_common(context, R);
        return;
    }
    sm2_ec_j T;
    sm2_ec_a P_neg;
    int      i;
    int      c = provider->uint256_tpl_carry(e3, e);
    sm2_ec_j_from_a_common(context, T, P);
    sm2_ec_a_neg_common(context, P_neg, P);
    if (c == 1)
    {
        i = 255;
    }
    else if (c == 2)
    {
        i = 255;
        sm2_ec_j_dbl_common(context, T, T);
    }
    else // c=0
    {
        i = 255;
        while (!provider->uint256_bittest(e3, i)) i--;
        i--;
    }
    for (; i >= 1; i--)
    {
        sm2_ec_j_dbl_common(context, T, T);
        int ei  = provider->uint256_bittest(e, i) ? 1 : 0;
        int e3i = provider->uint256_bittest(e3, i) ? 1 : 0;
        if (e3i == 1 && ei == 0)
        {
            sm2_ec_j_add_a_common(context, T, T, P);
        }
        else if (e3i == 0 && ei == 1)
        {
            sm2_ec_j_add_a_common(context, T, T, P_neg);
        }
    }
    sm2_ec_j_cpy_common(context, R, T);
}

static void sm2_ec_j_mul_g_common(const void*        context,
                                  sm2_ec_j           R,
                                  const std::uint8_t k[32]) noexcept
{
    // sm2_ec_a G;
    // sm2_fp_from_bytes_common(context, G[0], SM2_CURVE_GX);
    // sm2_fp_from_bytes_common(context, G[1], SM2_CURVE_GY);
    // sm2_ec_j_mul_a_common(context, R, k, G);

    // lut optimize
    int i = 0;
    while (i < 32 && k[i] == 0) i++;
    if (i == 32)
    {
        sm2_ec_j_set_inf_common(context, R);
        return;
    }
    sm2_ec_a T;
    sm2_ec_a_from_bytes04_common(context, T, &SM2_P256V1_TB[i][k[i]][0][0]);
    sm2_ec_j_from_a_common(context, R, T);
    i++;
    for (; i < 32; i++)
    {
        if (k[i] != 0)
        {
            sm2_ec_a_from_bytes04_common(context, T,
                                         &SM2_P256V1_TB[i][k[i]][0][0]);
            sm2_ec_j_add_a_common(context, R, R, T);
        }
    }
}

static void sm2_ec_j_from_a_common(const void*    context,
                                   sm2_ec_j       R,
                                   const sm2_ec_a P) noexcept
{
    sm2_fp_cpy_common(context, R[0], P[0]);
    sm2_fp_cpy_common(context, R[1], P[1]);
    sm2_fp_set_one_common(context, R[2]);
}

static void sm2_ec_j_to_a_common(const void*    context,
                                 sm2_ec_a       R,
                                 const sm2_ec_j P) noexcept
{
    // x = X/Z^2, y = Y/Z^3
    sm2_fp_t inv2, inv3;
    sm2_fp_inv_common(context, inv3, P[2]);
    sm2_fp_sqr_common(context, inv2, inv3);
    sm2_fp_mul_common(context, inv3, inv3, inv2);
    sm2_fp_mul_common(context, R[0], P[0], inv2);
    sm2_fp_mul_common(context, R[1], P[1], inv3);
}

static void sm2_ec_j_normal_common(const void*    context,
                                   sm2_ec_j       R,
                                   const sm2_ec_j P) noexcept
{
    if (sm2_ec_j_is_inf_common(context, P))
    {
        sm2_ec_j_set_inf_common(context, R);
        return;
    }
    // x = X/Z^2, y = Y/Z^3
    sm2_fp_t inv2, inv3;
    sm2_fp_inv_common(context, inv3, P[2]);
    sm2_fp_sqr_common(context, inv2, inv3);
    sm2_fp_mul_common(context, inv3, inv3, inv2);
    sm2_fp_mul_common(context, R[0], P[0], inv2);
    sm2_fp_mul_common(context, R[1], P[1], inv3);
    sm2_fp_set_one_common(context, R[2]);
}

static bool sm2_ec_j_equal_common(const void*    context,
                                  const sm2_ec_j P,
                                  const sm2_ec_j Q) noexcept
{
    // Xp * Zq^2 = Xq * Zp^2
    // Yp * Zq^3 = Yq * Zp^3
    sm2_fp_t Zq2, Zq3, Zp2, Zp3, t1, t2;
    sm2_fp_sqr_common(context, Zp2, P[2]);
    sm2_fp_mul_common(context, Zp3, Zp2, P[2]);
    sm2_fp_sqr_common(context, Zq2, Q[2]);
    sm2_fp_mul_common(context, Zq3, Zq2, Q[2]);
    sm2_fp_mul_common(context, t1, P[0], Zq2);
    sm2_fp_mul_common(context, t2, Q[0], Zp2);
    if (!sm2_fp_equal_common(context, t1, t2))
    {
        return false;
    }
    sm2_fp_mul_common(context, t1, P[1], Zq3);
    sm2_fp_mul_common(context, t2, Q[1], Zp3);
    if (!sm2_fp_equal_common(context, t1, t2))
    {
        return false;
    }
    return true;
}

class CommonBackendBundle
{
public:
    static const CommonBackendBundle& instance() noexcept
    {
        static const CommonBackendBundle bundle;
        return bundle;
    }

    SM2P256V1CommonContext context;
    SM2P256V1Provider      provider;

private:
    CommonBackendBundle() noexcept
        : context(),
          provider{
              []() noexcept { return true; },
              "common",
              &context,
              sm2_bn_cmp_common,
              sm2_bn_cpy_common,
              sm2_bn_equal_zero_common,
              sm2_bn_add_uint32_common,
              sm2_bn_mod_n_sub1_common,
              sm2_bn_mod_n_sub2_common,
              sm2_bn_from_bytes_common,
              sm2_bn_to_bytes_common,
              sm2_fp_add_common,
              sm2_fp_dbl_common,
              sm2_fp_tpl_common,
              sm2_fp_sub_common,
              sm2_fp_mul_common,
              sm2_fp_sqr_common,
              sm2_fp_neg_common,
              sm2_fp_sqrt_common,
              sm2_fp_inv_common,
              sm2_fp_equal_common,
              sm2_fp_equal_zero_common,
              sm2_fp_equal_one_common,
              sm2_fp_cpy_common,
              sm2_fp_set_zero_common,
              sm2_fp_set_one_common,
              sm2_fp_from_bytes_common,
              sm2_fp_to_bytes_common,
              sm2_fn_add_common,
              sm2_fn_sub_common,
              sm2_fn_mul_common,
              sm2_fn_sqr_common,
              sm2_fn_inv_common,
              sm2_fn_equal_common,
              sm2_fn_equal_zero_common,
              sm2_fn_equal_one_common,
              sm2_fn_cpy_common,
              sm2_fn_set_zero_common,
              sm2_fn_set_one_common,
              sm2_fn_from_bytes_common,
              sm2_fn_from_bytes_ex_common,
              sm2_fn_to_bytes_common,
              sm2_fp_to_bn_common,
              sm2_fp_from_bn_common,
              sm2_fn_to_bn_common,
              sm2_fn_from_bn_common,
              sm2_fn_from_fp_common,
              sm2_fn_to_fp_common,
              sm2_ec_a_cpy_common,
              sm2_ec_a_check_common,
              sm2_ec_a_neg_common,
              sm2_ec_a_to_bytes04_common,
              sm2_ec_a_from_bytes04_common,
              sm2_ec_a_to_bytes_uncompressed_common,
              sm2_ec_a_to_bytes_compressed_common,
              sm2_ec_a_to_bytes_mix_common,
              sm2_ec_a_from_bytes_common,
              sm2_ec_j_cpy_common,
              sm2_ec_j_is_inf_common,
              sm2_ec_j_set_inf_common,
              sm2_ec_j_neg_common,
              sm2_ec_j_add_common,
              sm2_ec_j_add_a_common,
              sm2_ec_j_dbl_common,
              sm2_ec_j_mul_a_common,
              sm2_ec_j_mul_g_common,
              sm2_ec_j_from_a_common,
              sm2_ec_j_to_a_common,
              sm2_ec_j_normal_common,
              sm2_ec_j_equal_common,
          }
    {
    }
};

static const SM2P256V1Provider* find_provider(const char* impl) noexcept
{
    const auto* provider = &CommonBackendBundle::instance().provider;
    if (provider->available() &&
        (impl == nullptr || std::strcmp(provider->algo_name, impl) == 0))
    {
        return provider;
    }
    return nullptr;
}

const SM2P256V1Provider* get_provider(const char* impl) noexcept
{
    if (impl == nullptr)
    {
        static const SM2P256V1Provider* provider = find_provider(nullptr);
        return provider;
    }
    return find_provider(impl);
}

} // namespace sm2::internal
