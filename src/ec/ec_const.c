#include <gmlib/ec.h>

#define BINT256_DEFINE(a7, a6, a5, a4, a3, a2, a1, a0) \
    { .dsize = 8, .sign = 1, .d = {a0, a1, a2, a3, a4, a5, a6, a7}, }

#define BINT192_DEFINE(a5, a4, a3, a2, a1, a0) \
    { .dsize = 6, .sign = 1, .d = {a0, a1, a2, a3, a4, a5}, }

EC_CTX EC_Fp256_CTX = {
    // p=0x8542D69E_4C044F18_E8B92435_BF6FF7DE_45728391_5C45517D_722EDB8B_08F1DFC3
    .p = BINT256_DEFINE(0x8542D69E,
                        0x4C044F18,
                        0xE8B92435,
                        0xBF6FF7DE,
                        0x45728391,
                        0x5C45517D,
                        0x722EDB8B,
                        0x08F1DFC3),
    // a=0x787968B4_FA32C3FD_2417842E_73BBFEFF_2F3C848B_6831D7E0_EC65228B_3937E498
    .a = BINT256_DEFINE(0x787968B4,
                        0xFA32C3FD,
                        0x2417842E,
                        0x73BBFEFF,
                        0x2F3C848B,
                        0x6831D7E0,
                        0xEC65228B,
                        0x3937E498),
    // b=0x63E4C6D3_B23B0C84_9CF84241_484BFE48_F61D59A5_B16BA06E_6E12D1DA_27C5249A
    .b = BINT256_DEFINE(0x63E4C6D3,
                        0xB23B0C84,
                        0x9CF84241,
                        0x484BFE48,
                        0xF61D59A5,
                        0xB16BA06E,
                        0x6E12D1DA,
                        0x27C5249A),
    // G=(x,y)
    // x=0x421DEBD6_1B62EAB6_746434EB_C3CC315E_32220B3B_ADD50BDC_4C4E6C14_7FEDD43D
    // y=0x0680512B_CBB42C07_D47349D2_153B70C4_E5D7FDFC_BFA36EA1_A85841B9_E46E09A2
    .G = {.x = BINT256_DEFINE(0x421DEBD6,
                              0x1B62EAB6,
                              0x746434EB,
                              0xC3CC315E,
                              0x32220B3B,
                              0xADD50BDC,
                              0x4C4E6C14,
                              0x7FEDD43D),
          .y = BINT256_DEFINE(0x0680512B,
                              0xCBB42C07,
                              0xD47349D2,
                              0x153B70C4,
                              0xE5D7FDFC,
                              0xBFA36EA1,
                              0xA85841B9,
                              0xE46E09A2),
          .infinity = 0},
    // n=0x8542D69E_4C044F18_E8B92435_BF6FF7DD_29772063_0485628D_5AE74EE7_C32E79B7
    .n = BINT256_DEFINE(0x8542D69E,
                        0x4C044F18,
                        0xE8B92435,
                        0xBF6FF7DD,
                        0x29772063,
                        0x0485628D,
                        0x5AE74EE7,
                        0xC32E79B7),
};

EC_CTX EC_Fp192_CTX = {
    // p = 0xBDB6F4FE_3E8B1D9E_0DA8C0D4_6F4C318C_EFE4AFE3_B6B8551F
    .p = BINT192_DEFINE(0xBDB6F4FE,
                        0x3E8B1D9E,
                        0x0DA8C0D4,
                        0x6F4C318C,
                        0xEFE4AFE3,
                        0xB6B8551F),
    // a = 0xBB8E5E8F_BC115E13_9FE6A814_FE48AAA6_F0ADA1AA_5DF91985
    .a = BINT192_DEFINE(0xBB8E5E8F,
                        0xBC115E13,
                        0x9FE6A814,
                        0xFE48AAA6,
                        0xF0ADA1AA,
                        0x5DF91985),
    // b = 0x1854BEBD_C31B21B7_AEFC80AB_0ECD10D5_B1B3308E_6DBF11C1
    .b = BINT192_DEFINE(0x1854BEBD,
                        0xC31B21B7,
                        0xAEFC80AB,
                        0x0ECD10D5,
                        0xB1B3308E,
                        0x6DBF11C1),
    // G=(x,y)
    // x = 0x4AD5F704_8DE709AD_51236DE6_5E4D4B48_2C836DC6_E4106640
    // y = 0x02BB3A02_D4AAADAC_AE24817A_4CA3A1B0_14B52704_32DB27D2
    .G = {.x = BINT192_DEFINE(0x4AD5F704,
                              0x8DE709AD,
                              0x51236DE6,
                              0x5E4D4B48,
                              0x2C836DC6,
                              0xE4106640),
          .y = BINT192_DEFINE(0x02BB3A02,
                              0xD4AAADAC,
                              0xAE24817A,
                              0x4CA3A1B0,
                              0x14B52704,
                              0x32DB27D2),
          .infinity = 0},
    // n = 0xBDB6F4FE_3E8B1D9E_0DA8C0D4_0FC96219_5DFAE76F_56564677
    .n = BINT192_DEFINE(0xBDB6F4FE,
                        0x3E8B1D9E,
                        0x0DA8C0D4,
                        0x0FC96219,
                        0x5DFAE76F,
                        0x56564677),
};
