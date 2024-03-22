#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <immintrin.h>

#if defined(_MSC_VER)
#include <intrin.h>
#else

#define _mulx_u64(a, b, c) _mulx_u64(a, b, (long long unsigned int *)c)
#define _addcarry_u64(a, b, c, d) \
    _addcarry_u64(a, b, c, (long long unsigned int *)d)
#define _subborrow_u64(a, b, c, d) \
    _subborrow_u64(a, b, c, (long long unsigned int *)d)

#define _loadbe_i64(ptr)     __builtin_bswap64(*(std::uint64_t *)(ptr))
#define _storebe_i64(ptr, a) *(std::uint64_t *)(ptr) = __builtin_bswap64(a)

static inline std::uint64_t _udiv128(std::uint64_t  h,
                                     std::uint64_t  l,
                                     std::uint64_t  d,
                                     std::uint64_t *r) noexcept
{
    __uint128_t hl = (__uint128_t)h << 64 | (__uint128_t)l;
    *r             = (std::uint64_t)(hl % d);
    return (std::uint64_t)(hl / d);
}

#endif

namespace number::internal::x64 {

// ****************************************
// ************ Arithmetic ****************
// ****************************************

int uint256_add_carry(std::uint64_t       sum[4],
                      const std::uint64_t augend[4],
                      const std::uint64_t addend[4]) noexcept
{
    unsigned char CF;
    CF = _addcarry_u64(0, augend[0], addend[0], &sum[0]);
    CF = _addcarry_u64(CF, augend[1], addend[1], &sum[1]);
    CF = _addcarry_u64(CF, augend[2], addend[2], &sum[2]);
    CF = _addcarry_u64(CF, augend[3], addend[3], &sum[3]);
    return CF;
}

int uint256_sub_borrow(std::uint64_t       difference[4],
                       const std::uint64_t minuend[4],
                       const std::uint64_t subtrahend[4]) noexcept
{
    unsigned char CF;
    CF = _subborrow_u64(0, minuend[0], subtrahend[0], &difference[0]);
    CF = _subborrow_u64(CF, minuend[1], subtrahend[1], &difference[1]);
    CF = _subborrow_u64(CF, minuend[2], subtrahend[2], &difference[2]);
    CF = _subborrow_u64(CF, minuend[3], subtrahend[3], &difference[3]);
    return -CF;
}

int uint256_dbl_carry(std::uint64_t       product[4],
                      const std::uint64_t multiplier[4]) noexcept
{
    unsigned char CF;
    CF = _addcarry_u64(0, multiplier[0], multiplier[0], &product[0]);
    CF = _addcarry_u64(CF, multiplier[1], multiplier[1], &product[1]);
    CF = _addcarry_u64(CF, multiplier[2], multiplier[2], &product[2]);
    CF = _addcarry_u64(CF, multiplier[3], multiplier[3], &product[3]);
    return CF;
}

int uint256_tpl_carry(std::uint64_t       product[4],
                      const std::uint64_t multiplier[4]) noexcept
{
    std::uint64_t t[4];
    int           ret = 0;
    unsigned char CF;
    CF = _addcarry_u64(0, multiplier[0], multiplier[0], &t[0]);
    CF = _addcarry_u64(CF, multiplier[1], multiplier[1], &t[1]);
    CF = _addcarry_u64(CF, multiplier[2], multiplier[2], &t[2]);
    CF = _addcarry_u64(CF, multiplier[3], multiplier[3], &t[3]);
    ret += CF;
    CF = _addcarry_u64(0, multiplier[0], t[0], &product[0]);
    CF = _addcarry_u64(CF, multiplier[1], t[1], &product[1]);
    CF = _addcarry_u64(CF, multiplier[2], t[2], &product[2]);
    CF = _addcarry_u64(CF, multiplier[3], t[3], &product[3]);
    ret += CF;
    return ret;
}

void uint256_mul(std::uint64_t       product[8],
                 const std::uint64_t multiplier[4],
                 const std::uint64_t multiplicand[4]) noexcept
{
    unsigned char CF;
    std::uint64_t hi[4]; // product lower
    std::uint64_t lo[4]; // product higher

    // ********************************************************
    // ******** product = multiplier x multiplicand ***********
    // ********************************************************
    // step 1
    product[0] = _mulx_u64(multiplier[0], multiplicand[0], &hi[0]);
    product[1] = _mulx_u64(multiplier[1], multiplicand[0], &hi[1]);
    product[2] = _mulx_u64(multiplier[2], multiplicand[0], &hi[2]);
    product[3] = _mulx_u64(multiplier[3], multiplicand[0], &hi[3]);

    CF = _addcarry_u64(0, product[1], hi[0], &product[1]);
    CF = _addcarry_u64(CF, product[2], hi[1], &product[2]);
    CF = _addcarry_u64(CF, product[3], hi[2], &product[3]);
    _addcarry_u64(CF, 0, hi[3], &product[4]); // drop CF

    // step 2
    lo[0] = _mulx_u64(multiplier[0], multiplicand[1], &hi[0]);
    lo[1] = _mulx_u64(multiplier[1], multiplicand[1], &hi[1]);
    lo[2] = _mulx_u64(multiplier[2], multiplicand[1], &hi[2]);
    lo[3] = _mulx_u64(multiplier[3], multiplicand[1], &hi[3]);

    CF = _addcarry_u64(0, product[1], lo[0], &product[1]);
    CF = _addcarry_u64(CF, product[2], lo[1], &product[2]);
    CF = _addcarry_u64(CF, product[3], lo[2], &product[3]);
    CF = _addcarry_u64(CF, product[4], lo[3], &product[4]);
    _addcarry_u64(CF, 0, 0, &product[5]); // drop CF

    CF = _addcarry_u64(0, product[2], hi[0], &product[2]);
    CF = _addcarry_u64(CF, product[3], hi[1], &product[3]);
    CF = _addcarry_u64(CF, product[4], hi[2], &product[4]);
    _addcarry_u64(CF, product[5], hi[3], &product[5]); // drop CF

    // step 3
    lo[0] = _mulx_u64(multiplier[0], multiplicand[2], &hi[0]);
    lo[1] = _mulx_u64(multiplier[1], multiplicand[2], &hi[1]);
    lo[2] = _mulx_u64(multiplier[2], multiplicand[2], &hi[2]);
    lo[3] = _mulx_u64(multiplier[3], multiplicand[2], &hi[3]);

    CF = _addcarry_u64(0, product[2], lo[0], &product[2]);
    CF = _addcarry_u64(CF, product[3], lo[1], &product[3]);
    CF = _addcarry_u64(CF, product[4], lo[2], &product[4]);
    CF = _addcarry_u64(CF, product[5], lo[3], &product[5]);
    _addcarry_u64(CF, 0, 0, &product[6]); // drop CF

    CF = _addcarry_u64(0, product[3], hi[0], &product[3]);
    CF = _addcarry_u64(CF, product[4], hi[1], &product[4]);
    CF = _addcarry_u64(CF, product[5], hi[2], &product[5]);
    _addcarry_u64(CF, product[6], hi[3], &product[6]); // drop CF

    // step 4
    lo[0] = _mulx_u64(multiplier[0], multiplicand[3], &hi[0]);
    lo[1] = _mulx_u64(multiplier[1], multiplicand[3], &hi[1]);
    lo[2] = _mulx_u64(multiplier[2], multiplicand[3], &hi[2]);
    lo[3] = _mulx_u64(multiplier[3], multiplicand[3], &hi[3]);

    CF = _addcarry_u64(0, product[3], lo[0], &product[3]);
    CF = _addcarry_u64(CF, product[4], lo[1], &product[4]);
    CF = _addcarry_u64(CF, product[5], lo[2], &product[5]);
    CF = _addcarry_u64(CF, product[6], lo[3], &product[6]);
    _addcarry_u64(CF, 0, 0, &product[7]); // drop CF

    CF = _addcarry_u64(0, product[4], hi[0], &product[4]);
    CF = _addcarry_u64(CF, product[5], hi[1], &product[5]);
    CF = _addcarry_u64(CF, product[6], hi[2], &product[6]);
    _addcarry_u64(CF, product[7], hi[3], &product[7]); // drop CF
}

void uint256_sqr(std::uint64_t       product[8],
                 const std::uint64_t multiplier[4]) noexcept
{
    uint256_mul(product, multiplier, multiplier);
}

int uint256_add_carry_uint64(std::uint64_t       sum[4],
                             const std::uint64_t augend[4],
                             std::uint64_t       addend) noexcept
{
    unsigned char CF;
    CF = _addcarry_u64(0, augend[0], addend, &sum[0]);
    CF = _addcarry_u64(CF, augend[1], 0, &sum[1]);
    CF = _addcarry_u64(CF, augend[2], 0, &sum[2]);
    CF = _addcarry_u64(CF, augend[3], 0, &sum[3]);
    return CF;
}

int uint256_sub_borrow_uint64(std::uint64_t       difference[4],
                              const std::uint64_t minuend[4],
                              std::uint64_t       subtrahend) noexcept
{
    unsigned char CF;
    CF = _subborrow_u64(0, minuend[0], subtrahend, &difference[0]);
    CF = _subborrow_u64(CF, minuend[1], 0, &difference[1]);
    CF = _subborrow_u64(CF, minuend[2], 0, &difference[2]);
    CF = _subborrow_u64(CF, minuend[3], 0, &difference[3]);
    return -CF;
}

std::uint64_t uint256_mul_carry_uint64(std::uint64_t       product[4],
                                       const std::uint64_t multiplier[4],
                                       std::uint64_t multiplicand) noexcept
{
    unsigned char CF;
    std::uint64_t hi[4]; // product lower
    std::uint64_t ret;

    product[0] = _mulx_u64(multiplier[0], multiplicand, &hi[0]);
    product[1] = _mulx_u64(multiplier[1], multiplicand, &hi[1]);
    product[2] = _mulx_u64(multiplier[2], multiplicand, &hi[2]);
    product[3] = _mulx_u64(multiplier[3], multiplicand, &hi[3]);

    CF = _addcarry_u64(0, product[1], hi[0], &product[1]);
    CF = _addcarry_u64(CF, product[2], hi[1], &product[2]);
    CF = _addcarry_u64(CF, product[3], hi[2], &product[3]);
    _addcarry_u64(CF, 0, hi[3], &ret); // drop CF
    return ret;
}

std::uint64_t uint256_div_uint64(std::uint64_t       quotient[4],
                                 const std::uint64_t dividend[4],
                                 std::uint64_t       divisor) noexcept
{
    std::uint64_t rem = 0;
    quotient[3]       = _udiv128(rem, dividend[3], divisor, &rem);
    quotient[2]       = _udiv128(rem, dividend[2], divisor, &rem);
    quotient[1]       = _udiv128(rem, dividend[1], divisor, &rem);
    quotient[0]       = _udiv128(rem, dividend[0], divisor, &rem);
    return rem;
}

void uint256_mod_add(std::uint64_t       sum[4],
                     const std::uint64_t augend[4],
                     const std::uint64_t addend[4],
                     const std::uint64_t divisor[4]) noexcept
{
    unsigned char c;
    c = _addcarry_u64(0, augend[0], addend[0], &sum[0]);
    c = _addcarry_u64(c, augend[1], addend[1], &sum[1]);
    c = _addcarry_u64(c, augend[2], addend[2], &sum[2]);
    c = _addcarry_u64(c, augend[3], addend[3], &sum[3]);
    if (c || uint256_cmp(sum, divisor) >= 0)
    {
        c = _subborrow_u64(0, sum[0], divisor[0], &sum[0]);
        c = _subborrow_u64(c, sum[1], divisor[1], &sum[1]);
        c = _subborrow_u64(c, sum[2], divisor[2], &sum[2]);
        c = _subborrow_u64(c, sum[3], divisor[3], &sum[3]);
    }
}

void uint256_mod_sub(std::uint64_t       difference[4],
                     const std::uint64_t minuend[4],
                     const std::uint64_t subtrahend[4],
                     const std::uint64_t divisor[4]) noexcept
{
    unsigned char c;
    c = _subborrow_u64(0, minuend[0], subtrahend[0], &difference[0]);
    c = _subborrow_u64(c, minuend[1], subtrahend[1], &difference[1]);
    c = _subborrow_u64(c, minuend[2], subtrahend[2], &difference[2]);
    c = _subborrow_u64(c, minuend[3], subtrahend[3], &difference[3]);
    if (c || uint256_cmp(difference, divisor) >= 0)
    {
        c = _addcarry_u64(0, difference[0], divisor[0], &difference[0]);
        c = _addcarry_u64(c, difference[1], divisor[1], &difference[1]);
        c = _addcarry_u64(c, difference[2], divisor[2], &difference[2]);
        c = _addcarry_u64(c, difference[3], divisor[3], &difference[3]);
    }
}

static void uint256_self_mod_sll_n(std::uint64_t       num[4],
                                   std::size_t         n,
                                   const std::uint64_t divisor[4]) noexcept
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

void uint256_mod(std::uint64_t       remainder[4],
                 const std::uint8_t *data,
                 std::size_t         data_len,
                 const std::uint64_t divisor[4]) noexcept
{
    std::uint64_t t[4];
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

int uint256_cmp(const std::uint64_t a[4], const std::uint64_t b[4]) noexcept
{
    for (int i = 3; i >= 0; i--)
    {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

int uint256_cmp_uint64(const std::uint64_t a[4], std::uint64_t b) noexcept
{
    for (int i = 3; i >= 1; i--)
    {
        if (a[i] > 0) return 1;
    }
    if (a[0] > b) return 1;
    if (a[0] < b) return -1;
    return 0;
}

bool uint256_equal(const std::uint64_t a[4], const std::uint64_t b[4]) noexcept
{
    return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]) | (a[3] ^ b[3])) == 0;
}

bool uint256_equal_zero(const std::uint64_t num[4]) noexcept
{
    return (num[0] | num[1] | num[2] | num[3]) == 0;
}

bool uint256_equal_one(const std::uint64_t a[4]) noexcept
{
    return ((a[1] | a[2] | a[3]) == 0) && (a[0] == 1);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void uint256_cpy(std::uint64_t ret[4], const std::uint64_t num[4]) noexcept
{
    ret[0] = num[0], ret[1] = num[1], ret[2] = num[2], ret[3] = num[3];
}

void uint256_set_zero(std::uint64_t num[4]) noexcept
{
    num[0] = num[1] = num[2] = num[3] = 0;
}

void uint256_set_one(std::uint64_t num[4]) noexcept
{
    num[0] = 1;
    num[1] = num[2] = num[3] = 0;
}

void uint256_set_uint64(std::uint64_t ret[4], std::uint64_t num) noexcept
{
    ret[0] = num;
    ret[1] = ret[2] = ret[3] = 0;
}

// ****************************************
// *************** Convert ****************
// ****************************************

void uint256_from_bytes(std::uint64_t      ret[4],
                        const std::uint8_t bytes[32]) noexcept
{
    ret[0] = _loadbe_i64(bytes + 24);
    ret[1] = _loadbe_i64(bytes + 16);
    ret[2] = _loadbe_i64(bytes + 8);
    ret[3] = _loadbe_i64(bytes + 0);
}

void uint256_to_bytes(std::uint8_t        bytes[32],
                      const std::uint64_t num[4]) noexcept
{
    _storebe_i64(bytes + 24, num[0]);
    _storebe_i64(bytes + 16, num[1]);
    _storebe_i64(bytes + 8, num[2]);
    _storebe_i64(bytes + 0, num[3]);
}

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

bool uint256_bittest(const std::uint64_t num[4], int i) noexcept
{
    int i_div64 = i / 64, i_mod64 = i % 64;
    return (num[i_div64] >> i_mod64) & 1;
}

} // namespace number::internal::x64
#endif