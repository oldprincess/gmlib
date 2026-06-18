#ifndef BALLET_BALLET_H
#define BALLET_BALLET_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <memory>

namespace ballet {

class Ballet128128 : public block_cipher_mode::BlockCipher
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
    static constexpr const char* NAME              = "Ballet-128-128";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 16;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_ = Ballet128128::create_cipher();

public:
    Ballet128128() noexcept = default;

    Ballet128128(const std::uint8_t* user_key, int enc)
    {
        this->set_key(user_key, enc);
    }

    Ballet128128(const Ballet128128& other)
    {
        impl_ = other.impl_->clone();
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
        return std::make_unique<Ballet128128>(*this);
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

class Ballet128256 : public block_cipher_mode::BlockCipher
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
    static constexpr const char* NAME              = "Ballet-128-256";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_ = Ballet128256::create_cipher();

public:
    Ballet128256() noexcept = default;

    Ballet128256(const std::uint8_t* user_key, int enc)
    {
        this->set_key(user_key, enc);
    }

    Ballet128256(const Ballet128256& other)
    {
        impl_ = other.impl_->clone();
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
        return std::make_unique<Ballet128256>(*this);
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

class Ballet256256 : public block_cipher_mode::BlockCipher
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
    static constexpr const char* NAME              = "Ballet-256-256";
    static constexpr std::size_t BLOCK_SIZE        = 32;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_ = Ballet256256::create_cipher();

public:
    Ballet256256() noexcept = default;

    Ballet256256(const std::uint8_t* user_key, int enc)
    {
        this->set_key(user_key, enc);
    }

    Ballet256256(const Ballet256256& other)
    {
        impl_ = other.impl_->clone();
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
        return std::make_unique<Ballet256256>(*this);
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

} // namespace ballet

#endif
