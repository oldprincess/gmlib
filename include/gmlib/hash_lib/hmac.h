#ifndef HASH_LIB_HMAC_H
#define HASH_LIB_HMAC_H

#include <gmlib/hash_lib/impl/hmac_impl.h>

namespace hash_lib {

template <class Hash>
using HMac = impl::HMacImpl<Hash>;

} // namespace hash_lib

#endif