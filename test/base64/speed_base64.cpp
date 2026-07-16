#include <gmlib/base64/provider.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace base64;

static void rand_mem(void* mem, std::size_t size)
{
    std::srand((unsigned int)std::time(nullptr));
    std::uint8_t* data = (std::uint8_t*)mem;
    for (std::size_t i = 0; i < size; i++)
    {
        data[i] = std::rand() % 256;
    }
}

constexpr int LOOP = 1000;
constexpr int SIZE = 1024 * 1024;

static void speed_provider(const Base64Provider* p)
{
    static std::uint8_t data[SIZE * 2];
    static char         base64str[SIZE * 8];
    double              time_s, speed_Mbps;
    static std::size_t  base64str_len;
    std::clock_t        st, et;

    rand_mem(data, SIZE);
    std::printf("  speed base64 [%s] ... \n", p->algo_name);
    // test encode
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        p->base64_encode(base64str, data, SIZE);
        base64str_len = p->base64_encode_strl(SIZE);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * LOOP / 1024.0 / 1024.0 / time_s;
    std::printf("    [encode] %f Mbps\n", speed_Mbps);
    // test decode
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        p->base64_decode(data, base64str, base64str_len);
    }
    et         = std::clock();
    time_s     = (double)(et - st) / CLOCKS_PER_SEC;
    speed_Mbps = 8.0 * SIZE * LOOP / 1024.0 / 1024.0 / time_s;
    std::printf("    [decode] %f Mbps\n", speed_Mbps);
}

void speed_base64()
{
    std::puts("speed base64 ... ");
    const char* const* name_list = get_base64_supported_provider_names();
    for (int i = 0; name_list[i] != nullptr; i++)
    {
        const Base64Provider* p = get_base64_provider(name_list[i]);
        if (p == nullptr)
        {
            std::fprintf(stderr,
                         "err: get_base64_provider('%s') returned null\n",
                         name_list[i]);
            std::exit(-1);
        }
        speed_provider(p);
    }
}
