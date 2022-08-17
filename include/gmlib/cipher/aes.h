/**
 * @file  aes.h
 * @brief AES 算法
 *
 * 参考资料：<br>
 * [1]. FIPS 197 Advanced Encryption Standard (AES) <br>
 * [2]. AES 查表优化(https://zhuanlan.zhihu.com/p/42264499) <br>
 *
 * 参考资料[1]为AES标准文档，资料[2]为AES查表优化的知乎链接
 */

#ifndef AES_H
#define AES_H

#include <gmlib/types.h>

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
/// @param[in]  key     用户密钥
/// @param[in]  kbits   密钥比特数(128/192/256)
/// @param[out] ctx     AES算法上下文
void aes_init(uint8_t* key, int kbits, AES_CTX* ctx);

/// @brief AES128 初始化
void aes128_init(uint8_t* key, AES_CTX* ctx);

/// @brief AES192 初始化
void aes192_init(uint8_t* key, AES_CTX* ctx);

/// @brief AES256 初始化
void aes256_init(uint8_t* key, AES_CTX* ctx);

/// @brief AES 加密
/// @param[out] out     输出(密文)
/// @param[in]  in      输入(明文)
/// @param[in]  ctx     AES算法上下文
void aes_encrypt(uint8_t* out, uint8_t* in, AES_CTX* ctx);

/// @brief AES 解密
/// @param[out] out     输出(明文)
/// @param[in]  in      输入(密文)
/// @param[in]  ctx     AES算法上下文
void aes_decrypt(uint8_t* out, uint8_t* in, AES_CTX* ctx);

#endif // AES_H
