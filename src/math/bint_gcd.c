#include <gmlib/err.h>
#include <gmlib/math.h>

#define swap(x, y, type) \
    do {                 \
        type t;          \
        t = x;           \
        x = y;           \
        y = t;           \
    } while (0)

/// @brief 整数求逆
int fp_inverse(BINT* r, BINT* n, BINT* p) {
    if (bint_is_zero(n)) {
        ERR_LOG("Inverse Error, 0 can't be inversed");
        goto error;
    }
    if (!bint_is_pos(p)) {
        ERR_LOG("Inverse Error, p need be positive");
        goto error;
    }

    BINT t[5];  // 临时变量
    BINT *a = &t[0], *b = &t[1], *t1 = &t[2];
    BINT *x1 = &t[3], *x2 = &t[4];
    // 暂存输入
    bint_copy(a, n);
    bint_copy(b, p);
    // x1, x2 = 1, 0
    bint_from_u32(x1, 1);
    bint_set_zero(x2);
    // while b!=0
    while (!bint_is_zero(b)) {
        // a, b = b, a % b
        try_goto(bint_divmod(t1, a, a, b));  // t1(q) = a/b, a = a%b
        swap(b, a, BINT*);                // a, b = b, a
        // x1 = x1 - x2 * q
        try_goto(bint_mul(t1, x2, t1));  // t1 = x2 * t1
        try_goto(bint_sub(x1, x1, t1));  // x1 = x1 - t1
        swap(x1, x2, BINT*);             // x1, x2 = x2, x1
    }
    // 处理gcd结果符号
    if (bint_is_neg(a)) {
        bint_neg(a, a);
        bint_neg(x1, x1);
    }
    // gcd != 1，无逆元
    if (bint_cmp(a, &BINT_ONE) != 0) {
        ERR_LOG("Inverse Error");
        goto error;
    }
    // 处理结果为负的情况
    while (bint_is_neg(x1)) {
        try_goto(bint_add(x1, x1, p));
    }
    bint_copy(r, x1);

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 最大公约数
int bint_gcd(BINT* gcd, BINT* n1, BINT* n2) {
    if (bint_is_zero(n1) && bint_is_zero(n2)) {
        ERR_LOG("GCD Error, gcd(0,0) is undefine");
        goto error;
    }

    BINT t[2];  // 临时变量
    BINT *a = &t[0], *b = &t[1];
    bint_copy(a, n1);
    bint_copy(b, n2);
    // while b!=0
    while (!bint_is_zero(b)) {
        // a, b = b, a%b
        try_goto(bint_divmod(NULL, a, a, b));  // a = a % b
        swap(a, b, BINT*);                  // a, b = b, a
    }
    bint_abs(gcd, a);  // gcd = |a|

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
