#ifndef SM2_INTERNAL_SM2_ALG_H
#define SM2_INTERNAL_SM2_ALG_H

#include <gmlib/hash_lib/hash.h>
#include <gmlib/rng/rng.h>

#include <cstddef>
#include <cstdint>

namespace sm2 {

enum class SM2EcPC : std::uint8_t;

namespace internal {

void sm2_set_public_key(std::uint8_t       public_x[32],
                        std::uint8_t       public_y[32],
                        const std::uint8_t x[32],
                        const std::uint8_t y[32]);

void sm2_get_public_key(std::uint8_t       x[32],
                        std::uint8_t       y[32],
                        const std::uint8_t public_x[32],
                        const std::uint8_t public_y[32]) noexcept;

void sm2_set_private_key(std::uint8_t       private_key[32],
                         std::uint8_t       public_x[32],
                         std::uint8_t       public_y[32],
                         const std::uint8_t input[32]);

void sm2_set_private_key_and_public_key(
    std::uint8_t       private_key[32],
    std::uint8_t       public_x[32],
    std::uint8_t       public_y[32],
    const std::uint8_t input_private_key[32],
    const std::uint8_t input_public_x[32],
    const std::uint8_t input_public_y[32]) noexcept;

void sm2_get_private_key(std::uint8_t       private_key[32],
                         const std::uint8_t stored_private_key[32]) noexcept;

void sm2_get_private_key_and_public_key(
    std::uint8_t       private_key[32],
    std::uint8_t       public_x[32],
    std::uint8_t       public_y[32],
    const std::uint8_t stored_private_key[32],
    const std::uint8_t stored_public_x[32],
    const std::uint8_t stored_public_y[32]) noexcept;

void sm2_generate_private_key(std::uint8_t private_key[32],
                              std::uint8_t public_x[32],
                              std::uint8_t public_y[32],
                              rng::Rng&    rng);

void sm2_compute_z(std::uint8_t*       z,
                   const std::uint8_t* id,
                   std::size_t         id_len,
                   const std::uint8_t  x[32],
                   const std::uint8_t  y[32],
                   hash_lib::Hash&     hash);

int sm2_kdf_xor(std::uint8_t*       out,
                const std::uint8_t* in,
                std::size_t         inl,
                const std::uint8_t* z,
                std::size_t         z_len,
                hash_lib::Hash&     hash);

bool sm2_verify(const std::uint8_t  sig_r[32],
                const std::uint8_t  sig_s[32],
                const std::uint8_t* msg,
                std::size_t         msg_len,
                const std::uint8_t* id,
                std::size_t         id_len,
                const std::uint8_t  pub_x[32],
                const std::uint8_t  pub_y[32],
                hash_lib::Hash&     hash);

std::size_t sm2_ciphertext_len(std::size_t plaintext_len,
                               std::size_t digest_size,
                               SM2EcPC     pc);

void sm2_encrypt(std::uint8_t*       ciphertext,
                 std::size_t*        ciphertext_len,
                 const std::uint8_t* plaintext,
                 std::size_t         plaintext_len,
                 rng::Rng&           rng,
                 SM2EcPC             pc,
                 const std::uint8_t  pub_x[32],
                 const std::uint8_t  pub_y[32],
                 hash_lib::Hash&     hash);

void sm2_sign(std::uint8_t        sig_r[32],
              std::uint8_t        sig_s[32],
              const std::uint8_t* msg,
              std::size_t         msg_len,
              rng::Rng&           rng,
              const std::uint8_t* id,
              std::size_t         id_len,
              const std::uint8_t  private_key[32],
              const std::uint8_t  pub_x[32],
              const std::uint8_t  pub_y[32],
              hash_lib::Hash&     hash);

std::size_t sm2_plaintext_len(const std::uint8_t* ciphertext,
                              std::size_t         ciphertext_len,
                              std::size_t         digest_size);

void sm2_decrypt(std::uint8_t*       plaintext,
                 std::size_t*        plaintext_len,
                 const std::uint8_t* ciphertext,
                 std::size_t         ciphertext_len,
                 const std::uint8_t  private_key[32],
                 hash_lib::Hash&     hash);

} // namespace internal
} // namespace sm2

#endif
