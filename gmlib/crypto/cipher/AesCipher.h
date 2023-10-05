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

#include <stdint.h>
#include <stddef.h>

namespace gmlib {

class Aes128Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = 16;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = 16;

private:
    uint32_t round_key[44];
    int      mode;

public:
    Aes128Cipher(const uint8_t* user_key, int mode) noexcept;
    Aes128Cipher()                          = default;
    Aes128Cipher(const Aes128Cipher& other) = default;
    ~Aes128Cipher()                         = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept;
    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept;
    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept;
    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept;
};

class Aes192Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = 16;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = 24;

private:
    uint32_t round_key[52];
    int      mode;

public:
    Aes192Cipher(const uint8_t* user_key, int mode) noexcept;
    Aes192Cipher()                          = default;
    Aes192Cipher(const Aes192Cipher& other) = default;
    ~Aes192Cipher()                         = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept;
    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept;
    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept;
    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept;
};

class Aes256Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = 16;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = 32;

private:
    uint32_t round_key[60];
    int      mode;

public:
    Aes256Cipher(const uint8_t* user_key, int mode) noexcept;
    Aes256Cipher()                          = default;
    Aes256Cipher(const Aes256Cipher& other) = default;
    ~Aes256Cipher()                         = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept;
    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept;
    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept;
    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept;
};

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_CIPHER_AES_CIPHER_H
