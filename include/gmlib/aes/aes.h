#ifndef AES_AES_H
#define AES_AES_H

#include <gmlib/aes/provider.h>
#include <gmlib/block_cipher_mode/block_cipher.h>

#include <memory>
#include <stdexcept>

namespace aes {

class AES128 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "AES128";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 16;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 16;

private:
    Cipher impl_;

public:
    explicit AES128(const char* provider = nullptr)
    {
        const auto* p = get_aes128_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("AES128: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    AES128(const AES128& other) : impl_(other.impl_->clone())
    {
    }

    AES128& operator=(const AES128& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    AES128(AES128&& other) noexcept            = default;
    AES128& operator=(AES128&& other) noexcept = default;

public:
    const char* get_name() const override
    {
        return impl_->get_name();
    }

    const char* get_impl_algo() const override
    {
        return impl_->get_impl_algo();
    }

    std::size_t get_block_size() const override
    {
        return impl_->get_block_size();
    }

    std::size_t get_key_len() const override
    {
        return impl_->get_key_len();
    }

    std::size_t get_parallel_num() const override
    {
        return impl_->get_parallel_num();
    }

    std::size_t get_security_strength() const override
    {
        return impl_->get_security_strength();
    }

    Cipher clone() const override
    {
        return impl_->clone();
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) override
    {
        impl_->set_key(user_key, enc);
    }

    void encrypt_block(std::uint8_t* out, const std::uint8_t* in) const override
    {
        impl_->encrypt_block(out, in);
    }

    void decrypt_block(std::uint8_t* out, const std::uint8_t* in) const override
    {
        impl_->decrypt_block(out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const override
    {
        impl_->encrypt_blocks(out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const override
    {
        impl_->decrypt_blocks(out, in, block_num);
    }
};

class AES192 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "AES192";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 24;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 24;

private:
    Cipher impl_;

public:
    explicit AES192(const char* provider = nullptr)
    {
        const auto* p = get_aes192_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("AES192: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    AES192(const AES192& other) : impl_(other.impl_->clone())
    {
    }

    AES192& operator=(const AES192& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    AES192(AES192&& other) noexcept            = default;
    AES192& operator=(AES192&& other) noexcept = default;

public:
    const char* get_name() const override
    {
        return impl_->get_name();
    }

    const char* get_impl_algo() const override
    {
        return impl_->get_impl_algo();
    }

    std::size_t get_block_size() const override
    {
        return impl_->get_block_size();
    }

    std::size_t get_key_len() const override
    {
        return impl_->get_key_len();
    }

    std::size_t get_parallel_num() const override
    {
        return impl_->get_parallel_num();
    }

    std::size_t get_security_strength() const override
    {
        return impl_->get_security_strength();
    }

    Cipher clone() const override
    {
        return impl_->clone();
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) override
    {
        impl_->set_key(user_key, enc);
    }

    void encrypt_block(std::uint8_t* out, const std::uint8_t* in) const override
    {
        impl_->encrypt_block(out, in);
    }

    void decrypt_block(std::uint8_t* out, const std::uint8_t* in) const override
    {
        impl_->decrypt_block(out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const override
    {
        impl_->encrypt_blocks(out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const override
    {
        impl_->decrypt_blocks(out, in, block_num);
    }
};

class AES256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "AES256";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 32;

private:
    Cipher impl_;

public:
    explicit AES256(const char* provider = nullptr)
    {
        const auto* p = get_aes256_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("AES256: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    AES256(const AES256& other) : impl_(other.impl_->clone())
    {
    }

    AES256& operator=(const AES256& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    AES256(AES256&& other) noexcept            = default;
    AES256& operator=(AES256&& other) noexcept = default;

public:
    const char* get_name() const override
    {
        return impl_->get_name();
    }

    const char* get_impl_algo() const override
    {
        return impl_->get_impl_algo();
    }

    std::size_t get_block_size() const override
    {
        return impl_->get_block_size();
    }

    std::size_t get_key_len() const override
    {
        return impl_->get_key_len();
    }

    std::size_t get_parallel_num() const override
    {
        return impl_->get_parallel_num();
    }

    std::size_t get_security_strength() const override
    {
        return impl_->get_security_strength();
    }

    Cipher clone() const override
    {
        return impl_->clone();
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) override
    {
        impl_->set_key(user_key, enc);
    }

    void encrypt_block(std::uint8_t* out, const std::uint8_t* in) const override
    {
        impl_->encrypt_block(out, in);
    }

    void decrypt_block(std::uint8_t* out, const std::uint8_t* in) const override
    {
        impl_->decrypt_block(out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const override
    {
        impl_->encrypt_blocks(out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const override
    {
        impl_->decrypt_blocks(out, in, block_num);
    }
};

} // namespace aes

#endif
