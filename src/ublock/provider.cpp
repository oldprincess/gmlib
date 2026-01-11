#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/ublock/ublock.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "config.h"
#include "ublock_common.h"
#include "ublock_gong25.h"
#include "ublock_standard.h"

namespace ublock {

typedef void (*fn_enc_key_init_t)(void*               round_key,
                                  const std::uint8_t* user_key);
typedef void (*fn_dec_key_init_t)(void*               round_key,
                                  const std::uint8_t* user_key);
typedef void (*fn_enc_block_t)(const void*         round_key,
                               std::uint8_t*       ciphertext,
                               const std::uint8_t* plaintext);
typedef void (*fn_dec_block_t)(const void*         round_key,
                               std::uint8_t*       plaintext,
                               const std::uint8_t* ciphertext);
typedef void (*fn_enc_blocks_t)(const void*         round_key,
                                std::uint8_t*       ciphertext,
                                const std::uint8_t* plaintext,
                                std::size_t         block_num);
typedef void (*fn_dec_blocks_t)(const void*         round_key,
                                std::uint8_t*       plaintext,
                                const std::uint8_t* ciphertext,
                                std::size_t         block_num);

struct uBlockProvider
{
    bool (*available)();

    const char* algo_name;

    std::size_t round_key_size;

    fn_enc_key_init_t enc_key_init;

    fn_dec_key_init_t dec_key_init;

    fn_enc_block_t enc_block;

    fn_dec_block_t dec_block;

    fn_enc_blocks_t enc_blocks;

    fn_dec_blocks_t dec_blocks;
};

static uBlockProvider ublock128128_providers[] = {

#if defined(UBLOCK_IMPL_GONG25)
    {
        []() { return cpuinfo::x86_64::cpu_supports_avx2(); },
        ublock::internal::gong25::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::gong25::UBlock128128RoundKey),
        (fn_enc_key_init_t)ublock::internal::gong25::ublock128128_enc_key_init,
        (fn_dec_key_init_t)ublock::internal::gong25::ublock128128_dec_key_init,
        (fn_enc_block_t)ublock::internal::gong25::ublock128128_enc_block,
        (fn_dec_block_t)ublock::internal::gong25::ublock128128_dec_block,
        (fn_enc_blocks_t)ublock::internal::gong25::ublock128128_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::gong25::ublock128128_dec_blocks,
    },
#elif defined(UBLOCK_IMPL_STANDARD)
    {
        []() { return cpuinfo::x86_64::cpu_supports_ssse3(); },
        ublock::internal::standard::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::standard::UBlock128128RoundKey),
        (fn_enc_key_init_t)
            ublock::internal::standard::ublock128128_enc_key_init,
        (fn_dec_key_init_t)
            ublock::internal::standard::ublock128128_dec_key_init,
        (fn_enc_block_t)ublock::internal::standard::ublock128128_enc_block,
        (fn_dec_block_t)ublock::internal::standard::ublock128128_dec_block,
        (fn_enc_blocks_t)ublock::internal::standard::ublock128128_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::standard::ublock128128_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        ublock::internal::common::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::common::UBlock128128RoundKey),
        (fn_enc_key_init_t)ublock::internal::common::ublock128128_enc_key_init,
        (fn_dec_key_init_t)ublock::internal::common::ublock128128_dec_key_init,
        (fn_enc_block_t)ublock::internal::common::ublock128128_enc_block,
        (fn_dec_block_t)ublock::internal::common::ublock128128_dec_block,
        (fn_enc_blocks_t)ublock::internal::common::ublock128128_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::common::ublock128128_dec_blocks,
    },
    // end
    {nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static uBlockProvider ublock128256_providers[] = {

#if defined(UBLOCK_IMPL_GONG25)
    {
        []() { return cpuinfo::x86_64::cpu_supports_avx2(); },
        ublock::internal::gong25::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::gong25::UBlock128256RoundKey),
        (fn_enc_key_init_t)ublock::internal::gong25::ublock128256_enc_key_init,
        (fn_dec_key_init_t)ublock::internal::gong25::ublock128256_dec_key_init,
        (fn_enc_block_t)ublock::internal::gong25::ublock128256_enc_block,
        (fn_dec_block_t)ublock::internal::gong25::ublock128256_dec_block,
        (fn_enc_blocks_t)ublock::internal::gong25::ublock128256_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::gong25::ublock128256_dec_blocks,
    },
#elif defined(UBLOCK_IMPL_STANDARD)
    {
        []() { return cpuinfo::x86_64::cpu_supports_ssse3(); },
        ublock::internal::standard::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::standard::UBlock128256RoundKey),
        (fn_enc_key_init_t)
            ublock::internal::standard::ublock128256_enc_key_init,
        (fn_dec_key_init_t)
            ublock::internal::standard::ublock128256_dec_key_init,
        (fn_enc_block_t)ublock::internal::standard::ublock128256_enc_block,
        (fn_dec_block_t)ublock::internal::standard::ublock128256_dec_block,
        (fn_enc_blocks_t)ublock::internal::standard::ublock128256_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::standard::ublock128256_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        ublock::internal::common::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::common::UBlock128256RoundKey),
        (fn_enc_key_init_t)ublock::internal::common::ublock128256_enc_key_init,
        (fn_dec_key_init_t)ublock::internal::common::ublock128256_dec_key_init,
        (fn_enc_block_t)ublock::internal::common::ublock128256_enc_block,
        (fn_dec_block_t)ublock::internal::common::ublock128256_dec_block,
        (fn_enc_blocks_t)ublock::internal::common::ublock128256_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::common::ublock128256_dec_blocks,
    },
    // end
    {nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static uBlockProvider ublock256256_providers[] = {

#if defined(UBLOCK_IMPL_GONG25)
    {
        []() { return cpuinfo::x86_64::cpu_supports_avx2(); },
        ublock::internal::gong25::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::gong25::UBlock256256RoundKey),
        (fn_enc_key_init_t)ublock::internal::gong25::ublock256256_enc_key_init,
        (fn_dec_key_init_t)ublock::internal::gong25::ublock256256_dec_key_init,
        (fn_enc_block_t)ublock::internal::gong25::ublock256256_enc_block,
        (fn_dec_block_t)ublock::internal::gong25::ublock256256_dec_block,
        (fn_enc_blocks_t)ublock::internal::gong25::ublock256256_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::gong25::ublock256256_dec_blocks,
    },
#elif defined(UBLOCK_IMPL_STANDARD)
    {
        []() { return cpuinfo::x86_64::cpu_supports_ssse3(); },
        ublock::internal::standard::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::standard::UBlock256256RoundKey),
        (fn_enc_key_init_t)
            ublock::internal::standard::ublock256256_enc_key_init,
        (fn_dec_key_init_t)
            ublock::internal::standard::ublock256256_dec_key_init,
        (fn_enc_block_t)ublock::internal::standard::ublock256256_enc_block,
        (fn_dec_block_t)ublock::internal::standard::ublock256256_dec_block,
        (fn_enc_blocks_t)ublock::internal::standard::ublock256256_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::standard::ublock256256_dec_blocks,
    },
#endif
    // universal
    {
        []() { return true; },
        ublock::internal::common::UBLOCK_ALGO_NAME,
        sizeof(ublock::internal::common::UBlock256256RoundKey),
        (fn_enc_key_init_t)ublock::internal::common::ublock256256_enc_key_init,
        (fn_dec_key_init_t)ublock::internal::common::ublock256256_dec_key_init,
        (fn_enc_block_t)ublock::internal::common::ublock256256_enc_block,
        (fn_dec_block_t)ublock::internal::common::ublock256256_dec_block,
        (fn_enc_blocks_t)ublock::internal::common::ublock256256_enc_blocks,
        (fn_dec_blocks_t)ublock::internal::common::ublock256256_dec_blocks,
    },
    // end
    {nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
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
    std::printf("[uBlock PROVIDER] Provider %s is not available. %s:%d\n",
                name ? name : "", __FILE__, __LINE__);
    std::exit(-1);
}

static auto UBLOCK128128_PROVIDER = get_provider(ublock128128_providers);
static auto UBLOCK128256_PROVIDER = get_provider(ublock128256_providers);
static auto UBLOCK256256_PROVIDER = get_provider(ublock256256_providers);

const char* uBlock128128::fetch_impl_algo() const noexcept
{
    return UBLOCK128128_PROVIDER->algo_name;
}

void uBlock128128::set_key(const std::uint8_t* user_key, int enc) noexcept
{
    if (enc == ENCRYPTION)
    {
        UBLOCK128128_PROVIDER->enc_key_init(rk_data_.get(), user_key);
    }
    else
    {
        UBLOCK128128_PROVIDER->dec_key_init(rk_data_.get(), user_key);
    }
}

void uBlock128128::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    UBLOCK128128_PROVIDER->enc_block(rk_data_.get(), ciphertext, plaintext);
}

void uBlock128128::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    UBLOCK128128_PROVIDER->dec_block(rk_data_.get(), plaintext, ciphertext);
}

void uBlock128128::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128128_PROVIDER->enc_blocks(rk_data_.get(), ciphertext, plaintext,
                                      block_num);
}

void uBlock128128::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128128_PROVIDER->dec_blocks(rk_data_.get(), plaintext, ciphertext,
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
        UBLOCK128256_PROVIDER->enc_key_init(rk_data_.get(), user_key);
    }
    else
    {
        UBLOCK128256_PROVIDER->dec_key_init(rk_data_.get(), user_key);
    }
}

void uBlock128256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    UBLOCK128256_PROVIDER->enc_block(rk_data_.get(), ciphertext, plaintext);
}

void uBlock128256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    UBLOCK128256_PROVIDER->dec_block(rk_data_.get(), plaintext, ciphertext);
}

void uBlock128256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128256_PROVIDER->enc_blocks(rk_data_.get(), ciphertext, plaintext,
                                      block_num);
}

void uBlock128256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK128256_PROVIDER->dec_blocks(rk_data_.get(), plaintext, ciphertext,
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
        UBLOCK256256_PROVIDER->enc_key_init(rk_data_.get(), user_key);
    }
    else
    {
        UBLOCK256256_PROVIDER->dec_key_init(rk_data_.get(), user_key);
    }
}

void uBlock256256::encrypt_block(std::uint8_t*       ciphertext,
                                 const std::uint8_t* plaintext) const noexcept
{
    UBLOCK256256_PROVIDER->enc_block(rk_data_.get(), ciphertext, plaintext);
}

void uBlock256256::decrypt_block(std::uint8_t*       plaintext,
                                 const std::uint8_t* ciphertext) const noexcept
{
    UBLOCK256256_PROVIDER->dec_block(rk_data_.get(), plaintext, ciphertext);
}

void uBlock256256::encrypt_blocks(std::uint8_t*       ciphertext,
                                  const std::uint8_t* plaintext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK256256_PROVIDER->enc_blocks(rk_data_.get(), ciphertext, plaintext,
                                      block_num);
}

void uBlock256256::decrypt_blocks(std::uint8_t*       plaintext,
                                  const std::uint8_t* ciphertext,
                                  std::size_t         block_num) const noexcept
{
    UBLOCK256256_PROVIDER->dec_blocks(rk_data_.get(), plaintext, ciphertext,
                                      block_num);
}

// uBlock128128 implementations
uBlock128128::uBlock128128()
{
    std::size_t size = UBLOCK128128_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
}

uBlock128128::uBlock128128(const std::uint8_t* user_key, int enc)
{
    std::size_t size = UBLOCK128128_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
    this->set_key(user_key, enc);
}

uBlock128128::uBlock128128(const uBlock128128& other)
{
    std::size_t size = UBLOCK128128_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
    std::memcpy(rk_data_.get(), other.rk_data_.get(), size);
}

uBlock128128::uBlock128128(uBlock128128&& other) = default;

uBlock128128& uBlock128128::operator=(const uBlock128128& other)
{
    if (this != &other)
    {
        std::size_t size = UBLOCK128128_PROVIDER->round_key_size;
        rk_data_         = std::make_unique<std::uint8_t[]>(size);
        std::memcpy(rk_data_.get(), other.rk_data_.get(), size);
    }
    return *this;
}

uBlock128128& uBlock128128::operator=(uBlock128128&& other) = default;

// uBlock128256 implementations
uBlock128256::uBlock128256()
{
    std::size_t size = UBLOCK128256_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
}

uBlock128256::uBlock128256(const std::uint8_t* user_key, int enc)
{
    std::size_t size = UBLOCK128256_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
    this->set_key(user_key, enc);
}

uBlock128256::uBlock128256(const uBlock128256& other)
{
    std::size_t size = UBLOCK128256_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
    std::memcpy(rk_data_.get(), other.rk_data_.get(), size);
}

uBlock128256::uBlock128256(uBlock128256&& other) = default;

uBlock128256& uBlock128256::operator=(const uBlock128256& other)
{
    if (this != &other)
    {
        std::size_t size = UBLOCK128256_PROVIDER->round_key_size;
        rk_data_         = std::make_unique<std::uint8_t[]>(size);
        std::memcpy(rk_data_.get(), other.rk_data_.get(), size);
    }
    return *this;
}

uBlock128256& uBlock128256::operator=(uBlock128256&& other) = default;

// uBlock256256 implementations
uBlock256256::uBlock256256()
{
    std::size_t size = UBLOCK256256_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
}

uBlock256256::uBlock256256(const std::uint8_t* user_key, int enc)
{
    std::size_t size = UBLOCK256256_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
    this->set_key(user_key, enc);
}

uBlock256256::uBlock256256(const uBlock256256& other)
{
    std::size_t size = UBLOCK256256_PROVIDER->round_key_size;
    rk_data_         = std::make_unique<std::uint8_t[]>(size);
    std::memcpy(rk_data_.get(), other.rk_data_.get(), size);
}

uBlock256256::uBlock256256(uBlock256256&& other) = default;

uBlock256256& uBlock256256::operator=(const uBlock256256& other)
{
    if (this != &other)
    {
        std::size_t size = UBLOCK256256_PROVIDER->round_key_size;
        rk_data_         = std::make_unique<std::uint8_t[]>(size);
        std::memcpy(rk_data_.get(), other.rk_data_.get(), size);
    }
    return *this;
}

uBlock256256& uBlock256256::operator=(uBlock256256&& other) = default;

} // namespace ublock