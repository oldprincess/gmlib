#ifndef GHASH_INTERNAL_PROVIDER_GHASH_COMMON_H
#define GHASH_INTERNAL_PROVIDER_GHASH_COMMON_H

#include "config.h"

#if defined(GHASH_IMPL_COMMON)

#include <gmlib/hash_lib/hash.h>

namespace ghash::internal::common {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace ghash::internal::common

#endif

#endif