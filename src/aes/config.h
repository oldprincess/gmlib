#ifndef AES_CONFIG_H
#define AES_CONFIG_H

#if defined(CPU_FLAG_INTEL_AES) && defined(CPU_FLAG_INTEL_SSE2)
#define AES_IMPL_AESNI
#endif

#if defined(CPU_FLAG_ARM_AES)
#define AES_IMPL_ARM_AES
#endif

#define AES_IMPL_LUT

#endif