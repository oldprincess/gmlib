#if defined(__SSE2__)

#include "memxor_sse2.h"

#include <immintrin.h>

namespace memory_utils {

namespace internal {

namespace sse2 {

static inline void memxor128(std::uint8_t       out[128],
                             const std::uint8_t in1[128],
                             const std::uint8_t in2[128]) noexcept
{
    __m128i a0 = _mm_loadu_si128((const __m128i *)(in1 + 0));
    __m128i a1 = _mm_loadu_si128((const __m128i *)(in1 + 16));
    __m128i a2 = _mm_loadu_si128((const __m128i *)(in1 + 32));
    __m128i a3 = _mm_loadu_si128((const __m128i *)(in1 + 48));
    __m128i a4 = _mm_loadu_si128((const __m128i *)(in1 + 64));
    __m128i a5 = _mm_loadu_si128((const __m128i *)(in1 + 80));
    __m128i a6 = _mm_loadu_si128((const __m128i *)(in1 + 96));
    __m128i a7 = _mm_loadu_si128((const __m128i *)(in1 + 112));
    __m128i c0 = _mm_xor_si128(a0, _mm_loadu_si128((const __m128i *)(in2 + 0)));
    __m128i c1 =
        _mm_xor_si128(a1, _mm_loadu_si128((const __m128i *)(in2 + 16)));
    __m128i c2 =
        _mm_xor_si128(a2, _mm_loadu_si128((const __m128i *)(in2 + 32)));
    __m128i c3 =
        _mm_xor_si128(a3, _mm_loadu_si128((const __m128i *)(in2 + 48)));
    __m128i c4 =
        _mm_xor_si128(a4, _mm_loadu_si128((const __m128i *)(in2 + 64)));
    __m128i c5 =
        _mm_xor_si128(a5, _mm_loadu_si128((const __m128i *)(in2 + 80)));
    __m128i c6 =
        _mm_xor_si128(a6, _mm_loadu_si128((const __m128i *)(in2 + 96)));
    __m128i c7 =
        _mm_xor_si128(a7, _mm_loadu_si128((const __m128i *)(in2 + 112)));
    _mm_storeu_si128((__m128i *)(out + 0), c0);
    _mm_storeu_si128((__m128i *)(out + 16), c1);
    _mm_storeu_si128((__m128i *)(out + 32), c2);
    _mm_storeu_si128((__m128i *)(out + 48), c3);
    _mm_storeu_si128((__m128i *)(out + 64), c4);
    _mm_storeu_si128((__m128i *)(out + 80), c5);
    _mm_storeu_si128((__m128i *)(out + 96), c6);
    _mm_storeu_si128((__m128i *)(out + 112), c7);
}

static inline void memxor64(std::uint8_t       out[64],
                            const std::uint8_t in1[64],
                            const std::uint8_t in2[64]) noexcept
{
    __m128i a0 = _mm_loadu_si128((const __m128i *)(in1 + 0));
    __m128i a1 = _mm_loadu_si128((const __m128i *)(in1 + 16));
    __m128i a2 = _mm_loadu_si128((const __m128i *)(in1 + 32));
    __m128i a3 = _mm_loadu_si128((const __m128i *)(in1 + 48));
    __m128i c0 = _mm_xor_si128(a0, _mm_loadu_si128((const __m128i *)(in2 + 0)));
    __m128i c1 =
        _mm_xor_si128(a1, _mm_loadu_si128((const __m128i *)(in2 + 16)));
    __m128i c2 =
        _mm_xor_si128(a2, _mm_loadu_si128((const __m128i *)(in2 + 32)));
    __m128i c3 =
        _mm_xor_si128(a3, _mm_loadu_si128((const __m128i *)(in2 + 48)));
    _mm_storeu_si128((__m128i *)(out + 0), c0);
    _mm_storeu_si128((__m128i *)(out + 16), c1);
    _mm_storeu_si128((__m128i *)(out + 32), c2);
    _mm_storeu_si128((__m128i *)(out + 48), c3);
}

static inline void memxor32(std::uint8_t       out[32],
                            const std::uint8_t in1[32],
                            const std::uint8_t in2[32]) noexcept
{
    __m128i a0 = _mm_loadu_si128((const __m128i *)(in1 + 0));
    __m128i a1 = _mm_loadu_si128((const __m128i *)(in1 + 16));
    __m128i c0 = _mm_xor_si128(a0, _mm_loadu_si128((const __m128i *)(in2 + 0)));
    __m128i c1 =
        _mm_xor_si128(a1, _mm_loadu_si128((const __m128i *)(in2 + 16)));
    _mm_storeu_si128((__m128i *)(out + 0), c0);
    _mm_storeu_si128((__m128i *)(out + 16), c1);
}

static inline void memxor16(std::uint8_t       out[16],
                            const std::uint8_t in1[16],
                            const std::uint8_t in2[16]) noexcept
{
    __m128i a0 = _mm_loadu_si128((const __m128i *)(in1 + 0));
    __m128i c0 = _mm_xor_si128(a0, _mm_loadu_si128((const __m128i *)(in2 + 0)));
    _mm_storeu_si128((__m128i *)(out + 0), c0);
}

}; // namespace sse2

static inline void memxor8(std::uint8_t       out[8],
                           const std::uint8_t in1[8],
                           const std::uint8_t in2[8]) noexcept
{
    std::uint64_t *out_ptr = (std::uint64_t *)(out);
    std::uint64_t *in1_ptr = (std::uint64_t *)(in1);
    std::uint64_t *in2_ptr = (std::uint64_t *)(in2);
    out_ptr[0]             = in1_ptr[0] ^ in2_ptr[0];
}

static inline void memxor4(std::uint8_t       out[4],
                           const std::uint8_t in1[4],
                           const std::uint8_t in2[4]) noexcept
{
    std::uint32_t *out_ptr = (std::uint32_t *)(out);
    std::uint32_t *in1_ptr = (std::uint32_t *)(in1);
    std::uint32_t *in2_ptr = (std::uint32_t *)(in2);
    out_ptr[0]             = in1_ptr[0] ^ in2_ptr[0];
}

static inline void memxor2(std::uint8_t       out[2],
                           const std::uint8_t in1[2],
                           const std::uint8_t in2[2]) noexcept
{
    std::uint16_t *out_ptr = (std::uint16_t *)(out);
    std::uint16_t *in1_ptr = (std::uint16_t *)(in1);
    std::uint16_t *in2_ptr = (std::uint16_t *)(in2);
    out_ptr[0]             = in1_ptr[0] ^ in2_ptr[0];
}

static inline void memxor1(std::uint8_t       out[1],
                           const std::uint8_t in1[1],
                           const std::uint8_t in2[1]) noexcept
{
    out[0] = in1[0] ^ in2[0];
}

} // namespace internal

} // namespace memory_utils

namespace memory_utils {

void sse2_memxor_n(void       *out,
                   const void *in1,
                   const void *in2,
                   std::size_t size) noexcept
{
    std::uint8_t       *out_ptr = static_cast<std::uint8_t *>(out);
    const std::uint8_t *in1_ptr = static_cast<const std::uint8_t *>(in1);
    const std::uint8_t *in2_ptr = static_cast<const std::uint8_t *>(in2);

    while (size >= 128)
    {
        internal::sse2::memxor128(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 128, in1_ptr += 128, in2_ptr += 128, size -= 128;
    }

    while (size >= 64)
    {
        internal::sse2::memxor64(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 64, in1_ptr += 64, in2_ptr += 64, size -= 64;
    }

    while (size >= 32)
    {
        internal::sse2::memxor32(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 32, in1_ptr += 32, in2_ptr += 32, size -= 32;
    }

    while (size >= 16)
    {
        internal::sse2::memxor16(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 16, in1_ptr += 16, in2_ptr += 16, size -= 16;
    }

    while (size >= 8)
    {
        internal::memxor8(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 8, in1_ptr += 8, in2_ptr += 8, size -= 8;
    }

    while (size >= 4)
    {
        internal::memxor4(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 4, in1_ptr += 4, in2_ptr += 4, size -= 4;
    }

    while (size >= 2)
    {
        internal::memxor2(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 2, in1_ptr += 2, in2_ptr += 2, size -= 2;
    }

    while (size >= 1)
    {
        internal::memxor1(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 1, in1_ptr += 1, in2_ptr += 1, size -= 1;
    }
}

} // namespace memory_utils

#endif