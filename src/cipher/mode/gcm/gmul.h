#ifndef GMUL_H
#define GMUL_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

#include <gmlib/cipher/mode.h>

void gmul_common(uint8_t* r, uint8_t* X, uint8_t* H);

void ghash_init_htable(uint8_t* H, GHashTable t);

void gmul_htable(uint8_t* r, uint8_t* X, GHashTable t);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // GMUL_H
