/**
 * @file sm4_common.h
 * @brief SM4 普通实现
 *
 */

#ifndef SM4_COMMON_H
#define SM4_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/cipher/sm4.h>

/// @brief SM4 轮密钥生成
/// @param[in]  key     128bit用户密钥
/// @param[out] sm4key  SM4轮密钥
void sm4_common_keyinit(uint8_t* key, SM4_KEY* sm4key);

/// @brief SM4 加密
/// @param[out] out     ciphertext（128bit密文）
/// @param[in]  in      plaintext（128bit明文）
/// @param[in]  sm4key  SM4轮密钥
void sm4_common_encrypt(uint8_t* out, uint8_t* in, SM4_KEY* sm4key);

/// @brief SM4 解密
/// @param[out] out     plaintext（128bit明文）
/// @param[in]  in      ciphertext（128bit密文）
/// @param[in]  sm4key  SM4轮密钥
void sm4_common_decrypt(uint8_t* out, uint8_t* in, SM4_KEY* sm4key);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SM4_COMMON_H
