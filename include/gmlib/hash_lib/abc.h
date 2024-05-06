#ifndef HASH_LIB_ABC_H
#define HASH_LIB_ABC_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace hash_lib {

namespace abc {

class Hash
{
public:
    virtual ~Hash() = default;

public:
    virtual const char* fetch_name() const noexcept = 0;

    virtual std::size_t fetch_name_str_len() const noexcept = 0;

    virtual std::size_t fetch_block_size() const noexcept = 0;

    virtual std::size_t fetch_digest_size() const noexcept = 0;

    virtual std::size_t fetch_security_strength() const noexcept = 0;

public:
    virtual void reset() = 0;

    virtual void update(const std::uint8_t* in, std::size_t inl) = 0;

    virtual void do_final(std::uint8_t*       digest,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;
};

} // namespace abc

namespace type_traits {

template <class T>
struct is_valid_hash
{
    static constexpr bool value =
        (nullptr != T::NAME) &&       //
        (0 < T::NAME_STR_LEN) &&      //
        (0 < T::BLOCK_SIZE) &&        //
        (0 < T::DIGEST_SIZE) &&       //
        (0 < T::SECURITY_STRENGTH) && //
        std::is_base_of<::hash_lib::abc::Hash, T>::value;
};

template <class T>
inline bool test_is_valid_hash()
{
    if (is_valid_hash<T>::value == false)
    {
        return false;
    }

    T          hash;
    abc::Hash& h = hash;
    if (std::strcmp(T::NAME, h.fetch_name()) != 0)
    {
        return false;
    }
    if (std::strlen(T::NAME) != h.fetch_name_str_len())
    {
        return false;
    }
    if (T::NAME_STR_LEN != h.fetch_name_str_len())
    {
        return false;
    }
    if (T::BLOCK_SIZE != h.fetch_block_size())
    {
        return false;
    }
    if (T::DIGEST_SIZE != h.fetch_digest_size())
    {
        return false;
    }
    if (T::SECURITY_STRENGTH != h.fetch_security_strength())
    {
        return false;
    }
    return true;
}

} // namespace type_traits

} // namespace hash_lib

#endif