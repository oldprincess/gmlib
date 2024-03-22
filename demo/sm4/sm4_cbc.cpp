#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm4/sm4_mode.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

int main()
{
    log("sm4 cbc demo begin");

    std::uint8_t user_key[sm4::SM4::USER_KEY_LEN], iv[sm4::SM4::BLOCK_SIZE];
    std::uint8_t buf[32];
    std::size_t  outl;

    sm4::SM4CbcEncryptor encryptor;
    sm4::SM4CbcDecryptor decryptor;
    rng::StdRng          rng;

    log("generate random user key");
    rng.gen(user_key, sizeof(user_key));
    memory_utils::memdump(user_key, sizeof(user_key));

    log("generate random iv");
    rng.gen(iv, sizeof(iv));
    memory_utils::memdump(iv, sizeof(iv));

    log("generate random msg");
    rng.gen(buf, sizeof(buf));
    memory_utils::memdump(buf, sizeof(buf));

    log("encrypt");
    encryptor.init(user_key, iv);
    encryptor.do_final(buf, &outl, buf, sizeof(buf));
    memory_utils::memdump(buf, sizeof(buf));

    log("decrypt");
    decryptor.init(user_key, iv);
    decryptor.do_final(buf, &outl, buf, sizeof(buf));
    log("plaintext: ");
    memory_utils::memdump(buf, sizeof(buf));

    log("sm4 cbc demo end");
    return 0;
}