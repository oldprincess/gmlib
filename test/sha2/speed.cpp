#include <gmlib/sha2/sha2.h>

#include <cstdio>
#include <ctime>
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

using namespace sha2;

constexpr std::size_t MSG_SIZE = 4096;
constexpr int         LOOP     = 10000;

void speed_sha224()
{
    SHA224       ctx;
    std::uint8_t digest[SHA224::DIGEST_SIZE];
    std::uint8_t msg[MSG_SIZE];
    std::clock_t st, et;
    double       time_s, speed_Mbps;

    rand_mem(msg, MSG_SIZE);
    std::printf("speed sha224 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        ctx.reset();
        ctx.do_final(digest, msg, MSG_SIZE);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = LOOP * MSG_SIZE * 8 / time_s / 1024.0 / 1024.0;
    std::printf("%f Mbps\n", speed_Mbps);
}

void speed_sha256()
{
    SHA256       ctx;
    std::uint8_t digest[SHA256::DIGEST_SIZE];
    std::uint8_t msg[MSG_SIZE];
    std::clock_t st, et;
    double       time_s, speed_Mbps;

    rand_mem(msg, MSG_SIZE);
    std::printf("speed sha256 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        ctx.reset();
        ctx.do_final(digest, msg, MSG_SIZE);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = LOOP * MSG_SIZE * 8 / time_s / 1024.0 / 1024.0;
    std::printf("%f Mbps\n", speed_Mbps);
}

void speed_sha384()
{
    SHA384       ctx;
    std::uint8_t digest[SHA384::DIGEST_SIZE];
    std::uint8_t msg[MSG_SIZE];
    std::clock_t st, et;
    double       time_s, speed_Mbps;

    rand_mem(msg, MSG_SIZE);
    std::printf("speed sha384 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        ctx.reset();
        ctx.do_final(digest, msg, MSG_SIZE);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = LOOP * MSG_SIZE * 8 / time_s / 1024.0 / 1024.0;
    std::printf("%f Mbps\n", speed_Mbps);
}

void speed_sha512()
{
    SHA512       ctx;
    std::uint8_t digest[SHA512::DIGEST_SIZE];
    std::uint8_t msg[MSG_SIZE];
    std::clock_t st, et;
    double       time_s, speed_Mbps;

    rand_mem(msg, MSG_SIZE);
    std::printf("speed sha512 %s ... ", ctx.fetch_impl_algo());
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        ctx.reset();
        ctx.do_final(digest, msg, MSG_SIZE);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = LOOP * MSG_SIZE * 8 / time_s / 1024.0 / 1024.0;
    std::printf("%f Mbps\n", speed_Mbps);
}