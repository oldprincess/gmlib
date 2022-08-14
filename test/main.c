#include <gmlib/err.h>
#include <stdio.h>
void test_math();
void test_bint();
void test_sm4();
void test_aes();
void test_sm3();
void test_sm2();
void test_ec();
void test_zuc();
void test_mode_ecb();
void test_mode_cbc();
void test_mode_gcm();
int main() {
    test_bint();
    test_sm4();
    test_aes();
    test_mode_ecb();
    test_mode_cbc();
    test_mode_gcm();
    test_math();
    test_sm3();
    test_ec();
    test_sm2();
    test_zuc();

    puts("test finish!");

    return 0;
}
