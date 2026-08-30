#if defined(SUPPORT_UBLOCK_STANDARD)

#include "provider_ublock_standard.h"

#include <gmlib/cpuinfo/cpuinfo.h>

#include "ublock_standard.h"

namespace ublock::internal::standard {
namespace {

struct UBlock128128Traits
{
    static constexpr const char* NAME              = "uBlock-128-128";
    static constexpr const char* ALGO_NAME         = UBLOCK_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = UBLOCK128128_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = UBLOCK128128_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = UBLOCK128128_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;
    using Context                                  = UBlock128128RoundKey;

    static bool is_available() noexcept
    {
        return cpuinfo::x86_64::cpu_supports_ssse3();
    }

    static constexpr auto enc_key_init   = ublock128128_enc_key_init;
    static constexpr auto dec_key_init   = ublock128128_dec_key_init;
    static constexpr auto encrypt_block  = ublock128128_enc_block;
    static constexpr auto decrypt_block  = ublock128128_dec_block;
    static constexpr auto encrypt_blocks = ublock128128_enc_blocks;
    static constexpr auto decrypt_blocks = ublock128128_dec_blocks;
};

struct UBlock128256Traits
{
    static constexpr const char* NAME              = "uBlock-128-256";
    static constexpr const char* ALGO_NAME         = UBLOCK_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = UBLOCK128256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = UBLOCK128256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = UBLOCK128256_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;
    using Context                                  = UBlock128256RoundKey;

    static bool is_available() noexcept
    {
        return cpuinfo::x86_64::cpu_supports_ssse3();
    }

    static constexpr auto enc_key_init   = ublock128256_enc_key_init;
    static constexpr auto dec_key_init   = ublock128256_dec_key_init;
    static constexpr auto encrypt_block  = ublock128256_enc_block;
    static constexpr auto decrypt_block  = ublock128256_dec_block;
    static constexpr auto encrypt_blocks = ublock128256_enc_blocks;
    static constexpr auto decrypt_blocks = ublock128256_dec_blocks;
};

struct UBlock256256Traits
{
    static constexpr const char* NAME              = "uBlock-256-256";
    static constexpr const char* ALGO_NAME         = UBLOCK_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = UBLOCK256256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = UBLOCK256256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = UBLOCK256256_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;
    using Context                                  = UBlock256256RoundKey;

    static bool is_available() noexcept
    {
        return cpuinfo::x86_64::cpu_supports_ssse3();
    }

    static constexpr auto enc_key_init   = ublock256256_enc_key_init;
    static constexpr auto dec_key_init   = ublock256256_dec_key_init;
    static constexpr auto encrypt_block  = ublock256256_enc_block;
    static constexpr auto decrypt_block  = ublock256256_dec_block;
    static constexpr auto encrypt_blocks = ublock256256_enc_blocks;
    static constexpr auto decrypt_blocks = ublock256256_dec_blocks;
};

using UBlock128128ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<UBlock128128Traits>;
using UBlock128256ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<UBlock128256Traits>;
using UBlock256256ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<UBlock256256Traits>;

} // namespace

const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_128128 =
    UBlock128128ProviderImpl::entry;
const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_128256 =
    UBlock128256ProviderImpl::entry;
const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_256256 =
    UBlock256256ProviderImpl::entry;

} // namespace ublock::internal::standard

#endif
