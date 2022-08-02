#include <gmlib/ec.h>

#define BINT256_DEFINE(a7, a6, a5, a4, a3, a2, a1, a0) \
    { .dsize = 8, .sign = 1, .d = {a0, a1, a2, a3, a4, a5, a6, a7}, }

#define BINT192_DEFINE(a5, a4, a3, a2, a1, a0) \
    { .dsize = 6, .sign = 1, .d = {a0, a1, a2, a3, a4, a5}, }

EC_CTX SM2_Fp256_CTX = {
    // p=FFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF 00000000 FFFFFFFF FFFFFFFF
    .p = BINT256_DEFINE(0xFFFFFFFE,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0x00000000,
                        0xFFFFFFFF,
                        0xFFFFFFFF),
    // a=FFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF 00000000 FFFFFFFF FFFFFFFC
    .a = BINT256_DEFINE(0xFFFFFFFE,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0x00000000,
                        0xFFFFFFFF,
                        0xFFFFFFFC),
    // b=28E9FA9E 9D9F5E34 4D5A9E4B CF6509A7 F39789F5 15AB8F92 DDBCBD41 4D940E93
    .b = BINT256_DEFINE(0x28E9FA9E,
                        0x9D9F5E34,
                        0x4D5A9E4B,
                        0xCF6509A7,
                        0xF39789F5,
                        0x15AB8F92,
                        0xDDBCBD41,
                        0x4D940E93),
    // G=(x,y)
    // x=32C4AE2C 1F198119 5F990446 6A39C994 8FE30BBF F2660BE1 715A4589 334C74C7
    // y=BC3736A2 F4F6779C 59BDCEE3 6B692153 D0A9877C C62A4740 02DF32E5 2139F0A0
    .G = {.x = BINT256_DEFINE(0x32C4AE2C,
                              0x1F198119,
                              0x5F990446,
                              0x6A39C994,
                              0x8FE30BBF,
                              0xF2660BE1,
                              0x715A4589,
                              0x334C74C7),
          .y = BINT256_DEFINE(0xBC3736A2,
                              0xF4F6779C,
                              0x59BDCEE3,
                              0x6B692153,
                              0xD0A9877C,
                              0xC62A4740,
                              0x02DF32E5,
                              0x2139F0A0),
          .infinity = 0},
    // n=FFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF 7203DF6B 21C6052B 53BBF409 39D54123
    .n = BINT256_DEFINE(0xFFFFFFFE,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0xFFFFFFFF,
                        0x7203DF6B,
                        0x21C6052B,
                        0x53BBF409,
                        0x39D54123),
};
