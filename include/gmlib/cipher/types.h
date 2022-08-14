#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdint.h>

typedef void (*CipherInit)(uint8_t* key, void* ctx);
typedef void (*CipherEncrypt)(uint8_t* out, uint8_t* in, void* ctx);
typedef void (*CipherDecrypt)(uint8_t* out, uint8_t* in, void* ctx);

typedef struct CipherInfo {
    CipherInit init;
    CipherEncrypt encrypt;
    CipherDecrypt decrypt;
} CipherInfo;

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // TYPES_H
