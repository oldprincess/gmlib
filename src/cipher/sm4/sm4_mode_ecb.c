#include <gmlib/cipher/mode.h>
#include <gmlib/cipher/sm4.h>
#include <gmlib/err.h>

void sm4_ecb_init(uint8_t* key, SM4_ECB_CTX* ecb_ctx) {
    sm4_keyinit(key, &(ecb_ctx->sm4key));
    ecb_ctx->bsize = 0;
}

void sm4_ecb_reset(SM4_ECB_CTX* ecb_ctx) {
    ecb_ctx->bsize = 0;
}

void sm4_ecb_encrypt_update(uint8_t* out,
                            int* outl,
                            uint8_t* in,
                            int inl,
                            SM4_ECB_CTX* ecb_ctx) {
    ecb_encrypt_update(out, outl, in, inl,          // input and output
                       (CipherEncrypt)sm4_encrypt,  // sm4 encrypt func
                       &ecb_ctx->sm4key,            // sm4 key
                       SM4_BLOCK_SIZE,              // sm4 block size
                       ecb_ctx->buffer,             // ecb ctx buffer
                       &ecb_ctx->bsize,             // ecb current buffer size
                       SM4_FAST_BLOCK_SIZE          // sm4 ecb max buffer size
    );
}

void sm4_ecb_decrypt_update(uint8_t* out,
                            int* outl,
                            uint8_t* in,
                            int inl,
                            SM4_ECB_CTX* ecb_ctx) {
    ecb_decrypt_update(out, outl, in, inl,          // input and output
                       (CipherDecrypt)sm4_decrypt,  // sm4 decrypt func
                       &ecb_ctx->sm4key,            // sm4 key
                       SM4_BLOCK_SIZE,              // sm4 block size
                       ecb_ctx->buffer,             // ecb ctx buffer
                       &ecb_ctx->bsize,             // ecb current buffer size
                       SM4_FAST_BLOCK_SIZE          // sm4 ecb max buffer size
    );
}

void sm4_ecb_encrypt_final(uint8_t* out, int* outl, SM4_ECB_CTX* ecb_ctx) {
    ecb_encrypt_final(out, outl,                   // output
                      (CipherEncrypt)sm4_encrypt,  // sm4 encrypt func
                      &ecb_ctx->sm4key,            // sm4 key
                      SM4_BLOCK_SIZE,              // sm4 block size
                      ecb_ctx->buffer,             // ecb ctx buffer
                      &ecb_ctx->bsize              // current bsize
    );
}

int sm4_ecb_decrypt_final(uint8_t* out, int* outl, SM4_ECB_CTX* ecb_ctx) {
    try_goto(ecb_decrypt_final(out, outl,                   // output
                               (CipherEncrypt)sm4_decrypt,  // sm4 decrypt func
                               &ecb_ctx->sm4key,            // sm4 key
                               SM4_BLOCK_SIZE,              // sm4 block size
                               ecb_ctx->buffer,             // ecb ctx buffer
                               &ecb_ctx->bsize              // current bsize
                               ));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
