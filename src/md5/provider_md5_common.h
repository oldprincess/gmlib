#ifndef MD5_INTERNAL_PROVIDER_MD5_COMMON_H
#define MD5_INTERNAL_PROVIDER_MD5_COMMON_H

#include <gmlib/hash_lib/hash.h>

namespace md5::internal::common {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace md5::internal::common

#endif