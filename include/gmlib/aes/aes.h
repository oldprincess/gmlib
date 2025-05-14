#ifndef AES_AES_H
#define AES_AES_H

#include <gmlib/block_cipher_mode/block_cipher.h>

namespace aes {

class AES128 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME              = "AES128";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 16;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 16;

private:
    std::uint8_t rk_data_[11 * 16];

public:
    AES128() = default;

    AES128(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    const char* fetch_impl_algo() const noexcept;

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return SECURITY_STRENGTH;
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override;

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override;

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override;

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override;
};

class AES192 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME              = "AES192";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 24;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 24;

private:
    std::uint8_t rk_data_[13 * 16];

public:
    AES192() = default;

    AES192(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    const char* fetch_impl_algo() const noexcept;

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return SECURITY_STRENGTH;
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override;

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override;

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override;

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override;
};

class AES256 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME              = "AES256";
    static constexpr std::size_t BLOCK_SIZE        = 16;
    static constexpr std::size_t USER_KEY_LEN      = 32;
    static constexpr std::size_t PARALLEL_NUM      = 1;
    static constexpr std::size_t SECURITY_STRENGTH = 32;

private:
    std::uint8_t rk_data_[15 * 16];

public:
    AES256() = default;

    AES256(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    const char* fetch_impl_algo() const noexcept;

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return SECURITY_STRENGTH;
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override;

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override;
    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override;

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override;
};

} // namespace aes

#endif