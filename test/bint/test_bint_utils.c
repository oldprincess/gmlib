#include <gmlib/bint.h>
#include <gmlib/err.h>
#include <stdlib.h>
#include <string.h>

static char* x_bin =
    "10110101010111100001010101010101010101011001010111111111110000101";

void test_bint_utils() {
    BINT x;
    // load from bin
    try_goto(bint_from_str(&x, x_bin, 2));
    int bits_size = bint_bits_len(&x);
    if (bits_size != strlen(x_bin)) {
        ERR_LOG("Err in bint_from_str BIN");
        goto error;
    }
    // test bint_bits_at
    for (int i = 0; i < bits_size; i++) {
        int b = x_bin[bits_size - 1 - i] - '0';
        if (b != bint_bits_at(&x, i)) {
            ERR_LOG("Err in bint_bits_at");
            goto error;
        }
    }
    return;
error:
    exit(-1);
}
