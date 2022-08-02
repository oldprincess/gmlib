#include "bint_add_sub.h"
#include <gmlib/err.h>
#include "bint_cmp.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/// @brief 大整数加法
int bint_add(BINT* r, BINT* n1, BINT* n2) {
    if (n1->sign == n2->sign) {
        // (0) + (0) -> (0)
        // (+) + (+) -> (+)
        // (-) + (-) -> (-)
        r->sign = n1->sign;
        try_goto(bint_uadd(r, n1, n2));
    } else {
        int cmp = bint_ucmp(n1, n2);
        if (cmp == 1) {
            // |n1|>|n2| 此时n1->sign必不为零
            r->sign = n1->sign;
            try_goto(bint_usub(r, n1, n2));
        } else if (cmp == -1) {
            // |n2|>|n1| 此时n2->sign必不为零
            r->sign = n2->sign;
            try_goto(bint_usub(r, n2, n1));
        } else {
            bint_set_zero(r);  // |n1|=|n2|
        }
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数减法
int bint_sub(BINT* r, BINT* n1, BINT* n2) {
    if (n1->sign == n2->sign) {
        int cmp = bint_ucmp(n1, n2);
        if (cmp == 1) {
            // |n1|>|n2| 此时n1->sign必不为零
            r->sign = n1->sign;
            try_goto(bint_usub(r, n1, n2));
        } else if (cmp == -1) {
            // |n2|>|n1| 此时n2->sign必不为零
            r->sign = -n2->sign;
            try_goto(bint_usub(r, n2, n1));
        } else {
            bint_set_zero(r);  // |n1|=|n2|
        }
    } else {
        // (+) - (0) -> (+), (+) - (-) -> (+)
        // (0) - (+) -> (-), (0) - (-) -> (+)
        // (-) - (+) -> (-), (-) - (0) -> (-)
        r->sign = (n1->sign != 0) ? (n1->sign) : (-n2->sign);
        try_goto(bint_uadd(r, n1, n2));
    }
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

// ========================================
// ============= local func ===============
// ========================================

/// @brief 大整数加法（不考虑符号位）
int bint_uadd(BINT* r, BINT* n1, BINT* n2) {
    uint32_t carry = 0;  // 进位
    uint64_t tmp = 0;    // 临时值

    BINT* bigger = (n1->dsize > n2->dsize) ? n1 : n2;   // 长度较大者
    BINT* smaller = (n1->dsize > n2->dsize) ? n2 : n1;  // 长度较小者
    int maxlen = bigger->dsize;                         // 最大长度
    int minlen = smaller->dsize;                        // 最小长度
    // 循环
    int i = 0;
    for (; i < minlen; i++) {
        tmp = (uint64_t)(bigger->d[i]) + (uint64_t)(smaller->d[i]) + carry;
        r->d[i] = (uint32_t)(tmp & UINT32_MAX);  // 取低32位
        carry = (uint32_t)(tmp >> 32);           //取高32位作为进位
    }
    for (; i < maxlen; i++) {
        tmp = (uint64_t)(bigger->d[i]) + carry;
        r->d[i] = (uint32_t)(tmp & UINT32_MAX);  // 取低32位
        carry = (uint32_t)(tmp >> 32);           //取高32位作为进位
    }
    r->dsize = maxlen;
    // 处理剩余进位
    if (carry > 0) {
        if (r->dsize == GMLIB_BINT_SIZE) {
            ERR_LOG("BINT addition result overflow");
            goto error;
        }
        r->d[r->dsize] = carry;
        (r->dsize)++;
    }
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数加法（不考虑符号位）
int bint_uadd_u32(BINT* r, BINT* n1, uint32_t n2) {
    uint32_t carry = n2;  // 进位
    uint64_t tmp = 0;     // 临时值
    for (int i = 0; i < n1->dsize; i++) {
        tmp = (uint64_t)(n1->d[i]) + carry;
        r->d[i] = (uint32_t)(tmp & UINT32_MAX);
        carry = (uint32_t)(tmp >> 32);
    }
    r->dsize = n1->dsize;
    if (carry > 0) {
        if (r->dsize == GMLIB_BINT_SIZE) {
            ERR_LOG("BINT addition result overflow");
            goto error;
        }
        r->d[r->dsize] = carry;
        (r->dsize)++;
    }
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数减法（不考虑符号位）(n1>n2)
int bint_usub(BINT* r, BINT* n1, BINT* n2) {
    uint32_t borrow = 0;  // 借位
    uint64_t tmp = 0;     // 临时值

    int maxlen = n1->dsize;  // 最大长度
    int minlen = n2->dsize;  // 最小长度

    int i = 0;
    for (; i < minlen; i++) {
        tmp = (uint64_t)(n1->d[i]) - (uint64_t)(n2->d[i]) - borrow;
        r->d[i] = (uint32_t)(tmp & UINT32_MAX);
        borrow = (tmp >> 32 != 0) ? 1 : 0;  // 借位
    }
    for (; i < maxlen; i++) {
        tmp = (uint64_t)(n1->d[i]) - borrow;
        r->d[i] = (uint32_t)(tmp & UINT32_MAX);
        borrow = (tmp >> 32 != 0) ? 1 : 0;  // 借位
    }
    if (borrow != 0) {
        ERR_LOG("BINT subtraction result overflow");
        goto error;
    }
    r->dsize = maxlen;
    // 规整长度dsize
    while (r->dsize > 0 && r->d[r->dsize - 1] == 0) {
        (r->dsize)--;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数减法（不考虑符号位）(n1>n2)
int bint_usub_u32(BINT* r, BINT* n1, uint32_t n2) {
    uint32_t borrow = n2;  // 借位
    uint64_t tmp = 0;      // 临时值

    for (int i = 0; i < n1->dsize; i++) {
        tmp = (uint64_t)(n1->d[i]) - borrow;
        r->d[i] = (uint32_t)(tmp & UINT32_MAX);
        borrow = (tmp >> 32 != 0) ? 1 : 0;  // 借位
    }
    if (borrow != 0) {
        ERR_LOG("BINT subtraction result overflow");
        goto error;
    }
    r->dsize = n1->dsize;
    // 规整长度dsize
    while (r->dsize > 0 && r->d[r->dsize - 1] == 0) {
        (r->dsize)--;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
