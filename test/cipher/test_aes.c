#include <gmlib/cipher/aes.h>
#include <gmlib/err.h>
#include <gmlib/utils.h>
#include <memory.h>
#include <stdlib.h>

static uint8_t pt[16] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
};

static uint8_t ct128[AES_BLOCK_SIZE] = {
    0x69, 0xC4, 0xE0, 0xD8, 0x6A, 0x7B, 0x04, 0x30,
    0xD8, 0xCD, 0xB7, 0x80, 0x70, 0xB4, 0xC5, 0x5A,
};

static uint8_t key128[16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};

static uint8_t ct192[AES_BLOCK_SIZE] = {
    0xDD, 0xA9, 0x7C, 0xA4, 0x86, 0x4C, 0xDF, 0xE0,
    0x6E, 0xAF, 0x70, 0xA0, 0xEC, 0x0D, 0x71, 0x91,
};

static uint8_t key192[192 / 8] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  //
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,  //
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  //
};

static uint8_t ct256[AES_BLOCK_SIZE] = {
    0x8E, 0xA2, 0xB7, 0xCA, 0x51, 0x67, 0x45, 0xBF,
    0xEA, 0xFC, 0x49, 0x90, 0x4B, 0x49, 0x60, 0x89,
};

static uint8_t key256[256 / 8] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  //
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,  //
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  //
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
};

static uint8_t out[AES_BLOCK_SIZE];

void test_aes() {
    AES_CTX aeskey;
    // aes128
    aes_init(key128, 128, &aeskey);
    aes_encrypt(out, pt, &aeskey);
    if (memcmp(out, ct128, AES_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in aes_encrypt 128");
        goto error;
    }
    aes_decrypt(out, ct128, &aeskey);
    if (memcmp(out, pt, AES_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in aes_decrypt 128");
        goto error;
    }

    // aes 192
    aes_init(key192, 192, &aeskey);

    aes_encrypt(out, pt, &aeskey);
    if (memcmp(out, ct192, AES_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in aes_encrypt 192");
        goto error;
    }
    aes_decrypt(out, ct192, &aeskey);
    if (memcmp(out, pt, AES_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in aes_decrypt 192");
        goto error;
    }

    // aes 256
    aes_init(key256, 256, &aeskey);

    aes_encrypt(out, pt, &aeskey);
    if (memcmp(out, ct256, AES_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in aes_encrypt 256");
        goto error;
    }
    aes_decrypt(out, ct256, &aeskey);
    if (memcmp(out, pt, AES_BLOCK_SIZE) != 0) {
        ERR_LOG("Err in aes_decrypt 256");
        goto error;
    }

    return;
error:
    exit(-1);
}