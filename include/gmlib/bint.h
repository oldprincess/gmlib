#ifndef BINT_H
#define BINT_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

/// 大整数BINT最大比特数
#define GMLIB_BINT_BITS 512

/// 大整数BINT最大字数（32bit为一个字）
#define GMLIB_BINT_SIZE (GMLIB_BINT_BITS / 32)

#define BINT_HEX 16
#define BINT_DEC 10
#define BINT_BIN 2
#define BINT_BIG_ENDIAN 1
#define BINT_LITTLE_ENDIAN 0

/// BINT结构
typedef struct BINT {
    uint32_t d[GMLIB_BINT_SIZE];  // GMLIB_BINT_BITS 内存空间
    int sign;                     // 符号（-1负数，1正数，0零）
    int dsize;                    // 数据长度
} BINT;

extern BINT BINT_ONE;

extern BINT BINT_TWO;

extern BINT BINT_THREE;

// =======================================
// ============ 类型转换 ==================
// =======================================

/// @brief 从字符串中读入大整数
/// @param[out] n       大整数指针
/// @param[in]  str     字符串
/// @param[in]  radix   进制数
/// @return 错误码（0表示无错误）
int bint_from_str(BINT* n, char* str, int radix);

/// @brief 大整数转字符串
/// @param[in]  n       大整数指针
/// @param[out] str     字符串
/// @param[in]  radix   进制数
/// @return 错误码（0表示无错误）
int bint_to_str(BINT* n, char* str, int radix);

/// @brief 大整数转字符串（非线程安全，用于打印输出）
/// @param[in]  n       大整数指针
/// @param[in]  radix   进制数
/// @return 字符串指针（不需要free）
char* bint_fast_to_str(BINT* n, int radix);

/// @brief 从整数中读入大整数
/// @param[out] n   大整数指针
/// @param[in]  u   32bit无符号整数
void bint_from_u32(BINT* n, uint32_t u);

/// @brief 大整数转32位整数
/// @param[out] u   32bit无符号整数指针
/// @param[in]  n   大整数指针
/// @return 错误码（0表示无错误）
int bint_to_u32(uint32_t* u, BINT* n);

/// @brief 从字节串中读取大整数
/// @param[out] n       大整数指针
/// @param[in]  b       字节串
/// @param[in]  bsize   字节串长度
/// @param[in]  endian  大小端序（1表示大端序）
/// @return 错误码（0表示无错误）
int bint_from_bytes(BINT* n, uint8_t* b, int bsize, int endian);

/// @brief 大整数转字节串
/// @param[out] n       大整数指针
/// @param[in]  b       字节串
/// @param[in]  bsize   字节串长度
/// @param[in]  endian  大小端序（1表示大端序）
/// @return 错误码（0表示无错误）
int bint_to_bytes(BINT* n, uint8_t* b, int bsize, int endian);

// =======================================
// ============ 算数运算 ==================
// =======================================

/// @brief 大整数加法
/// @param[out] r   和 sum
/// @param[in]  n1  被加数 augend
/// @param[in]  n2  加数 addend
/// @return 错误码（0表示无错误）
int bint_add(BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数减法
/// @param[out] r   差 difference
/// @param[in]  n1  被减数 minuend
/// @param[in]  n2  减数 subtrahend
/// @return 错误码（0表示无错误）
int bint_sub(BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数乘法
/// @param[out] r   乘积 product
/// @param[in]  n1  被乘数 multiplicand
/// @param[in]  n2  乘数 multiplier
/// @return 错误码（0表示无错误）
int bint_mul(BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数二次幂
/// @param[out] r   乘积 product
/// @param[in]  n   乘数
/// @return 错误码（0表示无错误）
int bint_sqr(BINT* r, BINT* n);

/// @brief 大整数乘法
/// @param[out] r   乘积 product
/// @param[in]  n1  被乘数 multiplicand
/// @param[in]  n2  乘数 multiplier
/// @return 错误码（0表示无错误）
int bint_mul_u32(BINT* r, BINT* n1, uint32_t n2);

/// @brief 大整数除法
/// @param[out] q   商（可以为NULL） quotient
/// @param[out] r   余数（可以为NULL） remainder
/// @param[in]  n1  被除数 dividend
/// @param[in]  n2  除数 divisor
/// @return 错误码（0表示无错误）
int bint_divmod(BINT* q, BINT* r, BINT* n1, BINT* n2);

/// @brief 大整数除法
/// @param[out] q   商（可以为NULL） quotient
/// @param[out] r   余数（可以为NULL） remainder
/// @param[in]  n1  被除数 dividend
/// @param[in]  n2  除数 divisor
/// @return 错误码（0表示无错误）
int bint_divmod_u32(BINT* q, uint32_t* r, BINT* n1, uint32_t n2);

/// @brief 大整数求幂
/// @param[out] r   幂 power
/// @param[in]  n   底数 base
/// @param[in]  e   指数 exponent
/// @param[in]  mod 模数（可以为NULL）
/// @return 错误码（0表示无错误）
int bint_pow(BINT* r, BINT* n, BINT* e, BINT* mod);

/// @brief 大整数求幂
/// @param[out] r   幂 power
/// @param[in]  n   底数 base
/// @param[in]  e   指数 exponent
/// @param[in]  mod 模数（可以为NULL）
/// @return 错误码（0表示无错误）
int bint_pow_u32(BINT* r, BINT* n, uint32_t e, BINT* mod);

/// @brief 大整数逻辑（算数）左移
/// @param[out] r
/// @param[in]  n
/// @param[in]  bits
/// @return 错误码（0表示无错误）
int bint_sll(BINT* r, BINT* n, int bits);

/// @brief 大整数算数右移
/// @param[out] r
/// @param[in]  n
/// @param[in]  bits
/// @return 错误码（0表示无错误）
int bint_sra(BINT* r, BINT* n, int bits);

// =======================================
// ============ bint utils ===============
// =======================================

/// @brief 大整数比较
/// @param[in] n1
/// @param[in] n2
/// @return 1(n1>n2), 0(n1=n2), -1(n1<n2)
int bint_cmp(BINT* n1, BINT* n2);

/// @brief 是否为零
/// @param[in] n
/// @return 1(yes), 0(no)
static inline int bint_is_zero(BINT* n) {
    return n->dsize == 0;
}

/// @brief 是否为负
/// @param[in] n
/// @return 1(yes), 0(no)
static inline int bint_is_neg(BINT* n) {
    return n->sign == -1;
}

/// @brief 是否为正
/// @param[in] n
/// @return 1(yes), 0(no)
static inline int bint_is_pos(BINT* n) {
    return n->sign == 1;
}

/// @brief 设置大整数为零
/// @param[inout] n
static inline void bint_set_zero(BINT* n) {
    n->dsize = 0;
    n->sign = 0;
}

/// @brief 是否是奇数
/// @param[in]  n
/// @return 1(奇数), 0(偶数)
static inline int bint_is_odd(BINT* n) {
    return (n->d[0] & 1) == 1 && n->dsize != 0;
}

/// @brief 大整数拷贝
/// @param[out] r
/// @param[in]  n
void bint_copy(BINT* r, BINT* n);

/// @brief 大整数取负
/// @param[out] r   结果指针
/// @param[in]  n   大整数指针
/// @return 错误码（0表示无错误）
void bint_neg(BINT* r, BINT* n);

/// @brief 大整数的字节数
/// @param[in] n
/// @return 字节数
int bint_bytes_len(BINT* n);

/// @brief 大整数的比特数
/// @param[in] n
/// @return bits
int bint_bits_len(BINT* n);

/// @brief 大整数某一比特位数值
/// @param[in]  n
/// @param[in]  index
/// @return 比特值(1/0)
int bint_bits_at(BINT* n, int index);

/// @brief 大整数取绝对值
/// @param[out] r
/// @param[in]  n
void bint_abs(BINT* r, BINT* n);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // BINT_H
