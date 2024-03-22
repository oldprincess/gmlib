#include "test.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "speed.h"

int main(int argc, char *argv[])
{
    try
    {
        test_sm4();
        test_sm4_ecb_mode();
        test_sm4_cbc_mode();
        test_sm4_cfb_mode();
        test_sm4_ofb_mode();
        test_sm4_ctr_mode();
        test_sm4_internal();
        test_sm4_lang18();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test sm4 finish!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_sm4_common();
        speed_sm4_lang18();
    }
    return 0;
}