#ifndef BALLET_INTERNAL_PROVIDER_BALLET_STANDARD_H
#define BALLET_INTERNAL_PROVIDER_BALLET_STANDARD_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_provider_impl.h>

namespace ballet::internal::standard {

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry
    provider_128128;
extern const block_cipher_mode::impl::BlockCipherModeProviderEntry
    provider_128256;
extern const block_cipher_mode::impl::BlockCipherModeProviderEntry
    provider_256256;

} // namespace ballet::internal::standard

#endif
