#ifndef GMLIB_SM3_H
#define GMLIB_SM3_H

#include <gmlib/api.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ******************************************
// ************** SM3-HASH ******************
// ******************************************

GMLIB_API size_t gmlib_sm3_hash_ctx_size();
GMLIB_API void*  gmlib_sm3_hash_ctx_alloc();
GMLIB_API int    gmlib_sm3_hash_ctx_free(void* ctx);
GMLIB_API size_t gmlib_sm3_hash_get_digest_size();
GMLIB_API size_t gmlib_sm3_hash_get_block_size();
GMLIB_API int    gmlib_sm3_hash_ctx_init(void* ctx);
GMLIB_API int    gmlib_sm3_hash_ctx_reset(void* ctx);
GMLIB_API int    gmlib_sm3_hash_ctx_update(void*          ctx,
                                           const uint8_t* in,
                                           size_t         inl);
GMLIB_API int    gmlib_sm3_hash_ctx_final_ex(void*          ctx,
                                             uint8_t*       out,
                                             size_t*        outl,
                                             const uint8_t* in,
                                             size_t         inl);
GMLIB_API int gmlib_sm3_hash_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// ************** SM3-HMAC ******************
// ******************************************

GMLIB_API size_t gmlib_sm3_hmac_ctx_size();
GMLIB_API void*  gmlib_sm3_hmac_ctx_alloc();
GMLIB_API int    gmlib_sm3_hmac_ctx_free(void* ctx);
GMLIB_API size_t gmlib_sm3_hmac_get_digest_size();
GMLIB_API int    gmlib_sm3_hmac_ctx_init(void*          ctx,
                                         const uint8_t* user_key,
                                         size_t         user_key_len);
GMLIB_API int    gmlib_sm3_hmac_ctx_reset(void*          ctx,
                                          const uint8_t* user_key,
                                          size_t         user_key_len);
GMLIB_API int    gmlib_sm3_hmac_ctx_update(void*          ctx,
                                           const uint8_t* in,
                                           size_t         inl);
GMLIB_API int    gmlib_sm3_hmac_ctx_final_ex(void*          ctx,
                                             uint8_t*       out,
                                             size_t*        outl,
                                             const uint8_t* in,
                                             size_t         inl);
GMLIB_API int gmlib_sm3_hmac_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// *********** SM3-HASH-DRBG ****************
// ******************************************

GMLIB_API void* gmlib_sm3_hash_drbg_ctx_new();
GMLIB_API int   gmlib_sm3_hash_drbg_ctx_free(void* ctx);
GMLIB_API int   gmlib_sm3_hash_drbg_ctx_gen(void* ctx, void* out, size_t len);

// ******************************************
// *********** SM3-HMAC-DRBG ****************
// ******************************************

GMLIB_API void* gmlib_sm3_hmac_drbg_ctx_new();
GMLIB_API int   gmlib_sm3_hmac_drbg_ctx_free(void* ctx);
GMLIB_API int   gmlib_sm3_hmac_drbg_ctx_gen(void* ctx, void* out, size_t len);

#ifdef __cplusplus
}
#endif

#endif