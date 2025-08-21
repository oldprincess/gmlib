#ifndef AES_CONFIG_H
#define AES_CONFIG_H

#if defined(__AES__) && defined(__SSE2__)
#define AES_IMPL_AESNI
#endif

#if defined(__ARM_NEON)
#define AES_IMPL_ARM_AES
#endif

#define AES_IMPL_LUT

#endif