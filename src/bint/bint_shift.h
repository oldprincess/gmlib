#ifndef BINT_SHIFT_H
#define BINT_SHIFT_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/bint.h>

/// @brief 大整数内存逻辑左移
/// @param[out] r
/// @param[in]  n
/// @param[in]  bits
void mem_sll(uint32_t* r, int* rsize, uint32_t* d, int dsize, int bits);

/// @brief 大整数内存逻辑右移
/// @param[out] r
/// @param[in]  n
/// @param[in]  bits
void mem_srl(uint32_t* r, int* rsize, uint32_t* d, int dsize, int bits);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // BINT_SHIFT_H
