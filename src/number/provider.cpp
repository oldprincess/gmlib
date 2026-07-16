#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/number/provider.h>

#include <cstring>

#if defined(SUPPORT_NUMBER_X64)
#include "mont256_x64.h"
#include "mpz_x64.h"
#include "uint256_x64.h"
#endif

#include "mont256_common.h"
#include "mpz_common.h"
#include "uint256_common.h"

namespace number {

struct Provider
{
    bool           (*available)() noexcept;
    NumberProvider fns;
};

static const Provider number_providers[] = {

// ****************************************************
// ***************** X64 ****************************
// ****************************************************

#if defined(SUPPORT_NUMBER_X64)
    {
        []() noexcept {
            static const bool available =
                cpuinfo::x86_64::cpu_supports_bmi2() &&
                cpuinfo::x86_64::cpu_supports_movbe();
            return available;
        },
        {
            "x64",
            reinterpret_cast<decltype(NumberProvider::uint256_add_carry)>(
                internal::x64::uint256_add_carry),
            reinterpret_cast<decltype(NumberProvider::uint256_sub_borrow)>(
                internal::x64::uint256_sub_borrow),
            reinterpret_cast<decltype(NumberProvider::uint256_dbl_carry)>(
                internal::x64::uint256_dbl_carry),
            reinterpret_cast<decltype(NumberProvider::uint256_tpl_carry)>(
                internal::x64::uint256_tpl_carry),
            reinterpret_cast<decltype(NumberProvider::uint256_mul)>(
                internal::x64::uint256_mul),
            reinterpret_cast<decltype(NumberProvider::uint256_sqr)>(
                internal::x64::uint256_sqr),
            reinterpret_cast<
                decltype(NumberProvider::uint256_add_carry_uint32)>(
                internal::x64::uint256_add_carry_uint32),
            reinterpret_cast<
                decltype(NumberProvider::uint256_add_carry_uint64)>(
                internal::x64::uint256_add_carry_uint64),
            reinterpret_cast<
                decltype(NumberProvider::uint256_sub_borrow_uint32)>(
                internal::x64::uint256_sub_borrow_uint32),
            reinterpret_cast<
                decltype(NumberProvider::uint256_sub_borrow_uint64)>(
                internal::x64::uint256_sub_borrow_uint64),
            reinterpret_cast<
                decltype(NumberProvider::uint256_mul_carry_uint32)>(
                internal::x64::uint256_mul_carry_uint32),
            reinterpret_cast<
                decltype(NumberProvider::uint256_mul_carry_uint64)>(
                internal::x64::uint256_mul_carry_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_div_uint32)>(
                internal::x64::uint256_div_uint32),
            reinterpret_cast<decltype(NumberProvider::uint256_div_uint64)>(
                internal::x64::uint256_div_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_mod_add)>(
                internal::x64::uint256_mod_add),
            reinterpret_cast<decltype(NumberProvider::uint256_mod_sub)>(
                internal::x64::uint256_mod_sub),
            reinterpret_cast<decltype(NumberProvider::uint256_mod)>(
                internal::x64::uint256_mod),
            reinterpret_cast<decltype(NumberProvider::uint256_cmp)>(
                internal::x64::uint256_cmp),
            reinterpret_cast<decltype(NumberProvider::uint256_cmp_uint32)>(
                internal::x64::uint256_cmp_uint32),
            reinterpret_cast<decltype(NumberProvider::uint256_cmp_uint64)>(
                internal::x64::uint256_cmp_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_equal)>(
                internal::x64::uint256_equal),
            reinterpret_cast<decltype(NumberProvider::uint256_equal_zero)>(
                internal::x64::uint256_equal_zero),
            reinterpret_cast<decltype(NumberProvider::uint256_equal_one)>(
                internal::x64::uint256_equal_one),
            reinterpret_cast<decltype(NumberProvider::uint256_cpy)>(
                internal::x64::uint256_cpy),
            reinterpret_cast<decltype(NumberProvider::uint256_set_zero)>(
                internal::x64::uint256_set_zero),
            reinterpret_cast<decltype(NumberProvider::uint256_set_one)>(
                internal::x64::uint256_set_one),
            reinterpret_cast<decltype(NumberProvider::uint256_set_uint32)>(
                internal::x64::uint256_set_uint32),
            reinterpret_cast<decltype(NumberProvider::uint256_set_uint64)>(
                internal::x64::uint256_set_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_from_bytes)>(
                internal::x64::uint256_from_bytes),
            reinterpret_cast<decltype(NumberProvider::uint256_to_bytes)>(
                internal::x64::uint256_to_bytes),
            reinterpret_cast<decltype(NumberProvider::uint256_bittest)>(
                internal::x64::uint256_bittest),

            reinterpret_cast<decltype(NumberProvider::mont256_add)>(
                internal::x64::mont256_add),
            reinterpret_cast<decltype(NumberProvider::mont256_sub)>(
                internal::x64::mont256_sub),
            reinterpret_cast<decltype(NumberProvider::mont256_dbl)>(
                internal::x64::mont256_dbl),
            reinterpret_cast<decltype(NumberProvider::mont256_tpl)>(
                internal::x64::mont256_tpl),
            reinterpret_cast<decltype(NumberProvider::mont256_neg)>(
                internal::x64::mont256_neg),
            reinterpret_cast<decltype(NumberProvider::mont256_mul)>(
                internal::x64::mont256_mul),
            reinterpret_cast<decltype(NumberProvider::mont256_sqr)>(
                internal::x64::mont256_sqr),
            reinterpret_cast<decltype(NumberProvider::mont256_pow)>(
                internal::x64::mont256_pow),
            reinterpret_cast<decltype(NumberProvider::mont256_div2)>(
                internal::x64::mont256_div2),
            reinterpret_cast<decltype(NumberProvider::mont256_inv)>(
                internal::x64::mont256_inv),
            reinterpret_cast<decltype(NumberProvider::mont256_equal)>(
                internal::x64::mont256_equal),
            reinterpret_cast<decltype(NumberProvider::mont256_equal_zero)>(
                internal::x64::mont256_equal_zero),
            reinterpret_cast<decltype(NumberProvider::mont256_equal_one)>(
                internal::x64::mont256_equal_one),
            reinterpret_cast<decltype(NumberProvider::mont256_cpy)>(
                internal::x64::mont256_cpy),
            reinterpret_cast<decltype(NumberProvider::mont256_set_zero)>(
                internal::x64::mont256_set_zero),
            reinterpret_cast<decltype(NumberProvider::mont256_set_one)>(
                internal::x64::mont256_set_one),
            reinterpret_cast<decltype(NumberProvider::mont256_set_uint32)>(
                internal::x64::mont256_set_uint32),
            reinterpret_cast<decltype(NumberProvider::mont256_set_uint64)>(
                internal::x64::mont256_set_uint64),
            reinterpret_cast<decltype(NumberProvider::mont256_from_bytes)>(
                internal::x64::mont256_from_bytes),
            reinterpret_cast<decltype(NumberProvider::mont256_to_bytes)>(
                internal::x64::mont256_to_bytes),
            reinterpret_cast<decltype(NumberProvider::mont256_from_bytes_ex)>(
                internal::x64::mont256_from_bytes_ex),

            reinterpret_cast<decltype(NumberProvider::mpz_add_carry)>(
                internal::x64::mpz_add_carry),
            reinterpret_cast<decltype(NumberProvider::mpz_sub_borrow)>(
                internal::x64::mpz_sub_borrow),
            reinterpret_cast<decltype(NumberProvider::mpz_mul)>(
                internal::x64::mpz_mul),
            reinterpret_cast<decltype(NumberProvider::mpz_cmp)>(
                internal::x64::mpz_cmp),
            reinterpret_cast<decltype(NumberProvider::mpz_cpy)>(
                internal::x64::mpz_cpy),
            reinterpret_cast<decltype(NumberProvider::mpz_from_bytes)>(
                internal::x64::mpz_from_bytes),
            reinterpret_cast<decltype(NumberProvider::mpz_to_bytes)>(
                internal::x64::mpz_to_bytes),
        },
    },
#endif

    // ****************************************************
    // ***************** COMMON ***************************
    // ****************************************************

    {
        []() noexcept { return true; },
        {
            "common",
            reinterpret_cast<decltype(NumberProvider::uint256_add_carry)>(
                internal::common::uint256_add_carry),
            reinterpret_cast<decltype(NumberProvider::uint256_sub_borrow)>(
                internal::common::uint256_sub_borrow),
            reinterpret_cast<decltype(NumberProvider::uint256_dbl_carry)>(
                internal::common::uint256_dbl_carry),
            reinterpret_cast<decltype(NumberProvider::uint256_tpl_carry)>(
                internal::common::uint256_tpl_carry),
            reinterpret_cast<decltype(NumberProvider::uint256_mul)>(
                internal::common::uint256_mul),
            reinterpret_cast<decltype(NumberProvider::uint256_sqr)>(
                internal::common::uint256_sqr),
            reinterpret_cast<
                decltype(NumberProvider::uint256_add_carry_uint32)>(
                internal::common::uint256_add_carry_uint32),
            reinterpret_cast<
                decltype(NumberProvider::uint256_add_carry_uint64)>(
                internal::common::uint256_add_carry_uint64),
            reinterpret_cast<
                decltype(NumberProvider::uint256_sub_borrow_uint32)>(
                internal::common::uint256_sub_borrow_uint32),
            reinterpret_cast<
                decltype(NumberProvider::uint256_sub_borrow_uint64)>(
                internal::common::uint256_sub_borrow_uint64),
            reinterpret_cast<
                decltype(NumberProvider::uint256_mul_carry_uint32)>(
                internal::common::uint256_mul_carry_uint32),
            reinterpret_cast<
                decltype(NumberProvider::uint256_mul_carry_uint64)>(
                internal::common::uint256_mul_carry_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_div_uint32)>(
                internal::common::uint256_div_uint32),
            reinterpret_cast<decltype(NumberProvider::uint256_div_uint64)>(
                internal::common::uint256_div_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_mod_add)>(
                internal::common::uint256_mod_add),
            reinterpret_cast<decltype(NumberProvider::uint256_mod_sub)>(
                internal::common::uint256_mod_sub),
            reinterpret_cast<decltype(NumberProvider::uint256_mod)>(
                internal::common::uint256_mod),
            reinterpret_cast<decltype(NumberProvider::uint256_cmp)>(
                internal::common::uint256_cmp),
            reinterpret_cast<decltype(NumberProvider::uint256_cmp_uint32)>(
                internal::common::uint256_cmp_uint32),
            reinterpret_cast<decltype(NumberProvider::uint256_cmp_uint64)>(
                internal::common::uint256_cmp_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_equal)>(
                internal::common::uint256_equal),
            reinterpret_cast<decltype(NumberProvider::uint256_equal_zero)>(
                internal::common::uint256_equal_zero),
            reinterpret_cast<decltype(NumberProvider::uint256_equal_one)>(
                internal::common::uint256_equal_one),
            reinterpret_cast<decltype(NumberProvider::uint256_cpy)>(
                internal::common::uint256_cpy),
            reinterpret_cast<decltype(NumberProvider::uint256_set_zero)>(
                internal::common::uint256_set_zero),
            reinterpret_cast<decltype(NumberProvider::uint256_set_one)>(
                internal::common::uint256_set_one),
            reinterpret_cast<decltype(NumberProvider::uint256_set_uint32)>(
                internal::common::uint256_set_uint32),
            reinterpret_cast<decltype(NumberProvider::uint256_set_uint64)>(
                internal::common::uint256_set_uint64),
            reinterpret_cast<decltype(NumberProvider::uint256_from_bytes)>(
                internal::common::uint256_from_bytes),
            reinterpret_cast<decltype(NumberProvider::uint256_to_bytes)>(
                internal::common::uint256_to_bytes),
            reinterpret_cast<decltype(NumberProvider::uint256_bittest)>(
                internal::common::uint256_bittest),

            reinterpret_cast<decltype(NumberProvider::mont256_add)>(
                internal::common::mont256_add),
            reinterpret_cast<decltype(NumberProvider::mont256_sub)>(
                internal::common::mont256_sub),
            reinterpret_cast<decltype(NumberProvider::mont256_dbl)>(
                internal::common::mont256_dbl),
            reinterpret_cast<decltype(NumberProvider::mont256_tpl)>(
                internal::common::mont256_tpl),
            reinterpret_cast<decltype(NumberProvider::mont256_neg)>(
                internal::common::mont256_neg),
            reinterpret_cast<decltype(NumberProvider::mont256_mul)>(
                internal::common::mont256_mul),
            reinterpret_cast<decltype(NumberProvider::mont256_sqr)>(
                internal::common::mont256_sqr),
            reinterpret_cast<decltype(NumberProvider::mont256_pow)>(
                internal::common::mont256_pow),
            reinterpret_cast<decltype(NumberProvider::mont256_div2)>(
                internal::common::mont256_div2),
            reinterpret_cast<decltype(NumberProvider::mont256_inv)>(
                internal::common::mont256_inv),
            reinterpret_cast<decltype(NumberProvider::mont256_equal)>(
                internal::common::mont256_equal),
            reinterpret_cast<decltype(NumberProvider::mont256_equal_zero)>(
                internal::common::mont256_equal_zero),
            reinterpret_cast<decltype(NumberProvider::mont256_equal_one)>(
                internal::common::mont256_equal_one),
            reinterpret_cast<decltype(NumberProvider::mont256_cpy)>(
                internal::common::mont256_cpy),
            reinterpret_cast<decltype(NumberProvider::mont256_set_zero)>(
                internal::common::mont256_set_zero),
            reinterpret_cast<decltype(NumberProvider::mont256_set_one)>(
                internal::common::mont256_set_one),
            reinterpret_cast<decltype(NumberProvider::mont256_set_uint32)>(
                internal::common::mont256_set_uint32),
            reinterpret_cast<decltype(NumberProvider::mont256_set_uint64)>(
                internal::common::mont256_set_uint64),
            reinterpret_cast<decltype(NumberProvider::mont256_from_bytes)>(
                internal::common::mont256_from_bytes),
            reinterpret_cast<decltype(NumberProvider::mont256_to_bytes)>(
                internal::common::mont256_to_bytes),
            reinterpret_cast<decltype(NumberProvider::mont256_from_bytes_ex)>(
                internal::common::mont256_from_bytes_ex),

            reinterpret_cast<decltype(NumberProvider::mpz_add_carry)>(
                internal::common::mpz_add_carry),
            reinterpret_cast<decltype(NumberProvider::mpz_sub_borrow)>(
                internal::common::mpz_sub_borrow),
            reinterpret_cast<decltype(NumberProvider::mpz_mul)>(
                internal::common::mpz_mul),
            reinterpret_cast<decltype(NumberProvider::mpz_cmp)>(
                internal::common::mpz_cmp),
            reinterpret_cast<decltype(NumberProvider::mpz_cpy)>(
                internal::common::mpz_cpy),
            reinterpret_cast<decltype(NumberProvider::mpz_from_bytes)>(
                internal::common::mpz_from_bytes),
            reinterpret_cast<decltype(NumberProvider::mpz_to_bytes)>(
                internal::common::mpz_to_bytes),
        },
    },
};

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept
{
    return N;
}

struct ProviderNameList
{
    const char* names[array_size(number_providers) + 1];
};

const NumberProvider* get_number_provider(const char* name) noexcept
{
    if (name == nullptr)
    {
        static const NumberProvider* default_provider = []() {
            for (const Provider& provider : number_providers)
            {
                if (provider.available())
                {
                    return &provider.fns;
                }
            }
            // unreachable
            return static_cast<const NumberProvider*>(nullptr);
        }();
        return default_provider;
    }
    else
    {
        for (const Provider& provider : number_providers)
        {
            if (provider.available() &&
                std::strcmp(provider.fns.algo_name, name) == 0)
            {
                return &provider.fns;
            }
        }
        return nullptr;
    }
}

const char* const* get_number_supported_provider_names() noexcept
{
    static const auto provider_name_list = []() {
        ProviderNameList list;
        int              idx = 0;
        for (const Provider& provider : number_providers)
        {
            if (provider.available())
            {
                list.names[idx++] = provider.fns.algo_name;
            }
        }
        list.names[idx] = nullptr;
        return list;
    }();
    return provider_name_list.names;
}

} // namespace number
