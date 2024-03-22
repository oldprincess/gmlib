#include <gmlib/memory_utils/memxor.h>

namespace memory_utils {

void memxor_n(void       *out,
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
