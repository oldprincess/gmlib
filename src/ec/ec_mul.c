#include <gmlib/ec.h>
#include <gmlib/err.h>
#include <gmlib/math.h>
#include "ec_jacobian.h"

/// @brief 椭圆曲线多倍点(仿射坐标)
int ec_mul(ECPoint* r, BINT* k, ECPoint* n, EC_CTX* ec_ctx) {
    ECPoint f, result;
    ec_set_infinity(&result);
    ec_copy(&f, n);
    int bit_size = bint_bits_len(k);
    for (int ik = 0; ik < bit_size; ik++) {
        if (bint_bits_at(k, ik) == 1) {
            try_goto(ec_add(&result, &result, &f, ec_ctx));
        }
        try_goto(ec_add(&f, &f, &f, ec_ctx));
    }
    ec_copy(r, &result);

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
