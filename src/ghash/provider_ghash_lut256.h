#ifndef GHASH_INTERNAL_PROVIDER_GHASH_LUT256_H
#define GHASH_INTERNAL_PROVIDER_GHASH_LUT256_H

#include <gmlib/hash_lib/hash.h>

namespace ghash::internal::lut256 {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace ghash::internal::lut256

#endif
