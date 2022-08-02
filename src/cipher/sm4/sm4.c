#include <gmlib/cipher/sm4.h>
#include <gmlib/err.h>
#include "sm4_common.h"
#include "sm4_tbox.h"

/// @brief SM4 轮密钥生成
void sm4_keyinit(uint8_t* key, SM4_Key* sm4key) {
    sm4_common_keyinit(key, sm4key);
}

/// @brief SM4 ECB模式加密
void sm4_encrypt(uint8_t* out, uint8_t* in, int block_num, SM4_Key* sm4key) {
    // encrypt
    int i = 0;
    for (; i < block_num; i++) {
        sm4_tbox_encrypt(out, in, sm4key);
        out += 16;
        in += 16;
    }
}

/// @brief SM4 ECB模式解密
void sm4_decrypt(uint8_t* out, uint8_t* in, int block_num, SM4_Key* sm4key) {
    // encrypt
    int i = 0;
    for (; i < block_num; i++) {
        sm4_tbox_decrypt(out, in, sm4key);
        out += 16;
        in += 16;
    }
}
