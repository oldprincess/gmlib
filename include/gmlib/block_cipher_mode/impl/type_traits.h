#ifndef BLOCK_CIPHER_MODE_IMPL_TYPE_TRAITS_H
#define BLOCK_CIPHER_MODE_IMPL_TYPE_TRAITS_H

#include <gmlib/block_cipher_mode/block_cipher.h>

#include <type_traits>

namespace block_cipher_mode::impl {

// ==============================================
// ============= BlockCipher ====================
// ==============================================

template <typename T, typename = void>
struct is_valid_block_cipher : std::false_type
{
};

template <typename T>
struct is_valid_block_cipher<
    T,
    std::void_t<decltype(T::BLOCK_SIZE),
                decltype(T::USER_KEY_LEN),
                decltype(T::PARALLEL_NUM),
                std::enable_if_t<std::is_base_of_v<BlockCipher, T>>>>
    : std::true_type
{
};

template <typename T>
constexpr bool is_valid_block_cipher_v = is_valid_block_cipher<T>::value;

// ==============================================
// ============= BlockCipherMode ================
// ==============================================

template <class T, class = void>
struct has_create_ecb_encryptor : std::false_type
{
};

template <class T>
struct has_create_ecb_encryptor<T,
                                std::void_t<decltype(T::create_ecb_encryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_ecb_encryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_ecb_decryptor : std::false_type
{
};

template <class T>
struct has_create_ecb_decryptor<T,
                                std::void_t<decltype(T::create_ecb_decryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_ecb_decryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_cbc_encryptor : std::false_type
{
};

template <class T>
struct has_create_cbc_encryptor<T,
                                std::void_t<decltype(T::create_cbc_encryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_cbc_encryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_cbc_decryptor : std::false_type
{
};

template <class T>
struct has_create_cbc_decryptor<T,
                                std::void_t<decltype(T::create_cbc_decryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_cbc_decryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_cfb_encryptor : std::false_type
{
};

template <class T>
struct has_create_cfb_encryptor<T,
                                std::void_t<decltype(T::create_cfb_encryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_cfb_encryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_cfb_decryptor : std::false_type
{
};

template <class T>
struct has_create_cfb_decryptor<T,
                                std::void_t<decltype(T::create_cfb_decryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_cfb_decryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_ofb_encryptor : std::false_type
{
};

template <class T>
struct has_create_ofb_encryptor<T,
                                std::void_t<decltype(T::create_ofb_encryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_ofb_encryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_ofb_decryptor : std::false_type
{
};

template <class T>
struct has_create_ofb_decryptor<T,
                                std::void_t<decltype(T::create_ofb_decryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_ofb_decryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_ctr_encryptor : std::false_type
{
};

template <class T>
struct has_create_ctr_encryptor<T,
                                std::void_t<decltype(T::create_ctr_encryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_ctr_encryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_ctr_decryptor : std::false_type
{
};

template <class T>
struct has_create_ctr_decryptor<T,
                                std::void_t<decltype(T::create_ctr_decryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_ctr_decryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_gcm_encryptor : std::false_type
{
};

template <class T>
struct has_create_gcm_encryptor<T,
                                std::void_t<decltype(T::create_gcm_encryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_gcm_encryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

template <class T, class = void>
struct has_create_gcm_decryptor : std::false_type
{
};

template <class T>
struct has_create_gcm_decryptor<T,
                                std::void_t<decltype(T::create_gcm_decryptor(
                                    std::declval<const char *>()))>>
    : std::bool_constant<std::is_convertible_v<
          decltype(T::create_gcm_decryptor(std::declval<const char *>())),
          std::unique_ptr<BlockCipherMode>>>
{
};

} // namespace block_cipher_mode::impl

#endif