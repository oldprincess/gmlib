#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm4/provider.h>
#include <gmlib/sm4/sm4.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

int main()
{
    log("sm4 gcm demo begin");

    std::uint8_t user_key[sm4::SM4::USER_KEY_LEN], iv[12], aad[16];
    std::uint8_t buf[32], tag[16];
    std::size_t  outl;

    auto provider = sm4::get_sm4_provider(nullptr);
    if (provider == nullptr)
    {
        log("provider not found");
        return -1;
    }
    if (provider->create_gcm_encryptor == nullptr ||
        provider->create_gcm_decryptor == nullptr)
    {
        log("provider not support gcm mode");
        return -1;
    }
    auto        encryptor = provider->create_gcm_encryptor();
    auto        decryptor = provider->create_gcm_decryptor();
    rng::StdRng rng;

    log("generate random user key");
    rng.gen(user_key, sizeof(user_key));
    memory_utils::memdump(user_key, sizeof(user_key));

    log("generate random iv");
    rng.gen(iv, sizeof(iv));
    memory_utils::memdump(iv, sizeof(iv));

    log("generate random aad");
    rng.gen(aad, sizeof(aad));
    memory_utils::memdump(aad, sizeof(aad));

    log("generate random msg");
    rng.gen(buf, sizeof(buf));
    memory_utils::memdump(buf, sizeof(buf));

    log("encrypt");
    encryptor->init(user_key, sizeof(user_key), iv, sizeof(iv), aad,
                    sizeof(aad));
    encryptor->do_final(buf, &outl, sizeof(buf), buf, sizeof(buf));
    encryptor->get_tag(tag, sizeof(tag));
    log("ciphertext: ");
    memory_utils::memdump(buf, sizeof(buf));
    log("tag: ");
    memory_utils::memdump(tag, sizeof(tag));

    log("decrypt");
    decryptor->init(user_key, sizeof(user_key), iv, sizeof(iv), aad,
                    sizeof(aad));
    decryptor->set_tag(tag, sizeof(tag));
    decryptor->do_final(buf, &outl, sizeof(buf), buf, sizeof(buf));
    log("plaintext: ");
    memory_utils::memdump(buf, sizeof(buf));

    log("sm4 gcm demo end");

    return 0;
}
