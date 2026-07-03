#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H

#include <gmlib/block_cipher_mode/block_cipher.h>

#include <memory>

namespace block_cipher_mode {

class BlockCipherMode
{
public:
    /**
     * @brief Destroy the block cipher mode context.
     */
    virtual ~BlockCipherMode() = default;

public:
    /**
     * @brief Get the name of the block cipher mode.
     * @return A null-terminated mode name owned by the implementation.
     */
    virtual const char* fetch_name() const noexcept = 0;

    /**
     * @brief Get the block size of the underlying block cipher.
     * @return The block size in bytes.
     */
    virtual std::size_t fetch_block_size() const noexcept = 0;

    /**
     * @brief Get the required user key length.
     * @return The user key length in bytes.
     */
    virtual std::size_t fetch_user_key_len() const noexcept = 0;

public:
    /**
     * @brief Get the underlying block cipher context.
     * @return A constant reference to the block cipher context.
     */
    virtual const BlockCipher& fetch_cipher_ctx() const noexcept = 0;

public:
    /**
     * @brief Invoke an implementation-specific control command.
     * @param[in]      cmd   Null-terminated command name.
     * @param[in]      argc  Number of entries in @p argv.
     * @param[in,out]  argv  Command arguments. Their types and directions are
     *                       defined by the concrete mode implementation.
     */
    virtual void ctrl(const char* cmd, std::size_t argc, void* argv[]) = 0;

    /**
     * @brief Create a copy of this block cipher mode context.
     * @return A newly allocated block cipher mode context.
     */
    virtual std::unique_ptr<BlockCipherMode> clone() const = 0;

    /**
     * @brief Process input data and buffer any incomplete trailing block.
     * @deprecated Use update(std::uint8_t*, std::size_t*, std::size_t,
     *                        const std::uint8_t*, std::size_t) instead.
     * @param[out]  out   Output buffer.
     * @param[out]  outl  Number of bytes written to @p out.
     * @param[in]   in    Input buffer.
     * @param[in]   inl   Input length in bytes.
     */
    virtual void update(std::uint8_t*       out,
                        std::size_t*        outl,
                        const std::uint8_t* in,
                        std::size_t         inl) = 0;

    /**
     * @brief Process optional final input and finalize the buffered data.
     * @deprecated Use do_final(std::uint8_t*, std::size_t*, std::size_t,
     *                          const std::uint8_t*, std::size_t) instead.
     * @param[out]  out   Output buffer.
     * @param[out]  outl  Number of bytes written to @p out.
     * @param[in]   in    Optional final input buffer.
     * @param[in]   inl   Final input length in bytes.
     */
    virtual void do_final(std::uint8_t*       out,
                          std::size_t*        outl,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;

    /**
     * @brief Process input data and buffer any incomplete trailing block.
     * @param[out]  out       Output buffer.
     * @param[out]  outl      Number of bytes written to @p out.
     * @param[in]   outl_max  Capacity of @p out in bytes.
     * @param[in]   in        Input buffer.
     * @param[in]   inl       Input length in bytes.
     */
    virtual void update(std::uint8_t*       out,
                        std::size_t*        outl,
                        std::size_t         outl_max,
                        const std::uint8_t* in,
                        std::size_t         inl) = 0;

    /**
     * @brief Process optional final input and finalize the buffered data.
     * @param[out]  out       Output buffer.
     * @param[out]  outl      Number of bytes written to @p out.
     * @param[in]   outl_max  Capacity of @p out in bytes.
     * @param[in]   in        Optional final input buffer.
     * @param[in]   inl       Final input length in bytes.
     */
    virtual void do_final(std::uint8_t*       out,
                          std::size_t*        outl,
                          std::size_t         outl_max,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;
};

} // namespace block_cipher_mode

#endif
