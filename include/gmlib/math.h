/**
 * @file  math.h
 * @brief 大整数数学运算
 *
 * 参考资料：<br>
 * [1]. openssl 3.0 大整数 bn 模块 <br>
 * [2]. 密码学实验教程. 郭华、刘建伟、李大伟 <br>
 *
 * 素性检测参考资料[1] bn_prime 模块，使用小素数预先过滤；
 * Miller-Rabin 测试、求逆、计算 gcd 等数学算法参考资料[2]；
 */
#ifndef GMLIB_MATH_H
#define GMLIB_MATH_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/bint.h>

/// @brief 随机生成bits比特大整数
/// @param[out] r       大整数
/// @param[in]  bits    比特数
/// @return 错误码（0表示无错误）
int bint_rand_bits(BINT* r, int bits);

/// @brief 随机生成[left, right)范围大整数
/// @param[out] r       大整数
/// @param[in]  left    下界
/// @param[in]  right   上界
/// @return 错误码（0表示无错误）
int bint_rand_range(BINT* r, BINT* left, BINT* right);

/// @brief 随机生成bits比特大素数
/// @param[out] r       大整数
/// @param[in]  bits    比特数
/// @return 错误码（0表示无错误）
int bint_prime_bits(BINT* r, int bits);

/// @brief 素数判断(无视符号位)
/// @param[in]  n       大整数
/// @param[out] status  1(素数),0(不是素数)
/// @return 错误码（0表示无错误）
int bint_is_prime(BINT* n, int* status);

/// @brief 最大公约数
/// @param[out] gcd
/// @param[in]  n1
/// @param[in]  n2
/// @return 错误码（0表示无错误）
int bint_gcd(BINT* gcd, BINT* n1, BINT* n2);

// ======================================
// =========== 有限域 ===================
// ======================================

/// @brief 有限域加法
/// @param[out] r   和 sum
/// @param[in]  n1  被加数 augend
/// @param[in]  n2  加数 addend
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_add(BINT* r, BINT* n1, BINT* n2, BINT* p);

/// @brief 有限域减法
/// @param[out] r   差 difference
/// @param[in]  n1  被减数 minuend
/// @param[in]  n2  减数 subtrahend
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_sub(BINT* r, BINT* n1, BINT* n2, BINT* p);

/// @brief 有限域乘法
/// @param[out] r   乘积 product
/// @param[in]  n1  被乘数 multiplicand
/// @param[in]  n2  乘数 multiplier
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_mul(BINT* r, BINT* n1, BINT* n2, BINT* p);

/// @brief 有限域乘法
/// @param[out] r   乘积 product
/// @param[in]  n1  被乘数 multiplicand
/// @param[in]  n2  乘数 multiplier
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_mul_u32(BINT* r, BINT* n1, uint32_t n2, BINT* p);

/// @brief 有限域二次幂
/// @param[out] r   乘积 product
/// @param[in]  n   乘数
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_sqr(BINT* r, BINT* n, BINT* p);

/// @brief 有限域求幂
/// @param[out] r   幂 power
/// @param[in]  n   底数 base
/// @param[in]  e   指数 exponent
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_pow(BINT* r, BINT* n, BINT* e, BINT* p);

/// @brief 有限域求逆
/// @param[out] r   逆元
/// @param[in]  n
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_inverse(BINT* r, BINT* n, BINT* p);

/// @brief 有限域取负
/// @param[out] r
/// @param[in]  n
/// @param[in]  p
/// @return 错误码（0表示无错误）
int fp_neg(BINT* r, BINT* n, BINT* p);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // GMLIB_MATH_H
