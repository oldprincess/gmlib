#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm3/sm3.h>
#include <gmlib/sm9/sm9.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

constexpr int MSG_SIZE = 64;

int main()
{
    log("sm9-sm3 sign demo begin");

    sm9::SM9SignMasterPrivateKey<sm3::SM3> master_priv_key;
    sm9::SM9SignPrivateKey<sm3::SM3>       priv_key;
    sm9::SM9SignPublicKey<sm3::SM3>        pub_key;
    rng::StdRng                            rng;

    std::uint8_t msg[MSG_SIZE];
    std::uint8_t sig[sm9::SM9SignPrivateKey<sm3::SM3>::MAX_SIG_SIZE];
    std::size_t  sig_len;
    std::uint8_t data_pub_x[64], data_pub_y[64], data_master_priv[32];
    std::uint8_t data_priv_x[32], data_priv_y[32];
    std::uint8_t id[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};

    // =========== key generate ============

    log("generate random master private key");
    master_priv_key.gen_priv(rng);
    master_priv_key.get_priv(data_master_priv);
    memory_utils::memdump(data_master_priv, sizeof(data_master_priv), 32);

    log("gen private key");
    priv_key = master_priv_key.gen_SignPrivateKey(id, sizeof(id), rng);
    priv_key.get_priv(data_priv_x, data_priv_y, data_pub_x, data_pub_y);

    log("public key - x");
    memory_utils::memdump(data_pub_x, sizeof(data_pub_x), 32);
    log("public key - y");
    memory_utils::memdump(data_pub_y, sizeof(data_pub_y), 32);

    log("rand msg");
    rng.gen(msg, MSG_SIZE);
    memory_utils::memdump(msg, MSG_SIZE, 32);

    // store data_priv_x, data_priv_y, data_pub_x, data_pub_y to some place

    log("sign");
    priv_key.set_priv(data_priv_x, data_priv_y, data_pub_x, data_pub_y);
    priv_key.sign(sig, &sig_len, msg, sizeof(msg), rng);
    memory_utils::memdump(sig, sizeof(sig), 32);

    log("verify");
    pub_key.set_pub(data_pub_x, data_pub_y);
    std::cout << pub_key.verify(sig, sig_len, msg, sizeof(msg), id, sizeof(id))
              << std::endl;

    log("sm9-sm3 sign demo end");
    return 0;
}