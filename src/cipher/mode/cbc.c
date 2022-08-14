#include <gmlib/cipher/mode.h>
#include <gmlib/err.h>
#include <gmlib/utils.h>
#include <memory.h>
#include "pad.h"

void cbc_init(uint8_t* key,
              uint8_t* iv,
              const CipherInfo* cipher,
              void* cctx,
              CBC_CTX* mctx) {
    cipher->init(key, cctx);
    mctx->bsize = 0;
    mctx->cipher = cipher;
    mctx->cctx = cctx;
    memcpy(mctx->iv, iv, BLOCK_SIZE);
}

void cbc_encrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        CBC_CTX* mctx) {
    *outl = 0;
    CipherEncrypt encrypt = mctx->cipher->encrypt;
    while (inl) {
        // copy buffer
        int size = BLOCK_SIZE - mctx->bsize;
        if (size > inl) {
            size = inl;
        }
        memmove(mctx->buffer + mctx->bsize, in, size);
        mctx->bsize += size;      // 更新 buffer size
        in += size, inl -= size;  // 更新 input

        // encrypt
        if (mctx->bsize == BLOCK_SIZE) {
            // xor data: IV ^ Plaintext
            memxor(mctx->buffer, mctx->buffer, mctx->iv, BLOCK_SIZE);
            // encrypt single block
            encrypt(mctx->iv, mctx->buffer, mctx->cctx);
            // copy output
            memcpy(out, mctx->iv, BLOCK_SIZE);

            out += BLOCK_SIZE, *outl += BLOCK_SIZE;  // 更新 output
            mctx->bsize = 0;                         // 清空缓冲区
        }
    }
}

void cbc_encrypt_final(uint8_t* out, int* outl, CBC_CTX* mctx) {
    CipherEncrypt encrypt = mctx->cipher->encrypt;
    // pkcs7 填充
    pkcs7_pad(mctx->buffer, &mctx->bsize, mctx->buffer, mctx->bsize,
              BLOCK_SIZE);
    // 加密剩余数据
    memxor(mctx->buffer, mctx->buffer, mctx->iv, BLOCK_SIZE);
    encrypt(out, mctx->buffer, mctx->cctx);

    *outl = BLOCK_SIZE;
}

void cbc_decrypt_update(uint8_t* out,
                        int* outl,
                        uint8_t* in,
                        int inl,
                        CBC_CTX* mctx) {
    *outl = 0;
    CipherDecrypt decrypt = mctx->cipher->decrypt;
    while (inl) {
        // decrypt
        if (mctx->bsize == BLOCK_SIZE) {
            // decrypt
            decrypt(out, mctx->buffer, mctx->cctx);
            // xor block
            memxor(out, out, mctx->iv, BLOCK_SIZE);
            // copy iv
            memcpy(mctx->iv, mctx->buffer, BLOCK_SIZE);

            out += BLOCK_SIZE, *outl += BLOCK_SIZE;  // 更新 output
            mctx->bsize = 0;                         // 清空缓冲区
        }
        // copy buffer
        int size = BLOCK_SIZE - mctx->bsize;
        if (size > inl) {
            size = inl;
        }
        memmove(mctx->buffer + mctx->bsize, in, size);
        mctx->bsize += size;      // 更新 buffer size
        in += size, inl -= size;  // 更新 input
    }
}

int cbc_decrypt_final(uint8_t* out, int* outl, CBC_CTX* mctx) {
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
    // xor
    memxor(mctx->buffer, mctx->buffer, mctx->iv, BLOCK_SIZE);
    try_goto(pkcs7_unpad(out, outl, mctx->buffer, mctx->bsize, BLOCK_SIZE));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
