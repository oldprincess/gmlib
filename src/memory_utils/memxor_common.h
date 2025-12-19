#ifndef MEMXOR_COMMON_H
#define MEMXOR_COMMON_H

#include <cstddef>
#include <cstdint>

namespace memory_utils {
namespace common {

void memxor_n(void       *out,
              const void *in1,
              const void *in2,
              std::size_t size) noexcept;

} // namespace common
} // namespace memory_utils

#endif