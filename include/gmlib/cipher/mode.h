/**
 * @file mode.h
 * @brief 分组密码工作模式
 *
 * 参考资料：<br>
 * [1]. SP 800-38A
 * specifies five confidentiality modes of operation for block ciphers <br>
 */

#ifndef MODE_H
#define MODE_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

// =========================================
// ============= Cipher Info ===============
// =========================================

//  Cipher Encrypt Function-Type
/// @brief 以ECB模式加密数据
/// @param[out] out         输出
/// @param[in]  in          输入
/// @param[in]  block_num   输入BLOCK数
/// @param[in]  cipher_key  算法轮密钥
typedef void (*CipherEncrypt)(uint8_t* out,     // output buffer
                              uint8_t* in,      // input buffer
                              int block_num,    // block number
                              void* cipher_key  // cipher key
);

//  Cipher Decrypt Function-Type
/// @brief 以ECB模式解密数据
/// @param[out] out         输出
/// @param[in]  in          输入
/// @param[in]  block_num   输入BLOCK数
/// @param[in]  cipher_key  算法轮密钥
typedef void (*CipherDecrypt)(uint8_t* out,     // output buffer
                              uint8_t* in,      // input buffer
                              int block_num,    // block number
                              void* cipher_key  // cipher key
);

// =========================================
// ============= ECB Mode ==================
// =========================================

/// @brief ECB模式加密update
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      in          输入
/// @param[in]      inl         输入长度
/// @param[in]      encrypt     加密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   ecb_buffer  ECB缓冲区
/// @param[inout]   ecb_bsize   ECB缓冲区长度
/// @param[in]      ecb_mbsize  ECB缓冲区上限
void ecb_encrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherEncrypt encrypt,  // encrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* ecb_buffer,    // ecb buffer
                        int* ecb_bsize,         // ecb buffer size
                        int ecb_mbsize          // ecb max bsize
);

/// @brief ECB模式解密update
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      in          输入
/// @param[in]      inl         输入长度
/// @param[in]      decrypt     解密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   ecb_buffer  ECB缓冲区
/// @param[inout]   ecb_bsize   ECB缓冲区长度
/// @param[in]      ecb_mbsize  ECB缓冲区上限
void ecb_decrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherDecrypt decrypt,  // decrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* ecb_buffer,    // ecb buffer
                        int* ecb_bsize,         // ecb buffer size
                        int ecb_mbsize          // ecb max bsize
);

/// @brief ECB模式加密final
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      encrypt     加密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   ecb_buffer  ECB缓冲区
/// @param[inout]   ecb_bsize   ECB缓冲区长度
void ecb_encrypt_final(uint8_t* out,           // output buffer
                       int* outl,              // output len
                       CipherEncrypt encrypt,  // encrypt func
                       void* cipher_key,       // cipher key
                       int block_size,         // cipher block size
                       uint8_t* ecb_buffer,    // ecb buffer
                       int* ecb_bsize          // ecb buffer size
);

/// @brief ECB模式加密final
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      decrypt     解密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   ecb_buffer  ECB缓冲区
/// @param[inout]   ecb_bsize   ECB缓冲区长度
/// @return 错误码（0表示无错误）
int ecb_decrypt_final(uint8_t* out,           // output buffer
                      int* outl,              // output len
                      CipherDecrypt decrypt,  // decrypt func
                      void* cipher_key,       // cipher key
                      int block_size,         // cipher block size
                      uint8_t* ecb_buffer,    // ecb buffer
                      int* ecb_bsize          // ecb buffer size
);

// =========================================
// ============= CBC Mode ==================
// =========================================

/// @brief CBC模式加密update
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      in          输入
/// @param[in]      inl         输入长度
/// @param[in]      encrypt     加密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   cbc_iv      CBC 初始向量iv
/// @param[inout]   cbc_buffer  CBC缓冲区
/// @param[inout]   cbc_bsize   CBC缓冲区长度
void cbc_encrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherEncrypt encrypt,  // encrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* cbc_iv,        // cbc iv
                        uint8_t* cbc_buffer,    // cbc buffer
                        int* cbc_bsize          // cbc buffer size
);

/// @brief CBC模式解密update
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      in          输入
/// @param[in]      inl         输入长度
/// @param[in]      decrypt     解密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   cbc_iv      CBC 初始向量iv
/// @param[inout]   cbc_buffer  CBC缓冲区
/// @param[inout]   cbc_bsize   CBC缓冲区长度
/// @param[in]      cbc_mbsize  CBC缓冲区上限
void cbc_decrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherDecrypt decrypt,  // decrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* cbc_iv,        // cbc iv
                        uint8_t* cbc_buffer,    // cbc buffer
                        int* cbc_bsize,         // cbc buffer size
                        int cbc_mbsize          // cbc max bsize
);

/// @brief CBC模式加密final
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      encrypt     加密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   cbc_iv      CBC 初始向量iv
/// @param[inout]   cbc_buffer  CBC缓冲区
/// @param[inout]   cbc_bsize   CBC缓冲区长度
void cbc_encrypt_final(uint8_t* out,           // output buffer
                       int* outl,              // output len
                       CipherEncrypt encrypt,  // encrypt func
                       void* cipher_key,       // cipher key
                       int block_size,         // cipher block size
                       uint8_t* cbc_iv,        // cbc iv
                       uint8_t* cbc_buffer,    // cbc buffer
                       int* cbc_bsize          // cbc buffer size
);

/// @brief CBC模式加密final
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      decrypt     解密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   cbc_iv      CBC 初始向量iv
/// @param[inout]   cbc_buffer  CBC缓冲区
/// @param[inout]   cbc_bsize   CBC缓冲区长度
int cbc_decrypt_final(uint8_t* out,           // output buffer
                      int* outl,              // output len
                      CipherDecrypt decrypt,  // decrypt func
                      void* cipher_key,       // cipher key
                      int block_size,         // cipher block size
                      uint8_t* cbc_iv,        // cbc iv
                      uint8_t* cbc_buffer,    // cbc buffer
                      int* cbc_bsize          // cbc buffer size
);

// =========================================
// ============= CTR Mode ==================
// =========================================

/// @brief CTR模式update
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      in          输入
/// @param[in]      inl         输入长度
/// @param[in]      encrypt     加密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   ctr_iv      CTR 初始向量iv
/// @param[inout]   ctr_buffer  CTR缓冲区
/// @param[inout]   ctr_bsize   CTR缓冲区长度
/// @param[in]      ctr_mbsize  CTR缓冲区上限
void ctr_update(uint8_t* out,           // output buffer
                int* outl,              // output len
                uint8_t* in,            // input buffer
                int inl,                // input len
                CipherEncrypt encrypt,  // encrypt func
                void* cipher_key,       // cipher key
                int block_size,         // cipher block size
                uint8_t* ctr_iv,        // ctr iv
                uint8_t* ctr_buffer,    // ctr buffer
                int* ctr_bsize,         // ctr buffer size
                int ctr_mbsize          // ctr max bsize
);

/// @brief CTR模式final
/// @param[out]     out         输出
/// @param[out]     outl        输出长度
/// @param[in]      encrypt     加密函数
/// @param[in]      cipher_key  算法密钥
/// @param[in]      block_size  算法block大小
/// @param[inout]   ctr_iv      CTR 初始向量iv
/// @param[inout]   ctr_buffer  CTR缓冲区
/// @param[inout]   ctr_bsize   CTR缓冲区长度
void ctr_final(uint8_t* out,           // output buffer
               int* outl,              // output len
               CipherEncrypt encrypt,  // encrypt func
               void* cipher_key,       // cipher key
               int block_size,         // cipher block size
               uint8_t* ctr_iv,        // ctr iv
               uint8_t* ctr_buffer,    // ctr buffer
               int* ctr_bsize          // ctr buffer size
);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // MODE_H
