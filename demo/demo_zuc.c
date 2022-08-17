#include <gmlib/stream/zuc.h>
#include <stdio.h>

static uint8_t key[ZUC_KEYLEN] = {0};
static uint8_t iv[ZUC_IVLEN] = {0};

int main() {
    ZUC_CTX ctx;
    uint32_t Z;
    // test 1
    zuc_init(key, iv, &ctx);
    Z = zuc_next(&ctx);
    printf("%08x, ", Z);  // 27bede74
    Z = zuc_next(&ctx);
    printf("%08x, ", Z);  // 018082da

    return 0;
}
