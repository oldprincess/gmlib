#include <gmlib/_aes256.h>
#include <gmlib/_debug.h>
#include <gmlib/aes/aes_mode.h>

#include "c_api_cipher.h"

using namespace aes;

// ******************************************
// ************** AES256-ECB ****************
// ******************************************

size_t gmlib_aes256_ecb_encrypt_ctx_size()
{
    return c_api::cipher_ecb_encrypt_ctx_size<AES256EcbEncryptor>();
}

void* gmlib_aes256_ecb_encrypt_ctx_new()
{
    return c_api::cipher_ecb_encrypt_ctx_new<AES256EcbEncryptor>();
}

void* gmlib_aes256_ecb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ecb_encrypt_ctx_new_inplace<AES256EcbEncryptor>(
        buf, buf_size);
}

int gmlib_aes256_ecb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_delete<AES256EcbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_delete_inplace<AES256EcbEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_ecb_encrypt_get_user_key_len()
{
    return c_api::cipher_ecb_encrypt_get_user_key_len<AES256EcbEncryptor>();
}

size_t gmlib_aes256_ecb_encrypt_get_block_size()
{
    return c_api::cipher_ecb_encrypt_get_block_size<AES256EcbEncryptor>();
}

int gmlib_aes256_ecb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_init<AES256EcbEncryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_reset<AES256EcbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_update<AES256EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final_ex<AES256EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final<AES256EcbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes256_ecb_decrypt_ctx_size()
{
    return c_api::cipher_ecb_decrypt_ctx_size<AES256EcbDecryptor>();
}

void* gmlib_aes256_ecb_decrypt_ctx_new()
{
    return c_api::cipher_ecb_decrypt_ctx_new<AES256EcbDecryptor>();
}

void* gmlib_aes256_ecb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ecb_decrypt_ctx_new_inplace<AES256EcbDecryptor>(
        buf, buf_size);
}

int gmlib_aes256_ecb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_delete<AES256EcbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_delete_inplace<AES256EcbDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_ecb_decrypt_get_user_key_len()
{
    return c_api::cipher_ecb_decrypt_get_user_key_len<AES256EcbDecryptor>();
}

size_t gmlib_aes256_ecb_decrypt_get_block_size()
{
    return c_api::cipher_ecb_decrypt_get_block_size<AES256EcbDecryptor>();
}

int gmlib_aes256_ecb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_init<AES256EcbDecryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_reset<AES256EcbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_update<AES256EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final_ex<AES256EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final<AES256EcbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES256-CBC ****************
// ******************************************

size_t gmlib_aes256_cbc_encrypt_ctx_size()
{
    return c_api::cipher_cbc_encrypt_ctx_size<AES256CbcEncryptor>();
}

void* gmlib_aes256_cbc_encrypt_ctx_new()
{
    return c_api::cipher_cbc_encrypt_ctx_new<AES256CbcEncryptor>();
}

void* gmlib_aes256_cbc_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cbc_encrypt_ctx_new_inplace<AES256CbcEncryptor>(
        buf, buf_size);
}

int gmlib_aes256_cbc_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_encrypt_ctx_delete<AES256CbcEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_encrypt_ctx_delete_inplace<AES256CbcEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_cbc_encrypt_get_user_key_len()
{
    return c_api::cipher_cbc_encrypt_get_user_key_len<AES256CbcEncryptor>();
}

size_t gmlib_aes256_cbc_encrypt_get_iv_len()
{
    return c_api::cipher_cbc_encrypt_get_iv_len<AES256CbcEncryptor>();
}

size_t gmlib_aes256_cbc_encrypt_get_block_size()
{
    return c_api::cipher_cbc_encrypt_get_block_size<AES256CbcEncryptor>();
}

int gmlib_aes256_cbc_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_init<AES256CbcEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_reset<AES256CbcEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_update<AES256CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final_ex<AES256CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final<AES256CbcEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes256_cbc_decrypt_ctx_size()
{
    return c_api::cipher_cbc_decrypt_ctx_size<AES256CbcDecryptor>();
}

void* gmlib_aes256_cbc_decrypt_ctx_new()
{
    return c_api::cipher_cbc_decrypt_ctx_new<AES256CbcDecryptor>();
}

void* gmlib_aes256_cbc_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cbc_decrypt_ctx_new_inplace<AES256CbcDecryptor>(
        buf, buf_size);
}

int gmlib_aes256_cbc_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_decrypt_ctx_delete<AES256CbcDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_decrypt_ctx_delete_inplace<AES256CbcDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_cbc_decrypt_get_user_key_len()
{
    return c_api::cipher_cbc_decrypt_get_user_key_len<AES256CbcDecryptor>();
}

size_t gmlib_aes256_cbc_decrypt_get_iv_len()
{
    return c_api::cipher_cbc_decrypt_get_iv_len<AES256CbcDecryptor>();
}

size_t gmlib_aes256_cbc_decrypt_get_block_size()
{
    return c_api::cipher_cbc_decrypt_get_block_size<AES256CbcDecryptor>();
}

int gmlib_aes256_cbc_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_init<AES256CbcDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_reset<AES256CbcDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_update<AES256CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final_ex<AES256CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final<AES256CbcDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES256-CFB ****************
// ******************************************

size_t gmlib_aes256_cfb_encrypt_ctx_size()
{
    return c_api::cipher_cfb_encrypt_ctx_size<AES256CfbEncryptor>();
}

void* gmlib_aes256_cfb_encrypt_ctx_new()
{
    return c_api::cipher_cfb_encrypt_ctx_new<AES256CfbEncryptor>();
}

void* gmlib_aes256_cfb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cfb_encrypt_ctx_new_inplace<AES256CfbEncryptor>(
        buf, buf_size);
}

int gmlib_aes256_cfb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_encrypt_ctx_delete<AES256CfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_encrypt_ctx_delete_inplace<AES256CfbEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_cfb_encrypt_get_user_key_len()
{
    return c_api::cipher_cfb_encrypt_get_user_key_len<AES256CfbEncryptor>();
}

size_t gmlib_aes256_cfb_encrypt_get_iv_len()
{
    return c_api::cipher_cfb_encrypt_get_iv_len<AES256CfbEncryptor>();
}

size_t gmlib_aes256_cfb_encrypt_get_block_size()
{
    return c_api::cipher_cfb_encrypt_get_block_size<AES256CfbEncryptor>();
}

int gmlib_aes256_cfb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_init<AES256CfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_reset<AES256CfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_update<AES256CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final_ex<AES256CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final<AES256CfbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes256_cfb_decrypt_ctx_size()
{
    return c_api::cipher_cfb_decrypt_ctx_size<AES256CfbDecryptor>();
}

void* gmlib_aes256_cfb_decrypt_ctx_new()
{
    return c_api::cipher_cfb_decrypt_ctx_new<AES256CfbDecryptor>();
}

void* gmlib_aes256_cfb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cfb_decrypt_ctx_new_inplace<AES256CfbDecryptor>(
        buf, buf_size);
}

int gmlib_aes256_cfb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_decrypt_ctx_delete<AES256CfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_decrypt_ctx_delete_inplace<AES256CfbDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_cfb_decrypt_get_user_key_len()
{
    return c_api::cipher_cfb_decrypt_get_user_key_len<AES256CfbDecryptor>();
}

size_t gmlib_aes256_cfb_decrypt_get_iv_len()
{
    return c_api::cipher_cfb_decrypt_get_iv_len<AES256CfbDecryptor>();
}

size_t gmlib_aes256_cfb_decrypt_get_block_size()
{
    return c_api::cipher_cfb_decrypt_get_block_size<AES256CfbDecryptor>();
}

int gmlib_aes256_cfb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_init<AES256CfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_reset<AES256CfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_update<AES256CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final_ex<AES256CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final<AES256CfbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES256-OFB ****************
// ******************************************

size_t gmlib_aes256_ofb_encrypt_ctx_size()
{
    return c_api::cipher_ofb_encrypt_ctx_size<AES256OfbEncryptor>();
}

void* gmlib_aes256_ofb_encrypt_ctx_new()
{
    return c_api::cipher_ofb_encrypt_ctx_new<AES256OfbEncryptor>();
}

void* gmlib_aes256_ofb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ofb_encrypt_ctx_new_inplace<AES256OfbEncryptor>(
        buf, buf_size);
}

int gmlib_aes256_ofb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_encrypt_ctx_delete<AES256OfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_encrypt_ctx_delete_inplace<AES256OfbEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_ofb_encrypt_get_user_key_len()
{
    return c_api::cipher_ofb_encrypt_get_user_key_len<AES256OfbEncryptor>();
}

size_t gmlib_aes256_ofb_encrypt_get_iv_len()
{
    return c_api::cipher_ofb_encrypt_get_iv_len<AES256OfbEncryptor>();
}

size_t gmlib_aes256_ofb_encrypt_get_block_size()
{
    return c_api::cipher_ofb_encrypt_get_block_size<AES256OfbEncryptor>();
}

int gmlib_aes256_ofb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_init<AES256OfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_reset<AES256OfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_update<AES256OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final_ex<AES256OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final<AES256OfbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes256_ofb_decrypt_ctx_size()
{
    return c_api::cipher_ofb_decrypt_ctx_size<AES256OfbDecryptor>();
}

void* gmlib_aes256_ofb_decrypt_ctx_new()
{
    return c_api::cipher_ofb_decrypt_ctx_new<AES256OfbDecryptor>();
}

void* gmlib_aes256_ofb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ofb_decrypt_ctx_new_inplace<AES256OfbDecryptor>(
        buf, buf_size);
}

int gmlib_aes256_ofb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_decrypt_ctx_delete<AES256OfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_decrypt_ctx_delete_inplace<AES256OfbDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_ofb_decrypt_get_user_key_len()
{
    return c_api::cipher_ofb_decrypt_get_user_key_len<AES256OfbDecryptor>();
}

size_t gmlib_aes256_ofb_decrypt_get_iv_len()
{
    return c_api::cipher_ofb_decrypt_get_iv_len<AES256OfbDecryptor>();
}

size_t gmlib_aes256_ofb_decrypt_get_block_size()
{
    return c_api::cipher_ofb_decrypt_get_block_size<AES256OfbDecryptor>();
}

int gmlib_aes256_ofb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_init<AES256OfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_reset<AES256OfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_update<AES256OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final_ex<AES256OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final<AES256OfbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES256-CTR ****************
// ******************************************

size_t gmlib_aes256_ctr_encrypt_ctx_size()
{
    return c_api::cipher_ctr_encrypt_ctx_size<AES256CtrEncryptor>();
}

void* gmlib_aes256_ctr_encrypt_ctx_new()
{
    return c_api::cipher_ctr_encrypt_ctx_new<AES256CtrEncryptor>();
}

void* gmlib_aes256_ctr_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ctr_encrypt_ctx_new_inplace<AES256CtrEncryptor>(
        buf, buf_size);
}

int gmlib_aes256_ctr_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_encrypt_ctx_delete<AES256CtrEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_encrypt_ctx_delete_inplace<AES256CtrEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_ctr_encrypt_get_user_key_len()
{
    return c_api::cipher_ctr_encrypt_get_user_key_len<AES256CtrEncryptor>();
}

size_t gmlib_aes256_ctr_encrypt_get_iv_len()
{
    return c_api::cipher_ctr_encrypt_get_iv_len<AES256CtrEncryptor>();
}

size_t gmlib_aes256_ctr_encrypt_get_block_size()
{
    return c_api::cipher_ctr_encrypt_get_block_size<AES256CtrEncryptor>();
}

int gmlib_aes256_ctr_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_init<AES256CtrEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_reset<AES256CtrEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_update<AES256CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final_ex<AES256CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final<AES256CtrEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes256_ctr_decrypt_ctx_size()
{
    return c_api::cipher_ctr_decrypt_ctx_size<AES256CtrDecryptor>();
}

void* gmlib_aes256_ctr_decrypt_ctx_new()
{
    return c_api::cipher_ctr_decrypt_ctx_new<AES256CtrDecryptor>();
}

void* gmlib_aes256_ctr_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ctr_decrypt_ctx_new_inplace<AES256CtrDecryptor>(
        buf, buf_size);
}

int gmlib_aes256_ctr_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_decrypt_ctx_delete<AES256CtrDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_decrypt_ctx_delete_inplace<AES256CtrDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_ctr_decrypt_get_user_key_len()
{
    return c_api::cipher_ctr_decrypt_get_user_key_len<AES256CtrDecryptor>();
}

size_t gmlib_aes256_ctr_decrypt_get_iv_len()
{
    return c_api::cipher_ctr_decrypt_get_iv_len<AES256CtrDecryptor>();
}

size_t gmlib_aes256_ctr_decrypt_get_block_size()
{
    return c_api::cipher_ctr_decrypt_get_block_size<AES256CtrDecryptor>();
}

int gmlib_aes256_ctr_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_init<AES256CtrDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_reset<AES256CtrDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_update<AES256CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final_ex<AES256CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final<AES256CtrDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES256-GCM ****************
// ******************************************

size_t gmlib_aes256_gcm_encrypt_ctx_size()
{
    return c_api::cipher_gcm_encrypt_ctx_size<AES256GcmEncryptor>();
}

void* gmlib_aes256_gcm_encrypt_ctx_new()
{
    return c_api::cipher_gcm_encrypt_ctx_new<AES256GcmEncryptor>();
}

void* gmlib_aes256_gcm_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_gcm_encrypt_ctx_new_inplace<AES256GcmEncryptor>(
        buf, buf_size);
}

int gmlib_aes256_gcm_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_delete<AES256GcmEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_delete_inplace<AES256GcmEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_gcm_encrypt_get_user_key_len()
{
    return c_api::cipher_gcm_encrypt_get_user_key_len<AES256GcmEncryptor>();
}

size_t gmlib_aes256_gcm_encrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_encrypt_get_default_iv_len<AES256GcmEncryptor>();
}

size_t gmlib_aes256_gcm_encrypt_get_block_size()
{
    return c_api::cipher_gcm_encrypt_get_block_size<AES256GcmEncryptor>();
}

size_t gmlib_aes256_gcm_encrypt_get_tag_len()
{
    return c_api::cipher_gcm_encrypt_get_tag_len<AES256GcmEncryptor>();
}

int gmlib_aes256_gcm_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_init<AES256GcmEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_reset<AES256GcmEncryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_update<AES256GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final_ex<AES256GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final<AES256GcmEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_get_tag<AES256GcmEncryptor>(
                    ctx, tag) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes256_gcm_decrypt_ctx_size()
{
    return c_api::cipher_gcm_decrypt_ctx_size<AES256GcmDecryptor>();
}

void* gmlib_aes256_gcm_decrypt_ctx_new()
{
    return c_api::cipher_gcm_decrypt_ctx_new<AES256GcmDecryptor>();
}

void* gmlib_aes256_gcm_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_gcm_decrypt_ctx_new_inplace<AES256GcmDecryptor>(
        buf, buf_size);
}

int gmlib_aes256_gcm_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_decrypt_ctx_delete<AES256GcmDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_decrypt_ctx_delete_inplace<AES256GcmDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes256_gcm_decrypt_get_user_key_len()
{
    return c_api::cipher_gcm_decrypt_get_user_key_len<AES256GcmDecryptor>();
}

size_t gmlib_aes256_gcm_decrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_decrypt_get_default_iv_len<AES256GcmDecryptor>();
}

size_t gmlib_aes256_gcm_decrypt_get_block_size()
{
    return c_api::cipher_gcm_decrypt_get_block_size<AES256GcmDecryptor>();
}

size_t gmlib_aes256_gcm_decrypt_get_tag_len()
{
    return c_api::cipher_gcm_decrypt_get_tag_len<AES256GcmDecryptor>();
}

int gmlib_aes256_gcm_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_init<AES256GcmDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_reset<AES256GcmDecryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_update<AES256GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final_ex<AES256GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final<AES256GcmDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_set_tag<AES256GcmDecryptor>(
                    ctx, tag) == 0,
                { return -1; });
    return 0;
}
