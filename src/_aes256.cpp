#include <gmlib/_aes256.h>
#include <gmlib/_debug.h>
#include <gmlib/aes/aes_mode.h>

#include <limits>

using namespace aes;

// ******************************************
// ************** AES256-ECB ****************
// ******************************************

size_t gmlib_aes256_ecb_encrypt_ctx_size()
{
    return sizeof(AES256EcbEncryptor);
}

void* gmlib_aes256_ecb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES256EcbEncryptor();
}

int gmlib_aes256_ecb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256EcbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_ecb_encrypt_get_user_key_len()
{
    return AES256EcbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_ecb_encrypt_get_block_size()
{
    return AES256EcbEncryptor::BLOCK_SIZE;
}

int gmlib_aes256_ecb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != AES256EcbEncryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbEncryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbEncryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes256_ecb_decrypt_ctx_size()
{
    return sizeof(AES256EcbDecryptor);
}

void* gmlib_aes256_ecb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES256EcbDecryptor();
}

int gmlib_aes256_ecb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256EcbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_ecb_decrypt_get_user_key_len()
{
    return AES256EcbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_ecb_decrypt_get_block_size()
{
    return AES256EcbDecryptor::BLOCK_SIZE;
}

int gmlib_aes256_ecb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != AES256EcbDecryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbDecryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbDecryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES256-CBC ****************
// ******************************************

size_t gmlib_aes256_cbc_encrypt_ctx_size()
{
    return sizeof(AES256CbcEncryptor);
}

void* gmlib_aes256_cbc_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES256CbcEncryptor();
}

int gmlib_aes256_cbc_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256CbcEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_cbc_encrypt_get_user_key_len()
{
    return AES256CbcEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_cbc_encrypt_get_iv_len()
{
    return AES256CbcEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_cbc_encrypt_get_block_size()
{
    return AES256CbcEncryptor::BLOCK_SIZE;
}

int gmlib_aes256_cbc_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes256_cbc_decrypt_ctx_size()
{
    return sizeof(AES256CbcDecryptor);
}

void* gmlib_aes256_cbc_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES256CbcDecryptor();
}

int gmlib_aes256_cbc_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256CbcDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_cbc_decrypt_get_user_key_len()
{
    return AES256CbcDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_cbc_decrypt_get_iv_len()
{
    return AES256CbcDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_cbc_decrypt_get_block_size()
{
    return AES256CbcDecryptor::BLOCK_SIZE;
}

int gmlib_aes256_cbc_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES256-CFB ****************
// ******************************************

size_t gmlib_aes256_cfb_encrypt_ctx_size()
{
    return sizeof(AES256CfbEncryptor);
}

void* gmlib_aes256_cfb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES256CfbEncryptor();
}

int gmlib_aes256_cfb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256CfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_cfb_encrypt_get_user_key_len()
{
    return AES256CfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_cfb_encrypt_get_iv_len()
{
    return AES256CfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_cfb_encrypt_get_block_size()
{
    return AES256CfbEncryptor::BLOCK_SIZE;
}

int gmlib_aes256_cfb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes256_cfb_decrypt_ctx_size()
{
    return sizeof(AES256CfbDecryptor);
}

void* gmlib_aes256_cfb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES256CfbDecryptor();
}

int gmlib_aes256_cfb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256CfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_cfb_decrypt_get_user_key_len()
{
    return AES256CfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_cfb_decrypt_get_iv_len()
{
    return AES256CfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_cfb_decrypt_get_block_size()
{
    return AES256CfbDecryptor::BLOCK_SIZE;
}

int gmlib_aes256_cfb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES256-OFB ****************
// ******************************************

size_t gmlib_aes256_ofb_encrypt_ctx_size()
{
    return sizeof(AES256OfbEncryptor);
}

void* gmlib_aes256_ofb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES256OfbEncryptor();
}

int gmlib_aes256_ofb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256OfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_ofb_encrypt_get_user_key_len()
{
    return AES256OfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_ofb_encrypt_get_iv_len()
{
    return AES256OfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_ofb_encrypt_get_block_size()
{
    return AES256OfbEncryptor::BLOCK_SIZE;
}

int gmlib_aes256_ofb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes256_ofb_decrypt_ctx_size()
{
    return sizeof(AES256OfbDecryptor);
}

void* gmlib_aes256_ofb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES256OfbDecryptor();
}

int gmlib_aes256_ofb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256OfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_ofb_decrypt_get_user_key_len()
{
    return AES256OfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_ofb_decrypt_get_iv_len()
{
    return AES256OfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_ofb_decrypt_get_block_size()
{
    return AES256OfbDecryptor::BLOCK_SIZE;
}

int gmlib_aes256_ofb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES256-CTR ****************
// ******************************************

size_t gmlib_aes256_ctr_encrypt_ctx_size()
{
    return sizeof(AES256CtrEncryptor);
}

void* gmlib_aes256_ctr_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES256CtrEncryptor();
}

int gmlib_aes256_ctr_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256CtrEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_ctr_encrypt_get_user_key_len()
{
    return AES256CtrEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_ctr_encrypt_get_iv_len()
{
    return AES256CtrEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_ctr_encrypt_get_block_size()
{
    return AES256CtrEncryptor::BLOCK_SIZE;
}

int gmlib_aes256_ctr_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes256_ctr_decrypt_ctx_size()
{
    return sizeof(AES256CtrDecryptor);
}

void* gmlib_aes256_ctr_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES256CtrDecryptor();
}

int gmlib_aes256_ctr_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256CtrDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_ctr_decrypt_get_user_key_len()
{
    return AES256CtrDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_ctr_decrypt_get_iv_len()
{
    return AES256CtrDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_ctr_decrypt_get_block_size()
{
    return AES256CtrDecryptor::BLOCK_SIZE;
}

int gmlib_aes256_ctr_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES256CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES256CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES256-GCM ****************
// ******************************************

size_t gmlib_aes256_gcm_encrypt_ctx_size()
{
    return sizeof(AES256GcmEncryptor);
}

void* gmlib_aes256_gcm_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES256GcmEncryptor();
}

int gmlib_aes256_gcm_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256GcmEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_gcm_encrypt_get_user_key_len()
{
    return AES256GcmEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_gcm_encrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_aes256_gcm_encrypt_get_block_size()
{
    return AES256GcmEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_gcm_encrypt_get_tag_len()
{
    return 16;
}

int gmlib_aes256_gcm_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                   //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmEncryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    if (ctx == nullptr ||                 //
        (iv == nullptr && iv_len != 0) || //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmEncryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmEncryptor*>(ctx);
        ptr->get_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmEncryptor::get_tag");
        return -1;
    }
    return 0;
}

size_t gmlib_aes256_gcm_decrypt_ctx_size()
{
    return sizeof(AES256GcmDecryptor);
}

void* gmlib_aes256_gcm_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES256GcmDecryptor();
}

int gmlib_aes256_gcm_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES256GcmDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes256_gcm_decrypt_get_user_key_len()
{
    return AES256GcmDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes256_gcm_decrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_aes256_gcm_decrypt_get_block_size()
{
    return AES256GcmDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes256_gcm_decrypt_get_tag_len()
{
    return 16;
}

int gmlib_aes256_gcm_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES256GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                   //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmDecryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len,
                                       const uint8_t* aad,
                                       size_t         aad_len)
{
    if (ctx == nullptr ||                 //
        (iv == nullptr && iv_len != 0) || //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmDecryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_update(void*          ctx,
                                        uint8_t*       out,
                                        size_t*        outl,
                                        const uint8_t* in,
                                        size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_final_ex(void*          ctx,
                                          uint8_t*       out,
                                          size_t*        outl,
                                          const uint8_t* in,
                                          size_t         inl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes256_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES256GcmDecryptor*>(ctx);
        ptr->set_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES256GcmDecryptor::set_tag");
        return -1;
    }
    return 0;
}
