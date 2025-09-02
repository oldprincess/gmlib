#ifndef SM4_CONFIG_H

#if defined(SUPPORT_SM4_LANG18)
#if defined(__AVX2__)
#define SM4_IMPL_LANG18
#endif
#endif

#if defined(SUPPORT_SM4_GONG23)
#if defined(__AVX512BW__) && defined(__AVX512VL__) && defined(__AVX512F__) && \
    defined(__GFNI__)
#define SM4_IMPL_GONG23
#endif
#endif

#define SM4_IMPL_COMMON

#endif