#include "test.h"

#include <gmlib/sm4/provider.h>

#include <cstring>
#include <iostream>
#include <iterator>
#include <stdexcept>

block_cipher_mode::test::TestSuite make_sm4_test_suite()
{
    using ModeKatFactory = std::vector<block_cipher_mode::test::ModeKat> (*)();

    block_cipher_mode::test::TestSuite suite = {
        "SM4", {"SM4", 16, 16, 16}, get_sm4_cipher_kats(), {}, {},
    };

    for (ModeKatFactory factory :
         {get_sm4_ecb_kats, get_sm4_cbc_kats, get_sm4_cfb_kats,
          get_sm4_ofb_kats, get_sm4_ctr_kats})
    {
        auto kats = factory();
        suite.mode_kats.insert(suite.mode_kats.end(),
                               std::make_move_iterator(kats.begin()),
                               std::make_move_iterator(kats.end()));
    }
    return suite;
}

namespace {

void test_sm4_suite()
{
    const auto suite = make_sm4_test_suite();
    const auto names = sm4::get_sm4_supported_provider_names();
    for (const char* const* name = names; *name != nullptr; ++name)
    {
        const auto provider = sm4::get_sm4_provider(*name);
        block_cipher_mode::test::run_test_suite(suite, provider);
    }
}

void speed_sm4()
{
    const auto suite = make_sm4_test_suite();
    const auto names = sm4::get_sm4_supported_provider_names();
    for (const char* const* name = names; *name != nullptr; ++name)
    {
        const auto provider = sm4::get_sm4_provider(*name);
        block_cipher_mode::test::run_speed_test(provider);
    }
}

} // namespace

int main(int argc, char* argv[])
{
    try
    {
        test_sm4_suite();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test sm4 finish!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_sm4();
    }
    return 0;
}
