#include <gmlib/number/uint256.h>

#include <stdexcept>

using namespace number;

void test_uint256_equal_zero()
{
    std::uint8_t zero_data[32] = {0};
    uint256_t    a;
    uint256_from_bytes(a, zero_data);
    if (!uint256_equal_zero(a))
    {
        throw std::runtime_error("err in uint256_equal_zero");
    }
}