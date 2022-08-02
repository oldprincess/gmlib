#include <gmlib/ec.h>
#include <gmlib/err.h>
#include <memory.h>

/// @brief 椭圆曲线点构造
void ec_construct(ECPoint* r, BINT* x, BINT* y) {
    bint_copy(&r->x, x);
    bint_copy(&r->y, y);
    r->infinity = 0;
}

/// @brief 椭圆曲线点转字节串
int ec_to_bytes(ECPoint* n, int PC, uint8_t* b, int* bsize, EC_CTX* ec_ctx) {
    int size = bint_bytes_len(&ec_ctx->p);
    if (ec_is_infinity(n)) {
        ERR_LOG("Infinity point can't cast to bytes");
        goto error;
    }
    if (PC == 4) {
        b[0] = PC;
        uint8_t *x_mem = b + 1, *y_mem = b + 1 + size;
        try_goto(bint_to_bytes(&n->x, x_mem, size, BINT_BIG_ENDIAN));
        try_goto(bint_to_bytes(&n->y, y_mem, size, BINT_BIG_ENDIAN));
        *bsize = 1 + 2 * size;
    } else {
        ERR_LOG("Unsupported ECPoint conversion type");
        goto error;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}

/// @brief 字节串转椭圆曲线点
int ec_from_bytes(ECPoint* n, uint8_t* b, EC_CTX* ec_ctx) {
    int size = bint_bytes_len(&ec_ctx->p);
    int PC = b[0];
    if (PC == 4) {
        uint8_t *x_mem = b + 1, *y_mem = b + 1 + size;
        try_goto(bint_from_bytes(&n->x, x_mem, size, BINT_BIG_ENDIAN));
        try_goto(bint_from_bytes(&n->y, y_mem, size, BINT_BIG_ENDIAN));
        n->infinity = 0;
    } else {
        ERR_LOG("Unsupported ECPoint conversion type");
        goto error;
    }
    // 校验点是否在曲线上
    int status = 0;
    try_goto(ec_check(n, &status, ec_ctx));
    if (status != 1) {
        ERR_LOG("ECPoint verification failed");
        goto error;
    }

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
