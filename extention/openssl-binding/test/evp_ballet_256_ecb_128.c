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

static uint8_t key128256[32] = {
    0x1B, 0x5D, 0x0C, 0x50, 0x7C, 0x3B, 0xAA, 0x0D,
    0xC1, 0x3D, 0x75, 0x76, 0x61, 0x08, 0x4D, 0x7F, //
    0xD3, 0x4B, 0xF8, 0x65, 0xAF, 0x4F, 0x67, 0xE5,
    0x10, 0xD0, 0x3A, 0xAB, 0x3C, 0x0C, 0x86, 0x0D,
};
static uint8_t pt128256[16] = {
    0xC4, 0x19, 0xAF, 0xDD, 0x74, 0x78, 0x86, 0xB9,
    0xF8, 0xE6, 0x89, 0x0A, 0x3D, 0xB1, 0x9F, 0xA3,
};
static uint8_t ct128256[16] = {
    0x82, 0x72, 0x60, 0x60, 0x2D, 0xE8, 0x7F, 0x86,
    0x5F, 0xE5, 0x74, 0x43, 0xF2, 0x4C, 0xB7, 0xCF,
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
    cipher = EVP_CIPHER_fetch(NULL, "Ballet-256-ECB-128", "provider=gmlibprov");
    if (cipher == NULL)
    {
        PRINT("EVP_CIPHER_fetch failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }
    cctx = EVP_CIPHER_CTX_new();

    printf("[%d] EVP Cipher Ballet-256-ECB-128 start\n", __LINE__);

    ret = EVP_CipherInit(cctx, cipher, key128256, NULL, 1);
    if (!ret)
    {
        PRINT("EVP_CipherInit failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }

    uint8_t* out  = buffer;
    int      outl = 0;

    ret = EVP_CipherUpdate(cctx, out, &outl, pt128256, sizeof(pt128256));
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

    if ((size_t)out - (size_t)buffer != sizeof(ct128256))
    {
        PRINT("EVP_CipherFinal failed");
        exit(0);
    }
    if (memcmp(ct128256, buffer, sizeof(ct128256)) != 0)
    {
        PRINT("EVP_CipherFinal failed");
        exit(0);
    }

    EVP_CIPHER_CTX_free(cctx);
    EVP_CIPHER_free(cipher);
    OSSL_PROVIDER_unload(prov);

    printf("[%d] EVP CIPHER Ballet-256-ECB-128 PASS\n", __LINE__);

    return 0;
}