#ifndef MEMORY_UTILS_MEMXOR_H
#define MEMORY_UTILS_MEMXOR_H

#include <cstddef>
#include <cstdint>

namespace memory_utils {

void memxor_n(void       *out,
              const void *in1,
              const void *in2,
              std::size_t size) noexcept;

template <std::size_t SIZE>
static inline void memxor(void *out, const void *in1, const void *in2) noexcept
{
    memxor_n(out, in1, in2, SIZE);
}

} // namespace memory_utils

#endif