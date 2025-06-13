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

static uint8_t key128128[16] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
};
static uint8_t pt128128[16] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
};
static uint8_t ct128128[16] = {
    0x32, 0x12, 0x2b, 0xed, 0xd0, 0x23, 0xc4, 0x29,
    0x02, 0x34, 0x70, 0xe1, 0x15, 0x8c, 0x14, 0x7d,
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
    cipher = EVP_CIPHER_fetch(NULL, "UBLOCK-128-ECB-128", "provider=gmlibprov");
    if (cipher == NULL)
    {
        PRINT("EVP_CIPHER_fetch failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }
    cctx = EVP_CIPHER_CTX_new();

    printf("[%d] EVP Cipher UBLOCK-128-ECB-128 start\n", __LINE__);

    ret = EVP_CipherInit(cctx, cipher, key128128, NULL, 1);
    if (!ret)
    {
        PRINT("EVP_CipherInit failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }

    uint8_t* out  = buffer;
    int      outl = 0;

    ret = EVP_CipherUpdate(cctx, out, &outl, pt128128, sizeof(pt128128));
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

    if ((size_t)out - (size_t)buffer != sizeof(ct128128))
    {
        PRINT("EVP_CipherFinal failed");
        exit(0);
    }
    if (memcmp(ct128128, buffer, sizeof(ct128128)) != 0)
    {
        PRINT("EVP_CipherFinal failed");
        exit(0);
    }

    EVP_CIPHER_CTX_free(cctx);
    EVP_CIPHER_free(cipher);
    OSSL_PROVIDER_unload(prov);

    printf("[%d] EVP CIPHER UBLOCK-128-ECB-128 PASS\n", __LINE__);

    return 0;
}