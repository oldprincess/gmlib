#ifndef GHASH_INTERNAL_PROVIDER_GHASH_PCLMUL_H
#define GHASH_INTERNAL_PROVIDER_GHASH_PCLMUL_H

#include "config.h"

#if defined(GHASH_IMPL_PCLMUL)

#include <gmlib/hash_lib/hash.h>

namespace ghash::internal::pclmul {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace ghash::internal::pclmul

#endif

#endif