#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_H

#include <gmlib/block_cipher_mode/abc.h>

#include <cstdio>
#include <cstdlib>

namespace block_cipher_mode {

class BlockCipherImpl : public abc::BlockCipher
{
public:
    static constexpr const char* NAME              = nullptr;
    static constexpr std::size_t NAME_STR_LEN      = 0;
    static constexpr std::size_t BLOCK_SIZE        = 0;
    static constexpr std::size_t USER_KEY_LEN      = 0;
    static constexpr std::size_t PARALLEL_NUM      = 0;
    static constexpr std::size_t SECURITY_STRENGTH = 0;

public:
    inline const char* fetch_name() const noexcept override;

    inline std::size_t fetch_name_str_len() const noexcept override;

    inline std::size_t fetch_block_size() const noexcept override;

    inline std::size_t fetch_user_key_len() const noexcept override;

    inline std::size_t fetch_parallel_num() const noexcept override;

    inline std::size_t fetch_security_strength() const noexcept override;
};

// ===============================

#define PRINT_ERR_AND_EXIT(exit_code)                                   \
    std::printf("[gmlib error] function not implemented. in file: %s, " \
                "func: %s, line: %d\n",                                 \
                __FILE__, __FUNCTION__, __LINE__);                      \
    std::exit(exit_code)

const char* BlockCipherImpl::fetch_name() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

std::size_t BlockCipherImpl::fetch_name_str_len() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

std::size_t BlockCipherImpl::fetch_block_size() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

std::size_t BlockCipherImpl::fetch_user_key_len() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

std::size_t BlockCipherImpl::fetch_parallel_num() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

std::size_t BlockCipherImpl::fetch_security_strength() const noexcept
{
    PRINT_ERR_AND_EXIT(-1);
}

#undef PRINT_ERR_AND_EXIT

} // namespace block_cipher_mode

#endif