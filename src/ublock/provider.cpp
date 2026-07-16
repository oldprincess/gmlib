#include <gmlib/ublock/provider.h>

#include <cstddef>
#include <cstring>

#include "provider_ublock_common.h"
#if defined(SUPPORT_UBLOCK_GONG25)
#include "provider_ublock_gong25.h"
#endif
#if defined(SUPPORT_UBLOCK_STANDARD)
#include "provider_ublock_standard.h"
#endif

namespace ublock {

struct Provider
{
    bool (*available)() noexcept;

    block_cipher_mode::BlockCipherModeProvider fns;
};

static const Provider providers_128128[] = {
#if defined(SUPPORT_UBLOCK_GONG25)
    {
        []() noexcept -> bool {
            return ublock::internal::gong25::provider_available();
        },
        {
            "gong25",
            ublock::internal::gong25::create_cipher_128128,
            ublock::internal::gong25::create_ecb_encryptor_128128,
            ublock::internal::gong25::create_ecb_decryptor_128128,
            ublock::internal::gong25::create_cbc_encryptor_128128,
            ublock::internal::gong25::create_cbc_decryptor_128128,
            ublock::internal::gong25::create_cfb_encryptor_128128,
            ublock::internal::gong25::create_cfb_decryptor_128128,
            ublock::internal::gong25::create_ofb_encryptor_128128,
            ublock::internal::gong25::create_ofb_decryptor_128128,
            ublock::internal::gong25::create_ctr_encryptor_128128,
            ublock::internal::gong25::create_ctr_decryptor_128128,
            ublock::internal::gong25::create_gcm_encryptor_128128,
            ublock::internal::gong25::create_gcm_decryptor_128128,
        },
    },

#endif
#if defined(SUPPORT_UBLOCK_STANDARD)
    {
        []() noexcept -> bool {
            return ublock::internal::standard::provider_available();
        },
        {
            "standard",
            ublock::internal::standard::create_cipher_128128,
            ublock::internal::standard::create_ecb_encryptor_128128,
            ublock::internal::standard::create_ecb_decryptor_128128,
            ublock::internal::standard::create_cbc_encryptor_128128,
            ublock::internal::standard::create_cbc_decryptor_128128,
            ublock::internal::standard::create_cfb_encryptor_128128,
            ublock::internal::standard::create_cfb_decryptor_128128,
            ublock::internal::standard::create_ofb_encryptor_128128,
            ublock::internal::standard::create_ofb_decryptor_128128,
            ublock::internal::standard::create_ctr_encryptor_128128,
            ublock::internal::standard::create_ctr_decryptor_128128,
            ublock::internal::standard::create_gcm_encryptor_128128,
            ublock::internal::standard::create_gcm_decryptor_128128,
        },
    },

#endif
    {
        []() noexcept -> bool {
            return ublock::internal::common::provider_available();
        },
        {
            "common",
            ublock::internal::common::create_cipher_128128,
            ublock::internal::common::create_ecb_encryptor_128128,
            ublock::internal::common::create_ecb_decryptor_128128,
            ublock::internal::common::create_cbc_encryptor_128128,
            ublock::internal::common::create_cbc_decryptor_128128,
            ublock::internal::common::create_cfb_encryptor_128128,
            ublock::internal::common::create_cfb_decryptor_128128,
            ublock::internal::common::create_ofb_encryptor_128128,
            ublock::internal::common::create_ofb_decryptor_128128,
            ublock::internal::common::create_ctr_encryptor_128128,
            ublock::internal::common::create_ctr_decryptor_128128,
            ublock::internal::common::create_gcm_encryptor_128128,
            ublock::internal::common::create_gcm_decryptor_128128,
        },
    },
};

static const Provider providers_128256[] = {
#if defined(SUPPORT_UBLOCK_GONG25)
    {
        []() noexcept -> bool {
            return ublock::internal::gong25::provider_available();
        },
        {
            "gong25",
            ublock::internal::gong25::create_cipher_128256,
            ublock::internal::gong25::create_ecb_encryptor_128256,
            ublock::internal::gong25::create_ecb_decryptor_128256,
            ublock::internal::gong25::create_cbc_encryptor_128256,
            ublock::internal::gong25::create_cbc_decryptor_128256,
            ublock::internal::gong25::create_cfb_encryptor_128256,
            ublock::internal::gong25::create_cfb_decryptor_128256,
            ublock::internal::gong25::create_ofb_encryptor_128256,
            ublock::internal::gong25::create_ofb_decryptor_128256,
            ublock::internal::gong25::create_ctr_encryptor_128256,
            ublock::internal::gong25::create_ctr_decryptor_128256,
            ublock::internal::gong25::create_gcm_encryptor_128256,
            ublock::internal::gong25::create_gcm_decryptor_128256,
        },
    },

#endif
#if defined(SUPPORT_UBLOCK_STANDARD)
    {
        []() noexcept -> bool {
            return ublock::internal::standard::provider_available();
        },
        {
            "standard",
            ublock::internal::standard::create_cipher_128256,
            ublock::internal::standard::create_ecb_encryptor_128256,
            ublock::internal::standard::create_ecb_decryptor_128256,
            ublock::internal::standard::create_cbc_encryptor_128256,
            ublock::internal::standard::create_cbc_decryptor_128256,
            ublock::internal::standard::create_cfb_encryptor_128256,
            ublock::internal::standard::create_cfb_decryptor_128256,
            ublock::internal::standard::create_ofb_encryptor_128256,
            ublock::internal::standard::create_ofb_decryptor_128256,
            ublock::internal::standard::create_ctr_encryptor_128256,
            ublock::internal::standard::create_ctr_decryptor_128256,
            ublock::internal::standard::create_gcm_encryptor_128256,
            ublock::internal::standard::create_gcm_decryptor_128256,
        },
    },

#endif
    {
        []() noexcept -> bool {
            return ublock::internal::common::provider_available();
        },
        {
            "common",
            ublock::internal::common::create_cipher_128256,
            ublock::internal::common::create_ecb_encryptor_128256,
            ublock::internal::common::create_ecb_decryptor_128256,
            ublock::internal::common::create_cbc_encryptor_128256,
            ublock::internal::common::create_cbc_decryptor_128256,
            ublock::internal::common::create_cfb_encryptor_128256,
            ublock::internal::common::create_cfb_decryptor_128256,
            ublock::internal::common::create_ofb_encryptor_128256,
            ublock::internal::common::create_ofb_decryptor_128256,
            ublock::internal::common::create_ctr_encryptor_128256,
            ublock::internal::common::create_ctr_decryptor_128256,
            ublock::internal::common::create_gcm_encryptor_128256,
            ublock::internal::common::create_gcm_decryptor_128256,
        },
    },
};

static const Provider providers_256256[] = {
#if defined(SUPPORT_UBLOCK_GONG25)
    {
        []() noexcept -> bool {
            return ublock::internal::gong25::provider_available();
        },
        {
            "gong25",
            ublock::internal::gong25::create_cipher_256256,
            ublock::internal::gong25::create_ecb_encryptor_256256,
            ublock::internal::gong25::create_ecb_decryptor_256256,
            ublock::internal::gong25::create_cbc_encryptor_256256,
            ublock::internal::gong25::create_cbc_decryptor_256256,
            ublock::internal::gong25::create_cfb_encryptor_256256,
            ublock::internal::gong25::create_cfb_decryptor_256256,
            ublock::internal::gong25::create_ofb_encryptor_256256,
            ublock::internal::gong25::create_ofb_decryptor_256256,
            ublock::internal::gong25::create_ctr_encryptor_256256,
            ublock::internal::gong25::create_ctr_decryptor_256256,
            nullptr,
            nullptr,
        },
    },

#endif
#if defined(SUPPORT_UBLOCK_STANDARD)
    {
        []() noexcept -> bool {
            return ublock::internal::standard::provider_available();
        },
        {
            "standard",
            ublock::internal::standard::create_cipher_256256,
            ublock::internal::standard::create_ecb_encryptor_256256,
            ublock::internal::standard::create_ecb_decryptor_256256,
            ublock::internal::standard::create_cbc_encryptor_256256,
            ublock::internal::standard::create_cbc_decryptor_256256,
            ublock::internal::standard::create_cfb_encryptor_256256,
            ublock::internal::standard::create_cfb_decryptor_256256,
            ublock::internal::standard::create_ofb_encryptor_256256,
            ublock::internal::standard::create_ofb_decryptor_256256,
            ublock::internal::standard::create_ctr_encryptor_256256,
            ublock::internal::standard::create_ctr_decryptor_256256,
            nullptr,
            nullptr,
        },
    },

#endif
    {
        []() noexcept -> bool {
            return ublock::internal::common::provider_available();
        },
        {
            "common",
            ublock::internal::common::create_cipher_256256,
            ublock::internal::common::create_ecb_encryptor_256256,
            ublock::internal::common::create_ecb_decryptor_256256,
            ublock::internal::common::create_cbc_encryptor_256256,
            ublock::internal::common::create_cbc_decryptor_256256,
            ublock::internal::common::create_cfb_encryptor_256256,
            ublock::internal::common::create_cfb_decryptor_256256,
            ublock::internal::common::create_ofb_encryptor_256256,
            ublock::internal::common::create_ofb_decryptor_256256,
            ublock::internal::common::create_ctr_encryptor_256256,
            ublock::internal::common::create_ctr_decryptor_256256,
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

const uBlock128128Provider* get_ublock128128_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const uBlock128128Provider* default_provider = []() {
            for (const Provider& provider : providers_128128)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const uBlock128128Provider*>(nullptr);
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

const char* const* get_ublock128128_supported_provider_names() noexcept
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

const uBlock128256Provider* get_ublock128256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const uBlock128256Provider* default_provider = []() {
            for (const Provider& provider : providers_128256)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const uBlock128256Provider*>(nullptr);
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

const char* const* get_ublock128256_supported_provider_names() noexcept
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

const uBlock256256Provider* get_ublock256256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const uBlock256256Provider* default_provider = []() {
            for (const Provider& provider : providers_256256)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const uBlock256256Provider*>(nullptr);
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

const char* const* get_ublock256256_supported_provider_names() noexcept
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

} // namespace ublock
