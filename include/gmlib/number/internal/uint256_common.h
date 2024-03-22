#ifndef NUMBER_INTERNAL_UINT256_COMMON_H
#define NUMBER_INTERNAL_UINT256_COMMON_H

#include <cstddef>
#include <cstdint>

namespace number::internal::common {

typedef std::uint32_t uint256_t[8];

// ****************************************
// ************ Arithmetic ****************
// ****************************************

int uint256_add_carry(std::uint32_t       sum[8],
                      const std::uint32_t augend[8],
                      const std::uint32_t addend[8]) noexcept;

int uint256_sub_borrow(std::uint32_t       difference[8],
                       const std::uint32_t minuend[8],
                       const std::uint32_t subtrahend[8]) noexcept;

int uint256_dbl_carry(std::uint32_t       product[8],
                      const std::uint32_t multiplier[8]) noexcept;

int uint256_tpl_carry(std::uint32_t       product[8],
                      const std::uint32_t multiplier[8]) noexcept;

void uint256_mul(std::uint32_t       product[16],
                 const std::uint32_t multiplier[8],
                 const std::uint32_t multiplicand[8]) noexcept;

void uint256_sqr(std::uint32_t       product[16],
                 const std::uint32_t multiplier[8]) noexcept;

int uint256_add_carry_uint32(std::uint32_t       sum[8],
                             const std::uint32_t augend[8],
                             std::uint32_t       addend) noexcept;

int uint256_sub_borrow_uint32(std::uint32_t       difference[8],
                              const std::uint32_t minuend[8],
                              std::uint32_t       subtrahend) noexcept;

std::uint32_t uint256_mul_carry_uint32(std::uint32_t       product[8],
                                       const std::uint32_t multiplier[8],
                                       std::uint32_t multiplicand) noexcept;

std::uint32_t uint256_div_uint32(std::uint32_t       quotient[8],
                                 const std::uint32_t dividend[8],
                                 std::uint32_t       divisor) noexcept;

void uint256_mod_add(std::uint32_t       sum[8],
                     const std::uint32_t augend[8],
                     const std::uint32_t addend[8],
                     const std::uint32_t divisor[8]) noexcept;

void uint256_mod_sub(std::uint32_t       difference[8],
                     const std::uint32_t minuend[8],
                     const std::uint32_t subtrahend[8],
                     const std::uint32_t divisor[8]) noexcept;

void uint256_mod(std::uint32_t       remainder[8],
                 const std::uint8_t* data,
                 std::size_t         data_len,
                 const std::uint32_t divisor[8]) noexcept;

// ****************************************
// *************** Compare ****************
// ****************************************

int uint256_cmp(const std::uint32_t a[8], const std::uint32_t b[8]) noexcept;

int uint256_cmp_uint32(const std::uint32_t a[8], std::uint32_t b) noexcept;

bool uint256_equal(const std::uint32_t a[8], const std::uint32_t b[8]) noexcept;

bool uint256_equal_zero(const std::uint32_t a[8]) noexcept;

bool uint256_equal_one(const std::uint32_t a[8]) noexcept;

// ****************************************
// ************* Set & Move ***************
// ****************************************

void uint256_cpy(std::uint32_t ret[8], const std::uint32_t num[8]) noexcept;

void uint256_set_zero(std::uint32_t num[8]) noexcept;

void uint256_set_one(std::uint32_t num[8]) noexcept;

void uint256_set_uint32(std::uint32_t ret[8], std::uint32_t num) noexcept;

// ****************************************
// *************** Convert ****************
// ****************************************

void uint256_from_bytes(std::uint32_t      ret[8],
                        const std::uint8_t bytes[32]) noexcept;

void uint256_to_bytes(std::uint8_t        bytes[32],
                      const std::uint32_t num[8]) noexcept;

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

bool uint256_bittest(const std::uint32_t num[8], int i) noexcept;

} // namespace number::internal::common

#endif