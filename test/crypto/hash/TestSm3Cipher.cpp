#include <gmlib/crypto/hash/Sm3Cipher.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

static const uint8_t msg[]           = {'a', 'b', 'c'};
static const uint8_t need_digest[32] = {
    0x66, 0xC7, 0xF0, 0xF4, 0x62, 0xEE, 0xED, 0xD9, 0xD1, 0xF2, 0xD4,
    0x6B, 0xDC, 0x10, 0xE4, 0xE2, 0x41, 0x67, 0xC4, 0x87, 0x5C, 0xF2,
    0xF7, 0xA2, 0x29, 0x7D, 0xA0, 0x2B, 0x8F, 0x4B, 0xA8, 0xE0,
};

using namespace gmlib;

void TestSm3Cipher()
{
    auto hash = Sm3Cipher();
    uint8_t digest[Sm3Cipher::DIGEST_SIZE];
    hash.update(msg, sizeof(msg));
    hash.final(digest);
    if (memcmp(digest, need_digest, sizeof(need_digest)) != 0)
    {
        for (int i = 0; i < 32; i++) printf("%02x ", digest[i]);
        throw std::exception("Err in Sm3 Hash");
    }
    

    hash.reset();
    hash.update(msg, sizeof(msg));
    hash.final(digest);
    if (memcmp(digest, need_digest, sizeof(need_digest)) != 0)
    {
        throw std::exception("Err in Sm3 Hash");
    }
}