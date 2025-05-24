#ifndef NUMBER_UINT256_H
#define NUMBER_UINT256_H

#include <cstddef>
#include <cstdint>

namespace number {

typedef std::uint8_t uint256_t[32];

const char* uint256_fetch_impl_algo() noexcept;

// ****************************************
// ************ Arithmetic ****************
// ****************************************

int uint256_add_carry(std::uint8_t       sum[32],
                      const std::uint8_t augend[32],
                      const std::uint8_t addend[32]) noexcept;

int uint256_sub_borrow(std::uint8_t       difference[32],
                       const std::uint8_t minuend[32],
                       const std::uint8_t subtrahend[32]) noexcept;

int uint256_dbl_carry(std::uint8_t       product[32],
                      const std::uint8_t multiplier[32]) noexcept;

int uint256_tpl_carry(std::uint8_t       product[32],
                      const std::uint8_t multiplier[32]) noexcept;

void uint256_mul(std::uint8_t       product[64],
                 const std::uint8_t multiplier[32],
                 const std::uint8_t multiplicand[32]) noexcept;

void uint256_sqr(std::uint8_t       product[64],
                 const std::uint8_t multiplier[32]) noexcept;

int uint256_add_carry_uint32(std::uint8_t       sum[32],
                             const std::uint8_t augend[32],
                             std::uint32_t      addend) noexcept;

int uint256_add_carry_uint64(std::uint8_t       sum[32],
                             const std::uint8_t augend[32],
                             std::uint64_t      addend) noexcept;

int uint256_sub_borrow_uint32(std::uint8_t       difference[32],
                              const std::uint8_t minuend[32],
                              std::uint32_t      subtrahend) noexcept;

int uint256_sub_borrow_uint64(std::uint8_t       difference[32],
                              const std::uint8_t minuend[32],
                              std::uint64_t      subtrahend) noexcept;

std::uint32_t uint256_mul_carry_uint32(std::uint8_t       product[32],
                                       const std::uint8_t multiplier[32],
                                       std::uint32_t multiplicand) noexcept;

std::uint64_t uint256_mul_carry_uint64(std::uint8_t       product[32],
                                       const std::uint8_t multiplier[32],
                                       std::uint64_t multiplicand) noexcept;

std::uint32_t uint256_div_uint32(std::uint8_t       quotient[32],
                                 const std::uint8_t dividend[32],
                                 std::uint32_t      divisor) noexcept;

std::uint64_t uint256_div_uint64(std::uint8_t       quotient[32],
                                 const std::uint8_t dividend[32],
                                 std::uint64_t      divisor) noexcept;

void uint256_mod_add(std::uint8_t       sum[32],
                     const std::uint8_t augend[32],
                     const std::uint8_t addend[32],
                     const std::uint8_t divisor[32]) noexcept;

void uint256_mod_sub(std::uint8_t       difference[32],
                     const std::uint8_t minuend[32],
                     const std::uint8_t subtrahend[32],
                     const std::uint8_t divisor[32]) noexcept;

void uint256_mod(std::uint8_t        remainder[32],
                 const std::uint8_t* data,
                 std::size_t         data_len,
                 const std::uint8_t  divisor[32]) noexcept;

// ****************************************
// *************** Compare ****************
// ****************************************

int uint256_cmp(const std::uint8_t a[32], const std::uint8_t b[32]) noexcept;

int uint256_cmp_uint32(const std::uint8_t a[32], std::uint32_t b) noexcept;

int uint256_cmp_uint64(const std::uint8_t a[32], std::uint64_t b) noexcept;

bool uint256_equal(const std::uint8_t a[32], const std::uint8_t b[32]) noexcept;

bool uint256_equal_zero(const std::uint8_t a[32]) noexcept;

bool uint256_equal_one(const std::uint8_t a[32]) noexcept;

// ****************************************
// ************* Set & Move ***************
// ****************************************

void uint256_cpy(std::uint8_t ret[32], const std::uint8_t num[32]) noexcept;

void uint256_set_zero(std::uint8_t num[32]) noexcept;

void uint256_set_one(std::uint8_t num[32]) noexcept;

void uint256_set_uint32(std::uint8_t ret[32], std::uint32_t num) noexcept;

void uint256_set_uint64(std::uint8_t ret[32], std::uint64_t num) noexcept;

// ****************************************
// *************** Convert ****************
// ****************************************

void uint256_from_bytes(std::uint8_t       ret[32],
                        const std::uint8_t bytes[32]) noexcept;

void uint256_to_bytes(std::uint8_t       bytes[32],
                      const std::uint8_t num[32]) noexcept;

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

bool uint256_bittest(const std::uint8_t num[32], int i) noexcept;

} // namespace number

#endif