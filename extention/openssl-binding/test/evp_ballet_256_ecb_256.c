#include <openssl/core.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/provider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
#define LIB_NAME(name) #name
#else
#define LIB_NAME(name) "lib" #name
#endif

static uint8_t key256256[32] = {
    0xF7, 0xF5, 0xC0, 0xBE, 0x97, 0xC3, 0x88, 0x08,
    0x10, 0x93, 0xA8, 0x40, 0xDF, 0xFF, 0x19, 0x09, //
    0x6C, 0xDD, 0x2D, 0x00, 0x31, 0xCF, 0xD0, 0xEF,
    0x1F, 0x16, 0x0D, 0x44, 0x3D, 0xA7, 0xD4, 0xC1,
};
static uint8_t pt256256[32] = {
    0xFD, 0xC0, 0xBF, 0x9C, 0x6B, 0xFE, 0xB2, 0xFF,
    0xD1, 0x60, 0x12, 0x8E, 0x51, 0x90, 0xAF, 0x6C, //
    0xDA, 0xD2, 0x91, 0x11, 0x4D, 0x95, 0x39, 0x86,
    0xDE, 0x47, 0x2A, 0xD8, 0xBE, 0x6E, 0xA8, 0xC7,
};
static uint8_t ct256256[32] = {
    0x71, 0xFC, 0x5C, 0x31, 0x6C, 0x0B, 0xAE, 0x1B,
    0x2E, 0xD1, 0xE7, 0x69, 0x99, 0x6C, 0x28, 0x93, //
    0x9B, 0xC7, 0x41, 0x92, 0x36, 0x36, 0x77, 0x7C,
    0xB0, 0x7E, 0xFB, 0x8D, 0xBF, 0x2D, 0x07, 0xFF,
};

#define PRINT(fmt, ...) \
    printf("[LOG] " fmt " %s:%d\n", ##__VA_ARGS__, __FILE__, __LINE__)

int main()
{
    static uint8_t  buffer[1024 * 1024];
    int             ret;
    EVP_CIPHER*     cipher = NULL;
    EVP_CIPHER_CTX* cctx   = NULL;
    OSSL_PROVIDER*  prov   = NULL;

    // set search path
    ret = OSSL_PROVIDER_set_default_search_path(NULL, "./");
    if (!ret)
    {
        PRINT("Failed to set default search path");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }
    prov = OSSL_PROVIDER_load(NULL, LIB_NAME(gmlibprov));
    if (prov == NULL)
    {
        PRINT("OSSL_PROVIDER_load failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }

    printf("[%d] Provider loaded\n", __LINE__);

    // fetch cipher
    cipher = EVP_CIPHER_fetch(NULL, "Ballet-256-ECB-256", "provider=gmlibprov");
    if (cipher == NULL)
    {
        PRINT("EVP_CIPHER_fetch failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }
    cctx = EVP_CIPHER_CTX_new();

    printf("[%d] EVP Cipher Ballet-256-ECB-256 start\n", __LINE__);

    ret = EVP_CipherInit(cctx, cipher, key256256, NULL, 1);
    if (!ret)
    {
        PRINT("EVP_CipherInit failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }

    uint8_t* out  = buffer;
    int      outl = 0;

    ret = EVP_CipherUpdate(cctx, out, &outl, pt256256, sizeof(pt256256));
    if (!ret)
    {
        PRINT("EVP_CipherUpdate failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }
    out += outl;

    ret = EVP_CipherFinal(cctx, out, &outl);
    if (!ret)
    {
        PRINT("EVP_CipherFinal failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }
    out += outl;

    if ((size_t)out - (size_t)buffer != sizeof(ct256256))
    {
        PRINT("EVP_CipherFinal failed");
        exit(0);
    }
    if (memcmp(ct256256, buffer, sizeof(ct256256)) != 0)
    {
        PRINT("EVP_CipherFinal failed");
        exit(0);
    }

    EVP_CIPHER_CTX_free(cctx);
    EVP_CIPHER_free(cipher);
    OSSL_PROVIDER_unload(prov);

    printf("[%d] EVP CIPHER Ballet-256-ECB-256 PASS\n", __LINE__);

    return 0;
}