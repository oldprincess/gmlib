#ifndef DES_DES_MODE_H
#define DES_DES_MODE_H

#include <gmlib/block_cipher_mode/cbc_mode.h>
#include <gmlib/block_cipher_mode/cfb_mode.h>
#include <gmlib/block_cipher_mode/ctr_mode.h>
#include <gmlib/block_cipher_mode/ecb_mode.h>
#include <gmlib/block_cipher_mode/ofb_mode.h>
#include <gmlib/des/des.h>

namespace des {

using DESEcbEncryptor = block_cipher_mode::EcbEncryptor<DES>;
using DESEcbDecryptor = block_cipher_mode::EcbDecryptor<DES>;

using DESCbcEncryptor = block_cipher_mode::CbcEncryptor<DES>;
using DESCbcDecryptor = block_cipher_mode::CbcDecryptor<DES>;

using DESCfbEncryptor = block_cipher_mode::CfbEncryptor<DES>;
using DESCfbDecryptor = block_cipher_mode::CfbDecryptor<DES>;

using DESOfbEncryptor = block_cipher_mode::OfbEncryptor<DES>;
using DESOfbDecryptor = block_cipher_mode::OfbDecryptor<DES>;

using DESCtrEncryptor = block_cipher_mode::CtrEncryptor<DES>;
using DESCtrDecryptor = block_cipher_mode::CtrDecryptor<DES>;

} // namespace des

#endif