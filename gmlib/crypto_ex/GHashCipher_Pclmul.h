/*
The MIT License (MIT)

Copyright (c) 2023 oldprincess, https://github.com/oldprincess/gmlib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _GMLIB_CRYPTO_EX_GHASH_CIPHER_PCLMUL_H
#define _GMLIB_CRYPTO_EX_GHASH_CIPHER_PCLMUL_H

#include <stdint.h>
#include <stddef.h>

namespace gmlib {

class GHashCipher_Pclmul
{
public:
    struct GHashPclmulCTX
    {
        uint8_t  H[16]; // LUT TABLE
        uint64_t state[2];

        uint8_t buf[16];
        size_t  buf_size;
    };

public:
    static constexpr size_t DIGEST_SIZE = 16;

private:
    struct GHashPclmulCTX ctx;

public:
    GHashCipher_Pclmul(const uint8_t H[16]) noexcept;
    GHashCipher_Pclmul()                               = default;
    GHashCipher_Pclmul(const GHashCipher_Pclmul& other) = default;
    ~GHashCipher_Pclmul()                              = default;

public:
    void set_key(const uint8_t H[16]) noexcept;

    void reset() noexcept;

    void update(const uint8_t* in, size_t inl) noexcept;

    void final(uint8_t digest[16]);
};

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_EX_GHASH_CIPHER_PCLMUL_H
