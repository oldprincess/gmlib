#include <gmlib/ec.h>
#include <gmlib/err.h>
#include <stdlib.h>

void test_ec_utils() {
    ECPoint d;
    try_goto(ec_mul(&d, &BINT_ONE, &EC_Fp192_CTX.G, &EC_Fp192_CTX));
    // [n]G = O
    try_goto(ec_mul(&d, &EC_Fp192_CTX.n, &EC_Fp192_CTX.G, &EC_Fp192_CTX));
    if (!ec_is_infinity(&d)) {
        ERR_LOG("Err in ec_mul");
        goto error;
    }
    try_goto(ec_mul(&d, &EC_Fp256_CTX.n, &EC_Fp256_CTX.G, &EC_Fp256_CTX));
    if (!ec_is_infinity(&d)) {
        ERR_LOG("Err in ec_mul");
        goto error;
    }
    // -G
    try_goto(ec_neg(&d, &EC_Fp256_CTX.G, &EC_Fp256_CTX));
    if (ec_neg_equal(&d, &EC_Fp256_CTX.G) != 1) {
        ERR_LOG("Err in ec_neg_equal");
        goto error;
    }
    // G + -G = O
    try_goto(ec_add(&d, &d, &EC_Fp256_CTX.G, &EC_Fp256_CTX));
    if (!ec_is_infinity(&d)) {
        ERR_LOG("Err in ec_add");
        goto error;
    }
    // G + O = G
    try_goto(ec_add(&d, &EC_Fp256_CTX.G, &d, &EC_Fp256_CTX));
    if (!ec_equal(&d, &EC_Fp256_CTX.G)) {
        ERR_LOG("Err in ec_add");
        goto error;
    }
    // O + G = G
    ec_set_infinity(&d);
    try_goto(ec_add(&d, &d, &EC_Fp256_CTX.G, &EC_Fp256_CTX));
    if (!ec_equal(&d, &EC_Fp256_CTX.G)) {
        ERR_LOG("Err in ec_add");
        goto error;
    }
    // bytes
    static uint8_t buffer[(GMLIB_BINT_BITS / 8) * 2 + 2];
    int bsize = 0;
    try_goto(ec_to_bytes(&EC_Fp192_CTX.G, 4, buffer, &bsize, &EC_Fp192_CTX));
    try_goto(ec_from_bytes(&d, buffer, &EC_Fp192_CTX));
    if (!ec_equal(&d, &EC_Fp192_CTX.G)) {
        ERR_LOG("Err in ec_to_bytes / ec_from_bytes");
        goto error;
    }

    try_goto(ec_to_bytes(&EC_Fp256_CTX.G, 4, buffer, &bsize, &EC_Fp256_CTX));
    try_goto(ec_from_bytes(&d, buffer, &EC_Fp256_CTX));
    if (!ec_equal(&d, &EC_Fp256_CTX.G)) {
        ERR_LOG("Err in ec_to_bytes / ec_from_bytes");
        goto error;
    }

    return;
error:
    exit(-1);
}
