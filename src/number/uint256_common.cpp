#include <gmlib/number/internal/uint256_common.h>

namespace number::internal::common {

/// @brief r = a + b + carry
/// @return (1/0)
static inline int _add_carry(std::uint32_t* r,
                             std::uint32_t  a,
                             std::uint32_t  b,
                             int            carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a + (std::uint64_t)b + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief  r = 2a + carry
/// @return (1/0)
static inline int _dbl_carry(std::uint32_t* r,
                             std::uint32_t  a,
                             int            carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a + (std::uint64_t)a + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r = 3a + carry
/// @return (2/1/0)
static inline int _tpl_carry(std::uint32_t* r,
                             std::uint32_t  a,
                             int            carry) noexcept
{
    std::uint64_t tmp =
        (std::uint64_t)a + (std::uint64_t)a + (std::uint64_t)a + carry;
    *r = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r = a - b + borrow
/// @return (-1/0)
static inline int _sub_borrow(std::uint32_t* r,
                              std::uint32_t  a,
                              std::uint32_t  b,
                              int            borrow) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a - (std::uint64_t)b + borrow;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r = a * b + carry
/// @return [0,2^32)
static inline std::uint32_t _mul_carry(std::uint32_t* r,
                                       std::uint32_t  a,
                                       std::uint32_t  b,
                                       std::uint32_t  carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a * (std::uint64_t)b + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r += n * mul_val + carry
/// @return [0,2^32)
static inline std::uint32_t _add_mul_carry(std::uint32_t* r,
                                           std::uint32_t  n,
                                           std::uint32_t  mul_val,
                                           std::uint32_t  carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)n * (std::uint64_t)mul_val + *r + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

static inline std::uint32_t MEM_LOAD32BE(const void* src) noexcept
{
    return ((std::uint32_t)(((std::uint8_t*)src)[0]) << 24) |
           ((std::uint32_t)(((std::uint8_t*)src)[1]) << 16) |
           ((std::uint32_t)(((std::uint8_t*)src)[2]) << 8) |
           ((std::uint32_t)(((std::uint8_t*)src)[3]) << 0);
}

static inline void MEM_STORE32BE(void* dst, std::uint32_t a) noexcept
{
    ((std::uint8_t*)dst)[0] = ((std::uint32_t)a >> 24) & 0xFF;
    ((std::uint8_t*)dst)[1] = ((std::uint32_t)a >> 16) & 0xFF;
    ((std::uint8_t*)dst)[2] = ((std::uint32_t)a >> 8) & 0xFF;
    ((std::uint8_t*)dst)[3] = ((std::uint32_t)a >> 0) & 0xFF;
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

int uint256_add_carry(std::uint32_t       sum[8],
                      const std::uint32_t augend[8],
                      const std::uint32_t addend[8]) noexcept
{
    int carry;
    carry = _add_carry(&sum[0], augend[0], addend[0], 0);
    carry = _add_carry(&sum[1], augend[1], addend[1], carry);
    carry = _add_carry(&sum[2], augend[2], addend[2], carry);
    carry = _add_carry(&sum[3], augend[3], addend[3], carry);
    carry = _add_carry(&sum[4], augend[4], addend[4], carry);
    carry = _add_carry(&sum[5], augend[5], addend[5], carry);
    carry = _add_carry(&sum[6], augend[6], addend[6], carry);
    carry = _add_carry(&sum[7], augend[7], addend[7], carry);
    return carry;
}

int uint256_sub_borrow(std::uint32_t       difference[8],
                       const std::uint32_t minuend[8],
                       const std::uint32_t subtrahend[8]) noexcept
{
    int borrow;
    borrow = _sub_borrow(&difference[0], minuend[0], subtrahend[0], 0);
    borrow = _sub_borrow(&difference[1], minuend[1], subtrahend[1], borrow);
    borrow = _sub_borrow(&difference[2], minuend[2], subtrahend[2], borrow);
    borrow = _sub_borrow(&difference[3], minuend[3], subtrahend[3], borrow);
    borrow = _sub_borrow(&difference[4], minuend[4], subtrahend[4], borrow);
    borrow = _sub_borrow(&difference[5], minuend[5], subtrahend[5], borrow);
    borrow = _sub_borrow(&difference[6], minuend[6], subtrahend[6], borrow);
    borrow = _sub_borrow(&difference[7], minuend[7], subtrahend[7], borrow);
    return borrow;
}

int uint256_dbl_carry(std::uint32_t       product[8],
                      const std::uint32_t multiplier[8]) noexcept
{
    int carry;
    carry = _dbl_carry(&product[0], multiplier[0], 0);
    carry = _dbl_carry(&product[1], multiplier[1], carry);
    carry = _dbl_carry(&product[2], multiplier[2], carry);
    carry = _dbl_carry(&product[3], multiplier[3], carry);
    carry = _dbl_carry(&product[4], multiplier[4], carry);
    carry = _dbl_carry(&product[5], multiplier[5], carry);
    carry = _dbl_carry(&product[6], multiplier[6], carry);
    carry = _dbl_carry(&product[7], multiplier[7], carry);
    return carry;
}

int uint256_tpl_carry(std::uint32_t       product[8],
                      const std::uint32_t multiplier[8]) noexcept
{
    int carry;
    carry = _tpl_carry(&product[0], multiplier[0], 0);
    carry = _tpl_carry(&product[1], multiplier[1], carry);
    carry = _tpl_carry(&product[2], multiplier[2], carry);
    carry = _tpl_carry(&product[3], multiplier[3], carry);
    carry = _tpl_carry(&product[4], multiplier[4], carry);
    carry = _tpl_carry(&product[5], multiplier[5], carry);
    carry = _tpl_carry(&product[6], multiplier[6], carry);
    carry = _tpl_carry(&product[7], multiplier[7], carry);
    return carry;
}

void uint256_mul(std::uint32_t       product[16],
                 const std::uint32_t multiplier[8],
                 const std::uint32_t multiplicand[8]) noexcept
{
    std::uint32_t carry;
    // step 0
    carry = _mul_carry(&product[0], multiplier[0], multiplicand[0], 0);
    carry = _mul_carry(&product[1], multiplier[1], multiplicand[0], carry);
    carry = _mul_carry(&product[2], multiplier[2], multiplicand[0], carry);
    carry = _mul_carry(&product[3], multiplier[3], multiplicand[0], carry);
    carry = _mul_carry(&product[4], multiplier[4], multiplicand[0], carry);
    carry = _mul_carry(&product[5], multiplier[5], multiplicand[0], carry);
    carry = _mul_carry(&product[6], multiplier[6], multiplicand[0], carry);
    carry = _mul_carry(&product[7], multiplier[7], multiplicand[0], carry);

    product[8] = carry;
    // step 1
    carry = _add_mul_carry(&product[1], multiplier[0], multiplicand[1], 0);
    carry = _add_mul_carry(&product[2], multiplier[1], multiplicand[1], carry);
    carry = _add_mul_carry(&product[3], multiplier[2], multiplicand[1], carry);
    carry = _add_mul_carry(&product[4], multiplier[3], multiplicand[1], carry);
    carry = _add_mul_carry(&product[5], multiplier[4], multiplicand[1], carry);
    carry = _add_mul_carry(&product[6], multiplier[5], multiplicand[1], carry);
    carry = _add_mul_carry(&product[7], multiplier[6], multiplicand[1], carry);
    carry = _add_mul_carry(&product[8], multiplier[7], multiplicand[1], carry);
    product[9] = carry;
    // step 2
    carry = _add_mul_carry(&product[2], multiplier[0], multiplicand[2], 0);
    carry = _add_mul_carry(&product[3], multiplier[1], multiplicand[2], carry);
    carry = _add_mul_carry(&product[4], multiplier[2], multiplicand[2], carry);
    carry = _add_mul_carry(&product[5], multiplier[3], multiplicand[2], carry);
    carry = _add_mul_carry(&product[6], multiplier[4], multiplicand[2], carry);
    carry = _add_mul_carry(&product[7], multiplier[5], multiplicand[2], carry);
    carry = _add_mul_carry(&product[8], multiplier[6], multiplicand[2], carry);
    carry = _add_mul_carry(&product[9], multiplier[7], multiplicand[2], carry);
    product[10] = carry;
    // step 3
    carry = _add_mul_carry(&product[3], multiplier[0], multiplicand[3], 0);
    carry = _add_mul_carry(&product[4], multiplier[1], multiplicand[3], carry);
    carry = _add_mul_carry(&product[5], multiplier[2], multiplicand[3], carry);
    carry = _add_mul_carry(&product[6], multiplier[3], multiplicand[3], carry);
    carry = _add_mul_carry(&product[7], multiplier[4], multiplicand[3], carry);
    carry = _add_mul_carry(&product[8], multiplier[5], multiplicand[3], carry);
    carry = _add_mul_carry(&product[9], multiplier[6], multiplicand[3], carry);
    carry = _add_mul_carry(&product[10], multiplier[7], multiplicand[3], carry);
    product[11] = carry;
    // step 4
    carry = _add_mul_carry(&product[4], multiplier[0], multiplicand[4], 0);
    carry = _add_mul_carry(&product[5], multiplier[1], multiplicand[4], carry);
    carry = _add_mul_carry(&product[6], multiplier[2], multiplicand[4], carry);
    carry = _add_mul_carry(&product[7], multiplier[3], multiplicand[4], carry);
    carry = _add_mul_carry(&product[8], multiplier[4], multiplicand[4], carry);
    carry = _add_mul_carry(&product[9], multiplier[5], multiplicand[4], carry);
    carry = _add_mul_carry(&product[10], multiplier[6], multiplicand[4], carry);
    carry = _add_mul_carry(&product[11], multiplier[7], multiplicand[4], carry);
    product[12] = carry;
    // step 5
    carry = _add_mul_carry(&product[5], multiplier[0], multiplicand[5], 0);
    carry = _add_mul_carry(&product[6], multiplier[1], multiplicand[5], carry);
    carry = _add_mul_carry(&product[7], multiplier[2], multiplicand[5], carry);
    carry = _add_mul_carry(&product[8], multiplier[3], multiplicand[5], carry);
    carry = _add_mul_carry(&product[9], multiplier[4], multiplicand[5], carry);
    carry = _add_mul_carry(&product[10], multiplier[5], multiplicand[5], carry);
    carry = _add_mul_carry(&product[11], multiplier[6], multiplicand[5], carry);
    carry = _add_mul_carry(&product[12], multiplier[7], multiplicand[5], carry);
    product[13] = carry;
    // step 6
    carry = _add_mul_carry(&product[6], multiplier[0], multiplicand[6], 0);
    carry = _add_mul_carry(&product[7], multiplier[1], multiplicand[6], carry);
    carry = _add_mul_carry(&product[8], multiplier[2], multiplicand[6], carry);
    carry = _add_mul_carry(&product[9], multiplier[3], multiplicand[6], carry);
    carry = _add_mul_carry(&product[10], multiplier[4], multiplicand[6], carry);
    carry = _add_mul_carry(&product[11], multiplier[5], multiplicand[6], carry);
    carry = _add_mul_carry(&product[12], multiplier[6], multiplicand[6], carry);
    carry = _add_mul_carry(&product[13], multiplier[7], multiplicand[6], carry);
    product[14] = carry;
    // step 7
    carry = _add_mul_carry(&product[7], multiplier[0], multiplicand[7], 0);
    carry = _add_mul_carry(&product[8], multiplier[1], multiplicand[7], carry);
    carry = _add_mul_carry(&product[9], multiplier[2], multiplicand[7], carry);
    carry = _add_mul_carry(&product[10], multiplier[3], multiplicand[7], carry);
    carry = _add_mul_carry(&product[11], multiplier[4], multiplicand[7], carry);
    carry = _add_mul_carry(&product[12], multiplier[5], multiplicand[7], carry);
    carry = _add_mul_carry(&product[13], multiplier[6], multiplicand[7], carry);
    carry = _add_mul_carry(&product[14], multiplier[7], multiplicand[7], carry);
    product[15] = carry;
}

void uint256_sqr(std::uint32_t       product[16],
                 const std::uint32_t multiplier[8]) noexcept
{
    uint256_mul(product, multiplier, multiplier);
}

int uint256_add_carry_uint32(std::uint32_t       sum[8],
                             const std::uint32_t augend[8],
                             std::uint32_t       addend) noexcept
{
    int carry;
    carry = _add_carry(&sum[0], augend[0], addend, 0);
    carry = _add_carry(&sum[1], augend[1], 0, carry);
    carry = _add_carry(&sum[2], augend[2], 0, carry);
    carry = _add_carry(&sum[3], augend[3], 0, carry);
    carry = _add_carry(&sum[4], augend[4], 0, carry);
    carry = _add_carry(&sum[5], augend[5], 0, carry);
    carry = _add_carry(&sum[6], augend[6], 0, carry);
    carry = _add_carry(&sum[7], augend[7], 0, carry);
    return carry;
}

int uint256_sub_borrow_uint32(std::uint32_t       difference[8],
                              const std::uint32_t minuend[8],
                              std::uint32_t       subtrahend) noexcept
{
    int borrow;
    borrow = _sub_borrow(&difference[0], minuend[0], subtrahend, 0);
    borrow = _sub_borrow(&difference[1], minuend[1], 0, borrow);
    borrow = _sub_borrow(&difference[2], minuend[2], 0, borrow);
    borrow = _sub_borrow(&difference[3], minuend[3], 0, borrow);
    borrow = _sub_borrow(&difference[4], minuend[4], 0, borrow);
    borrow = _sub_borrow(&difference[5], minuend[5], 0, borrow);
    borrow = _sub_borrow(&difference[6], minuend[6], 0, borrow);
    borrow = _sub_borrow(&difference[7], minuend[7], 0, borrow);
    return borrow;
}

std::uint32_t uint256_mul_carry_uint32(std::uint32_t       product[8],
                                       const std::uint32_t multiplier[8],
                                       std::uint32_t multiplicand) noexcept
{
    std::uint32_t carry;
    carry = _mul_carry(&product[0], multiplier[0], multiplicand, 0);
    carry = _mul_carry(&product[1], multiplier[1], multiplicand, carry);
    carry = _mul_carry(&product[2], multiplier[2], multiplicand, carry);
    carry = _mul_carry(&product[3], multiplier[3], multiplicand, carry);
    carry = _mul_carry(&product[4], multiplier[4], multiplicand, carry);
    carry = _mul_carry(&product[5], multiplier[5], multiplicand, carry);
    carry = _mul_carry(&product[6], multiplier[6], multiplicand, carry);
    carry = _mul_carry(&product[7], multiplier[7], multiplicand, carry);
    return carry;
}

std::uint32_t uint256_div_uint32(std::uint32_t       quotient[8],
                                 const std::uint32_t dividend[8],
                                 std::uint32_t       divisor) noexcept
{
    std::uint64_t rem = 0;
    for (int i = 7; i >= 0; i--)
    {
        rem = (rem << 32) | (std::uint32_t)dividend[i];

        quotient[i] = (std::uint32_t)(rem / divisor);
        rem         = rem % divisor;
    }
    return (std::uint32_t)rem;
}

void uint256_mod_add(std::uint32_t       sum[8],
                     const std::uint32_t augend[8],
                     const std::uint32_t addend[8],
                     const std::uint32_t divisor[8]) noexcept
{
    int carry = uint256_add_carry(sum, augend, addend);
    if (carry || uint256_cmp(sum, divisor) >= 0)
    {
        uint256_sub_borrow(sum, sum, divisor);
    }
}

void uint256_mod_sub(std::uint32_t       difference[8],
                     const std::uint32_t minuend[8],
                     const std::uint32_t subtrahend[8],
                     const std::uint32_t divisor[8]) noexcept
{
    int borrow = uint256_sub_borrow(difference, minuend, subtrahend);
    if (borrow || uint256_cmp(difference, divisor) >= 0)
    {
        uint256_add_carry(difference, difference, divisor);
    }
}

static void uint256_self_mod_sll_n(std::uint32_t       num[8],
                                   std::size_t         n,
                                   const std::uint32_t divisor[8]) noexcept
{
    if (uint256_equal_zero(num))
    {
        return;
    }
    for (std::size_t i = 0; i < n; i++)
    {
        uint256_mod_add(num, num, num, divisor);
    }
}

void uint256_mod(std::uint32_t       remainder[8],
                 const std::uint8_t* data,
                 std::size_t         data_len,
                 const std::uint32_t divisor[8]) noexcept
{
    std::uint32_t t[8];
    std::uint8_t  tmp_buf[32] = {0};
    uint256_set_zero(remainder);
    if (data_len >= 32)
    {
        uint256_from_bytes(t, data);
        while (uint256_cmp(t, divisor) >= 0)
        {
            uint256_sub_borrow(t, t, divisor); // never CF
        }
        uint256_mod_add(remainder, remainder, t, divisor);
        data_len -= 32, data += 32;
    }
    while (data_len >= 32)
    {
        uint256_self_mod_sll_n(remainder, 256, divisor);
        uint256_from_bytes(t, data);
        while (uint256_cmp(t, divisor) >= 0)
        {
            uint256_sub_borrow(t, t, divisor); // never CF
        }
        uint256_mod_add(remainder, remainder, t, divisor);
        data_len -= 32, data += 32;
    }
    if (data_len)
    {
        uint256_self_mod_sll_n(remainder, 8 * data_len, divisor);
        for (std::size_t i = 0; i < data_len; i++)
        {
            tmp_buf[31 - i] = data[data_len - 1 - i];
        }
        uint256_from_bytes(t, tmp_buf);
        while (uint256_cmp(t, divisor) >= 0)
        {
            uint256_sub_borrow(t, t, divisor); // never CF
        }
        uint256_mod_add(remainder, remainder, t, divisor);
    }
}

// ****************************************
// *************** Compare ****************
// ****************************************

int uint256_cmp(const std::uint32_t a[8], const std::uint32_t b[8]) noexcept
{
    for (int i = 7; i >= 0; i--)
    {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

int uint256_cmp_uint32(const std::uint32_t a[8], std::uint32_t b) noexcept
{
    for (int i = 7; i >= 1; i--)
    {
        if (a[i] > 0) return 1;
    }
    if (a[0] > b) return 1;
    if (a[0] < b) return -1;
    return 0;
}

bool uint256_equal(const std::uint32_t a[8], const std::uint32_t b[8]) noexcept
{
    return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3]) |
            (a[4] ^ b[4]) | (a[5] ^ b[5]) | (a[6] ^ b[6]) | (a[7] ^ b[7])) == 0;
}

bool uint256_equal_zero(const std::uint32_t a[8]) noexcept
{
    return (a[0] | a[1] | a[2] | a[3] | a[4] | a[5] | a[6] | a[7]) == 0;
}

bool uint256_equal_one(const std::uint32_t a[8]) noexcept
{
    return ((a[1] | a[2] | a[3] | a[4] | a[5] | a[6] | a[7]) == 0) &&
           (a[0] == 1);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void uint256_cpy(std::uint32_t ret[8], const std::uint32_t num[8]) noexcept
{
    ret[0] = num[0], ret[1] = num[1], ret[2] = num[2], ret[3] = num[3];
    ret[4] = num[4], ret[5] = num[5], ret[6] = num[6], ret[7] = num[7];
}

void uint256_set_zero(std::uint32_t num[8]) noexcept
{
    num[0] = num[1] = num[2] = num[3] = num[4] = num[5] = num[6] = num[7] = 0;
}

void uint256_set_one(std::uint32_t num[8]) noexcept
{
    num[0] = 1;
    num[1] = num[2] = num[3] = num[4] = num[5] = num[6] = num[7] = 0;
}

void uint256_set_uint32(std::uint32_t ret[8], std::uint32_t num) noexcept
{
    ret[0] = num;
    ret[1] = ret[2] = ret[3] = ret[4] = ret[5] = ret[6] = ret[7] = 0;
}

// ****************************************
// *************** Convert ****************
// ****************************************

void uint256_from_bytes(std::uint32_t      ret[8],
                        const std::uint8_t bytes[32]) noexcept
{
    ret[7] = MEM_LOAD32BE(bytes + 0);
    ret[6] = MEM_LOAD32BE(bytes + 4);
    ret[5] = MEM_LOAD32BE(bytes + 8);
    ret[4] = MEM_LOAD32BE(bytes + 12);
    ret[3] = MEM_LOAD32BE(bytes + 16);
    ret[2] = MEM_LOAD32BE(bytes + 20);
    ret[1] = MEM_LOAD32BE(bytes + 24);
    ret[0] = MEM_LOAD32BE(bytes + 28);
}

void uint256_to_bytes(std::uint8_t        bytes[32],
                      const std::uint32_t num[8]) noexcept
{
    MEM_STORE32BE(bytes + 0, num[7]);
    MEM_STORE32BE(bytes + 4, num[6]);
    MEM_STORE32BE(bytes + 8, num[5]);
    MEM_STORE32BE(bytes + 12, num[4]);
    MEM_STORE32BE(bytes + 16, num[3]);
    MEM_STORE32BE(bytes + 20, num[2]);
    MEM_STORE32BE(bytes + 24, num[1]);
    MEM_STORE32BE(bytes + 28, num[0]);
}

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

bool uint256_bittest(const std::uint32_t num[8], int i) noexcept
{
    return ((num[i / 32] >> (i % 32)) & 1) == 1;
}

}; // namespace number::internal::common