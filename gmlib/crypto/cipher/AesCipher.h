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

#ifndef _GMLIB_CRYPTO_CIPHER_AES_CIPHER_H
#define _GMLIB_CRYPTO_CIPHER_AES_CIPHER_H

#include <gmlib/crypto/cipher/aes/aes_aesni.h>
#include <gmlib/crypto/cipher/aes/aes_lut.h>

namespace gmlib {

using Aes128Cipher = aes_aesni::Aes128Cipher;
using Aes192Cipher = aes_aesni::Aes192Cipher;
using Aes256Cipher = aes_aesni::Aes256Cipher;

// using Aes128Cipher = aes_lut::Aes128Cipher;
// using Aes192Cipher = aes_lut::Aes192Cipher;
// using Aes256Cipher = aes_lut::Aes256Cipher;

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_CIPHER_AES_CIPHER_H
