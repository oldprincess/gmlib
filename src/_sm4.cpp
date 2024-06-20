#include <gmlib/_debug.h>
#include <gmlib/_sm4.h>
#include <gmlib/sm4/sm4_mode.h>

#include <limits>

using namespace sm4;

// ******************************************
// ************** SM4-ECB *******************
// ******************************************

size_t gmlib_sm4_ecb_encrypt_ctx_size()
{
    return sizeof(SM4EcbEncryptor);
}

void* gmlib_sm4_ecb_encrypt_ctx_alloc()
{
    return new (std::nothrow) SM4EcbEncryptor();
}

int gmlib_sm4_ecb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4EcbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_ecb_encrypt_get_user_key_len()
{
    return SM4EcbEncryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_ecb_encrypt_get_block_size()
{
    return SM4EcbEncryptor::BLOCK_SIZE;
}

int gmlib_sm4_ecb_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != SM4EcbEncryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4EcbEncryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4EcbEncryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4EcbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4EcbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_sm4_ecb_decrypt_ctx_size()
{
    return sizeof(SM4EcbDecryptor);
}

void* gmlib_sm4_ecb_decrypt_ctx_alloc()
{
    return new (std::nothrow) SM4EcbDecryptor();
}

int gmlib_sm4_ecb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4EcbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_ecb_decrypt_get_user_key_len()
{
    return SM4EcbDecryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_ecb_decrypt_get_block_size()
{
    return SM4EcbDecryptor::BLOCK_SIZE;
}

int gmlib_sm4_ecb_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len)
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != SM4EcbDecryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4EcbDecryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_reset(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4EcbDecryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4EcbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4EcbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4EcbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** SM4-CBC *******************
// ******************************************

size_t gmlib_sm4_cbc_encrypt_ctx_size()
{
    return sizeof(SM4CbcEncryptor);
}

void* gmlib_sm4_cbc_encrypt_ctx_alloc()
{
    return new (std::nothrow) SM4CbcEncryptor();
}

int gmlib_sm4_cbc_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4CbcEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_cbc_encrypt_get_user_key_len()
{
    return SM4CbcEncryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_cbc_encrypt_get_iv_len()
{
    return SM4CbcEncryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_cbc_encrypt_get_block_size()
{
    return SM4CbcEncryptor::BLOCK_SIZE;
}

int gmlib_sm4_cbc_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CbcEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CbcEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4CbcEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CbcEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_sm4_cbc_decrypt_ctx_size()
{
    return sizeof(SM4CbcDecryptor);
}

void* gmlib_sm4_cbc_decrypt_ctx_alloc()
{
    return new (std::nothrow) SM4CbcDecryptor();
}

int gmlib_sm4_cbc_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4CbcDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_cbc_decrypt_get_user_key_len()
{
    return SM4CbcDecryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_cbc_decrypt_get_iv_len()
{
    return SM4CbcDecryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_cbc_decrypt_get_block_size()
{
    return SM4CbcDecryptor::BLOCK_SIZE;
}

int gmlib_sm4_cbc_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4CbcEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CbcDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4CbcEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CbcDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4CbcDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CbcDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CbcDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** SM4-CFB *******************
// ******************************************

size_t gmlib_sm4_cfb_encrypt_ctx_size()
{
    return sizeof(SM4CfbEncryptor);
}

void* gmlib_sm4_cfb_encrypt_ctx_alloc()
{
    return new (std::nothrow) SM4CfbEncryptor();
}

int gmlib_sm4_cfb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4CfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_cfb_encrypt_get_user_key_len()
{
    return SM4CfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_cfb_encrypt_get_iv_len()
{
    return SM4CfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_cfb_encrypt_get_block_size()
{
    return SM4CfbEncryptor::BLOCK_SIZE;
}

int gmlib_sm4_cfb_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4CfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_sm4_cfb_decrypt_ctx_size()
{
    return sizeof(SM4CfbDecryptor);
}

void* gmlib_sm4_cfb_decrypt_ctx_alloc()
{
    return new (std::nothrow) SM4CfbDecryptor();
}

int gmlib_sm4_cfb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4CfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_cfb_decrypt_get_user_key_len()
{
    return SM4CfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_cfb_decrypt_get_iv_len()
{
    return SM4CfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_cfb_decrypt_get_block_size()
{
    return SM4CfbDecryptor::BLOCK_SIZE;
}

int gmlib_sm4_cfb_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4CfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4CfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4CfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** SM4-OFB *******************
// ******************************************

size_t gmlib_sm4_ofb_encrypt_ctx_size()
{
    return sizeof(SM4OfbEncryptor);
}

void* gmlib_sm4_ofb_encrypt_ctx_alloc()
{
    return new (std::nothrow) SM4OfbEncryptor();
}

int gmlib_sm4_ofb_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4OfbEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_ofb_encrypt_get_user_key_len()
{
    return SM4OfbEncryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_ofb_encrypt_get_iv_len()
{
    return SM4OfbEncryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_ofb_encrypt_get_block_size()
{
    return SM4OfbEncryptor::BLOCK_SIZE;
}

int gmlib_sm4_ofb_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4OfbEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4OfbEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4OfbEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4OfbEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_sm4_ofb_decrypt_ctx_size()
{
    return sizeof(SM4OfbDecryptor);
}

void* gmlib_sm4_ofb_decrypt_ctx_alloc()
{
    return new (std::nothrow) SM4OfbDecryptor();
}

int gmlib_sm4_ofb_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4OfbDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_ofb_decrypt_get_user_key_len()
{
    return SM4OfbDecryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_ofb_decrypt_get_iv_len()
{
    return SM4OfbDecryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_ofb_decrypt_get_block_size()
{
    return SM4OfbDecryptor::BLOCK_SIZE;
}

int gmlib_sm4_ofb_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4OfbEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4OfbDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4OfbEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4OfbDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4OfbDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4OfbDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4OfbDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** SM4-CTR *******************
// ******************************************

size_t gmlib_sm4_ctr_encrypt_ctx_size()
{
    return sizeof(SM4CtrEncryptor);
}

void* gmlib_sm4_ctr_encrypt_ctx_alloc()
{
    return new (std::nothrow) SM4CtrEncryptor();
}

int gmlib_sm4_ctr_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4CtrEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_ctr_encrypt_get_user_key_len()
{
    return SM4CtrEncryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_ctr_encrypt_get_iv_len()
{
    return SM4CtrEncryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_ctr_encrypt_get_block_size()
{
    return SM4CtrEncryptor::BLOCK_SIZE;
}

int gmlib_sm4_ctr_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CtrEncryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CtrEncryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4CtrEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CtrEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrEncryptor::do_final");
        return -1;
    }
    return 0;
}

size_t gmlib_sm4_ctr_decrypt_ctx_size()
{
    return sizeof(SM4CtrDecryptor);
}

void* gmlib_sm4_ctr_decrypt_ctx_alloc()
{
    return new (std::nothrow) SM4CtrDecryptor();
}

int gmlib_sm4_ctr_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4CtrDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_ctr_decrypt_get_user_key_len()
{
    return SM4CtrDecryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_ctr_decrypt_get_iv_len()
{
    return SM4CtrDecryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_ctr_decrypt_get_block_size()
{
    return SM4CtrDecryptor::BLOCK_SIZE;
}

int gmlib_sm4_ctr_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4CtrEncryptor::USER_KEY_LEN || //
        iv == nullptr ||                                 //
        iv_len != SM4CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CtrDecryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_reset(void* ctx, const uint8_t* iv, size_t iv_len)
{
    if (ctx == nullptr || iv == nullptr ||
        iv_len != SM4CtrEncryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CtrDecryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4CtrDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4CtrDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4CtrDecryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** SM4-GCM *******************
// ******************************************

size_t gmlib_sm4_gcm_encrypt_ctx_size()
{
    return sizeof(SM4GcmEncryptor);
}

void* gmlib_sm4_gcm_encrypt_ctx_alloc()
{
    return new (std::nothrow) SM4GcmEncryptor();
}

int gmlib_sm4_gcm_encrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4GcmEncryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_gcm_encrypt_get_user_key_len()
{
    return SM4GcmEncryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_gcm_encrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_sm4_gcm_encrypt_get_block_size()
{
    return SM4GcmEncryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_gcm_encrypt_get_tag_len()
{
    return 16;
}

int gmlib_sm4_gcm_encrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len,
                                   const uint8_t* aad,
                                   size_t         aad_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4GcmEncryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmEncryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<SM4GcmEncryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmEncryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4GcmEncryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmEncryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4GcmEncryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmEncryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4GcmEncryptor*>(ctx);
        ptr->get_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmEncryptor::get_tag");
        return -1;
    }
    return 0;
}

size_t gmlib_sm4_gcm_decrypt_ctx_size()
{
    return sizeof(SM4GcmDecryptor);
}

void* gmlib_sm4_gcm_decrypt_ctx_alloc()
{
    return new (std::nothrow) SM4GcmDecryptor();
}

int gmlib_sm4_gcm_decrypt_ctx_free(void* ctx)
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<SM4GcmDecryptor*>(ctx);
    delete ptr;
    return 0;
}

size_t gmlib_sm4_gcm_decrypt_get_user_key_len()
{
    return SM4GcmDecryptor::USER_KEY_LEN;
}

size_t gmlib_sm4_gcm_decrypt_get_default_iv_len()
{
    return 12;
}

size_t gmlib_sm4_gcm_decrypt_get_block_size()
{
    return SM4GcmDecryptor::BLOCK_SIZE;
}

size_t gmlib_sm4_gcm_decrypt_get_tag_len()
{
    return 16;
}

int gmlib_sm4_gcm_decrypt_ctx_init(void*          ctx,
                                   const uint8_t* user_key,
                                   size_t         user_key_len,
                                   const uint8_t* iv,
                                   size_t         iv_len,
                                   const uint8_t* aad,
                                   size_t         aad_len)
{
    if (ctx == nullptr ||                                //
        user_key == nullptr ||                           //
        user_key_len != SM4GcmEncryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||                //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4GcmDecryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmDecryptor::init");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<SM4GcmDecryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmDecryptor::reset");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_update(void*          ctx,
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
        auto ptr = static_cast<SM4GcmDecryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmDecryptor::update");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<SM4GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl)
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4GcmDecryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmDecryptor::do_final");
        return -1;
    }
    return 0;
}

int gmlib_sm4_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag)
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<SM4GcmDecryptor*>(ctx);
        ptr->set_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened SM4GcmDecryptor::set_tag");
        return -1;
    }
    return 0;
}
