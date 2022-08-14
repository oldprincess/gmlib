#ifndef MODE_H
#define MODE_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/cipher/types.h>

#define BLOCK_SIZE 16

// ==========================================
// ============== ECB MODE ==================
// ==========================================

typedef struct ECB_CTX {
    uint8_t buffer[BLOCK_SIZE];
    int bsize;
    const CipherInfo* cipher;
    void* cctx;
} ECB_CTX;

/// @brief ECB 模式初始化
void ecb_init(uint8_t* key,              ///< [in]    用户密钥
              const CipherInfo* cipher,  ///< [in]    算法
              void* cctx,                ///< [inout] 算法上下文
              ECB_CTX* mctx);

/// @brief ECB 加密
void ecb_encrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        ECB_CTX* mctx);

/// @brief ECB 加密
void ecb_encrypt_final(uint8_t* out, int* outl, ECB_CTX* mctx);

/// @brief ECB 解密
void ecb_decrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        ECB_CTX* mctx);

/// @brief ECB 解密
/// @return 错误码（0表示无错误）
int ecb_decrypt_final(uint8_t* out, int* outl, ECB_CTX* mctx);

// ==========================================
// ============== CBC MODE ==================
// ==========================================

typedef struct CBC_CTX {
    uint8_t iv[BLOCK_SIZE];
    uint8_t buffer[BLOCK_SIZE];
    int bsize;
    const CipherInfo* cipher;
    void* cctx;
} CBC_CTX;

/// @brief CBC 模式初始化
void cbc_init(uint8_t* key,              ///< [in]    用户密钥
              uint8_t* iv,               ///< [in]    初始向量
              const CipherInfo* cipher,  ///< [in]    算法
              void* cctx,                ///< [inout] 算法上下文
              CBC_CTX* mctx);

/// @brief CBC 加密
void cbc_encrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        CBC_CTX* mctx);

/// @brief CBC 加密
void cbc_encrypt_final(uint8_t* out, int* outl, CBC_CTX* mctx);

/// @brief CBC 解密
void cbc_decrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        CBC_CTX* mctx);

/// @brief CBC 解密
/// @return 错误码（0表示无错误）
int cbc_decrypt_final(uint8_t* out, int* outl, CBC_CTX* mctx);

// ==========================================
// ============== GCM MODE ==================
// ==========================================

// GHashTable 将占用巨大存储空间
typedef uint64_t GHashTable[256][2];

typedef struct GHash_CTX {
    uint8_t buffer[BLOCK_SIZE];
    int bsize;
    uint8_t X[BLOCK_SIZE];
    uint8_t H[BLOCK_SIZE];
    GHashTable* ht;
} GHash_CTX;

typedef struct GCTR_CTX {
    uint8_t j0[BLOCK_SIZE];
    uint8_t j[BLOCK_SIZE];
    uint8_t buffer[BLOCK_SIZE];
    int bsize;
    const CipherInfo* cipher;
    void* cctx;
} GCTR_CTX;

typedef struct GCM_CTX {
    GHash_CTX hctx;
    GCTR_CTX gctx;
    int alen, clen;
} GCM_CTX;

void gcm_init(uint8_t* key,              ///< [in]    用户密钥
              uint8_t* iv,               ///< [in]    初始向量
              int ivlen,                 ///< [in]    初始向量长度
              GHashTable* ht,            ///< [inout] GHash查找表(可为NULL)
              const CipherInfo* cipher,  ///< [in]    算法
              void* cctx,                ///< [inout] 算法上下文
              GCM_CTX* mctx);

void gcm_update_aad(uint8_t* aad, int alen, GCM_CTX* mctx);

/// @brief GCM 加密
void gcm_encrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        GCM_CTX* mctx);

/// @brief GCM 加密
void gcm_encrypt_final(uint8_t* out,  ///< [out] 输出
                       int* outl,     ///< [out] 输出长度
                       uint8_t* tag,  ///< [out] tag
                       int tlen,      ///< [in]  tag长度
                       GCM_CTX* mctx);

/// @brief GCM 解密
void gcm_decrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        GCM_CTX* mctx);

/// @brief GCM 解密
/// @return 错误码（0表示无错误）
int gcm_decrypt_final(uint8_t* out,  ///< [out] 输出
                      int* outl,     ///< [out] 输出长度
                      uint8_t* tag,  ///< [in]  tag
                      int tlen,      ///< [in]  tag长度
                      GCM_CTX* mctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // MODE_H
