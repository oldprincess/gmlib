#ifndef GMLIB_BN_INC_H
#define GMLIB_BN_INC_H

#include <stddef.h>
#include <stdint.h>

/// @brief  r = a + b + carry
/// @param[out] r
/// @param[in] a 32
/// @param[in] b 32
/// @param[in] carry (1/0)
/// @return (1/0)
static inline int _add_carry(uint32_t* r, uint32_t a, uint32_t b, int carry)
{
    uint64_t tmp = (uint64_t)a + (uint64_t)b + carry;
    *r           = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief  r = 2a + carry
/// @param[out] r
/// @param[in] a 32
/// @param[in] carry (1/0)
/// @return (1/0)
static inline int _double_carry(uint32_t* r, uint32_t a, int carry)
{
    uint64_t tmp = (uint64_t)a * 2 + carry;
    *r           = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r = 3a + carry
/// @param[out] r
/// @param[in] a 32
/// @param[in] carry (2/1/0)
/// @return (2/1/0)
static inline int _triple_carry(uint32_t* r, uint32_t a, int carry)
{
    uint64_t tmp = (uint64_t)a * 3 + carry;
    *r           = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief  r = a - b + borrow
/// @param[out] r
/// @param[in] a 32
/// @param[in] b 32
/// @param[in] borrow (-1/0)
/// @return (-1/0)
static inline int _sub_borrow(uint32_t* r, uint32_t a, uint32_t b, int borrow)
{
    uint64_t tmp = (uint64_t)a - (uint64_t)b + borrow;
    *r           = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief  r = a * b + carry
/// @param[out] r
/// @param[in] a 32
/// @param[in] b 32
/// @param[in] carry
/// @return
static inline uint32_t _mul_carry(uint32_t* r,
                                  uint32_t  a,
                                  uint32_t  b,
                                  uint32_t  carry)
{
    uint64_t tmp = (uint64_t)a * (uint64_t)b + carry;
    *r           = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief  r = n * mulVal + addVal + carry
/// @param[out] r
/// @param[in] n
/// @param[in] mulVal
/// @param[in] addVal
/// @param[in] carry
/// @return
static inline uint32_t _mul_add_carry(uint32_t* r,
                                      uint32_t  n,
                                      uint32_t  mulVal,
                                      uint32_t  addVal,
                                      uint32_t  carry)
{
    uint64_t tmp = (uint64_t)n * (uint64_t)mulVal + addVal + carry;
    *r           = tmp & UINT32_MAX;
    return tmp >> 32;
}

#endif