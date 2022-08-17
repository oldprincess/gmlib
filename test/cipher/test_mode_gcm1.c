#include <gmlib/cipher/aes.h>
#include <gmlib/cipher/mode.h>
#include <gmlib/err.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdlib.h>

/* AES key */
static uint8_t gcm_key[] = {
    0xee, 0xbc, 0x1f, 0x57, 0x48, 0x7f, 0x51, 0x92,  //
    0x1c, 0x04, 0x65, 0x66, 0x5f, 0x8a, 0xe6, 0xd1,  //
    0x65, 0x8b, 0xb2, 0x6d, 0xe6, 0xf8, 0xa0, 0x69,  //
    0xa3, 0x52, 0x02, 0x93, 0xa5, 0x72, 0x07, 0x8f,  //
};

/* Unique initialisation vector */
static uint8_t gcm_iv[] = {
    0x99, 0xaa, 0x3e, 0x68, 0xed, 0x81, 0x73, 0xa0, 0xee, 0xd0, 0x66, 0x84,
};

/* Example plaintext to encrypt */
static uint8_t gcm_pt[] = {
    0xf5, 0x6e, 0x87, 0x05, 0x5b, 0xc3, 0x2d, 0x0e,
    0xeb, 0x31, 0xb2, 0xea, 0xcc, 0x2b, 0xf2, 0xa5,
};

/*
 * Example of Additional Authenticated Data (AAD), i.e. unencrypted data
 * which can be authenticated using the generated Tag value.
 */
static uint8_t gcm_aad[] = {
    0x4d, 0x23, 0xc3, 0xce, 0xc3, 0x34, 0xb4, 0x9b,
    0xdb, 0x37, 0x0c, 0x43, 0x7f, 0xec, 0x78, 0xde,
};

/* Expected ciphertext value */
static uint8_t gcm_ct[] = {
    0xf7, 0x26, 0x44, 0x13, 0xa8, 0x4c, 0x0e, 0x7c,
    0xd5, 0x36, 0x86, 0x7e, 0xb9, 0xf2, 0x17, 0x36,
};

/* Expected AEAD Tag value */
static uint8_t gcm_tag[] = {
    0x67, 0xba, 0x05, 0x10, 0x26, 0x2a, 0xe4, 0x87,
    0xd7, 0x37, 0xee, 0x62, 0x98, 0xf7, 0x7e, 0x0c,
};

static uint8_t out[BLOCK_SIZE * 4];
static int outl;
static uint8_t tag[BLOCK_SIZE];

void test_mode_gcm1() {
    GCM_CTX ctx;
    AES_CTX aes_ctx;
    uint8_t* outptr;
    const CipherInfo* cipher = &AES256Info;

    // 加密测试
    outptr = out;
    gcm_init(gcm_key, gcm_iv, sizeof(gcm_iv), NULL, cipher, &aes_ctx, &ctx);
    gcm_update_aad(gcm_aad, sizeof(gcm_aad), &ctx);
    gcm_encrypt_update(outptr, &outl, gcm_pt, sizeof(gcm_pt), &ctx);
    outptr += outl;
    gcm_encrypt_final(outptr, &outl, tag, sizeof(gcm_tag), &ctx);
    outptr += outl;

    if (memcmp(tag, gcm_tag, sizeof(gcm_tag)) != 0 ||
        memcmp(out, gcm_ct, sizeof(gcm_ct)) != 0) {
        ERR_LOG("Err in aes_gcm");
        goto error;
    }
    // 解密测试
    outptr = out;
    gcm_init(gcm_key, gcm_iv, sizeof(gcm_iv), NULL, cipher, &aes_ctx, &ctx);
    gcm_update_aad(gcm_aad, sizeof(gcm_aad), &ctx);
    gcm_decrypt_update(outptr, &outl, gcm_ct, sizeof(gcm_ct), &ctx);
    outptr += outl;
    try_goto(gcm_decrypt_final(outptr, &outl, tag, sizeof(gcm_tag), &ctx));
    outptr += outl;
    if (memcmp(out, gcm_pt, sizeof(gcm_pt)) != 0) {
        ERR_LOG("Err in aes_gcm");
        goto error;
    }

    // 测试GHash 查找表
    GHashTable ht;
    // 加密测试
    outptr = out;
    gcm_init(gcm_key, gcm_iv, sizeof(gcm_iv), &ht, cipher, &aes_ctx, &ctx);
    gcm_update_aad(gcm_aad, sizeof(gcm_aad), &ctx);
    gcm_encrypt_update(outptr, &outl, gcm_pt, sizeof(gcm_pt), &ctx);
    outptr += outl;
    gcm_encrypt_final(outptr, &outl, tag, sizeof(gcm_tag), &ctx);
    outptr += outl;

    if (memcmp(tag, gcm_tag, sizeof(gcm_tag)) != 0 ||
        memcmp(out, gcm_ct, sizeof(gcm_ct)) != 0) {
        ERR_LOG("Err in aes_gcm");
        goto error;
    }
    // 解密测试
    outptr = out;
    gcm_init(gcm_key, gcm_iv, sizeof(gcm_iv), &ht, cipher, &aes_ctx, &ctx);
    gcm_update_aad(gcm_aad, sizeof(gcm_aad), &ctx);
    gcm_decrypt_update(outptr, &outl, gcm_ct, sizeof(gcm_ct), &ctx);
    outptr += outl;
    try_goto(gcm_decrypt_final(outptr, &outl, tag, sizeof(gcm_tag), &ctx));
    outptr += outl;
    if (memcmp(out, gcm_pt, sizeof(gcm_pt)) != 0) {
        ERR_LOG("Err in aes_gcm");
        goto error;
    }

    return;
error:
    exit(-1);
}
