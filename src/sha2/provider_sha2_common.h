#ifndef SHA2_INTERNAL_PROVIDER_SHA2_COMMON_H
#define SHA2_INTERNAL_PROVIDER_SHA2_COMMON_H

#include <gmlib/hash_lib/hash.h>

namespace sha2::internal::common {

bool provider_available();

hash_lib::Hash::HashPtr create_sha224();

hash_lib::Hash::HashPtr create_sha256();

hash_lib::Hash::HashPtr create_sha384();

hash_lib::Hash::HashPtr create_sha512();

} // namespace sha2::internal::common

#endif
