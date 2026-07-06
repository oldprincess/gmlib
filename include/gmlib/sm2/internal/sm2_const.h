#ifndef SM2_INTERNAL_SM2_CONST_H
#define SM2_INTERNAL_SM2_CONST_H

#include <cstddef>
#include <cstdint>

namespace sm2::internal {

extern const std::uint8_t SM2_DEFAULT_ID[16];
extern const std::size_t  SM2_DEFAULT_ID_LEN;
extern const std::uint8_t SM2_CURVE_P[32];
extern const std::uint8_t SM2_CURVE_A[32];
extern const std::uint8_t SM2_CURVE_B[32];
extern const std::uint8_t SM2_CURVE_N[32];
extern const std::uint8_t SM2_CURVE_GX[32];
extern const std::uint8_t SM2_CURVE_GY[32];

} // namespace sm2::internal

#endif
