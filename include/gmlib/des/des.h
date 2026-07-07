#ifndef DES_DES_H
#define DES_DES_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <memory>

namespace des {

/**
 * @brief   DES Block Cipher
 * @details GB/T 32907-2016
 */
class DES : public block_cipher_mode::BlockCipher
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
    static constexpr const char* NAME = "DES";

    static constexpr std::size_t BLOCK_SIZE        = 8;
    static constexpr std::size_t USER_KEY_LEN      = 8;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_ = DES::create_cipher();

public:
    DES() noexcept = default;

    DES(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

    DES(const DES& other)
    {
        impl_ = other.impl_->clone();
    }

    DES& operator=(const DES& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    DES(DES&& other) noexcept            = default;
    DES& operator=(DES&& other) noexcept = default;

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

} // namespace des

#endif
