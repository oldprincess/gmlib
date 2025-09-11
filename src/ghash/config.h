#ifndef GHASH_CONFIG_H
#define GHASH_CONFIG_H

#if defined(__PCLMUL__) && defined(__SSE2__) && defined(__SSSE3__)
#define GHASH_IMPL_PCLMUL
#endif

#define GHASH_IMPL_LUT256

#define GHASH_IMPL_COMMON

#endif