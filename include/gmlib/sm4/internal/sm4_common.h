#ifndef SM4_INTERNAL_SM4_COMMON_H
#define SM4_INTERNAL_SM4_COMMON_H

#include <cstddef>
#include <cstdint>

namespace sm4::internal::common {

constexpr std::size_t SM4_BLOCK_SIZE   = 16;
constexpr std::size_t SM4_USER_KEY_LEN = 16;
constexpr std::size_t SM4_PARALLEL_NUM = 1;

/**
 * @brief SM4 cipher context of commom implementation
 */
typedef struct Sm4CTX
{
    std::uint32_t round_key[32]; // 32x32-bit round key
} Sm4CTX;

/**
 * @brief           SM4 key schedule (encryption)
 * @param ctx       SM4 encryption context
 * @param user_key  16-byte secret key
 */
void sm4_enc_key_init(Sm4CTX *ctx, const std::uint8_t user_key[16]) noexcept;

/**
 * @brief           SM4 key schedule (decryption)
 * @param ctx       SM4 decryption context
 * @param user_key  16-byte secret key
 */
void sm4_dec_key_init(Sm4CTX *ctx, const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               SM4 block encryption
 * @param ctx           SM4 encryption context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void sm4_enc_block(const Sm4CTX      *ctx,
                   std::uint8_t       ciphertext[16],
                   const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               SM4 block decryption
 * @param ctx           SM4 decryption context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void sm4_dec_block(const Sm4CTX      *ctx,
                   std::uint8_t       plaintext[16],
                   const std::uint8_t ciphertext[16]) noexcept;

/**
 * @brief               SM4 block encryption, crypt in ECB mode
 * @param ctx           SM4 encryption context
 * @param ciphertext    output blocks, length of 16 x block_num bytes
 * @param plaintext     input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void sm4_enc_blocks(const Sm4CTX       *ctx,
                    std::uint8_t       *ciphertext,
                    const std::uint8_t *plaintext,
                    std::size_t         block_num) noexcept;

/**
 * @brief               SM4 block decryption, crypt in ECB mode
 * @param ctx           SM4 decryption context
 * @param plaintext     output blocks, length of 16 x block_num bytes
 * @param ciphertext    input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void sm4_dec_blocks(const Sm4CTX       *ctx,
                    std::uint8_t       *plaintext,
                    const std::uint8_t *ciphertext,
                    std::size_t         block_num) noexcept;

}; // namespace sm4::internal::common

#endif