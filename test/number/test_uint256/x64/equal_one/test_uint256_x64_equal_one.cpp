#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>

using namespace number::internal::x64;

void test_uint256_x64_equal_one()
{
    std::uint8_t one_data[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    uint256_t    a;
    uint256_from_bytes(a, one_data);
    if (!uint256_equal_one(a))
    {
        throw std::runtime_error("err in x64::uint256_equal_one");
    }
}
#else
void test_uint256_x64_equal_one()
{
}
#endif