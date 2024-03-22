#ifndef SM4_SM4_MODE_H
#define SM4_SM4_MODE_H

#include <gmlib/block_cipher_mode/cbc_mode.h>
#include <gmlib/block_cipher_mode/cfb_mode.h>
#include <gmlib/block_cipher_mode/ctr_mode.h>
#include <gmlib/block_cipher_mode/ecb_mode.h>
#include <gmlib/block_cipher_mode/gcm_mode.h>
#include <gmlib/block_cipher_mode/ofb_mode.h>
#include <gmlib/sm4/sm4.h>

namespace sm4 {

using SM4EcbEncryptor = block_cipher_mode::EcbEncryptor<SM4>;
using SM4EcbDecryptor = block_cipher_mode::EcbDecryptor<SM4>;

using SM4CbcEncryptor = block_cipher_mode::CbcEncryptor<SM4>;
using SM4CbcDecryptor = block_cipher_mode::CbcDecryptor<SM4>;

using SM4CfbEncryptor = block_cipher_mode::CfbEncryptor<SM4>;
using SM4CfbDecryptor = block_cipher_mode::CfbDecryptor<SM4>;

using SM4OfbEncryptor = block_cipher_mode::OfbEncryptor<SM4>;
using SM4OfbDecryptor = block_cipher_mode::OfbDecryptor<SM4>;

using SM4CtrEncryptor = block_cipher_mode::CtrEncryptor<SM4>;
using SM4CtrDecryptor = block_cipher_mode::CtrDecryptor<SM4>;

using SM4GcmEncryptor = block_cipher_mode::GcmEncryptor<SM4>;
using SM4GcmDecryptor = block_cipher_mode::GcmDecryptor<SM4>;

} // namespace sm4

#endif