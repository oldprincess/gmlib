#include <gmlib/aes/provider.h>

#include <cstddef>
#include <cstring>

#if defined(SUPPORT_AES_AESNI)
#include "provider_aes_aesni.h"
#endif
#if defined(SUPPORT_AES_ARM_AES)
#include "provider_aes_arm_aes.h"
#endif
#include "provider_aes_lut.h"

namespace aes {

// =======================================================================
// Internal provider wrappers (available predicate + factory functions)
// =======================================================================

struct Provider128
{
    bool           (*available)() noexcept;
    AES128Provider fns;
};

struct Provider192
{
    bool           (*available)() noexcept;
    AES192Provider fns;
};

struct Provider256
{
    bool           (*available)() noexcept;
    AES256Provider fns;
};

// =======================================================================
// AES-128 static provider instances
// =======================================================================

static const Provider128 aes128_providers[] = {
#if defined(SUPPORT_AES_AESNI)
    {
        []() noexcept -> bool {
            return aes::internal::aesni::provider_available();
        },
        {
            "aesni",
            aes::internal::aesni::create_cipher_128,        //
            aes::internal::aesni::create_ecb_encryptor_128, //
            aes::internal::aesni::create_ecb_decryptor_128, //
            aes::internal::aesni::create_cbc_encryptor_128, //
            aes::internal::aesni::create_cbc_decryptor_128, //
            aes::internal::aesni::create_cfb_encryptor_128, //
            aes::internal::aesni::create_cfb_decryptor_128, //
            aes::internal::aesni::create_ofb_encryptor_128, //
            aes::internal::aesni::create_ofb_decryptor_128, //
            aes::internal::aesni::create_ctr_encryptor_128, //
            aes::internal::aesni::create_ctr_decryptor_128, //
            aes::internal::aesni::create_gcm_encryptor_128, //
            aes::internal::aesni::create_gcm_decryptor_128, //
        },
    },
#endif

#if defined(SUPPORT_AES_ARM_AES)
    {
        []() noexcept -> bool {
            return aes::internal::arm_aes::provider_available();
        },
        {
            "arm_aes",
            aes::internal::arm_aes::create_cipher_128,        //
            aes::internal::arm_aes::create_ecb_encryptor_128, //
            aes::internal::arm_aes::create_ecb_decryptor_128, //
            aes::internal::arm_aes::create_cbc_encryptor_128, //
            aes::internal::arm_aes::create_cbc_decryptor_128, //
            aes::internal::arm_aes::create_cfb_encryptor_128, //
            aes::internal::arm_aes::create_cfb_decryptor_128, //
            aes::internal::arm_aes::create_ofb_encryptor_128, //
            aes::internal::arm_aes::create_ofb_decryptor_128, //
            aes::internal::arm_aes::create_ctr_encryptor_128, //
            aes::internal::arm_aes::create_ctr_decryptor_128, //
            aes::internal::arm_aes::create_gcm_encryptor_128, //
            aes::internal::arm_aes::create_gcm_decryptor_128, //
        },
    },
#endif

    {
        []() noexcept -> bool { return true; },
        {
            "lut",
            aes::internal::lut::create_cipher_128,        //
            aes::internal::lut::create_ecb_encryptor_128, //
            aes::internal::lut::create_ecb_decryptor_128, //
            aes::internal::lut::create_cbc_encryptor_128, //
            aes::internal::lut::create_cbc_decryptor_128, //
            aes::internal::lut::create_cfb_encryptor_128, //
            aes::internal::lut::create_cfb_decryptor_128, //
            aes::internal::lut::create_ofb_encryptor_128, //
            aes::internal::lut::create_ofb_decryptor_128, //
            aes::internal::lut::create_ctr_encryptor_128, //
            aes::internal::lut::create_ctr_decryptor_128, //
            aes::internal::lut::create_gcm_encryptor_128, //
            aes::internal::lut::create_gcm_decryptor_128, //
        },
    },
};

// =======================================================================
// AES-192 static provider instances
// =======================================================================

static const Provider192 aes192_providers[] = {
#if defined(SUPPORT_AES_AESNI)
    {
        []() noexcept -> bool {
            return aes::internal::aesni::provider_available();
        },
        {
            "aesni",
            aes::internal::aesni::create_cipher_192,        //
            aes::internal::aesni::create_ecb_encryptor_192, //
            aes::internal::aesni::create_ecb_decryptor_192, //
            aes::internal::aesni::create_cbc_encryptor_192, //
            aes::internal::aesni::create_cbc_decryptor_192, //
            aes::internal::aesni::create_cfb_encryptor_192, //
            aes::internal::aesni::create_cfb_decryptor_192, //
            aes::internal::aesni::create_ofb_encryptor_192, //
            aes::internal::aesni::create_ofb_decryptor_192, //
            aes::internal::aesni::create_ctr_encryptor_192, //
            aes::internal::aesni::create_ctr_decryptor_192, //
            aes::internal::aesni::create_gcm_encryptor_192, //
            aes::internal::aesni::create_gcm_decryptor_192, //
        },
    },
#endif

#if defined(SUPPORT_AES_ARM_AES)
    {
        []() noexcept -> bool {
            return aes::internal::arm_aes::provider_available();
        },
        {
            "arm_aes",
            aes::internal::arm_aes::create_cipher_192,        //
            aes::internal::arm_aes::create_ecb_encryptor_192, //
            aes::internal::arm_aes::create_ecb_decryptor_192, //
            aes::internal::arm_aes::create_cbc_encryptor_192, //
            aes::internal::arm_aes::create_cbc_decryptor_192, //
            aes::internal::arm_aes::create_cfb_encryptor_192, //
            aes::internal::arm_aes::create_cfb_decryptor_192, //
            aes::internal::arm_aes::create_ofb_encryptor_192, //
            aes::internal::arm_aes::create_ofb_decryptor_192, //
            aes::internal::arm_aes::create_ctr_encryptor_192, //
            aes::internal::arm_aes::create_ctr_decryptor_192, //
            aes::internal::arm_aes::create_gcm_encryptor_192, //
            aes::internal::arm_aes::create_gcm_decryptor_192, //
        },
    },
#endif

    {
        []() noexcept -> bool { return true; },
        {
            "lut",
            aes::internal::lut::create_cipher_192,        //
            aes::internal::lut::create_ecb_encryptor_192, //
            aes::internal::lut::create_ecb_decryptor_192, //
            aes::internal::lut::create_cbc_encryptor_192, //
            aes::internal::lut::create_cbc_decryptor_192, //
            aes::internal::lut::create_cfb_encryptor_192, //
            aes::internal::lut::create_cfb_decryptor_192, //
            aes::internal::lut::create_ofb_encryptor_192, //
            aes::internal::lut::create_ofb_decryptor_192, //
            aes::internal::lut::create_ctr_encryptor_192, //
            aes::internal::lut::create_ctr_decryptor_192, //
            aes::internal::lut::create_gcm_encryptor_192, //
            aes::internal::lut::create_gcm_decryptor_192, //
        },
    },
};

// =======================================================================
// AES-256 static provider instances
// =======================================================================

static const Provider256 aes256_providers[] = {
#if defined(SUPPORT_AES_AESNI)
    {
        []() noexcept -> bool {
            return aes::internal::aesni::provider_available();
        },
        {
            "aesni",
            aes::internal::aesni::create_cipher_256,        //
            aes::internal::aesni::create_ecb_encryptor_256, //
            aes::internal::aesni::create_ecb_decryptor_256, //
            aes::internal::aesni::create_cbc_encryptor_256, //
            aes::internal::aesni::create_cbc_decryptor_256, //
            aes::internal::aesni::create_cfb_encryptor_256, //
            aes::internal::aesni::create_cfb_decryptor_256, //
            aes::internal::aesni::create_ofb_encryptor_256, //
            aes::internal::aesni::create_ofb_decryptor_256, //
            aes::internal::aesni::create_ctr_encryptor_256, //
            aes::internal::aesni::create_ctr_decryptor_256, //
            aes::internal::aesni::create_gcm_encryptor_256, //
            aes::internal::aesni::create_gcm_decryptor_256, //
        },
    },
#endif

#if defined(SUPPORT_AES_ARM_AES)
    {
        []() noexcept -> bool {
            return aes::internal::arm_aes::provider_available();
        },
        {
            "arm_aes",
            aes::internal::arm_aes::create_cipher_256,        //
            aes::internal::arm_aes::create_ecb_encryptor_256, //
            aes::internal::arm_aes::create_ecb_decryptor_256, //
            aes::internal::arm_aes::create_cbc_encryptor_256, //
            aes::internal::arm_aes::create_cbc_decryptor_256, //
            aes::internal::arm_aes::create_cfb_encryptor_256, //
            aes::internal::arm_aes::create_cfb_decryptor_256, //
            aes::internal::arm_aes::create_ofb_encryptor_256, //
            aes::internal::arm_aes::create_ofb_decryptor_256, //
            aes::internal::arm_aes::create_ctr_encryptor_256, //
            aes::internal::arm_aes::create_ctr_decryptor_256, //
            aes::internal::arm_aes::create_gcm_encryptor_256, //
            aes::internal::arm_aes::create_gcm_decryptor_256, //
        },
    },
#endif

    {
        []() noexcept -> bool { return true; },
        {
            "lut",
            aes::internal::lut::create_cipher_256,        //
            aes::internal::lut::create_ecb_encryptor_256, //
            aes::internal::lut::create_ecb_decryptor_256, //
            aes::internal::lut::create_cbc_encryptor_256, //
            aes::internal::lut::create_cbc_decryptor_256, //
            aes::internal::lut::create_cfb_encryptor_256, //
            aes::internal::lut::create_cfb_decryptor_256, //
            aes::internal::lut::create_ofb_encryptor_256, //
            aes::internal::lut::create_ofb_decryptor_256, //
            aes::internal::lut::create_ctr_encryptor_256, //
            aes::internal::lut::create_ctr_decryptor_256, //
            aes::internal::lut::create_gcm_encryptor_256, //
            aes::internal::lut::create_gcm_decryptor_256, //
        },
    },
};

// =======================================================================
// get_aes128_provider
// =======================================================================

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept
{
    return N;
}

const AES128Provider* get_aes128_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const AES128Provider* default_provider = []() {
            for (const Provider128& provider : aes128_providers)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const AES128Provider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider128& provider : aes128_providers)
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

// =======================================================================
// get_aes192_provider
// =======================================================================

const AES192Provider* get_aes192_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const AES192Provider* default_provider = []() {
            for (const Provider192& provider : aes192_providers)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const AES192Provider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider192& provider : aes192_providers)
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

// =======================================================================
// get_aes256_provider
// =======================================================================

const AES256Provider* get_aes256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const AES256Provider* default_provider = []() {
            for (const Provider256& provider : aes256_providers)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const AES256Provider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider256& provider : aes256_providers)
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

// =======================================================================
// Provider name lists
// =======================================================================

const char* const* get_aes128_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        struct ProviderNameList
        {
            const char* names[array_size(aes128_providers) + 1];
        };
        ProviderNameList list;
        int              idx = 0;
        for (const Provider128& provider : aes128_providers)
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

const char* const* get_aes192_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        struct ProviderNameList
        {
            const char* names[array_size(aes192_providers) + 1];
        };
        ProviderNameList list;
        int              idx = 0;
        for (const Provider192& provider : aes192_providers)
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

const char* const* get_aes256_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        struct ProviderNameList
        {
            const char* names[array_size(aes256_providers) + 1];
        };
        ProviderNameList list;
        int              idx = 0;
        for (const Provider256& provider : aes256_providers)
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

} // namespace aes
