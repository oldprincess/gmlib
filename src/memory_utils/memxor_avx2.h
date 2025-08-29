#if defined(__AVX2__)

#ifndef MEMXOR_AVX2_H
#define MEMXOR_AVX2_H

#include <cstddef>
#include <cstdint>

namespace memory_utils {

void avx2_memxor_n(void       *out,
                   const void *in1,
                   const void *in2,
                   std::size_t size) noexcept;

}

#endif

#endif