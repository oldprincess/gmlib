#include <gmlib/rng/cstd_rng.h>
#include <gmlib/sm3/sm3.h>
#include <gmlib/sm9/sm9.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdexcept>

constexpr int MSG_SIZE = 64;
constexpr int LOOP     = 500;

using namespace rng;
using namespace sm9;
using namespace sm3;

using SM9SignMSK = SM9SignMasterPrivateKey<SM3>;
using SM9SignMPK = SM9SignMasterPublicKey<SM3>;
using SM9SignSK  = SM9SignPrivateKey<SM3>;
using SM9SignPK  = SM9SignPublicKey<SM3>;

void speed_sm9_sign()
{
    static const char* ID = "Alice";

    std::uint8_t msg[MSG_SIZE];
    std::uint8_t sig[SM9SignSK::MAX_SIG_SIZE];
    std::size_t  sig_len;
    CstdRng      rng;
    SM9SignMSK   msk;
    std::clock_t st, et;
    double       time_s, opt_s;

    msk.gen_priv(rng);
    rng.gen(msg, MSG_SIZE);
    auto sk =
        msk.gen_SignPrivateKey((const std::uint8_t*)ID, std::strlen(ID), rng);

    std::printf("speed sm9-sm3 sign (%d bytes)... ", MSG_SIZE);
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        sk.sign(sig, &sig_len, msg, MSG_SIZE, rng);
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);

    std::printf("speed sm9-sm3 verify ... ");
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        if (!sk.verify(sig, sig_len, msg, MSG_SIZE, (const std::uint8_t*)ID,
                       std::strlen(ID)))
        {
            throw std::runtime_error("err in speed sm9 verify");
        }
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);
}
