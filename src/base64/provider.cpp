#include <gmlib/base64/base64.h>
#include <gmlib/cpuinfo/cpuinfo.h>

#include "base64_avx2.h"
#include "base64_chromium.h"
#include "base64_common.h"

namespace base64 {

struct Provider
{
    decltype(&internal::common::base64_is_b64)      is_b64;
    decltype(&internal::common::base64_encode_outl) encode_outl;
    decltype(&internal::common::base64_encode_strl) encode_strl;
    decltype(&internal::common::base64_decode_outl) decode_outl;
    decltype(&internal::common::base64_encode)      encode;
    decltype(&internal::common::base64_decode)      decode;
};

static Provider create_provider() noexcept
{
#if defined(BASE64_IMPL_AVX2)
    if (cpuinfo::x86_64::cpu_supports_avx2())
    {
        return {
            internal::avx2::base64_is_b64,
            internal::avx2::base64_encode_outl,
            internal::avx2::base64_encode_strl,
            internal::avx2::base64_decode_outl,
            internal::avx2::base64_encode,
            internal::avx2::base64_decode,
        };
    }
#endif
#if defined(BASE64_IMPL_CHROMIUM)
    return {
        internal::chromium::base64_is_b64,
        internal::chromium::base64_encode_outl,
        internal::chromium::base64_encode_strl,
        internal::chromium::base64_decode_outl,
        internal::chromium::base64_encode,
        internal::chromium::base64_decode,
    };
#else
    return {
        internal::common::base64_is_b64,
        internal::common::base64_encode_outl,
        internal::common::base64_encode_strl,
        internal::common::base64_decode_outl,
        internal::common::base64_encode,
        internal::common::base64_decode,
    };
#endif
}

static const Provider& get_provider() noexcept
{
    static const Provider provider = create_provider();
    return provider;
}

bool base64_is_b64(const char* in, std::size_t inl) noexcept
{
    return get_provider().is_b64(in, inl);
}

std::size_t base64_encode_outl(std::size_t inl) noexcept
{
    return get_provider().encode_outl(inl);
}

std::size_t base64_encode_strl(std::size_t inl) noexcept
{
    return get_provider().encode_strl(inl);
}

std::size_t base64_decode_outl(const char* in, std::size_t inl) noexcept
{
    return get_provider().decode_outl(in, inl);
}

void base64_encode(char* out, const std::uint8_t* in, std::size_t inl) noexcept
{
    get_provider().encode(out, in, inl);
}

int base64_decode(std::uint8_t* out, const char* in, std::size_t inl) noexcept
{
    return get_provider().decode(out, in, inl);
}

}; // namespace base64
