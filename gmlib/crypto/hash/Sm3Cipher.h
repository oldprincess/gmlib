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

#ifndef _GMLIB_CRYPTO_HASH_SM3_CIPHER_H
#define _GMLIB_CRYPTO_HASH_SM3_CIPHER_H

#include <stdint.h>
#include <stddef.h>

namespace gmlib {

class Sm3Cipher
{
public:
    static constexpr size_t BLOCK_SIZE  = 64;
    static constexpr size_t DIGEST_SIZE = 32;

public:
    struct Sm3CTX
    {
        uint32_t state[8];
        uint64_t data_bits; // input bits < 2^64

        uint8_t buf[64];
        size_t  buf_size;
    };

private:
    struct Sm3CTX ctx;

public:
    Sm3Cipher() noexcept;
    Sm3Cipher(const Sm3Cipher& other) = default;
    ~Sm3Cipher()                      = default;

public:
    const char* name() noexcept
    {
        return "Sm3Cipher";
    }

public:
    void reset() noexcept;

    void update(const uint8_t* in, size_t inl);

    void final(uint8_t digest[32]) noexcept;
};

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_HASH_SM3_CIPHER_H
