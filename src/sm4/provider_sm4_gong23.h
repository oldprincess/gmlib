#if defined(SUPPORT_SM4_GONG23)

#ifndef SM4_INTERNAL_PROVIDER_SM4_GONG23_H
#define SM4_INTERNAL_PROVIDER_SM4_GONG23_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_provider_impl.h>

namespace sm4::internal::gong23 {

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry provider;

} // namespace sm4::internal::gong23

#endif

#endif
