#include <gmlib/md5/md5.h>

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

constexpr std::size_t MSG_SIZE = 4096;
constexpr int         LOOP     = 10000;

void speed_md5()
{
    md5::MD5     ctx;
    std::uint8_t digest[md5::MD5::DIGEST_SIZE];
    std::uint8_t msg[MSG_SIZE];
    std::clock_t st, et;
    double       time_s, speed_Mbps;

    rand_mem(msg, MSG_SIZE);
    std::printf("speed md5 %s ... ", ctx.fetch_impl_algo());
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