#include "gctr.h"
#include <gmlib/utils.h>
#include <memory.h>
#include "ghash.h"

static void gctr_inc32(uint8_t* r, uint8_t* cnt) {
    uint32_t n = loadu32_be(cnt + 12);
    storeu32_be(r + 12, n + 1);
    memcpy(r, cnt, 12);
}

void gctr_init(uint8_t* iv,  ///< [in]  初始向量
               int ivlen,    ///< [in]  初始向量长度
               uint8_t* H,
               GHashTable* ht,
               GCTR_CTX* gctx) {
    if (ivlen == (96 / 8)) {
        memset(gctx->j0, 0, BLOCK_SIZE);
        memcpy(gctx->j0, iv, 96 / 8);
        gctx->j0[BLOCK_SIZE - 1] = 1;
    } else {
        int s = ivlen % BLOCK_SIZE;
        uint8_t tmp[BLOCK_SIZE] = {0};
        GHash_CTX ctx;
        ghash_init(H, ht, &ctx);
        ghash_update(iv, ivlen, &ctx);
        while (s) {
            int size = 16;
            if (size > s) {
                size = s;
            }
            ghash_update(tmp, size, &ctx);
            s -= size;
        }
        storeu64_be(tmp, (uint64_t)(ivlen * 8));
        ghash_update(tmp, sizeof(uint64_t), &ctx);
        ghash_final(gctx->j0, &ctx);
    }
    gctr_inc32(gctx->j, gctx->j0);
    gctx->bsize = 0;
}

void gctr_update(uint8_t* out,  ///< [out]   输出
                 int* outl,     ///< [out]   输出长度
                 uint8_t* in,   ///< [in]    输入
                 int inl,       ///< [in]    输入长度
                 GCTR_CTX* gctx) {
    *outl = 0;  // 初始化 outl
    CipherEncrypt encrypt = gctx->cipher->encrypt;
    while (inl > 0) {
        // 拷贝缓冲区数据
        int size = BLOCK_SIZE - gctx->bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(gctx->buffer + gctx->bsize, in, size);
        gctx->bsize += size;      // 更新 buffer pos
        in += size, inl -= size;  // 更新 input
        // 缓冲区是否已满
        if (gctx->bsize == BLOCK_SIZE) {
            // 缓冲区填满，加密
            memcpy(out, gctx->buffer, BLOCK_SIZE);  // 临时拷贝
            memcpy(gctx->buffer, gctx->j, BLOCK_SIZE);

            gctr_inc32(gctx->j, gctx->j);
            encrypt(gctx->buffer, gctx->buffer, gctx->cctx);
            memxor(out, out, gctx->buffer, BLOCK_SIZE);

            gctx->bsize = 0;                         // 清空缓冲区
            *outl += BLOCK_SIZE, out += BLOCK_SIZE;  // 更新 output
        }
    }
}

void gctr_final(uint8_t* out, int* outl, GCTR_CTX* gctx) {
    CipherEncrypt encrypt = gctx->cipher->encrypt;
    if (gctx->bsize) {
        memcpy(out, gctx->buffer, gctx->bsize);  // 临时拷贝
        // encrypt
        encrypt(gctx->buffer, gctx->j, gctx->cctx);
        memxor(out, out, gctx->buffer, gctx->bsize);
    }

    *outl = gctx->bsize;  //更新output len
}
