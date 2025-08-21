#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/sha1/sha1.h>

#include <stdexcept>

#include "config.h"
#include "sha1_common.h"
#include "sha1_sha.h"

namespace sha1 {

struct SHA1Provider
{
    bool (*available)();

    const char* algo_name;

    void (*init)(std::uint32_t state[5], std::uint64_t* data_bits);

    void (*reset)(std::uint32_t state[5], std::uint64_t* data_bits);

    int (*update_blocks)(std::uint32_t       state[5],
                         std::uint64_t*      data_bits,
                         const std::uint8_t* in,
                         std::size_t         block_num);

    int (*final_block)(std::uint32_t       state[5],
                       std::uint64_t*      data_bits,
                       std::uint8_t        digest[32],
                       const std::uint8_t* in,
                       std::size_t         inl);
};

static SHA1Provider sha1_providers[] = {

#if defined(SHA1_IMPL_SHA)
    {
        []() {
            return cpuinfo::x86_64::cpu_supports_sha() &&
                   cpuinfo::x86_64::cpu_supports_sse4_1();
        },
        sha1::internal::sha::SHA1_ALGO_NAME,
        sha1::internal::sha::sha1_init,
        sha1::internal::sha::sha1_reset,
        sha1::internal::sha::sha1_update_blocks,
        sha1::internal::sha::sha1_final_block,
    },
#endif
    // universal
    {
        []() { return true; },
        sha1::internal::common::SHA1_ALGO_NAME,
        sha1::internal::common::sha1_init,
        sha1::internal::common::sha1_reset,
        sha1::internal::common::sha1_update_blocks,
        sha1::internal::common::sha1_final_block,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr},
};

static const SHA1Provider* get_provider(const SHA1Provider* providers,
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
    std::printf("[SHA1 PROVIDER] Provider %s is not available. %s:%d\n", name,
                __FILE__, __LINE__);
    std::exit(-1);
}

#define SHA1_PROVIDER get_provider(sha1_providers)

SHA1::SHA1() noexcept
{
    SHA1_PROVIDER->init(state_, &data_bits_);
}

const char* SHA1::fetch_impl_algo() const noexcept
{
    return SHA1_PROVIDER->algo_name;
}

void SHA1::reset() noexcept
{
    this->HashImpl<64>::reset();
    SHA1_PROVIDER->reset(state_, &data_bits_);
}

void SHA1::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = SHA1_PROVIDER->update_blocks(state_, &data_bits_, in, block_num);
    if (ret != 0)
    {
        throw std::runtime_error("sha1 update blocks error");
    }
}

void SHA1::final_block(std::uint8_t*       digest,
                       const std::uint8_t* in,
                       std::size_t         inl)
{
    int ret = SHA1_PROVIDER->final_block(state_, &data_bits_, digest, in, inl);
    if (ret != 0)
    {
        throw std::runtime_error("sha1 final block error");
    }
}

}; // namespace sha1