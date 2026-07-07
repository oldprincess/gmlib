#include "sm2p256v1_common.h"

#include <gmlib/sm2/internal/sm2_const.h>

#include <cassert>

#include "sm2_p256v1_tb.inc"

namespace sm2::internal::common {

CommonContext::CommonContext() noexcept
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

// =============================================================================
// BN functions
// =============================================================================

int sm2_bn_cmp(const CommonContext* ctx,
               const std::uint8_t   a[32],
               const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_cmp != nullptr);
    return provider->uint256_cmp(a, b);
}

void sm2_bn_cpy(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_cpy != nullptr);
    provider->uint256_cpy(r, a);
}

bool sm2_bn_equal_zero(const CommonContext* ctx,
                       const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_equal_zero != nullptr);
    return provider->uint256_equal_zero(a);
}

int sm2_bn_add_uint32(const CommonContext* ctx,
                      std::uint8_t         r[32],
                      const std::uint8_t   a[32],
                      std::uint32_t        b) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_add_carry_uint32 != nullptr);
    return provider->uint256_add_carry_uint32(r, a, b);
}

void sm2_bn_mod_n_sub1(const CommonContext* ctx, std::uint8_t a[32]) noexcept
{
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

void sm2_bn_mod_n_sub2(const CommonContext* ctx, std::uint8_t a[32]) noexcept
{
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

void sm2_bn_from_bytes(const CommonContext* ctx,
                       std::uint8_t         r[32],
                       const std::uint8_t   in[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_from_bytes != nullptr);
    provider->uint256_from_bytes(r, in);
}

void sm2_bn_to_bytes(const CommonContext* ctx,
                     std::uint8_t         out[32],
                     const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_to_bytes != nullptr);
    provider->uint256_to_bytes(out, a);
}

// =============================================================================
// FP functions
// =============================================================================

void sm2_fp_add(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_add != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_add(mont_ctx, r, a, b);
}

void sm2_fp_dbl(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_dbl != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_dbl(mont_ctx, r, a);
}

void sm2_fp_tpl(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_tpl != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_tpl(mont_ctx, r, a);
}

void sm2_fp_sub(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sub != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_sub(mont_ctx, r, a, b);
}

void sm2_fp_mul(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_mul != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_mul(mont_ctx, r, a, b);
}

void sm2_fp_sqr(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sqr != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_sqr(mont_ctx, r, a);
}

int sm2_fp_sqrt(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_pow != nullptr);
    assert(provider->mont256_sqr != nullptr);
    assert(provider->mont256_equal != nullptr);
    assert(provider->mont256_cpy != nullptr);
    const auto*  mont_ctx = &ctx->fp_mont_ctx;
    std::uint8_t t[32], t2[32];
    provider->mont256_pow(mont_ctx, t, a, ctx->p_sub3_div4_add1);
    provider->mont256_sqr(mont_ctx, t2, t);
    if (!provider->mont256_equal(mont_ctx, a, t2))
    {
        return -1;
    }
    provider->mont256_cpy(mont_ctx, r, t);
    return 0;
}

void sm2_fp_neg(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_neg != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_neg(mont_ctx, r, a);
}

void sm2_fp_inv(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_inv != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_inv(mont_ctx, r, a);
}

bool sm2_fp_equal(const CommonContext* ctx,
                  const std::uint8_t   a[32],
                  const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    return provider->mont256_equal(mont_ctx, a, b);
}

bool sm2_fp_equal_zero(const CommonContext* ctx,
                       const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_zero != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    return provider->mont256_equal_zero(mont_ctx, a);
}

bool sm2_fp_equal_one(const CommonContext* ctx,
                      const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_one != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    return provider->mont256_equal_one(mont_ctx, a);
}

void sm2_fp_cpy(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_cpy != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_cpy(mont_ctx, r, a);
}

void sm2_fp_set_zero(const CommonContext* ctx, std::uint8_t r[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_zero != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_set_zero(mont_ctx, r);
}

void sm2_fp_set_one(const CommonContext* ctx, std::uint8_t r[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_one != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_set_one(mont_ctx, r);
}

void sm2_fp_from_bytes(const CommonContext* ctx,
                       std::uint8_t         r[32],
                       const std::uint8_t   in[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_from_bytes(mont_ctx, r, in);
}

void sm2_fp_to_bytes(const CommonContext* ctx,
                     std::uint8_t         out[32],
                     const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_to_bytes != nullptr);
    const auto* mont_ctx = &ctx->fp_mont_ctx;
    provider->mont256_to_bytes(mont_ctx, out, a);
}

// =============================================================================
// FN functions
// =============================================================================

void sm2_fn_add(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_add != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_add(mont_ctx, r, a, b);
}

void sm2_fn_sub(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sub != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_sub(mont_ctx, r, a, b);
}

void sm2_fn_mul(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32],
                const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_mul != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_mul(mont_ctx, r, a, b);
}

void sm2_fn_sqr(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_sqr != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_sqr(mont_ctx, r, a);
}

void sm2_fn_inv(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_inv != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_inv(mont_ctx, r, a);
}

bool sm2_fn_equal(const CommonContext* ctx,
                  const std::uint8_t   a[32],
                  const std::uint8_t   b[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    return provider->mont256_equal(mont_ctx, a, b);
}

bool sm2_fn_equal_zero(const CommonContext* ctx,
                       const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_zero != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    return provider->mont256_equal_zero(mont_ctx, a);
}

bool sm2_fn_equal_one(const CommonContext* ctx,
                      const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_equal_one != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    return provider->mont256_equal_one(mont_ctx, a);
}

void sm2_fn_cpy(const CommonContext* ctx,
                std::uint8_t         r[32],
                const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_cpy != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_cpy(mont_ctx, r, a);
}

void sm2_fn_set_zero(const CommonContext* ctx, std::uint8_t r[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_zero != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_set_zero(mont_ctx, r);
}

void sm2_fn_set_one(const CommonContext* ctx, std::uint8_t r[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_set_one != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_set_one(mont_ctx, r);
}

void sm2_fn_from_bytes(const CommonContext* ctx,
                       std::uint8_t         r[32],
                       const std::uint8_t   in[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_from_bytes(mont_ctx, r, in);
}

void sm2_fn_from_bytes_ex(const CommonContext* ctx,
                          std::uint8_t         r[32],
                          const std::uint8_t*  in,
                          std::size_t          inl) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_from_bytes_ex != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_from_bytes_ex(mont_ctx, r, in, inl);
}

void sm2_fn_to_bytes(const CommonContext* ctx,
                     std::uint8_t         out[32],
                     const std::uint8_t   a[32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->mont256_to_bytes != nullptr);
    const auto* mont_ctx = &ctx->fn_mont_ctx;
    provider->mont256_to_bytes(mont_ctx, out, a);
}

// =============================================================================
// Conversions
// =============================================================================

void sm2_fp_to_bn(const CommonContext* ctx,
                  std::uint8_t         r[32],
                  const std::uint8_t   a[32]) noexcept
{
    std::uint8_t buf[32];
    sm2_fp_to_bytes(ctx, buf, a);
    sm2_bn_from_bytes(ctx, r, buf);
}

void sm2_fp_from_bn(const CommonContext* ctx,
                    std::uint8_t         r[32],
                    const std::uint8_t   a[32]) noexcept
{
    std::uint8_t buf[32];
    sm2_bn_to_bytes(ctx, buf, a);
    sm2_fp_from_bytes(ctx, r, buf);
}

void sm2_fn_to_bn(const CommonContext* ctx,
                  std::uint8_t         r[32],
                  const std::uint8_t   a[32]) noexcept
{
    std::uint8_t buf[32];
    sm2_fn_to_bytes(ctx, buf, a);
    sm2_bn_from_bytes(ctx, r, buf);
}

void sm2_fn_from_bn(const CommonContext* ctx,
                    std::uint8_t         r[32],
                    const std::uint8_t   a[32]) noexcept
{
    std::uint8_t buf[32];
    sm2_bn_to_bytes(ctx, buf, a);
    sm2_fn_from_bytes(ctx, r, buf);
}

void sm2_fn_from_fp(const CommonContext* ctx,
                    std::uint8_t         r[32],
                    const std::uint8_t   a[32]) noexcept
{
    std::uint8_t buf[32];
    sm2_fp_to_bytes(ctx, buf, a);
    sm2_fn_from_bytes(ctx, r, buf);
}

void sm2_fn_to_fp(const CommonContext* ctx,
                  std::uint8_t         r[32],
                  const std::uint8_t   a[32]) noexcept
{
    std::uint8_t buf[32];
    sm2_fn_to_bytes(ctx, buf, a);
    sm2_fp_from_bytes(ctx, r, buf);
}

// =============================================================================
// EC affine functions
// =============================================================================

void sm2_ec_a_cpy(const CommonContext* ctx,
                  std::uint8_t         R[2][32],
                  const std::uint8_t   P[2][32]) noexcept
{
    sm2_fp_cpy(ctx, R[0], P[0]);
    sm2_fp_cpy(ctx, R[1], P[1]);
}

bool sm2_ec_a_check(const CommonContext* ctx,
                    const std::uint8_t   P[2][32]) noexcept
{
    // y^2 = x^3 + ax + b
    std::uint8_t left[32], right[32], t[32];
    sm2_fp_sqr(ctx, left, P[1]);
    sm2_fp_from_bytes(ctx, right, SM2_CURVE_B);
    sm2_fp_from_bytes(ctx, t, SM2_CURVE_A);
    sm2_fp_mul(ctx, t, t, P[0]);
    sm2_fp_add(ctx, right, right, t);
    sm2_fp_sqr(ctx, t, P[0]);
    sm2_fp_mul(ctx, t, t, P[0]);
    sm2_fp_add(ctx, right, right, t);
    return sm2_fp_equal(ctx, left, right);
}

void sm2_ec_a_neg(const CommonContext* ctx,
                  std::uint8_t         R[2][32],
                  const std::uint8_t   P[2][32]) noexcept
{
    sm2_fp_cpy(ctx, R[0], P[0]);
    sm2_fp_neg(ctx, R[1], P[1]);
}

void sm2_ec_a_to_bytes04(const CommonContext* ctx,
                         std::uint8_t         out[64],
                         const std::uint8_t   P[2][32]) noexcept
{
    sm2_fp_to_bytes(ctx, out + 0, P[0]);
    sm2_fp_to_bytes(ctx, out + 32, P[1]);
}

void sm2_ec_a_from_bytes04(const CommonContext* ctx,
                           std::uint8_t         R[2][32],
                           const std::uint8_t   in[64]) noexcept
{
    sm2_fp_from_bytes(ctx, R[0], in + 0);
    sm2_fp_from_bytes(ctx, R[1], in + 32);
}

void sm2_ec_a_to_bytes_uncompressed(const CommonContext* ctx,
                                    std::uint8_t         out[65],
                                    const std::uint8_t   P[2][32]) noexcept
{
    out[0] = 0x04;
    sm2_ec_a_to_bytes04(ctx, out + 1, P);
}

void sm2_ec_a_to_bytes_compressed(const CommonContext* ctx,
                                  std::uint8_t         out[33],
                                  const std::uint8_t   P[2][32]) noexcept
{
    sm2_fp_to_bytes(ctx, out + 1, P[1]);
    out[0] = ((out[32] & 1) == 0) ? 0x02 : 0x03;
    sm2_fp_to_bytes(ctx, out + 1, P[0]);
}

void sm2_ec_a_to_bytes_mix(const CommonContext* ctx,
                           std::uint8_t         out[65],
                           const std::uint8_t   P[2][32]) noexcept
{
    sm2_ec_a_to_bytes04(ctx, out + 1, P);
    out[0] = ((out[64] & 1) == 0) ? 0x06 : 0x07;
}

int sm2_ec_recover_y(const CommonContext* ctx,
                     std::uint8_t         y[32],
                     const std::uint8_t   x[32],
                     int                  y_hat) noexcept
{
    // y^2 = x^3 + ax + b
    std::uint8_t y2[32], t[32], buf[32];
    sm2_fp_from_bytes(ctx, y2, SM2_CURVE_B);
    sm2_fp_from_bytes(ctx, t, SM2_CURVE_A);
    sm2_fp_mul(ctx, t, t, x);
    sm2_fp_add(ctx, y2, y2, t);
    sm2_fp_sqr(ctx, t, x);
    sm2_fp_mul(ctx, t, t, x);
    sm2_fp_add(ctx, y2, y2, t);
    if (sm2_fp_sqrt(ctx, y, y2))
    {
        return -1;
    }
    sm2_fp_to_bytes(ctx, buf, y);
    int lsb_y = buf[31] & 1;
    if (lsb_y != y_hat)
    {
        sm2_fp_neg(ctx, y, y);
    }
    return 0;
}

int sm2_ec_a_from_bytes(const CommonContext* ctx,
                        std::uint8_t         R[2][32],
                        std::size_t*         read_n,
                        const std::uint8_t*  in,
                        std::size_t          inl) noexcept
{
    if (inl == 0)
    {
        return -1;
    }
    if (in[0] == 0x04 || in[0] == 0x06 || in[0] == 0x07)
    {
        *read_n = 65;
        sm2_ec_a_from_bytes04(ctx, R, in + 1);
    }
    else if (in[0] == 0x02 || in[0] == 0x03)
    {
        *read_n = 33;
        sm2_fp_from_bytes(ctx, R[0], in + 1);
        int y_hat = in[0] == 0x02 ? 0 : 1;
        if (sm2_ec_recover_y(ctx, R[1], R[0], y_hat))
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return sm2_ec_a_check(ctx, R) ? 0 : -1;
}

// =============================================================================
// EC jacobian functions
// =============================================================================

void sm2_ec_j_cpy(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32]) noexcept
{
    sm2_fp_cpy(ctx, R[0], P[0]);
    sm2_fp_cpy(ctx, R[1], P[1]);
    sm2_fp_cpy(ctx, R[2], P[2]);
}

bool sm2_ec_j_is_inf(const CommonContext* ctx,
                     const std::uint8_t   P[3][32]) noexcept
{
    return sm2_fp_equal_zero(ctx, P[2]);
}

void sm2_ec_j_set_inf(const CommonContext* ctx, std::uint8_t R[3][32]) noexcept
{
    // 1,1,0
    sm2_fp_set_one(ctx, R[0]);
    sm2_fp_set_one(ctx, R[1]);
    sm2_fp_set_zero(ctx, R[2]);
}

void sm2_ec_j_neg(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32]) noexcept
{
    sm2_fp_cpy(ctx, R[0], P[0]);
    sm2_fp_neg(ctx, R[1], P[1]);
    sm2_fp_cpy(ctx, R[2], P[2]);
}

void sm2_ec_j_add(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32],
                  const std::uint8_t   Q[3][32]) noexcept
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

    std::uint8_t Z1Z1[32], Z2Z2[32], U1[32], U2[32], S1[32], S2[32];
    std::uint8_t H[32], I[32], J[32], r[32], V[32];
    sm2_fp_sqr(ctx, Z1Z1, Z1);
    sm2_fp_sqr(ctx, Z2Z2, Z2);
    sm2_fp_mul(ctx, U1, X1, Z2Z2);
    sm2_fp_mul(ctx, U2, X2, Z1Z1);
    sm2_fp_mul(ctx, S1, Y1, Z2);
    sm2_fp_mul(ctx, S1, S1, Z2Z2);
    sm2_fp_mul(ctx, S2, Y2, Z1);
    sm2_fp_mul(ctx, S2, S2, Z1Z1);

    if (sm2_fp_equal(ctx, U1, U2))
    {
        if (sm2_fp_equal(ctx, S1, S2))
        {
            sm2_ec_j_dbl(ctx, R, P);
        }
        else
        {
            sm2_ec_j_set_inf(ctx, R);
        }
        return;
    }

    sm2_fp_sub(ctx, H, U2, U1);
    sm2_fp_dbl(ctx, I, H);
    sm2_fp_sqr(ctx, I, I);
    sm2_fp_mul(ctx, J, H, I);
    sm2_fp_sub(ctx, r, S2, S1);
    sm2_fp_dbl(ctx, r, r);
    sm2_fp_mul(ctx, V, U1, I);

    // X3 = r2-J-2*V
    sm2_fp_sqr(ctx, X3, r);
    sm2_fp_sub(ctx, X3, X3, J);
    sm2_fp_sub(ctx, X3, X3, V);
    sm2_fp_sub(ctx, X3, X3, V);
    // Y3 = r*(V-X3)-2*S1*J
    sm2_fp_sub(ctx, Y3, V, X3);
    sm2_fp_mul(ctx, Y3, Y3, r);
    sm2_fp_mul(ctx, V, S1, J); // use V as tmp
    sm2_fp_dbl(ctx, V, V);
    sm2_fp_sub(ctx, Y3, Y3, V);
    // Z3 = ((Z1+Z2)^2-Z1Z1-Z2Z2)*H
    sm2_fp_add(ctx, Z3, Z1, Z2);
    sm2_fp_sqr(ctx, Z3, Z3);
    sm2_fp_sub(ctx, Z3, Z3, Z1Z1);
    sm2_fp_sub(ctx, Z3, Z3, Z2Z2);
    sm2_fp_mul(ctx, Z3, Z3, H);
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

void sm2_ec_j_add_a(const CommonContext* ctx,
                    std::uint8_t         R[3][32],
                    const std::uint8_t   P[3][32],
                    const std::uint8_t   Q[2][32]) noexcept
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

    std::uint8_t Z1Z1[32], U2[32], S2[32], H[32], HH[32], I[32], J[32], r[32],
        V[32];

    sm2_fp_sqr(ctx, Z1Z1, Z1);     // Z1Z1 = Z1^2
    sm2_fp_mul(ctx, U2, X2, Z1Z1); //  U2 = X2*Z1Z1
    sm2_fp_mul(ctx, S2, Y2, Z1);
    sm2_fp_mul(ctx, S2, S2, Z1Z1); //  S2 = Y2*Z1*Z1Z1
    sm2_fp_sub(ctx, H, U2, X1);    // H = U2-X1
    sm2_fp_sqr(ctx, HH, H);        // HH = H^2
    sm2_fp_dbl(ctx, I, HH);
    sm2_fp_dbl(ctx, I, I);    // I = 4*HH
    sm2_fp_mul(ctx, J, H, I); // J = H*I
    sm2_fp_sub(ctx, r, S2, Y1);
    sm2_fp_dbl(ctx, r, r);     // r = 2*(S2-Y1)
    sm2_fp_mul(ctx, V, X1, I); // V = X1*I
    // X3 = r^2-J-2*V
    sm2_fp_sqr(ctx, X3, r);
    sm2_fp_sub(ctx, X3, X3, J);
    sm2_fp_sub(ctx, X3, X3, V);
    sm2_fp_sub(ctx, X3, X3, V);
    // Y3 = r*(V-X3)-2*Y1*J
    sm2_fp_sub(ctx, V, V, X3);
    sm2_fp_mul(ctx, V, r, V);
    sm2_fp_mul(ctx, Y3, Y1, J);
    sm2_fp_dbl(ctx, Y3, Y3);
    sm2_fp_sub(ctx, Y3, V, Y3);
    // Z3 = (Z1+H)^2-Z1Z1-HH
    sm2_fp_add(ctx, Z3, Z1, H);
    sm2_fp_sqr(ctx, Z3, Z3);
    sm2_fp_sub(ctx, Z3, Z3, Z1Z1);
    sm2_fp_sub(ctx, Z3, Z3, HH);

#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef X3
#undef Y3
#undef Z3
}

void sm2_ec_j_dbl(const CommonContext* ctx,
                  std::uint8_t         R[3][32],
                  const std::uint8_t   P[3][32]) noexcept
{
    // http://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-3.html#doubling-dbl-2001-b
    // Cost: 3M + 5S + 8add + 1*3 + 1*4 + 2*8.
#define X3 R[0]
#define Y3 R[1]
#define Z3 R[2]
#define X1 P[0]
#define Y1 P[1]
#define Z1 P[2]

    std::uint8_t delta[32], gamma[32], beta[32], alpha[32];
    // delta = Z1^2, gamma = Y1^2
    sm2_fp_sqr(ctx, delta, Z1);
    sm2_fp_sqr(ctx, gamma, Y1);
    // alpha = 3*(X1-delta)*(X1+delta), use 'beta' as tmp
    sm2_fp_sub(ctx, alpha, X1, delta);
    sm2_fp_add(ctx, beta, X1, delta);
    sm2_fp_mul(ctx, alpha, alpha, beta);
    sm2_fp_tpl(ctx, alpha, alpha);
    // beta = X1*gamma
    sm2_fp_mul(ctx, beta, X1, gamma);

    // X3 = alpha^2-8*beta
    sm2_fp_sqr(ctx, X3, alpha);
    sm2_fp_dbl(ctx, beta, beta);
    sm2_fp_dbl(ctx, beta, beta);
    sm2_fp_sub(ctx, X3, X3, beta);
    sm2_fp_sub(ctx, X3, X3, beta);
    // Z3 = (Y1+Z1)^2-gamma-delta
    sm2_fp_add(ctx, Z3, Y1, Z1);
    sm2_fp_sqr(ctx, Z3, Z3);
    sm2_fp_sub(ctx, Z3, Z3, gamma);
    sm2_fp_sub(ctx, Z3, Z3, delta);
    // Y3 = alpha*(4*beta-X3)-8*gamma^2
    sm2_fp_sub(ctx, Y3, beta, X3);
    sm2_fp_mul(ctx, Y3, Y3, alpha);
    sm2_fp_dbl(ctx, gamma, gamma);
    sm2_fp_sqr(ctx, gamma, gamma);
    sm2_fp_dbl(ctx, gamma, gamma);
    sm2_fp_sub(ctx, Y3, Y3, gamma);

#undef X1
#undef Y1
#undef Z1
#undef X3
#undef Y3
#undef Z3
}

void sm2_ec_j_mul_a(const CommonContext* ctx,
                    std::uint8_t         R[3][32],
                    const std::uint8_t   k[32],
                    const std::uint8_t   P[2][32]) noexcept
{
    assert(ctx != nullptr);
    const auto* provider = ctx->number_provider;
    assert(provider != nullptr);
    assert(provider->uint256_from_bytes != nullptr);
    assert(provider->uint256_cmp != nullptr);
    assert(provider->uint256_sub_borrow != nullptr);
    assert(provider->uint256_equal_zero != nullptr);
    assert(provider->uint256_tpl_carry != nullptr);
    assert(provider->uint256_bittest != nullptr);

    // add-sub method
    const std::uint8_t* N = ctx->n;
    std::uint8_t        e[32], e3[32];
    std::uint8_t        T[3][32];
    std::uint8_t        P_neg[2][32];
    int                 i;
    provider->uint256_from_bytes(e, k);
    if (provider->uint256_cmp(e, N) >= 0)
    {
        provider->uint256_sub_borrow(e, e, N);
    }
    if (provider->uint256_equal_zero(e))
    {
        sm2_ec_j_set_inf(ctx, R);
        return;
    }
    int c = provider->uint256_tpl_carry(e3, e);
    sm2_ec_j_from_a(ctx, T, P);
    sm2_ec_a_neg(ctx, P_neg, P);
    if (c == 1)
    {
        i = 255;
    }
    else if (c == 2)
    {
        i = 255;
        sm2_ec_j_dbl(ctx, T, T);
    }
    else // c=0
    {
        i = 255;
        while (!provider->uint256_bittest(e3, i)) i--;
        i--;
    }
    for (; i >= 1; i--)
    {
        sm2_ec_j_dbl(ctx, T, T);
        int ei  = provider->uint256_bittest(e, i) ? 1 : 0;
        int e3i = provider->uint256_bittest(e3, i) ? 1 : 0;
        if (e3i == 1 && ei == 0)
        {
            sm2_ec_j_add_a(ctx, T, T, P);
        }
        else if (e3i == 0 && ei == 1)
        {
            sm2_ec_j_add_a(ctx, T, T, P_neg);
        }
    }
    sm2_ec_j_cpy(ctx, R, T);
}

void sm2_ec_j_mul_g(const CommonContext* ctx,
                    std::uint8_t         R[3][32],
                    const std::uint8_t   k[32]) noexcept
{
    // lut optimize
    int i = 0;
    while (i < 32 && k[i] == 0) i++;
    if (i == 32)
    {
        sm2_ec_j_set_inf(ctx, R);
        return;
    }
    std::uint8_t T[2][32];
    sm2_ec_a_from_bytes04(ctx, T, &SM2_P256V1_TB[i][k[i]][0][0]);
    sm2_ec_j_from_a(ctx, R, T);
    i++;
    for (; i < 32; i++)
    {
        if (k[i] != 0)
        {
            sm2_ec_a_from_bytes04(ctx, T, &SM2_P256V1_TB[i][k[i]][0][0]);
            sm2_ec_j_add_a(ctx, R, R, T);
        }
    }
}

void sm2_ec_j_from_a(const CommonContext* ctx,
                     std::uint8_t         R[3][32],
                     const std::uint8_t   P[2][32]) noexcept
{
    sm2_fp_cpy(ctx, R[0], P[0]);
    sm2_fp_cpy(ctx, R[1], P[1]);
    sm2_fp_set_one(ctx, R[2]);
}

void sm2_ec_j_to_a(const CommonContext* ctx,
                   std::uint8_t         R[2][32],
                   const std::uint8_t   P[3][32]) noexcept
{
    // x = X/Z^2, y = Y/Z^3
    std::uint8_t inv2[32], inv3[32];
    sm2_fp_inv(ctx, inv3, P[2]);
    sm2_fp_sqr(ctx, inv2, inv3);
    sm2_fp_mul(ctx, inv3, inv3, inv2);
    sm2_fp_mul(ctx, R[0], P[0], inv2);
    sm2_fp_mul(ctx, R[1], P[1], inv3);
}

void sm2_ec_j_normal(const CommonContext* ctx,
                     std::uint8_t         R[3][32],
                     const std::uint8_t   P[3][32]) noexcept
{
    if (sm2_ec_j_is_inf(ctx, P))
    {
        sm2_ec_j_set_inf(ctx, R);
        return;
    }
    // x = X/Z^2, y = Y/Z^3
    std::uint8_t inv2[32], inv3[32];
    sm2_fp_inv(ctx, inv3, P[2]);
    sm2_fp_sqr(ctx, inv2, inv3);
    sm2_fp_mul(ctx, inv3, inv3, inv2);
    sm2_fp_mul(ctx, R[0], P[0], inv2);
    sm2_fp_mul(ctx, R[1], P[1], inv3);
    sm2_fp_set_one(ctx, R[2]);
}

bool sm2_ec_j_equal(const CommonContext* ctx,
                    const std::uint8_t   P[3][32],
                    const std::uint8_t   Q[3][32]) noexcept
{
    // Xp * Zq^2 = Xq * Zp^2
    // Yp * Zq^3 = Yq * Zp^3
    std::uint8_t Zq2[32], Zq3[32], Zp2[32], Zp3[32], t1[32], t2[32];
    sm2_fp_sqr(ctx, Zp2, P[2]);
    sm2_fp_mul(ctx, Zp3, Zp2, P[2]);
    sm2_fp_sqr(ctx, Zq2, Q[2]);
    sm2_fp_mul(ctx, Zq3, Zq2, Q[2]);
    sm2_fp_mul(ctx, t1, P[0], Zq2);
    sm2_fp_mul(ctx, t2, Q[0], Zp2);
    if (!sm2_fp_equal(ctx, t1, t2))
    {
        return false;
    }
    sm2_fp_mul(ctx, t1, P[1], Zq3);
    sm2_fp_mul(ctx, t2, Q[1], Zp3);
    if (!sm2_fp_equal(ctx, t1, t2))
    {
        return false;
    }
    return true;
}

} // namespace sm2::internal::common
