#include "test.h"

#include <iostream>

int main()
{
    try
    {
        test_ecb_mode();
        test_cbc_mode();
        test_cfb_mode();
        test_ofb_mode();
        test_ctr_mode();
        test_gcm_mode();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "block_cipher_mode test finish!" << std::endl;
    return 0;
}