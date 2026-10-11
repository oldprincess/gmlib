#ifndef BLOCK_CIPHER_MODE_GCM_MODE_H
#define BLOCK_CIPHER_MODE_GCM_MODE_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>

namespace block_cipher_mode {

template <typename BlockCipher>
using GcmEncryptor = impl::GcmEncryptorImpl<BlockCipher>;

template <typename BlockCipher>
using GcmDecryptor = impl::GcmDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif
