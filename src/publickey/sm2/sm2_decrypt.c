#include <gmlib/err.h>
#include <gmlib/publickey/sm2.h>
#include <gmlib/utils.h>
#include <memory.h>
#include "sm2_alg.h"

int sm2_decrypt(uint8_t* out,
                int* outl,
                uint8_t* in,
                int inl,
                EC_CTX* ec_ctx,
                BINT* da) {
    ECPoint dot;
    int size = bint_bytes_len(&ec_ctx->p);
    int output_len;
    *outl = 0;
    uint8_t *C1 = in, *C3 = NULL;
    // 加载C1并校验是否在曲线上
    try_goto(ec_from_bytes(&dot, C1, &output_len, ec_ctx));
    in += output_len, inl -= output_len;
    C3 = C1 + output_len;
    in += SM2_CRYPT_C3_SIZE, inl -= SM2_CRYPT_C3_SIZE;

    // 忽略校验 [h]C1!=O
    // (x2,y2)=[da]C1
    try_goto(ec_mul(&dot, da, &dot, ec_ctx));
    uint8_t x2[GMLIB_BINT_BITS / 8], y2[GMLIB_BINT_BITS / 8];
    try_goto(bint_to_bytes(&dot.x, x2, size, BINT_BIG_ENDIAN));
    try_goto(bint_to_bytes(&dot.y, y2, size, BINT_BIG_ENDIAN));

    // 初始化 kdf H(x2||y2||...
    SM2_KDF_CTX kdf;
    sm2_kdf_init(&kdf);
    sm2_kdf_init_update(x2, size, &kdf);
    sm2_kdf_init_update(y2, size, &kdf);

    // 初始化 SM3 = H(x2||...
    SM3_CTX sm3_ctx;
    sm3_init(&sm3_ctx);
    sm3_update(x2, size, &sm3_ctx);

    // 解密
    uint8_t key_stream[SM3_DIGEST_SIZE];
    uint8_t* optr = out;  // 缓存输出指针首地址
    while (inl) {
        int size = SM3_DIGEST_SIZE;
        if (size > inl) {
            size = inl;
        }
        sm2_kdf_next(key_stream, &kdf);
        memxor(out, in, key_stream, size);
        out += size, *outl += size;
        in += size, inl -= size;
    }

    // 计算C3
    uint8_t digest[SM3_DIGEST_SIZE];
    sm3_update(optr, *outl, &sm3_ctx);
    sm3_update(y2, size, &sm3_ctx);
    sm3_final(digest, &sm3_ctx);

    // 判断msg是否被篡改
    if (memcmp(digest, C3, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("SM2 message corruption");
        goto error;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
