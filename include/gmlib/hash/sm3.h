#ifndef SM3_H
#define SM3_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

#define SM3_DIGEST_SIZE (256 / 8)
#define SM3_BLOCK_SIZE (512 / 8)
typedef struct SM3_CTX {
    uint32_t state[8];
    uint8_t buffer[SM3_BLOCK_SIZE];
    int bsize;
    uint64_t dbits;
} SM3_CTX;

void sm3_init(SM3_CTX* ctx);
void sm3_update(uint8_t* in, int inl, SM3_CTX* ctx);
void sm3_final(uint8_t* out, SM3_CTX* ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // SM3_H
