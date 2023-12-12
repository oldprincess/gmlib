#ifndef _GMLIB_CRYPTO_RNG_OS_WINCRYPT_RNG_H
#define _GMLIB_CRYPTO_RNG_OS_WINCRYPT_RNG_H

#include <gmlib/crypto/rng/RngCipher.h>
#include <gmlib/exception.h>
#include <Windows.h>
#include <wincrypt.h>

namespace gmlib {

namespace wincrypt_rng {

class WinRngCipher : public RngCipher
{
private:
    HCRYPTPROV hCryptProv;

public:
    WinRngCipher()
    {
        BOOL ret;
        ret =
            CryptAcquireContext(&(this->hCryptProv), NULL, NULL, PROV_RSA_FULL,
                                CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
        if (ret == FALSE)
        {
            throw gmlib::Exception("Err in call CryptAcquireContext");
        }
    }

    WinRngCipher(const WinRngCipher& other) = delete;

    ~WinRngCipher()
    {
        BOOL ret;
        ret = CryptReleaseContext(this->hCryptProv, 0);
        if (ret == FALSE)
        {
            fprintf(stderr, "Err in call CryptReleaseContext");
            std::terminate();
        }
    }

public:
    const char* name() noexcept
    {
        return "WinRngCipher(CryptGenRandom)";
    }

public:
    void gen(uint8_t* out, size_t len)
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
        BOOL ret;
        while (len >= MAXDWORD)
        {
            ret = CryptGenRandom(this->hCryptProv, MAXDWORD, out);
            if (ret == FALSE)
            {
                throw gmlib::Exception("Err in call CryptGenRandom");
            }
            out += MAXDWORD, len -= MAXDWORD;
        }
        if (len)
        {
            ret = CryptGenRandom(this->hCryptProv, (DWORD)len, out);
            if (ret == FALSE)
            {
                throw gmlib::Exception("Err in call CryptGenRandom");
            }
        }
    }
};

} // namespace wincrypt_rng

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_RNG_WIN_WINCRYPT_RNG_H
