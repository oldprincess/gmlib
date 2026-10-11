#ifndef BLOCK_CIPHER_MODE_OFB_MODE_H
#define BLOCK_CIPHER_MODE_OFB_MODE_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>

namespace block_cipher_mode {

template <typename BlockCipher>
using OfbEncryptor = impl::OfbEncryptorImpl<BlockCipher>;

template <typename BlockCipher>
using OfbDecryptor = impl::OfbDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif
