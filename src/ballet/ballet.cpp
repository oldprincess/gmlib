#include <gmlib/ballet/ballet.h>

#include "ballet_standard.h"

namespace ballet {
namespace alg = internal::standard;
} // namespace ballet

namespace ballet {

const char* Ballet128128::fetch_impl_algo() const noexcept
{
    return alg::BALLET_ALGO_NAME;
}

void Ballet128128::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::ballet128128_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::ballet128128_dec_key_init(rk_data_, user_key);
    }
}

void Ballet128128::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    alg::ballet128128_enc_block(rk_data_, ciphertext, plaintext);
}

void Ballet128128::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    alg::ballet128128_dec_block(rk_data_, plaintext, ciphertext);
}

void Ballet128128::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    alg::ballet128128_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void Ballet128128::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    alg::ballet128128_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* Ballet128256::fetch_impl_algo() const noexcept
{
    return alg::BALLET_ALGO_NAME;
}

void Ballet128256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::ballet128256_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::ballet128256_dec_key_init(rk_data_, user_key);
    }
}

void Ballet128256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    alg::ballet128256_enc_block(rk_data_, ciphertext, plaintext);
}

void Ballet128256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    alg::ballet128256_dec_block(rk_data_, plaintext, ciphertext);
}

void Ballet128256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    alg::ballet128256_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void Ballet128256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    alg::ballet128256_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* Ballet256256::fetch_impl_algo() const noexcept
{
    return alg::BALLET_ALGO_NAME;
}

void Ballet256256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::ballet256256_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::ballet256256_dec_key_init(rk_data_, user_key);
    }
}

void Ballet256256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    alg::ballet256256_enc_block(rk_data_, ciphertext, plaintext);
}

void Ballet256256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    alg::ballet256256_dec_block(rk_data_, plaintext, ciphertext);
}

void Ballet256256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    alg::ballet256256_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void Ballet256256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    alg::ballet256256_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

}; // namespace ballet