#ifndef GCTR_H
#define GCTR_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/cipher/mode.h>

void gctr_init(uint8_t* iv,  ///< [in]  初始向量
               int ivlen,    ///< [in]  初始向量长度
               uint8_t* H,
               GHashTable* ht,
               GCTR_CTX* gctx);

void gctr_update(uint8_t* out,  ///< [out]   输出
                 int* outl,     ///< [out]   输出长度
                 uint8_t* in,   ///< [in]    输入
                 int inl,       ///< [in]    输入长度
                 GCTR_CTX* gctx);

void gctr_final(uint8_t* out, int* outl, GCTR_CTX* gctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // GCTR_H
