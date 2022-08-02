#include "bint_mul.h"
#include <gmlib/err.h>
#include <memory.h>

/// @brief 大整数二次幂
int bint_sqr(BINT* r, BINT* n) {
    // 待优化
    try_goto(bint_mul(r, n, n));
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数乘法
int bint_mul(BINT* r, BINT* n1, BINT* n2) {
    // (+) x (+) -> (+), (+) x (0) -> (0), (+) x (-) -> (-)
    // (0) x (+) -> (0), (0) x (0) -> (0), (0) x (-) -> (0)
    // (-) x (+) -> (-), (-) x (0) -> (0), (-) x (-) -> (+)
    r->sign = n1->sign * n2->sign;
    if (r->sign != 0) {
        try_goto(bint_umul(r, n1, n2));
    } else {
        r->dsize = 0;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数乘法
int bint_mul_u32(BINT* r, BINT* n1, uint32_t n2) {
    int n2_sign = (n2 != 0) ? 1 : 0;
    r->sign = n1->sign * n2_sign;
    if (r->sign != 0) {
        try_goto(bint_umul_u32(r, n1, n2));
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

// ========================================
// ============= local func ===============
// ========================================

/// @brief 大整数乘法（不考虑符号位）
int bint_umul(BINT* r, BINT* n1, BINT* n2) {  // 初步判断是否存在溢出可能
    if (n1->dsize + n2->dsize - 1 > GMLIB_BINT_SIZE) {
        ERR_LOG("BINT multiplication result overflow");
        goto error;
    }

    uint32_t t[GMLIB_BINT_SIZE + 1] = {0};  // 临时缓冲区，+1避免溢出
    // 使用n2的每个32bit字乘以n1
    for (int i2 = 0; i2 < n2->dsize; i2++) {
        uint32_t carry = 0;        // 进位
        uint64_t tmp;              // 临时值
        uint32_t val = n2->d[i2];  // 乘数
        for (int i1 = 0; i1 < n1->dsize; i1++) {
            tmp = (uint64_t)(t[i2 + i1]) + (uint64_t)(n1->d[i1]) * val +
                  (uint64_t)carry;
            t[i2 + i1] = (uint32_t)(tmp & UINT32_MAX);
            carry = (uint32_t)(tmp >> 32);
        }
        t[i2 + n1->dsize] = carry;  // 保存最终进位
    }
    int tsize = n1->dsize + n2->dsize;
    // 规整长度dsize
    while (tsize > 0 && t[tsize - 1] == 0) {
        tsize--;
    }
    // 发生溢出
    if (tsize > GMLIB_BINT_SIZE) {
        ERR_LOG("BINT multiplication result overflow");
        goto error;
    }
    memcpy(r->d, t, tsize * 4);
    r->dsize = tsize;

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数乘法（不考虑符号位）
int bint_umul_u32(BINT* r, BINT* n1, uint32_t n2) {
    uint64_t tmp;
    uint32_t carry = 0;
    for (int i = 0; i < n1->dsize; i++) {
        tmp = (uint64_t)(n1->d[i]) * n2 + carry;
        r->d[i] = (uint32_t)(tmp & UINT32_MAX);
        carry = (uint32_t)(tmp >> 32);
    }
    r->dsize = n1->dsize;
    if (carry != 0) {
        if (n1->dsize == GMLIB_BINT_SIZE) {
            ERR_LOG("BINT multiplication result overflow");
            goto error;
        }
        r->d[n1->dsize] = carry;
        (r->dsize)++;
    }
    // 规整长度dsize
    while (r->dsize > 0 && r->d[r->dsize - 1] == 0) {
        (r->dsize)--;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
