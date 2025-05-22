#include <gmlib/ublock/ublock.h>

#include "config.h"
#if defined(UBLOCK_IMPL_STANDARD)
#include "ublock_standard.h"
namespace ublock {
namespace alg = internal::standard;
}
#else
#include "ublock_common.h"
namespace ublock {
namespace alg = internal::common;
}
#endif

namespace ublock {

const char* uBlock128128::fetch_impl_algo() const noexcept
{
    return alg::UBLOCK_ALGO_NAME;
}

void uBlock128128::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::ublock128128_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::ublock128128_dec_key_init(rk_data_, user_key);
    }
}

void uBlock128128::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    alg::ublock128128_enc_block(rk_data_, ciphertext, plaintext);
}

void uBlock128128::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    alg::ublock128128_dec_block(rk_data_, plaintext, ciphertext);
}

void uBlock128128::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    alg::ublock128128_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void uBlock128128::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    alg::ublock128128_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* uBlock128256::fetch_impl_algo() const noexcept
{
    return alg::UBLOCK_ALGO_NAME;
}

void uBlock128256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::ublock128256_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::ublock128256_dec_key_init(rk_data_, user_key);
    }
}

void uBlock128256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    alg::ublock128256_enc_block(rk_data_, ciphertext, plaintext);
}

void uBlock128256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    alg::ublock128256_dec_block(rk_data_, plaintext, ciphertext);
}

void uBlock128256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    alg::ublock128256_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void uBlock128256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    alg::ublock128256_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* uBlock256256::fetch_impl_algo() const noexcept
{
    return alg::UBLOCK_ALGO_NAME;
}

void uBlock256256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::ublock256256_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::ublock256256_dec_key_init(rk_data_, user_key);
    }
}

void uBlock256256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    alg::ublock256256_enc_block(rk_data_, ciphertext, plaintext);
}

void uBlock256256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    alg::ublock256256_dec_block(rk_data_, plaintext, ciphertext);
}

void uBlock256256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    alg::ublock256256_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void uBlock256256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    alg::ublock256256_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

} // namespace ublock