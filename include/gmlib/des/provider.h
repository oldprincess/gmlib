#ifndef DES_PROVIDER_H
#define DES_PROVIDER_H

#include <gmlib/block_cipher_mode/provider.h>

namespace des {

using DESProvider = block_cipher_mode::BlockCipherModeProvider;

const DESProvider* get_des_provider(const char* name) noexcept;

const char* const* get_des_supported_provider_names() noexcept;

} // namespace des

#endif
