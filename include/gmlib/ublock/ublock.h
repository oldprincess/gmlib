#ifndef UBLOCK_UBLOCK_H
#define UBLOCK_UBLOCK_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/ublock/provider.h>

#include <memory>
#include <stdexcept>

namespace ublock {

class uBlock128128 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "uBlock-128-128";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 16;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_;

public:
    explicit uBlock128128(const char* provider = nullptr)
    {
        const auto* p = get_ublock128128_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("uBlock128128: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    uBlock128128(const uBlock128128& other) : impl_(other.impl_->clone())
    {
    }

    uBlock128128& operator=(const uBlock128128& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    uBlock128128(uBlock128128&& other) noexcept            = default;
    uBlock128128& operator=(uBlock128128&& other) noexcept = default;

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

    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const override
    {
        impl_->decrypt_block(plaintext, ciphertext);
    }

    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const override
    {
        impl_->encrypt_blocks(ciphertext, plaintext, block_num);
    }

    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

class uBlock128256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "uBlock-128-256";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_;

public:
    explicit uBlock128256(const char* provider = nullptr)
    {
        const auto* p = get_ublock128256_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("uBlock128256: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    uBlock128256(const uBlock128256& other) : impl_(other.impl_->clone())
    {
    }

    uBlock128256& operator=(const uBlock128256& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    uBlock128256(uBlock128256&& other) noexcept            = default;
    uBlock128256& operator=(uBlock128256&& other) noexcept = default;

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

    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const override
    {
        impl_->decrypt_block(plaintext, ciphertext);
    }

    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const override
    {
        impl_->encrypt_blocks(ciphertext, plaintext, block_num);
    }

    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

class uBlock256256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "uBlock-256-256";
    static constexpr std::size_t BLOCK_SIZE        = 32;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_;

public:
    explicit uBlock256256(const char* provider = nullptr)
    {
        const auto* p = get_ublock256256_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("uBlock256256: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    uBlock256256(const uBlock256256& other) : impl_(other.impl_->clone())
    {
    }

    uBlock256256& operator=(const uBlock256256& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    uBlock256256(uBlock256256&& other) noexcept            = default;
    uBlock256256& operator=(uBlock256256&& other) noexcept = default;

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

    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const override
    {
        impl_->decrypt_block(plaintext, ciphertext);
    }

    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const override
    {
        impl_->encrypt_blocks(ciphertext, plaintext, block_num);
    }

    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

} // namespace ublock

#endif
