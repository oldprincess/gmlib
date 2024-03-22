/**
 * FIPS 197. Advanced Encryption Standard (AES)
 *
 * J.Daemen, V.Rijmen. The Design of Rijndael[M]. Berlin: Springer, 2020: 53-63.
 */
#ifndef AES_INTERNAL_AES_LUT_H
#define AES_INTERNAL_AES_LUT_H

#include <cstddef>
#include <cstdint>

namespace aes::internal::lut {

constexpr std::size_t AES128_BLOCK_SIZE   = 16;
constexpr std::size_t AES128_USER_KEY_LEN = 16;
constexpr std::size_t AES128_PARALLEL_NUM = 1;

constexpr std::size_t AES192_BLOCK_SIZE   = 16;
constexpr std::size_t AES192_USER_KEY_LEN = 24;
constexpr std::size_t AES192_PARALLEL_NUM = 1;

constexpr std::size_t AES256_BLOCK_SIZE   = 16;
constexpr std::size_t AES256_USER_KEY_LEN = 32;
constexpr std::size_t AES256_PARALLEL_NUM = 1;

// ****************************************
// ************* AES 128 ******************
// ****************************************

typedef struct Aes128CTX
{
    std::uint32_t round_key[44];
} Aes128CTX;

/**
 * @brief               AES-128 key schedule (encryption)
 * @param ctx           AES-128 Encryption Context
 * @param user_key      16-byte secret key
 */
void aes128_enc_key_init(Aes128CTX*         ctx,
                         const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               AES-128 key schedule (decryption)
 * @param ctx           AES-128 Decryption Context
 * @param user_key      16-byte secret key
 */
void aes128_dec_key_init(Aes128CTX*         ctx,
                         const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               AES-128 block encryption
 * @param ctx           AES-128 Encryption Context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void aes128_enc_block(const Aes128CTX*   ctx,
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               AES-128 block decryption
 * @param ctx           AES-128 Decryption Context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void aes128_dec_block(const Aes128CTX*   ctx,
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept;

void aes128_enc_blocks(const Aes128CTX*    ctx,
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept;

void aes128_dec_blocks(const Aes128CTX*    ctx,
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept;

// ****************************************
// ************* AES 192 ******************
// ****************************************

typedef struct Aes192CTX
{
    std::uint32_t round_key[52];
} Aes192CTX;

/**
 * @brief               AES-192 key schedule (encryption)
 * @param ctx           AES-192 Encryption Context
 * @param user_key      24-byte secret key
 */
void aes192_enc_key_init(Aes192CTX*         ctx,
                         const std::uint8_t user_key[24]) noexcept;

/**
 * @brief               AES-192 key schedule (decryption)
 * @param ctx           AES-192 Decryption Context
 * @param user_key      24-byte secret key
 */
void aes192_dec_key_init(Aes192CTX*         ctx,
                         const std::uint8_t user_key[24]) noexcept;

/**
 * @brief               AES-192 block encryption
 * @param ctx           AES-192 Encryption Context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void aes192_enc_block(const Aes192CTX*   ctx,
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               AES-192 block decryption
 * @param ctx           AES-192 Decryption Context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void aes192_dec_block(const Aes192CTX*   ctx,
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept;

void aes192_enc_blocks(const Aes192CTX*    ctx,
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept;

void aes192_dec_blocks(const Aes192CTX*    ctx,
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept;

// ****************************************
// ************* AES 256 ******************
// ****************************************

typedef struct Aes256CTX
{
    std::uint32_t round_key[60];
} Aes256CTX;

/**
 * @brief               AES-256 key schedule (encryption)
 * @param ctx           AES-256 Encryption Context
 * @param user_key      32-byte secret key
 */
void aes256_enc_key_init(Aes256CTX*         ctx,
                         const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               AES-256 key schedule (decryption)
 * @param ctx           AES-256 Decryption Context
 * @param user_key      32-byte secret key
 */
void aes256_dec_key_init(Aes256CTX*         ctx,
                         const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               AES-256 block encryption
 * @param ctx           AES-256 Encryption Context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void aes256_enc_block(const Aes256CTX*   ctx,
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               AES-256 block decryption
 * @param ctx           AES-256 Decryption Context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void aes256_dec_block(const Aes256CTX*   ctx,
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept;

void aes256_enc_blocks(const Aes256CTX*    ctx,
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept;

void aes256_dec_blocks(const Aes256CTX*    ctx,
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept;

}; // namespace aes::internal::lut

#endif