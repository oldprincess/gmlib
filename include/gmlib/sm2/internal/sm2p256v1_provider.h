#ifndef SM2_INTERNAL_SM2P256V1_PROVIDER_H
#define SM2_INTERNAL_SM2P256V1_PROVIDER_H

#include <cstddef>
#include <cstdint>

namespace sm2::internal {

struct SM2P256V1Provider
{
    bool (*available)() noexcept;

    const char* algo_name;

    const void* context;

    int (*sm2_bn_cmp)(const void*        context,
                      const std::uint8_t a[32],
                      const std::uint8_t b[32]) noexcept;

    void (*sm2_bn_cpy)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    bool (*sm2_bn_equal_zero)(const void*        context,
                              const std::uint8_t a[32]) noexcept;

    int (*sm2_bn_add_uint32)(const void*        context,
                             std::uint8_t       r[32],
                             const std::uint8_t a[32],
                             std::uint32_t      b) noexcept;

    void (*sm2_bn_mod_n_sub1)(const void* context, std::uint8_t a[32]) noexcept;

    void (*sm2_bn_mod_n_sub2)(const void* context, std::uint8_t a[32]) noexcept;

    void (*sm2_bn_from_bytes)(const void*        context,
                              std::uint8_t       r[32],
                              const std::uint8_t in[32]) noexcept;

    void (*sm2_bn_to_bytes)(const void*        context,
                            std::uint8_t       out[32],
                            const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_add)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32],
                       const std::uint8_t b[32]) noexcept;

    void (*sm2_fp_dbl)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_tpl)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_sub)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32],
                       const std::uint8_t b[32]) noexcept;

    void (*sm2_fp_mul)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32],
                       const std::uint8_t b[32]) noexcept;

    void (*sm2_fp_sqr)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_neg)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    int (*sm2_fp_sqrt)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_inv)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    bool (*sm2_fp_equal)(const void*        context,
                         const std::uint8_t a[32],
                         const std::uint8_t b[32]) noexcept;

    bool (*sm2_fp_equal_zero)(const void*        context,
                              const std::uint8_t a[32]) noexcept;

    bool (*sm2_fp_equal_one)(const void*        context,
                             const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_cpy)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_set_zero)(const void* context, std::uint8_t r[32]) noexcept;

    void (*sm2_fp_set_one)(const void* context, std::uint8_t r[32]) noexcept;

    void (*sm2_fp_from_bytes)(const void*        context,
                              std::uint8_t       r[32],
                              const std::uint8_t in[32]) noexcept;

    void (*sm2_fp_to_bytes)(const void*        context,
                            std::uint8_t       out[32],
                            const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_add)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32],
                       const std::uint8_t b[32]) noexcept;

    void (*sm2_fn_sub)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32],
                       const std::uint8_t b[32]) noexcept;

    void (*sm2_fn_mul)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32],
                       const std::uint8_t b[32]) noexcept;

    void (*sm2_fn_sqr)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_inv)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    bool (*sm2_fn_equal)(const void*        context,
                         const std::uint8_t a[32],
                         const std::uint8_t b[32]) noexcept;

    bool (*sm2_fn_equal_zero)(const void*        context,
                              const std::uint8_t a[32]) noexcept;

    bool (*sm2_fn_equal_one)(const void*        context,
                             const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_cpy)(const void*        context,
                       std::uint8_t       r[32],
                       const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_set_zero)(const void* context, std::uint8_t r[32]) noexcept;

    void (*sm2_fn_set_one)(const void* context, std::uint8_t r[32]) noexcept;

    void (*sm2_fn_from_bytes)(const void*        context,
                              std::uint8_t       r[32],
                              const std::uint8_t in[32]) noexcept;

    void (*sm2_fn_from_bytes_ex)(const void*         context,
                                 std::uint8_t        r[32],
                                 const std::uint8_t* in,
                                 std::size_t         inl) noexcept;

    void (*sm2_fn_to_bytes)(const void*        context,
                            std::uint8_t       out[32],
                            const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_to_bn)(const void*        context,
                         std::uint8_t       r[32],
                         const std::uint8_t a[32]) noexcept;

    void (*sm2_fp_from_bn)(const void*        context,
                           std::uint8_t       r[32],
                           const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_to_bn)(const void*        context,
                         std::uint8_t       r[32],
                         const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_from_bn)(const void*        context,
                           std::uint8_t       r[32],
                           const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_from_fp)(const void*        context,
                           std::uint8_t       r[32],
                           const std::uint8_t a[32]) noexcept;

    void (*sm2_fn_to_fp)(const void*        context,
                         std::uint8_t       r[32],
                         const std::uint8_t a[32]) noexcept;

    void (*sm2_ec_a_cpy)(const void*        context,
                         std::uint8_t       R[2][32],
                         const std::uint8_t P[2][32]) noexcept;

    bool (*sm2_ec_a_check)(const void*        context,
                           const std::uint8_t P[2][32]) noexcept;

    void (*sm2_ec_a_neg)(const void*        context,
                         std::uint8_t       R[2][32],
                         const std::uint8_t P[2][32]) noexcept;

    void (*sm2_ec_a_to_bytes04)(const void*        context,
                                std::uint8_t       out[64],
                                const std::uint8_t P[2][32]) noexcept;

    void (*sm2_ec_a_from_bytes04)(const void*        context,
                                  std::uint8_t       R[2][32],
                                  const std::uint8_t in[64]) noexcept;

    void (*sm2_ec_a_to_bytes_uncompressed)(
        const void*        context,
        std::uint8_t       out[65],
        const std::uint8_t P[2][32]) noexcept;

    void (*sm2_ec_a_to_bytes_compressed)(const void*        context,
                                         std::uint8_t       out[33],
                                         const std::uint8_t P[2][32]) noexcept;

    void (*sm2_ec_a_to_bytes_mix)(const void*        context,
                                  std::uint8_t       out[65],
                                  const std::uint8_t P[2][32]) noexcept;

    int (*sm2_ec_a_from_bytes)(const void*         context,
                               std::uint8_t        R[2][32],
                               std::size_t*        read_n,
                               const std::uint8_t* in,
                               std::size_t         inl) noexcept;

    void (*sm2_ec_j_cpy)(const void*        context,
                         std::uint8_t       R[3][32],
                         const std::uint8_t P[3][32]) noexcept;

    bool (*sm2_ec_j_is_inf)(const void*        context,
                            const std::uint8_t P[3][32]) noexcept;

    void (*sm2_ec_j_set_inf)(const void*  context,
                             std::uint8_t R[3][32]) noexcept;

    void (*sm2_ec_j_neg)(const void*        context,
                         std::uint8_t       R[3][32],
                         const std::uint8_t P[3][32]) noexcept;

    void (*sm2_ec_j_add)(const void*        context,
                         std::uint8_t       R[3][32],
                         const std::uint8_t P[3][32],
                         const std::uint8_t Q[3][32]) noexcept;

    void (*sm2_ec_j_add_a)(const void*        context,
                           std::uint8_t       R[3][32],
                           const std::uint8_t P[3][32],
                           const std::uint8_t Q[2][32]) noexcept;

    void (*sm2_ec_j_dbl)(const void*        context,
                         std::uint8_t       R[3][32],
                         const std::uint8_t P[3][32]) noexcept;

    void (*sm2_ec_j_mul_a)(const void*        context,
                           std::uint8_t       R[3][32],
                           const std::uint8_t k[32],
                           const std::uint8_t P[2][32]) noexcept;

    void (*sm2_ec_j_mul_g)(const void*        context,
                           std::uint8_t       R[3][32],
                           const std::uint8_t k[32]) noexcept;

    void (*sm2_ec_j_from_a)(const void*        context,
                            std::uint8_t       R[3][32],
                            const std::uint8_t P[2][32]) noexcept;

    void (*sm2_ec_j_to_a)(const void*        context,
                          std::uint8_t       R[2][32],
                          const std::uint8_t P[3][32]) noexcept;

    void (*sm2_ec_j_normal)(const void*        context,
                            std::uint8_t       R[3][32],
                            const std::uint8_t P[3][32]) noexcept;

    bool (*sm2_ec_j_equal)(const void*        context,
                           const std::uint8_t P[3][32],
                           const std::uint8_t Q[3][32]) noexcept;
};

const SM2P256V1Provider* get_provider(const char* impl) noexcept;

} // namespace sm2::internal

#endif
