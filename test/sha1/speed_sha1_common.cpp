#include <gmlib/sha1/internal/sha1_common.h>

#if defined(SHA1_IMPL_COMMON)

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

using namespace sha1::internal::common;

constexpr std::size_t MSG_SIZE = 4096;
constexpr int         LOOP     = 10000;

void speed_sha1_common()
{
    Sha1CTX      ctx;
    std::uint8_t digest[SHA1_DIGEST_SIZE];
    std::uint8_t msg[MSG_SIZE];
    std::clock_t st, et;
    double       time_s, speed_Mbps;

    rand_mem(msg, MSG_SIZE);
    std::printf("speed sha1 common ... ");
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        sha1_init(&ctx);
        sha1_update_blocks(&ctx, msg, MSG_SIZE / SHA1_BLOCK_SIZE);
        sha1_final_block(&ctx, digest, nullptr, 0);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = LOOP * MSG_SIZE * 8 / time_s / 1024.0 / 1024.0;
    std::printf("%f Mbps\n", speed_Mbps);
}
#else
void speed_sha1_common()
{
}
#endif