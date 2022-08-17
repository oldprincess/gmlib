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

static uint8_t out[2048];      // 输出
static int outl;               // 输出长度
static int PC = EC_PC_NO_ZIP;  // 非压缩表示

static BINT da;    // 私钥
static ECPoint P;  // 公钥

int main() {
    // 初始化双方数据
    try_goto(bint_from_str(&da, da_hex, 16));  // load da
    // P = [da]G
    try_goto(ec_mul(&P, &da, &SM2_Fp256_CTX.G, &SM2_Fp256_CTX));

    puts("msg:");
    dump_data(msg, sizeof(msg));

    // 加密
    try_goto(sm2_encrypt(out, &outl, msg, sizeof(msg), PC, &SM2_Fp256_CTX, &P));

    puts("ciphertext:");
    dump_data(out, outl);

    // 解密
    try_goto(sm2_decrypt(out, &outl, out, outl, &SM2_Fp256_CTX, &da));

    puts("msg(decrypt):");
    dump_data(out, outl);

    return 0;
error:
    return -1;
}
