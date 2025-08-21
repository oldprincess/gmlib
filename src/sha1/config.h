#ifndef SHA1_CONFIG_H
#define SHA1_CONFIG_H

#if defined(__SHA__) && defined(__SSE4_1__)
#define SHA1_IMPL_SHA
#endif

#define SHA1_IMPL_COMMON

#endif