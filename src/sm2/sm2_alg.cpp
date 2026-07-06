#include <gmlib/memory_utils/endian.h>
#include <gmlib/memory_utils/memxor.h>
#include <gmlib/sm2/internal/sm2_alg.h>
#include <gmlib/sm2/internal/sm2_const.h>
#include <gmlib/sm2/internal/sm2p256v1.h>
#include <gmlib/sm2/sm2.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace sm2::internal {

namespace {

std::size_t digest_size(hash_lib::Hash& hash)
{
    const std::size_t size = hash.fetch_digest_size();
    if (size == 0)
    {
        throw std::runtime_error("SM2 hash is not set");
    }
    return size;
}

} // namespace

void sm2_set_public_key(std::uint8_t       public_x[32],
                        std::uint8_t       public_y[32],
                        const std::uint8_t x[32],
                        const std::uint8_t y[32])
{
    internal::sm2_ec_a point;
    internal::sm2_fp_from_bytes(point[0], x);
    internal::sm2_fp_from_bytes(point[1], y);
    if (!internal::sm2_ec_a_check(point))
    {
        throw std::runtime_error("invalid sm2p256v1 PublicKey");
    }
    std::memcpy(public_x, x, 32);
    std::memcpy(public_y, y, 32);
}

void sm2_get_public_key(std::uint8_t       x[32],
                        std::uint8_t       y[32],
                        const std::uint8_t public_x[32],
                        const std::uint8_t public_y[32]) noexcept
{
    std::memcpy(x, public_x, 32);
    std::memcpy(y, public_y, 32);
}

void sm2_set_private_key(std::uint8_t       private_key[32],
                         std::uint8_t       public_x[32],
                         std::uint8_t       public_y[32],
                         const std::uint8_t input[32])
{
    internal::sm2_bn_t d, reduced;
    internal::sm2_bn_from_bytes(d, input);
    internal::sm2_bn_cpy(reduced, d);
    internal::sm2_bn_mod_n_sub1(reduced);
    if (internal::sm2_bn_equal_zero(d) || internal::sm2_bn_cmp(d, reduced) != 0)
    {
        throw std::runtime_error("invalid sm2 PrivateKey");
    }

    std::memcpy(private_key, input, 32);
    internal::sm2_ec_t public_point;
    internal::sm2_ec_j_mul_g(public_point.j, input);
    internal::sm2_ec_j_to_a(public_point.a, public_point.j);
    internal::sm2_fp_to_bytes(public_x, public_point.a[0]);
    internal::sm2_fp_to_bytes(public_y, public_point.a[1]);
}

void sm2_set_private_key_and_public_key(
    std::uint8_t       private_key[32],
    std::uint8_t       public_x[32],
    std::uint8_t       public_y[32],
    const std::uint8_t input_private_key[32],
    const std::uint8_t input_public_x[32],
    const std::uint8_t input_public_y[32]) noexcept
{
    std::memcpy(private_key, input_private_key, 32);
    std::memcpy(public_x, input_public_x, 32);
    std::memcpy(public_y, input_public_y, 32);
}

void sm2_get_private_key(std::uint8_t       private_key[32],
                         const std::uint8_t stored_private_key[32]) noexcept
{
    std::memcpy(private_key, stored_private_key, 32);
}

void sm2_get_private_key_and_public_key(
    std::uint8_t       private_key[32],
    std::uint8_t       public_x[32],
    std::uint8_t       public_y[32],
    const std::uint8_t stored_private_key[32],
    const std::uint8_t stored_public_x[32],
    const std::uint8_t stored_public_y[32]) noexcept
{
    std::memcpy(private_key, stored_private_key, 32);
    std::memcpy(public_x, stored_public_x, 32);
    std::memcpy(public_y, stored_public_y, 32);
}

void sm2_generate_private_key(std::uint8_t private_key[32],
                              std::uint8_t public_x[32],
                              std::uint8_t public_y[32],
                              rng::Rng&    rng)
{
    std::uint8_t       random[32];
    internal::sm2_bn_t d;
    rng.gen(random, sizeof(random));
    internal::sm2_bn_from_bytes(d, random);
    internal::sm2_bn_mod_n_sub2(d);
    internal::sm2_bn_add_uint32(d, d, 1);
    internal::sm2_bn_to_bytes(private_key, d);

    internal::sm2_ec_t public_point;
    internal::sm2_ec_j_mul_g(public_point.j, private_key);
    internal::sm2_ec_j_to_a(public_point.a, public_point.j);
    internal::sm2_fp_to_bytes(public_x, public_point.a[0]);
    internal::sm2_fp_to_bytes(public_y, public_point.a[1]);
}

void sm2_compute_z(std::uint8_t*       z,
                   const std::uint8_t* id,
                   std::size_t         id_len,
                   const std::uint8_t  x[32],
                   const std::uint8_t  y[32],
                   hash_lib::Hash&     hash)
{
    if (id_len > UINT16_MAX / 8)
    {
        throw std::runtime_error("SM2 ID length too long");
    }

    std::uint16_t entl_len = static_cast<std::uint16_t>(id_len * 8);
    std::uint8_t  entl[2]  = {
        static_cast<std::uint8_t>(entl_len >> 8),
        static_cast<std::uint8_t>(entl_len),
    };

    hash.reset();
    hash.update(entl, sizeof(entl));
    hash.update(id, id_len);
    hash.update(SM2_CURVE_A, 32);
    hash.update(SM2_CURVE_B, 32);
    hash.update(SM2_CURVE_GX, 32);
    hash.update(SM2_CURVE_GY, 32);
    hash.update(x, 32);
    hash.update(y, 32);
    hash.do_final(z);
}

int sm2_kdf_xor(std::uint8_t*       out,
                const std::uint8_t* in,
                std::size_t         inl,
                const std::uint8_t* z,
                std::size_t         z_len,
                hash_lib::Hash&     hash)
{
    std::size_t size = digest_size(hash);
    if (inl / size >= UINT32_MAX)
    {
        throw std::runtime_error("SM2 KDF derived key too long");
    }
    if (inl == 0)
    {
        return 0;
    }

    bool                      all_zero = true;
    std::uint32_t             ct       = 1;
    std::uint8_t              ct_buf[4];
    std::vector<std::uint8_t> dk(size);
    std::vector<std::uint8_t> zero(size);

    hash.reset();
    hash.update(z, z_len);

    while (inl >= size)
    {
        memory_utils::store32_be(ct_buf, ct);
        auto hash_tmp = hash.clone();
        if (!hash_tmp)
        {
            throw std::runtime_error("SM2 hash is not set");
        }
        hash_tmp->do_final(dk.data(), ct_buf, sizeof(ct_buf));
        all_zero = all_zero && (std::memcmp(zero.data(), dk.data(), size) == 0);
        memory_utils::memxor_n(out, in, dk.data(), size);
        out += size;
        in += size;
        inl -= size;
        ++ct;
    }

    if (inl != 0)
    {
        memory_utils::store32_be(ct_buf, ct);
        auto hash_tmp = hash.clone();
        if (!hash_tmp)
        {
            throw std::runtime_error("SM2 hash is not set");
        }
        hash_tmp->do_final(dk.data(), ct_buf, sizeof(ct_buf));
        all_zero = all_zero && (std::memcmp(zero.data(), dk.data(), inl) == 0);
        memory_utils::memxor_n(out, in, dk.data(), inl);
    }

    return all_zero ? -1 : 0;
}

bool sm2_verify(const std::uint8_t  sig_r[32],
                const std::uint8_t  sig_s[32],
                const std::uint8_t* msg,
                std::size_t         msg_len,
                const std::uint8_t* id,
                std::size_t         id_len,
                const std::uint8_t  pub_x[32],
                const std::uint8_t  pub_y[32],
                hash_lib::Hash&     hash)
{
    std::size_t               size = digest_size(hash);
    std::vector<std::uint8_t> z(size);
    std::uint8_t              t[32];
    internal::sm2_num_t       e, r, s, tmp;
    internal::sm2_ec_t        sG, tP;

    internal::sm2_bn_from_bytes(r.bn, sig_r);
    internal::sm2_bn_from_bytes(s.bn, sig_s);
    internal::sm2_bn_from_bytes(tmp.bn, internal::SM2_CURVE_N);
    if (internal::sm2_bn_equal_zero(r.bn) ||
        internal::sm2_bn_cmp(r.bn, tmp.bn) >= 0 ||
        internal::sm2_bn_equal_zero(s.bn) ||
        internal::sm2_bn_cmp(s.bn, tmp.bn) >= 0)
    {
        return false;
    }

    sm2_compute_z(z.data(), id, id_len, pub_x, pub_y, hash);
    hash.reset();
    hash.update(z.data(), size);
    hash.update(msg, msg_len);
    hash.do_final(z.data());

    internal::sm2_fn_from_bytes(r.fn, sig_r);
    internal::sm2_fn_from_bytes(s.fn, sig_s);
    internal::sm2_fn_add(tmp.fn, r.fn, s.fn);
    if (internal::sm2_fn_equal_zero(tmp.fn))
    {
        return false;
    }
    internal::sm2_fn_to_bytes(t, tmp.fn);

    internal::sm2_fp_from_bytes(tP.a[0], pub_x);
    internal::sm2_fp_from_bytes(tP.a[1], pub_y);
    internal::sm2_ec_j_mul_g(sG.j, sig_s);
    internal::sm2_ec_j_mul_a(tP.j, t, tP.a);
    internal::sm2_ec_j_add(tP.j, sG.j, tP.j);
    internal::sm2_ec_j_to_a(tP.a, tP.j);

    internal::sm2_fn_from_fp(tmp.fn, tP.a[0]);
    internal::sm2_fn_from_bytes_ex(e.fn, z.data(), size);
    internal::sm2_fn_add(tmp.fn, e.fn, tmp.fn);
    return internal::sm2_fn_equal(tmp.fn, r.fn);
}

std::size_t sm2_ciphertext_len(std::size_t plaintext_len,
                               std::size_t digest_size,
                               SM2EcPC     pc)
{
    if (digest_size == 0)
    {
        throw std::runtime_error("SM2 hash is not set");
    }
    const std::size_t point_size = (pc == SM2EcPC::COMPRESSED) ? 33 : 65;
    return point_size + digest_size + plaintext_len;
}

void sm2_encrypt(std::uint8_t*       ciphertext,
                 std::size_t*        ciphertext_len,
                 const std::uint8_t* plaintext,
                 std::size_t         plaintext_len,
                 rng::Rng&           rng,
                 SM2EcPC             pc,
                 const std::uint8_t  pub_x[32],
                 const std::uint8_t  pub_y[32],
                 hash_lib::Hash&     hash)
{
    std::size_t   size   = digest_size(hash);
    std::size_t   c1_len = (pc == SM2EcPC::COMPRESSED) ? 33 : 65;
    std::uint8_t* c1     = ciphertext;
    std::uint8_t* c3     = c1 + c1_len;
    std::uint8_t* c2     = c3 + size;

    internal::sm2_ec_a  public_point;
    internal::sm2_ec_t  kG, kP;
    internal::sm2_num_t k;
    std::uint8_t        scalar[32];
    std::uint8_t        x2y2[64];

    internal::sm2_fp_from_bytes(public_point[0], pub_x);
    internal::sm2_fp_from_bytes(public_point[1], pub_y);

retry:
    rng.gen(scalar, sizeof(scalar));
    internal::sm2_bn_from_bytes(k.bn, scalar);
    internal::sm2_bn_mod_n_sub1(k.bn);
    internal::sm2_bn_add_uint32(k.bn, k.bn, 1);
    internal::sm2_bn_to_bytes(scalar, k.bn);

    internal::sm2_ec_j_mul_g(kG.j, scalar);
    internal::sm2_ec_j_to_a(kG.a, kG.j);
    internal::sm2_ec_j_mul_a(kP.j, scalar, public_point);
    internal::sm2_ec_j_to_a(kP.a, kP.j);
    internal::sm2_ec_a_to_bytes04(x2y2, kP.a);

    if (sm2_kdf_xor(c2, plaintext, plaintext_len, x2y2, sizeof(x2y2), hash))
    {
        goto retry;
    }

    hash.reset();
    hash.update(x2y2, 32);
    hash.update(plaintext, plaintext_len);
    hash.update(x2y2 + 32, 32);
    hash.do_final(c3);

    if (pc == SM2EcPC::UNCOMPRESSED)
    {
        internal::sm2_ec_a_to_bytes_uncompressed(c1, kG.a);
    }
    else if (pc == SM2EcPC::MIX)
    {
        internal::sm2_ec_a_to_bytes_mix(c1, kG.a);
    }
    else
    {
        internal::sm2_ec_a_to_bytes_compressed(c1, kG.a);
    }

    *ciphertext_len = c1_len + size + plaintext_len;
}

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
              hash_lib::Hash&     hash)
{
    std::size_t               size = digest_size(hash);
    std::vector<std::uint8_t> z(size);
    internal::sm2_num_t       e, r, s, da, k;
    internal::sm2_ec_t        kG;
    internal::sm2_num_t&      tmp = e;
    std::uint8_t              scalar[32];

    sm2_compute_z(z.data(), id, id_len, pub_x, pub_y, hash);
    hash.reset();
    hash.update(z.data(), size);
    hash.update(msg, msg_len);
    hash.do_final(z.data());

retry:
    rng.gen(scalar, sizeof(scalar));
    internal::sm2_bn_from_bytes(k.bn, scalar);
    internal::sm2_bn_mod_n_sub1(k.bn);
    internal::sm2_bn_add_uint32(k.bn, k.bn, 1);
    internal::sm2_bn_to_bytes(scalar, k.bn);

    internal::sm2_ec_j_mul_g(kG.j, scalar);
    internal::sm2_ec_j_to_a(kG.a, kG.j);

    internal::sm2_fn_from_bytes_ex(e.fn, z.data(), size);
    internal::sm2_fn_from_fp(r.fn, kG.a[0]);
    internal::sm2_fn_add(r.fn, e.fn, r.fn);

    internal::sm2_fn_from_bytes(k.fn, scalar);
    internal::sm2_fn_add(tmp.fn, r.fn, k.fn);
    if (internal::sm2_fn_equal_zero(r.fn) ||
        internal::sm2_fn_equal_zero(tmp.fn))
    {
        goto retry;
    }

    internal::sm2_fn_from_bytes(da.fn, private_key);
    internal::sm2_fn_set_one(s.fn);
    internal::sm2_fn_add(s.fn, s.fn, da.fn);
    internal::sm2_fn_inv(s.fn, s.fn);
    internal::sm2_fn_mul(tmp.fn, r.fn, da.fn);
    internal::sm2_fn_sub(k.fn, k.fn, tmp.fn);
    internal::sm2_fn_mul(s.fn, s.fn, k.fn);
    if (internal::sm2_fn_equal_zero(s.fn))
    {
        goto retry;
    }

    internal::sm2_fn_to_bytes(sig_r, r.fn);
    internal::sm2_fn_to_bytes(sig_s, s.fn);
}

std::size_t sm2_plaintext_len(const std::uint8_t* ciphertext,
                              std::size_t         ciphertext_len,
                              std::size_t         digest_size)
{
    if (digest_size == 0)
    {
        throw std::runtime_error("SM2 hash is not set");
    }
    if (ciphertext_len == 0)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }

    std::size_t overhead;
    if (ciphertext[0] == 0x02 || ciphertext[0] == 0x03)
    {
        overhead = 33 + digest_size;
    }
    else if (ciphertext[0] == 0x04 || ciphertext[0] == 0x06 ||
             ciphertext[0] == 0x07)
    {
        overhead = 65 + digest_size;
    }
    else
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }

    if (ciphertext_len < overhead)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    return ciphertext_len - overhead;
}

void sm2_decrypt(std::uint8_t*       plaintext,
                 std::size_t*        plaintext_len,
                 const std::uint8_t* ciphertext,
                 std::size_t         ciphertext_len,
                 const std::uint8_t  private_key[32],
                 hash_lib::Hash&     hash)
{
    std::size_t size   = digest_size(hash);
    std::size_t c2_len = sm2_plaintext_len(ciphertext, ciphertext_len, size);
    std::size_t c1_len = ciphertext_len - c2_len - size;
    const std::uint8_t* c1 = ciphertext;
    const std::uint8_t* c3 = c1 + c1_len;
    const std::uint8_t* c2 = c3 + size;

    internal::sm2_ec_t        dC1;
    std::uint8_t              x2y2[64];
    std::vector<std::uint8_t> computed_c3(size);
    std::size_t               out_len;

    if (internal::sm2_ec_a_from_bytes(dC1.a, &out_len, c1, c1_len))
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    if (out_len != c1_len)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }

    internal::sm2_ec_j_mul_a(dC1.j, private_key, dC1.a);
    internal::sm2_ec_j_to_a(dC1.a, dC1.j);
    internal::sm2_ec_a_to_bytes04(x2y2, dC1.a);

    if (sm2_kdf_xor(plaintext, c2, c2_len, x2y2, sizeof(x2y2), hash))
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    *plaintext_len = c2_len;

    hash.reset();
    hash.update(x2y2, 32);
    hash.update(plaintext, *plaintext_len);
    hash.update(x2y2 + 32, 32);
    hash.do_final(computed_c3.data());
    if (std::memcmp(computed_c3.data(), c3, size) != 0)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
}

} // namespace sm2::internal
