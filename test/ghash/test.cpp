#include "test.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        test_ghash_common();
        test_ghash_lut256();
        test_ghash_pclmul();
        test_ghash();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test ghash finish!" << std::endl;
    return 0;
}