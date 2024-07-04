#ifndef GMLIB_SM2_H
#define GMLIB_SM2_H

#include <gmlib/api.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t gmlib_sm2_sm3_private_key_size();
void*  gmlib_sm2_sm3_private_key_new();
void*  gmlib_sm2_sm3_private_key_new_inplace();
int    gmlib_sm2_sm3_private_key_delete(void* ctx);
int    gmlib_sm2_sm3_private_key_delete_inplace(void* ctx);
int    gmlib_sm2_sm3_private_key_sign(void*          ctx,
                                      uint8_t*       sig,
                                      size_t*        outl,
                                      const uint8_t* msg,
                                      size_t         msg_len);

#ifdef __cplusplus
}
#endif

#endif