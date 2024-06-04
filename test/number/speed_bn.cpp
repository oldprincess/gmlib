#include <gmlib/number/bn.h>

#include <cstdio>
#include <ctime>
#include <random>

#include "speed.h"

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

using namespace number;

constexpr int LOOP = 10000000;

void speed_bn()
{
    // init
    std::vector<std::uint8_t> bytes(32);
    rand_mem(bytes.data(), 32);
    BigNum a1 = BigNum::from_bytes(bytes);
    BigNum a2 = BigNum::from_bytes(bytes);
    BigNum b  = BigNum::from_uint32(0);
    // speed
    std::size_t  cnt;
    std::clock_t st, et;
    double       time_s, speed_opt_s;

    std::printf("speed bn256 mul bn256 ... ");
    cnt = 0;
    st  = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        b = a1 * a2;
        cnt++;
    }
    et          = std::clock();
    time_s      = (double)(et - st) / CLOCKS_PER_SEC;
    speed_opt_s = cnt / time_s;
    std::printf("%e opt/s\n", speed_opt_s);

    std::printf("speed bn512 div bn256...");
    a1  = a1 * a2;
    cnt = 0;
    st  = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        b = a1 / a2;
        cnt++;
    }
    et          = std::clock();
    time_s      = (double)(et - st) / CLOCKS_PER_SEC;
    speed_opt_s = cnt / time_s;
    std::printf("%e opt/s\n", speed_opt_s);
}