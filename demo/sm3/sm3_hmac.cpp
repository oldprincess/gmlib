#include <gmlib/hash_lib/hmac.h>
#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm3/sm3.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

constexpr int MSG_SIZE = 128;

int main()
{
    log("sm3 hmac demo begin");

    std::uint8_t msg[MSG_SIZE], out[sm3::SM3::DIGEST_SIZE];
    std::uint8_t key[sm3::SM3::BLOCK_SIZE];
    rng::StdRng  rng;

    log("rand memory");
    rng.gen(msg, MSG_SIZE);
    memory_utils::memdump(msg, MSG_SIZE);

    log("rand key");
    rng.gen(key, sizeof(key));
    memory_utils::memdump(key, sizeof(key));

    log("compute hmac");
    hash_lib::HMac<sm3::SM3> hmac;
    hmac.set_key(key, sizeof(key));
    hmac.update(msg, MSG_SIZE);
    hmac.do_final(out);
    memory_utils::memdump(out, sizeof(out));

    log("sm3 hmac demo end");
    return 0;
}