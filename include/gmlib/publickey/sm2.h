/**
 * @file  sm2.h
 * @brief SM2 公钥算法
 *
 * 参考资料：<br>
 * [1]. GM/T 0003.1-2012 SM2 椭圆曲线公钥密码算法第1部分：总则<br>
 * [2]. GM/T 0003.2-2012 SM2 椭圆曲线公钥密码算法第2部分：数字签名算法<br>
 * [3]. GM/T 0003.3-2012 SM2 椭圆曲线公钥密码算法第3部分：密钥交换协议<br>
 * [4]. GM/T 0003.4-2012 SM2 椭圆曲线公钥密码算法第4部分：公钥加密算法<br>
 * [5]. GM/T 0003.5-2012 SM2 椭圆曲线公钥密码算法第5部分：参数定义<br>
 */

#ifndef SM2_H
#define SM2_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/ec.h>
#include <gmlib/hash/sm3.h>

extern EC_CTX SM2_Fp256_CTX;  // SM2 椭圆曲线参数

// ========================================
// =========== SM2 签名 ===================
// ========================================

typedef struct SM2_SIGN_CTX {
    // Z = H(ENTL || ID || a || b || G.x || G.y || P.x || P.y)
    uint8_t Z[SM3_DIGEST_SIZE];  // 签名者标识
    EC_CTX* ec_ctx;              // 椭圆曲线 Context
    SM3_CTX sm3_ctx;             // sm3 Context
    BINT da;                     // 签名者私钥
    BINT da_plus_1_iv;           // (da+1)^-1 % EC.n
} SM2_SIGN_CTX;

/// @brief SM2 签名初始化
/// @return 错误码（0表示无错误）
int sm2_sign_init(uint8_t ENTL[2],  ///< [in] ID比字节长度
                  uint8_t* ID,      ///< [in] 签名者ID
                  EC_CTX* ec_ctx,   ///< [in] 椭圆曲线上下文
                  BINT* da,         ///< [in] 签名者私钥
                  ECPoint* P,       ///< [in] 签名者公钥
                  SM2_SIGN_CTX* sm2_sign_ctx);

/// @brief SM2 签名Update
void sm2_sign_update(uint8_t* in, int inl, SM2_SIGN_CTX* sm2_sign_ctx);

/// @brief SM2 签名Final
/// @return 错误码（0表示无错误）
int sm2_sign_final(uint8_t* out, int* outl, SM2_SIGN_CTX* sm2_sign_ctx);

// ========================================
// =========== SM2 验签 ===================
// ========================================

typedef struct SM2_VERIFY_CTX {
    // Z = H(ENTL || ID || a || b || G.x || G.y || P.x || P.y)
    uint8_t Z[SM3_DIGEST_SIZE];  // 签名者标识
    EC_CTX* ec_ctx;              // 椭圆曲线上下文
    SM3_CTX sm3_ctx;             // SM3算法上下文
    ECPoint P;                   // 签名者公钥
} SM2_VERIFY_CTX;

/// @brief SM2 验签初始化
/// @return 错误码（0表示无错误）
int sm2_verify_init(uint8_t ENTL[2],  ///< [in] ID比字节长度
                    uint8_t* ID,      ///< [in] 签名者ID
                    EC_CTX* ec_ctx,   ///< [in] 椭圆曲线上下文
                    ECPoint* P,       ///< [in] 签名者公钥
                    SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签Update
void sm2_verify_update(uint8_t* in, int inl, SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签Final
/// @return 错误码（0表示无错误）
int sm2_verify_final(int* status,         ///< [out] 1(成功),0(失败)
                     uint8_t* signature,  ///< [in]  签名
                     SM2_VERIFY_CTX* sm2_verify_ctx);

// ========================================
// =========== SM2 加解密 ==================
// ========================================

#define SM2_CRYPT_C3_SIZE SM3_DIGEST_SIZE

/// @brief SM2 加密
/// @return 错误码（0表示无错误）
int sm2_encrypt(uint8_t* out,    ///< [out] 输出
                int* outl,       ///< [out] 输出长度
                uint8_t* in,     ///< [in]  输入
                int inl,         ///< [in]  输入长度
                int PC,          ///< [in]  椭圆曲线点表示方法
                EC_CTX* ec_ctx,  ///< [in]  椭圆曲线参数
                ECPoint* P       ///< [in]  接收方公钥
);

/// @brief SM2 解密
/// @return 错误码（0表示无错误）
int sm2_decrypt(uint8_t* out,    ///< [out] 输出
                int* outl,       ///< [out] 输出长度
                uint8_t* in,     ///< [in]  输入
                int inl,         ///< [in]  输入长度
                EC_CTX* ec_ctx,  ///< [in]  椭圆曲线参数
                BINT* da         ///< [in]  接收者私钥
);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SM2_H
