#include "test.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "speed.h"

int main(int argc, char* argv[])
{
    try
    {
        test_sm9_field();
        test_sm9_sign();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test sm9 finish!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_sm9_sign();
    }
    return 0;
}