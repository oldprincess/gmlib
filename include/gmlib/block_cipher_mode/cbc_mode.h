#ifndef BLOCK_CIPHER_MODE_CBC_MODE_H
#define BLOCK_CIPHER_MODE_CBC_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>
#include <gmlib/memory_utils/memxor.h>

#include <stdexcept>

namespace block_cipher_mode {

template <class Cipher>
class CbcEncryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");

public:
    static constexpr const char* NAME_SUFFIX = "/CBC-ENC";

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
    std::uint8_t iv_[BLOCK_SIZE];

public:
    CbcEncryptor() = default;

    CbcEncryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        std::uint8_t* cur_iv = iv_;
        while (block_num)
        {
            memory_utils::memxor<BLOCK_SIZE>(iv_, in, cur_iv);
            cipher_.encrypt_block(out, iv_);
            cur_iv = out;
            in += BLOCK_SIZE, out += BLOCK_SIZE, block_num--;
        }
        std::memcpy(iv_, cur_iv, BLOCK_SIZE);
    }

    void final_block(std::uint8_t*       out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        // input len != 0
        if (inl != BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in CBC mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->update_blocks(out, in, 1);
    }
};

template <class Cipher>
class CbcDecryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");

public:
    static constexpr const char* NAME_SUFFIX = "/CBC-DEC";

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
    Cipher  cipher_;
    uint8_t iv_[Cipher::BLOCK_SIZE];

public:
    CbcDecryptor() = default;

    CbcDecryptor(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        this->init(user_key, iv);
    }

public:
    void init(const std::uint8_t* user_key, const std::uint8_t* iv)
    {
        cipher_.set_key(user_key, Cipher::DECRYPTION);
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

    void reset(const std::uint8_t* iv) noexcept
    {
        this->BlockCipherModeImpl<BLOCK_SIZE>::reset();
        std::memcpy(iv_, iv, BLOCK_SIZE);
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        constexpr std::size_t PARALLEL_NUM   = Cipher::PARALLEL_NUM;
        constexpr std::size_t PARALLEL_BYTES = BLOCK_SIZE * PARALLEL_NUM;
        constexpr std::size_t REMAIN         = PARALLEL_BYTES - BLOCK_SIZE;

        std::uint8_t buffer[PARALLEL_BYTES], next_iv[BLOCK_SIZE];
        while (block_num >= PARALLEL_NUM)
        {
            std::memcpy(next_iv, in + REMAIN, BLOCK_SIZE);

            cipher_.decrypt_blocks(buffer, in, PARALLEL_NUM);
            memory_utils::memxor<BLOCK_SIZE>(out, buffer, iv_);
            std::uint8_t *ptr1 = out + BLOCK_SIZE, *ptr2 = buffer + BLOCK_SIZE;
            memory_utils::memxor<REMAIN>(ptr1, ptr2, in);
            in += PARALLEL_BYTES, out += PARALLEL_BYTES;
            block_num -= PARALLEL_NUM;

            std::memcpy(iv_, next_iv, BLOCK_SIZE);
        }
        if (block_num)
        {
            std::size_t remain = (block_num - 1) * BLOCK_SIZE;
            std::memcpy(next_iv, in + remain, BLOCK_SIZE);

            cipher_.decrypt_blocks(buffer, in, block_num);
            memory_utils::memxor<BLOCK_SIZE>(out, buffer, iv_);
            std::uint8_t *ptr1 = out + BLOCK_SIZE, *ptr2 = buffer + BLOCK_SIZE;
            memory_utils::memxor_n(ptr1, ptr2, in, remain);

            std::memcpy(iv_, next_iv, BLOCK_SIZE);
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
        // input len != 0
        if (inl != BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in CBC mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        this->update_blocks(out, in, 1);
    }
};

} // namespace block_cipher_mode

#endif
