#if defined(SUPPORT_SM4_GONG23_AESNI)

#ifndef SM4_INTERNAL_PROVIDER_SM4_GONG23_AESNI_H
#define SM4_INTERNAL_PROVIDER_SM4_GONG23_AESNI_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_provider_impl.h>

namespace sm4::internal::gong23_aesni {

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry provider;

} // namespace sm4::internal::gong23_aesni

#endif

#endif
