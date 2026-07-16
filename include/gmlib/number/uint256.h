#ifndef NUMBER_UINT256_H
#define NUMBER_UINT256_H

#include <gmlib/number/provider.h>

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace number {

static inline const char* uint256_fetch_impl_algo() noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    return provider->algo_name;
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

static inline int uint256_add_carry(std::uint8_t       sum[32],
                                    const std::uint8_t augend[32],
                                    const std::uint8_t addend[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_add_carry != nullptr);
    return provider->uint256_add_carry(sum, augend, addend);
}

static inline int uint256_sub_borrow(std::uint8_t       difference[32],
                                     const std::uint8_t minuend[32],
                                     const std::uint8_t subtrahend[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_sub_borrow != nullptr);
    return provider->uint256_sub_borrow(difference, minuend, subtrahend);
}

static inline int uint256_dbl_carry(std::uint8_t       product[32],
                                    const std::uint8_t multiplier[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_dbl_carry != nullptr);
    return provider->uint256_dbl_carry(product, multiplier);
}

static inline int uint256_tpl_carry(std::uint8_t       product[32],
                                    const std::uint8_t multiplier[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_tpl_carry != nullptr);
    return provider->uint256_tpl_carry(product, multiplier);
}

static inline void uint256_mul(std::uint8_t       product[64],
                               const std::uint8_t multiplier[32],
                               const std::uint8_t multiplicand[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_mul != nullptr);
    provider->uint256_mul(product, multiplier, multiplicand);
}

static inline void uint256_sqr(std::uint8_t       product[64],
                               const std::uint8_t multiplier[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_sqr != nullptr);
    provider->uint256_sqr(product, multiplier);
}

static inline int uint256_add_carry_uint32(std::uint8_t       sum[32],
                                           const std::uint8_t augend[32],
                                           std::uint32_t      addend) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_add_carry_uint32 != nullptr);
    return provider->uint256_add_carry_uint32(sum, augend, addend);
}

static inline int uint256_add_carry_uint64(std::uint8_t       sum[32],
                                           const std::uint8_t augend[32],
                                           std::uint64_t      addend) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_add_carry_uint64 != nullptr);
    return provider->uint256_add_carry_uint64(sum, augend, addend);
}

static inline int uint256_sub_borrow_uint32(std::uint8_t       difference[32],
                                            const std::uint8_t minuend[32],
                                            std::uint32_t subtrahend) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_sub_borrow_uint32 != nullptr);
    return provider->uint256_sub_borrow_uint32(difference, minuend, subtrahend);
}

static inline int uint256_sub_borrow_uint64(std::uint8_t       difference[32],
                                            const std::uint8_t minuend[32],
                                            std::uint64_t subtrahend) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_sub_borrow_uint64 != nullptr);
    return provider->uint256_sub_borrow_uint64(difference, minuend, subtrahend);
}

static inline std::uint32_t uint256_mul_carry_uint32(
    std::uint8_t       product[32],
    const std::uint8_t multiplier[32],
    std::uint32_t      multiplicand) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_mul_carry_uint32 != nullptr);
    return provider->uint256_mul_carry_uint32(product, multiplier,
                                              multiplicand);
}

static inline std::uint64_t uint256_mul_carry_uint64(
    std::uint8_t       product[32],
    const std::uint8_t multiplier[32],
    std::uint64_t      multiplicand) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_mul_carry_uint64 != nullptr);
    return provider->uint256_mul_carry_uint64(product, multiplier,
                                              multiplicand);
}

static inline std::uint32_t uint256_div_uint32(std::uint8_t       quotient[32],
                                               const std::uint8_t dividend[32],
                                               std::uint32_t divisor) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_div_uint32 != nullptr);
    return provider->uint256_div_uint32(quotient, dividend, divisor);
}

static inline std::uint64_t uint256_div_uint64(std::uint8_t       quotient[32],
                                               const std::uint8_t dividend[32],
                                               std::uint64_t divisor) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_div_uint64 != nullptr);
    return provider->uint256_div_uint64(quotient, dividend, divisor);
}

static inline void uint256_mod_add(std::uint8_t       sum[32],
                                   const std::uint8_t augend[32],
                                   const std::uint8_t addend[32],
                                   const std::uint8_t divisor[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_mod_add != nullptr);
    provider->uint256_mod_add(sum, augend, addend, divisor);
}

static inline void uint256_mod_sub(std::uint8_t       difference[32],
                                   const std::uint8_t minuend[32],
                                   const std::uint8_t subtrahend[32],
                                   const std::uint8_t divisor[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_mod_sub != nullptr);
    provider->uint256_mod_sub(difference, minuend, subtrahend, divisor);
}

static inline void uint256_mod(std::uint8_t        remainder[32],
                               const std::uint8_t* data,
                               std::size_t         data_len,
                               const std::uint8_t  divisor[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_mod != nullptr);
    provider->uint256_mod(remainder, data, data_len, divisor);
}

// ****************************************
// *************** Compare ****************
// ****************************************

static inline int uint256_cmp(const std::uint8_t a[32],
                              const std::uint8_t b[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_cmp != nullptr);
    return provider->uint256_cmp(a, b);
}

static inline int uint256_cmp_uint32(const std::uint8_t a[32],
                                     std::uint32_t      b) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_cmp_uint32 != nullptr);
    return provider->uint256_cmp_uint32(a, b);
}

static inline int uint256_cmp_uint64(const std::uint8_t a[32],
                                     std::uint64_t      b) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_cmp_uint64 != nullptr);
    return provider->uint256_cmp_uint64(a, b);
}

static inline bool uint256_equal(const std::uint8_t a[32],
                                 const std::uint8_t b[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_equal != nullptr);
    return provider->uint256_equal(a, b);
}

static inline bool uint256_equal_zero(const std::uint8_t a[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_equal_zero != nullptr);
    return provider->uint256_equal_zero(a);
}

static inline bool uint256_equal_one(const std::uint8_t a[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_equal_one != nullptr);
    return provider->uint256_equal_one(a);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

static inline void uint256_cpy(std::uint8_t       ret[32],
                               const std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_cpy != nullptr);
    provider->uint256_cpy(ret, num);
}

static inline void uint256_set_zero(std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_set_zero != nullptr);
    provider->uint256_set_zero(num);
}

static inline void uint256_set_one(std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_set_one != nullptr);
    provider->uint256_set_one(num);
}

static inline void uint256_set_uint32(std::uint8_t  ret[32],
                                      std::uint32_t num) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_set_uint32 != nullptr);
    provider->uint256_set_uint32(ret, num);
}

static inline void uint256_set_uint64(std::uint8_t  ret[32],
                                      std::uint64_t num) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_set_uint64 != nullptr);
    provider->uint256_set_uint64(ret, num);
}

// ****************************************
// *************** Convert ****************
// ****************************************

static inline void uint256_from_bytes(std::uint8_t       ret[32],
                                      const std::uint8_t bytes[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_from_bytes != nullptr);
    provider->uint256_from_bytes(ret, bytes);
}

static inline void uint256_to_bytes(std::uint8_t       bytes[32],
                                    const std::uint8_t num[32]) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_to_bytes != nullptr);
    provider->uint256_to_bytes(bytes, num);
}

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

static inline bool uint256_bittest(const std::uint8_t num[32], int i) noexcept
{
    const NumberProvider* provider = get_number_provider(nullptr);
    assert(provider != nullptr);
    assert(provider->uint256_bittest != nullptr);
    return provider->uint256_bittest(num, i);
}

} // namespace number

#endif
