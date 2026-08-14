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
    /**
     * @brief Destroy the block cipher context.
     */
    virtual ~BlockCipher() = default;

public:
    /**
     * @brief Get the block cipher algorithm name.
     * @return A null-terminated algorithm name owned by the implementation.
     */
    virtual const char* fetch_name() const noexcept = 0;

    /**
     * @brief Get the name of the concrete implementation algorithm.
     * @return A null-terminated implementation name owned by the
     * implementation.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual const char* fetch_impl_algo() const
    {
        throw std::runtime_error("Not implemented");
    }

    /**
     * @brief Get the cipher block size.
     * @return The block size in bytes.
     */
    virtual std::size_t fetch_block_size() const noexcept = 0;

    /**
     * @brief Get the required user key length.
     * @return The user key length in bytes.
     */
    virtual std::size_t fetch_user_key_len() const noexcept = 0;

    /**
     * @brief Get the preferred number of blocks for parallel processing.
     * @return The number of blocks processed in parallel by the
     * implementation.
     */
    virtual std::size_t fetch_parallel_num() const noexcept = 0;

    /**
     * @brief Get the security strength of the cipher.
     * @return The security strength in bytes.
     */
    virtual std::size_t fetch_security_strength() const noexcept = 0;

public:
    /**
     * @brief Create a copy of this block cipher context.
     * @return A newly allocated block cipher context.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual std::unique_ptr<BlockCipher> clone() const
    {
        throw std::runtime_error("Not implemented");
    }

public:
    /**
     * @brief Set the user key and select the key schedule direction.
     * @param[in] user_key  User key containing fetch_user_key_len() bytes.
     * @param[in] enc       @c ENCRYPTION for encryption or @c DECRYPTION
     *                      for decryption.
     */
    virtual void set_key(const std::uint8_t* user_key, int enc) = 0;

    /**
     * @brief Encrypt one block.
     * @param[out] out Output buffer containing fetch_block_size() bytes.
     * @param[in]  in  Input buffer containing fetch_block_size() bytes.
     */
    virtual void encrypt_block(std::uint8_t*       out,
                               const std::uint8_t* in) const = 0;

    /**
     * @brief Decrypt one block.
     * @param[out] out Output buffer containing fetch_block_size() bytes.
     * @param[in]  in  Input buffer containing fetch_block_size() bytes.
     */
    virtual void decrypt_block(std::uint8_t*       out,
                               const std::uint8_t* in) const = 0;

    /**
     * @brief Encrypt multiple consecutive blocks.
     * @param[out] out       Output buffer containing at least
     *                       @p block_num * fetch_block_size() bytes.
     * @param[in]  in        Input buffer containing at least
     *                       @p block_num * fetch_block_size() bytes.
     * @param[in]  block_num Number of blocks to encrypt.
     */
    virtual void encrypt_blocks(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) const = 0;

    /**
     * @brief Decrypt multiple consecutive blocks.
     * @param[out] out       Output buffer containing at least
     *                       @p block_num * fetch_block_size() bytes.
     * @param[in]  in        Input buffer containing at least
     *                       @p block_num * fetch_block_size() bytes.
     * @param[in]  block_num Number of blocks to decrypt.
     */
    virtual void decrypt_blocks(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) const = 0;
};

} // namespace block_cipher_mode

#endif
