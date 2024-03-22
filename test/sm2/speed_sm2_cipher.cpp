#include <gmlib/rng/std_rng.h>
#include <gmlib/sm2/sm2.h>
#include <gmlib/sm3/sm3.h>

#include <cstdio>
#include <ctime>
#include <stdexcept>

constexpr int PT_SIZE = 64;
constexpr int LOOP    = 5000;

using namespace rng;
using namespace sm2;
using namespace sm3;

using SM2withSM3PriKey = SM2PrivateKey<SM3>;

void speed_sm2_cipher()
{
    SM2withSM3PriKey key;
    StdRng           rng;
    std::uint8_t     pt[PT_SIZE], ct[PT_SIZE + 100];
    std::size_t      ct_len, pt_len;
    std::clock_t     st, et;
    double           time_s, opt_s;

    key.gen_priv(rng);
    rng.gen(pt, PT_SIZE);

    std::printf("speed sm2-sm3 encrypt (%d bytes)... ", PT_SIZE);
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        key.encrypt(ct, &ct_len, pt, PT_SIZE, rng);
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);

    std::printf("speed sm2-sm3 decrypt (%d bytes)... ", PT_SIZE);
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        key.decrypt(pt, &pt_len, ct, ct_len);
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);
}
