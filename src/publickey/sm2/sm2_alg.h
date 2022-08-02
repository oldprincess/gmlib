#ifndef SM2_ALG_H
#define SM2_ALG_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
#include <gmlib/ec.h>

/// @brief 计算 Z = SM3(ENTL || ID || a || b || G.x || G.y || P.x || P.y)
int sm2_calculate_z(uint8_t* out,
                    uint8_t* ENTL,
                    uint8_t* ID,
                    ECPoint* P,
                    EC_CTX* ec_ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // SM2_ALG_H
