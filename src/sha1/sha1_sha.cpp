#if defined(SUPPORT_SHA1_SHA)

/**
 * part of the code is "derived from miTLS project. sha1-x86.c"
 *
 * https://github.com/noloader/SHA-Intrinsics/blob/master/sha1-x86.c
 *
 * sha1-x86.c - Intel SHA extensions using C intrinsics
 * Written and place in public domain by Jeffrey Walton
 * Based on code from Intel, and by Sean Gulley for
 * the miTLS project.
 */
#include "sha1_sha.h"

#include <immintrin.h>

#include <cstring>

#define MEM_LOAD32BE(src)                                  \
    (((std::uint32_t)(((std::uint8_t *)(src))[0]) << 24) | \
     ((std::uint32_t)(((std::uint8_t *)(src))[1]) << 16) | \
     ((std::uint32_t)(((std::uint8_t *)(src))[2]) << 8) |  \
     ((std::uint32_t)(((std::uint8_t *)(src))[3]) << 0))

#define MEM_STORE32BE(dst, a)                                        \
    (((std::uint8_t *)(dst))[0] = ((std::uint32_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t *)(dst))[1] = ((std::uint32_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t *)(dst))[2] = ((std::uint32_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t *)(dst))[3] = ((std::uint32_t)(a) >> 0) & 0xFF)

#define MEM_STORE64BE(dst, a)                                        \
    (((std::uint8_t *)(dst))[0] = ((std::uint64_t)(a) >> 56) & 0xFF, \
     ((std::uint8_t *)(dst))[1] = ((std::uint64_t)(a) >> 48) & 0xFF, \
     ((std::uint8_t *)(dst))[2] = ((std::uint64_t)(a) >> 40) & 0xFF, \
     ((std::uint8_t *)(dst))[3] = ((std::uint64_t)(a) >> 32) & 0xFF, \
     ((std::uint8_t *)(dst))[4] = ((std::uint64_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t *)(dst))[5] = ((std::uint64_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t *)(dst))[6] = ((std::uint64_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t *)(dst))[7] = ((std::uint64_t)(a) >> 0) & 0xFF)

namespace sha1::internal::sha {

/**
 * Starting from here, until the next similar comment declaration.
 *
 * part of the code is "derived from miTLS project. sha1-x86.c"
 *
 * https://github.com/noloader/SHA-Intrinsics/blob/master/sha1-x86.c
 */

static void sha1_compress_block(std::uint32_t      state[5],
                                const std::uint8_t data[64]) noexcept
{
    __m128i       ABCD, ABCD_SAVE, E0, E0_SAVE, E1;
    __m128i       MSG0, MSG1, MSG2, MSG3;
    const __m128i MASK =
        _mm_set_epi64x(0x0001020304050607ULL, 0x08090a0b0c0d0e0fULL);

    /* Load initial values */
    ABCD = _mm_loadu_si128((const __m128i *)state);
    E0   = _mm_set_epi32(state[4], 0, 0, 0);
    ABCD = _mm_shuffle_epi32(ABCD, 0x1B);

    /* Save current state  */
    ABCD_SAVE = ABCD;
    E0_SAVE   = E0;

    /* Rounds 0-3 */
    MSG0 = _mm_loadu_si128((const __m128i *)(data + 0));
    MSG0 = _mm_shuffle_epi8(MSG0, MASK);
    E0   = _mm_add_epi32(E0, MSG0);
    E1   = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);

    /* Rounds 4-7 */
    MSG1 = _mm_loadu_si128((const __m128i *)(data + 16));
    MSG1 = _mm_shuffle_epi8(MSG1, MASK);
    E1   = _mm_sha1nexte_epu32(E1, MSG1);
    E0   = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);

    /* Rounds 8-11 */
    MSG2 = _mm_loadu_si128((const __m128i *)(data + 32));
    MSG2 = _mm_shuffle_epi8(MSG2, MASK);
    E0   = _mm_sha1nexte_epu32(E0, MSG2);
    E1   = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 = _mm_xor_si128(MSG0, MSG2);

    /* Rounds 12-15 */
    MSG3 = _mm_loadu_si128((const __m128i *)(data + 48));
    MSG3 = _mm_shuffle_epi8(MSG3, MASK);
    E1   = _mm_sha1nexte_epu32(E1, MSG3);
    E0   = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 0);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 = _mm_xor_si128(MSG1, MSG3);

    /* Rounds 16-19 */
    E0   = _mm_sha1nexte_epu32(E0, MSG0);
    E1   = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 0);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 = _mm_xor_si128(MSG2, MSG0);

    /* Rounds 20-23 */
    E1   = _mm_sha1nexte_epu32(E1, MSG1);
    E0   = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 = _mm_xor_si128(MSG3, MSG1);

    /* Rounds 24-27 */
    E0   = _mm_sha1nexte_epu32(E0, MSG2);
    E1   = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 = _mm_xor_si128(MSG0, MSG2);

    /* Rounds 28-31 */
    E1   = _mm_sha1nexte_epu32(E1, MSG3);
    E0   = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 = _mm_xor_si128(MSG1, MSG3);

    /* Rounds 32-35 */
    E0   = _mm_sha1nexte_epu32(E0, MSG0);
    E1   = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 1);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 = _mm_xor_si128(MSG2, MSG0);

    /* Rounds 36-39 */
    E1   = _mm_sha1nexte_epu32(E1, MSG1);
    E0   = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 1);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 = _mm_xor_si128(MSG3, MSG1);

    /* Rounds 40-43 */
    E0   = _mm_sha1nexte_epu32(E0, MSG2);
    E1   = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 = _mm_xor_si128(MSG0, MSG2);

    /* Rounds 44-47 */
    E1   = _mm_sha1nexte_epu32(E1, MSG3);
    E0   = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 = _mm_xor_si128(MSG1, MSG3);

    /* Rounds 48-51 */
    E0   = _mm_sha1nexte_epu32(E0, MSG0);
    E1   = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 = _mm_xor_si128(MSG2, MSG0);

    /* Rounds 52-55 */
    E1   = _mm_sha1nexte_epu32(E1, MSG1);
    E0   = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 2);
    MSG0 = _mm_sha1msg1_epu32(MSG0, MSG1);
    MSG3 = _mm_xor_si128(MSG3, MSG1);

    /* Rounds 56-59 */
    E0   = _mm_sha1nexte_epu32(E0, MSG2);
    E1   = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 2);
    MSG1 = _mm_sha1msg1_epu32(MSG1, MSG2);
    MSG0 = _mm_xor_si128(MSG0, MSG2);

    /* Rounds 60-63 */
    E1   = _mm_sha1nexte_epu32(E1, MSG3);
    E0   = ABCD;
    MSG0 = _mm_sha1msg2_epu32(MSG0, MSG3);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG2 = _mm_sha1msg1_epu32(MSG2, MSG3);
    MSG1 = _mm_xor_si128(MSG1, MSG3);

    /* Rounds 64-67 */
    E0   = _mm_sha1nexte_epu32(E0, MSG0);
    E1   = ABCD;
    MSG1 = _mm_sha1msg2_epu32(MSG1, MSG0);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);
    MSG3 = _mm_sha1msg1_epu32(MSG3, MSG0);
    MSG2 = _mm_xor_si128(MSG2, MSG0);

    /* Rounds 68-71 */
    E1   = _mm_sha1nexte_epu32(E1, MSG1);
    E0   = ABCD;
    MSG2 = _mm_sha1msg2_epu32(MSG2, MSG1);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);
    MSG3 = _mm_xor_si128(MSG3, MSG1);

    /* Rounds 72-75 */
    E0   = _mm_sha1nexte_epu32(E0, MSG2);
    E1   = ABCD;
    MSG3 = _mm_sha1msg2_epu32(MSG3, MSG2);
    ABCD = _mm_sha1rnds4_epu32(ABCD, E0, 3);

    /* Rounds 76-79 */
    E1   = _mm_sha1nexte_epu32(E1, MSG3);
    E0   = ABCD;
    ABCD = _mm_sha1rnds4_epu32(ABCD, E1, 3);

    /* Combine state */
    E0   = _mm_sha1nexte_epu32(E0, E0_SAVE);
    ABCD = _mm_add_epi32(ABCD, ABCD_SAVE);

    /* Save state */
    ABCD = _mm_shuffle_epi32(ABCD, 0x1B);
    _mm_storeu_si128((__m128i *)state, ABCD);
    state[4] = _mm_extract_epi32(E0, 3);
}

/**
 * Ending here, to the previous similar comment declaration.
 *
 * part of the code is "derived from miTLS project. sha1-x86.c"
 *
 * https://github.com/noloader/SHA-Intrinsics/blob/master/sha1-x86.c
 */

void sha1_init(std::uint32_t state[5], std::uint64_t *data_bits) noexcept
{
    static const uint32_t SHA1_INIT_DIGEST[5] = {
        0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0,
    };
    state[0]   = SHA1_INIT_DIGEST[0];
    state[1]   = SHA1_INIT_DIGEST[1];
    state[2]   = SHA1_INIT_DIGEST[2];
    state[3]   = SHA1_INIT_DIGEST[3];
    state[4]   = SHA1_INIT_DIGEST[4];
    *data_bits = 0;
}

void sha1_reset(std::uint32_t state[5], std::uint64_t *data_bits) noexcept
{
    sha1_init(state, data_bits);
}

int sha1_update_blocks(std::uint32_t       state[5],
                       std::uint64_t      *data_bits,
                       const std::uint8_t *in,
                       std::size_t         block_num) noexcept
{
    if (block_num > UINT64_MAX / 512)
    {
        return -1;
    }
    std::uint64_t nxt_bits = block_num * 512 + *data_bits;
    if (nxt_bits < *data_bits)
    {
        return -1;
    }
    *data_bits = nxt_bits;
    while (block_num)
    {
        sha1_compress_block(state, in);
        in += 64, block_num -= 1;
    }
    return 0;
}

int sha1_final_block(std::uint32_t       state[5],
                     std::uint64_t      *data_bits,
                     std::uint8_t        digest[32],
                     const std::uint8_t *in,
                     std::size_t         inl) noexcept
{
    std::uint64_t nxt_bits = inl * 8 + *data_bits;
    if (nxt_bits < *data_bits)
    {
        return -1;
    }
    *data_bits = nxt_bits;

    size_t  pad_num = (64ULL + 56 - 1 - inl) % 64;
    uint8_t buf[64 * 2];
    size_t  buf_size = 0;
    std::memcpy(buf, in, inl);
    buf_size += inl;                           // update
    buf[buf_size] = 0x80;                      // 10..0
    buf_size += 1;                             // update
    std::memset(buf + buf_size, 0, pad_num);   // pad 0
    buf_size += pad_num;                       // update
    MEM_STORE64BE(buf + buf_size, *data_bits); //
    buf_size += 8;                             // update
    // compress
    for (std::size_t i = 0; i < buf_size; i += 64)
    {
        sha1_compress_block(state, buf + i);
    }
    // output digest
    MEM_STORE32BE(digest + 4 * 0, state[0]);
    MEM_STORE32BE(digest + 4 * 1, state[1]);
    MEM_STORE32BE(digest + 4 * 2, state[2]);
    MEM_STORE32BE(digest + 4 * 3, state[3]);
    MEM_STORE32BE(digest + 4 * 4, state[4]);

    return 0;
}

} // namespace sha1::internal::sha
#endif
