#include <gmlib/des/provider.h>

#include <cstddef>
#include <cstring>

#include "provider_des_common.h"

namespace des {

struct Provider
{
    bool (*available)() noexcept;

    block_cipher_mode::BlockCipherModeProvider fns;
};

static const Provider providers[] = {
    {
        []() noexcept -> bool {
            return des::internal::common::provider_available();
        },
        {
            "common",
            des::internal::common::create_cipher,
            des::internal::common::create_ecb_encryptor,
            des::internal::common::create_ecb_decryptor,
            des::internal::common::create_cbc_encryptor,
            des::internal::common::create_cbc_decryptor,
            des::internal::common::create_cfb_encryptor,
            des::internal::common::create_cfb_decryptor,
            des::internal::common::create_ofb_encryptor,
            des::internal::common::create_ofb_decryptor,
            des::internal::common::create_ctr_encryptor,
            des::internal::common::create_ctr_decryptor,
            nullptr,
            nullptr,
        },
    },
};

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept
{
    return N;
}

const DESProvider* get_des_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const DESProvider* default_provider = []() {
            for (const Provider& provider : providers)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const DESProvider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider& provider : providers)
        {
            if (provider.available() &&
                std::strcmp(provider.fns.algo_name, name) == 0)
            {
                return &provider.fns;
            }
        }
        return nullptr;
    }
}

const char* const* get_des_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        struct ProviderNameList
        {
            const char* names[array_size(providers) + 1];
        };
        ProviderNameList list;
        int              idx = 0;
        for (const Provider& provider : providers)
        {
            if (provider.available())
            {
                list.names[idx++] = provider.fns.algo_name;
            }
        }
        list.names[idx] = nullptr;
        return list;
    }();
    return provider_name_list.names;
}

} // namespace des
