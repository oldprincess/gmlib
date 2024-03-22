#include <gmlib/rng/cstd_rng.h>
#include <gmlib/sm2/sm2.h>
#include <gmlib/sm3/sm3.h>

#include <cstring>
#include <stdexcept>

#include "test.h"

using namespace sm2;
using namespace sm3;

using SM2withSM3PriKey = SM2PrivateKey<SM3>;

constexpr int LOOP     = 100;
constexpr int MSG_SIZE = 1024;

class Sm2FixkRng : public rng::Rng
{
private:
    std::uint8_t fix_k_[32];

public:
    const char* name() const override
    {
        return "Sm2FixkRng";
    }

public:
    Sm2FixkRng(const std::uint8_t k[32])
    {
        std::memcpy(fix_k_, k, 32);
        if (fix_k_[31] == 0)
        {
            throw std::runtime_error("Error, invalid Sm2 fix-k for this rng");
        }
        fix_k_[31] -= 1;
        // in Sm2 Sign, generate a random integer in [1, n-1],
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

void test_sm2_sign()
{
    SM2withSM3PriKey key;
    rng::CstdRng     rng;

    std::uint8_t sig_rs[SM2withSM3PriKey::SIG_SIZE];
    std::uint8_t msg[MSG_SIZE];

    static const std::uint8_t fix_k[32] = {
        0x59, 0x27, 0x6e, 0x27, 0xd5, 0x06, 0x86, 0x1a, 0x16, 0x68, 0x0f,
        0x3a, 0xd9, 0xc0, 0x2d, 0xcc, 0xef, 0x3c, 0xc1, 0xfa, 0x3c, 0xdb,
        0xe4, 0xce, 0x6d, 0x54, 0xb8, 0x0d, 0xea, 0xc1, 0xbc, 0x21,
    };
    static const std::uint8_t da[32] = {
        0x39, 0x45, 0x20, 0x8f, 0x7b, 0x21, 0x44, 0xb1, 0x3f, 0x36, 0xe3,
        0x8a, 0xc6, 0xd3, 0x9f, 0x95, 0x88, 0x93, 0x93, 0x69, 0x28, 0x60,
        0xb5, 0x1a, 0x42, 0xfb, 0x81, 0xef, 0x4d, 0xf7, 0xc5, 0xb8,
    };
    static std::uint8_t test_msg[14] = {
        'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 'd', 'i', 'g', 'e', 's', 't',
    }; // "message digest"
    static std::uint8_t need_sig_r[32] = {
        0xf5, 0xa0, 0x3b, 0x06, 0x48, 0xd2, 0xc4, 0x63, 0x0e, 0xea, 0xc5,
        0x13, 0xe1, 0xbb, 0x81, 0xa1, 0x59, 0x44, 0xda, 0x38, 0x27, 0xd5,
        0xb7, 0x41, 0x43, 0xac, 0x7e, 0xac, 0xee, 0xe7, 0x20, 0xb3,
    };
    static std::uint8_t need_sig_s[32] = {
        0xb1, 0xb6, 0xaa, 0x29, 0xdf, 0x21, 0x2f, 0xd8, 0x76, 0x31, 0x82,
        0xbc, 0x0d, 0x42, 0x1c, 0xa1, 0xbb, 0x90, 0x38, 0xfd, 0x1f, 0x7f,
        0x42, 0xd4, 0x84, 0x0b, 0x69, 0xc4, 0x85, 0xbb, 0xc1, 0xaa,
    };
    auto fix_k_rng = Sm2FixkRng(fix_k);
    key.set_priv(da);
    key.sign(sig_rs, test_msg, 14, fix_k_rng);
    if (std::memcmp(sig_rs + 0, need_sig_r, 32) != 0 ||
        std::memcmp(sig_rs + 32, need_sig_s, 32) != 0)
    {
        throw std::runtime_error("err in sm2 sign");
    }

    key.gen_priv(rng);
    for (int i = 0; i < LOOP; i++)
    {
        rng.gen(msg, MSG_SIZE);
        key.sign(sig_rs, msg, MSG_SIZE, rng);
        if (!key.verify(sig_rs, msg, MSG_SIZE))
        {
            throw std::runtime_error("err in sm2 sign random");
        }
    }
}