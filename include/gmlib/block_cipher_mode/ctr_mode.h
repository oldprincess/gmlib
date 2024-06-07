#ifndef BLOCK_CIPHER_MODE_CTR_MODE_H
#define BLOCK_CIPHER_MODE_CTR_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/block_cipher_mode/internal/ctr_inc.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode {

template <class Cipher>
class CtrCryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");

public:
    static constexpr const char* NAME_SUFFIX = "/CTR";

    static constexpr std::size_t NAME_STR_LEN = Cipher::NAME_STR_LEN + 4;

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
            std::memcpy(name_part1, cipher_.fetch_name(), Cipher::NAME_STR_LEN);
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
        if (item_iv->second.second != BLOCK_SIZE)
        {
            throw std::runtime_error("invalid iv len");
        }

        this->init(
            static_cast<const std::uint8_t*>(item_user_key->second.first), //
            static_cast<const std::uint8_t*>(item_iv->second.first)        //
        );
        return ParamKey::USER_KEY | ParamKey::IV;
    }

private:
    Cipher       cipher_;
    std::uint8_t counter_[Cipher::BLOCK_SIZE];

public:
    CtrCryptor() = default;
    CtrCryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(counter_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(counter_, iv, Cipher::BLOCK_SIZE);
    }

private:
    void gen_block_key_stream(std::uint8_t* out, std::size_t block_num)
    {
        if (block_num == 0)
        {
            return;
        }
        constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;
        // generate counter
        std::uint8_t* cur_counter = out;
        std::memcpy(cur_counter, counter_, BLOCK_SIZE);
        for (std::size_t i = 1; i < block_num; i++)
        {
            std::uint8_t* nxt_counter = cur_counter + BLOCK_SIZE;
            internal::ctr_inc<BLOCK_SIZE>(nxt_counter, cur_counter);
            cur_counter = nxt_counter;
        }
        internal::ctr_inc<BLOCK_SIZE>(counter_, cur_counter);
        // generate key stream
        cipher_.encrypt_blocks(out, out, block_num);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;

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
        constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        if (inl == 0)
        {
            return;
        }
        std::uint8_t key_stream[BLOCK_SIZE];
        this->gen_block_key_stream(key_stream, 1);
        memory_utils::memxor_n(out, key_stream, in, inl);
    }
};

template <class Cipher>
using CtrEncryptor = CtrCryptor<Cipher>;

template <class Cipher>
using CtrDecryptor = CtrCryptor<Cipher>;

} // namespace block_cipher_mode

#endif