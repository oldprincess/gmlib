#ifndef BLOCK_CIPHER_MODE_CBC_MODE_H
#define BLOCK_CIPHER_MODE_CBC_MODE_H

#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>

namespace block_cipher_mode {

template <class BlockCipher>
using CbcEncryptor = impl::CbcEncryptorImpl<BlockCipher>;

template <class BlockCipher>
using CbcDecryptor = impl::CbcDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif