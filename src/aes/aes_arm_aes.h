#if defined(SUPPORT_AES_ARM_AES)

#ifndef AES_INTERNAL_AES_ARM_AES_H
#define AES_INTERNAL_AES_ARM_AES_H

#include <cstddef>
#include <cstdint>

namespace aes::internal::arm_aes {

constexpr const char* AES_ALGO_NAME = "arm_aes";

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

/**
 * @brief               AES-128 key schedule (encryption)
 * @param round_key     AES-128 Round Key
 * @param user_key      16-byte secret key
 */
void aes128_enc_key_init(std::uint8_t       round_key[11 * 16],
                         const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               AES-128 key schedule (decryption)
 * @param round_key     AES-128 Round Key
 * @param user_key      16-byte secret key
 */
void aes128_dec_key_init(std::uint8_t       round_key[11 * 16],
                         const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               AES-128 block encryption
 * @param round_key     AES-128 Round Key
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void aes128_enc_block(const std::uint8_t round_key[11 * 16],
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               AES-128 block decryption
 * @param round_key     AES-128 Round Key
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void aes128_dec_block(const std::uint8_t round_key[11 * 16],
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept;

void aes128_enc_blocks(const std::uint8_t  round_key[11 * 16],
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept;

void aes128_dec_blocks(const std::uint8_t  round_key[11 * 16],
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept;

// ****************************************
// ************* AES 192 ******************
// ****************************************

/**
 * @brief               AES-192 key schedule (encryption)
 * @param round_key     AES-192 Round Key
 * @param user_key      24-byte secret key
 */
void aes192_enc_key_init(std::uint8_t       round_key[13 * 16],
                         const std::uint8_t user_key[24]) noexcept;

/**
 * @brief               AES-192 key schedule (decryption)
 * @param round_key     AES-192 Round Key
 * @param user_key      24-byte secret key
 */
void aes192_dec_key_init(std::uint8_t       round_key[13 * 16],
                         const std::uint8_t user_key[24]) noexcept;

/**
 * @brief               AES-192 block encryption
 * @param round_key     AES-192 Round Key
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void aes192_enc_block(const std::uint8_t round_key[13 * 16],
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               AES-192 block decryption
 * @param round_key     AES-192 Round Key
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void aes192_dec_block(const std::uint8_t round_key[13 * 16],
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept;

void aes192_enc_blocks(const std::uint8_t  round_key[13 * 16],
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept;

void aes192_dec_blocks(const std::uint8_t  round_key[13 * 16],
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept;

// ****************************************
// ************* AES 256 ******************
// ****************************************

/**
 * @brief               AES-256 key schedule (encryption)
 * @param round_key     AES-256 Round Key
 * @param user_key      32-byte secret key
 */
void aes256_enc_key_init(std::uint8_t       round_key[15 * 16],
                         const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               AES-256 key schedule (decryption)
 * @param round_key     AES-256 Round Key
 * @param user_key      32-byte secret key
 */
void aes256_dec_key_init(std::uint8_t       round_key[15 * 16],
                         const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               AES-256 block encryption
 * @param round_key     AES-256 Round Key
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void aes256_enc_block(const std::uint8_t round_key[15 * 16],
                      std::uint8_t       ciphertext[16],
                      const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               AES-256 block decryption
 * @param round_key     AES-256 Round Key
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void aes256_dec_block(const std::uint8_t round_key[15 * 16],
                      std::uint8_t       plaintext[16],
                      const std::uint8_t ciphertext[16]) noexcept;

void aes256_enc_blocks(const std::uint8_t  round_key[15 * 16],
                       std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext,
                       std::size_t         block_num) noexcept;

void aes256_dec_blocks(const std::uint8_t  round_key[15 * 16],
                       std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext,
                       std::size_t         block_num) noexcept;

}; // namespace aes::internal::arm_aes

#endif

#endif
