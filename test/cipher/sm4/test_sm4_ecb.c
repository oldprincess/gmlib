#include <gmlib/cipher/sm4.h>
#include <gmlib/err.h>
#include <memory.h>
#include <stdlib.h>

static uint8_t key[SM4_KEYLEN] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  //
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  //
};

// 测试点1

static uint8_t plaintext1[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  //
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  //
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  //
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  //
};

static uint8_t ciphertext1[] = {
    0x68, 0x1E, 0xDF, 0x34, 0xD2, 0x06, 0x96, 0x5E,  //
    0x86, 0xB3, 0xE9, 0x4F, 0x53, 0x6E, 0x42, 0x46,  //
    0x68, 0x1E, 0xDF, 0x34, 0xD2, 0x06, 0x96, 0x5E,  //
    0x86, 0xB3, 0xE9, 0x4F, 0x53, 0x6E, 0x42, 0x46,  //
    0x00, 0x2A, 0x8A, 0x4E, 0xFA, 0x86, 0x3C, 0xCA,  //
    0xD0, 0x24, 0xAC, 0x03, 0x00, 0xBB, 0x40, 0xD2,  //
};

// 测试点2

static uint8_t plaintext2[SM4_BLOCK_SIZE - 2] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  //
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54,              //
};

static uint8_t ciphertext2[SM4_BLOCK_SIZE] = {
    0x74, 0xD9, 0x3B, 0xED, 0x35, 0xB5, 0x42, 0xBB,  //
    0x77, 0xD0, 0x21, 0x82, 0xB1, 0x86, 0x51, 0x25,  //
};

// 测试点3

static uint8_t plaintext3_1[] = {
    0x01, 0x23, 0x45,  //
};

static uint8_t plaintext3_2[] = {
    0x67, 0x89, 0xAB, 0xCD, 0xEF,                    //
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  //
};

static uint8_t ciphertext3[] = {
    0x68, 0x1E, 0xDF, 0x34, 0xD2, 0x06, 0x96, 0x5E,  //
    0x86, 0xB3, 0xE9, 0x4F, 0x53, 0x6E, 0x42, 0x46,  //
    0x00, 0x2A, 0x8A, 0x4E, 0xFA, 0x86, 0x3C, 0xCA,  //
    0xD0, 0x24, 0xAC, 0x03, 0x00, 0xBB, 0x40, 0xD2,  //
};

// 测试点4

static uint8_t plaintext4[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  //
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  //
};

static uint8_t ciphertext4_1[] = {
    0x68, 0x1E, 0xDF, 0x34, 0xD2, 0x06, 0x96, 0x5E,  //
    0x86, 0xB3, 0xE9, 0x4F, 0x53, 0x6E, 0x42, 0x46,  //
    0x00, 0x2A,                                      //
};

static uint8_t ciphertext4_2[] = {
    0x8A, 0x4E, 0xFA, 0x86, 0x3C, 0xCA,              //
    0xD0, 0x24, 0xAC, 0x03, 0x00, 0xBB, 0x40, 0xD2,  //
};

void test_sm4_ecb() {
    SM4_ECB_CTX ctx;
    sm4_ecb_init(key, &ctx);
    static uint8_t out[SM4_BLOCK_SIZE * 4];
    int outl = 0;
    uint8_t* outptr = NULL;
    // 测试点1
    sm4_ecb_reset(&ctx);  // reset
    outptr = out;
    sm4_ecb_encrypt_update(outptr, &outl, plaintext1, sizeof(plaintext1), &ctx);
    outptr += outl;
    sm4_ecb_encrypt_final(outptr, &outl, &ctx);
    outptr += outl;
    if (memcmp(out, ciphertext1, sizeof(ciphertext1)) != 0 ||
        sizeof(ciphertext1) != outptr - out) {
        ERR_LOG("Err in sm4_ecb");
        goto error;
    }

    sm4_ecb_reset(&ctx);  // reset
    outptr = out;
    sm4_ecb_decrypt_update(outptr, &outl,                     // output
                           ciphertext1, sizeof(ciphertext1),  // ciphertext
                           &ctx);
    outptr += outl;
    sm4_ecb_decrypt_final(outptr, &outl, &ctx);
    outptr += outl;
    if (memcmp(out, plaintext1, sizeof(plaintext1)) != 0 ||
        sizeof(plaintext1) != outptr - out) {
        ERR_LOG("Err in sm4_ecb");
        goto error;
    }

    // 测试点2
    sm4_ecb_reset(&ctx);
    outptr = out;
    sm4_ecb_encrypt_update(outptr, &outl, plaintext2, sizeof(plaintext2), &ctx);
    outptr += outl;
    sm4_ecb_encrypt_final(outptr, &outl, &ctx);
    outptr += outl;
    if (memcmp(out, ciphertext2, sizeof(ciphertext2)) != 0 ||
        sizeof(ciphertext2) != outptr - out) {
        ERR_LOG("Err in sm4_ecb");
        goto error;
    }

    sm4_ecb_reset(&ctx);  // reset
    outptr = out;
    sm4_ecb_decrypt_update(outptr, &outl,                     // output
                           ciphertext2, sizeof(ciphertext2),  // ciphertext
                           &ctx);
    outptr += outl;
    sm4_ecb_decrypt_final(outptr, &outl, &ctx);
    outptr += outl;
    if (memcmp(out, plaintext2, sizeof(plaintext2)) != 0 ||
        sizeof(plaintext2) != outptr - out) {
        ERR_LOG("Err in sm4_ecb");
        goto error;
    }
    // 测试点3
    sm4_ecb_reset(&ctx);
    outptr = out;
    sm4_ecb_encrypt_update(outptr, &outl, plaintext3_1, sizeof(plaintext3_1),
                           &ctx);
    outptr += outl;
    sm4_ecb_encrypt_update(outptr, &outl, plaintext3_2, sizeof(plaintext3_2),
                           &ctx);
    outptr += outl;
    sm4_ecb_encrypt_final(outptr, &outl, &ctx);
    outptr += outl;
    if (memcmp(out, ciphertext3, sizeof(ciphertext3)) != 0 ||
        sizeof(ciphertext3) != outptr - out) {
        ERR_LOG("Err in sm4_ecb");
        goto error;
    }
    // 测试点4
    sm4_ecb_reset(&ctx);  // reset
    outptr = out;
    sm4_ecb_decrypt_update(outptr, &outl,                         // output
                           ciphertext4_1, sizeof(ciphertext4_1),  // ciphertext
                           &ctx);
    outptr += outl;
    sm4_ecb_decrypt_update(outptr, &outl,                         // output
                           ciphertext4_2, sizeof(ciphertext4_2),  // ciphertext
                           &ctx);
    outptr += outl;
    sm4_ecb_decrypt_final(outptr, &outl, &ctx);
    outptr += outl;
    if (memcmp(out, plaintext4, sizeof(plaintext4)) != 0 ||
        sizeof(plaintext4) != outptr - out) {
        ERR_LOG("Err in sm4_ecb");
        goto error;
    }

    return;
error:
    exit(-1);
}
