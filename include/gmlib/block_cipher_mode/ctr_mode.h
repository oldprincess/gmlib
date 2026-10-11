#ifndef BLOCK_CIPHER_MODE_CTR_MODE_H
#define BLOCK_CIPHER_MODE_CTR_MODE_H

#include <gmlib/block_cipher_mode/impl/block_cipher_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>

namespace block_cipher_mode {

template <typename BlockCipher>
using CtrEncryptor = impl::CtrEncryptorImpl<BlockCipher>;

template <typename BlockCipher>
using CtrDecryptor = impl::CtrDecryptorImpl<BlockCipher>;

} // namespace block_cipher_mode

#endif
