#ifndef C_API_TP_CIPHER_H
#define C_API_TP_CIPHER_H

#include <gmlib/_debug.h>
#include <stddef.h>
#include <stdint.h>

namespace c_api {

// ******************************************
// ************** CIPHER-ECB ****************
// ******************************************

template <class Cryptor>
size_t cipher_ecb_encrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_ecb_encrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_ecb_encrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_ecb_encrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_ecb_encrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_ecb_encrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_ecb_encrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_ecb_encrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len) noexcept
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != Cryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_encrypt_ctx_reset(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_encrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_encrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
size_t cipher_ecb_decrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_ecb_decrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_ecb_decrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_ecb_decrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_ecb_decrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_ecb_decrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_ecb_decrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_ecb_decrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len) noexcept
{
    if (ctx == nullptr || user_key == nullptr ||
        user_key_len != Cryptor::USER_KEY_LEN)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_decrypt_ctx_reset(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_decrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_decrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ecb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** CIPHER-CBC ****************
// ******************************************

template <class Cryptor>
size_t cipher_cbc_encrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_cbc_encrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_cbc_encrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_cbc_encrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_cbc_encrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_cbc_encrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_cbc_encrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_cbc_encrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_cbc_encrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_encrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_encrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_encrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
size_t cipher_cbc_decrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_cbc_decrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_cbc_decrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_cbc_decrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_cbc_decrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_cbc_decrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_cbc_decrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_cbc_decrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_cbc_decrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_decrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_decrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_decrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cbc_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** CIPHER-CFB ****************
// ******************************************

template <class Cryptor>
size_t cipher_cfb_encrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_cfb_encrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_cfb_encrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_cfb_encrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_cfb_encrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_cfb_encrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_cfb_encrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_cfb_encrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_cfb_encrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_encrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_encrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_encrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
size_t cipher_cfb_decrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_cfb_decrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_cfb_decrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_cfb_decrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_cfb_decrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_cfb_decrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_cfb_decrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_cfb_decrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_cfb_decrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_decrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_decrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_decrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_cfb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** CIPHER-OFB ****************
// ******************************************

template <class Cryptor>
size_t cipher_ofb_encrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_ofb_encrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_ofb_encrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_ofb_encrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_ofb_encrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_ofb_encrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_ofb_encrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_ofb_encrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_ofb_encrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_encrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_encrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_encrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
size_t cipher_ofb_decrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_ofb_decrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_ofb_decrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_ofb_decrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_ofb_decrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_ofb_decrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_ofb_decrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_ofb_decrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_ofb_decrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_decrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_decrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_decrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ofb_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** CIPHER-CTR ****************
// ******************************************

template <class Cryptor>
size_t cipher_ctr_encrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_ctr_encrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_ctr_encrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_ctr_encrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_ctr_encrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_ctr_encrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_ctr_encrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_ctr_encrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_ctr_encrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_encrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_encrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_encrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
size_t cipher_ctr_decrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_ctr_decrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_ctr_decrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_ctr_decrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_ctr_decrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_ctr_decrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_ctr_decrypt_get_iv_len() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_ctr_decrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
int cipher_ctr_decrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len) noexcept
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        iv == nullptr ||                         //
        iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_decrypt_ctx_reset(void*          ctx,
                                 const uint8_t* iv,
                                 size_t         iv_len) noexcept
{
    if (ctx == nullptr || iv == nullptr || iv_len != Cryptor::BLOCK_SIZE)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_decrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_decrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_ctr_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** CIPHER-GCM ****************
// ******************************************

template <class Cryptor>
size_t cipher_gcm_encrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_gcm_encrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_gcm_encrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_gcm_encrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_gcm_encrypt_get_default_iv_len()
{
    return 12;
}

template <class Cryptor>
size_t cipher_gcm_encrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_gcm_encrypt_get_tag_len()
{
    return 16;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len,
                                const uint8_t* aad,
                                size_t         aad_len)
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||        //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_get_tag(void* ctx, uint8_t* tag) noexcept
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->get_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::get_tag");
        return -1;
    }
    return 0;
}

template <class Cryptor>
size_t cipher_gcm_decrypt_ctx_size() noexcept
{
    return sizeof(Cryptor);
}

template <class Cryptor>
void* cipher_gcm_decrypt_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
void* cipher_gcm_decrypt_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Cryptor))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Cryptor());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::Cryptor()");
    }
    return ptr;
}

template <class Cryptor>
int cipher_gcm_decrypt_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    delete ptr;
    return 0;
}

template <class Cryptor>
int cipher_gcm_decrypt_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Cryptor*>(ctx);
    ptr->~Cryptor();
    return 0;
}

template <class Cryptor>
size_t cipher_gcm_decrypt_get_user_key_len() noexcept
{
    return Cryptor::USER_KEY_LEN;
}

template <class Cryptor>
size_t cipher_gcm_decrypt_get_default_iv_len()
{
    return 12;
}

template <class Cryptor>
size_t cipher_gcm_decrypt_get_block_size() noexcept
{
    return Cryptor::BLOCK_SIZE;
}

template <class Cryptor>
size_t cipher_gcm_decrypt_get_tag_len()
{
    return 16;
}

template <class Cryptor>
int cipher_gcm_decrypt_ctx_init(void*          ctx,
                                const uint8_t* user_key,
                                size_t         user_key_len,
                                const uint8_t* iv,
                                size_t         iv_len,
                                const uint8_t* aad,
                                size_t         aad_len)
{
    if (ctx == nullptr ||                        //
        user_key == nullptr ||                   //
        user_key_len != Cryptor::USER_KEY_LEN || //
        (iv == nullptr && iv_len != 0) ||        //
        (aad == nullptr && aad_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->init(user_key, iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::init");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_decrypt_ctx_reset(void*          ctx,
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
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->reset(iv, iv_len, aad, aad_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::reset");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_decrypt_ctx_update(void*          ctx,
                                  uint8_t*       out,
                                  size_t*        outl,
                                  const uint8_t* in,
                                  size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->update(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::update");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_decrypt_ctx_final_ex(void*          ctx,
                                    uint8_t*       out,
                                    size_t*        outl,
                                    const uint8_t* in,
                                    size_t         inl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr ||
        (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_decrypt_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->do_final(out, outl, nullptr, 0);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::do_final");
        return -1;
    }
    return 0;
}

template <class Cryptor>
int cipher_gcm_encrypt_ctx_set_tag(void* ctx, const uint8_t* tag) noexcept
{
    if (ctx == nullptr || tag == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Cryptor*>(ctx);
        ptr->set_tag(tag);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Cryptor::set_tag");
        return -1;
    }
    return 0;
}

} // namespace c_api

#endif