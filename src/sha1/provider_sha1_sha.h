#if defined(SUPPORT_SHA1_SHA)

#ifndef SHA1_INTERNAL_PROVIDER_SHA1_SHA_H
#define SHA1_INTERNAL_PROVIDER_SHA1_SHA_H

#include <gmlib/hash_lib/hash.h>

namespace sha1::internal::sha {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace sha1::internal::sha

#endif

#endif
