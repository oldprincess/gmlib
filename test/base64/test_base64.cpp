#include <gmlib/base64/base64.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void test_base64()
{
    static uint8_t data1[32] = {
        0x9e, 0xfd, 0x44, 0x24, 0x10, 0x64, 0xb5, 0xfe, 0xde, 0x6e, 0xa1,
        0x23, 0x7e, 0x50, 0x62, 0x2a, 0xb4, 0xdf, 0x2b, 0x94, 0x1e, 0xb1,
        0xf9, 0x3e, 0x4e, 0x27, 0x27, 0xf7, 0x96, 0x9a, 0xe5, 0xe4,
    };
    static char    b64_1[]   = "nv1EJBBktf7ebqEjflBiKrTfK5Qesfk+Ticn95aa5eQ=";
    static uint8_t data2[32] = {
        0x3d, 0x8b, 0xc5, 0x24, 0x8c, 0xd7, 0x37, 0xf8, 0x53, 0x11, 0x63,
        0xae, 0x45, 0x01, 0x53, 0xbe, 0x3c, 0x90, 0xb9, 0x78, 0x98, 0x50,
        0xe1, 0x86, 0xe3, 0x33, 0xf9, 0xe3, 0x82, 0x35, 0xca, 0x58,
    };
    static char    b64_2[]   = "PYvFJIzXN/hTEWOuRQFTvjyQuXiYUOGG4zP544I1ylg=";
    static uint8_t data3[16] = {
        0xc2, 0x88, 0xf3, 0x5f, 0xcc, 0x22, 0x04, 0x6e,
        0x68, 0x59, 0x0a, 0xf2, 0x8a, 0x81, 0x94, 0xd5,
    };
    static char    b64_3[]   = "wojzX8wiBG5oWQryioGU1Q==";
    static uint8_t data4[16] = {
        0xb0, 0x86, 0x55, 0xe0, 0x9c, 0x12, 0xe7, 0xc9,
        0xf0, 0x0d, 0x98, 0x44, 0x82, 0xb9, 0x45, 0xc9,
    };
    static char b64_4[] = "sIZV4JwS58nwDZhEgrlFyQ==";

    uint8_t data[32];
    char    b64[60];
    // test encode
    base64_encode(b64, data1, sizeof(data1));
    if (strcmp(b64, b64_1) != 0)
    {
        fprintf(stderr, "err in base64_encode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    base64_encode(b64, data2, sizeof(data2));
    if (strcmp(b64, b64_2) != 0)
    {
        fprintf(stderr, "err in base64_encode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    base64_encode(b64, data3, sizeof(data3));
    if (strcmp(b64, b64_3) != 0)
    {
        fprintf(stderr, "err in base64_encode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    base64_encode(b64, data4, sizeof(data4));
    if (strcmp(b64, b64_4) != 0)
    {
        fprintf(stderr, "err in base64_encode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    // test decode
    if (base64_decode(data, b64_1, strlen(b64_1)))
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    if (base64_decode_outl(b64_1, strlen(b64_1)) != sizeof(data1) ||
        memcmp(data, data1, sizeof(data1)) != 0)
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    if (base64_decode(data, b64_2, strlen(b64_2)))
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    if (base64_decode_outl(b64_2, strlen(b64_2)) != sizeof(data2) ||
        memcmp(data, data2, sizeof(data2)) != 0)
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    if (base64_decode(data, b64_3, strlen(b64_3)))
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    if (base64_decode_outl(b64_3, strlen(b64_3)) != sizeof(data3) ||
        memcmp(data, data3, sizeof(data3)) != 0)
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    if (base64_decode(data, b64_4, strlen(b64_4)))
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
    if (base64_decode_outl(b64_4, strlen(b64_4)) != sizeof(data4) ||
        memcmp(data, data4, sizeof(data4)) != 0)
    {
        fprintf(stderr, "err in base64_decode, file: %s, line: %d\n", __FILE__,
                __LINE__);
        exit(-1);
    }
}
