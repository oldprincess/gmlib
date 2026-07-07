#include <gmlib/sm2/internal/sm2p256v1_provider.h>

#include <cstring>

#include "sm2p256v1_common.h"

namespace sm2::internal {

class CommonBackendBundle
{
public:
    static const CommonBackendBundle& instance() noexcept
    {
        static const CommonBackendBundle bundle;
        return bundle;
    }

    common::CommonContext context;
    SM2P256V1Provider     provider;

private:
    CommonBackendBundle() noexcept
        : context(),
          provider{
              []() noexcept { return true; },
              "common",
              &context,
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_cmp)>(
                  common::sm2_bn_cmp),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_cpy)>(
                  common::sm2_bn_cpy),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_equal_zero)>(
                  common::sm2_bn_equal_zero),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_add_uint32)>(
                  common::sm2_bn_add_uint32),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_mod_n_sub1)>(
                  common::sm2_bn_mod_n_sub1),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_mod_n_sub2)>(
                  common::sm2_bn_mod_n_sub2),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_from_bytes)>(
                  common::sm2_bn_from_bytes),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_bn_to_bytes)>(
                  common::sm2_bn_to_bytes),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_add)>(
                  common::sm2_fp_add),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_dbl)>(
                  common::sm2_fp_dbl),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_tpl)>(
                  common::sm2_fp_tpl),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_sub)>(
                  common::sm2_fp_sub),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_mul)>(
                  common::sm2_fp_mul),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_sqr)>(
                  common::sm2_fp_sqr),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_neg)>(
                  common::sm2_fp_neg),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_sqrt)>(
                  common::sm2_fp_sqrt),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_inv)>(
                  common::sm2_fp_inv),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_equal)>(
                  common::sm2_fp_equal),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_equal_zero)>(
                  common::sm2_fp_equal_zero),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_equal_one)>(
                  common::sm2_fp_equal_one),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_cpy)>(
                  common::sm2_fp_cpy),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_set_zero)>(
                  common::sm2_fp_set_zero),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_set_one)>(
                  common::sm2_fp_set_one),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_from_bytes)>(
                  common::sm2_fp_from_bytes),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_to_bytes)>(
                  common::sm2_fp_to_bytes),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_add)>(
                  common::sm2_fn_add),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_sub)>(
                  common::sm2_fn_sub),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_mul)>(
                  common::sm2_fn_mul),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_sqr)>(
                  common::sm2_fn_sqr),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_inv)>(
                  common::sm2_fn_inv),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_equal)>(
                  common::sm2_fn_equal),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_equal_zero)>(
                  common::sm2_fn_equal_zero),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_equal_one)>(
                  common::sm2_fn_equal_one),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_cpy)>(
                  common::sm2_fn_cpy),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_set_zero)>(
                  common::sm2_fn_set_zero),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_set_one)>(
                  common::sm2_fn_set_one),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_from_bytes)>(
                  common::sm2_fn_from_bytes),
              reinterpret_cast<
                  decltype(SM2P256V1Provider::sm2_fn_from_bytes_ex)>(
                  common::sm2_fn_from_bytes_ex),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_to_bytes)>(
                  common::sm2_fn_to_bytes),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_to_bn)>(
                  common::sm2_fp_to_bn),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fp_from_bn)>(
                  common::sm2_fp_from_bn),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_to_bn)>(
                  common::sm2_fn_to_bn),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_from_bn)>(
                  common::sm2_fn_from_bn),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_from_fp)>(
                  common::sm2_fn_from_fp),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_fn_to_fp)>(
                  common::sm2_fn_to_fp),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_a_cpy)>(
                  common::sm2_ec_a_cpy),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_a_check)>(
                  common::sm2_ec_a_check),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_a_neg)>(
                  common::sm2_ec_a_neg),
              reinterpret_cast<
                  decltype(SM2P256V1Provider::sm2_ec_a_to_bytes04)>(
                  common::sm2_ec_a_to_bytes04),
              reinterpret_cast<
                  decltype(SM2P256V1Provider::sm2_ec_a_from_bytes04)>(
                  common::sm2_ec_a_from_bytes04),
              reinterpret_cast<
                  decltype(SM2P256V1Provider::sm2_ec_a_to_bytes_uncompressed)>(
                  common::sm2_ec_a_to_bytes_uncompressed),
              reinterpret_cast<
                  decltype(SM2P256V1Provider::sm2_ec_a_to_bytes_compressed)>(
                  common::sm2_ec_a_to_bytes_compressed),
              reinterpret_cast<
                  decltype(SM2P256V1Provider::sm2_ec_a_to_bytes_mix)>(
                  common::sm2_ec_a_to_bytes_mix),
              reinterpret_cast<
                  decltype(SM2P256V1Provider::sm2_ec_a_from_bytes)>(
                  common::sm2_ec_a_from_bytes),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_cpy)>(
                  common::sm2_ec_j_cpy),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_is_inf)>(
                  common::sm2_ec_j_is_inf),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_set_inf)>(
                  common::sm2_ec_j_set_inf),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_neg)>(
                  common::sm2_ec_j_neg),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_add)>(
                  common::sm2_ec_j_add),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_add_a)>(
                  common::sm2_ec_j_add_a),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_dbl)>(
                  common::sm2_ec_j_dbl),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_mul_a)>(
                  common::sm2_ec_j_mul_a),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_mul_g)>(
                  common::sm2_ec_j_mul_g),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_from_a)>(
                  common::sm2_ec_j_from_a),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_to_a)>(
                  common::sm2_ec_j_to_a),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_normal)>(
                  common::sm2_ec_j_normal),
              reinterpret_cast<decltype(SM2P256V1Provider::sm2_ec_j_equal)>(
                  common::sm2_ec_j_equal),
          }
    {
    }
};

static const SM2P256V1Provider* find_provider(const char* impl) noexcept
{
    const auto* provider = &CommonBackendBundle::instance().provider;
    if (provider->available() &&
        (impl == nullptr || std::strcmp(provider->algo_name, impl) == 0))
    {
        return provider;
    }
    return nullptr;
}

const SM2P256V1Provider* get_provider(const char* impl) noexcept
{
    if (impl == nullptr)
    {
        static const SM2P256V1Provider* provider = find_provider(nullptr);
        return provider;
    }
    return find_provider(impl);
}

} // namespace sm2::internal
