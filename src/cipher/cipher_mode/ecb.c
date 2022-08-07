#include <gmlib/cipher/mode.h>
#include <gmlib/err.h>
#include <memory.h>
#include "pad.h"

/// @brief ECB模式加密update
void ecb_encrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherEncrypt encrypt,  // encrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* ecb_buffer,    // ecb buffer
                        int* ecb_bsize,         // ecb buffer size
                        int ecb_mbsize          // ecb max bsize
) {
    *outl = 0;  // 初始化 outl
    while (inl > 0) {
        // 拷贝缓冲区数据
        int size = ecb_mbsize - *ecb_bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(ecb_buffer + *ecb_bsize, in, size);
        *ecb_bsize += size;  // 更新 buffer pos
        in += size;          // 更新 input ptr
        inl -= size;         // 更新 input len
        // 缓冲区是否已满
        if (*ecb_bsize == ecb_mbsize) {
            // 缓冲区填满，加密
            encrypt(out, ecb_buffer, ecb_mbsize / block_size, cipher_key);
            *ecb_bsize = 0;       // 清空缓冲区
            *outl += ecb_mbsize;  //更新output len
            out += ecb_mbsize;    // 更新 output ptr
        }
    }
}

/// @brief ECB模式解密update
void ecb_decrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherDecrypt decrypt,  // decrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* ecb_buffer,    // ecb buffer
                        int* ecb_bsize,         // ecb buffer size
                        int ecb_mbsize          // ecb max bsize
) {
    *outl = 0;  // 初始化 outl
    while (inl > 0) {
        // 缓冲区是否已满
        if (*ecb_bsize == ecb_mbsize) {
            // 缓冲区填满，解密
            decrypt(out, ecb_buffer, ecb_mbsize / block_size, cipher_key);
            *ecb_bsize = 0;       // 清空缓冲区
            *outl += ecb_mbsize;  // 更新 output len
            out += ecb_mbsize;    // 更新 output ptr
        }
        // 拷贝缓冲区数据
        int size = ecb_mbsize - *ecb_bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(ecb_buffer + *ecb_bsize, in, size);
        *ecb_bsize += size;  // 更新 buffer pos
        in += size;          // 更新 input ptr
        inl -= size;         // 更新 input len
    }
}

/// @brief ECB模式加密final
void ecb_encrypt_final(uint8_t* out,           // output buffer
                       int* outl,              // output len
                       CipherEncrypt encrypt,  // encrypt func
                       void* cipher_key,       // cipher key
                       int block_size,         // cipher block size
                       uint8_t* ecb_buffer,    // ecb buffer
                       int* ecb_bsize          // ecb buffer size
) {
    // pkcs7 填充
    pkcs7_pad(ecb_buffer, ecb_bsize, ecb_buffer, *ecb_bsize, block_size);
    // 加密剩余数据
    encrypt(out, ecb_buffer, *ecb_bsize / block_size, cipher_key);
    *outl = *ecb_bsize;
}

/// @brief ECB模式加密final
int ecb_decrypt_final(uint8_t* out,           // output buffer
                      int* outl,              // output len
                      CipherDecrypt decrypt,  // decrypt func
                      void* cipher_key,       // cipher key
                      int block_size,         // cipher block size
                      uint8_t* ecb_buffer,    // ecb buffer
                      int* ecb_bsize          // ecb buffer size
) {
    if (*ecb_bsize == 0) {
        ERR_LOG("Empty data");
        goto error;
    }
    if (*ecb_bsize % block_size != 0) {
        ERR_LOG("Bad data size");
        goto error;
    }
    decrypt(ecb_buffer, ecb_buffer, *ecb_bsize / block_size, cipher_key);
    try_goto(pkcs7_unpad(out, outl, ecb_buffer, *ecb_bsize, block_size));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
