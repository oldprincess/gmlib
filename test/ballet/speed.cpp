#include "speed.h"

#include <gmlib/ballet/ballet.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace ballet;

constexpr std::size_t SIZE = 4096 * 32;
constexpr int         loop = 1000;

static void rand_mem(void* mem, std::size_t size)
{
    std::srand((unsigned int)std::time(nullptr));
    std::uint8_t* data = (std::uint8_t*)mem;
    for (std::size_t i = 0; i < size; i++)
    {
        data[i] = std::rand() % 256;
    }
}

static void speed_ballet128128()
{
    std::clock_t st, et;
    Ballet128128 ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ballet128128 %s ... ", ctx.fetch_impl_algo());

    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.set_key(user_key, ctx.ENCRYPTION);
        ctx.encrypt_blocks(data, data, SIZE / ctx.BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_ballet128256()
{
    std::clock_t st, et;
    Ballet128256 ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ballet128256 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.set_key(user_key, ctx.ENCRYPTION);
        ctx.encrypt_blocks(data, data, SIZE / ctx.BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_ballet256256()
{
    std::clock_t st, et;
    Ballet256256 ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ballet256256 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.set_key(user_key, ctx.ENCRYPTION);
        ctx.encrypt_blocks(data, data, SIZE / ctx.BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

void speed_ballet()
{
    speed_ballet128128();
    speed_ballet128256();
    speed_ballet256256();
}