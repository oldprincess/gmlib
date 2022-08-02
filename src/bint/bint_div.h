#ifndef BINT_DIV_H
#define BINT_DIV_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/bint.h>

/// @brief 大整数除法(n1>n2, n2!=0, n2.dsize>=2)（不考虑符号位）
/// @param[out] q   商（可以为NULL） quotient
/// @param[out] r   余数（可以为NULL） remainder
/// @param[in]  n1  被除数 dividend
/// @param[in]  n2  除数 divisor
void bint_udiv_knuth(BINT* q, BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数除法(n2!=0)（不考虑符号位）
/// @param[out] q   商（可以为NULL） quotient
/// @param[out] r   余数（可以为NULL） remainder
/// @param[in]  n1  被除数 dividend
/// @param[in]  n2  除数 divisor
void bint_udiv_u32(BINT* q, uint32_t* r, BINT* n1, uint32_t n2);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // BINT_DIV_H
