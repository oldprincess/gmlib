#ifndef GHASH_CONFIG_H
#define GHASH_CONFIG_H

#if defined(CPU_FLAG_INTEL_PCLMUL) && defined(CPU_FLAG_INTEL_SSE2)
#define GHASH_IMPL_PCLMUL
#else
#define GHASH_IMPL_LUT256
#endif

#endif