#ifndef BLOCK_CIPHER_MODE_ABC_H
#define BLOCK_CIPHER_MODE_ABC_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <map>
#include <type_traits>
#include <utility>

namespace block_cipher_mode {

enum ParamKey : std::size_t
{
    IV       = 0b0001,
    USER_KEY = 0b0010,
    AAD      = 0b0100,
    TAG      = 0b1000,
};

using ConstParameter = std::map<ParamKey, std::pair<const void*, std::size_t>>;
using Parameter      = std::map<ParamKey, std::pair<void*, std::size_t>>;

namespace abc {

class BlockCipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    virtual ~BlockCipher() = default;

public:
    virtual const char* fetch_name() const noexcept = 0;

    virtual std::size_t fetch_name_str_len() const noexcept = 0;

    virtual std::size_t fetch_block_size() const noexcept = 0;

    virtual std::size_t fetch_user_key_len() const noexcept = 0;

    virtual std::size_t fetch_parallel_num() const noexcept = 0;

    virtual std::size_t fetch_security_strength() const noexcept = 0;

public:
    virtual void set_key(const std::uint8_t* user_key, int enc) = 0;

    virtual void encrypt_block(std::uint8_t*       out,
                               const std::uint8_t* in) const = 0;

    virtual void decrypt_block(std::uint8_t*       out,
                               const std::uint8_t* in) const = 0;

    virtual void encrypt_blocks(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) const = 0;

    virtual void decrypt_blocks(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) const = 0;
};

class BlockCipherMode
{
public:
    virtual ~BlockCipherMode() = default;

public:
    virtual const char* fetch_name() const noexcept = 0;

    virtual std::size_t fetch_name_str_len() const noexcept = 0;

    virtual std::size_t fetch_block_size() const noexcept = 0;

    virtual std::size_t fetch_user_key_len() const noexcept = 0;

public:
    virtual const BlockCipher& fetch_cipher_ctx() const noexcept = 0;

public:
    virtual std::size_t init(const ConstParameter& params) = 0;

    virtual std::size_t set(const ConstParameter& params) = 0;

    virtual std::size_t get(const Parameter& params) = 0;

public:
    virtual void update(std::uint8_t*       out,
                        std::size_t*        outl,
                        const std::uint8_t* in,
                        std::size_t         inl) = 0;

    virtual void do_final(std::uint8_t*       out,
                          std::size_t*        outl,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;
};

} // namespace abc

namespace type_traits {

template <class T>
struct is_valid_cipher
{
    static constexpr bool value =
        (1 == T::ENCRYPTION) &&       //
        (0 == T::DECRYPTION) &&       //
        (nullptr != T::NAME) &&       //
        (0 < T::NAME_STR_LEN) &&      //
        (0 < T::BLOCK_SIZE) &&        //
        (0 < T::USER_KEY_LEN) &&      //
        (0 < T::PARALLEL_NUM) &&      //
        (0 < T::SECURITY_STRENGTH) && //
        std::is_base_of<::block_cipher_mode::abc::BlockCipher, T>::value;
};

template <class T>
struct is_valid_cipher_mode
{
    static constexpr bool value =
        (nullptr != T::NAME_SUFFIX) && //
        (0 < T::NAME_STR_LEN) &&       //
        (0 < T::BLOCK_SIZE) &&         //
        (0 < T::USER_KEY_LEN) &&       //
        std::is_base_of<::block_cipher_mode::abc::BlockCipherMode, T>::value;
};

template <class T>
inline bool test_is_valid_cipher()
{
    if (is_valid_cipher<T>::value == false)
    {
        return false;
    }
    T                 cipher;
    abc::BlockCipher& c = cipher;
    if (std::strcmp(T::NAME, c.fetch_name()) != 0)
    {
        return false;
    }
    if (std::strlen(T::NAME) != c.fetch_name_str_len())
    {
        return false;
    }
    if (T::NAME_STR_LEN != c.fetch_name_str_len())
    {
        return false;
    }
    if (T::BLOCK_SIZE != c.fetch_block_size())
    {
        return false;
    }
    if (T::USER_KEY_LEN != c.fetch_user_key_len())
    {
        return false;
    }
    if (T::PARALLEL_NUM != c.fetch_parallel_num())
    {
        return false;
    }
    if (T::SECURITY_STRENGTH != c.fetch_security_strength())
    {
        return false;
    }
    return true;
}

template <class T>
inline bool test_is_valid_cipher_mode()
{
    if (is_valid_cipher_mode<T>::value == false)
    {
        return false;
    }
    T                     cipher_mode;
    abc::BlockCipherMode& c = cipher_mode;
    if (std::strstr(c.fetch_name(), T::NAME_SUFFIX) == nullptr)
    {
        return false;
    }
    if (std::strlen(c.fetch_name()) != c.fetch_name_str_len())
    {
        return false;
    }
    if (T::NAME_STR_LEN != c.fetch_name_str_len())
    {
        return false;
    }
    if (T::BLOCK_SIZE != c.fetch_block_size())
    {
        return false;
    }
    if (T::USER_KEY_LEN != c.fetch_user_key_len())
    {
        return false;
    }
    return true;
}

} // namespace type_traits

} // namespace block_cipher_mode

#endif