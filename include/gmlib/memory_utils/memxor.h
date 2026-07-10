#ifndef MEMORY_UTILS_MEMXOR_H
#define MEMORY_UTILS_MEMXOR_H

#include <cstddef>
#include <cstdint>

namespace memory_utils {

static inline void memxor_n(void       *out,
                            const void *in1,
                            const void *in2,
                            std::size_t size) noexcept
{
    std::uint8_t       *out_ptr = static_cast<std::uint8_t *>(out);
    const std::uint8_t *in1_ptr = static_cast<const std::uint8_t *>(in1);
    const std::uint8_t *in2_ptr = static_cast<const std::uint8_t *>(in2);

    for (std::size_t i = 0; i < size; i++)
    {
        out_ptr[i] = in1_ptr[i] ^ in2_ptr[i];
    }
}

/**
 * @deprecated Use memxor_n() instead
 */
template <std::size_t SIZE>
static inline void memxor(void *out, const void *in1, const void *in2) noexcept
{
    memxor_n(out, in1, in2, SIZE);
}

} // namespace memory_utils

#endif
