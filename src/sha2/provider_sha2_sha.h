#if defined(SHA224_256_IMPL_SHA)

#ifndef SHA2_INTERNAL_PROVIDER_SHA2_SHA_H
#define SHA2_INTERNAL_PROVIDER_SHA2_SHA_H

#include <gmlib/hash_lib/hash.h>

namespace sha2::internal::sha {

bool provider_available();

hash_lib::Hash::HashPtr create_sha224();

hash_lib::Hash::HashPtr create_sha256();

} // namespace sha2::internal::sha

#endif

#endif
