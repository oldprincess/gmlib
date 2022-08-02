#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

/// @brief 以大端形式读取32比特数
uint32_t loadu32_be(uint8_t* src);

/// @brief 以大端形式存储32比特数
void storeu32_be(uint8_t* dst, uint32_t n);

/// @brief 以大端形式存储64比特数
void storeu64_be(uint8_t* dst, uint64_t n);

/// @brief 打印内存数据
void dump_data(uint8_t* d, int len);

/// @brief 字节异或
void memxor(uint8_t* dst, uint8_t* a, uint8_t* b, int size);

/// @brief 内存随机化
void rand_mem(uint8_t* mem, int size);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // UTILS_H
