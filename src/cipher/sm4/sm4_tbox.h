/**
 * @file sm4_tbox.h
 * @brief SM4 查表优化实现
 *
 * 参考资料：SM4的快速软件实现技术. 郎欢, 张蕾, 吴文玲 <br>
 */

#ifndef SM4_TBOX_H
#define SM4_TBOX_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/cipher/sm4.h>

/// @brief SM4 加密
/// @param[out] out     ciphertext（128bit密文）
/// @param[in]  in      plaintext（128bit明文）
/// @param[in]  sm4key  SM4轮密钥
void sm4_tbox_encrypt(uint8_t* out, uint8_t* in, SM4_KEY* sm4key);

/// @brief SM4 解密
/// @param[out] out     plaintext（128bit明文）
/// @param[in]  in      ciphertext（128bit密文）
/// @param[in]  sm4key  SM4轮密钥
void sm4_tbox_decrypt(uint8_t* out, uint8_t* in, SM4_KEY* sm4key);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // SM4_TBOX_H
