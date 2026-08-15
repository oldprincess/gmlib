#if defined(SUPPORT_SM4_LANG18_AVX2)

#ifndef SM4_INTERNAL_PROVIDER_SM4_LANG18_AVX2_H
#define SM4_INTERNAL_PROVIDER_SM4_LANG18_AVX2_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_provider_impl.h>

namespace sm4::internal::lang18_avx2 {

extern const block_cipher_mode::impl::BlockCipherModeProviderEntry provider;

} // namespace sm4::internal::lang18_avx2

#endif

#endif
