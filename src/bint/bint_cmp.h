#ifndef BINT_CMP_H
#define BINT_CMP_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/bint.h>

/// @brief 大整数比较（无视符号位）
/// @param[in] n1
/// @param[in] n2
/// @return 1(n1>n2), 0(n1=n2), -1(n1<n2)
int bint_ucmp(BINT* n1, BINT* n2);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // BINT_CMP_H
