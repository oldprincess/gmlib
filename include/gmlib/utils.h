/**
 * @file utils.h
 * @brief 功能函数
 *
 * 参考资料：<br>
 * [1]. openssl 3.0 bio_dump 模块 <br>
 *
 * 函数 dump_data 参考了 openssl bio_dump 的 log 形式；
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

/// @brief 以大端形式读取32比特数
/// @param[in]  src     源地址
/// @return 32比特数
uint32_t loadu32_be(uint8_t* src);

/// @brief 以大端形式存储32比特数
/// @param[out] dst     目的地址
/// @param[in]  n       待存储32比特数
void storeu32_be(uint8_t* dst, uint32_t n);

/// @brief 以大端形式读取64比特数
/// @param[in]  src     源地址
/// @return 64比特数
uint64_t loadu64_be(uint8_t* src);

/// @brief 以大端形式存储64比特数
/// @param[out] dst     目的地址
/// @param[in]  n       待存储64比特数
void storeu64_be(uint8_t* dst, uint64_t n);

/// @brief 打印内存数据
/// @param[in]  d       内存地址
/// @param[in]  len     长度
void dump_data(uint8_t* d, int len);

/// @brief 字节异或
/// @param[out] dst     目的地址
/// @param[in]  a       内存段1
/// @param[in]  b       内存段2
/// @param[in]  size    内存长度
void memxor(uint8_t* dst, uint8_t* a, uint8_t* b, int size);

/// @brief 内存随机化
/// @param[out] mem     目的地址
/// @param[in]  size    内存长度
void rand_mem(uint8_t* mem, int size);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // UTILS_H
