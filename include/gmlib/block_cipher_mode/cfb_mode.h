#ifndef BLOCK_CIPHER_MODE_CFB_MODE_H
#define BLOCK_CIPHER_MODE_CFB_MODE_H

#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/type_traits.h>

namespace block_cipher_mode {

template <class BlockCipher>
class CfbEncryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit CfbEncryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_cfb_encryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_cfb_encryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::CfbEncryptorImpl<BlockCipher>>();
        }
    }

    CfbEncryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : CfbEncryptor(provider)
    {
        this->init(user_key, iv);
    }

    CfbEncryptor(const CfbEncryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    CfbEncryptor& operator=(const CfbEncryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    CfbEncryptor(CfbEncryptor&& other) noexcept            = default;
    CfbEncryptor& operator=(CfbEncryptor&& other) noexcept = default;

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
class CfbDecryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit CfbDecryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_cfb_decryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_cfb_decryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::CfbDecryptorImpl<BlockCipher>>();
        }
    }

    CfbDecryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : CfbDecryptor(provider)
    {
        this->init(user_key, iv);
    }

    CfbDecryptor(const CfbDecryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    CfbDecryptor& operator=(const CfbDecryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    CfbDecryptor(CfbDecryptor&& other) noexcept            = default;
    CfbDecryptor& operator=(CfbDecryptor&& other) noexcept = default;

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
