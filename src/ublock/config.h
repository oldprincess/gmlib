#ifndef UBLOCK_CONFIG_H
#define UBLOCK_CONFIG_H

#if defined(CPU_FLAG_INTEL_SSSE3)
#define UBLOCK_IMPL_STANDARD
#else
#define UBLOCK_IMPL_COMMON
#endif

#endif