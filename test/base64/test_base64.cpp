#include <gmlib/base64/provider.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace base64;

// clang-format off
/*
import base64
import os

b = os.urandom(32)
s = base64.b64encode(b)

for item in b:
    print('0x' + hex(item)[2::].zfill(2), end=', ')
print()
print(s)
*/
// clang-format on

static void test_provider(const Base64Provider* p)
{
    static std::uint8_t data1[32] = {
        0x9e, 0xfd, 0x44, 0x24, 0x10, 0x64, 0xb5, 0xfe, 0xde, 0x6e, 0xa1,
        0x23, 0x7e, 0x50, 0x62, 0x2a, 0xb4, 0xdf, 0x2b, 0x94, 0x1e, 0xb1,
        0xf9, 0x3e, 0x4e, 0x27, 0x27, 0xf7, 0x96, 0x9a, 0xe5, 0xe4,
    };
    static char b64_1[] = "nv1EJBBktf7ebqEjflBiKrTfK5Qesfk+Ticn95aa5eQ=";
    static std::uint8_t data2[32] = {
        0x3d, 0x8b, 0xc5, 0x24, 0x8c, 0xd7, 0x37, 0xf8, 0x53, 0x11, 0x63,
        0xae, 0x45, 0x01, 0x53, 0xbe, 0x3c, 0x90, 0xb9, 0x78, 0x98, 0x50,
        0xe1, 0x86, 0xe3, 0x33, 0xf9, 0xe3, 0x82, 0x35, 0xca, 0x58,
    };
    static char b64_2[] = "PYvFJIzXN/hTEWOuRQFTvjyQuXiYUOGG4zP544I1ylg=";
    static std::uint8_t data3[16] = {
        0xc2, 0x88, 0xf3, 0x5f, 0xcc, 0x22, 0x04, 0x6e,
        0x68, 0x59, 0x0a, 0xf2, 0x8a, 0x81, 0x94, 0xd5,
    };
    static char         b64_3[]   = "wojzX8wiBG5oWQryioGU1Q==";
    static std::uint8_t data4[16] = {
        0xb0, 0x86, 0x55, 0xe0, 0x9c, 0x12, 0xe7, 0xc9,
        0xf0, 0x0d, 0x98, 0x44, 0x82, 0xb9, 0x45, 0xc9,
    };
    static char b64_4[] = "sIZV4JwS58nwDZhEgrlFyQ==";

    std::uint8_t data[32];
    char         b64[60];

    // test is_b64
    if (!p->base64_is_b64(b64_1, std::strlen(b64_1)))
    {
        std::fprintf(stderr, "err in base64_is_b64 [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }

    // test encode_outl
    if (p->base64_encode_outl(sizeof(data1)) < std::strlen(b64_1))
    {
        std::fprintf(stderr,
                     "err in base64_encode_outl [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }

    // test encode_strl
    if (p->base64_encode_strl(sizeof(data1)) != std::strlen(b64_1))
    {
        std::fprintf(stderr,
                     "err in base64_encode_strl [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }

    // test encode
    p->base64_encode(b64, data1, sizeof(data1));
    if (std::strcmp(b64, b64_1) != 0)
    {
        std::fprintf(stderr, "err in base64_encode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    p->base64_encode(b64, data2, sizeof(data2));
    if (std::strcmp(b64, b64_2) != 0)
    {
        std::fprintf(stderr, "err in base64_encode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    p->base64_encode(b64, data3, sizeof(data3));
    if (std::strcmp(b64, b64_3) != 0)
    {
        std::fprintf(stderr, "err in base64_encode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    p->base64_encode(b64, data4, sizeof(data4));
    if (std::strcmp(b64, b64_4) != 0)
    {
        std::fprintf(stderr, "err in base64_encode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }

    // test decode_outl
    if (p->base64_decode_outl(b64_1, std::strlen(b64_1)) != sizeof(data1))
    {
        std::fprintf(stderr,
                     "err in base64_decode_outl [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }

    // test decode
    if (p->base64_decode(data, b64_1, std::strlen(b64_1)))
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    if (std::memcmp(data, data1, sizeof(data1)) != 0)
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    if (p->base64_decode(data, b64_2, std::strlen(b64_2)))
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    if (std::memcmp(data, data2, sizeof(data2)) != 0)
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    if (p->base64_decode(data, b64_3, std::strlen(b64_3)))
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    if (std::memcmp(data, data3, sizeof(data3)) != 0)
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    if (p->base64_decode(data, b64_4, std::strlen(b64_4)))
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }
    if (std::memcmp(data, data4, sizeof(data4)) != 0)
    {
        std::fprintf(stderr, "err in base64_decode [%s], file: %s, line: %d\n",
                     p->algo_name, __FILE__, __LINE__);
        std::exit(-1);
    }

    std::printf("  provider '%s' passed\n", p->algo_name);
}

void test_base64()
{
    const char* const* name_list = get_provider_name_list();
    for (int i = 0; name_list[i] != nullptr; i++)
    {
        const Base64Provider* p = get_provider(name_list[i]);
        if (p == nullptr)
        {
            std::fprintf(stderr, "err: get_provider('%s') returned null\n",
                         name_list[i]);
            std::exit(-1);
        }
        test_provider(p);
    }
}
