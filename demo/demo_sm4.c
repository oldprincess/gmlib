#include <gmlib/cipher/sm4.h>
#include <gmlib/utils.h>

// 128比特密钥
uint8_t key[SM4_KEYLEN] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
};

// 128比特明文
uint8_t plaintext[SM4_BLOCK_SIZE] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
};

// 128比特密文输出
uint8_t out[SM4_BLOCK_SIZE];

int main() {
    SM4_Key sm4key;
    // SM4 轮密钥初始化
    sm4_keyinit(key, &sm4key);
    // SM4 加密
    sm4_encrypt(out, plaintext, sizeof(plaintext) / SM4_BLOCK_SIZE, &sm4key);

    dump_data(out, SM4_BLOCK_SIZE);
    // 	09 32 5c 48 53 83 2d cb 93 37 a5 98 4f 67 1b 9a
    return 0;
}
