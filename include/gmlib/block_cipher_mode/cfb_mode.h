#ifndef BLOCK_CIPHER_MODE_CFB_MODE_H
#define BLOCK_CIPHER_MODE_CFB_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode {

template <class Cipher>
class CfbEncryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");

public:
    static constexpr const char* NAME_SUFFIX = "/CFB-ENC";

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
    std::uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CfbEncryptor() = default;

    CfbEncryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t BLOCK_SIZE = Cipher::BLOCK_SIZE;

        std::uint8_t* pre_ct = iv_;
        while (block_num)
        {
            cipher_.encrypt_block(iv_, pre_ct);
            memory_utils::memxor<BLOCK_SIZE>(out, in, iv_);
            pre_ct = out;
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
        std::memcpy(iv_, pre_ct, BLOCK_SIZE);
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        cipher_.encrypt_block(iv_, iv_);
        memory_utils::memxor_n(out, iv_, in, inl);
    }
};

template <class Cipher>
class CfbDecryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");

public:
    static constexpr const char* NAME_SUFFIX = "/CFB-DEC";

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

private:
    Cipher       cipher_;
    std::uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CfbDecryptor() = default;

    CfbDecryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
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

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, Cipher::BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t BLOCK_SIZE     = Cipher::BLOCK_SIZE;
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;
        constexpr std::size_t REMAIN         = PARALLEL_BYTES - BLOCK_SIZE;

        std::uint8_t buffer[PARALLEL_BYTES];
        while (block_num >= PARALLEL_NUM)
        {
            std::memcpy(buffer, iv_, BLOCK_SIZE);
            std::memcpy(buffer + BLOCK_SIZE, in, REMAIN);
            std::memcpy(iv_, in + REMAIN, BLOCK_SIZE);
            cipher_.encrypt_blocks(buffer, buffer, PARALLEL_NUM);
            memory_utils::memxor<PARALLEL_BYTES>(out, in, buffer);
            out += PARALLEL_BYTES;
            in += PARALLEL_BYTES, block_num -= PARALLEL_NUM;
        }
        if (block_num)
        {
            std::size_t         remain_bytes = block_num * BLOCK_SIZE;
            const std::uint8_t* nxt_iv       = in + remain_bytes - BLOCK_SIZE;
            std::memcpy(buffer, iv_, BLOCK_SIZE);
            std::memcpy(buffer + BLOCK_SIZE, in, remain_bytes - BLOCK_SIZE);
            std::memcpy(iv_, nxt_iv, BLOCK_SIZE);
            cipher_.encrypt_blocks(buffer, buffer, block_num);
            memory_utils::memxor_n(out, in, buffer, remain_bytes);
        }
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        cipher_.encrypt_block(iv_, iv_);
        memory_utils::memxor_n(out, in, iv_, inl);
    }
};

} // namespace block_cipher_mode

#endif