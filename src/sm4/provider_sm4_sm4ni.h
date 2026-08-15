#if defined(SUPPORT_SM4_SM4NI)

#ifndef SM4_INTERNAL_PROVIDER_SM4_SM4NI_H
#define SM4_INTERNAL_PROVIDER_SM4_SM4NI_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_provider_impl.h>

namespace sm4::internal::sm4ni {

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry provider;

} // namespace sm4::internal::sm4ni

#endif

#endif
