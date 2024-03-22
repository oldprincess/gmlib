#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm4/sm4.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

int main()
{
    log("sm4 cipher demo begin");

    std::uint8_t user_key[sm4::SM4::USER_KEY_LEN];
    std::uint8_t buf[32];

    sm4::SM4    cipher;
    rng::StdRng rng;

    log("generate random user key");
    rng.gen(user_key, sizeof(user_key));
    memory_utils::memdump(user_key, sizeof(user_key));

    log("generate random msg");
    rng.gen(buf, sizeof(buf));
    memory_utils::memdump(buf, sizeof(buf));

    log("encrypt");
    cipher.set_key(user_key, sm4::SM4::ENCRYPTION);
    cipher.encrypt_blocks(buf, buf, sizeof(buf) / cipher.BLOCK_SIZE);
    memory_utils::memdump(buf, sizeof(buf));

    log("decrypt");
    cipher.set_key(user_key, sm4::SM4::DECRYPTION);
    cipher.encrypt_blocks(buf, buf, sizeof(buf) / cipher.BLOCK_SIZE);
    memory_utils::memdump(buf, sizeof(buf));

    log("sm4 cipher demo end");
    return 0;
}