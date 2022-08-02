#include <gmlib/bint.h>
#include <gmlib/err.h>
#include <memory.h>
#include "bint_add_sub.h"
#include "bint_div.h"
#include "bint_mul.h"

/// @brief 从字符串中读入大整数
int bint_from_str(BINT* n, char* str, int radix) {
    if (radix < 2 || radix > 36) {
        ERR_LOG("The radix range is [2, 36], get %d", radix);
        goto error;
    }

    // 对于 radix进制，以 parse_span[radix] 个字符为单位进行转化
    static int parse_span[] = {0, 0, 30, 19, 15, 13, 11, 11, 10, 9, 9, 8, 8,
                               8, 8, 7,  7,  7,  7,  7,  7,  7,  6, 6, 6, 6,
                               6, 6, 6,  6,  6,  6,  6,  6,  6,  6, 5};

    // 处理符号位
    int sign;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        sign = 1;
        str++;
    } else {
        sign = 1;
    }

    bint_set_zero(n);  // 初始化为零
    // 进制转换
    while (*str != '\0') {
        uint32_t add_val = 0;  // 加数
        uint32_t mul_val = 1;  // 乘数
        // 进制转换，parse_span[radix] 个字符为一组
        int i = 0;
        while (i < parse_span[radix]) {
            uint32_t tmp = 0;
            char c = *str;
            // End of String
            if (c == '\0') {
                break;
            }
            // 分隔符，跳过
            if (c == '_') {
                str++;
                continue;
            }
            // 字符转整数
            if ('0' <= c && c <= '9') {
                // 0~9
                tmp = c - '0';
            } else if ('A' <= c && c <= 'A' + radix - 10 - 1) {
                // A~Z
                tmp = c - 'A' + 10;
            } else if ('a' <= c && c <= 'a' + radix - 10 - 1) {
                // a~z
                tmp = c - 'a' + 10;
            } else {
                char c1;
                if (radix <= 10) {
                    c1 = '0' + radix - 1;
                } else {
                    c1 = 'A' + radix - 10 - 1;
                }
                ERR_LOG("Bad string input, need [0, %c], get %c", c1, c);
                goto error;
            }
            mul_val = mul_val * radix;        // 更新乘数
            add_val = add_val * radix + tmp;  // 更新加数

            str++;
            i++;
        }

        try_goto(bint_umul_u32(n, n, mul_val));
        try_goto(bint_uadd_u32(n, n, add_val));
    }
    if (n->dsize != 0) {
        n->sign = sign;
    } else {
        bint_set_zero(n);
    }
    return ERR_NOERROR;

error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数转字符串
int bint_to_str(BINT* n, char* str, int radix) {
    if (radix < 2 || radix > 36) {
        ERR_LOG("The radix range is [2, 36], get %d", radix);
        goto error;
    }

    // 特判零
    if (bint_is_zero(n)) {
        str[0] = '0';
        str[1] = '\0';
        goto final;
    }
    // 负数特判
    if (bint_is_neg(n)) {
        *str = '-';
        str++;
    }

    BINT u;  // 临时值
    bint_copy(&u, n);
    // 除
    uint32_t r = 0;
    char* cur = str;
    while (u.dsize > 0) {
        bint_udiv_u32(&u, &r, &u, radix);
        if (r >= 0 && r <= 9) {
            *cur = '0' + (char)r;  // 0~9 直接转化为数字
        } else {
            *cur = 'A' + (char)r - 10;  // 大于9的需要转为为字母A~Z
        }
        cur++;
    }
    *cur = '\0';
    // 逆序字符串
    int32_t sLen = (int32_t)((size_t)cur - (size_t)str);
    for (int32_t i = 0; i < sLen / 2; i++) {
        char t = str[i];
        str[i] = str[sLen - 1 - i];
        str[sLen - 1 - i] = t;
    }

final:
    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数转字符串（非线程安全，用于打印输出）
char* bint_fast_to_str(BINT* n, int radix) {
    static char str[GMLIB_BINT_BITS + 2] = {0};
    bint_to_str(n, str, radix);
    return str;
}

/// @brief 从整数中读入大整数
void bint_from_u32(BINT* n, uint32_t u) {
    if (u == 0) {
        bint_set_zero(n);
    } else {
        n->d[0] = u;
        n->sign = 1;
        n->dsize = 1;
    }
}

/// @brief 大整数转32位整数
int bint_to_u32(uint32_t* u, BINT* n) {
    if (n->dsize == 0) {
        *u = 0;
    } else if (n->dsize == 1) {
        *u = n->d[0];
    } else {
        ERR_LOG("Unable to convert BINT to u32, data overflow");
        goto error;
    }
    return ERR_NOERROR;

error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 从字节串中读取大整数
int bint_from_bytes(BINT* n, uint8_t* b, int bsize, int endian) {
    if (bsize > (GMLIB_BINT_BITS / 8)) {
        ERR_LOG(
            "Unable to convert byte string to BINT,exceeding the maximum "
            "representation range: %d bytes ",
            GMLIB_BINT_BITS / 8);
        goto error;
    }
    // 字节串->BINT
    int dsize = (bsize + 3) / 4;  // 预估长度，除以4上取整
    if (endian == BINT_BIG_ENDIAN) {
        // 大端格式
        n->d[dsize - 1] = 0;  // 置零避免脏数据
        // 内存拷贝（逆序）
        uint8_t* nptr = (uint8_t*)(n->d);
        for (int i = 0; i < bsize; i++) {
            nptr[bsize - i - 1] = b[i];
        }
    } else {
        // 小端格式
        n->d[dsize - 1] = 0;                     // 置零避免脏数据
        memcpy((void*)(n->d), (void*)b, bsize);  // 内存拷贝
    }
    // 调整长度
    while (dsize > 0 && n->d[dsize - 1] == 0) {
        dsize--;
    }
    if (dsize == 0) {
        bint_set_zero(n);
    } else {
        n->dsize = dsize;
        n->sign = 1;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 大整数转字节串
int bint_to_bytes(BINT* n, uint8_t* b, int bsize, int endian) {
    int nbsize = bint_bytes_len(n);  // 获取存储所需最小字节数
    if (nbsize > bsize) {
        ERR_LOG("Unable to store BINT into byte string, data overflow");
        goto error;
    }
    if (endian == BINT_BIG_ENDIAN) {
        // 大端格式
        //内存拷贝（逆序）
        uint8_t* nptr = (uint8_t*)(n->d);
        for (int i = 0; i < nbsize; i++) {
            b[bsize - i - 1] = nptr[i];
        }
        memset(b, 0, bsize - nbsize);  // 清除多余位
    } else {
        // 小端格式
        memcpy(b, n->d, nbsize);                //内存拷贝
        memset(b + nbsize, 0, bsize - nbsize);  // 清除多余位
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
