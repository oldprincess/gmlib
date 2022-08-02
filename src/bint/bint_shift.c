#include "bint_shift.h"
#include <gmlib/bint.h>
#include <gmlib/err.h>

/// @brief 大整数逻辑（算数）左移
int bint_sll(BINT* r, BINT* n, int bits) {
    int nbits = bint_bits_len(n);  // 比特长度
    if (nbits + bits > GMLIB_BINT_BITS) {
        ERR_LOG("BINT shift left result overflow");
        goto error;
    }
    mem_sll(r->d, &(r->dsize), n->d, n->dsize, bits);
    r->sign = n->sign;
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数算数右移
int bint_sra(BINT* r, BINT* n, int bits) {
    int nbits = bint_bits_len(n);  // 比特长度
    if (nbits <= bits) {
        bint_set_zero(r);
    } else {
        mem_srl(r->d, &(r->dsize), n->d, n->dsize, bits);
        r->sign = n->sign;
    }
    return ERR_NOERROR;
}

// ========================================
// ============= local func ===============
// ========================================

/// @brief 大整数内存逻辑左移
void mem_sll(uint32_t* r, int* rsize, uint32_t* d, int dsize, int bits) {
    if (dsize == 0) {
        *rsize = 0;
        return;
    }
    int b32 = bits / 32;  // 32bit字移位数
    int b = bits % 32;    // bit移位数（32比特内）

    // 32整数倍比特移位
    for (int i = dsize - 1; i >= 0; i--) {
        r[i + b32] = d[i];
    }
    for (int i = 0; i < b32; i++) {
        r[i] = 0;  // 清除脏位
    }
    *rsize = dsize + b32;

    // 若b=0，则左右移位会发生错误
    if (b != 0) {
        uint32_t carry = 0;
        for (int i = b32; i < dsize + b32; i++) {
            // r[i] = r[i]<<b | r[i-1]>>(32-b)
            uint32_t tmp = r[i] << b | carry;
            carry = r[i] >> (32 - b);
            r[i] = tmp;
        }
        if (carry != 0) {
            r[*rsize] = carry;
            (*rsize)++;
        }
    }
}

/// @brief 大整数内存逻辑右移
void mem_srl(uint32_t* r, int* rsize, uint32_t* d, int dsize, int bits) {
    int b32 = bits / 32;  // 32bit字移位数
    int b = bits % 32;    // bit移位数（32比特内）

    // 移位长度大于内存长度
    if (dsize <= b32) {
        *rsize = 0;
        return;
    }

    // 32整数倍比特移位
    for (int i = 0; i < dsize - b32; i++) {
        r[i] = d[i + b32];
    }

    // 若b=0，则左右移位会发生错误
    if (b != 0) {
        uint32_t carry = 0;
        for (int i = dsize - b32 - 1; i >= 0; i--) {
            // r[i] = r[i+1]<<(32-b) | r[i]>>b
            uint32_t tmp = carry | (r[i] >> b);
            carry = r[i] << (32 - b);
            r[i] = tmp;
        }
    }
    *rsize = dsize - b32;
    // 规整长度rsize
    while (*rsize > 0 && r[*rsize - 1] == 0) {
        (*rsize)--;
    }
}
