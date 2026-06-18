#ifndef SM4_SM4_H
#define SM4_SM4_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <memory>

namespace sm4 {

/**
 * @brief   SM4 Block Cipher
 * @details GB/T 32907-2016
 */
class SM4 : public block_cipher_mode::BlockCipher
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
    static constexpr const char* NAME = "SM4";

    /// @brief SM4 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 16;

    /// @brief SM4 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = 16;

    /// @brief SM4 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = 64;

    static constexpr std::size_t SECURITY_STRENGTH = 16;

private:
    Cipher impl_ = SM4::create_cipher();

public:
    /**
     * @brief   SM4 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    SM4() noexcept = default;

    /**
     * @brief                   SM4 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         SM4::ENCRYPTION or SM4::DECRYPTION
     */
    SM4(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

    SM4(const SM4& other)
    {
        impl_ = other.impl_->clone();
    }

    SM4& operator=(const SM4& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SM4(SM4&& other) noexcept            = default;
    SM4& operator=(SM4&& other) noexcept = default;

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
        return std::make_unique<SM4>(*this);
    }

public:
    /**
     * @brief                   SM4 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         SM4::ENCRYPTION or SM4::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        impl_->set_key(user_key, enc);
    }

    /**
     * @brief                   SM4 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    /**
     * @brief                   SM4 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        impl_->decrypt_block(plaintext, ciphertext);
    }

    /**
     * @brief                   SM4 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->encrypt_blocks(ciphertext, plaintext, block_num);
    }

    /**
     * @brief                   SM4 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

} // namespace sm4

#endif
