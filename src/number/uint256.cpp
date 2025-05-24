#include <gmlib/number/uint256.h>

#include "config.h"

#if defined(NUMBER_IMPL_UINT256_X64)
#include "uint256_x64.h"
namespace number {
namespace alg = internal::x64;
typedef std::uint64_t limb_t;

static const char* UINT256_ALGO_NAME = "x64";

}; // namespace number
#else
#include "uint256_common.h"
namespace number {
namespace alg = internal::common;
typedef std::uint32_t limb_t;

static const char* UINT256_ALGO_NAME = "common";

}; // namespace number
#endif

namespace number {

const char* uint256_fetch_impl_algo() noexcept
{
    return UINT256_ALGO_NAME;
}

// ****************************************
// ************ Arithmetic ****************
// ****************************************

int uint256_add_carry(std::uint8_t       sum[32],
                      const std::uint8_t augend[32],
                      const std::uint8_t addend[32]) noexcept
{
    return alg::uint256_add_carry((limb_t*)sum,           //
                                  (const limb_t*)augend,  //
                                  (const limb_t*)addend); //
}

int uint256_sub_borrow(std::uint8_t       difference[32],
                       const std::uint8_t minuend[32],
                       const std::uint8_t subtrahend[32]) noexcept
{
    return alg::uint256_sub_borrow((limb_t*)difference,        //
                                   (const limb_t*)minuend,     //
                                   (const limb_t*)subtrahend); //
}

int uint256_dbl_carry(std::uint8_t       product[32],
                      const std::uint8_t multiplier[32]) noexcept
{
    return alg::uint256_dbl_carry((limb_t*)product,           //
                                  (const limb_t*)multiplier); //
}

int uint256_tpl_carry(std::uint8_t       product[32],
                      const std::uint8_t multiplier[32]) noexcept
{
    return alg::uint256_tpl_carry((limb_t*)product,           //
                                  (const limb_t*)multiplier); //
}

void uint256_mul(std::uint8_t       product[64],
                 const std::uint8_t multiplier[32],
                 const std::uint8_t multiplicand[32]) noexcept
{
    return alg::uint256_mul((limb_t*)product,             //
                            (const limb_t*)multiplier,    //
                            (const limb_t*)multiplicand); //
}

void uint256_sqr(std::uint8_t       product[64],
                 const std::uint8_t multiplier[32]) noexcept
{
    return alg::uint256_sqr((limb_t*)product, (const limb_t*)multiplier);
}

int uint256_add_carry_uint32(std::uint8_t       sum[32],
                             const std::uint8_t augend[32],
                             std::uint32_t      addend) noexcept
{
    return alg::uint256_add_carry_uint32((limb_t*)sum,          //
                                         (const limb_t*)augend, //
                                         addend);               //
}

int uint256_add_carry_uint64(std::uint8_t       sum[32],
                             const std::uint8_t augend[32],
                             std::uint64_t      addend) noexcept
{
    return alg::uint256_add_carry_uint64((limb_t*)sum,          //
                                         (const limb_t*)augend, //
                                         addend);               //
}

int uint256_sub_borrow_uint32(std::uint8_t       difference[32],
                              const std::uint8_t minuend[32],
                              std::uint32_t      subtrahend) noexcept
{
    return alg::uint256_sub_borrow_uint32((limb_t*)difference,    //
                                          (const limb_t*)minuend, //
                                          subtrahend);
}

int uint256_sub_borrow_uint64(std::uint8_t       difference[32],
                              const std::uint8_t minuend[32],
                              std::uint64_t      subtrahend) noexcept
{
    return alg::uint256_sub_borrow_uint64((limb_t*)difference,    //
                                          (const limb_t*)minuend, //
                                          subtrahend);            //
}

std::uint32_t uint256_mul_carry_uint32(std::uint8_t       product[32],
                                       const std::uint8_t multiplier[32],
                                       std::uint32_t      multiplicand) noexcept
{
    return alg::uint256_mul_carry_uint32((limb_t*)product,          //
                                         (const limb_t*)multiplier, //
                                         multiplicand);             //
}

std::uint64_t uint256_mul_carry_uint64(std::uint8_t       product[32],
                                       const std::uint8_t multiplier[32],
                                       std::uint64_t      multiplicand) noexcept
{
    return alg::uint256_mul_carry_uint64((limb_t*)product,          //
                                         (const limb_t*)multiplier, //
                                         multiplicand);             //
}

std::uint32_t uint256_div_uint32(std::uint8_t       quotient[32],
                                 const std::uint8_t dividend[32],
                                 std::uint32_t      divisor) noexcept
{
    return alg::uint256_div_uint32((limb_t*)quotient,       //
                                   (const limb_t*)dividend, //
                                   divisor);                //
}

std::uint64_t uint256_div_uint64(std::uint8_t       quotient[32],
                                 const std::uint8_t dividend[32],
                                 std::uint64_t      divisor) noexcept
{
    return alg::uint256_div_uint64((limb_t*)quotient,       //
                                   (const limb_t*)dividend, //
                                   divisor);                //
}

void uint256_mod_add(std::uint8_t       sum[32],
                     const std::uint8_t augend[32],
                     const std::uint8_t addend[32],
                     const std::uint8_t divisor[32]) noexcept
{
    return alg::uint256_mod_add((limb_t*)sum,            //
                                (const limb_t*)augend,   //
                                (const limb_t*)addend,   //
                                (const limb_t*)divisor); //
}

void uint256_mod_sub(std::uint8_t       difference[32],
                     const std::uint8_t minuend[32],
                     const std::uint8_t subtrahend[32],
                     const std::uint8_t divisor[32]) noexcept
{
    return alg::uint256_mod_sub((limb_t*)difference,       //
                                (const limb_t*)minuend,    //
                                (const limb_t*)subtrahend, //
                                (const limb_t*)divisor);   //
}

void uint256_mod(std::uint8_t        remainder[32],
                 const std::uint8_t* data,
                 std::size_t         data_len,
                 const std::uint8_t  divisor[32]) noexcept
{
    return alg::uint256_mod((limb_t*)remainder,      //
                            data, data_len,          //
                            (const limb_t*)divisor); //
}

// ****************************************
// *************** Compare ****************
// ****************************************

int uint256_cmp(const std::uint8_t a[32], const std::uint8_t b[32]) noexcept
{
    return alg::uint256_cmp((const limb_t*)a, (const limb_t*)b);
}

int uint256_cmp_uint32(const std::uint8_t a[32], std::uint32_t b) noexcept
{
    return alg::uint256_cmp_uint32((const limb_t*)a, b);
}

int uint256_cmp_uint64(const std::uint8_t a[32], std::uint64_t b) noexcept
{
    return alg::uint256_cmp_uint64((const limb_t*)a, b);
}

bool uint256_equal(const std::uint8_t a[32], const std::uint8_t b[32]) noexcept
{
    return alg::uint256_equal((const limb_t*)a, (const limb_t*)b);
}

bool uint256_equal_zero(const std::uint8_t a[32]) noexcept
{
    return alg::uint256_equal_zero((const limb_t*)a);
}

bool uint256_equal_one(const std::uint8_t a[32]) noexcept
{
    return alg::uint256_equal_one((const limb_t*)a);
}

// ****************************************
// ************* Set & Move ***************
// ****************************************

void uint256_cpy(std::uint8_t ret[32], const std::uint8_t num[32]) noexcept
{
    alg::uint256_cpy((limb_t*)ret, (const limb_t*)num);
}

void uint256_set_zero(std::uint8_t num[32]) noexcept
{
    alg::uint256_set_zero((limb_t*)num);
}

void uint256_set_one(std::uint8_t num[32]) noexcept
{
    alg::uint256_set_one((limb_t*)num);
}

void uint256_set_uint32(std::uint8_t ret[32], std::uint32_t num) noexcept
{
    alg::uint256_set_uint32((limb_t*)ret, num);
}

void uint256_set_uint64(std::uint8_t ret[32], std::uint64_t num) noexcept
{
    alg::uint256_set_uint64((limb_t*)ret, num);
}

// ****************************************
// *************** Convert ****************
// ****************************************

void uint256_from_bytes(std::uint8_t       ret[32],
                        const std::uint8_t bytes[32]) noexcept
{
    alg::uint256_from_bytes((limb_t*)ret, bytes);
}

void uint256_to_bytes(std::uint8_t       bytes[32],
                      const std::uint8_t num[32]) noexcept
{
    alg::uint256_to_bytes(bytes, (const limb_t*)num);
}

// ****************************************
// ********** Bit Manipulation ************
// ****************************************

bool uint256_bittest(const std::uint8_t num[32], int i) noexcept
{
    return alg::uint256_bittest((const limb_t*)num, i);
}

} // namespace number