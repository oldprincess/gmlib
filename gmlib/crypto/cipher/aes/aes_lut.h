#ifndef _GMLIB_CRYPTO_CIPHER_AES_LUT_H
#define _GMLIB_CRYPTO_CIPHER_AES_LUT_H

#include <TinyCrypto/cipher/aes/aes_lut.h>

namespace gmlib {

namespace aes_lut {

class Aes128Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = AES128_BLOCK_SIZE;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = AES128_USER_KEY_LEN;

private:
    tc::Aes128LutCTX ctx;
    int              mode;

public:
    Aes128Cipher(const uint8_t* user_key, int mode) noexcept
    {
        this->set_key(user_key, mode);
    }

    Aes128Cipher() = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept
    {
        this->mode = mode;
        if (mode == Aes128Cipher::ENCRYPTION)
        {
            tc::aes128_lut_enc_key_init(&this->ctx, user_key);
        }
        else
        {
            tc::aes128_lut_dec_key_init(&this->ctx, user_key);
        }
    }

    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept
    {
        if (mode == Aes128Cipher::ENCRYPTION)
        {
            tc::aes128_lut_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::aes128_lut_dec_block(&this->ctx, out, in);
        }
    }

    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept
    {
        if (mode == Aes128Cipher::ENCRYPTION)
        {
            tc::aes128_lut_enc_blocks(&this->ctx, out, in, block_num);
        }
        else
        {
            tc::aes128_lut_dec_blocks(&this->ctx, out, in, block_num);
        }
    }

    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept
    {
        if (mode == Aes128Cipher::ENCRYPTION)
        {
            tc::aes128_lut_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::aes128_lut_dec_block(&this->ctx, out, in);
        }
    }
};

class Aes192Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = AES192_BLOCK_SIZE;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = AES192_USER_KEY_LEN;

private:
    tc::Aes192LutCTX ctx;
    int              mode;

public:
    Aes192Cipher(const uint8_t* user_key, int mode) noexcept
    {
        this->set_key(user_key, mode);
    }

    Aes192Cipher() = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept
    {
        this->mode = mode;
        if (mode == Aes192Cipher::ENCRYPTION)
        {
            tc::aes192_lut_enc_key_init(&this->ctx, user_key);
        }
        else
        {
            tc::aes192_lut_dec_key_init(&this->ctx, user_key);
        }
    }

    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept
    {
        if (mode == Aes192Cipher::ENCRYPTION)
        {
            tc::aes192_lut_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::aes192_lut_dec_block(&this->ctx, out, in);
        }
    }

    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept
    {
        if (mode == Aes192Cipher::ENCRYPTION)
        {
            tc::aes192_lut_enc_blocks(&this->ctx, out, in, block_num);
        }
        else
        {
            tc::aes192_lut_dec_blocks(&this->ctx, out, in, block_num);
        }
    }

    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept
    {
        if (mode == Aes192Cipher::ENCRYPTION)
        {
            tc::aes192_lut_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::aes192_lut_dec_block(&this->ctx, out, in);
        }
    }
};

class Aes256Cipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    static constexpr size_t BLOCK_SIZE   = AES256_BLOCK_SIZE;
    static constexpr size_t PARALLEL_NUM = 1;
    static constexpr size_t USER_KEY_LEN = AES256_USER_KEY_LEN;

private:
    tc::Aes256LutCTX ctx;
    int              mode;

public:
    Aes256Cipher(const uint8_t* user_key, int mode) noexcept
    {
        this->set_key(user_key, mode);
    }

    Aes256Cipher() = default;

public:
    void set_key(const uint8_t* user_key, int mode) noexcept
    {
        this->mode = mode;
        if (mode == Aes256Cipher::ENCRYPTION)
        {
            tc::aes256_lut_enc_key_init(&this->ctx, user_key);
        }
        else
        {
            tc::aes256_lut_dec_key_init(&this->ctx, user_key);
        }
    }

    void crypt_block(uint8_t out[16], const uint8_t in[16]) const noexcept
    {
        if (mode == Aes256Cipher::ENCRYPTION)
        {
            tc::aes256_lut_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::aes256_lut_dec_block(&this->ctx, out, in);
        }
    }

    void crypt_blocks(uint8_t*       out,
                      const uint8_t* in,
                      size_t         block_num) const noexcept
    {
        if (mode == Aes256Cipher::ENCRYPTION)
        {
            tc::aes256_lut_enc_blocks(&this->ctx, out, in, block_num);
        }
        else
        {
            tc::aes256_lut_dec_blocks(&this->ctx, out, in, block_num);
        }
    }

    void crypt_blocks_parallel(uint8_t* out, const uint8_t* in) const noexcept
    {
        if (mode == Aes256Cipher::ENCRYPTION)
        {
            tc::aes256_lut_enc_block(&this->ctx, out, in);
        }
        else
        {
            tc::aes256_lut_dec_block(&this->ctx, out, in);
        }
    }
};

} // namespace aes_lut

} // namespace gmlib

#endif