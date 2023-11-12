#include <iostream>
#include <gmlib/crypto/cipher/CipherMode.h>
#include <gmlib/crypto/cipher/AesCipher.h>

#include <stdlib.h>
using namespace gmlib;
using namespace std;

static void gcm_test1();
static void gcm_test2();

void TestGcmMode()
{
    gcm_test1();
    gcm_test2();
}

static void gcm_test1()
{
    /* AES-GCM test data obtained from NIST public test vectors */

    /* AES key */
    static const unsigned char gcm_key[32] = {
        0xee, 0xbc, 0x1f, 0x57, 0x48, 0x7f, 0x51, 0x92, 0x1c, 0x04, 0x65,
        0x66, 0x5f, 0x8a, 0xe6, 0xd1, 0x65, 0x8b, 0xb2, 0x6d, 0xe6, 0xf8,
        0xa0, 0x69, 0xa3, 0x52, 0x02, 0x93, 0xa5, 0x72, 0x07, 0x8f,
    };
    /* Unique initialisation vector */
    static const unsigned char gcm_iv[12] = {
        0x99, 0xaa, 0x3e, 0x68, 0xed, 0x81, 0x73, 0xa0, 0xee, 0xd0, 0x66, 0x84,
    };
    /* Example plaintext to encrypt */
    static const unsigned char gcm_pt[] = {
        0xf5, 0x6e, 0x87, 0x05, 0x5b, 0xc3, 0x2d, 0x0e,
        0xeb, 0x31, 0xb2, 0xea, 0xcc, 0x2b, 0xf2, 0xa5,
    };
    /*
     * Example of Additional Authenticated Data (AAD), i.e. unencrypted data
     * which can be authenticated using the generated Tag value.
     */
    static const unsigned char gcm_aad[16] = {
        0x4d, 0x23, 0xc3, 0xce, 0xc3, 0x34, 0xb4, 0x9b,
        0xdb, 0x37, 0x0c, 0x43, 0x7f, 0xec, 0x78, 0xde,
    };
    /* Expected ciphertext value */
    static const unsigned char gcm_ct[16] = {
        0xf7, 0x26, 0x44, 0x13, 0xa8, 0x4c, 0x0e, 0x7c,
        0xd5, 0x36, 0x86, 0x7e, 0xb9, 0xf2, 0x17, 0x36,
    };
    /* Expected AEAD Tag value */
    static const unsigned char gcm_tag[16] = {
        0x67, 0xba, 0x05, 0x10, 0x26, 0x2a, 0xe4, 0x87,
        0xd7, 0x37, 0xee, 0x62, 0x98, 0xf7, 0x7e, 0x0c,
    };

    uint8_t  out[sizeof(gcm_pt)], tag[16];
    size_t   outl;
    uint8_t* outptr;

    auto encryptor = GcmEncryptor<Aes256Cipher>(gcm_key, gcm_iv, sizeof(gcm_iv),
                                                gcm_aad, sizeof(gcm_aad));
    outptr         = out;
    encryptor.update(outptr, &outl, gcm_pt, sizeof(gcm_pt));
    outptr += outl;
    encryptor.final(outptr, &outl);
    outptr += outl;
    encryptor.get_tag(tag);
    if (memcmp(out, gcm_ct, sizeof(gcm_ct)) != 0 ||
        memcmp(tag, gcm_tag, 16) != 0 ||
        (size_t)(outptr - out) != sizeof(gcm_ct))
    {
        throw std::runtime_error("err in Gcm Encrypt");
    }

    outptr = out;
    encryptor.reset(gcm_iv, sizeof(gcm_iv), gcm_aad, sizeof(gcm_aad));
    encryptor.update(outptr, &outl, gcm_pt, sizeof(gcm_pt));
    outptr += outl;
    encryptor.final(outptr, &outl);
    outptr += outl;
    encryptor.get_tag(tag);
    if (memcmp(out, gcm_ct, sizeof(gcm_ct)) != 0 ||
        memcmp(tag, gcm_tag, 16) != 0 ||
        (size_t)(outptr - out) != sizeof(gcm_ct))
    {
        throw std::runtime_error("err in Gcm Encrypt");
    }

    auto decryptor = GcmDecryptor<Aes256Cipher>(gcm_key, gcm_iv, sizeof(gcm_iv),
                                                gcm_aad, sizeof(gcm_aad));
    outptr         = out;
    decryptor.set_tag(gcm_tag);
    decryptor.update(outptr, &outl, gcm_ct, sizeof(gcm_ct));
    outptr += outl;
    decryptor.final(outptr, &outl);
    outptr += outl;
    if (memcmp(out, gcm_pt, sizeof(gcm_pt)) != 0 ||
        (size_t)(outptr - out) != sizeof(gcm_pt))
    {
        throw std::runtime_error("err in Gcm Decrypt");
    }

    outptr = out;
    decryptor.reset(gcm_iv, sizeof(gcm_iv), gcm_aad, sizeof(gcm_aad));
    decryptor.set_tag(gcm_tag);
    decryptor.update(outptr, &outl, gcm_ct, sizeof(gcm_ct));
    outptr += outl;
    decryptor.final(outptr, &outl);
    outptr += outl;
    if (memcmp(out, gcm_pt, sizeof(gcm_pt)) != 0 ||
        (size_t)(outptr - out) != sizeof(gcm_pt))
    {
        throw std::runtime_error("err in Gcm Decrypt");
    }
}
void gcm_test2()
{
    /* AES128 key */
    static uint8_t gcm_key[] = {
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
    };
    static uint8_t gcm_iv[] = {
        0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
    };
    static uint8_t gcm_pt[] = {
        0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 0xa5, 0x59, 0x09, 0xc5,
        0xaf, 0xf5, 0x26, 0x9a, 0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
        0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72, 0x1c, 0x3c, 0x0c, 0x95,
        0x95, 0x68, 0x09, 0x53, 0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
        0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 0xba, 0x63, 0x7b, 0x39,
    };
    static uint8_t gcm_aad[] = {
        0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 0xfe, 0xed,
        0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 0xab, 0xad, 0xda, 0xd2,
    };
    static uint8_t gcm_ct[] = {
        0x61, 0x35, 0x3B, 0x4C, 0x28, 0x06, 0x93, 0x4A, 0x77, 0x7F, 0xF5, 0x1F,
        0xA2, 0x2A, 0x47, 0x55, 0x69, 0x9B, 0x2A, 0x71, 0x4F, 0xCD, 0xC6, 0xF8,
        0x37, 0x66, 0xE5, 0xF9, 0x7B, 0x6C, 0x74, 0x23, 0x73, 0x80, 0x69, 0x00,
        0xE4, 0x9F, 0x24, 0xB2, 0x2B, 0x09, 0x75, 0x44, 0xD4, 0x89, 0x6B, 0x42,
        0x49, 0x89, 0xB5, 0xE1, 0xEB, 0xAC, 0x0F, 0x07, 0xC2, 0x3F, 0x45, 0x98,
    };
    static uint8_t gcm_tag[] = {
        0x36, 0x12, 0xD2, 0xE7, 0x9E, 0x3B, 0x07, 0x85,
        0x56, 0x1B, 0xE1, 0x4A, 0xAC, 0xA2, 0xFC, 0xCB,
    };

    uint8_t out[sizeof(gcm_ct)], tag[16];
    size_t  outl;

    uint8_t* outptr;

    auto encryptor = GcmEncryptor<Aes128Cipher>(gcm_key, gcm_iv, sizeof(gcm_iv),
                                                gcm_aad, sizeof(gcm_aad));
    outptr         = out;
    encryptor.update(outptr, &outl, gcm_pt, sizeof(gcm_pt));
    outptr += outl;
    encryptor.final(outptr, &outl);
    outptr += outl;
    encryptor.get_tag(tag);
    if (memcmp(tag, gcm_tag, 16) != 0 ||
        memcmp(out, gcm_ct, sizeof(gcm_ct)) != 0 ||
        sizeof(gcm_ct) != (size_t)(outptr - out))
    {
        throw std::runtime_error("err in GCM");
    }

    encryptor.reset(gcm_iv, sizeof(gcm_iv), gcm_aad, sizeof(gcm_aad));
    outptr = out;
    encryptor.update(outptr, &outl, gcm_pt, sizeof(gcm_pt));
    outptr += outl;
    encryptor.final(outptr, &outl);
    outptr += outl;
    encryptor.get_tag(tag);
    if (memcmp(tag, gcm_tag, 16) != 0 ||
        memcmp(out, gcm_ct, sizeof(gcm_ct)) != 0 ||
        sizeof(gcm_ct) != (size_t)(outptr - out))
    {
        throw std::runtime_error("err in GCM");
    }

    auto decryptor = GcmDecryptor<Aes128Cipher>(gcm_key, gcm_iv, sizeof(gcm_iv),
                                                gcm_aad, sizeof(gcm_aad));
    outptr         = out;
    decryptor.set_tag(gcm_tag);
    decryptor.update(outptr, &outl, gcm_ct, sizeof(gcm_ct));
    outptr += outl;
    decryptor.final(outptr, &outl);
    outptr += outl;
    if (memcmp(out, gcm_pt, sizeof(gcm_pt)) != 0 ||
        sizeof(gcm_pt) != (size_t)(outptr - out))
    {
        throw std::runtime_error("err in GCM");
    }

    decryptor.reset(gcm_iv, sizeof(gcm_iv), gcm_aad, sizeof(gcm_aad));
    outptr = out;
    decryptor.set_tag(gcm_tag);
    decryptor.update(outptr, &outl, gcm_ct, sizeof(gcm_ct));
    outptr += outl;
    decryptor.final(outptr, &outl);
    outptr += outl;
    if (memcmp(out, gcm_pt, sizeof(gcm_pt)) != 0 ||
        sizeof(gcm_pt) != (size_t)(outptr - out))
    {
        throw std::runtime_error("err in GCM");
    }
}