#if defined(CPU_FLAG_SSSE3)
#ifndef UBLOCK_INTERNAL_UBLOCK_STANDARD_H
#define UBLOCK_INTERNAL_UBLOCK_STANDARD_H

#include <cstddef>
#include <cstdint>

namespace ublock::internal::standard {

constexpr std::size_t UBLOCK128128_BLOCK_SIZE   = 16;
constexpr std::size_t UBLOCK128128_USER_KEY_LEN = 16;
constexpr std::size_t UBLOCK128128_PARALLEL_NUM = 1;

constexpr std::size_t UBLOCK128256_BLOCK_SIZE   = 16;
constexpr std::size_t UBLOCK128256_USER_KEY_LEN = 32;
constexpr std::size_t UBLOCK128256_PARALLEL_NUM = 1;

constexpr std::size_t UBLOCK256256_BLOCK_SIZE   = 32;
constexpr std::size_t UBLOCK256256_USER_KEY_LEN = 32;
constexpr std::size_t UBLOCK256256_PARALLEL_NUM = 1;

typedef struct uBlockCTX
{
    union SubKey
    {
        std::uint8_t sub_key128128[17][32]; // ublock<blk=128><key=128>
        std::uint8_t sub_key128256[25][32]; // ublock<blk=128><key=256>
        std::uint8_t sub_key256256[25][64]; // ublock<blk=256><key=256>
    } m;
} uBlockCTX;

// ****************************************
// ********** uBlock 128/128 **************
// ****************************************

/**
 * @brief           uBlock128/128 key schedule (encryption)
 * @param ctx       uBlock128/128 standard encryption context
 * @param user_key  16-byte secret key
 */
void ublock128128_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept;

/**
 * @brief           uBlock128/128 key schedule (decryption)
 * @param ctx       uBlock128/128 standard decryption context
 * @param user_key  16-byte secret key
 */
void ublock128128_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[16]) noexcept;

/**
 * @brief               uBlock128/128 block encryption
 * @param ctx           uBlock128/128 standard encryption context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void ublock128128_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               uBlock128/128 block decryption
 * @param ctx           uBlock128/128 standard decryption context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void ublock128128_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept;

/**
 * @brief               uBlock128/128 block encryption, crypt in ECB mode
 * @param ctx           uBlock128/128 standard encryption context
 * @param ciphertext    output blocks, length of 16 x block_num bytes
 * @param plaintext     input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ublock128128_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept;

/**
 * @brief               uBlock128/128 block decryption, crypt in ECB mode
 * @param ctx           uBlock128/128 standard decryption context
 * @param plaintext     output blocks, length of 16 x block_num bytes
 * @param ciphertext    input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ublock128128_dec_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept;

// ****************************************
// ********** uBlock 128/256 **************
// ****************************************

/**
 * @brief           uBlock128/256 key schedule (encryption)
 * @param ctx       uBlock128/256 standard encryption context
 * @param user_key  32-byte secret key
 */
void ublock128256_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief           uBlock128/256 key schedule (decryption)
 * @param ctx       uBlock128/256 standard decryption context
 * @param user_key  32-byte secret key
 */
void ublock128256_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               uBlock128/256 block encryption
 * @param ctx           uBlock128/256 standard encryption context
 * @param ciphertext    16-byte output block
 * @param plaintext     16-byte input block
 */
void ublock128256_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[16],
                            const std::uint8_t plaintext[16]) noexcept;

/**
 * @brief               uBlock128/256 block decryption
 * @param ctx           uBlock128/256 standard decryption context
 * @param plaintext     16-byte output block
 * @param ciphertext    16-byte input block
 */
void ublock128256_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept;

/**
 * @brief               uBlock128/256 block encryption, crypt in ECB mode
 * @param ctx           uBlock128/256 standard encryption context
 * @param ciphertext    output blocks, length of 16 x block_num bytes
 * @param plaintext     input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ublock128256_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept;

/**
 * @brief               uBlock128/256 block decryption, crypt in ECB mode
 * @param ctx           uBlock128/256 standard decryption context
 * @param plaintext     output blocks, length of 16 x block_num bytes
 * @param ciphertext    input blocks, length of 16 x block_num bytes
 * @param block_num     block num
 */
void ublock128256_dec_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept;

// ****************************************
// ********** uBlock 256/256 **************
// ****************************************

/**
 * @brief           uBlock256/256 key schedule (encryption)
 * @param ctx       uBlock1256/256 standard encryption context
 * @param user_key  32-byte secret key
 */
void ublock256256_enc_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief           uBlock256/256 key schedule (decryption)
 * @param ctx       uBlock1256/256 standard decryption context
 * @param user_key  32-byte secret key
 */
void ublock256256_dec_key_init(uBlockCTX         *ctx,
                               const std::uint8_t user_key[32]) noexcept;

/**
 * @brief               uBlock256/256 block encryption
 * @param ctx           uBlock256/256 standard encryption context
 * @param ciphertext    32-byte output block
 * @param plaintext     32-byte input block
 */
void ublock256256_enc_block(const uBlockCTX   *ctx,
                            std::uint8_t       ciphertext[32],
                            const std::uint8_t plaintext[32]) noexcept;

/**
 * @brief               uBlock256/256 block decryption
 * @param ctx           uBlock256/256 standard decryption context
 * @param plaintext     32-byte output block
 * @param ciphertext    32-byte input block
 */
void ublock256256_dec_block(const uBlockCTX   *ctx,
                            std::uint8_t       plaintext[32],
                            const std::uint8_t ciphertext[32]) noexcept;

/**
 * @brief               uBlock256/256 block encryption, crypt in ECB mode
 * @param ctx           uBlock256/256 standard encryption context
 * @param ciphertext    output blocks, length of 32 x block_num bytes
 * @param plaintext     input blocks, length of 32 x block_num bytes
 * @param block_num     block num
 */
void ublock256256_enc_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *ciphertext,
                             const std::uint8_t *plaintext,
                             std::size_t         block_num) noexcept;

/**
 * @brief               uBlock256/256 block decryption, crypt in ECB mode
 * @param ctx           uBlock256/256 standard decryption context
 * @param plaintext     output blocks, length of 32 x block_num bytes
 * @param ciphertext    input blocks, length of 32 x block_num bytes
 * @param block_num     block num
 */
void ublock256256_dec_blocks(const uBlockCTX    *ctx,
                             std::uint8_t       *plaintext,
                             const std::uint8_t *ciphertext,
                             std::size_t         block_num) noexcept;

}; // namespace ublock::internal::standard

#endif
#endif