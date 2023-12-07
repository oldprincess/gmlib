#include <gmlib/crypto/mac/HMacCipher.h>
#include <gmlib/crypto/hash/Md5Cipher.h>
#include <TinyCrypto/encoding/str/hexadecimal.h>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

using namespace gmlib;
using namespace std;

typedef HMacCipher<Md5Cipher> Md5HMac;

void TestHMacCipher()
{
    // test 1
    {
        const char* key_hex    = "0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b";
        const char* data_str   = "Hi There";
        const char* digest_hex = "9294727a3638bb1c13f48ef8158bfc9d";

        uint8_t key[16], data[8], digest[16], need_digest[16];
        tc::hex_to_u8array(key, key_hex, 32);
        memcpy(data, data_str, 8);
        tc::hex_to_u8array(need_digest, digest_hex, 32);
        Md5HMac::compute(digest, key, 16, data, 8);
        if (memcmp(need_digest, digest, 16) != 0)
        {
            throw std::runtime_error("Err in Md5 HMac");
        }
    }
    // test 2
    {
        const char* key_str    = "Jefe";
        const char* data_str   = "what do ya want for nothing?";
        const char* digest_hex = "750c783e6ab0b503eaa86e310a5db738";

        uint8_t key[4], data[28], digest[16], need_digest[16];
        memcpy(key, key_str, 4);
        memcpy(data, data_str, 28);
        tc::hex_to_u8array(need_digest, digest_hex, 32);
        Md5HMac::compute(digest, key, 4, data, 28);
        if (memcmp(need_digest, digest, 16) != 0)
        {
            throw std::runtime_error("Err in Md5 HMac");
        }
    }
    // test 3
    {
        const char* key_hex    = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        const char* digest_hex = "56be34521d144c88dbb8c733f0e8b3f6";

        uint8_t key[16], data[50], digest[16], need_digest[16];
        tc::hex_to_u8array(key, key_hex, 32);
        memset(data, 0xDD, 50);
        tc::hex_to_u8array(need_digest, digest_hex, 32);
        Md5HMac::compute(digest, key, 16, data, 50);
        if (memcmp(need_digest, digest, 16) != 0)
        {
            throw std::runtime_error("Err in Md5 HMac");
        }
    }
}