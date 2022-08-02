#include <gmlib/bint.h>
#include <memory.h>

BINT BINT_ONE = {
    .d = {1},
    .dsize = 1,
    .sign = 1,
};

BINT BINT_TWO = {
    .d = {2},
    .dsize = 1,
    .sign = 1,
};

BINT BINT_THREE = {
    .d = {3},
    .dsize = 1,
    .sign = 1,
};

/// @brief 整数比特长度
static int bits_len(uint32_t n) {
    int bit = 0;
    // 判断最高有效位
    while (n != 0) {
        n >>= 1;
        bit++;
    }
    return bit;
}

/// @brief 大整数拷贝
void bint_copy(BINT* r, BINT* n) {
    if (r != n) {
        memcpy((void*)r, (void*)n, sizeof(BINT));
    }
}

/// @brief 大整数取负
void bint_neg(BINT* r, BINT* n) {
    bint_copy(r, n);
    r->sign = -(r->sign);
}

/// @brief 大整数的字节数
int bint_bytes_len(BINT* n) {
    return (bint_bits_len(n) + 7) / 8;
}

/// @brief 大整数的比特数
int bint_bits_len(BINT* n) {
    if (n->dsize == 0) {
        return 0;
    } else {
        return bits_len(n->d[n->dsize - 1]) + 32 * (n->dsize - 1);
    }
}

/// @brief 大整数取绝对值
void bint_abs(BINT* r, BINT* n) {
    if (bint_is_neg(n)) {
        bint_neg(r, n);
    } else {
        bint_copy(r, n);
    }
}

/// @brief 大整数某一比特位数值
int bint_bits_at(BINT* n, int index) {
    int b32 = index / 32;
    int b = index % 32;
    if (b32 >= n->dsize) {
        return 0;
    }
    uint32_t d = n->d[b32];
    return (d >> b) & 1;
}
