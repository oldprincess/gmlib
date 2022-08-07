#ifndef PAD_H
#define PAD_H

#include <stdint.h>

/// @brief PKCS7 填充
/// @param[out] out         输出
/// @param[out] outl        输出长度
/// @param[in]  in          输入
/// @param[in]  inl         输入长度
/// @param[in]  block_size  分组大小
void pkcs7_pad(uint8_t* out, int* outl, uint8_t* in, int inl, int block_size);

/// @brief PKCS7 填充
/// @param[out] out         输出
/// @param[out] outl        输出长度
/// @param[in]  in          输入
/// @param[in]  inl         输入长度
/// @param[in]  block_size  分组大小
/// @return 错误码（0表示无错误）
int pkcs7_unpad(uint8_t* out, int* outl, uint8_t* in, int inl, int block_size);

#endif // PAD_H
