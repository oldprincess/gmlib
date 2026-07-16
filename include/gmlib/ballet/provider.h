#ifndef BALLET_PROVIDER_H
#define BALLET_PROVIDER_H

#include <gmlib/block_cipher_mode/provider.h>

namespace ballet {

using Ballet128128Provider = block_cipher_mode::BlockCipherModeProvider;
using Ballet128256Provider = block_cipher_mode::BlockCipherModeProvider;
using Ballet256256Provider = block_cipher_mode::BlockCipherModeProvider;

const Ballet128128Provider* get_ballet128128_provider(
    const char* name) noexcept;
const char* const* get_ballet128128_supported_provider_names() noexcept;

const Ballet128256Provider* get_ballet128256_provider(
    const char* name) noexcept;
const char* const* get_ballet128256_supported_provider_names() noexcept;

const Ballet256256Provider* get_ballet256256_provider(
    const char* name) noexcept;
const char* const* get_ballet256256_supported_provider_names() noexcept;

} // namespace ballet

#endif
