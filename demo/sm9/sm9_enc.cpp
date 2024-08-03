#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm3/sm3.h>
#include <gmlib/sm9/sm9.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

constexpr int PT_SIZE = 64;

int main()
{
    log("sm9-sm3 enc demo begin");

    sm9::SM9EncryptMasterPrivateKey<sm3::SM3> master_priv_key;
    sm9::SM9EncryptPrivateKey<sm3::SM3>       priv_key;
    sm9::SM9EncryptPublicKey<sm3::SM3>        pub_key;
    rng::StdRng                               rng;

    std::unique_ptr<std::uint8_t[]> ct(nullptr);
    std::unique_ptr<std::uint8_t[]> buf(nullptr);

    std::uint8_t pt[PT_SIZE];
    std::size_t  ct_len, buf_len;
    std::uint8_t data_pub_x[32], data_pub_y[32], data_master_priv[32];
    std::uint8_t data_priv_x[64], data_priv_y[64];
    std::uint8_t id[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};

    // =========== key generate ============

    log("generate random master private key");
    master_priv_key.gen_priv(rng);
    master_priv_key.get_priv(data_master_priv);
    memory_utils::memdump(data_master_priv, sizeof(data_master_priv), 32);

    log("gen private key");
    priv_key = master_priv_key.gen_EncryptPrivateKey(id, sizeof(id));
    priv_key.get_priv(data_priv_x, data_priv_y, data_pub_x, data_pub_y);

    log("public key - x");
    memory_utils::memdump(data_pub_x, sizeof(data_pub_x), 32);
    log("public key - y");
    memory_utils::memdump(data_pub_y, sizeof(data_pub_y), 32);

    log("rand plaintext");
    rng.gen(pt, PT_SIZE);
    memory_utils::memdump(pt, PT_SIZE, 32);

    // store data_priv_x, data_priv_y, data_pub_x, data_pub_y to some place

    log("encrypt");
    pub_key.set_pub(data_pub_x, data_pub_y);
    ct_len = pub_key.ciphertext_len(pt, PT_SIZE);
    ct = std::move(std::unique_ptr<std::uint8_t[]>(new std::uint8_t[ct_len]));
    pub_key.encrypt0(ct.get(), &ct_len, pt, PT_SIZE, id, sizeof(id), rng);
    memory_utils::memdump(ct.get(), ct_len, 32);

    log("decrypt");
    priv_key.set_priv(data_priv_x, data_priv_y, data_pub_x, data_pub_y);
    buf = std::move(                                                   //
        std::unique_ptr<std::uint8_t[]>(                               //
            new std::uint8_t[priv_key.plaintext_len(ct.get(), ct_len)] //
            )                                                          //
    );
    priv_key.decrypt0(buf.get(), &buf_len, ct.get(), ct_len, id, sizeof(id));
    memory_utils::memdump(buf.get(), buf_len, 32);

    log("sm9-sm3 enc demo end");
    return 0;
}