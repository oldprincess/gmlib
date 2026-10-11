#ifndef BLOCK_CIPHER_MODE_CBC_MODE_H
#define BLOCK_CIPHER_MODE_CBC_MODE_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>

namespace block_cipher_mode {

template <typename BlockCipher>
using CbcEncryptor = impl::CbcEncryptorImpl<BlockCipher>;

template <typename BlockCipher>
using CbcDecryptor = impl::CbcDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif
