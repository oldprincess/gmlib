#ifndef SHA2_CONFIG_H
#define SHA2_CONFIG_H

#if defined(__SHA__) && defined(__SSE4_1__)
#define SHA224_256_IMPL_SHA
#endif

#define SHA2_IMPL_COMMON

#endif