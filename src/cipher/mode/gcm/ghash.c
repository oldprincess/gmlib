#include <gmlib/cipher/mode.h>
#include <gmlib/utils.h>
#include <memory.h>
#include "gmul.h"

void ghash_init(uint8_t* H, GHashTable* ht, GHash_CTX* ctx) {
    memset(ctx->X, 0, BLOCK_SIZE);
    memcpy(ctx->H, H, BLOCK_SIZE);
    ctx->ht = ht;
    if (ht != NULL) {
        ghash_init_htable(H, *ht);
    }
    ctx->bsize = 0;
}

void ghash_update(uint8_t* in, int inl, GHash_CTX* ctx) {
    while (inl) {
        // 拷贝缓冲区
        int size = BLOCK_SIZE - ctx->bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(ctx->buffer + ctx->bsize, in, size);
        ctx->bsize += size;
        in += size, inl -= size;
        // gmul
        if (ctx->bsize == BLOCK_SIZE) {
            memxor(ctx->X, ctx->X, ctx->buffer, BLOCK_SIZE);
            if (ctx->ht == NULL) {
                gmul_common(ctx->X, ctx->X, ctx->H);
            } else {
                gmul_htable(ctx->X, ctx->X, *ctx->ht);
            }
            ctx->bsize = 0;
        }
    }
}

void ghash_final(uint8_t* out, GHash_CTX* ctx) {
    memcpy(out, ctx->X, BLOCK_SIZE);
}
