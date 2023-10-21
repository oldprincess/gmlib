#include <iostream>
using namespace std;

void TestSm4Cipher();
void TestSm3Cipher();
void TestAesCipher();
void TestCipherMode();
void TestGcmMode();
void TestGHashCipher();
void TestUBlockCipher_Standard();
int  main()
{
    TestSm3Cipher();
    TestSm4Cipher();
    TestAesCipher();
    TestCipherMode();
    TestGHashCipher();
    TestGcmMode();
    TestUBlockCipher_Standard();
    cout << "test finish!" << endl;
    return 0;
}