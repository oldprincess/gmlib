#ifndef SM4_H
#define SM4_H

#include <gmlib/cipher/types.h>

#define SM4_KEYLEN 16
#define SM4_BLOCK_SIZE 16

typedef struct SM4_CTX {
    uint32_t rk[32];  // 32轮轮密钥
} SM4_CTX;

extern const CipherInfo SM4Info;

/// @brief SM4 初始化
void sm4_init(uint8_t* key, SM4_CTX* ctx);

/// @brief SM4 加密
void sm4_encrypt(uint8_t* out, uint8_t* in, SM4_CTX* ctx);

/// @brief SM4 解密
void sm4_decrypt(uint8_t* out, uint8_t* in, SM4_CTX* ctx);

#endif  // SM4_H
