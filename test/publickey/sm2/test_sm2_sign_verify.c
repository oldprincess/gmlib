#include <gmlib/err.h>
#include <gmlib/publickey/sm2.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdlib.h>

static uint8_t ID_A[] = {
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  //
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  //
};

static uint8_t ENTL_A[] = {0x00, 0x80};

static char* da_hex =
    "3945208F_7B2144B1_3F36E38A_C6D39F95_88939369_2860B51A_42FB81EF_4DF7C5B8";

// message digest
static uint8_t msg[] = {
    'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 'd', 'i', 'g', 'e', 's', 't',
};

// signature=(r,s)
static uint8_t signature[] = {
    // r
    0xf5, 0xa0, 0x3b, 0x06, 0x48, 0xd2, 0xc4, 0x63,  //
    0x0e, 0xea, 0xc5, 0x13, 0xe1, 0xbb, 0x81, 0xa1,  //
    0x59, 0x44, 0xda, 0x38, 0x27, 0xd5, 0xb7, 0x41,  //
    0x43, 0xac, 0x7e, 0xac, 0xee, 0xe7, 0x20, 0xb3,  //

    // s
    0xb1, 0xb6, 0xaa, 0x29, 0xdf, 0x21, 0x2f, 0xd8,  //
    0x76, 0x31, 0x82, 0xbc, 0x0d, 0x42, 0x1c, 0xa1,  //
    0xbb, 0x90, 0x38, 0xfd, 0x1f, 0x7f, 0x42, 0xd4,  //
    0x84, 0x0b, 0x69, 0xc4, 0x85, 0xbb, 0xc1, 0xaa,  //
};

static uint8_t out[2 * (GMLIB_BINT_BITS / 8)];
static int outl;

void test_sm2_sign_verify() {
    BINT da;
    ECPoint P;
    try_goto(bint_from_str(&da, da_hex, 16));  // load da
    // P = [da]G
    try_goto(ec_mul(&P, &da, &SM2_Fp256_CTX.G, &SM2_Fp256_CTX));

    // test sm2 sign
    SM2_SIGN_CTX sm2_sign_ctx;
    try_goto(
        sm2_sign_init(ENTL_A, ID_A, &SM2_Fp256_CTX, &da, &P, &sm2_sign_ctx));
    sm2_sign_reset(&sm2_sign_ctx);
    sm2_sign_update(msg, sizeof(msg), &sm2_sign_ctx);
    try_goto(sm2_sign_final(out, &outl, &sm2_sign_ctx));
    if (outl != sizeof(signature) || memcmp(out, signature, outl) != 0) {
        ERR_LOG("Err in sm2_sign");
        goto error;
    }

    // test sm2 verify
    SM2_VERIFY_CTX sm2_verify_ctx;
    int status = 0;
    try_goto(
        sm2_verify_init(ENTL_A, ID_A, &SM2_Fp256_CTX, &P, &sm2_verify_ctx));
    sm2_verify_reset(&sm2_verify_ctx);
    sm2_verify_update(msg, sizeof(msg), &sm2_verify_ctx);
    try_goto(sm2_verify_final(&status, out, &sm2_verify_ctx));
    if (status != 1) {
        ERR_LOG("Err in sm2_verify");
        goto error;
    }

    // 随机签名验签测试
    for (int i = 0; i < 30; i++) {
        sm2_sign_reset(&sm2_sign_ctx);
        sm2_verify_reset(&sm2_verify_ctx);
        static uint8_t random_msg[512];
        rand_mem(random_msg, sizeof(random_msg));
        // 签名
        sm2_sign_update(random_msg, sizeof(random_msg), &sm2_sign_ctx);
        try_goto(sm2_sign_final(out, &outl, &sm2_sign_ctx));
        // 验签
        sm2_verify_update(random_msg, sizeof(random_msg), &sm2_verify_ctx);
        try_goto(sm2_verify_final(&status, out, &sm2_verify_ctx));
        if (status != 1) {
            ERR_LOG("Err in sm2");
            goto error;
        }
    }

    return;
error:
    exit(-1);
}
