#include "test.h"

#include <gmlib/des/provider.h>

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace {

using block_cipher_mode::test::TestSuite;

TestSuite make_des_test_suite()
{
    return {"DES",
            {"DES", 8, 8, 8},
            get_des_cipher_kats(),
            get_des_mode_kats(),
            {}};
}

void test_des_suite()
{
    const TestSuite suite = make_des_test_suite();
    const auto      names = des::get_des_supported_provider_names();
    for (const char* const* name = names; *name != nullptr; ++name)
    {
        const auto* provider = des::get_des_provider(*name);
        if (provider->create_gcm_encryptor != nullptr ||
            provider->create_gcm_decryptor != nullptr)
        {
            throw std::runtime_error(suite.name + "/" + provider->algo_name +
                                     ": unexpected GCM support");
        }
        block_cipher_mode::test::run_test_suite(suite, provider);
    }
}

void speed_des()
{
    const auto names = des::get_des_supported_provider_names();
    for (const char* const* name = names; *name != nullptr; ++name)
    {
        block_cipher_mode::test::run_speed_test(des::get_des_provider(*name));
    }
}

} // namespace

int main(int argc, char* argv[])
{
    try
    {
        test_des_suite();
        std::cout << "test DES finish!" << std::endl;
        if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
        {
            speed_des();
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}
