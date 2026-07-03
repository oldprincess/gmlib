#ifndef SM3_INTERNAL_PROVIDER_SM3_COMMON_H
#define SM3_INTERNAL_PROVIDER_SM3_COMMON_H

#include <gmlib/hash_lib/hash.h>

namespace sm3::internal::common {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace sm3::internal::common

#endif
