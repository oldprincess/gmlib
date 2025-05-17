#include "speed.h"

#include <gmlib/des/des.h>

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

using namespace des;

void speed_des()
{
    std::clock_t st, et;
    DES          ctx;

    constexpr int         loop = 1000;
    constexpr std::size_t SIZE = 4096;

    std::uint8_t user_key[8];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 8);

    std::printf("speed des %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.set_key(user_key, ctx.ENCRYPTION);
        ctx.encrypt_blocks(data, data, SIZE / 8);
    }
    et = std::clock();

    double time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    double speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);
    delete[] data;
}
