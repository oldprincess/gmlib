#ifndef BLOCK_CIPHER_MODE_GCM_MODE_H
#define BLOCK_CIPHER_MODE_GCM_MODE_H

#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/type_traits.h>

namespace block_cipher_mode {

template <class BlockCipher>
class GcmEncryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit GcmEncryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_gcm_encryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_gcm_encryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::GcmEncryptorImpl<BlockCipher>>();
        }
    }

    GcmEncryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 std::size_t         iv_len,
                 const std::uint8_t* aad,
                 std::size_t         aad_len,
                 const char*         provider = nullptr)
        : GcmEncryptor(provider)
    {
        this->init(user_key, iv, iv_len, aad, aad_len);
    }

    GcmEncryptor(const GcmEncryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    GcmEncryptor& operator=(const GcmEncryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    GcmEncryptor(GcmEncryptor&& other) noexcept            = default;
    GcmEncryptor& operator=(GcmEncryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::make_unique<GcmEncryptor>(*this);
    }

    void init(const std::uint8_t* user_key,
              const std::uint8_t* iv,
              std::size_t         iv_len,
              const std::uint8_t* aad,
              std::size_t         aad_len)
    {
        const std::uint8_t* key   = user_key;
        const std::uint8_t* iv_p  = iv;
        const std::uint8_t* aad_p = aad;
        void* args[] = {&key, &iv_p, &iv_len, &aad_p, &aad_len};
        dispatch_ctrl(*impl_, "init", 5, args);
    }

    void reset(const std::uint8_t* iv,
               std::size_t         iv_len,
               const std::uint8_t* aad,
               std::size_t         aad_len)
    {
        const std::uint8_t* iv_p  = iv;
        const std::uint8_t* aad_p = aad;
        void*               args[] = {&iv_p, &iv_len, &aad_p, &aad_len};
        dispatch_ctrl(*impl_, "reset", 4, args);
    }

    void get_tag(std::uint8_t tag[16]) const
    {
        std::uint8_t* tag_p = tag;
        void*         args[] = {&tag_p};
        const_cast<GcmEncryptor*>(this)->dispatch_ctrl(*impl_, "get_tag", 1,
                                                       args);
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
class GcmDecryptor : public impl::BlockCipherModeForwarder
{
private:
    std::unique_ptr<BlockCipherMode> impl_;

public:
    explicit GcmDecryptor(const char* provider = nullptr)
    {
        if constexpr (impl::has_create_gcm_decryptor<BlockCipher>::value)
        {
            impl_ = BlockCipher::create_gcm_decryptor(provider);
        }
        else
        {
            (void)provider;
            impl_ = std::make_unique<impl::GcmDecryptorImpl<BlockCipher>>();
        }
    }

    GcmDecryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 std::size_t         iv_len,
                 const std::uint8_t* aad,
                 std::size_t         aad_len,
                 const char*         provider = nullptr)
        : GcmDecryptor(provider)
    {
        this->init(user_key, iv, iv_len, aad, aad_len);
    }

    GcmDecryptor(const GcmDecryptor& other)
    {
        impl_ = other.impl_->clone();
    }

    GcmDecryptor& operator=(const GcmDecryptor& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    GcmDecryptor(GcmDecryptor&& other) noexcept            = default;
    GcmDecryptor& operator=(GcmDecryptor&& other) noexcept = default;

public:
    std::unique_ptr<BlockCipherMode> clone() const override
    {
        return std::make_unique<GcmDecryptor>(*this);
    }

    void init(const std::uint8_t* user_key,
              const std::uint8_t* iv,
              std::size_t         iv_len,
              const std::uint8_t* aad,
              std::size_t         aad_len)
    {
        const std::uint8_t* key   = user_key;
        const std::uint8_t* iv_p  = iv;
        const std::uint8_t* aad_p = aad;
        void* args[] = {&key, &iv_p, &iv_len, &aad_p, &aad_len};
        dispatch_ctrl(*impl_, "init", 5, args);
    }

    void reset(const std::uint8_t* iv,
               std::size_t         iv_len,
               const std::uint8_t* aad,
               std::size_t         aad_len)
    {
        const std::uint8_t* iv_p  = iv;
        const std::uint8_t* aad_p = aad;
        void*               args[] = {&iv_p, &iv_len, &aad_p, &aad_len};
        dispatch_ctrl(*impl_, "reset", 4, args);
    }

    void set_tag(const std::uint8_t tag[16])
    {
        const std::uint8_t* tag_p = tag;
        void*               args[] = {&tag_p};
        dispatch_ctrl(*impl_, "set_tag", 1, args);
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
