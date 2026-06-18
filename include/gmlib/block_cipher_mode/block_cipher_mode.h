#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H

#include <gmlib/block_cipher_mode/block_cipher.h>

#include <memory>

namespace block_cipher_mode {

class BlockCipherMode
{
public:
    virtual ~BlockCipherMode() = default;

public:
    virtual const char* fetch_name() const noexcept = 0;

    virtual std::size_t fetch_block_size() const noexcept = 0;

    virtual std::size_t fetch_user_key_len() const noexcept = 0;

public:
    virtual const BlockCipher& fetch_cipher_ctx() const noexcept = 0;

public:
    virtual void ctrl(const char* cmd, std::size_t argc, void* argv[]) = 0;

    virtual std::unique_ptr<BlockCipherMode> clone() const = 0;

    virtual void update(std::uint8_t*       out,
                        std::size_t*        outl,
                        const std::uint8_t* in,
                        std::size_t         inl) = 0;

    virtual void do_final(std::uint8_t*       out,
                          std::size_t*        outl,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;
};

} // namespace block_cipher_mode

#endif
