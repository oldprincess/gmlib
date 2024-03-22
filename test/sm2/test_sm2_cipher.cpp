#include <gmlib/rng/cstd_rng.h>
#include <gmlib/sm2/sm2.h>
#include <gmlib/sm3/sm3.h>

#include <cstring>
#include <stdexcept>

#include "test.h"

using namespace sm2;
using namespace sm3;

using SM2withSM3PriKey = SM2PrivateKey<SM3>;

constexpr int LOOP    = 100;
constexpr int PT_SIZE = 1024;

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

void test_sm2_cipher()
{
    rng::CstdRng     rng;
    SM2withSM3PriKey key;
    std::uint8_t     pt[PT_SIZE], ct[PT_SIZE + 100], pt2[PT_SIZE];
    std::size_t      ct_len, pt_len;

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
    static std::uint8_t test_msg[] = {
        'e', 'n', 'c', 'r', 'y', 'p', 't', 'i', 'o', 'n',
        ' ', 's', 't', 'a', 'n', 'd', 'a', 'r', 'd',
    }; // "encryption standard"
    static std::uint8_t need_ct[116] = {
        0x04, // pc=04
        0x04, 0xeb, 0xfc, 0x71, 0x8e, 0x8d, 0x17, 0x98, 0x62, 0x04, 0x32,
        0x26, 0x8e, 0x77, 0xfe, 0xb6, 0x41, 0x5e, 0x2e, 0xde, 0x0e, 0x07,
        0x3c, 0x0f, 0x4f, 0x64, 0x0e, 0xcd, 0x2e, 0x14, 0x9a, 0x73, // C1.x
        0xe8, 0x58, 0xf9, 0xd8, 0x1e, 0x54, 0x30, 0xa5, 0x7b, 0x36, 0xda,
        0xab, 0x8f, 0x95, 0x0a, 0x3c, 0x64, 0xe6, 0xee, 0x6a, 0x63, 0x09,
        0x4d, 0x99, 0x28, 0x3a, 0xff, 0x76, 0x7e, 0x12, 0x4d, 0xf0, // C1.y
        0x59, 0x98, 0x3c, 0x18, 0xf8, 0x09, 0xe2, 0x62, 0x92, 0x3c, 0x53,
        0xae, 0xc2, 0x95, 0xd3, 0x03, 0x83, 0xb5, 0x4e, 0x39, 0xd6, 0x09,
        0xd1, 0x60, 0xaf, 0xcb, 0x19, 0x08, 0xd0, 0xbd, 0x87, 0x66, // C3
        0x21, 0x88, 0x6c, 0xa9, 0x89, 0xca, 0x9c, 0x7d, 0x58, 0x08, 0x73,
        0x07, 0xca, 0x93, 0x09, 0x2d, 0x65, 0x1e, 0xfa, // C2
    };

    Sm2FixkRng fix_rng(fix_k);
    key.set_priv(da);
    key.encrypt(ct, &ct_len, test_msg, sizeof(test_msg), fix_rng);
    if (key.ciphertext_len(test_msg, sizeof(test_msg)) != sizeof(need_ct))
    {
        throw std::runtime_error("err in sm2 cipher");
    }
    if (std::memcmp(ct, need_ct, sizeof(need_ct)) != 0 ||
        ct_len != sizeof(need_ct))
    {
        throw std::runtime_error("err in sm2 cipher");
    }
    key.decrypt(pt, &pt_len, need_ct, sizeof(need_ct));
    if (key.plaintext_len(need_ct, sizeof(need_ct)) != sizeof(test_msg))
    {
        throw std::runtime_error("err in sm2 cipher");
    }
    if (std::memcmp(pt, test_msg, sizeof(test_msg)) != 0 &&
        pt_len != sizeof(test_msg))
    {
        throw std::runtime_error("err in sm2 cipher");
    }

    key.gen_priv(rng);
    for (int i = 0; i < LOOP; i++)
    {
        rng.gen(pt, PT_SIZE);
        auto size = rng.rand<std::size_t>() % PT_SIZE;
        key.encrypt(ct, &ct_len, pt, size, rng, SM2EcPC::COMPRESSED);
        key.decrypt(pt2, &pt_len, ct, ct_len);
        if (std::memcmp(pt, pt2, size) != 0 && pt_len != size)
        {
            throw std::runtime_error("err in sm2 cipher random");
        }
        key.encrypt(ct, &ct_len, pt, size, rng, SM2EcPC::UNCOMPRESSED);
        key.decrypt(pt2, &pt_len, ct, ct_len);
        if (std::memcmp(pt, pt2, size) != 0 && pt_len != size)
        {
            throw std::runtime_error("err in sm2 cipher random");
        }
        key.encrypt(ct, &ct_len, pt, size, rng, SM2EcPC::MIX);
        key.decrypt(pt2, &pt_len, ct, ct_len);
        if (std::memcmp(pt, pt2, size) != 0 && pt_len != size)
        {
            throw std::runtime_error("err in sm2 cipher random");
        }
    }
}