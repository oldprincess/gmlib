#if defined(SM3_IMPL_YANG15)

#ifndef SM3_INTERNAL_PROVIDER_SM3_YANG15_H
#define SM3_INTERNAL_PROVIDER_SM3_YANG15_H

#include <gmlib/hash_lib/hash.h>

namespace sm3::internal::yang15 {

bool provider_available();

hash_lib::Hash::HashPtr create_hash();

} // namespace sm3::internal::yang15

#endif

#endif
