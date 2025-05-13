#ifndef BLOCK_CIPHER_MODE_OFB_MODE_H
#define BLOCK_CIPHER_MODE_OFB_MODE_H

#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>

namespace block_cipher_mode {

template <class BlockCipher>
using OfbEncryptor = impl::OfbEncryptorImpl<BlockCipher>;

template <class BlockCipher>
using OfbDecryptor = impl::OfbDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif