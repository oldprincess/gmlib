#include <gmlib/sm4/provider.h>

#include <array>

#include "provider_sm4_common.h"
#if defined(SUPPORT_SM4_GONG23)
#include "provider_sm4_gong23.h"
#endif
#if defined(SUPPORT_SM4_LANG18_AVX2)
#include "provider_sm4_lang18_avx2.h"
#endif
#if defined(SUPPORT_SM4_SM4NI)
#include "provider_sm4_sm4ni.h"
#endif
#if defined(SUPPORT_SM4_LANG18)
#include "provider_sm4_lang18.h"
#endif

namespace sm4 {
namespace {

using block_cipher_mode::impl::BlockCipherModeProviderEntry;

static const BlockCipherModeProviderEntry* const providers[] = {
#if defined(SUPPORT_SM4_GONG23)
    &internal::gong23::provider,
#endif
#if defined(SUPPORT_SM4_LANG18_AVX2)
    &internal::lang18_avx2::provider,
#endif
#if defined(SUPPORT_SM4_LANG18)
    &internal::lang18::provider,
#endif
#if defined(SUPPORT_SM4_SM4NI)
    &internal::sm4ni::provider,
#endif
    &internal::common::provider,
};

constexpr std::size_t PROVIDER_NUM = std::size(providers);

} // namespace

const SM4Provider* get_sm4_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const SM4Provider* default_provider =
            block_cipher_mode::impl::get_provider( //
                nullptr, providers, PROVIDER_NUM   //
            );                                     //
        return default_provider;
    }
    return block_cipher_mode::impl::get_provider(name, providers, PROVIDER_NUM);
}

const char* const* get_sm4_supported_provider_names() noexcept
{
    static const auto name_list = []() {
        std::array<const char*, PROVIDER_NUM + 1> names;
        block_cipher_mode::impl::get_supported_provider_names(
            names.data(), providers, PROVIDER_NUM);
        return names;
    }();
    return name_list.data();
}

} // namespace sm4
