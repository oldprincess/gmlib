#include "test.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "speed.h"

int main(int argc, char* argv[])
{
    try
    {
        test_sm2p256v1();
        test_sm2_sign();
        test_sm2_cipher();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test sm2 finish!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_sm2_sign();
        speed_sm2_cipher();
    }
    return 0;
}