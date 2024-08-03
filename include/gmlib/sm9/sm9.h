#ifndef SM9_SM9_H
#define SM9_SM9_H
#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/rng.h>
#include <gmlib/sm9/internal/sm9_alg.h>
#include <gmlib/sm9/internal/sm9_field.h>

#include <stdexcept>

namespace sm9 {

static constexpr std::uint8_t SM9_SIG_HID = 1;
static constexpr std::uint8_t SM9_ENC_HID = 3;

enum class SM9EcPC
{
    UNCOMPRESSED,
    COMPRESSED,
    MIX,
};

enum class SM9EncType
{
    SEQUENCE = 0,
    ECB      = 1,
    CBC      = 2,
    OFB      = 4,
    CFB      = 8,
};

template <class Hash>
class SM9SignMasterPrivateKey;

template <class Hash>
class SM9SignMasterPublicKey;

template <class Hash>
class SM9SignPrivateKey;

template <class Hash>
using SM9SignPublicKey = SM9SignMasterPublicKey<Hash>;

template <class Hash>
class SM9EncryptMasterPrivateKey;

template <class Hash>
class SM9EncryptMasterPublicKey;

template <class Hash>
class SM9EncryptPrivateKey;

template <class Hash>
using SM9EncryptPublicKey = SM9EncryptMasterPublicKey<Hash>;

// ======================================

template <class Hash>
class SM9SignMasterPrivateKey
{
    friend SM9SignMasterPublicKey<Hash>;
    friend SM9SignPrivateKey<Hash>;

private:
    /// @brief SM9 Sign Master Private Key Data
    std::uint8_t ks_[32];

    /// @brief SM9 Sign Public Key
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

template <class Hash>
class SM9EncryptMasterPrivateKey
{
    friend SM9EncryptMasterPublicKey<Hash>;
    friend SM9EncryptPrivateKey<Hash>;

private:
    /// @brief SM9 Encrypt Master Private Key Data
    std::uint8_t ke_[32];

    /// @brief SM9 Encrypt Public Key
    SM9EncryptMasterPublicKey<Hash> pub_;

public:
    /**
     * @brief   SM9 Encrypt Master Private Key Initialize
     * @note    need to call the "set_priv" or "gen_priv" function to Set Key
     */
    SM9EncryptMasterPrivateKey() noexcept = default;

    /**
     * @brief                   SM9 Encrypt Master Private Key Initialize and
     *                          Set
     * @param[in]   priv_key    private key data (32 bytes, big endian)
     */
    inline SM9EncryptMasterPrivateKey(const std::uint8_t priv_key[32]);

    /**
     * @brief               SM9 Encrypt Master Private Key Initialize and
     *                      Generate
     * @param[in]   rng     Random Number Generator
     */
    inline SM9EncryptMasterPrivateKey(rng::Rng& rng);

public:
    /**
     * @brief                   SM9 Encrypt Master Private Key Set
     * @param[in]   priv_key    private key data (32 bytes, big endian)
     */
    inline void set_priv(const std::uint8_t priv_key[32]);

    /**
     * @brief                   SM9 Encrypt Master Private Key Get
     * @param[out]  priv_key    private key data (32 bytes, big endian)
     */
    inline void get_priv(std::uint8_t priv_key[32]) const noexcept;

    /**
     * @brief               SM9 Encrypt Master Private Key Generate
     * @param[in]   rng     Random Number Generator
     */
    inline void gen_priv(rng::Rng& rng);

    /**
     * @brief               generate SM9 Encrypt Private Key
     * @param[in]   id      id
     * @param[in]   id_len  id length (in bytes)
     * @param[in]   hid     hid
     * @return              SM9 Encrypt Private Key
     */
    inline SM9EncryptPrivateKey<Hash> gen_EncryptPrivateKey(
        const std::uint8_t* id,
        std::size_t         id_len,
        std::uint8_t        hid = SM9_ENC_HID) const;

    /**
     * @brief   fetch SM9 Encrypt Public Key
     * @return  SM9 Encrypt Public Key const reference
     */
    inline const SM9EncryptPublicKey<Hash>& fetch_EncryptPublicKey()
        const noexcept;
};

template <class Hash>
class SM9EncryptMasterPublicKey
{
    friend SM9EncryptMasterPrivateKey<Hash>;
    friend SM9EncryptPrivateKey<Hash>;

private:
    /// @brief SM9 Encrypt Master PublicKey - Ppube
    internal::sm9_ec_a P_;

    /// @brief precompute data, e(Ppube, P2)
    internal::sm9_fp12_t e_Ppube_P2_;

public:
    /**
     * @brief   SM9 Encrypt Public Key Initialize
     * @note    need to call the "set_pub" function to Set Key
     */
    SM9EncryptMasterPublicKey() noexcept = default;

    /**
     * @brief           SM9 Encrypt Public Key Set
     * @param[in]   x   x coordinate of Public Key (32-bytes, big endian)
     * @param[in]   y   y coordinate of Public Key (32-bytes, big endian)
     */
    inline void set_pub(const std::uint8_t x[32], const std::uint8_t y[32]);

    /**
     * @brief           SM9 Encrypt Public Key Get
     * @param[out]  x   x coordinate of Public Key (32-bytes, big endian)
     * @param[out]  y   y coordinate of Public Key (32-bytes, big endian)
     */
    inline void get_pub(std::uint8_t x[32], std::uint8_t y[32]) const noexcept;

    /**
     * @brief                   SM9 calculate ciphertext length
     * @param[in]   plaintext   plaintext data
     * @param[in]   p_len       plaintext length (in bytes)
     * @return                  ciphertext length
     */
    static inline std::size_t ciphertext_len(const std::uint8_t* plaintext,
                                             std::size_t p_len) noexcept;

    inline void encrypt0(std::uint8_t*       out,
                         std::size_t*        outl,
                         const std::uint8_t* in,
                         std::size_t         inl,
                         const std::uint8_t* id,
                         std::size_t         id_len,
                         rng::Rng&           rng);
};

template <class Hash>
class SM9EncryptPrivateKey
{
    friend SM9EncryptMasterPrivateKey<Hash>;
    friend SM9EncryptPublicKey<Hash>;

private:
    /// @brief SM9 Private Key data
    internal::sm9_ec2_a priv_;

    /// @brief SM9 Encrypt Public Key
    SM9EncryptPublicKey<Hash> pub_;

public:
    /**
     * @brief   SM9 Encrypt Private Key Initialize
     * @note    need to call the "set_priv" function to Set Key
     */
    SM9EncryptPrivateKey() noexcept = default;

    /**
     * @brief   fetch SM9 Encrypt Public Key
     * @return  SM9 Sign Public Key const reference
     */
    inline const SM9EncryptPublicKey<Hash>& fetch_pub() const noexcept;

    /**
     * @brief               SM9 Encrypt Private Key Set
     * @param[in]   priv_x  x coordinate of Private Key (64-bytes, big endian)
     * @param[in]   priv_y  y coordinate of Private Key (64-bytes, big endian)
     * @param[in]   pub_x   x coordinate of Public Key (32-bytes, big endian)
     * @param[in]   pub_y   y coordinate of Public Key (32-bytes, big endian)
     */
    inline void set_priv(const std::uint8_t priv_x[64],
                         const std::uint8_t priv_y[64],
                         const std::uint8_t pub_x[32],
                         const std::uint8_t pub_y[32]);

    /**
     * @brief               SM9 Encrypt Private Key Get
     * @param[out]  priv_x  x coordinate of Private Key (64-bytes, big endian)
     * @param[out]  priv_y  y coordinate of Private Key (64-bytes, big endian)
     * @param[out]  pub_x   x coordinate of Public Key (32-bytes, big endian)
     * @param[out]  pub_y   y coordinate of Public Key (32-bytes, big endian)
     */
    inline void get_priv(std::uint8_t priv_x[64],
                         std::uint8_t priv_y[64],
                         std::uint8_t pub_x[32],
                         std::uint8_t pub_y[32]) const noexcept;

    /**
     * @brief                   SM9 calculate ciphertext length
     * @param[in]   plaintext   plaintext data
     * @param[in]   p_len       plaintext length (in bytes)
     * @return                  ciphertext length
     */
    static inline std::size_t ciphertext_len(const std::uint8_t* plaintext,
                                             std::size_t p_len) noexcept;

    /**
     * @brief                   SM9 calculate plaintext length
     * @param[in]   ciphertext  ciphertext data
     * @param[in]   c_len       ciphertext length (in bytes)
     * @return                  plaintext length (in bytes)
     */
    static inline std::size_t plaintext_len(const std::uint8_t* ciphertext,
                                            std::size_t         c_len);

    inline void encrypt0(std::uint8_t*       out,
                         std::size_t*        outl,
                         const std::uint8_t* in,
                         std::size_t         inl,
                         const std::uint8_t* id,
                         std::size_t         id_len,
                         rng::Rng&           rng);

    inline void decrypt0(std::uint8_t*       out,
                         std::size_t*        outl,
                         const std::uint8_t* in,
                         std::size_t         inl,
                         const std::uint8_t* id,
                         std::size_t         id_len);
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

template <class Hash>
inline SM9EncryptMasterPrivateKey<Hash>::SM9EncryptMasterPrivateKey(
    const std::uint8_t priv_key[32])
{
    this->set_priv(priv_key);
}

template <class Hash>
inline SM9EncryptMasterPrivateKey<Hash>::SM9EncryptMasterPrivateKey(
    rng::Rng& rng)
{
    this->gen_priv(rng);
}

template <class Hash>
inline void SM9EncryptMasterPrivateKey<Hash>::set_priv(
    const std::uint8_t priv_key[32])
{
    // check ke in [1, N-1]
    internal::sm9_bn_t ke, N;
    internal::sm9_bn_from_bytes(ke, priv_key);
    internal::sm9_bn_from_bytes(N, internal::SM9_CURVE_N);
    if (internal::sm9_bn_equal_zero(ke) || internal::sm9_bn_cmp(ke, N) >= 0)
    {
        throw std::runtime_error("invalid sm9 priv key");
    }
    // set priv and pub
    std::memcpy(ke_, priv_key, 32);
    internal::sm9_ec_j T;
    internal::sm9_ec_j_mul_g(T, ke_); // never inf
    internal::sm9_ec_j_to_a(pub_.P_, T);
    internal::sm9_pairing_P_P2(pub_.e_Ppube_P2_, pub_.P_);
}

template <class Hash>
inline void SM9EncryptMasterPrivateKey<Hash>::get_priv(
    std::uint8_t priv_key[32]) const noexcept
{
    std::memcpy(priv_key, ke_, 32);
}

template <class Hash>
inline void SM9EncryptMasterPrivateKey<Hash>::gen_priv(rng::Rng& rng)
{
    std::uint8_t priv_key[32];
    // gen priv_key, [1, N-1]
    internal::sm9_bn_t d;
    rng.gen(priv_key, 32);
    internal::sm9_bn_from_bytes(d, priv_key);
    internal::sm9_bn_mod_n_sub1(d);
    internal::sm9_bn_add_uint32(d, d, 1);
    internal::sm9_bn_to_bytes(ke_, d);
    // set pub
    internal::sm9_ec_j dG;
    internal::sm9_ec_j_mul_g(dG, ke_); // never inf
    internal::sm9_ec_j_to_a(pub_.P_, dG);
    internal::sm9_pairing_P_P2(pub_.e_Ppube_P2_, pub_.P_);
}

template <class Hash>
inline SM9EncryptPrivateKey<Hash>
SM9EncryptMasterPrivateKey<Hash>::gen_EncryptPrivateKey(const std::uint8_t* id,
                                                        std::size_t  id_len,
                                                        std::uint8_t hid) const
{
    internal::sm9_fn_t         t1, ke;
    std::uint8_t               t2_buf[32];
    std::uint8_t*              t1_buf = t2_buf;
    SM9EncryptPrivateKey<Hash> enc_priv;
    internal::sm9_ec2_j        t2P2;
    // t1 = H1(ID || hid, N) + ke
    internal::sm9_fn_from_bytes(ke, ke_);
    internal::sm9_Hn<Hash>(t1_buf, id, id_len, &hid, 1, 1);
    internal::sm9_fn_from_bytes(t1, t1_buf);
    internal::sm9_fn_add(t1, t1, ke);
    if (internal::sm9_fn_equal_zero(t1))
    {
        throw std::runtime_error(
            "err in generate EncryptPrivateKey for ID, "
            "please re-gen SM9EncryptMasterPrivateKey, and try again");
    }
    // t2 = ke * t1^-1
    internal::sm9_fn_inv(t1, t1);
    internal::sm9_fn_mul(t1, ke, t1);
    internal::sm9_fn_to_bytes(t2_buf, t1);
    // dsa = [t2]P2
    internal::sm9_ec2_j_mul_g(t2P2, t2_buf);
    internal::sm9_ec2_j_to_a(enc_priv.priv_, t2P2);
    // copy pub
    enc_priv.pub_ = pub_;
    return enc_priv;
}

template <class Hash>
inline const SM9EncryptPublicKey<Hash>&
SM9EncryptMasterPrivateKey<Hash>::fetch_EncryptPublicKey() const noexcept
{
    return this->pub_;
}

template <class Hash>
inline void SM9EncryptMasterPublicKey<Hash>::set_pub(const std::uint8_t x[32],
                                                     const std::uint8_t y[32])
{
    internal::sm9_ec_a T;
    internal::sm9_fp_from_bytes(T[0], x);
    internal::sm9_fp_from_bytes(T[1], y);
    if (!internal::sm9_ec_a_check(T))
    {
        throw std::runtime_error("invalid sm9 EncryptPublicKey");
    }
    internal::sm9_ec_a_cpy(P_, T);
    internal::sm9_pairing_P_P2(e_Ppube_P2_, P_);
}

template <class Hash>
inline void SM9EncryptMasterPublicKey<Hash>::get_pub(
    std::uint8_t x[32],
    std::uint8_t y[32]) const noexcept
{
    internal::sm9_fp_to_bytes(x, P_[0]);
    internal::sm9_fp_to_bytes(y, P_[1]);
}

template <class Hash>
inline std::size_t SM9EncryptMasterPublicKey<Hash>::ciphertext_len(
    const std::uint8_t* plaintext,
    std::size_t         p_len) noexcept
{
    return 64 + Hash::DIGEST_SIZE + p_len;
}

template <class Hash>
inline void SM9EncryptMasterPublicKey<Hash>::encrypt0( //
    std::uint8_t*       out,
    std::size_t*        outl,
    const std::uint8_t* in,
    std::size_t         inl,
    const std::uint8_t* id,
    std::size_t         id_len,
    rng::Rng&           rng)
{
    internal::SM9Kdf<Hash> kdf_ctx;
    Hash                   hash_ctx;
    internal::sm9_num_t    r;
    internal::sm9_ec_j     Qb;
    internal::sm9_ec_t     C1;
    internal::sm9_fp12_t   w;
    std::uint8_t           w_buf[384];
    std::uint8_t           k2_buf[32];

    std::uint8_t* r_buf  = w_buf;
    std::uint8_t* h_buf  = w_buf;
    std::uint8_t* C1_ptr = out;
    std::uint8_t* C3_ptr = C1_ptr + 64;
    std::uint8_t* C2_ptr = C3_ptr + Hash::DIGEST_SIZE;

    // QB = [H1(ID || hid, N)]P1 + Ppube
    internal::sm9_Hn<Hash>(h_buf, id, id_len, &SM9_ENC_HID, 1, 1);
    internal::sm9_ec_j_mul_g(Qb, h_buf);
    internal::sm9_ec_j_add_a(Qb, Qb, P_);
retry:
    // r = [1, N-1]
    rng.gen(r_buf, 32);
    internal::sm9_bn_from_bytes(r.bn, r_buf);
    internal::sm9_bn_mod_n_sub1(r.bn);
    internal::sm9_bn_add_uint32(r.bn, r.bn, 1);
    internal::sm9_bn_to_bytes(r_buf, r.bn);
    // C1 = [r]QB
    internal::sm9_ec_j_mul_j(C1.j, r_buf, Qb);
    internal::sm9_ec_j_to_a(C1.a, C1.j);
    internal::sm9_ec_a_to_bytes04(C1_ptr, C1.a);
    // w = g^r, g = e(Ppube, P2)
    internal::sm9_fp12_pow(w, e_Ppube_P2_, r_buf);
    internal::sm9_fp12_to_bytes(w_buf, w);
    // K = KDF(C1 || w || ID, klen), klen = inl + 32
    // C2 = K1 xor M
    kdf_ctx.update_z(C1_ptr, 64);
    kdf_ctx.update_z(w_buf, sizeof(w_buf));
    kdf_ctx.update_z(id, id_len);
    kdf_ctx.gen_keystream_and_xor(C2_ptr, in, inl);
    kdf_ctx.gen_keystream(k2_buf, sizeof(k2_buf));
    if (kdf_ctx.all_zero_check())
    {
        goto retry;
    }
    // C3 = MAC(K2, C2) = HASH(C2 || K2)
    hash_ctx.reset();
    hash_ctx.update(C2_ptr, inl);
    hash_ctx.update(k2_buf, sizeof(k2_buf));
    hash_ctx.do_final(C3_ptr);

    *outl = 64 + Hash::DIGEST_SIZE + inl;
}

template <class Hash>
inline const SM9EncryptPublicKey<Hash>& SM9EncryptPrivateKey<Hash>::fetch_pub()
    const noexcept
{
    return pub_;
}

template <class Hash>
inline void SM9EncryptPrivateKey<Hash>::set_priv(const std::uint8_t priv_x[64],
                                                 const std::uint8_t priv_y[64],
                                                 const std::uint8_t pub_x[32],
                                                 const std::uint8_t pub_y[32])
{
    internal::sm9_ec2_a T;
    internal::sm9_fp2_from_bytes(T[0], priv_x);
    internal::sm9_fp2_from_bytes(T[1], priv_y);
    if (!internal::sm9_ec2_a_check(T))
    {
        throw std::runtime_error("invalid sm9 EncryptPrivateKey");
    }
    internal::sm9_ec2_a_cpy(priv_, T);

    pub_.set_pub(pub_x, pub_y);
}

template <class Hash>
inline void SM9EncryptPrivateKey<Hash>::get_priv(
    std::uint8_t priv_x[64],
    std::uint8_t priv_y[64],
    std::uint8_t pub_x[32],
    std::uint8_t pub_y[32]) const noexcept
{
    internal::sm9_fp2_to_bytes(priv_x, priv_[0]);
    internal::sm9_fp2_to_bytes(priv_y, priv_[1]);
    pub_.get_pub(pub_x, pub_y);
}

template <class Hash>
inline std::size_t SM9EncryptPrivateKey<Hash>::ciphertext_len(
    const std::uint8_t* plaintext,
    std::size_t         p_len) noexcept
{
    return SM9EncryptMasterPublicKey<Hash>::ciphertext_len(plaintext, p_len);
}

template <class Hash>
inline std::size_t SM9EncryptPrivateKey<Hash>::plaintext_len(
    const std::uint8_t* ciphertext,
    std::size_t         c_len)
{
    if (c_len < 64 + Hash::DIGEST_SIZE)
    {
        throw std::runtime_error("invalid SM9 ciphertext");
    }
    return c_len - 64 - Hash::DIGEST_SIZE;
}

template <class Hash>
inline void SM9EncryptPrivateKey<Hash>::encrypt0(std::uint8_t*       out,
                                                 std::size_t*        outl,
                                                 const std::uint8_t* in,
                                                 std::size_t         inl,
                                                 const std::uint8_t* id,
                                                 std::size_t         id_len,
                                                 rng::Rng&           rng)
{
    return pub_.encrypt0(out, outl, in, inl, id, id_len, rng);
}

template <class Hash>
inline void SM9EncryptPrivateKey<Hash>::decrypt0(std::uint8_t*       out,
                                                 std::size_t*        outl,
                                                 const std::uint8_t* in,
                                                 std::size_t         inl,
                                                 const std::uint8_t* id,
                                                 std::size_t         id_len)
{
    Hash                   hash_ctx;
    internal::SM9Kdf<Hash> kdf_ctx;
    internal::sm9_ec_a     C1;
    internal::sm9_fp12_t   w;
    std::uint8_t           w_buf[384];
    std::uint8_t           k2_buf[32];

    const std::uint8_t* C1_ptr = in;
    const std::uint8_t* C3_ptr = C1_ptr + 64;
    const std::uint8_t* C2_ptr = C3_ptr + Hash::DIGEST_SIZE;
    std::size_t         C2_len;
    std::uint8_t*       C3_buf = k2_buf;

    if (inl < 64 + Hash::DIGEST_SIZE)
    {
        throw std::runtime_error("invalid SM9 Ciphertext");
    }
    C2_len = inl - 64 - Hash::DIGEST_SIZE;

    internal::sm9_ec_a_from_bytes04(C1, C1_ptr);
    if (!internal::sm9_ec_a_check(C1))
    {
        throw std::runtime_error("invalid SM9 Ciphertext");
    }
    // w = e(C1, de)
    internal::sm9_pairing(w, C1, priv_);
    internal::sm9_fp12_to_bytes(w_buf, w);
    // K = KDF(C1 || w || ID, klen), klen = inl + 32
    // C2 = K1 xor M
    kdf_ctx.update_z(C1_ptr, 64);
    kdf_ctx.update_z(w_buf, sizeof(w_buf));
    kdf_ctx.update_z(id, id_len);
    kdf_ctx.gen_keystream_and_xor(out, C2_ptr, C2_len);
    kdf_ctx.gen_keystream(k2_buf, sizeof(k2_buf));
    if (kdf_ctx.all_zero_check())
    {
        throw std::runtime_error("invalid SM9 Ciphertext");
    }
    // C3 = MAC(K2, C2) = HASH(C2 || K2)
    hash_ctx.update(C2_ptr, C2_len);
    hash_ctx.update(k2_buf, sizeof(k2_buf));
    hash_ctx.do_final(C3_buf);
    if (std::memcmp(C3_buf, C3_ptr, Hash::DIGEST_SIZE) != 0)
    {
        throw std::runtime_error("invalid SM9 Ciphertext");
    }

    *outl = C2_len;
}

} // namespace sm9

#endif