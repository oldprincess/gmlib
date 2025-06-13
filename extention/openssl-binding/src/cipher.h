#ifndef EXTENTION_OPENSSL_BINDING_CIPHER_H
#define EXTENTION_OPENSSL_BINDING_CIPHER_H

#include <openssl/core_dispatch.h>
#include <openssl/core_names.h>

#ifdef __cplusplus
extern "C" {
#endif

// ========================================================
// ========================================================
// ============== CIPHER SM4 DISPATCH DEFINE ==============
// ========================================================
// ========================================================

extern const OSSL_DISPATCH SM4_ecb_impl[];
extern const OSSL_DISPATCH SM4_cbc_impl[];
extern const OSSL_DISPATCH SM4_cfb_impl[];
extern const OSSL_DISPATCH SM4_ofb_impl[];
extern const OSSL_DISPATCH SM4_ctr_impl[];
extern const OSSL_DISPATCH SM4_gcm_impl[];

// ========================================================
// ========================================================
// ============== CIPHER UBLOCK DISPATCH DEFINE ===========
// ========================================================
// ========================================================

extern const OSSL_DISPATCH uBlock128128_ecb_impl[];
extern const OSSL_DISPATCH uBlock128128_cbc_impl[];
extern const OSSL_DISPATCH uBlock128128_ofb_impl[];
extern const OSSL_DISPATCH uBlock128128_cfb_impl[];
extern const OSSL_DISPATCH uBlock128128_ctr_impl[];
extern const OSSL_DISPATCH uBlock128128_gcm_impl[];

extern const OSSL_DISPATCH uBlock128256_ecb_impl[];
extern const OSSL_DISPATCH uBlock128256_cbc_impl[];
extern const OSSL_DISPATCH uBlock128256_ofb_impl[];
extern const OSSL_DISPATCH uBlock128256_cfb_impl[];
extern const OSSL_DISPATCH uBlock128256_ctr_impl[];
extern const OSSL_DISPATCH uBlock128256_gcm_impl[];

extern const OSSL_DISPATCH uBlock256256_ecb_impl[];
extern const OSSL_DISPATCH uBlock256256_cbc_impl[];
extern const OSSL_DISPATCH uBlock256256_ofb_impl[];
extern const OSSL_DISPATCH uBlock256256_cfb_impl[];
extern const OSSL_DISPATCH uBlock256256_ctr_impl[];

// ========================================================
// ========================================================
// ============== CIPHER Ballet DISPATCH DEFINE ===========
// ========================================================
// ========================================================

extern const OSSL_DISPATCH Ballet128128_ecb_impl[];
extern const OSSL_DISPATCH Ballet128128_cbc_impl[];
extern const OSSL_DISPATCH Ballet128128_ofb_impl[];
extern const OSSL_DISPATCH Ballet128128_cfb_impl[];
extern const OSSL_DISPATCH Ballet128128_ctr_impl[];
extern const OSSL_DISPATCH Ballet128128_gcm_impl[];

extern const OSSL_DISPATCH Ballet128256_ecb_impl[];
extern const OSSL_DISPATCH Ballet128256_cbc_impl[];
extern const OSSL_DISPATCH Ballet128256_ofb_impl[];
extern const OSSL_DISPATCH Ballet128256_cfb_impl[];
extern const OSSL_DISPATCH Ballet128256_ctr_impl[];
extern const OSSL_DISPATCH Ballet128256_gcm_impl[];

extern const OSSL_DISPATCH Ballet256256_ecb_impl[];
extern const OSSL_DISPATCH Ballet256256_cbc_impl[];
extern const OSSL_DISPATCH Ballet256256_ofb_impl[];
extern const OSSL_DISPATCH Ballet256256_cfb_impl[];
extern const OSSL_DISPATCH Ballet256256_ctr_impl[];

// ========================================================
// ========================================================
// ============== CIPHER DISPATCH DEFINE ==================
// ========================================================
// ========================================================

// algorithm_names
// property_definition
// implementation
// algorithm_description

static const OSSL_ALGORITHM GMLIBPROV_cipher_algorithms[] = {
    // SM4 128 KEYLEN 128 BLOCKSIZE
    {"SM4-ECB:1.2.156.10197.1.104.1", "provider=gmlibprov", SM4_ecb_impl, NULL},
    {"SM4-CBC:1.2.156.10197.1.104.2", "provider=gmlibprov", SM4_cbc_impl, NULL},
    {"SM4-OFB:1.2.156.10197.1.104.3", "provider=gmlibprov", SM4_ofb_impl, NULL},
    {"SM4-CFB:1.2.156.10197.1.104.4", "provider=gmlibprov", SM4_cfb_impl, NULL},
    {"SM4-CTR:1.2.156.10197.1.104.7", "provider=gmlibprov", SM4_ctr_impl, NULL},
    {"SM4-GCM:1.2.156.10197.1.104.8", "provider=gmlibprov", SM4_gcm_impl, NULL},
    // UBLOCK 128 KEYLEN 128 BLOCKSIZE
    {"UBLOCK-128-ECB-128", "provider=gmlibprov", uBlock128128_ecb_impl, NULL},
    {"UBLOCK-128-CBC-128", "provider=gmlibprov", uBlock128128_cbc_impl, NULL},
    {"UBLOCK-128-OFB-128", "provider=gmlibprov", uBlock128128_ofb_impl, NULL},
    {"UBLOCK-128-CFB-128", "provider=gmlibprov", uBlock128128_cfb_impl, NULL},
    {"UBLOCK-128-CTR-128", "provider=gmlibprov", uBlock128128_ctr_impl, NULL},
    {"UBLOCK-128-GCM-128", "provider=gmlibprov", uBlock128128_gcm_impl, NULL},
    // UBLOCK 256 KEYLEN 128 BLOCKSIZE
    {"UBLOCK-256-ECB-128", "provider=gmlibprov", uBlock128256_ecb_impl, NULL},
    {"UBLOCK-256-CBC-128", "provider=gmlibprov", uBlock128256_cbc_impl, NULL},
    {"UBLOCK-256-OFB-128", "provider=gmlibprov", uBlock128256_ofb_impl, NULL},
    {"UBLOCK-256-CFB-128", "provider=gmlibprov", uBlock128256_cfb_impl, NULL},
    {"UBLOCK-256-CTR-128", "provider=gmlibprov", uBlock128256_ctr_impl, NULL},
    {"UBLOCK-256-GCM-128", "provider=gmlibprov", uBlock128256_gcm_impl, NULL},
    // UBLOCK 256 KEYLEN 256 BLOCKSIZE
    {"UBLOCK-256-ECB-256", "provider=gmlibprov", uBlock256256_ecb_impl, NULL},
    {"UBLOCK-256-CBC-256", "provider=gmlibprov", uBlock256256_cbc_impl, NULL},
    {"UBLOCK-256-OFB-256", "provider=gmlibprov", uBlock256256_ofb_impl, NULL},
    {"UBLOCK-256-CFB-256", "provider=gmlibprov", uBlock256256_cfb_impl, NULL},
    {"UBLOCK-256-CTR-256", "provider=gmlibprov", uBlock256256_ctr_impl, NULL},
    // BALLET 128 KEYLEN 128 BLOCKSIZE
    {"BALLET-128-ECB-128", "provider=gmlibprov", Ballet128128_ecb_impl, NULL},
    {"BALLET-128-CBC-128", "provider=gmlibprov", Ballet128128_cbc_impl, NULL},
    {"BALLET-128-OFB-128", "provider=gmlibprov", Ballet128128_ofb_impl, NULL},
    {"BALLET-128-CFB-128", "provider=gmlibprov", Ballet128128_cfb_impl, NULL},
    {"BALLET-128-CTR-128", "provider=gmlibprov", Ballet128128_ctr_impl, NULL},
    {"BALLET-128-GCM-128", "provider=gmlibprov", Ballet128128_gcm_impl, NULL},
    // BALLET 256 KEYLEN 128 BLOCKSIZE
    {"BALLET-256-ECB-128", "provider=gmlibprov", Ballet128256_ecb_impl, NULL},
    {"BALLET-256-CBC-128", "provider=gmlibprov", Ballet128256_cbc_impl, NULL},
    {"BALLET-256-OFB-128", "provider=gmlibprov", Ballet128256_ofb_impl, NULL},
    {"BALLET-256-CFB-128", "provider=gmlibprov", Ballet128256_cfb_impl, NULL},
    {"BALLET-256-CTR-128", "provider=gmlibprov", Ballet128256_ctr_impl, NULL},
    {"BALLET-256-GCM-128", "provider=gmlibprov", Ballet128256_gcm_impl, NULL},
    // BALLET 256 KEYLEN 256 BLOCKSIZE
    {"BALLET-256-ECB-256", "provider=gmlibprov", Ballet256256_ecb_impl, NULL},
    {"BALLET-256-CBC-256", "provider=gmlibprov", Ballet256256_cbc_impl, NULL},
    {"BALLET-256-CFB-256", "provider=gmlibprov", Ballet256256_cfb_impl, NULL},
    {"BALLET-256-OFB-256", "provider=gmlibprov", Ballet256256_ofb_impl, NULL},
    {"BALLET-256-CTR-256", "provider=gmlibprov", Ballet256256_ctr_impl, NULL},
    // END
    {NULL, NULL, NULL, NULL},
};

#ifdef __cplusplus
}
#endif

#endif