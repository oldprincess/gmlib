#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/memory_utils/memxor.h>

#if defined(__AVX2__)
#include "memxor_avx2.h"
#endif
#if defined(__SSE2__)
#include "memxor_sse2.h"
#endif

#include "memxor_common.h"

namespace memory_utils {

typedef void (*memxor_n_t)(void       *out,
                           const void *in1,
                           const void *in2,
                           std::size_t size) noexcept;

static memxor_n_t fetch_impl()
{
#if defined(__AVX2__)
    if (cpuinfo::x86_64::cpu_supports_avx2())
    {
        return avx2::memxor_n;
    }
    else
#elif defined(__SSE2__)
    if (cpuinfo::x86_64::cpu_supports_sse2())
    {
        return sse2::memxor_n;
    }
    else
#endif
    {
        return common::memxor_n;
    }
}

void memxor_n(void       *out,
              const void *in1,
              const void *in2,
              std::size_t size) noexcept
{
    static memxor_n_t impl = fetch_impl();
    impl(out, in1, in2, size);
}

} // namespace memory_utils
