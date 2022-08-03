#ifndef SM3_H
#define SM3_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

/// SM3 摘要字节数
#define SM3_DIGEST_SIZE (256 / 8)

/// SM3 压缩函数分组数
#define SM3_BLOCK_SIZE (512 / 8)

typedef struct SM3_CTX {
    uint32_t state[8];               // SM3 状态数据
    uint8_t buffer[SM3_BLOCK_SIZE];  // 消息 buffer
    int bsize;                       // buffer 长度
    uint64_t dbits;                  // 消息比特长度
} SM3_CTX;

/// @brief SM3 初始化
void sm3_init(SM3_CTX* ctx);

/// @brief SM3 更新消息
void sm3_update(uint8_t* in, int inl, SM3_CTX* ctx);

/// @brief SM3 Final 并输出摘要
void sm3_final(uint8_t* out, SM3_CTX* ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SM3_H
