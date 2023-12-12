#ifndef _GMLIB_CRYPTO_RNG_OS_RNG_CIPHER_H
#define _GMLIB_CRYPTO_RNG_OS_RNG_CIPHER_H

#include <gmlib/crypto/rng/os/bcrypt_rng.h>
#include <gmlib/crypto/rng/os/wincrypt_rng.h>

namespace gmlib {

using OsRngCipher = bcrypt_rng::WinRngCipher;

// using OsRngCipher = wincrypt_rng::WinRngCipher;

} // namespace gmlib

#endif