#if defined(__SSE2__)

#ifndef MEMXOR_SSE2_H
#define MEMXOR_SSE2_H

#include <cstddef>
#include <cstdint>

namespace memory_utils {

void sse2_memxor_n(void       *out,
                   const void *in1,
                   const void *in2,
                   std::size_t size) noexcept;

}

#endif

#endif