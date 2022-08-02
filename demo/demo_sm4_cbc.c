#include <gmlib/cipher/sm4.h>
#include <gmlib/utils.h>

// 128比特密钥
uint8_t key[SM4_KEYLEN] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,  //
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,  //
};

// 128比特初始向量
uint8_t iv[SM4_KEYLEN] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,  //
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  //
};

// 128比特明文
uint8_t plaintext[SM4_BLOCK_SIZE] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,  //
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,  //
};

// 128比特密文输出
uint8_t out[SM4_BLOCK_SIZE * 2];
int outl;

int main() {
    SM4_CBC_CTX sm4_cbc_ctx;
    uint8_t* outptr = out;
    outl = 0;

    // SM4 CBC初始化
    sm4_cbc_init(key, iv, &sm4_cbc_ctx);
    // SM4 CBC Update 消息
    sm4_cbc_encrypt_update(outptr, &outl, plaintext, sizeof(plaintext),
                           &sm4_cbc_ctx);
    outptr += outl;  // 更新out指针
    // SM4 CBC Final
    sm4_cbc_encrypt_final(outptr, &outl, &sm4_cbc_ctx);
    outptr += outl;  // 更新out指针

    int ciphertext_size = (int)(outptr - out);
    dump_data(out, ciphertext_size);
    // 	5d 1f ee 63 f5 eb 8b b5 03 58 0a b8 23 92 5d 55
    //  d1 b0 fc eb 63 b8 b2 4f 3f f5 d9 3a 33 ea d1 70
    return 0;
}
