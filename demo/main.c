#include <gmlib/cipher/aes.h>
#include <gmlib/cipher/sm4.h>
#include <gmlib/utils.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
int main() {
    uint8_t x[16];
    clock_t clk1, clk2;
    SM4_CTX ctx;

    clk1 = clock();
    for (int i = 0; i < 1e6; i++) {
        sm4_encrypt(x, x, &ctx);
    }
    clk2 = clock();
    printf("SM4 clk=%ld\n", clk2 - clk1);

    AES_CTX actx;
    aes128_init(x, &actx);

    clk1 = clock();
    for (int i = 0; i < 1e6; i++) {
        aes_encrypt(x, x, &actx);
    }
    clk2 = clock();
    printf("AES clk=%ld\n", clk2 - clk1);

    return 0;
}
