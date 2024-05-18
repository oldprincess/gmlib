#ifndef MEMORY_UTILS_MEMXOR_H
#define MEMORY_UTILS_MEMXOR_H

#include <cstddef>
#include <cstdint>

#if defined(CPU_FLAG_SSE2) || defined(CPU_FLAG_AVX2)

#include <immintrin.h>

#endif

namespace memory_utils {

namespace internal {

#if defined(CPU_FLAG_AVX2)
namespace avx2 {

static inline void memxor512(std::uint8_t       out[512],
                             const std::uint8_t in1[512],
                             const std::uint8_t in2[512]) noexcept
{
    __m256i a0  = _mm256_loadu_si256((const __m256i *)(in1 + 0));
    __m256i a1  = _mm256_loadu_si256((const __m256i *)(in1 + 32));
    __m256i a2  = _mm256_loadu_si256((const __m256i *)(in1 + 64));
    __m256i a3  = _mm256_loadu_si256((const __m256i *)(in1 + 96));
    __m256i a4  = _mm256_loadu_si256((const __m256i *)(in1 + 128));
    __m256i a5  = _mm256_loadu_si256((const __m256i *)(in1 + 160));
    __m256i a6  = _mm256_loadu_si256((const __m256i *)(in1 + 192));
    __m256i a7  = _mm256_loadu_si256((const __m256i *)(in1 + 224));
    __m256i a8  = _mm256_loadu_si256((const __m256i *)(in1 + 256));
    __m256i a9  = _mm256_loadu_si256((const __m256i *)(in1 + 288));
    __m256i a10 = _mm256_loadu_si256((const __m256i *)(in1 + 320));
    __m256i a11 = _mm256_loadu_si256((const __m256i *)(in1 + 352));
    __m256i a12 = _mm256_loadu_si256((const __m256i *)(in1 + 384));
    __m256i a13 = _mm256_loadu_si256((const __m256i *)(in1 + 416));
    __m256i a14 = _mm256_loadu_si256((const __m256i *)(in1 + 448));
    __m256i a15 = _mm256_loadu_si256((const __m256i *)(in1 + 480));
    __m256i c0 =
        _mm256_xor_si256(a0, _mm256_loadu_si256((const __m256i *)(in2 + 0)));
    __m256i c1 =
        _mm256_xor_si256(a1, _mm256_loadu_si256((const __m256i *)(in2 + 32)));
    __m256i c2 =
        _mm256_xor_si256(a2, _mm256_loadu_si256((const __m256i *)(in2 + 64)));
    __m256i c3 =
        _mm256_xor_si256(a3, _mm256_loadu_si256((const __m256i *)(in2 + 96)));
    __m256i c4 =
        _mm256_xor_si256(a4, _mm256_loadu_si256((const __m256i *)(in2 + 128)));
    __m256i c5 =
        _mm256_xor_si256(a5, _mm256_loadu_si256((const __m256i *)(in2 + 160)));
    __m256i c6 =
        _mm256_xor_si256(a6, _mm256_loadu_si256((const __m256i *)(in2 + 192)));
    __m256i c7 =
        _mm256_xor_si256(a7, _mm256_loadu_si256((const __m256i *)(in2 + 224)));
    __m256i c8 =
        _mm256_xor_si256(a8, _mm256_loadu_si256((const __m256i *)(in2 + 256)));
    __m256i c9 =
        _mm256_xor_si256(a9, _mm256_loadu_si256((const __m256i *)(in2 + 288)));
    __m256i c10 =
        _mm256_xor_si256(a10, _mm256_loadu_si256((const __m256i *)(in2 + 320)));
    __m256i c11 =
        _mm256_xor_si256(a11, _mm256_loadu_si256((const __m256i *)(in2 + 352)));
    __m256i c12 =
        _mm256_xor_si256(a12, _mm256_loadu_si256((const __m256i *)(in2 + 384)));
    __m256i c13 =
        _mm256_xor_si256(a13, _mm256_loadu_si256((const __m256i *)(in2 + 416)));
    __m256i c14 =
        _mm256_xor_si256(a14, _mm256_loadu_si256((const __m256i *)(in2 + 448)));
    __m256i c15 =
        _mm256_xor_si256(a15, _mm256_loadu_si256((const __m256i *)(in2 + 480)));
    _mm256_storeu_si256((__m256i *)(out + 0), c0);
    _mm256_storeu_si256((__m256i *)(out + 32), c1);
    _mm256_storeu_si256((__m256i *)(out + 64), c2);
    _mm256_storeu_si256((__m256i *)(out + 96), c3);
    _mm256_storeu_si256((__m256i *)(out + 128), c4);
    _mm256_storeu_si256((__m256i *)(out + 160), c5);
    _mm256_storeu_si256((__m256i *)(out + 192), c6);
    _mm256_storeu_si256((__m256i *)(out + 224), c7);
    _mm256_storeu_si256((__m256i *)(out + 256), c8);
    _mm256_storeu_si256((__m256i *)(out + 288), c9);
    _mm256_storeu_si256((__m256i *)(out + 320), c10);
    _mm256_storeu_si256((__m256i *)(out + 352), c11);
    _mm256_storeu_si256((__m256i *)(out + 384), c12);
    _mm256_storeu_si256((__m256i *)(out + 416), c13);
    _mm256_storeu_si256((__m256i *)(out + 448), c14);
    _mm256_storeu_si256((__m256i *)(out + 480), c15);
}

static inline void memxor256(std::uint8_t       out[256],
                             const std::uint8_t in1[256],
                             const std::uint8_t in2[256]) noexcept
{
    __m256i a0 = _mm256_loadu_si256((const __m256i *)(in1 + 0));
    __m256i a1 = _mm256_loadu_si256((const __m256i *)(in1 + 32));
    __m256i a2 = _mm256_loadu_si256((const __m256i *)(in1 + 64));
    __m256i a3 = _mm256_loadu_si256((const __m256i *)(in1 + 96));
    __m256i a4 = _mm256_loadu_si256((const __m256i *)(in1 + 128));
    __m256i a5 = _mm256_loadu_si256((const __m256i *)(in1 + 160));
    __m256i a6 = _mm256_loadu_si256((const __m256i *)(in1 + 192));
    __m256i a7 = _mm256_loadu_si256((const __m256i *)(in1 + 224));
    __m256i c0 =
        _mm256_xor_si256(a0, _mm256_loadu_si256((const __m256i *)(in2 + 0)));
    __m256i c1 =
        _mm256_xor_si256(a1, _mm256_loadu_si256((const __m256i *)(in2 + 32)));
    __m256i c2 =
        _mm256_xor_si256(a2, _mm256_loadu_si256((const __m256i *)(in2 + 64)));
    __m256i c3 =
        _mm256_xor_si256(a3, _mm256_loadu_si256((const __m256i *)(in2 + 96)));
    __m256i c4 =
        _mm256_xor_si256(a4, _mm256_loadu_si256((const __m256i *)(in2 + 128)));
    __m256i c5 =
        _mm256_xor_si256(a5, _mm256_loadu_si256((const __m256i *)(in2 + 160)));
    __m256i c6 =
        _mm256_xor_si256(a6, _mm256_loadu_si256((const __m256i *)(in2 + 192)));
    __m256i c7 =
        _mm256_xor_si256(a7, _mm256_loadu_si256((const __m256i *)(in2 + 224)));
    _mm256_storeu_si256((__m256i *)(out + 0), c0);
    _mm256_storeu_si256((__m256i *)(out + 32), c1);
    _mm256_storeu_si256((__m256i *)(out + 64), c2);
    _mm256_storeu_si256((__m256i *)(out + 96), c3);
    _mm256_storeu_si256((__m256i *)(out + 128), c4);
    _mm256_storeu_si256((__m256i *)(out + 160), c5);
    _mm256_storeu_si256((__m256i *)(out + 192), c6);
    _mm256_storeu_si256((__m256i *)(out + 224), c7);
}

static inline void memxor128(std::uint8_t       out[128],
                             const std::uint8_t in1[128],
                             const std::uint8_t in2[128]) noexcept
{
    __m256i a0 = _mm256_loadu_si256((const __m256i *)(in1 + 0));
    __m256i a1 = _mm256_loadu_si256((const __m256i *)(in1 + 32));
    __m256i a2 = _mm256_loadu_si256((const __m256i *)(in1 + 64));
    __m256i a3 = _mm256_loadu_si256((const __m256i *)(in1 + 96));
    __m256i c0 =
        _mm256_xor_si256(a0, _mm256_loadu_si256((const __m256i *)(in2 + 0)));
    __m256i c1 =
        _mm256_xor_si256(a1, _mm256_loadu_si256((const __m256i *)(in2 + 32)));
    __m256i c2 =
        _mm256_xor_si256(a2, _mm256_loadu_si256((const __m256i *)(in2 + 64)));
    __m256i c3 =
        _mm256_xor_si256(a3, _mm256_loadu_si256((const __m256i *)(in2 + 96)));
    _mm256_storeu_si256((__m256i *)(out + 0), c0);
    _mm256_storeu_si256((__m256i *)(out + 32), c1);
    _mm256_storeu_si256((__m256i *)(out + 64), c2);
    _mm256_storeu_si256((__m256i *)(out + 96), c3);
}

static inline void memxor64(std::uint8_t       out[64],
                            const std::uint8_t in1[64],
                            const std::uint8_t in2[64]) noexcept
{
    __m256i a0 = _mm256_loadu_si256((const __m256i *)(in1 + 0));
    __m256i a1 = _mm256_loadu_si256((const __m256i *)(in1 + 32));
    __m256i c0 =
        _mm256_xor_si256(a0, _mm256_loadu_si256((const __m256i *)(in2 + 0)));
    __m256i c1 =
        _mm256_xor_si256(a1, _mm256_loadu_si256((const __m256i *)(in2 + 32)));
    _mm256_storeu_si256((__m256i *)(out + 0), c0);
    _mm256_storeu_si256((__m256i *)(out + 32), c1);
}

static inline void memxor32(std::uint8_t       out[32],
                            const std::uint8_t in1[32],
                            const std::uint8_t in2[32]) noexcept
{
    __m256i a0 = _mm256_loadu_si256((const __m256i *)(in1 + 0));
    __m256i c0 =
        _mm256_xor_si256(a0, _mm256_loadu_si256((const __m256i *)(in2 + 0)));
    _mm256_storeu_si256((__m256i *)(out + 0), c0);
}

}; // namespace avx2
#endif

#if defined(CPU_FLAG_SSE2)
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
#endif

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

template <std::size_t SIZE>
static inline void memxor(void *out, const void *in1, const void *in2) noexcept
{
    std::uint8_t       *out_ptr = static_cast<std::uint8_t *>(out);
    const std::uint8_t *in1_ptr = static_cast<const std::uint8_t *>(in1);
    const std::uint8_t *in2_ptr = static_cast<const std::uint8_t *>(in2);
    if constexpr (SIZE >= 512)
    {
#if defined(CPU_FLAG_AVX2)
        for (std::size_t i = 0; i < SIZE / 512; i++)
        {
            internal::avx2::memxor512(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 512, in1_ptr += 512, in2_ptr += 512;
        }
        memxor<SIZE % 512>(out_ptr, in1_ptr, in2_ptr);
        return;
#endif
    }
    if constexpr (SIZE >= 256)
    {
#if defined(CPU_FLAG_AVX2)
        for (std::size_t i = 0; i < SIZE / 256; i++)
        {
            internal::avx2::memxor256(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 256, in1_ptr += 256, in2_ptr += 256;
        }
        memxor<SIZE % 256>(out_ptr, in1_ptr, in2_ptr);
        return;
#endif
    }
    if constexpr (SIZE >= 128)
    {
#if defined(CPU_FLAG_AVX2)
        for (std::size_t i = 0; i < SIZE / 128; i++)
        {
            internal::avx2::memxor128(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 128, in1_ptr += 128, in2_ptr += 128;
        }
        memxor<SIZE % 128>(out_ptr, in1_ptr, in2_ptr);
        return;
#elif defined(CPU_FLAG_SSE2)
        for (std::size_t i = 0; i < SIZE / 128; i++)
        {
            internal::sse2::memxor128(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 128, in1_ptr += 128, in2_ptr += 128;
        }
        memxor<SIZE % 128>(out_ptr, in1_ptr, in2_ptr);
        return;
#endif
    }
    if constexpr (SIZE >= 64)
    {
#if defined(CPU_FLAG_AVX2)
        for (std::size_t i = 0; i < SIZE / 64; i++)
        {
            internal::avx2::memxor64(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 64, in1_ptr += 64, in2_ptr += 64;
        }
        memxor<SIZE % 64>(out_ptr, in1_ptr, in2_ptr);
        return;
#elif defined(CPU_FLAG_SSE2)
        for (std::size_t i = 0; i < SIZE / 64; i++)
        {
            internal::sse2::memxor64(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 64, in1_ptr += 64, in2_ptr += 64;
        }
        memxor<SIZE % 64>(out_ptr, in1_ptr, in2_ptr);
        return;
#endif
    }
    if constexpr (SIZE >= 32)
    {
#if defined(CPU_FLAG_AVX2)
        for (std::size_t i = 0; i < SIZE / 32; i++)
        {
            internal::avx2::memxor32(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 32, in1_ptr += 32, in2_ptr += 32;
        }
        memxor<SIZE % 32>(out_ptr, in1_ptr, in2_ptr);
        return;
#elif defined(CPU_FLAG_SSE2)
        for (std::size_t i = 0; i < SIZE / 32; i++)
        {
            internal::sse2::memxor32(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 32, in1_ptr += 32, in2_ptr += 32;
        }
        memxor<SIZE % 32>(out_ptr, in1_ptr, in2_ptr);
        return;
#endif
    }
    if constexpr (SIZE >= 16)
    {
#if defined(CPU_FLAG_SSE2)
        for (std::size_t i = 0; i < SIZE / 16; i++)
        {
            internal::sse2::memxor16(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 16, in1_ptr += 16, in2_ptr += 16;
        }
        memxor<SIZE % 16>(out_ptr, in1_ptr, in2_ptr);
        return;
#endif
    }
    if constexpr (SIZE >= 8)
    {
        for (std::size_t i = 0; i < SIZE / 8; i++)
        {
            internal::memxor8(out_ptr, in1_ptr, in2_ptr);
            out_ptr += 8, in1_ptr += 8, in2_ptr += 8;
        }
        memxor<SIZE % 8>(out_ptr, in1_ptr, in2_ptr);
        return;
    }
    if constexpr (SIZE >= 4)
    {
        internal::memxor4(out_ptr, in1_ptr, in2_ptr);
        memxor<SIZE - 4>(out_ptr + 4, in1_ptr + 4, in2_ptr + 4);
        return;
    }
    if constexpr (SIZE >= 2)
    {
        internal::memxor2(out_ptr, in1_ptr, in2_ptr);
        memxor<SIZE - 2>(out_ptr + 2, in1_ptr + 2, in2_ptr + 2);
        return;
    }
    if constexpr (SIZE >= 1)
    {
        internal::memxor1(out_ptr, in1_ptr, in2_ptr);
        memxor<SIZE - 1>(out_ptr + 1, in1_ptr + 1, in2_ptr + 1);
        return;
    }
}

inline void memxor_n(void       *out,
                     const void *in1,
                     const void *in2,
                     std::size_t size) noexcept
{
    std::uint8_t       *out_ptr = static_cast<std::uint8_t *>(out);
    const std::uint8_t *in1_ptr = static_cast<const std::uint8_t *>(in1);
    const std::uint8_t *in2_ptr = static_cast<const std::uint8_t *>(in2);
#if defined(CPU_FLAG_AVX2)
    while (size >= 512)
    {
        internal::avx2::memxor512(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 512, in1_ptr += 512, in2_ptr += 512, size -= 512;
    }
#endif

#if defined(CPU_FLAG_AVX2)
    while (size >= 256)
    {
        internal::avx2::memxor256(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 256, in1_ptr += 256, in2_ptr += 256, size -= 256;
    }
#endif

#if defined(CPU_FLAG_AVX2)
    while (size >= 128)
    {
        internal::avx2::memxor128(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 128, in1_ptr += 128, in2_ptr += 128, size -= 128;
    }
#elif defined(CPU_FLAG_SSE2)
    while (size >= 128)
    {
        internal::sse2::memxor128(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 128, in1_ptr += 128, in2_ptr += 128, size -= 128;
    }
#endif

#if defined(CPU_FLAG_AVX2)
    while (size >= 64)
    {
        internal::avx2::memxor64(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 64, in1_ptr += 64, in2_ptr += 64, size -= 64;
    }
#elif defined(CPU_FLAG_SSE2)
    while (size >= 64)
    {
        internal::sse2::memxor64(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 64, in1_ptr += 64, in2_ptr += 64, size -= 64;
    }
#endif

#if defined(CPU_FLAG_AVX2)
    while (size >= 32)
    {
        internal::avx2::memxor32(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 32, in1_ptr += 32, in2_ptr += 32, size -= 32;
    }
#elif defined(CPU_FLAG_SSE2)
    while (size >= 32)
    {
        internal::sse2::memxor32(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 32, in1_ptr += 32, in2_ptr += 32, size -= 32;
    }
#endif

#if defined(CPU_FLAG_SSE2)
    while (size >= 16)
    {
        internal::sse2::memxor16(out_ptr, in1_ptr, in2_ptr);
        out_ptr += 16, in1_ptr += 16, in2_ptr += 16, size -= 16;
    }
#endif

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