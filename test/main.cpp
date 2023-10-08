#include <iostream>
using namespace std;

void TestSm4Cipher();
void TestSm3Cipher();
void TestAesCipher();
void TestCipherMode();
void TestGcmMode();
void TestGHashCipher();
int  main()
{
    TestSm3Cipher();
    TestSm4Cipher();
    TestAesCipher();
    TestCipherMode();
    TestGHashCipher();
    TestGcmMode();
    cout << "test finish!" << endl;
    return 0;
}