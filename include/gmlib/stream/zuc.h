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
/// @param[out] zuc_ctx     ZUC算法上下文
void zuc_init(uint8_t* key, uint8_t* iv, ZUC_CTX* zuc_ctx);

/// @brief 祖冲之算法产生一节拍32比特密钥
/// @param[inout]   zuc_ctx     ZUC算法上下文
/// @return 32比特密钥字
uint32_t zuc_next(ZUC_CTX* zuc_ctx);

/// @brief 祖冲之算法产生一节拍32比特密钥
/// @param[out]     out         32比特密钥
/// @param[inout]   zuc_ctx     ZUC算法上下文
void zuc_put_next(uint8_t* out, ZUC_CTX* zuc_ctx);

// ========================================
// =========== ZUC 机密性算法 ==============
// ========================================

/// @brief 祖冲之算法机密性算法(加/解密)
void zuc_confidentiality_crypt(uint8_t* out,    ///< [out] 输出
                               uint8_t* in,     ///< [in]  输入
                               int inbits,      ///< [in]  输入比特长度
                               uint32_t COUNT,  ///< [in]  计数器
                               uint8_t BEARER,  ///< [in]  承载层标识(5比特)
                               uint8_t DIRECTION,  ///< [in] 传播方向标识(1比特)
                               uint8_t* CK  ///< [in]  128比特机密性密钥
);

// ========================================
// =========== ZUC 完整性算法 ==============
// ========================================

#define ZUC_MAC_SIZE 4

/// @brief 祖冲之算法完整性算法(MAC)
void zuc_integrity_mac(uint8_t* out,       ///< [out] 输出
                       uint8_t* in,        ///< [in]  输入
                       int inbits,         ///< [in]  输入比特长度
                       uint32_t COUNT,     ///< [in]  计数器
                       uint8_t BEARER,     ///< [in]  承载层标识(5比特)
                       uint8_t DIRECTION,  ///< [in]  传播方向标识(1比特)
                       uint8_t* IK         ///< [in]  128比特完整性密钥
);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // ZUC_H
