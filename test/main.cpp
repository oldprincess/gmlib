#include <iostream>
#include <gmlib/exception.h>
using namespace std;

void TestSm4Cipher();
void TestSm3Cipher();
void TestAesCipher();
void TestCipherMode();
void TestGcmMode();
void TestGHashCipher();
void TestUBlockCipher();
void TestHMacCipher();
void TestPBKDF2();
void TestSm2Cipher();
int  main()
{
    try
    {
        TestSm3Cipher();
        TestSm4Cipher();
        TestAesCipher();
        TestCipherMode();
        TestGHashCipher();
        TestGcmMode();
        TestUBlockCipher();
        TestHMacCipher();
        TestPBKDF2();
        TestSm2Cipher();
    }
    catch (gmlib::Exception& e)
    {
        cout << e.trace << endl;
        cout << e.what() << endl;
        std::exit(-1);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        std::exit(-1);
    }
    cout << "test finish!" << endl;
    return 0;
}