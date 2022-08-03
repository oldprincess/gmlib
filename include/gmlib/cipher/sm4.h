#ifndef SM4_H
#define SM4_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

#define SM4_BLOCK_SIZE 16
#define SM4_FAST_BLOCK_SIZE 16
#define SM4_KEYLEN 16

typedef struct SM4_Key {
    uint32_t rk[32];  // sm4 round key
} SM4_Key;

/// @brief SM4 轮密钥生成
/// @param[in]  key     128bit用户密钥
/// @param[out] sm4key  SM4轮密钥
void sm4_keyinit(uint8_t* key, SM4_Key* sm4key);

/// @brief SM4 ECB模式加密
/// @param[out] out         ciphertext
/// @param[in]  in          plaintext
/// @param[in]  block_num   输入分组数
/// @param[in]  sm4key      SM4轮密钥
void sm4_encrypt(uint8_t* out, uint8_t* in, int block_num, SM4_Key* sm4key);

/// @brief SM4 ECB模式解密
/// @param[out] out         plaintext
/// @param[in]  in          ciphertext
/// @param[in]  block_num   输入分组数
/// @param[in]  sm4key      SM4轮密钥
void sm4_decrypt(uint8_t* out, uint8_t* in, int block_num, SM4_Key* sm4key);

// =========================================
// ============ ECB Mode ===================
// =========================================

typedef struct SM4_ECB_CTX {
    SM4_Key sm4key;                       // SM4 轮密钥
    uint8_t buffer[SM4_FAST_BLOCK_SIZE];  // 缓冲区
    int bsize;                            // buffer 长度
} SM4_ECB_CTX;

/// @brief SM4 ECB模式初始化
/// @param[in] key          用户密钥
/// @param[inout] ecb_ctx   ECB Context
void sm4_ecb_init(uint8_t* key, SM4_ECB_CTX* ecb_ctx);

/// @brief SM4 ECB模式Context重置
/// @param[inout] ecb_ctx   ECB Context
void sm4_ecb_reset(SM4_ECB_CTX* ecb_ctx);

/// @brief SM4 ECB加密模式Update数据
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  in      输入
/// @param[in]  inl     输入长度
/// @param[in]  ecb_ctx ECB Context
void sm4_ecb_encrypt_update(uint8_t* out, int* outl, uint8_t* in, int inl,
                            SM4_ECB_CTX* ecb_ctx);

/// @brief SM4 ECB解密模式Update数据
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  in      输入
/// @param[in]  inl     输入长度
/// @param[in]  ecb_ctx ECB Context
void sm4_ecb_decrypt_update(uint8_t* out, int* outl, uint8_t* in, int inl,
                            SM4_ECB_CTX* ecb_ctx);

/// @brief SM4 ECB加密模式Final
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  ecb_ctx ECB Context
void sm4_ecb_encrypt_final(uint8_t* out, int* outl, SM4_ECB_CTX* ecb_ctx);

/// @brief SM4 ECB解密模式Final
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  ecb_ctx ECB Context
/// @return 错误码（0表示无错误）
int sm4_ecb_decrypt_final(uint8_t* out, int* outl, SM4_ECB_CTX* ecb_ctx);

// =========================================
// ============ CBC Mode ===================
// =========================================

typedef struct SM4_CBC_CTX {
    SM4_Key sm4key;
    uint8_t iv[SM4_BLOCK_SIZE];
    uint8_t buffer[SM4_FAST_BLOCK_SIZE];
    int bsize;
} SM4_CBC_CTX;

/// @brief SM4 CBC模式初始化
/// @param[in]      key         用户密钥
/// @param[in]      iv          初始向量iv
/// @param[inout]   cbc_ctx     CBC Context
void sm4_cbc_init(uint8_t* key, uint8_t* iv, SM4_CBC_CTX* cbc_ctx);

/// @brief SM4 CBC模式Context重置
/// @param[in]      iv          初始向量iv
/// @param[inout]   cbc_ctx     CBC Context
void sm4_cbc_reset(uint8_t* iv, SM4_CBC_CTX* cbc_ctx);

/// @brief SM4 CBC加密模式Update数据
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  in      输入
/// @param[in]  inl     输入长度
/// @param[in]  cbc_ctx CBC Context
void sm4_cbc_encrypt_update(uint8_t* out, int* outl, uint8_t* in, int inl,
                            SM4_CBC_CTX* cbc_ctx);

/// @brief SM4 CBC解密模式Update数据
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  in      输入
/// @param[in]  inl     输入长度
/// @param[in]  cbc_ctx CBC Context
void sm4_cbc_decrypt_update(uint8_t* out, int* outl, uint8_t* in, int inl,
                            SM4_CBC_CTX* cbc_ctx);

/// @brief SM4 CBC加密模式Final
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  cbc_ctx CBC Context
void sm4_cbc_encrypt_final(uint8_t* out, int* outl, SM4_CBC_CTX* cbc_ctx);

/// @brief SM4 CBC解密模式Final
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  cbc_ctx CBC Context
/// @return 错误码（0表示无错误）
int sm4_cbc_decrypt_final(uint8_t* out, int* outl, SM4_CBC_CTX* cbc_ctx);

// =========================================
// ============ CTR Mode ===================
// =========================================

typedef struct SM4_CTR_CTX {
    SM4_Key sm4key;
    uint8_t iv[SM4_BLOCK_SIZE];
    uint8_t buffer[SM4_FAST_BLOCK_SIZE];
    int bsize;
} SM4_CTR_CTX;

/// @brief SM4 CTR模式初始化
/// @param[in]      key         用户密钥
/// @param[in]      iv          初始向量iv
/// @param[inout]   ctr_ctx     CTRContext
void sm4_ctr_init(uint8_t* key, uint8_t* iv, SM4_CTR_CTX* ctr_ctx);

/// @brief SM4 CTR模式Context重置
/// @param[in]      iv          初始向量iv
/// @param[inout]   ctr_ctx     CTR Context
void sm4_ctr_reset(uint8_t* iv, SM4_CTR_CTX* ctr_ctx);

/// @brief SM4 CTR加密模式Update数据
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  in      输入
/// @param[in]  inl     输入长度
/// @param[in]  ctr_ctx CTR Context
void sm4_ctr_encrypt_update(uint8_t* out, int* outl, uint8_t* in, int inl,
                            SM4_CTR_CTX* ctr_ctx);

/// @brief SM4 CTR解密模式Update数据
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  in      输入
/// @param[in]  inl     输入长度
/// @param[in]  ctr_ctx CTR Context
void sm4_ctr_decrypt_update(uint8_t* out, int* outl, uint8_t* in, int inl,
                            SM4_CTR_CTX* ctr_ctx);

/// @brief SM4 CTR加密模式Final
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  ctr_ctx CTR Context
void sm4_ctr_encrypt_final(uint8_t* out, int* outl, SM4_CTR_CTX* ctr_ctx);

/// @brief SM4 CTR解密模式Final
/// @param[out] out     输出
/// @param[out] outl    输出长度
/// @param[in]  ctr_ctx CTR Context
void sm4_ctr_decrypt_final(uint8_t* out, int* outl, SM4_CTR_CTX* ctr_ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SM4_H
