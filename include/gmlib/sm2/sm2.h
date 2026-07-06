#ifndef SM2_SM2_H
#define SM2_SM2_H

#include <gmlib/hash_lib/hash.h>
#include <gmlib/rng/rng.h>
#include <gmlib/sm2/internal/sm2_alg.h>
#include <gmlib/sm2/internal/sm2_const.h>

#include <cstring>
#include <functional>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace sm2 {

enum class SM2EcPC : std::uint8_t
{
    UNCOMPRESSED,
    COMPRESSED,
    MIX,
};

template <class Hash>
class SM2PrivateKey;

template <class Hash>
class SM2PublicKey
{
    friend class SM2PrivateKey<Hash>;

public:
    static constexpr std::size_t SIG_SIZE = 64;

private:
    std::uint8_t x_[32], y_[32];

public:
    SM2PublicKey() = default;

    inline SM2PublicKey(const std::uint8_t x[32], const std::uint8_t y[32])
    {
        this->set_pub(x, y);
    }

    ~SM2PublicKey()
    {
        std::memset(x_, 0, sizeof(x_));
        std::memset(y_, 0, sizeof(y_));
    }

public:
    inline void set_pub(const std::uint8_t x[32], const std::uint8_t y[32])
    {
        internal::sm2_set_public_key(x_, y_, x, y);
    }

    inline void get_pub(std::uint8_t x[32], std::uint8_t y[32]) const noexcept
    {
        internal::sm2_get_public_key(x, y, x_, y_);
    }

public:
    inline bool verify(const std::uint8_t  sig_rs[64],
                       const std::uint8_t* msg,
                       std::size_t         msg_len,
                       const std::uint8_t* id = internal::SM2_DEFAULT_ID,
                       std::size_t id_len = internal::SM2_DEFAULT_ID_LEN) const
    {
        Hash hash;
        return internal::sm2_verify( //
            sig_rs, sig_rs + 32,     //
            msg, msg_len,            //
            id, id_len,              //
            x_,                      //
            y_,                      //
            hash                     //
        );                           //
    }

    inline std::size_t ciphertext_len(const std::uint8_t* plaintext,
                                      std::size_t         plaintext_len,
                                      SM2EcPC pc = SM2EcPC::UNCOMPRESSED) const
    {
        (void)plaintext;
        return internal::sm2_ciphertext_len( //
            plaintext_len,                   //
            Hash::DIGEST_SIZE,               //
            pc                               //
        );                                   //
    }

    inline void encrypt(std::uint8_t*       ciphertext,
                        std::size_t*        ciphertext_len,
                        const std::uint8_t* plaintext,
                        std::size_t         plaintext_len,
                        rng::Rng&           rng,
                        SM2EcPC             pc = SM2EcPC::UNCOMPRESSED) const
    {
        Hash hash;
        internal::sm2_encrypt(ciphertext, ciphertext_len, //
                              plaintext, plaintext_len,   //
                              rng,                        //
                              pc,                         //
                              x_,                         //
                              y_,                         //
                              hash                        //
        );                                                //
    }
};

template <class Hash>
class SM2PrivateKey
{
    friend class SM2PublicKey<Hash>;

public:
    static constexpr std::size_t SIG_SIZE = 64;

private:
    std::uint8_t       priv_[32];
    SM2PublicKey<Hash> pub_;

public:
    SM2PrivateKey() = default;

    inline SM2PrivateKey(const std::uint8_t private_key[32])
    {
        this->set_priv(private_key);
    }

    inline SM2PrivateKey(rng::Rng& rng)
    {
        this->gen_priv(rng);
    }

    ~SM2PrivateKey()
    {
        std::memset(priv_, 0, sizeof(priv_));
    }

public:
    inline void set_priv(const std::uint8_t private_key[32])
    {
        internal::sm2_set_private_key(priv_, pub_.x_, pub_.y_, private_key);
    }

    inline void set_priv_and_pub(const std::uint8_t private_key[32],
                                 const std::uint8_t pub_x[32],
                                 const std::uint8_t pub_y[32]) noexcept
    {
        internal::sm2_set_private_key_and_public_key( //
            priv_, pub_.x_, pub_.y_,                  //
            private_key, pub_x, pub_y                 //
        );                                            //
    }

    inline void get_priv(std::uint8_t private_key[32]) const noexcept
    {
        internal::sm2_get_private_key(private_key, priv_);
    }

    inline void get_priv_and_pub(std::uint8_t private_key[32],
                                 std::uint8_t pub_x[32],
                                 std::uint8_t pub_y[32]) const noexcept
    {
        internal::sm2_get_private_key_and_public_key( //
            private_key, pub_x, pub_y,                //
            priv_, pub_.x_, pub_.y_                   //
        );                                            //
    }

    inline void gen_priv(rng::Rng& rng)
    {
        internal::sm2_generate_private_key(priv_, pub_.x_, pub_.y_, rng);
    }

    inline const SM2PublicKey<Hash>& fetch_pub() const noexcept
    {
        return pub_;
    }

public:
    inline void sign(std::uint8_t        sig_rs[64],
                     const std::uint8_t* msg,
                     std::size_t         msg_len,
                     rng::Rng&           rng,
                     const std::uint8_t* id = internal::SM2_DEFAULT_ID,
                     std::size_t id_len = internal::SM2_DEFAULT_ID_LEN) const
    {
        Hash hash;
        internal::sm2_sign(sig_rs, sig_rs + 32, //
                           msg, msg_len,        //
                           rng,                 //
                           id, id_len,          //
                           priv_,               //
                           pub_.x_,             //
                           pub_.y_,             //
                           hash                 //
        );                                      //
    }

    inline bool verify(const std::uint8_t  sig_rs[64],
                       const std::uint8_t* msg,
                       std::size_t         msg_len,
                       const std::uint8_t* id = internal::SM2_DEFAULT_ID,
                       std::size_t id_len = internal::SM2_DEFAULT_ID_LEN) const
    {
        return pub_.verify(sig_rs, msg, msg_len, id, id_len);
    }

    inline std::size_t ciphertext_len(const std::uint8_t* plaintext,
                                      std::size_t         plaintext_len,
                                      SM2EcPC pc = SM2EcPC::UNCOMPRESSED) const
    {
        return pub_.ciphertext_len(plaintext, plaintext_len, pc);
    }

    inline void encrypt(std::uint8_t*       ciphertext,
                        std::size_t*        ciphertext_len,
                        const std::uint8_t* plaintext,
                        std::size_t         plaintext_len,
                        rng::Rng&           rng,
                        SM2EcPC             pc = SM2EcPC::UNCOMPRESSED) const
    {
        pub_.encrypt(ciphertext, ciphertext_len, //
                     plaintext, plaintext_len,   //
                     rng,                        //
                     pc                          //
        );                                       //
    }

    inline std::size_t plaintext_len(const std::uint8_t* ciphertext,
                                     std::size_t         ciphertext_len) const
    {
        return internal::sm2_plaintext_len( //
            ciphertext, ciphertext_len,     //
            Hash::DIGEST_SIZE               //
        );                                  //
    }

    inline void decrypt(std::uint8_t*       plaintext,
                        std::size_t*        plaintext_len,
                        const std::uint8_t* ciphertext,
                        std::size_t         ciphertext_len) const
    {
        Hash hash;
        internal::sm2_decrypt(plaintext, plaintext_len,   //
                              ciphertext, ciphertext_len, //
                              priv_,                      //
                              hash                        //
        );                                                //
    }
};

} // namespace sm2

#endif
