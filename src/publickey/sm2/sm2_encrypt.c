#include <gmlib/err.h>
#include <gmlib/math.h>
#include <gmlib/publickey/sm2.h>
#include <gmlib/utils.h>
#include "sm2_alg.h"

int sm2_encrypt(uint8_t* out,
                int* outl,
                uint8_t* in,
                int inl,
                int PC,
                EC_CTX* ec_ctx,
                ECPoint* P) {
    ECPoint dot;
    BINT k;
    int size = bint_bytes_len(&ec_ctx->p);
    uint8_t *C1 = out, *C3 = NULL;
    int output_len;
    *outl = 0;

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
    try_goto(ec_to_bytes(&dot, PC, C1, &output_len, ec_ctx));
    *outl += output_len, out += output_len;
    C3 = C1 + output_len;
    out += SM2_CRYPT_C3_SIZE, *outl += SM2_CRYPT_C3_SIZE;

    // 忽略对余因子 h 的 [k]P!=O 的判断
    // (x2,y2)=[k]P
    try_goto(ec_mul(&dot, &k, P, ec_ctx));
    uint8_t x2[GMLIB_BINT_BITS / 8], y2[GMLIB_BINT_BITS / 8];
    try_goto(bint_to_bytes(&dot.x, x2, size, BINT_BIG_ENDIAN));
    try_goto(bint_to_bytes(&dot.y, y2, size, BINT_BIG_ENDIAN));

    // C3 = H(x2||msg||y2)
    SM3_CTX sm3_ctx;
    sm3_init(&sm3_ctx);
    sm3_update(x2, size, &sm3_ctx);
    sm3_update(in, inl, &sm3_ctx);
    sm3_update(y2, size, &sm3_ctx);
    sm3_final(C3, &sm3_ctx);

    // 初始化 kdf H(x2||y2||...
    SM2_KDF_CTX kdf;
    sm2_kdf_init(&kdf);
    sm2_kdf_init_update(x2, size, &kdf);
    sm2_kdf_init_update(y2, size, &kdf);

    // 加密
    uint8_t key_stream[SM3_DIGEST_SIZE];
    while (inl) {
        int size = SM3_DIGEST_SIZE;
        if (size > inl) {
            size = inl;
        }
        sm2_kdf_next(key_stream, &kdf);
        memxor(out, key_stream, in, size);
        *outl += size, out += size;
        inl -= size;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
