#include <gmlib/number/uint256.h>

#include <stdexcept>

using namespace number;

void test_uint256_equal_one()
{
    std::uint8_t one_data[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    uint256_t    a;
    uint256_from_bytes(a, one_data);
    if (!uint256_equal_one(a))
    {
        throw std::runtime_error("err in uint256_equal_one");
    }
}