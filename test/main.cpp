#include <iostream>
using namespace std;

void TestSm4Cipher();
void TestSm3Cipher();
void TestAesCipher();
void TestCipherMode();
void TestGcmMode();
void TestGMacCipher();
int  main()
{
    TestSm3Cipher();
    TestSm4Cipher();
    TestAesCipher();
    TestCipherMode();
    TestGMacCipher();
    TestGcmMode();
    cout << "test finish!" << endl;
    return 0;
}