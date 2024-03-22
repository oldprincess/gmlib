#include <gmlib/rng/std_rng.h>
#include <gmlib/sm2/sm2.h>
#include <gmlib/sm3/sm3.h>

#include <cstdio>
#include <ctime>
#include <stdexcept>

constexpr int MSG_SIZE = 64;
constexpr int LOOP     = 5000;

using namespace rng;
using namespace sm2;
using namespace sm3;

using SM2withSM3PriKey = SM2PrivateKey<SM3>;

void speed_sm2_sign()
{
    std::uint8_t     msg[MSG_SIZE];
    std::uint8_t     sig_rs[SM2withSM3PriKey::SIG_SIZE];
    StdRng           rng;
    SM2withSM3PriKey key;
    std::clock_t     st, et;
    double           time_s, opt_s;

    key.gen_priv(rng);
    rng.gen(msg, MSG_SIZE);

    std::printf("speed sm2-sm3 sign (%d bytes)... ", MSG_SIZE);
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        key.sign(sig_rs, msg, MSG_SIZE, rng);
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);

    std::printf("speed sm2-sm3 verify ... ");
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        if (!key.verify(sig_rs, msg, MSG_SIZE))
        {
            throw std::runtime_error("err in speed sm2 verify");
        }
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);
}
