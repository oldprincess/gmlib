/**
 * @file  sm4.h
 * @brief SM4 算法
 *
 * 参考资料：<br>
 * [1]. GM/T 0002-2012 SM4分组密码算法 <br>
 * [2]. 郎欢, 张蕾, 吴文玲. SM4的快速软件实现技术 <br>
 *
 * 资料[1]是SM4官方国标文档，资料[2]是查表优化的参考文献
 */

#ifndef SM4_H
#define SM4_H

#include <gmlib/types.h>

#define SM4_KEYLEN 16
#define SM4_BLOCK_SIZE 16

typedef struct SM4_CTX {
    uint32_t rk[32];  // 32轮轮密钥
} SM4_CTX;

extern const CipherInfo SM4Info;

/// @brief SM4 初始化
/// @param[in]  key     128比特用户密钥
/// @param[out] ctx     SM4算法上下文
void sm4_init(uint8_t* key, SM4_CTX* ctx);

/// @brief SM4 加密
/// @param[out] out     输出(密文)
/// @param[in]  in      输入(明文)
/// @param[in]  ctx     SM4算法上下文
void sm4_encrypt(uint8_t* out, uint8_t* in, SM4_CTX* ctx);

/// @brief SM4 解密
/// @param[out] out     输出(明文)
/// @param[in]  in      输入(密文)
/// @param[in]  ctx     SM4算法上下文
void sm4_decrypt(uint8_t* out, uint8_t* in, SM4_CTX* ctx);

#endif  // SM4_H
