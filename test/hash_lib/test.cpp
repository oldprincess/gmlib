#include "test.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        test_hash();
        test_hmac();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "hash_lib test finish!" << std::endl;

    return 0;
}