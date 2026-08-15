#if defined(SUPPORT_SM4_LANG18)

#include "provider_sm4_lang18.h"

#include "sm4_lang18.h"

namespace sm4::internal::lang18 {
namespace {

struct Traits
{
    static constexpr const char* NAME      = "SM4";
    static constexpr const char* ALGO_NAME = SM4_ALGO_NAME;

    static constexpr std::size_t BLOCK_SIZE        = SM4_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = SM4_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = SM4_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = SM4_USER_KEY_LEN;

    using Context = SM4Context;

    static bool is_available() noexcept
    {
        return true;
    }

    static constexpr auto enc_key_init   = sm4_enc_key_init;
    static constexpr auto dec_key_init   = sm4_dec_key_init;
    static constexpr auto encrypt_block  = sm4_enc_block;
    static constexpr auto decrypt_block  = sm4_dec_block;
    static constexpr auto encrypt_blocks = sm4_enc_blocks;
    static constexpr auto decrypt_blocks = sm4_dec_blocks;
};

using ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Traits>;

} // namespace

const block_cipher_mode::impl::BlockCipherModeProviderEntry provider =
    ProviderImpl::entry;

} // namespace sm4::internal::lang18

#endif
