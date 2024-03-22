#ifndef NUMBER_MPZ_H
#define NUMBER_MPZ_H

#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
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