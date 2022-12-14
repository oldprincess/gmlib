#include <gmlib/err.h>
#include <gmlib/publickey/sm2.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdlib.h>

static char* da_hex =
    "3945208F_7B2144B1_3F36E38A_C6D39F95_88939369_2860B51A_42FB81EF_4DF7C5B8";

// "encryption standard"
static uint8_t msg[] = {'e', 'n', 'c', 'r', 'y', 'p', 't', 'i', 'o', 'n',
                        ' ', 's', 't', 'a', 'n', 'd', 'a', 'r', 'd'};

static uint8_t ciphertext[] = {
    // C1 (04,x1,y1)
    0x04,                                            //
    0x04, 0xeb, 0xfc, 0x71, 0x8e, 0x8d, 0x17, 0x98,  //
    0x62, 0x04, 0x32, 0x26, 0x8e, 0x77, 0xfe, 0xb6,  //
    0x41, 0x5e, 0x2e, 0xde, 0x0e, 0x07, 0x3c, 0x0f,  //
    0x4f, 0x64, 0x0e, 0xcd, 0x2e, 0x14, 0x9a, 0x73,  //

    0xe8, 0x58, 0xf9, 0xd8, 0x1e, 0x54, 0x30, 0xa5,  //
    0x7b, 0x36, 0xda, 0xab, 0x8f, 0x95, 0x0a, 0x3c,  //
    0x64, 0xe6, 0xee, 0x6a, 0x63, 0x09, 0x4d, 0x99,  //
    0x28, 0x3a, 0xff, 0x76, 0x7e, 0x12, 0x4d, 0xf0,  //
    // C3
    0x59, 0x98, 0x3c, 0x18, 0xf8, 0x09, 0xe2, 0x62,  //
    0x92, 0x3c, 0x53, 0xae, 0xc2, 0x95, 0xd3, 0x03,  //
    0x83, 0xb5, 0x4e, 0x39, 0xd6, 0x09, 0xd1, 0x60,  //
    0xaf, 0xcb, 0x19, 0x08, 0xd0, 0xbd, 0x87, 0x66,
    // C2
    0x21, 0x88, 0x6c, 0xa9, 0x89, 0xca, 0x9c, 0x7d,  //
    0x58, 0x08, 0x73, 0x07, 0xca, 0x93, 0x09, 0x2d,  //
    0x65, 0x1e, 0xfa,                                //
};

static uint8_t out[2048];
static int outl;
static int PC = EC_PC_NO_ZIP;

static BINT da;    // 私钥
static ECPoint P;  // 公钥

void test_sm2_crypt() {
    // 初始化双方数据
    try_goto(bint_from_str(&da, da_hex, 16));  // load da
    // P = [da]G
    try_goto(ec_mul(&P, &da, &SM2_Fp256_CTX.G, &SM2_Fp256_CTX));

    // 加密
    try_goto(sm2_encrypt(out, &outl, msg, sizeof(msg), PC, &SM2_Fp256_CTX, &P));
    if (memcmp(out, ciphertext, sizeof(ciphertext)) != 0) {
        ERR_LOG("Err in sm2_crypt");
        goto error;
    }
    // 解密
    try_goto(sm2_decrypt(out, &outl, ciphertext, sizeof(ciphertext),
                         &SM2_Fp256_CTX, &da));
    if (sizeof(msg) != outl && memcmp(out, msg, sizeof(msg)) != 0) {
        ERR_LOG("Err in sm2_crypt");
        goto error;
    }

    // 随机加解密数据测试
    for (int i = 0; i < 30; i++) {
        static uint8_t random_pt[512], ct[1024];
        rand_mem(random_pt, sizeof(random_pt));
        try_goto(sm2_encrypt(ct, &outl, random_pt, sizeof(random_pt), PC,
                             &SM2_Fp256_CTX, &P));
        try_goto(sm2_decrypt(out, &outl, ct, outl, &SM2_Fp256_CTX, &da));
        if (memcmp(random_pt, out, sizeof(random_pt)) != 0) {
            ERR_LOG("Err in sm2");
            goto error;
        }
    }

    return;
error:
    exit(-1);
}

