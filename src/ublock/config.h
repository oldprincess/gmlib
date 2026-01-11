#ifndef UBLOCK_CONFIG_H
#define UBLOCK_CONFIG_H

#if defined(__SSSE3__)
#define UBLOCK_IMPL_STANDARD
#endif

#if defined(SUPPORT_UBLOCK_GONG25)
#if defined(__AVX2__)
#define UBLOCK_IMPL_GONG25
#endif
#endif

#define UBLOCK_IMPL_COMMON

#endif