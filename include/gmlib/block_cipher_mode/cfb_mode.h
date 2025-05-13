#ifndef BLOCK_CIPHER_MODE_CFB_MODE_H
#define BLOCK_CIPHER_MODE_CFB_MODE_H

#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>

namespace block_cipher_mode {

template <class BlockCipher>
using CfbEncryptor = impl::CfbEncryptorImpl<BlockCipher>;

template <class BlockCipher>
using CfbDecryptor = impl::CfbDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif