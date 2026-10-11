#if defined(SUPPORT_AES_AESNI)

#include "provider_aes_aesni.h"

#include <gmlib/cpuinfo/cpuinfo.h>

#include "aes_aesni.h"

namespace aes::internal::aesni {
namespace {

bool is_available() noexcept
{
    return cpuinfo::x86_64::cpu_supports_aes() &&
           cpuinfo::x86_64::cpu_supports_sse2();
}

struct Traits128
{
    static constexpr const char* NAME              = "AES128";
    static constexpr const char* ALGO_NAME         = AES_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = AES128_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = AES128_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = AES128_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = AES128_USER_KEY_LEN;

    struct Context
    {
        std::uint8_t round_key[11 * 16];
    };

    static constexpr auto is_available = aesni::is_available;

    static void enc_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        aes128_enc_key_init(ctx->round_key, user_key);
    }

    static void dec_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        aes128_dec_key_init(ctx->round_key, user_key);
    }

    static void encrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        aes128_enc_block(ctx->round_key, out, in);
    }

    static void encrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        aes128_enc_blocks(ctx->round_key, out, in, block_num);
    }

    static void decrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        aes128_dec_block(ctx->round_key, out, in);
    }

    static void decrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        aes128_dec_blocks(ctx->round_key, out, in, block_num);
    }
};

struct Traits192
{
    static constexpr const char* NAME              = "AES192";
    static constexpr const char* ALGO_NAME         = AES_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = AES192_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = AES192_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = AES192_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = AES192_USER_KEY_LEN;

    struct Context
    {
        std::uint8_t round_key[13 * 16];
    };

    static constexpr auto is_available = aesni::is_available;

    static void enc_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        aes192_enc_key_init(ctx->round_key, user_key);
    }

    static void dec_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        aes192_dec_key_init(ctx->round_key, user_key);
    }

    static void encrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        aes192_enc_block(ctx->round_key, out, in);
    }

    static void encrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        aes192_enc_blocks(ctx->round_key, out, in, block_num);
    }

    static void decrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        aes192_dec_block(ctx->round_key, out, in);
    }

    static void decrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        aes192_dec_blocks(ctx->round_key, out, in, block_num);
    }
};

struct Traits256
{
    static constexpr const char* NAME              = "AES256";
    static constexpr const char* ALGO_NAME         = AES_ALGO_NAME;
    static constexpr std::size_t BLOCK_SIZE        = AES256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = AES256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = AES256_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = AES256_USER_KEY_LEN;

    struct Context
    {
        std::uint8_t round_key[15 * 16];
    };

    static constexpr auto is_available = aesni::is_available;

    static void enc_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        aes256_enc_key_init(ctx->round_key, user_key);
    }

    static void dec_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        aes256_dec_key_init(ctx->round_key, user_key);
    }

    static void encrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        aes256_enc_block(ctx->round_key, out, in);
    }

    static void encrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        aes256_enc_blocks(ctx->round_key, out, in, block_num);
    }

    static void decrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        aes256_dec_block(ctx->round_key, out, in);
    }

    static void decrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        aes256_dec_blocks(ctx->round_key, out, in, block_num);
    }
};

} // namespace

const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_128 =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Traits128>::entry;

const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_192 =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Traits192>::entry;

const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_256 =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Traits256>::entry;

} // namespace aes::internal::aesni

#endif
