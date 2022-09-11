#include <gmlib/err.h>
#include <gmlib/hash/sm3.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdlib.h>

static uint8_t msg1[] = {'a', 'b', 'c'};

static uint8_t digest1[] = {
    0x66, 0xC7, 0xF0, 0xF4, 0x62, 0xEE, 0xED, 0xD9,  //
    0xD1, 0xF2, 0xD4, 0x6B, 0xDC, 0x10, 0xE4, 0xE2,  //
    0x41, 0x67, 0xC4, 0x87, 0x5C, 0xF2, 0xF7, 0xA2,  //
    0x29, 0x7D, 0xA0, 0x2B, 0x8F, 0x4B, 0xA8, 0xE0,  //
};

static uint8_t msg2[] = {
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
    0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,  //
};

static uint8_t digest2[] = {
    0xDE, 0xBE, 0x9F, 0xF9, 0x22, 0x75, 0xB8, 0xA1,  //
    0x38, 0x60, 0x48, 0x89, 0xC1, 0x8E, 0x5A, 0x4D,  //
    0x6F, 0xDB, 0x70, 0xE5, 0x38, 0x7E, 0x57, 0x65,  //
    0x29, 0x3D, 0xCB, 0xA3, 0x9C, 0x0C, 0x57, 0x32,  //
};

static uint8_t out[SM3_DIGEST_SIZE];

void test_sm3_alg() {
    SM3_CTX ctx;
    // 测试点1
    sm3_init(&ctx);
    sm3_update(msg1, sizeof(msg1), &ctx);
    sm3_final(out, &ctx);
    if (memcmp(out, digest1, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("Err in sm3");
        goto error;
    }
    // 测试点2
    sm3_init(&ctx);
    sm3_update(msg2, sizeof(msg2), &ctx);
    sm3_final(out, &ctx);
    if (memcmp(out, digest2, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("Err in sm3");
        goto error;
    }
    // 测试点3
    sm3_init(&ctx);
    sm3_update(msg2, sizeof(msg2) - 3, &ctx);
    sm3_update(msg2 + sizeof(msg2) - 3, 3, &ctx);
    sm3_final(out, &ctx);
    if (memcmp(out, digest2, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("Err in sm3");
        goto error;
    }
    return;
error:
    exit(-1);
}
