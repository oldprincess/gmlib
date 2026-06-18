#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace block_cipher_mode {

class BlockCipher
{
public:
    static constexpr int ENCRYPTION = 1;
    static constexpr int DECRYPTION = 0;

public:
    virtual ~BlockCipher() = default;

public:
    virtual const char* fetch_name() const noexcept = 0;

    virtual const char* fetch_impl_algo() const
    {
        throw std::runtime_error("Not implemented");
    }

    virtual std::size_t fetch_block_size() const noexcept = 0;

    virtual std::size_t fetch_user_key_len() const noexcept = 0;

    virtual std::size_t fetch_parallel_num() const noexcept = 0;

    virtual std::size_t fetch_security_strength() const noexcept = 0;

public:
    virtual std::unique_ptr<BlockCipher> clone() const
    {
        throw std::runtime_error("Not implemented");
    }

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

} // namespace block_cipher_mode

#endif