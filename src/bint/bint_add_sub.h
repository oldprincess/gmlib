#ifndef BINT_ADD_SUB_H
#define BINT_ADD_SUB_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/bint.h>

/// @brief 大整数加法（不考虑符号位）
/// @param[out] r   和 sum
/// @param[in]  n1  被加数 augend
/// @param[in]  n2  加数 addend
/// @return 错误码（0表示无错误）
int bint_uadd(BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数加法（不考虑符号位）
/// @param[out] r   和 sum
/// @param[in]  n1  被加数 augend
/// @param[in]  n2  加数 addend
/// @return 错误码（0表示无错误）
int bint_uadd_u32(BINT* r, BINT* n1, uint32_t n2);

/// @brief 大整数减法（不考虑符号位）(n1>n2)
/// @param[out] r   差 difference
/// @param[in]  n1  被减数 minuend
/// @param[in]  n2  减数 subtrahend
/// @return 错误码（0表示无错误）
int bint_usub(BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数减法（不考虑符号位）(n1>n2)
/// @param[out] r   差 difference
/// @param[in]  n1  被减数 minuend
/// @param[in]  n2  减数 subtrahend
/// @return 错误码（0表示无错误）
int bint_usub_u32(BINT* r, BINT* n1, uint32_t n2);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // BINT_ADD_SUB_H
