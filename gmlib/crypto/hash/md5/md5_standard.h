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
#ifndef _GMLIB_CRYPTO_HASH_MD5_STANDARD_H
#define _GMLIB_CRYPTO_HASH_MD5_STANDARD_H

#include <TinyCrypto/hash/md5/md5_standard.h>

namespace gmlib {

namespace md5_standard {

class Md5Cipher
{
public:
    static constexpr size_t BLOCK_SIZE  = MD5_BLOCK_SIZE;
    static constexpr size_t DIGEST_SIZE = MD5_DIGEST_SIZE;

private:
    tc::Md5StandardCTX ctx;

public:
    Md5Cipher() noexcept
    {
        tc::md5_standard_init(&this->ctx);
    }

public:
    void reset() noexcept
    {
        tc::md5_standard_reset(&this->ctx);
    }

    void update(const uint8_t* in, size_t inl) noexcept
    {
        tc::md5_standard_update(&this->ctx, in, inl);
    }

    void final(uint8_t digest[16]) noexcept
    {
        tc::md5_standard_final(&this->ctx, digest);
    }

public:
    static void compute(uint8_t        digest[16],
                        const uint8_t* msg,
                        size_t         msg_len) noexcept
    {
        Md5Cipher h;
        h.update(msg, msg_len);
        h.final(digest);
    }
};

} // namespace md5_standard

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_HASH_MD5_STANDARD_H
