#ifndef NUMBER_MONT256_H
#define NUMBER_MONT256_H

#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/mont256_x64.h>
namespace number {
using namespace number::internal::x64;

static inline void mont256_set_uint32(const Mont256CTX* ctx,
                                      std::uint64_t     ret[4],
                                      std::uint32_t     num) noexcept
{
    mont256_set_uint64(ctx, ret, num);
}

} // namespace number

#else
#include <gmlib/number/internal/mont256_common.h>
namespace number {
using namespace number::internal::common;
} // namespace number
#endif

#endif