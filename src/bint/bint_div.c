#include "bint_div.h"
#include <gmlib/err.h>
#include "bint_cmp.h"
#include "bint_shift.h"

/// @brief 大整数除法
int bint_divmod(BINT* q, BINT* r, BINT* n1, BINT* n2) {
    if (bint_is_zero(n2)) {
        ERR_LOG("Divisor cannot be zero");
        goto error;
    }

    if (q == NULL && r == NULL) {
        goto final;
    }

    if (bint_is_zero(n1)) {
        if (q != NULL) {
            bint_set_zero(q);
        }
        if (r != NULL) {
            bint_set_zero(r);
        }
        goto final;
    }

    // n1 = q*n2+r
    // n1 (+) (-) (+) (-)
    // n2 (+) (+) (-) (-)
    // q  (+) (-) (-) (+)
    // r  (+) (-) (+) (-)
    int q_sign = n1->sign * n2->sign;  // q.sign
    int r_sign = n1->sign;             // r.sign

    int cmp = bint_ucmp(n1, n2);
    if (cmp == 0) {
        // |n1|=|n2|, n1/n2 = 1...0
        if (q != NULL) {
            bint_from_u32(q, 1);
            q->sign = q_sign;
        }
        if (r != NULL) {
            bint_set_zero(r);
        }
    } else if (cmp < 0) {
        // |n1|<|n2|, n1/n2 = 0...n1
        if (q != NULL) {
            bint_set_zero(q);
        }
        if (r != NULL) {
            bint_copy(r, n1);
            r->sign = r_sign;
        }
    } else {
        // |n1|>|n2|
        if (n2->dsize == 1) {
            uint32_t rem;
            bint_udiv_u32(q, &rem, n1, n2->d[0]);
            if (q != NULL) {
                q->sign = q_sign;
            }
            if (r != NULL) {
                bint_from_u32(r, rem);
                r->sign = r_sign;
            }
        } else {
            bint_udiv_knuth(q, r, n1, n2);

            if (q != NULL) {
                q->sign = q_sign;
            }
            if (r != NULL) {
                r->sign = r_sign;
            }
        }
    }

final:
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数除法
int bint_divmod_u32(BINT* q, uint32_t* r, BINT* n1, uint32_t n2) {
    if (n2 == 0) {
        ERR_LOG("Divisor cannot be zero");
        goto error;
    }

    if (q == NULL && r == NULL) {
        goto final;
    } else {
        if (q != NULL) {
            q->sign = n1->sign;
        }
        bint_udiv_u32(q, r, n1, n2);
    }

final:
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

// ========================================
// ============= local func ===============
// ========================================

/// @brief 大整数除法（不考虑符号位）(n1>n2, n2!=0, n2.dsize>=2)（不考虑符号位）
void bint_udiv_knuth(BINT* q, BINT* r, BINT* n1, BINT* n2) {
    // Knuth 除法
    int d = (32 - bint_bits_len(n2) % 32) % 32;

    uint32_t u[GMLIB_BINT_SIZE + 2];  // 被除数（+2避免溢出）
    uint32_t v[GMLIB_BINT_SIZE + 1];  // 除数（+1避免溢出）
    int usize, vsize;
    mem_sll(u, &usize, n1->d, n1->dsize, d);
    mem_sll(v, &vsize, n2->d, n2->dsize, d);

    u[usize] = 0;  // 为了方便 D2 的循环迭代
    // D2 初始化 j
    int32_t div_len = vsize;
    uint32_t div_h = v[div_len - 1];
    uint32_t div_l = v[div_len - 2];
    uint64_t base = (uint64_t)UINT32_MAX + 1;  // 2^32

    for (int32_t j = usize - div_len; j >= 0; j--) {
        // D3 计算qhat
        uint64_t qhat, rhat;
        uint64_t uh = (uint64_t)(u[j + div_len]);
        uint64_t ul = (uint64_t)(u[j + div_len - 1]);
        uint64_t ul2 = (uint64_t)(u[j + div_len - 2]);

        qhat = (uh * base + ul) / (uint64_t)div_h;
        if (qhat > UINT32_MAX) {
            // 防止计算出的qhat过大
            qhat = UINT32_MAX;
        }
        rhat = (uh * base + ul) - (uint64_t)div_h * qhat;
        if (qhat == 0) {
            // 商为0，跳过本轮
            if (q != NULL) {
                q->d[j] = 0;
            }
            continue;
        }
        while (qhat * (uint64_t)div_l > base * rhat + ul2) {
            // 调整qhat
            qhat--;
            rhat += div_h;
            if (rhat >= base) {
                break;
            }
        }
        // D4 乘和减
        uint64_t tmp = 0;     //临时值
        uint64_t borrow = 0;  // u的借位
        uint64_t carry = 0;   // div的进位
        for (int32_t i = 0; i < div_len; i++) {
            // 计算乘法 div*qhat
            uint64_t t = qhat * (uint64_t)(v[i]) + carry;
            carry = t >> 32;
            // 计算减法 u - div*qhat
            tmp = (uint64_t)(u[j + i]) - (t & UINT32_MAX) - borrow;
            borrow = (tmp >> 32) ? 1 : 0;
            // 赋值
            u[j + i] = (uint32_t)(tmp & UINT32_MAX);
        }
        if (borrow != 0 || carry != 0) {
            tmp = (uint64_t)(u[j + div_len]) - carry - borrow;
            borrow = (tmp >> 32) ? 1 : 0;
            u[j + div_len] = (uint32_t)(tmp & UINT32_MAX);
        }
        // D5 测试余数
        if (q != NULL) {
            q->d[j] = (borrow == 0) ? (uint32_t)qhat : (uint32_t)qhat - 1;
        }
        // D6 往回加
        if (borrow != 0) {
            uint64_t carry = 0;  // 加法进位
            for (int32_t i = 0; i < div_len; i++) {
                tmp = (uint64_t)u[j + i] + (uint64_t)(v[i]) + carry;
                u[j + i] = (uint32_t)(tmp & UINT32_MAX);
                carry = tmp >> 32;
            }
            if (carry != 0) {
                tmp = (uint64_t)u[j + div_len] + carry;
                u[j + div_len] = (uint32_t)(tmp & UINT32_MAX);
                // 将之后的进位丢弃，以抵消D4中的借位
            }
        }
    }  // D7 对 j 进行循环
    if (q != NULL) {
        q->dsize = usize - div_len + 1;
        while (q->dsize > 0 && q->d[q->dsize - 1] == 0) {
            (q->dsize)--;
        }
    }
    if (r != NULL) {
        mem_srl(r->d, &(r->dsize), u, vsize, d);
    }
}

/// @brief 大整数除法(n2!=0)（不考虑符号位）
void bint_udiv_u32(BINT* q, uint32_t* r, BINT* n1, uint32_t n2) {
    uint64_t tmp;      //临时值
    uint64_t rem = 0;  //余数
    // 从最高位一直除至最低位
    uint64_t divisor = (uint64_t)n2;  // 除数 扩大类型
    for (int32_t i = n1->dsize - 1; i >= 0; i--) {
        tmp = (rem << 32) | (uint64_t)(n1->d[i]);
        if (q != NULL) {
            q->d[i] = (uint32_t)(tmp / divisor);  // 记录商
        }
        rem = tmp % divisor;
    }
    if (r != NULL) {
        *r = (uint32_t)rem;  // 余数
    }
    if (q != NULL) {
        q->dsize = n1->dsize;
        while (q->dsize > 0 && q->d[q->dsize - 1] == 0) {
            (q->dsize)--;
        }
    }
}
