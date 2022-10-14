#include <gmlib/err.h>
#include <gmlib/math.h>
#include <gmlib/publickey/sm2.h>
#include "sm2_alg.h"

/// @brief SM2 签名初始化
int sm2_sign_init(uint8_t* ENTL,
                  uint8_t* ID,
                  EC_CTX* ec_ctx,
                  BINT* da,
                  ECPoint* P,
                  SM2_SIGN_CTX* sm2_sign_ctx) {
    SM2_SIGN_CTX* ctx = sm2_sign_ctx;
    // 拷贝参数
    ctx->ec_ctx = ec_ctx;
    bint_copy(&ctx->da, da);

    // 预计算数据 (da+1)^-1
    BINT da_plus_1;
    try_goto(bint_add(&da_plus_1, da, &BINT_ONE));
    try_goto(fp_inverse(&ctx->da_plus_1_iv, &da_plus_1, &ec_ctx->n));

    // 计算标识符Z
    try_goto(sm2_calculate_z(ctx->Z, ENTL, ID, P, ec_ctx));

    // 初始化 H(Z || ...)
    sm3_init(&ctx->sm3_ctx);
    sm3_update(ctx->Z, SM3_DIGEST_SIZE, &ctx->sm3_ctx);

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief SM2 签名Update
void sm2_sign_update(uint8_t* in, int inl, SM2_SIGN_CTX* sm2_sign_ctx) {
    sm3_update(in, inl, &sm2_sign_ctx->sm3_ctx);
}

/// @brief SM2 签名Final
int sm2_sign_final(uint8_t* out, int* outl, SM2_SIGN_CTX* sm2_sign_ctx) {
    uint8_t digest[SM3_DIGEST_SIZE];
    BINT e, k, r, t;
    ECPoint point;
    EC_CTX* ec_ctx = sm2_sign_ctx->ec_ctx;
    BINT* da = &sm2_sign_ctx->da;
    BINT* da_plus_1_iv = &sm2_sign_ctx->da_plus_1_iv;
    // e = H(Z || msg)
    sm3_final(digest, &sm2_sign_ctx->sm3_ctx);
    try_goto(bint_from_bytes(&e, digest, SM3_DIGEST_SIZE, BINT_BIG_ENDIAN));

start:
    // k = range[1, n)
    try_goto(bint_rand_range(&k, &BINT_ONE, &ec_ctx->n));

#ifdef GMLIB_TEST
    // 构造TEST数据的k
    // 59276E27_D506861A_16680F3A_D9C02DCC_EF3CC1FA_3CDBE4CE_6D54B80D_EAC1BC21
    try_goto(bint_from_str(&k,
                           "59276E27_D506861A_16680F3A_D9C02DCC_EF3CC1FA_"
                           "3CDBE4CE_6D54B80D_EAC1BC21",
                           16));
#endif

    // (x1, y1) = [k]G
    try_goto(ec_mul(&point, &k, &ec_ctx->G, ec_ctx));
    // r = (e+x1) % EC.n
    try_goto(fp_add(&r, &e, &point.x, &ec_ctx->n));
    // r=0 or r+k=n
    if (bint_is_zero(&r)) {
        goto start;
    }
    try_goto(bint_add(&t, &r, &k));
    if (bint_cmp(&t, &ec_ctx->n) == 0) {
        goto start;
    }
    // s = (1+da)^-1 * (k - r*da) % EC.n
    try_goto(fp_mul(&t, &r, da, &ec_ctx->n));            // r*da
    try_goto(fp_sub(&t, &k, &t, &ec_ctx->n));            // k - r*da
    try_goto(fp_mul(&t, da_plus_1_iv, &t, &ec_ctx->n));  // s
    if (bint_is_zero(&t)) {
        goto start;
    }

    // output (s, r)
    int bsize = bint_bytes_len(&ec_ctx->p);
    try_goto(bint_to_bytes(&r, out, bsize, BINT_BIG_ENDIAN));
    try_goto(bint_to_bytes(&t, out + bsize, bsize, BINT_BIG_ENDIAN));
    *outl = 2 * bsize;

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
