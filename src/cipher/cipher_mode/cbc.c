#include <gmlib/cipher/mode.h>
#include <gmlib/err.h>
#include <gmlib/utils.h>
#include <memory.h>
#include "pad.h"

/// @brief CBC模式加密update
void cbc_encrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherEncrypt encrypt,  // encrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* cbc_iv,        // cbc iv
                        uint8_t* cbc_buffer,    // cbc buffer
                        int* cbc_bsize          // cbc buffer size
) {
    *outl = 0;
    while (inl) {
        // copy buffer
        int size = block_size - *cbc_bsize;
        if (size > inl) {
            size = inl;
        }
        memmove(cbc_buffer + *cbc_bsize, in, size);
        *cbc_bsize += size;  // 更新 buffer size
        in += size;          // 更新 input ptr
        inl -= size;         // 更新 input len

        // encrypt
        if (*cbc_bsize == block_size) {
            // xor data: IV ^ Plaintext
            memxor(cbc_buffer, cbc_buffer, cbc_iv, block_size);
            // encrypt single block
            encrypt(cbc_iv, cbc_buffer, 1, cipher_key);
            // copy output
            memcpy(out, cbc_iv, block_size);

            out += block_size;    // 更新 output ptr
            *outl += block_size;  // 更新 output len
            *cbc_bsize = 0;       // 清空缓冲区
        }
    }
}

/// @brief CBC模式解密update
void cbc_decrypt_update(uint8_t* out,           // output buffer
                        int* outl,              // output len
                        uint8_t* in,            // input buffer
                        int inl,                // input len
                        CipherDecrypt decrypt,  // decrypt func
                        void* cipher_key,       // cipher key
                        int block_size,         // cipher block size
                        uint8_t* cbc_iv,        // cbc iv
                        uint8_t* cbc_buffer,    // cbc buffer
                        int* cbc_bsize,         // cbc buffer size
                        int cbc_mbsize          // cbc max bsize
) {
    *outl = 0;
    while (inl) {
        // encrypt
        if (*cbc_bsize == cbc_mbsize) {
            // decrypt
            decrypt(out, cbc_buffer, cbc_mbsize / block_size, cipher_key);
            // xor block
            memxor(out, out, cbc_iv, block_size);
            // xor block
            memxor(out + block_size, out + block_size, cbc_buffer,
                   cbc_mbsize - block_size);
            // copy iv
            memcpy(cbc_iv, cbc_buffer + cbc_mbsize - block_size, block_size);

            out += cbc_mbsize;    // 更新 output ptr
            *outl += cbc_mbsize;  // 更新 output len
            *cbc_bsize = 0;       // 清空缓冲区
        }
        // copy buffer
        int size = cbc_mbsize - *cbc_bsize;
        if (size > inl) {
            size = inl;
        }
        memmove(cbc_buffer + *cbc_bsize, in, size);
        *cbc_bsize += size;  // 更新 buffer size
        in += size;          // 更新 input ptr
        inl -= size;         // 更新 input len
    }
}

/// @brief CBC模式加密final
void cbc_encrypt_final(uint8_t* out,           // output buffer
                       int* outl,              // output len
                       CipherEncrypt encrypt,  // encrypt func
                       void* cipher_key,       // cipher key
                       int block_size,         // cipher block size
                       uint8_t* cbc_iv,        // cbc iv
                       uint8_t* cbc_buffer,    // cbc buffer
                       int* cbc_bsize          // cbc buffer size
) {
    // pkcs7 填充
    pkcs7_pad(cbc_buffer, cbc_bsize, cbc_buffer, *cbc_bsize, block_size);
    // 加密剩余数据
    memxor(cbc_buffer, cbc_buffer, cbc_iv, block_size);
    encrypt(out, cbc_buffer, 1, cipher_key);

    *outl = block_size;
}

/// @brief CBC模式加密final
int cbc_decrypt_final(uint8_t* out,           // output buffer
                      int* outl,              // output len
                      CipherDecrypt decrypt,  // decrypt func
                      void* cipher_key,       // cipher key
                      int block_size,         // cipher block size
                      uint8_t* cbc_iv,        // cbc iv
                      uint8_t* cbc_buffer,    // cbc buffer
                      int* cbc_bsize          // cbc buffer size
) {
    if (*cbc_bsize == 0) {
        ERR_LOG("Empty data");
        goto error;
    }
    if (*cbc_bsize % block_size != 0) {
        ERR_LOG("Bad data size");
        goto error;
    }
    memcpy(out, cbc_buffer, *cbc_bsize - block_size);  // 将out区域用作临时内存
    decrypt(cbc_buffer, cbc_buffer, *cbc_bsize / block_size, cipher_key);
    // xor
    memxor(cbc_buffer, cbc_buffer, cbc_iv, block_size);
    memxor(cbc_buffer + block_size, cbc_buffer + block_size, out,
           *cbc_bsize - block_size);
    try_goto(pkcs7_unpad(out, outl, cbc_buffer, *cbc_bsize, block_size));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
