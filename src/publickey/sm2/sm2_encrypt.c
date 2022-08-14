#include <gmlib/err.h>
#include <gmlib/math.h>
#include <gmlib/publickey/sm2.h>
#include <gmlib/utils.h>
#include "sm2_alg.h"

/// @brief SM2 加密初始化(输出C1)
int sm2_encrypt_init(uint8_t* C1,
                     int* outl,
                     int PC,
                     EC_CTX* ec_ctx,
                     ECPoint* P,
                     SM2_CRYPT_CTX* sm2_crypt_ctx) {
    ECPoint dot;
    BINT k;
    int size = bint_bytes_len(&ec_ctx->p);

    // k [1, n-1]
    try_goto(bint_rand_range(&k, &BINT_ONE, &ec_ctx->n));
#ifdef GMLIB_TEST
    // 生成固定随机数k，便于测试
    try_goto(bint_from_str(&k,
                           "59276E27_D506861A_16680F3A_D9C02DCC_EF3CC1FA_"
                           "3CDBE4CE_6D54B80D_EAC1BC21",
                           16));
#endif

    // C1 = [k]G
    try_goto(ec_mul(&dot, &k, &ec_ctx->G, ec_ctx));
    try_goto(ec_to_bytes(&dot, PC, C1, outl, ec_ctx));

    // 忽略对余因子 h 的 [k]P!=O 的判断
    // (x2,y2)=[k]P
    try_goto(ec_mul(&dot, &k, P, ec_ctx));
    sm2_crypt_ctx->dot2.bsize = size;
    uint8_t x2[GMLIB_BINT_BITS / 8];
    uint8_t* y2 = sm2_crypt_ctx->dot2.y;
    try_goto(bint_to_bytes(&dot.x, x2, size, BINT_BIG_ENDIAN));
    try_goto(bint_to_bytes(&dot.y, y2, size, BINT_BIG_ENDIAN));

    // 初始化 kdf H(x2||y2||...
    sm2_kdf_init(&sm2_crypt_ctx->kdf.ctx);
    sm2_kdf_init_update(x2, size, &sm2_crypt_ctx->kdf.ctx);
    sm2_kdf_init_update(y2, size, &sm2_crypt_ctx->kdf.ctx);
    sm2_crypt_ctx->kdf.kpos = SM3_DIGEST_SIZE;

    // 初始化 SM3 = H(x2||...
    sm3_init(&sm2_crypt_ctx->sm3_ctx);
    sm3_update(x2, size, &sm2_crypt_ctx->sm3_ctx);

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief SM2 加密Update(输出C2)
void sm2_encrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        SM2_CRYPT_CTX* sm2_crypt_ctx) {
    SM2_CRYPT_CTX* ctx = sm2_crypt_ctx;
    *outl = 0;
    // 更新 SM3 = H(x2||msg
    sm3_update(in, inl, &ctx->sm3_ctx);
    // 加密
    while (inl) {
        // 生成密钥流
        if (ctx->kdf.kpos == SM3_DIGEST_SIZE) {
            sm2_kdf_next(sm2_crypt_ctx->kdf.key_stream,
                         &sm2_crypt_ctx->kdf.ctx);
            ctx->kdf.kpos = 0;
        }
        // 加密处理数据
        int size = SM3_DIGEST_SIZE - ctx->kdf.kpos;
        if (size > inl) {
            size = inl;
        }
        memxor(out, in, ctx->kdf.key_stream + ctx->kdf.kpos, size);  // xor
        // 更新数据
        inl -= size;
        in += size;
        out += size;
        *outl += size;
        ctx->kdf.kpos += size;
    }
}

/// @brief SM2 加密Final(输出C3)
void sm2_encrypt_final(uint8_t* C3, SM2_CRYPT_CTX* sm2_crypt_ctx) {
    SM3_CTX* sm3_ctx = &sm2_crypt_ctx->sm3_ctx;

    int size = sm2_crypt_ctx->dot2.bsize;
    // H(x2 || msg || y2)
    sm3_update(sm2_crypt_ctx->dot2.y, size, sm3_ctx);
    sm3_final(C3, sm3_ctx);
}
