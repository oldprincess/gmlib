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

#ifndef _GMLIB_CRYPTO_CIPHER_SM4_LUT_H
#define _GMLIB_CRYPTO_CIPHER_SM4_LUT_H

#include <TinyCrypto/cipher/sm4/sm4_lut.h>

namespace gmlib {

namespace sm4_lut {

class Sm4Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = SM4_BLOCK_SIZE;
    static constexpr size_t PARALLEL_NUM = 4;
    static constexpr size_t USER_KEY_LEN = SM4_USER_KEY_LEN;

private:
    tc::Sm4LutCTX ctx;
    int           mode;

public:
    Sm4Cipher(const uint8_t* user_key, int mode) noexcept
    {
        this->set_key(user_key, mode);
    }

    Sm4Cipher() = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept
    {
        this->mode = mode;
        if (mode == Sm4Cipher::ENCRYPTION)
        {
            tc::sm4_lut_enc_key_init(&this->ctx, user_key);
        }
        else
        {
            tc::sm4_lut_dec_key_init(&this->ctx, user_key);
        }
    }

    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept
    {
        if (mode == Sm4Cipher::ENCRYPTION)
        {
            tc::sm4_lut_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::sm4_lut_dec_block(&this->ctx, out, in);
        }
    }

    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept
    {
        if (mode == Sm4Cipher::ENCRYPTION)
        {
            tc::sm4_lut_enc_blocks(&this->ctx, out, in, block_num);
        }
        else
        {
            tc::sm4_lut_dec_blocks(&this->ctx, out, in, block_num);
        }
    }

    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept
    {
        if (mode == Sm4Cipher::ENCRYPTION)
        {
            tc::sm4_lut_enc_block_x4(&this->ctx, out, in);
        }
        else
        {
            tc::sm4_lut_dec_block_x4(&this->ctx, out, in);
        }
    }
};

} // namespace sm4_lut

}; // namespace gmlib

#endif // !_GMLIB_CRYPTO_CIPHER_SM4_LUT_H
