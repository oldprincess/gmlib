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

#pragma once
#ifndef _GMLIB_CRYPTO_CIPHER_CIPHER_MODE_HPP
#define _GMLIB_CRYPTO_CIPHER_CIPHER_MODE_HPP

#include <stdexcept>
#include <cassert>
#include <memory>
#include <gmlib/crypto/hash/GHashCipher.h>

namespace gmlib {

namespace CipherModeUtil {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// **************** Memory Algo *********************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

static inline uint32_t MEM_LOAD32BE(const void* src) noexcept
{
    return ((uint32_t)(((uint8_t*)src)[0]) << 24) |
           ((uint32_t)(((uint8_t*)src)[1]) << 16) |
           ((uint32_t)(((uint8_t*)src)[2]) << 8) |
           ((uint32_t)(((uint8_t*)src)[3]) << 0);
}

static inline void MEM_STORE32BE(void* dst, uint32_t a) noexcept
{
    ((uint8_t*)dst)[0] = ((uint32_t)a >> 24) & 0xFF;
    ((uint8_t*)dst)[1] = ((uint32_t)a >> 16) & 0xFF;
    ((uint8_t*)dst)[2] = ((uint32_t)a >> 8) & 0xFF;
    ((uint8_t*)dst)[3] = ((uint32_t)a >> 0) & 0xFF;
}

static inline uint64_t MEM_LOAD64BE(const void* src) noexcept
{
    return ((uint64_t)(((uint8_t*)src)[0]) << 56) |
           ((uint64_t)(((uint8_t*)src)[1]) << 48) |
           ((uint64_t)(((uint8_t*)src)[2]) << 40) |
           ((uint64_t)(((uint8_t*)src)[3]) << 32) |
           ((uint64_t)(((uint8_t*)src)[4]) << 24) |
           ((uint64_t)(((uint8_t*)src)[5]) << 16) |
           ((uint64_t)(((uint8_t*)src)[6]) << 8) |
           ((uint64_t)(((uint8_t*)src)[7]) << 0);
}

static inline void MEM_STORE64BE(void* dst, uint64_t a) noexcept
{
    ((uint8_t*)dst)[0] = ((uint64_t)a >> 56) & 0xFF;
    ((uint8_t*)dst)[1] = ((uint64_t)a >> 48) & 0xFF;
    ((uint8_t*)dst)[2] = ((uint64_t)a >> 40) & 0xFF;
    ((uint8_t*)dst)[3] = ((uint64_t)a >> 32) & 0xFF;
    ((uint8_t*)dst)[4] = ((uint64_t)a >> 24) & 0xFF;
    ((uint8_t*)dst)[5] = ((uint64_t)a >> 16) & 0xFF;
    ((uint8_t*)dst)[6] = ((uint64_t)a >> 8) & 0xFF;
    ((uint8_t*)dst)[7] = ((uint64_t)a >> 0) & 0xFF;
}

// ****************************************
// ************ Memory Xor ****************
// ****************************************

static inline void memxor16(void*       dst,
                            const void* src1,
                            const void* src2) noexcept
{
    ((uint64_t*)dst)[0] = ((uint64_t*)src1)[0] ^ ((uint64_t*)src2)[0];
    ((uint64_t*)dst)[1] = ((uint64_t*)src1)[1] ^ ((uint64_t*)src2)[1];
}

static inline void memxor64(void*       dst,
                            const void* src1,
                            const void* src2) noexcept
{
    ((uint64_t*)dst)[0] = ((uint64_t*)src1)[0] ^ ((uint64_t*)src2)[0];
    ((uint64_t*)dst)[1] = ((uint64_t*)src1)[1] ^ ((uint64_t*)src2)[1];
    ((uint64_t*)dst)[2] = ((uint64_t*)src1)[2] ^ ((uint64_t*)src2)[2];
    ((uint64_t*)dst)[3] = ((uint64_t*)src1)[3] ^ ((uint64_t*)src2)[3];
    ((uint64_t*)dst)[4] = ((uint64_t*)src1)[4] ^ ((uint64_t*)src2)[4];
    ((uint64_t*)dst)[5] = ((uint64_t*)src1)[5] ^ ((uint64_t*)src2)[5];
    ((uint64_t*)dst)[6] = ((uint64_t*)src1)[6] ^ ((uint64_t*)src2)[6];
    ((uint64_t*)dst)[7] = ((uint64_t*)src1)[7] ^ ((uint64_t*)src2)[7];
}

static inline void memxor_n(void*       dst,
                            const void* src1,
                            const void* src2,
                            size_t      size) noexcept
{
    uint8_t* dst_u8  = (uint8_t*)dst;
    uint8_t *src1_u8 = (uint8_t*)src1, *src2_u8 = (uint8_t*)src2;
    while (size >= 64)
    {
        memxor64(dst_u8, src1_u8, src2_u8);
        dst_u8 += 64, src1_u8 += 64, src2_u8 += 64, size -= 64;
    }
    while (size >= 16)
    {
        memxor16(dst_u8, src1_u8, src2_u8);
        dst_u8 += 16, src1_u8 += 16, src2_u8 += 16, size -= 16;
    }
    while (size)
    {
        *dst_u8 = *src1_u8 ^ *src2_u8;
        dst_u8 += 1, src1_u8 += 1, src2_u8 += 1, size -= 1;
    }
}

template <size_t size>
inline void memxor(void* dst, const void* src1, const void* src2) noexcept
{
    memxor_n(dst, src1, src2, size);
}

template <>
inline void memxor<16>(void* dst, const void* src1, const void* src2) noexcept
{
    memxor16(dst, src1, src2);
}

template <>
inline void memxor<64>(void* dst, const void* src1, const void* src2) noexcept
{
    memxor64(dst, src1, src2);
}

// ****************************************
// *********** CTR Mode Inc ***************
// ****************************************

static inline void ctr_inc8(uint8_t* out, const uint8_t* in) noexcept
{
    uint64_t tmp = 1;
    tmp += MEM_LOAD32BE(in + 4);
    MEM_STORE32BE(out + 4, tmp & UINT32_MAX);
    tmp = MEM_LOAD32BE(in + 0) + (tmp >> 32);
    MEM_STORE32BE(out + 0, tmp & UINT32_MAX);
}

static inline void ctr_inc16(uint8_t* out, const uint8_t* in) noexcept
{
    uint64_t tmp = 1;
    tmp += MEM_LOAD32BE(in + 12);
    MEM_STORE32BE(out + 12, tmp & UINT32_MAX);
    tmp = MEM_LOAD32BE(in + 8) + (tmp >> 32);
    MEM_STORE32BE(out + 8, tmp & UINT32_MAX);
    tmp = MEM_LOAD32BE(in + 4) + (tmp >> 32);
    MEM_STORE32BE(out + 4, tmp & UINT32_MAX);
    tmp = MEM_LOAD32BE(in + 0) + (tmp >> 32);
    MEM_STORE32BE(out + 0, tmp & UINT32_MAX);
}

template <size_t BLOCK_SIZE>
inline void ctr_inc(uint8_t* out, const uint8_t* in) noexcept
{
    assert(0);
}

template <>
inline void ctr_inc<8>(uint8_t* out, const uint8_t* in) noexcept
{
    ctr_inc8(out, in);
}

template <>
inline void ctr_inc<16>(uint8_t* out, const uint8_t* in) noexcept
{
    ctr_inc16(out, in);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************** GCM Mode Algo *********************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

static inline void gctr_inc(uint8_t* out, const uint8_t* in) noexcept
{
    ((uint32_t*)out)[0] = ((const uint32_t*)in)[0];
    ((uint32_t*)out)[1] = ((const uint32_t*)in)[1];
    ((uint32_t*)out)[2] = ((const uint32_t*)in)[2];
    uint32_t tmp        = MEM_LOAD32BE(in + 12) + 1;
    MEM_STORE32BE(out + 12, tmp);
}

template <class GHash>
static void gcm_init_cnt(GHash*         mac,
                         uint8_t        counter[16],
                         const uint8_t* iv,
                         size_t         iv_len) noexcept
{
    static const uint8_t ZERO[16] = {0};
    // mac->reset();
    if (iv_len == 12)
    {
        memcpy(counter, iv, 12);
        counter[12] = 0;
        counter[13] = 0;
        counter[14] = 0;
        counter[15] = 1;
    }
    else
    {
        uint8_t t[16];
        // H(IV || 0(s+64) || ivlen(64) )
        mac->update(iv, iv_len);
        mac->update(ZERO, (16 - (iv_len % 16)) % 16);
        MEM_STORE64BE(t + 0, 0);
        MEM_STORE64BE(t + 8, iv_len * 8);
        mac->update(t, 16);
        mac->final(counter);
        mac->reset();
    }
}

}; // namespace CipherModeUtil

class CipherMode
{
public:
    virtual void update_blocks(uint8_t*       out,
                               const uint8_t* in,
                               size_t         block_num) = 0;

    virtual void final_block(uint8_t* out, const uint8_t* in, size_t inl) = 0;
};

template <size_t BLOCK_SIZE>
class CipherCryptor
{
private:
    uint8_t buf[BLOCK_SIZE];
    size_t  buf_size;

private:
    virtual void update_blocks(uint8_t*       out,
                               const uint8_t* in,
                               size_t         block_num) = 0;

    virtual void final_block(uint8_t* out, const uint8_t* in, size_t inl) = 0;

public:
    CipherCryptor() : buf_size(0)
    {
    }

public:
    void update(uint8_t* out, size_t* outl, const uint8_t* in, size_t inl)
    {
        if (inl == 0) return;
        uint8_t* out_base = out;
        if (this->buf_size == 0)
        {
            size_t block_num = inl / BLOCK_SIZE;
            size_t size      = block_num * BLOCK_SIZE;
            this->update_blocks(out, in, block_num);
            out += size, in += size, inl -= size;

            memcpy(this->buf, in, inl);
            this->buf_size = inl, *outl = (size_t)(out - out_base);
            return;
        }
        {
            size_t size = BLOCK_SIZE - this->buf_size;
            if (size > inl)
            {
                size = inl;
            }
            memcpy(this->buf + this->buf_size, in, size);
            this->buf_size += size, in += size, inl -= size;

            if (this->buf_size == BLOCK_SIZE)
            {
                this->update_blocks(out, this->buf, 1);
                this->buf_size = 0, out += BLOCK_SIZE;
            }
        }
        if (this->buf_size == 0)
        {
            size_t block_num = inl / BLOCK_SIZE;
            size_t size      = block_num * BLOCK_SIZE;
            this->update_blocks(out, in, block_num);
            out += size, in += size, inl -= size;

            memcpy(this->buf, in, inl);
            this->buf_size = inl, *outl = (size_t)(out - out_base);
            return;
        }
    }

    void final(uint8_t* out, size_t* outl)
    {
        this->final_block(out, this->buf, this->buf_size);
        *outl = this->buf_size;
    }
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// *************** ECB Cipher Mode ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

template <class Cipher>
class EcbEncryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher cipher; // Symmetric Cipher Context

public:
    EcbEncryptor(const uint8_t* user_key) : cipher(user_key, Cipher::ENCRYPTION)
    {
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        this->cipher.crypt_blocks(out, in, block_num);
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        if (inl == 0) return;
        // input len != 0
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in ECB mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->cipher.crypt_block(out, in);
    }
};

template <class Cipher>
class EcbDecryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher cipher; // Symmetric Cipher Context

public:
    EcbDecryptor(const uint8_t* user_key) : cipher(user_key, Cipher::DECRYPTION)
    {
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        this->cipher.crypt_blocks(out, in, block_num);
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        if (inl == 0) return;
        // input len != 0
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in ECB mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->cipher.crypt_block(out, in);
    }
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// *************** CBC Cipher Mode ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

template <class Cipher>
class CbcEncryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher  cipher;
    uint8_t iv[Cipher::BLOCK_SIZE];

public:
    CbcEncryptor(const uint8_t* user_key, const uint8_t* iv)
        : cipher(user_key, Cipher::ENCRYPTION)
    {
        memcpy(this->iv, iv, Cipher::BLOCK_SIZE);
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        uint8_t* cur_iv = this->iv;
        while (block_num)
        {
            CipherModeUtil::memxor<BLOCK_SIZE>(this->iv, in, cur_iv);
            this->cipher.crypt_block(out, this->iv);
            cur_iv = out;
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
        memcpy(this->iv, cur_iv, BLOCK_SIZE);
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        if (inl == 0) return;
        // input len != 0
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in CBC mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->update_blocks(out, in, 1);
    }
};

template <class Cipher>
class CbcDecryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher  cipher;
    uint8_t iv[Cipher::BLOCK_SIZE];

public:
    CbcDecryptor(const uint8_t* user_key, const uint8_t* iv)
        : cipher(user_key, Cipher::DECRYPTION)
    {
        memcpy(this->iv, iv, Cipher::BLOCK_SIZE);
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        constexpr size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;
        constexpr size_t REMAIN         = PARALLEL_BYTES - BLOCK_SIZE;

        uint8_t buffer[PARALLEL_BYTES], next_iv[BLOCK_SIZE];
        while (block_num >= PARALLEL_NUM)
        {
            memcpy(next_iv, in + REMAIN, BLOCK_SIZE);

            this->cipher.crypt_blocks_parallel(buffer, in);
            CipherModeUtil::memxor<BLOCK_SIZE>(out, buffer, this->iv);
            uint8_t *ptr1 = out + BLOCK_SIZE, *ptr2 = buffer + BLOCK_SIZE;
            CipherModeUtil::memxor<REMAIN>(ptr1, ptr2, in);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;

            memcpy(this->iv, next_iv, BLOCK_SIZE);
        }
        if (block_num)
        {
            size_t remain = (block_num - 1) * BLOCK_SIZE;
            memcpy(next_iv, in + remain, BLOCK_SIZE);

            this->cipher.crypt_blocks(buffer, in, block_num);
            CipherModeUtil::memxor<BLOCK_SIZE>(out, buffer, this->iv);
            uint8_t *ptr1 = out + BLOCK_SIZE, *ptr2 = buffer + BLOCK_SIZE;
            CipherModeUtil::memxor_n(ptr1, ptr2, in, remain);

            memcpy(this->iv, next_iv, BLOCK_SIZE);
        }
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        if (inl == 0) return;
        // input len != 0
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in CBC mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->update_blocks(out, in, 1);
    }
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// *************** CFB Cipher Mode ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

template <class Cipher>
class CfbEncryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher  cipher;
    uint8_t iv[Cipher::BLOCK_SIZE];

public:
    CfbEncryptor(const uint8_t* user_key, const uint8_t* iv)
        : cipher(user_key, Cipher::ENCRYPTION)
    {
        memcpy(this->iv, iv, Cipher::BLOCK_SIZE);
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        uint8_t* pre_ct = this->iv;
        while (block_num)
        {
            this->cipher.crypt_block(this->iv, pre_ct);
            CipherModeUtil::memxor<BLOCK_SIZE>(out, in, this->iv);
            pre_ct = out;
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
        memcpy(this->iv, pre_ct, BLOCK_SIZE);
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        assert(0 <= inl && inl <= Cipher::BLOCK_SIZE);
        if (inl == 0) return;
        this->cipher.crypt_block(this->iv, this->iv);
        CipherModeUtil::memxor_n(out, this->iv, in, inl);
    }
};

template <class Cipher>
class CfbDecryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher  cipher;
    uint8_t iv[Cipher::BLOCK_SIZE];

public:
    CfbDecryptor(const uint8_t* user_key, const uint8_t* iv)
        : cipher(user_key, Cipher::ENCRYPTION)
    {
        memcpy(this->iv, iv, Cipher::BLOCK_SIZE);
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        constexpr size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;
        constexpr size_t REMAIN         = PARALLEL_BYTES - BLOCK_SIZE;

        uint8_t buffer[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            memcpy(buffer, this->iv, BLOCK_SIZE);
            memcpy(buffer + BLOCK_SIZE, in, REMAIN);
            memcpy(this->iv, in + REMAIN, BLOCK_SIZE);
            this->cipher.crypt_blocks_parallel(buffer, buffer);
            CipherModeUtil::memxor<PARALLEL_BYTES>(out, in, buffer);
            out += PARALLEL_BYTES;
            in += PARALLEL_BYTES, block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            size_t         remain_bytes = block_num * BLOCK_SIZE;
            const uint8_t* nxt_iv       = in + remain_bytes - BLOCK_SIZE;
            memcpy(buffer, this->iv, BLOCK_SIZE);
            memcpy(buffer + BLOCK_SIZE, in, remain_bytes - BLOCK_SIZE);
            memcpy(this->iv, nxt_iv, BLOCK_SIZE);
            this->cipher.crypt_blocks(buffer, buffer, block_num);
            CipherModeUtil::memxor_n(out, in, buffer, remain_bytes);
        }
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        assert(0 <= inl && inl <= Cipher::BLOCK_SIZE);
        if (inl == 0) return;
        this->cipher.crypt_block(this->iv, this->iv);
        CipherModeUtil::memxor_n(out, in, this->iv, inl);
    }
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// *************** OFB Cipher Mode ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

template <class Cipher>
class OfbCryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher  cipher;
    uint8_t iv[Cipher::BLOCK_SIZE];

private:
    void gen_key_stream(uint8_t* out, size_t outl)
    {
        assert(outl % Cipher::BLOCK_SIZE == 0);

        constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        uint8_t* pre_ct = this->iv;
        do
        {
            this->cipher.crypt_block(out, pre_ct);
            pre_ct = out;
            out += BLOCK_SIZE, outl -= BLOCK_SIZE;
        } while (outl >= BLOCK_SIZE);
        memcpy(this->iv, pre_ct, BLOCK_SIZE);
    }

public:
    OfbCryptor(const uint8_t* user_key, const uint8_t* iv)
        : cipher(user_key, Cipher::ENCRYPTION)
    {
        memcpy(this->iv, iv, Cipher::BLOCK_SIZE);
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        uint8_t key_stream[BLOCK_SIZE];
        while (block_num)
        {
            this->gen_key_stream(key_stream, BLOCK_SIZE);
            CipherModeUtil::memxor<BLOCK_SIZE>(out, in, key_stream);
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        assert(0 <= inl && inl <= Cipher::BLOCK_SIZE);
        if (inl == 0) return;

        constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        uint8_t key_stream[BLOCK_SIZE];
        this->gen_key_stream(key_stream, BLOCK_SIZE);
        CipherModeUtil::memxor_n(out, in, key_stream, inl);
    }
};

template <class Cipher>
using OfbEncryptor = OfbCryptor<Cipher>;

template <class Cipher>
using OfbDecryptor = OfbCryptor<Cipher>;

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// *************** CTR Cipher Mode ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

template <class Cipher>
class CtrCryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    Cipher  cipher;
    uint8_t counter[Cipher::BLOCK_SIZE];

private:
    void gen_block_key_stream(uint8_t* out, size_t block_num)
    {
        if (block_num == 0) return;
        constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;
        // generate counter
        uint8_t* cur_counter = out;
        memcpy(cur_counter, this->counter, BLOCK_SIZE);
        for (size_t i = 1; i < block_num; i++)
        {
            uint8_t* nxt_counter = cur_counter + BLOCK_SIZE;
            CipherModeUtil::ctr_inc<BLOCK_SIZE>(nxt_counter, cur_counter);
            cur_counter = nxt_counter;
        }
        CipherModeUtil::ctr_inc<BLOCK_SIZE>(this->counter, cur_counter);
        // generate key stream
        this->cipher.crypt_blocks(out, out, block_num);
    }

public:
    CtrCryptor(const uint8_t* user_key, const uint8_t* iv)
        : cipher(user_key, Cipher::ENCRYPTION)
    {
        memcpy(this->counter, iv, Cipher::BLOCK_SIZE);
    }

public:
    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        constexpr size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;

        uint8_t key_stream[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            this->gen_block_key_stream(key_stream, PARALLEL_NUM);
            CipherModeUtil::memxor<PARALLEL_BYTES>(out, in, key_stream);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            size_t remain_bytes = block_num * BLOCK_SIZE;
            this->gen_block_key_stream(key_stream, block_num);
            CipherModeUtil::memxor_n(out, in, key_stream, remain_bytes);
        }
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        assert(0 <= inl && inl <= Cipher::BLOCK_SIZE);
        if (inl == 0) return;
        constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;
        uint8_t          key_stream[BLOCK_SIZE];
        this->gen_block_key_stream(key_stream, 1);
        CipherModeUtil::memxor_n(out, key_stream, in, inl);
    }
};

template <class Cipher>
using CtrEncryptor = CtrCryptor<Cipher>;

template <class Cipher>
using CtrDecryptor = CtrCryptor<Cipher>;

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// *************** Gcm Cipher Mode ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

template <class Cipher, class GHash = GHashCipher>
class GcmEncryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
    static_assert(Cipher::BLOCK_SIZE == 16,
                  "GCM mode only supports Cipher with BLOCK_SIZE=16");

public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    static constexpr uint8_t ZERO[16] = {0};

    GHash    mac;
    Cipher   cipher;
    uint8_t  tag[16];
    uint8_t  counter[16];
    uint8_t  counter0[16];
    uint64_t aad_len, ct_len;

private:
    void gen_block_key_stream(uint8_t* out, size_t block_num)
    {
        if (block_num == 0) return;
        // generate counter
        uint8_t* cur_counter = out;
        memcpy(cur_counter, this->counter, 16);
        for (size_t i = 1; i < block_num; i++)
        {
            uint8_t* nxt_counter = cur_counter + 16;
            CipherModeUtil::gctr_inc(nxt_counter, cur_counter);
            cur_counter = nxt_counter;
        }
        CipherModeUtil::gctr_inc(this->counter, cur_counter);
        // generate key stream
        this->cipher.crypt_blocks(out, out, block_num);
    }

public:
    GcmEncryptor(const uint8_t* user_key,
                 const uint8_t* iv,
                 size_t         iv_len,
                 const uint8_t* aad,
                 size_t         aad_len)
        : cipher(user_key, Cipher::ENCRYPTION)
    {
        uint8_t t[16];
        this->cipher.crypt_block(t, this->ZERO);
        this->mac.set_key(t);
        // init counter
        CipherModeUtil::gcm_init_cnt<GHash>(&this->mac, this->counter0, iv,
                                            iv_len);
        CipherModeUtil::gctr_inc(this->counter, this->counter0);
        // gmac aad(additional authenticated data)
        this->mac.update(aad, aad_len);
        this->mac.update(this->ZERO, (16 - (aad_len % 16)) % 16);
        this->aad_len = aad_len;
        this->ct_len  = 0;
    }

public:
    void reset(const uint8_t* iv,
               size_t         iv_len,
               const uint8_t* aad,
               size_t         aad_len)
    {
        this->mac.reset();
        CipherModeUtil::gcm_init_cnt<GHash>(&this->mac, this->counter0, iv,
                                            iv_len);
        CipherModeUtil::gctr_inc(this->counter, this->counter0);
        // gmac aad(additional authenticated data)
        this->mac.update(aad, aad_len);
        this->mac.update(this->ZERO, (16 - (aad_len % 16)) % 16);

        this->aad_len = aad_len;
        this->ct_len  = 0;
    }

    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        if (block_num == 0) return;
        constexpr size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;

        uint8_t* base_out = out;
        // gctr
        uint8_t key_stream[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            this->gen_block_key_stream(key_stream, PARALLEL_NUM);
            CipherModeUtil::memxor<PARALLEL_BYTES>(out, in, key_stream);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            size_t remain_bytes = block_num * BLOCK_SIZE;
            this->gen_block_key_stream(key_stream, block_num);
            CipherModeUtil::memxor_n(out, in, key_stream, remain_bytes);
        }
        // gmac
        this->mac.update(base_out, (size_t)(out - base_out));
        this->ct_len += (size_t)(out - base_out);
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        assert(0 <= inl && inl < 16);
        if (inl != 0)
        {
            uint8_t key_stream[16];
            this->gen_block_key_stream(key_stream, 1);
            CipherModeUtil::memxor_n(out, key_stream, in, inl);
            this->mac.update(out, inl);
            this->mac.update(this->ZERO, (16 - inl % 16) % 16);
            this->ct_len += inl;
        }
        uint8_t t[16];
        CipherModeUtil::MEM_STORE64BE(t + 0, this->aad_len * 8);
        CipherModeUtil::MEM_STORE64BE(t + 8, this->ct_len * 8);
        this->mac.update(t, 16);
        this->mac.final(this->tag);
        this->cipher.crypt_block(t, this->counter0);
        CipherModeUtil::memxor<16>(this->tag, this->tag, t);
    }

    void get_tag(uint8_t tag[16]) const noexcept
    {
        memcpy(tag, this->tag, 16);
    }
};

template <class Cipher, class GHash = GHashCipher>
class GcmDecryptor : public CipherCryptor<Cipher::BLOCK_SIZE>
{
    static_assert(Cipher::BLOCK_SIZE == 16,
                  "GCM mode only supports Cipher with BLOCK_SIZE=16");

public:
    static constexpr size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

private:
    static constexpr uint8_t ZERO[16] = {0};

    GHash   mac;
    Cipher  cipher;
    uint8_t tag[16];
    uint8_t counter[16];
    uint8_t counter0[16];
    size_t  aad_len, ct_len;

private:
    void gen_block_key_stream(uint8_t* out, size_t block_num)
    {
        if (block_num == 0) return;
        // generate counter
        uint8_t* cur_counter = out;
        memcpy(cur_counter, this->counter, 16);
        for (size_t i = 1; i < block_num; i++)
        {
            uint8_t* nxt_counter = cur_counter + 16;
            CipherModeUtil::gctr_inc(nxt_counter, cur_counter);
            cur_counter = nxt_counter;
        }
        CipherModeUtil::gctr_inc(this->counter, cur_counter);
        // generate key stream
        this->cipher.crypt_blocks(out, out, block_num);
    }

public:
    // additional authenticated data
    GcmDecryptor(const uint8_t* user_key,
                 const uint8_t* iv,
                 size_t         iv_len,
                 const uint8_t* aad,
                 size_t         aad_len)
        : cipher(user_key, Cipher::ENCRYPTION)
    {
        uint8_t t[16];
        this->cipher.crypt_block(t, this->ZERO);
        this->mac.set_key(t);
        // init counter
        CipherModeUtil::gcm_init_cnt<GHash>(&this->mac, this->counter0, iv,
                                            iv_len);
        CipherModeUtil::gctr_inc(this->counter, this->counter0);
        // gmac aad(additional authenticated data)
        this->mac.update(aad, aad_len);
        this->mac.update(this->ZERO, (16 - (aad_len % 16)) % 16);

        this->aad_len = aad_len;
        this->ct_len  = 0;
    }

public:
    void reset(const uint8_t* iv,
               size_t         iv_len,
               const uint8_t* aad,
               size_t         aad_len)
    {
        this->mac.reset();
        CipherModeUtil::gcm_init_cnt<GHash>(&this->mac, this->counter0, iv,
                                            iv_len);
        CipherModeUtil::gctr_inc(this->counter, this->counter0);
        // gmac aad(additional authenticated data)
        this->mac.update(aad, aad_len);
        this->mac.update(this->ZERO, (16 - (aad_len % 16)) % 16);

        this->aad_len = aad_len;
        this->ct_len  = 0;
    }

    void update_blocks(uint8_t* out, const uint8_t* in, size_t block_num)
    {
        if (block_num == 0) return;
        // gmac
        this->mac.update(in, block_num * Cipher::BLOCK_SIZE);
        this->ct_len += block_num * Cipher::BLOCK_SIZE;

        constexpr size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;

        uint8_t* base_out = out;
        // gctr
        uint8_t key_stream[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            this->gen_block_key_stream(key_stream, PARALLEL_NUM);
            CipherModeUtil::memxor<PARALLEL_BYTES>(out, in, key_stream);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            size_t remain_bytes = block_num * BLOCK_SIZE;
            this->gen_block_key_stream(key_stream, block_num);
            CipherModeUtil::memxor_n(out, in, key_stream, remain_bytes);
        }
    }

    void final_block(uint8_t* out, const uint8_t* in, size_t inl)
    {
        assert(0 <= inl && inl <= 16);
        if (inl != 0)
        {
            this->mac.update(in, inl);
            this->mac.update(this->ZERO, (16 - inl % 16) % 16);
            this->ct_len += inl;

            uint8_t key_stream[16];
            this->gen_block_key_stream(key_stream, 1);
            CipherModeUtil::memxor_n(out, key_stream, in, inl);
        }
        uint8_t t[16], t1[16];
        CipherModeUtil::MEM_STORE64BE(t + 0, this->aad_len * 8);
        CipherModeUtil::MEM_STORE64BE(t + 8, this->ct_len * 8);
        this->mac.update(t, 16);
        this->mac.final(t);

        this->cipher.crypt_block(t1, this->counter0);
        CipherModeUtil::memxor<16>(t, t1, t);
        if (memcmp(this->tag, t, 16) != 0)
        {
            throw std::runtime_error("GCM tag check fail");
        }
    }

    void set_tag(const uint8_t tag[16]) noexcept
    {
        memcpy(this->tag, tag, 16);
    }
};

}; // namespace gmlib

#endif