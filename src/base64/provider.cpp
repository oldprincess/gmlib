#include <gmlib/base64/base64.h>
#include <gmlib/cpuinfo/cpuinfo.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "base64_avx2.h"
#include "base64_chromium.h"
#include "base64_common.h"
#include "config.h"

namespace base64 {

struct Base64Provider
{
    bool (*available)();

    const char* algo_name;

    bool (*is_b64)(const char* in, std::size_t inl);

    std::size_t (*encode_outl)(std::size_t inl);

    std::size_t (*encode_strl)(std::size_t inl);

    std::size_t (*decode_outl)(const char* in, std::size_t inl);

    void (*encode)(char* out, const std::uint8_t* in, std::size_t inl);

    int (*decode)(std::uint8_t* out, const char* in, std::size_t inl);
};

static Base64Provider base64_providers[] = {
// x86_64
#if defined(BASE64_IMPL_AVX2)
    {
        []() { return cpuinfo::x86_64::cpu_supports_avx2(); },
        "avx2",
        base64::internal::avx2::base64_is_b64,
        base64::internal::avx2::base64_encode_outl,
        base64::internal::avx2::base64_encode_strl,
        base64::internal::avx2::base64_decode_outl,
        base64::internal::avx2::base64_encode,
        base64::internal::avx2::base64_decode,
    },
#endif
// arm
#if defined(BASE64_IMPL_CHROMIUM)
    {
        []() { return true; },
        "chromium",
        base64::internal::chromium::base64_is_b64,
        base64::internal::chromium::base64_encode_outl,
        base64::internal::chromium::base64_encode_strl,
        base64::internal::chromium::base64_decode_outl,
        base64::internal::chromium::base64_encode,
        base64::internal::chromium::base64_decode,
    },
#endif
    // universal
    {
        []() { return true; },
        "common",
        base64::internal::common::base64_is_b64,
        base64::internal::common::base64_encode_outl,
        base64::internal::common::base64_encode_strl,
        base64::internal::common::base64_decode_outl,
        base64::internal::common::base64_encode,
        base64::internal::common::base64_decode,
    },
    // end
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
};

static const Base64Provider* get_provider(const Base64Provider* providers,
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
    std::printf("[BASE64 PROVIDER] Provider %s is not available. %s:%d\n",
                name ? name : "", __FILE__, __LINE__);
    std::exit(-1);
}

#define BASE64_PROVIDER get_provider(base64_providers)

bool base64_is_b64(const char* in, std::size_t inl) noexcept
{
    return BASE64_PROVIDER->is_b64(in, inl);
}

std::size_t base64_encode_outl(std::size_t inl) noexcept
{
    return BASE64_PROVIDER->encode_outl(inl);
}

std::size_t base64_encode_strl(std::size_t inl) noexcept
{
    return BASE64_PROVIDER->encode_strl(inl);
}

std::size_t base64_decode_outl(const char* in, std::size_t inl) noexcept
{
    return BASE64_PROVIDER->decode_outl(in, inl);
}

void base64_encode(char* out, const std::uint8_t* in, std::size_t inl) noexcept
{
    return BASE64_PROVIDER->encode(out, in, inl);
}

int base64_decode(std::uint8_t* out, const char* in, std::size_t inl) noexcept
{
    return BASE64_PROVIDER->decode(out, in, inl);
}

}; // namespace base64