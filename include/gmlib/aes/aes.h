#ifndef AES_AES_H
#define AES_AES_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <memory>

namespace aes {

class AES128 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;
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
    static constexpr const char* NAME              = "AES128";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 16;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 16;

private:
    Cipher impl_ = AES128::create_cipher();

public:
    AES128() noexcept = default;

    AES128(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

    AES128(const AES128& other)
    {
        impl_ = other.impl_->clone();
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

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        impl_->encrypt_block(out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        impl_->decrypt_block(out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        impl_->encrypt_blocks(out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        impl_->decrypt_blocks(out, in, block_num);
    }
};

class AES192 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;
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
    static constexpr const char* NAME              = "AES192";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 24;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 24;

private:
    Cipher impl_ = AES192::create_cipher();

public:
    AES192() noexcept = default;

    AES192(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

    AES192(const AES192& other)
    {
        impl_ = other.impl_->clone();
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

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        impl_->encrypt_block(out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        impl_->decrypt_block(out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        impl_->encrypt_blocks(out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        impl_->decrypt_blocks(out, in, block_num);
    }
};

class AES256 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;
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
    static constexpr const char* NAME              = "AES256";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 32;

private:
    Cipher impl_ = AES256::create_cipher();

public:
    AES256() noexcept = default;

    AES256(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

    AES256(const AES256& other)
    {
        impl_ = other.impl_->clone();
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

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        impl_->encrypt_block(out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        impl_->decrypt_block(out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        impl_->encrypt_blocks(out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        impl_->decrypt_blocks(out, in, block_num);
    }
};

} // namespace aes

#endif
