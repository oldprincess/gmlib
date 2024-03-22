#include <gmlib/number/internal/uint256_common.h>

#include <cstring>
#include <random>
#include <stdexcept>

using namespace number::internal::common;

constexpr int TEST_VECTOR_NUM = 100;

void test_uint256_common_cpy()
{
    std::random_device device;
    std::mt19937_64    rng(device());

    uint256_t    a, b;
    std::uint8_t a_data[32], b_data[32];

    for (int i = 0; i < TEST_VECTOR_NUM; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            a_data[j] = rng() % 256;
            b_data[j] = rng() % 256;
        }

        uint256_from_bytes(a, a_data);
        uint256_cpy(b, a);
        uint256_to_bytes(b_data, b);
        if (std::memcmp(a_data, b_data, 32) != 0)
        {
            throw std::runtime_error("err in uint256_common_cpy");
        }
    }
}