#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include "gmlib/number/internal/uint256_x64.h"
#include "speed.h"
#include <ctime>
#include <cstdio>
#include <random>

static void rand_mem(void* mem, std::size_t size)
{
    std::random_device device;
    std::mt19937_64    rng(device());
    std::uint8_t*      data = (std::uint8_t*)mem;
    for (std::size_t i = 0; i < size; i++)
    {
        data[i] = rng() % 256;
    }
}

using namespace number::internal::x64;

constexpr int LOOP = 10000000;

void speed_uint256_x64()
{
    // speed
    std::clock_t st, et;
    double       time_s, speed_opt_s;

    uint256_t    a, b, c[2];
    std::size_t  cnt = 0;
    std::uint8_t a_data[32], b_data[32];
    rand_mem(a_data, 32);
    rand_mem(b_data, 32);
    uint256_from_bytes(a, a_data);
    uint256_from_bytes(b, b_data);

    std::printf("speed uint256 x64 mul ... ");
    cnt = 0;
    st  = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        uint256_mul(c[0], a, b);
        cnt++;
    }
    et          = std::clock();
    time_s      = (double)(et - st) / CLOCKS_PER_SEC;
    speed_opt_s = cnt / time_s;
    std::printf("%e opt/s\n", speed_opt_s);

    std::printf("speed uint256 x64 sqr ... ");
    cnt = 0;
    st  = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        uint256_sqr(a, a);
        cnt++;
    }
    et          = std::clock();
    time_s      = (double)(et - st) / CLOCKS_PER_SEC;
    speed_opt_s = cnt / time_s;
    std::printf("%e opt/s\n", speed_opt_s);
}
#else
void speed_uint256_x64()
{
}
#endif