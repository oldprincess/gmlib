#ifndef DES_INTERNAL_PROVIDER_DES_COMMON_H
#define DES_INTERNAL_PROVIDER_DES_COMMON_H

#include "config.h"

#if defined(DES_IMPL_COMMON)

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

namespace des::internal::common {

using block_cipher_mode::BlockCipher;
using block_cipher_mode::BlockCipherMode;

bool provider_available();

std::unique_ptr<BlockCipher> create_cipher();

std::unique_ptr<BlockCipherMode> create_cbc_encryptor();

std::unique_ptr<BlockCipherMode> create_cbc_decryptor();

std::unique_ptr<BlockCipherMode> create_cfb_encryptor();

std::unique_ptr<BlockCipherMode> create_cfb_decryptor();

std::unique_ptr<BlockCipherMode> create_ctr_encryptor();

std::unique_ptr<BlockCipherMode> create_ctr_decryptor();

std::unique_ptr<BlockCipherMode> create_ofb_encryptor();

std::unique_ptr<BlockCipherMode> create_ofb_decryptor();

std::unique_ptr<BlockCipherMode> create_ecb_encryptor();

std::unique_ptr<BlockCipherMode> create_ecb_decryptor();

} // namespace des::internal::common

#endif

#endif