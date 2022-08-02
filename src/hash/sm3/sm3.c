#include <gmlib/hash/sm3.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdint.h>
#include "sm3_common.h"

static uint32_t SM3_INIT_DIGEST[8] = {
    0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600,
    0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E,
};

void sm3_init(SM3_CTX* ctx) {
    ctx->bsize = 0;
    ctx->dbits = 0;
    memcpy(ctx->state, SM3_INIT_DIGEST, sizeof(SM3_INIT_DIGEST));
}

void sm3_update(uint8_t* in, int inl, SM3_CTX* ctx) {
    ctx->dbits += inl * 8;  // 更新数据长度
    while (inl) {
        // 内存拷贝
        int size = SM3_BLOCK_SIZE - ctx->bsize;
        if (size > inl) {
            size = inl;
        }
        memcpy(ctx->buffer + ctx->bsize, in, size);
        in += size;          // 更新输入指针
        inl -= size;         // 更新输入长度
        ctx->bsize += size;  // 更新缓冲区长度
        // 压缩
        if (ctx->bsize == SM3_BLOCK_SIZE) {
            sm3_common_compress(ctx->buffer, ctx->state);
            ctx->bsize = 0;
        }
    }
}

void sm3_final(uint8_t* out, SM3_CTX* ctx) {
    // 填充
    int pad_num = (64 + 56 - 1 - ctx->bsize) % 64;  // 计算填充字节
    uint8_t buffer[SM3_BLOCK_SIZE * 2];             // 临时缓冲区
    int bsize = 0;
    memcpy(buffer, ctx->buffer, ctx->bsize);  // 拷贝残余数据
    bsize += ctx->bsize;                      // update
    buffer[bsize] = 0x80;                     // 10..0
    bsize++;                                  // update
    memset(buffer + bsize, 0, pad_num);       // 填充0
    bsize += pad_num;                         // update
    storeu64_be(buffer + bsize, ctx->dbits);  // 存储数据长度
    bsize += 8;                               // update
    // 压缩函数
    for (int i = 0; i < bsize; i += SM3_BLOCK_SIZE) {
        sm3_common_compress(buffer + i, ctx->state);
    }
    // 输出数据
    for (int i = 0; i < 8; i++) {
        storeu32_be(out + 4 * i, ctx->state[i]);
    }
}
