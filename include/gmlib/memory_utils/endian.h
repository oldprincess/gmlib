#ifndef MEMORY_UTILS_ENDIAN_H
#define MEMORY_UTILS_ENDIAN_H

#include <cstdint>

#if defined(CPU_FLAG_MOVBE)

#include <immintrin.h>

#if defined(_MSC_VER)
#include <intrin.h>
#else

#define _loadbe_i16(ptr)     __builtin_bswap16(*(std::uint16_t *)(ptr))
#define _storebe_i16(ptr, a) *(std::uint16_t *)(ptr) = __builtin_bswap16(a)
#define _loadbe_i32(ptr)     __builtin_bswap32(*(std::uint32_t *)(ptr))
#define _storebe_i32(ptr, a) *(std::uint32_t *)(ptr) = __builtin_bswap32(a)
#define _loadbe_i64(ptr)     __builtin_bswap64(*(std::uint64_t *)(ptr))
#define _storebe_i64(ptr, a) *(std::uint64_t *)(ptr) = __builtin_bswap64(a)

#endif

#endif

namespace memory_utils {

static inline std::uint8_t load8_le(const void *src) noexcept
{
    return *static_cast<const std::uint8_t *>(src);
}

static inline std::uint16_t load16_le(const void *src) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    return *static_cast<const std::uint16_t *>(src);
#else
    const std::uint8_t *src_ptr = static_cast<const uint8_t *>(src);
    return ((std::uint16_t)src_ptr[1] << 8) | (std::uint16_t)src_ptr[0];
#endif
}

static inline std::uint32_t load32_le(const void *src) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    return *static_cast<const std::uint32_t *>(src);
#else
    const std::uint8_t *src_ptr = static_cast<const uint8_t *>(src);
    return ((std::uint32_t)src_ptr[3] << 24) |
           ((std::uint32_t)src_ptr[2] << 16) |
           ((std::uint32_t)src_ptr[1] << 8) | (std::uint32_t)src_ptr[0];
#endif
}

static inline std::uint64_t load64_le(const void *src) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    return *static_cast<const std::uint64_t *>(src);
#else
    const std::uint8_t *src_ptr = static_cast<const uint8_t *>(src);
    return ((std::uint64_t)src_ptr[7] << 56) |
           ((std::uint64_t)src_ptr[6] << 48) |
           ((std::uint64_t)src_ptr[5] << 40) |
           ((std::uint64_t)src_ptr[4] << 32) |
           ((std::uint64_t)src_ptr[3] << 24) |
           ((std::uint64_t)src_ptr[2] << 16) |
           ((std::uint64_t)src_ptr[1] << 8) | (std::uint64_t)src_ptr[0];
#endif
}

static inline std::uint8_t load8_be(const void *src) noexcept
{
    return *static_cast<const std::uint8_t *>(src);
}

static inline std::uint16_t load16_be(const void *src) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    return (std::uint16_t)_loadbe_i16(src);
#else
    const std::uint8_t *src_ptr = static_cast<const uint8_t *>(src);
    return ((std::uint16_t)src_ptr[0] << 8) | (std::uint16_t)src_ptr[1];
#endif
}

static inline std::uint32_t load32_be(const void *src) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    return (std::uint32_t)_loadbe_i32(src);
#else
    const std::uint8_t *src_ptr = static_cast<const uint8_t *>(src);
    return ((std::uint32_t)src_ptr[0] << 24) |
           ((std::uint32_t)src_ptr[1] << 16) |
           ((std::uint32_t)src_ptr[2] << 8) | (std::uint32_t)src_ptr[3];
#endif
}

static inline std::uint64_t load64_be(const void *src) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    return (std::uint64_t)_loadbe_i64(src);
#else
    const std::uint8_t *src_ptr = static_cast<const uint8_t *>(src);
    return ((std::uint64_t)src_ptr[0] << 56) |
           ((std::uint64_t)src_ptr[1] << 48) |
           ((std::uint64_t)src_ptr[2] << 40) |
           ((std::uint64_t)src_ptr[3] << 32) |
           ((std::uint64_t)src_ptr[4] << 24) |
           ((std::uint64_t)src_ptr[5] << 16) |
           ((std::uint64_t)src_ptr[6] << 8) | (std::uint64_t)src_ptr[7];
#endif
}

static inline void store8_le(void *dst, std::uint8_t n) noexcept
{
    *static_cast<std::uint8_t *>(dst) = n;
}

static inline void store16_le(void *dst, std::uint16_t n) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    *static_cast<std::uint16_t *>(dst) = n;
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = n & 0xFF;
    dst_ptr[1]            = (n >> 8) & 0xFF;
#endif
}

static inline void store32_le(void *dst, std::uint32_t n) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    *static_cast<std::uint32_t *>(dst) = n;
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = n & 0xFF;
    dst_ptr[1]            = (n >> 8) & 0xFF;
    dst_ptr[2]            = (n >> 16) & 0xFF;
    dst_ptr[3]            = (n >> 24) & 0xFF;
#endif
}

static inline void store64_le(void *dst, std::uint64_t n) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    *static_cast<std::uint64_t *>(dst) = n;
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = n & 0xFF;
    dst_ptr[1]            = (n >> 8) & 0xFF;
    dst_ptr[2]            = (n >> 16) & 0xFF;
    dst_ptr[3]            = (n >> 24) & 0xFF;
    dst_ptr[4]            = (n >> 32) & 0xFF;
    dst_ptr[5]            = (n >> 40) & 0xFF;
    dst_ptr[6]            = (n >> 48) & 0xFF;
    dst_ptr[7]            = (n >> 56) & 0xFF;
#endif
}

static inline void store8_be(void *dst, std::uint8_t n) noexcept
{
    *static_cast<std::uint8_t *>(dst) = n;
}

static inline void store16_be(void *dst, std::uint16_t n) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    _storebe_i16(dst, n);
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 8) & 0xFF;
    dst_ptr[1]            = (n >> 0) & 0xFF;
#endif
}

static inline void store32_be(void *dst, std::uint32_t n) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    _storebe_i32(dst, n);
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 24) & 0xFF;
    dst_ptr[1]            = (n >> 16) & 0xFF;
    dst_ptr[2]            = (n >> 8) & 0xFF;
    dst_ptr[3]            = (n >> 0) & 0xFF;
#endif
}

static inline void store64_be(void *dst, std::uint64_t n) noexcept
{
#if defined(CPU_FLAG_MOVBE)
    _storebe_i64(dst, n);
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 56) & 0xFF;
    dst_ptr[1]            = (n >> 48) & 0xFF;
    dst_ptr[2]            = (n >> 40) & 0xFF;
    dst_ptr[3]            = (n >> 32) & 0xFF;
    dst_ptr[4]            = (n >> 24) & 0xFF;
    dst_ptr[5]            = (n >> 16) & 0xFF;
    dst_ptr[6]            = (n >> 8) & 0xFF;
    dst_ptr[7]            = (n >> 0) & 0xFF;
#endif
}

} // namespace memory_utils

#if defined(_MSC_VER)

#else

#undef _loadbe_i16
#undef _storebe_i16
#undef _loadbe_i32
#undef _storebe_i32
#undef _loadbe_i64
#undef _storebe_i64

#endif

#endif