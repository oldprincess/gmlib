#include <ctype.h>
#include <gmlib/utils.h>
#include <stdio.h>
#include <stdlib.h>

/// @brief 以大端形式读取32比特数
uint32_t loadu32_be(uint8_t* data) {
    uint32_t n = data[3];
    n |= data[2] << 8;
    n |= data[1] << 16;
    n |= data[0] << 24;
    return n;
}

/// @brief 以大端形式读取64比特数
uint64_t loadu64_be(uint8_t* data) {
    return ((uint64_t)loadu32_be(data) << 32) | loadu32_be(data + 4);
}

/// @brief 以大端形式存储32比特数
void storeu32_be(uint8_t* dst, uint32_t n) {
    dst[3] = n & 0xFF;
    dst[2] = (n >> 8) & 0xFF;
    dst[1] = (n >> 16) & 0xFF;
    dst[0] = (n >> 24) & 0xFF;
}

/// @brief 以大端形式存储64比特数
void storeu64_be(uint8_t* dst, uint64_t n) {
    storeu32_be(dst, n >> 32);             // 高32位
    storeu32_be(dst + 4, n & UINT32_MAX);  // 低32位
}

/// @brief 打印内存数据
void dump_data(uint8_t* d, int size) {
    printf("dump data: size = %d\n", size);  // 打印头部信息
    // 16 字节一行
    for (int i = 0; i < size; i += 16) {
        printf("%04x - ", i);  // 行索引
        // 打印该行的16个字节
        for (int j = i; j < i + 16; j++) {
            if (j < size) {
                printf("%02x ", d[j]);
            } else {
                printf("   ");  // 超出内存数据范围(3空格)
            }
        }
        putchar(' ');  // 1空格
        // 输出对应数据的ascii码
        for (int j = i; j < i + 16; j++) {
            if (j < size) {
                if (isprint(d[j])) {
                    putchar(d[j]);  // 可打印字符
                } else {
                    putchar('.');  // 不可打印字符
                }
            } else {
                putchar(' ');  // 超出内存数据范围(1空格)
            }
        }
        puts("");  // 行末换行
    }
    puts("");  // 最终换行
}

/// @brief 字节异或
void memxor(uint8_t* dst, uint8_t* a, uint8_t* b, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = a[i] ^ b[i];
    }
}

#include <time.h>
/// @brief 内存随机化
void rand_mem(uint8_t* mem, int size) {
    static int init = 0;
    if (init == 0) {
        // 初始化随机数
        srand((unsigned)time(NULL));
        init = 1;
    }
    for (int i = 0; i < size; i++) {
        mem[i] = rand() % 256;
    }
}
