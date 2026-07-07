#ifndef BLOCK_CIPHER_MODE_CBC_MODE_H
#define BLOCK_CIPHER_MODE_CBC_MODE_H

#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/type_traits.h>

namespace block_cipher_mode {

template <class BlockCipher>
class CbcEncryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit CbcEncryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_cbc_encryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_cbc_encryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::CbcEncryptorImpl<BlockCipher>>();
        }
    }

    CbcEncryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : CbcEncryptor(provider)
    {
        this->init(user_key, iv);
    }

    CbcEncryptor(const CbcEncryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    CbcEncryptor& operator=(const CbcEncryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    CbcEncryptor(CbcEncryptor&& other) noexcept            = default;
    CbcEncryptor& operator=(CbcEncryptor&& other) noexcept = default;

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
class CbcDecryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit CbcDecryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_cbc_decryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_cbc_decryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::CbcDecryptorImpl<BlockCipher>>();
        }
    }

    CbcDecryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 const char*         provider = nullptr)
        : CbcDecryptor(provider)
    {
        this->init(user_key, iv);
    }

    CbcDecryptor(const CbcDecryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    CbcDecryptor& operator=(const CbcDecryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    CbcDecryptor(CbcDecryptor&& other) noexcept            = default;
    CbcDecryptor& operator=(CbcDecryptor&& other) noexcept = default;

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
