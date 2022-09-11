#include <gmlib/err.h>
#include <gmlib/hash/sm3.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdlib.h>

static uint8_t msg[64] = {0};
static uint8_t out[SM3_DIGEST_SIZE];

static uint8_t key_1[16] = {0};
static uint8_t digest_1[SM3_DIGEST_SIZE] = {
    0xAB, 0xBC, 0xED, 0x41, 0x5D, 0xF5, 0xCA, 0x97,  //
    0x4A, 0x87, 0xAF, 0xCC, 0x7D, 0xA6, 0x87, 0x57,  //
    0x18, 0xCB, 0x2C, 0x70, 0x3D, 0x61, 0xA1, 0x8C,  //
    0x22, 0x69, 0x22, 0x98, 0xE7, 0xAF, 0xAF, 0x79,  //
};

static uint8_t key_2[512] = {0};
static uint8_t digest_2[SM3_DIGEST_SIZE] = {
    0xDE, 0xD1, 0x64, 0xF9, 0x74, 0x5F, 0x32, 0x78,  //
    0x08, 0x08, 0x0F, 0xB2, 0xD5, 0x94, 0x38, 0xA0,  //
    0xCE, 0x26, 0x24, 0x96, 0xD4, 0x7B, 0xA4, 0x8F,  //
    0x58, 0x10, 0xE5, 0xFC, 0x7C, 0x53, 0x9F, 0x14,  //
};

static uint8_t key_3[SM3_BLOCK_SIZE] = {0};
// digest_3 结果与 digest_1 相同

void test_sm3_hmac() {
    HMAC_SM3_CTX hmctx;
    // 测试样例1
    hmac_sm3_init(key_1, sizeof(key_1), &hmctx);
    hmac_sm3_update(msg, sizeof(msg), &hmctx);
    hmac_sm3_final(out, &hmctx);
    if (memcmp(out, digest_1, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("Err in sm3 hmac");
        goto error;
    }
    // 测试样例2
    hmac_sm3_init(key_2, sizeof(key_2), &hmctx);
    hmac_sm3_update(msg, sizeof(msg), &hmctx);
    hmac_sm3_final(out, &hmctx);
    if (memcmp(out, digest_2, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("Err in sm3 hmac");
        goto error;
    }
    // 测试样例3
    hmac_sm3_init(key_3, sizeof(key_3), &hmctx);
    hmac_sm3_update(msg, sizeof(msg), &hmctx);
    hmac_sm3_final(out, &hmctx);
    if (memcmp(out, digest_1, SM3_DIGEST_SIZE) != 0) {
        ERR_LOG("Err in sm3 hmac");
    }

    return;
error:
    exit(-1);
}
