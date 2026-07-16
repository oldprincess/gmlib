#include <gmlib/base64/provider.h>
#include <gmlib/cpuinfo/cpuinfo.h>

#include <cstddef>
#include <cstring>

#if defined(SUPPORT_BASE64_AVX2)
#include "base64_avx2.h"
#endif
#if defined(SUPPORT_BASE64_CHROMIUM)
#include "base64_chromium.h"
#endif
#include "base64_common.h"

namespace base64 {

struct Provider
{
    /**
     * @brief Tests whether this implementation is available.
     * @return Whether the implementation is usable.
     */
    bool (*available)() noexcept;

    Base64Provider fns;
};

static const Provider providers[] = {
#if defined(SUPPORT_BASE64_AVX2)
    {
        []() noexcept -> bool { return cpuinfo::x86_64::cpu_supports_avx2(); },
        {
            "avx2",
            internal::avx2::base64_is_b64,
            internal::avx2::base64_encode_outl,
            internal::avx2::base64_encode_strl,
            internal::avx2::base64_decode_outl,
            internal::avx2::base64_encode,
            internal::avx2::base64_decode,
        },
    },
#endif
#if defined(SUPPORT_BASE64_CHROMIUM)
    {
        []() noexcept -> bool { return true; },
        {
            "chromium",
            internal::chromium::base64_is_b64,
            internal::chromium::base64_encode_outl,
            internal::chromium::base64_encode_strl,
            internal::chromium::base64_decode_outl,
            internal::chromium::base64_encode,
            internal::chromium::base64_decode,
        },
    },
#endif
    {
        []() noexcept -> bool { return true; },
        {
            "common",
            internal::common::base64_is_b64,
            internal::common::base64_encode_outl,
            internal::common::base64_encode_strl,
            internal::common::base64_decode_outl,
            internal::common::base64_encode,
            internal::common::base64_decode,
        },
    },
};

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept
{
    return N;
}

const Base64Provider* get_base64_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Base64Provider* default_provider = []() {
            for (const Provider& provider : providers)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            return static_cast<const Base64Provider*>(nullptr);
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

const char* const* get_base64_supported_provider_names() noexcept
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

} // namespace base64
