#include <gmlib/sm3/sm3.h>

#include <cstdio>
#include <stdexcept>

#include "config.h"
#include "sm3_common.h"
#include "sm3_yang15.h"

namespace sm3 {

struct SM3Provider
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

static SM3Provider sm3_providers[] = {

#if defined(SM3_IMPL_YANG15)
    {
        []() { return true; },
        sm3::internal::yang15::SM3_ALGO_NAME,
        sm3::internal::yang15::sm3_init,
        sm3::internal::yang15::sm3_reset,
        sm3::internal::yang15::sm3_update_blocks,
        sm3::internal::yang15::sm3_final_block,
    },
#endif
    // universal
    {
        []() { return true; },
        sm3::internal::common::SM3_ALGO_NAME,
        sm3::internal::common::sm3_init,
        sm3::internal::common::sm3_reset,
        sm3::internal::common::sm3_update_blocks,
        sm3::internal::common::sm3_final_block,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr},
};

static const SM3Provider* get_provider(const SM3Provider* providers,
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
    std::printf("[SM3 PROVIDER] Provider %s is not available. %s:%d\n",
                name ? name : "", __FILE__, __LINE__);
    std::exit(-1);
}

#define SM3_PROVIDER get_provider(sm3_providers)

SM3::SM3() noexcept
{
    SM3_PROVIDER->init(state_, &data_bits_);
}

const char* SM3::fetch_impl_algo() const noexcept
{
    return SM3_PROVIDER->algo_name;
}

void SM3::reset() noexcept
{
    this->HashImpl<SM3::BLOCK_SIZE>::reset();
    SM3_PROVIDER->reset(state_, &data_bits_);
}

void SM3::update_blocks(const std::uint8_t* in, std::size_t block_num)
{
    int ret = SM3_PROVIDER->update_blocks(state_, &data_bits_, in, block_num);
    if (ret)
    {
        throw std::runtime_error("sm3 update blocks error");
    }
}

void SM3::final_block(std::uint8_t*       digest,
                      const std::uint8_t* in,
                      std::size_t         inl)
{
    int ret = SM3_PROVIDER->final_block(state_, &data_bits_, digest, in, inl);
    if (ret)
    {
        throw std::runtime_error("sm3 final block error");
    }
}

}; // namespace sm3