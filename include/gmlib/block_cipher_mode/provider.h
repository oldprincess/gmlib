#ifndef BLOCK_CIPHER_MODE_PROVIDER_H
#define BLOCK_CIPHER_MODE_PROVIDER_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <cstddef>
#include <cstdint>
#include <memory>

namespace block_cipher_mode {

struct BlockCipherModeProvider
{
    /** @brief Implementation name. */
    const char* algo_name;

    /**
     * @brief  Create a new block cipher instance.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipher> (*create_cipher)() = nullptr;

    /**
     * @brief  Create a new ECB mode encryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_ecb_encryptor)() = nullptr;

    /**
     * @brief  Create a new ECB mode decryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_ecb_decryptor)() = nullptr;

    /**
     * @brief  Create a new CBC mode encryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_cbc_encryptor)() = nullptr;

    /**
     * @brief  Create a new CBC mode decryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_cbc_decryptor)() = nullptr;

    /**
     * @brief  Create a new CFB mode encryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_cfb_encryptor)() = nullptr;

    /**
     * @brief  Create a new CFB mode decryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_cfb_decryptor)() = nullptr;

    /**
     * @brief  Create a new OFB mode encryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_ofb_encryptor)() = nullptr;

    /**
     * @brief  Create a new OFB mode decryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_ofb_decryptor)() = nullptr;

    /**
     * @brief  Create a new CTR mode encryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_ctr_encryptor)() = nullptr;

    /**
     * @brief  Create a new CTR mode decryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_ctr_decryptor)() = nullptr;

    /**
     * @brief  Create a new GCM mode encryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_gcm_encryptor)() = nullptr;

    /**
     * @brief  Create a new GCM mode decryptor.
     * @note   The function pointer must be checked for @c nullptr before use.
     */
    std::unique_ptr<BlockCipherMode> (*create_gcm_decryptor)() = nullptr;
};

} // namespace block_cipher_mode

#endif
