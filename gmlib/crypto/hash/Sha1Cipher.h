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
#ifndef _GMLIB_CRYPTO_HASH_SHA1_CIPHER_H
#define _GMLIB_CRYPTO_HASH_SHA1_CIPHER_H

#include <TinyCrypto/hash/sha1/sha1_standard.h>
#include <gmlib/exception.h>

namespace gmlib {

class Sha1Cipher
{
public:
    static constexpr size_t BLOCK_SIZE  = SHA1_BLOCK_SIZE;
    static constexpr size_t DIGEST_SIZE = SHA1_DIGEST_SIZE;

private:
    tc::Sha1StandardCTX ctx;

public:
    Sha1Cipher() noexcept
    {
        tc::sha1_standard_init(&this->ctx);
    }

    Sha1Cipher(const Sha1Cipher& other) = default;
    ~Sha1Cipher()                       = default;

public:
    void reset() noexcept
    {
        tc::sha1_standard_reset(&this->ctx);
    }

    void update(const uint8_t* in, size_t inl) noexcept
    {
        if (tc::sha1_standard_update(&this->ctx, in, inl))
        {
            throw gmlib::Exception("sha1 input bits overflow");
        }
    }

    void final(uint8_t digest[32]) noexcept
    {
        tc::sha1_standard_final(&this->ctx, digest);
    }
};

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_HASH_sha1_CIPHER_H
