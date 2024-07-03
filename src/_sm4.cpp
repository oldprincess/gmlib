#include <gmlib/_debug.h>
#include <gmlib/_sm4.h>
#include <gmlib/sm4/sm4_mode.h>

#include "c_api_cipher.h"

using namespace sm4;

// ******************************************
// ***************** SM4-ECB ****************
// ******************************************

size_t gmlib_sm4_ecb_encrypt_ctx_size()
{
    return c_api::cipher_ecb_encrypt_ctx_size<SM4EcbEncryptor>();
}

void* gmlib_sm4_ecb_encrypt_ctx_new()
{
    return c_api::cipher_ecb_encrypt_ctx_new<SM4EcbEncryptor>();
}

void* gmlib_sm4_ecb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ecb_encrypt_ctx_new_inplace<SM4EcbEncryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_ecb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_delete<SM4EcbEncryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_encrypt_ctx_delete_inplace<SM4EcbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_ecb_encrypt_get_user_key_len()
{
    return c_api::cipher_ecb_encrypt_get_user_key_len<SM4EcbEncryptor>();
}

size_t gmlib_sm4_ecb_encrypt_get_block_size()
{
    return c_api::cipher_ecb_encrypt_get_block_size<SM4EcbEncryptor>();
}

int gmlib_sm4_ecb_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_init<SM4EcbEncryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_reset<SM4EcbEncryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_update<SM4EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final_ex<SM4EcbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_encrypt_ctx_final<SM4EcbEncryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_sm4_ecb_decrypt_ctx_size()
{
    return c_api::cipher_ecb_decrypt_ctx_size<SM4EcbDecryptor>();
}

void* gmlib_sm4_ecb_decrypt_ctx_new()
{
    return c_api::cipher_ecb_decrypt_ctx_new<SM4EcbDecryptor>();
}

void* gmlib_sm4_ecb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ecb_decrypt_ctx_new_inplace<SM4EcbDecryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_ecb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_delete<SM4EcbDecryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ecb_decrypt_ctx_delete_inplace<SM4EcbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_ecb_decrypt_get_user_key_len()
{
    return c_api::cipher_ecb_decrypt_get_user_key_len<SM4EcbDecryptor>();
}

size_t gmlib_sm4_ecb_decrypt_get_block_size()
{
    return c_api::cipher_ecb_decrypt_get_block_size<SM4EcbDecryptor>();
}

int gmlib_sm4_ecb_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_init<SM4EcbDecryptor>(
                    ctx, user_key, user_key_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_reset(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_reset<SM4EcbDecryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_update<SM4EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final_ex<SM4EcbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ecb_decrypt_ctx_final<SM4EcbDecryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ***************** SM4-CBC ****************
// ******************************************

size_t gmlib_sm4_cbc_encrypt_ctx_size()
{
    return c_api::cipher_cbc_encrypt_ctx_size<SM4CbcEncryptor>();
}

void* gmlib_sm4_cbc_encrypt_ctx_new()
{
    return c_api::cipher_cbc_encrypt_ctx_new<SM4CbcEncryptor>();
}

void* gmlib_sm4_cbc_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cbc_encrypt_ctx_new_inplace<SM4CbcEncryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_cbc_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_delete<SM4CbcEncryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_encrypt_ctx_delete_inplace<SM4CbcEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_cbc_encrypt_get_user_key_len()
{
    return c_api::cipher_cbc_encrypt_get_user_key_len<SM4CbcEncryptor>();
}

size_t gmlib_sm4_cbc_encrypt_get_iv_len()
{
    return c_api::cipher_cbc_encrypt_get_iv_len<SM4CbcEncryptor>();
}

size_t gmlib_sm4_cbc_encrypt_get_block_size()
{
    return c_api::cipher_cbc_encrypt_get_block_size<SM4CbcEncryptor>();
}

int gmlib_sm4_cbc_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_init<SM4CbcEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_reset<SM4CbcEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_update<SM4CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final_ex<SM4CbcEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_encrypt_ctx_final<SM4CbcEncryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_sm4_cbc_decrypt_ctx_size()
{
    return c_api::cipher_cbc_decrypt_ctx_size<SM4CbcDecryptor>();
}

void* gmlib_sm4_cbc_decrypt_ctx_new()
{
    return c_api::cipher_cbc_decrypt_ctx_new<SM4CbcDecryptor>();
}

void* gmlib_sm4_cbc_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cbc_decrypt_ctx_new_inplace<SM4CbcDecryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_cbc_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_delete<SM4CbcDecryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cbc_decrypt_ctx_delete_inplace<SM4CbcDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_cbc_decrypt_get_user_key_len()
{
    return c_api::cipher_cbc_decrypt_get_user_key_len<SM4CbcDecryptor>();
}

size_t gmlib_sm4_cbc_decrypt_get_iv_len()
{
    return c_api::cipher_cbc_decrypt_get_iv_len<SM4CbcDecryptor>();
}

size_t gmlib_sm4_cbc_decrypt_get_block_size()
{
    return c_api::cipher_cbc_decrypt_get_block_size<SM4CbcDecryptor>();
}

int gmlib_sm4_cbc_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_init<SM4CbcDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_reset<SM4CbcDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_update<SM4CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final_ex<SM4CbcDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cbc_decrypt_ctx_final<SM4CbcDecryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ***************** SM4-CFB ****************
// ******************************************

size_t gmlib_sm4_cfb_encrypt_ctx_size()
{
    return c_api::cipher_cfb_encrypt_ctx_size<SM4CfbEncryptor>();
}

void* gmlib_sm4_cfb_encrypt_ctx_new()
{
    return c_api::cipher_cfb_encrypt_ctx_new<SM4CfbEncryptor>();
}

void* gmlib_sm4_cfb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cfb_encrypt_ctx_new_inplace<SM4CfbEncryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_cfb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_delete<SM4CfbEncryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_encrypt_ctx_delete_inplace<SM4CfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_cfb_encrypt_get_user_key_len()
{
    return c_api::cipher_cfb_encrypt_get_user_key_len<SM4CfbEncryptor>();
}

size_t gmlib_sm4_cfb_encrypt_get_iv_len()
{
    return c_api::cipher_cfb_encrypt_get_iv_len<SM4CfbEncryptor>();
}

size_t gmlib_sm4_cfb_encrypt_get_block_size()
{
    return c_api::cipher_cfb_encrypt_get_block_size<SM4CfbEncryptor>();
}

int gmlib_sm4_cfb_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_init<SM4CfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_reset<SM4CfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_update<SM4CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final_ex<SM4CfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_encrypt_ctx_final<SM4CfbEncryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_sm4_cfb_decrypt_ctx_size()
{
    return c_api::cipher_cfb_decrypt_ctx_size<SM4CfbDecryptor>();
}

void* gmlib_sm4_cfb_decrypt_ctx_new()
{
    return c_api::cipher_cfb_decrypt_ctx_new<SM4CfbDecryptor>();
}

void* gmlib_sm4_cfb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_cfb_decrypt_ctx_new_inplace<SM4CfbDecryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_cfb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_delete<SM4CfbDecryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_cfb_decrypt_ctx_delete_inplace<SM4CfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_cfb_decrypt_get_user_key_len()
{
    return c_api::cipher_cfb_decrypt_get_user_key_len<SM4CfbDecryptor>();
}

size_t gmlib_sm4_cfb_decrypt_get_iv_len()
{
    return c_api::cipher_cfb_decrypt_get_iv_len<SM4CfbDecryptor>();
}

size_t gmlib_sm4_cfb_decrypt_get_block_size()
{
    return c_api::cipher_cfb_decrypt_get_block_size<SM4CfbDecryptor>();
}

int gmlib_sm4_cfb_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_init<SM4CfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_reset<SM4CfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_update<SM4CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final_ex<SM4CfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_cfb_decrypt_ctx_final<SM4CfbDecryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ***************** SM4-OFB ****************
// ******************************************

size_t gmlib_sm4_ofb_encrypt_ctx_size()
{
    return c_api::cipher_ofb_encrypt_ctx_size<SM4OfbEncryptor>();
}

void* gmlib_sm4_ofb_encrypt_ctx_new()
{
    return c_api::cipher_ofb_encrypt_ctx_new<SM4OfbEncryptor>();
}

void* gmlib_sm4_ofb_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ofb_encrypt_ctx_new_inplace<SM4OfbEncryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_ofb_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_delete<SM4OfbEncryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_encrypt_ctx_delete_inplace<SM4OfbEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_ofb_encrypt_get_user_key_len()
{
    return c_api::cipher_ofb_encrypt_get_user_key_len<SM4OfbEncryptor>();
}

size_t gmlib_sm4_ofb_encrypt_get_iv_len()
{
    return c_api::cipher_ofb_encrypt_get_iv_len<SM4OfbEncryptor>();
}

size_t gmlib_sm4_ofb_encrypt_get_block_size()
{
    return c_api::cipher_ofb_encrypt_get_block_size<SM4OfbEncryptor>();
}

int gmlib_sm4_ofb_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_init<SM4OfbEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_reset<SM4OfbEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_update<SM4OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final_ex<SM4OfbEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_encrypt_ctx_final<SM4OfbEncryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_sm4_ofb_decrypt_ctx_size()
{
    return c_api::cipher_ofb_decrypt_ctx_size<SM4OfbDecryptor>();
}

void* gmlib_sm4_ofb_decrypt_ctx_new()
{
    return c_api::cipher_ofb_decrypt_ctx_new<SM4OfbDecryptor>();
}

void* gmlib_sm4_ofb_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ofb_decrypt_ctx_new_inplace<SM4OfbDecryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_ofb_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_delete<SM4OfbDecryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ofb_decrypt_ctx_delete_inplace<SM4OfbDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_ofb_decrypt_get_user_key_len()
{
    return c_api::cipher_ofb_decrypt_get_user_key_len<SM4OfbDecryptor>();
}

size_t gmlib_sm4_ofb_decrypt_get_iv_len()
{
    return c_api::cipher_ofb_decrypt_get_iv_len<SM4OfbDecryptor>();
}

size_t gmlib_sm4_ofb_decrypt_get_block_size()
{
    return c_api::cipher_ofb_decrypt_get_block_size<SM4OfbDecryptor>();
}

int gmlib_sm4_ofb_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_init<SM4OfbDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_reset<SM4OfbDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_update<SM4OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final_ex<SM4OfbDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ofb_decrypt_ctx_final<SM4OfbDecryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ***************** SM4-CTR ****************
// ******************************************

size_t gmlib_sm4_ctr_encrypt_ctx_size()
{
    return c_api::cipher_ctr_encrypt_ctx_size<SM4CtrEncryptor>();
}

void* gmlib_sm4_ctr_encrypt_ctx_new()
{
    return c_api::cipher_ctr_encrypt_ctx_new<SM4CtrEncryptor>();
}

void* gmlib_sm4_ctr_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ctr_encrypt_ctx_new_inplace<SM4CtrEncryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_ctr_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_delete<SM4CtrEncryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_encrypt_ctx_delete_inplace<SM4CtrEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_ctr_encrypt_get_user_key_len()
{
    return c_api::cipher_ctr_encrypt_get_user_key_len<SM4CtrEncryptor>();
}

size_t gmlib_sm4_ctr_encrypt_get_iv_len()
{
    return c_api::cipher_ctr_encrypt_get_iv_len<SM4CtrEncryptor>();
}

size_t gmlib_sm4_ctr_encrypt_get_block_size()
{
    return c_api::cipher_ctr_encrypt_get_block_size<SM4CtrEncryptor>();
}

int gmlib_sm4_ctr_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_init<SM4CtrEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_reset<SM4CtrEncryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_update<SM4CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final_ex<SM4CtrEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_encrypt_ctx_final<SM4CtrEncryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

size_t gmlib_sm4_ctr_decrypt_ctx_size()
{
    return c_api::cipher_ctr_decrypt_ctx_size<SM4CtrDecryptor>();
}

void* gmlib_sm4_ctr_decrypt_ctx_new()
{
    return c_api::cipher_ctr_decrypt_ctx_new<SM4CtrDecryptor>();
}

void* gmlib_sm4_ctr_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_ctr_decrypt_ctx_new_inplace<SM4CtrDecryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_ctr_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_delete<SM4CtrDecryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_ctr_decrypt_ctx_delete_inplace<SM4CtrDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_ctr_decrypt_get_user_key_len()
{
    return c_api::cipher_ctr_decrypt_get_user_key_len<SM4CtrDecryptor>();
}

size_t gmlib_sm4_ctr_decrypt_get_iv_len()
{
    return c_api::cipher_ctr_decrypt_get_iv_len<SM4CtrDecryptor>();
}

size_t gmlib_sm4_ctr_decrypt_get_block_size()
{
    return c_api::cipher_ctr_decrypt_get_block_size<SM4CtrDecryptor>();
}

int gmlib_sm4_ctr_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_init<SM4CtrDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_reset<SM4CtrDecryptor>(
                    ctx, iv, iv_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_update<SM4CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final_ex<SM4CtrDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_ctr_decrypt_ctx_final<SM4CtrDecryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

// ******************************************
// ***************** SM4-GCM ****************
// ******************************************

size_t gmlib_sm4_gcm_encrypt_ctx_size()
{
    return c_api::cipher_gcm_encrypt_ctx_size<SM4GcmEncryptor>();
}

void* gmlib_sm4_gcm_encrypt_ctx_new()
{
    return c_api::cipher_gcm_encrypt_ctx_new<SM4GcmEncryptor>();
}

void* gmlib_sm4_gcm_encrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_gcm_encrypt_ctx_new_inplace<SM4GcmEncryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_gcm_encrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_delete<SM4GcmEncryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_delete_inplace<SM4GcmEncryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_gcm_encrypt_get_user_key_len()
{
    return c_api::cipher_gcm_encrypt_get_user_key_len<SM4GcmEncryptor>();
}

size_t gmlib_sm4_gcm_encrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_encrypt_get_default_iv_len<SM4GcmEncryptor>();
}

size_t gmlib_sm4_gcm_encrypt_get_block_size()
{
    return c_api::cipher_gcm_encrypt_get_block_size<SM4GcmEncryptor>();
}

size_t gmlib_sm4_gcm_encrypt_get_tag_len()
{
    return c_api::cipher_gcm_encrypt_get_tag_len<SM4GcmEncryptor>();
}

int gmlib_sm4_gcm_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len,
                                   const uint8_t* aad,
                                   size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_init<SM4GcmEncryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_reset(void*          ctx,
                                    const uint8_t* iv,
                                    size_t         iv_len,
                                    const uint8_t* aad,
                                    size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_reset<SM4GcmEncryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_update<SM4GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final_ex<SM4GcmEncryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_encrypt_ctx_final<SM4GcmEncryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_get_tag<SM4GcmEncryptor>(ctx, tag) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_gcm_decrypt_ctx_size()
{
    return c_api::cipher_gcm_decrypt_ctx_size<SM4GcmDecryptor>();
}

void* gmlib_sm4_gcm_decrypt_ctx_new()
{
    return c_api::cipher_gcm_decrypt_ctx_new<SM4GcmDecryptor>();
}

void* gmlib_sm4_gcm_decrypt_ctx_new_inplace(void* buf, size_t buf_size)
{
    return c_api::cipher_gcm_decrypt_ctx_new_inplace<SM4GcmDecryptor>(buf,
                                                                      buf_size);
}

int gmlib_sm4_gcm_decrypt_ctx_delete(void* ctx)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_delete<SM4GcmDecryptor>(ctx) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_delete_inplace(void* ctx)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_decrypt_ctx_delete_inplace<SM4GcmDecryptor>(ctx) == 0,
        { return -1; });
    return 0;
}

size_t gmlib_sm4_gcm_decrypt_get_user_key_len()
{
    return c_api::cipher_gcm_decrypt_get_user_key_len<SM4GcmDecryptor>();
}

size_t gmlib_sm4_gcm_decrypt_get_default_iv_len()
{
    return c_api::cipher_gcm_decrypt_get_default_iv_len<SM4GcmDecryptor>();
}

size_t gmlib_sm4_gcm_decrypt_get_block_size()
{
    return c_api::cipher_gcm_decrypt_get_block_size<SM4GcmDecryptor>();
}

size_t gmlib_sm4_gcm_decrypt_get_tag_len()
{
    return c_api::cipher_gcm_decrypt_get_tag_len<SM4GcmDecryptor>();
}

int gmlib_sm4_gcm_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len,
                                   const uint8_t* aad,
                                   size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_init<SM4GcmDecryptor>(
                    ctx, user_key, user_key_len, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_reset(void*          ctx,
                                    const uint8_t* iv,
                                    size_t         iv_len,
                                    const uint8_t* aad,
                                    size_t         aad_len)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_reset<SM4GcmDecryptor>(
                    ctx, iv, iv_len, aad, aad_len) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_update(void*          ctx,
                                     uint8_t*       out,
                                     size_t*        outl,
                                     const uint8_t* in,
                                     size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_update<SM4GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_final_ex(void*          ctx,
                                       uint8_t*       out,
                                       size_t*        outl,
                                       const uint8_t* in,
                                       size_t         inl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final_ex<SM4GcmDecryptor>(
                    ctx, out, outl, in, inl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    GMLIB_CHECK(c_api::cipher_gcm_decrypt_ctx_final<SM4GcmDecryptor>(ctx, out,
                                                                     outl) == 0,
                { return -1; });
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    GMLIB_CHECK(
        c_api::cipher_gcm_encrypt_ctx_set_tag<SM4GcmDecryptor>(ctx, tag) == 0,
        { return -1; });
    return 0;
}
