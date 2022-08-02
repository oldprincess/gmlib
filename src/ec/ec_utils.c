#include <gmlib/ec.h>
#include <gmlib/err.h>
#include <gmlib/math.h>

/// @brief 椭圆曲线点判等(仿射坐标)
int ec_equal(ECPoint* n1, ECPoint* n2) {
    BINT *x1 = &n1->x, *y1 = &n1->y;
    BINT *x2 = &n2->x, *y2 = &n2->y;
    return bint_cmp(x1, x2) == 0 && bint_cmp(y1, y2) == 0;
}

/// @brief 椭圆曲线点互逆判断(仿射坐标)
int ec_neg_equal(ECPoint* n1, ECPoint* n2) {
    BINT *x1 = &n1->x, *y1 = &n1->y;
    BINT *x2 = &n2->x, *y2 = &n2->y;

    return bint_cmp(x1, x2) == 0 && bint_cmp(y1, y2) != 0;
}

/// @brief 椭圆曲线是否是无穷远点
int ec_is_infinity(ECPoint* n) {
    return n->infinity == 1;
}

/// @brief 椭圆曲线设置无穷远点
void ec_set_infinity(ECPoint* n) {
    n->infinity = 1;
}

/// @brief 校验点是否在椭圆曲线上(仿射坐标)
int ec_check(ECPoint* n, int* status, EC_CTX* ec_ctx) {
    // y^2 = x^3+ax+b
    BINT *a = &ec_ctx->a, *b = &ec_ctx->b, *p = &ec_ctx->p;
    BINT t1, t2, t3;
    try_goto(fp_sqr(&t1, &n->y, &ec_ctx->p));  // y^2

    try_goto(fp_mul(&t2, &n->x, a, p));        // ax
    try_goto(fp_add(&t2, &t2, b, p));          // ax+b
    try_goto(bint_pow_u32(&t3, &n->x, 3, p));  // x^3
    try_goto(fp_add(&t2, &t2, &t3, p));        // x^3+ax+b

    *status = bint_cmp(&t1, &t2) == 0;

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 椭圆曲线点拷贝
void ec_copy(ECPoint* r, ECPoint* n) {
    bint_copy(&r->x, &n->x);
    bint_copy(&r->y, &n->y);
    r->infinity = n->infinity;
}

/// @brief 椭圆曲线点取负
int ec_neg(ECPoint* r, ECPoint* n, EC_CTX* ec_ctx) {
    bint_copy(&r->x, &n->x);
    try_goto(fp_neg(&r->y, &n->y, &ec_ctx->p));
    r->infinity = n->infinity;

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
