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
        test_base64();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
        terminate();
    }
    cout << "test base64 ok" << endl;
    if (argc == 2 && std::strcmp(argv[1], "speed") == 0)
    {
        speed_base64();
    }
    return 0;
}