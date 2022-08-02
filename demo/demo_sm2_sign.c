#include <gmlib/publickey/sm2.h>
#include <stdio.h>

static uint8_t ID_A[] = {
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  //
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  //
};

static uint8_t ENTL_A[] = {0x00, 0x80};

// 签名方私钥
static char* da_hex =
    "3945208F_7B2144B1_3F36E38A_C6D39F95_88939369_2860B51A_42FB81EF_4DF7C5B8";

// 待签名消息
static uint8_t msg[] = {
    'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 'd', 'i', 'g', 'e', 's', 't',
};

// signature=(r,s)
static uint8_t signature[2 * (GMLIB_BINT_BITS / 8)];
static int outl;

int main() {
    BINT da;    // 私钥
    ECPoint P;  // 公钥

    // 载入私钥
    bint_from_str(&da, da_hex, 16);
    // 计算公钥 P = [da]G
    ec_mul(&P, &da, &SM2_Fp256_CTX.G, &SM2_Fp256_CTX);

    // sm2 签名
    SM2_SIGN_CTX sm2_sign_ctx;
    sm2_sign_init(ENTL_A, ID_A, &SM2_Fp256_CTX, &da, &P, &sm2_sign_ctx);
    sm2_sign_update(msg, sizeof(msg), &sm2_sign_ctx);
    sm2_sign_final(signature, &outl, &sm2_sign_ctx);

    // sm2 验签
    SM2_VERIFY_CTX sm2_verify_ctx;
    int status = 0;  // 签名正确性
    sm2_verify_init(ENTL_A, ID_A, &SM2_Fp256_CTX, &P, &sm2_verify_ctx);
    sm2_verify_update(msg, sizeof(msg), &sm2_verify_ctx);
    sm2_verify_final(&status, signature, &sm2_verify_ctx);
    if (status != 1) {
        puts("check fail!");
        return -1;
    }
    puts("check ok!");
    return 0;
}
