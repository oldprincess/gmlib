#ifndef SM4_INTERNAL_SM4_LANG18_H
#define SM4_INTERNAL_SM4_LANG18_H

#include "config.h"

#if defined(SM4_IMPL_LANG18)

#include <cstddef>
#include <cstdint>

namespace sm4::internal::lang18 {

constexpr std::size_t SM4_BLOCK_SIZE   = 16;
constexpr std::size_t SM4_USER_KEY_LEN = 16;
constexpr std::size_t SM4_PARALLEL_NUM = 16;

constexpr const char *SM4_ALGO_NAME = "lang18";

/**
 * @brief               SM4 key schedule (encryption)
 * @param round_key     SM4 Encryption Round Key
 * @param user_key      16-byte secret key
 */
void sm4_enc_key_init(std::uint8_t       round_key[128],
                      const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               SM4 key schedule (decryption)
 * @param round_key     SM4 Decryption Round Key
 * @param user_key      16-byte secret key
 */
void sm4_dec_key_init(std::uint8_t       round_key[128],
                      const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               SM4 block encryption
 * @param round_key     SM4 Encryption Round Key
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void sm4_enc_block(const std::uint8_t round_key[128],
                   std::uint8_t       ciphertext[16],
                   const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               SM4 block decryption
 * @param round_key     SM4 Decryption Round Key
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void sm4_dec_block(const std::uint8_t round_key[128],
                   std::uint8_t       plaintext[16],
                   const std::uint8_t ciphertext[16]) noexcept;

/**
 * @brief               SM4 block encryption, crypt in ECB mode
 * @param round_key     SM4 Encryption Round Key
 * @param ciphertext    output blocks, length of 16 x block_num bytes
 * @param plaintext     input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void sm4_enc_blocks(const std::uint8_t  round_key[128],
                    std::uint8_t       *ciphertext,
                    const std::uint8_t *plaintext,
                    std::size_t         block_num) noexcept;

/**
 * @brief               SM4 block decryption, crypt in ECB mode
 * @param round_key     SM4 Decryption Round Key
 * @param plaintext     output blocks, length of 16 x block_num bytes
 * @param ciphertext    input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void sm4_dec_blocks(const std::uint8_t  round_key[128],
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept;

}; // namespace sm4::internal::lang18

#endif
#endif