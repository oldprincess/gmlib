#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/ghash/ghash.h>

#include <cstring>
#include <stdexcept>

#include "provider_ghash_common.h"
#include "provider_ghash_lut256.h"
#include "provider_ghash_pclmul.h"

namespace ghash {

hash_lib::Hash::HashPtr GHash::create_hash(const char* provider)
{
#if defined(GHASH_IMPL_PCLMUL)
    if (ghash::internal::pclmul::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "pclmul") == 0)
        {
            return ghash::internal::pclmul::create_hash();
        }
    }
#endif
    if (ghash::internal::lut256::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut256") == 0)
        {
            return ghash::internal::lut256::create_hash();
        }
    }
    if (ghash::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ghash::internal::common::create_hash();
        }
    }
    throw std::runtime_error("No provider available");
}

} // namespace ghash
