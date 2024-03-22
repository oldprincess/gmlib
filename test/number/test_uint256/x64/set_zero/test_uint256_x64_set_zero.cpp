#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::x64;

void test_uint256_x64_set_zero()
{
    std::uint8_t zero_data[32] = {0};
    std::uint8_t a_data[32];
    uint256_t    a;
    uint256_set_zero(a);
    uint256_to_bytes(a_data, a);
    if (std::memcmp(a_data, zero_data, 32) != 0)
    {
        throw std::runtime_error("err in x64::uint256_set_zero");
    }
}
#else
void test_uint256_x64_set_zero()
{
}
#endif