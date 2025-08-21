#ifndef BASE64_CONFIG_H
#define BASE64_CONFIG_H

#if defined(__AVX2__)
#define BASE64_IMPL_AVX2
#endif

#if defined(SUPPORT_BASE64_CHROMIUM)
#define BASE64_IMPL_CHROMIUM
#endif

#define BASE64_IMPL_COMMON

#endif