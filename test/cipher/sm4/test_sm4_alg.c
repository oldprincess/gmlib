#include <gmlib/cipher/sm4.h>
#include <gmlib/err.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdlib.h>

void test_sm4_alg() {
    static uint8_t key[SM4_KEYLEN] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
    };
    static uint8_t plaintext[SM4_BLOCK_SIZE] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    };
    static uint8_t ciphertext[SM4_BLOCK_SIZE] = {
        0x09, 0x32, 0x5c, 0x48, 0x53, 0x83, 0x2d, 0xcb,
        0x93, 0x37, 0xa5, 0x98, 0x4f, 0x67, 0x1b, 0x9a,
    };
    static uint8_t buffer[SM4_BLOCK_SIZE] = {0};

    SM4_KEY sm4key;
    int block_num = sizeof(plaintext) / SM4_BLOCK_SIZE;
    sm4_keyinit(key, &sm4key);
    sm4_encrypt(buffer, plaintext, block_num, &sm4key);
    if (memcmp(buffer, ciphertext, block_num * SM4_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in sm4_encrypt");
        exit(-1);
    }

    sm4_decrypt(buffer, ciphertext, block_num, &sm4key);
    if (memcmp(buffer, plaintext, block_num * SM4_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in sm4_decrypt");
        exit(-1);
    }
}
