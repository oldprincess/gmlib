#ifndef UBLOCK_INTERNAL_UBLOCK_COMMON_H
#define UBLOCK_INTERNAL_UBLOCK_COMMON_H

#include "config.h"

#if defined(UBLOCK_IMPL_COMMON)

#include <cstddef>
#include <cstdint>

namespace ublock::internal::common {

constexpr const char* UBLOCK_ALGO_NAME = "common";

constexpr std::size_t UBLOCK128128_BLOCK_SIZE   = 16;
constexpr std::size_t UBLOCK128128_USER_KEY_LEN = 16;
constexpr std::size_t UBLOCK128128_PARALLEL_NUM = 1;

constexpr std::size_t UBLOCK128256_BLOCK_SIZE   = 16;
constexpr std::size_t UBLOCK128256_USER_KEY_LEN = 32;
constexpr std::size_t UBLOCK128256_PARALLEL_NUM = 1;

constexpr std::size_t UBLOCK256256_BLOCK_SIZE   = 32;
constexpr std::size_t UBLOCK256256_USER_KEY_LEN = 32;
constexpr std::size_t UBLOCK256256_PARALLEL_NUM = 1;

typedef struct UBlock128128RoundKey
{
    std::uint8_t round_key[17][16];
} UBlock128128RoundKey;

typedef struct UBlock128256RoundKey
{
    std::uint8_t round_key[25][16];
} UBlock128256RoundKey;

typedef struct UBlock256256RoundKey
{
    std::uint8_t round_key[25][32];
} UBlock256256RoundKey;

// ****************************************
// ********** uBlock 128/128 **************
// ****************************************

void ublock128128_enc_key_init(UBlock128128RoundKey* round_key,
                               const std::uint8_t    user_key[16]) noexcept;

void ublock128128_dec_key_init(UBlock128128RoundKey* round_key,
                               const std::uint8_t    user_key[16]) noexcept;

void ublock128128_enc_block(const UBlock128128RoundKey* round_key,
                            std::uint8_t                ciphertext[16],
                            const std::uint8_t          plaintext[16]) noexcept;

void ublock128128_dec_block(const UBlock128128RoundKey* round_key,
                            std::uint8_t                plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept;

void ublock128128_enc_blocks(const UBlock128128RoundKey* round_key,
                             std::uint8_t*               ciphertext,
                             const std::uint8_t*         plaintext,
                             std::size_t                 block_num) noexcept;

void ublock128128_dec_blocks(const UBlock128128RoundKey* round_key,
                             std::uint8_t*               plaintext,
                             const std::uint8_t*         ciphertext,
                             std::size_t                 block_num) noexcept;

// ****************************************
// ********** uBlock 128/256 **************
// ****************************************

void ublock128256_enc_key_init(UBlock128256RoundKey* round_key,
                               const std::uint8_t    user_key[32]) noexcept;

void ublock128256_dec_key_init(UBlock128256RoundKey* round_key,
                               const std::uint8_t    user_key[32]) noexcept;

void ublock128256_enc_block(const UBlock128256RoundKey* round_key,
                            std::uint8_t                ciphertext[16],
                            const std::uint8_t          plaintext[16]) noexcept;

void ublock128256_dec_block(const UBlock128256RoundKey* round_key,
                            std::uint8_t                plaintext[16],
                            const std::uint8_t ciphertext[16]) noexcept;

void ublock128256_enc_blocks(const UBlock128256RoundKey* round_key,
                             std::uint8_t*               ciphertext,
                             const std::uint8_t*         plaintext,
                             std::size_t                 block_num) noexcept;

void ublock128256_dec_blocks(const UBlock128256RoundKey* round_key,
                             std::uint8_t*               plaintext,
                             const std::uint8_t*         ciphertext,
                             std::size_t                 block_num) noexcept;

// ****************************************
// ********** uBlock 256/256 **************
// ****************************************

void ublock256256_enc_key_init(UBlock256256RoundKey* round_key,
                               const std::uint8_t    user_key[32]) noexcept;

void ublock256256_dec_key_init(UBlock256256RoundKey* round_key,
                               const std::uint8_t    user_key[32]) noexcept;

void ublock256256_enc_block(const UBlock256256RoundKey* round_key,
                            std::uint8_t                ciphertext[32],
                            const std::uint8_t          plaintext[32]) noexcept;

void ublock256256_dec_block(const UBlock256256RoundKey* round_key,
                            std::uint8_t                plaintext[32],
                            const std::uint8_t ciphertext[32]) noexcept;

void ublock256256_enc_blocks(const UBlock256256RoundKey* round_key,
                             std::uint8_t*               ciphertext,
                             const std::uint8_t*         plaintext,
                             std::size_t                 block_num) noexcept;

void ublock256256_dec_blocks(const UBlock256256RoundKey* round_key,
                             std::uint8_t*               plaintext,
                             const std::uint8_t*         ciphertext,
                             std::size_t                 block_num) noexcept;

}; // namespace ublock::internal::common

#endif
#endif