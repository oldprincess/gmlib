#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_uint256_common_set_zero()
{
    std::uint8_t zero_data[32] = {0};
    std::uint8_t a_data[32];
    uint256_t    a;
    uint256_set_zero(a);
    uint256_to_bytes(a_data, a);
    if (std::memcmp(a_data, zero_data, 32) != 0)
    {
        throw std::runtime_error("err in common::uint256_set_zero");
    }
}