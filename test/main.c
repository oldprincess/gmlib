#include <gmlib/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test_math();
void test_bint();
void test_sm4();
void test_sm3();
void test_sm2();
void test_ec();

int main() {
    test_bint();
    test_sm4();
    test_math();
    test_sm3();
    test_ec();
    test_sm2();
    puts("test finish!");

    return 0;
}
