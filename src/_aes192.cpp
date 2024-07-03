#include <gmlib/_aes192.h>
#include <gmlib/_debug.h>
#include <gmlib/aes/aes_mode.h>

#include "c_api_cipher.h"

using namespace aes;

// ******************************************
// ************** AES192-ECB ****************
// ******************************************

size_t gmlib_aes192_ecb_encrypt_ctx_size()
{
    return c_api::cipher_ecb_encrypt_ctx_size<AES192EcbEncryptor>();
}

void* gmlib_aes192_ecb_encrypt_ctx_new()
{
    return c_api::cipher_ecb_encrypt_ctx_new<AES192EcbEncryptor>();
}

void* gmlib_aes192_ecb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ecb_encrypt_ctx_new_inplace<AES192EcbEncryptor>(
        buf, buf_size);
}

int gmlib_aes192_ecb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_delete<AES192EcbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_delete_inplace<AES192EcbEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_ecb_encrypt_get_user_key_len()
{
    return c_api::cipher_ecb_encrypt_get_user_key_len<AES192EcbEncryptor>();
}

size_t gmlib_aes192_ecb_encrypt_get_block_size()
{
    return c_api::cipher_ecb_encrypt_get_block_size<AES192EcbEncryptor>();
}

int gmlib_aes192_ecb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_init<AES192EcbEncryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_reset<AES192EcbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_update<AES192EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final_ex<AES192EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final<AES192EcbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes192_ecb_decrypt_ctx_size()
{
    return c_api::cipher_ecb_decrypt_ctx_size<AES192EcbDecryptor>();
}

void* gmlib_aes192_ecb_decrypt_ctx_new()
{
    return c_api::cipher_ecb_decrypt_ctx_new<AES192EcbDecryptor>();
}

void* gmlib_aes192_ecb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ecb_decrypt_ctx_new_inplace<AES192EcbDecryptor>(
        buf, buf_size);
}

int gmlib_aes192_ecb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_delete<AES192EcbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_delete_inplace<AES192EcbDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_ecb_decrypt_get_user_key_len()
{
    return c_api::cipher_ecb_decrypt_get_user_key_len<AES192EcbDecryptor>();
}

size_t gmlib_aes192_ecb_decrypt_get_block_size()
{
    return c_api::cipher_ecb_decrypt_get_block_size<AES192EcbDecryptor>();
}

int gmlib_aes192_ecb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_init<AES192EcbDecryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_reset<AES192EcbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_update<AES192EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final_ex<AES192EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final<AES192EcbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES192-CBC ****************
// ******************************************

size_t gmlib_aes192_cbc_encrypt_ctx_size()
{
    return c_api::cipher_cbc_encrypt_ctx_size<AES192CbcEncryptor>();
}

void* gmlib_aes192_cbc_encrypt_ctx_new()
{
    return c_api::cipher_cbc_encrypt_ctx_new<AES192CbcEncryptor>();
}

void* gmlib_aes192_cbc_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cbc_encrypt_ctx_new_inplace<AES192CbcEncryptor>(
        buf, buf_size);
}

int gmlib_aes192_cbc_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_encrypt_ctx_delete<AES192CbcEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_encrypt_ctx_delete_inplace<AES192CbcEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_cbc_encrypt_get_user_key_len()
{
    return c_api::cipher_cbc_encrypt_get_user_key_len<AES192CbcEncryptor>();
}

size_t gmlib_aes192_cbc_encrypt_get_iv_len()
{
    return c_api::cipher_cbc_encrypt_get_iv_len<AES192CbcEncryptor>();
}

size_t gmlib_aes192_cbc_encrypt_get_block_size()
{
    return c_api::cipher_cbc_encrypt_get_block_size<AES192CbcEncryptor>();
}

int gmlib_aes192_cbc_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_init<AES192CbcEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_reset<AES192CbcEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_update<AES192CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final_ex<AES192CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final<AES192CbcEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes192_cbc_decrypt_ctx_size()
{
    return c_api::cipher_cbc_decrypt_ctx_size<AES192CbcDecryptor>();
}

void* gmlib_aes192_cbc_decrypt_ctx_new()
{
    return c_api::cipher_cbc_decrypt_ctx_new<AES192CbcDecryptor>();
}

void* gmlib_aes192_cbc_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cbc_decrypt_ctx_new_inplace<AES192CbcDecryptor>(
        buf, buf_size);
}

int gmlib_aes192_cbc_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_decrypt_ctx_delete<AES192CbcDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_decrypt_ctx_delete_inplace<AES192CbcDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_cbc_decrypt_get_user_key_len()
{
    return c_api::cipher_cbc_decrypt_get_user_key_len<AES192CbcDecryptor>();
}

size_t gmlib_aes192_cbc_decrypt_get_iv_len()
{
    return c_api::cipher_cbc_decrypt_get_iv_len<AES192CbcDecryptor>();
}

size_t gmlib_aes192_cbc_decrypt_get_block_size()
{
    return c_api::cipher_cbc_decrypt_get_block_size<AES192CbcDecryptor>();
}

int gmlib_aes192_cbc_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_init<AES192CbcDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_reset<AES192CbcDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_update<AES192CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final_ex<AES192CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final<AES192CbcDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES192-CFB ****************
// ******************************************

size_t gmlib_aes192_cfb_encrypt_ctx_size()
{
    return c_api::cipher_cfb_encrypt_ctx_size<AES192CfbEncryptor>();
}

void* gmlib_aes192_cfb_encrypt_ctx_new()
{
    return c_api::cipher_cfb_encrypt_ctx_new<AES192CfbEncryptor>();
}

void* gmlib_aes192_cfb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cfb_encrypt_ctx_new_inplace<AES192CfbEncryptor>(
        buf, buf_size);
}

int gmlib_aes192_cfb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_encrypt_ctx_delete<AES192CfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_encrypt_ctx_delete_inplace<AES192CfbEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_cfb_encrypt_get_user_key_len()
{
    return c_api::cipher_cfb_encrypt_get_user_key_len<AES192CfbEncryptor>();
}

size_t gmlib_aes192_cfb_encrypt_get_iv_len()
{
    return c_api::cipher_cfb_encrypt_get_iv_len<AES192CfbEncryptor>();
}

size_t gmlib_aes192_cfb_encrypt_get_block_size()
{
    return c_api::cipher_cfb_encrypt_get_block_size<AES192CfbEncryptor>();
}

int gmlib_aes192_cfb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_init<AES192CfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_reset<AES192CfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_update<AES192CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final_ex<AES192CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final<AES192CfbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes192_cfb_decrypt_ctx_size()
{
    return c_api::cipher_cfb_decrypt_ctx_size<AES192CfbDecryptor>();
}

void* gmlib_aes192_cfb_decrypt_ctx_new()
{
    return c_api::cipher_cfb_decrypt_ctx_new<AES192CfbDecryptor>();
}

void* gmlib_aes192_cfb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cfb_decrypt_ctx_new_inplace<AES192CfbDecryptor>(
        buf, buf_size);
}

int gmlib_aes192_cfb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_decrypt_ctx_delete<AES192CfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_decrypt_ctx_delete_inplace<AES192CfbDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_cfb_decrypt_get_user_key_len()
{
    return c_api::cipher_cfb_decrypt_get_user_key_len<AES192CfbDecryptor>();
}

size_t gmlib_aes192_cfb_decrypt_get_iv_len()
{
    return c_api::cipher_cfb_decrypt_get_iv_len<AES192CfbDecryptor>();
}

size_t gmlib_aes192_cfb_decrypt_get_block_size()
{
    return c_api::cipher_cfb_decrypt_get_block_size<AES192CfbDecryptor>();
}

int gmlib_aes192_cfb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_init<AES192CfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_reset<AES192CfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_update<AES192CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final_ex<AES192CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final<AES192CfbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES192-OFB ****************
// ******************************************

size_t gmlib_aes192_ofb_encrypt_ctx_size()
{
    return c_api::cipher_ofb_encrypt_ctx_size<AES192OfbEncryptor>();
}

void* gmlib_aes192_ofb_encrypt_ctx_new()
{
    return c_api::cipher_ofb_encrypt_ctx_new<AES192OfbEncryptor>();
}

void* gmlib_aes192_ofb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ofb_encrypt_ctx_new_inplace<AES192OfbEncryptor>(
        buf, buf_size);
}

int gmlib_aes192_ofb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_encrypt_ctx_delete<AES192OfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_encrypt_ctx_delete_inplace<AES192OfbEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_ofb_encrypt_get_user_key_len()
{
    return c_api::cipher_ofb_encrypt_get_user_key_len<AES192OfbEncryptor>();
}

size_t gmlib_aes192_ofb_encrypt_get_iv_len()
{
    return c_api::cipher_ofb_encrypt_get_iv_len<AES192OfbEncryptor>();
}

size_t gmlib_aes192_ofb_encrypt_get_block_size()
{
    return c_api::cipher_ofb_encrypt_get_block_size<AES192OfbEncryptor>();
}

int gmlib_aes192_ofb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_init<AES192OfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_reset<AES192OfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_update<AES192OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final_ex<AES192OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final<AES192OfbEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes192_ofb_decrypt_ctx_size()
{
    return c_api::cipher_ofb_decrypt_ctx_size<AES192OfbDecryptor>();
}

void* gmlib_aes192_ofb_decrypt_ctx_new()
{
    return c_api::cipher_ofb_decrypt_ctx_new<AES192OfbDecryptor>();
}

void* gmlib_aes192_ofb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ofb_decrypt_ctx_new_inplace<AES192OfbDecryptor>(
        buf, buf_size);
}

int gmlib_aes192_ofb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_decrypt_ctx_delete<AES192OfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_decrypt_ctx_delete_inplace<AES192OfbDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_ofb_decrypt_get_user_key_len()
{
    return c_api::cipher_ofb_decrypt_get_user_key_len<AES192OfbDecryptor>();
}

size_t gmlib_aes192_ofb_decrypt_get_iv_len()
{
    return c_api::cipher_ofb_decrypt_get_iv_len<AES192OfbDecryptor>();
}

size_t gmlib_aes192_ofb_decrypt_get_block_size()
{
    return c_api::cipher_ofb_decrypt_get_block_size<AES192OfbDecryptor>();
}

int gmlib_aes192_ofb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_init<AES192OfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_reset<AES192OfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_update<AES192OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final_ex<AES192OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final<AES192OfbDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES192-CTR ****************
// ******************************************

size_t gmlib_aes192_ctr_encrypt_ctx_size()
{
    return c_api::cipher_ctr_encrypt_ctx_size<AES192CtrEncryptor>();
}

void* gmlib_aes192_ctr_encrypt_ctx_new()
{
    return c_api::cipher_ctr_encrypt_ctx_new<AES192CtrEncryptor>();
}

void* gmlib_aes192_ctr_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ctr_encrypt_ctx_new_inplace<AES192CtrEncryptor>(
        buf, buf_size);
}

int gmlib_aes192_ctr_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_encrypt_ctx_delete<AES192CtrEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_encrypt_ctx_delete_inplace<AES192CtrEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_ctr_encrypt_get_user_key_len()
{
    return c_api::cipher_ctr_encrypt_get_user_key_len<AES192CtrEncryptor>();
}

size_t gmlib_aes192_ctr_encrypt_get_iv_len()
{
    return c_api::cipher_ctr_encrypt_get_iv_len<AES192CtrEncryptor>();
}

size_t gmlib_aes192_ctr_encrypt_get_block_size()
{
    return c_api::cipher_ctr_encrypt_get_block_size<AES192CtrEncryptor>();
}

int gmlib_aes192_ctr_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_init<AES192CtrEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_reset<AES192CtrEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_update<AES192CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final_ex<AES192CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final<AES192CtrEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes192_ctr_decrypt_ctx_size()
{
    return c_api::cipher_ctr_decrypt_ctx_size<AES192CtrDecryptor>();
}

void* gmlib_aes192_ctr_decrypt_ctx_new()
{
    return c_api::cipher_ctr_decrypt_ctx_new<AES192CtrDecryptor>();
}

void* gmlib_aes192_ctr_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ctr_decrypt_ctx_new_inplace<AES192CtrDecryptor>(
        buf, buf_size);
}

int gmlib_aes192_ctr_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_decrypt_ctx_delete<AES192CtrDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_decrypt_ctx_delete_inplace<AES192CtrDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_ctr_decrypt_get_user_key_len()
{
    return c_api::cipher_ctr_decrypt_get_user_key_len<AES192CtrDecryptor>();
}

size_t gmlib_aes192_ctr_decrypt_get_iv_len()
{
    return c_api::cipher_ctr_decrypt_get_iv_len<AES192CtrDecryptor>();
}

size_t gmlib_aes192_ctr_decrypt_get_block_size()
{
    return c_api::cipher_ctr_decrypt_get_block_size<AES192CtrDecryptor>();
}

int gmlib_aes192_ctr_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_init<AES192CtrDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_reset<AES192CtrDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_update<AES192CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final_ex<AES192CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final<AES192CtrDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ************** AES192-GCM ****************
// ******************************************

size_t gmlib_aes192_gcm_encrypt_ctx_size()
{
    return c_api::cipher_gcm_encrypt_ctx_size<AES192GcmEncryptor>();
}

void* gmlib_aes192_gcm_encrypt_ctx_new()
{
    return c_api::cipher_gcm_encrypt_ctx_new<AES192GcmEncryptor>();
}

void* gmlib_aes192_gcm_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_gcm_encrypt_ctx_new_inplace<AES192GcmEncryptor>(
        buf, buf_size);
}

int gmlib_aes192_gcm_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_delete<AES192GcmEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_delete_inplace<AES192GcmEncryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_gcm_encrypt_get_user_key_len()
{
    return c_api::cipher_gcm_encrypt_get_user_key_len<AES192GcmEncryptor>();
}

size_t gmlib_aes192_gcm_encrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_encrypt_get_default_iv_len<AES192GcmEncryptor>();
}

size_t gmlib_aes192_gcm_encrypt_get_block_size()
{
    return c_api::cipher_gcm_encrypt_get_block_size<AES192GcmEncryptor>();
}

size_t gmlib_aes192_gcm_encrypt_get_tag_len()
{
    return c_api::cipher_gcm_encrypt_get_tag_len<AES192GcmEncryptor>();
}

int gmlib_aes192_gcm_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_init<AES192GcmEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_reset<AES192GcmEncryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_update<AES192GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final_ex<AES192GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final<AES192GcmEncryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_get_tag<AES192GcmEncryptor>(
                    ctx, tag) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_aes192_gcm_decrypt_ctx_size()
{
    return c_api::cipher_gcm_decrypt_ctx_size<AES192GcmDecryptor>();
}

void* gmlib_aes192_gcm_decrypt_ctx_new()
{
    return c_api::cipher_gcm_decrypt_ctx_new<AES192GcmDecryptor>();
}

void* gmlib_aes192_gcm_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_gcm_decrypt_ctx_new_inplace<AES192GcmDecryptor>(
        buf, buf_size);
}

int gmlib_aes192_gcm_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_decrypt_ctx_delete<AES192GcmDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_decrypt_ctx_delete_inplace<AES192GcmDecryptor>(ctx) ==
            0,
        { return -1; });
    return 0;
}

size_t gmlib_aes192_gcm_decrypt_get_user_key_len()
{
    return c_api::cipher_gcm_decrypt_get_user_key_len<AES192GcmDecryptor>();
}

size_t gmlib_aes192_gcm_decrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_decrypt_get_default_iv_len<AES192GcmDecryptor>();
}

size_t gmlib_aes192_gcm_decrypt_get_block_size()
{
    return c_api::cipher_gcm_decrypt_get_block_size<AES192GcmDecryptor>();
}

size_t gmlib_aes192_gcm_decrypt_get_tag_len()
{
    return c_api::cipher_gcm_decrypt_get_tag_len<AES192GcmDecryptor>();
}

int gmlib_aes192_gcm_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_init<AES192GcmDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_reset<AES192GcmDecryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_update<AES192GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final_ex<AES192GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final<AES192GcmDecryptor>(
                    ctx, out, outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_set_tag<AES192GcmDecryptor>(
                    ctx, tag) == 0,
                { return -1; });
    return 0;
}
