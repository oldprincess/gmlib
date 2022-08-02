#ifndef BINT_MUL_H
#define BINT_MUL_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/bint.h>

/// @brief 大整数乘法（不考虑符号位）
/// @param[out] r   乘积 product
/// @param[in]  n1  被乘数 multiplicand
/// @param[in]  n2  乘数 multiplier
/// @return 错误码（0表示无错误）
int bint_umul(BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数乘法（不考虑符号位）
/// @param[out] r   乘积 product
/// @param[in]  n1  被乘数 multiplicand
/// @param[in]  n2  乘数 multiplier
/// @return 错误码（0表示无错误）
int bint_umul_u32(BINT* r, BINT* n1, uint32_t n2);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // BINT_MUL_H
