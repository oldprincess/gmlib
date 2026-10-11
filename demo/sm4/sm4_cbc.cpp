#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm4/provider.h>
#include <gmlib/sm4/sm4.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

int main()
{
    log("sm4 cbc demo begin");

    std::uint8_t user_key[sm4::SM4::USER_KEY_LEN], iv[sm4::SM4::BLOCK_SIZE];
    std::uint8_t buf0[32], buf1[32];
    std::size_t  outl;

    auto provider = sm4::get_sm4_provider(nullptr);
    if (provider == nullptr)
    {
        log("provider not found");
        return -1;
    }
    if (provider->create_cbc_encryptor == nullptr ||
        provider->create_cbc_decryptor == nullptr)
    {
        log("provider not support cbc mode");
        return -1;
    }
    auto        encryptor = provider->create_cbc_encryptor();
    auto        decryptor = provider->create_cbc_decryptor();
    rng::StdRng rng;

    log("generate random user key");
    rng.gen(user_key, sizeof(user_key));
    memory_utils::memdump(user_key, sizeof(user_key));

    log("generate random iv");
    rng.gen(iv, sizeof(iv));
    memory_utils::memdump(iv, sizeof(iv));

    log("generate random msg");
    rng.gen(buf0, sizeof(buf0));
    memory_utils::memdump(buf0, sizeof(buf0));

    log("encrypt");
    encryptor->init(user_key, sizeof(user_key), iv, sizeof(iv), nullptr, 0);
    encryptor->do_final(buf1, &outl, sizeof(buf1), buf0, sizeof(buf0));
    memory_utils::memdump(buf1, sizeof(buf1));

    log("decrypt");
    decryptor->init(user_key, sizeof(user_key), iv, sizeof(iv), nullptr, 0);
    decryptor->do_final(buf0, &outl, sizeof(buf0), buf1, sizeof(buf1));
    log("plaintext: ");
    memory_utils::memdump(buf0, sizeof(buf0));

    log("sm4 cbc demo end");
    return 0;
}