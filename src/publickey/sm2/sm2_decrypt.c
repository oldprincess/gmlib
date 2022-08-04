#include <gmlib/err.h>
#include <gmlib/publickey/sm2.h>
#include <gmlib/utils.h>
#include <memory.h>
#include "sm2_alg.h"

/// @brief SM2 解密初始化
int sm2_decrypt_init(uint8_t* C1,
                     int* read_size,
                     EC_CTX* ec_ctx,
                     BINT* da,
                     SM2_Crypt_CTX* sm2_crypt_ctx) {
    ECPoint dot;
    int size = bint_bytes_len(&ec_ctx->p);
    // 加载C1并校验是否在曲线上
    try_goto(ec_from_bytes(&dot, C1, read_size, ec_ctx));

    // 忽略校验 [h]C1!=O
    // (x2,y2)=[da]C1
    try_goto(ec_mul(&dot, da, &dot, ec_ctx));
    uint8_t x2[GMLIB_BINT_BITS / 8];
    uint8_t* y2 = sm2_crypt_ctx->dot2.y;
    sm2_crypt_ctx->dot2.bsize = size;
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

/// @brief SM2 解密Update(输出msg)
void sm2_decrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        SM2_Crypt_CTX* sm2_crypt_ctx) {
    SM2_Crypt_CTX* ctx = sm2_crypt_ctx;
    *outl = 0;
    uint8_t* optr = out;  // 保存outptr原始位置
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
    // 更新 SM3 = H(x2||msg
    sm3_update(optr, *outl, &ctx->sm3_ctx);
}

/// @brief SM2 解密Final
int sm2_decrypt_final(uint8_t* C3, SM2_Crypt_CTX* sm2_crypt_ctx) {
    uint8_t digest[SM3_DIGEST_SIZE];
    SM3_CTX* sm3_ctx = &sm2_crypt_ctx->sm3_ctx;

    int size = sm2_crypt_ctx->dot2.bsize;
    // H(x2 || msg || y2)
    sm3_update(sm2_crypt_ctx->dot2.y, size, sm3_ctx);
    sm3_final(digest, sm3_ctx);

    // 判断msg是否被篡改
    if (memcmp(digest, C3, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("SM2 message corruption");
        goto error;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
