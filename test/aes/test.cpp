#include "test.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "speed.h"

int main(int argc, char* argv[])
{
    try
    {
        test_aes_lut();
        test_aes_aesni();
        test_aes();
        test_aes_mode();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    std::cout << "test aes finish!" << std::endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_aes_lut();
        speed_aes_aesni();
    }
    return 0;
}