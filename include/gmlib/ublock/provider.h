#ifndef UBLOCK_PROVIDER_H
#define UBLOCK_PROVIDER_H

#include <gmlib/block_cipher_mode/provider.h>

namespace ublock {

using uBlock128128Provider = block_cipher_mode::BlockCipherModeProvider;
using uBlock128256Provider = block_cipher_mode::BlockCipherModeProvider;
using uBlock256256Provider = block_cipher_mode::BlockCipherModeProvider;

/**
 * @brief   Get the uBlock-128-128 block cipher and mode provider.
 * @param   name  Provider name. Pass @c nullptr for the default (highest
 *                priority available backend).
 * @return  Pointer to the provider, or @c nullptr if the named provider
 *          is unavailable.
 * @note    The function pointers in the returned provider must be checked
 *          for @c nullptr before use.
 */
const uBlock128128Provider* get_ublock128128_provider(
    const char* name) noexcept;

/**
 * @brief   Get the list of available uBlock-128-128 provider names.
 * @return  Null-terminated array of provider name strings. The array is
 *          statically allocated and must not be freed by the caller.
 */
const char* const* get_ublock128128_supported_provider_names() noexcept;

/**
 * @brief   Get the uBlock-128-256 block cipher and mode provider.
 * @param   name  Provider name. Pass @c nullptr for the default (highest
 *                priority available backend).
 * @return  Pointer to the provider, or @c nullptr if the named provider
 *          is unavailable.
 * @note    The function pointers in the returned provider must be checked
 *          for @c nullptr before use.
 */
const uBlock128256Provider* get_ublock128256_provider(
    const char* name) noexcept;

/**
 * @brief   Get the list of available uBlock-128-256 provider names.
 * @return  Null-terminated array of provider name strings. The array is
 *          statically allocated and must not be freed by the caller.
 */
const char* const* get_ublock128256_supported_provider_names() noexcept;

/**
 * @brief   Get the uBlock-256-256 block cipher and mode provider.
 * @param   name  Provider name. Pass @c nullptr for the default (highest
 *                priority available backend).
 * @return  Pointer to the provider, or @c nullptr if the named provider
 *          is unavailable.
 * @note    The function pointers in the returned provider must be checked
 *          for @c nullptr before use.
 */
const uBlock256256Provider* get_ublock256256_provider(
    const char* name) noexcept;

/**
 * @brief   Get the list of available uBlock-256-256 provider names.
 * @return  Null-terminated array of provider name strings. The array is
 *          statically allocated and must not be freed by the caller.
 */
const char* const* get_ublock256256_supported_provider_names() noexcept;

} // namespace ublock

#endif
