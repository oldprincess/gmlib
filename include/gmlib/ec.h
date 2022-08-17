/**
 * @file ec.h
 * @brief 椭圆曲线运算
 *
 * 参考资料：<br>
 * [1]. GM/T 0003.1-2012 SM2 椭圆曲线公钥密码算法第1部分：总则 <br>
 *
 * 椭圆曲线点与字节串转化、点加/数乘运算、jacobian坐标系表示等均可在
 * SM2 国标文档中查看学习
 * http://www.gmbz.org.cn/main/viewfile/20180108015515787986.html
 */

#ifndef EC_H
#define EC_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/bint.h>

typedef struct ECPoint {
    BINT x, y;     // 坐标
    int infinity;  // 1(无穷远点), 0(非无穷远)
} ECPoint;

typedef struct EC_CTX {
    BINT a, b;  // y^2 = x^3+ax+b
    BINT p;     // 素数
    ECPoint G;  // 生成元
    BINT n;     // 阶
} EC_CTX;

extern EC_CTX EC_Fp192_CTX;
extern EC_CTX EC_Fp256_CTX;

// ====================================
// ======== 椭圆曲线 CTX ==============
// ====================================

/// @brief EC Context 拷贝
/// @param[out] r   结果输出
/// @param[in]  ctx
void ec_ctx_copy(EC_CTX* r, EC_CTX* ctx);

/// @brief EC Context 构造
void ec_ctx_construct(EC_CTX* r,   ///< [out] 椭圆曲线上下文
                      BINT* a,     ///< [in]  参数a
                      BINT* b,     ///< [in]  参数b
                      BINT* p,     ///< [in]  素域p
                      ECPoint* G,  ///< [in]  曲线生成元G
                      BINT* n      ///< [in]  生成元的阶n
);

/// @brief 椭圆曲线点拷贝
/// @param[out] r
/// @param[out] n
void ec_copy(ECPoint* r, ECPoint* n);

/// @brief 椭圆曲线点构造
/// @param[out] r   点
/// @param[in]  x   x坐标
/// @param[in]  y   y坐标
void ec_construct(ECPoint* r, BINT* x, BINT* y);

// ====================================
// ======== 椭圆曲线点 cast ============
// ====================================

// 非压缩形式
#define EC_PC_NO_ZIP 0x04

/// @brief 椭圆曲线点转字节串
/// @param[in]  n       点(仿射坐标)
/// @param[in]  PC      转换方式(04:未压缩)
/// @param[out] b       字节串
/// @param[out] bsize   输出长度
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_to_bytes(ECPoint* n, int PC, uint8_t* b, int* bsize, EC_CTX* ec_ctx);

/// @brief 字节串转椭圆曲线点
/// @param[out] n       点(仿射坐标)
/// @param[in]  b       字节串
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_from_bytes(ECPoint* n, uint8_t* b, int* read_size, EC_CTX* ec_ctx);

// ====================================
// ======== 椭圆曲线点算数 =============
// ====================================

/// @brief 椭圆曲线点加
/// @param[out] r       结果
/// @param[in]  n1      加数
/// @param[in]  n2      加数
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_add(ECPoint* r, ECPoint* n1, ECPoint* n2, EC_CTX* ec_ctx);

/// @brief 椭圆曲线多倍点
/// @param[out] r       结果
/// @param[in]  k       乘数
/// @param[in]  n       加数
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_mul(ECPoint* r, BINT* k, ECPoint* n, EC_CTX* ec_ctx);

// ====================================
// ======== 椭圆曲线功能函数 ===========
// ====================================

/// @brief 椭圆曲线点判等
/// @param[in]  n1      点
/// @param[in]  n2      点
/// @return 1(相等),0(不等)
int ec_equal(ECPoint* n1, ECPoint* n2);

/// @brief 椭圆曲线点互逆判断
/// @param[in]  n1      点
/// @param[in]  n2      点
/// @return 1(相等),0(不等)
int ec_neg_equal(ECPoint* n1, ECPoint* n2);

/// @brief 椭圆曲线是否是无穷远点
/// @param[in]  n       点
/// @return 1(是),0(否)
int ec_is_infinity(ECPoint* n);

/// @brief 椭圆曲线设置无穷远点
/// @param[inout]   n
void ec_set_infinity(ECPoint* n);

/// @brief 校验点是否在椭圆曲线上
/// @param[in]  n       点
/// @param[out] status  1(在曲线上),0(不在)
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_check(ECPoint* n, int* status, EC_CTX* ec_ctx);

/// @brief 椭圆曲线点取负
/// @param[out] r
/// @param[out] n
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_neg(ECPoint* r, ECPoint* n, EC_CTX* ec_ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // EC_H
