#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>

using namespace number::internal::common;

void test_uint256_common_equal_zero()
{
    std::uint8_t zero_data[32] = {0};
    uint256_t    a;
    uint256_from_bytes(a, zero_data);
    if (!uint256_equal_zero(a))
    {
        throw std::runtime_error("err in common::uint256_equal_zero");
    }
}