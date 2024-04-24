#ifndef HASH_TYPE_TRAITS_H
#define HASH_TYPE_TRAITS_H

#include <gmlib/hash_lib/hash.h>

#include <type_traits>

namespace hash_lib {

namespace hash_type_traits {

template <class T>
struct is_valid
{
    static constexpr bool value =
        (0 < T::BLOCK_SIZE) &&        //
        (0 < T::DIGEST_SIZE) &&       //
        (0 < T::SECURITY_STRENGTH) && //
        std::is_base_of<::hash_lib::Hash_Base, T>::value;
};

} // namespace hash_type_traits

} // namespace hash_lib

#endif