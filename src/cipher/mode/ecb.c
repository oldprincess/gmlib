#include <gmlib/cipher/mode.h>
#include <gmlib/err.h>
#include <memory.h>
#include "pad.h"

void ecb_init(uint8_t* key,
              const CipherInfo* cipher,
              void* cctx,
              ECB_CTX* mctx) {
    cipher->init(key, cctx);
    mctx->bsize = 0;
    mctx->cipher = cipher;
    mctx->cctx = cctx;
}

void ecb_encrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        ECB_CTX* mctx) {
    *outl = 0;  // 初始化 outl
    CipherEncrypt encrypt = mctx->cipher->encrypt;
    while (inl > 0) {
        // 拷贝缓冲区数据
        int size = BLOCK_SIZE - mctx->bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(mctx->buffer + mctx->bsize, in, size);
        mctx->bsize += size;      // 更新 buffer pos
        in += size, inl -= size;  // 更新 input
        // 缓冲区是否已满
        if (mctx->bsize == BLOCK_SIZE) {
            // 缓冲区填满，加密
            encrypt(out, mctx->buffer, mctx->cctx);
            mctx->bsize = 0;                         // 清空缓冲区
            *outl += BLOCK_SIZE, out += BLOCK_SIZE;  // 更新 output
        }
    }
}

void ecb_encrypt_final(uint8_t* out, int* outl, ECB_CTX* mctx) {
    // pkcs7 填充
    pkcs7_pad(mctx->buffer, &mctx->bsize, mctx->buffer, mctx->bsize,
              BLOCK_SIZE);
    // 加密剩余数据
    CipherEncrypt encrypt = mctx->cipher->encrypt;
    encrypt(out, mctx->buffer, mctx->cctx);
    *outl = mctx->bsize;
}

void ecb_decrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        ECB_CTX* mctx) {
    *outl = 0;  // 初始化 outl
    CipherDecrypt decrypt = mctx->cipher->decrypt;
    while (inl > 0) {
        // 缓冲区是否已满
        if (mctx->bsize == BLOCK_SIZE) {
            // 缓冲区填满，解密
            decrypt(out, mctx->buffer, mctx->cctx);
            mctx->bsize = 0;                         // 清空缓冲区
            *outl += BLOCK_SIZE, out += BLOCK_SIZE;  // 更新 output
        }
        // 拷贝缓冲区数据
        int size = BLOCK_SIZE - mctx->bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(mctx->buffer + mctx->bsize, in, size);
        mctx->bsize += size;      // 更新 buffer pos
        in += size, inl -= size;  // 更新 input
    }
}

int ecb_decrypt_final(uint8_t* out, int* outl, ECB_CTX* mctx) {
    if (mctx->bsize == 0) {
        ERR_LOG("Empty data");
        goto error;
    }
    if (mctx->bsize % BLOCK_SIZE != 0) {
        ERR_LOG("Bad data size");
        goto error;
    }
    CipherDecrypt decrypt = mctx->cipher->decrypt;
    decrypt(mctx->buffer, mctx->buffer, mctx->cctx);
    try_goto(pkcs7_unpad(out, outl, mctx->buffer, mctx->bsize, BLOCK_SIZE));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
