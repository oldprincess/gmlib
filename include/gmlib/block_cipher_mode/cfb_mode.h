#ifndef BLOCK_CIPHER_MODE_CFB_MODE_H
#define BLOCK_CIPHER_MODE_CFB_MODE_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>

namespace block_cipher_mode {

template <typename BlockCipher>
using CfbEncryptor = impl::CfbEncryptorImpl<BlockCipher>;

template <typename BlockCipher>
using CfbDecryptor = impl::CfbDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif
