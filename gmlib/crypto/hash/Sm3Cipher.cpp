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

#include <gmlib/crypto/hash/Sm3Cipher.h>
#include <stdexcept>
#include <string.h>

using Sm3CTX = gmlib::Sm3Cipher::Sm3CTX;

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************* SM3 Core Algorithm *****************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma region "SM3 Core Algorithm"

#define MEM_LOAD32BE(src)                        \
    (((uint32_t)(((uint8_t *)(src))[0]) << 24) | \
     ((uint32_t)(((uint8_t *)(src))[1]) << 16) | \
     ((uint32_t)(((uint8_t *)(src))[2]) << 8) |  \
     ((uint32_t)(((uint8_t *)(src))[3]) << 0))

#define MEM_STORE32BE(dst, a)                              \
    (((uint8_t *)(dst))[0] = ((uint32_t)(a) >> 24) & 0xFF, \
     ((uint8_t *)(dst))[1] = ((uint32_t)(a) >> 16) & 0xFF, \
     ((uint8_t *)(dst))[2] = ((uint32_t)(a) >> 8) & 0xFF,  \
     ((uint8_t *)(dst))[3] = ((uint32_t)(a) >> 0) & 0xFF)

#define MEM_LOAD64BE(src)                        \
    (((uint64_t)(((uint8_t *)(src))[0]) << 56) | \
     ((uint64_t)(((uint8_t *)(src))[1]) << 48) | \
     ((uint64_t)(((uint8_t *)(src))[2]) << 40) | \
     ((uint64_t)(((uint8_t *)(src))[3]) << 32) | \
     ((uint64_t)(((uint8_t *)(src))[4]) << 24) | \
     ((uint64_t)(((uint8_t *)(src))[5]) << 16) | \
     ((uint64_t)(((uint8_t *)(src))[6]) << 8) |  \
     ((uint64_t)(((uint8_t *)(src))[7]) << 0))

#define MEM_STORE64BE(dst, a)                              \
    (((uint8_t *)(dst))[0] = ((uint64_t)(a) >> 56) & 0xFF, \
     ((uint8_t *)(dst))[1] = ((uint64_t)(a) >> 48) & 0xFF, \
     ((uint8_t *)(dst))[2] = ((uint64_t)(a) >> 40) & 0xFF, \
     ((uint8_t *)(dst))[3] = ((uint64_t)(a) >> 32) & 0xFF, \
     ((uint8_t *)(dst))[4] = ((uint64_t)(a) >> 24) & 0xFF, \
     ((uint8_t *)(dst))[5] = ((uint64_t)(a) >> 16) & 0xFF, \
     ((uint8_t *)(dst))[6] = ((uint64_t)(a) >> 8) & 0xFF,  \
     ((uint8_t *)(dst))[7] = ((uint64_t)(a) >> 0) & 0xFF)

static inline uint32_t rotl(uint32_t x, int s)
{
    return ((x) << (s) | (x) >> (32 - (s)));
}

static inline uint32_t P0(uint32_t x)
{
    return x ^ rotl(x, 9) ^ rotl(x, 17);
}

static inline uint32_t P1(uint32_t x)
{
    return x ^ rotl(x, 15) ^ rotl(x, 23);
}

static inline uint32_t FFj(uint32_t x, uint32_t y, uint32_t z, int j)
{
    if (j < 16)
    {
        return x ^ y ^ z;
    }
    else
    {
        return (x & y) | (x & z) | (y & z);
    }
}

static inline uint32_t GGj(uint32_t x, uint32_t y, uint32_t z, int j)
{
    if (j < 16)
    {
        return x ^ y ^ z;
    }
    else
    {
        return (x & y) | (~x & z);
    }
}

// T[j] = Tj <<< (j mod 32)
static uint32_t T[64] = {
    0x79cc4519, 0xf3988a32, 0xe7311465, 0xce6228cb, 0x9cc45197, 0x3988a32f,
    0x7311465e, 0xe6228cbc, 0xcc451979, 0x988a32f3, 0x311465e7, 0x6228cbce,
    0xc451979c, 0x88a32f39, 0x11465e73, 0x228cbce6, 0x9d8a7a87, 0x3b14f50f,
    0x7629ea1e, 0xec53d43c, 0xd8a7a879, 0xb14f50f3, 0x629ea1e7, 0xc53d43ce,
    0x8a7a879d, 0x14f50f3b, 0x29ea1e76, 0x53d43cec, 0xa7a879d8, 0x4f50f3b1,
    0x9ea1e762, 0x3d43cec5, 0x7a879d8a, 0xf50f3b14, 0xea1e7629, 0xd43cec53,
    0xa879d8a7, 0x50f3b14f, 0xa1e7629e, 0x43cec53d, 0x879d8a7a, 0x0f3b14f5,
    0x1e7629ea, 0x3cec53d4, 0x79d8a7a8, 0xf3b14f50, 0xe7629ea1, 0xcec53d43,
    0x9d8a7a87, 0x3b14f50f, 0x7629ea1e, 0xec53d43c, 0xd8a7a879, 0xb14f50f3,
    0x629ea1e7, 0xc53d43ce, 0x8a7a879d, 0x14f50f3b, 0x29ea1e76, 0x53d43cec,
    0xa7a879d8, 0x4f50f3b1, 0x9ea1e762, 0x3d43cec5,
};

static void sm3_fast_compress(uint32_t state[8], const uint8_t data[64])
{
    // expand
    uint32_t w[68];
    for (int j = 0; j < 16; j++)
    {
        w[j] = MEM_LOAD32BE(data + 4 * j);
    }
    for (int j = 16; j < 68; j++)
    {
        w[j] = P1(w[j - 16] ^ w[j - 9] ^ rotl(w[j - 3], 15)) ^
               rotl(w[j - 13], 7) ^ w[j - 6];
    }
    // compress
    uint32_t A, B, C, D, E, F, G, H;
    A = state[0], B = state[1], C = state[2], D = state[3];
    E = state[4], F = state[5], G = state[6], H = state[7];
    uint32_t SS1, SS2, TT1, TT2;
    for (int j = 0; j < 64; j++)
    {
        SS1 = rotl((rotl(A, 12) + E + T[j]), 7);
        SS2 = SS1 ^ rotl(A, 12);
        TT1 = FFj(A, B, C, j) + D + SS2 + (w[j] ^ w[j + 4]);
        TT2 = GGj(E, F, G, j) + H + SS1 + w[j];
        D   = C;
        C   = rotl(B, 9);
        B   = A;
        A   = TT1;
        H   = G;
        G   = rotl(F, 19);
        F   = E;
        E   = P0(TT2);
    }
    state[0] ^= A, state[1] ^= B, state[2] ^= C, state[3] ^= D;
    state[4] ^= E, state[5] ^= F, state[6] ^= G, state[7] ^= H;
}

static int uint64_add(uint64_t *self, uint64_t other)
{
    uint32_t a0, a1, b0, b1, r0, r1;
    uint64_t t;
    a0 = *self & UINT32_MAX, a1 = *self >> 32;
    b0 = other & UINT32_MAX, b1 = other >> 32;

    t  = (uint64_t)a0 + b0;
    r0 = t & UINT32_MAX;
    t  = t >> 32;

    t  = (uint64_t)a1 + b1 + t;
    r1 = t & UINT32_MAX;
    t  = t >> 32;

    *self = (uint64_t)r1 << 32 | r0;
    return (int)t;
}

static void sm3_fast_init(Sm3CTX *ctx)
{
    static const uint32_t SM3_INIT_DIGEST[8] = {
        0x7380166F,
        0x4914B2B9,
        0x172442D7,
        0xDA8A0600,
        0xA96F30BC,
        0x163138AA,
        0xE38DEE4D,
        0xB0FB0E4E,
    };
    ctx->state[0] = SM3_INIT_DIGEST[0];
    ctx->state[1] = SM3_INIT_DIGEST[1];
    ctx->state[2] = SM3_INIT_DIGEST[2];
    ctx->state[3] = SM3_INIT_DIGEST[3];
    ctx->state[4] = SM3_INIT_DIGEST[4];
    ctx->state[5] = SM3_INIT_DIGEST[5];
    ctx->state[6] = SM3_INIT_DIGEST[6];
    ctx->state[7] = SM3_INIT_DIGEST[7];

    ctx->data_bits = 0;
    ctx->buf_size  = 0;
}

static int sm3_fast_update(Sm3CTX *ctx, const uint8_t *in, size_t inl)
{
    uint64_t inl_bits = (uint64_t)inl * 8;
    if (inl_bits < inl || uint64_add(&(ctx->data_bits), inl_bits))
    {
        return -1; // input bits overflow
    }

    if (ctx->buf_size == 0)
    {
        size_t block_num = inl / 64;
        while (block_num)
        {
            sm3_fast_compress(ctx->state, in);
            in += 64, inl -= 64, block_num--;
        }
    }
    while (inl)
    {
        size_t size = 64 - ctx->buf_size;
        if (size > inl)
        {
            size = inl;
        }
        memcpy(ctx->buf + ctx->buf_size, in, size);
        in += size, inl -= size, ctx->buf_size += size;

        if (ctx->buf_size == 64)
        {
            sm3_fast_compress(ctx->state, ctx->buf);
            ctx->buf_size = 0;
        }
    }
    return 0;
}

static void sm3_fast_final(Sm3CTX *ctx, uint8_t digest[32])
{
    size_t  pad_num = (64ULL + 56 - 1 - ctx->buf_size) % 64;
    uint8_t buf[64 * 2];
    size_t  buf_size = 0;
    memcpy(buf, ctx->buf, ctx->buf_size);
    buf_size += ctx->buf_size;                     // update
    buf[buf_size] = 0x80;                          // 10..0
    buf_size += 1;                                 // update
    memset(buf + buf_size, 0, pad_num);            // pad 0
    buf_size += pad_num;                           // update
    MEM_STORE64BE(buf + buf_size, ctx->data_bits); //
    buf_size += 8;                                 // update
    // compress
    for (size_t i = 0; i < buf_size; i += 64)
    {
        sm3_fast_compress(ctx->state, buf + i);
    }
    // output digest
    for (int i = 0; i < 8; i++)
    {
        MEM_STORE32BE(digest + 4 * i, ctx->state[i]);
    }
}

#pragma endregion

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ***************** SM3 Cipher *********************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma region "SM3 Cipher"

namespace gmlib {

Sm3Cipher::Sm3Cipher() noexcept
{
    sm3_fast_init(&(this->ctx));
}

void Sm3Cipher::reset() noexcept
{
    sm3_fast_init(&(this->ctx));
}

void Sm3Cipher::update(const uint8_t *in, size_t inl)
{
    int err = sm3_fast_update(&(this->ctx), in, inl);
    if (err)
    {
        throw std::overflow_error(
            "input data too long, SM3 message bits need < 2^64");
    }
}

void Sm3Cipher::final(uint8_t digest[32]) noexcept
{
    sm3_fast_final(&(this->ctx), digest);
}

}; // namespace gmlib

#pragma endregion