#ifndef AES_AES_H
#define AES_AES_H

#include <gmlib/aes/internal/aes_aesni.h>
#include <gmlib/aes/internal/aes_lut.h>
#include <gmlib/block_cipher_mode/block_cipher.h>

namespace aes {

#if defined(CPU_FLAG_AES) && defined(CPU_FLAG_SSE2)
namespace alg = internal::aesni;
#else
namespace alg = internal::lut;
#endif

class AES128 : public block_cipher_mode::BlockCipherImpl
{
public:
    static constexpr const char* NAME              = "AES128";
    static constexpr std::size_t NAME_STR_LEN      = 6;
    static constexpr std::size_t BLOCK_SIZE        = alg::AES128_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = alg::AES128_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = alg::AES128_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    alg::Aes128CTX ctx_;

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

    std::size_t fetch_name_str_len() const noexcept override
    {
        return NAME_STR_LEN;
    }

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
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == AES128::ENCRYPTION)
        {
            alg::aes128_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::aes128_dec_key_init(&ctx_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        alg::aes128_enc_block(&ctx_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        alg::aes128_dec_block(&ctx_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        alg::aes128_enc_blocks(&ctx_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        alg::aes128_dec_blocks(&ctx_, out, in, block_num);
    }
};

class AES192 : public block_cipher_mode::BlockCipherImpl
{
public:
    static constexpr const char* NAME              = "AES192";
    static constexpr std::size_t NAME_STR_LEN      = 6;
    static constexpr std::size_t BLOCK_SIZE        = alg::AES192_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = alg::AES192_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = alg::AES192_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    alg::Aes192CTX ctx_;

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

    std::size_t fetch_name_str_len() const noexcept override
    {
        return NAME_STR_LEN;
    }

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
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == AES192::ENCRYPTION)
        {
            alg::aes192_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::aes192_dec_key_init(&ctx_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        alg::aes192_enc_block(&ctx_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        alg::aes192_dec_block(&ctx_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        alg::aes192_enc_blocks(&ctx_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        alg::aes192_dec_blocks(&ctx_, out, in, block_num);
    }
};

class AES256 : public block_cipher_mode::BlockCipherImpl
{
public:
    static constexpr const char* NAME              = "AES256";
    static constexpr std::size_t NAME_STR_LEN      = 6;
    static constexpr std::size_t BLOCK_SIZE        = alg::AES256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = alg::AES256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = alg::AES256_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    alg::Aes256CTX ctx_;

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

    std::size_t fetch_name_str_len() const noexcept override
    {
        return NAME_STR_LEN;
    }

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
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == AES256::ENCRYPTION)
        {
            alg::aes256_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::aes256_dec_key_init(&ctx_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        alg::aes256_enc_block(&ctx_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        alg::aes256_dec_block(&ctx_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        alg::aes256_enc_blocks(&ctx_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        alg::aes256_dec_blocks(&ctx_, out, in, block_num);
    }
};

} // namespace aes

#endif