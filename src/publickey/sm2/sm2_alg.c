#include "sm2_alg.h"
#include <gmlib/err.h>
#include <gmlib/hash/sm3.h>

/// @brief 计算 Z = SM3(ENTL || ID || a || b || G.x || G.y || P.x || P.y)
int sm2_calculate_z(uint8_t* out,
                    uint8_t* ENTL,
                    uint8_t* ID,
                    ECPoint* P,
                    EC_CTX* ec_ctx) {
    // 计算标识符Z
    ECPoint* G = &ec_ctx->G;
    BINT *a = &ec_ctx->a, *b = &ec_ctx->b;
    uint8_t buffer[GMLIB_BINT_BITS / 8];     // BINT buffer
    int bsize = bint_bytes_len(&ec_ctx->p);  // 坐标字节串长度
    SM3_CTX sm3_ctx;
    sm3_init(&sm3_ctx);  // 初始化SM3函数

    sm3_update(ENTL, 2, &sm3_ctx);  // ENTL
    int ID_size = (ENTL[0] << 8 | ENTL[1]) / 8;
    sm3_update(ID, ID_size, &sm3_ctx);  // ID
    try_goto(bint_to_bytes(a, buffer, bsize, BINT_BIG_ENDIAN));
    sm3_update(buffer, bsize, &sm3_ctx);  // a
    try_goto(bint_to_bytes(b, buffer, bsize, BINT_BIG_ENDIAN));
    sm3_update(buffer, bsize, &sm3_ctx);  // b
    try_goto(bint_to_bytes(&G->x, buffer, bsize, BINT_BIG_ENDIAN));
    sm3_update(buffer, bsize, &sm3_ctx);  // G.x
    try_goto(bint_to_bytes(&G->y, buffer, bsize, BINT_BIG_ENDIAN));
    sm3_update(buffer, bsize, &sm3_ctx);  // G.y
    try_goto(bint_to_bytes(&P->x, buffer, bsize, BINT_BIG_ENDIAN));
    sm3_update(buffer, bsize, &sm3_ctx);  // P.x
    try_goto(bint_to_bytes(&P->y, buffer, bsize, BINT_BIG_ENDIAN));
    sm3_update(buffer, bsize, &sm3_ctx);  // P.y

    sm3_final(out, &sm3_ctx);  // 存储Z

    return ERR_NOERROR;
error:
    return ERR_RUNTIME_ERROR;
}
