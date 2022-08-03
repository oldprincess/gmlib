#include <ctype.h>
#include <gmlib/utils.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t loadu32_be(uint8_t* data) {
    uint32_t n = data[3];
    n |= data[2] << 8;
    n |= data[1] << 16;
    n |= data[0] << 24;
    return n;
}

void storeu32_be(uint8_t* dst, uint32_t n) {
    dst[3] = n & 0xFF;
    dst[2] = (n >> 8) & 0xFF;
    dst[1] = (n >> 16) & 0xFF;
    dst[0] = (n >> 24) & 0xFF;
}

void storeu64_be(uint8_t* dst, uint64_t n) {
    storeu32_be(dst, n >> 32);
    storeu32_be(dst + sizeof(uint32_t), n & UINT32_MAX);
}

void dump_data(uint8_t* d, int size) {
    // log header
    printf("dump data: size = %d\n", size);
    // 16 Byte 1 Batch
    for (int i = 0; i < size; i += 16) {
        printf("%04x - ", i);
        putchar('\t');
        for (int j = i; j < i + 16; j++) {
            if (j < size) {
                printf("%02x ", d[j]);
            } else {
                // out of size
                printf("   ");
            }
        }
        putchar('\t');
        for (int j = i; j < i + 16; j++) {
            if (j < size) {
                // can print or not
                if (isprint(d[j])) {
                    putchar(d[j]);
                } else {
                    putchar('.');
                }
            } else {
                // out of size
                putchar(' ');
            }
        }
        puts("");
    }
    puts("");
}

void memxor(uint8_t* dst, uint8_t* a, uint8_t* b, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = a[i] ^ b[i];
    }
}

void rand_mem(uint8_t* mem, int size) {
    for (int i = 0; i < size; i++) {
        mem[i] = rand() % 256;
    }
}
