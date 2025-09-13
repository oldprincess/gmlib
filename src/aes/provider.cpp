#include <gmlib/aes/aes.h>
#include <gmlib/cpuinfo/cpuinfo.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "config.h"
// x86_64
#include "aes_aesni.h"
// arm
#include "aes_arm_aes.h"
// universal
#include "aes_lut.h"

namespace aes {

struct AESProvider
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

static AESProvider aes128_providers[] = {
// x86_64
#if defined(AES_IMPL_AESNI)
    {
        []() {
            return cpuinfo::x86_64::cpu_supports_aes() &&
                   cpuinfo::x86_64::cpu_supports_sse2();
        },
        aes::internal::aesni::AES_ALGO_NAME,
        aes::internal::aesni::aes128_enc_key_init,
        aes::internal::aesni::aes128_dec_key_init,
        aes::internal::aesni::aes128_enc_block,
        aes::internal::aesni::aes128_dec_block,
        aes::internal::aesni::aes128_enc_blocks,
        aes::internal::aesni::aes128_dec_blocks,
    },
#endif
// arm
#if defined(AES_IMPL_ARM_AES)
    {
        []() {
            return (cpuinfo::arm::cpu_supports_aes() &&
                    cpuinfo::arm::cpu_supports_neon()) ||
                   (cpuinfo::aarch64::cpu_supports_aes() &&
                    cpuinfo::aarch64::cpu_supports_asimd());
        },
        aes::internal::arm_aes::AES_ALGO_NAME,
        aes::internal::arm_aes::aes128_enc_key_init,
        aes::internal::arm_aes::aes128_dec_key_init,
        aes::internal::arm_aes::aes128_enc_block,
        aes::internal::arm_aes::aes128_dec_block,
        aes::internal::arm_aes::aes128_enc_blocks,
        aes::internal::arm_aes::aes128_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        aes::internal::lut::AES_ALGO_NAME,
        aes::internal::lut::aes128_enc_key_init,
        aes::internal::lut::aes128_dec_key_init,
        aes::internal::lut::aes128_enc_block,
        aes::internal::lut::aes128_dec_block,
        aes::internal::lut::aes128_enc_blocks,
        aes::internal::lut::aes128_dec_blocks,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static AESProvider aes192_providers[] = {
// x86_64
#if defined(AES_IMPL_AESNI)
    {
        []() {
            return cpuinfo::x86_64::cpu_supports_aes() &&
                   cpuinfo::x86_64::cpu_supports_sse2();
        },
        aes::internal::aesni::AES_ALGO_NAME,
        aes::internal::aesni::aes192_enc_key_init,
        aes::internal::aesni::aes192_dec_key_init,
        aes::internal::aesni::aes192_enc_block,
        aes::internal::aesni::aes192_dec_block,
        aes::internal::aesni::aes192_enc_blocks,
        aes::internal::aesni::aes192_dec_blocks,
    },
#endif
// arm
#if defined(AES_IMPL_ARM_AES)
    {
        []() {
            return (cpuinfo::arm::cpu_supports_aes() &&
                    cpuinfo::arm::cpu_supports_neon()) ||
                   (cpuinfo::aarch64::cpu_supports_aes() &&
                    cpuinfo::aarch64::cpu_supports_asimd());
        },
        aes::internal::arm_aes::AES_ALGO_NAME,
        aes::internal::arm_aes::aes192_enc_key_init,
        aes::internal::arm_aes::aes192_dec_key_init,
        aes::internal::arm_aes::aes192_enc_block,
        aes::internal::arm_aes::aes192_dec_block,
        aes::internal::arm_aes::aes192_enc_blocks,
        aes::internal::arm_aes::aes192_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        aes::internal::lut::AES_ALGO_NAME,
        aes::internal::lut::aes192_enc_key_init,
        aes::internal::lut::aes192_dec_key_init,
        aes::internal::lut::aes192_enc_block,
        aes::internal::lut::aes192_dec_block,
        aes::internal::lut::aes192_enc_blocks,
        aes::internal::lut::aes192_dec_blocks,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static AESProvider aes256_providers[] = {
// x86_64
#if defined(AES_IMPL_AESNI)
    {
        []() {
            return cpuinfo::x86_64::cpu_supports_aes() &&
                   cpuinfo::x86_64::cpu_supports_sse2();
        },
        aes::internal::aesni::AES_ALGO_NAME,
        aes::internal::aesni::aes256_enc_key_init,
        aes::internal::aesni::aes256_dec_key_init,
        aes::internal::aesni::aes256_enc_block,
        aes::internal::aesni::aes256_dec_block,
        aes::internal::aesni::aes256_enc_blocks,
        aes::internal::aesni::aes256_dec_blocks,
    },
#endif
// arm
#if defined(AES_IMPL_ARM_AES)
    {
        []() {
            return (cpuinfo::arm::cpu_supports_aes() &&
                    cpuinfo::arm::cpu_supports_neon()) ||
                   (cpuinfo::aarch64::cpu_supports_aes() &&
                    cpuinfo::aarch64::cpu_supports_asimd());
        },
        aes::internal::arm_aes::AES_ALGO_NAME,
        aes::internal::arm_aes::aes256_enc_key_init,
        aes::internal::arm_aes::aes256_dec_key_init,
        aes::internal::arm_aes::aes256_enc_block,
        aes::internal::arm_aes::aes256_dec_block,
        aes::internal::arm_aes::aes256_enc_blocks,
        aes::internal::arm_aes::aes256_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        aes::internal::lut::AES_ALGO_NAME,
        aes::internal::lut::aes256_enc_key_init,
        aes::internal::lut::aes256_dec_key_init,
        aes::internal::lut::aes256_enc_block,
        aes::internal::lut::aes256_dec_block,
        aes::internal::lut::aes256_enc_blocks,
        aes::internal::lut::aes256_dec_blocks,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static const AESProvider* get_provider(const AESProvider* providers,
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
    std::printf("[AES PROVIDER] Provider %s is not available. %s:%d\n",
                name ? name : "", __FILE__, __LINE__);
    std::exit(-1);
}

#define AES128_PROVIDER get_provider(aes128_providers)
#define AES192_PROVIDER get_provider(aes192_providers)
#define AES256_PROVIDER get_provider(aes256_providers)

const char* AES128::fetch_impl_algo() const noexcept
{
    return AES128_PROVIDER->algo_name;
}

void AES128::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        AES128_PROVIDER->enc_key_init(rk_data_, user_key);
    }
    else
    {
        AES128_PROVIDER->dec_key_init(rk_data_, user_key);
    }
}

void AES128::encrypt_block(std::uint8_t*       ciphertext,
                           const std::uint8_t* plaintext) const noexcept
{
    AES128_PROVIDER->enc_block(rk_data_, ciphertext, plaintext);
}

void AES128::decrypt_block(std::uint8_t*       plaintext,
                           const std::uint8_t* ciphertext) const noexcept
{
    AES128_PROVIDER->dec_block(rk_data_, plaintext, ciphertext);
}

void AES128::encrypt_blocks(std::uint8_t*       ciphertext,
                            const std::uint8_t* plaintext,
                            std::size_t         block_num) const noexcept
{
    AES128_PROVIDER->enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void AES128::decrypt_blocks(std::uint8_t*       plaintext,
                            const std::uint8_t* ciphertext,
                            std::size_t         block_num) const noexcept
{
    AES128_PROVIDER->dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* AES192::fetch_impl_algo() const noexcept
{
    return AES192_PROVIDER->algo_name;
}

void AES192::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        AES192_PROVIDER->enc_key_init(rk_data_, user_key);
    }
    else
    {
        AES192_PROVIDER->dec_key_init(rk_data_, user_key);
    }
}

void AES192::encrypt_block(std::uint8_t*       ciphertext,
                           const std::uint8_t* plaintext) const noexcept
{
    AES192_PROVIDER->enc_block(rk_data_, ciphertext, plaintext);
}

void AES192::decrypt_block(std::uint8_t*       plaintext,
                           const std::uint8_t* ciphertext) const noexcept
{
    AES192_PROVIDER->dec_block(rk_data_, plaintext, ciphertext);
}

void AES192::encrypt_blocks(std::uint8_t*       ciphertext,
                            const std::uint8_t* plaintext,
                            std::size_t         block_num) const noexcept
{
    AES192_PROVIDER->enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void AES192::decrypt_blocks(std::uint8_t*       plaintext,
                            const std::uint8_t* ciphertext,
                            std::size_t         block_num) const noexcept
{
    AES192_PROVIDER->dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

const char* AES256::fetch_impl_algo() const noexcept
{
    return AES256_PROVIDER->algo_name;
}

void AES256::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        AES256_PROVIDER->enc_key_init(rk_data_, user_key);
    }
    else
    {
        AES256_PROVIDER->dec_key_init(rk_data_, user_key);
    }
}

void AES256::encrypt_block(std::uint8_t*       ciphertext,
                           const std::uint8_t* plaintext) const noexcept
{
    AES256_PROVIDER->enc_block(rk_data_, ciphertext, plaintext);
}

void AES256::decrypt_block(std::uint8_t*       plaintext,
                           const std::uint8_t* ciphertext) const noexcept
{
    AES256_PROVIDER->dec_block(rk_data_, plaintext, ciphertext);
}

void AES256::encrypt_blocks(std::uint8_t*       ciphertext,
                            const std::uint8_t* plaintext,
                            std::size_t         block_num) const noexcept
{
    AES256_PROVIDER->enc_blocks(rk_data_, ciphertext, plaintext, block_num);
}

void AES256::decrypt_blocks(std::uint8_t*       plaintext,
                            const std::uint8_t* ciphertext,
                            std::size_t         block_num) const noexcept
{
    AES256_PROVIDER->dec_blocks(rk_data_, plaintext, ciphertext, block_num);
}

}; // namespace aes