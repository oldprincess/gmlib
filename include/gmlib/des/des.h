#ifndef DES_DES_H
#define DES_DES_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/des/provider.h>

#include <memory>
#include <stdexcept>

namespace des {

/**
 * @brief   DES Block Cipher
 * @details GB/T 32907-2016
 */
class DES : public block_cipher_mode::BlockCipher
{
public:
    using Cipher = std::unique_ptr<block_cipher_mode::BlockCipher>;

public:
    static constexpr const char* NAME = "DES";

    static constexpr std::size_t BLOCK_SIZE        = 8;
    static constexpr std::size_t USER_KEY_LEN      = 8;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    Cipher impl_;

public:
    explicit DES(const char* provider = nullptr)
    {
        const auto* p = get_des_provider(provider);
        if (p == nullptr || p->create_cipher == nullptr)
        {
            throw std::runtime_error("DES: cipher not available");
        }
        impl_ = p->create_cipher();
    }

    DES(const DES& other) : impl_(other.impl_->clone())
    {
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

} // namespace des

#endif
