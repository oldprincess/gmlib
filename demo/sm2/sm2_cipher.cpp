#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm2/sm2.h>
#include <gmlib/sm3/sm3.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

constexpr int MSG_SIZE = 64;

int main()
{
    log("sm2-sm3 sign demo begin");

    sm2::SM2PrivateKey<sm3::SM3> priv_key;
    sm2::SM2PublicKey<sm3::SM3>  pub_key;
    rng::StdRng                  rng;

    std::uint8_t msg[MSG_SIZE];
    std::uint8_t ct[1024], pt[1024];
    std::size_t  ct_len, pt_len;
    std::uint8_t data_pub_x[32], data_pub_y[32], data_priv[32];

    log("generate random private key");
    priv_key.gen_priv(rng);
    priv_key.get_priv(data_priv);
    memory_utils::memdump(data_priv, sizeof(data_priv));

    log("fetch public key");
    pub_key = priv_key.fetch_pub();
    pub_key.get_pub(data_pub_x, data_pub_y);
    log("public key - x");
    memory_utils::memdump(data_pub_x, sizeof(data_pub_x));
    log("public key - y");
    memory_utils::memdump(data_pub_y, sizeof(data_pub_y));

    log("rand msg");
    rng.gen(msg, MSG_SIZE);
    memory_utils::memdump(msg, MSG_SIZE);

    // store data_pub_x[32], data_pub_y[32], data_priv[32] to some place

    log("encrypt");
    pub_key.set_pub(data_pub_x, data_pub_y);
    if (sizeof(ct) < pub_key.ciphertext_len(msg, sizeof(msg)))
    {
        log("err");
        return -1;
    }
    pub_key.encrypt(ct, &ct_len, msg, sizeof(msg), rng);
    memory_utils::memdump(ct, ct_len);

    log("decrypt");
    priv_key.set_priv(data_priv);
    if (sizeof(pt) < priv_key.plaintext_len(ct, ct_len))
    {
        log("err");
        return -1;
    }
    priv_key.decrypt(pt, &pt_len, ct, ct_len);
    memory_utils::memdump(pt, pt_len);

    log("sm2-sm3 sign demo end");
    return 0;
}