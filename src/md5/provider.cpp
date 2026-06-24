#include <gmlib/md5/md5.h>

#include <cstring>
#include <stdexcept>

#include "provider_md5_common.h"

namespace md5 {

hash_lib::Hash::HashPtr MD5::create_hash(const char* provider)
{
    if (internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return internal::common::create_hash();
        }
    }
    throw std::runtime_error("No provider available");
}

} // namespace md5
