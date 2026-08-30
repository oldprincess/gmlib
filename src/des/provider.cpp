#include <gmlib/des/provider.h>

#include <array>

#include "provider_des_common.h"

namespace des {
namespace {

using block_cipher_mode::impl::BlockCipherModeProviderEntry;

static const BlockCipherModeProviderEntry* const providers[] = {
    &internal::common::provider,
};

constexpr std::size_t PROVIDER_NUM = std::size(providers);

} // namespace

const DESProvider* get_des_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const DESProvider* default_provider =
            block_cipher_mode::impl::get_provider(nullptr, providers,
                                                  PROVIDER_NUM);
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers, PROVIDER_NUM);
}

const char* const* get_des_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers, PROVIDER_NUM);
        return names;
    }();
    return name_list.data();
}

} // namespace des
