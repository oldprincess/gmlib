/**
 * part of the code is "derived from
 * https://sfjs.cacrnet.org.cn/site/term/list_76_1.html"
 *
 * CUI T T, WANG M Q, FAN Y H, HU K, FU Y, HUANG L N. Ballet: A
 * software-friendly block cipher [J]. Journal of Cryptologic Research, 2019,
 * 6(6): 704-712.
 */
#include "ballet_standard.h"

namespace ballet::internal::standard {

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************ BALLET COMMON CORE FUNC *************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * Starting from here, until the next similar comment declaration.
 *
 * the code is "derived from
 * https://sfjs.cacrnet.org.cn/site/term/list_76_1.html"
 *
 * CUI T T, WANG M Q, FAN Y H, HU K, FU Y, HUANG L N. Ballet: A
 * software-friendly block cipher [J]. Journal of Cryptologic Research, 2019,
 * 6(6): 704-712.
 */

#define RoundBallet128128 46
#define RoundBallet128256 48
#define RoundBallet256256 74

#define ROTL4(v, n)  (((v) << (n)) | ((v) >> (4 - (n))))
#define ROTL8(v, n)  ((uint8_t)((v) << (n)) | ((v) >> (8 - (n))))
#define ROTL16(v, n) ((uint16_t)((v) << (n)) | ((v) >> (16 - (n))))
#define ROTR16(v, n) ((uint16_t)((v) >> (n)) | ((v) << (16 - (n))))
#define SWAP16(v)    ROTL16(v, 8)
#define ROTL32(v, n) ((uint32_t)((v) << (n)) | ((v) >> (32 - (n))))
#define ROTR32(v, n) ((uint32_t)((v) >> (n)) | ((v) << (32 - (n))))
#define SWAP32(v)                              \
    ((ROTL32(v, 8) & (uint32_t)(0x00FF00FF)) | \
     (ROTL32(v, 24) & (uint32_t)(0xFF00FF00)))
#define SWAP64(v)                              \
    (((uint64_t)SWAP32((uint32_t)(v)) << 32) | \
     (uint64_t)SWAP32((uint32_t)(v >> 32)))
#define ROTL64(v, n) ((uint64_t)((v) << (n)) | ((v) >> (64 - (n))))
#define ROTR64(v, n) ((uint64_t)((v) >> (n)) | ((v) << (64 - (n))))

static void BalletGenRK_128_128(uint8_t       Rk[4 * 4 * 46],
                                const uint8_t K[16],
                                int           enc)
{
    uint64_t  i;
    uint64_t  k0, k1;
    uint64_t *p = (uint64_t *)Rk;
    k0          = *((const uint64_t *)K);
    k1          = *((const uint64_t *)(K + 8));
    k0          = SWAP64(k0);
    k1          = SWAP64(k1);
    if (enc)
    {
        for (i = 0; i < RoundBallet128128; i++)
        {
            if (i % 2 == 0)
            {
                *p = k0;
                k0 ^= ROTL64(k1, 3) ^ ROTL64(k1, 5) ^ i;
            }
            else
            {
                *p = k1;
                k1 ^= ROTL64(k0, 3) ^ ROTL64(k0, 5) ^ (i);
            }
            p++;
        }
    }
    else
    {
        p += RoundBallet128128 - 1;
        for (i = 0; i < RoundBallet128128; i++)
        {
            if (i % 2 == 0)
            {
                *p = k0;
                k0 ^= ROTL64(k1, 3) ^ ROTL64(k1, 5) ^ i;
            }
            else
            {
                *p = k1;
                k1 ^= ROTL64(k0, 3) ^ ROTL64(k0, 5) ^ (i);
            }
            p--;
        }
    }
}

static void Ballet128128EncDataS(uint8_t       out[16],
                                 const uint8_t in[16],
                                 const uint8_t rk[4 * 4 * 46])
{
    int             i;
    uint32_t        t0;
    const uint32_t *trk = (const uint32_t *)rk;
    uint32_t        a   = *((const uint32_t *)in);
    uint32_t        b   = *((const uint32_t *)(in + 4));
    uint32_t        c   = *((const uint32_t *)(in + 8));
    uint32_t        d   = *((const uint32_t *)(in + 12));

    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);
    for (i = 0; i < RoundBallet128128; i += 2)
    {
        t0 = b ^ c;
        b ^= (*(trk + 1));
        c ^= (*trk);
        d = ROTL32(d, 15);
        a = ROTL32(a, 6);
        a += ROTL32(t0, 9);
        d += ROTL32(t0, 14);
        trk += 2;

        t0 = a ^ d;
        b  = ROTL32(b, 6);
        b += ROTL32(t0, 9);
        d ^= (*(trk));
        a ^= (*(trk + 1));
        c = ROTL32(c, 15);
        c += ROTL32(t0, 14);

        trk += 2;
    }
    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);

    *((uint32_t *)out)        = b;
    *((uint32_t *)(out + 4))  = a;
    *((uint32_t *)(out + 8))  = d;
    *((uint32_t *)(out + 12)) = c;
}

static void Ballet128128DecDataS(uint8_t       out[16],
                                 const uint8_t in[16],
                                 const uint8_t rk[4 * 4 * 46])
{
    int             i;
    uint32_t        t0;
    const uint32_t *trk = (const uint32_t *)rk;
    uint32_t        a   = *((uint32_t *)in);
    uint32_t        b   = *((uint32_t *)(in + 4));
    uint32_t        c   = *((uint32_t *)(in + 8));
    uint32_t        d   = *((uint32_t *)(in + 12));

    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);
    for (i = 0; i < RoundBallet128128; i += 2)
    {
        b ^= (*(trk + 1));
        c ^= (*trk);
        t0 = b ^ c;
        a -= ROTL32(t0, 9);
        d -= ROTL32(t0, 14);
        a = ROTL32(a, 32 - 6);
        d = ROTL32(d, 32 - 15);
        trk += 2;
        a ^= (*(trk + 1));
        d ^= (*(trk));
        t0 = a ^ d;
        b -= ROTL32(t0, 9);
        c -= ROTL32(t0, 14);
        b = ROTL32(b, 32 - 6);
        c = ROTL32(c, 32 - 15);
        trk += 2;
    }
    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);

    *((uint32_t *)out)        = b;
    *((uint32_t *)(out + 4))  = a;
    *((uint32_t *)(out + 8))  = d;
    *((uint32_t *)(out + 12)) = c;
}

static void BalletGenRK_128_256(uint8_t       Rk[4 * 4 * 48],
                                const uint8_t K[32],
                                int           enc)
{
    uint64_t  i;
    uint64_t  k0, k1, t0, t1;
    uint64_t *p = (uint64_t *)Rk;
    k0          = *((const uint64_t *)K);
    k1          = *((const uint64_t *)(K + 8));
    t0          = *((const uint64_t *)(K + 16));
    t1          = *((const uint64_t *)(K + 24));
    k0          = SWAP64(k0);
    k1          = SWAP64(k1);
    t0          = SWAP64(t0);
    t1          = SWAP64(t1);
    if (enc)
    {
        for (i = 0; i < RoundBallet128256; i++)
        {
            if (i % 2 == 0)
            {
                *p = k0;
                t0 ^= ROTL64(t1, 7) ^ ROTL64(t1, 17);
                k0 ^= ROTL64(k1, 3) ^ ROTL64(k1, 5);
                k0 ^= t0 ^ i;
            }
            else
            {
                *(p) = k1;
                t1 ^= ROTL64(t0, 7) ^ ROTL64(t0, 17);
                k1 ^= ROTL64(k0, 3) ^ ROTL64(k0, 5);
                k1 ^= t1 ^ (i);
            }
            p++;
        }
    }
    else
    {
        p += RoundBallet128256 - 1;
        for (i = 0; i < RoundBallet128256; i++)
        {
            if (i % 2 == 0)
            {
                *p = k0;
                t0 ^= ROTL64(t1, 7) ^ ROTL64(t1, 17);
                k0 ^= ROTL64(k1, 3) ^ ROTL64(k1, 5);
                k0 ^= t0 ^ i;
            }
            else
            {
                *(p) = k1;
                t1 ^= ROTL64(t0, 7) ^ ROTL64(t0, 17);
                k1 ^= ROTL64(k0, 3) ^ ROTL64(k0, 5);
                k1 ^= t1 ^ (i);
            }
            p--;
        }
    }
}

static void Ballet128256EncDataS(uint8_t       out[16],
                                 const uint8_t in[16],
                                 const uint8_t rk[4 * 4 * 48])
{
    int             i;
    uint32_t        t0;
    const uint32_t *trk = (const uint32_t *)rk;
    uint32_t        a   = *((const uint32_t *)in);
    uint32_t        b   = *((const uint32_t *)(in + 4));
    uint32_t        c   = *((const uint32_t *)(in + 8));
    uint32_t        d   = *((const uint32_t *)(in + 12));

    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);
    for (i = 0; i < RoundBallet128256; i++)
    {
        if (i % 2 == 0)
        {
            t0 = b ^ c;
            b ^= (*(trk + 1));
            c ^= (*trk);
            d = ROTL32(d, 15);
            a = ROTL32(a, 6);
            a += ROTL32(t0, 9);
            d += ROTL32(t0, 14);
        }
        else
        {
            t0 = a ^ d;
            b  = ROTL32(b, 6);
            b += ROTL32(t0, 9);
            d ^= (*(trk));
            a ^= (*(trk + 1));
            c = ROTL32(c, 15);
            c += ROTL32(t0, 14);
        }
        trk += 2;
    }
    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);

    *((uint32_t *)out)        = b;
    *((uint32_t *)(out + 4))  = a;
    *((uint32_t *)(out + 8))  = d;
    *((uint32_t *)(out + 12)) = c;
}

static void Ballet128256DecDataS(uint8_t       out[16],
                                 const uint8_t in[16],
                                 const uint8_t rk[4 * 4 * 48])
{
    int             i;
    uint32_t        t0;
    const uint32_t *trk = (const uint32_t *)rk;
    uint32_t        a   = *((const uint32_t *)in);
    uint32_t        b   = *((const uint32_t *)(in + 4));
    uint32_t        c   = *((const uint32_t *)(in + 8));
    uint32_t        d   = *((const uint32_t *)(in + 12));

    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);
    for (i = 0; i < RoundBallet128256; i++)
    {
        if (i % 2 == 0)
        {
            b ^= (*(trk + 1));
            c ^= (*trk);
            t0 = b ^ c;
            a -= ROTL32(t0, 9);
            d -= ROTL32(t0, 14);
            a = ROTL32(a, 32 - 6);
            d = ROTL32(d, 32 - 15);
        }
        else
        {
            a ^= (*(trk + 1));
            d ^= (*(trk));
            t0 = a ^ d;
            b -= ROTL32(t0, 9);
            c -= ROTL32(t0, 14);
            b = ROTL32(b, 32 - 6);
            c = ROTL32(c, 32 - 15);
        }
        trk += 2;
    }
    a = SWAP32(a);
    b = SWAP32(b);
    c = SWAP32(c);
    d = SWAP32(d);

    *((uint32_t *)out)        = b;
    *((uint32_t *)(out + 4))  = a;
    *((uint32_t *)(out + 8))  = d;
    *((uint32_t *)(out + 12)) = c;
}

static void BalletGenRK_256_256(uint8_t       Rk[4 * 4 * 74],
                                const uint8_t K[32],
                                int           enc)
{
    uint64_t  i;
    uint64_t  k00, k01, k10, k11;
    uint64_t *p = (uint64_t *)Rk;
    k01         = *((const uint64_t *)K);
    k00         = *((const uint64_t *)(K + 8));
    k11         = *((const uint64_t *)(K + 16));
    k10         = *((const uint64_t *)(K + 24));

    k00 = SWAP64(k00);
    k01 = SWAP64(k01);
    k10 = SWAP64(k10);
    k11 = SWAP64(k11);
    if (enc)
    {
        for (i = 0; i < RoundBallet256256; i += 2)
        {
            *p       = k00;
            *(p + 1) = k01;
            k00 ^= ((k10 << 3) | (k11 >> 61)) ^ ((k10 << 5) | (k11 >> 59)) ^ i;
            k01 ^= ((k11 << 3) | (k10 >> 61)) ^ ((k11 << 5) | (k10 >> 59));
            *(p + 2) = k10;
            *(p + 3) = k11;
            k10 ^= ((k00 << 3) | (k01 >> 61)) ^ ((k00 << 5) | (k01 >> 59)) ^
                   (i + 1);
            k11 ^= ((k01 << 3) | (k00 >> 61)) ^ ((k01 << 5) | (k00 >> 59));
            p += 4;
        }
    }
    else
    {
        p += (RoundBallet256256 * 2 - 1);
        for (i = 0; i < RoundBallet256256; i += 2)
        {
            *(p - 1) = k00;
            *(p)     = k01;
            k00 ^= ((k10 << 3) | (k11 >> 61)) ^ ((k10 << 5) | (k11 >> 59)) ^ i;
            k01 ^= ((k11 << 3) | (k10 >> 61)) ^ ((k11 << 5) | (k10 >> 59));
            *(p - 3) = k10;
            *(p - 2) = k11;
            k10 ^= ((k00 << 3) | (k01 >> 61)) ^ ((k00 << 5) | (k01 >> 59)) ^
                   (i + 1);
            k11 ^= ((k01 << 3) | (k00 >> 61)) ^ ((k01 << 5) | (k00 >> 59));
            p -= 4;
        }
    }
}

static void Ballet256256EncDataS(uint8_t       out[32],
                                 const uint8_t in[32],
                                 const uint8_t rk[4 * 4 * 74])
{
    int             i;
    uint64_t        t0;
    const uint64_t *trk = (const uint64_t *)rk;
    uint64_t        a   = *((const uint64_t *)in);
    uint64_t        b   = *((const uint64_t *)(in + 8));
    uint64_t        c   = *((const uint64_t *)(in + 16));
    uint64_t        d   = *((const uint64_t *)(in + 24));

    a = SWAP64(a);
    b = SWAP64(b);
    c = SWAP64(c);
    d = SWAP64(d);

    for (i = 0; i < RoundBallet256256; i++)
    {
        if (i % 2 == 0)
        {
            t0 = b ^ c;
            b ^= (*(trk + 1));
            c ^= (*trk);
            d = ROTL64(d, 15);
            a = ROTL64(a, 6);
            a += ROTL64(t0, 9);
            d += ROTL64(t0, 14);
        }
        else
        {
            t0 = a ^ d;
            b  = ROTL64(b, 6);
            b += ROTL64(t0, 9);
            d ^= (*(trk));
            a ^= (*(trk + 1));
            c = ROTL64(c, 15);
            c += ROTL64(t0, 14);
        }
        trk += 2;
    }
    a = SWAP64(a);
    b = SWAP64(b);
    c = SWAP64(c);
    d = SWAP64(d);

    *((uint64_t *)out)        = b;
    *((uint64_t *)(out + 8))  = a;
    *((uint64_t *)(out + 16)) = d;
    *((uint64_t *)(out + 24)) = c;
}

static void Ballet256256DecDataS(uint8_t       out[32],
                                 const uint8_t in[32],
                                 const uint8_t rk[4 * 4 * 74])
{
    int             i;
    uint64_t        t0;
    const uint64_t *trk = (const uint64_t *)rk;
    uint64_t        a   = *((const uint64_t *)in);
    uint64_t        b   = *((const uint64_t *)(in + 8));
    uint64_t        c   = *((const uint64_t *)(in + 16));
    uint64_t        d   = *((const uint64_t *)(in + 24));

    a = SWAP64(a);
    b = SWAP64(b);
    c = SWAP64(c);
    d = SWAP64(d);
    for (i = 0; i < RoundBallet256256; i++)
    {
        if (i % 2 == 0)
        {
            b ^= (*(trk + 1));
            c ^= (*trk);
            t0 = b ^ c;
            a -= ROTL64(t0, 9);
            d -= ROTL64(t0, 14);
            a = ROTR64(a, 6);
            d = ROTR64(d, 15);
        }
        else
        {
            a ^= (*(trk + 1));
            d ^= (*(trk));
            t0 = a ^ d;
            b -= ROTL64(t0, 9);
            c -= ROTL64(t0, 14);
            b = ROTR64(b, 6);
            c = ROTR64(c, 15);
        }
        trk += 2;
    }

    a = SWAP64(a);
    b = SWAP64(b);
    c = SWAP64(c);
    d = SWAP64(d);

    *((uint64_t *)out)        = b;
    *((uint64_t *)(out + 8))  = a;
    *((uint64_t *)(out + 16)) = d;
    *((uint64_t *)(out + 24)) = c;
}

/**
 * Ending here, to the previous similar comment declaration.
 *
 * the code is "derived from
 * https://sfjs.cacrnet.org.cn/site/term/list_76_1.html"
 *
 * CUI T T, WANG M Q, FAN Y H, HU K, FU Y, HUANG L N. Ballet: A
 * software-friendly block cipher [J]. Journal of Cryptologic Research, 2019,
 * 6(6): 704-712.
 */

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************* BALLET CIPHER API ******************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

// ****************************************
// ********** Ballet 128/128 **************
// ****************************************
void ballet128128_enc_key_init(std::uint8_t       sub_key[4 * 4 * 46],
                               const std::uint8_t user_key[16]) noexcept
{
    BalletGenRK_128_128(sub_key, user_key, 1);
}

void ballet128128_dec_key_init(std::uint8_t       sub_key[4 * 4 * 46],
                               const std::uint8_t user_key[16]) noexcept
{
    BalletGenRK_128_128(sub_key, user_key, 0);
}

void ballet128128_enc_block(const std::uint8_t sub_key[4 * 4 * 46],
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept
{
    Ballet128128EncDataS(ciphertext, plaintext, sub_key);
}

void ballet128128_dec_block(const std::uint8_t sub_key[4 * 4 * 46],
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept
{
    Ballet128128DecDataS(plaintext, ciphertext, sub_key);
}

void ballet128128_enc_blocks(const std::uint8_t  sub_key[4 * 4 * 46],
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        Ballet128128EncDataS(ciphertext, plaintext, sub_key);
        ciphertext += 16, plaintext += 16, block_num--;
    }
}

void ballet128128_dec_blocks(const std::uint8_t  sub_key[4 * 4 * 46],
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        Ballet128128DecDataS(plaintext, ciphertext, sub_key);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** Ballet 128/256 **************
// ****************************************

void ballet128256_enc_key_init(std::uint8_t       sub_key[4 * 4 * 48],
                               const std::uint8_t user_key[32]) noexcept
{
    BalletGenRK_128_256(sub_key, user_key, 1);
}

void ballet128256_dec_key_init(std::uint8_t       sub_key[4 * 4 * 48],
                               const std::uint8_t user_key[32]) noexcept
{
    BalletGenRK_128_256(sub_key, user_key, 0);
}

void ballet128256_enc_block(const std::uint8_t sub_key[4 * 4 * 48],
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept
{
    Ballet128256EncDataS(ciphertext, plaintext, sub_key);
}

void ballet128256_dec_block(const std::uint8_t sub_key[4 * 4 * 48],
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept
{
    Ballet128256DecDataS(plaintext, ciphertext, sub_key);
}

void ballet128256_enc_blocks(const std::uint8_t  sub_key[4 * 4 * 48],
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        Ballet128256EncDataS(ciphertext, plaintext, sub_key);
        ciphertext += 16, plaintext += 16, block_num--;
    }
}

void ballet128256_dec_blocks(const std::uint8_t  sub_key[4 * 4 * 48],
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        Ballet128256DecDataS(plaintext, ciphertext, sub_key);
        plaintext += 16, ciphertext += 16, block_num--;
    }
}

// ****************************************
// ********** Ballet 256/256 **************
// ****************************************

void ballet256256_enc_key_init(std::uint8_t       sub_key[4 * 4 * 74],
                               const std::uint8_t user_key[32]) noexcept
{
    BalletGenRK_256_256(sub_key, user_key, 1);
}

void ballet256256_dec_key_init(std::uint8_t       sub_key[4 * 4 * 74],
                               const std::uint8_t user_key[32]) noexcept
{
    BalletGenRK_256_256(sub_key, user_key, 0);
}

void ballet256256_enc_block(const std::uint8_t sub_key[4 * 4 * 74],
                            std::uint8_t       ciphertext[32],
                            const std::uint8_t plaintext[32]) noexcept
{
    Ballet256256EncDataS(ciphertext, plaintext, sub_key);
}

void ballet256256_dec_block(const std::uint8_t sub_key[4 * 4 * 74],
                            std::uint8_t       plaintext[32],
                            const std::uint8_t ciphertext[32]) noexcept
{
    Ballet256256DecDataS(plaintext, ciphertext, sub_key);
}

void ballet256256_enc_blocks(const std::uint8_t  sub_key[4 * 4 * 74],
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        Ballet256256EncDataS(ciphertext, plaintext, sub_key);
        ciphertext += 32, plaintext += 32, block_num--;
    }
}

void ballet256256_dec_blocks(const std::uint8_t  sub_key[4 * 4 * 74],
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept
{
    while (block_num)
    {
        Ballet256256DecDataS(plaintext, ciphertext, sub_key);
        plaintext += 32, ciphertext += 32, block_num--;
    }
}

}; // namespace ballet::internal::standard
