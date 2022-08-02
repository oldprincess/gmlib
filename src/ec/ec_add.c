#include <gmlib/ec.h>
#include <gmlib/err.h>
#include <gmlib/math.h>

/// @brief 椭圆曲线点加(仿射坐标)
int ec_add(ECPoint* r, ECPoint* n1, ECPoint* n2, EC_CTX* ec_ctx) {
    if (ec_is_infinity(n1)) {
        ec_copy(r, n2);
        goto final;
    }
    if (ec_is_infinity(n2)) {
        ec_copy(r, n1);
        goto final;
    }
    if (ec_neg_equal(n1, n2)) {
        ec_set_infinity(r);
        goto final;
    }

    BINT lamda, t, x3, y3;
    BINT *x1 = &n1->x, *y1 = &n1->y;
    BINT *x2 = &n2->x, *y2 = &n2->y;
    BINT *a = &ec_ctx->a, *p = &ec_ctx->p;
    if (ec_equal(n1, n2)) {
        try_goto(fp_sqr(&lamda, x1, p));             // x1^2
        try_goto(fp_mul_u32(&lamda, &lamda, 3, p));  // 3 x1^2
        try_goto(fp_add(&lamda, &lamda, a, p));      // 3 x1^2 + a

        try_goto(fp_add(&t, y1, y1, p));  // 2 y1
        try_goto(fp_inverse(&t, &t, p));  // (2 y1)^-1

        // (3 x1^2+a) / (2 y1)
        try_goto(fp_mul(&lamda, &lamda, &t, p));

    } else {
        try_goto(fp_sub(&lamda, y1, y2, p));  // y1-y2
        try_goto(fp_sub(&t, x1, x2, p));      // x1-x2
        try_goto(fp_inverse(&t, &t, p));
        // (y1-y2)/(x1-x2)
        try_goto(fp_mul(&lamda, &lamda, &t, p));
    }

    // x3 = lamda^2 -x1 -x2
    try_goto(fp_sqr(&t, &lamda, p));  // lamda^2
    try_goto(fp_sub(&t, &t, x1, p));
    try_goto(fp_sub(&x3, &t, x2, p));
    // y3 = lamda*(x1 -x3) -y1
    try_goto(fp_sub(&t, x1, &x3, p));
    try_goto(fp_mul(&t, &lamda, &t, p));
    try_goto(fp_sub(&y3, &t, y1, p));

    ec_construct(r, &x3, &y3);

final:
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
