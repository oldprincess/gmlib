#include <gmlib/hash/sm3.h>
#include <gmlib/utils.h>

int main() {
    SM3_CTX sm3_ctx;
    uint8_t msg[] = {'a', 'b', 'c'};  // 原始消息
    uint8_t digest[SM3_DIGEST_SIZE];  // 消息摘要

    // 初始化 SM3
    sm3_init(&sm3_ctx);
    // 输入消息
    sm3_update(msg, sizeof(msg), &sm3_ctx);
    // 结束 SM3 并输出摘要 digest
    sm3_final(digest, &sm3_ctx);

    dump_data(digest, sizeof(digest));
    /*  SM3 摘要结果
        66 c7 f0 f4 62 ee ed d9 d1 f2 d4 6b dc 10 e4 e2
        41 67 c4 87 5c f2 f7 a2 29 7d a0 2b 8f 4b a8 e0
    */
    return 0;
}
