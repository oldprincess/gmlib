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
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, //
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};
static uint8_t pt256256[32] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, //
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};
static uint8_t ct256256[32] = {
    0xd8, 0xe9, 0x35, 0x1c, 0x5f, 0x4d, 0x27, 0xea,
    0x84, 0x21, 0x35, 0xca, 0x16, 0x40, 0xad, 0x4b, //
    0x0c, 0xe1, 0x19, 0xbc, 0x25, 0xc0, 0x3e, 0x7c,
    0x32, 0x9e, 0xa8, 0xfe, 0x93, 0xe7, 0xbd, 0xfe,
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
    cipher = EVP_CIPHER_fetch(NULL, "UBLOCK-256-ECB-256", "provider=gmlibprov");
    if (cipher == NULL)
    {
        PRINT("EVP_CIPHER_fetch failed");
        PRINT("%s", ERR_error_string(ERR_get_error(), NULL));
        exit(0);
    }
    cctx = EVP_CIPHER_CTX_new();

    printf("[%d] EVP Cipher UBLOCK-256-ECB-256 start\n", __LINE__);

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

    printf("[%d] EVP CIPHER UBLOCK-256-ECB-256 PASS\n", __LINE__);

    return 0;
}