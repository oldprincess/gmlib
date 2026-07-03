#if defined(AES_IMPL_ARM_AES)

#include "aes_arm_aes.h"

#include <arm_neon.h>

#define aesenc_8x16(state, rk) vaesmcq_u8(vaeseq_u8(state, rk))
#define aesdec_8x16(state, rk) vaesimcq_u8(vaesdq_u8(state, rk))

#define load_8x16(ptr) vld1q_u8((const std::uint8_t*)ptr)

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

namespace aes::internal::arm_aes {

static const std::uint8_t SBOX[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B,
    0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 0xB7, 0xFD, 0x93, 0x26,
    0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2,
    0xEB, 0x27, 0xB2, 0x75, 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84, 0x53, 0xD1, 0x00, 0xED,
    0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F,
    0x50, 0x3C, 0x9F, 0xA8, 0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 0xCD, 0x0C, 0x13, 0xEC,
    0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14,
    0xDE, 0x5E, 0x0B, 0xDB, 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79, 0xE7, 0xC8, 0x37, 0x6D,
    0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F,
    0x4B, 0xBD, 0x8B, 0x8A, 0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 0xE1, 0xF8, 0x98, 0x11,
    0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F,
    0xB0, 0x54, 0xBB, 0x16,
};

/**
 * @brief               AES key schedule (encryption)
 * @param round_key     44/52/60-dword round key (11/13/15-round)
 * @param user_key      16/24/32-byte secret key
 * @param bits          AES key bits 128/192/256
 */
static void aes_enc_key_init(std::uint8_t*       round_key,
                             const std::uint8_t* user_key,
                             int                 bits) noexcept
{
    static const std::uint32_t Rcon[10] = {
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36,
    };
    int            nr = 10 + (bits - 128) / 32; // Nr
    int            nk = bits / 32;              // Nk
    std::uint32_t  tmp, tmp1;
    std::uint32_t* w = (std::uint32_t*)round_key;
    //--------------Load as BigEndian---------------
    for (int i = 0; i < nk; i++)
    {
        w[i] = MEM_LOAD32BE(user_key + 4 * i);
    }
    //------------KeyExpand-----------------
    for (int i = nk; i < 4 * (nr + 1); i++)
    {
        tmp = w[i - 1];
        if (i % nk == 0)
        {
            // tmp = SubWord(RotWord(w[i-1]))
            tmp1 = tmp;
            tmp  = SBOX[(tmp1 >> 24) & 0xFF];
            tmp |= SBOX[(tmp1 >> 0) & 0xFF] << 8;
            tmp |= SBOX[(tmp1 >> 8) & 0xFF] << 16;
            tmp |= (SBOX[(tmp1 >> 16) & 0xFF] ^ Rcon[i / nk - 1]) << 24;
        }
        else if (nk > 6 && i % nk == 4)
        {
            // tmp = SubWord(w[i-1])
            tmp1 = tmp;
            tmp  = SBOX[(tmp1 >> 0) & 0xFF];
            tmp |= SBOX[(tmp1 >> 8) & 0xFF] << 8;
            tmp |= SBOX[(tmp1 >> 16) & 0xFF] << 16;
            tmp |= SBOX[(tmp1 >> 24) & 0xFF] << 24;
        }
        w[i] = w[i - nk] ^ tmp;
    }
    for (int i = 0; i < 4 * (nr + 1); i++)
    {
        std::uint32_t tmp = w[i];
        MEM_STORE32BE(round_key + i * 4, tmp);
    }
}

static void AES_128_Key_Expansion(const std::uint8_t* user_key,
                                  std::uint8_t*       round_key) noexcept
{
    aes_enc_key_init(round_key, user_key, 128);
}

static void AES_192_Key_Expansion(const std::uint8_t* user_key,
                                  std::uint8_t*       round_key) noexcept
{
    aes_enc_key_init(round_key, user_key, 192);
}

static void AES_256_Key_Expansion(const std::uint8_t* user_key,
                                  std::uint8_t*       round_key) noexcept
{
    aes_enc_key_init(round_key, user_key, 256);
}

// ****************************************
// ************* AES 128 ******************
// ****************************************

void aes128_enc_key_init(std::uint8_t       round_key[11 * 16],
                         const std::uint8_t user_key[16]) noexcept
{
    AES_128_Key_Expansion(user_key, round_key);
}

void aes128_dec_key_init(std::uint8_t       round_key[11 * 16],
                         const std::uint8_t user_key[16]) noexcept
{
    uint8x16_t rk[11];
    AES_128_Key_Expansion(user_key, (unsigned char*)rk);
    vst1q_u8((round_key + 0 * 16), rk[10]);
    vst1q_u8((round_key + 1 * 16), vaesimcq_u8(rk[9]));
    vst1q_u8((round_key + 2 * 16), vaesimcq_u8(rk[8]));
    vst1q_u8((round_key + 3 * 16), vaesimcq_u8(rk[7]));
    vst1q_u8((round_key + 4 * 16), vaesimcq_u8(rk[6]));
    vst1q_u8((round_key + 5 * 16), vaesimcq_u8(rk[5]));
    vst1q_u8((round_key + 6 * 16), vaesimcq_u8(rk[4]));
    vst1q_u8((round_key + 7 * 16), vaesimcq_u8(rk[3]));
    vst1q_u8((round_key + 8 * 16), vaesimcq_u8(rk[2]));
    vst1q_u8((round_key + 9 * 16), vaesimcq_u8(rk[1]));
    vst1q_u8((round_key + 10 * 16), rk[0]);
}

void aes128_enc_blocks(const std::uint8_t  round_key[11 * 16],
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept
{
    uint8x16_t        state;
    const uint8x16_t* rki = (const uint8x16_t*)round_key;
    while (block_num)
    {
        state = load_8x16(plaintext);
        // AESMixColumns(AESSubBytes(AESShiftRows(EOR(state, rki))));
        state = aesenc_8x16(state, rki[0]);
        state = aesenc_8x16(state, rki[1]);
        state = aesenc_8x16(state, rki[2]);
        state = aesenc_8x16(state, rki[3]);
        state = aesenc_8x16(state, rki[4]);
        state = aesenc_8x16(state, rki[5]);
        state = aesenc_8x16(state, rki[6]);
        state = aesenc_8x16(state, rki[7]);
        state = aesenc_8x16(state, rki[8]);
        state = vaeseq_u8(state, rki[9]);
        state = veorq_u8(state, rki[10]);
        vst1q_u8(ciphertext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes128_dec_blocks(const std::uint8_t  round_key[11 * 16],
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept
{
    uint8x16_t        state;
    const uint8x16_t* rki = (const uint8x16_t*)round_key;
    while (block_num)
    {
        state = load_8x16(ciphertext);
        state = aesdec_8x16(state, rki[0]);
        state = aesdec_8x16(state, rki[1]);
        state = aesdec_8x16(state, rki[2]);
        state = aesdec_8x16(state, rki[3]);
        state = aesdec_8x16(state, rki[4]);
        state = aesdec_8x16(state, rki[5]);
        state = aesdec_8x16(state, rki[6]);
        state = aesdec_8x16(state, rki[7]);
        state = aesdec_8x16(state, rki[8]);
        state = vaesdq_u8(state, rki[9]);
        state = veorq_u8(state, rki[10]);
        vst1q_u8(plaintext, state);

        plaintext += 16, ciphertext += 16, block_num -= 1;
    }
}

void aes128_enc_block(const std::uint8_t round_key[11 * 16],
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept
{
    aes128_enc_blocks(round_key, ciphertext, plaintext, 1);
}

void aes128_dec_block(const std::uint8_t round_key[11 * 16],
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept
{
    aes128_dec_blocks(round_key, plaintext, ciphertext, 1);
}

// ****************************************
// ************* AES 192 ******************
// ****************************************

void aes192_enc_key_init(std::uint8_t       round_key[13 * 16],
                         const std::uint8_t user_key[24]) noexcept
{
    AES_192_Key_Expansion(user_key, round_key);
}

void aes192_dec_key_init(std::uint8_t       round_key[13 * 16],
                         const std::uint8_t user_key[24]) noexcept
{
    uint8x16_t rk[13];
    AES_192_Key_Expansion(user_key, (unsigned char*)rk);
    vst1q_u8((round_key + 0 * 16), rk[12]);
    vst1q_u8((round_key + 1 * 16), vaesimcq_u8(rk[11]));
    vst1q_u8((round_key + 2 * 16), vaesimcq_u8(rk[10]));
    vst1q_u8((round_key + 3 * 16), vaesimcq_u8(rk[9]));
    vst1q_u8((round_key + 4 * 16), vaesimcq_u8(rk[8]));
    vst1q_u8((round_key + 5 * 16), vaesimcq_u8(rk[7]));
    vst1q_u8((round_key + 6 * 16), vaesimcq_u8(rk[6]));
    vst1q_u8((round_key + 7 * 16), vaesimcq_u8(rk[5]));
    vst1q_u8((round_key + 8 * 16), vaesimcq_u8(rk[4]));
    vst1q_u8((round_key + 9 * 16), vaesimcq_u8(rk[3]));
    vst1q_u8((round_key + 10 * 16), vaesimcq_u8(rk[2]));
    vst1q_u8((round_key + 11 * 16), vaesimcq_u8(rk[1]));
    vst1q_u8((round_key + 12 * 16), rk[0]);
}

void aes192_enc_blocks(const std::uint8_t  round_key[13 * 16],
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept
{
    uint8x16_t        state;
    const uint8x16_t* rki = (const uint8x16_t*)round_key;
    while (block_num)
    {
        state = load_8x16(plaintext);
        state = aesenc_8x16(state, rki[0]);
        state = aesenc_8x16(state, rki[1]);
        state = aesenc_8x16(state, rki[2]);
        state = aesenc_8x16(state, rki[3]);
        state = aesenc_8x16(state, rki[4]);
        state = aesenc_8x16(state, rki[5]);
        state = aesenc_8x16(state, rki[6]);
        state = aesenc_8x16(state, rki[7]);
        state = aesenc_8x16(state, rki[8]);
        state = aesenc_8x16(state, rki[9]);
        state = aesenc_8x16(state, rki[10]);
        state = vaeseq_u8(state, rki[11]);
        state = veorq_u8(state, rki[12]);
        vst1q_u8(ciphertext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes192_dec_blocks(const std::uint8_t  round_key[13 * 16],
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept
{
    uint8x16_t        state;
    const uint8x16_t* rki = (const uint8x16_t*)round_key;
    while (block_num)
    {
        state = load_8x16(ciphertext);
        state = aesdec_8x16(state, rki[0]);
        state = aesdec_8x16(state, rki[1]);
        state = aesdec_8x16(state, rki[2]);
        state = aesdec_8x16(state, rki[3]);
        state = aesdec_8x16(state, rki[4]);
        state = aesdec_8x16(state, rki[5]);
        state = aesdec_8x16(state, rki[6]);
        state = aesdec_8x16(state, rki[7]);
        state = aesdec_8x16(state, rki[8]);
        state = aesdec_8x16(state, rki[9]);
        state = aesdec_8x16(state, rki[10]);
        state = vaesdq_u8(state, rki[11]);
        state = veorq_u8(state, rki[12]);
        vst1q_u8(plaintext, state);

        plaintext += 16, ciphertext += 16, block_num -= 1;
    }
}

void aes192_enc_block(const std::uint8_t round_key[13 * 16],
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept
{
    aes192_enc_blocks(round_key, ciphertext, plaintext, 1);
}

void aes192_dec_block(const std::uint8_t round_key[13 * 16],
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept
{
    aes192_dec_blocks(round_key, plaintext, ciphertext, 1);
}

// ****************************************
// ************* AES 256 ******************
// ****************************************

void aes256_enc_key_init(std::uint8_t       round_key[15 * 16],
                         const std::uint8_t user_key[32]) noexcept
{
    uint8x16_t rk[15];
    AES_256_Key_Expansion(user_key, (unsigned char*)rk);
    vst1q_u8((round_key + 0 * 16), rk[0]);
    vst1q_u8((round_key + 1 * 16), rk[1]);
    vst1q_u8((round_key + 2 * 16), rk[2]);
    vst1q_u8((round_key + 3 * 16), rk[3]);
    vst1q_u8((round_key + 4 * 16), rk[4]);
    vst1q_u8((round_key + 5 * 16), rk[5]);
    vst1q_u8((round_key + 6 * 16), rk[6]);
    vst1q_u8((round_key + 7 * 16), rk[7]);
    vst1q_u8((round_key + 8 * 16), rk[8]);
    vst1q_u8((round_key + 9 * 16), rk[9]);
    vst1q_u8((round_key + 10 * 16), rk[10]);
    vst1q_u8((round_key + 11 * 16), rk[11]);
    vst1q_u8((round_key + 12 * 16), rk[12]);
    vst1q_u8((round_key + 13 * 16), rk[13]);
    vst1q_u8((round_key + 14 * 16), rk[14]);
}

void aes256_dec_key_init(std::uint8_t       round_key[15 * 16],
                         const std::uint8_t user_key[32]) noexcept
{
    uint8x16_t rk[15];
    AES_256_Key_Expansion(user_key, (unsigned char*)rk);
    vst1q_u8((round_key + 0 * 16), rk[14]);
    vst1q_u8((round_key + 1 * 16), vaesimcq_u8(rk[13]));
    vst1q_u8((round_key + 2 * 16), vaesimcq_u8(rk[12]));
    vst1q_u8((round_key + 3 * 16), vaesimcq_u8(rk[11]));
    vst1q_u8((round_key + 4 * 16), vaesimcq_u8(rk[10]));
    vst1q_u8((round_key + 5 * 16), vaesimcq_u8(rk[9]));
    vst1q_u8((round_key + 6 * 16), vaesimcq_u8(rk[8]));
    vst1q_u8((round_key + 7 * 16), vaesimcq_u8(rk[7]));
    vst1q_u8((round_key + 8 * 16), vaesimcq_u8(rk[6]));
    vst1q_u8((round_key + 9 * 16), vaesimcq_u8(rk[5]));
    vst1q_u8((round_key + 10 * 16), vaesimcq_u8(rk[4]));
    vst1q_u8((round_key + 11 * 16), vaesimcq_u8(rk[3]));
    vst1q_u8((round_key + 12 * 16), vaesimcq_u8(rk[2]));
    vst1q_u8((round_key + 13 * 16), vaesimcq_u8(rk[1]));
    vst1q_u8((round_key + 14 * 16), rk[0]);
}

void aes256_enc_blocks(const std::uint8_t  round_key[15 * 16],
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept
{
    uint8x16_t        state;
    const uint8x16_t* rki = (const uint8x16_t*)round_key;
    while (block_num)
    {
        state = load_8x16(plaintext);
        state = aesenc_8x16(state, rki[0]);
        state = aesenc_8x16(state, rki[1]);
        state = aesenc_8x16(state, rki[2]);
        state = aesenc_8x16(state, rki[3]);
        state = aesenc_8x16(state, rki[4]);
        state = aesenc_8x16(state, rki[5]);
        state = aesenc_8x16(state, rki[6]);
        state = aesenc_8x16(state, rki[7]);
        state = aesenc_8x16(state, rki[8]);
        state = aesenc_8x16(state, rki[9]);
        state = aesenc_8x16(state, rki[10]);
        state = aesenc_8x16(state, rki[11]);
        state = aesenc_8x16(state, rki[12]);
        state = vaeseq_u8(state, rki[13]);
        state = veorq_u8(state, rki[14]);
        vst1q_u8(ciphertext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes256_dec_blocks(const std::uint8_t  round_key[15 * 16],
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept
{
    uint8x16_t        state;
    const uint8x16_t* rki = (const uint8x16_t*)round_key;
    while (block_num)
    {
        state = load_8x16(ciphertext);
        state = aesdec_8x16(state, rki[0]);
        state = aesdec_8x16(state, rki[1]);
        state = aesdec_8x16(state, rki[2]);
        state = aesdec_8x16(state, rki[3]);
        state = aesdec_8x16(state, rki[4]);
        state = aesdec_8x16(state, rki[5]);
        state = aesdec_8x16(state, rki[6]);
        state = aesdec_8x16(state, rki[7]);
        state = aesdec_8x16(state, rki[8]);
        state = aesdec_8x16(state, rki[9]);
        state = aesdec_8x16(state, rki[10]);
        state = aesdec_8x16(state, rki[11]);
        state = aesdec_8x16(state, rki[12]);
        state = vaesdq_u8(state, rki[13]);
        state = veorq_u8(state, rki[14]);
        vst1q_u8(plaintext, state);

        ciphertext += 16, plaintext += 16, block_num -= 1;
    }
}

void aes256_enc_block(const std::uint8_t round_key[15 * 16],
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept
{
    aes256_enc_blocks(round_key, ciphertext, plaintext, 1);
}

void aes256_dec_block(const std::uint8_t round_key[15 * 16],
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept
{
    aes256_dec_blocks(round_key, plaintext, ciphertext, 1);
}

}; // namespace aes::internal::arm_aes
#endif
