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

#ifndef _GMLIB_CRYPTO_CIPHER_UBLOCK_STANDARD_H
#define _GMLIB_CRYPTO_CIPHER_UBLOCK_STANDARD_H

#include <TinyCrypto/cipher/ublock/ublock_standard.h>

namespace gmlib {

namespace ublock_standard {

class UBlock128128Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = UBLOCK128128_BLOCK_SIZE;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = UBLOCK128128_USER_KEY_LEN;

private:
    tc::UBlockStandardCTX ctx;
    int                   mode;

public:
    UBlock128128Cipher(const uint8_t* user_key, int mode) noexcept
    {
        this->set_key(user_key, mode);
    }

    UBlock128128Cipher() = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept
    {
        this->mode = mode;
        if (mode == UBlock128128Cipher::ENCRYPTION)
        {
            tc::ublock128128_standard_enc_key_init(&this->ctx, user_key);
        }
        else
        {
            tc::ublock128128_standard_dec_key_init(&this->ctx, user_key);
        }
    }

    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept
    {
        if (mode == UBlock128128Cipher::ENCRYPTION)
        {
            tc::ublock128128_standard_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::ublock128128_standard_dec_block(&this->ctx, out, in);
        }
    }

    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept
    {
        if (mode == UBlock128128Cipher::ENCRYPTION)
        {
            tc::ublock128128_standard_enc_blocks(&this->ctx, out, in,
                                                 block_num);
        }
        else
        {
            tc::ublock128128_standard_dec_blocks(&this->ctx, out, in,
                                                 block_num);
        }
    }

    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept
    {
        if (mode == UBlock128128Cipher::ENCRYPTION)
        {
            tc::ublock128128_standard_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::ublock128128_standard_dec_block(&this->ctx, out, in);
        }
    }
};

class UBlock128256Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = UBLOCK128256_BLOCK_SIZE;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = UBLOCK128256_USER_KEY_LEN;

private:
    tc::UBlockStandardCTX ctx;
    int                   mode;

public:
    UBlock128256Cipher(const uint8_t* user_key, int mode) noexcept
    {
        this->set_key(user_key, mode);
    }

    UBlock128256Cipher() = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept
    {
        this->mode = mode;
        if (mode == UBlock128256Cipher::ENCRYPTION)
        {
            tc::ublock128256_standard_enc_key_init(&this->ctx, user_key);
        }
        else
        {
            tc::ublock128256_standard_dec_key_init(&this->ctx, user_key);
        }
    }

    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept
    {
        if (mode == UBlock128256Cipher::ENCRYPTION)
        {
            tc::ublock128256_standard_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::ublock128256_standard_dec_block(&this->ctx, out, in);
        }
    }

    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept
    {
        if (mode == UBlock128256Cipher::ENCRYPTION)
        {
            tc::ublock128256_standard_enc_blocks(&this->ctx, out, in,
                                                 block_num);
        }
        else
        {
            tc::ublock128256_standard_dec_blocks(&this->ctx, out, in,
                                                 block_num);
        }
    }

    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept
    {
        if (mode == UBlock128256Cipher::ENCRYPTION)
        {
            tc::ublock128256_standard_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::ublock128256_standard_dec_block(&this->ctx, out, in);
        }
    }
};

class UBlock256256Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = UBLOCK256256_BLOCK_SIZE;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = UBLOCK256256_USER_KEY_LEN;

private:
    tc::UBlockStandardCTX ctx;
    int                   mode;

public:
    UBlock256256Cipher(const uint8_t* user_key, int mode) noexcept
    {
        this->set_key(user_key, mode);
    }

    UBlock256256Cipher() = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept
    {
        this->mode = mode;
        if (mode == UBlock256256Cipher::ENCRYPTION)
        {
            tc::ublock256256_standard_enc_key_init(&this->ctx, user_key);
        }
        else
        {
            tc::ublock256256_standard_dec_key_init(&this->ctx, user_key);
        }
    }

    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept
    {
        if (mode == UBlock256256Cipher::ENCRYPTION)
        {
            tc::ublock256256_standard_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::ublock256256_standard_dec_block(&this->ctx, out, in);
        }
    }

    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept
    {
        if (mode == UBlock256256Cipher::ENCRYPTION)
        {
            tc::ublock256256_standard_enc_blocks(&this->ctx, out, in,
                                                 block_num);
        }
        else
        {
            tc::ublock256256_standard_dec_blocks(&this->ctx, out, in,
                                                 block_num);
        }
    }

    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept
    {
        if (mode == UBlock256256Cipher::ENCRYPTION)
        {
            tc::ublock256256_standard_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::ublock256256_standard_dec_block(&this->ctx, out, in);
        }
    }
};

} // namespace ublock_standard

}; // namespace gmlib

#endif