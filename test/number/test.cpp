#include "test.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "speed.h"

int main(int argc, char* argv[])
{
    try
    {
        test_uint256_common();
        test_mont256_common();
        test_mpz_common();
        test_uint256_x64();
        test_mont256_x64();
        test_mpz_x64();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test number finish!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_uint256_common();
        speed_mont256_common();
        speed_uint256_x64();
        speed_mont256_x64();
    }
    return 0;
}