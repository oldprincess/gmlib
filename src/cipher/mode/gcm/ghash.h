#ifndef GHASH_H
#define GHASH_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <gmlib/cipher/mode.h>

void ghash_init(uint8_t* H, GHashTable* ht, GHash_CTX* ctx);

void ghash_reset(GHash_CTX* ctx);

void ghash_update(uint8_t* in, int inl, GHash_CTX* ctx);

void ghash_final(uint8_t* out, GHash_CTX* ctx);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // GHASH_H
