#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/memory_utils/memxor.h>

#include "memxor_avx2.h"
#include "memxor_sse2.h"

namespace memory_utils {

void memxor_n(void       *out,
              const void *in1,
              const void *in2,
              std::size_t size) noexcept
{
#if defined(__AVX2__)
    if (cpuinfo::x86_64::cpu_supports_avx2())
    {
        avx2_memxor_n(out, in1, in2, size);
        return;
    }
    else
#elif defined(__SSE2__)
    if (cpuinfo::x86_64::cpu_supports_sse2())
    {
        sse2_memxor_n(out, in1, in2, size);
        return;
    }
    else
#endif

    {
        std::uint8_t       *out_ptr = (std::uint8_t *)(out);
        const std::uint8_t *in1_ptr = (const std::uint8_t *)(in1);
        const std::uint8_t *in2_ptr = (const std::uint8_t *)(in2);
        while (size >= 8)
        {
            ((std::uint64_t *)out_ptr)[0] =
                ((const std::uint64_t *)in1_ptr)[0] ^
                ((const std::uint64_t *)in2_ptr)[0];
            out_ptr += 8, in1_ptr += 8, in2_ptr += 8, size -= 8;
        }

        while (size >= 4)
        {
            ((std::uint32_t *)out_ptr)[0] =
                ((const std::uint32_t *)in1_ptr)[0] ^
                ((const std::uint32_t *)in2_ptr)[0];
            out_ptr += 4, in1_ptr += 4, in2_ptr += 4, size -= 4;
        }

        while (size >= 2)
        {
            ((std::uint16_t *)out_ptr)[0] =
                ((const std::uint16_t *)in1_ptr)[0] ^
                ((const std::uint16_t *)in2_ptr)[0];
            out_ptr += 2, in1_ptr += 2, in2_ptr += 2, size -= 2;
        }

        while (size >= 1)
        {
            out_ptr[0] = in1_ptr[0] ^ in2_ptr[0];
            out_ptr += 1, in1_ptr += 1, in2_ptr += 1, size -= 1;
        }
    }
}

} // namespace memory_utils
