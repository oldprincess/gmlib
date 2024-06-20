#ifndef BLOCK_CIPHER_MODE_GCM_MODE_H
#define BLOCK_CIPHER_MODE_GCM_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/block_cipher_mode/internal/gctr_inc.h>
#include <gmlib/ghash/ghash.h>
#include <gmlib/memory_utils/memxor.h>

namespace block_cipher_mode {

template <class Cipher>
class GctrCryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");
    static_assert(Cipher::BLOCK_SIZE == 16, "gctr need BLOCK_SIZE=16");

public:
    static constexpr std::size_t BLOCK_SIZE   = Cipher::BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

protected:
    Cipher       cipher_;
    std::uint8_t tag_[16];
    std::uint8_t counter_[16];
    std::uint8_t counter0_[16];

public:
    GctrCryptor() = default;

    GctrCryptor(const std::uint8_t* user_key,
                const std::uint8_t* iv,
                std::size_t         iv_len,
                ghash::GHash&       hash)
    {
        this->init(user_key, iv, iv_len, hash);
    }

protected:
    const std::uint8_t* get_counter0() const noexcept
    {
        return counter0_;
    }

public:
    void init(const std::uint8_t* user_key,
              const std::uint8_t* iv,
              std::size_t         iv_len,
              ghash::GHash&       hash)
    {
        static const std::uint8_t ZERO[16] = {0};
        std::uint8_t              t[16];

        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        cipher_.encrypt_block(t, ZERO);
        hash.set_key(t);
        // init counter
        if (iv_len == 12)
        {
            std::memcpy(counter0_, iv, 12);
            counter0_[12] = 0, counter0_[13] = 0;
            counter0_[14] = 0, counter0_[15] = 1;
        }
        else
        {
            // H(IV || 0(s+64) || ivlen(64) )
            hash.update(iv, iv_len);
            hash.update(ZERO, (16 - (iv_len % 16)) % 16);
            memory_utils::store64_be(t + 0, 0);
            memory_utils::store64_be(t + 8, iv_len * 8);
            hash.update(t, 16);
            hash.do_final(counter0_);
            hash.reset();
        }
        internal::gctr_inc(counter_, counter0_);
    }

    void reset(const std::uint8_t* iv, std::size_t iv_len, ghash::GHash& hash)
    {
        static const std::uint8_t ZERO[16] = {0};
        std::uint8_t              t[16];

        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
        hash.reset();
        // init counter
        if (iv_len == 12)
        {
            std::memcpy(counter0_, iv, 12);
            counter0_[12] = 0, counter0_[13] = 0;
            counter0_[14] = 0, counter0_[15] = 1;
        }
        else
        {
            // H(IV || 0(s+64) || ivlen(64) )
            hash.update(iv, iv_len);
            hash.update(ZERO, (16 - (iv_len % 16)) % 16);
            memory_utils::store64_be(t + 0, 0);
            memory_utils::store64_be(t + 8, iv_len * 8);
            hash.update(t, 16);
            hash.do_final(counter0_);
            hash.reset();
        }
        internal::gctr_inc(counter_, counter0_);
    }

private:
    void gen_block_key_stream(std::uint8_t* out, std::size_t block_num)
    {
        if (block_num == 0)
        {
            return;
        }
        // generate counter
        std::uint8_t* cur_counter = out;
        std::memcpy(cur_counter, counter_, 16);
        for (std::size_t i = 1; i < block_num; i++)
        {
            std::uint8_t* nxt_counter = cur_counter + 16;
            internal::gctr_inc(nxt_counter, cur_counter);
            cur_counter = nxt_counter;
        }
        internal::gctr_inc(counter_, cur_counter);
        // generate key stream
        cipher_.encrypt_blocks(out, out, block_num);
    }

protected:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        if (block_num == 0)
        {
            return;
        }
        constexpr std::size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;

        std::uint8_t* base_out = out;
        // gctr
        std::uint8_t key_stream[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            this->gen_block_key_stream(key_stream, PARALLEL_NUM);
            memory_utils::memxor<PARALLEL_BYTES>(out, in, key_stream);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            std::size_t remain_bytes = block_num * BLOCK_SIZE;
            this->gen_block_key_stream(key_stream, block_num);
            memory_utils::memxor_n(out, in, key_stream, remain_bytes);
        }
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl != 0)
        {
            std::uint8_t key_stream[16];
            this->gen_block_key_stream(key_stream, 1);
            memory_utils::memxor_n(out, key_stream, in, inl);
        }
    }
};

template <class Cipher>
class GcmEncryptor : public GctrCryptor<Cipher>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");
    static_assert(Cipher::BLOCK_SIZE == 16, "gcm need BLOCK_SIZE=16");

public:
    static constexpr const char* NAME_SUFFIX = "/GCM-ENC";

    static constexpr std::size_t NAME_STR_LEN = Cipher::NAME_STR_LEN + 8;

    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        static char name[NAME_STR_LEN + 1] = {0};
        static bool inited                 = false;
        if (inited == false)
        {
            char* name_part1 = name;
            char* name_part2 = name + Cipher::NAME_STR_LEN;
            std::memcpy(name_part1, Cipher::NAME, Cipher::NAME_STR_LEN);
            std::memcpy(name_part2, NAME_SUFFIX,
                        NAME_STR_LEN - Cipher::NAME_STR_LEN);
            inited = true;
        }
        return name;
    }

    std::size_t fetch_name_str_len() const noexcept override
    {
        return NAME_STR_LEN;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

public:
    std::size_t init(const ConstParameter& params) override
    {
        const auto& item_user_key = params.find(ParamKey::USER_KEY);
        const auto& item_iv       = params.find(ParamKey::IV);
        const auto& item_aad      = params.find(ParamKey::AAD);

        const std::uint8_t* aad     = nullptr;
        std::size_t         aad_len = 0;

        std::size_t ret = 0;
        if (item_user_key == params.end())
        {
            throw std::runtime_error("init need user_key");
        }
        if (item_user_key->second.second != USER_KEY_LEN)
        {
            throw std::runtime_error("invalid user_key len");
        }
        if (item_iv == params.end())
        {
            throw std::runtime_error("init need iv");
        }
        if (item_aad != params.end())
        {
            aad     = static_cast<const std::uint8_t*>(item_aad->second.first);
            aad_len = item_aad->second.second;
            ret     = ret | ParamKey::AAD;
        }

        this->init(
            static_cast<const std::uint8_t*>(item_user_key->second.first), //
            static_cast<const std::uint8_t*>(item_iv->second.first),       //
            item_iv->second.second,                                        //
            aad,                                                           //
            aad_len                                                        //
        );
        return ParamKey::USER_KEY | ParamKey::IV | ret;
    }

    std::size_t get(const Parameter& params) override
    {
        const auto& item_tag = params.find(ParamKey::TAG);
        std::size_t ret      = 0;
        if (item_tag != params.end())
        {
            if (item_tag->second.second != sizeof(tag_))
            {
                throw std::runtime_error("gcm only support tag=16");
            }
            this->get_tag(static_cast<std::uint8_t*>(item_tag->second.first));
            ret = ret | ParamKey::TAG;
        }
        return ret;
    }

private:
    ghash::GHash  hash_;
    std::uint8_t  tag_[16];
    std::uint64_t ct_len_, aad_len_;

public:
    GcmEncryptor() = default;

    GcmEncryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 std::size_t         iv_len,
                 const std::uint8_t* aad,
                 std::size_t         aad_len)
    {
        this->init(user_key, iv, iv_len, aad, aad_len);
    }

public:
    void init(const std::uint8_t* user_key,
              const std::uint8_t* iv,
              std::size_t         iv_len,
              const std::uint8_t* aad,
              std::size_t         aad_len)
    {
        if (aad_len > UINT64_MAX / 8)
        {
            throw std::runtime_error(
                "additional authenticated data length too loog");
        }
        this->GctrCryptor<Cipher>::init(user_key, iv, iv_len, hash_);
        // gmac aad(additional authenticated data)
        static std::uint8_t ZERO[16] = {0};
        hash_.update(aad, aad_len);
        hash_.update(ZERO, (16 - (aad_len % 16)) % 16);
        aad_len_ = (std::uint64_t)aad_len;
        ct_len_  = 0;
        std::memset(tag_, 0, 16);
    }

    void reset(const std::uint8_t* iv,
               std::size_t         iv_len,
               const std::uint8_t* aad,
               std::size_t         aad_len)
    {
        if (aad_len > UINT64_MAX / 8)
        {
            throw std::runtime_error(
                "additional authenticated data length too loog");
        }
        this->GctrCryptor<Cipher>::reset(iv, iv_len, hash_);
        // gmac aad(additional authenticated data)
        static std::uint8_t ZERO[16] = {0};
        hash_.update(aad, aad_len);
        hash_.update(ZERO, (16 - (aad_len % 16)) % 16);
        aad_len_ = (std::uint64_t)aad_len;
        ct_len_  = 0;
        std::memset(tag_, 0, 16);
    }

    void get_tag(std::uint8_t tag[16]) const noexcept
    {
        std::memcpy(tag, tag_, 16);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        this->GctrCryptor<Cipher>::update_blocks(out, in, block_num);
        // gmac
        std::size_t outl       = block_num * Cipher::BLOCK_SIZE;
        std::size_t nxt_ct_len = ct_len_ + outl;
        if (nxt_ct_len < ct_len_ || (nxt_ct_len > UINT64_MAX / 8))
        {
            throw std::runtime_error("ciphertext too long");
        }
        ct_len_ = nxt_ct_len;
        hash_.update(out, outl);
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        static const std::uint8_t ZERO[16] = {0};
        if (inl)
        {
            this->GctrCryptor<Cipher>::final_block(out, in, inl);
            hash_.update(out, inl);
            hash_.update(ZERO, (16 - inl % 16) % 16);

            std::size_t nxt_ct_len = ct_len_ + inl;
            if (nxt_ct_len < ct_len_ || (nxt_ct_len > UINT64_MAX / 8))
            {
                throw std::runtime_error("ciphertext too long");
            }
            ct_len_ = nxt_ct_len;
        }
        std::uint8_t t[16];
        memory_utils::store64_be(t + 0, aad_len_ * 8);
        memory_utils::store64_be(t + 8, ct_len_ * 8);
        hash_.update(t, 16);
        hash_.do_final(tag_);
        this->GctrCryptor<Cipher>::cipher_.encrypt_block(
            t, this->GctrCryptor<Cipher>::get_counter0());
        memory_utils::memxor<16>(tag_, tag_, t);
    }
};

template <class Cipher>
class GcmDecryptor : public GctrCryptor<Cipher>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");
    static_assert(Cipher::BLOCK_SIZE == 16, "gcm need BLOCK_SIZE=16");

public:
    static constexpr const char* NAME_SUFFIX = "/GCM-DEC";

    static constexpr std::size_t NAME_STR_LEN = Cipher::NAME_STR_LEN + 8;

    static constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

    static constexpr std::size_t USER_KEY_LEN = Cipher::USER_KEY_LEN;

public:
    const char* fetch_name() const noexcept override
    {
        static char name[NAME_STR_LEN + 1] = {0};
        static bool inited                 = false;
        if (inited == false)
        {
            char* name_part1 = name;
            char* name_part2 = name + Cipher::NAME_STR_LEN;
            std::memcpy(name_part1, Cipher::NAME, Cipher::NAME_STR_LEN);
            std::memcpy(name_part2, NAME_SUFFIX,
                        NAME_STR_LEN - Cipher::NAME_STR_LEN);
            inited = true;
        }
        return name;
    }

    std::size_t fetch_name_str_len() const noexcept override
    {
        return NAME_STR_LEN;
    }

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

public:
    std::size_t init(const ConstParameter& params) override
    {
        const auto& item_user_key = params.find(ParamKey::USER_KEY);
        const auto& item_iv       = params.find(ParamKey::IV);
        const auto& item_aad      = params.find(ParamKey::AAD);
        const auto& item_tag      = params.find(ParamKey::TAG);

        const std::uint8_t* aad     = nullptr;
        std::size_t         aad_len = 0;

        std::size_t ret = 0;
        if (item_user_key == params.end())
        {
            throw std::runtime_error("init need user_key");
        }
        if (item_user_key->second.second != USER_KEY_LEN)
        {
            throw std::runtime_error("invalid user_key len");
        }
        if (item_iv == params.end())
        {
            throw std::runtime_error("init need iv");
        }
        if (item_aad != params.end())
        {
            aad     = static_cast<const std::uint8_t*>(item_aad->second.first);
            aad_len = item_aad->second.second;
            ret     = ret | ParamKey::AAD;
        }
        if (item_tag != params.end())
        {
            if (item_tag->second.second != sizeof(tag_))
            {
                throw std::runtime_error("gcm only support tag=16");
            }
            this->set_tag(
                static_cast<const std::uint8_t*>(item_tag->second.first));
            ret = ret | ParamKey::TAG;
        }

        this->init(
            static_cast<const std::uint8_t*>(item_user_key->second.first), //
            static_cast<const std::uint8_t*>(item_iv->second.first),       //
            item_iv->second.second,                                        //
            aad,                                                           //
            aad_len                                                        //
        );
        return ParamKey::USER_KEY | ParamKey::IV;
    }

    std::size_t set(const ConstParameter& params) override
    {
        const auto& item_tag = params.find(ParamKey::TAG);
        std::size_t ret      = 0;
        if (item_tag != params.end())
        {
            if (item_tag->second.second != sizeof(tag_))
            {
                throw std::runtime_error("gcm only support tag=16");
            }
            this->set_tag(
                static_cast<const std::uint8_t*>(item_tag->second.first) //
            );
            ret = ret | ParamKey::TAG;
        }
        return ret;
    }

private:
    ghash::GHash  hash_;
    std::uint8_t  tag_[16];
    std::uint64_t aad_len_, ct_len_;

public:
    GcmDecryptor() = default;

    GcmDecryptor(const std::uint8_t* user_key,
                 const std::uint8_t* iv,
                 std::size_t         iv_len,
                 const std::uint8_t* aad,
                 std::size_t         aad_len)
    {
        this->init(user_key, iv, iv_len, aad, aad_len);
    }

public:
    void init(const std::uint8_t* user_key,
              const std::uint8_t* iv,
              std::size_t         iv_len,
              const std::uint8_t* aad,
              std::size_t         aad_len)
    {
        if (aad_len > UINT64_MAX / 8)
        {
            throw std::runtime_error(
                "additional authenticated data length too loog");
        }
        this->GctrCryptor<Cipher>::init(user_key, iv, iv_len, hash_);
        static const std::uint8_t ZERO[16] = {0};
        // gmac aad(additional authenticated data)
        hash_.update(aad, aad_len);
        hash_.update(ZERO, (16 - (aad_len % 16)) % 16);
        aad_len_ = aad_len;
        ct_len_  = 0;
    }

    void reset(const std::uint8_t* iv,
               std::size_t         iv_len,
               const std::uint8_t* aad,
               std::size_t         aad_len)
    {
        if (aad_len > UINT64_MAX / 8)
        {
            throw std::runtime_error(
                "additional authenticated data length too loog");
        }
        this->GctrCryptor<Cipher>::reset(iv, iv_len, hash_);
        // gmac aad(additional authenticated data)
        static std::uint8_t ZERO[16] = {0};
        hash_.update(aad, aad_len);
        hash_.update(ZERO, (16 - (aad_len % 16)) % 16);
        aad_len_ = (std::uint64_t)aad_len;
        ct_len_  = 0;
        std::memset(tag_, 0, 16);
    }

    void set_tag(const std::uint8_t tag[16]) noexcept
    {
        std::memcpy(tag_, tag, 16);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        if (block_num == 0)
        {
            return;
        }
        // gmac
        std::size_t nxt_ct_len = ct_len_ + block_num * Cipher::BLOCK_SIZE;
        if (nxt_ct_len < ct_len_)
        {
            throw std::runtime_error("input data too long");
        }
        ct_len_ = nxt_ct_len;
        hash_.update(in, block_num * Cipher::BLOCK_SIZE);
        // gctr
        this->GctrCryptor<Cipher>::update_blocks(out, in, block_num);
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        static std::uint8_t t[16] = {0}, tag[16];
        if (inl != 0)
        {
            std::size_t nxt_ct_len = ct_len_ + inl;
            if (nxt_ct_len < ct_len_)
            {
                throw std::runtime_error("input data too long");
            }
            ct_len_ = nxt_ct_len;

            hash_.update(in, inl);
            hash_.update(t, (16 - inl % 16) % 16);

            this->GctrCryptor<Cipher>::final_block(out, in, inl);
        }
        memory_utils::store64_be(t + 0, aad_len_ * 8);
        memory_utils::store64_be(t + 8, ct_len_ * 8);
        hash_.update(t, 16);
        hash_.do_final(tag);
        this->GctrCryptor<Cipher>::cipher_.encrypt_block(
            t, this->GctrCryptor<Cipher>::get_counter0());
        memory_utils::memxor<16>(tag, tag, t);
        if (std::memcmp(tag, tag_, 16) != 0)
        {
            throw std::runtime_error("invalid gcm ciphertext");
        }
    }
};

} // namespace block_cipher_mode

#endif