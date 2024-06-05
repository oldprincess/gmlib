#ifndef NUMBER_INTERNAL_BN_COMMON_H
#define NUMBER_INTERNAL_BN_COMMON_H

#include <cstddef>
#include <cstdint>
#include <memory_resource>

namespace number::internal::common {

typedef struct BigNum_st
{
    std::uint32_t* data;      //
    std::size_t    data_len;  //
    std::size_t    MAX_DSIZE; //
    int            sign;      // (1/0/-1)
} BigNum_st;

int bn_alloc(
    BigNum_st**                n,
    std::size_t                bits,
    std::pmr::memory_resource* mp = std::pmr::get_default_resource()) noexcept;

void bn_free(
    BigNum_st*                 n,
    std::pmr::memory_resource* mp = std::pmr::get_default_resource()) noexcept;

int bn_add(BigNum_st* r, const BigNum_st* a, const BigNum_st* b) noexcept;

int bn_sub(BigNum_st* r, const BigNum_st* a, const BigNum_st* b) noexcept;

int bn_mul(BigNum_st* r, const BigNum_st* a, const BigNum_st* b) noexcept;

int bn_div(
    BigNum_st*                 r,
    const BigNum_st*           a,
    const BigNum_st*           b,
    std::pmr::memory_resource* mp = std::pmr::get_default_resource()) noexcept;

int bn_mod(
    BigNum_st*                 r,
    const BigNum_st*           a,
    const BigNum_st*           b,
    std::pmr::memory_resource* mp = std::pmr::get_default_resource()) noexcept;

int bn_divmod(BigNum_st*                 q,
              BigNum_st*                 r,
              const BigNum_st*           a,
              const BigNum_st*           b,
              std::pmr::memory_resource* mp = std::pmr::get_default_resource()) noexcept;

int bn_umul32_uadd32(BigNum_st*       r,
                     const BigNum_st* a,
                     std::uint32_t    mul_val,
                     std::uint32_t    add_val) noexcept;
int bn_udivmod32(BigNum_st*       q,
                 std::uint32_t*   r,
                 const BigNum_st* a,
                 std::uint32_t    b) noexcept;
int bn_ucmp(const BigNum_st* a, const BigNum_st* b) noexcept;
int bn_ucmp_zero(const BigNum_st* a) noexcept;

int bn_from_str(BigNum_st* r, const char* s, int radix) noexcept;

int bn_to_str(char*                      s,
              const BigNum_st*           a,
              int                        radix,
              std::pmr::memory_resource* mp = std::pmr::get_default_resource()) noexcept;

int bn_from_bytes(BigNum_st*     r,
                  const uint8_t* bytes,
                  std::size_t    bytes_len,
                  int            is_big_endian) noexcept;

int bn_to_bytes(uint8_t*         bytes,
                std::size_t      bytes_len,
                const BigNum_st* a,
                int              is_big_endian) noexcept;

int bn_from_u32(BigNum_st* r, std::uint32_t a) noexcept;

int bn_cmp(const BigNum_st* a, const BigNum_st* b) noexcept;

int bn_cmp_zero(const BigNum_st* a) noexcept;

int bn_cmp_u32(const BigNum_st* a, std::uint32_t b) noexcept;

int bn_test(const BigNum_st* a, std::size_t i) noexcept;

void bn_set_zero(BigNum_st* a) noexcept;

int bn_cpy(BigNum_st* r, const BigNum_st* a) noexcept;

std::size_t bn_bits_length(const BigNum_st* a) noexcept;

} // namespace number::internal::common

#endif