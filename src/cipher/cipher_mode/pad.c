#include "pad.h"
#include <gmlib/err.h>
#include <memory.h>

void pkcs7_pad(uint8_t* out, int* outl, uint8_t* in, int inl, int block_size) {
    int pad_num = block_size - inl % block_size;  // 计算填充值
    memmove(out, in, inl);                        // 拷贝
    memset(out + inl, pad_num, pad_num);          // 设置填充
    *outl = inl + pad_num;
}

int pkcs7_unpad(uint8_t* out, int* outl, uint8_t* in, int inl, int block_size) {
    // 校验 input len
    if (inl % block_size != 0 || inl == 0) {
        ERR_LOG("PKCS#7 Unpadding Error: invalid input size");
        goto error;
    }
    int pad_num = in[inl - 1];  // 获取填充值
    // 校验填充值正确性
    if (pad_num == 0) {
        ERR_LOG("PKCS#7 Unpadding Error: invalid padding data");
        goto error;
    }
    // 校验填充正确性
    for (int i = 0; i < pad_num; i++) {
        if (in[inl - i - 1] != pad_num) {
            ERR_LOG("PKCS#7 Unpadding Error: invalid padding data");
            goto error;
        }
    }
    // 拷贝
    memmove(out, in, inl - pad_num);
    *outl = inl - pad_num;

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
