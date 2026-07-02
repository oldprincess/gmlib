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

#if defined(BASE64_IMPL_AVX2)
namespace internal::avx2 {
bool available()
{
    return cpuinfo::x86_64::cpu_supports_avx2();
}
} // namespace internal::avx2
#endif

#if defined(BASE64_IMPL_CHROMIUM)
namespace internal::chromium {
bool available()
{
    return true;
}
} // namespace internal::chromium
#endif

#if defined(BASE64_IMPL_COMMON)
namespace internal::common {
bool available()
{
    return true;
}
} // namespace internal::common
#endif

bool base64_is_b64(const char* in, std::size_t inl) noexcept
{
#if defined(BASE64_IMPL_AVX2)
    if (internal::avx2::available())
    {
        return internal::avx2::base64_is_b64(in, inl);
    }
#endif
#if defined(BASE64_IMPL_CHROMIUM)
    if (internal::chromium::available())
    {
        return internal::chromium::base64_is_b64(in, inl);
    }
#endif
    {
        return internal::common::base64_is_b64(in, inl);
    }
}

std::size_t base64_encode_outl(std::size_t inl) noexcept
{
#if defined(BASE64_IMPL_AVX2)
    if (internal::avx2::available())
    {
        return internal::avx2::base64_encode_outl(inl);
    }
#endif
#if defined(BASE64_IMPL_CHROMIUM)
    if (internal::chromium::available())
    {
        return internal::chromium::base64_encode_outl(inl);
    }
#endif
    {
        return internal::common::base64_encode_outl(inl);
    }
}

std::size_t base64_encode_strl(std::size_t inl) noexcept
{
#if defined(BASE64_IMPL_AVX2)
    if (internal::avx2::available())
    {
        return internal::avx2::base64_encode_strl(inl);
    }
#endif
#if defined(BASE64_IMPL_CHROMIUM)
    if (internal::chromium::available())
    {
        return internal::chromium::base64_encode_strl(inl);
    }
#endif
    {
        return internal::common::base64_encode_strl(inl);
    }
}

std::size_t base64_decode_outl(const char* in, std::size_t inl) noexcept
{
#if defined(BASE64_IMPL_AVX2)
    if (internal::avx2::available())
    {
        return internal::avx2::base64_decode_outl(in, inl);
    }
#endif
#if defined(BASE64_IMPL_CHROMIUM)
    if (internal::chromium::available())
    {
        return internal::chromium::base64_decode_outl(in, inl);
    }
#endif
    {
        return internal::common::base64_decode_outl(in, inl);
    }
}

void base64_encode(char* out, const std::uint8_t* in, std::size_t inl) noexcept
{
#if defined(BASE64_IMPL_AVX2)
    if (internal::avx2::available())
    {
        internal::avx2::base64_encode(out, in, inl);
        return;
    }
#endif
#if defined(BASE64_IMPL_CHROMIUM)
    if (internal::chromium::available())
    {
        internal::chromium::base64_encode(out, in, inl);
        return;
    }
#endif
    {
        internal::common::base64_encode(out, in, inl);
        return;
    }
}

int base64_decode(std::uint8_t* out, const char* in, std::size_t inl) noexcept
{
#if defined(BASE64_IMPL_AVX2)
    if (internal::avx2::available())
    {
        return internal::avx2::base64_decode(out, in, inl);
    }
#endif
#if defined(BASE64_IMPL_CHROMIUM)
    if (internal::chromium::available())
    {
        return internal::chromium::base64_decode(out, in, inl);
    }
#endif
    {
        return internal::common::base64_decode(out, in, inl);
    }
}

}; // namespace base64