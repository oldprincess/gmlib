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

#ifndef _GMLIB_CRYPTO_RNG_CIPHER_H
#define _GMLIB_CRYPTO_RNG_CIPHER_H

#include <stdint.h>
#include <stddef.h>
#include <type_traits>

namespace gmlib {

class RngCipher
{
public:
    RngCipher()                       = default;
    RngCipher(const RngCipher& other) = default;
    virtual ~RngCipher()              = default;

public:
    virtual const char* name() = 0;

public:
    virtual void gen(uint8_t* out, size_t len) = 0;

    template <typename T>
    T rand()
    {
        static_assert(std::is_pod<T>::value, "only support POD type");
        T r;
        this->gen((uint8_t*)(&r), sizeof(T));
        return r;
    }
};
} // namespace gmlib

#endif // !_GMLIB_CRYPTO_RNG_CIPHER_H
