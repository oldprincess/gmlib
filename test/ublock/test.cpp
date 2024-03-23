#include "test.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "speed.h"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        test_ublock_common();
        test_ublock_standard();
        test_ublock();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
        terminate();
    }
    cout << "test uBlock ok" << endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_ublock_common();
        speed_ublock_standard();
    }
    return 0;
}