#ifndef AES_AES_MODE_H
#define AES_AES_MODE_H

#include <gmlib/aes/aes.h>
#include <gmlib/block_cipher_mode/cbc_mode.h>
#include <gmlib/block_cipher_mode/cfb_mode.h>
#include <gmlib/block_cipher_mode/ctr_mode.h>
#include <gmlib/block_cipher_mode/ecb_mode.h>
#include <gmlib/block_cipher_mode/gcm_mode.h>
#include <gmlib/block_cipher_mode/ofb_mode.h>

namespace aes {

using AES128EcbEncryptor = block_cipher_mode::EcbEncryptor<AES128>;
using AES192EcbEncryptor = block_cipher_mode::EcbEncryptor<AES192>;
using AES256EcbEncryptor = block_cipher_mode::EcbEncryptor<AES256>;
using AES128EcbDecryptor = block_cipher_mode::EcbDecryptor<AES128>;
using AES192EcbDecryptor = block_cipher_mode::EcbDecryptor<AES192>;
using AES256EcbDecryptor = block_cipher_mode::EcbDecryptor<AES256>;

using AES128CbcEncryptor = block_cipher_mode::CbcEncryptor<AES128>;
using AES192CbcEncryptor = block_cipher_mode::CbcEncryptor<AES192>;
using AES256CbcEncryptor = block_cipher_mode::CbcEncryptor<AES256>;
using AES128CbcDecryptor = block_cipher_mode::CbcDecryptor<AES128>;
using AES192CbcDecryptor = block_cipher_mode::CbcDecryptor<AES192>;
using AES256CbcDecryptor = block_cipher_mode::CbcDecryptor<AES256>;

using AES128CfbEncryptor = block_cipher_mode::CfbEncryptor<AES128>;
using AES192CfbEncryptor = block_cipher_mode::CfbEncryptor<AES192>;
using AES256CfbEncryptor = block_cipher_mode::CfbEncryptor<AES256>;
using AES128CfbDecryptor = block_cipher_mode::CfbDecryptor<AES128>;
using AES192CfbDecryptor = block_cipher_mode::CfbDecryptor<AES192>;
using AES256CfbDecryptor = block_cipher_mode::CfbDecryptor<AES256>;

using AES128OfbEncryptor = block_cipher_mode::OfbEncryptor<AES128>;
using AES192OfbEncryptor = block_cipher_mode::OfbEncryptor<AES192>;
using AES256OfbEncryptor = block_cipher_mode::OfbEncryptor<AES256>;
using AES128OfbDecryptor = block_cipher_mode::OfbDecryptor<AES128>;
using AES192OfbDecryptor = block_cipher_mode::OfbDecryptor<AES192>;
using AES256OfbDecryptor = block_cipher_mode::OfbDecryptor<AES256>;

using AES128CtrEncryptor = block_cipher_mode::CtrEncryptor<AES128>;
using AES192CtrEncryptor = block_cipher_mode::CtrEncryptor<AES192>;
using AES256CtrEncryptor = block_cipher_mode::CtrEncryptor<AES256>;
using AES128CtrDecryptor = block_cipher_mode::CtrDecryptor<AES128>;
using AES192CtrDecryptor = block_cipher_mode::CtrDecryptor<AES192>;
using AES256CtrDecryptor = block_cipher_mode::CtrDecryptor<AES256>;

using AES128GcmEncryptor = block_cipher_mode::GcmEncryptor<AES128>;
using AES192GcmEncryptor = block_cipher_mode::GcmEncryptor<AES192>;
using AES256GcmEncryptor = block_cipher_mode::GcmEncryptor<AES256>;
using AES128GcmDecryptor = block_cipher_mode::GcmDecryptor<AES128>;
using AES192GcmDecryptor = block_cipher_mode::GcmDecryptor<AES192>;
using AES256GcmDecryptor = block_cipher_mode::GcmDecryptor<AES256>;

} // namespace aes

#endif