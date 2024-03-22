#include <gmlib/aes/internal/aes_lut.h>

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

using namespace aes::internal::lut;

static void speed_aes128_lut()
{
    std::clock_t st, et;
    Aes128CTX    ctx;

    constexpr int         loop = 10000;
    constexpr std::size_t SIZE = 4096;
    double                time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed aes128 lut ... ");
    aes128_enc_key_init(&ctx, user_key);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        aes128_enc_blocks(&ctx, data, data, SIZE / 16);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_aes192_lut()
{
    std::clock_t st, et;
    Aes192CTX    ctx;

    constexpr int         loop = 10000;
    constexpr std::size_t SIZE = 4096;
    double                time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed aes192 lut ... ");
    aes192_enc_key_init(&ctx, user_key);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        aes192_enc_blocks(&ctx, data, data, SIZE / 16);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

static void speed_aes256_lut()
{
    std::clock_t st, et;
    Aes256CTX    ctx;

    constexpr int         loop = 10000;
    constexpr std::size_t SIZE = 4096;
    double                time_s, speed_Mbps;

    std::uint8_t user_key[32];

    std::uint8_t* data = new std::uint8_t[SIZE];

    rand_mem(data, SIZE);
    rand_mem(user_key, 32);

    std::printf("speed aes256 lut ... ");
    aes256_enc_key_init(&ctx, user_key);
    st = std::clock();
    for (int i = 0; i < loop; i++)
    {
        aes256_enc_blocks(&ctx, data, data, SIZE / 16);
    }
    et = std::clock();

    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * loop / 1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps\n", speed_Mbps);

    delete[] data;
}

void speed_aes_lut()
{
    speed_aes128_lut();
    speed_aes192_lut();
    speed_aes256_lut();
}