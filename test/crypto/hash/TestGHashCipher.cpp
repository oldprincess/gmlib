#include <gmlib/crypto/hash/GHashCipher.h>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <gmlib/crypto_ex/win/WinRng.h>
#include <gmlib/crypto_ex/GHashCipher_Pclmul.h>
using namespace gmlib;
using namespace std;

void TestGHashCipher()
{
    uint8_t buf[1024], d1[16], d2[16], H[16];
    WinRng  rng;
    for (int i = 0; i < 100; i++)
    {
        size_t size = sizeof(buf);
        rng.gen(buf, size);
        rng.gen(H, 16);
        auto gmac = GHashCipher();
        gmac.set_key(H);
        gmac.update(buf, size);
        gmac.final(d1);

        auto gmac2 = GHashCipher_Pclmul(H);
        gmac2.update(buf, size);
        gmac2.final(d2);
        if (memcmp(d1, d2, 16) != 0)
        {
            throw std::runtime_error("err in gmac");
        }
    }
}