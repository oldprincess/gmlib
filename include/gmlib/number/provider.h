#ifndef NUMBER_PROVIDER_H
#define NUMBER_PROVIDER_H

#include <cstddef>
#include <cstdint>

namespace number {

typedef std::uint8_t uint256_t[32];

typedef std::uint8_t mont256_t[32];

typedef struct Mont256CTX
{
    const std::uint8_t* P;      // 256bits p
    const std::uint8_t* P_SUB2; // 256bits p - 2
    const std::uint8_t* R;      // 256bits 2^256 mod p
    const std::uint8_t* R_POW2; // 256bits R^2 mod p
    const std::uint8_t* N_;     // 256bits N':N'*p=-1 mod 2^256
} Mont256CTX;

struct NumberProvider
{
    // ****************************************************
    // ***************** BASIC INFO ***********************
    // ****************************************************

    /** @brief Implementation name. */
    const char* algo_name;

    // ****************************************************
    // ***************** UINT256 **************************
    // ****************************************************

    /**
     * @brief Adds two 256-bit integers.
     * @param[out] sum          Output sum.
     * @param[in]  augend       First operand.
     * @param[in]  addend       Second operand.
     * @return The carry bit.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_add_carry)(std::uint8_t       sum[32],
                             const std::uint8_t augend[32],
                             const std::uint8_t addend[32]) noexcept = nullptr;

    /**
     * @brief Subtracts one 256-bit integer from another.
     * @param[out] difference   Output difference.
     * @param[in]  minuend      Value to subtract from.
     * @param[in]  subtrahend   Value to subtract.
     * @return The borrow bit.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_sub_borrow)(std::uint8_t       difference[32],
                              const std::uint8_t minuend[32],
                              const std::uint8_t subtrahend[32]) noexcept =
        nullptr;

    /**
     * @brief Doubles a 256-bit integer.
     * @param[out] product      Output product.
     * @param[in]  multiplier   Value to double.
     * @return The carry bit.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_dbl_carry)(std::uint8_t       product[32],
                             const std::uint8_t multiplier[32]) noexcept =
        nullptr;

    /**
     * @brief Triples a 256-bit integer.
     * @param[out] product      Output product.
     * @param[in]  multiplier   Value to triple.
     * @return The carry value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_tpl_carry)(std::uint8_t       product[32],
                             const std::uint8_t multiplier[32]) noexcept =
        nullptr;

    /**
     * @brief Multiplies two 256-bit integers.
     * @param[out] product      Output 512-bit product.
     * @param[in]  multiplier   First factor.
     * @param[in]  multiplicand Second factor.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_mul)(std::uint8_t       product[64],
                        const std::uint8_t multiplier[32],
                        const std::uint8_t multiplicand[32]) noexcept = nullptr;

    /**
     * @brief Squares a 256-bit integer.
     * @param[out] product      Output 512-bit square.
     * @param[in]  multiplier   Value to square.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_sqr)(std::uint8_t       product[64],
                        const std::uint8_t multiplier[32]) noexcept = nullptr;

    /**
     * @brief Adds a 32-bit integer to a 256-bit integer.
     * @param[out] sum          Output sum.
     * @param[in]  augend       256-bit operand.
     * @param[in]  addend       32-bit operand.
     * @return The carry bit.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_add_carry_uint32)(std::uint8_t       sum[32],
                                    const std::uint8_t augend[32],
                                    std::uint32_t addend) noexcept = nullptr;

    /**
     * @brief Adds a 64-bit integer to a 256-bit integer.
     * @param[out] sum          Output sum.
     * @param[in]  augend       256-bit operand.
     * @param[in]  addend       64-bit operand.
     * @return The carry bit.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_add_carry_uint64)(std::uint8_t       sum[32],
                                    const std::uint8_t augend[32],
                                    std::uint64_t addend) noexcept = nullptr;

    /**
     * @brief Subtracts a 32-bit integer from a 256-bit integer.
     * @param[out] difference   Output difference.
     * @param[in]  minuend      256-bit operand.
     * @param[in]  subtrahend   32-bit operand.
     * @return The borrow bit.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_sub_borrow_uint32)(std::uint8_t       difference[32],
                                     const std::uint8_t minuend[32],
                                     std::uint32_t      subtrahend) noexcept =
        nullptr;

    /**
     * @brief Subtracts a 64-bit integer from a 256-bit integer.
     * @param[out] difference   Output difference.
     * @param[in]  minuend      256-bit operand.
     * @param[in]  subtrahend   64-bit operand.
     * @return The borrow bit.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_sub_borrow_uint64)(std::uint8_t       difference[32],
                                     const std::uint8_t minuend[32],
                                     std::uint64_t      subtrahend) noexcept =
        nullptr;

    /**
     * @brief Multiplies a 256-bit integer by a 32-bit integer.
     * @param[out] product      Output low 256 bits of the product.
     * @param[in]  multiplier   256-bit factor.
     * @param[in]  multiplicand 32-bit factor.
     * @return The high 32 bits of the product.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    std::uint32_t (*uint256_mul_carry_uint32)(
        std::uint8_t       product[32],
        const std::uint8_t multiplier[32],
        std::uint32_t      multiplicand) noexcept = nullptr;

    /**
     * @brief Multiplies a 256-bit integer by a 64-bit integer.
     * @param[out] product      Output low 256 bits of the product.
     * @param[in]  multiplier   256-bit factor.
     * @param[in]  multiplicand 64-bit factor.
     * @return The high 64 bits of the product.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    std::uint64_t (*uint256_mul_carry_uint64)(
        std::uint8_t       product[32],
        const std::uint8_t multiplier[32],
        std::uint64_t      multiplicand) noexcept = nullptr;

    /**
     * @brief Divides a 256-bit integer by a 32-bit integer.
     * @param[out] quotient     Output quotient.
     * @param[in]  dividend     Dividend.
     * @param[in]  divisor      32-bit divisor.
     * @return The remainder.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    std::uint32_t (*uint256_div_uint32)(std::uint8_t       quotient[32],
                                        const std::uint8_t dividend[32],
                                        std::uint32_t      divisor) noexcept =
        nullptr;

    /**
     * @brief Divides a 256-bit integer by a 64-bit integer.
     * @param[out] quotient     Output quotient.
     * @param[in]  dividend     Dividend.
     * @param[in]  divisor      64-bit divisor.
     * @return The remainder.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    std::uint64_t (*uint256_div_uint64)(std::uint8_t       quotient[32],
                                        const std::uint8_t dividend[32],
                                        std::uint64_t      divisor) noexcept =
        nullptr;

    /**
     * @brief Adds two 256-bit integers modulo a divisor.
     * @param[out] sum          Output modular sum.
     * @param[in]  augend       First operand.
     * @param[in]  addend       Second operand.
     * @param[in]  divisor      Modulus.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_mod_add)(std::uint8_t       sum[32],
                            const std::uint8_t augend[32],
                            const std::uint8_t addend[32],
                            const std::uint8_t divisor[32]) noexcept = nullptr;

    /**
     * @brief Subtracts two 256-bit integers modulo a divisor.
     * @param[out] difference   Output modular difference.
     * @param[in]  minuend      Value to subtract from.
     * @param[in]  subtrahend   Value to subtract.
     * @param[in]  divisor      Modulus.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_mod_sub)(std::uint8_t       difference[32],
                            const std::uint8_t minuend[32],
                            const std::uint8_t subtrahend[32],
                            const std::uint8_t divisor[32]) noexcept = nullptr;

    /**
     * @brief Reduces a big-endian integer modulo a 256-bit divisor.
     * @param[out] remainder    Output remainder.
     * @param[in]  data         Input big-endian bytes.
     * @param[in]  data_len     Input length in bytes.
     * @param[in]  divisor      Modulus.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_mod)(std::uint8_t        remainder[32],
                        const std::uint8_t* data,
                        std::size_t         data_len,
                        const std::uint8_t  divisor[32]) noexcept = nullptr;

    /**
     * @brief Compares two 256-bit integers.
     * @param[in]  a            First operand.
     * @param[in]  b            Second operand.
     * @return A negative, zero, or positive value if @p a is less than, equal
     * to, or greater than @p b, respectively.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_cmp)(const std::uint8_t a[32],
                       const std::uint8_t b[32]) noexcept = nullptr;

    /**
     * @brief Compares a 256-bit integer with a 32-bit integer.
     * @param[in]  a            256-bit operand.
     * @param[in]  b            32-bit operand.
     * @return A negative, zero, or positive value if @p a is less than, equal
     * to, or greater than @p b, respectively.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_cmp_uint32)(const std::uint8_t a[32],
                              std::uint32_t      b) noexcept = nullptr;

    /**
     * @brief Compares a 256-bit integer with a 64-bit integer.
     * @param[in]  a            256-bit operand.
     * @param[in]  b            64-bit operand.
     * @return A negative, zero, or positive value if @p a is less than, equal
     * to, or greater than @p b, respectively.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*uint256_cmp_uint64)(const std::uint8_t a[32],
                              std::uint64_t      b) noexcept = nullptr;

    /**
     * @brief Tests two 256-bit integers for equality.
     * @param[in]  a            First operand.
     * @param[in]  b            Second operand.
     * @return Whether the operands are equal.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    bool (*uint256_equal)(const std::uint8_t a[32],
                          const std::uint8_t b[32]) noexcept = nullptr;

    /**
     * @brief Tests whether a 256-bit integer is zero.
     * @param[in]  a            Operand to test.
     * @return Whether the operand is zero.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    bool (*uint256_equal_zero)(const std::uint8_t a[32]) noexcept = nullptr;

    /**
     * @brief Tests whether a 256-bit integer is one.
     * @param[in]  a            Operand to test.
     * @return Whether the operand is one.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    bool (*uint256_equal_one)(const std::uint8_t a[32]) noexcept = nullptr;

    /**
     * @brief Copies a 256-bit integer.
     * @param[out] ret          Output value.
     * @param[in]  num          Input value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_cpy)(std::uint8_t       ret[32],
                        const std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Sets a 256-bit integer to zero.
     * @param[out] num          Output value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_set_zero)(std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Sets a 256-bit integer to one.
     * @param[out] num          Output value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_set_one)(std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Sets a 256-bit integer from a 32-bit integer.
     * @param[out] ret          Output value.
     * @param[in]  num          32-bit input.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_set_uint32)(std::uint8_t  ret[32],
                               std::uint32_t num) noexcept = nullptr;

    /**
     * @brief Sets a 256-bit integer from a 64-bit integer.
     * @param[out] ret          Output value.
     * @param[in]  num          64-bit input.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_set_uint64)(std::uint8_t  ret[32],
                               std::uint64_t num) noexcept = nullptr;

    /**
     * @brief Converts big-endian bytes to the internal 256-bit representation.
     * @param[out] ret          Output internal value.
     * @param[in]  bytes        Input big-endian bytes.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_from_bytes)(std::uint8_t       ret[32],
                               const std::uint8_t bytes[32]) noexcept = nullptr;

    /**
     * @brief Converts an internal 256-bit value to big-endian bytes.
     * @param[out] bytes        Output big-endian bytes.
     * @param[in]  num          Input internal value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*uint256_to_bytes)(std::uint8_t       bytes[32],
                             const std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Tests a bit in a 256-bit integer.
     * @param[in]  num          Input value.
     * @param[in]  i            Zero-based bit index.
     * @return Whether the selected bit is set.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    bool (*uint256_bittest)(const std::uint8_t num[32],
                            int                i) noexcept = nullptr;

    // ****************************************************
    // ***************** MONT256 **************************
    // ****************************************************

    /**
     * @brief Adds two Montgomery values.
     * @param[in]  ctx          Montgomery context.
     * @param[out] sum          Output sum.
     * @param[in]  augend       First operand.
     * @param[in]  addend       Second operand.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_add)(const Mont256CTX*  ctx,
                        std::uint8_t       sum[32],
                        const std::uint8_t augend[32],
                        const std::uint8_t addend[32]) noexcept = nullptr;

    /**
     * @brief Subtracts one Montgomery value from another.
     * @param[in]  ctx          Montgomery context.
     * @param[out] difference   Output difference.
     * @param[in]  minuend      Value to subtract from.
     * @param[in]  subtrahend   Value to subtract.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_sub)(const Mont256CTX*  ctx,
                        std::uint8_t       difference[32],
                        const std::uint8_t minuend[32],
                        const std::uint8_t subtrahend[32]) noexcept = nullptr;

    /**
     * @brief Doubles a Montgomery value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] product      Output product.
     * @param[in]  multiplier   Value to double.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_dbl)(const Mont256CTX*  ctx,
                        std::uint8_t       product[32],
                        const std::uint8_t multiplier[32]) noexcept = nullptr;

    /**
     * @brief Triples a Montgomery value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] product      Output product.
     * @param[in]  multiplier   Value to triple.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_tpl)(const Mont256CTX*  ctx,
                        std::uint8_t       product[32],
                        const std::uint8_t multiplier[32]) noexcept = nullptr;

    /**
     * @brief Negates a Montgomery value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] ret          Output negation.
     * @param[in]  num          Input value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_neg)(const Mont256CTX*  ctx,
                        std::uint8_t       ret[32],
                        const std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Multiplies two Montgomery values.
     * @param[in]  ctx          Montgomery context.
     * @param[out] product      Output product.
     * @param[in]  multiplier   First factor.
     * @param[in]  multiplicand Second factor.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_mul)(const Mont256CTX*  ctx,
                        std::uint8_t       product[32],
                        const std::uint8_t multiplier[32],
                        const std::uint8_t multiplicand[32]) noexcept = nullptr;

    /**
     * @brief Squares a Montgomery value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] product      Output square.
     * @param[in]  multiplier   Value to square.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_sqr)(const Mont256CTX*  ctx,
                        std::uint8_t       product[32],
                        const std::uint8_t multiplier[32]) noexcept = nullptr;

    /**
     * @brief Raises a Montgomery value to a 256-bit power.
     * @param[in]  ctx          Montgomery context.
     * @param[out] power        Output power.
     * @param[in]  base         Base.
     * @param[in]  exponent     Exponent.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_pow)(const Mont256CTX*  ctx,
                        std::uint8_t       power[32],
                        const std::uint8_t base[32],
                        const std::uint8_t exponent[32]) noexcept = nullptr;

    /**
     * @brief Divides a Montgomery value by two.
     * @param[in]  ctx          Montgomery context.
     * @param[out] quotient     Output quotient.
     * @param[in]  dividend     Dividend.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_div2)(const Mont256CTX*  ctx,
                         std::uint8_t       quotient[32],
                         const std::uint8_t dividend[32]) noexcept = nullptr;

    /**
     * @brief Computes the multiplicative inverse of a Montgomery value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] inverse      Output inverse.
     * @param[in]  num          Input value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_inv)(const Mont256CTX*  ctx,
                        std::uint8_t       inverse[32],
                        const std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Tests two Montgomery values for equality.
     * @param[in]  ctx          Montgomery context.
     * @param[in]  a            First operand.
     * @param[in]  b            Second operand.
     * @return Whether the operands are equal.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    bool (*mont256_equal)(const Mont256CTX*  ctx,
                          const std::uint8_t a[32],
                          const std::uint8_t b[32]) noexcept = nullptr;

    /**
     * @brief Tests whether a Montgomery value is zero.
     * @param[in]  ctx          Montgomery context.
     * @param[in]  a            Operand to test.
     * @return Whether the operand is zero.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    bool (*mont256_equal_zero)(const Mont256CTX*  ctx,
                               const std::uint8_t a[32]) noexcept = nullptr;

    /**
     * @brief Tests whether a Montgomery value is one.
     * @param[in]  ctx          Montgomery context.
     * @param[in]  a            Operand to test.
     * @return Whether the operand is one.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    bool (*mont256_equal_one)(const Mont256CTX*  ctx,
                              const std::uint8_t a[32]) noexcept = nullptr;

    /**
     * @brief Copies a Montgomery value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] ret          Output value.
     * @param[in]  num          Input value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_cpy)(const Mont256CTX*  ctx,
                        std::uint8_t       ret[32],
                        const std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Sets a Montgomery value to zero.
     * @param[in]  ctx          Montgomery context.
     * @param[out] num          Output value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_set_zero)(const Mont256CTX* ctx,
                             std::uint8_t      num[32]) noexcept = nullptr;

    /**
     * @brief Sets a Montgomery value to one.
     * @param[in]  ctx          Montgomery context.
     * @param[out] num          Output value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_set_one)(const Mont256CTX* ctx,
                            std::uint8_t      num[32]) noexcept = nullptr;

    /**
     * @brief Sets a Montgomery value from a 32-bit integer.
     * @param[in]  ctx          Montgomery context.
     * @param[out] ret          Output value.
     * @param[in]  num          32-bit input.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_set_uint32)(const Mont256CTX* ctx,
                               std::uint8_t      ret[32],
                               std::uint32_t     num) noexcept = nullptr;

    /**
     * @brief Sets a Montgomery value from a 64-bit integer.
     * @param[in]  ctx          Montgomery context.
     * @param[out] ret          Output value.
     * @param[in]  num          64-bit input.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_set_uint64)(const Mont256CTX* ctx,
                               std::uint8_t      ret[32],
                               std::uint64_t     num) noexcept = nullptr;

    /**
     * @brief Converts 32 big-endian bytes to a Montgomery value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] num          Output Montgomery value.
     * @param[in]  bytes        Input big-endian bytes.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_from_bytes)(const Mont256CTX*  ctx,
                               std::uint8_t       num[32],
                               const std::uint8_t bytes[32]) noexcept = nullptr;

    /**
     * @brief Converts a Montgomery value to 32 big-endian bytes.
     * @param[in]  ctx          Montgomery context.
     * @param[out] bytes        Output big-endian bytes.
     * @param[in]  num          Input Montgomery value.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_to_bytes)(const Mont256CTX*  ctx,
                             std::uint8_t       bytes[32],
                             const std::uint8_t num[32]) noexcept = nullptr;

    /**
     * @brief Converts a variable-length big-endian integer to a Montgomery
     * value.
     * @param[in]  ctx          Montgomery context.
     * @param[out] num          Output Montgomery value.
     * @param[in]  bytes        Input big-endian bytes.
     * @param[in]  bytes_len    Input length in bytes.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mont256_from_bytes_ex)(const Mont256CTX*   ctx,
                                  std::uint8_t        num[32],
                                  const std::uint8_t* bytes,
                                  std::size_t bytes_len) noexcept = nullptr;

    // ****************************************************
    // ***************** MPZ ******************************
    // ****************************************************

    /**
     * @brief Adds two arbitrary-width integers and an input carry.
     * @param[out] r            Output sum.
     * @param[in]  a            First operand.
     * @param[in]  b            Second operand.
     * @param[in]  carry        Input carry.
     * @param[in]  bits         Operand width in bits.
     * @return The output carry.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*mpz_add_carry)(std::uint8_t*       r,
                         const std::uint8_t* a,
                         const std::uint8_t* b,
                         int                 carry,
                         std::size_t         bits) noexcept = nullptr;

    /**
     * @brief Subtracts two arbitrary-width integers and an input borrow.
     * @param[out] r            Output difference.
     * @param[in]  a            Value to subtract from.
     * @param[in]  b            Value to subtract.
     * @param[in]  borrow       Input borrow.
     * @param[in]  bits         Operand width in bits.
     * @return The output borrow.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*mpz_sub_borrow)(std::uint8_t*       r,
                          const std::uint8_t* a,
                          const std::uint8_t* b,
                          int                 borrow,
                          std::size_t         bits) noexcept = nullptr;

    /**
     * @brief Multiplies two arbitrary-width integers.
     * @param[out] r            Output product.
     * @param[in]  a            First factor.
     * @param[in]  b            Second factor.
     * @param[in]  bits         Operand width in bits.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mpz_mul)(std::uint8_t*       r,
                    const std::uint8_t* a,
                    const std::uint8_t* b,
                    std::size_t         bits) noexcept = nullptr;

    /**
     * @brief Compares two arbitrary-width integers.
     * @param[in]  a            First operand.
     * @param[in]  b            Second operand.
     * @param[in]  bits         Operand width in bits.
     * @return A negative, zero, or positive value if @p a is less than, equal
     * to, or greater than @p b, respectively.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    int (*mpz_cmp)(const std::uint8_t* a,
                   const std::uint8_t* b,
                   std::size_t         bits) noexcept = nullptr;

    /**
     * @brief Copies an arbitrary-width integer.
     * @param[out] r            Output value.
     * @param[in]  a            Input value.
     * @param[in]  bits         Operand width in bits.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mpz_cpy)(std::uint8_t*       r,
                    const std::uint8_t* a,
                    std::size_t         bits) noexcept = nullptr;

    /**
     * @brief Converts big-endian bytes to an arbitrary-width internal value.
     * @param[out] r            Output internal value.
     * @param[in]  src          Input big-endian bytes.
     * @param[in]  bits         Operand width in bits.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mpz_from_bytes)(std::uint8_t*       r,
                           const std::uint8_t* src,
                           std::size_t         bits) noexcept = nullptr;

    /**
     * @brief Converts an arbitrary-width internal value to big-endian bytes.
     * @param[out] r            Output big-endian bytes.
     * @param[in]  src          Input internal value.
     * @param[in]  bits         Operand width in bits.
     * @note The function pointer must be checked for @c nullptr before use.
     */
    void (*mpz_to_bytes)(std::uint8_t*       r,
                         const std::uint8_t* src,
                         std::size_t         bits) noexcept = nullptr;
};

const NumberProvider* get_number_provider(const char* name) noexcept;

const char* const* get_number_supported_provider_names() noexcept;

} // namespace number

#endif
