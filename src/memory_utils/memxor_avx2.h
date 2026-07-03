#if defined(MEMXOR_IMPL_AVX2)

#ifndef MEMXOR_AVX2_H
#define MEMXOR_AVX2_H

#include <cstddef>
#include <cstdint>

namespace memory_utils {
namespace avx2 {

void memxor_n(void       *out,
              const void *in1,
              const void *in2,
              std::size_t size) noexcept;

} // namespace avx2
} // namespace memory_utils

#endif

#endif
