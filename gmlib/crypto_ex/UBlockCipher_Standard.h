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

/**
 * WU W L, ZHANG L, ZHENG Y F, LI L C. The block cipher uBlock[J]. Journal of
 * Cryptologic Research, 2019, 6(6): 690–703.
 *
 * https://sfjs.cacrnet.org.cn/site/term/list_73_1.html
 */
#ifndef _GMLIB_CRYPTO_EX_UBLOCK_CIPHER_STANDARD_H
#define _GMLIB_CRYPTO_EX_UBLOCK_CIPHER_STANDARD_H

#include <stdint.h>
#include <stddef.h>

namespace gmlib {

class UBlock128128Cipher_Standard
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = 16;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = 16;

private:
    uint8_t sub_key[17][32];
    int     mode;

public:
    UBlock128128Cipher_Standard(const uint8_t* user_key, int mode) noexcept;
    UBlock128128Cipher_Standard()                                   = default;
    UBlock128128Cipher_Standard(const UBlock128128Cipher_Standard&) = default;
    ~UBlock128128Cipher_Standard()                                  = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept;
    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept;
    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept;
    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept;
};

class UBlock128256Cipher_Standard
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = 16;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = 32;

private:
    uint8_t sub_key[25][32];
    int     mode;

public:
    UBlock128256Cipher_Standard(const uint8_t* user_key, int mode) noexcept;
    UBlock128256Cipher_Standard()                                   = default;
    UBlock128256Cipher_Standard(const UBlock128256Cipher_Standard&) = default;
    ~UBlock128256Cipher_Standard()                                  = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept;
    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept;
    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept;
    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept;
};

class UBlock256256Cipher_Standard
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = 32;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = 32;

private:
    uint8_t sub_key[25][64];
    int     mode;

public:
    UBlock256256Cipher_Standard(const uint8_t* user_key, int mode) noexcept;
    UBlock256256Cipher_Standard()                                   = default;
    UBlock256256Cipher_Standard(const UBlock256256Cipher_Standard&) = default;
    ~UBlock256256Cipher_Standard()                                  = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept;
    void crypt_block(uint8_t out[32], const uint8_t in[32]) const noexcept;
    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept;
    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept;
};

}; // namespace gmlib

#endif //