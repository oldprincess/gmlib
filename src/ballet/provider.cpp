#include <gmlib/ballet/provider.h>

#include <array>

#include "provider_ballet_standard.h"

namespace ballet {
namespace {

using block_cipher_mode::impl::BlockCipherModeProviderEntry;

static const BlockCipherModeProviderEntry* const providers_128128[] = {
    &internal::standard::provider_128128,
};
static const BlockCipherModeProviderEntry* const providers_128256[] = {
    &internal::standard::provider_128256,
};
static const BlockCipherModeProviderEntry* const providers_256256[] = {
    &internal::standard::provider_256256,
};

constexpr std::size_t PROVIDER_128128_NUM = std::size(providers_128128);
constexpr std::size_t PROVIDER_128256_NUM = std::size(providers_128256);
constexpr std::size_t PROVIDER_256256_NUM = std::size(providers_256256);

} // namespace

const Ballet128128Provider* get_ballet128128_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Ballet128128Provider* default_provider =
            block_cipher_mode::impl::get_provider(nullptr, providers_128128,
                                                  PROVIDER_128128_NUM);
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers_128128,
                                                 PROVIDER_128128_NUM);
}

const char* const* get_ballet128128_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_128128_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers_128128, PROVIDER_128128_NUM);
        return names;
    }();
    return name_list.data();
}

const Ballet128256Provider* get_ballet128256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Ballet128256Provider* default_provider =
            block_cipher_mode::impl::get_provider(nullptr, providers_128256,
                                                  PROVIDER_128256_NUM);
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers_128256,
                                                 PROVIDER_128256_NUM);
}

const char* const* get_ballet128256_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_128256_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers_128256, PROVIDER_128256_NUM);
        return names;
    }();
    return name_list.data();
}

const Ballet256256Provider* get_ballet256256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const Ballet256256Provider* default_provider =
            block_cipher_mode::impl::get_provider(nullptr, providers_256256,
                                                  PROVIDER_256256_NUM);
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers_256256,
                                                 PROVIDER_256256_NUM);
}

const char* const* get_ballet256256_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_256256_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers_256256, PROVIDER_256256_NUM);
        return names;
    }();
    return name_list.data();
}

} // namespace ballet
