#include <gmlib/aes/aes.h>

#include "config.h"
#ifdef AES_IMPL_AESNI
#include "aes_aesni.h"
namespace aes {
namespace alg = internal::aesni;
}
#else
#include "aes_lut.h"
namespace aes {
namespace alg = internal::lut;
}
#endif

namespace aes {

const char* AES128::fetch_impl_algo() const noexcept
{
    return alg::AES_ALGO_NAME;
}

void AES128::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::aes128_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::aes128_dec_key_init(rk_data_, user_key);
    }
}

void AES128::encrypt_block(std::uint8_t*       ciphertext,
                           const std::uint8_t* plaintext) const noexcept
{
    alg::aes128_enc_block(rk_data_, ciphertext, plaintext);
}

void AES128::decrypt_block(std::uint8_t*       plaintext,
                           const std::uint8_t* ciphertext) const noexcept
{
    alg::aes128_dec_block(rk_data_, plaintext, ciphertext);
}

void AES128::encrypt_blocks(std::uint8_t*       ciphertext,
                            const std::uint8_t* plaintext,
                            std::size_t         block_num) const noexcept
{
    alg::aes128_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void AES128::decrypt_blocks(std::uint8_t*       plaintext,
                            const std::uint8_t* ciphertext,
                            std::size_t         block_num) const noexcept
{
    alg::aes128_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* AES192::fetch_impl_algo() const noexcept
{
    return alg::AES_ALGO_NAME;
}

void AES192::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::aes192_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::aes192_dec_key_init(rk_data_, user_key);
    }
}

void AES192::encrypt_block(std::uint8_t*       ciphertext,
                           const std::uint8_t* plaintext) const noexcept
{
    alg::aes192_enc_block(rk_data_, ciphertext, plaintext);
}

void AES192::decrypt_block(std::uint8_t*       plaintext,
                           const std::uint8_t* ciphertext) const noexcept
{
    alg::aes192_dec_block(rk_data_, plaintext, ciphertext);
}

void AES192::encrypt_blocks(std::uint8_t*       ciphertext,
                            const std::uint8_t* plaintext,
                            std::size_t         block_num) const noexcept
{
    alg::aes192_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void AES192::decrypt_blocks(std::uint8_t*       plaintext,
                            const std::uint8_t* ciphertext,
                            std::size_t         block_num) const noexcept
{
    alg::aes192_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* AES256::fetch_impl_algo() const noexcept
{
    return alg::AES_ALGO_NAME;
}

void AES256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::aes256_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::aes256_dec_key_init(rk_data_, user_key);
    }
}

void AES256::encrypt_block(std::uint8_t*       ciphertext,
                           const std::uint8_t* plaintext) const noexcept
{
    alg::aes256_enc_block(rk_data_, ciphertext, plaintext);
}

void AES256::decrypt_block(std::uint8_t*       plaintext,
                           const std::uint8_t* ciphertext) const noexcept
{
    alg::aes256_dec_block(rk_data_, plaintext, ciphertext);
}

void AES256::encrypt_blocks(std::uint8_t*       ciphertext,
                            const std::uint8_t* plaintext,
                            std::size_t         block_num) const noexcept
{
    alg::aes256_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void AES256::decrypt_blocks(std::uint8_t*       plaintext,
                            const std::uint8_t* ciphertext,
                            std::size_t         block_num) const noexcept
{
    alg::aes256_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

}; // namespace aes