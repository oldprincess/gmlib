#ifndef SHA1_CONFIG_H
#define SHA1_CONFIG_H

#if defined(CPU_FLAG_INTEL_SHA) && defined(CPU_FLAG_INTEL_SSE4_1)
#define SHA1_IMPL_SHA
#else
#define SHA1_IMPL_COMMON
#endif

#endif