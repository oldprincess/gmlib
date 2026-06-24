#ifndef SHA1_INTERNAL_PROVIDER_SHA1_SHA_H
#define SHA1_INTERNAL_PROVIDER_SHA1_SHA_H

#include "config.h"

#if defined(SHA1_IMPL_SHA)

#include <gmlib/hash_lib/hash.h>

namespace sha1::internal::sha {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace sha1::internal::sha

#endif

#endif