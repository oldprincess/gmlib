#include "test.h"

#include <gmlib/ballet/provider.h>

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

struct BalletVariant
{
    MakeSuite     make_suite;
    ProviderNames provider_names;
    GetProvider   get_provider;
};

TestSuite make_ballet128128_test_suite()
{
    return {"Ballet-128-128",
            {"Ballet-128-128", 16, 16, 16},
            get_ballet128128_cipher_kats(),
            get_ballet128128_mode_kats(),
            {}};
}

TestSuite make_ballet128256_test_suite()
{
    return {"Ballet-128-256",
            {"Ballet-128-256", 16, 32, 32},
            get_ballet128256_cipher_kats(),
            get_ballet128256_mode_kats(),
            {}};
}

TestSuite make_ballet256256_test_suite()
{
    return {"Ballet-256-256",
            {"Ballet-256-256", 32, 32, 32},
            get_ballet256256_cipher_kats(),
            get_ballet256256_mode_kats(),
            {}};
}

const std::array<BalletVariant, 3>& ballet_variants()
{
    static const std::array<BalletVariant, 3> VARIANTS = {{
        {make_ballet128128_test_suite,
         ballet::get_ballet128128_supported_provider_names,
         ballet::get_ballet128128_provider},
        {make_ballet128256_test_suite,
         ballet::get_ballet128256_supported_provider_names,
         ballet::get_ballet128256_provider},
        {make_ballet256256_test_suite,
         ballet::get_ballet256256_supported_provider_names,
         ballet::get_ballet256256_provider},
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

void test_ballet_suites()
{
    for (const BalletVariant& variant : ballet_variants())
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

void speed_ballet()
{
    for (const BalletVariant& variant : ballet_variants())
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
        test_ballet_suites();
        std::cout << "test Ballet finish!" << std::endl;
        if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
        {
            speed_ballet();
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}
