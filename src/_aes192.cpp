#include <gmlib/_aes192.h>
#include <gmlib/_debug.h>
#include <gmlib/aes/aes_mode.h>

#include <limits>

using namespace aes;

// ******************************************
// ************** AES192-ECB ****************
// ******************************************

size_t gmlib_aes192_ecb_encrypt_ctx_size()
{
    return sizeof(AES192EcbEncryptor);
}

void* gmlib_aes192_ecb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES192EcbEncryptor();
}

int gmlib_aes192_ecb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192EcbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_ecb_encrypt_get_user_key_len()
{
    return AES192EcbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_ecb_encrypt_get_block_size()
{
    return AES192EcbEncryptor::BLOCK_SIZE;
}

int gmlib_aes192_ecb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != AES192EcbEncryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192EcbEncryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192EcbEncryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192EcbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes192_ecb_decrypt_ctx_size()
{
    return sizeof(AES192EcbDecryptor);
}

void* gmlib_aes192_ecb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES192EcbDecryptor();
}

int gmlib_aes192_ecb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192EcbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_ecb_decrypt_get_user_key_len()
{
    return AES192EcbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_ecb_decrypt_get_block_size()
{
    return AES192EcbDecryptor::BLOCK_SIZE;
}

int gmlib_aes192_ecb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != AES192EcbDecryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192EcbDecryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192EcbDecryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192EcbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES192-CBC ****************
// ******************************************

size_t gmlib_aes192_cbc_encrypt_ctx_size()
{
    return sizeof(AES192CbcEncryptor);
}

void* gmlib_aes192_cbc_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES192CbcEncryptor();
}

int gmlib_aes192_cbc_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192CbcEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_cbc_encrypt_get_user_key_len()
{
    return AES192CbcEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_cbc_encrypt_get_iv_len()
{
    return AES192CbcEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_cbc_encrypt_get_block_size()
{
    return AES192CbcEncryptor::BLOCK_SIZE;
}

int gmlib_aes192_cbc_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CbcEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CbcEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192CbcEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes192_cbc_decrypt_ctx_size()
{
    return sizeof(AES192CbcDecryptor);
}

void* gmlib_aes192_cbc_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES192CbcDecryptor();
}

int gmlib_aes192_cbc_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192CbcDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_cbc_decrypt_get_user_key_len()
{
    return AES192CbcDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_cbc_decrypt_get_iv_len()
{
    return AES192CbcDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_cbc_decrypt_get_block_size()
{
    return AES192CbcDecryptor::BLOCK_SIZE;
}

int gmlib_aes192_cbc_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CbcDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CbcDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192CbcDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES192-CFB ****************
// ******************************************

size_t gmlib_aes192_cfb_encrypt_ctx_size()
{
    return sizeof(AES192CfbEncryptor);
}

void* gmlib_aes192_cfb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES192CfbEncryptor();
}

int gmlib_aes192_cfb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192CfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_cfb_encrypt_get_user_key_len()
{
    return AES192CfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_cfb_encrypt_get_iv_len()
{
    return AES192CfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_cfb_encrypt_get_block_size()
{
    return AES192CfbEncryptor::BLOCK_SIZE;
}

int gmlib_aes192_cfb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192CfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes192_cfb_decrypt_ctx_size()
{
    return sizeof(AES192CfbDecryptor);
}

void* gmlib_aes192_cfb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES192CfbDecryptor();
}

int gmlib_aes192_cfb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192CfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_cfb_decrypt_get_user_key_len()
{
    return AES192CfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_cfb_decrypt_get_iv_len()
{
    return AES192CfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_cfb_decrypt_get_block_size()
{
    return AES192CfbDecryptor::BLOCK_SIZE;
}

int gmlib_aes192_cfb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192CfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES192-OFB ****************
// ******************************************

size_t gmlib_aes192_ofb_encrypt_ctx_size()
{
    return sizeof(AES192OfbEncryptor);
}

void* gmlib_aes192_ofb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES192OfbEncryptor();
}

int gmlib_aes192_ofb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192OfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_ofb_encrypt_get_user_key_len()
{
    return AES192OfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_ofb_encrypt_get_iv_len()
{
    return AES192OfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_ofb_encrypt_get_block_size()
{
    return AES192OfbEncryptor::BLOCK_SIZE;
}

int gmlib_aes192_ofb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192OfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192OfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192OfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes192_ofb_decrypt_ctx_size()
{
    return sizeof(AES192OfbDecryptor);
}

void* gmlib_aes192_ofb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES192OfbDecryptor();
}

int gmlib_aes192_ofb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192OfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_ofb_decrypt_get_user_key_len()
{
    return AES192OfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_ofb_decrypt_get_iv_len()
{
    return AES192OfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_ofb_decrypt_get_block_size()
{
    return AES192OfbDecryptor::BLOCK_SIZE;
}

int gmlib_aes192_ofb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192OfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192OfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192OfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES192-CTR ****************
// ******************************************

size_t gmlib_aes192_ctr_encrypt_ctx_size()
{
    return sizeof(AES192CtrEncryptor);
}

void* gmlib_aes192_ctr_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES192CtrEncryptor();
}

int gmlib_aes192_ctr_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192CtrEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_ctr_encrypt_get_user_key_len()
{
    return AES192CtrEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_ctr_encrypt_get_iv_len()
{
    return AES192CtrEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_ctr_encrypt_get_block_size()
{
    return AES192CtrEncryptor::BLOCK_SIZE;
}

int gmlib_aes192_ctr_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CtrEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CtrEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192CtrEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes192_ctr_decrypt_ctx_size()
{
    return sizeof(AES192CtrDecryptor);
}

void* gmlib_aes192_ctr_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES192CtrDecryptor();
}

int gmlib_aes192_ctr_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192CtrDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_ctr_decrypt_get_user_key_len()
{
    return AES192CtrDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_ctr_decrypt_get_iv_len()
{
    return AES192CtrDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_ctr_decrypt_get_block_size()
{
    return AES192CtrDecryptor::BLOCK_SIZE;
}

int gmlib_aes192_ctr_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES192CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CtrDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES192CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CtrDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192CtrDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES192-GCM ****************
// ******************************************

size_t gmlib_aes192_gcm_encrypt_ctx_size()
{
    return sizeof(AES192GcmEncryptor);
}

void* gmlib_aes192_gcm_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES192GcmEncryptor();
}

int gmlib_aes192_gcm_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192GcmEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_gcm_encrypt_get_user_key_len()
{
    return AES192GcmEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_gcm_encrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_aes192_gcm_encrypt_get_block_size()
{
    return AES192GcmEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_gcm_encrypt_get_tag_len()
{
    return 16;
}

int gmlib_aes192_gcm_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                   //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192GcmEncryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<AES192GcmEncryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192GcmEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192GcmEncryptor*>(ctx);
        ptr->get_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmEncryptor::get_tag");
        return -1;
    }
    return 0;
}

size_t gmlib_aes192_gcm_decrypt_ctx_size()
{
    return sizeof(AES192GcmDecryptor);
}

void* gmlib_aes192_gcm_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES192GcmDecryptor();
}

int gmlib_aes192_gcm_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES192GcmDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes192_gcm_decrypt_get_user_key_len()
{
    return AES192GcmDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes192_gcm_decrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_aes192_gcm_decrypt_get_block_size()
{
    return AES192GcmDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes192_gcm_decrypt_get_tag_len()
{
    return 16;
}

int gmlib_aes192_gcm_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES192GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                   //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192GcmDecryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<AES192GcmDecryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES192GcmDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES192GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes192_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES192GcmDecryptor*>(ctx);
        ptr->set_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES192GcmDecryptor::set_tag");
        return -1;
    }
    return 0;
}
