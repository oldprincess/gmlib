#ifndef SHA1_INTERNAL_PROVIDER_SHA1_COMMON_H
#define SHA1_INTERNAL_PROVIDER_SHA1_COMMON_H

#include "config.h"

#if defined(SHA1_IMPL_COMMON)

#include <gmlib/hash_lib/hash.h>

namespace sha1::internal::common {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace sha1::internal::common

#endif

#endif