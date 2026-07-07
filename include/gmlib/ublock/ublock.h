#ifndef UBLOCK_UBLOCK_H
#define UBLOCK_UBLOCK_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <memory>

namespace ublock {

class uBlock128128 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher     = std::unique_ptr<block_cipher_mode::BlockCipher>;
    using CipherMode = std::unique_ptr<block_cipher_mode::BlockCipherMode>;

public:
    static Cipher create_cipher(const char* provider = nullptr);

    static CipherMode create_ecb_encryptor(const char* provider = nullptr);
    static CipherMode create_ecb_decryptor(const char* provider = nullptr);

    static CipherMode create_cbc_encryptor(const char* provider = nullptr);
    static CipherMode create_cbc_decryptor(const char* provider = nullptr);

    static CipherMode create_ofb_encryptor(const char* provider = nullptr);
    static CipherMode create_ofb_decryptor(const char* provider = nullptr);

    static CipherMode create_cfb_encryptor(const char* provider = nullptr);
    static CipherMode create_cfb_decryptor(const char* provider = nullptr);

    static CipherMode create_ctr_encryptor(const char* provider = nullptr);
    static CipherMode create_ctr_decryptor(const char* provider = nullptr);

    static CipherMode create_gcm_encryptor(const char* provider = nullptr);
    static CipherMode create_gcm_decryptor(const char* provider = nullptr);

public:
    static constexpr const char* NAME              = "uBlock-128-128";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 16;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_ = uBlock128128::create_cipher();

public:
    uBlock128128() noexcept = default;

    uBlock128128(const std::uint8_t* user_key, int enc)
    {
        this->set_key(user_key, enc);
    }

    uBlock128128(const uBlock128128& other)
    {
        impl_ = other.impl_->clone();
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
    const char* fetch_name() const noexcept override
    {
        return impl_->fetch_name();
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return impl_->fetch_impl_algo();
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return impl_->fetch_block_size();
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return impl_->fetch_user_key_len();
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return impl_->fetch_parallel_num();
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return impl_->fetch_security_strength();
    }

    Cipher clone() const override
    {
        return impl_->clone();
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        impl_->set_key(user_key, enc);
    }

    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        impl_->decrypt_block(plaintext, ciphertext);
    }

    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->encrypt_blocks(ciphertext, plaintext, block_num);
    }

    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

class uBlock128256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher     = std::unique_ptr<block_cipher_mode::BlockCipher>;
    using CipherMode = std::unique_ptr<block_cipher_mode::BlockCipherMode>;

public:
    static Cipher create_cipher(const char* provider = nullptr);

    static CipherMode create_ecb_encryptor(const char* provider = nullptr);
    static CipherMode create_ecb_decryptor(const char* provider = nullptr);

    static CipherMode create_cbc_encryptor(const char* provider = nullptr);
    static CipherMode create_cbc_decryptor(const char* provider = nullptr);

    static CipherMode create_ofb_encryptor(const char* provider = nullptr);
    static CipherMode create_ofb_decryptor(const char* provider = nullptr);

    static CipherMode create_cfb_encryptor(const char* provider = nullptr);
    static CipherMode create_cfb_decryptor(const char* provider = nullptr);

    static CipherMode create_ctr_encryptor(const char* provider = nullptr);
    static CipherMode create_ctr_decryptor(const char* provider = nullptr);

    static CipherMode create_gcm_encryptor(const char* provider = nullptr);
    static CipherMode create_gcm_decryptor(const char* provider = nullptr);

public:
    static constexpr const char* NAME              = "uBlock-128-256";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_ = uBlock128256::create_cipher();

public:
    uBlock128256() noexcept = default;

    uBlock128256(const std::uint8_t* user_key, int enc)
    {
        this->set_key(user_key, enc);
    }

    uBlock128256(const uBlock128256& other)
    {
        impl_ = other.impl_->clone();
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
    const char* fetch_name() const noexcept override
    {
        return impl_->fetch_name();
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return impl_->fetch_impl_algo();
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return impl_->fetch_block_size();
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return impl_->fetch_user_key_len();
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return impl_->fetch_parallel_num();
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return impl_->fetch_security_strength();
    }

    Cipher clone() const override
    {
        return impl_->clone();
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        impl_->set_key(user_key, enc);
    }

    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        impl_->decrypt_block(plaintext, ciphertext);
    }

    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->encrypt_blocks(ciphertext, plaintext, block_num);
    }

    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

class uBlock256256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher     = std::unique_ptr<block_cipher_mode::BlockCipher>;
    using CipherMode = std::unique_ptr<block_cipher_mode::BlockCipherMode>;

public:
    static Cipher create_cipher(const char* provider = nullptr);

    static CipherMode create_ecb_encryptor(const char* provider = nullptr);
    static CipherMode create_ecb_decryptor(const char* provider = nullptr);

    static CipherMode create_cbc_encryptor(const char* provider = nullptr);
    static CipherMode create_cbc_decryptor(const char* provider = nullptr);

    static CipherMode create_ofb_encryptor(const char* provider = nullptr);
    static CipherMode create_ofb_decryptor(const char* provider = nullptr);

    static CipherMode create_cfb_encryptor(const char* provider = nullptr);
    static CipherMode create_cfb_decryptor(const char* provider = nullptr);

    static CipherMode create_ctr_encryptor(const char* provider = nullptr);
    static CipherMode create_ctr_decryptor(const char* provider = nullptr);

public:
    static constexpr const char* NAME              = "uBlock-256-256";
    static constexpr std::size_t BLOCK_SIZE        = 32;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_ = uBlock256256::create_cipher();

public:
    uBlock256256() noexcept = default;

    uBlock256256(const std::uint8_t* user_key, int enc)
    {
        this->set_key(user_key, enc);
    }

    uBlock256256(const uBlock256256& other)
    {
        impl_ = other.impl_->clone();
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
    const char* fetch_name() const noexcept override
    {
        return impl_->fetch_name();
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return impl_->fetch_impl_algo();
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return impl_->fetch_block_size();
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return impl_->fetch_user_key_len();
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return impl_->fetch_parallel_num();
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return impl_->fetch_security_strength();
    }

    Cipher clone() const override
    {
        return impl_->clone();
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        impl_->set_key(user_key, enc);
    }

    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        impl_->decrypt_block(plaintext, ciphertext);
    }

    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->encrypt_blocks(ciphertext, plaintext, block_num);
    }

    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

} // namespace ublock

#endif
