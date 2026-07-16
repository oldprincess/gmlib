#include <gmlib/ballet/provider.h>

#include <cstddef>
#include <cstring>

#include "provider_ballet_standard.h"

namespace ballet {

struct Provider
{
    bool (*available)() noexcept;

    block_cipher_mode::BlockCipherModeProvider fns;
};

static const Provider providers_128128[] = {
    {
        []() noexcept -> bool {
            return ballet::internal::standard::provider_available();
        },
        {
            "standard",
            ballet::internal::standard::create_cipher_128128,
            ballet::internal::standard::create_ecb_encryptor_128128,
            ballet::internal::standard::create_ecb_decryptor_128128,
            ballet::internal::standard::create_cbc_encryptor_128128,
            ballet::internal::standard::create_cbc_decryptor_128128,
            ballet::internal::standard::create_cfb_encryptor_128128,
            ballet::internal::standard::create_cfb_decryptor_128128,
            ballet::internal::standard::create_ofb_encryptor_128128,
            ballet::internal::standard::create_ofb_decryptor_128128,
            ballet::internal::standard::create_ctr_encryptor_128128,
            ballet::internal::standard::create_ctr_decryptor_128128,
            ballet::internal::standard::create_gcm_encryptor_128128,
            ballet::internal::standard::create_gcm_decryptor_128128,
        },
    },
};

static const Provider providers_128256[] = {
    {
        []() noexcept -> bool {
            return ballet::internal::standard::provider_available();
        },
        {
            "standard",
            ballet::internal::standard::create_cipher_128256,
            ballet::internal::standard::create_ecb_encryptor_128256,
            ballet::internal::standard::create_ecb_decryptor_128256,
            ballet::internal::standard::create_cbc_encryptor_128256,
            ballet::internal::standard::create_cbc_decryptor_128256,
            ballet::internal::standard::create_cfb_encryptor_128256,
            ballet::internal::standard::create_cfb_decryptor_128256,
            ballet::internal::standard::create_ofb_encryptor_128256,
            ballet::internal::standard::create_ofb_decryptor_128256,
            ballet::internal::standard::create_ctr_encryptor_128256,
            ballet::internal::standard::create_ctr_decryptor_128256,
            ballet::internal::standard::create_gcm_encryptor_128256,
            ballet::internal::standard::create_gcm_decryptor_128256,
        },
    },
};

static const Provider providers_256256[] = {
    {
        []() noexcept -> bool {
            return ballet::internal::standard::provider_available();
        },
        {
            "standard",
            ballet::internal::standard::create_cipher_256256,
            ballet::internal::standard::create_ecb_encryptor_256256,
            ballet::internal::standard::create_ecb_decryptor_256256,
            ballet::internal::standard::create_cbc_encryptor_256256,
            ballet::internal::standard::create_cbc_decryptor_256256,
            ballet::internal::standard::create_cfb_encryptor_256256,
            ballet::internal::standard::create_cfb_decryptor_256256,
            ballet::internal::standard::create_ofb_encryptor_256256,
            ballet::internal::standard::create_ofb_decryptor_256256,
            ballet::internal::standard::create_ctr_encryptor_256256,
            ballet::internal::standard::create_ctr_decryptor_256256,
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

const Ballet128128Provider* get_ballet128128_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Ballet128128Provider* default_provider = []() {
            for (const Provider& provider : providers_128128)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const Ballet128128Provider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider& provider : providers_128128)
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

const char* const* get_ballet128128_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        struct ProviderNameList
        {
            const char* names[array_size(providers_128128) + 1];
        };
        ProviderNameList list;
        int              idx = 0;
        for (const Provider& provider : providers_128128)
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

const Ballet128256Provider* get_ballet128256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Ballet128256Provider* default_provider = []() {
            for (const Provider& provider : providers_128256)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const Ballet128256Provider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider& provider : providers_128256)
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

const char* const* get_ballet128256_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        struct ProviderNameList
        {
            const char* names[array_size(providers_128256) + 1];
        };
        ProviderNameList list;
        int              idx = 0;
        for (const Provider& provider : providers_128256)
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

const Ballet256256Provider* get_ballet256256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Ballet256256Provider* default_provider = []() {
            for (const Provider& provider : providers_256256)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const Ballet256256Provider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider& provider : providers_256256)
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

const char* const* get_ballet256256_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        struct ProviderNameList
        {
            const char* names[array_size(providers_256256) + 1];
        };
        ProviderNameList list;
        int              idx = 0;
        for (const Provider& provider : providers_256256)
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

} // namespace ballet
