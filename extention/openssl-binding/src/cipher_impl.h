#ifndef EXTENTION_OPENSSL_BINDING_CIPHER_IMPL_H
#define EXTENTION_OPENSSL_BINDING_CIPHER_IMPL_H

// GMLIB
#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/block_cipher_mode/cbc_mode.h>
#include <gmlib/block_cipher_mode/cfb_mode.h>
#include <gmlib/block_cipher_mode/ctr_mode.h>
#include <gmlib/block_cipher_mode/ecb_mode.h>
#include <gmlib/block_cipher_mode/gcm_mode.h>
#include <gmlib/block_cipher_mode/ofb_mode.h>
// OPENSSL
#include <openssl/core_names.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/params.h>
// STD
#include <cstring>
#include <stdexcept>
#include <vector>

#if defined(DEBUG) || defined(_DEBUG)

#define GMLIBPROV_CIPHER_IMPL_PRINT(stream, fmt, ...)            \
    std::fprintf(stream, "[GMLIBPROV] " fmt ". %s(...) %s:%d\n", \
                 ##__VA_ARGS__, __FUNCTION__, __FILE__, __LINE__)

#else

#define GMLIBPROV_CIPHER_IMPL_PRINT(stream, fmt, ...)

#endif

#define GMLIBPROV_CIPHER_IMPL_ASSERT(expression)          \
    if (!(expression))                                    \
    {                                                     \
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, #expression); \
        return 0;                                         \
    }

namespace gmlibprov {

// ========================================================
// ========================================================
// ============== CIPHER CTX STRUCT DEF ===================
// ========================================================
// ========================================================

enum class CipherStatus
{
    UNKNOWN,
    INITED,
    RUNNING,
    FINISHED,
};

template <class T_>
struct ECB_CTX
{
    using T = T_;

    block_cipher_mode::EcbEncryptor<T> encryptor;
    block_cipher_mode::EcbDecryptor<T> decryptor;

    int               enc    = 0;
    enum CipherStatus status = CipherStatus::UNKNOWN;
};

template <class T_>
struct CBC_CTX
{
    using T = T_;

    block_cipher_mode::CbcEncryptor<T> encryptor;
    block_cipher_mode::CbcDecryptor<T> decryptor;

    int               enc               = 0;
    std::uint8_t      iv[T::BLOCK_SIZE] = {0};
    enum CipherStatus status            = CipherStatus::UNKNOWN;
};

template <class T_>
struct OFB_CTX
{
    using T = T_;

    block_cipher_mode::OfbEncryptor<T> encryptor;
    block_cipher_mode::OfbDecryptor<T> decryptor;

    int               enc               = 0;
    std::uint8_t      iv[T::BLOCK_SIZE] = {0};
    enum CipherStatus status            = CipherStatus::UNKNOWN;
};

template <class T_>
struct CFB_CTX
{
    using T = T_;

    block_cipher_mode::CfbEncryptor<T> encryptor;
    block_cipher_mode::CfbDecryptor<T> decryptor;

    int               enc               = 0;
    std::uint8_t      iv[T::BLOCK_SIZE] = {0};
    enum CipherStatus status            = CipherStatus::UNKNOWN;
};

template <class T_>
struct CTR_CTX
{
    using T = T_;

    block_cipher_mode::CtrEncryptor<T> encryptor;
    block_cipher_mode::CtrDecryptor<T> decryptor;

    int               enc               = 0;
    std::uint8_t      iv[T::BLOCK_SIZE] = {0};
    enum CipherStatus status            = CipherStatus::UNKNOWN;
};

template <class T_>
struct GCM_CTX
{
    using T     = T_;
    using bytes = std::vector<std::uint8_t>;

    block_cipher_mode::GcmEncryptor<T> encryptor;
    block_cipher_mode::GcmDecryptor<T> decryptor;

    int               enc                  = 0;
    std::uint8_t      key[T::USER_KEY_LEN] = {0};
    bytes             iv                   = bytes(12);
    bytes             tag                  = bytes(16);
    enum CipherStatus status               = CipherStatus::UNKNOWN;
};

// ========================================================
// ========================================================
// ============== CIPHER NEW CTX FUNC DEF =================
// ========================================================
// ========================================================

template <class CIPHR_CTX>
static void* CIPHER_CTX_newctx()
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "newctx");
    try
    {
        return new CIPHR_CTX();
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return nullptr;
    }
}

template <class T>
static void* ECB_newctx()
{
    return CIPHER_CTX_newctx<ECB_CTX<T>>();
}

template <class T>
static void* CBC_newctx()
{
    return CIPHER_CTX_newctx<CBC_CTX<T>>();
}

template <class T>
static void* OFB_newctx()
{
    return CIPHER_CTX_newctx<OFB_CTX<T>>();
}

template <class T>
static void* CFB_newctx()
{
    return CIPHER_CTX_newctx<CFB_CTX<T>>();
}

template <class T>
static void* CTR_newctx()
{
    return CIPHER_CTX_newctx<CTR_CTX<T>>();
}

template <class T>
static void* GCM_newctx()
{
    return CIPHER_CTX_newctx<GCM_CTX<T>>();
}

// ========================================================
// ========================================================
// ============== CIPHER ENCRYPT INIT FUNC DEF ============
// ========================================================
// ========================================================

template <class CIPHER_CTX>
static int CIPHER_CTX_NOIV_init(void*                cctx,
                                const unsigned char* key,
                                size_t               keylen,
                                const unsigned char* iv,
                                size_t               ivlen,
                                int                  enc,
                                const OSSL_PARAM     params[])
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "init(keylen=%zu, ivlen=%zu, enc=%d)",
                                keylen, ivlen, enc);
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    GMLIBPROV_CIPHER_IMPL_ASSERT(keylen == CIPHER_CTX::T::USER_KEY_LEN);
    GMLIBPROV_CIPHER_IMPL_ASSERT(ivlen == 0);
    try
    {
        auto* obj = (CIPHER_CTX*)cctx;
        if (enc)
        {
            obj->encryptor.init(key);
            obj->enc = 1;
        }
        else
        {
            obj->decryptor.init(key);
            obj->enc = 0;
        }
        obj->status = CipherStatus::RUNNING;
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return 0;
    }
    return 1;
}

template <class CIPHER_CTX>
static int CIPHER_CTX_init(void*                cctx,
                           const unsigned char* key,
                           size_t               keylen,
                           const unsigned char* iv,
                           size_t               ivlen,
                           int                  enc,
                           const OSSL_PARAM     params[])
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "init(keylen=%zu, ivlen=%zu, enc=%d)",
                                keylen, ivlen, enc);
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    GMLIBPROV_CIPHER_IMPL_ASSERT(keylen == CIPHER_CTX::T::USER_KEY_LEN);
    GMLIBPROV_CIPHER_IMPL_ASSERT(ivlen == CIPHER_CTX::T::BLOCK_SIZE);
    try
    {
        auto* obj = (CIPHER_CTX*)cctx;
        if (enc)
        {
            obj->encryptor.init(key, iv);
            obj->enc = 1;
        }
        else
        {
            obj->decryptor.init(key, iv);
            obj->enc = 0;
        }
        obj->status = CipherStatus::RUNNING;
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return 0;
    }
    return 1;
}

template <class T>
static int ECB_init(void*                cctx,
                    const unsigned char* key,
                    size_t               keylen,
                    const unsigned char* iv,
                    size_t               ivlen,
                    int                  enc,
                    const OSSL_PARAM     params[])
{
    return CIPHER_CTX_NOIV_init<ECB_CTX<T>>(cctx, key, keylen, iv, ivlen, enc,
                                            params);
}

template <class T>
static int CBC_init(void*                cctx,
                    const unsigned char* key,
                    size_t               keylen,
                    const unsigned char* iv,
                    size_t               ivlen,
                    int                  enc,
                    const OSSL_PARAM     params[])
{
    return CIPHER_CTX_init<CBC_CTX<T>>(cctx, key, keylen, iv, ivlen, enc,
                                       params);
}

template <class T>
static int OFB_init(void*                cctx,
                    const unsigned char* key,
                    size_t               keylen,
                    const unsigned char* iv,
                    size_t               ivlen,
                    int                  enc,
                    const OSSL_PARAM     params[])
{
    return CIPHER_CTX_init<OFB_CTX<T>>(cctx, key, keylen, iv, ivlen, enc,
                                       params);
}

template <class T>
static int CFB_init(void*                cctx,
                    const unsigned char* key,
                    size_t               keylen,
                    const unsigned char* iv,
                    size_t               ivlen,
                    int                  enc,
                    const OSSL_PARAM     params[])
{
    return CIPHER_CTX_init<CFB_CTX<T>>(cctx, key, keylen, iv, ivlen, enc,
                                       params);
}

template <class T>
static int CTR_init(void*                cctx,
                    const unsigned char* key,
                    size_t               keylen,
                    const unsigned char* iv,
                    size_t               ivlen,
                    int                  enc,
                    const OSSL_PARAM     params[])
{
    return CIPHER_CTX_init<CTR_CTX<T>>(cctx, key, keylen, iv, ivlen, enc,
                                       params);
}

template <class T>
static int GCM_init(void*                cctx,
                    const unsigned char* key,
                    size_t               keylen,
                    const unsigned char* iv,
                    size_t               ivlen,
                    int                  enc,
                    const OSSL_PARAM     params[])
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "init(keylen=%zu, ivlen=%zu, enc=%d)",
                                keylen, ivlen, enc);
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    GMLIBPROV_CIPHER_IMPL_ASSERT(keylen == T::USER_KEY_LEN);
    try
    {
        GCM_CTX<T>* obj = (GCM_CTX<T>*)cctx;
        obj->iv.resize(ivlen);
        std::memcpy(obj->key, key, keylen);
        std::memcpy(obj->iv.data(), iv, ivlen);
        obj->enc    = (enc) ? 1 : 0;
        obj->status = CipherStatus::INITED;
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return 0;
    }
    return 1;
}

template <class T>
static int ECB_encrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return ECB_init<T>(cctx, key, keylen, iv, ivlen, 1, params);
}

template <class T>
static int CBC_encrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return CBC_init<T>(cctx, key, keylen, iv, ivlen, 1, params);
}

template <class T>
static int OFB_encrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return OFB_init<T>(cctx, key, keylen, iv, ivlen, 1, params);
}

template <class T>
static int CFB_encrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return CFB_init<T>(cctx, key, keylen, iv, ivlen, 1, params);
}

template <class T>
static int CTR_encrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return CTR_init<T>(cctx, key, keylen, iv, ivlen, 1, params);
}

template <class T>
static int GCM_encrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return GCM_init<T>(cctx, key, keylen, iv, ivlen, 1, params);
}

// ========================================================
// ========================================================
// ============== CIPHER DECRYPT INIT FUNC DEF ============
// ========================================================
// ========================================================

template <class T>
static int ECB_decrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return ECB_init<T>(cctx, key, keylen, iv, ivlen, 0, params);
}

template <class T>
static int CBC_decrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return CBC_init<T>(cctx, key, keylen, iv, ivlen, 0, params);
}

template <class T>
static int OFB_decrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return OFB_init<T>(cctx, key, keylen, iv, ivlen, 0, params);
}

template <class T>
static int CFB_decrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return CFB_init<T>(cctx, key, keylen, iv, ivlen, 0, params);
}

template <class T>
static int CTR_decrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return CTR_init<T>(cctx, key, keylen, iv, ivlen, 0, params);
}

template <class T>
static int GCM_decrypt_init(void*                cctx,
                            const unsigned char* key,
                            size_t               keylen,
                            const unsigned char* iv,
                            size_t               ivlen,
                            const OSSL_PARAM     params[])
{
    return GCM_init<T>(cctx, key, keylen, iv, ivlen, 0, params);
}

// ========================================================
// ========================================================
// ============== CIPHER UPDATE FUNC DEF ==================
// ========================================================
// ========================================================

template <class CIPHER_CTX>
static int CIPHER_CTX_update(void*                cctx,
                             unsigned char*       out,
                             size_t*              outl,
                             size_t               outsize,
                             const unsigned char* in,
                             size_t               inl)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "update(outsize=%zu, inl=%zu)", outsize,
                                inl);
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    auto* obj = (CIPHER_CTX*)cctx;
    try
    {
        GMLIBPROV_CIPHER_IMPL_ASSERT(obj->status == CipherStatus::RUNNING);
        *outl = outsize;
        if (obj->enc)
        {
            obj->encryptor.update(out, outl, in, inl);
        }
        else
        {
            obj->decryptor.update(out, outl, in, inl);
        }
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return 0;
    }
    return 1;
}

template <class T>
static int ECB_update(void*                cctx,
                      unsigned char*       out,
                      size_t*              outl,
                      size_t               outsize,
                      const unsigned char* in,
                      size_t               inl)
{
    return CIPHER_CTX_update<ECB_CTX<T>>(cctx, out, outl, outsize, in, inl);
}

template <class T>
static int CBC_update(void*                cctx,
                      unsigned char*       out,
                      size_t*              outl,
                      size_t               outsize,
                      const unsigned char* in,
                      size_t               inl)
{
    return CIPHER_CTX_update<CBC_CTX<T>>(cctx, out, outl, outsize, in, inl);
}

template <class T>
static int OFB_update(void*                cctx,
                      unsigned char*       out,
                      size_t*              outl,
                      size_t               outsize,
                      const unsigned char* in,
                      size_t               inl)
{
    return CIPHER_CTX_update<OFB_CTX<T>>(cctx, out, outl, outsize, in, inl);
}

template <class T>
static int CFB_update(void*                cctx,
                      unsigned char*       out,
                      size_t*              outl,
                      size_t               outsize,
                      const unsigned char* in,
                      size_t               inl)
{
    return CIPHER_CTX_update<CFB_CTX<T>>(cctx, out, outl, outsize, in, inl);
}

template <class T>
static int CTR_update(void*                cctx,
                      unsigned char*       out,
                      size_t*              outl,
                      size_t               outsize,
                      const unsigned char* in,
                      size_t               inl)
{
    return CIPHER_CTX_update<CTR_CTX<T>>(cctx, out, outl, outsize, in, inl);
}

template <class T>
static int GCM_update(void*                cctx,
                      unsigned char*       out,
                      size_t*              outl,
                      size_t               outsize,
                      const unsigned char* in,
                      size_t               inl)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "update(outsize=%zu, inl=%zu)", outsize,
                                inl);
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    auto* obj = (GCM_CTX<T>*)cctx;
    try
    {
        GMLIBPROV_CIPHER_IMPL_ASSERT(obj->status == CipherStatus::INITED ||
                                     obj->status == CipherStatus::RUNNING);
        if (obj->status == CipherStatus::INITED)
        {
            if (obj->enc)
            {
                obj->encryptor.init(obj->key, obj->iv.data(), obj->iv.size(),
                                    in, inl);
            }
            else
            {
                obj->decryptor.init(obj->key, obj->iv.data(), obj->iv.size(),
                                    in, inl);
            }
            std::memset(obj->key, 0, T::USER_KEY_LEN);
            obj->status = CipherStatus::RUNNING;
            *outl       = inl;
        }
        else if (obj->status == CipherStatus::RUNNING)
        {
            *outl = outsize;
            if (obj->enc == 1)
            {
                obj->encryptor.update(out, outl, in, inl);
            }
            else
            {
                obj->decryptor.update(out, outl, in, inl);
            }
        }
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return 0;
    }
    return 1;
}

// ========================================================
// ========================================================
// ============== CIPHER FINAL FUNC DEF ===================
// ========================================================
// ========================================================

template <class CIPHER_CTX>
static int CIPHER_CTX_final(void*          cctx,
                            unsigned char* out,
                            size_t*        outl,
                            size_t         outsize)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "finish(outsize=%zu)", outsize);
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    auto* obj = (CIPHER_CTX*)cctx;
    try
    {
        GMLIBPROV_CIPHER_IMPL_ASSERT(obj->status == CipherStatus::RUNNING);
        if (obj->enc == 1)
        {
            obj->encryptor.do_final(out, outl);
        }
        else
        {
            obj->decryptor.do_final(out, outl);
        }
        obj->status = CipherStatus::FINISHED;
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return 0;
    }
    return 1;
}

template <class T>
static int ECB_final(void*          cctx,
                     unsigned char* out,
                     std::size_t*   outl,
                     size_t         outsize)
{
    return CIPHER_CTX_final<ECB_CTX<T>>(cctx, out, outl, outsize);
}

template <class T>
static int CBC_final(void*          cctx,
                     unsigned char* out,
                     std::size_t*   outl,
                     size_t         outsize)
{
    return CIPHER_CTX_final<CBC_CTX<T>>(cctx, out, outl, outsize);
}

template <class T>
static int OFB_final(void*          cctx,
                     unsigned char* out,
                     std::size_t*   outl,
                     size_t         outsize)
{
    return CIPHER_CTX_final<OFB_CTX<T>>(cctx, out, outl, outsize);
}

template <class T>
static int CFB_final(void*          cctx,
                     unsigned char* out,
                     std::size_t*   outl,
                     size_t         outsize)
{
    return CIPHER_CTX_final<CFB_CTX<T>>(cctx, out, outl, outsize);
}

template <class T>
static int CTR_final(void*          cctx,
                     unsigned char* out,
                     std::size_t*   outl,
                     size_t         outsize)
{
    return CIPHER_CTX_final<CTR_CTX<T>>(cctx, out, outl, outsize);
}

template <class T>
static int GCM_final(void*          cctx,
                     unsigned char* out,
                     std::size_t*   outl,
                     size_t         outsize)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "final(outsize=%zu)", outsize);
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    auto* obj = (GCM_CTX<T>*)cctx;
    try
    {
        GMLIBPROV_CIPHER_IMPL_ASSERT(obj->status == CipherStatus::RUNNING);
        if (obj->enc)
        {
            obj->encryptor.do_final(out, outl);
            obj->encryptor.get_tag(obj->tag.data());
        }
        else
        {
            obj->decryptor.set_tag(obj->tag.data());
            obj->decryptor.do_final(out, outl);
        }
        obj->status = CipherStatus::FINISHED;
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return 0;
    }
    return 1;
}

// ========================================================
// ========================================================
// ============== CIPHER FREECTX FUNC DEF =================
// ========================================================
// ========================================================

template <class CIPHER_CTX>
static void CIPHER_CTX_freectx(void* cctx)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "freectx(cctx=%p)", cctx);
    delete (CIPHER_CTX*)(cctx);
}

template <class T>
static void ECB_freectx(void* cctx)
{
    CIPHER_CTX_freectx<ECB_CTX<T>>(cctx);
}

template <class T>
static void CBC_freectx(void* cctx)
{
    CIPHER_CTX_freectx<CBC_CTX<T>>(cctx);
}

template <class T>
static void OFB_freectx(void* cctx)
{
    CIPHER_CTX_freectx<OFB_CTX<T>>(cctx);
}

template <class T>
static void CFB_freectx(void* cctx)
{
    CIPHER_CTX_freectx<CFB_CTX<T>>(cctx);
}

template <class T>
static void CTR_freectx(void* cctx)
{
    CIPHER_CTX_freectx<CTR_CTX<T>>(cctx);
}

template <class T>
static void GCM_freectx(void* cctx)
{
    CIPHER_CTX_freectx<GCM_CTX<T>>(cctx);
}

// ========================================================
// ========================================================
// ============== CIPHER DUPCTX FUNC DEF ==================
// ========================================================
// ========================================================

template <class CIPHER_CTX>
static void* CIPHER_CTX_dupctx(void* cctx)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "dupctx");
    GMLIBPROV_CIPHER_IMPL_ASSERT(cctx != NULL);
    try
    {
        return new CIPHER_CTX(*(CIPHER_CTX*)cctx);
    }
    catch (std::exception& e)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stderr, "catch exception: %s", e.what());
        return NULL;
    }
}

template <class T>
static void* ECB_dupctx(void* cctx)
{
    return CIPHER_CTX_dupctx<ECB_CTX<T>>(cctx);
}

template <class T>
static void* CBC_dupctx(void* cctx)
{
    return CIPHER_CTX_dupctx<CBC_CTX<T>>(cctx);
}

template <class T>
static void* CTR_dupctx(void* cctx)
{
    return CIPHER_CTX_dupctx<CTR_CTX<T>>(cctx);
}

template <class T>
static void* CFB_dupctx(void* cctx)
{
    return CIPHER_CTX_dupctx<CFB_CTX<T>>(cctx);
}

template <class T>
static void* OFB_dupctx(void* cctx)
{
    return CIPHER_CTX_dupctx<OFB_CTX<T>>(cctx);
}

template <class T>
static void* GCM_dupctx(void* cctx)
{
    return CIPHER_CTX_dupctx<GCM_CTX<T>>(cctx);
}

// ========================================================
// ========================================================
// ============== CIPHER GET PARAMS FUNC DEF ==============
// ========================================================
// ========================================================

static int default_get_params(OSSL_PARAM  params[],
                              int         mode,
                              std::size_t keylen,
                              std::size_t ivlen,
                              std::size_t block_size,
                              int         aead)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get_params");
    OSSL_PARAM* p = NULL;
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_MODE)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get OSSL_CIPHER_PARAM_MODE");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_uint(p, mode));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_KEYLEN)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get OSSL_CIPHER_PARAM_KEYLEN");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, keylen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_IVLEN)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get OSSL_CIPHER_PARAM_IVLEN");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, ivlen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_BLOCK_SIZE)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get OSSL_CIPHER_PARAM_BLOCK_SIZE");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, block_size));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_AEAD)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get OSSL_CIPHER_PARAM_AEAD");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_int(p, aead));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_CUSTOM_IV)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get OSSL_CIPHER_PARAM_CUSTOM_IV");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_int(p, 0));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_CTS)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get OSSL_CIPHER_PARAM_CTS");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_int(p, 0));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK)) !=
        NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout,
                                    "get OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_int(p, 0));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_HAS_RAND_KEY)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout,
                                    "get OSSL_CIPHER_PARAM_HAS_RAND_KEY");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_int(p, 0));
    }
    return 1;
}

template <class T>
static int ECB_get_params(OSSL_PARAM params[])
{
    return default_get_params(params, EVP_CIPH_ECB_MODE, T::USER_KEY_LEN, 0,
                              T::BLOCK_SIZE, 0);
}

template <class T>
static int CBC_get_params(OSSL_PARAM params[])
{
    return default_get_params(params, EVP_CIPH_CBC_MODE, T::USER_KEY_LEN,
                              T::BLOCK_SIZE, T::BLOCK_SIZE, 0);
}

template <class T>
static int CFB_get_params(OSSL_PARAM params[])
{
    return default_get_params(params, EVP_CIPH_CFB_MODE, T::USER_KEY_LEN,
                              T::BLOCK_SIZE, T::BLOCK_SIZE, 0);
}

template <class T>
static int OFB_get_params(OSSL_PARAM params[])
{
    return default_get_params(params, EVP_CIPH_OFB_MODE, T::USER_KEY_LEN,
                              T::BLOCK_SIZE, T::BLOCK_SIZE, 0);
}

template <class T>
static int CTR_get_params(OSSL_PARAM params[])
{
    return default_get_params(params, EVP_CIPH_CTR_MODE, T::USER_KEY_LEN,
                              T::BLOCK_SIZE, T::BLOCK_SIZE, 0);
}

template <class T>
static int GCM_get_params(OSSL_PARAM params[])
{
    return default_get_params(params, EVP_CIPH_GCM_MODE, T::USER_KEY_LEN, 12,
                              T::BLOCK_SIZE, 1);
}

// ========================================================
// ========================================================
// ============== CIPHER GET CTX PARAMS FUNC DEF ==========
// ========================================================
// ========================================================

static int default_get_ctx_params(void*       cctx,
                                  OSSL_PARAM  params[],
                                  std::size_t keylen,
                                  std::size_t ivlen,
                                  void*       iv_ptr)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get_ctx_params");
    OSSL_PARAM* p = NULL;
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_KEYLEN)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get ctx OSSL_CIPHER_PARAM_KEYLEN");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, keylen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_IVLEN)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get ctx OSSL_CIPHER_PARAM_IVLEN");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, ivlen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_PADDING)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout,
                                    "get ctx OSSL_CIPHER_PARAM_PADDING");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_uint(p, 0));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_IV)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get ctx OSSL_CIPHER_PARAM_IV");
        GMLIBPROV_CIPHER_IMPL_ASSERT(
            OSSL_PARAM_set_octet_string(p, iv_ptr, ivlen));
    }
    return 1;
}

static int aead_get_ctx_params(void*       cctx,
                               OSSL_PARAM  params[],
                               std::size_t keylen,
                               std::size_t ivlen,
                               void*       iv_ptr,
                               std::size_t taglen,
                               void*       tag_ptr)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get_ctx_params");
    OSSL_PARAM* p = NULL;
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_KEYLEN)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get ctx OSSL_CIPHER_PARAM_KEYLEN");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, keylen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_AEAD_IVLEN)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout,
                                    "get ctx OSSL_CIPHER_PARAM_AEAD_IVLEN");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, ivlen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_AEAD_TAGLEN)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout,
                                    "get ctx OSSL_CIPHER_PARAM_AEAD_TAGLEN");
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_set_size_t(p, ivlen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_IV)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "get ctx OSSL_CIPHER_PARAM_IV");
        GMLIBPROV_CIPHER_IMPL_ASSERT(
            OSSL_PARAM_set_octet_string(p, iv_ptr, ivlen));
    }
    if ((p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_AEAD_TAG)) != NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout,
                                    "get ctx OSSL_CIPHER_PARAM_AEAD_TAG");
        GMLIBPROV_CIPHER_IMPL_ASSERT(
            OSSL_PARAM_set_octet_string(p, tag_ptr, taglen));
    }
    return 1;
}

template <class CIPHER_CTX>
static int CIPHER_CTX_get_ctx_params(void* cctx, OSSL_PARAM params[])
{
    return default_get_ctx_params(cctx, params, CIPHER_CTX::T::USER_KEY_LEN,
                                  CIPHER_CTX::T::BLOCK_SIZE,
                                  ((CIPHER_CTX*)cctx)->iv);
}

template <class T>
static int ECB_get_ctx_params(void* cctx, OSSL_PARAM params[])
{
    return default_get_ctx_params(cctx, params, T::USER_KEY_LEN, 0, NULL);
}

template <class T>
static int CBC_get_ctx_params(void* cctx, OSSL_PARAM params[])
{
    return CIPHER_CTX_get_ctx_params<CBC_CTX<T>>(cctx, params);
}

template <class T>
static int CFB_get_ctx_params(void* cctx, OSSL_PARAM params[])
{
    return CIPHER_CTX_get_ctx_params<CFB_CTX<T>>(cctx, params);
}

template <class T>
static int OFB_get_ctx_params(void* cctx, OSSL_PARAM params[])
{
    return CIPHER_CTX_get_ctx_params<OFB_CTX<T>>(cctx, params);
}

template <class T>
static int CTR_get_ctx_params(void* cctx, OSSL_PARAM params[])
{
    return CIPHER_CTX_get_ctx_params<CTR_CTX<T>>(cctx, params);
}

template <class T>
static int GCM_get_ctx_params(void* cctx, OSSL_PARAM params[])
{
    return aead_get_ctx_params(
        cctx, params, T::USER_KEY_LEN, ((GCM_CTX<T>*)cctx)->iv.size(),
        ((GCM_CTX<T>*)cctx)->iv.data(), ((GCM_CTX<T>*)cctx)->tag.size(),
        ((GCM_CTX<T>*)cctx)->tag.data());
}

// ========================================================
// ========================================================
// ============== CIPHER SET CTX PARAMS FUNC DEF ==========
// ========================================================
// ========================================================

template <class CIPHER_CTX>
static int CIPHER_CTX_set_ctx_params(void* cctx, const OSSL_PARAM params[])
{
    return 1;
}

template <class T>
static int ECB_set_ctx_params(void* cctx, const OSSL_PARAM params[])
{
    return 1;
}

template <class T>
static int CBC_set_ctx_params(void* cctx, const OSSL_PARAM params[])
{
    return 1;
}

template <class T>
static int OFB_set_ctx_params(void* cctx, const OSSL_PARAM params[])
{
    return 1;
}

template <class T>
static int CFB_set_ctx_params(void* cctx, const OSSL_PARAM params[])
{
    return 1;
}

template <class T>
static int CTR_set_ctx_params(void* cctx, const OSSL_PARAM params[])
{
    return 1;
}

template <class T>
static int GCM_set_ctx_params(void* cctx, const OSSL_PARAM params[])
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "set_ctx_params");
    auto&             tag = ((GCM_CTX<T>*)cctx)->tag;
    auto&             iv  = ((GCM_CTX<T>*)cctx)->iv;
    const OSSL_PARAM* p   = NULL;
    if ((p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_TAG)) !=
        NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "set OSSL_CIPHER_PARAM_AEAD_TAG");
        auto* val = tag.data();
        GMLIBPROV_CIPHER_IMPL_ASSERT(
            OSSL_PARAM_get_octet_string(p, (void**)&val, tag.size(), NULL));
    }
    if ((p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_AEAD_IVLEN)) !=
        NULL)
    {
        GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "set OSSL_CIPHER_PARAM_AEAD_IVLEN");
        std::size_t val;
        GMLIBPROV_CIPHER_IMPL_ASSERT(OSSL_PARAM_get_size_t(p, &val));
        iv.resize(val);
    }
    return 1;
}

// ========================================================
// ========================================================
// ============== CIPHER GETTABLE PARAMS IMPL =============
// ========================================================
// ========================================================

static const OSSL_PARAM* default_gettable_params(void* provctx)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "gettable_params");
    static const OSSL_PARAM params[] = {
        OSSL_PARAM_uint(OSSL_CIPHER_PARAM_MODE, NULL),
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_KEYLEN, NULL),
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_IVLEN, NULL),
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_BLOCK_SIZE, NULL),
        OSSL_PARAM_int(OSSL_CIPHER_PARAM_AEAD, NULL),
        OSSL_PARAM_int(OSSL_CIPHER_PARAM_CUSTOM_IV, NULL),
        OSSL_PARAM_int(OSSL_CIPHER_PARAM_CTS, NULL),
        OSSL_PARAM_int(OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK, NULL),
        OSSL_PARAM_int(OSSL_CIPHER_PARAM_HAS_RAND_KEY, NULL),
        OSSL_PARAM_END,
    };
    return params;
}

template <class T>
static const OSSL_PARAM* ECB_gettable_params(void* provctx)
{
    return default_gettable_params(provctx);
}

template <class T>
static const OSSL_PARAM* CBC_gettable_params(void* provctx)
{
    return default_gettable_params(provctx);
}

template <class T>
static const OSSL_PARAM* OFB_gettable_params(void* provctx)
{
    return default_gettable_params(provctx);
}

template <class T>
static const OSSL_PARAM* CFB_gettable_params(void* provctx)
{
    return default_gettable_params(provctx);
}

template <class T>
static const OSSL_PARAM* CTR_gettable_params(void* provctx)
{
    return default_gettable_params(provctx);
}

template <class T>
static const OSSL_PARAM* GCM_gettable_params(void* provctx)
{
    return default_gettable_params(provctx);
}

// ========================================================
// ========================================================
// ============== CIPHER GETTABLE CTX PARAMS IMPL =========
// ========================================================
// ========================================================

static const OSSL_PARAM* default_gettable_ctx_params(void* cctx, void* provctx)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "gettable_ctx_params");
    static const OSSL_PARAM params[] = {
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_KEYLEN, NULL),
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_IVLEN, NULL),
        OSSL_PARAM_uint(OSSL_CIPHER_PARAM_PADDING, NULL),
        // OSSL_PARAM_uint(OSSL_CIPHER_PARAM_NUM, NULL),
        OSSL_PARAM_octet_string(OSSL_CIPHER_PARAM_IV, NULL, 0),
        // OSSL_PARAM_octet_string(OSSL_CIPHER_PARAM_UPDATED_IV, NULL, 0),
        OSSL_PARAM_END,
    };
    return params;
}

static const OSSL_PARAM* aead_gettable_ctx_params(void* cctx, void* provctx)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "gettable_ctx_params");
    static const OSSL_PARAM params[] = {
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_KEYLEN, NULL),
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_IVLEN, NULL),
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_AEAD_TAGLEN, NULL),
        OSSL_PARAM_octet_string(OSSL_CIPHER_PARAM_IV, NULL, 0),
        // OSSL_PARAM_octet_string(OSSL_CIPHER_PARAM_UPDATED_IV, NULL, 0),
        OSSL_PARAM_octet_string(OSSL_CIPHER_PARAM_AEAD_TAG, NULL, 0),
        // OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_AEAD_TLS1_AAD_PAD, NULL),
        // OSSL_PARAM_octet_string(OSSL_CIPHER_PARAM_AEAD_TLS1_GET_IV_GEN, NULL,
        //                         0),
        OSSL_PARAM_END,
    };
    return params;
}

template <class T>
static const OSSL_PARAM* ECB_gettable_ctx_params(void* cctx, void* provctx)
{
    return default_gettable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* CBC_gettable_ctx_params(void* cctx, void* provctx)
{
    return default_gettable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* OFB_gettable_ctx_params(void* cctx, void* provctx)
{
    return default_gettable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* CFB_gettable_ctx_params(void* cctx, void* provctx)
{
    return default_gettable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* CTR_gettable_ctx_params(void* cctx, void* provctx)
{
    return default_gettable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* GCM_gettable_ctx_params(void* cctx, void* provctx)
{
    return aead_gettable_ctx_params(cctx, provctx);
}

// ========================================================
// ========================================================
// ============== CIPHER SETTABLE IMPL ====================
// ========================================================
// ========================================================

static const OSSL_PARAM* default_settable_ctx_params(void* cctx, void* provctx)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "settable_ctx_params");
    static OSSL_PARAM params[] = {OSSL_PARAM_END};
    return params;
}

static const OSSL_PARAM* aead_settable_ctx_params(void* cctx, void* provctx)
{
    GMLIBPROV_CIPHER_IMPL_PRINT(stdout, "settable_ctx_params");
    static OSSL_PARAM params[] = {
        OSSL_PARAM_octet_string(OSSL_CIPHER_PARAM_AEAD_TAG, NULL, 0),
        OSSL_PARAM_size_t(OSSL_CIPHER_PARAM_AEAD_IVLEN, 0),
        OSSL_PARAM_END,
    };
    return params;
}

template <class T>
static const OSSL_PARAM* ECB_settable_ctx_params(void* cctx, void* provctx)
{
    return default_settable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* CBC_settable_ctx_params(void* cctx, void* provctx)
{
    return default_settable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* OFB_settable_ctx_params(void* cctx, void* provctx)
{
    return default_settable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* CFB_settable_ctx_params(void* cctx, void* provctx)
{
    return default_settable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* CTR_settable_ctx_params(void* cctx, void* provctx)
{
    return default_settable_ctx_params(cctx, provctx);
}

template <class T>
static const OSSL_PARAM* GCM_settable_ctx_params(void* cctx, void* provctx)
{
    return aead_settable_ctx_params(cctx, provctx);
}

// ========================================================
// ========================================================
// ============== CIPHER IMPLE DEFINE =====================
// ========================================================
// ========================================================

#define GMLIBPROV_CIPHER_IMPL_DEF_DISPACH(T, NAME, MODE, VARIABLE_NAME)      \
    const OSSL_DISPATCH VARIABLE_NAME[] = {                                  \
        {OSSL_FUNC_CIPHER_NEWCTX, (void (*)(void))MODE##_newctx<T>},         \
        {OSSL_FUNC_CIPHER_ENCRYPT_INIT,                                      \
         (void (*)(void))MODE##_encrypt_init<T>},                            \
        {OSSL_FUNC_CIPHER_DECRYPT_INIT,                                      \
         (void (*)(void))MODE##_decrypt_init<T>},                            \
        {OSSL_FUNC_CIPHER_UPDATE, (void (*)(void))MODE##_update<T>},         \
        {OSSL_FUNC_CIPHER_FINAL, (void (*)(void))MODE##_final<T>},           \
        {OSSL_FUNC_CIPHER_FREECTX, (void (*)(void))MODE##_freectx<T>},       \
        {OSSL_FUNC_CIPHER_DUPCTX, (void (*)(void))MODE##_dupctx<T>},         \
        {OSSL_FUNC_CIPHER_GET_PARAMS, (void (*)(void))MODE##_get_params<T>}, \
        {OSSL_FUNC_CIPHER_GET_CTX_PARAMS,                                    \
         (void (*)(void))MODE##_get_ctx_params<T>},                          \
        {OSSL_FUNC_CIPHER_SET_CTX_PARAMS,                                    \
         (void (*)(void))MODE##_set_ctx_params<T>},                          \
        {OSSL_FUNC_CIPHER_GETTABLE_PARAMS,                                   \
         (void (*)(void))MODE##_gettable_params<T>},                         \
        {OSSL_FUNC_CIPHER_GETTABLE_CTX_PARAMS,                               \
         (void (*)(void))MODE##_gettable_ctx_params<T>},                     \
        {OSSL_FUNC_CIPHER_SETTABLE_CTX_PARAMS,                               \
         (void (*)(void))MODE##_settable_ctx_params<T>},                     \
        OSSL_DISPATCH_END,                                                   \
    }

} // namespace gmlibprov

#endif