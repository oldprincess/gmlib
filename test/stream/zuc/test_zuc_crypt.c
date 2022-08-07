#include <gmlib/err.h>
#include <gmlib/stream/zuc.h>
#include <memory.h>
#include <stdlib.h>

static uint8_t CK1[] = {
    0x17, 0x3D, 0x14, 0xBA, 0x50, 0x03, 0x73, 0x1D,
    0x7A, 0x60, 0x04, 0x94, 0x70, 0xF0, 0x0A, 0x29,
};

static uint32_t COUNT1 = 0x66035492;
static uint8_t BEARER1 = 0xF;
static uint8_t DIRECTION1 = 0;
static uint8_t IBS1[] = {
    0x6C, 0xF6, 0x53, 0x40,  // 6F F6 53 40
    0x73, 0x55, 0x52, 0xAB,  // 73 55 52 AB
    0x0C, 0x97, 0x52, 0xFA,  // 0C 97 52 FA
    0x6F, 0x90, 0x25, 0xFE,  // 6F 90 25 FE
    0x0B, 0xD6, 0x75, 0xD9,  // 0B D6 75 D9
    0x00, 0x58, 0x75, 0xB2,  // 00 58 75 B2
    0x00, 0x00, 0x00, 0x00,  // 00 00 00 00
};
static int LENGTH1 = 0xC1;
static uint8_t OBS1[] = {
    0xA6, 0xC8, 0x5F, 0xC6,  //
    0x6A, 0xFB, 0x85, 0x33,  //
    0xAA, 0xFC, 0x25, 0x18,  //
    0xDF, 0xE7, 0x84, 0x94,  //
    0x0E, 0xE1, 0xE4, 0xB0,  //
    0x30, 0x23, 0x8C, 0xC8,  //
    0x00, 0x00, 0x00, 0x00,  //
};

static uint8_t out[1024];
void test_zuc_crypt() {
    zuc_confidentiality_crypt(out, IBS1, LENGTH1, COUNT1, BEARER1, DIRECTION1,
                              CK1);
    if (memcmp(out, OBS1, (LENGTH1 + 7) / 8) != 0) {
        ERR_LOG("Err in zuc confidentiality");
        goto error;
    }
    zuc_confidentiality_crypt(out, OBS1, LENGTH1, COUNT1, BEARER1, DIRECTION1,
                              CK1);
    if (memcmp(out, IBS1, (LENGTH1 + 7) / 8) != 0) {
        ERR_LOG("Err in zuc confidentiality");
        goto error;
    }

    return;
error:
    exit(-1);
}
