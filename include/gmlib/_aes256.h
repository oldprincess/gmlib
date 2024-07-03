#ifndef GMLIB_AES256_H
#define GMLIB_AES256_H

#include <gmlib/api.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ******************************************
// *********** AES256-ECB *******************
// ******************************************

GMLIB_API size_t gmlib_aes128_ecb_encrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_ecb_encrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_ecb_encrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_ecb_encrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_ecb_encrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_ecb_encrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_ecb_encrypt_get_block_size();
GMLIB_API int    gmlib_aes128_ecb_encrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len);
GMLIB_API int    gmlib_aes128_ecb_encrypt_ctx_reset(void* ctx);
GMLIB_API int    gmlib_aes128_ecb_encrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_ecb_encrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_ecb_encrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

GMLIB_API size_t gmlib_aes128_ecb_decrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_ecb_decrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_ecb_decrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_ecb_decrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_ecb_decrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_ecb_decrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_ecb_decrypt_get_block_size();
GMLIB_API int    gmlib_aes128_ecb_decrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len);
GMLIB_API int    gmlib_aes128_ecb_decrypt_ctx_reset(void* ctx);
GMLIB_API int    gmlib_aes128_ecb_decrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_ecb_decrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_ecb_decrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

// ******************************************
// *********** AES256-CBC *******************
// ******************************************

GMLIB_API size_t gmlib_aes128_cbc_encrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_cbc_encrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_cbc_encrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_delete_inplace(void* ctx);
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_delete(void* ctx);
GMLIB_API size_t gmlib_aes128_cbc_encrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_cbc_encrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_cbc_encrypt_get_block_size();
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_cbc_encrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

GMLIB_API size_t gmlib_aes128_cbc_decrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_cbc_decrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_cbc_decrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_cbc_decrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_cbc_decrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_cbc_decrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_cbc_decrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_cbc_decrypt_get_block_size();
GMLIB_API int    gmlib_aes128_cbc_decrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_cbc_decrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_cbc_decrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_cbc_decrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_cbc_decrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

// ******************************************
// *********** AES256-CFB *******************
// ******************************************

GMLIB_API size_t gmlib_aes128_cfb_encrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_cfb_encrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_cfb_encrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_delete_inplace(void* ctx);
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_delete(void* ctx);
GMLIB_API size_t gmlib_aes128_cfb_encrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_cfb_encrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_cfb_encrypt_get_block_size();
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_cfb_encrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

GMLIB_API size_t gmlib_aes128_cfb_decrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_cfb_decrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_cfb_decrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_cfb_decrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_cfb_decrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_cfb_decrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_cfb_decrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_cfb_decrypt_get_block_size();
GMLIB_API int    gmlib_aes128_cfb_decrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_cfb_decrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_cfb_decrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_cfb_decrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_cfb_decrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

// ******************************************
// *********** AES256-OFB *******************
// ******************************************

GMLIB_API size_t gmlib_aes128_ofb_encrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_ofb_encrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_ofb_encrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_ofb_encrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_ofb_encrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_ofb_encrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_ofb_encrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_ofb_encrypt_get_block_size();
GMLIB_API int    gmlib_aes128_ofb_encrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_ofb_encrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_ofb_encrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_ofb_encrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_ofb_encrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

GMLIB_API size_t gmlib_aes128_ofb_decrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_ofb_decrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_ofb_decrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_ofb_decrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_ofb_decrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_ofb_decrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_ofb_decrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_ofb_decrypt_get_block_size();
GMLIB_API int    gmlib_aes128_ofb_decrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_ofb_decrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_ofb_decrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_ofb_decrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_ofb_decrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

// ******************************************
// *********** AES256-CTR *******************
// ******************************************

GMLIB_API size_t gmlib_aes128_ctr_encrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_ctr_encrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_ctr_encrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_ctr_encrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_ctr_encrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_ctr_encrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_ctr_encrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_ctr_encrypt_get_block_size();
GMLIB_API int    gmlib_aes128_ctr_encrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_ctr_encrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_ctr_encrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_ctr_encrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_ctr_encrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

GMLIB_API size_t gmlib_aes128_ctr_decrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_ctr_decrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_ctr_decrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_ctr_decrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_ctr_decrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_ctr_decrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_ctr_decrypt_get_iv_len();
GMLIB_API size_t gmlib_aes128_ctr_decrypt_get_block_size();
GMLIB_API int    gmlib_aes128_ctr_decrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len);
GMLIB_API int    gmlib_aes128_ctr_decrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len);
GMLIB_API int    gmlib_aes128_ctr_decrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_ctr_decrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_ctr_decrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);

// ******************************************
// *********** AES256-GCM *******************
// ******************************************

GMLIB_API size_t gmlib_aes128_gcm_encrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_gcm_encrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_gcm_encrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_gcm_encrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_gcm_encrypt_get_default_iv_len();
GMLIB_API size_t gmlib_aes128_gcm_encrypt_get_block_size();
GMLIB_API size_t gmlib_aes128_gcm_encrypt_get_tag_len();
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len,
                                                   const uint8_t* aad,
                                                   size_t         aad_len);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len,
                                                    const uint8_t* aad,
                                                    size_t         aad_len);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag);

GMLIB_API size_t gmlib_aes128_gcm_decrypt_ctx_size();
GMLIB_API void*  gmlib_aes128_gcm_decrypt_ctx_new();
GMLIB_API void*  gmlib_aes128_gcm_decrypt_ctx_new_inplace(void*  buf,
                                                          size_t buf_size);
GMLIB_API int    gmlib_aes128_gcm_decrypt_ctx_delete(void* ctx);
GMLIB_API int    gmlib_aes128_gcm_decrypt_ctx_delete_inplace(void* ctx);
GMLIB_API size_t gmlib_aes128_gcm_decrypt_get_user_key_len();
GMLIB_API size_t gmlib_aes128_gcm_decrypt_get_default_iv_len();
GMLIB_API size_t gmlib_aes128_gcm_decrypt_get_block_size();
GMLIB_API size_t gmlib_aes128_gcm_decrypt_get_tag_len();
GMLIB_API int    gmlib_aes128_gcm_decrypt_ctx_init(void*          ctx,
                                                   const uint8_t* user_key,
                                                   size_t         user_key_len,
                                                   const uint8_t* iv,
                                                   size_t         iv_len,
                                                   const uint8_t* aad,
                                                   size_t         aad_len);
GMLIB_API int    gmlib_aes128_gcm_decrypt_ctx_reset(void*          ctx,
                                                    const uint8_t* iv,
                                                    size_t         iv_len,
                                                    const uint8_t* aad,
                                                    size_t         aad_len);
GMLIB_API int    gmlib_aes128_gcm_decrypt_ctx_update(void*          ctx,
                                                     uint8_t*       out,
                                                     size_t*        outl,
                                                     const uint8_t* in,
                                                     size_t         inl);
GMLIB_API int    gmlib_aes128_gcm_decrypt_ctx_final_ex(void*          ctx,
                                                       uint8_t*       out,
                                                       size_t*        outl,
                                                       const uint8_t* in,
                                                       size_t         inl);
GMLIB_API int    gmlib_aes128_gcm_decrypt_ctx_final(void*    ctx,
                                                    uint8_t* out,
                                                    size_t*  outl);
GMLIB_API int    gmlib_aes128_gcm_encrypt_ctx_set_tag(void*          ctx,
                                                      const uint8_t* tag);

#ifdef __cplusplus
}
#endif

#endif