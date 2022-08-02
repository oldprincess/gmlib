#include <gmlib/ec.h>

/// @brief EC Context 拷贝
void ec_ctx_copy(EC_CTX* r, EC_CTX* ctx) {
    bint_copy(&r->a, &ctx->a);
    bint_copy(&r->b, &ctx->b);
    bint_copy(&r->p, &ctx->p);
    bint_copy(&r->n, &ctx->n);
    ec_copy(&r->G, &ctx->G);
}

/// @brief EC Context 构造
void ec_ctx_construct(EC_CTX* r,
                      BINT* a,
                      BINT* b,
                      BINT* p,
                      ECPoint* G,
                      BINT* n) {
    bint_copy(&r->a, a);
    bint_copy(&r->b, b);
    bint_copy(&r->p, p);
    bint_copy(&r->n, n);
    ec_copy(&r->G, G);
}
