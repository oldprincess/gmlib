#ifndef _GMLIB_CRYPTO_PKC_SM2_CIPHER_H
#define _GMLIB_CRYPTO_PKC_SM2_CIPHER_H

#include <TinyCrypto/pkc/sm2/sm2p256v1.h>
#include <gmlib/crypto/rng/RngCipher.h>
#include <gmlib/exception.h>

namespace gmlib {

namespace Sm2Utils {

template <class Hash>
void sm2_compute_z(uint8_t*       z,
                   const uint8_t* id,
                   size_t         id_len,
                   const uint8_t  x[32],
                   const uint8_t  y[32])
{
    if (id_len * 8 > UINT16_MAX)
    {
        throw gmlib::Exception("SM2 ID length too long");
    }
    uint8_t  ENTL[2];
    uint16_t entl_len = (uint16_t)(id_len * 8);
    ENTL[0]           = entl_len >> 8;
    ENTL[1]           = entl_len & 0xFF;
    auto hash         = Hash();
    hash.update(ENTL, 2);
    hash.update(id, id_len);
    hash.update(tc::sm2p256v1::SM2_CURVE_A, 32);
    hash.update(tc::sm2p256v1::SM2_CURVE_B, 32);
    hash.update(tc::sm2p256v1::SM2_CURVE_GX, 32);
    hash.update(tc::sm2p256v1::SM2_CURVE_GY, 32);
    hash.update(x, 32);
    hash.update(y, 32);
    hash.final(z);
}

} // namespace Sm2Utils

class Sm2PrivateKey;
class Sm2PublicKey;

template <class Hash>
class Sm2Sig
{
    friend Sm2PrivateKey;
    friend Sm2PublicKey;

private:
    uint8_t r[32], s[32];

public:
    const uint8_t* get_r() noexcept
    {
        return this->r;
    }

    const uint8_t* get_s() noexcept
    {
        return this->s;
    }
};

class Sm2PublicKey
{
    friend Sm2PrivateKey;

private:
    uint8_t x[32], y[32];

public:
    const uint8_t* get_x() noexcept
    {
        return this->x;
    }

    const uint8_t* get_y() noexcept
    {
        return this->y;
    }

public:
    template <class Hash>
    bool verify(const Sm2Sig<Hash>& sig,
                const uint8_t*      msg,
                size_t              msg_len,
                const uint8_t*      id     = tc::sm2p256v1::SM2_DEFAULT_ID,
                size_t              id_len = tc::sm2p256v1::SM2_DEFAULT_ID_LEN)
    {
        uint8_t Z[Hash::DIGEST_SIZE];
        uint8_t _t[32];

        tc::sm2p256v1::sm2_num_t e, r, s, tmp;
        tc::sm2p256v1::sm2_ec_t  sG, tP;

        // r' in [1,n-1]?, s' in [1,n-1]?
        tc::sm2p256v1::sm2_bn_from_bytes(r.bn, sig.r);
        tc::sm2p256v1::sm2_bn_from_bytes(s.bn, sig.s);
        tc::sm2p256v1::sm2_bn_from_bytes(tmp.bn, tc::sm2p256v1::SM2_CURVE_N);
        if (tc::sm2p256v1::sm2_bn_equal_zero(r.bn) ||
            tc::sm2p256v1::sm2_bn_cmp(r.bn, tmp.bn) >= 0 ||
            tc::sm2p256v1::sm2_bn_equal_zero(s.bn) ||
            tc::sm2p256v1::sm2_bn_cmp(s.bn, tmp.bn) >= 0)
        {
            return false;
        }
        // H(Z || M)
        Sm2Utils::sm2_compute_z<Hash>(Z, id, id_len, this->x, this->y);
        auto hash = Hash();
        hash.update(Z, Hash::DIGEST_SIZE);
        hash.update(msg, msg_len);
        hash.final(Z);
        // t = r' + s' mod n
        tc::sm2p256v1::sm2_fn_from_bytes(r.fn, sig.r);
        tc::sm2p256v1::sm2_fn_from_bytes(s.fn, sig.s);
        tc::sm2p256v1::sm2_fn_add(tmp.fn, r.fn, s.fn);
        if (tc::sm2p256v1::sm2_fn_equal_zero(tmp.fn))
        {
            return false;
        }
        tc::sm2p256v1::sm2_fn_to_bytes(_t, tmp.fn);
        // x1', y1' = [s']G + [t]P
        tc::sm2p256v1::sm2_fp_from_bytes(tP.a[0], this->x);
        tc::sm2p256v1::sm2_fp_from_bytes(tP.a[1], this->y);
        tc::sm2p256v1::sm2_ec_j_mul_g(sG.j, sig.s);
        tc::sm2p256v1::sm2_ec_j_mul_a(tP.j, _t, tP.a);
        tc::sm2p256v1::sm2_ec_j_add(tP.j, sG.j, tP.j);
        tc::sm2p256v1::sm2_ec_j_normal(tP.a, tP.j);
        // R = e' + x1' mod n
        tc::sm2p256v1::sm2_fn_from_fp(tmp.fn, tP.a[0]);
        tc::sm2p256v1::sm2_fn_from_bytes_ex(e.fn, Z, Hash::DIGEST_SIZE);
        tc::sm2p256v1::sm2_fn_add(tmp.fn, e.fn, tmp.fn);
        if (tc::sm2p256v1::sm2_fn_equal(tmp.fn, r.fn))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

// SM2PrivateKey ::= INTEGER
class Sm2PrivateKey
{
private:
    uint8_t      d[32];
    Sm2PublicKey pub;

public:
    static Sm2PrivateKey gen(RngCipher* rng)
    {
        uint8_t _d[32];

        tc::sm2p256v1::sm2_num_t d;
        // d = [1, n-2]
        rng->gen(_d, 32);
        tc::sm2p256v1::sm2_bn_from_bytes(d.bn, _d);
        tc::sm2p256v1::sm2_bn_mod_n_sub3(d.bn);
        tc::sm2p256v1::sm2_bn_add_uint32(d.bn, d.bn, 1);
        tc::sm2p256v1::sm2_bn_to_bytes(_d, d.bn);

        Sm2PrivateKey priv;
        priv.set_key(_d);
        return priv;
    }

public:
    /**
     * @brief       Sm2 set PrivateKey, auto set PublicKey
     * @param d     Integer as bytes, [1, n-2]
     */
    void set_key(const uint8_t d[32]) noexcept
    {
        memcpy(this->d, d, 32);
        tc::sm2p256v1::sm2_ec_t dG;
        tc::sm2p256v1::sm2_ec_j_mul_g(dG.j, d);
        if (tc::sm2p256v1::sm2_ec_j_is_inf(dG.j))
        {
            std::terminate();
        }
        tc::sm2p256v1::sm2_ec_j_to_a(dG.a, dG.j);
        tc::sm2p256v1::sm2_fp_to_bytes(this->pub.x, dG.a[0]);
        tc::sm2p256v1::sm2_fp_to_bytes(this->pub.y, dG.a[1]);
    }

public:
    const uint8_t* get_d() noexcept
    {
        return this->d;
    }

    const Sm2PublicKey& fetch_pub() noexcept
    {
        return this->pub;
    }

    const uint8_t* get_pub_x() noexcept
    {
        return this->pub.get_x();
    }

    const uint8_t* get_pub_y() noexcept
    {
        return this->pub.get_y();
    }

public:
    template <class Hash>
    Sm2Sig<Hash> sign(const uint8_t* msg,
                      size_t         msg_len,
                      RngCipher*     rng,
                      const uint8_t* id     = tc::sm2p256v1::SM2_DEFAULT_ID,
                      size_t         id_len = tc::sm2p256v1::SM2_DEFAULT_ID_LEN)
    {
        uint8_t                   Z[Hash::DIGEST_SIZE];
        tc::sm2p256v1::sm2_num_t  e, r, s, da, k;
        tc::sm2p256v1::sm2_ec_t   kG;
        tc::sm2p256v1::sm2_num_t& tmp = e;

        uint8_t _k[32];
        Sm2Utils::sm2_compute_z<Hash>(Z, id, id_len, this->pub.x, this->pub.y);

        auto hash = Hash();
        hash.update(Z, Hash::DIGEST_SIZE);
        hash.update(msg, msg_len);
        hash.final(Z);

    retry:
        // k = random[1, n-1]
        rng->gen(_k, 32);
        tc::sm2p256v1::sm2_bn_from_bytes(k.bn, _k);
        tc::sm2p256v1::sm2_bn_mod_n_sub2(k.bn);
        tc::sm2p256v1::sm2_bn_add_uint32(k.bn, k.bn, 1);
        tc::sm2p256v1::sm2_bn_to_bytes(_k, k.bn);
        // x1,y1 = [k]G
        tc::sm2p256v1::sm2_ec_j_mul_g(kG.j, _k);
        tc::sm2p256v1::sm2_ec_j_to_a(kG.a, kG.j);
        // r = e + x1 mod n
        tc::sm2p256v1::sm2_fn_from_bytes_ex(e.fn, Z, Hash::DIGEST_SIZE);
        tc::sm2p256v1::sm2_fn_from_fp(r.fn, kG.a[0]);
        tc::sm2p256v1::sm2_fn_add(r.fn, e.fn, r.fn);
        // if r=0 or r+k=n, retry
        tc::sm2p256v1::sm2_fn_from_bytes(k.fn, _k);
        tc::sm2p256v1::sm2_fn_add(tmp.fn, r.fn, k.fn);
        if (tc::sm2p256v1::sm2_fn_equal_zero(r.fn) ||
            tc::sm2p256v1::sm2_fn_equal_zero(tmp.fn))
        {
            goto retry;
        }
        // s = (1+da)^-1 * (k - r * da) mod n
        tc::sm2p256v1::sm2_fn_from_bytes(da.fn, this->d);
        tc::sm2p256v1::sm2_fn_set_one(s.fn);
        tc::sm2p256v1::sm2_fn_add(s.fn, s.fn, da.fn);
        tc::sm2p256v1::sm2_fn_inv(s.fn, s.fn);
        tc::sm2p256v1::sm2_fn_mul(tmp.fn, r.fn, da.fn);
        tc::sm2p256v1::sm2_fn_sub(k.fn, k.fn, tmp.fn);
        tc::sm2p256v1::sm2_fn_mul(s.fn, s.fn, k.fn);
        if (tc::sm2p256v1::sm2_fn_equal_zero(s.fn))
        {
            goto retry;
        }
        //
        Sm2Sig<Hash> sig;
        tc::sm2p256v1::sm2_fn_to_bytes(sig.r, r.fn);
        tc::sm2p256v1::sm2_fn_to_bytes(sig.s, s.fn);
        return sig;
    }

    template <class Hash>
    bool verify(const Sm2Sig<Hash>& sig,
                const uint8_t*      msg,
                size_t              msg_len,
                const uint8_t*      id     = tc::sm2p256v1::SM2_DEFAULT_ID,
                size_t              id_len = tc::sm2p256v1::SM2_DEFAULT_ID_LEN)
    {
        return this->pub.verify(sig, msg, msg_len, id, id_len);
    }
};

} // namespace gmlib

#endif