#include <gmlib/err.h>
#include <gmlib/math.h>
#include <gmlib/utils.h>

// BITS_MASK1[i] 取32比特后i-1位（i=0表示取后31位）
static uint32_t BITS_MASK1[32] = {
    0x7fffffff, 0x00000000, 0x00000001, 0x00000003, 0x00000007, 0x0000000f,
    0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff, 0x000001ff, 0x000003ff,
    0x000007ff, 0x00000fff, 0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
    0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff, 0x001fffff, 0x003fffff,
    0x007fffff, 0x00ffffff, 0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff,
    0x1fffffff, 0x3fffffff,
};

// BITS_MASK2[i] 将第i比特（从右往左为第1,2...32）置1（i=0表示置第32比特）
static uint32_t BITS_MASK2[32] = {
    0x80000000, 0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010,
    0x00000020, 0x00000040, 0x00000080, 0x00000100, 0x00000200, 0x00000400,
    0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000, 0x00010000,
    0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000,
    0x00800000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
    0x20000000, 0x40000000,
};

/// @brief 随机生成bits比特大整数
int bint_rand_bits(BINT* r, int bits) {
    if (bits > GMLIB_BINT_BITS) {
        ERR_LOG("BINT overflow");
        goto error;
    }
    if (bits < 0) {
        ERR_LOG("BINT overflow");
        goto error;
    }

    if (bits == 0) {
        bint_set_zero(r);
        goto final;
    }
    if (bits == 1) {
        bint_from_u32(r, 1);
        goto final;
    }

    r->sign = 1;
    r->dsize = (bits + 31) / 32;  // 上取整
    int b = bits % 32;
    rand_mem((uint8_t*)(r->d), (bits + 7) / 8);  // 随机生成比特数，上取整
    // 将最高位置1
    r->d[r->dsize - 1] = (r->d[r->dsize - 1] & BITS_MASK1[b]) | BITS_MASK2[b];

final:
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

int bint_rand_range(BINT* r, BINT* left, BINT* right) {
    int cmp = bint_cmp(left, right);
    if (cmp >= 0) {
        ERR_LOG("Range num error, [left, right)");
        goto error;
    }

    BINT mod, t;
    try_goto(bint_sub(&mod, right, left));
    try_goto(bint_rand_bits(&t, bint_bits_len(&mod)));
    try_goto(bint_divmod(NULL, &t, &t, &mod));
    try_goto(bint_add(r, &t, left));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
