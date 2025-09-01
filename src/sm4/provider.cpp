#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/sm4/sm4.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "config.h"
#include "sm4_common.h"
#include "sm4_gong23.h"
#include "sm4_lang18.h"

namespace sm4 {

struct SM4Provider
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

static SM4Provider sm4_providers[] = {

#if defined(SM4_IMPL_GONG23)
    {
        []() {
            static bool available = cpuinfo::x86_64::cpu_supports_avx512bw() &&
                                    cpuinfo::x86_64::cpu_supports_avx512f() &&
                                    cpuinfo::x86_64::cpu_supports_avx512vl() &&
                                    cpuinfo::x86_64::cpu_supports_gfni();
            return available;
        },
        sm4::internal::gong23::SM4_ALGO_NAME,
        sm4::internal::gong23::sm4_enc_key_init,
        sm4::internal::gong23::sm4_dec_key_init,
        sm4::internal::gong23::sm4_enc_block,
        sm4::internal::gong23::sm4_dec_block,
        sm4::internal::gong23::sm4_enc_blocks,
        sm4::internal::gong23::sm4_dec_blocks,
    },
#endif

#if defined(SM4_IMPL_LANG18)
    {
        []() { return true; },
        sm4::internal::lang18::SM4_ALGO_NAME,
        sm4::internal::lang18::sm4_enc_key_init,
        sm4::internal::lang18::sm4_dec_key_init,
        sm4::internal::lang18::sm4_enc_block,
        sm4::internal::lang18::sm4_dec_block,
        sm4::internal::lang18::sm4_enc_blocks,
        sm4::internal::lang18::sm4_dec_blocks,
    },
#endif

    // universal
    {
        []() { return true; },
        sm4::internal::common::SM4_ALGO_NAME,
        sm4::internal::common::sm4_enc_key_init,
        sm4::internal::common::sm4_dec_key_init,
        sm4::internal::common::sm4_enc_block,
        sm4::internal::common::sm4_dec_block,
        sm4::internal::common::sm4_enc_blocks,
        sm4::internal::common::sm4_dec_blocks,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static const SM4Provider* get_provider(const SM4Provider* providers,
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
    std::printf("[SM4 PROVIDER] Provider %s is not available. %s:%d\n", name,
                __FILE__, __LINE__);
    std::exit(-1);
}

#define SM4_PROVIDER get_provider(sm4_providers)

const char* SM4::fetch_impl_algo() const noexcept
{
    return SM4_PROVIDER->algo_name;
}

void SM4::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        SM4_PROVIDER->enc_key_init(rk_data_, user_key);
    }
    else
    {
        SM4_PROVIDER->dec_key_init(rk_data_, user_key);
    }
}

void SM4::encrypt_block(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext) const noexcept
{
    SM4_PROVIDER->enc_block(rk_data_, ciphertext, plaintext);
}

void SM4::decrypt_block(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext) const noexcept
{
    SM4_PROVIDER->dec_block(rk_data_, plaintext, ciphertext);
}

void SM4::encrypt_blocks(std::uint8_t*       ciphertext,
                         const std::uint8_t* plaintext,
                         std::size_t         block_num) const noexcept
{
    SM4_PROVIDER->enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void SM4::decrypt_blocks(std::uint8_t*       plaintext,
                         const std::uint8_t* ciphertext,
                         std::size_t         block_num) const noexcept
{
    SM4_PROVIDER->dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

}; // namespace sm4