#ifndef NUMBER_UINT256_H
#define NUMBER_UINT256_H

#include <gmlib/number/config.h>

#if defined(NUMBER_IMPL_UINT256_X64)

#include <gmlib/number/internal/uint256_x64.h>
namespace number {
using namespace number::internal::x64;

// ****************************************
// *************** Extend *****************
// ****************************************

#define uint256_add_carry_uint32  uint256_add_carry_uint64
#define uint256_sub_borrow_uint32 uint256_sub_borrow_uint64
#define uint256_cmp_uint32        uint256_cmp_uint64
#define uint256_set_uint32        uint256_set_uint64
#define uint256_mul_carry_uint32(x, y, z) \
    (std::uint32_t)uint256_mul_carry_uint64(x, y, z)

} // namespace number

#else
#include <gmlib/number/internal/uint256_common.h>
namespace number {
using namespace number::internal::common;
} // namespace number
#endif

#endif