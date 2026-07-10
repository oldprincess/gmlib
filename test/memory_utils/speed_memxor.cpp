#include <gmlib/memory_utils/memxor.h>

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "speed.h"

static void rand_mem(std::uint8_t *out, std::size_t size) noexcept
{
    for (std::size_t i = 0; i < size; i++)
    {
        out[i] = static_cast<std::uint8_t>(std::rand() % 256);
    }
}

static std::uint64_t checksum(const std::uint8_t *in, std::size_t size) noexcept
{
    std::uint64_t ret = 0;
    for (std::size_t i = 0; i < size; i++)
    {
        ret += in[i];
    }
    return ret;
}

static void speed_memxor_size(std::size_t size)
{
    constexpr std::size_t TARGET_BYTES = 1024ULL * 1024ULL * 1024ULL;

    std::vector<std::uint8_t> in1(size);
    std::vector<std::uint8_t> in2(size);
    std::vector<std::uint8_t> out(size);
    std::size_t loop = std::max<std::size_t>(1, TARGET_BYTES / size);

    rand_mem(in1.data(), size);
    rand_mem(in2.data(), size);

    std::printf("speed memxor_n %zu bytes, loop=%zu ... ", size, loop);
    auto st = std::chrono::steady_clock::now();
    for (std::size_t i = 0; i < loop; i++)
    {
        memory_utils::memxor_n(out.data(), in1.data(), in2.data(), size);
    }
    auto et = std::chrono::steady_clock::now();

    double time_s = std::chrono::duration<double>(et - st).count();
    double mbps = 8.0 * static_cast<double>(size) * static_cast<double>(loop) /
                  1024.0 / 1024.0 / time_s;
    std::printf("%f Mbps, checksum=%llu\n", mbps,
                static_cast<unsigned long long>(checksum(out.data(), size)));
}

void speed_memxor()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    speed_memxor_size(64);
    speed_memxor_size(256);
    speed_memxor_size(1024);
    speed_memxor_size(4096);
    speed_memxor_size(65536);
    speed_memxor_size(1048576);
}
