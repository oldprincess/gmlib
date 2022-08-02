#ifndef PAD_H
#define PAD_H

#include <stdint.h>

void pkcs7_pad(uint8_t* out, int* outl, uint8_t* in, int inl, int block_size);
int pkcs7_unpad(uint8_t* out, int* outl, uint8_t* in, int inl, int block_size);

#endif // PAD_H
