#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/sha2/sha2.h>

#include <cstring>
#include <stdexcept>

#include "provider_sha2_common.h"
#include "provider_sha2_sha.h"

namespace sha2 {

// SHA224

hash_lib::Hash::HashPtr SHA224::create_hash(const char* provider)
{
#if defined(SHA224_256_IMPL_SHA)
    if (internal::sha::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sha") == 0)
        {
            return internal::sha::create_sha224();
        }
    }
#endif
    if (internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return internal::common::create_sha224();
        }
    }
    throw std::runtime_error("No provider available");
}

// SHA256

hash_lib::Hash::HashPtr SHA256::create_hash(const char* provider)
{
#if defined(SHA224_256_IMPL_SHA)
    if (internal::sha::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sha") == 0)
        {
            return internal::sha::create_sha256();
        }
    }
#endif
    if (internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return internal::common::create_sha256();
        }
    }
    throw std::runtime_error("No provider available");
}

// SHA384

hash_lib::Hash::HashPtr SHA384::create_hash(const char* provider)
{
    if (internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return internal::common::create_sha384();
        }
    }
    throw std::runtime_error("No provider available");
}

// SHA512

hash_lib::Hash::HashPtr SHA512::create_hash(const char* provider)
{
    if (internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return internal::common::create_sha512();
        }
    }
    throw std::runtime_error("No provider available");
}

} // namespace sha2
