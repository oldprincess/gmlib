/**
 * @file zuc.h
 * @brief ZUC 祖冲之算法
 *
 * 参考资料：<br>
 * [1]. GM/T 0001.1-2012 祖冲之序列密码算法：第1部分：算法描述<br>
 * [2]. GM/T 0001.2-2012
 *      祖冲之序列密码算法：第2部分：基于祖冲之算法的机密性算法<br>
 * [3]. GM/T 0001.3-2012
 *      祖冲之序列密码算法：第3部分：基于祖冲之算法的完整性算法<br>
 */

#ifndef ZUC_H
#define ZUC_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

// 祖冲之算法密钥长度
#define ZUC_KEYLEN 16

// 祖冲之算法初始向量长度
#define ZUC_IVLEN 16

typedef struct ZUC_CTX {
    uint32_t lsfr[16];  // 16个31比特寄存器
    uint32_t r1, r2;
} ZUC_CTX;

/// @brief 祖冲之算法ZUC初始化
/// @param[in]  key         128比特密钥
/// @param[in]  iv          128比特初始向量
/// @param[out] zuc_ctx     ZUC算法Context
void zuc_init(uint8_t* key, uint8_t* iv, ZUC_CTX* zuc_ctx);

/// @brief 祖冲之算法产生一节拍32比特密钥
/// @param[inout]   zuc_ctx     ZUC算法Context
/// @return 32比特密钥字
uint32_t zuc_next(ZUC_CTX* zuc_ctx);

/// @brief 祖冲之算法产生一节拍32比特密钥
/// @param[out]     out         32比特密钥
/// @param[inout]   zuc_ctx     ZUC算法Context
void zuc_put_next(uint8_t* out, ZUC_CTX* zuc_ctx);

// ========================================
// =========== ZUC 机密性算法 ==============
// ========================================

/// @brief 祖冲之算法机密性算法(加/解密)
/// @param[out] out         输出
/// @param[in]  in          输入
/// @param[in]  inbits      输入比特长度
/// @param[in]  COUNT       计数器
/// @param[in]  BEARER      承载层标识(5比特)
/// @param[in]  DIRECTION   传播方向标识(1比特)
/// @param[in]  CK          128比特机密性密钥
void zuc_confidentiality_crypt(uint8_t* out,
                               uint8_t* in,
                               int inbits,
                               uint32_t COUNT,
                               uint8_t BEARER,
                               uint8_t DIRECTION,
                               uint8_t* CK);

// ========================================
// =========== ZUC 完整性算法 ==============
// ========================================

#define ZUC_MAC_SIZE 4

/// @brief 祖冲之算法完整性算法(MAC)
/// @param[out] out         32比特MAC输出
/// @param[in]  in          输入消息
/// @param[in]  inbits      输入比特长度
/// @param[in]  COUNT       计数器
/// @param[in]  BEARER      承载层标识(5比特)
/// @param[in]  DIRECTION   传播方向标识(1比特)
/// @param[in]  IK          128比特完整性密钥
void zuc_integrity_mac(uint8_t* out,
                       uint8_t* in,
                       int inbits,
                       uint32_t COUNT,
                       uint8_t BEARER,
                       uint8_t DIRECTION,
                       uint8_t* IK);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // ZUC_H
