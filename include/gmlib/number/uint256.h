#ifndef NUMBER_UINT256_H
#define NUMBER_UINT256_H

#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
namespace number {
using namespace number::internal::x64;

// ****************************************
// *************** Extend *****************
// ****************************************

static inline int uint256_add_carry_uint32(std::uint64_t       sum[4],
                                           const std::uint64_t augend[4],
                                           std::uint32_t       addend) noexcept
{
    return uint256_add_carry_uint64(sum, augend, addend);
}

static inline int uint256_sub_borrow_uint32(std::uint64_t       difference[4],
                                            const std::uint64_t minuend[4],
                                            std::uint32_t subtrahend) noexcept
{
    return uint256_sub_borrow_uint64(difference, minuend, subtrahend);
}

static inline std::uint32_t uint256_mul_carry_uint32(
    std::uint64_t       product[4],
    const std::uint64_t multiplier[4],
    std::uint32_t       multiplicand) noexcept
{
    return (std::uint32_t)uint256_mul_carry_uint64(product, multiplier,
                                                   multiplicand);
}

static inline int uint256_cmp_uint32(const std::uint64_t a[4],
                                     std::uint32_t       b) noexcept
{
    return uint256_cmp_uint64(a, b);
}

static inline void uint256_set_uint32(std::uint64_t ret[4],
                                      std::uint32_t num) noexcept
{
    uint256_set_uint64(ret, num);
}

} // namespace number

#else
#include <gmlib/number/internal/uint256_common.h>
namespace number {
using namespace number::internal::common;
} // namespace number
#endif

#endif