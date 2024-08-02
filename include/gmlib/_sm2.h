#ifndef GMLIB_SM2_H
#define GMLIB_SM2_H

#include <gmlib/api.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t gmlib_sm2_sm3_max_sig_size();
size_t gmlib_sm2_sm3_max_ct_size(const uint8_t* in, size_t inl);
int    gmlib_sm2_sm3_max_pt_size(size_t* ret, const uint8_t* in, size_t inl);

size_t gmlib_sm2_sm3_private_key_size();
void*  gmlib_sm2_sm3_private_key_new();
void*  gmlib_sm2_sm3_private_key_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm2_sm3_private_key_gen(void* ctx);
int    gmlib_sm2_sm3_private_key_set(void*          ctx,
                                     const uint8_t* priv_key,
                                     size_t         priv_key_size,
                                     const uint8_t* pub_x,
                                     size_t         pub_x_size,
                                     const uint8_t* pub_y,
                                     size_t         pub_y_size);

int    gmlib_sm2_sm3_private_key_delete(void* ctx);
int    gmlib_sm2_sm3_private_key_delete_inplace(void* ctx);
int    gmlib_sm2_sm3_private_key_sign(void*          ctx,
                                      uint8_t*       sig,
                                      size_t*        outl,
                                      const uint8_t* msg,
                                      size_t         msg_len);
int    gmlib_sm2_sm3_private_key_verify(void*          ctx,
                                        const uint8_t* sig,
                                        size_t         sig_len,
                                        const uint8_t* msg,
                                        size_t         msg_len);
int    gmlib_sm2_sm3_private_key_encrypt(void*          ctx,
                                         uint8_t*       out,
                                         size_t*        outl,
                                         const uint8_t* in,
                                         size_t         inl);
int    gmlib_sm2_sm3_private_key_decrypt(void*          ctx,
                                         uint8_t*       out,
                                         size_t*        outl,
                                         const uint8_t* in,
                                         size_t         inl);

size_t gmlib_sm2_sm3_public_key_size();
void*  gmlib_sm2_sm3_public_key_new();
void*  gmlib_sm2_sm3_public_key_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm2_sm3_public_key_delete(void* ctx);
int    gmlib_sm2_sm3_public_key_delete_inplace(void* ctx);
int    gmlib_sm2_sm3_public_key_verify(void*          ctx,
                                       const uint8_t* sig,
                                       size_t         sig_len,
                                       const uint8_t* msg,
                                       size_t         msg_len);
int    gmlib_sm2_sm3_public_key_encrypt(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);

#ifdef __cplusplus
}
#endif

#endif