#include <gmlib/base64/provider.h>
#include <gmlib/cpuinfo/cpuinfo.h>

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

#if defined(SUPPORT_BASE64_AVX2)
static const Provider base64_avx2_provider = {
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
};
#endif
#if defined(SUPPORT_BASE64_CHROMIUM)
static const Provider base64_chromium_provider = {
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
};
#endif
static const Provider base64_common_provider = {
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
};

const Base64Provider* get_base64_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Base64Provider* default_provider =
            []() noexcept -> const Base64Provider* {
#if defined(SUPPORT_BASE64_AVX2)
            if (base64_avx2_provider.available())
            {
                return &base64_avx2_provider.fns;
            }
#endif
#if defined(SUPPORT_BASE64_CHROMIUM)
            if (base64_chromium_provider.available())
            {
                return &base64_chromium_provider.fns;
            }
#endif
            return &base64_common_provider.fns;
        }();
        return default_provider;
    }
    else
    {
        if (std::strcmp(name, "avx2") == 0)
        {
#if defined(SUPPORT_BASE64_AVX2)
            if (base64_avx2_provider.available())
            {
                return &base64_avx2_provider.fns;
            }
#endif
            return nullptr;
        }
        else if (std::strcmp(name, "chromium") == 0)
        {
#if defined(SUPPORT_BASE64_CHROMIUM)
            if (base64_chromium_provider.available())
            {
                return &base64_chromium_provider.fns;
            }
#endif
            return nullptr;
        }
        else if (std::strcmp(name, "common") == 0)
        {
            return &base64_common_provider.fns;
        }
        else
        {
            return nullptr;
        }
    }
}

struct ProviderNameList
{
    const char* names[
#if defined(SUPPORT_BASE64_AVX2)
        1 + // avx2
#endif
#if defined(SUPPORT_BASE64_CHROMIUM)
        1 + // chromium
#endif
        1 + // common
        1   // nullptr
    ];
};

const char* const* get_base64_supported_provider_names() noexcept
{
    static const ProviderNameList list = []() noexcept -> ProviderNameList {
        ProviderNameList list;
        int              idx = 0;
#if defined(SUPPORT_BASE64_AVX2)
        if (base64_avx2_provider.available())
        {
            list.names[idx++] = "avx2";
        }
#endif
#if defined(SUPPORT_BASE64_CHROMIUM)
        if (base64_chromium_provider.available())
        {
            list.names[idx++] = "chromium";
        }
#endif
        list.names[idx++] = "common";
        list.names[idx]   = nullptr;
        return list;
    }();
    return list.names;
}

} // namespace base64
