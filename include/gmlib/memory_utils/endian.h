#ifndef MEMORY_UTILS_ENDIAN_H
#define MEMORY_UTILS_ENDIAN_H

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

#if defined(__MOVBE__)
#include <immintrin.h>
#endif

namespace memory_utils {

enum class endian
{
    little  = 0,
    big     = 1,
    unknown = 2,

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
    defined(__ORDER_BIG_ENDIAN__)

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    native = little
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    native = big
#else
    native = unknown

#endif
#elif defined(_MSC_VER)

    // MSVC targets supported by Microsoft are little-endian:
    // x86, x64, ARM, ARM64.
    native = little

#else

    native = unknown

#endif
};

/**
 * @brief Informs the compiler that a pointer satisfies a specified alignment.
 *
 * This function neither adjusts the pointer nor checks its alignment at
 * runtime. It only provides an alignment assumption for optimization.
 *
 * @tparam N Required alignment in bytes. Must be a non-zero power of two.
 * @tparam T Type of the object pointed to.
 * @param ptr Pointer assumed to be aligned to an N-byte boundary.
 * @return A pointer to the same address with the specified alignment
 * assumption.
 *
 * @pre @p ptr must be aligned to an N-byte boundary. Violating this
 *      precondition results in undefined behavior.
 *
 * @note This interface follows the semantics of C++20 std::assume_aligned.
 */
template <std::size_t N, class T>
constexpr T *assume_aligned(T *ptr) noexcept
{
    constexpr bool is_pow_of_two = (N & (N - 1)) == 0;
    static_assert(is_pow_of_two, "alignment must be a non-zero power of two");
#if defined(_MSC_VER)
    __assume(reinterpret_cast<std::uintptr_t>(ptr) % N == 0);
    return ptr;
#elif defined(__GNUC__) || defined(__clang__)
    return static_cast<T *>(__builtin_assume_aligned(ptr, N));
#else
    return ptr;
#endif
}

// *********************************************************
// **************** Byte swapping functions ****************
// *********************************************************

/**
 * @brief Reverses the byte order of a 16-bit unsigned integer.
 *
 * @param x Value whose byte order is reversed.
 * @return The byte-swapped value.
 */
static inline std::uint16_t bswap16(std::uint16_t x) noexcept
{
#if defined(_MSC_VER)
    return _byteswap_ushort(x);
#elif defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap16(x);
#else
    return (x >> 8) | (x << 8);
#endif
}

/**
 * @brief Reverses the byte order of a 32-bit unsigned integer.
 *
 * @param x Value whose byte order is reversed.
 * @return The byte-swapped value.
 */
static inline std::uint32_t bswap32(std::uint32_t x) noexcept
{
#if defined(_MSC_VER)
    return _byteswap_ulong(x);
#elif defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap32(x);
#else
    return ((x & 0x000000FFu) << 24) | ((x & 0x0000FF00u) << 8) |
           ((x & 0x00FF0000u) >> 8) | ((x & 0xFF000000u) >> 24);
#endif
}

/**
 * @brief Reverses the byte order of a 64-bit unsigned integer.
 *
 * @param x Value whose byte order is reversed.
 * @return The byte-swapped value.
 */
static inline std::uint64_t bswap64(std::uint64_t x) noexcept
{
#if defined(_MSC_VER)
    return _byteswap_uint64(x);
#elif defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap64(x);
#else
    return ((x & 0x00000000000000FFull) << 56) |
           ((x & 0x000000000000FF00ull) << 40) |
           ((x & 0x0000000000FF0000ull) << 24) |
           ((x & 0x00000000FF000000ull) << 8) |
           ((x & 0x000000FF00000000ull) >> 8) |
           ((x & 0x0000FF0000000000ull) >> 24) |
           ((x & 0x00FF000000000000ull) >> 40) |
           ((x & 0xFF00000000000000ull) >> 56);
#endif
}

// *********************************************************
// **************** Unaligned load functions ***************
// *********************************************************

/**
 * @brief Loads a little-endian 16-bit unsigned integer.
 *
 * @param src Address of the encoded value. No alignment is required.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 2 readable bytes.
 */
static inline std::uint16_t load16_le_unaligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    return (std::uint16_t)src_ptr[0] | (std::uint16_t)src_ptr[1] << 8;
}

/**
 * @brief Loads a little-endian 32-bit unsigned integer.
 *
 * @param src Address of the encoded value. No alignment is required.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 4 readable bytes.
 */
static inline std::uint32_t load32_le_unaligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    return (std::uint32_t)src_ptr[0] << 0 |  //
           (std::uint32_t)src_ptr[1] << 8 |  //
           (std::uint32_t)src_ptr[2] << 16 | //
           (std::uint32_t)src_ptr[3] << 24;
}

/**
 * @brief Loads a little-endian 64-bit unsigned integer.
 *
 * @param src Address of the encoded value. No alignment is required.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 8 readable bytes.
 */
static inline std::uint64_t load64_le_unaligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    return (std::uint64_t)src_ptr[0] << 0 |  //
           (std::uint64_t)src_ptr[1] << 8 |  //
           (std::uint64_t)src_ptr[2] << 16 | //
           (std::uint64_t)src_ptr[3] << 24 | //
           (std::uint64_t)src_ptr[4] << 32 | //
           (std::uint64_t)src_ptr[5] << 40 | //
           (std::uint64_t)src_ptr[6] << 48 | //
           (std::uint64_t)src_ptr[7] << 56;
}

/**
 * @brief Loads a big-endian 16-bit unsigned integer.
 *
 * @param src Address of the encoded value. No alignment is required.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 2 readable bytes.
 */
static inline std::uint16_t load16_be_unaligned(const void *src) noexcept
{
#if defined(__MOVBE__)
    return (std::uint16_t)_loadbe_i16(src);
#else
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    return (std::uint16_t)src_ptr[0] << 8 | (std::uint16_t)src_ptr[1];
#endif
}

/**
 * @brief Loads a big-endian 32-bit unsigned integer.
 *
 * @param src Address of the encoded value. No alignment is required.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 4 readable bytes.
 */
static inline std::uint32_t load32_be_unaligned(const void *src) noexcept
{
#if defined(__MOVBE__)
    return (std::uint32_t)_loadbe_i32(src);
#else
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    return (std::uint32_t)src_ptr[0] << 24 | //
           (std::uint32_t)src_ptr[1] << 16 | //
           (std::uint32_t)src_ptr[2] << 8 |  //
           (std::uint32_t)src_ptr[3];
#endif
}

/**
 * @brief Loads a big-endian 64-bit unsigned integer.
 *
 * @param src Address of the encoded value. No alignment is required.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 8 readable bytes.
 */
static inline std::uint64_t load64_be_unaligned(const void *src) noexcept
{
#if defined(__MOVBE__)
    return (std::uint64_t)_loadbe_i64(src);
#else
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    return (std::uint64_t)src_ptr[0] << 56 | //
           (std::uint64_t)src_ptr[1] << 48 | //
           (std::uint64_t)src_ptr[2] << 40 | //
           (std::uint64_t)src_ptr[3] << 32 | //
           (std::uint64_t)src_ptr[4] << 24 | //
           (std::uint64_t)src_ptr[5] << 16 | //
           (std::uint64_t)src_ptr[6] << 8 |  //
           (std::uint64_t)src_ptr[7];
#endif
}

// *********************************************************
// **************** Aligned load functions *****************
// *********************************************************
/**
 * @brief Loads a little-endian 16-bit unsigned integer from aligned storage.
 *
 * @param src Address of the encoded value.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 2 readable bytes and be aligned to
 *      `alignof(std::uint16_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline std::uint16_t load16_le_aligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    src_ptr = assume_aligned<alignof(std::uint16_t)>(src_ptr);
    if constexpr (endian::native == endian::little)
    {
        return *reinterpret_cast<const std::uint16_t *>(src_ptr);
    }
    else if constexpr (endian::native == endian::big)
    {
        return bswap16(*reinterpret_cast<const std::uint16_t *>(src_ptr));
    }
    else
    {
        return load16_le_unaligned(src_ptr);
    }
}

/**
 * @brief Loads a little-endian 32-bit unsigned integer from aligned storage.
 *
 * @param src Address of the encoded value.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 4 readable bytes and be aligned to
 *      `alignof(std::uint32_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline std::uint32_t load32_le_aligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    src_ptr = assume_aligned<alignof(std::uint32_t)>(src_ptr);
    if constexpr (endian::native == endian::little)
    {
        return *reinterpret_cast<const std::uint32_t *>(src_ptr);
    }
    else if constexpr (endian::native == endian::big)
    {
        return bswap32(*reinterpret_cast<const std::uint32_t *>(src_ptr));
    }
    else
    {
        return load32_le_unaligned(src_ptr);
    }
}

/**
 * @brief Loads a little-endian 64-bit unsigned integer from aligned storage.
 *
 * @param src Address of the encoded value.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 8 readable bytes and be aligned to
 *      `alignof(std::uint64_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline std::uint64_t load64_le_aligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    src_ptr = assume_aligned<alignof(std::uint64_t)>(src_ptr);
    if constexpr (endian::native == endian::little)
    {
        return *reinterpret_cast<const std::uint64_t *>(src_ptr);
    }
    else if constexpr (endian::native == endian::big)
    {
        return bswap64(*reinterpret_cast<const std::uint64_t *>(src_ptr));
    }
    else
    {
        return load64_le_unaligned(src_ptr);
    }
}

/**
 * @brief Loads a big-endian 16-bit unsigned integer from aligned storage.
 *
 * @param src Address of the encoded value.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 2 readable bytes and be aligned to
 *      `alignof(std::uint16_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline std::uint16_t load16_be_aligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    src_ptr = assume_aligned<alignof(std::uint16_t)>(src_ptr);
#if defined(__MOVBE__)
    return (std::uint16_t)_loadbe_i16(src_ptr);
#else
    if constexpr (endian::native == endian::little)
    {
        return bswap16(*reinterpret_cast<const std::uint16_t *>(src_ptr));
    }
    else if constexpr (endian::native == endian::big)
    {
        return *reinterpret_cast<const std::uint16_t *>(src_ptr);
    }
    else
    {
        return load16_be_unaligned(src_ptr);
    }
#endif
}

/**
 * @brief Loads a big-endian 32-bit unsigned integer from aligned storage.
 *
 * @param src Address of the encoded value.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 4 readable bytes and be aligned to
 *      `alignof(std::uint32_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline std::uint32_t load32_be_aligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    src_ptr = assume_aligned<alignof(std::uint32_t)>(src_ptr);
#if defined(__MOVBE__)
    return (std::uint32_t)_loadbe_i32(src_ptr);
#else
    if constexpr (endian::native == endian::little)
    {
        return bswap32(*reinterpret_cast<const std::uint32_t *>(src_ptr));
    }
    else if constexpr (endian::native == endian::big)
    {
        return *reinterpret_cast<const std::uint32_t *>(src_ptr);
    }
    else
    {
        return load32_be_unaligned(src_ptr);
    }
#endif
}

/**
 * @brief Loads a big-endian 64-bit unsigned integer from aligned storage.
 *
 * @param src Address of the encoded value.
 * @return The decoded value in native byte order.
 *
 * @pre @p src must point to at least 8 readable bytes and be aligned to
 *      `alignof(std::uint64_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline std::uint64_t load64_be_aligned(const void *src) noexcept
{
    const std::uint8_t *src_ptr = static_cast<const std::uint8_t *>(src);
    src_ptr = assume_aligned<alignof(std::uint64_t)>(src_ptr);
#if defined(__MOVBE__)
    return (std::uint64_t)_loadbe_i64(src_ptr);
#else
    if constexpr (endian::native == endian::little)
    {
        return bswap64(*reinterpret_cast<const std::uint64_t *>(src_ptr));
    }
    else if constexpr (endian::native == endian::big)
    {
        return *reinterpret_cast<const std::uint64_t *>(src_ptr);
    }
    else
    {
        return load64_be_unaligned(src_ptr);
    }
#endif
}

// **************************************************
// ************ Unaligned Store Functions ***********
// **************************************************

/**
 * @brief Stores a 16-bit unsigned integer in little-endian byte order.
 *
 * @param dst Destination address. No alignment is required.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 2 writable bytes.
 */
static inline void store16_le_unaligned(void *dst, std::uint16_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 0) & 0xFF;
    dst_ptr[1]            = (n >> 8) & 0xFF;
}

/**
 * @brief Stores a 32-bit unsigned integer in little-endian byte order.
 *
 * @param dst Destination address. No alignment is required.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 4 writable bytes.
 */
static inline void store32_le_unaligned(void *dst, std::uint32_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 0) & 0xFF;
    dst_ptr[1]            = (n >> 8) & 0xFF;
    dst_ptr[2]            = (n >> 16) & 0xFF;
    dst_ptr[3]            = (n >> 24) & 0xFF;
}

/**
 * @brief Stores a 64-bit unsigned integer in little-endian byte order.
 *
 * @param dst Destination address. No alignment is required.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 8 writable bytes.
 */
static inline void store64_le_unaligned(void *dst, std::uint64_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 0) & 0xFF;
    dst_ptr[1]            = (n >> 8) & 0xFF;
    dst_ptr[2]            = (n >> 16) & 0xFF;
    dst_ptr[3]            = (n >> 24) & 0xFF;
    dst_ptr[4]            = (n >> 32) & 0xFF;
    dst_ptr[5]            = (n >> 40) & 0xFF;
    dst_ptr[6]            = (n >> 48) & 0xFF;
    dst_ptr[7]            = (n >> 56) & 0xFF;
}

/**
 * @brief Stores a 16-bit unsigned integer in big-endian byte order.
 *
 * @param dst Destination address. No alignment is required.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 2 writable bytes.
 */
static inline void store16_be_unaligned(void *dst, std::uint16_t n) noexcept
{
#if defined(__MOVBE__)
    _storebe_i16(dst, n);
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 8) & 0xFF;
    dst_ptr[1]            = (n >> 0) & 0xFF;
#endif
}

/**
 * @brief Stores a 32-bit unsigned integer in big-endian byte order.
 *
 * @param dst Destination address. No alignment is required.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 4 writable bytes.
 */
static inline void store32_be_unaligned(void *dst, std::uint32_t n) noexcept
{
#if defined(__MOVBE__)
    _storebe_i32(dst, n);
#else
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr[0]            = (n >> 24) & 0xFF;
    dst_ptr[1]            = (n >> 16) & 0xFF;
    dst_ptr[2]            = (n >> 8) & 0xFF;
    dst_ptr[3]            = (n >> 0) & 0xFF;
#endif
}

/**
 * @brief Stores a 64-bit unsigned integer in big-endian byte order.
 *
 * @param dst Destination address. No alignment is required.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 8 writable bytes.
 */
static inline void store64_be_unaligned(void *dst, std::uint64_t n) noexcept
{
#if defined(__MOVBE__)
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

// **************************************************
// ************ Aligned Store Functions ************
// **************************************************

/**
 * @brief Stores a 16-bit unsigned integer in little-endian byte order.
 *
 * @param dst Destination address.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 2 writable bytes and be aligned to
 *      `alignof(std::uint16_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline void store16_le_aligned(void *dst, std::uint16_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr               = assume_aligned<alignof(std::uint16_t)>(dst_ptr);
    if constexpr (endian::native == endian::little)
    {
        *reinterpret_cast<std::uint16_t *>(dst_ptr) = n;
    }
    else if constexpr (endian::native == endian::big)
    {
        *reinterpret_cast<std::uint16_t *>(dst_ptr) = bswap16(n);
    }
    else
    {
        store16_le_unaligned(dst_ptr, n);
    }
}

/**
 * @brief Stores a 32-bit unsigned integer in little-endian byte order.
 *
 * @param dst Destination address.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 4 writable bytes and be aligned to
 *      `alignof(std::uint32_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline void store32_le_aligned(void *dst, std::uint32_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr               = assume_aligned<alignof(std::uint32_t)>(dst_ptr);
    if constexpr (endian::native == endian::little)
    {
        *reinterpret_cast<std::uint32_t *>(dst_ptr) = n;
    }
    else if constexpr (endian::native == endian::big)
    {
        *reinterpret_cast<std::uint32_t *>(dst_ptr) = bswap32(n);
    }
    else
    {
        store32_le_unaligned(dst_ptr, n);
    }
}

/**
 * @brief Stores a 64-bit unsigned integer in little-endian byte order.
 *
 * @param dst Destination address.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 8 writable bytes and be aligned to
 *      `alignof(std::uint64_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline void store64_le_aligned(void *dst, std::uint64_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr               = assume_aligned<alignof(std::uint64_t)>(dst_ptr);
    if constexpr (endian::native == endian::little)
    {
        *reinterpret_cast<std::uint64_t *>(dst_ptr) = n;
    }
    else if constexpr (endian::native == endian::big)
    {
        *reinterpret_cast<std::uint64_t *>(dst_ptr) = bswap64(n);
    }
    else
    {
        store64_le_unaligned(dst_ptr, n);
    }
}

/**
 * @brief Stores a 16-bit unsigned integer in big-endian byte order.
 *
 * @param dst Destination address.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 2 writable bytes and be aligned to
 *      `alignof(std::uint16_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline void store16_be_aligned(void *dst, std::uint16_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr               = assume_aligned<alignof(std::uint16_t)>(dst_ptr);
#if defined(__MOVBE__)
    _storebe_i16(dst_ptr, n);
#else
    if constexpr (endian::native == endian::little)
    {
        *reinterpret_cast<std::uint16_t *>(dst_ptr) = bswap16(n);
    }
    else if constexpr (endian::native == endian::big)
    {
        *reinterpret_cast<std::uint16_t *>(dst_ptr) = n;
    }
    else
    {
        store16_be_unaligned(dst_ptr, n);
    }
#endif
}

/**
 * @brief Stores a 32-bit unsigned integer in big-endian byte order.
 *
 * @param dst Destination address.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 4 writable bytes and be aligned to
 *      `alignof(std::uint32_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline void store32_be_aligned(void *dst, std::uint32_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr               = assume_aligned<alignof(std::uint32_t)>(dst_ptr);
#if defined(__MOVBE__)
    _storebe_i32(dst_ptr, n);
#else
    if constexpr (endian::native == endian::little)
    {
        *reinterpret_cast<std::uint32_t *>(dst_ptr) = bswap32(n);
    }
    else if constexpr (endian::native == endian::big)
    {
        *reinterpret_cast<std::uint32_t *>(dst_ptr) = n;
    }
    else
    {
        store32_be_unaligned(dst_ptr, n);
    }
#endif
}

/**
 * @brief Stores a 64-bit unsigned integer in big-endian byte order.
 *
 * @param dst Destination address.
 * @param n Value to encode.
 *
 * @pre @p dst must point to at least 8 writable bytes and be aligned to
 *      `alignof(std::uint64_t)`. A misaligned address results in undefined
 *      behavior.
 */
static inline void store64_be_aligned(void *dst, std::uint64_t n) noexcept
{
    std::uint8_t *dst_ptr = static_cast<std::uint8_t *>(dst);
    dst_ptr               = assume_aligned<alignof(std::uint64_t)>(dst_ptr);
#if defined(__MOVBE__)
    _storebe_i64(dst_ptr, n);
#else
    if constexpr (endian::native == endian::little)
    {
        *reinterpret_cast<std::uint64_t *>(dst_ptr) = bswap64(n);
    }
    else if constexpr (endian::native == endian::big)
    {
        *reinterpret_cast<std::uint64_t *>(dst_ptr) = n;
    }
    else
    {
        store64_be_unaligned(dst_ptr, n);
    }
#endif
}

// ***************************************************
// ************ Deprecated Load Functions ************
// ***************************************************

/** @deprecated Read the std::uint8_t value directly instead. */
static inline std::uint8_t load8_le(const void *src) noexcept
{
    return *static_cast<const std::uint8_t *>(src);
}

/** @deprecated Use load16_le_aligned() or load16_le_unaligned() instead. */
static inline std::uint16_t load16_le(const void *src) noexcept
{
    return load16_le_unaligned(src);
}

/** @deprecated Use load32_le_aligned() or load32_le_unaligned() instead. */
static inline std::uint32_t load32_le(const void *src) noexcept
{
    return load32_le_unaligned(src);
}

/** @deprecated Use load64_le_aligned() or load64_le_unaligned() instead. */
static inline std::uint64_t load64_le(const void *src) noexcept
{
    return load64_le_unaligned(src);
}

/** @deprecated Read the std::uint8_t value directly instead. */
static inline std::uint8_t load8_be(const void *src) noexcept
{
    return *static_cast<const std::uint8_t *>(src);
}

/** @deprecated Use load16_be_aligned() or load16_be_unaligned() instead. */
static inline std::uint16_t load16_be(const void *src) noexcept
{
    return load16_be_unaligned(src);
}

/** @deprecated Use load32_be_aligned() or load32_be_unaligned() instead. */
static inline std::uint32_t load32_be(const void *src) noexcept
{
    return load32_be_unaligned(src);
}

/** @deprecated Use load64_be_aligned() or load64_be_unaligned() instead. */
static inline std::uint64_t load64_be(const void *src) noexcept
{
    return load64_be_unaligned(src);
}

// ****************************************************
// ************ Deprecated Store Functions ************
// ****************************************************

/** @deprecated Write the std::uint8_t value directly instead. */
static inline void store8_le(void *dst, std::uint8_t n) noexcept
{
    *static_cast<std::uint8_t *>(dst) = n;
}

/** @deprecated Use store16_le_aligned() or store16_le_unaligned() instead. */
static inline void store16_le(void *dst, std::uint16_t n) noexcept
{
    store16_le_unaligned(dst, n);
}

/** @deprecated Use store32_le_aligned() or store32_le_unaligned() instead. */
static inline void store32_le(void *dst, std::uint32_t n) noexcept
{
    store32_le_unaligned(dst, n);
}

/** @deprecated Use store64_le_aligned() or store64_le_unaligned() instead. */
static inline void store64_le(void *dst, std::uint64_t n) noexcept
{
    store64_le_unaligned(dst, n);
}

/** @deprecated Write the std::uint8_t value directly instead. */
static inline void store8_be(void *dst, std::uint8_t n) noexcept
{
    *static_cast<std::uint8_t *>(dst) = n;
}

/** @deprecated Use store16_be_aligned() or store16_be_unaligned() instead. */
static inline void store16_be(void *dst, std::uint16_t n) noexcept
{
    store16_be_unaligned(dst, n);
}

/** @deprecated Use store32_be_aligned() or store32_be_unaligned() instead. */
static inline void store32_be(void *dst, std::uint32_t n) noexcept
{
    store32_be_unaligned(dst, n);
}

/** @deprecated Use store64_be_aligned() or store64_be_unaligned() instead. */
static inline void store64_be(void *dst, std::uint64_t n) noexcept
{
    store64_be_unaligned(dst, n);
}

} // namespace memory_utils

#endif
