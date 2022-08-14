#ifndef AES_H
#define AES_H

#include <gmlib/cipher/types.h>

#define AES128_KEYLEN 16
#define AES192_KEYLEN 24
#define AES256_KEYLEN 32
#define AES_BLOCK_SIZE 16

typedef struct AES_CTX {
    uint32_t ek[4 * 15];  // 加密轮密钥
    uint32_t dk[4 * 15];  // 解密轮密钥
    int nr;               // 加密轮数
} AES_CTX;

extern const CipherInfo AES128Info;
extern const CipherInfo AES192Info;
extern const CipherInfo AES256Info;

/// @brief AES 初始化
void aes_init(uint8_t* key, int kbits, AES_CTX* ctx);
void aes128_init(uint8_t* key, AES_CTX* ctx);
void aes192_init(uint8_t* key, AES_CTX* ctx);
void aes256_init(uint8_t* key, AES_CTX* ctx);

/// @brief AES 加密
void aes_encrypt(uint8_t* out, uint8_t* in, AES_CTX* ctx);

/// @brief AES 解密
void aes_decrypt(uint8_t* out, uint8_t* in, AES_CTX* ctx);

#endif // AES_H
