#include "bint_cmp.h"
#include <gmlib/err.h>

/// @brief 大整数比较（无视符号位）
int bint_ucmp(BINT* n1, BINT* n2) {
    // 长度比较
    if (n1->dsize > n2->dsize) {
        return 1;
    } else if (n1->dsize < n2->dsize) {
        return -1;
    }
    // 位数相同
    int dsize = n1->dsize;
    for (int i = dsize - 1; i >= 0; i--) {
        if (n1->d[i] > n2->d[i]) {
            return 1;
        } else if (n1->d[i] < n2->d[i]) {
            return -1;
        }
    }
    return 0;
}

/// @brief 大整数比较
int bint_cmp(BINT* n1, BINT* n2) {
    // 符号位比较
    if (n1->sign > n2->sign) {
        return 1;  // (+) > (0)/(-), (0) > (-)
    } else if (n1->sign < n2->sign) {
        return -1;  // (-) < (0)/(+), (0) < (+)
    }
    // 符号位相同比较
    int cmp = bint_ucmp(n1, n2);
    if (cmp == 0) {
        return 0;  // n1=n2
    } else if (cmp == 1) {
        return n1->sign;  // |n1|>|n2|
    } else {
        return -n1->sign;  // |n1|<|n2|
    }
}
