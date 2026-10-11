#ifndef BALLET_BALLET_H
#define BALLET_BALLET_H

#include <gmlib/ballet/provider.h>
#include <gmlib/block_cipher_mode/block_cipher.h>

#include <memory>
#include <stdexcept>

namespace ballet {

class Ballet128128 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "Ballet-128-128";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 16;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_;

public:
    explicit Ballet128128(const char* provider = nullptr)
    {
        const auto* p = get_ballet128128_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("Ballet128128: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    Ballet128128(const Ballet128128& other) : impl_(other.impl_->clone())
    {
    }

    Ballet128128& operator=(const Ballet128128& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    Ballet128128(Ballet128128&& other) noexcept            = default;
    Ballet128128& operator=(Ballet128128&& other) noexcept = default;

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

class Ballet128256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "Ballet-128-256";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_;

public:
    explicit Ballet128256(const char* provider = nullptr)
    {
        const auto* p = get_ballet128256_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("Ballet128256: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    Ballet128256(const Ballet128256& other) : impl_(other.impl_->clone())
    {
    }

    Ballet128256& operator=(const Ballet128256& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    Ballet128256(Ballet128256&& other) noexcept            = default;
    Ballet128256& operator=(Ballet128256&& other) noexcept = default;

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

class Ballet256256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME              = "Ballet-256-256";
    static constexpr std::size_t BLOCK_SIZE        = 32;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_;

public:
    explicit Ballet256256(const char* provider = nullptr)
    {
        const auto* p = get_ballet256256_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("Ballet256256: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    Ballet256256(const Ballet256256& other) : impl_(other.impl_->clone())
    {
    }

    Ballet256256& operator=(const Ballet256256& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    Ballet256256(Ballet256256&& other) noexcept            = default;
    Ballet256256& operator=(Ballet256256&& other) noexcept = default;

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

} // namespace ballet

#endif
