#ifndef EC_JACOBIAN_H
#define EC_JACOBIAN_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// 有BUG

#include <gmlib/ec.h>

typedef struct ECJacobianPoint {
    BINT x, y, z;
} ECJacobianPoint;

/// @brief 椭圆曲线二倍点(jacobian坐标)
/// @param[out] r       结果(jacobian坐标)
/// @param[in]  n       加数(jacobian坐标)
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_jacobian_double(ECJacobianPoint* r, ECJacobianPoint* n, EC_CTX* ec_ctx);

/// @brief 椭圆曲线加法(jacobian坐标)
/// @param[out] r       结果(jacobian坐标)
/// @param[in]  n1      加数(jacobian坐标)
/// @param[in]  n2      加数(jacobian坐标)
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_jacobian_add_neq(ECJacobianPoint* r,
                        ECJacobianPoint* n1,
                        ECJacobianPoint* n2,
                        EC_CTX* ec_ctx);

/// @brief 椭圆曲线jacobian转换(仿射坐标->jacobian)
/// @param[out] r       点(jacobian坐标)
/// @param[out] n       点(仿射坐标)
/// @param[in]  ec_ctx  椭圆曲线参数
void ec_jacobian_construct(ECJacobianPoint* r, ECPoint* n, EC_CTX* ec_ctx);

void ec_jacobian_set_infinity(ECJacobianPoint* n);

/// @brief 椭圆曲线规范化(jacobian->仿射坐标)
/// @param[out] r       点(仿射坐标)
/// @param[out] n       点(jacobian坐标)
/// @param[in]  ec_ctx  椭圆曲线参数
/// @return 错误码（0表示无错误）
int ec_construct_from_jacobian(ECPoint* r, ECJacobianPoint* n, EC_CTX* ec_ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // EC_JACOBIAN_H
