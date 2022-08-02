#include <gmlib/cipher/mode.h>
#include <gmlib/cipher/sm4.h>
#include <gmlib/err.h>
#include <memory.h>

void sm4_cbc_init(uint8_t* key, uint8_t* iv, SM4_CBC_CTX* cbc_ctx) {
    sm4_keyinit(key, &(cbc_ctx->sm4key));
    memcpy(cbc_ctx->iv, iv, SM4_BLOCK_SIZE);
    cbc_ctx->bsize = 0;
}

void sm4_cbc_reset(uint8_t* iv, SM4_CBC_CTX* cbc_ctx) {
    memcpy(cbc_ctx->iv, iv, SM4_BLOCK_SIZE);
    cbc_ctx->bsize = 0;
}

void sm4_cbc_encrypt_update(uint8_t* out,
                            int* outl,
                            uint8_t* in,
                            int inl,
                            SM4_CBC_CTX* cbc_ctx) {
    cbc_encrypt_update(out, outl, in, inl,          // input and output
                       (CipherEncrypt)sm4_encrypt,  // sm4 encrypt func
                       &cbc_ctx->sm4key,            // sm4 key
                       SM4_BLOCK_SIZE,              // sm4 block size
                       cbc_ctx->iv,                 // cbc iv
                       cbc_ctx->buffer,             // cbc ctx buffer
                       &cbc_ctx->bsize              // cbc current buffer size
    );
}

void sm4_cbc_decrypt_update(uint8_t* out,
                            int* outl,
                            uint8_t* in,
                            int inl,
                            SM4_CBC_CTX* cbc_ctx) {
    cbc_decrypt_update(out, outl, in, inl,          // input and output
                       (CipherDecrypt)sm4_decrypt,  // sm4 decrypt func
                       &cbc_ctx->sm4key,            // sm4 key
                       SM4_BLOCK_SIZE,              // sm4 block size
                       cbc_ctx->iv,                 // cbc iv
                       cbc_ctx->buffer,             // cbc ctx buffer
                       &cbc_ctx->bsize,             // cbc current buffer size
                       SM4_FAST_BLOCK_SIZE          // sm4 ecb max buffer size
    );
}

void sm4_cbc_encrypt_final(uint8_t* out, int* outl, SM4_CBC_CTX* cbc_ctx) {
    cbc_encrypt_final(out, outl,                   // output
                      (CipherEncrypt)sm4_encrypt,  // sm4 encrypt func
                      &cbc_ctx->sm4key,            // sm4 key
                      SM4_BLOCK_SIZE,              // sm4 block size
                      cbc_ctx->iv,                 // cbc iv
                      cbc_ctx->buffer,             // cbc ctx buffer
                      &cbc_ctx->bsize              // current bsize
    );
}

int sm4_cbc_decrypt_final(uint8_t* out, int* outl, SM4_CBC_CTX* cbc_ctx) {
    try_goto(cbc_decrypt_final(out, outl,                   // output
                               (CipherEncrypt)sm4_decrypt,  // sm4 decrypt func
                               &cbc_ctx->sm4key,            // sm4 key
                               SM4_BLOCK_SIZE,              // sm4 block size
                               cbc_ctx->iv,                 // cbc iv
                               cbc_ctx->buffer,             // cbc ctx buffer
                               &cbc_ctx->bsize              // current bsize
                               ));

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
