#ifndef GMLIB_SM4_H
#define GMLIB_SM4_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ******************************************
// ************** SM4-ECB *******************
// ******************************************

size_t gmlib_sm4_ecb_encrypt_ctx_size();
void*  gmlib_sm4_ecb_encrypt_ctx_new();
void*  gmlib_sm4_ecb_encrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_ecb_encrypt_ctx_delete(void* ctx);
int    gmlib_sm4_ecb_encrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_ecb_encrypt_get_user_key_len();
size_t gmlib_sm4_ecb_encrypt_get_block_size();
int    gmlib_sm4_ecb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len);
int    gmlib_sm4_ecb_encrypt_ctx_reset(void* ctx);
int    gmlib_sm4_ecb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_ecb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

size_t gmlib_sm4_ecb_decrypt_ctx_size();
void*  gmlib_sm4_ecb_decrypt_ctx_new();
void*  gmlib_sm4_ecb_decrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_ecb_decrypt_ctx_delete(void* ctx);
int    gmlib_sm4_ecb_decrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_ecb_decrypt_get_user_key_len();
size_t gmlib_sm4_ecb_decrypt_get_block_size();
int    gmlib_sm4_ecb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len);
int    gmlib_sm4_ecb_decrypt_ctx_reset(void* ctx);
int    gmlib_sm4_ecb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_ecb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// ************** SM4-CBC *******************
// ******************************************

size_t gmlib_sm4_cbc_encrypt_ctx_size();
void*  gmlib_sm4_cbc_encrypt_ctx_new();
void*  gmlib_sm4_cbc_encrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_cbc_encrypt_ctx_delete(void* ctx);
int    gmlib_sm4_cbc_encrypt_ctx_delete_inplace(void* ctx);
int    gmlib_sm4_cbc_encrypt_ctx_delete(void* ctx);
size_t gmlib_sm4_cbc_encrypt_get_user_key_len();
size_t gmlib_sm4_cbc_encrypt_get_iv_len();
size_t gmlib_sm4_cbc_encrypt_get_block_size();
int    gmlib_sm4_cbc_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_cbc_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_cbc_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_cbc_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

size_t gmlib_sm4_cbc_decrypt_ctx_size();
void*  gmlib_sm4_cbc_decrypt_ctx_new();
void*  gmlib_sm4_cbc_decrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_cbc_decrypt_ctx_delete(void* ctx);
int    gmlib_sm4_cbc_decrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_cbc_decrypt_get_user_key_len();
size_t gmlib_sm4_cbc_decrypt_get_iv_len();
size_t gmlib_sm4_cbc_decrypt_get_block_size();
int    gmlib_sm4_cbc_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_cbc_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_cbc_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_cbc_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// ************** SM4-CFB *******************
// ******************************************

size_t gmlib_sm4_cfb_encrypt_ctx_size();
void*  gmlib_sm4_cfb_encrypt_ctx_new();
void*  gmlib_sm4_cfb_encrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_cfb_encrypt_ctx_delete(void* ctx);
int    gmlib_sm4_cfb_encrypt_ctx_delete_inplace(void* ctx);
int    gmlib_sm4_cfb_encrypt_ctx_delete(void* ctx);
size_t gmlib_sm4_cfb_encrypt_get_user_key_len();
size_t gmlib_sm4_cfb_encrypt_get_iv_len();
size_t gmlib_sm4_cfb_encrypt_get_block_size();
int    gmlib_sm4_cfb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_cfb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_cfb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_cfb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

size_t gmlib_sm4_cfb_decrypt_ctx_size();
void*  gmlib_sm4_cfb_decrypt_ctx_new();
void*  gmlib_sm4_cfb_decrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_cfb_decrypt_ctx_delete(void* ctx);
int    gmlib_sm4_cfb_decrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_cfb_decrypt_get_user_key_len();
size_t gmlib_sm4_cfb_decrypt_get_iv_len();
size_t gmlib_sm4_cfb_decrypt_get_block_size();
int    gmlib_sm4_cfb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_cfb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_cfb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_cfb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// ************** SM4-OFB *******************
// ******************************************

size_t gmlib_sm4_ofb_encrypt_ctx_size();
void*  gmlib_sm4_ofb_encrypt_ctx_new();
void*  gmlib_sm4_ofb_encrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_ofb_encrypt_ctx_delete(void* ctx);
int    gmlib_sm4_ofb_encrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_ofb_encrypt_get_user_key_len();
size_t gmlib_sm4_ofb_encrypt_get_iv_len();
size_t gmlib_sm4_ofb_encrypt_get_block_size();
int    gmlib_sm4_ofb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_ofb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_ofb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_ofb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

size_t gmlib_sm4_ofb_decrypt_ctx_size();
void*  gmlib_sm4_ofb_decrypt_ctx_new();
void*  gmlib_sm4_ofb_decrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_ofb_decrypt_ctx_delete(void* ctx);
int    gmlib_sm4_ofb_decrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_ofb_decrypt_get_user_key_len();
size_t gmlib_sm4_ofb_decrypt_get_iv_len();
size_t gmlib_sm4_ofb_decrypt_get_block_size();
int    gmlib_sm4_ofb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_ofb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_ofb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_ofb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// ************** SM4-CTR *******************
// ******************************************

size_t gmlib_sm4_ctr_encrypt_ctx_size();
void*  gmlib_sm4_ctr_encrypt_ctx_new();
void*  gmlib_sm4_ctr_encrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_ctr_encrypt_ctx_delete(void* ctx);
int    gmlib_sm4_ctr_encrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_ctr_encrypt_get_user_key_len();
size_t gmlib_sm4_ctr_encrypt_get_iv_len();
size_t gmlib_sm4_ctr_encrypt_get_block_size();
int    gmlib_sm4_ctr_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_ctr_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_ctr_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_ctr_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

size_t gmlib_sm4_ctr_decrypt_ctx_size();
void*  gmlib_sm4_ctr_decrypt_ctx_new();
void*  gmlib_sm4_ctr_decrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_ctr_decrypt_ctx_delete(void* ctx);
int    gmlib_sm4_ctr_decrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_ctr_decrypt_get_user_key_len();
size_t gmlib_sm4_ctr_decrypt_get_iv_len();
size_t gmlib_sm4_ctr_decrypt_get_block_size();
int    gmlib_sm4_ctr_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len);
int    gmlib_sm4_ctr_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len);
int    gmlib_sm4_ctr_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_ctr_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// ************** SM4-GCM *******************
// ******************************************

size_t gmlib_sm4_gcm_encrypt_ctx_size();
void*  gmlib_sm4_gcm_encrypt_ctx_new();
void*  gmlib_sm4_gcm_encrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_gcm_encrypt_ctx_delete(void* ctx);
int    gmlib_sm4_gcm_encrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_gcm_encrypt_get_user_key_len();
size_t gmlib_sm4_gcm_encrypt_get_default_iv_len();
size_t gmlib_sm4_gcm_encrypt_get_block_size();
size_t gmlib_sm4_gcm_encrypt_get_tag_len();
int    gmlib_sm4_gcm_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len);
int    gmlib_sm4_gcm_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len);
int    gmlib_sm4_gcm_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_gcm_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);
int    gmlib_sm4_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag);

size_t gmlib_sm4_gcm_decrypt_ctx_size();
void*  gmlib_sm4_gcm_decrypt_ctx_new();
void*  gmlib_sm4_gcm_decrypt_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm4_gcm_decrypt_ctx_delete(void* ctx);
int    gmlib_sm4_gcm_decrypt_ctx_delete_inplace(void* ctx);
size_t gmlib_sm4_gcm_decrypt_get_user_key_len();
size_t gmlib_sm4_gcm_decrypt_get_default_iv_len();
size_t gmlib_sm4_gcm_decrypt_get_block_size();
size_t gmlib_sm4_gcm_decrypt_get_tag_len();
int    gmlib_sm4_gcm_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len);
int    gmlib_sm4_gcm_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len);
int    gmlib_sm4_gcm_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl);
int    gmlib_sm4_gcm_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl);
int    gmlib_sm4_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl);
int    gmlib_sm4_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag);

#ifdef __cplusplus
}
#endif

#endif