#include "speed.h"

#include <gmlib/ublock/ublock.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace ublock;

constexpr std::size_t SIZE = 4096 * 32;
constexpr int         loop = 100;

static void rand_mem(void* mem, std::size_t size)
{
    std::srand((unsigned int)std::time(nullptr));
    std::uint8_t* data = (std::uint8_t*)mem;
    for (std::size_t i = 0; i < size; i++)
    {
        data[i] = std::rand() % 256;
    }
}

static void speed_ublock128128()
{
    std::clock_t st, et;
    uBlock128128 ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ublock128128 %s ... ", ctx.fetch_impl_algo());

    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.set_key(user_key, uBlock128128::ENCRYPTION);
        ctx.encrypt_blocks(data, data, SIZE / uBlock128128::BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_ublock128256()
{
    std::clock_t st, et;
    uBlock128256 ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ublock128256 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.set_key(user_key, uBlock128256::ENCRYPTION);
        ctx.encrypt_blocks(data, data, SIZE / uBlock128256::BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_ublock256256()
{
    std::clock_t st, et;
    uBlock256256 ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ublock256256 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.set_key(user_key, uBlock256256::ENCRYPTION);
        ctx.encrypt_blocks(data, data, SIZE / uBlock256256::BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

void speed_ublock()
{
    speed_ublock128128();
    speed_ublock128256();
    speed_ublock256256();
}