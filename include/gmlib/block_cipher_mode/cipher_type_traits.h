#ifndef BLOCK_CIPHER_MODE_CIPHER_TYPE_TRAITS_H
#define BLOCK_CIPHER_MODE_CIPHER_TYPE_TRAITS_H

#include <gmlib/block_cipher_mode/block_cipher.h>

#include <type_traits>

namespace block_cipher_mode {
namespace cipher_type_traits {

template <class T>
struct is_valid
{
    static constexpr bool value =
        (0 < T::BLOCK_SIZE) &&   //
        (0 < T::USER_KEY_LEN) && //
        (0 < T::PARALLEL_NUM) && //
        std::is_base_of<::block_cipher_mode::BlockCipher, T>::value;
};

} // namespace cipher_type_traits
} // namespace block_cipher_mode

#endif