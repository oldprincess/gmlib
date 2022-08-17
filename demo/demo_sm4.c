#include <gmlib/cipher/mode.h>
#include <gmlib/cipher/sm4.h>
#include <gmlib/err.h>
#include <gmlib/utils.h>

static uint8_t sm4_key[SM4_KEYLEN] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
};

static uint8_t sm4_pt[SM4_BLOCK_SIZE] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
};

static uint8_t out[SM4_BLOCK_SIZE * 2];

int main() {
    SM4_CTX sm4key;
    sm4_init(sm4_key, &sm4key);
    sm4_encrypt(out, sm4_pt, &sm4key);
    // 09 32 5c 48 53 83 2d cb 93 37 a5 98 4f 67 1b 9a
    dump_data(out, SM4_BLOCK_SIZE);

    ECB_CTX ctx;
    uint8_t* outptr = out;
    int outl;
    ecb_init(sm4_key, &SM4Info, &sm4key, &ctx);
    ecb_encrypt_update(outptr, &outl, sm4_pt, sizeof(sm4_pt), &ctx);
    outptr += outl;
    ecb_encrypt_final(outptr, &outl, &ctx);
    outptr += outl;
    // 09 32 5c 48 53 83 2d cb 93 37 a5 98 4f 67 1b 9a
    // 00 2a 8a 4e fa 86 3c ca d0 24 ac 03 00 bb 40 d2
    dump_data(out, (int)(outptr - out));

    return 0;
}
