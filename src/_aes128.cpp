#include <gmlib/_aes128.h>
#include <gmlib/_debug.h>
#include <gmlib/aes/aes_mode.h>

#include <limits>

using namespace aes;

// ******************************************
// ************** AES128-ECB ****************
// ******************************************

size_t gmlib_aes128_ecb_encrypt_ctx_size()
{
    return sizeof(AES128EcbEncryptor);
}

void* gmlib_aes128_ecb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES128EcbEncryptor();
}

int gmlib_aes128_ecb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128EcbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_ecb_encrypt_get_user_key_len()
{
    return AES128EcbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_ecb_encrypt_get_block_size()
{
    return AES128EcbEncryptor::BLOCK_SIZE;
}

int gmlib_aes128_ecb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != AES128EcbEncryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128EcbEncryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128EcbEncryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128EcbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes128_ecb_decrypt_ctx_size()
{
    return sizeof(AES128EcbDecryptor);
}

void* gmlib_aes128_ecb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES128EcbDecryptor();
}

int gmlib_aes128_ecb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128EcbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_ecb_decrypt_get_user_key_len()
{
    return AES128EcbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_ecb_decrypt_get_block_size()
{
    return AES128EcbDecryptor::BLOCK_SIZE;
}

int gmlib_aes128_ecb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != AES128EcbDecryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128EcbDecryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128EcbDecryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128EcbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES128-CBC ****************
// ******************************************

size_t gmlib_aes128_cbc_encrypt_ctx_size()
{
    return sizeof(AES128CbcEncryptor);
}

void* gmlib_aes128_cbc_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES128CbcEncryptor();
}

int gmlib_aes128_cbc_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128CbcEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_cbc_encrypt_get_user_key_len()
{
    return AES128CbcEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_cbc_encrypt_get_iv_len()
{
    return AES128CbcEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_cbc_encrypt_get_block_size()
{
    return AES128CbcEncryptor::BLOCK_SIZE;
}

int gmlib_aes128_cbc_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CbcEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CbcEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128CbcEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes128_cbc_decrypt_ctx_size()
{
    return sizeof(AES128CbcDecryptor);
}

void* gmlib_aes128_cbc_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES128CbcDecryptor();
}

int gmlib_aes128_cbc_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128CbcDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_cbc_decrypt_get_user_key_len()
{
    return AES128CbcDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_cbc_decrypt_get_iv_len()
{
    return AES128CbcDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_cbc_decrypt_get_block_size()
{
    return AES128CbcDecryptor::BLOCK_SIZE;
}

int gmlib_aes128_cbc_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CbcDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CbcDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128CbcDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES128-CFB ****************
// ******************************************

size_t gmlib_aes128_cfb_encrypt_ctx_size()
{
    return sizeof(AES128CfbEncryptor);
}

void* gmlib_aes128_cfb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES128CfbEncryptor();
}

int gmlib_aes128_cfb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128CfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_cfb_encrypt_get_user_key_len()
{
    return AES128CfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_cfb_encrypt_get_iv_len()
{
    return AES128CfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_cfb_encrypt_get_block_size()
{
    return AES128CfbEncryptor::BLOCK_SIZE;
}

int gmlib_aes128_cfb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128CfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes128_cfb_decrypt_ctx_size()
{
    return sizeof(AES128CfbDecryptor);
}

void* gmlib_aes128_cfb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES128CfbDecryptor();
}

int gmlib_aes128_cfb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128CfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_cfb_decrypt_get_user_key_len()
{
    return AES128CfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_cfb_decrypt_get_iv_len()
{
    return AES128CfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_cfb_decrypt_get_block_size()
{
    return AES128CfbDecryptor::BLOCK_SIZE;
}

int gmlib_aes128_cfb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128CfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES128-OFB ****************
// ******************************************

size_t gmlib_aes128_ofb_encrypt_ctx_size()
{
    return sizeof(AES128OfbEncryptor);
}

void* gmlib_aes128_ofb_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES128OfbEncryptor();
}

int gmlib_aes128_ofb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128OfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_ofb_encrypt_get_user_key_len()
{
    return AES128OfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_ofb_encrypt_get_iv_len()
{
    return AES128OfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_ofb_encrypt_get_block_size()
{
    return AES128OfbEncryptor::BLOCK_SIZE;
}

int gmlib_aes128_ofb_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128OfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128OfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128OfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes128_ofb_decrypt_ctx_size()
{
    return sizeof(AES128OfbDecryptor);
}

void* gmlib_aes128_ofb_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES128OfbDecryptor();
}

int gmlib_aes128_ofb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128OfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_ofb_decrypt_get_user_key_len()
{
    return AES128OfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_ofb_decrypt_get_iv_len()
{
    return AES128OfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_ofb_decrypt_get_block_size()
{
    return AES128OfbDecryptor::BLOCK_SIZE;
}

int gmlib_aes128_ofb_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128OfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128OfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128OfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES128-CTR ****************
// ******************************************

size_t gmlib_aes128_ctr_encrypt_ctx_size()
{
    return sizeof(AES128CtrEncryptor);
}

void* gmlib_aes128_ctr_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES128CtrEncryptor();
}

int gmlib_aes128_ctr_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128CtrEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_ctr_encrypt_get_user_key_len()
{
    return AES128CtrEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_ctr_encrypt_get_iv_len()
{
    return AES128CtrEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_ctr_encrypt_get_block_size()
{
    return AES128CtrEncryptor::BLOCK_SIZE;
}

int gmlib_aes128_ctr_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CtrEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CtrEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128CtrEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_aes128_ctr_decrypt_ctx_size()
{
    return sizeof(AES128CtrDecryptor);
}

void* gmlib_aes128_ctr_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES128CtrDecryptor();
}

int gmlib_aes128_ctr_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128CtrDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_ctr_decrypt_get_user_key_len()
{
    return AES128CtrDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_ctr_decrypt_get_iv_len()
{
    return AES128CtrDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_ctr_decrypt_get_block_size()
{
    return AES128CtrDecryptor::BLOCK_SIZE;
}

int gmlib_aes128_ctr_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                    //
        iv_len != AES128CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CtrDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_reset(void*          ctx,
                                       const uint8_t* iv,
                                       size_t         iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != AES128CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CtrDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128CtrDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** AES128-GCM ****************
// ******************************************

size_t gmlib_aes128_gcm_encrypt_ctx_size()
{
    return sizeof(AES128GcmEncryptor);
}

void* gmlib_aes128_gcm_encrypt_ctx_alloc()
{
    return new (std::nothrow) AES128GcmEncryptor();
}

int gmlib_aes128_gcm_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128GcmEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_gcm_encrypt_get_user_key_len()
{
    return AES128GcmEncryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_gcm_encrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_aes128_gcm_encrypt_get_block_size()
{
    return AES128GcmEncryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_gcm_encrypt_get_tag_len()
{
    return 16;
}

int gmlib_aes128_gcm_encrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                   //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128GcmEncryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<AES128GcmEncryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128GcmEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128GcmEncryptor*>(ctx);
        ptr->get_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmEncryptor::get_tag");
        return -1;
    }
    return 0;
}

size_t gmlib_aes128_gcm_decrypt_ctx_size()
{
    return sizeof(AES128GcmDecryptor);
}

void* gmlib_aes128_gcm_decrypt_ctx_alloc()
{
    return new (std::nothrow) AES128GcmDecryptor();
}

int gmlib_aes128_gcm_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<AES128GcmDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_aes128_gcm_decrypt_get_user_key_len()
{
    return AES128GcmDecryptor::USER_KEY_LEN;
}

size_t gmlib_aes128_gcm_decrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_aes128_gcm_decrypt_get_block_size()
{
    return AES128GcmDecryptor::BLOCK_SIZE;
}

size_t gmlib_aes128_gcm_decrypt_get_tag_len()
{
    return 16;
}

int gmlib_aes128_gcm_decrypt_ctx_init(void*          ctx,
                                      const uint8_t* user_key,
                                      size_t         user_key_len,
                                      const uint8_t* iv,
                                      size_t         iv_len,
                                      const uint8_t* aad,
                                      size_t         aad_len)
{
    if (ctx == nullptr ||                                   //
        user_key == nullptr ||                              //
        user_key_len != AES128GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                   //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128GcmDecryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<AES128GcmDecryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<AES128GcmDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<AES128GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_aes128_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<AES128GcmDecryptor*>(ctx);
        ptr->set_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened AES128GcmDecryptor::set_tag");
        return -1;
    }
    return 0;
}
