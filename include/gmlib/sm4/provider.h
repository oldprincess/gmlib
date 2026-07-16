#ifndef SM4_PROVIDER_H
#define SM4_PROVIDER_H

#include <gmlib/block_cipher_mode/provider.h>

namespace sm4 {

using SM4Provider = block_cipher_mode::BlockCipherModeProvider;

const SM4Provider* get_sm4_provider(const char* name) noexcept;

const char* const* get_sm4_supported_provider_names() noexcept;

} // namespace sm4

#endif
