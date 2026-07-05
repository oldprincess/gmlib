#if defined(SUPPORT_AES_AESNI)

#ifndef AES_INTERNAL_PROVIDER_AES_AESNI_H
#define AES_INTERNAL_PROVIDER_AES_AESNI_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

namespace aes::internal::aesni {

using block_cipher_mode::BlockCipher;
using block_cipher_mode::BlockCipherMode;

bool provider_available();

std::unique_ptr<BlockCipher>     create_cipher_128();
std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128();
std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128();
std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128();
std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128();
std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128();
std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128();
std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128();
std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128();
std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128();
std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128();
std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128();
std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128();

std::unique_ptr<BlockCipher>     create_cipher_192();
std::unique_ptr<BlockCipherMode> create_cbc_encryptor_192();
std::unique_ptr<BlockCipherMode> create_cbc_decryptor_192();
std::unique_ptr<BlockCipherMode> create_cfb_encryptor_192();
std::unique_ptr<BlockCipherMode> create_cfb_decryptor_192();
std::unique_ptr<BlockCipherMode> create_ctr_encryptor_192();
std::unique_ptr<BlockCipherMode> create_ctr_decryptor_192();
std::unique_ptr<BlockCipherMode> create_ofb_encryptor_192();
std::unique_ptr<BlockCipherMode> create_ofb_decryptor_192();
std::unique_ptr<BlockCipherMode> create_ecb_encryptor_192();
std::unique_ptr<BlockCipherMode> create_ecb_decryptor_192();
std::unique_ptr<BlockCipherMode> create_gcm_encryptor_192();
std::unique_ptr<BlockCipherMode> create_gcm_decryptor_192();

std::unique_ptr<BlockCipher>     create_cipher_256();
std::unique_ptr<BlockCipherMode> create_cbc_encryptor_256();
std::unique_ptr<BlockCipherMode> create_cbc_decryptor_256();
std::unique_ptr<BlockCipherMode> create_cfb_encryptor_256();
std::unique_ptr<BlockCipherMode> create_cfb_decryptor_256();
std::unique_ptr<BlockCipherMode> create_ctr_encryptor_256();
std::unique_ptr<BlockCipherMode> create_ctr_decryptor_256();
std::unique_ptr<BlockCipherMode> create_ofb_encryptor_256();
std::unique_ptr<BlockCipherMode> create_ofb_decryptor_256();
std::unique_ptr<BlockCipherMode> create_ecb_encryptor_256();
std::unique_ptr<BlockCipherMode> create_ecb_decryptor_256();
std::unique_ptr<BlockCipherMode> create_gcm_encryptor_256();
std::unique_ptr<BlockCipherMode> create_gcm_decryptor_256();

} // namespace aes::internal::aesni

#endif

#endif
