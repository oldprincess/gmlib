#include "sha1_common.h"

#include <cstring>

#define MEM_LOAD32BE(src)                                       \
    (((std::uint32_t)(((const std::uint8_t*)(src))[0]) << 24) | \
     ((std::uint32_t)(((const std::uint8_t*)(src))[1]) << 16) | \
     ((std::uint32_t)(((const std::uint8_t*)(src))[2]) << 8) |  \
     ((std::uint32_t)(((const std::uint8_t*)(src))[3]) << 0))

#define MEM_STORE32BE(dst, a)                                       \
    (((std::uint8_t*)(dst))[0] = ((std::uint32_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t*)(dst))[1] = ((std::uint32_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t*)(dst))[2] = ((std::uint32_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t*)(dst))[3] = ((std::uint32_t)(a) >> 0) & 0xFF)

#define MEM_STORE64BE(dst, a)                                       \
    (((std::uint8_t*)(dst))[0] = ((std::uint64_t)(a) >> 56) & 0xFF, \
     ((std::uint8_t*)(dst))[1] = ((std::uint64_t)(a) >> 48) & 0xFF, \
     ((std::uint8_t*)(dst))[2] = ((std::uint64_t)(a) >> 40) & 0xFF, \
     ((std::uint8_t*)(dst))[3] = ((std::uint64_t)(a) >> 32) & 0xFF, \
     ((std::uint8_t*)(dst))[4] = ((std::uint64_t)(a) >> 24) & 0xFF, \
     ((std::uint8_t*)(dst))[5] = ((std::uint64_t)(a) >> 16) & 0xFF, \
     ((std::uint8_t*)(dst))[6] = ((std::uint64_t)(a) >> 8) & 0xFF,  \
     ((std::uint8_t*)(dst))[7] = ((std::uint64_t)(a) >> 0) & 0xFF)

#define rotl(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

namespace sha1::internal::common {

static void sha1_compress_block(std::uint32_t      state[5],
                                const std::uint8_t data[64]) noexcept
{
    static const std::uint32_t K[4] = {
        0x5A827999,
        0x6ED9EBA1,
        0x8F1BBCDC,
        0xCA62C1D6,
    };
    std::uint32_t W[80];
    std::uint32_t A, B, C, D, E;
    std::uint32_t temp;

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
    for (int t = 16; t < 80; t++)
    {
        W[t] = rotl(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);
    }

    A = state[0];
    B = state[1];
    C = state[2];
    D = state[3];
    E = state[4];

    for (int t = 0; t < 20; t++)
    {
        temp = rotl(A, 5) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
        E    = D;
        D    = C;
        C    = rotl(B, 30);
        B    = A;
        A    = temp;
    }

    for (int t = 20; t < 40; t++)
    {
        temp = rotl(A, 5) + (B ^ C ^ D) + E + W[t] + K[1];
        E    = D;
        D    = C;
        C    = rotl(B, 30);
        B    = A;
        A    = temp;
    }

    for (int t = 40; t < 60; t++)
    {
        temp = rotl(A, 5) + ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
        E    = D;
        D    = C;
        C    = rotl(B, 30);
        B    = A;
        A    = temp;
    }

    for (int t = 60; t < 80; t++)
    {
        temp = rotl(A, 5) + (B ^ C ^ D) + E + W[t] + K[3];
        E    = D;
        D    = C;
        C    = rotl(B, 30);
        B    = A;
        A    = temp;
    }

    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
    state[4] += E;
}

void sha1_init(std::uint32_t state[5], std::uint64_t* data_bits) noexcept
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

void sha1_reset(std::uint32_t state[5], std::uint64_t* data_bits) noexcept
{
    sha1_init(state, data_bits);
}

int sha1_update_blocks(std::uint32_t       state[5],
                       std::uint64_t*      data_bits,
                       const std::uint8_t* in,
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
                     std::uint64_t*      data_bits,
                     std::uint8_t        digest[32],
                     const std::uint8_t* in,
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

} // namespace sha1::internal::common
