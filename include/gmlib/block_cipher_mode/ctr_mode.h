#ifndef BLOCK_CIPHER_MODE_CTR_MODE_H
#define BLOCK_CIPHER_MODE_CTR_MODE_H

#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/type_traits.h>

namespace block_cipher_mode {

template <class BlockCipher>
class CtrEncryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit CtrEncryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_ctr_encryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_ctr_encryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::CtrEncryptorImpl<BlockCipher>>();
        }
    }

    CtrEncryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : CtrEncryptor(provider)
    {
        this->init(user_key, iv);
    }

    CtrEncryptor(const CtrEncryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    CtrEncryptor& operator=(const CtrEncryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    CtrEncryptor(CtrEncryptor&& other) noexcept            = default;
    CtrEncryptor& operator=(CtrEncryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return impl_->clone();
    }

    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        const std::uint8_t* key  = user_key;
        const std::uint8_t* iv_p = iv;
        void*               args[] = {&key, &iv_p};
        dispatch_ctrl(*impl_, "init", 2, args);
    }

    void reset(const std::uint8_t* iv)
    {
        const std::uint8_t* iv_p = iv;
        void*               args[] = {&iv_p};
        dispatch_ctrl(*impl_, "reset", 1, args);
    }

private:
    BlockCipherMode& impl() noexcept override
    {
        return *impl_;
    }

    const BlockCipherMode& impl() const noexcept override
    {
        return *impl_;
    }
};

template <class BlockCipher>
class CtrDecryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit CtrDecryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_ctr_decryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_ctr_decryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::CtrDecryptorImpl<BlockCipher>>();
        }
    }

    CtrDecryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : CtrDecryptor(provider)
    {
        this->init(user_key, iv);
    }

    CtrDecryptor(const CtrDecryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    CtrDecryptor& operator=(const CtrDecryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    CtrDecryptor(CtrDecryptor&& other) noexcept            = default;
    CtrDecryptor& operator=(CtrDecryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return impl_->clone();
    }

    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        const std::uint8_t* key  = user_key;
        const std::uint8_t* iv_p = iv;
        void*               args[] = {&key, &iv_p};
        dispatch_ctrl(*impl_, "init", 2, args);
    }

    void reset(const std::uint8_t* iv)
    {
        const std::uint8_t* iv_p = iv;
        void*               args[] = {&iv_p};
        dispatch_ctrl(*impl_, "reset", 1, args);
    }

private:
    BlockCipherMode& impl() noexcept override
    {
        return *impl_;
    }

    const BlockCipherMode& impl() const noexcept override
    {
        return *impl_;
    }
};

} // namespace block_cipher_mode

#endif
