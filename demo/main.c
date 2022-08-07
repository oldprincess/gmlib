#include <gmlib/utils.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static uint64_t matrix1[256][2];
static uint64_t matrix2[16][2];
#define SIZE 100000000
static uint8_t Lst[SIZE];
int main() {
    srand((unsigned)time(NULL));
    uint64_t x[2] = {0};
    clock_t clk1, clk2;
    rand_mem(matrix1, sizeof(matrix1));
    rand_mem(matrix2, sizeof(matrix1));
    rand_mem(Lst, SIZE);

    clk1 = clock();
    for (int i = 0; i < SIZE; i++) {
        x[0] ^= matrix1[Lst[i]][0];
        x[1] ^= matrix1[Lst[i]][1];
    }
    clk2 = clock();
    printf("big:%d\n", (int)(clk2 - clk1));
    dump_data(x, sizeof(x));

    clk1 = clock();
    for (int i = 0; i < SIZE; i++) {
        x[0] ^= matrix2[Lst[i] & 0xFF][0];
        x[1] ^= matrix2[Lst[i] & 0xFF][1];
        x[0] ^= matrix2[Lst[i] >> 4][0];
        x[1] ^= matrix2[Lst[i] >> 4][1];
    }
    clk2 = clock();
    printf("small:%d\n", (int)(clk2 - clk1));
    dump_data(x, sizeof(x));

    return 0;
}
