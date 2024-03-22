#include <gmlib/sm4/internal/sm4_common.h>
#include "speed.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>

static void rand_mem(void* mem, std::size_t size)
{
    std::srand((unsigned int)std::time(nullptr));
    std::uint8_t* data = (std::uint8_t*)mem;
    for (std::size_t i = 0; i < size; i++)
    {
        data[i] = std::rand() % 256;
    }
}

using namespace sm4::internal::common;

void speed_sm4_common()
{
    std::clock_t st, et;
    Sm4CTX       ctx;

    constexpr int         loop = 10000;
    constexpr std::size_t SIZE = 4096;

    std::uint8_t user_key[16];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 16);

    std::printf("speed sm4 common ... ");
    sm4_enc_key_init(&ctx, user_key);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        sm4_enc_blocks(&ctx, data, data, SIZE / 16);
    }
    et = std::clock();

    double time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    double speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);
    delete[] data;
}