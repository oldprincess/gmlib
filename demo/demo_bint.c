#include <gmlib/bint.h>
#include <stdio.h>

int main() {
    BINT x, y;
    BINT z1, z2, z3;
    char str1[GMLIB_BINT_BITS + 2];  // 字符串 buffer
    char str2[GMLIB_BINT_BITS + 2];  // 字符串 buffer

    // 读入字符串
    bint_from_str(&x, "FFFFAAAA", 16);  // 从16进制中读入
    bint_from_str(&y, "12345678", 10);  // 从10进制中读入

    // 运算
    bint_add(&z1, &x, &y);          // z1 = x + y
    bint_divmod(&z2, &z3, &x, &y);  // z3 = x / y, z4 = x % y

    // 打印结果
    bint_to_str(&z1, str1, 10);  // 转化成10进制字符串
    printf("x+y=%s\n", str1);    // 打印字符串
    printf("x+y=%s\n", bint_fast_to_str(&z1, 10));  // 同上

    // 错误，调用bint_fast_to_str后会将上一次调用结果覆盖
    printf("x/y=%s, x mod y=%s\n", bint_fast_to_str(&z2, 10),
           bint_fast_to_str(&z3, 10));
    // 正确
    bint_to_str(&z2, str1, 10);  // 转化成10进制字符串
    bint_to_str(&z3, str2, 10);  // 转化成10进制字符串
    printf("x/y=%s, x mod y=%s\n", str1, str2);

    /*
        x+y=4307291128
        x+y=4307291128
        x/y=347, x mod y=347
        x/y=347, x mod y=10995184
    */
    return 0;
}
