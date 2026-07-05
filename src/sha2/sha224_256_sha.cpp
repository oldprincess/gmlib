#if defined(SUPPORT_SHA2_SHA)

#include "sha224_256_sha.h"

#include <immintrin.h>

#include <cstring>

namespace sha2 {
namespace internal {
namespace sha {

#define MEM_LOAD32BE(src)                                 \
    (((std::uint32_t)(((std::uint8_t*)(src))[0]) << 24) | \
     ((std::uint32_t)(((std::uint8_t*)(src))[1]) << 16) | \
     ((std::uint32_t)(((std::uint8_t*)(src))[2]) << 8) |  \
     ((std::uint32_t)(((std::uint8_t*)(src))[3]) << 0))

#define MEM_STORE32BE(dst, a)                                       \
    (((std::uint8_t*)(dst))[0] = ((std::uint32_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t*)(dst))[1] = ((std::uint32_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t*)(dst))[2] = ((std::uint32_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t*)(dst))[3] = ((std::uint32_t)(a) >> 0) & 0xFF)

#define MEM_LOAD64BE(src)                                 \
    (((std::uint64_t)(((std::uint8_t*)(src))[0]) << 56) | \
     ((std::uint64_t)(((std::uint8_t*)(src))[1]) << 48) | \
     ((std::uint64_t)(((std::uint8_t*)(src))[2]) << 40) | \
     ((std::uint64_t)(((std::uint8_t*)(src))[3]) << 32) | \
     ((std::uint64_t)(((std::uint8_t*)(src))[4]) << 24) | \
     ((std::uint64_t)(((std::uint8_t*)(src))[5]) << 16) | \
     ((std::uint64_t)(((std::uint8_t*)(src))[6]) << 8) |  \
     ((std::uint64_t)(((std::uint8_t*)(src))[7]) << 0))

#define MEM_STORE64BE(dst, a)                                       \
    (((std::uint8_t*)(dst))[0] = ((std::uint64_t)(a) >> 56) & 0xFF, \
     ((std::uint8_t*)(dst))[1] = ((std::uint64_t)(a) >> 48) & 0xFF, \
     ((std::uint8_t*)(dst))[2] = ((std::uint64_t)(a) >> 40) & 0xFF, \
     ((std::uint8_t*)(dst))[3] = ((std::uint64_t)(a) >> 32) & 0xFF, \
     ((std::uint8_t*)(dst))[4] = ((std::uint64_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t*)(dst))[5] = ((std::uint64_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t*)(dst))[6] = ((std::uint64_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t*)(dst))[7] = ((std::uint64_t)(a) >> 0) & 0xFF)

/**
 * Starting from here, until the next similar comment declaration.
 *
 * part of the code is "derived from miTLS project. sha256-x86.c"
 *
 * https://github.com/noloader/SHA-Intrinsics/blob/master/sha256-x86.c
 */

static void sha224_256_compress_block(std::uint32_t      state[8],
                                      const std::uint8_t in[64])
{
    __m128i       STATE0, STATE1;
    __m128i       MSG, TMP;
    __m128i       MSG0, MSG1, MSG2, MSG3;
    __m128i       ABEF_SAVE, CDGH_SAVE;
    const __m128i MASK = _mm_set_epi64x( //
        0x0c0d0e0f08090a0bULL,           //
        0x0405060700010203ULL            //
    );                                   //

    /* Load initial values */
    TMP    = _mm_loadu_si128((const __m128i*)&state[0]);
    STATE1 = _mm_loadu_si128((const __m128i*)&state[4]);

    TMP    = _mm_shuffle_epi32(TMP, 0xB1);       /* CDAB */
    STATE1 = _mm_shuffle_epi32(STATE1, 0x1B);    /* EFGH */
    STATE0 = _mm_alignr_epi8(TMP, STATE1, 8);    /* ABEF */
    STATE1 = _mm_blend_epi16(STATE1, TMP, 0xF0); /* CDGH */

    /* Save current state */
    ABEF_SAVE = STATE0;
    CDGH_SAVE = STATE1;

    /* Rounds 0-3 */
    MSG  = _mm_loadu_si128((const __m128i*)(in + 0));
    MSG0 = _mm_shuffle_epi8(MSG, MASK);
    MSG  = _mm_add_epi32(
        MSG0, _mm_set_epi64x(0xE9B5DBA5B5C0FBCFULL, 0x71374491428A2F98ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

    /* Rounds 4-7 */
    MSG1 = _mm_loadu_si128((const __m128i*)(in + 16));
    MSG1 = _mm_shuffle_epi8(MSG1, MASK);
    MSG  = _mm_add_epi32(
        MSG1, _mm_set_epi64x(0xAB1C5ED5923F82A4ULL, 0x59F111F13956C25BULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG0   = _mm_sha256msg1_epu32(MSG0, MSG1);

    /* Rounds 8-11 */
    MSG2 = _mm_loadu_si128((const __m128i*)(in + 32));
    MSG2 = _mm_shuffle_epi8(MSG2, MASK);
    MSG  = _mm_add_epi32(
        MSG2, _mm_set_epi64x(0x550C7DC3243185BEULL, 0x12835B01D807AA98ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG1   = _mm_sha256msg1_epu32(MSG1, MSG2);

    /* Rounds 12-15 */
    MSG3 = _mm_loadu_si128((const __m128i*)(in + 48));
    MSG3 = _mm_shuffle_epi8(MSG3, MASK);
    MSG  = _mm_add_epi32(
        MSG3, _mm_set_epi64x(0xC19BF1749BDC06A7ULL, 0x80DEB1FE72BE5D74ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG3, MSG2, 4);
    MSG0   = _mm_add_epi32(MSG0, TMP);
    MSG0   = _mm_sha256msg2_epu32(MSG0, MSG3);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG2   = _mm_sha256msg1_epu32(MSG2, MSG3);

    /* Rounds 16-19 */
    MSG = _mm_add_epi32(
        MSG0, _mm_set_epi64x(0x240CA1CC0FC19DC6ULL, 0xEFBE4786E49B69C1ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG0, MSG3, 4);
    MSG1   = _mm_add_epi32(MSG1, TMP);
    MSG1   = _mm_sha256msg2_epu32(MSG1, MSG0);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG3   = _mm_sha256msg1_epu32(MSG3, MSG0);

    /* Rounds 20-23 */
    MSG = _mm_add_epi32(
        MSG1, _mm_set_epi64x(0x76F988DA5CB0A9DCULL, 0x4A7484AA2DE92C6FULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG1, MSG0, 4);
    MSG2   = _mm_add_epi32(MSG2, TMP);
    MSG2   = _mm_sha256msg2_epu32(MSG2, MSG1);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG0   = _mm_sha256msg1_epu32(MSG0, MSG1);

    /* Rounds 24-27 */
    MSG = _mm_add_epi32(
        MSG2, _mm_set_epi64x(0xBF597FC7B00327C8ULL, 0xA831C66D983E5152ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG2, MSG1, 4);
    MSG3   = _mm_add_epi32(MSG3, TMP);
    MSG3   = _mm_sha256msg2_epu32(MSG3, MSG2);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG1   = _mm_sha256msg1_epu32(MSG1, MSG2);

    /* Rounds 28-31 */
    MSG = _mm_add_epi32(
        MSG3, _mm_set_epi64x(0x1429296706CA6351ULL, 0xD5A79147C6E00BF3ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG3, MSG2, 4);
    MSG0   = _mm_add_epi32(MSG0, TMP);
    MSG0   = _mm_sha256msg2_epu32(MSG0, MSG3);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG2   = _mm_sha256msg1_epu32(MSG2, MSG3);

    /* Rounds 32-35 */
    MSG = _mm_add_epi32(
        MSG0, _mm_set_epi64x(0x53380D134D2C6DFCULL, 0x2E1B213827B70A85ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG0, MSG3, 4);
    MSG1   = _mm_add_epi32(MSG1, TMP);
    MSG1   = _mm_sha256msg2_epu32(MSG1, MSG0);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG3   = _mm_sha256msg1_epu32(MSG3, MSG0);

    /* Rounds 36-39 */
    MSG = _mm_add_epi32(
        MSG1, _mm_set_epi64x(0x92722C8581C2C92EULL, 0x766A0ABB650A7354ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG1, MSG0, 4);
    MSG2   = _mm_add_epi32(MSG2, TMP);
    MSG2   = _mm_sha256msg2_epu32(MSG2, MSG1);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG0   = _mm_sha256msg1_epu32(MSG0, MSG1);

    /* Rounds 40-43 */
    MSG = _mm_add_epi32(
        MSG2, _mm_set_epi64x(0xC76C51A3C24B8B70ULL, 0xA81A664BA2BFE8A1ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG2, MSG1, 4);
    MSG3   = _mm_add_epi32(MSG3, TMP);
    MSG3   = _mm_sha256msg2_epu32(MSG3, MSG2);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG1   = _mm_sha256msg1_epu32(MSG1, MSG2);

    /* Rounds 44-47 */
    MSG = _mm_add_epi32(
        MSG3, _mm_set_epi64x(0x106AA070F40E3585ULL, 0xD6990624D192E819ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG3, MSG2, 4);
    MSG0   = _mm_add_epi32(MSG0, TMP);
    MSG0   = _mm_sha256msg2_epu32(MSG0, MSG3);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG2   = _mm_sha256msg1_epu32(MSG2, MSG3);

    /* Rounds 48-51 */
    MSG = _mm_add_epi32(
        MSG0, _mm_set_epi64x(0x34B0BCB52748774CULL, 0x1E376C0819A4C116ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG0, MSG3, 4);
    MSG1   = _mm_add_epi32(MSG1, TMP);
    MSG1   = _mm_sha256msg2_epu32(MSG1, MSG0);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);
    MSG3   = _mm_sha256msg1_epu32(MSG3, MSG0);

    /* Rounds 52-55 */
    MSG = _mm_add_epi32(
        MSG1, _mm_set_epi64x(0x682E6FF35B9CCA4FULL, 0x4ED8AA4A391C0CB3ULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG1, MSG0, 4);
    MSG2   = _mm_add_epi32(MSG2, TMP);
    MSG2   = _mm_sha256msg2_epu32(MSG2, MSG1);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

    /* Rounds 56-59 */
    MSG = _mm_add_epi32(
        MSG2, _mm_set_epi64x(0x8CC7020884C87814ULL, 0x78A5636F748F82EEULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    TMP    = _mm_alignr_epi8(MSG2, MSG1, 4);
    MSG3   = _mm_add_epi32(MSG3, TMP);
    MSG3   = _mm_sha256msg2_epu32(MSG3, MSG2);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

    /* Rounds 60-63 */
    MSG = _mm_add_epi32(
        MSG3, _mm_set_epi64x(0xC67178F2BEF9A3F7ULL, 0xA4506CEB90BEFFFAULL));
    STATE1 = _mm_sha256rnds2_epu32(STATE1, STATE0, MSG);
    MSG    = _mm_shuffle_epi32(MSG, 0x0E);
    STATE0 = _mm_sha256rnds2_epu32(STATE0, STATE1, MSG);

    /* Combine state  */
    STATE0 = _mm_add_epi32(STATE0, ABEF_SAVE);
    STATE1 = _mm_add_epi32(STATE1, CDGH_SAVE);

    TMP    = _mm_shuffle_epi32(STATE0, 0x1B);    /* FEBA */
    STATE1 = _mm_shuffle_epi32(STATE1, 0xB1);    /* DCHG */
    STATE0 = _mm_blend_epi16(TMP, STATE1, 0xF0); /* DCBA */
    STATE1 = _mm_alignr_epi8(STATE1, TMP, 8);    /* ABEF */

    /* Save state */
    _mm_storeu_si128((__m128i*)&state[0], STATE0);
    _mm_storeu_si128((__m128i*)&state[4], STATE1);
}

/**
 * Ending here, to the previous similar comment declaration.
 *
 * the code is "derived from IETF Trust and the persons identified as authors of
 * the code. sha224-256.c, sha384-512.c"
 *
 * cite: https://www.rfc-editor.org/rfc/rfc6234#section-8.2.2
 */

static int add_carry_u64(std::uint64_t* self, std::uint64_t other)
{
    std::uint64_t res = *self + other;

    int c = (int)(res < *self);
    *self = res;
    return c;
}

static int sha224_256_update_blocks(std::uint8_t        state[32],
                                    std::uint64_t*      data_bits,
                                    const std::uint8_t* in,
                                    std::size_t         block_num) noexcept
{
    if (block_num > UINT64_MAX / 512)
    {
        return -1;
    }
    if (add_carry_u64(data_bits, block_num * 512))
    {
        return -1;
    }
    while (block_num)
    {
        sha224_256_compress_block((std::uint32_t*)state, in);
        in += 64;
        block_num--;
    }
    return 0;
}

static int sha224_256_final_n(std::uint8_t        state[32],
                              std::uint64_t*      data_bits,
                              std::uint8_t*       digest,
                              std::size_t         digest_size,
                              const std::uint8_t* in,
                              std::size_t         inl)
{
    if (inl > UINT64_MAX / 8)
    {
        return -1;
    }
    if (add_carry_u64(data_bits, inl * 8))
    {
        return -1;
    }

    std::size_t  pad_num = (64ULL + 56 - 1 - inl) % 64;
    std::uint8_t buf[64 * 2];
    std::size_t  buf_size = 0;
    std::memcpy(buf, in, inl);
    buf_size += inl;                           // update
    buf[buf_size] = 0x80;                      // 10..0
    buf_size += 1;                             // update
    std::memset(buf + buf_size, 0, pad_num);   // pad 0
    buf_size += pad_num;                       // update
    MEM_STORE64BE(buf + buf_size, *data_bits); //
    buf_size += 8;                             // update
    // compress
    for (size_t i = 0; i < buf_size; i += 64)
    {
        sha224_256_compress_block((std::uint32_t*)state, buf + i);
    }
    // output digest
    MEM_STORE32BE(buf + 4 * 0, ((std::uint32_t*)state)[0]);
    MEM_STORE32BE(buf + 4 * 1, ((std::uint32_t*)state)[1]);
    MEM_STORE32BE(buf + 4 * 2, ((std::uint32_t*)state)[2]);
    MEM_STORE32BE(buf + 4 * 3, ((std::uint32_t*)state)[3]);
    MEM_STORE32BE(buf + 4 * 4, ((std::uint32_t*)state)[4]);
    MEM_STORE32BE(buf + 4 * 5, ((std::uint32_t*)state)[5]);
    MEM_STORE32BE(buf + 4 * 6, ((std::uint32_t*)state)[6]);
    MEM_STORE32BE(buf + 4 * 7, ((std::uint32_t*)state)[7]);
    std::memcpy(digest, buf, digest_size);
    return 0;
}

void sha224_init(std::uint8_t state[32], std::uint64_t* data_bits) noexcept
{
    static const std::uint32_t SHA224_H0[8] = {
        0xC1059ED8, 0x367CD507, 0x3070DD17, 0xF70E5939,
        0xFFC00B31, 0x68581511, 0x64F98FA7, 0xBEFA4FA4,
    };
    ((std::uint32_t*)state)[0] = SHA224_H0[0];
    ((std::uint32_t*)state)[1] = SHA224_H0[1];
    ((std::uint32_t*)state)[2] = SHA224_H0[2];
    ((std::uint32_t*)state)[3] = SHA224_H0[3];
    ((std::uint32_t*)state)[4] = SHA224_H0[4];
    ((std::uint32_t*)state)[5] = SHA224_H0[5];
    ((std::uint32_t*)state)[6] = SHA224_H0[6];
    ((std::uint32_t*)state)[7] = SHA224_H0[7];
    *data_bits                 = 0;
}

void sha224_reset(std::uint8_t state[32], std::uint64_t* data_bits) noexcept
{
    sha224_init(state, data_bits);
}

int sha224_update_blocks(std::uint8_t        state[32],
                         std::uint64_t*      data_bits,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept
{
    return sha224_256_update_blocks(state, data_bits, in, block_num);
}

int sha224_final_block(std::uint8_t        state[32],
                       std::uint64_t*      data_bits,
                       std::uint8_t        digest[28],
                       const std::uint8_t* in,
                       std::size_t         inl) noexcept
{
    return sha224_256_final_n(state, data_bits, digest, 28, in, inl);
}

void sha256_init(std::uint8_t state[32], std::uint64_t* data_bits) noexcept
{
    static const uint32_t SHA256_H0[8] = {
        0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
        0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19,
    };
    ((std::uint32_t*)state)[0] = SHA256_H0[0];
    ((std::uint32_t*)state)[1] = SHA256_H0[1];
    ((std::uint32_t*)state)[2] = SHA256_H0[2];
    ((std::uint32_t*)state)[3] = SHA256_H0[3];
    ((std::uint32_t*)state)[4] = SHA256_H0[4];
    ((std::uint32_t*)state)[5] = SHA256_H0[5];
    ((std::uint32_t*)state)[6] = SHA256_H0[6];
    ((std::uint32_t*)state)[7] = SHA256_H0[7];
    *data_bits                 = 0;
}

void sha256_reset(std::uint8_t state[32], std::uint64_t* data_bits) noexcept
{
    sha256_init(state, data_bits);
}

int sha256_update_blocks(std::uint8_t        state[32],
                         std::uint64_t*      data_bits,
                         const std::uint8_t* in,
                         std::size_t         block_num) noexcept
{
    return sha224_256_update_blocks(state, data_bits, in, block_num);
}

int sha256_final_block(std::uint8_t        state[32],
                       std::uint64_t*      data_bits,
                       std::uint8_t        digest[32],
                       const std::uint8_t* in,
                       std::size_t         inl) noexcept
{
    return sha224_256_final_n(state, data_bits, digest, 32, in, inl);
}

} // namespace sha
} // namespace internal
} // namespace sha2

#endif
