#include <gmlib/aes/provider.h>

#include <array>

#if defined(SUPPORT_AES_AESNI)
#include "provider_aes_aesni.h"
#endif
#if defined(SUPPORT_AES_ARM_AES)
#include "provider_aes_arm_aes.h"
#endif
#include "provider_aes_lut.h"

namespace aes {
namespace {

using block_cipher_mode::impl::BlockCipherModeProviderEntry;

static const BlockCipherModeProviderEntry* const providers_128[] = {
#if defined(SUPPORT_AES_AESNI)
    &internal::aesni::provider_128,
#endif
#if defined(SUPPORT_AES_ARM_AES)
    &internal::arm_aes::provider_128,
#endif
    &internal::lut::provider_128,
};
static const BlockCipherModeProviderEntry* const providers_192[] = {
#if defined(SUPPORT_AES_AESNI)
    &internal::aesni::provider_192,
#endif
#if defined(SUPPORT_AES_ARM_AES)
    &internal::arm_aes::provider_192,
#endif
    &internal::lut::provider_192,
};
static const BlockCipherModeProviderEntry* const providers_256[] = {
#if defined(SUPPORT_AES_AESNI)
    &internal::aesni::provider_256,
#endif
#if defined(SUPPORT_AES_ARM_AES)
    &internal::arm_aes::provider_256,
#endif
    &internal::lut::provider_256,
};

constexpr std::size_t PROVIDER_128_NUM = std::size(providers_128);
constexpr std::size_t PROVIDER_192_NUM = std::size(providers_192);
constexpr std::size_t PROVIDER_256_NUM = std::size(providers_256);

} // namespace

const AES128Provider* get_aes128_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const AES128Provider* default_provider =
            block_cipher_mode::impl::get_provider(nullptr, providers_128,
                                                  PROVIDER_128_NUM);
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers_128,
                                                 PROVIDER_128_NUM);
}

const char* const* get_aes128_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_128_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers_128, PROVIDER_128_NUM);
        return names;
    }();
    return name_list.data();
}

const AES192Provider* get_aes192_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const AES192Provider* default_provider =
            block_cipher_mode::impl::get_provider(nullptr, providers_192,
                                                  PROVIDER_192_NUM);
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers_192,
                                                 PROVIDER_192_NUM);
}

const char* const* get_aes192_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_192_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers_192, PROVIDER_192_NUM);
        return names;
    }();
    return name_list.data();
}

const AES256Provider* get_aes256_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const AES256Provider* default_provider =
            block_cipher_mode::impl::get_provider(nullptr, providers_256,
                                                  PROVIDER_256_NUM);
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers_256,
                                                 PROVIDER_256_NUM);
}

const char* const* get_aes256_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_256_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers_256, PROVIDER_256_NUM);
        return names;
    }();
    return name_list.data();
}

} // namespace aes
