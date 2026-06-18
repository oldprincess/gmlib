#ifndef UBLOCK_INTERNAL_PROVIDER_UBLOCK_STANDARD_H
#define UBLOCK_INTERNAL_PROVIDER_UBLOCK_STANDARD_H

#include "config.h"

#if defined(UBLOCK_IMPL_STANDARD)

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

namespace ublock::internal::standard {

using block_cipher_mode::BlockCipher;
using block_cipher_mode::BlockCipherMode;

bool provider_available();

std::unique_ptr<BlockCipher>     create_cipher_128128();
std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128128();
std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128128();
std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128128();
std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128128();
std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128128();
std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128128();
std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128128();
std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128128();
std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128128();
std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128128();
std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128128();
std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128128();

std::unique_ptr<BlockCipher>     create_cipher_128256();
std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128256();
std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128256();
std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128256();
std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128256();
std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128256();
std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128256();
std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128256();
std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128256();
std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128256();
std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128256();
std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128256();
std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128256();

std::unique_ptr<BlockCipher>     create_cipher_256256();
std::unique_ptr<BlockCipherMode> create_cbc_encryptor_256256();
std::unique_ptr<BlockCipherMode> create_cbc_decryptor_256256();
std::unique_ptr<BlockCipherMode> create_cfb_encryptor_256256();
std::unique_ptr<BlockCipherMode> create_cfb_decryptor_256256();
std::unique_ptr<BlockCipherMode> create_ctr_encryptor_256256();
std::unique_ptr<BlockCipherMode> create_ctr_decryptor_256256();
std::unique_ptr<BlockCipherMode> create_ofb_encryptor_256256();
std::unique_ptr<BlockCipherMode> create_ofb_decryptor_256256();
std::unique_ptr<BlockCipherMode> create_ecb_encryptor_256256();
std::unique_ptr<BlockCipherMode> create_ecb_decryptor_256256();

} // namespace ublock::internal::standard

#endif

#endif
