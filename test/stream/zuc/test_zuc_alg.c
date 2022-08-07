#include <gmlib/err.h>
#include <gmlib/stream/zuc.h>
#include <stdlib.h>

static uint8_t key1[ZUC_KEYLEN] = {0};
static uint8_t iv1[ZUC_IVLEN] = {0};
static uint32_t z1[] = {0x27bede74, 0x018082da};

static uint8_t key2[ZUC_KEYLEN] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

static uint8_t iv2[ZUC_IVLEN] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

static uint32_t z2[] = {0x0657cfa0, 0x7096398b};

static uint8_t key3[ZUC_KEYLEN] = {
    0x3d, 0x4c, 0x4b, 0xe9, 0x6a, 0x82, 0xfd, 0xae,
    0xb5, 0x8f, 0x64, 0x1d, 0xb1, 0x7b, 0x45, 0x5b,
};

static uint8_t iv3[ZUC_IVLEN] = {
    0x84, 0x31, 0x9a, 0xa8, 0xde, 0x69, 0x15, 0xca,
    0x1f, 0x6b, 0xda, 0x6b, 0xfb, 0xd8, 0xc7, 0x66,
};

static uint32_t z3[] = {0x14F1C272, 0x3279C419};

void test_zuc_alg() {
    ZUC_CTX ctx;
    // test 1
    zuc_init(key1, iv1, &ctx);
    for (int i = 0; i < 2; i++) {
        if (z1[i] != zuc_next(&ctx)) {
            ERR_LOG("Err in zuc");
            goto error;
        }
    }
    // test 2
    zuc_init(key2, iv2, &ctx);
    for (int i = 0; i < 2; i++) {
        if (z2[i] != zuc_next(&ctx)) {
            ERR_LOG("Err in zuc");
            goto error;
        }
    }
    // test 3
    zuc_init(key3, iv3, &ctx);
    for (int i = 0; i < 2; i++) {
        if (z3[i] != zuc_next(&ctx)) {
            ERR_LOG("Err in zuc");
            goto error;
        }
    }

    return;
error:
    exit(-1);
}
