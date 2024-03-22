#include <gmlib/rng/cstd_rng.h>
#include <gmlib/sm3/sm3.h>
#include <gmlib/sm9/sm9.h>

#include <cstring>
#include <stdexcept>

#include "test.h"

using namespace rng;
using namespace sm3;
using namespace sm9;
constexpr int LOOP = 100;

class Sm9FixkRng : public Rng
{
private:
    std::uint8_t fix_k_[32];

public:
    const char* name() const override
    {
        return "Sm9FixkRng";
    }

public:
    Sm9FixkRng(const std::uint8_t k[32])
    {
        std::memcpy(fix_k_, k, 32);
        if (fix_k_[31] == 0)
        {
            throw std::runtime_error("Error, invalid Sm2 fix-k for this rng");
        }
        fix_k_[31] -= 1;
        // in Sm9 Sign, generate a random integer in [1, n-1],
        // by computing: rand() % (n-1) + 1
        // so, need to -1 to offset '+1'
    }

public:
    void gen(void* out, std::size_t len) override
    {
        if (len != 32)
        {
            throw std::runtime_error("Error, this rng only for Sm2 fix-k test");
        }
        std::memcpy(out, fix_k_, 32);
    }
};

void test_sm9_sign()
{
    static const char* ID  = "Alice";
    static const char* msg = "Chinese IBS standard";
    // 000130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4
    static std::uint8_t master_key_data[32] = {
        0x00, 0x01, 0x30, 0xe7, 0x84, 0x59, 0xd7, 0x85, 0x45, 0xcb, 0x54,
        0xc5, 0x87, 0xe0, 0x2c, 0xf4, 0x80, 0xce, 0x0b, 0x66, 0x34, 0x0f,
        0x31, 0x9f, 0x34, 0x8a, 0x1d, 0x5b, 0x1f, 0x2d, 0xc5, 0xf4,
    };

    static std::uint8_t need_sig[32 + 65] = {
        0x82, 0x3c, 0x4b, 0x21, 0xe4, 0xbd, 0x2d, 0xfe, 0x1e, 0xd9, 0x2c,
        0x60, 0x66, 0x53, 0xe9, 0x96, 0x66, 0x85, 0x63, 0x15, 0x2f, 0xc3,
        0x3f, 0x55, 0xd7, 0xbf, 0xbb, 0x9b, 0xd9, 0x70, 0x5a, 0xdb, /* h   */
        0x04,                                                       /* 04  */
        0x73, 0xbf, 0x96, 0x92, 0x3c, 0xe5, 0x8b, 0x6a, 0xd0, 0xe1, 0x3e,
        0x96, 0x43, 0xa4, 0x06, 0xd8, 0xeb, 0x98, 0x41, 0x7c, 0x50, 0xef,
        0x1b, 0x29, 0xce, 0xf9, 0xad, 0xb4, 0x8b, 0x6d, 0x59, 0x8c, /* S.x */
        0x85, 0x67, 0x12, 0xf1, 0xc2, 0xe0, 0x96, 0x8a, 0xb7, 0x76, 0x9f,
        0x42, 0xa9, 0x95, 0x86, 0xae, 0xd1, 0x39, 0xd5, 0xb8, 0xb3, 0xe1,
        0x58, 0x91, 0x82, 0x7c, 0xc2, 0xac, 0xed, 0x9b, 0xaa, 0x05, /* S.y */
    };

    static std::uint8_t fix_k[32] = {
        0x00, 0x03, 0x3c, 0x86, 0x16, 0xb0, 0x67, 0x04, 0x81, 0x32, 0x03,
        0xdf, 0xd0, 0x09, 0x65, 0x02, 0x2e, 0xd1, 0x59, 0x75, 0xc6, 0x62,
        0x33, 0x7a, 0xed, 0x64, 0x88, 0x35, 0xdc, 0x4b, 0x1c, 0xbe,
    };

    CstdRng                      rng;
    SM9SignMasterPrivateKey<SM3> mpk;
    Sm9FixkRng                   fix_rng(fix_k);
    static std::uint8_t          buf[1024];

    std::uint8_t sig[SM9SignPublicKey<SM3>::MAX_SIG_SIZE];
    std::size_t  sig_len;

    mpk.set_priv(master_key_data);
    auto priv = mpk.gen_SignPrivateKey((const std::uint8_t*)ID, std::strlen(ID),
                                       fix_rng);

    priv.sign(sig, &sig_len, (const std::uint8_t*)msg, std::strlen(msg),
              fix_rng, SM9EcPC::UNCOMPRESSED);
    if (std::memcmp(sig, need_sig, sizeof(need_sig)) &&
        sig_len == sizeof(need_sig))
    {
        throw std::runtime_error("err in test sm9 sign");
    }
    if (!priv.verify(need_sig, sizeof(need_sig), (const std::uint8_t*)msg,
                     std::strlen(msg), (const std::uint8_t*)ID,
                     std::strlen(ID)))
    {
        throw std::runtime_error("err in test sm9 sign");
    }

    priv =
        mpk.gen_SignPrivateKey((const std::uint8_t*)ID, std::strlen(ID), rng);
    auto& pub = priv.fetch_pub();
    for (int i = 0; i < LOOP; i++)
    {
        std::size_t size = rng.rand<std::size_t>() % sizeof(buf);
        rng.gen(buf, size);

        priv.sign(sig, &sig_len, buf, size, fix_rng, SM9EcPC::UNCOMPRESSED);
        if (!pub.verify(sig, sig_len, buf, size, (const std::uint8_t*)ID,
                        std::strlen(ID)))
        {
            throw std::runtime_error("err in test sm9 sign");
        }
        priv.sign(sig, &sig_len, buf, size, fix_rng, SM9EcPC::MIX);
        if (!pub.verify(sig, sig_len, buf, size, (const std::uint8_t*)ID,
                        std::strlen(ID)))
        {
            throw std::runtime_error("err in test sm9 sign");
        }
        priv.sign(sig, &sig_len, buf, size, fix_rng, SM9EcPC::COMPRESSED);
        if (!pub.verify(sig, sig_len, buf, size, (const std::uint8_t*)ID,
                        std::strlen(ID)))
        {
            throw std::runtime_error("err in test sm9 sign");
        }
    }
}