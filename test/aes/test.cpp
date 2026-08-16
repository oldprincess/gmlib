#include "test.h"

#include <gmlib/aes/provider.h>

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

struct AesVariant
{
    MakeSuite     make_suite;
    ProviderNames provider_names;
    GetProvider   get_provider;
};

TestSuite make_aes128_test_suite()
{
    return {"AES128",
            {"AES128", 16, 16, 16},
            get_aes128_cipher_kats(),
            get_aes128_mode_kats(),
            get_aes128_aead_kats()};
}

TestSuite make_aes192_test_suite()
{
    return {"AES192",
            {"AES192", 16, 24, 24},
            get_aes192_cipher_kats(),
            get_aes192_mode_kats(),
            get_aes192_aead_kats()};
}

TestSuite make_aes256_test_suite()
{
    return {"AES256",
            {"AES256", 16, 32, 32},
            get_aes256_cipher_kats(),
            get_aes256_mode_kats(),
            get_aes256_aead_kats()};
}

const std::array<AesVariant, 3>& aes_variants()
{
    static const std::array<AesVariant, 3> VARIANTS = {{
        {make_aes128_test_suite, aes::get_aes128_supported_provider_names,
         aes::get_aes128_provider},
        {make_aes192_test_suite, aes::get_aes192_supported_provider_names,
         aes::get_aes192_provider},
        {make_aes256_test_suite, aes::get_aes256_supported_provider_names,
         aes::get_aes256_provider},
    }};
    return VARIANTS;
}

void test_aes_suites()
{
    for (const AesVariant& variant : aes_variants())
    {
        const TestSuite suite = variant.make_suite();
        const auto      names = variant.provider_names();
        for (const char* const* name = names; *name != nullptr; ++name)
        {
            block_cipher_mode::test::run_test_suite(
                suite, variant.get_provider(*name));
        }
    }
}

void speed_aes()
{
    for (const AesVariant& variant : aes_variants())
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
        test_aes_suites();
        std::cout << "test aes finish!" << std::endl;
        if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
        {
            speed_aes();
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}
