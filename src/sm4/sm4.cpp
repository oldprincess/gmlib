#include <gmlib/sm4/sm4.h>

#include "config.h"
#ifdef SM4_IMPL_LANG18
#include "sm4_lang18.h"
namespace sm4 {
namespace alg = internal::lang18;
}
#else
#include "sm4_common.h"
namespace sm4 {
namespace alg = internal::common;
}
#endif

namespace sm4 {

const char* SM4::fetch_impl_algo() const noexcept
{
    return alg::SM4_ALGO_NAME;
}

void SM4::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        alg::sm4_enc_key_init(rk_data_, user_key);
    }
    else
    {
        alg::sm4_dec_key_init(rk_data_, user_key);
    }
}

void SM4::encrypt_block(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext) const noexcept
{
    alg::sm4_enc_block(rk_data_, ciphertext, plaintext);
}

void SM4::decrypt_block(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext) const noexcept
{
    alg::sm4_dec_block(rk_data_, plaintext, ciphertext);
}

void SM4::encrypt_blocks(std::uint8_t*       ciphertext,
                         const std::uint8_t* plaintext,
                         std::size_t         block_num) const noexcept
{
    alg::sm4_enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void SM4::decrypt_blocks(std::uint8_t*       plaintext,
                         const std::uint8_t* ciphertext,
                         std::size_t         block_num) const noexcept
{
    alg::sm4_dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

}; // namespace sm4