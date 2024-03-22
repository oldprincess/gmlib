#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include "gmlib/number/internal/mont256_x64.h"
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

static std::uint8_t P_data[32] = {
    0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static std::uint8_t P_SUB2_data[32] = {
    0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd};
static std::uint8_t R_data[32] = {
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
static std::uint8_t R_POW2_data[32] = {
    0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03};
static std::uint32_t N_ = 1;

constexpr int LOOP = 10000000;

void speed_mont256_x64()
{
    // init
    uint256_t P, P_SUB2, R, R_POW2;
    uint256_from_bytes(P, P_data);
    uint256_from_bytes(P_SUB2, P_SUB2_data);
    uint256_from_bytes(R, R_data);
    uint256_from_bytes(R_POW2, R_POW2_data);

    Mont256CTX ctx;
    ctx.P = P, ctx.P_SUB2 = P_SUB2;
    ctx.R = R, ctx.R_POW2 = R_POW2;
    ctx.N_ = N_;
    // speed
    std::clock_t st, et;
    double       time_s, speed_opt_s;

    mont256_t    a, b;
    std::size_t  cnt = 0;
    std::uint8_t a_data[32], b_data[32];
    rand_mem(a_data, 32);
    rand_mem(b_data, 32);
    mont256_from_bytes(&ctx, a, a_data);
    mont256_from_bytes(&ctx, b, b_data);

    std::printf("speed mont256 x64 mul ... ");
    cnt = 0;
    st  = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        mont256_mul(&ctx, a, a, b);
        cnt++;
    }
    et          = std::clock();
    time_s      = (double)(et - st) / CLOCKS_PER_SEC;
    speed_opt_s = cnt / time_s;
    std::printf("%e opt/s\n", speed_opt_s);

    std::printf("speed mont256 x64 sqr ... ");
    cnt = 0;
    st  = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        mont256_sqr(&ctx, a, a);
        cnt++;
    }
    et          = std::clock();
    time_s      = (double)(et - st) / CLOCKS_PER_SEC;
    speed_opt_s = cnt / time_s;
    std::printf("%e opt/s\n", speed_opt_s);

    std::printf("speed mont256 x64 inv ... ");
    cnt = 0;
    st  = std::clock();
    for (int i = 0; i < LOOP / 100; i++)
    {
        mont256_inv(&ctx, a, a);
        cnt++;
    }
    et          = std::clock();
    time_s      = (double)(et - st) / CLOCKS_PER_SEC;
    speed_opt_s = cnt / time_s;
    std::printf("%e opt/s\n", speed_opt_s);
}
#else
void speed_mont256_x64()
{
}
#endif