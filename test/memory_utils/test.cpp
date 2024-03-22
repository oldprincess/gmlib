#include "test.h"

#include <exception>
#include <iostream>

int main()
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
    return 0;
}