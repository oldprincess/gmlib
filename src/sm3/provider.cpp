#include <gmlib/sm3/sm3.h>

#include <cstring>
#include <stdexcept>

#include "config.h"
#include "provider_sm3_common.h"
#include "provider_sm3_yang15.h"

namespace sm3 {

hash_lib::Hash::HashPtr SM3::create_hash(const char* provider)
{
#if defined(SM3_IMPL_YANG15)
    if (internal::yang15::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "yang15") == 0)
        {
            return internal::yang15::create_hash();
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

} // namespace sm3
