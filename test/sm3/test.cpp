#include "test.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "speed.h"

int main(int argc, char* argv[])
{
    try
    {
        test_sm3_common();
        test_sm3_yang15();
        test_sm3();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test sm3 finish!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_sm3_common();
        speed_sm3_yang15();
    }
    return 0;
}