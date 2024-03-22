#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm3/sm3.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

constexpr int MSG_SIZE = 128;

int main()
{
    log("sm3 hash demo begin");

    std::uint8_t msg[MSG_SIZE], out[sm3::SM3::DIGEST_SIZE];
    rng::StdRng  rng;

    log("rand memory");
    rng.gen(msg, MSG_SIZE);
    memory_utils::memdump(msg, MSG_SIZE);

    log("compute digest");
    sm3::SM3 hash;
    hash.update(msg, MSG_SIZE);
    hash.do_final(out);
    memory_utils::memdump(out, sizeof(out));

    log("sm3 hash demo end");
    return 0;
}