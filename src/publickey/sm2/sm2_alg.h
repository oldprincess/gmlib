#ifndef SM2_ALG_H
#define SM2_ALG_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
#include <gmlib/hash/sm3.h>
#include <gmlib/publickey/sm2.h>

/// @brief 计算 Z = SM3(ENTL || ID || a || b || G.x || G.y || P.x || P.y)
int sm2_calculate_z(uint8_t* out,
                    uint8_t ENTL[2],
                    uint8_t* ID,
                    ECPoint* P,
                    EC_CTX* ec_ctx);

/// @brief SM2 KDF 初始化
void sm2_kdf_init(SM2_KDF_CTX* kdf_ctx);

/// @brief SM2 KDF 初始化
void sm2_kdf_init_update(uint8_t* in, int inl, SM2_KDF_CTX* kdf_ctx);

/// @brief SM2 KDF 生成下一256比特密钥流
void sm2_kdf_next(uint8_t* out, SM2_KDF_CTX* kdf_ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // SM2_ALG_H
