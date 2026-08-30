#if defined(SUPPORT_UBLOCK_STANDARD)

#ifndef UBLOCK_INTERNAL_PROVIDER_UBLOCK_STANDARD_H
#define UBLOCK_INTERNAL_PROVIDER_UBLOCK_STANDARD_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_provider_impl.h>

namespace ublock::internal::standard {

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry
    provider_128128;
extern const block_cipher_mode::impl::BlockCipherModeProviderEntry
    provider_128256;
extern const block_cipher_mode::impl::BlockCipherModeProviderEntry
    provider_256256;

} // namespace ublock::internal::standard

#endif

#endif
