#include "provider_ballet_standard.h"

#include "ballet_standard.h"

namespace ballet::internal::standard {
namespace {

struct Ballet128128Traits
{
    static constexpr const char* NAME              = "Ballet-128-128";
    static constexpr const char* ALGO_NAME         = BALLET_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = BALLET128128_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = BALLET128128_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = BALLET128128_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;
    using Context                                  = Ballet128128RoundKey;

    static bool is_available() noexcept
    {
        return true;
    }

    static constexpr auto enc_key_init   = ballet128128_enc_key_init;
    static constexpr auto dec_key_init   = ballet128128_dec_key_init;
    static constexpr auto encrypt_block  = ballet128128_enc_block;
    static constexpr auto decrypt_block  = ballet128128_dec_block;
    static constexpr auto encrypt_blocks = ballet128128_enc_blocks;
    static constexpr auto decrypt_blocks = ballet128128_dec_blocks;
};

struct Ballet128256Traits
{
    static constexpr const char* NAME              = "Ballet-128-256";
    static constexpr const char* ALGO_NAME         = BALLET_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = BALLET128256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = BALLET128256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = BALLET128256_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;
    using Context                                  = Ballet128256RoundKey;

    static bool is_available() noexcept
    {
        return true;
    }

    static constexpr auto enc_key_init   = ballet128256_enc_key_init;
    static constexpr auto dec_key_init   = ballet128256_dec_key_init;
    static constexpr auto encrypt_block  = ballet128256_enc_block;
    static constexpr auto decrypt_block  = ballet128256_dec_block;
    static constexpr auto encrypt_blocks = ballet128256_enc_blocks;
    static constexpr auto decrypt_blocks = ballet128256_dec_blocks;
};

struct Ballet256256Traits
{
    static constexpr const char* NAME              = "Ballet-256-256";
    static constexpr const char* ALGO_NAME         = BALLET_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = BALLET256256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = BALLET256256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = BALLET256256_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;
    using Context                                  = Ballet256256RoundKey;

    static bool is_available() noexcept
    {
        return true;
    }

    static constexpr auto enc_key_init   = ballet256256_enc_key_init;
    static constexpr auto dec_key_init   = ballet256256_dec_key_init;
    static constexpr auto encrypt_block  = ballet256256_enc_block;
    static constexpr auto decrypt_block  = ballet256256_dec_block;
    static constexpr auto encrypt_blocks = ballet256256_enc_blocks;
    static constexpr auto decrypt_blocks = ballet256256_dec_blocks;
};

using Ballet128128ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Ballet128128Traits>;
using Ballet128256ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Ballet128256Traits>;
using Ballet256256ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Ballet256256Traits>;

} // namespace

const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_128128 =
    Ballet128128ProviderImpl::entry;
const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_128256 =
    Ballet128256ProviderImpl::entry;
const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_256256 =
    Ballet256256ProviderImpl::entry;

} // namespace ballet::internal::standard
