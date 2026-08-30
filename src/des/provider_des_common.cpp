#include "provider_des_common.h"

#include "des_common.h"

namespace des::internal::common {
namespace {

struct DESContext
{
    std::uint8_t round_key[128];
};

struct Traits
{
    static constexpr const char* NAME      = "DES";
    static constexpr const char* ALGO_NAME = DES_ALGO_NAME;

    static constexpr std::size_t BLOCK_SIZE        = DES_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN      = DES_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM      = DES_PARALLEL_NUM;
    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

    using Context = DESContext;

    static bool is_available() noexcept
    {
        return true;
    }

    static void enc_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        des_enc_key_init(ctx->round_key, user_key);
    }

    static void dec_key_init(Context*            ctx,
                             const std::uint8_t* user_key) noexcept
    {
        des_dec_key_init(ctx->round_key, user_key);
    }

    static void encrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        des_enc_block(ctx->round_key, out, in);
    }

    static void decrypt_block(const Context*      ctx,
                              std::uint8_t*       out,
                              const std::uint8_t* in) noexcept
    {
        des_dec_block(ctx->round_key, out, in);
    }

    static void encrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        des_enc_blocks(ctx->round_key, out, in, block_num);
    }

    static void decrypt_blocks(const Context*      ctx,
                               std::uint8_t*       out,
                               const std::uint8_t* in,
                               std::size_t         block_num) noexcept
    {
        des_dec_blocks(ctx->round_key, out, in, block_num);
    }
};

using ProviderImpl =
    block_cipher_mode::impl::BlockCipherModeProviderImpl<Traits>;

} // namespace

const block_cipher_mode::impl::BlockCipherModeProviderEntry provider =
    ProviderImpl::entry;

} // namespace des::internal::common
