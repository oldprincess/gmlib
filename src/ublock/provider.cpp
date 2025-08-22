#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/ublock/ublock.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "config.h"
#include "ublock_common.h"
#include "ublock_standard.h"

namespace ublock {

struct uBlockProvider
{
    bool (*available)();

    const char* algo_name;

    void (*enc_key_init)(std::uint8_t* round_key, const std::uint8_t* user_key);

    void (*dec_key_init)(std::uint8_t* round_key, const std::uint8_t* user_key);

    void (*enc_block)(const std::uint8_t* round_key,
                      std::uint8_t*       ciphertext,
                      const std::uint8_t* plaintext);

    void (*dec_block)(const std::uint8_t* round_key,
                      std::uint8_t*       plaintext,
                      const std::uint8_t* ciphertext);

    void (*enc_blocks)(const std::uint8_t* round_key,
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num);

    void (*dec_blocks)(const std::uint8_t* round_key,
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num);
};

static uBlockProvider ublock128128_providers[] = {

#if defined(UBLOCK_IMPL_STANDARD)
    {
        []() { return cpuinfo::x86_64::cpu_supports_ssse3(); },
        ublock::internal::standard::UBLOCK_ALGO_NAME,
        ublock::internal::standard::ublock128128_enc_key_init,
        ublock::internal::standard::ublock128128_dec_key_init,
        ublock::internal::standard::ublock128128_enc_block,
        ublock::internal::standard::ublock128128_dec_block,
        ublock::internal::standard::ublock128128_enc_blocks,
        ublock::internal::standard::ublock128128_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        ublock::internal::common::UBLOCK_ALGO_NAME,
        ublock::internal::common::ublock128128_enc_key_init,
        ublock::internal::common::ublock128128_dec_key_init,
        ublock::internal::common::ublock128128_enc_block,
        ublock::internal::common::ublock128128_dec_block,
        ublock::internal::common::ublock128128_enc_blocks,
        ublock::internal::common::ublock128128_dec_blocks,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static uBlockProvider ublock128256_providers[] = {

#if defined(UBLOCK_IMPL_STANDARD)
    {
        []() { return cpuinfo::x86_64::cpu_supports_ssse3(); },
        ublock::internal::standard::UBLOCK_ALGO_NAME,
        ublock::internal::standard::ublock128256_enc_key_init,
        ublock::internal::standard::ublock128256_dec_key_init,
        ublock::internal::standard::ublock128256_enc_block,
        ublock::internal::standard::ublock128256_dec_block,
        ublock::internal::standard::ublock128256_enc_blocks,
        ublock::internal::standard::ublock128256_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        ublock::internal::common::UBLOCK_ALGO_NAME,
        ublock::internal::common::ublock128256_enc_key_init,
        ublock::internal::common::ublock128256_dec_key_init,
        ublock::internal::common::ublock128256_enc_block,
        ublock::internal::common::ublock128256_dec_block,
        ublock::internal::common::ublock128256_enc_blocks,
        ublock::internal::common::ublock128256_dec_blocks,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static uBlockProvider ublock256256_providers[] = {

#if defined(UBLOCK_IMPL_STANDARD)
    {
        []() { return cpuinfo::x86_64::cpu_supports_ssse3(); },
        ublock::internal::standard::UBLOCK_ALGO_NAME,
        ublock::internal::standard::ublock256256_enc_key_init,
        ublock::internal::standard::ublock256256_dec_key_init,
        ublock::internal::standard::ublock256256_enc_block,
        ublock::internal::standard::ublock256256_dec_block,
        ublock::internal::standard::ublock256256_enc_blocks,
        ublock::internal::standard::ublock256256_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        ublock::internal::common::UBLOCK_ALGO_NAME,
        ublock::internal::common::ublock256256_enc_key_init,
        ublock::internal::common::ublock256256_dec_key_init,
        ublock::internal::common::ublock256256_enc_block,
        ublock::internal::common::ublock256256_dec_block,
        ublock::internal::common::ublock256256_enc_blocks,
        ublock::internal::common::ublock256256_dec_blocks,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static const uBlockProvider* get_provider(const uBlockProvider* providers,
                                          const char* name = nullptr) noexcept
{
    std::size_t idx = 0;
    while (providers[idx].algo_name != nullptr)
    {
        if (providers[idx].available())
        {
            if (name == nullptr)
            {
                return &providers[idx];
            }

            if (std::strcmp(providers[idx].algo_name, name) == 0)
            {
                return &providers[idx];
            }
        }
        idx += 1;
    }
    std::printf("[uBlock PROVIDER] Provider %s is not available. %s:%d\n", name,
                __FILE__, __LINE__);
    std::exit(-1);
}

#define UBLOCK128128_PROVIDER get_provider(ublock128128_providers)
#define UBLOCK128256_PROVIDER get_provider(ublock128256_providers)
#define UBLOCK256256_PROVIDER get_provider(ublock256256_providers)

const char* uBlock128128::fetch_impl_algo() const noexcept
{
    return UBLOCK128128_PROVIDER->algo_name;
}

void uBlock128128::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        UBLOCK128128_PROVIDER->enc_key_init(rk_data_, user_key);
    }
    else
    {
        UBLOCK128128_PROVIDER->dec_key_init(rk_data_, user_key);
    }
}

void uBlock128128::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    UBLOCK128128_PROVIDER->enc_block(rk_data_, ciphertext, plaintext);
}

void uBlock128128::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    UBLOCK128128_PROVIDER->dec_block(rk_data_, plaintext, ciphertext);
}

void uBlock128128::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128128_PROVIDER->enc_blocks(rk_data_, ciphertext, plaintext,
                                      block_num);
}

void uBlock128128::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128128_PROVIDER->dec_blocks(rk_data_, plaintext, ciphertext,
                                      block_num);
}

const char* uBlock128256::fetch_impl_algo() const noexcept
{
    return UBLOCK128256_PROVIDER->algo_name;
}

void uBlock128256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        UBLOCK128256_PROVIDER->enc_key_init(rk_data_, user_key);
    }
    else
    {
        UBLOCK128256_PROVIDER->dec_key_init(rk_data_, user_key);
    }
}

void uBlock128256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    UBLOCK128256_PROVIDER->enc_block(rk_data_, ciphertext, plaintext);
}

void uBlock128256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    UBLOCK128256_PROVIDER->dec_block(rk_data_, plaintext, ciphertext);
}

void uBlock128256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128256_PROVIDER->enc_blocks(rk_data_, ciphertext, plaintext,
                                      block_num);
}

void uBlock128256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128256_PROVIDER->dec_blocks(rk_data_, plaintext, ciphertext,
                                      block_num);
}

const char* uBlock256256::fetch_impl_algo() const noexcept
{
    return UBLOCK256256_PROVIDER->algo_name;
}

void uBlock256256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        UBLOCK256256_PROVIDER->enc_key_init(rk_data_, user_key);
    }
    else
    {
        UBLOCK256256_PROVIDER->dec_key_init(rk_data_, user_key);
    }
}

void uBlock256256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    UBLOCK256256_PROVIDER->enc_block(rk_data_, ciphertext, plaintext);
}

void uBlock256256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    UBLOCK256256_PROVIDER->dec_block(rk_data_, plaintext, ciphertext);
}

void uBlock256256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK256256_PROVIDER->enc_blocks(rk_data_, ciphertext, plaintext,
                                      block_num);
}

void uBlock256256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK256256_PROVIDER->dec_blocks(rk_data_, plaintext, ciphertext,
                                      block_num);
}

} // namespace ublock