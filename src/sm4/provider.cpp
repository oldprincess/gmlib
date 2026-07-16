#include <gmlib/sm4/provider.h>

#include <cstddef>
#include <cstring>

#include "provider_sm4_common.h"
#if defined(SUPPORT_SM4_GONG23)
#include "provider_sm4_gong23.h"
#endif
#if defined(SUPPORT_SM4_LANG18)
#include "provider_sm4_lang18.h"
#endif
#if defined(SUPPORT_SM4_SM4NI)
#include "provider_sm4_sm4ni.h"
#endif

namespace sm4 {

struct Provider
{
    bool                                       (*available)() noexcept;
    block_cipher_mode::BlockCipherModeProvider fns;
};

static const Provider providers[] = {
#if defined(SUPPORT_SM4_GONG23)
    {
        []() noexcept -> bool {
            return sm4::internal::gong23::provider_available();
        },
        {
            "gong23",
            sm4::internal::gong23::create_cipher,
            sm4::internal::gong23::create_ecb_encryptor,
            sm4::internal::gong23::create_ecb_decryptor,
            sm4::internal::gong23::create_cbc_encryptor,
            sm4::internal::gong23::create_cbc_decryptor,
            sm4::internal::gong23::create_cfb_encryptor,
            sm4::internal::gong23::create_cfb_decryptor,
            sm4::internal::gong23::create_ofb_encryptor,
            sm4::internal::gong23::create_ofb_decryptor,
            sm4::internal::gong23::create_ctr_encryptor,
            sm4::internal::gong23::create_ctr_decryptor,
            sm4::internal::gong23::create_gcm_encryptor,
            sm4::internal::gong23::create_gcm_decryptor,
        },
    },

#endif
#if defined(SUPPORT_SM4_LANG18)
    {
        []() noexcept -> bool {
            return sm4::internal::lang18::provider_available();
        },
        {
            "lang18",
            sm4::internal::lang18::create_cipher,
            sm4::internal::lang18::create_ecb_encryptor,
            sm4::internal::lang18::create_ecb_decryptor,
            sm4::internal::lang18::create_cbc_encryptor,
            sm4::internal::lang18::create_cbc_decryptor,
            sm4::internal::lang18::create_cfb_encryptor,
            sm4::internal::lang18::create_cfb_decryptor,
            sm4::internal::lang18::create_ofb_encryptor,
            sm4::internal::lang18::create_ofb_decryptor,
            sm4::internal::lang18::create_ctr_encryptor,
            sm4::internal::lang18::create_ctr_decryptor,
            sm4::internal::lang18::create_gcm_encryptor,
            sm4::internal::lang18::create_gcm_decryptor,
        },
    },

#endif
#if defined(SUPPORT_SM4_SM4NI)
    {
        []() noexcept -> bool {
            return sm4::internal::sm4ni::provider_available();
        },
        {
            "sm4ni",
            sm4::internal::sm4ni::create_cipher,
            sm4::internal::sm4ni::create_ecb_encryptor,
            sm4::internal::sm4ni::create_ecb_decryptor,
            sm4::internal::sm4ni::create_cbc_encryptor,
            sm4::internal::sm4ni::create_cbc_decryptor,
            sm4::internal::sm4ni::create_cfb_encryptor,
            sm4::internal::sm4ni::create_cfb_decryptor,
            sm4::internal::sm4ni::create_ofb_encryptor,
            sm4::internal::sm4ni::create_ofb_decryptor,
            sm4::internal::sm4ni::create_ctr_encryptor,
            sm4::internal::sm4ni::create_ctr_decryptor,
            sm4::internal::sm4ni::create_gcm_encryptor,
            sm4::internal::sm4ni::create_gcm_decryptor,
        },
    },

#endif
    {
        []() noexcept -> bool {
            return sm4::internal::common::provider_available();
        },
        {
            "common",
            sm4::internal::common::create_cipher,
            sm4::internal::common::create_ecb_encryptor,
            sm4::internal::common::create_ecb_decryptor,
            sm4::internal::common::create_cbc_encryptor,
            sm4::internal::common::create_cbc_decryptor,
            sm4::internal::common::create_cfb_encryptor,
            sm4::internal::common::create_cfb_decryptor,
            sm4::internal::common::create_ofb_encryptor,
            sm4::internal::common::create_ofb_decryptor,
            sm4::internal::common::create_ctr_encryptor,
            sm4::internal::common::create_ctr_decryptor,
            sm4::internal::common::create_gcm_encryptor,
            sm4::internal::common::create_gcm_decryptor,
        },
    },
};

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept
{
    return N;
}

const SM4Provider* get_sm4_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const SM4Provider* default_provider = []() {
            for (const Provider& provider : providers)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const SM4Provider*>(nullptr);
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

const char* const* get_sm4_supported_provider_names() noexcept
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

} // namespace sm4
