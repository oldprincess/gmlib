#ifndef BLOCK_CIPHER_MODE_ECB_MODE_H
#define BLOCK_CIPHER_MODE_ECB_MODE_H

#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>

namespace block_cipher_mode {

template <class BlockCipher>
using EcbEncryptor = impl::EcbEncryptorImpl<BlockCipher>;

template <class BlockCipher>
using EcbDecryptor = impl::EcbDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif