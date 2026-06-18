#ifndef BALLET_BALLET_MODE_H
#define BALLET_BALLET_MODE_H

#include <gmlib/ballet/ballet.h>
#include <gmlib/block_cipher_mode/cbc_mode.h>
#include <gmlib/block_cipher_mode/cfb_mode.h>
#include <gmlib/block_cipher_mode/ctr_mode.h>
#include <gmlib/block_cipher_mode/ecb_mode.h>
#include <gmlib/block_cipher_mode/gcm_mode.h>
#include <gmlib/block_cipher_mode/ofb_mode.h>

namespace ballet {

using Ballet128128EcbEncryptor = block_cipher_mode::EcbEncryptor<Ballet128128>;
using Ballet128256EcbEncryptor = block_cipher_mode::EcbEncryptor<Ballet128256>;
using Ballet256256EcbEncryptor = block_cipher_mode::EcbEncryptor<Ballet256256>;
using Ballet128128EcbDecryptor = block_cipher_mode::EcbDecryptor<Ballet128128>;
using Ballet128256EcbDecryptor = block_cipher_mode::EcbDecryptor<Ballet128256>;
using Ballet256256EcbDecryptor = block_cipher_mode::EcbDecryptor<Ballet256256>;

using Ballet128128CbcEncryptor = block_cipher_mode::CbcEncryptor<Ballet128128>;
using Ballet128256CbcEncryptor = block_cipher_mode::CbcEncryptor<Ballet128256>;
using Ballet256256CbcEncryptor = block_cipher_mode::CbcEncryptor<Ballet256256>;
using Ballet128128CbcDecryptor = block_cipher_mode::CbcDecryptor<Ballet128128>;
using Ballet128256CbcDecryptor = block_cipher_mode::CbcDecryptor<Ballet128256>;
using Ballet256256CbcDecryptor = block_cipher_mode::CbcDecryptor<Ballet256256>;

using Ballet128128CfbEncryptor = block_cipher_mode::CfbEncryptor<Ballet128128>;
using Ballet128256CfbEncryptor = block_cipher_mode::CfbEncryptor<Ballet128256>;
using Ballet256256CfbEncryptor = block_cipher_mode::CfbEncryptor<Ballet256256>;
using Ballet128128CfbDecryptor = block_cipher_mode::CfbDecryptor<Ballet128128>;
using Ballet128256CfbDecryptor = block_cipher_mode::CfbDecryptor<Ballet128256>;
using Ballet256256CfbDecryptor = block_cipher_mode::CfbDecryptor<Ballet256256>;

using Ballet128128OfbEncryptor = block_cipher_mode::OfbEncryptor<Ballet128128>;
using Ballet128256OfbEncryptor = block_cipher_mode::OfbEncryptor<Ballet128256>;
using Ballet256256OfbEncryptor = block_cipher_mode::OfbEncryptor<Ballet256256>;
using Ballet128128OfbDecryptor = block_cipher_mode::OfbDecryptor<Ballet128128>;
using Ballet128256OfbDecryptor = block_cipher_mode::OfbDecryptor<Ballet128256>;
using Ballet256256OfbDecryptor = block_cipher_mode::OfbDecryptor<Ballet256256>;

using Ballet128128CtrEncryptor = block_cipher_mode::CtrEncryptor<Ballet128128>;
using Ballet128256CtrEncryptor = block_cipher_mode::CtrEncryptor<Ballet128256>;
using Ballet256256CtrEncryptor = block_cipher_mode::CtrEncryptor<Ballet256256>;
using Ballet128128CtrDecryptor = block_cipher_mode::CtrDecryptor<Ballet128128>;
using Ballet128256CtrDecryptor = block_cipher_mode::CtrDecryptor<Ballet128256>;
using Ballet256256CtrDecryptor = block_cipher_mode::CtrDecryptor<Ballet256256>;

using Ballet128128GcmEncryptor = block_cipher_mode::GcmEncryptor<Ballet128128>;
using Ballet128256GcmEncryptor = block_cipher_mode::GcmEncryptor<Ballet128256>;
using Ballet128128GcmDecryptor = block_cipher_mode::GcmDecryptor<Ballet128128>;
using Ballet128256GcmDecryptor = block_cipher_mode::GcmDecryptor<Ballet128256>;

} // namespace ballet

#endif
