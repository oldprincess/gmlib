/**
 * PKCS #5: Password-Based Key Derivation Function 2 (PBKDF2) Test Vectors
 * bsd license
 *
 * Copyright (c) 2011 IETF Trust and the persons identified as the document
 * authors.  All rights reserved.
 *
 * https://www.rfc-editor.org/rfc/rfc6070#page-2
 */

#include <gmlib/crypto/kdf/pbkdf2.h>
#include <gmlib/crypto/hash/Sha1Cipher.h>
#include <gmlib/crypto/mac/HMacCipher.h>
#include <iostream>
#include <TinyCrypto/encoding/str/hexadecimal.h>

using namespace gmlib;

using HMacSha1 = HMacCipher<Sha1Cipher>;

void TestPBKDF2()
{
    printf("testing PBKDF2: ");
    // test 1
    {
        const char*    P           = "password";
        const char*    s           = "salt";
        size_t         c           = 1;
        size_t         dkLen       = 20;
        uint8_t        dk[20]      = {0};
        static uint8_t need_dk[20] = {
            0x0c, 0x60, 0xc8, 0x0f, 0x96, 0x1f, 0x0e, 0x71, 0xf3, 0xa9,
            0xb5, 0x24, 0xaf, 0x60, 0x12, 0x06, 0x2f, 0xe0, 0x37, 0xa6,
        };
        pbkdf2_hmac<HMacSha1>(dk, dkLen, (const uint8_t*)P, strlen(P),
                              (const uint8_t*)s, strlen(s), c);
        if (memcmp(dk, need_dk, dkLen) != 0)
        {
            throw gmlib::Exception("Error in pbkdf2 HMAC-SHA1");
        }
    }
    printf(".");
    // test 2
    {
        const char*    P           = "password";
        const char*    s           = "salt";
        size_t         c           = 2;
        size_t         dkLen       = 20;
        uint8_t        dk[20]      = {0};
        static uint8_t need_dk[20] = {
            0xea, 0x6c, 0x01, 0x4d, 0xc7, 0x2d, 0x6f, 0x8c, 0xcd, 0x1e,
            0xd9, 0x2a, 0xce, 0x1d, 0x41, 0xf0, 0xd8, 0xde, 0x89, 0x57,
        };
        pbkdf2_hmac<HMacSha1>(dk, dkLen, (const uint8_t*)P, strlen(P),
                              (const uint8_t*)s, strlen(s), c);
        if (memcmp(dk, need_dk, dkLen) != 0)
        {
            throw gmlib::Exception("Error in pbkdf2 HMAC-SHA1");
        }
    }
    printf(".");
    // test 3
    {
        const char*    P           = "password";
        const char*    s           = "salt";
        size_t         c           = 16777216;
        size_t         dkLen       = 20;
        uint8_t        dk[20]      = {0};
        static uint8_t need_dk[20] = {
            0xee, 0xfe, 0x3d, 0x61, 0xcd, 0x4d, 0xa4, 0xe4, 0xe9, 0x94,
            0x5b, 0x3d, 0x6b, 0xa2, 0x15, 0x8c, 0x26, 0x34, 0xe9, 0x84,
        };
        pbkdf2_hmac<HMacSha1>(dk, dkLen, (const uint8_t*)P, strlen(P),
                              (const uint8_t*)s, strlen(s), c);
        if (memcmp(dk, need_dk, dkLen) != 0)
        {
            throw gmlib::Exception("Error in pbkdf2 HMAC-SHA1");
        }
    }
    printf(".");
    // test 4
    {
        const char*    P           = "passwordPASSWORDpassword";
        const char*    s           = "saltSALTsaltSALTsaltSALTsaltSALTsalt";
        size_t         c           = 4096;
        size_t         dkLen       = 25;
        uint8_t        dk[25]      = {0};
        static uint8_t need_dk[25] = {
            0x3d, 0x2e, 0xec, 0x4f, 0xe4, 0x1c, 0x84, 0x9b, 0x80,
            0xc8, 0xd8, 0x36, 0x62, 0xc0, 0xe4, 0x4a, 0x8b, 0x29,
            0x1a, 0x96, 0x4c, 0xf2, 0xf0, 0x70, 0x38,
        };
        pbkdf2_hmac<HMacSha1>(dk, dkLen, (const uint8_t*)P, strlen(P),
                              (const uint8_t*)s, strlen(s), c);
        if (memcmp(dk, need_dk, dkLen) != 0)
        {
            throw gmlib::Exception("Error in pbkdf2 HMAC-SHA1");
        }
    }
    printf(".");
    puts("");
}