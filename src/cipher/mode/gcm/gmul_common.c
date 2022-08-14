#include <gmlib/utils.h>
#include "gmul.h"

void gmul_common(uint8_t* r, uint8_t* X, uint8_t* H) {
    // Rh = E100...00 (64bit)
    uint64_t Rh = (uint64_t)0xE1 << 56;
    // 定义128bit数Z，区分高64位和低64位
    uint64_t Zh = 0;
    uint64_t Zl = 0;
    // 定义128bit数V，区分高64位和低64位，并从Y对应的内存中加载
    uint64_t Vh = loadu64_be(H);
    uint64_t Vl = loadu64_be(H + 8);
    // 局部变量
    uint8_t x, t;
    // 进行乘法
    for (int i = 0; i < 16; i++) {
        x = X[i];
        for (int j = 7; j >= 0; j--) {
            if ((x >> j) & 1) {
                Zh ^= Vh, Zl ^= Vl;
            }
            t = Vl & 1;
            Vl = (Vh << 63) | (Vl >> 1);
            Vh = Vh >> 1;
            if (t) {
                Vh ^= Rh;
            }
        }
    }
    // 将Z存入res中
    storeu64_be(r, Zh);
    storeu64_be(r + 8, Zl);
}
