#include <gmlib/hash/sm3.h>
#include <memory.h>

#define HMAC_IPAD 0x36
#define HMAC_OPAD 0x5c

/// @brief SM3 HMAC 初始化
void hmac_sm3_init(uint8_t* key, int klen, HMAC_SM3_CTX* hmctx) {
    sm3_init(&hmctx->hctx);
    memset(hmctx->hkey, 0, SM3_BLOCK_SIZE);
    if (klen <= SM3_BLOCK_SIZE) {
        memcpy(hmctx->hkey, key, klen);
    } else {
        // hkey = Hash(key)
        SM3_CTX ctx;
        sm3_init(&ctx);
        sm3_update(key, klen, &ctx);
        sm3_final(hmctx->hkey, &ctx);
    }
    uint8_t ipad[SM3_BLOCK_SIZE];
    for (int i = 0; i < SM3_BLOCK_SIZE; i++) {
        ipad[i] = hmctx->hkey[i] ^ HMAC_IPAD;
    }
    // SM3(ipad||...
    sm3_update(ipad, SM3_BLOCK_SIZE, &hmctx->hctx);
}

/// @brief SM3 更新消息
void hmac_sm3_update(uint8_t* in, int inl, HMAC_SM3_CTX* hmctx) {
    // SM3(ipad||msg ...
    sm3_update(in, inl, &hmctx->hctx);
}

/// @brief SM3 Final 并输出摘要
void hmac_sm3_final(uint8_t* out, HMAC_SM3_CTX* hmctx) {
    uint8_t digest[SM3_DIGEST_SIZE], opad[SM3_BLOCK_SIZE];
    // SM3(ipad||msg)
    sm3_final(digest, &hmctx->hctx);
    for (int i = 0; i < SM3_BLOCK_SIZE; i++) {
        opad[i] = hmctx->hkey[i] ^ HMAC_OPAD;
    }
    // SM3(opad||digest)
    sm3_init(&hmctx->hctx);
    sm3_update(opad, SM3_BLOCK_SIZE, &hmctx->hctx);
    sm3_update(digest, SM3_DIGEST_SIZE, &hmctx->hctx);
    sm3_final(out, &hmctx->hctx);
}
