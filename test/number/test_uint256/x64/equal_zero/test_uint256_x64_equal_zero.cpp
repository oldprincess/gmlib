#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>

using namespace number::internal::x64;

void test_uint256_x64_equal_zero()
{
    std::uint8_t zero_data[32] = {0};
    uint256_t    a;
    uint256_from_bytes(a, zero_data);
    if (!uint256_equal_zero(a))
    {
        throw std::runtime_error("err in x64::uint256_equal_zero");
    }
}
#else
void test_uint256_x64_equal_zero()
{
}
#endif