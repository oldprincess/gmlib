#include <gmlib/cipher/mode.h>
#include <gmlib/cipher/sm4.h>
#include <gmlib/err.h>
#include <memory.h>

void sm4_ctr_init(uint8_t* key, uint8_t* iv, SM4_CTR_CTX* ctr_ctx) {
    sm4_keyinit(key, &(ctr_ctx->sm4key));
    memcpy(ctr_ctx->iv, iv, SM4_BLOCK_SIZE);
    ctr_ctx->bsize = 0;
}

void sm4_ctr_reset(uint8_t* iv, SM4_CTR_CTX* ctr_ctx) {
    memcpy(ctr_ctx->iv, iv, SM4_BLOCK_SIZE);
    ctr_ctx->bsize = 0;
}

static void sm4_ctr_update(uint8_t* out,
                           int* outl,
                           uint8_t* in,
                           int inl,
                           SM4_CTR_CTX* ctr_ctx) {
    ctr_update(out, outl, in, inl,          // input and output
               (CipherEncrypt)sm4_encrypt,  // sm4 encrypt func
               &ctr_ctx->sm4key,            // sm4 key
               SM4_BLOCK_SIZE,              // sm4 block size
               ctr_ctx->iv,                 // ctr iv
               ctr_ctx->buffer,             // ctr ctx buffer
               &ctr_ctx->bsize,             // ctr current buffer size
               SM4_FAST_BLOCK_SIZE          // sm4 ctr max buffer size
    );
}

static void sm4_ctr_final(uint8_t* out, int* outl, SM4_CTR_CTX* ctr_ctx) {
    ctr_final(out, outl,                   // output
              (CipherEncrypt)sm4_encrypt,  // sm4 encrypt func
              &ctr_ctx->sm4key,            // sm4 key
              SM4_BLOCK_SIZE,              // sm4 block size
              ctr_ctx->iv,                 // ctr iv
              ctr_ctx->buffer,             // ctr ctx buffer
              &ctr_ctx->bsize              // current bsize
    );
}

void sm4_ctr_encrypt_update(uint8_t* out,
                            int* outl,
                            uint8_t* in,
                            int inl,
                            SM4_CTR_CTX* ctr_ctx) {
    sm4_ctr_update(out, outl, in, inl, ctr_ctx);
}

void sm4_ctr_decrypt_update(uint8_t* out,
                            int* outl,
                            uint8_t* in,
                            int inl,
                            SM4_CTR_CTX* ctr_ctx) {
    sm4_ctr_update(out, outl, in, inl, ctr_ctx);
}

void sm4_ctr_encrypt_final(uint8_t* out, int* outl, SM4_CTR_CTX* ctr_ctx) {
    sm4_ctr_final(out, outl, ctr_ctx);
}

void sm4_ctr_decrypt_final(uint8_t* out, int* outl, SM4_CTR_CTX* ctr_ctx) {
    sm4_ctr_final(out, outl, ctr_ctx);
}
