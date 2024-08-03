#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm3/sm3.h>
#include <gmlib/sm9/sm9.h>

#include <cstring>
#include <stdexcept>

#include "test.h"

using namespace std;
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

void test_sm9_enc()
{
    const char*          ID_B    = "Bob";
    static const char*   msg     = "Chinese IBE standard";
    static const uint8_t mke[32] = {
        0x00, 0x01, 0xed, 0xee, 0x37, 0x78, 0xf4, 0x41, 0xf8, 0xde, 0xa3,
        0xd9, 0xfa, 0x0a, 0xcc, 0x4e, 0x07, 0xee, 0x36, 0xc9, 0x3f, 0x9a,
        0x08, 0x61, 0x8a, 0xf4, 0xad, 0x85, 0xce, 0xde, 0x1c, 0x22,
    };
    static const uint8_t r[32] = {
        0x00, 0x00, 0xaa, 0xc0, 0x54, 0x17, 0x79, 0xc8, 0xfc, 0x45, 0xe3,
        0xe2, 0xcb, 0x25, 0xc1, 0x2b, 0x5d, 0x25, 0x76, 0xb2, 0x12, 0x9a,
        0xe8, 0xbb, 0x5e, 0xe2, 0xcb, 0xe5, 0xec, 0x9e, 0x78, 0x5c,
    };

    static uint8_t ct_buf[1024], pt_buf[128], pt2_buf[128];
    static size_t  ct_len, pt_len, pt2_len;

    SM9EncryptMasterPrivateKey<SM3> m_priv;
    SM9EncryptPrivateKey<SM3>       priv;
    SM9EncryptMasterPublicKey<SM3>  pub;
    StdRng                          rng;
    Sm9FixkRng                      fix_r_rng(r);

    m_priv.set_priv(mke);
    priv = m_priv.gen_EncryptPrivateKey((const uint8_t*)ID_B, strlen(ID_B));
    pub  = priv.fetch_pub();

    pub.encrypt0(ct_buf, &ct_len, (const uint8_t*)msg, strlen(msg),
                 (const uint8_t*)ID_B, strlen(ID_B), fix_r_rng);
    priv.decrypt0(pt_buf, &pt_len, ct_buf, ct_len, (const uint8_t*)ID_B,
                  strlen(ID_B));

    if (memcmp(pt_buf, msg, strlen(msg)) != 0)
    {
        throw std::runtime_error("err in test sm9 enc");
    }

    for (int i = 0; i < LOOP; i++)
    {
        m_priv.gen_priv(rng);
        priv = m_priv.gen_EncryptPrivateKey((const uint8_t*)ID_B, strlen(ID_B));
        pub  = priv.fetch_pub();

        pt_len = rng.rand<std::size_t>() % sizeof(pt_buf);
        rng.gen(pt_buf, pt_len);

        pub.encrypt0(ct_buf, &ct_len, pt_buf, pt_len, (const uint8_t*)ID_B,
                     strlen(ID_B), rng);
        priv.decrypt0(pt2_buf, &pt2_len, ct_buf, ct_len, (const uint8_t*)ID_B,
                      strlen(ID_B));

        if (pt2_len != pt_len || memcmp(pt2_buf, pt_buf, pt_len) != 0)
        {
            throw std::runtime_error("err in test sm9 enc");
        }
    }
}