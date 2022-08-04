#include <gmlib/bint.h>
#include <gmlib/err.h>
#include <stdio.h>

int main() {
    BINT x;
    bint_from_str(&x, "a1234", 10);
    //    printf("%s\n", bint_fast_to_str(&x, 10));
    return 0;
}
