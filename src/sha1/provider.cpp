#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/sha1/sha1.h>

#include <cstring>
#include <stdexcept>

#include "provider_sha1_common.h"
#include "provider_sha1_sha.h"

namespace sha1 {

hash_lib::Hash::HashPtr SHA1::create_hash(const char* provider)
{
#if defined(SHA1_IMPL_SHA)
    if (internal::sha::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sha") == 0)
        {
            return internal::sha::create_hash();
        }
    }
#endif
    if (internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return internal::common::create_hash();
        }
    }
    throw std::runtime_error("No provider available");
}

} // namespace sha1
