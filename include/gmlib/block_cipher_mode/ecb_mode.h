#ifndef BLOCK_CIPHER_MODE_ECB_MODE_H
#define BLOCK_CIPHER_MODE_ECB_MODE_H

#include <gmlib/block_cipher_mode/block_cipher_mode.h>

#include <stdexcept>

namespace block_cipher_mode {

template <class Cipher>
class EcbEncryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");

public:
    static constexpr const char* NAME_SUFFIX = "/ECB-ENC";

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

        if (item_user_key == params.end())
        {
            throw std::runtime_error("init need user_key");
        }
        if (item_user_key->second.second != USER_KEY_LEN)
        {
            throw std::runtime_error("invalid user_key len");
        }

        this->init(
            static_cast<const std::uint8_t*>(item_user_key->second.first) //
        );
        return ParamKey::USER_KEY;
    }

private:
    Cipher cipher_;

public:
    EcbEncryptor() = default;

    EcbEncryptor(const std::uint8_t* user_key)
    {
        this->init(user_key);
    }

public:
    void init(const std::uint8_t* user_key)
    {
        cipher_.set_key(user_key, Cipher::ENCRYPTION);
    }

    void reset() noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        cipher_.encrypt_blocks(out, in, block_num);
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
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in ECB mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        cipher_.encrypt_block(out, in);
    }
};

template <class Cipher>
class EcbDecryptor : public BlockCipherModeImpl<Cipher::BLOCK_SIZE>
{
    static_assert(type_traits::is_valid_cipher<Cipher>::value,
                  "invalid block cipher class");

public:
    static constexpr const char* NAME_SUFFIX = "/ECB-DEC";

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

        if (item_user_key == params.end())
        {
            throw std::runtime_error("init need user_key");
        }
        if (item_user_key->second.second != USER_KEY_LEN)
        {
            throw std::runtime_error("invalid user_key len");
        }

        this->init(
            static_cast<const std::uint8_t*>(item_user_key->second.first) //
        );
        return ParamKey::USER_KEY;
    }

private:
    Cipher cipher_; // Symmetric Cipher Context

public:
    EcbDecryptor() = default;

    EcbDecryptor(const std::uint8_t* user_key)
    {
        this->init(user_key);
    }

public:
    void init(const std::uint8_t* user_key)
    {
        cipher_.set_key(user_key, Cipher::DECRYPTION);
    }

    void reset() noexcept
    {
        this->BlockCipherModeImpl<Cipher::BLOCK_SIZE>::reset();
    }

private:
    void update_blocks(std::uint8_t*       out,
                       const std::uint8_t* in,
                       std::size_t         block_num) override
    {
        cipher_.decrypt_blocks(out, in, block_num);
    }

    void final_block(uint8_t*            out,
                     const std::uint8_t* in,
                     std::size_t         inl) override
    {
        if (inl == 0)
        {
            return;
        }
        // input len != 0
        if (inl != Cipher::BLOCK_SIZE)
        {
            throw std::runtime_error("input data length in ECB mode needs to "
                                     "be an integer multiple of BLOCK_SIZE");
        }
        cipher_.decrypt_block(out, in);
    }
};

} // namespace block_cipher_mode

#endif