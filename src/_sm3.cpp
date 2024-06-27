#include <gmlib/_sm3.h>
#include <gmlib/hash_lib/hmac.h>
#include <gmlib/rng/drbg.h>
#include <gmlib/sm3/sm3.h>

#include "c_api_hash.h"

using hash_lib::HMac;
using rng::HashDrbg;
using rng::HMacDrbg;
using sm3::SM3;

using SM3HMac     = HMac<SM3>;
using SM3HashDrbg = HashDrbg<SM3>;
using SM3HMacDrbg = HMacDrbg<SM3>;

// ******************************************
// ************** SM3-HASH ******************
// ******************************************

GMLIB_API size_t gmlib_sm3_hash_ctx_size()
{
    return c_api::hash_ctx_size<SM3>();
}

GMLIB_API void* gmlib_sm3_hash_ctx_alloc()
{
    return c_api::hash_ctx_alloc<SM3>();
}

GMLIB_API int gmlib_sm3_hash_ctx_free(void* ctx)
{
    GMLIB_CHECK(c_api::hash_ctx_free<SM3>(ctx) == 0, { return -1; });
    return 0;
}

GMLIB_API size_t gmlib_sm3_hash_get_digest_size()
{
    return c_api::hash_get_digest_size<SM3>();
}

GMLIB_API size_t gmlib_sm3_hash_get_block_size()
{
    return c_api::hash_get_block_size<SM3>();
}

GMLIB_API int gmlib_sm3_hash_ctx_init(void* ctx)
{
    GMLIB_CHECK(c_api::hash_ctx_init<SM3>(ctx) == 0, { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hash_ctx_reset(void* ctx)
{
    GMLIB_CHECK(c_api::hash_ctx_reset<SM3>(ctx) == 0, { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hash_ctx_update(void*          ctx,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::hash_ctx_update<SM3>(ctx, in, inl) == 0, { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hash_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::hash_ctx_final_ex<SM3>(ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hash_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::hash_ctx_final<SM3>(ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** SM3-HMAC ******************
// ******************************************

GMLIB_API size_t gmlib_sm3_hmac_ctx_size()
{
    return c_api::hmac_ctx_size<SM3HMac>();
}

GMLIB_API void* gmlib_sm3_hmac_ctx_alloc()
{
    return c_api::hmac_ctx_alloc<SM3HMac>();
}

GMLIB_API int gmlib_sm3_hmac_ctx_free(void* ctx)
{
    GMLIB_CHECK(c_api::hmac_ctx_free<SM3HMac>(ctx) == 0, { return -1; });
    return 0;
}

GMLIB_API size_t gmlib_sm3_hmac_get_digest_size()
{
    return c_api::hmac_get_digest_size<SM3HMac>();
}

GMLIB_API int gmlib_sm3_hmac_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    GMLIB_CHECK(c_api::hmac_ctx_init<SM3HMac>(ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hmac_ctx_reset(void*          ctx,
                                       const uint8_t* user_key,
                                       size_t         user_key_len)
{
    GMLIB_CHECK(
        c_api::hmac_ctx_reset<SM3HMac>(ctx, user_key, user_key_len) == 0,
        { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hmac_ctx_update(void*          ctx,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::hmac_ctx_update<SM3HMac>(ctx, in, inl) == 0,
                { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hmac_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::hmac_ctx_final_ex<SM3HMac>(ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hmac_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::hmac_ctx_final<SM3HMac>(ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// *********** SM3-HASH-DRBG ****************
// ******************************************

GMLIB_API void* gmlib_sm3_hash_drbg_ctx_new()
{
    return c_api::hash_drbg_ctx_new<SM3HashDrbg>();
}

GMLIB_API int gmlib_sm3_hash_drbg_ctx_free(void* ctx)
{
    GMLIB_CHECK(c_api::hash_drbg_ctx_free<SM3HashDrbg>(ctx) == 0,
                { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hash_drbg_ctx_gen(void* ctx, void* out, size_t len)
{
    GMLIB_CHECK(c_api::hash_drbg_ctx_gen<SM3HashDrbg>(ctx, out, len) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// *********** SM3-HMAC-DRBG ****************
// ******************************************

GMLIB_API void* gmlib_sm3_hmac_drbg_ctx_new()
{
    return c_api::hmac_drbg_ctx_new<SM3HMacDrbg>();
}

GMLIB_API int gmlib_sm3_hmac_drbg_ctx_free(void* ctx)
{
    GMLIB_CHECK(c_api::hmac_drbg_ctx_free<SM3HMacDrbg>(ctx) == 0,
                { return -1; });
    return 0;
}

GMLIB_API int gmlib_sm3_hmac_drbg_ctx_gen(void* ctx, void* out, size_t len)
{
    GMLIB_CHECK(c_api::hmac_drbg_ctx_gen<SM3HMacDrbg>(ctx, out, len) == 0,
                { return -1; });
    return 0;
}
