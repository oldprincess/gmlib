#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/sha2/sha2.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#include "sha224_256_sha.h"
#include "sha2_common.h"

namespace sha2 {

struct SHA2Provider
{
    bool (*available)();

    const char* algo_name;

    // sha224

    void (*sha224_init)(std::uint8_t state[32], std::uint64_t* data_bits);

    void (*sha224_reset)(std::uint8_t state[32], std::uint64_t* data_bits);

    int (*sha224_update_blocks)(std::uint8_t        state[32],
                                std::uint64_t*      data_bits,
                                const std::uint8_t* in,
                                std::size_t         block_num);

    int (*sha224_final_block)(std::uint8_t        state[32],
                              std::uint64_t*      data_bits,
                              std::uint8_t*       digest,
                              const std::uint8_t* in,
                              std::size_t         inl);

    // sha256

    void (*sha256_init)(std::uint8_t state[32], std::uint64_t* data_bits);

    void (*sha256_reset)(std::uint8_t state[32], std::uint64_t* data_bits);

    int (*sha256_update_blocks)(std::uint8_t        state[32],
                                std::uint64_t*      data_bits,
                                const std::uint8_t* in,
                                std::size_t         block_num);

    int (*sha256_final_block)(std::uint8_t        state[32],
                              std::uint64_t*      data_bits,
                              std::uint8_t*       digest,
                              const std::uint8_t* in,
                              std::size_t         inl);

    // sha384

    void (*sha384_init)(std::uint8_t   state[64],
                        std::uint64_t* data_bits_h,
                        std::uint64_t* data_bits_l);

    void (*sha384_reset)(std::uint8_t   state[64],
                         std::uint64_t* data_bits_h,
                         std::uint64_t* data_bits_l);

    int (*sha384_update_blocks)(std::uint8_t        state[64],
                                std::uint64_t*      data_bits_h,
                                std::uint64_t*      data_bits_l,
                                const std::uint8_t* in,
                                std::size_t         block_num);

    int (*sha384_final_block)(std::uint8_t        state[64],
                              std::uint64_t*      data_bits_h,
                              std::uint64_t*      data_bits_l,
                              std::uint8_t*       digest,
                              const std::uint8_t* in,
                              std::size_t         inl);

    // sha512
    void (*sha512_init)(std::uint8_t   state[64],
                        std::uint64_t* data_bits_h,
                        std::uint64_t* data_bits_l);

    void (*sha512_reset)(std::uint8_t   state[64],
                         std::uint64_t* data_bits_h,
                         std::uint64_t* data_bits_l);

    int (*sha512_update_blocks)(std::uint8_t        state[64],
                                std::uint64_t*      data_bits_h,
                                std::uint64_t*      data_bits_l,
                                const std::uint8_t* in,
                                std::size_t         block_num);

    int (*sha512_final_block)(std::uint8_t        state[64],
                              std::uint64_t*      data_bits_h,
                              std::uint64_t*      data_bits_l,
                              std::uint8_t*       digest,
                              const std::uint8_t* in,
                              std::size_t         inl);
};

static const SHA2Provider sha224_256_providers[] = {
// sha
#if defined(SHA224_256_IMPL_SHA)
    {
        []() {
            return cpuinfo::x86_64::cpu_supports_sha() &&
                   cpuinfo::x86_64::cpu_supports_sse4_1();
        },
        "sha",
        // sha
        internal::sha::sha224_init,
        internal::sha::sha224_reset,
        internal::sha::sha224_update_blocks,
        internal::sha::sha224_final_block,
        // sha256
        internal::sha::sha256_init,
        internal::sha::sha256_reset,
        internal::sha::sha256_update_blocks,
        internal::sha::sha256_final_block,
        // sha384
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        // sha512
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },
#endif
    // common
    {
        []() { return true; },
        "common",
        // sha224
        internal::common::sha224_init,
        internal::common::sha224_reset,
        internal::common::sha224_update_blocks,
        internal::common::sha224_final_block,
        // sha256
        internal::common::sha256_init,
        internal::common::sha256_reset,
        internal::common::sha256_update_blocks,
        internal::common::sha256_final_block,
        // sha384
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        // sha512
        nullptr,
        nullptr,
        nullptr,
        nullptr,
    },

    {nullptr},
};

static const SHA2Provider sha384_512_providers[] = {
    // common
    {
        []() { return true; },
        "common",
        // sha224
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        // sha256
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        // sha384
        internal::common::sha384_init,
        internal::common::sha384_reset,
        internal::common::sha384_update_blocks,
        internal::common::sha384_final_block,
        // sha512
        internal::common::sha512_init,
        internal::common::sha512_reset,
        internal::common::sha512_update_blocks,
        internal::common::sha512_final_block,
    },

    {nullptr},
};

static const SHA2Provider* get_provider(const SHA2Provider* providers,
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
    std::printf("[SHA2 PROVIDER] Provider %s is not available. %s:%d\n",
                name ? name : "", __FILE__, __LINE__);
    std::exit(-1);
}

static const SHA2Provider* SHA224_256_PROVIDER =
    get_provider(sha224_256_providers);

static const SHA2Provider* SHA384_512_PROVIDER =
    get_provider(sha384_512_providers);

// sha224

SHA224::SHA224() noexcept
{
    SHA224_256_PROVIDER->sha224_init(state_, &data_bits_);
}

const char* SHA224::fetch_impl_algo() const noexcept
{
    return SHA224_256_PROVIDER->algo_name;
}

void SHA224::reset() noexcept
{
    this->HashImpl<64>::reset();
    SHA224_256_PROVIDER->sha224_reset(state_, &data_bits_);
}

void SHA224::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = SHA224_256_PROVIDER->sha224_update_blocks( //
        state_, &data_bits_, in, block_num               //
    );                                                   //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 update blocks error");
    }
}

void SHA224::final_block(std::uint8_t*       digest,
                         const std::uint8_t* in,
                         std::size_t         inl)
{
    int ret = SHA224_256_PROVIDER->sha224_final_block( //
        state_, &data_bits_, digest, in, inl           //
    );                                                 //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 final block error");
    }
}

// sha256

SHA256::SHA256() noexcept
{
    SHA224_256_PROVIDER->sha256_init(state_, &data_bits_);
}

const char* SHA256::fetch_impl_algo() const noexcept
{
    return SHA224_256_PROVIDER->algo_name;
}

void SHA256::reset() noexcept
{
    this->HashImpl<64>::reset();
    SHA224_256_PROVIDER->sha256_reset(state_, &data_bits_);
}

void SHA256::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = SHA224_256_PROVIDER->sha256_update_blocks( //
        state_, &data_bits_, in, block_num               //
    );                                                   //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 update blocks error");
    }
}

void SHA256::final_block(std::uint8_t*       digest,
                         const std::uint8_t* in,
                         std::size_t         inl)
{
    int ret = SHA224_256_PROVIDER->sha256_final_block( //
        state_, &data_bits_, digest, in, inl           //
    );                                                 //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 final block error");
    }
}

// sha384

SHA384::SHA384() noexcept
{
    SHA384_512_PROVIDER->sha384_init(state_, &data_bits_h_, &data_bits_l_);
}

const char* SHA384::fetch_impl_algo() const noexcept
{
    return SHA384_512_PROVIDER->algo_name;
}

void SHA384::reset() noexcept
{
    this->HashImpl<128>::reset();
    SHA384_512_PROVIDER->sha384_reset(state_, &data_bits_h_, &data_bits_l_);
}

void SHA384::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = SHA384_512_PROVIDER->sha384_update_blocks(    //
        state_, &data_bits_h_, &data_bits_l_, in, block_num //
    );                                                      //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 update blocks error");
    }
}

void SHA384::final_block(std::uint8_t*       digest,
                         const std::uint8_t* in,
                         std::size_t         inl)
{
    int ret = SHA384_512_PROVIDER->sha384_final_block(        //
        state_, &data_bits_h_, &data_bits_l_, digest, in, inl //
    );                                                        //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 final block error");
    }
}

// sha512

SHA512::SHA512() noexcept
{
    SHA384_512_PROVIDER->sha512_init(state_, &data_bits_h_, &data_bits_l_);
}

const char* SHA512::fetch_impl_algo() const noexcept
{
    return SHA384_512_PROVIDER->algo_name;
}

void SHA512::reset() noexcept

{
    this->HashImpl<128>::reset();
    SHA384_512_PROVIDER->sha512_reset(state_, &data_bits_h_, &data_bits_l_);
}

void SHA512::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = SHA384_512_PROVIDER->sha512_update_blocks(    //
        state_, &data_bits_h_, &data_bits_l_, in, block_num //
    );                                                      //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 update blocks error");
    }
}

void SHA512::final_block(std::uint8_t*       digest,
                         const std::uint8_t* in,
                         std::size_t         inl)
{
    int ret = SHA384_512_PROVIDER->sha512_final_block(        //
        state_, &data_bits_h_, &data_bits_l_, digest, in, inl //
    );                                                        //
    if (ret != 0)
    {
        throw std::runtime_error("sha2 final block error");
    }
}

} // namespace sha2
