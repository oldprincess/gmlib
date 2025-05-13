#include "speed.h"

#include <gmlib/sm4/sm4.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

static void rand_mem(void* mem, std::size_t size)
{
    std::srand((unsigned int)std::time(nullptr));
    std::uint8_t* data = (std::uint8_t*)mem;
    for (std::size_t i = 0; i < size; i++)
    {
        data[i] = std::rand() % 256;
    }
}

using namespace sm4;

void speed_sm4()
{
    std::clock_t st, et;
    SM4          ctx;

    constexpr int         loop = 10000;
    constexpr std::size_t SIZE = 4096;

    std::uint8_t user_key[16];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 16);

    std::printf("speed sm4 %s... ", ctx.fetch_impl_algo());
    ctx.set_key(user_key, SM4::ENCRYPTION);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.encrypt_blocks(data, data, SIZE / 16);
    }
    et = std::clock();

    double time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    double speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);
    delete[] data;
}