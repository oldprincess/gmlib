/**
 * @file  sm3.h
 * @brief SM3 哈希算法
 *
 * 参考资料：<br>
 * [1]. GM/T 0004-2012 SM3 密码杂凑算法<br>
 * [2]. GmSSL(https://github.com/guanzhi/GmSSL) <br>
 */

#ifndef SM3_H
#define SM3_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/types.h>
#include <stdint.h>

extern const HashInfo SM3Info;

// SM3 摘要字节数
#define SM3_DIGEST_SIZE (256 / 8)

// SM3 压缩函数分组数
#define SM3_BLOCK_SIZE (512 / 8)

typedef struct SM3_CTX {
    uint32_t state[8];               // SM3 状态数据
    uint8_t buffer[SM3_BLOCK_SIZE];  // 消息 buffer
    int bsize;                       // buffer 长度
    uint64_t dbits;                  // 消息比特长度
} SM3_CTX;

/// @brief SM3 初始化
/// @param[in]  ctx     SM3算法上下文
void sm3_init(SM3_CTX* ctx);

/// @brief SM3 更新消息
/// @param[in]      in      输入
/// @param[in]      inl     输入长度
/// @param[inout]   ctx     SM3算法上下文
void sm3_update(uint8_t* in, int inl, SM3_CTX* ctx);

/// @brief SM3 Final 并输出摘要
/// @param[out]     out     256比特摘要
/// @param[inout]   ctx     SM3算法上下文
void sm3_final(uint8_t* out, SM3_CTX* ctx);

// ==================================
// ============== HMAC ==============
// ==================================

typedef struct HMAC_SM3_CTX {
    SM3_CTX hctx;
    uint8_t hkey[SM3_BLOCK_SIZE];
} HMAC_SM3_CTX;

/// @brief SM3 HMAC 初始化
/// @param[in]  key     密钥
/// @param[in]  klen    密钥长度
/// @param[in]  hmctx   SM3 HMAC算法上下文
void hmac_sm3_init(uint8_t* key, int klen, HMAC_SM3_CTX* hmctx);

/// @brief SM3 更新消息
/// @param[in]      in      输入
/// @param[in]      inl     输入长度
/// @param[inout]   hmctx   SM3 HMAC算法上下文
void hmac_sm3_update(uint8_t* in, int inl, HMAC_SM3_CTX* hmctx);

/// @brief SM3 Final 并输出摘要
/// @param[out]     out     256比特摘要
/// @param[inout]   hmctx   SM3 HMAC算法上下文
void hmac_sm3_final(uint8_t* out, HMAC_SM3_CTX* hmctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SM3_H
