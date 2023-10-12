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

#define MEM_LOAD32BE(src)                       \
    (((uint32_t)(((uint8_t*)(src))[0]) << 24) | \
     ((uint32_t)(((uint8_t*)(src))[1]) << 16) | \
     ((uint32_t)(((uint8_t*)(src))[2]) << 8) |  \
     ((uint32_t)(((uint8_t*)(src))[3]) << 0))

#define MEM_STORE32BE(dst, a)                             \
    (((uint8_t*)(dst))[0] = ((uint32_t)(a) >> 24) & 0xFF, \
     ((uint8_t*)(dst))[1] = ((uint32_t)(a) >> 16) & 0xFF, \
     ((uint8_t*)(dst))[2] = ((uint32_t)(a) >> 8) & 0xFF,  \
     ((uint8_t*)(dst))[3] = ((uint32_t)(a) >> 0) & 0xFF)

#define MEM_STORE64BE(dst, a)                             \
    (((uint8_t*)(dst))[0] = ((uint64_t)(a) >> 56) & 0xFF, \
     ((uint8_t*)(dst))[1] = ((uint64_t)(a) >> 48) & 0xFF, \
     ((uint8_t*)(dst))[2] = ((uint64_t)(a) >> 40) & 0xFF, \
     ((uint8_t*)(dst))[3] = ((uint64_t)(a) >> 32) & 0xFF, \
     ((uint8_t*)(dst))[4] = ((uint64_t)(a) >> 24) & 0xFF, \
     ((uint8_t*)(dst))[5] = ((uint64_t)(a) >> 16) & 0xFF, \
     ((uint8_t*)(dst))[6] = ((uint64_t)(a) >> 8) & 0xFF,  \
     ((uint8_t*)(dst))[7] = ((uint64_t)(a) >> 0) & 0xFF)

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************** SM3 CORE FUNCTIONS ****************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

#define rotl(x, n)    (((x) << (n)) | ((x) >> (32 - (n))))
#define P0(x)         ((x) ^ rotl((x), 9) ^ rotl((x), 17))
#define P1(x)         ((x) ^ rotl((x), 15) ^ rotl((x), 23))
#define FF00(x, y, z) ((x) ^ (y) ^ (z))
#define FF16(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define GG00(x, y, z) ((x) ^ (y) ^ (z))
#define GG16(x, y, z) ((((y) ^ (z)) & (x)) ^ (z))

#define R(A, B, C, D, E, F, G, H, xx)                                 \
    do                                                                \
    {                                                                 \
        uint32_t SS1 = rotl((rotl(A, 12) + E + T[j]), 7);             \
        uint32_t SS2 = SS1 ^ rotl(A, 12);                             \
        uint32_t TT1 = FF##xx(A, B, C) + D + SS2 + (W[j] ^ W[j + 4]); \
        uint32_t TT2 = GG##xx(E, F, G) + H + SS1 + W[j];              \
        B            = rotl(B, 9);                                    \
        D            = TT1;                                           \
        F            = rotl(F, 19);                                   \
        H            = P0(TT2);                                       \
        j++;                                                          \
    } while (0)

#define R4(A, B, C, D, E, F, G, H, xx) \
    R(A, B, C, D, E, F, G, H, xx);     \
    R(D, A, B, C, H, E, F, G, xx);     \
    R(C, D, A, B, G, H, E, F, xx);     \
    R(B, C, D, A, F, G, H, E, xx)

static const uint32_t T[64] = {
    0x79cc4519U, 0xf3988a32U, 0xe7311465U, 0xce6228cbU, 0x9cc45197U,
    0x3988a32fU, 0x7311465eU, 0xe6228cbcU, 0xcc451979U, 0x988a32f3U,
    0x311465e7U, 0x6228cbceU, 0xc451979cU, 0x88a32f39U, 0x11465e73U,
    0x228cbce6U, 0x9d8a7a87U, 0x3b14f50fU, 0x7629ea1eU, 0xec53d43cU,
    0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U, 0xc53d43ceU, 0x8a7a879dU,
    0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU, 0xa7a879d8U, 0x4f50f3b1U,
    0x9ea1e762U, 0x3d43cec5U, 0x7a879d8aU, 0xf50f3b14U, 0xea1e7629U,
    0xd43cec53U, 0xa879d8a7U, 0x50f3b14fU, 0xa1e7629eU, 0x43cec53dU,
    0x879d8a7aU, 0x0f3b14f5U, 0x1e7629eaU, 0x3cec53d4U, 0x79d8a7a8U,
    0xf3b14f50U, 0xe7629ea1U, 0xcec53d43U, 0x9d8a7a87U, 0x3b14f50fU,
    0x7629ea1eU, 0xec53d43cU, 0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U,
    0xc53d43ceU, 0x8a7a879dU, 0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU,
    0xa7a879d8U, 0x4f50f3b1U, 0x9ea1e762U, 0x3d43cec5U,
};

static void sm3_fast_compress(uint32_t digest[8], const uint8_t* data)
{
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t W[68];

    A = digest[0];
    B = digest[1];
    C = digest[2];
    D = digest[3];
    E = digest[4];
    F = digest[5];
    G = digest[6];
    H = digest[7];

    W[0]  = MEM_LOAD32BE(data + 0);
    W[1]  = MEM_LOAD32BE(data + 4);
    W[2]  = MEM_LOAD32BE(data + 8);
    W[3]  = MEM_LOAD32BE(data + 12);
    W[4]  = MEM_LOAD32BE(data + 16);
    W[5]  = MEM_LOAD32BE(data + 20);
    W[6]  = MEM_LOAD32BE(data + 24);
    W[7]  = MEM_LOAD32BE(data + 28);
    W[8]  = MEM_LOAD32BE(data + 32);
    W[9]  = MEM_LOAD32BE(data + 36);
    W[10] = MEM_LOAD32BE(data + 40);
    W[11] = MEM_LOAD32BE(data + 44);
    W[12] = MEM_LOAD32BE(data + 48);
    W[13] = MEM_LOAD32BE(data + 52);
    W[14] = MEM_LOAD32BE(data + 56);
    W[15] = MEM_LOAD32BE(data + 60);
    for (int j = 16; j < 68; j++)
    {
        W[j] = P1(W[j - 16] ^ W[j - 9] ^ rotl(W[j - 3], 15)) ^
               rotl(W[j - 13], 7) ^ W[j - 6];
    }

    int j = 0;
    R4(A, B, C, D, E, F, G, H, 00);
    R4(A, B, C, D, E, F, G, H, 00);
    R4(A, B, C, D, E, F, G, H, 00);
    R4(A, B, C, D, E, F, G, H, 00);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    R4(A, B, C, D, E, F, G, H, 16);
    digest[0] ^= A;
    digest[1] ^= B;
    digest[2] ^= C;
    digest[3] ^= D;
    digest[4] ^= E;
    digest[5] ^= F;
    digest[6] ^= G;
    digest[7] ^= H;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************* SM3 CIPHER FUNCTION ****************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

static int u64_add(uint64_t* r, uint64_t n)
{
    uint32_t a1  = (uint32_t)(*r >> 32);
    uint32_t a0  = *r & UINT32_MAX;
    uint32_t b1  = (uint32_t)(n >> 32);
    uint32_t b0  = n & UINT32_MAX;
    uint64_t tmp = (uint64_t)a0 + b0;
    uint32_t r0  = tmp & UINT32_MAX;
    tmp          = (uint64_t)a1 + b1 + (tmp >> 32);
    uint32_t r1  = tmp & UINT32_MAX;
    *r           = (uint64_t)r1 << 32 | r0;
    return (int)(tmp >> 32); // carry bit
}

static void sm3_fast_init(Sm3CTX* ctx)
{
    static const uint32_t SM3_INIT_DIGEST[8] = {
        0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600,
        0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E,
    };
    ctx->state[0]  = SM3_INIT_DIGEST[0];
    ctx->state[1]  = SM3_INIT_DIGEST[1];
    ctx->state[2]  = SM3_INIT_DIGEST[2];
    ctx->state[3]  = SM3_INIT_DIGEST[3];
    ctx->state[4]  = SM3_INIT_DIGEST[4];
    ctx->state[5]  = SM3_INIT_DIGEST[5];
    ctx->state[6]  = SM3_INIT_DIGEST[6];
    ctx->state[7]  = SM3_INIT_DIGEST[7];
    ctx->data_bits = 0;

    ctx->buf_size = 0;
}

static void sm3_fast_reset(Sm3CTX* ctx)
{
    sm3_fast_init(ctx);
}

static int sm3_fast_update(Sm3CTX* ctx, const uint8_t* in, size_t inl)
{
    uint64_t inl_bits = (uint64_t)inl * 8;
    if (inl_bits < inl || u64_add(&(ctx->data_bits), inl_bits))
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
        if (inl)
        {
            memcpy(ctx->buf, in, inl);
            ctx->buf_size = inl;
        }
        return 0;
    }
    if (inl)
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
    if (inl && ctx->buf_size == 0)
    {
        size_t block_num = inl / 64;
        while (block_num)
        {
            sm3_fast_compress(ctx->state, in);
            in += 64, inl -= 64, block_num--;
        }
        if (inl)
        {
            memcpy(ctx->buf, in, inl);
            ctx->buf_size = inl;
        }
        return 0;
    }
    return 0;
}

static void sm3_fast_final(Sm3CTX* ctx, uint8_t digest[32])
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

void Sm3Cipher::update(const uint8_t* in, size_t inl)
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