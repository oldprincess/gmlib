#include <gmlib/rng/drbg.h>
#include <gmlib/sm3/sm3.h>
#include <gmlib/sm9/sm9.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <memory>
#include <stdexcept>

constexpr int MSG_SIZE = 64;
constexpr int LOOP     = 500;

using namespace rng;
using namespace sm9;
using namespace sm3;

using SM9EncMSK = SM9EncryptMasterPrivateKey<SM3>;
using SM9EncMPK = SM9EncryptMasterPublicKey<SM3>;
using SM9EncSK  = SM9EncryptPrivateKey<SM3>;
using SM9EncPK  = SM9EncryptPublicKey<SM3>;

void speed_sm9_enc()
{
    static const char* ID = "Bob";

    std::uint8_t  msg[MSG_SIZE];
    std::size_t   ct_len = SM9EncPK::ciphertext_len(msg, MSG_SIZE);
    auto          ct_buf = std::unique_ptr<std::uint8_t[]>( //
        new std::uint8_t[ct_len]                   //
    );
    auto          pt_buf = std::unique_ptr<std::uint8_t[]>( //
        new std::uint8_t[sizeof(msg)]              //
    );
    HashDrbg<SM3> rng;
    SM9EncMSK     msk;
    std::clock_t  st, et;
    double        time_s, opt_s;

    msk.gen_priv(rng);
    rng.gen(msg, MSG_SIZE);
    auto sk = msk.gen_EncryptPrivateKey( //
        (const std::uint8_t*)ID,         //
        std::strlen(ID)                  //
    );

    std::printf("speed sm9-sm3 encrypt (%d bytes)... ", MSG_SIZE);
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        sk.encrypt0(ct_buf.get(), &ct_len, msg, MSG_SIZE,
                    (const std::uint8_t*)ID, std::strlen(ID), rng);
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);

    std::printf("speed sm9-sm3 decrypt (%d bytes)... ", MSG_SIZE);
    st = std::clock();
    for (int i = 0; i < LOOP; i++)
    {
        std::size_t tmp;
        sk.decrypt0(pt_buf.get(), &tmp, ct_buf.get(), ct_len,
                    (const std::uint8_t*)ID, std::strlen(ID));
    }
    et     = std::clock();
    time_s = (double)(et - st) / CLOCKS_PER_SEC;
    opt_s  = LOOP / time_s;
    std::printf("%g opt/s\n", opt_s);
}
