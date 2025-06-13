#include <openssl/core_dispatch.h>
#include <openssl/core_names.h>
#include <openssl/err.h>
#include <openssl/params.h>

#include "cipher.h"

// =========================================================
// =========================================================
// ============ GMLIB Provider Defines =====================
// =========================================================
// =========================================================

static const char* PROV_NAME      = "gmlib";
static const char* PROV_VERSION   = "1.0.0";
static const char* PROV_BUILDINFO = "None";

static const char* PROV_PARAM_GMLIB_VERSION = "gmlib-version";
static const char* PROV_VALUE_GMLIB_VERSION = "2.0";

static const OSSL_PARAM* prov_gettable_params(void* provctx)
{
    static const OSSL_PARAM params[] = {
        // OSSL PROV PARAM
        OSSL_PARAM_utf8_ptr(OSSL_PROV_PARAM_NAME, NULL, 0),
        OSSL_PARAM_utf8_ptr(OSSL_PROV_PARAM_VERSION, NULL, 0),
        OSSL_PARAM_int(OSSL_PROV_PARAM_STATUS, NULL),
        OSSL_PARAM_utf8_ptr(OSSL_PROV_PARAM_BUILDINFO, NULL, 0),
        // PROV PARAM
        OSSL_PARAM_utf8_ptr(PROV_PARAM_GMLIB_VERSION, NULL, 0),
        OSSL_PARAM_END,
    };
    return params;
}

static int prov_get_params(void* provctx, OSSL_PARAM* params)
{
    OSSL_PARAM* p = NULL;

    // =====================================
    // ============= OSSL PARAM ============
    // =====================================

    if ((p = OSSL_PARAM_locate(params, OSSL_PROV_PARAM_NAME)) != NULL)
    {
        if (!OSSL_PARAM_set_utf8_ptr(p, PROV_NAME))
        {
            return 0;
        }
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_PROV_PARAM_VERSION)) != NULL)
    {
        if (!OSSL_PARAM_set_utf8_ptr(p, PROV_VERSION))
        {
            return 0;
        }
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_PROV_PARAM_BUILDINFO)) != NULL)
    {
        if (!OSSL_PARAM_set_utf8_ptr(p, PROV_BUILDINFO))
        {
            return 0;
        }
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_PROV_PARAM_STATUS)) != NULL)
    {
        if (!OSSL_PARAM_set_int(p, 1))
        {
            return 0;
        }
    }

    // =====================================
    // ============= PROV PARAM ============
    // =====================================

    if ((p = OSSL_PARAM_locate(params, PROV_PARAM_GMLIB_VERSION)) != NULL)
    {
        if (!OSSL_PARAM_set_utf8_ptr(p, PROV_VALUE_GMLIB_VERSION))
        {
            return 0;
        }
    }

    return 1;
}

static const OSSL_ALGORITHM* prov_query_operation(void* provctx,
                                                  int   operation_id,
                                                  int*  no_store)
{
    static const OSSL_ALGORITHM empty_algorithms[] = {
        {NULL, NULL, NULL, NULL},
    };

    *no_store = 0;
    switch (operation_id)
    {
        case OSSL_OP_CIPHER: return GMLIBPROV_cipher_algorithms;
        default: return empty_algorithms;
    }
}

static const OSSL_DISPATCH provider_functions[] = {
    {OSSL_FUNC_PROVIDER_TEARDOWN, NULL},
    {OSSL_FUNC_PROVIDER_GETTABLE_PARAMS, (void (*)(void))prov_gettable_params},
    {OSSL_FUNC_PROVIDER_GET_PARAMS, (void (*)(void))prov_get_params},
    {OSSL_FUNC_PROVIDER_QUERY_OPERATION, (void (*)(void))prov_query_operation},
    {OSSL_FUNC_PROVIDER_UNQUERY_OPERATION, NULL},
    {OSSL_FUNC_PROVIDER_GET_REASON_STRINGS, NULL},
    {OSSL_FUNC_PROVIDER_GET_CAPABILITIES, NULL},
    {OSSL_FUNC_PROVIDER_SELF_TEST, NULL},
    {OSSL_FUNC_PROVIDER_RANDOM_BYTES, NULL},
    OSSL_DISPATCH_END,
};

#if defined(_WIN32) || defined(_WIN64)
#define GMLIBPROV_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
// use -fvisibility=hidden to change the "default" behavior
#define GMLIBPROV_EXPORT __attribute__((visibility("default")))
#else
#define GMLIBPROV_EXPORT
#endif

GMLIBPROV_EXPORT int OSSL_provider_init(const OSSL_CORE_HANDLE* core,
                                        const OSSL_DISPATCH*    in,
                                        const OSSL_DISPATCH**   out,
                                        void**                  vprovctx)
{
    *vprovctx = NULL;
    *out      = provider_functions;
    return 1;
}