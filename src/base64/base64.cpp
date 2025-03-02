#include <gmlib/base64/base64.h>

#if defined(CPU_FLAG_AVX2)
#include "base64_avx2.h"
namespace alg = base64::internal::avx2;
#elif defined(SUPPORT_BASE64_CHROMIUM)
#include "base64_chromium.h"
namespace alg = base64::internal::chromium;
#else
#include "base64_common.h"
namespace alg = base64::internal::common;
#endif

namespace base64 {
bool base64_is_b64(const char* in, std::size_t inl) noexcept
{
    return alg::base64_is_b64(in, inl);
}

std::size_t base64_encode_outl(std::size_t inl) noexcept
{
    return alg::base64_encode_outl(inl);
}

std::size_t base64_encode_strl(std::size_t inl) noexcept
{
    return alg::base64_encode_strl(inl);
}

std::size_t base64_decode_outl(const char* in, std::size_t inl) noexcept
{
    return alg::base64_decode_outl(in, inl);
}

void base64_encode(char* out, const std::uint8_t* in, std::size_t inl) noexcept
{
    return alg::base64_encode(out, in, inl);
}

int base64_decode(std::uint8_t* out, const char* in, std::size_t inl) noexcept
{
    return alg::base64_decode(out, in, inl);
}

}; // namespace base64