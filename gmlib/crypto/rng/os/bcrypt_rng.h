#ifndef _GMLIB_CRYPTO_RNG_OS_BCRYPT_RNG_H
#define _GMLIB_CRYPTO_RNG_OS_BCRYPT_RNG_H

#include <gmlib/crypto/rng/RngCipher.h>
#include <gmlib/exception.h>
#include <Windows.h>
#include <bcrypt.h>

#pragma comment(lib, "Bcrypt.lib")

namespace gmlib {

namespace bcrypt_rng {

class WinRngCipher : public RngCipher
{
public:
    const char* name() noexcept
    {
        return "WinRngCipher(BCryptGenRandom)";
    }

public:
    void gen(uint8_t* out, size_t len)
    {
        // Microsoft BCryptGenRandom function (bcrypt.h)
        //  NTSTATUS BCryptGenRandom(
        //      [in, out] BCRYPT_ALG_HANDLE hAlgorithm,
        //      [in, out] PUCHAR            pbBuffer,
        //      [in] ULONG                  cbBuffer,
        //      [in] ULONG                  dwFlags
        //  );

        NTSTATUS ret;
        while (len >= ULONG_MAX)
        {
            ret = BCryptGenRandom(NULL, out, ULONG_MAX,
                                  BCRYPT_USE_SYSTEM_PREFERRED_RNG);
            if (ret < 0)
            {
                throw gmlib::Exception("Err in call BCryptGenRandom");
            }
            out += ULONG_MAX, len -= ULONG_MAX;
        }
        if (len)
        {
            ret = BCryptGenRandom(NULL, out, (ULONG)len,
                                  BCRYPT_USE_SYSTEM_PREFERRED_RNG);
            if (ret < 0)
            {
                throw gmlib::Exception("Err in call BCryptGenRandom");
            }
        }
    }
};

} // namespace bcrypt_rng

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_RNG_WIN_BCRYPT_RNG2_H
