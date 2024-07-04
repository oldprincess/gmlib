#ifndef SM2_SM2_H
#define SM2_SM2_H

#include <gmlib/rng/rng.h>
#include <gmlib/sm2/internal/sm2_alg.h>
#include <gmlib/sm2/internal/sm2p256v1.h>

#include <cstring>
#include <stdexcept>

namespace sm2 {

enum class SM2EcPC
{
    UNCOMPRESSED,
    COMPRESSED,
    MIX,
};

template <class Hash>
class SM2PrivateKey;

template <class Hash>
class SM2PublicKey;

template <class Hash>
class SM2PublicKey
{
    friend SM2PrivateKey<Hash>;

public:
    /// @brief SM2 Signature Size (in bytes)
    static constexpr std::size_t SIG_SIZE = 64;

private:
    /// @brief SM2 Public Key Point
    internal::sm2_ec_a P_;

    /// @brief SM2 Public Key Point coordinate Data
    std::uint8_t x_[32], y_[32];

public:
    /**
     * @brief   SM2 Public Key Initialize
     * @note    need to call the "set_pub" function to Set Key
     */
    SM2PublicKey() noexcept = default;

    /**
     * @brief           SM2 Public Key Initialize and Set
     * @param[in]   x   x coordinate of Public Key (32-bytes, big endian)
     * @param[in]   y   y coordinate of Public Key (32-bytes, big endian)
     */
    inline SM2PublicKey(const std::uint8_t x[32], const std::uint8_t y[32]);

public:
    /**
     * @brief           SM2 Public Key Set
     * @param[in]   x   x coordinate of Public Key (32-bytes, big endian)
     * @param[in]   y   y coordinate of Public Key (32-bytes, big endian)
     */
    inline void set_pub(const std::uint8_t x[32], const std::uint8_t y[32]);

    /**
     * @brief           SM2 Public Key Get
     * @param[out]  x   x coordinate of Public Key (32-bytes, big endian)
     * @param[out]  y   y coordinate of Public Key (32-bytes, big endian)
     */
    inline void get_pub(std::uint8_t x[32], std::uint8_t y[32]) const noexcept;

public:
    /**
     * @brief                   SM2 signature verify
     * @param[in]   sig_rs      signature (64 bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   id          id
     * @param[in]   id_len      id length (in bytes)
     * @return                  Verify Pass (true) or Not (false)
     */
    inline bool verify(
        const std::uint8_t  sig_rs[64],
        const std::uint8_t* msg,
        std::size_t         msg_len,
        const std::uint8_t* id = internal::SM2_DEFAULT_ID,
        std::size_t id_len     = internal::SM2_DEFAULT_ID_LEN) const noexcept;

    /**
     * @brief                   SM2 calculate ciphertext length
     * @param[in]   plaintext   plaintext data
     * @param[in]   p_len       plaintext length (in bytes)
     * @param[in]   PC          EC point PC
     * @return                  ciphertext length
     */
    static inline std::size_t ciphertext_len(
        const std::uint8_t* plaintext,
        std::size_t         p_len,
        SM2EcPC             PC = SM2EcPC::UNCOMPRESSED) noexcept;

    /**
     * @brief                   SM2 encrypt
     * @param[out]  ciphertext  ciphertext data
     * @param[out]  c_len       ciphertext length (in bytes)
     * @param[in]   plaintext   plaintext data
     * @param[in]   p_len       plaintext length (in bytes)
     * @param[in]   rng         Random Number Generator
     * @param[in]   PC          EC point PC
     */
    inline void encrypt(std::uint8_t*       ciphertext,
                        std::size_t*        c_len,
                        const std::uint8_t* plaintext,
                        std::size_t         p_len,
                        rng::Rng&           rng,
                        SM2EcPC             PC = SM2EcPC::UNCOMPRESSED) const;

private:
    /**
     * @brief                   SM2 encrypt
     * @param[out]  C1          ciphertext C1, point
     * @param[out]  C1_len      C1 length (in bytes)
     * @param[out]  C3          ciphertext C3, hash
     * @param[out]  C3_len      C3 length (in bytes)
     * @param[out]  C2          ciphertext C2, data
     * @param[out]  C2_len      C2 length (in bytes)
     * @param[in]   plaintext   plaintext data
     * @param[in]   p_len       plaintext length (in bytes)
     * @param[in]   rng         Random Number Generator
     * @param[in]   PC          EC point PC
     */
    inline void encrypt_(std::uint8_t*       C1,
                         std::size_t*        C1_len,
                         std::uint8_t*       C3,
                         std::size_t*        C3_len,
                         std::uint8_t*       C2,
                         std::size_t*        C2_len,
                         const std::uint8_t* plaintext,
                         std::size_t         p_len,
                         rng::Rng&           rng,
                         SM2EcPC             PC) const;

    /**
     * @brief                   SM2 signature verify
     * @param[in]   sig_r       signature r (32 bytes)
     * @param[in]   sig_s       signature s (32 bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   id          id
     * @param[in]   id_len      id length (in bytes)
     * @return                  Verify Pass (true) or Not (false)
     */
    inline bool verify_(const std::uint8_t  sig_r[32],
                        const std::uint8_t  sig_s[32],
                        const std::uint8_t* msg,
                        std::size_t         msg_len,
                        const std::uint8_t* id,
                        std::size_t         id_len) const noexcept;
};

template <class Hash>
class SM2PrivateKey
{
    friend SM2PublicKey<Hash>;

public:
    /// @brief SM2 Signature Size (in bytes)
    static constexpr std::size_t SIG_SIZE = 64;

private:
    /// @brief SM2 Private Key Data
    std::uint8_t priv_[32];

    /// @brief SM2 Public Key
    SM2PublicKey<Hash> pub_;

public:
    /**
     * @brief   SM2 Private Key Initialize
     * @note    need to call the "set_priv" or "gen_priv" function to Set Key
     */
    SM2PrivateKey() noexcept = default;

    /**
     * @brief                   SM2 Private Key Initialize and Set
     * @param[in]   priv_key    private key data (32 bytes, big endian)
     */
    inline SM2PrivateKey(const std::uint8_t priv_key[32]);

    /**
     * @brief               SM2 Private Key Initialize and Generate
     * @param[in]   rng     Random Number Generator
     */
    inline SM2PrivateKey(rng::Rng& rng);

public:
    /**
     * @brief                   SM2 Private Key Set
     * @param[in]   priv_key    private key data (32 bytes, big endian)
     */
    inline void set_priv(const std::uint8_t priv_key[32]);

    /**
     * @brief                   SM2 Private Key Set
     * @param[in]   priv_key    private key data (32 bytes, big endian)
     * @param[in]   pub_x       x coordinate of Public Key (32-bytes, big
     *                          endian)
     * @param[in]   pub_y       y coordinate of Public Key (32-bytes, big
     *                          endian)
     * @warning                 will not verify the legitimacy of input data
     */
    inline void set_priv_and_pub(const std::uint8_t priv_key[32],
                                 const std::uint8_t pub_x[32],
                                 const std::uint8_t pub_y[32]) noexcept;

    /**
     * @brief                   SM2 Private Key Get
     * @param[out]  priv_key    private key data (32 bytes, big endian)
     */
    inline void get_priv(std::uint8_t priv_key[32]) const noexcept;

    /**
     * @brief                   SM2 Private Key Get
     * @param[out]  priv_key    private key data (32 bytes, big endian)
     * @param[out]  pub_x       x coordinate of Public Key (32-bytes, big
     *                          endian)
     * @param[out]  pub_y       y coordinate of Public Key (32-bytes, big
     *                          endian)
     */
    inline void get_priv_and_pub(std::uint8_t priv_key[32],
                                 std::uint8_t pub_x[32],
                                 std::uint8_t pub_y[32]) const noexcept;

    /**
     * @brief               SM2 Private Key Generate
     * @param[in]   rng     Random Number Generator
     */
    inline void gen_priv(rng::Rng& rng);

    /**
     * @brief   fetch SM2 Public Key
     * @return  SM2 Public Key const reference
     */
    inline const SM2PublicKey<Hash>& fetch_pub() const noexcept;

public:
    /**
     * @brief                   SM2 sign
     * @param[out]  sig_rs      SM2 signature (64 bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   rng         Random Number Generator
     * @param[in]   id          id, less than 2^16 / 8 bytes
     * @param[in]   id_len      id length (in bytes)
     */
    inline void sign(std::uint8_t        sig_rs[64],
                     const std::uint8_t* msg,
                     std::size_t         msg_len,
                     rng::Rng&           rng,
                     const std::uint8_t* id = internal::SM2_DEFAULT_ID,
                     std::size_t id_len = internal::SM2_DEFAULT_ID_LEN) const;

    /**
     * @brief                   SM2 signature verify
     * @param[in]   sig_rs      signature (64 bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   id          id, less than 2^16 / 8 bytes
     * @param[in]   id_len      id length (in bytes)
     * @return                  Verify Pass (true) or Not (false)
     */
    inline bool verify(
        const std::uint8_t  sig_rs[64],
        const std::uint8_t* msg,
        std::size_t         msg_len,
        const std::uint8_t* id = internal::SM2_DEFAULT_ID,
        std::size_t id_len     = internal::SM2_DEFAULT_ID_LEN) const noexcept;

    /**
     * @brief                   SM2 calculate ciphertext length
     * @param[in]   plaintext   plaintext data
     * @param[in]   p_len       plaintext length (in bytes)
     * @param[in]   PC          EC point PC
     * @return                  ciphertext length
     */
    static inline std::size_t ciphertext_len(
        const std::uint8_t* plaintext,
        std::size_t         p_len,
        SM2EcPC             PC = SM2EcPC::UNCOMPRESSED) noexcept;

    /**
     * @brief                   SM2 encrypt
     * @param[out]  ciphertext  ciphertext data
     * @param[out]  c_len       ciphertext length (in bytes)
     * @param[in]   plaintext   plaintext data
     * @param[in]   p_len       plaintext length (in bytes)
     * @param[in]   rng         Random Number Generator
     * @param[in]   PC          EC point PC
     */
    inline void encrypt(std::uint8_t*       ciphertext,
                        std::size_t*        c_len,
                        const std::uint8_t* plaintext,
                        std::size_t         p_len,
                        rng::Rng&           rng,
                        SM2EcPC             PC = SM2EcPC::UNCOMPRESSED) const;

    /**
     * @brief                   SM2 calculate plaintext length
     * @param[in]   ciphertext  ciphertext data
     * @param[in]   c_len       ciphertext length (in bytes)
     * @return                  plaintext length (in bytes)
     */
    static inline std::size_t plaintext_len(const std::uint8_t* ciphertext,
                                            std::size_t         c_len);

    /**
     * @brief                   SM2 decrypt
     * @param[out]  plaintext   plaintext data
     * @param[out]  p_len       plaintext length (in bytes)
     * @param[in]   ciphertext  ciphertext data
     * @param[in]   c_len       ciphertext length (in bytes)
     */
    inline void decrypt(std::uint8_t*       plaintext,
                        std::size_t*        p_len,
                        const std::uint8_t* ciphertext,
                        std::size_t         c_len) const;

private:
    /**
     * @brief                   SM2 sign
     * @param[out]  sig_r       signature r (32 bytes)
     * @param[out]  sig_s       signature s (32 bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   rng         Random Number Generator
     * @param[in]   id          id, less than 2^16 / 8 bytes
     * @param[in]   id_len      id length (in bytes)
     */
    inline void sign_(std::uint8_t        sig_r[32],
                      std::uint8_t        sig_s[32],
                      const std::uint8_t* msg,
                      std::size_t         msg_len,
                      rng::Rng&           rng,
                      const std::uint8_t* id,
                      std::size_t         id_len) const;

    /**
     * @brief                   SM2 decrypt, ciphertext = C1 || C3 || C2
     * @param[out]  plaintext   plaintext data
     * @param[out]  p_len       plaintext length (in bytes)
     * @param[in]   C1          ciphertext C1, point
     * @param[in]   C1_len      C1 length (in bytes)
     * @param[in]   C3          ciphertext C3, hash
     * @param[in]   C3_len      C3 length (in bytes)
     * @param[in]   C2          ciphertext C2, data
     * @param[in]   C2_len      C2 length (in bytes)
     */
    inline void decrypt_(std::uint8_t*       plaintext,
                         std::size_t*        p_len,
                         const std::uint8_t* C1,
                         std::size_t         C1_len,
                         const std::uint8_t* C3,
                         std::size_t         C3_len,
                         const std::uint8_t* C2,
                         std::size_t         C2_len) const;
};

// ==============================================
// =============== Implement ====================
// ==============================================

template <class Hash>
inline SM2PublicKey<Hash>::SM2PublicKey(const std::uint8_t x[32],
                                        const std::uint8_t y[32])
{
    this->set_pub(x, y);
}

template <class Hash>
inline void SM2PublicKey<Hash>::set_pub(const std::uint8_t x[32],
                                        const std::uint8_t y[32])
{
    internal::sm2_ec_a T;
    internal::sm2_fp_from_bytes(T[0], x);
    internal::sm2_fp_from_bytes(T[1], y);
    if (!internal::sm2_ec_a_check(T))
    {
        throw std::runtime_error("invalid sm2p256v1 PublicKey");
    }
    internal::sm2_ec_a_cpy(P_, T);
    std::memcpy(x_, x, 32);
    std::memcpy(y_, y, 32);
}

template <class Hash>
inline void SM2PublicKey<Hash>::get_pub(std::uint8_t x[32],
                                        std::uint8_t y[32]) const noexcept
{
    std::memcpy(x, x_, 32);
    std::memcpy(y, y_, 32);
}

template <class Hash>
inline bool SM2PublicKey<Hash>::verify(const std::uint8_t  sig_rs[64],
                                       const std::uint8_t* msg,
                                       std::size_t         msg_len,
                                       const std::uint8_t* id,
                                       std::size_t id_len) const noexcept
{
    return this->verify_(sig_rs, sig_rs + 32, msg, msg_len, id, id_len);
}

template <class Hash>
inline std::size_t SM2PublicKey<Hash>::ciphertext_len(
    const std::uint8_t* plaintext,
    std::size_t         p_len,
    SM2EcPC             PC) noexcept
{
    if (PC == SM2EcPC::UNCOMPRESSED || PC == SM2EcPC::MIX)
    {
        return 65 + Hash::DIGEST_SIZE + p_len;
    }
    else
    {
        return 33 + Hash::DIGEST_SIZE + p_len;
    }
}

template <class Hash>
inline void SM2PublicKey<Hash>::encrypt(std::uint8_t*       ciphertext,
                                        std::size_t*        c_len,
                                        const std::uint8_t* plaintext,
                                        std::size_t         p_len,
                                        rng::Rng&           rng,
                                        SM2EcPC             PC) const
{
    std::uint8_t* C1 = ciphertext;
    std::uint8_t* C3 = C1 + ((PC == SM2EcPC::COMPRESSED) ? 33 : 65);
    std::uint8_t* C2 = C3 + Hash::DIGEST_SIZE;
    std::size_t   C1_len, C3_len, C2_len;
    this->encrypt_(C1, &C1_len, C3, &C3_len, C2, &C2_len, //
                   plaintext, p_len, rng, PC);
    *c_len = C1_len + C3_len + C2_len;
}

template <class Hash>
inline bool SM2PublicKey<Hash>::verify_(const std::uint8_t  sig_r[32],
                                        const std::uint8_t  sig_s[32],
                                        const std::uint8_t* msg,
                                        std::size_t         msg_len,
                                        const std::uint8_t* id,
                                        std::size_t id_len) const noexcept
{
    std::uint8_t        Z[Hash::DIGEST_SIZE], t[32];
    internal::sm2_num_t e, r, s, tmp;
    internal::sm2_ec_t  sG, tP;

    // r' in [1,n-1]?, s' in [1,n-1]?
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
    // H(Z || M)
    internal::sm2_compute_z<Hash>(Z, id, id_len, x_, y_);
    Hash hash;
    hash.update(Z, Hash::DIGEST_SIZE);
    hash.update(msg, msg_len);
    hash.do_final(Z);
    // t = r' + s' mod n
    internal::sm2_fn_from_bytes(r.fn, sig_r);
    internal::sm2_fn_from_bytes(s.fn, sig_s);
    internal::sm2_fn_add(tmp.fn, r.fn, s.fn);
    if (internal::sm2_fn_equal_zero(tmp.fn))
    {
        return false;
    }
    internal::sm2_fn_to_bytes(t, tmp.fn);
    // x1', y1' = [s']G + [t]P
    internal::sm2_fp_from_bytes(tP.a[0], x_);
    internal::sm2_fp_from_bytes(tP.a[1], y_);
    internal::sm2_ec_j_mul_g(sG.j, sig_s);
    internal::sm2_ec_j_mul_a(tP.j, t, tP.a);
    internal::sm2_ec_j_add(tP.j, sG.j, tP.j);
    internal::sm2_ec_j_to_a(tP.a, tP.j);
    // R = e' + x1' mod n
    internal::sm2_fn_from_fp(tmp.fn, tP.a[0]);
    internal::sm2_fn_from_bytes_ex(e.fn, Z, Hash::DIGEST_SIZE);
    internal::sm2_fn_add(tmp.fn, e.fn, tmp.fn);
    if (internal::sm2_fn_equal(tmp.fn, r.fn))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class Hash>
inline void SM2PublicKey<Hash>::encrypt_(std::uint8_t*       C1,
                                         std::size_t*        C1_len,
                                         std::uint8_t*       C3,
                                         std::size_t*        C3_len,
                                         std::uint8_t*       C2,
                                         std::size_t*        C2_len,
                                         const std::uint8_t* plaintext,
                                         std::size_t         p_len,
                                         rng::Rng&           rng,
                                         SM2EcPC             PC) const
{
    internal::sm2_ec_t  kG, kP;
    internal::sm2_num_t k;
    std::uint8_t        _k[32];
    std::uint8_t        x2y2[64];
    Hash                hash;

retry:
    // k = random[1, n-1]
    rng.gen(_k, 32);
    internal::sm2_bn_from_bytes(k.bn, _k);
    internal::sm2_bn_mod_n_sub1(k.bn);
    internal::sm2_bn_add_uint32(k.bn, k.bn, 1);
    internal::sm2_bn_to_bytes(_k, k.bn);
    // C1 = x1,y1 = [k]G
    internal::sm2_ec_j_mul_g(kG.j, _k);
    internal::sm2_ec_j_to_a(kG.a, kG.j);
    // x2,y2 = [k]P
    internal::sm2_ec_j_mul_a(kP.j, _k, P_);
    internal::sm2_ec_j_to_a(kP.a, kP.j);
    internal::sm2_ec_a_to_bytes04(x2y2, kP.a);
    // C2 = M xor KDF
    if (internal::sm2_kdf_xor<Hash>(C2, plaintext, p_len, x2y2, 64))
    {
        goto retry;
    }
    *C2_len = p_len;
    // C3 = Hash(x2 || M || y2)
    hash.update(x2y2 + 0, 32);
    hash.update(plaintext, p_len);
    hash.update(x2y2 + 32, 32);
    hash.do_final(C3);
    *C3_len = Hash::DIGEST_SIZE;
    //
    if (PC == SM2EcPC::UNCOMPRESSED)
    {
        internal::sm2_ec_a_to_bytes_uncompressed(C1, kG.a);
        *C1_len = 65;
    }
    else if (PC == SM2EcPC::MIX)
    {
        internal::sm2_ec_a_to_bytes_mix(C1, kG.a);
        *C1_len = 65;
    }
    else
    {
        internal::sm2_ec_a_to_bytes_compressed(C1, kG.a);
        *C1_len = 33;
    }
}

template <class Hash>
inline SM2PrivateKey<Hash>::SM2PrivateKey(const std::uint8_t priv_key[32])
{
    this->set_priv(priv_key);
}

template <class Hash>
inline SM2PrivateKey<Hash>::SM2PrivateKey(rng::Rng& rng)
{
    this->gen_priv(rng);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::gen_priv(rng::Rng& rng)
{
    std::uint8_t priv_key[32];
    // gen priv_key, [1, n-2]
    internal::sm2_bn_t d;
    rng.gen(priv_key, 32);
    internal::sm2_bn_from_bytes(d, priv_key);
    internal::sm2_bn_mod_n_sub1(d);
    internal::sm2_bn_add_uint32(d, d, 1);
    internal::sm2_bn_to_bytes(priv_, d);
    // set pub
    internal::sm2_ec_t dG;
    internal::sm2_ec_j_mul_g(dG.j, priv_); // never inf
    internal::sm2_ec_j_to_a(dG.a, dG.j);
    internal::sm2_ec_a_cpy(pub_.P_, dG.a);
    internal::sm2_fp_to_bytes(pub_.x_, dG.a[0]);
    internal::sm2_fp_to_bytes(pub_.y_, dG.a[1]);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::set_priv(const std::uint8_t priv_key[32])
{
    // check priv_key, [1, n-2]
    internal::sm2_bn_t d, t;
    internal::sm2_bn_from_bytes(d, priv_key);
    internal::sm2_bn_cpy(t, d);
    internal::sm2_bn_mod_n_sub1(t);
    if (internal::sm2_bn_equal_zero(d) || internal::sm2_bn_cmp(d, t) != 0)
    {
        throw std::runtime_error("invalid sm2 PrivateKey");
    }
    std::memcpy(priv_, priv_key, 32);
    // set pub
    internal::sm2_ec_j dG;
    internal::sm2_ec_j_mul_g(dG, priv_key); // never inf
    internal::sm2_ec_j_to_a(pub_.P_, dG);
    internal::sm2_fp_to_bytes(pub_.x_, pub_.P_[0]);
    internal::sm2_fp_to_bytes(pub_.y_, pub_.P_[1]);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::set_priv_and_pub(
    const std::uint8_t priv_key[32],
    const std::uint8_t pub_x[32],
    const std::uint8_t pub_y[32]) noexcept
{
    std::memcpy(priv_, priv_key, 32);
    std::memcpy(pub_.x_, pub_x, 32);
    std::memcpy(pub_.y_, pub_y, 32);
    internal::sm2_fp_from_bytes(pub_.P_[0], pub_x);
    internal::sm2_fp_from_bytes(pub_.P_[1], pub_y);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::get_priv(
    std::uint8_t priv_key[32]) const noexcept
{
    std::memcpy(priv_key, priv_, 32);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::get_priv_and_pub(
    std::uint8_t priv_key[32],
    std::uint8_t pub_x[32],
    std::uint8_t pub_y[32]) const noexcept
{
    std::memcpy(priv_key, priv_, 32);
    std::memcpy(pub_x, pub_.x_, 32);
    std::memcpy(pub_y, pub_.y_, 32);
}

template <class Hash>
inline const SM2PublicKey<Hash>& SM2PrivateKey<Hash>::fetch_pub() const noexcept
{
    return pub_;
}

template <class Hash>
inline void SM2PrivateKey<Hash>::sign(std::uint8_t        sig_rs[64],
                                      const std::uint8_t* msg,
                                      std::size_t         msg_len,
                                      rng::Rng&           rng,
                                      const std::uint8_t* id,
                                      std::size_t         id_len) const
{
    this->sign_(sig_rs + 0, sig_rs + 32, msg, msg_len, rng, id, id_len);
}

template <class Hash>
inline bool SM2PrivateKey<Hash>::verify(const std::uint8_t  sig_rs[64],
                                        const std::uint8_t* msg,
                                        std::size_t         msg_len,
                                        const std::uint8_t* id,
                                        std::size_t id_len) const noexcept
{
    return pub_.verify(sig_rs, msg, msg_len, id, id_len);
}

template <class Hash>
inline std::size_t SM2PrivateKey<Hash>::ciphertext_len(
    const std::uint8_t* plaintext,
    std::size_t         p_len,
    SM2EcPC             PC) noexcept
{
    return SM2PublicKey<Hash>::ciphertext_len(plaintext, p_len, PC);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::encrypt(std::uint8_t*       ciphertext,
                                         std::size_t*        c_len,
                                         const std::uint8_t* plaintext,
                                         std::size_t         p_len,
                                         rng::Rng&           rng,
                                         SM2EcPC             PC) const
{
    pub_.encrypt(ciphertext, c_len, plaintext, p_len, rng, PC);
}

template <class Hash>
inline std::size_t SM2PrivateKey<Hash>::plaintext_len(
    const std::uint8_t* ciphertext,
    std::size_t         c_len)
{
    if (c_len == 0)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    std::size_t C1C3_len;
    if (ciphertext[0] == 0x02 || ciphertext[0] == 0x03)
    {
        C1C3_len = 33 + Hash::DIGEST_SIZE;
    }
    else if (ciphertext[0] == 0x04 || ciphertext[0] == 0x06 ||
             ciphertext[0] == 0x07)
    {
        C1C3_len = 65 + Hash::DIGEST_SIZE;
    }
    else
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    if (c_len < C1C3_len)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    return c_len - C1C3_len;
}

template <class Hash>
inline void SM2PrivateKey<Hash>::decrypt(std::uint8_t*       plaintext,
                                         std::size_t*        p_len,
                                         const std::uint8_t* ciphertext,
                                         std::size_t         c_len) const
{
    std::size_t         C3_len = Hash::DIGEST_SIZE;
    std::size_t         C2_len = this->plaintext_len(ciphertext, c_len);
    std::size_t         C1_len = c_len - C2_len - C3_len;
    const std::uint8_t* C1     = ciphertext;
    const std::uint8_t* C3     = C1 + C1_len;
    const std::uint8_t* C2     = C3 + C3_len;
    this->decrypt_(plaintext, p_len, C1, C1_len, C3, C3_len, C2, C2_len);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::sign_(std::uint8_t        sig_r[32],
                                       std::uint8_t        sig_s[32],
                                       const std::uint8_t* msg,
                                       std::size_t         msg_len,
                                       rng::Rng&           rng,
                                       const std::uint8_t* id,
                                       std::size_t         id_len) const
{
    std::uint8_t         Z[Hash::DIGEST_SIZE];
    internal::sm2_num_t  e, r, s, da, k;
    internal::sm2_ec_t   kG;
    internal::sm2_num_t& tmp = e;

    std::uint8_t _k[32];
    internal::sm2_compute_z<Hash>(Z, id, id_len, pub_.x_, pub_.y_);

    Hash hash;
    hash.update(Z, Hash::DIGEST_SIZE);
    hash.update(msg, msg_len);
    hash.do_final(Z);

retry:
    // k = random[1, n-1]
    rng.gen(_k, 32);
    internal::sm2_bn_from_bytes(k.bn, _k);
    internal::sm2_bn_mod_n_sub1(k.bn);
    internal::sm2_bn_add_uint32(k.bn, k.bn, 1);
    internal::sm2_bn_to_bytes(_k, k.bn);
    // x1,y1 = [k]G
    internal::sm2_ec_j_mul_g(kG.j, _k);
    internal::sm2_ec_j_to_a(kG.a, kG.j);
    // r = e + x1 mod n
    internal::sm2_fn_from_bytes_ex(e.fn, Z, Hash::DIGEST_SIZE);
    internal::sm2_fn_from_fp(r.fn, kG.a[0]);
    internal::sm2_fn_add(r.fn, e.fn, r.fn);
    // if r=0 or r+k=n, retry
    internal::sm2_fn_from_bytes(k.fn, _k);
    internal::sm2_fn_add(tmp.fn, r.fn, k.fn);
    if (internal::sm2_fn_equal_zero(r.fn) ||
        internal::sm2_fn_equal_zero(tmp.fn))
    {
        goto retry;
    }
    // s = (1+da)^-1 * (k - r * da) mod n
    internal::sm2_fn_from_bytes(da.fn, priv_);
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
    // output
    internal::sm2_fn_to_bytes(sig_r, r.fn);
    internal::sm2_fn_to_bytes(sig_s, s.fn);
}

template <class Hash>
inline void SM2PrivateKey<Hash>::decrypt_(std::uint8_t*       plaintext,
                                          std::size_t*        p_len,
                                          const std::uint8_t* C1,
                                          std::size_t         C1_len,
                                          const std::uint8_t* C3,
                                          std::size_t         C3_len,
                                          const std::uint8_t* C2,
                                          std::size_t         C2_len) const
{
    internal::sm2_ec_t dC1;
    std::uint8_t       x2y2[64], buf[Hash::DIGEST_SIZE];
    Hash               hash;
    std::size_t        outl;
    // x1,y1 = C1
    if (internal::sm2_ec_a_from_bytes(dC1.a, &outl, C1, C1_len))
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    if (outl != C1_len || C3_len != Hash::DIGEST_SIZE)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    // x2,y2 = [d]C1
    internal::sm2_ec_j_mul_a(dC1.j, priv_, dC1.a);
    internal::sm2_ec_j_to_a(dC1.a, dC1.j);
    // M = KDF xor C2
    internal::sm2_ec_a_to_bytes04(x2y2, dC1.a);
    if (internal::sm2_kdf_xor<Hash>(plaintext, C2, C2_len, x2y2, 64))
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
    *p_len = C2_len;
    // C3 = Hash(x2 || M || y2)
    hash.update(x2y2 + 0, 32);
    hash.update(plaintext, *p_len);
    hash.update(x2y2 + 32, 32);
    hash.do_final(buf);
    if (std::memcmp(buf, C3, Hash::DIGEST_SIZE) != 0)
    {
        throw std::runtime_error("invalid sm2 ciphertext");
    }
}

} // namespace sm2

#endif