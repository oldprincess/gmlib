#include <gmlib/crypto_ex/UBlockCipher_Standard.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

using namespace gmlib;
using namespace std;

// redefine class name, simplify
using UBlock128128CipherEx = UBlock128128Cipher_Standard;
using UBlock128256CipherEx = UBlock128256Cipher_Standard;
using UBlock256256CipherEx = UBlock256256Cipher_Standard;

void TestUBlockCipher_Standard()
{
    static uint8_t key128128[16] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
    };
    static uint8_t pt128128[16] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
    };
    static uint8_t ct128128[16] = {
        0x32, 0x12, 0x2b, 0xed, 0xd0, 0x23, 0xc4, 0x29,
        0x02, 0x34, 0x70, 0xe1, 0x15, 0x8c, 0x14, 0x7d,
    };
    uint8_t out[32];

    auto ublock128128 = UBlock128128CipherEx();
    ublock128128.set_key(key128128, UBlock128128CipherEx::ENCRYPTION);
    ublock128128.crypt_block(out, pt128128);
    if (memcmp(ct128128, out, UBlock128128CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Encryption Mode");
    }
    ublock128128.crypt_blocks(out, pt128128, 1);
    if (memcmp(ct128128, out, UBlock128128CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Encryption Mode");
    }
    ublock128128.set_key(key128128, UBlock128128CipherEx::DECRYPTION);
    ublock128128.crypt_block(out, ct128128);
    if (memcmp(pt128128, out, UBlock128128CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Decryption Mode");
    }
    ublock128128.crypt_blocks(out, ct128128, 1);
    if (memcmp(pt128128, out, UBlock128128CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Decryption Mode");
    }

    static uint8_t key128256[32] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, //
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    };
    static uint8_t pt128256[16] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
    };
    static uint8_t ct128256[16] = {
        0x64, 0xac, 0xcd, 0x6e, 0x34, 0xca, 0xc8, 0x4d,
        0x38, 0x4c, 0xd4, 0xba, 0x7a, 0xea, 0xdd, 0x19,
    };

    auto ublock128256 = UBlock128256CipherEx();
    ublock128256.set_key(key128256, UBlock128256CipherEx::ENCRYPTION);
    ublock128256.crypt_block(out, pt128256);
    if (memcmp(ct128256, out, UBlock128256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Encryption Mode");
    }
    ublock128256.crypt_blocks(out, pt128256, 1);
    if (memcmp(ct128256, out, UBlock128256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Encryption Mode");
    }
    ublock128256.set_key(key128256, UBlock128256CipherEx::DECRYPTION);
    ublock128256.crypt_block(out, ct128256);
    if (memcmp(pt128256, out, UBlock128256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Decryption Mode");
    }
    ublock128256.crypt_blocks(out, ct128256, 1);
    if (memcmp(pt128256, out, UBlock128256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Decryption Mode");
    }

    static uint8_t key256256[32] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, //
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    };
    static uint8_t pt256256[32] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, //
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    };
    static uint8_t ct256256[32] = {
        0xd8, 0xe9, 0x35, 0x1c, 0x5f, 0x4d, 0x27, 0xea,
        0x84, 0x21, 0x35, 0xca, 0x16, 0x40, 0xad, 0x4b, //
        0x0c, 0xe1, 0x19, 0xbc, 0x25, 0xc0, 0x3e, 0x7c,
        0x32, 0x9e, 0xa8, 0xfe, 0x93, 0xe7, 0xbd, 0xfe,
    };

    auto ublock256256 = UBlock256256CipherEx();
    ublock256256.set_key(key256256, UBlock256256CipherEx::ENCRYPTION);
    ublock256256.crypt_block(out, pt256256);
    if (memcmp(ct256256, out, UBlock256256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Encryption Mode");
    }
    ublock256256.crypt_blocks(out, pt256256, 1);
    if (memcmp(ct256256, out, UBlock256256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Encryption Mode");
    }
    ublock256256.set_key(key256256, UBlock256256CipherEx::DECRYPTION);
    ublock256256.crypt_block(out, ct256256);
    if (memcmp(pt256256, out, UBlock256256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Decryption Mode");
    }
    ublock256256.crypt_blocks(out, ct256256, 1);
    if (memcmp(pt256256, out, UBlock256256CipherEx::BLOCK_SIZE) != 0)
    {
        throw std::exception("Error in UBlockCipher Decryption Mode");
    }
}