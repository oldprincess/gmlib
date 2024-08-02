#include <gmlib/md5/internal/md5_common.h>

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

using namespace md5::internal::common;

constexpr std::size_t MSG_SIZE = 4096;
constexpr int         LOOP     = 10000;

void speed_md5_common()
{
    Md5CTX       ctx;
    std::uint8_t digest[MD5_DIGEST_SIZE];
    std::uint8_t msg[MSG_SIZE];
    std::clock_t st, et;
    double       time_s, speed_Mbps;

    rand_mem(msg, MSG_SIZE);
    std::printf("speed md5 common ... ");
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        md5_init(&ctx);
        md5_update_blocks(&ctx, msg, MSG_SIZE / MD5_BLOCK_SIZE);
        md5_final_block(&ctx, digest, nullptr, 0);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = LOOP * MSG_SIZE * 8 / time_s / 1024.0 / 1024.0;
    std::printf("%f Mbps\n", speed_Mbps);
}