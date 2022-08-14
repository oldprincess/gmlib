#include <gmlib/err.h>
#include <gmlib/utils.h>
#include <memory.h>
#include "gcm/gctr.h"
#include "gcm/ghash.h"

static uint8_t ZERO_BUFFER[BLOCK_SIZE] = {0};

void gcm_init(uint8_t* key,              ///< [in]    用户密钥
              uint8_t* iv,               ///< [in]    初始向量
              int ivlen,                 ///< [in]    初始向量长度
              GHashTable* ht,            ///< [inout] GHash查找表(可为NULL)
              const CipherInfo* cipher,  ///< [in]    算法
              void* cctx,                ///< [inout] 算法上下文
              GCM_CTX* mctx) {
    // 初始化算法
    cipher->init(key, cctx);
    mctx->gctx.cctx = cctx;
    mctx->gctx.cipher = cipher;
    // 初始化GHash
    uint8_t H[BLOCK_SIZE];
    cipher->encrypt(H, ZERO_BUFFER, cctx);
    ghash_init(H, ht, &mctx->hctx);
    // 初始化 GCTR
    gctr_init(iv, ivlen, H, ht, &mctx->gctx);
    // 初始化 GCM
    mctx->alen = 0, mctx->clen = 0;
}

void gcm_update_aad(uint8_t* aad, int alen, GCM_CTX* mctx) {
    mctx->alen = alen;
    int rem = (BLOCK_SIZE - alen % BLOCK_SIZE) % BLOCK_SIZE;
    ghash_update(aad, alen, &mctx->hctx);
    ghash_update(ZERO_BUFFER, rem, &mctx->hctx);
}

/// @brief CBC 加密
void gcm_encrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        GCM_CTX* mctx) {
    gctr_update(out, outl, in, inl, &mctx->gctx);
    mctx->clen += *outl;
    ghash_update(out, *outl, &mctx->hctx);
}

/// @brief CBC 加密
void gcm_encrypt_final(uint8_t* out,  ///< [out] 输出
                       int* outl,     ///< [out] 输出长度
                       uint8_t* tag,  ///< [out] tag
                       int tlen,      ///< [in]  tag长度
                       GCM_CTX* mctx) {
    gctr_final(out, outl, &mctx->gctx);
    mctx->clen += *outl;
    int rem = (BLOCK_SIZE - mctx->clen % BLOCK_SIZE) % BLOCK_SIZE;
    ghash_update(out, *outl, &mctx->hctx);
    ghash_update(ZERO_BUFFER, rem, &mctx->hctx);
    // aclen
    uint8_t z1[BLOCK_SIZE], z2[BLOCK_SIZE];
    storeu64_be(z1, (uint64_t)(mctx->alen * 8));
    storeu64_be(z1 + 8, (uint64_t)(mctx->clen * 8));
    ghash_update(z1, BLOCK_SIZE, &mctx->hctx);
    // 生成 Tag
    CipherEncrypt encrypt = mctx->gctx.cipher->encrypt;
    encrypt(z2, mctx->gctx.j0, mctx->gctx.cctx);
    ghash_final(z1, &mctx->hctx);
    memxor(tag, z1, z2, tlen);
}

/// @brief CBC 解密
void gcm_decrypt_update(uint8_t* out,  ///< [out] 输出
                        int* outl,     ///< [out] 输出长度
                        uint8_t* in,   ///< [in]  输入
                        int inl,       ///< [in]  输入长度
                        GCM_CTX* mctx) {
    gctr_update(out, outl, in, inl, &mctx->gctx);
    mctx->clen += inl;
    ghash_update(in, inl, &mctx->hctx);
}

/// @brief CBC 解密
/// @return 错误码（0表示无错误）
int gcm_decrypt_final(uint8_t* out,  ///< [out] 输出
                      int* outl,     ///< [out] 输出长度
                      uint8_t* tag,  ///< [in]  tag
                      int tlen,      ///< [in]  tag长度
                      GCM_CTX* mctx) {
    gctr_final(out, outl, &mctx->gctx);

    int rem = (BLOCK_SIZE - mctx->clen % BLOCK_SIZE) % BLOCK_SIZE;
    ghash_update(ZERO_BUFFER, rem, &mctx->hctx);
    // aclen
    uint8_t z1[BLOCK_SIZE], z2[BLOCK_SIZE];
    storeu64_be(z1, (uint64_t)(mctx->alen * 8));
    storeu64_be(z1 + 8, (uint64_t)(mctx->clen * 8));
    ghash_update(z1, BLOCK_SIZE, &mctx->hctx);
    // 生成 Tag
    CipherEncrypt encrypt = mctx->gctx.cipher->encrypt;
    encrypt(z2, mctx->gctx.j0, mctx->gctx.cctx);
    ghash_final(z1, &mctx->hctx);
    memxor(z1, z1, z2, tlen);
    if (memcmp(z1, tag, tlen) != 0) {
        ERR_LOG("GCM Tag verification failed");
        goto error;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
