#include <gmlib/number/internal/mpz_common.h>

#include <cstring>

namespace number::internal::common {

/// @brief r = a + b + carry
/// @return (1/0)
static inline int _add_carry(std::uint32_t* r,
                             std::uint32_t  a,
                             std::uint32_t  b,
                             int            carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a + (std::uint64_t)b + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief  r = 2a + carry
/// @return (1/0)
static inline int _dbl_carry(std::uint32_t* r,
                             std::uint32_t  a,
                             int            carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a + (std::uint64_t)a + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r = 3a + carry
/// @return (2/1/0)
static inline int _tpl_carry(std::uint32_t* r,
                             std::uint32_t  a,
                             int            carry) noexcept
{
    std::uint64_t tmp =
        (std::uint64_t)a + (std::uint64_t)a + (std::uint64_t)a + carry;
    *r = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r = a - b + borrow
/// @return (-1/0)
static inline int _sub_borrow(std::uint32_t* r,
                              std::uint32_t  a,
                              std::uint32_t  b,
                              int            borrow) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a - (std::uint64_t)b + borrow;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r = a * b + carry
/// @return [0,2^32)
static inline std::uint32_t _mul_carry(std::uint32_t* r,
                                       std::uint32_t  a,
                                       std::uint32_t  b,
                                       std::uint32_t  carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)a * (std::uint64_t)b + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

/// @brief r += n * mul_val + carry
/// @return [0,2^32)
static inline std::uint32_t _add_mul_carry(std::uint32_t* r,
                                           std::uint32_t  n,
                                           std::uint32_t  mul_val,
                                           std::uint32_t  carry) noexcept
{
    std::uint64_t tmp = (std::uint64_t)n * (std::uint64_t)mul_val + *r + carry;
    *r                = tmp & UINT32_MAX;
    return tmp >> 32;
}

static inline std::uint32_t MEM_LOAD32BE(const void* src) noexcept
{
    return ((std::uint32_t)(((std::uint8_t*)src)[0]) << 24) |
           ((std::uint32_t)(((std::uint8_t*)src)[1]) << 16) |
           ((std::uint32_t)(((std::uint8_t*)src)[2]) << 8) |
           ((std::uint32_t)(((std::uint8_t*)src)[3]) << 0);
}

static inline void MEM_STORE32BE(void* dst, std::uint32_t a) noexcept
{
    ((std::uint8_t*)dst)[0] = ((std::uint32_t)a >> 24) & 0xFF;
    ((std::uint8_t*)dst)[1] = ((std::uint32_t)a >> 16) & 0xFF;
    ((std::uint8_t*)dst)[2] = ((std::uint32_t)a >> 8) & 0xFF;
    ((std::uint8_t*)dst)[3] = ((std::uint32_t)a >> 0) & 0xFF;
}

int mpz_add_carry(std::uint32_t*       r,
                  const std::uint32_t* a,
                  const std::uint32_t* b,
                  int                  carry,
                  std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return 0;

    for (std::size_t i = 0; i < limb_size; i++)
    {
        carry = _add_carry(&r[i], a[i], b[i], carry);
    }
    return carry;
}

int mpz_sub_borrow(std::uint32_t*       r,
                   const std::uint32_t* a,
                   const std::uint32_t* b,
                   int                  borrow,
                   std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return 0;

    for (std::size_t i = 0; i < limb_size; i++)
    {
        borrow = _sub_borrow(&r[i], a[i], b[i], borrow);
    }
    return borrow;
}

void mpz_mul(std::uint32_t*       r,
             const std::uint32_t* a,
             const std::uint32_t* b,
             std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return;

    {
        std::uint32_t carry = 0;
        for (std::size_t ia = 0; ia < limb_size; ia++)
        {
            carry = _mul_carry(&r[0 + ia], a[ia], b[0], carry);
        }
        r[0 + limb_size] = carry;
    }
    for (std::size_t ib = 1; ib < limb_size; ib++)
    {
        std::uint32_t carry = 0;
        for (std::size_t ia = 0; ia < limb_size; ia++)
        {
            carry = _add_mul_carry(&r[ib + ia], a[ia], b[ib], carry);
        }
        r[ib + limb_size] = carry;
    }
}

int mpz_cmp(const std::uint32_t* a,
            const std::uint32_t* b,
            std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return 0;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        std::size_t pos = limb_size - 1 - i;
        if (a[pos] > b[pos]) return 1;
        if (a[pos] < b[pos]) return -1;
    }
    return 0;
}

void mpz_cpy(std::uint32_t*       r,
             const std::uint32_t* a,
             std::size_t          limb_size) noexcept
{
    std::memmove(r, a, limb_size * sizeof(std::uint32_t));
}

void mpz_from_bytes(std::uint32_t*      r,
                    const std::uint8_t* src,
                    std::size_t         limb_size) noexcept
{
    if (limb_size == 0) return;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        r[limb_size - 1 - i] = MEM_LOAD32BE(src + 4 * i);
    }
}

void mpz_to_bytes(std::uint8_t*        r,
                  const std::uint32_t* src,
                  std::size_t          limb_size) noexcept
{
    if (limb_size == 0) return;
    for (std::size_t i = 0; i < limb_size; i++)
    {
        MEM_STORE32BE(r + 4 * i, src[limb_size - 1 - i]);
    }
}

}; // namespace number::internal::common