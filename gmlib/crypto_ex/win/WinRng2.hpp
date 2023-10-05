#ifndef _GMLIB_CRYPTO_EX_WIN_RNG2_HPP
#define _GMLIB_CRYPTO_EX_WIN_RNG2_HPP

#include <gmlib/crypto/rng/RngCipher.h>
#include <stdexcept>
#include <Windows.h>
#include <bcrypt.h>

#pragma comment(lib, "Bcrypt.lib")

namespace gmlib {

class WinRng2 : public RngCipher
{
public:
    WinRng2()                     = default;
    WinRng2(const WinRng2& other) = default;
    ~WinRng2()                    = default;

public:
    const char* name() noexcept
    {
        return "WinRng2(BCryptGenRandom)";
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
            ret = BCryptGenRandom(NULL,
                                  out,
                                  ULONG_MAX,
                                  BCRYPT_USE_SYSTEM_PREFERRED_RNG);
            if (ret < 0)
            {
                throw std::runtime_error("Err in call BCryptGenRandom");
            }
            out += ULONG_MAX, len -= ULONG_MAX;
        }
        if (len)
        {
            ret = BCryptGenRandom(NULL,
                                  out,
                                  ULONG(len),
                                  BCRYPT_USE_SYSTEM_PREFERRED_RNG);
            if (ret < 0)
            {
                throw std::runtime_error("Err in call BCryptGenRandom");
            }
        }
    }
};

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_EX_WIN_RNG2_HPP
