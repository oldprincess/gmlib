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
int sm2_sign_init(uint8_t* ENTL, uint8_t* ID, EC_CTX* ec_ctx, BINT* da,
                  ECPoint* P, SM2_SIGN_CTX* sm2_sign_ctx);

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
int sm2_verify_init(uint8_t* ENTL, uint8_t* ID, EC_CTX* ec_ctx, ECPoint* P,
                    SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签重置
void sm2_verify_reset(SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签Update
void sm2_verify_update(uint8_t* in, int inl, SM2_VERIFY_CTX* sm2_verify_ctx);

/// @brief SM2 验签Final
int sm2_verify_final(int* status, uint8_t* signature,
                     SM2_VERIFY_CTX* sm2_verify_ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SM2_H
