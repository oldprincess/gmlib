/**
 * @file sm2.h
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

extern EC_CTX SM2_Fp256_CTX;

// ========================================
// =========== SM2 签名 ===================
// ========================================

typedef struct SM2_SIGN_CTX {
    // Z = H(ENTL || ID || a || b || G.x || G.y || P.x || P.y)
    uint8_t Z[SM3_DIGEST_SIZE];  // 签名者标识
    EC_CTX ec_ctx;               // 椭圆曲线 Context
    SM3_CTX sm3_ctx;             // sm3 Context
    BINT da;                     // 签名者私钥
    BINT da_plus_1_iv;           // (da+1)^-1 % EC.n
} SM2_SIGN_CTX;

/// @brief SM2 签名初始化
int sm2_sign_init(uint8_t ENTL[2],
                  uint8_t* ID,
                  EC_CTX* ec_ctx,
                  BINT* da,
                  ECPoint* P,
                  SM2_SIGN_CTX* sm2_sign_ctx);

/// @brief SM2 签名重置
void sm2_sign_reset(SM2_SIGN_CTX* sm2_sign_ctx);

/// @brief SM2 签名Update
void sm2_sign_update(uint8_t* in, int inl, SM2_SIGN_CTX* sm2_sign_ctx);

/// @brief SM2 签名Final
int sm2_sign_final(uint8_t* out, int* outl, SM2_SIGN_CTX* sm2_sign_ctx);

// ========================================
// =========== SM2 验签 ===================
// ========================================

typedef struct SM2_VERIFY_CTX {
    // Z = H(ENTL || ID || a || b || G.x || G.y || P.x || P.y)
    uint8_t Z[SM3_DIGEST_SIZE];  // 签名者标识
    EC_CTX ec_ctx;               // 椭圆曲线 Context
    SM3_CTX sm3_ctx;             // sm3 Context
    ECPoint P;                   // 签名者公钥
} SM2_VERIFY_CTX;

/// @brief SM2 验签初始化
int sm2_verify_init(uint8_t ENTL[2],
                    uint8_t* ID,
                    EC_CTX* ec_ctx,
                    ECPoint* P,
                    SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签重置
void sm2_verify_reset(SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签Update
void sm2_verify_update(uint8_t* in, int inl, SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签Final
int sm2_verify_final(int* status,
                     uint8_t* signature,
                     SM2_VERIFY_CTX* sm2_verify_ctx);

// ========================================
// =========== SM2 加密 ===================
// ========================================

#define SM2_CRYPT_C3_SIZE SM3_DIGEST_SIZE

typedef struct SM2_KDF_CTX {
    uint32_t ct;
    SM3_CTX sm3_ctx;
} SM2_KDF_CTX;

typedef struct SM2_CRYPT_CTX {
    SM3_CTX sm3_ctx;  // SM3
    // KDF
    struct {
        uint8_t key_stream[SM3_DIGEST_SIZE];  // 密钥流缓冲区
        int kpos;                             // 密钥流指针
        SM2_KDF_CTX ctx;
    } kdf;
    // 存放中间数据 (x2, y2) 的内存区
    struct {
        uint8_t y[GMLIB_BINT_BITS / 8];  // y2
        int bsize;
    } dot2;  // (x2, y2)
} SM2_CRYPT_CTX;

/// @brief SM2 加密初始化(输出C1)
int sm2_encrypt_init(uint8_t* C1,
                     int* outl,
                     int PC,
                     EC_CTX* ec_ctx,
                     ECPoint* P,
                     SM2_CRYPT_CTX* sm2_crypt_ctx);

/// @brief SM2 加密Update(输出C2)
void sm2_encrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        SM2_CRYPT_CTX* sm2_crypt_ctx);

/// @brief SM2 加密Final(输出C3)
void sm2_encrypt_final(uint8_t* C3, SM2_CRYPT_CTX* sm2_crypt_ctx);

// ========================================
// =========== SM2 解密 ===================
// ========================================

/// @brief SM2 解密初始化
int sm2_decrypt_init(uint8_t* C1,
                     int* read_size,
                     EC_CTX* ec_ctx,
                     BINT* da,
                     SM2_CRYPT_CTX* sm2_crypt_ctx);

/// @brief SM2 解密Update(输出msg)
void sm2_decrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        SM2_CRYPT_CTX* sm2_crypt_ctx);

/// @brief SM2 解密Final
int sm2_decrypt_final(uint8_t* C3, SM2_CRYPT_CTX* sm2_crypt_ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SM2_H
