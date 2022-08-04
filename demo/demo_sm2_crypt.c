#include <gmlib/publickey/sm2.h>
#include <gmlib/utils.h>
#include <stdio.h>
#include <stdlib.h>

static char* da_hex =
    "3945208F_7B2144B1_3F36E38A_C6D39F95_88939369_2860B51A_42FB81EF_4DF7C5B8";

// "encryption standard"
static uint8_t msg[] = {'e', 'n', 'c', 'r', 'y', 'p', 't', 'i', 'o', 'n',
                        ' ', 's', 't', 'a', 'n', 'd', 'a', 'r', 'd'};

static uint8_t ciphertext[2048];
static uint8_t out[2048];
static int PC = EC_PC_NO_ZIP;
static uint8_t *C1, *C2, *C3;  // (C1,C3,C2)分量指针

static BINT da;    // 私钥
static ECPoint P;  // 公钥

void test_sm2_crypt() {}

int main() {
    // 初始化双方数据
    bint_from_str(&da, da_hex, 16);  // load da
    // P = [da]G
    ec_mul(&P, &da, &SM2_Fp256_CTX.G, &SM2_Fp256_CTX);

    puts("msg:");
    dump_data(msg, sizeof(msg));

    int outl, csize, c2size;
    SM2_Crypt_CTX crypt_ctx;
    // 加密
    sm2_encrypt_init(ciphertext, &outl, PC, &SM2_Fp256_CTX, &P, &crypt_ctx);
    C1 = ciphertext;                             // 确定C1的位置
    C3 = ciphertext + outl;                      // 确定C3的位置
    C2 = ciphertext + outl + SM2_CRYPT_C3_SIZE;  // 确定C2的位置

    sm2_encrypt_update(C2, &c2size, msg, sizeof(msg), &crypt_ctx);
    sm2_encrypt_final(C3, &crypt_ctx);
    csize = (int)(C2 - C1) + c2size;

    puts("ciphertext");
    dump_data(ciphertext, csize);

    // 解密
    sm2_decrypt_init(ciphertext, &outl, &SM2_Fp256_CTX, &da, &crypt_ctx);
    C1 = ciphertext;                             // 确定C1的位置
    C3 = ciphertext + outl;                      // 确定C3的位置
    C2 = ciphertext + outl + SM2_CRYPT_C3_SIZE;  // 确定C2的位置
    c2size = csize - (int)(C2 - C1);
    sm2_decrypt_update(out, &outl, C2, c2size, &crypt_ctx);
    sm2_decrypt_final(C3, &crypt_ctx);

    puts("msg:");
    dump_data(out, outl);

    return 0;
}
