#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>

using namespace number::internal::common;

void test_uint256_common_equal_one()
{
    std::uint8_t one_data[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    uint256_t    a;
    uint256_from_bytes(a, one_data);
    if (!uint256_equal_one(a))
    {
        throw std::runtime_error("err in common::uint256_equal_one");
    }
}