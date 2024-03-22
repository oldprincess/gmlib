#ifndef RNG_OS_RNG_BCRYPT_RNG_H
#define RNG_OS_RNG_BCRYPT_RNG_H

#include <Windows.h>
#include <bcrypt.h>
#include <gmlib/rng/rng.h>

#include <stdexcept>

// -lbcrypt
#pragma comment(lib, "Bcrypt.lib")

namespace rng::os_rng {

class BcryptRng : public Rng
{
public:
    const char* name() const noexcept override
    {
        return "WinRng(BCryptGenRandom)";
    }

public:
    void gen(void* out, std::size_t len) override
    {
        // Microsoft BCryptGenRandom function (bcrypt.h)
        //  NTSTATUS BCryptGenRandom(
        //      [in, out] BCRYPT_ALG_HANDLE hAlgorithm,
        //      [in, out] PUCHAR            pbBuffer,
        //      [in] ULONG                  cbBuffer,
        //      [in] ULONG                  dwFlags
        //  );

        NTSTATUS      ret;
        std::uint8_t* out_u8 = (std::uint8_t*)out;
        while (len >= ULONG_MAX)
        {
            ret = BCryptGenRandom(NULL, out_u8, ULONG_MAX,
                                  BCRYPT_USE_SYSTEM_PREFERRED_RNG);
            if (ret < 0)
            {
                throw std::runtime_error("Err in call BCryptGenRandom");
            }
            out_u8 += ULONG_MAX, len -= ULONG_MAX;
        }
        if (len)
        {
            ret = BCryptGenRandom(NULL, out_u8, (ULONG)len,
                                  BCRYPT_USE_SYSTEM_PREFERRED_RNG);
            if (ret < 0)
            {
                throw std::runtime_error("Err in call BCryptGenRandom");
            }
        }
    }
};

}; // namespace rng::os_rng

#endif // !RNG_OS_RNG_BCRYPT_RNG_H
