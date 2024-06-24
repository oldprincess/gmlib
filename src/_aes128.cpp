#include <gmlib/_aes128.h>
#include <gmlib/_debug.h>
#include <gmlib/aes/aes_mode.h>

#include "c_api_cipher.h"

using namespace aes;

// ******************************************
// ************** AES128-ECB ****************
// ******************************************

size_t gmlib_aes128_ecb_encrypt_ctx_size()
{
    return c_api::cipher_ecb_encrypt_ctx_size<AES128EcbEncryptor>();
}

void* gmlib_aes128_ecb_encrypt_ctx_alloc()
{
    return c_api::cipher_ecb_encrypt_ctx_alloc<AES128EcbEncryptor>();
}

int gmlib_aes128_ecb_encrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_free<AES128EcbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_ecb_encrypt_get_user_key_len()
{
    return c_api::cipher_ecb_encrypt_get_user_key_len<AES128EcbEncryptor>();
}

size_t gmlib_aes128_ecb_encrypt_get_block_size()
{
    return c_api::cipher_ecb_encrypt_get_block_size<AES128EcbEncryptor>();
}

int gmlib_aes128_ecb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_init<AES128EcbEncryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_reset<AES128EcbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_update<AES128EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final_ex<AES128EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final<AES128EcbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes128_ecb_decrypt_ctx_size()
{
    return c_api::cipher_ecb_decrypt_ctx_size<AES128EcbDecryptor>();
}

void* gmlib_aes128_ecb_decrypt_ctx_alloc()
{
    return c_api::cipher_ecb_decrypt_ctx_alloc<AES128EcbDecryptor>();
}

int gmlib_aes128_ecb_decrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_free<AES128EcbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_ecb_decrypt_get_user_key_len()
{
    return c_api::cipher_ecb_decrypt_get_user_key_len<AES128EcbDecryptor>();
}

size_t gmlib_aes128_ecb_decrypt_get_block_size()
{
    return c_api::cipher_ecb_decrypt_get_block_size<AES128EcbDecryptor>();
}

int gmlib_aes128_ecb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_init<AES128EcbDecryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_reset<AES128EcbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_update<AES128EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final_ex<AES128EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final<AES128EcbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES128-CBC ****************
// ******************************************

size_t gmlib_aes128_cbc_encrypt_ctx_size()
{
    return c_api::cipher_cbc_encrypt_ctx_size<AES128CbcEncryptor>();
}

void* gmlib_aes128_cbc_encrypt_ctx_alloc()
{
    return c_api::cipher_cbc_encrypt_ctx_alloc<AES128CbcEncryptor>();
}

int gmlib_aes128_cbc_encrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_encrypt_ctx_free<AES128CbcEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_cbc_encrypt_get_user_key_len()
{
    return c_api::cipher_cbc_encrypt_get_user_key_len<AES128CbcEncryptor>();
}

size_t gmlib_aes128_cbc_encrypt_get_iv_len()
{
    return c_api::cipher_cbc_encrypt_get_iv_len<AES128CbcEncryptor>();
}

size_t gmlib_aes128_cbc_encrypt_get_block_size()
{
    return c_api::cipher_cbc_encrypt_get_block_size<AES128CbcEncryptor>();
}

int gmlib_aes128_cbc_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_init<AES128CbcEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_reset<AES128CbcEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_update<AES128CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final_ex<AES128CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final<AES128CbcEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes128_cbc_decrypt_ctx_size()
{
    return c_api::cipher_cbc_decrypt_ctx_size<AES128CbcDecryptor>();
}

void* gmlib_aes128_cbc_decrypt_ctx_alloc()
{
    return c_api::cipher_cbc_decrypt_ctx_alloc<AES128CbcDecryptor>();
}

int gmlib_aes128_cbc_decrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_decrypt_ctx_free<AES128CbcDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_cbc_decrypt_get_user_key_len()
{
    return c_api::cipher_cbc_decrypt_get_user_key_len<AES128CbcDecryptor>();
}

size_t gmlib_aes128_cbc_decrypt_get_iv_len()
{
    return c_api::cipher_cbc_decrypt_get_iv_len<AES128CbcDecryptor>();
}

size_t gmlib_aes128_cbc_decrypt_get_block_size()
{
    return c_api::cipher_cbc_decrypt_get_block_size<AES128CbcDecryptor>();
}

int gmlib_aes128_cbc_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_init<AES128CbcDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_reset<AES128CbcDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_update<AES128CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final_ex<AES128CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final<AES128CbcDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES128-CFB ****************
// ******************************************

size_t gmlib_aes128_cfb_encrypt_ctx_size()
{
    return c_api::cipher_cfb_encrypt_ctx_size<AES128CfbEncryptor>();
}

void* gmlib_aes128_cfb_encrypt_ctx_alloc()
{
    return c_api::cipher_cfb_encrypt_ctx_alloc<AES128CfbEncryptor>();
}

int gmlib_aes128_cfb_encrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_encrypt_ctx_free<AES128CfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_cfb_encrypt_get_user_key_len()
{
    return c_api::cipher_cfb_encrypt_get_user_key_len<AES128CfbEncryptor>();
}

size_t gmlib_aes128_cfb_encrypt_get_iv_len()
{
    return c_api::cipher_cfb_encrypt_get_iv_len<AES128CfbEncryptor>();
}

size_t gmlib_aes128_cfb_encrypt_get_block_size()
{
    return c_api::cipher_cfb_encrypt_get_block_size<AES128CfbEncryptor>();
}

int gmlib_aes128_cfb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_init<AES128CfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_reset<AES128CfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_update<AES128CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final_ex<AES128CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final<AES128CfbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes128_cfb_decrypt_ctx_size()
{
    return c_api::cipher_cfb_decrypt_ctx_size<AES128CfbDecryptor>();
}

void* gmlib_aes128_cfb_decrypt_ctx_alloc()
{
    return c_api::cipher_cfb_decrypt_ctx_alloc<AES128CfbDecryptor>();
}

int gmlib_aes128_cfb_decrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_decrypt_ctx_free<AES128CfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_cfb_decrypt_get_user_key_len()
{
    return c_api::cipher_cfb_decrypt_get_user_key_len<AES128CfbDecryptor>();
}

size_t gmlib_aes128_cfb_decrypt_get_iv_len()
{
    return c_api::cipher_cfb_decrypt_get_iv_len<AES128CfbDecryptor>();
}

size_t gmlib_aes128_cfb_decrypt_get_block_size()
{
    return c_api::cipher_cfb_decrypt_get_block_size<AES128CfbDecryptor>();
}

int gmlib_aes128_cfb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_init<AES128CfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_reset<AES128CfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_update<AES128CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final_ex<AES128CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final<AES128CfbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES128-OFB ****************
// ******************************************

size_t gmlib_aes128_ofb_encrypt_ctx_size()
{
    return c_api::cipher_ofb_encrypt_ctx_size<AES128OfbEncryptor>();
}

void* gmlib_aes128_ofb_encrypt_ctx_alloc()
{
    return c_api::cipher_ofb_encrypt_ctx_alloc<AES128OfbEncryptor>();
}

int gmlib_aes128_ofb_encrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_encrypt_ctx_free<AES128OfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_ofb_encrypt_get_user_key_len()
{
    return c_api::cipher_ofb_encrypt_get_user_key_len<AES128OfbEncryptor>();
}

size_t gmlib_aes128_ofb_encrypt_get_iv_len()
{
    return c_api::cipher_ofb_encrypt_get_iv_len<AES128OfbEncryptor>();
}

size_t gmlib_aes128_ofb_encrypt_get_block_size()
{
    return c_api::cipher_ofb_encrypt_get_block_size<AES128OfbEncryptor>();
}

int gmlib_aes128_ofb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_init<AES128OfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_reset<AES128OfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_update<AES128OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final_ex<AES128OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final<AES128OfbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes128_ofb_decrypt_ctx_size()
{
    return c_api::cipher_ofb_decrypt_ctx_size<AES128OfbDecryptor>();
}

void* gmlib_aes128_ofb_decrypt_ctx_alloc()
{
    return c_api::cipher_ofb_decrypt_ctx_alloc<AES128OfbDecryptor>();
}

int gmlib_aes128_ofb_decrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_decrypt_ctx_free<AES128OfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_ofb_decrypt_get_user_key_len()
{
    return c_api::cipher_ofb_decrypt_get_user_key_len<AES128OfbDecryptor>();
}

size_t gmlib_aes128_ofb_decrypt_get_iv_len()
{
    return c_api::cipher_ofb_decrypt_get_iv_len<AES128OfbDecryptor>();
}

size_t gmlib_aes128_ofb_decrypt_get_block_size()
{
    return c_api::cipher_ofb_decrypt_get_block_size<AES128OfbDecryptor>();
}

int gmlib_aes128_ofb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_init<AES128OfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_reset<AES128OfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_update<AES128OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final_ex<AES128OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final<AES128OfbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES128-CTR ****************
// ******************************************

size_t gmlib_aes128_ctr_encrypt_ctx_size()
{
    return c_api::cipher_ctr_encrypt_ctx_size<AES128CtrEncryptor>();
}

void* gmlib_aes128_ctr_encrypt_ctx_alloc()
{
    return c_api::cipher_ctr_encrypt_ctx_alloc<AES128CtrEncryptor>();
}

int gmlib_aes128_ctr_encrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_encrypt_ctx_free<AES128CtrEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_ctr_encrypt_get_user_key_len()
{
    return c_api::cipher_ctr_encrypt_get_user_key_len<AES128CtrEncryptor>();
}

size_t gmlib_aes128_ctr_encrypt_get_iv_len()
{
    return c_api::cipher_ctr_encrypt_get_iv_len<AES128CtrEncryptor>();
}

size_t gmlib_aes128_ctr_encrypt_get_block_size()
{
    return c_api::cipher_ctr_encrypt_get_block_size<AES128CtrEncryptor>();
}

int gmlib_aes128_ctr_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_init<AES128CtrEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_reset<AES128CtrEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_update<AES128CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final_ex<AES128CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final<AES128CtrEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes128_ctr_decrypt_ctx_size()
{
    return c_api::cipher_ctr_decrypt_ctx_size<AES128CtrDecryptor>();
}

void* gmlib_aes128_ctr_decrypt_ctx_alloc()
{
    return c_api::cipher_ctr_decrypt_ctx_alloc<AES128CtrDecryptor>();
}

int gmlib_aes128_ctr_decrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_decrypt_ctx_free<AES128CtrDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_ctr_decrypt_get_user_key_len()
{
    return c_api::cipher_ctr_decrypt_get_user_key_len<AES128CtrDecryptor>();
}

size_t gmlib_aes128_ctr_decrypt_get_iv_len()
{
    return c_api::cipher_ctr_decrypt_get_iv_len<AES128CtrDecryptor>();
}

size_t gmlib_aes128_ctr_decrypt_get_block_size()
{
    return c_api::cipher_ctr_decrypt_get_block_size<AES128CtrDecryptor>();
}

int gmlib_aes128_ctr_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_init<AES128CtrDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_reset<AES128CtrDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_update<AES128CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final_ex<AES128CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final<AES128CtrDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES128-GCM ****************
// ******************************************

size_t gmlib_aes128_gcm_encrypt_ctx_size()
{
    return c_api::cipher_gcm_encrypt_ctx_size<AES128GcmEncryptor>();
}

void* gmlib_aes128_gcm_encrypt_ctx_alloc()
{
    return c_api::cipher_gcm_encrypt_ctx_alloc<AES128GcmEncryptor>();
}

int gmlib_aes128_gcm_encrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_free<AES128GcmEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_gcm_encrypt_get_user_key_len()
{
    return c_api::cipher_gcm_encrypt_get_user_key_len<AES128GcmEncryptor>();
}

size_t gmlib_aes128_gcm_encrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_encrypt_get_default_iv_len<AES128GcmEncryptor>();
}

size_t gmlib_aes128_gcm_encrypt_get_block_size()
{
    return c_api::cipher_gcm_encrypt_get_block_size<AES128GcmEncryptor>();
}

size_t gmlib_aes128_gcm_encrypt_get_tag_len()
{
    return c_api::cipher_gcm_encrypt_get_tag_len<AES128GcmEncryptor>();
}

int gmlib_aes128_gcm_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_init<AES128GcmEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_reset<AES128GcmEncryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_update<AES128GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final_ex<AES128GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final<AES128GcmEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_get_tag<AES128GcmEncryptor>(
                    ctx, tag) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes128_gcm_decrypt_ctx_size()
{
    return c_api::cipher_gcm_decrypt_ctx_size<AES128GcmDecryptor>();
}

void* gmlib_aes128_gcm_decrypt_ctx_alloc()
{
    return c_api::cipher_gcm_decrypt_ctx_alloc<AES128GcmDecryptor>();
}

int gmlib_aes128_gcm_decrypt_ctx_free(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_decrypt_ctx_free<AES128GcmDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_aes128_gcm_decrypt_get_user_key_len()
{
    return c_api::cipher_gcm_decrypt_get_user_key_len<AES128GcmDecryptor>();
}

size_t gmlib_aes128_gcm_decrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_decrypt_get_default_iv_len<AES128GcmDecryptor>();
}

size_t gmlib_aes128_gcm_decrypt_get_block_size()
{
    return c_api::cipher_gcm_decrypt_get_block_size<AES128GcmDecryptor>();
}

size_t gmlib_aes128_gcm_decrypt_get_tag_len()
{
    return c_api::cipher_gcm_decrypt_get_tag_len<AES128GcmDecryptor>();
}

int gmlib_aes128_gcm_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_init<AES128GcmDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_reset<AES128GcmDecryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_update<AES128GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final_ex<AES128GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final<AES128GcmDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_set_tag<AES128GcmDecryptor>(
                    ctx, tag) == 0,
                { return -1; });
    return 0;
}
