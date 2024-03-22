#ifndef RNG_OS_RNGWINCRYPT_RNG_H
#define RNG_OS_RNGWINCRYPT_RNG_H

#include <Windows.h>
#include <gmlib/rng/rng.h>
#include <wincrypt.h>

#include <cstdio>
#include <stdexcept>

namespace rng::os_rng {

// This API is deprecated. New and existing software should start using
// Cryptography Next Generation APIs. Microsoft may remove this API in future
// releases.
class WincryptRng : public Rng
{
private:
    HCRYPTPROV hCryptProv_;

public:
    WincryptRng()
    {
        // BOOL CryptAcquireContextA(
        //   [out] HCRYPTPROV *phProv,
        //   [in]  LPCSTR     szContainer,
        //   [in]  LPCSTR     szProvider,
        //   [in]  DWORD      dwProvType,
        //   [in]  DWORD      dwFlags
        // );
        BOOL ret;
        ret = CryptAcquireContext(&hCryptProv_, NULL, NULL, PROV_RSA_FULL,
                                  CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
        if (ret == FALSE)
        {
            throw std::runtime_error("Err in call CryptAcquireContext");
        }
    }

    WincryptRng(const WincryptRng& other) = delete;

    ~WincryptRng() override
    {
        BOOL ret;
        ret = CryptReleaseContext(hCryptProv_, 0);
        if (ret == FALSE)
        {
            std::fprintf(stderr, "Err in call CryptReleaseContext");
            std::terminate();
        }
    }

public:
    const char* name() const noexcept override
    {
        return "WincryptCipher(CryptGenRandom)";
    }

public:
    void gen(void* out, std::size_t len) override
    {
        // Microsoft CryptGenRandom function (wincrypt.h)
        //
        //  BOOL CryptGenRandom(
        //      [in]      HCRYPTPROV hProv,
        //      [in]      DWORD      dwLen,
        //      [in, out] BYTE       *pbBuffer
        //  );
        //  [in] hProv
        //      Handle of a cryptographic service provider(CSP) created by a
        //      call to CryptAcquireContext.
        //  [in] dwLen
        //      Number of bytes of random data to be generated.
        //  [in, out] pbBuffer
        //      Buffer to receive the returned data. This buffer must be at
        //      least dwLen bytes in length.
        BOOL          ret;
        std::uint8_t* out_u8 = (std::uint8_t*)out;
        while (len >= MAXDWORD)
        {
            ret = CryptGenRandom(hCryptProv_, MAXDWORD, out_u8);
            if (ret == FALSE)
            {
                throw std::runtime_error("Err in call CryptGenRandom");
            }
            out_u8 += MAXDWORD, len -= MAXDWORD;
        }
        if (len)
        {
            ret = CryptGenRandom(hCryptProv_, (DWORD)len, out_u8);
            if (ret == FALSE)
            {
                throw std::runtime_error("Err in call CryptGenRandom");
            }
        }
    }
};

} // namespace rng::os_rng

#endif // !RNG_OS_RNGWINCRYPT_RNG_H
