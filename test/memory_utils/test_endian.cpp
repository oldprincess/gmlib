#include <gmlib/memory_utils/endian.h>

#include <cstring>
#include <stdexcept>

void test_endian()
{
    std::uint8_t mem1[1] = {0x11};
    std::uint8_t mem2[2] = {0x11, 0x22};
    std::uint8_t mem4[4] = {0x11, 0x22, 0x33, 0x44};
    std::uint8_t mem8[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    std::uint8_t  n1_le = 0x11;
    std::uint8_t  n1_be = 0x11;
    std::uint16_t n2_le = 0x2211;
    std::uint16_t n2_be = 0x1122;
    std::uint32_t n4_le = 0x44332211U;
    std::uint32_t n4_be = 0x11223344U;
    std::uint64_t n8_le = 0x8877665544332211ULL;
    std::uint64_t n8_be = 0x1122334455667788ULL;

    if (memory_utils::load8_le(mem1) != n1_le ||
        memory_utils::load8_be(mem1) != n1_be)
    {
        throw std::runtime_error("err in endian load8");
    }
    if (memory_utils::load16_le(mem2) != n2_le ||
        memory_utils::load16_be(mem2) != n2_be)
    {
        throw std::runtime_error("err in endian load16");
    }
    if (memory_utils::load32_le(mem4) != n4_le ||
        memory_utils::load32_be(mem4) != n4_be)
    {
        throw std::runtime_error("err in endian load32");
    }
    if (memory_utils::load64_le(mem8) != n8_le ||
        memory_utils::load64_be(mem8) != n8_be)
    {
        throw std::runtime_error("err in endian load64");
    }

    std::uint8_t data1[1], data2[2], data4[4], data8[8];
    memory_utils::store8_le(data1, n1_le);
    if (std::memcmp(data1, mem1, 1) != 0)
    {
        throw std::runtime_error("err in endian store8");
    }
    memory_utils::store8_be(data1, n1_be);
    if (std::memcmp(data1, mem1, 1) != 0)
    {
        throw std::runtime_error("err in endian store8");
    }

    memory_utils::store16_le(data2, n2_le);
    if (std::memcmp(data2, mem2, 2) != 0)
    {
        throw std::runtime_error("err in endian store16");
    }
    memory_utils::store16_be(data2, n2_be);
    if (std::memcmp(data2, mem2, 2) != 0)
    {
        throw std::runtime_error("err in endian store16");
    }

    memory_utils::store32_le(data4, n4_le);
    if (std::memcmp(data4, mem4, 4) != 0)
    {
        throw std::runtime_error("err in endian store32");
    }
    memory_utils::store32_be(data4, n4_be);
    if (std::memcmp(data4, mem4, 4) != 0)
    {
        throw std::runtime_error("err in endian store32");
    }

    memory_utils::store64_le(data8, n8_le);
    if (std::memcmp(data8, mem8, 8) != 0)
    {
        throw std::runtime_error("err in endian store64");
    }
    memory_utils::store64_be(data8, n8_be);
    if (std::memcmp(data8, mem8, 8) != 0)
    {
        throw std::runtime_error("err in endian store64");
    }
}