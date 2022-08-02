#ifndef SM3_COMMON_H
#define SM3_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

void sm3_common_compress(uint8_t* data, uint32_t* digest);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // SM3_COMMON_H
