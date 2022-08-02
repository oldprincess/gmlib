#include <gmlib/err.h>
#include <gmlib/math.h>
#include <gmlib/publickey/sm2.h>
#include "sm2_alg.h"

/// @brief SM2 验签初始化
int sm2_verify_init(uint8_t* ENTL,
                    uint8_t* ID,
                    EC_CTX* ec_ctx,
                    ECPoint* P,
                    SM2_VERIFY_CTX* sm2_verify_ctx) {
    // 拷贝参数
    ec_ctx_copy(&sm2_verify_ctx->ec_ctx, ec_ctx);
    ec_copy(&sm2_verify_ctx->P, P);

    // 计算标识符Z
    try_goto(sm2_calculate_z(sm2_verify_ctx->Z, ENTL, ID, P, ec_ctx));

    // 初始化 H(Z || ...)
    sm3_init(&sm2_verify_ctx->sm3_ctx);
    sm3_update(sm2_verify_ctx->Z, SM3_DIGEST_SIZE, &sm2_verify_ctx->sm3_ctx);

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief SM2 验签重置
void sm2_verify_reset(SM2_VERIFY_CTX* sm2_verify_ctx) {
    sm3_init(&sm2_verify_ctx->sm3_ctx);
    sm3_update(sm2_verify_ctx->Z, SM3_DIGEST_SIZE, &sm2_verify_ctx->sm3_ctx);
}

/// @brief SM2 验签Update
void sm2_verify_update(uint8_t* in, int inl, SM2_VERIFY_CTX* sm2_verify_ctx) {
    sm3_update(in, inl, &sm2_verify_ctx->sm3_ctx);
}

/// @brief SM2 验签Final
int sm2_verify_final(int* status,
                     uint8_t* signature,
                     SM2_VERIFY_CTX* sm2_verify_ctx) {
    BINT r, s, e, t, R;
    EC_CTX* ec_ctx = &sm2_verify_ctx->ec_ctx;
    ECPoint d1, d2;

    // load (r,s)
    int bsize = bint_bytes_len(&ec_ctx->p);
    uint8_t *r_data = signature, *s_data = signature + bsize;
    try_goto(bint_from_bytes(&r, r_data, bsize, BINT_BIG_ENDIAN));
    try_goto(bint_from_bytes(&s, s_data, bsize, BINT_BIG_ENDIAN));

    // check r, s
    if (!bint_is_pos(&r) || !(bint_cmp(&r, &ec_ctx->n) < 0) ||  // r in [1,n-1]
        !bint_is_pos(&s) || !(bint_cmp(&s, &ec_ctx->n) < 0)     // s in [1,n-1]
    ) {
        ERR_LOG("Err signature data (r,s)");
        goto error;
    }

    // e = H(Z || msg)
    uint8_t digest[SM3_DIGEST_SIZE];
    sm3_final(digest, &sm2_verify_ctx->sm3_ctx);
    try_goto(bint_from_bytes(&e, digest, SM3_DIGEST_SIZE, BINT_BIG_ENDIAN));

    // t = (r+s) % n
    try_goto(fp_add(&t, &r, &s, &ec_ctx->n));

    // (x1,y1) = [s]G+[t]P
    try_goto(ec_mul(&d1, &s, &ec_ctx->G, ec_ctx));
    try_goto(ec_mul(&d2, &t, &sm2_verify_ctx->P, ec_ctx));
    try_goto(ec_add(&d1, &d1, &d2, ec_ctx));

    // R = (e+x1) % n
    try_goto(fp_add(&R, &e, &d1.x, &ec_ctx->n));

    *status = bint_cmp(&r, &R) == 0;

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
