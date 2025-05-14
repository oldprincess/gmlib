#include <gmlib/aes/aes.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "speed.h"

static void rand_mem(void* mem, std::size_t size)
{
    std::srand((unsigned int)std::time(nullptr));
    std::uint8_t* data = (std::uint8_t*)mem;
    for (std::size_t i = 0; i < size; i++)
    {
        data[i] = std::rand() % 256;
    }
}

using namespace aes;

constexpr std::size_t SIZE = 4096 * 32;
constexpr int         loop = 10000;

static void speed_aes128()
{
    std::clock_t st, et;
    AES128       ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed aes128 %s ... ", ctx.fetch_impl_algo());
    ctx.set_key(user_key, ctx.ENCRYPTION);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.encrypt_blocks(data, data, SIZE / 16);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_aes192()
{
    std::clock_t st, et;
    AES192       ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed aes192 %s ... ", ctx.fetch_impl_algo());
    ctx.set_key(user_key, ctx.ENCRYPTION);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.encrypt_blocks(data, data, SIZE / 16);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_aes256()
{
    std::clock_t st, et;
    AES256       ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed aes256 %s ... ", ctx.fetch_impl_algo());
    ctx.set_key(user_key, ctx.ENCRYPTION);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ctx.encrypt_blocks(data, data, SIZE / 16);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

void speed_aes()
{
    speed_aes128();
    speed_aes192();
    speed_aes256();
}
