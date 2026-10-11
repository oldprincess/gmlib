#if defined(SUPPORT_AES_AESNI)

#ifndef AES_INTERNAL_PROVIDER_AES_AESNI_H
#define AES_INTERNAL_PROVIDER_AES_AESNI_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_provider_impl.h>

namespace aes::internal::aesni {

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_128;

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_192;

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry provider_256;

} // namespace aes::internal::aesni

#endif

#endif
