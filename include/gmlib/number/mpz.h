#ifndef NUMBER_MPZ_H
#define NUMBER_MPZ_H

#include <gmlib/number/config.h>

#if defined(NUMBER_MPZ_X64)
#include <gmlib/number/internal/mpz_x64.h>
namespace number {
using namespace number::internal::x64;

} // namespace number

#else
#include <gmlib/number/internal/mpz_common.h>
namespace number {
using namespace number::internal::common;
} // namespace number
#endif

#endif