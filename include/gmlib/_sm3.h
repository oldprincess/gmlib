#ifndef GMLIB_SM3_H
#define GMLIB_SM3_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ******************************************
// ************** SM3-HASH ******************
// ******************************************

size_t gmlib_sm3_hash_ctx_size();
void*  gmlib_sm3_hash_ctx_new();
void*  gmlib_sm3_hash_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm3_hash_ctx_delete(void* ctx);
int    gmlib_sm3_hash_ctx_delete_inplace(void* ctx);
size_t gmlib_sm3_hash_get_digest_size();
size_t gmlib_sm3_hash_get_block_size();
int    gmlib_sm3_hash_ctx_init(void* ctx);
int    gmlib_sm3_hash_ctx_reset(void* ctx);
int    gmlib_sm3_hash_ctx_update(void* ctx, const uint8_t* in, size_t inl);
int    gmlib_sm3_hash_ctx_final_ex(void*          ctx,
                                   uint8_t*       out,
                                   size_t*        outl,
                                   const uint8_t* in,
                                   size_t         inl);
int    gmlib_sm3_hash_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// ************** SM3-HMAC ******************
// ******************************************

size_t gmlib_sm3_hmac_ctx_size();
void*  gmlib_sm3_hmac_ctx_new();
void*  gmlib_sm3_hmac_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm3_hmac_ctx_delete(void* ctx);
int    gmlib_sm3_hmac_ctx_delete_inplace(void* ctx);
size_t gmlib_sm3_hmac_get_digest_size();
int    gmlib_sm3_hmac_ctx_init(void*          ctx,
                               const uint8_t* user_key,
                               size_t         user_key_len);
int    gmlib_sm3_hmac_ctx_reset(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len);
int    gmlib_sm3_hmac_ctx_update(void* ctx, const uint8_t* in, size_t inl);
int    gmlib_sm3_hmac_ctx_final_ex(void*          ctx,
                                   uint8_t*       out,
                                   size_t*        outl,
                                   const uint8_t* in,
                                   size_t         inl);
int    gmlib_sm3_hmac_ctx_final(void* ctx, uint8_t* out, size_t* outl);

// ******************************************
// *********** SM3-HASH-DRBG ****************
// ******************************************

size_t gmlib_sm3_hash_drbg_ctx_size();
void*  gmlib_sm3_hash_drbg_ctx_new();
void*  gmlib_sm3_hash_drbg_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm3_hash_drbg_ctx_delete(void* ctx);
int    gmlib_sm3_hash_drbg_ctx_delete_inplace(void* ctx);
int    gmlib_sm3_hash_drbg_ctx_gen(void* ctx, void* out, size_t len);

// ******************************************
// *********** SM3-HMAC-DRBG ****************
// ******************************************

size_t gmlib_sm3_hmac_drbg_ctx_size();
void*  gmlib_sm3_hmac_drbg_ctx_new();
void*  gmlib_sm3_hmac_drbg_ctx_new_inplace(void* buf, size_t buf_size);
int    gmlib_sm3_hmac_drbg_ctx_delete(void* ctx);
int    gmlib_sm3_hmac_drbg_ctx_delete_inplace(void* ctx);
int    gmlib_sm3_hmac_drbg_ctx_gen(void* ctx, void* out, size_t len);

#ifdef __cplusplus
}
#endif

#endif