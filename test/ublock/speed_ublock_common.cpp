#include <gmlib/ublock/internal/ublock_common.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "speed.h"

using namespace ublock::internal::common;

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

static void speed_ublock128128_common()
{
    std::clock_t st, et;
    uBlockCTX    ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ublock128128 common ... ");
    ublock128128_enc_key_init(&ctx, user_key);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ublock128128_enc_blocks(&ctx, data, data,
                                SIZE / UBLOCK128128_BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_ublock128256_common()
{
    std::clock_t st, et;
    uBlockCTX    ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ublock128256 common ... ");
    ublock128256_enc_key_init(&ctx, user_key);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ublock128256_enc_blocks(&ctx, data, data,
                                SIZE / UBLOCK128256_BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_ublock256256_common()
{
    std::clock_t st, et;
    uBlockCTX    ctx;

    double time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed ublock256256 common ... ");
    ublock256256_enc_key_init(&ctx, user_key);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        ublock256256_enc_blocks(&ctx, data, data,
                                SIZE / UBLOCK256256_BLOCK_SIZE);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

void speed_ublock_common()
{
    speed_ublock128128_common();
    speed_ublock128256_common();
    speed_ublock256256_common();
}