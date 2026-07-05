#if defined(SUPPORT_MEMXOR_SSE2)

#ifndef MEMXOR_SSE2_H
#define MEMXOR_SSE2_H

#include <cstddef>
#include <cstdint>

namespace memory_utils {
namespace sse2 {

void memxor_n(void       *out,
              const void *in1,
              const void *in2,
              std::size_t size) noexcept;

}
} // namespace memory_utils

#endif

#endif
