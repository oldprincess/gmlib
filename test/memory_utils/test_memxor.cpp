#include <gmlib/memory_utils/memxor.h>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdexcept>

#include "test.h"

static void mem_xor(std::uint8_t       *out,
                    const std::uint8_t *in1,
                    const std::uint8_t *in2,
                    std::size_t         size) noexcept
{
    for (std::size_t i = 0; i < size; i++)
    {
        out[i] = in1[i] ^ in2[i];
    }
}

static void rand_mem(std::uint8_t *out, std::size_t size) noexcept
{
    for (std::size_t i = 0; i < size; i++)
    {
        out[i] = std::rand() % 256;
    }
}

void test_memxor()
{
    std::srand((unsigned int)std::time(nullptr));
    static constexpr std::size_t SIZE = 2048;
    static std::uint8_t          mem1[SIZE], mem2[SIZE], mem3[SIZE], mem4[SIZE];
    for (int i = 0; i < 100; i++)
    {
        rand_mem(mem1, SIZE);
        rand_mem(mem2, SIZE);
        mem_xor(mem3, mem1, mem2, SIZE);
        // test memxor_n
        rand_mem(mem4, SIZE);
        memory_utils::memxor_n(mem4, mem1, mem2, SIZE);
        if (std::memcmp(mem3, mem4, SIZE) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 1
        rand_mem(mem4, SIZE);
        memory_utils::memxor<1>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 1) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 2
        rand_mem(mem4, SIZE);
        memory_utils::memxor<2>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 2) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 4
        rand_mem(mem4, SIZE);
        memory_utils::memxor<4>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 4) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 8
        rand_mem(mem4, SIZE);
        memory_utils::memxor<8>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 8) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 16
        rand_mem(mem4, SIZE);
        memory_utils::memxor<16>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 16) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 32
        rand_mem(mem4, SIZE);
        memory_utils::memxor<32>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 32) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 64
        rand_mem(mem4, SIZE);
        memory_utils::memxor<64>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 64) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 128
        rand_mem(mem4, SIZE);
        memory_utils::memxor<128>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 128) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 256
        rand_mem(mem4, SIZE);
        memory_utils::memxor<256>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 256) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor 512
        rand_mem(mem4, SIZE);
        memory_utils::memxor<512>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, 512) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
        // test memxor SIZE
        rand_mem(mem4, SIZE);
        memory_utils::memxor<SIZE>(mem4, mem1, mem2);
        if (std::memcmp(mem3, mem4, SIZE) != 0)
        {
            throw std::runtime_error("err in test_memxor");
        }
    }
}