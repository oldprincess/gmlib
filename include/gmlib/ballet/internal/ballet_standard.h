#ifndef BALLET_INTERNAL_BALLET_STANDARD_H
#define BALLET_INTERNAL_BALLET_STANDARD_H

#include <cstddef>
#include <cstdint>

namespace ballet::internal::standard {

constexpr std::size_t BALLET128128_BLOCK_SIZE   = 16;
constexpr std::size_t BALLET128128_USER_KEY_LEN = 16;
constexpr std::size_t BALLET128128_PARALLEL_NUM = 1;

constexpr std::size_t BALLET128256_BLOCK_SIZE   = 16;
constexpr std::size_t BALLET128256_USER_KEY_LEN = 32;
constexpr std::size_t BALLET128256_PARALLEL_NUM = 1;

constexpr std::size_t BALLET256256_BLOCK_SIZE   = 32;
constexpr std::size_t BALLET256256_USER_KEY_LEN = 32;
constexpr std::size_t BALLET256256_PARALLEL_NUM = 1;

typedef struct BalletCTX
{
    union SubKey
    {
        std::uint8_t sub_key128128[4 * 4 * 46]; // ballet<blk=128><key=128>
        std::uint8_t sub_key128256[4 * 4 * 48]; // ballet<blk=128><key=256>
        std::uint8_t sub_key256256[4 * 4 * 74]; // ballet<blk=256><key=256>
    } m;
} BalletCTX;

// ****************************************
// ********** Ballet 128/128 **************
// ****************************************

/**
 * @brief           Ballet128/128 key schedule (encryption)
 * @param ctx       Ballet128/128 standard encryption context
 * @param user_key  16-byte secret key
 */
void ballet128128_enc_key_init(BalletCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept;

/**
 * @brief           Ballet128/128 key schedule (decryption)
 * @param ctx       Ballet128/128 standard decryption context
 * @param user_key  16-byte secret key
 */
void ballet128128_dec_key_init(BalletCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               Ballet128/128 block encryption
 * @param ctx           Ballet128/128 standard encryption context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void ballet128128_enc_block(const BalletCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               Ballet128/128 block decryption
 * @param ctx           Ballet128/128 standard decryption context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void ballet128128_dec_block(const BalletCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept;

/**
 * @brief               Ballet128/128 block encryption, crypt in ECB mode
 * @param ctx           Ballet128/128 standard encryption context
 * @param ciphertext    output blocks, length of 16 x block_num bytes
 * @param plaintext     input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ballet128128_enc_blocks(const BalletCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept;

/**
 * @brief               Ballet128/128 block decryption, crypt in ECB mode
 * @param ctx           Ballet128/128 standard decryption context
 * @param plaintext     output blocks, length of 16 x block_num bytes
 * @param ciphertext    input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ballet128128_dec_blocks(const BalletCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept;

// ****************************************
// ********** Ballet 128/256 **************
// ****************************************

/**
 * @brief           Ballet128/256 key schedule (encryption)
 * @param ctx       Ballet128/256 standard encryption context
 * @param user_key  32-byte secret key
 */
void ballet128256_enc_key_init(BalletCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief           Ballet128/256 key schedule (decryption)
 * @param ctx       Ballet128/256 standard decryption context
 * @param user_key  32-byte secret key
 */
void ballet128256_dec_key_init(BalletCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               Ballet128/256 block encryption
 * @param ctx           Ballet128/256 standard encryption context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void ballet128256_enc_block(const BalletCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               Ballet128/256 block decryption
 * @param ctx           Ballet128/256 standard decryption context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void ballet128256_dec_block(const BalletCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept;

/**
 * @brief               Ballet128/256 block encryption, crypt in ECB mode
 * @param ctx           Ballet128/256 standard encryption context
 * @param ciphertext    output blocks, length of 16 x block_num bytes
 * @param plaintext     input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ballet128256_enc_blocks(const BalletCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept;

/**
 * @brief               Ballet128/256 block decryption, crypt in ECB mode
 * @param ctx           Ballet128/256 standard decryption context
 * @param plaintext     output blocks, length of 16 x block_num bytes
 * @param ciphertext    input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ballet128256_dec_blocks(const BalletCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept;

// ****************************************
// ********** Ballet 256/256 **************
// ****************************************

/**
 * @brief           Ballet256/256 key schedule (encryption)
 * @param ctx       Ballet1256/256 standard encryption context
 * @param user_key  32-byte secret key
 */
void ballet256256_enc_key_init(BalletCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief           Ballet256/256 key schedule (decryption)
 * @param ctx       Ballet1256/256 standard decryption context
 * @param user_key  32-byte secret key
 */
void ballet256256_dec_key_init(BalletCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               Ballet256/256 block encryption
 * @param ctx           Ballet256/256 standard encryption context
 * @param ciphertext    32-byte output block
 * @param plaintext     32-byte input block
 */
void ballet256256_enc_block(const BalletCTX   *ctx,
                            std::uint8_t       ciphertext[32],
                            const std::uint8_t plaintext[32]) noexcept;

/**
 * @brief               Ballet256/256 block decryption
 * @param ctx           Ballet256/256 standard decryption context
 * @param plaintext     32-byte output block
 * @param ciphertext    32-byte input block
 */
void ballet256256_dec_block(const BalletCTX   *ctx,
                            std::uint8_t       plaintext[32],
                            const std::uint8_t ciphertext[32]) noexcept;

/**
 * @brief               Ballet256/256 block encryption, crypt in ECB mode
 * @param ctx           Ballet256/256 standard encryption context
 * @param ciphertext    output blocks, length of 32 x block_num bytes
 * @param plaintext     input blocks, length of 32 x block_num bytes
 * @param block_num     block num
 */
void ballet256256_enc_blocks(const BalletCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept;

/**
 * @brief               Ballet256/256 block decryption, crypt in ECB mode
 * @param ctx           Ballet256/256 standard decryption context
 * @param plaintext     output blocks, length of 32 x block_num bytes
 * @param ciphertext    input blocks, length of 32 x block_num bytes
 * @param block_num     block num
 */
void ballet256256_dec_blocks(const BalletCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept;

}; // namespace ballet::internal::standard

#endif