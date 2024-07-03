#ifndef C_API_HASH_H
#define C_API_HASH_H

#include <gmlib/_debug.h>
#include <stddef.h>
#include <stdint.h>

namespace c_api {

template <class Hash>
size_t hash_ctx_size() noexcept
{
    return sizeof(Hash);
}

template <class Hash>
void* hash_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new Hash());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Hash::Hash()");
    }
    return ptr;
}

template <class Hash>
void* hash_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(Hash))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) Hash());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new Hash::Hash()");
    }
    return ptr;
}

template <class Hash>
int hash_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Hash*>(ctx);
    delete ptr;
    return 0;
}

template <class Hash>
int hash_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<Hash*>(ctx);
    ptr->~Hash();
    return 0;
}

template <class Hash>
size_t hash_get_digest_size() noexcept
{
    return Hash::DIGEST_SIZE;
}

template <class Hash>
size_t hash_get_block_size() noexcept
{
    return Hash::BLOCK_SIZE;
}

template <class Hash>
int hash_ctx_init(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Hash*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Hash::reset");
        return -1;
    }
    return 0;
}

template <class Hash>
int hash_ctx_reset(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Hash*>(ctx);
        ptr->reset();
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Hash::reset");
        return -1;
    }
    return 0;
}

template <class Hash>
int hash_ctx_update(void* ctx, const uint8_t* in, size_t inl) noexcept
{
    if (ctx == nullptr || (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Hash*>(ctx);
        ptr->update(in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Hash::update");
        return -1;
    }
    return 0;
}

template <class Hash>
int hash_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<Hash*>(ctx);
        ptr->do_final(out, in, inl);
        *outl = Hash::DIGEST_SIZE;
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Hash::do_final");
        return -1;
    }
    return 0;
}

template <class Hash>
int hash_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<Hash*>(ctx);
        ptr->do_final(out);
        *outl = Hash::DIGEST_SIZE;
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened Hash::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** Hash-HMAC ******************
// ******************************************

template <class HMac>
size_t hmac_ctx_size() noexcept
{
    return sizeof(HMac);
}

template <class HMac>
void* hmac_ctx_new() noexcept
{
    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new HMac());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new HMac::HMac()");
    }
    return ptr;
}

template <class HMac>
void* hmac_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(HMac))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ptr = nullptr;
    try
    {
        ptr = static_cast<void*>(new (buf) HMac());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened new HMac::HMac()");
    }
    return ptr;
}

template <class HMac>
int hmac_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<HMac*>(ctx);
    delete ptr;
    return 0;
}

template <class HMac>
int hmac_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<HMac*>(ctx);
    ptr->~HMac();
    return 0;
}

template <class HMac>
size_t hmac_get_digest_size() noexcept
{
    return HMac::DIGEST_SIZE;
}

template <class HMac>
int hmac_ctx_init(void*          ctx,
                  const uint8_t* user_key,
                  size_t         user_key_len) noexcept
{
    if (ctx == nullptr || (user_key == nullptr && user_key_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<HMac*>(ctx);
        ptr->set_key(user_key, user_key_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMac::set_key");
        return -1;
    }
    return 0;
}

template <class HMac>
int hmac_ctx_reset(void*          ctx,
                   const uint8_t* user_key,
                   size_t         user_key_len) noexcept
{
    if (ctx == nullptr || (user_key == nullptr && user_key_len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<HMac*>(ctx);
        ptr->set_key(user_key, user_key_len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMac::set_key");
        return -1;
    }
    return 0;
}

template <class HMac>
int hmac_ctx_update(void* ctx, const uint8_t* in, size_t inl) noexcept
{
    if (ctx == nullptr || (in == nullptr && inl != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<HMac*>(ctx);
        ptr->update(in, inl);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMac::update");
        return -1;
    }
    return 0;
}

template <class HMac>
int hmac_ctx_final_ex(void*          ctx,
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
        auto ptr = static_cast<HMac*>(ctx);
        ptr->do_final(out, in, inl);
        *outl = HMac::DIGEST_SIZE;
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMac::do_final");
        return -1;
    }
    return 0;
}

template <class HMac>
int hmac_ctx_final(void* ctx, uint8_t* out, size_t* outl) noexcept
{
    if (ctx == nullptr || out == nullptr || outl == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<HMac*>(ctx);
        ptr->do_final(out);
        *outl = HMac::DIGEST_SIZE;
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMac::do_final");
        return -1;
    }
    return 0;
}

// ******************************************
// ************** HASH-DRBG *****************
// ******************************************

template <class HashDrbg>
size_t hash_drbg_ctx_size() noexcept
{
    return sizeof(HashDrbg);
}

template <class HashDrbg>
void* hash_drbg_ctx_new() noexcept
{
    void* ctx = nullptr;
    try
    {
        ctx = static_cast<void*>(new HashDrbg());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HashDrbg()");
    }
    return ctx;
}

template <class HashDrbg>
void* hash_drbg_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(HashDrbg))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ctx = nullptr;
    try
    {
        ctx = static_cast<void*>(new (buf) HashDrbg());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HashDrbg()");
    }
    return ctx;
}

template <class HashDrbg>
int hash_drbg_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<HashDrbg*>(ctx);
    delete ptr;
    return 0;
}

template <class HashDrbg>
int hash_drbg_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<HashDrbg*>(ctx);
    ptr->~HashDrbg();
    return 0;
}

template <class HashDrbg>
int hash_drbg_ctx_gen(void* ctx, void* out, size_t len) noexcept
{
    if (ctx == nullptr || (out == nullptr && len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<HashDrbg*>(ctx);
        ptr->gen(out, len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HashDrbg::gen");
        return -1;
    }
    return 0;
}

// ******************************************
// *************** HMAC-DRBG ****************
// ******************************************

template <class HMacDrbg>
size_t hmac_drbg_ctx_size() noexcept
{
    return sizeof(HMacDrbg);
}

template <class HMacDrbg>
void* hmac_drbg_ctx_new() noexcept
{
    void* ctx = nullptr;
    try
    {
        ctx = static_cast<void*>(new HMacDrbg());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMacDrbg()");
    }
    return ctx;
}

template <class HMacDrbg>
void* hmac_drbg_ctx_new_inplace(void* buf, size_t buf_size) noexcept
{
    if (buf == nullptr || buf_size != sizeof(HMacDrbg))
    {
        GMLIB_ERR_LOG("invalid input");
        return nullptr;
    }

    void* ctx = nullptr;
    try
    {
        ctx = static_cast<void*>(new (buf) HMacDrbg());
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMacDrbg()");
    }
    return ctx;
}

template <class HMacDrbg>
int hmac_drbg_ctx_delete(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<HMacDrbg*>(ctx);
    delete ptr;
    return 0;
}

template <class HMacDrbg>
int hmac_drbg_ctx_delete_inplace(void* ctx) noexcept
{
    if (ctx == nullptr)
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    auto ptr = static_cast<HMacDrbg*>(ctx);
    ptr->~HMacDrbg();
    return 0;
}

template <class HMacDrbg>
int hmac_drbg_ctx_gen(void* ctx, void* out, size_t len) noexcept
{
    if (ctx == nullptr || (out == nullptr && len != 0))
    {
        GMLIB_ERR_LOG("invalid input");
        return -1;
    }

    try
    {
        auto ptr = static_cast<HMacDrbg*>(ctx);
        ptr->gen(out, len);
    }
    catch (...)
    {
        GMLIB_ERR_LOG("err happened HMacDrbg::gen");
        return -1;
    }
    return 0;
}

} // namespace c_api

#endif