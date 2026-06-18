#ifndef UBLOCK_UBLOCK_MODE_H
#define UBLOCK_UBLOCK_MODE_H

#include <gmlib/block_cipher_mode/cbc_mode.h>
#include <gmlib/block_cipher_mode/cfb_mode.h>
#include <gmlib/block_cipher_mode/ctr_mode.h>
#include <gmlib/block_cipher_mode/ecb_mode.h>
#include <gmlib/block_cipher_mode/gcm_mode.h>
#include <gmlib/block_cipher_mode/ofb_mode.h>
#include <gmlib/ublock/ublock.h>

namespace ublock {

using uBlock128128EcbEncryptor = block_cipher_mode::EcbEncryptor<uBlock128128>;
using uBlock128256EcbEncryptor = block_cipher_mode::EcbEncryptor<uBlock128256>;
using uBlock256256EcbEncryptor = block_cipher_mode::EcbEncryptor<uBlock256256>;
using uBlock128128EcbDecryptor = block_cipher_mode::EcbDecryptor<uBlock128128>;
using uBlock128256EcbDecryptor = block_cipher_mode::EcbDecryptor<uBlock128256>;
using uBlock256256EcbDecryptor = block_cipher_mode::EcbDecryptor<uBlock256256>;

using uBlock128128CbcEncryptor = block_cipher_mode::CbcEncryptor<uBlock128128>;
using uBlock128256CbcEncryptor = block_cipher_mode::CbcEncryptor<uBlock128256>;
using uBlock256256CbcEncryptor = block_cipher_mode::CbcEncryptor<uBlock256256>;
using uBlock128128CbcDecryptor = block_cipher_mode::CbcDecryptor<uBlock128128>;
using uBlock128256CbcDecryptor = block_cipher_mode::CbcDecryptor<uBlock128256>;
using uBlock256256CbcDecryptor = block_cipher_mode::CbcDecryptor<uBlock256256>;

using uBlock128128CfbEncryptor = block_cipher_mode::CfbEncryptor<uBlock128128>;
using uBlock128256CfbEncryptor = block_cipher_mode::CfbEncryptor<uBlock128256>;
using uBlock256256CfbEncryptor = block_cipher_mode::CfbEncryptor<uBlock256256>;
using uBlock128128CfbDecryptor = block_cipher_mode::CfbDecryptor<uBlock128128>;
using uBlock128256CfbDecryptor = block_cipher_mode::CfbDecryptor<uBlock128256>;
using uBlock256256CfbDecryptor = block_cipher_mode::CfbDecryptor<uBlock256256>;

using uBlock128128OfbEncryptor = block_cipher_mode::OfbEncryptor<uBlock128128>;
using uBlock128256OfbEncryptor = block_cipher_mode::OfbEncryptor<uBlock128256>;
using uBlock256256OfbEncryptor = block_cipher_mode::OfbEncryptor<uBlock256256>;
using uBlock128128OfbDecryptor = block_cipher_mode::OfbDecryptor<uBlock128128>;
using uBlock128256OfbDecryptor = block_cipher_mode::OfbDecryptor<uBlock128256>;
using uBlock256256OfbDecryptor = block_cipher_mode::OfbDecryptor<uBlock256256>;

using uBlock128128CtrEncryptor = block_cipher_mode::CtrEncryptor<uBlock128128>;
using uBlock128256CtrEncryptor = block_cipher_mode::CtrEncryptor<uBlock128256>;
using uBlock256256CtrEncryptor = block_cipher_mode::CtrEncryptor<uBlock256256>;
using uBlock128128CtrDecryptor = block_cipher_mode::CtrDecryptor<uBlock128128>;
using uBlock128256CtrDecryptor = block_cipher_mode::CtrDecryptor<uBlock128256>;
using uBlock256256CtrDecryptor = block_cipher_mode::CtrDecryptor<uBlock256256>;

using uBlock128128GcmEncryptor = block_cipher_mode::GcmEncryptor<uBlock128128>;
using uBlock128256GcmEncryptor = block_cipher_mode::GcmEncryptor<uBlock128256>;
using uBlock128128GcmDecryptor = block_cipher_mode::GcmDecryptor<uBlock128128>;
using uBlock128256GcmDecryptor = block_cipher_mode::GcmDecryptor<uBlock128256>;

} // namespace ublock

#endif
