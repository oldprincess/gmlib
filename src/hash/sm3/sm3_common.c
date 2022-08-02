#include "sm3_common.h"
#include <gmlib/utils.h>

#define rotl(x, s) ((x) << (s) | (x) >> (32 - (s)))
#define P0(x) ((x) ^ rotl(x, 9) ^ rotl(x, 17))
#define P1(x) ((x) ^ rotl(x, 15) ^ rotl(x, 23))

static uint32_t FFj(uint32_t x, uint32_t y, uint32_t z, int j) {
    if (j < 16) {
        return x ^ y ^ z;
    } else {
        return (x & y) | (x & z) | (y & z);
    }
}

static uint32_t GGj(uint32_t x, uint32_t y, uint32_t z, int j) {
    if (j < 16) {
        return x ^ y ^ z;
    } else {
        return (x & y) | (~x & z);
    }
}

#define T00 0x79cc4519U
#define T16 0x7a879d8aU

// T[j] = Tj <<< (j mod 32)
static uint32_t T[] = {
    0x79cc4519U, 0xf3988a32U, 0xe7311465U, 0xce6228cbU,  //
    0x9cc45197U, 0x3988a32fU, 0x7311465eU, 0xe6228cbcU,  //
    0xcc451979U, 0x988a32f3U, 0x311465e7U, 0x6228cbceU,  //
    0xc451979cU, 0x88a32f39U, 0x11465e73U, 0x228cbce6U,  //
    0x9d8a7a87U, 0x3b14f50fU, 0x7629ea1eU, 0xec53d43cU,  //
    0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U, 0xc53d43ceU,  //
    0x8a7a879dU, 0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU,  //
    0xa7a879d8U, 0x4f50f3b1U, 0x9ea1e762U, 0x3d43cec5U,  //
    0x7a879d8aU, 0xf50f3b14U, 0xea1e7629U, 0xd43cec53U,  //
    0xa879d8a7U, 0x50f3b14fU, 0xa1e7629eU, 0x43cec53dU,  //
    0x879d8a7aU, 0x0f3b14f5U, 0x1e7629eaU, 0x3cec53d4U,  //
    0x79d8a7a8U, 0xf3b14f50U, 0xe7629ea1U, 0xcec53d43U,  //
    0x9d8a7a87U, 0x3b14f50fU, 0x7629ea1eU, 0xec53d43cU,  //
    0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U, 0xc53d43ceU,  //
    0x8a7a879dU, 0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU,  //
    0xa7a879d8U, 0x4f50f3b1U, 0x9ea1e762U, 0x3d43cec5U,  //
};

void sm3_common_compress(uint8_t* data, uint32_t* digest) {
    // expand
    uint32_t w[68];
    for (int j = 0; j < 16; j++) {
        w[j] = loadu32_be(data + 4 * j);
    }
    for (int j = 16; j < 68; j++) {
        w[j] = P1(w[j - 16] ^ w[j - 9] ^ rotl(w[j - 3], 15)) ^
               rotl(w[j - 13], 7) ^ w[j - 6];
    }
    //
    uint32_t A, B, C, D, E, F, G, H;
    A = digest[0], B = digest[1], C = digest[2], D = digest[3];
    E = digest[4], F = digest[5], G = digest[6], H = digest[7];
    uint32_t SS1, SS2, TT1, TT2;
    for (int j = 0; j < 64; j++) {
        SS1 = rotl((rotl(A, 12) + E + T[j]), 7);
        SS2 = SS1 ^ rotl(A, 12);
        TT1 = FFj(A, B, C, j) + D + SS2 + (w[j] ^ w[j + 4]);
        TT2 = GGj(E, F, G, j) + H + SS1 + w[j];
        D = C;
        C = rotl(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = rotl(F, 19);
        F = E;
        E = P0(TT2);
    }
    //
    digest[0] ^= A;
    digest[1] ^= B;
    digest[2] ^= C;
    digest[3] ^= D;
    digest[4] ^= E;
    digest[5] ^= F;
    digest[6] ^= G;
    digest[7] ^= H;
}
