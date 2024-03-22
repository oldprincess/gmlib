#ifndef SM9_SM9_H
#define SM9_SM9_H

#include <gmlib/rng/rng.h>
#include <gmlib/sm9/internal/sm9_alg.h>
#include <gmlib/sm9/internal/sm9_field.h>

#include <stdexcept>

namespace sm9 {

constexpr std::uint8_t SM9_SIG_HID = 1;

enum class SM9EcPC
{
    UNCOMPRESSED,
    COMPRESSED,
    MIX,
};

template <class Hash>
class SM9SignMasterPrivateKey;

template <class Hash>
class SM9SignMasterPublicKey;

template <class Hash>
class SM9SignPrivateKey;

template <class Hash>
using SM9SignPublicKey = SM9SignMasterPublicKey<Hash>;

// ======================================

template <class Hash>
class SM9SignMasterPrivateKey
{
    friend SM9SignMasterPublicKey<Hash>;
    friend SM9SignPrivateKey<Hash>;

private:
    /// @brief SM2 Sign Master Private Key Data
    std::uint8_t ks_[32];

    /// @brief SM2 Sign Public Key
    SM9SignMasterPublicKey<Hash> pub_;

public:
    /**
     * @brief   SM9 Sign Master Private Key Initialize
     * @note    need to call the "set_priv" or "gen_priv" function to Set Key
     */
    SM9SignMasterPrivateKey() noexcept = default;

    /**
     * @brief                   SM9 Sign Master Private Key Initialize and Set
     * @param[in]   priv_key    private key data (32 bytes, big endian)
     */
    inline SM9SignMasterPrivateKey(const std::uint8_t priv_key[32]);

    /**
     * @brief               SM9 Sign Master Private Key Initialize and Generate
     * @param[in]   rng     Random Number Generator
     */
    inline SM9SignMasterPrivateKey(rng::Rng& rng);

public:
    /**
     * @brief                   SM9 Sign Master Private Key Set
     * @param[in]   priv_key    private key data (32 bytes, big endian)
     */
    inline void set_priv(const std::uint8_t priv_key[32]);

    /**
     * @brief                   SM9 Sign Master Private Key Get
     * @param[out]  priv_key    private key data (32 bytes, big endian)
     */
    inline void get_priv(std::uint8_t priv_key[32]) const noexcept;

    /**
     * @brief               SM9 Sign Master Private Key Generate
     * @param[in]   rng     Random Number Generator
     */
    inline void gen_priv(rng::Rng& rng);

    /**
     * @brief               generate SM9 Sign Private Key
     * @param[in]   id      id
     * @param[in]   id_len  id length (in bytes)
     * @param[in]   rng     Random Number Generator
     * @param[in]   hid     hid
     * @return              SM9 Sign Private Key
     */
    inline SM9SignPrivateKey<Hash> gen_SignPrivateKey(
        const std::uint8_t* id,
        std::size_t         id_len,
        rng::Rng&           rng,
        std::uint8_t        hid = SM9_SIG_HID) const;

    /**
     * @brief   fetch SM9 Sign Public Key
     * @return  SM9 Sign Public Key const reference
     */
    inline const SM9SignPublicKey<Hash>& fetch_SignPublicKey() const noexcept;
};

template <class Hash>
class SM9SignMasterPublicKey
{
    friend SM9SignMasterPrivateKey<Hash>;
    friend SM9SignPrivateKey<Hash>;

public:
    static constexpr std::size_t MAX_SIG_SIZE = 32 + 65;

private:
    /// @brief SM9 Sign Master PublicKey - Ppubs
    internal::sm9_ec2_a P_;

    /// @brief precompute data, e(P1, Ppubs)
    internal::sm9_fp12_t e_P1_Ppubs_;

public:
    /**
     * @brief   SM9 Sign Public Key Initialize
     * @note    need to call the "set_pub" function to Set Key
     */
    SM9SignMasterPublicKey() noexcept = default;

    /**
     * @brief           SM9 Sign Public Key Set
     * @param[in]   x   x coordinate of Public Key (64-bytes, big endian)
     * @param[in]   y   y coordinate of Public Key (64-bytes, big endian)
     */
    inline void set_pub(const std::uint8_t x[64], const std::uint8_t y[64]);

    /**
     * @brief           SM9 Sign Public Key Get
     * @param[out]  x   x coordinate of Public Key (64-bytes, big endian)
     * @param[out]  y   y coordinate of Public Key (64-bytes, big endian)
     */
    inline void get_pub(std::uint8_t x[64], std::uint8_t y[64]) const noexcept;

    /**
     * @brief                   SM9 signature verify
     * @param[in]   sig         signature
     * @param[in]   sig_len     signature length (in bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   id          id
     * @param[in]   id_len      id length (in bytes)
     * @param[in]   hid         hid
     * @return                  Verify Pass (true) or Not (false)
     */
    inline bool verify(const std::uint8_t* sig,
                       std::size_t         sig_len,
                       const uint8_t*      msg,
                       std::size_t         msg_len,
                       const std::uint8_t* id,
                       std::size_t         id_len,
                       std::uint8_t        hid = SM9_SIG_HID) const noexcept;
};

template <class Hash>
class SM9SignPrivateKey
{
    friend SM9SignMasterPrivateKey<Hash>;
    friend SM9SignPublicKey<Hash>;

public:
    /// @brief SM9 Max Signature Size (in bytes)
    static constexpr std::size_t MAX_SIG_SIZE = 32 + 65;

private:
    /// @brief SM9 Private Key data
    internal::sm9_ec_a priv_;

    /// @brief SM9 Sign Public Key
    SM9SignPublicKey<Hash> pub_;

public:
    /**
     * @brief   SM9 Sign Private Key Initialize
     * @note    need to call the "set_priv" function to Set Key
     */
    SM9SignPrivateKey() noexcept = default;

    /**
     * @brief   fetch SM9 Sign Public Key
     * @return  SM9 Sign Public Key const reference
     */
    inline const SM9SignPublicKey<Hash>& fetch_pub() const noexcept;

    /**
     * @brief               SM9 Sign Private Key Set
     * @param[in]   priv_x  x coordinate of Private Key (32-bytes, big endian)
     * @param[in]   priv_y  y coordinate of Private Key (32-bytes, big endian)
     * @param[in]   pub_x   x coordinate of Public Key (64-bytes, big endian)
     * @param[in]   pub_y   y coordinate of Public Key (64-bytes, big endian)
     */
    inline void set_priv(const std::uint8_t priv_x[32],
                         const std::uint8_t priv_y[32],
                         const std::uint8_t pub_x[64],
                         const std::uint8_t pub_y[64]);

    /**
     * @brief               SM9 Sign Private Key Get
     * @param[out]  priv_x  x coordinate of Private Key (32-bytes, big endian)
     * @param[out]  priv_y  y coordinate of Private Key (32-bytes, big endian)
     * @param[out]  pub_x   x coordinate of Public Key (64-bytes, big endian)
     * @param[out]  pub_y   y coordinate of Public Key (64-bytes, big endian)
     */
    inline void get_priv(std::uint8_t priv_x[32],
                         std::uint8_t priv_y[32],
                         std::uint8_t pub_x[64],
                         std::uint8_t pub_y[64]) const noexcept;

    /**
     * @brief
     * @param[in]   sig         signature
     * @param[in]   outl        signature length (in bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   rng         Random Number Generator
     * @param[in]   PC          EC point PC
     */
    inline void sign(std::uint8_t*  sig,
                     std::size_t*   outl,
                     const uint8_t* msg,
                     std::size_t    msg_len,
                     rng::Rng&      rng,
                     SM9EcPC        PC = SM9EcPC::UNCOMPRESSED) const;

    /**
     * @brief                   SM9 signature verify
     * @param[in]   sig         signature
     * @param[in]   sig_len     signature length (in bytes)
     * @param[in]   msg         message
     * @param[in]   msg_len     message length (in bytes)
     * @param[in]   id          id
     * @param[in]   id_len      id length (in bytes)
     * @param[in]   hid         hid
     * @return                  Verify Pass (true) or Not (false)
     */
    inline bool verify(const std::uint8_t* sig,
                       std::size_t         sig_len,
                       const uint8_t*      msg,
                       std::size_t         msg_len,
                       const std::uint8_t* id,
                       std::size_t         id_len,
                       std::uint8_t        hid = SM9_SIG_HID) const noexcept;
};

// ==============================================
// =============== Implement ====================
// ==============================================

template <class Hash>
inline SM9SignMasterPrivateKey<Hash>::SM9SignMasterPrivateKey(
    const std::uint8_t priv_key[32])
{
    this->set_priv(priv_key);
}

template <class Hash>
inline SM9SignMasterPrivateKey<Hash>::SM9SignMasterPrivateKey(rng::Rng& rng)
{
    this->gen_priv(rng);
}

template <class Hash>
inline void SM9SignMasterPrivateKey<Hash>::set_priv(
    const std::uint8_t priv_key[32])
{
    // check ks in [1, N-1]
    internal::sm9_bn_t ks, N;
    internal::sm9_bn_from_bytes(ks, priv_key);
    internal::sm9_bn_from_bytes(N, internal::SM9_CURVE_N);
    if (internal::sm9_bn_equal_zero(ks) || internal::sm9_bn_cmp(ks, N) >= 0)
    {
        throw std::runtime_error("invalid sm9 priv key");
    }
    // set priv and pub
    std::memcpy(ks_, priv_key, 32);
    internal::sm9_ec2_j T;
    internal::sm9_ec2_j_mul_g(T, ks_); // never inf
    internal::sm9_ec2_j_to_a(pub_.P_, T);
    internal::sm9_pairing_P1_Q(pub_.e_P1_Ppubs_, pub_.P_);
}

template <class Hash>
inline void SM9SignMasterPrivateKey<Hash>::get_priv(
    std::uint8_t priv_key[32]) const noexcept
{
    std::memcpy(priv_key, ks_, 32);
}

template <class Hash>
inline void SM9SignMasterPrivateKey<Hash>::gen_priv(rng::Rng& rng)
{
    std::uint8_t priv_key[32];
    // gen priv_key, [1, N-1]
    internal::sm9_bn_t d;
    rng.gen(priv_key, 32);
    internal::sm9_bn_from_bytes(d, priv_key);
    internal::sm9_bn_mod_n_sub1(d);
    internal::sm9_bn_add_uint32(d, d, 1);
    internal::sm9_bn_to_bytes(ks_, d);
    // set pub
    internal::sm9_ec2_j dG;
    internal::sm9_ec2_j_mul_g(dG, ks_); // never inf
    internal::sm9_ec2_j_to_a(pub_.P_, dG);
    internal::sm9_pairing_P1_Q(pub_.e_P1_Ppubs_, pub_.P_);
}

template <class Hash>
inline SM9SignPrivateKey<Hash>
SM9SignMasterPrivateKey<Hash>::gen_SignPrivateKey(const std::uint8_t* id,
                                                  std::size_t         id_len,
                                                  rng::Rng&           rng,
                                                  std::uint8_t        hid) const
{
    internal::sm9_fn_t      t1, ks;
    std::uint8_t            t2_buf[32];
    std::uint8_t*           t1_buf = t2_buf;
    SM9SignPrivateKey<Hash> sign_priv;
    internal::sm9_ec_j      t2P1;
    // t1 = H1(ID || hid, N) + ks
    internal::sm9_fn_from_bytes(ks, ks_);
    internal::sm9_Hn<Hash>(t1_buf, id, id_len, &hid, 1, 1);
    internal::sm9_fn_from_bytes(t1, t1_buf);
    internal::sm9_fn_add(t1, t1, ks);
    if (internal::sm9_fn_equal_zero(t1))
    {
        throw std::runtime_error(
            "err in generate SignPrivateKey for ID, "
            "please re-gen SM9SignMasterPrivateKey, and try again");
    }
    // t2 = ks * t1^-1
    internal::sm9_fn_inv(t1, t1);
    internal::sm9_fn_mul(t1, ks, t1);
    internal::sm9_fn_to_bytes(t2_buf, t1);
    // dsa = [t2]P1
    internal::sm9_ec_j_mul_g(t2P1, t2_buf);
    internal::sm9_ec_j_to_a(sign_priv.priv_, t2P1);
    // copy pub
    sign_priv.pub_ = pub_;
    return sign_priv;
}

template <class Hash>
inline const SM9SignPublicKey<Hash>&
SM9SignMasterPrivateKey<Hash>::fetch_SignPublicKey() const noexcept
{
    return this->pub_;
}

template <class Hash>
inline void SM9SignMasterPublicKey<Hash>::set_pub(const std::uint8_t x[64],
                                                  const std::uint8_t y[64])
{
    internal::sm9_ec2_a T;
    internal::sm9_fp2_from_bytes(T[0], x);
    internal::sm9_fp2_from_bytes(T[1], y);
    if (!internal::sm9_ec2_a_check(T))
    {
        throw std::runtime_error("invalid sm9 SignPublicKey");
    }
    internal::sm9_ec2_a_cpy(P_, T);
    internal::sm9_pairing_P1_Q(e_P1_Ppubs_, P_);
}

template <class Hash>
inline void SM9SignMasterPublicKey<Hash>::get_pub(
    std::uint8_t x[64],
    std::uint8_t y[64]) const noexcept
{
    internal::sm9_fp2_to_bytes(x, P_[0]);
    internal::sm9_fp2_to_bytes(y, P_[1]);
}

template <class Hash>
inline bool SM9SignMasterPublicKey<Hash>::verify(
    const std::uint8_t* sig,
    std::size_t         sig_len,
    const uint8_t*      msg,
    std::size_t         msg_len,
    const std::uint8_t* id,
    std::size_t         id_len,
    std::uint8_t        hid) const noexcept
{
    internal::sm9_fp12_t t, w;
    internal::sm9_ec2_t  T;
    internal::sm9_ec_a   S;
    std::uint8_t         w_buf[384];
    std::size_t          size;

    std::uint8_t*       h_ = w_buf;
    const std::uint8_t* h  = sig;

    // (h,S)=sig
    if (sig_len < 32)
    {
        return false;
    }
    if (internal::sm9_ec_a_from_bytes(S, &size, sig + 32, sig_len - 32))
    {
        return false;
    }
    if (size + 32 != sig_len)
    {
        return false;
    }
    // t = e(P1, Ppubs)^h
    internal::sm9_fp12_pow(t, e_P1_Ppubs_, h);
    // h1 = H1(id||HID)
    internal::sm9_Hn<Hash>(h_, id, id_len, &hid, 1, 1);
    //  P = [h1]P2 + Ppub
    internal::sm9_ec2_j_mul_g(T.j, h_);
    internal::sm9_ec2_j_add_a(T.j, T.j, P_);
    internal::sm9_ec2_j_to_a(T.a, T.j);
    // w' = e(S', P) * t
    internal::sm9_pairing(w, S, T.a);
    internal::sm9_fp12_mul(w, w, t);
    internal::sm9_fp12_to_bytes(w_buf, w);
    // h2 = H2(M || w', N)
    internal::sm9_Hn<Hash>(h_, msg, msg_len, w_buf, sizeof(w_buf), 2);
    // check h2 == h'?
    return std::memcmp(h_, h, 32) == 0;
}

template <class Hash>
inline void SM9SignPrivateKey<Hash>::set_priv(const std::uint8_t priv_x[32],
                                              const std::uint8_t priv_y[32],
                                              const std::uint8_t pub_x[64],
                                              const std::uint8_t pub_y[64])
{
    internal::sm9_ec_a T;
    internal::sm9_fp_from_bytes(T[0], priv_x);
    internal::sm9_fp_from_bytes(T[1], priv_y);
    if (!internal::sm9_ec_a_check(T))
    {
        throw std::runtime_error("invalid sm9 SignPrivateKey");
    }
    internal::sm9_ec_a_cpy(priv_, T);

    pub_.set_pub(pub_x, pub_y);
}

template <class Hash>
inline void SM9SignPrivateKey<Hash>::get_priv(
    std::uint8_t priv_x[32],
    std::uint8_t priv_y[32],
    std::uint8_t pub_x[64],
    std::uint8_t pub_y[64]) const noexcept
{
    internal::sm9_fp_to_bytes(priv_x, priv_[0]);
    internal::sm9_fp_to_bytes(priv_y, priv_[1]);
    pub_.get_pub(pub_x, pub_y);
}

template <class Hash>
inline const SM9SignPublicKey<Hash>& SM9SignPrivateKey<Hash>::fetch_pub()
    const noexcept
{
    return pub_;
}

template <class Hash>
inline void SM9SignPrivateKey<Hash>::sign(std::uint8_t*  sig,
                                          std::size_t*   outl,
                                          const uint8_t* msg,
                                          std::size_t    msg_len,
                                          rng::Rng&      rng,
                                          SM9EcPC        PC) const
{
    internal::sm9_fp12_t w;
    internal::sm9_ec_t   S;
    internal::sm9_num_t  r, h;
    std::uint8_t         w_buf[384];

    std::uint8_t* r_buf = w_buf + 0;
    std::uint8_t* h_buf = w_buf + 32;
    std::uint8_t* l_buf = w_buf + 64;
retry:
    // r = [1, N-1]
    rng.gen(r_buf, 32);
    internal::sm9_bn_from_bytes(r.bn, r_buf);
    internal::sm9_bn_mod_n_sub1(r.bn);
    internal::sm9_bn_add_uint32(r.bn, r.bn, 1);
    internal::sm9_bn_to_bytes(r_buf, r.bn);
    // w = e(P1, Ppubs)^r
    internal::sm9_fp12_pow(w, pub_.e_P1_Ppubs_, r_buf);
    internal::sm9_fp12_to_bytes(w_buf, w);
    // h = H2(M||w, N)
    internal::sm9_Hn<Hash>(h_buf, msg, msg_len, w_buf, sizeof(w_buf), 2);
    // l = (r-h) mod N
    internal::sm9_fn_from_bn(r.fn, r.bn);
    internal::sm9_fn_from_bytes(h.fn, h_buf);
    internal::sm9_fn_sub(r.fn, r.fn, h.fn);
    if (internal::sm9_fn_equal_zero(r.fn))
    {
        goto retry;
    }
    internal::sm9_fn_to_bytes(l_buf, r.fn);
    // S = [l]dsa
    internal::sm9_ec_j_mul_a(S.j, l_buf, priv_);
    internal::sm9_ec_j_to_a(S.a, S.j);

    std::memcpy(sig + 0, h_buf, 32);
    if (PC == SM9EcPC::UNCOMPRESSED)
    {
        internal::sm9_ec_a_to_bytes_uncompressed(sig + 32, S.a);
        *outl = 32 + 65;
    }
    else if (PC == SM9EcPC::COMPRESSED)
    {
        internal::sm9_ec_a_to_bytes_compressed(sig + 32, S.a);
        *outl = 32 + 33;
    }
    else
    {
        internal::sm9_ec_a_to_bytes_mix(sig + 32, S.a);
        *outl = 32 + 65;
    }
}

template <class Hash>
inline bool SM9SignPrivateKey<Hash>::verify(const std::uint8_t* sig,
                                            std::size_t         sig_len,
                                            const uint8_t*      msg,
                                            std::size_t         msg_len,
                                            const std::uint8_t* id,
                                            std::size_t         id_len,
                                            std::uint8_t hid) const noexcept
{
    return pub_.verify(sig, sig_len, msg, msg_len, id, id_len, hid);
}

} // namespace sm9

#endif