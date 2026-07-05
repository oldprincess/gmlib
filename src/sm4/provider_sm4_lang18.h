#if defined(SUPPORT_SM4_LANG18)

#ifndef SM4_INTERNAL_PROVIDER_SM4_LANG18_H
#define SM4_INTERNAL_PROVIDER_SM4_LANG18_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/block_cipher_mode/block_cipher_mode.h>

namespace sm4::internal::lang18 {

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

std::unique_ptr<BlockCipherMode> create_gcm_encryptor();

std::unique_ptr<BlockCipherMode> create_gcm_decryptor();

} // namespace sm4::internal::lang18

#endif

#endif
