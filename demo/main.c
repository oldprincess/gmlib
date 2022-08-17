#include <gmlib/cipher/aes.h>
#include <gmlib/cipher/sm4.h>
#include <gmlib/utils.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
int main() {
    uint8_t x[16];
    clock_t clk1, clk2;
    double time;
    SM4_CTX ctx;

    clk1 = clock();
    for (int i = 0; i < 1e6; i++) {
        sm4_encrypt(x, x, &ctx);
    }
    clk2 = clock();
    time = (double)(clk2 - clk1) / CLOCKS_PER_SEC;
    printf("SM4 clk=%ld, speed=%.4f MB/s\n", clk2 - clk1, 16 / time);

    AES_CTX actx;
    aes128_init(x, &actx);

    clk1 = clock();
    for (int i = 0; i < 1e6; i++) {
        aes_encrypt(x, x, &actx);
    }
    clk2 = clock();
    time = (double)(clk2 - clk1) / CLOCKS_PER_SEC;
    printf("AES clk=%ld, speed=%.4f MB/s\n", clk2 - clk1, 16 / time);

    return 0;
}
