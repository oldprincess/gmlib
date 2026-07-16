#ifndef AES_PROVIDER_H
#define AES_PROVIDER_H

#include <gmlib/block_cipher_mode/provider.h>

namespace aes {

using AES128Provider = block_cipher_mode::BlockCipherModeProvider;
using AES192Provider = block_cipher_mode::BlockCipherModeProvider;
using AES256Provider = block_cipher_mode::BlockCipherModeProvider;

/**
 * @brief   Get the AES-128 block cipher and mode provider.
 * @param   name  Provider name. Pass @c nullptr for the default (highest
 *                priority available backend).
 * @return  Pointer to the provider, or @c nullptr if the named provider
 *          is unavailable.
 * @note    The function pointers in the returned provider must be checked
 *          for @c nullptr before use.
 */
const AES128Provider* get_aes128_provider(const char* name) noexcept;

/**
 * @brief   Get the list of available AES-128 provider names.
 * @return  Null-terminated array of provider name strings. The array is
 *          statically allocated and must not be freed by the caller.
 */
const char* const* get_aes128_supported_provider_names() noexcept;

/**
 * @brief   Get the AES-192 block cipher and mode provider.
 * @param   name  Provider name. Pass @c nullptr for the default (highest
 *                priority available backend).
 * @return  Pointer to the provider, or @c nullptr if the named provider
 *          is unavailable.
 * @note    The function pointers in the returned provider must be checked
 *          for @c nullptr before use.
 */
const AES192Provider* get_aes192_provider(const char* name) noexcept;

/**
 * @brief   Get the list of available AES-192 provider names.
 * @return  Null-terminated array of provider name strings. The array is
 *      statically allocated and must not be freed by the caller.
 */
const char* const* get_aes192_supported_provider_names() noexcept;

/**
 * @brief   Get the AES-256 block cipher and mode provider.
 * @param   name  Provider name. Pass @c nullptr for the default (highest
 *                priority available backend).
 * @return  Pointer to the provider, or @c nullptr if the named provider
 *          is unavailable.
 * @note    The function pointers in the returned provider must be checked
 *          for @c nullptr before use.
 */
const AES256Provider* get_aes256_provider(const char* name) noexcept;

/**
 * @brief   Get the list of available AES-256 provider names.
 * @return  Null-terminated array of provider name strings. The array is
 *          statically allocated and must not be freed by the caller.
 */
const char* const* get_aes256_supported_provider_names() noexcept;

} // namespace aes

#endif
