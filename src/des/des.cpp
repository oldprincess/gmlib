#include <gmlib/des/des.h>

#include "des_common.h"

namespace des {
namespace alg = internal::common;
} // namespace des

namespace des {

const char* DES::fetch_impl_algo() const noexcept
{
    return alg::DES_ALGO_NAME;
}

void DES::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::des_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::des_dec_key_init(rk_data_, user_key);
    }
}

void DES::encrypt_block(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext) const noexcept
{
    alg::des_enc_block(rk_data_, ciphertext, plaintext);
}

void DES::decrypt_block(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext) const noexcept
{
    alg::des_dec_block(rk_data_, plaintext, ciphertext);
}

void DES::encrypt_blocks(std::uint8_t*       ciphertext,
                         const std::uint8_t* plaintext,
                         std::size_t         block_num) const noexcept
{
    alg::des_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void DES::decrypt_blocks(std::uint8_t*       plaintext,
                         const std::uint8_t* ciphertext,
                         std::size_t         block_num) const noexcept
{
    alg::des_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

} // namespace des
