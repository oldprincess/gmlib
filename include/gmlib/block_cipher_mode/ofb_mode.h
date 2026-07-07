#ifndef BLOCK_CIPHER_MODE_OFB_MODE_H
#define BLOCK_CIPHER_MODE_OFB_MODE_H

#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/type_traits.h>

namespace block_cipher_mode {

template <class BlockCipher>
class OfbEncryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit OfbEncryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_ofb_encryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_ofb_encryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::OfbEncryptorImpl<BlockCipher>>();
        }
    }

    OfbEncryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : OfbEncryptor(provider)
    {
        this->init(user_key, iv);
    }

    OfbEncryptor(const OfbEncryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    OfbEncryptor& operator=(const OfbEncryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    OfbEncryptor(OfbEncryptor&& other) noexcept            = default;
    OfbEncryptor& operator=(OfbEncryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return impl_->clone();
    }

    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        const std::uint8_t* key    = user_key;
        const std::uint8_t* iv_p   = iv;
        void*               args[] = {&key, &iv_p};
        dispatch_ctrl(*impl_, "init", 2, args);
    }

    void reset(const std::uint8_t* iv)
    {
        const std::uint8_t* iv_p   = iv;
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
class OfbDecryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit OfbDecryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_ofb_decryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_ofb_decryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::OfbDecryptorImpl<BlockCipher>>();
        }
    }

    OfbDecryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : OfbDecryptor(provider)
    {
        this->init(user_key, iv);
    }

    OfbDecryptor(const OfbDecryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    OfbDecryptor& operator=(const OfbDecryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    OfbDecryptor(OfbDecryptor&& other) noexcept            = default;
    OfbDecryptor& operator=(OfbDecryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return impl_->clone();
    }

    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        const std::uint8_t* key    = user_key;
        const std::uint8_t* iv_p   = iv;
        void*               args[] = {&key, &iv_p};
        dispatch_ctrl(*impl_, "init", 2, args);
    }

    void reset(const std::uint8_t* iv)
    {
        const std::uint8_t* iv_p   = iv;
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
