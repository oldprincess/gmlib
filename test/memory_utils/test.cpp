#include "test.h"

#include <cstring>
#include <exception>
#include <iostream>

#include "speed.h"

int main(int argc, char *argv[])
{
    try
    {
        test_endian();
        test_memxor();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test memory_utils ok!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_memxor();
    }
    return 0;
}
