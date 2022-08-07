#include <gmlib/stream/zuc.h>
#include <gmlib/utils.h>
#include "zuc_common.h"

/// @brief 祖冲之算法ZUC初始化
void zuc_init(uint8_t* key, uint8_t* iv, ZUC_CTX* zuc_ctx) {
    zuc_common_init(key, iv, zuc_ctx);
}

///  @brief 祖冲之算法产生一节拍32比特密钥
uint32_t zuc_next(ZUC_CTX* zuc_ctx) {
    return zuc_common_next(zuc_ctx);
}

///  @brief 祖冲之算法产生一节拍32比特密钥
void zuc_put_next(uint8_t* out, ZUC_CTX* zuc_ctx) {
    storeu32_be(out, zuc_next(zuc_ctx));
}

/// @brief 祖冲之算法机密性算法(加/解密)
void zuc_confidentiality_crypt(uint8_t* out,
                               uint8_t* in,
                               int inbits,
                               uint32_t COUNT,
                               uint8_t BEARER,
                               uint8_t DIRECTION,
                               uint8_t* CK) {
    // get Msb(i)
    static uint8_t BITS_MASK[8] = {
        0b11111111, 0b10000000, 0b11000000, 0b11100000,  //
        0b11110000, 0b11111000, 0b11111100, 0b11111110,  //
    };

    // =================================
    // =========== 初始化 ZUC ===========
    // =================================
    uint8_t iv[16];
    // IV[0] = COUNT[0], ..., IV[3] = COUNT[3]
    storeu32_be(iv, COUNT);
    // IV[4] = BEARER(5) || DIRECTION(1) || 00
    iv[4] = (BEARER << 3) | (DIRECTION << 2);
    iv[5] = iv[6] = iv[7] = 0;
    for (int i = 8; i < 16; i++) {
        iv[i] = iv[i - 8];
    }
    // 初始化ZUC
    ZUC_CTX ctx;
    zuc_init(CK, iv, &ctx);

    // =================================
    // =========== Crypt ===============
    // =================================
    uint8_t k[4];  // 一节拍密钥
    while (inbits >= 32) {
        // 以32比特步长处理数据
        zuc_put_next(k, &ctx);            // 生成密钥流
        memxor(out, in, k, 4);            // 异或
        out += 4, in += 4, inbits -= 32;  // 更新数据
    }
    if (inbits) {
        zuc_put_next(k, &ctx);  // 生成密钥流
        uint8_t* kptr = k;      // 密钥流指针
        while (inbits >= 8) {
            // 以8比特步长处理数据
            *out = *in ^ *kptr;                // 异或
            out++, in++, kptr++, inbits -= 8;  // 更新数据
        }
        if (inbits) {
            // 只异或前inbits比特
            *out = *in ^ (*kptr & BITS_MASK[inbits]);
        }
    }
}

#define u32_bit_at(n, i) (((n) >> (31 - i)) & 1)
#define u8_bit_at(n, i) (((n) >> (7 - i)) & 1)

/// @brief 祖冲之算法完整性算法(MAC)
void zuc_integrity_mac(uint8_t* out,
                       uint8_t* in,
                       int inbits,
                       uint32_t COUNT,
                       uint8_t BEARER,
                       uint8_t DIRECTION,
                       uint8_t* IK) {
    // =================================
    // =========== 初始化 ZUC ===========
    // =================================
    // 初始化IV
    uint8_t iv[16];
    // IV[0] = COUNT[0], ..., IV[3] = COUNT[3]
    storeu32_be(iv, COUNT);
    iv[4] = BEARER << 3;  // IV[4] = BEARER(5) || 000
    iv[5] = iv[6] = iv[7] = 0;
    for (int i = 8; i < 16; i++) {
        iv[i] = iv[i - 8];
    }
    iv[8] ^= (DIRECTION << 7);
    iv[14] ^= (DIRECTION << 7);

    // 初始化ZUC
    ZUC_CTX ctx;
    zuc_init(IK, iv, &ctx);

    // =================================
    // =========== MAC =================
    // =================================
    uint32_t T = 0;
    uint64_t k64 = (uint64_t)zuc_next(&ctx) << 32;  // k[0] || 0(32)
    // 32比特步长MAC
    while (inbits >= 32) {
        k64 = k64 | (uint64_t)zuc_next(&ctx);  // k[i] || k[i+1]
        uint32_t msg32 = loadu32_be(in);       // 读取32比特字
        for (int i = 0; i < 32; i++) {
            // 第i比特是否为1
            if (u32_bit_at(msg32, i)) {
                T ^= (k64 >> 32) & UINT32_MAX;
            }
            k64 <<= 1;  // 更新数据
        }
        in += 4, inbits -= 32;  // 更新数据
    }
    if (inbits) {
        k64 = k64 | (uint64_t)zuc_next(&ctx);  // k[i] || k[i+1]
        // 8比特步长MAC
        while (inbits >= 8) {
            uint8_t msg8 = *in;
            for (int i = 0; i < 8; i++) {
                if (u8_bit_at(msg8, i)) {
                    T ^= (k64 >> 32) & UINT32_MAX;
                }
                k64 <<= 1;  // 更新数据
            }
            in++, inbits -= 8;  // 更新数据
        }
        // 1比特步长MAC
        while (inbits) {
            uint8_t msg8 = *in;
            for (int i = 0; i < inbits; i++) {
                if (u8_bit_at(msg8, i)) {
                    T ^= (k64 >> 32) & UINT32_MAX;
                }
                k64 <<= 1;  // 更新数据
            }
            in++, inbits = 0;
        }
    }
    T ^= (k64 >> 32) & UINT32_MAX;  // T ^ k[LENGTH]
    T ^= zuc_next(&ctx);            // T ^ k[32*(L-1)]
    // 存储MAC
    storeu32_be(out, T);
}
