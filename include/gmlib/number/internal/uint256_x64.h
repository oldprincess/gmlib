#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#ifndef NUMBER_INTERNAL_UINT256_X64_H
#define NUMBER_INTERNAL_UINT256_X64_H

#include <cstddef>
#include <cstdint>

namespace number::internal::x64 {

typedef std::uint64_t uint256_t[4];

// ****************************************
// ************ Arithmetic ****************
// ****************************************

int uint256_add_carry(std::uint64_t       sum[4],
                      const std::uint64_t augend[4],
                      const std::uint64_t addend[4]) noexcept;

int uint256_sub_borrow(std::uint64_t       difference[4],
                       const std::uint64_t minuend[4],
                       const std::uint64_t subtrahend[4]) noexcept;

int uint256_dbl_carry(std::uint64_t       product[4],
                      const std::uint64_t multiplier[4]) noexcept;

int uint256_tpl_carry(std::uint64_t       product[4],
                      const std::uint64_t multiplier[4]) noexcept;

void uint256_mul(std::uint64_t       product[8],
                 const std::uint64_t multiplier[4],
                 const std::uint64_t multiplicand[4]) noexcept;

void uint256_sqr(std::uint64_t       product[8],
                 const std::uint64_t multiplier[4]) noexcept;

int uint256_add_carry_uint64(std::uint64_t       sum[4],
                             const std::uint64_t augend[4],
                             std::uint64_t       addend) noexcept;

int uint256_sub_borrow_uint64(std::uint64_t       difference[4],
                              const std::uint64_t minuend[4],
                              std::uint64_t       subtrahend) noexcept;

std::uint64_t uint256_mul_carry_uint64(std::uint64_t       product[4],
                                       const std::uint64_t multiplier[4],
                                       std::uint64_t multiplicand) noexcept;

std::uint64_t uint256_div_uint64(std::uint64_t       quotient[4],
                                 const std::uint64_t dividend[4],
                                 std::uint64_t       divisor) noexcept;

void uint256_mod_add(std::uint64_t       sum[4],
                     const std::uint64_t augend[4],
                     const std::uint64_t addend[4],
                     const std::uint64_t divisor[4]) noexcept;

void uint256_mod_sub(std::uint64_t       difference[4],
                     const std::uint64_t minuend[4],
                     const std::uint64_t subtrahend[4],
                     const std::uint64_t divisor[4]) noexcept;

void uint256_mod(std::uint64_t       remainder[4],
                 const std::uint8_t* data,
                 std::size_t         data_len,
                 const std::uint64_t divisor[4]) noexcept;

// ****************************************
// *************** Compare ****************
// ****************************************

int uint256_cmp(const std::uint64_t a[4], const std::uint64_t b[4]) noexcept;

int uint256_cmp_uint64(const std::uint64_t a[4], std::uint64_t b) noexcept;

bool uint256_equal(const std::uint64_t a[4], const std::uint64_t b[4]) noexcept;

bool uint256_equal_zero(const std::uint64_t a[4]) noexcept;

bool uint256_equal_one(const std::uint64_t a[4]) noexcept;

// ****************************************
// ************* Set & Move ***************
// ****************************************

void uint256_cpy(std::uint64_t ret[4], const std::uint64_t num[4]) noexcept;

void uint256_set_zero(std::uint64_t num[4]) noexcept;

void uint256_set_one(std::uint64_t num[4]) noexcept;

void uint256_set_uint64(std::uint64_t ret[4], std::uint64_t num) noexcept;

// ****************************************
// *************** Convert ****************
// ****************************************

void uint256_from_bytes(std::uint64_t      ret[4],
                        const std::uint8_t bytes[32]) noexcept;

void uint256_to_bytes(std::uint8_t        bytes[32],
                      const std::uint64_t num[4]) noexcept;

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

bool uint256_bittest(const std::uint64_t num[4], int i) noexcept;

} // namespace number::internal::x64
#endif
#endif