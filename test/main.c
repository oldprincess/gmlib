#include <stdio.h>

void test_math();
void test_bint();
void test_sm4();
void test_sm3();
void test_sm2();
void test_ec();
void test_zuc();
int main() {
    test_bint();
    test_sm4();
    test_math();
    test_sm3();
    test_ec();
    test_sm2();
    test_zuc();
    puts("test finish!");

    return 0;
}
