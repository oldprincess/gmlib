#include <gmlib/des/des.h>

#include <cstdio>
#include <cstdlib>

using namespace des;

#define MEM_LOAD64BE(src)                        \
    (((uint64_t)(((uint8_t *)(src))[0]) << 56) | \
     ((uint64_t)(((uint8_t *)(src))[1]) << 48) | \
     ((uint64_t)(((uint8_t *)(src))[2]) << 40) | \
     ((uint64_t)(((uint8_t *)(src))[3]) << 32) | \
     ((uint64_t)(((uint8_t *)(src))[4]) << 24) | \
     ((uint64_t)(((uint8_t *)(src))[5]) << 16) | \
     ((uint64_t)(((uint8_t *)(src))[6]) << 8) |  \
     ((uint64_t)(((uint8_t *)(src))[7]) << 0))

#define MEM_STORE64BE(dst, a)                              \
    (((uint8_t *)(dst))[0] = ((uint64_t)(a) >> 56) & 0xFF, \
     ((uint8_t *)(dst))[1] = ((uint64_t)(a) >> 48) & 0xFF, \
     ((uint8_t *)(dst))[2] = ((uint64_t)(a) >> 40) & 0xFF, \
     ((uint8_t *)(dst))[3] = ((uint64_t)(a) >> 32) & 0xFF, \
     ((uint8_t *)(dst))[4] = ((uint64_t)(a) >> 24) & 0xFF, \
     ((uint8_t *)(dst))[5] = ((uint64_t)(a) >> 16) & 0xFF, \
     ((uint8_t *)(dst))[6] = ((uint64_t)(a) >> 8) & 0xFF,  \
     ((uint8_t *)(dst))[7] = ((uint64_t)(a) >> 0) & 0xFF)

// test vector gen from: https://www.mklab.cn/utils/des
static uint64_t pt[] = {
    0x3030303030303030,
    0x3131313131313131,
    0x3132333434333231,
    0x3132333434333231,
};
static uint64_t key[] = {
    0x0000000000000000,
    0x0000000000000000,
    0x0000000000000000,
    0x0123456776543210,
};
static uint64_t ct[] = {
    0xde8d55142b18deb7,
    0x238d5aa666706c3a,
    0x968761d7a3927826,
    0x0470c53d49847abd,
};

void test_des()
{
    DES     ctx;
    uint8_t in[8], out[8], user_key[8];
    for (int i = 0; i < sizeof(pt) / sizeof(pt[0]); i++)
    {
        MEM_STORE64BE(in, pt[i]);
        MEM_STORE64BE(user_key, key[i]);
        ctx.set_key(user_key, DES::ENCRYPTION);
        ctx.encrypt_block(out, in);
        if (MEM_LOAD64BE(out) != ct[i])
        {
            std::printf("err in des common enc, file: %s, line: %d\n", __FILE__,
                        __LINE__);
            std::printf("%llx %llx %llx\n", pt[i], ct[i],
                        (unsigned long long)MEM_LOAD64BE(out));
            std::exit(-1);
        }
        ctx.encrypt_blocks(out, in, 1);
        if (MEM_LOAD64BE(out) != ct[i])
        {
            std::printf("err in des common enc, file: %s, line: %d\n", __FILE__,
                        __LINE__);
            std::printf("%llx %llx %llx\n", pt[i], ct[i],
                        (unsigned long long)MEM_LOAD64BE(out));
            std::exit(-1);
        }
        MEM_STORE64BE(in, ct[i]);
        MEM_STORE64BE(user_key, key[i]);
        ctx.set_key(user_key, DES::DECRYPTION);
        ctx.decrypt_block(out, in);
        if (MEM_LOAD64BE(out) != pt[i])
        {
            std::printf("err in des common dec, file: %s, line: %d\n", __FILE__,
                        __LINE__);
            std::exit(-1);
        }
        ctx.decrypt_blocks(out, in, 1);
        if (MEM_LOAD64BE(out) != pt[i])
        {
            std::printf("err in des common dec, file: %s, line: %d\n", __FILE__,
                        __LINE__);
            std::exit(-1);
        }
    }
}