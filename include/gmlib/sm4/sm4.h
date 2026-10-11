#ifndef SM4_SM4_H
#define SM4_SM4_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/sm4/provider.h>

#include <memory>
#include <stdexcept>

namespace sm4 {

/**
 * @brief   SM4 Block Cipher
 * @details GB/T 32907-2016
 */
class SM4 : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

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
    Cipher impl_;

public:
    /**
     * @brief   SM4 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    explicit SM4(const char* provider = nullptr)
    {
        const auto* p = get_sm4_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("SM4: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    SM4(const SM4& other) : impl_(other.impl_->clone())
    {
    }

    SM4& operator=(const SM4& other)
    {
        if (this != &other)
        {
            impl_ = other.impl_->clone();
        }
        return *this;
    }

    SM4(SM4&& other) noexcept = default;

    SM4& operator=(SM4&& other) noexcept = default;

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
    /**
     * @brief                   SM4 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         SM4::ENCRYPTION or SM4::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) override
    {
        impl_->set_key(user_key, enc);
    }

    /**
     * @brief                   SM4 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const override
    {
        impl_->encrypt_block(ciphertext, plaintext);
    }

    /**
     * @brief                   SM4 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const override
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
                        std::size_t         block_num) const override
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
                        std::size_t         block_num) const override
    {
        impl_->decrypt_blocks(plaintext, ciphertext, block_num);
    }
};

} // namespace sm4

#endif
