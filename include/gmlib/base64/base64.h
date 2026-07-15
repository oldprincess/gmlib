#ifndef BASE64_BASE64_H
#define BASE64_BASE64_H

#include <gmlib/base64/provider.h>

namespace base64 {

static inline bool base64_is_b64(const char* in, std::size_t inl) noexcept
{
    return get_base64_provider(nullptr)->base64_is_b64(in, inl);
}

static inline std::size_t base64_encode_outl(std::size_t inl) noexcept
{
    return get_base64_provider(nullptr)->base64_encode_outl(inl);
}

static inline std::size_t base64_encode_strl(std::size_t inl) noexcept
{
    return get_base64_provider(nullptr)->base64_encode_strl(inl);
}

static inline std::size_t base64_decode_outl(const char* in,
                                             std::size_t inl) noexcept
{
    return get_base64_provider(nullptr)->base64_decode_outl(in, inl);
}

static inline void base64_encode(char*               out,
                                 const std::uint8_t* in,
                                 std::size_t         inl) noexcept
{
    get_base64_provider(nullptr)->base64_encode(out, in, inl);
}

static inline int base64_decode(std::uint8_t* out,
                                const char*   in,
                                std::size_t   inl) noexcept
{
    return get_base64_provider(nullptr)->base64_decode(out, in, inl);
}

} // namespace base64

#endif
