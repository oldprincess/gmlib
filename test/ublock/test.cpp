#include "test.h"

#include <gmlib/ublock/provider.h>

#include <array>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace {

using block_cipher_mode::BlockCipherModeProvider;
using block_cipher_mode::test::TestSuite;
using ProviderNames = const char* const*           (*)() noexcept;
using GetProvider   = const BlockCipherModeProvider* (*)(const char*) noexcept;
using MakeSuite     = TestSuite                        (*)();

struct UBlockVariant
{
    MakeSuite     make_suite;
    ProviderNames provider_names;
    GetProvider   get_provider;
};

TestSuite make_ublock128128_test_suite()
{
    return {"uBlock-128-128",
            {"uBlock-128-128", 16, 16, 16},
            get_ublock128128_cipher_kats(),
            get_ublock128128_mode_kats(),
            {}};
}

TestSuite make_ublock128256_test_suite()
{
    return {"uBlock-128-256",
            {"uBlock-128-256", 16, 32, 32},
            get_ublock128256_cipher_kats(),
            get_ublock128256_mode_kats(),
            {}};
}

TestSuite make_ublock256256_test_suite()
{
    return {"uBlock-256-256",
            {"uBlock-256-256", 32, 32, 32},
            get_ublock256256_cipher_kats(),
            get_ublock256256_mode_kats(),
            {}};
}

const std::array<UBlockVariant, 3>& ublock_variants()
{
    static const std::array<UBlockVariant, 3> VARIANTS = {{
        {make_ublock128128_test_suite,
         ublock::get_ublock128128_supported_provider_names,
         ublock::get_ublock128128_provider},
        {make_ublock128256_test_suite,
         ublock::get_ublock128256_supported_provider_names,
         ublock::get_ublock128256_provider},
        {make_ublock256256_test_suite,
         ublock::get_ublock256256_supported_provider_names,
         ublock::get_ublock256256_provider},
    }};
    return VARIANTS;
}

void require_gcm_support(const TestSuite&               suite,
                         const BlockCipherModeProvider& provider,
                         bool                           expected)
{
    const bool has_encryptor = provider.create_gcm_encryptor != nullptr;
    const bool has_decryptor = provider.create_gcm_decryptor != nullptr;
    if (has_encryptor != expected || has_decryptor != expected)
    {
        throw std::runtime_error(suite.name + "/" + provider.algo_name +
                                 ": unexpected GCM support");
    }
}

void test_ublock_suites()
{
    for (const UBlockVariant& variant : ublock_variants())
    {
        const TestSuite suite = variant.make_suite();
        const auto      names = variant.provider_names();
        for (const char* const* name = names; *name != nullptr; ++name)
        {
            const auto* provider = variant.get_provider(*name);
            require_gcm_support(suite, *provider,
                                suite.cipher.block_size == 16);
            block_cipher_mode::test::run_test_suite(suite, provider);
        }
    }
}

void speed_ublock()
{
    for (const UBlockVariant& variant : ublock_variants())
    {
        const auto names = variant.provider_names();
        for (const char* const* name = names; *name != nullptr; ++name)
        {
            block_cipher_mode::test::run_speed_test(
                variant.get_provider(*name));
        }
    }
}

} // namespace

int main(int argc, char* argv[])
{
    try
    {
        test_ublock_suites();
        std::cout << "test uBlock finish!" << std::endl;
        if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
        {
            speed_ublock();
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}
