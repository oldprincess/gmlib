/// 该算法有Bug，待完成...

#include "ec_jacobian.h"
#include <gmlib/err.h>
#include <gmlib/math.h>

static int ec_jacobian_is_infinity(ECJacobianPoint* n) {
    return bint_is_zero(&n->z);
}

void ec_jacobian_set_infinity(ECJacobianPoint* n) {
    bint_set_zero(&n->z);
}

/// @brief 椭圆曲线二倍点(jacobian坐标)
int ec_jacobian_double(ECJacobianPoint* r, ECJacobianPoint* n, EC_CTX* ec_ctx) {
    if (bint_cmp(&BINT_ONE, &n->z) == 0) {
        printf("get x:%s\n", bint_fast_to_str(&n->x, 16));
        printf("get y:%s\n", bint_fast_to_str(&n->y, 16));
    }
    ECPoint d1, d3;
    ec_construct_from_jacobian(&d1, n, ec_ctx);
    ec_add(&d3, &d1, &d1, ec_ctx);

    BINT *x1 = &n->x, *y1 = &n->y, *z1 = &n->z;
    BINT *x3 = &r->x, *y3 = &r->y, *z3 = &r->z;
    BINT *a = &ec_ctx->a, *p = &ec_ctx->p;
    BINT lamda[3], t;
    // lamda[0] = 3 x^2 + a z^4
    try_goto(fp_sqr(&t, x1, p));
    try_goto(fp_mul_u32(&lamda[0], &t, 3, p));
    try_goto(fp_sqr(&t, z1, p));
    try_goto(fp_sqr(&t, &t, p));
    try_goto(fp_mul(&t, a, &t, p));
    try_goto(fp_add(&lamda[0], &lamda[0], &t, p));
    // lamda[1] = 4 x y^2
    try_goto(fp_mul_u32(&lamda[1], x1, 4, p));
    try_goto(fp_sqr(&t, y1, p));  // y^2
    try_goto(fp_mul(&lamda[1], &lamda[1], &t, p));
    // lamda[2] = 8 y^4
    try_goto(fp_sqr(&t, &t, p));  // y^4
    try_goto(fp_mul_u32(&lamda[2], &t, 8, p));
    // x3 = lamda[0]^2 - 2 lamda[1]
    try_goto(fp_add(&t, &lamda[1], &lamda[1], p));
    try_goto(fp_sqr(x3, &lamda[0], p));
    try_goto(fp_sub(x3, x3, &t, p));
    // y3 = lamda[0]*(lamda[1] - x3) - lamda[2]
    try_goto(fp_sub(y3, &lamda[1], x3, p));
    try_goto(fp_mul(y3, &lamda[0], y3, p));
    try_goto(fp_sub(y3, y3, &lamda[2], p));
    // z3 = 2 yz
    try_goto(fp_mul(&t, y1, z1, p));
    try_goto(fp_add(z3, &t, &t, p));

    ec_construct_from_jacobian(&d1, r, ec_ctx);
    if (!ec_equal(&d1, &d3)) {
        printf("expect X:%s\n", bint_fast_to_str(&d3.x, 10));
        printf("expect Y:%s\n", bint_fast_to_str(&d3.y, 10));

        printf("r.x:%s\n", bint_fast_to_str(&r->x, 10));
        printf("r.z:%s\n", bint_fast_to_str(&r->z, 10));
        printf("get X:%s\n", bint_fast_to_str(&d1.x, 10));
        printf("get Y:%s\n", bint_fast_to_str(&d1.y, 10));
        goto error;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 椭圆曲线加法(jacobian坐标)
int ec_jacobian_add_neq(ECJacobianPoint* r,
                        ECJacobianPoint* n1,
                        ECJacobianPoint* n2,
                        EC_CTX* ec_ctx);

/// @brief 椭圆曲线jacobian转换(仿射坐标->jacobian)
void ec_jacobian_construct(ECJacobianPoint* r, ECPoint* n, EC_CTX* ec_ctx) {
    if (ec_is_infinity(n)) {
        bint_from_u32(&r->x, 1);
        bint_from_u32(&r->y, 1);
        bint_from_u32(&r->z, 0);
    } else {
        bint_copy(&r->x, &n->x);
        bint_copy(&r->y, &n->y);
        bint_from_u32(&r->z, 1);
    }
}

/// @brief 椭圆曲线规范化(jacobian->仿射坐标)
int ec_construct_from_jacobian(ECPoint* r, ECJacobianPoint* n, EC_CTX* ec_ctx) {
    if (ec_jacobian_is_infinity(n)) {
        ec_set_infinity(r);
    } else {
        BINT iv;
        BINT x, y;

        try_goto(fp_inverse(&iv, &n->z, &ec_ctx->p));  // z^-1
        try_goto(fp_mul(&y, &n->y, &iv, &ec_ctx->p));  // y/z

        try_goto(fp_sqr(&iv, &iv, &ec_ctx->p));        // z^-2
        try_goto(fp_mul(&x, &n->x, &iv, &ec_ctx->p));  // x/(z^2)
        try_goto(fp_mul(&y, &y, &iv, &ec_ctx->p));     // y/(z^3)

        ec_construct(r, &x, &y);
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
