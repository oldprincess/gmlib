#ifndef DES_INTERNAL_DES_COMMON_H
#define DES_INTERNAL_DES_COMMON_H

#include <cstddef>
#include <cstdint>

namespace des::internal::common {

constexpr const char *DES_ALGO_NAME = "common";

constexpr std::size_t DES_BLOCK_SIZE   = 8;
constexpr std::size_t DES_USER_KEY_LEN = 8;
constexpr std::size_t DES_PARALLEL_NUM = 1;

/**
 * @brief           DES key schedule (encryption)
 * @param round_key DES Round Key
 * @param user_key  8-byte secret key
 */
void des_enc_key_init(std::uint8_t       round_key[128],
                      const std::uint8_t user_key[8]) noexcept;

/**
 * @brief           DES key schedule (decryption)
 * @param round_key DES Round Key
 * @param user_key  8-byte secret key
 */
void des_dec_key_init(std::uint8_t       round_key[128],
                      const std::uint8_t user_key[8]) noexcept;

/**
 * @brief               DES block encryption
 * @param round_key     DES Round Key
 * @param ciphertext    8-byte output block
 * @param plaintext     8-byte input block
 */
void des_enc_block(const std::uint8_t round_key[128],
                   std::uint8_t       ciphertext[8],
                   const std::uint8_t plaintext[8]) noexcept;

/**
 * @brief               DES block decryption
 * @param round_key     DES Round Key
 * @param plaintext     8-byte output block
 * @param ciphertext    8-byte input block
 */
void des_dec_block(const std::uint8_t round_key[128],
                   std::uint8_t       plaintext[8],
                   const std::uint8_t ciphertext[8]) noexcept;

/**
 * @brief               DES block encryption, crypt in ECB mode
 * @param round_key     DES Round Key
 * @param ciphertext    output blocks, length of 8 x block_num bytes
 * @param plaintext     input blocks, length of 8 x block_num bytes
 * @param block_num     block num
 */
void des_enc_blocks(const std::uint8_t  round_key[128],
                    std::uint8_t       *ciphertext,
                    const std::uint8_t *plaintext,
                    std::size_t         block_num) noexcept;

/**
 * @brief               DES block decryption, crypt in ECB mode
 * @param round_key     DES Round Key
 * @param plaintext     output blocks, length of 16 x block_num bytes
 * @param ciphertext    input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void des_dec_blocks(const std::uint8_t  round_key[128],
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept;

}; // namespace des::internal::common

#endif