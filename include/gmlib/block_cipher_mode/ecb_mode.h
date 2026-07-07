#ifndef BLOCK_CIPHER_MODE_ECB_MODE_H
#define BLOCK_CIPHER_MODE_ECB_MODE_H

#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/type_traits.h>

namespace block_cipher_mode {

template <class BlockCipher>
class EcbEncryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit EcbEncryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_ecb_encryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_ecb_encryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::EcbEncryptorImpl<BlockCipher>>();
        }
    }

    EcbEncryptor(const std::uint8_t* user_key, const char* provider = nullptr)
        : EcbEncryptor(provider)
    {
        this->init(user_key);
    }

    EcbEncryptor(const EcbEncryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    EcbEncryptor& operator=(const EcbEncryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    EcbEncryptor(EcbEncryptor&& other) noexcept            = default;
    EcbEncryptor& operator=(EcbEncryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return impl_->clone();
    }

    void init(const std::uint8_t* user_key)
    {
        const std::uint8_t* key  = user_key;
        void*               args[] = {&key};
        dispatch_ctrl(*impl_, "init", 1, args);
    }

    void reset()
    {
        dispatch_ctrl(*impl_, "reset", 0, nullptr);
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
class EcbDecryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit EcbDecryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_ecb_decryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_ecb_decryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::EcbDecryptorImpl<BlockCipher>>();
        }
    }

    EcbDecryptor(const std::uint8_t* user_key, const char* provider = nullptr)
        : EcbDecryptor(provider)
    {
        this->init(user_key);
    }

    EcbDecryptor(const EcbDecryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    EcbDecryptor& operator=(const EcbDecryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    EcbDecryptor(EcbDecryptor&& other) noexcept            = default;
    EcbDecryptor& operator=(EcbDecryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return impl_->clone();
    }

    void init(const std::uint8_t* user_key)
    {
        const std::uint8_t* key  = user_key;
        void*               args[] = {&key};
        dispatch_ctrl(*impl_, "init", 1, args);
    }

    void reset()
    {
        dispatch_ctrl(*impl_, "reset", 0, nullptr);
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
