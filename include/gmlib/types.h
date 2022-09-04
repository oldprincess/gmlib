#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

// ==================================
// ============ 分组密码 ============
// ==================================

typedef void (*CipherInit)(uint8_t* key, void* ctx);
typedef void (*CipherEncrypt)(uint8_t* out, uint8_t* in, void* ctx);
typedef void (*CipherDecrypt)(uint8_t* out, uint8_t* in, void* ctx);

typedef struct CipherInfo {
    CipherInit init;        ///< 初始化算法
    CipherEncrypt encrypt;  ///< 加密算法
    CipherDecrypt decrypt;  ///< 解密算法
} CipherInfo;

// ==================================
// ============ 哈希函数 ============
// ==================================

typedef void (*HashInit)(void* ctx);
typedef void (*HashUpdate)(uint8_t* in, int inl, void* ctx);
typedef void (*HashFinal)(uint8_t* out, void* ctx);

typedef struct HashInfo {
    HashInit init;          ///< 初始化算法
    HashUpdate update;      ///< 压缩算法
    HashFinal final;        ///< 压缩结果输出
    const int digest_size;  ///< 摘要长度
} HashInfo;

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // TYPES_H
