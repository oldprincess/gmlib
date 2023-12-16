#include <gmlib/crypto/pkc/Sm2Cipher.h>
#include <gmlib/crypto/rng/OsRngCipher.h>
#include <gmlib/crypto/hash/Sm3Cipher.h>
#include <stdio.h>

using gmlib::Sm2PrivateKey;
using gmlib::Sm2PublicKey;
using gmlib::Sm2Sig;
using gmlib::Sm3Cipher;
using gmlib::OsRngCipher;

static void dumphex(const uint8_t* mem, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%02x ", mem[i]);
    }
    puts("");
}

class Sm2FixkRng : public gmlib::RngCipher
{
private:
    uint8_t fix_k[32];

public:
    const char* name()
    {
        return "Sm2FixkRng";
    }

public:
    Sm2FixkRng(const uint8_t* k)
    {
        memcpy(this->fix_k, k, 32);
        if (this->fix_k[31] == 0)
        {
            gmlib::Exception("Error, invalid Sm2 fix-k for this rng");
        }
        this->fix_k[31] -= 1;
        // in Sm2 Sign, generate a random integer in [1, n-1],
        // by computing: rand() % (n-2) + 1
        // so, need to -1 to offset '+1'
    }

public:
    void gen(uint8_t* out, size_t len)
    {
        if (len != 32)
        {
            gmlib::Exception("Error, this rng only for Sm2 fix-k test");
        }
        memcpy(out, this->fix_k, 32);
    }
};

void TestSm2Cipher()
{
    uint8_t msg[1024];

    static const uint8_t fix_k[32] = {
        0x59, 0x27, 0x6e, 0x27, 0xd5, 0x06, 0x86, 0x1a, 0x16, 0x68, 0x0f,
        0x3a, 0xd9, 0xc0, 0x2d, 0xcc, 0xef, 0x3c, 0xc1, 0xfa, 0x3c, 0xdb,
        0xe4, 0xce, 0x6d, 0x54, 0xb8, 0x0d, 0xea, 0xc1, 0xbc, 0x21,
    };
    static const uint8_t da[32] = {
        0x39, 0x45, 0x20, 0x8f, 0x7b, 0x21, 0x44, 0xb1, 0x3f, 0x36, 0xe3,
        0x8a, 0xc6, 0xd3, 0x9f, 0x95, 0x88, 0x93, 0x93, 0x69, 0x28, 0x60,
        0xb5, 0x1a, 0x42, 0xfb, 0x81, 0xef, 0x4d, 0xf7, 0xc5, 0xb8,
    };
    static uint8_t test_msg[14] = {
        'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 'd', 'i', 'g', 'e', 's', 't',
    }; // "message digest"
    static uint8_t need_sig_r[32] = {
        0xf5, 0xa0, 0x3b, 0x06, 0x48, 0xd2, 0xc4, 0x63, 0x0e, 0xea, 0xc5,
        0x13, 0xe1, 0xbb, 0x81, 0xa1, 0x59, 0x44, 0xda, 0x38, 0x27, 0xd5,
        0xb7, 0x41, 0x43, 0xac, 0x7e, 0xac, 0xee, 0xe7, 0x20, 0xb3,
    };
    static uint8_t need_sig_s[32] = {
        0xb1, 0xb6, 0xaa, 0x29, 0xdf, 0x21, 0x2f, 0xd8, 0x76, 0x31, 0x82,
        0xbc, 0x0d, 0x42, 0x1c, 0xa1, 0xbb, 0x90, 0x38, 0xfd, 0x1f, 0x7f,
        0x42, 0xd4, 0x84, 0x0b, 0x69, 0xc4, 0x85, 0xbb, 0xc1, 0xaa,
    };
    auto fix_k_rng = Sm2FixkRng(fix_k);
    auto priv      = Sm2PrivateKey();
    priv.set_key(da);
    auto sig = priv.sign<Sm3Cipher>(test_msg, 14, &fix_k_rng);
    if (memcmp(sig.get_r(), need_sig_r, 32) != 0 ||
        memcmp(sig.get_s(), need_sig_s, 32) != 0)
    {
        throw gmlib::Exception("Error in Sm2Cipher");
    }

    auto rng = OsRngCipher();
    for (int i = 0; i < 100; i++)
    {
        priv           = Sm2PrivateKey::gen(&rng);
        size_t msg_len = rng.rand<size_t>() % sizeof(msg);
        auto   sig     = priv.sign<Sm3Cipher>(msg, msg_len, &rng);
        if (!priv.verify<Sm3Cipher>(sig, msg, msg_len))
        {
            throw gmlib::Exception("Error in Sm2Cipher");
        }
    }
}