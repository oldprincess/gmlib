#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

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
     * @brief Create a copy of this block cipher context.
     * @return A newly allocated block cipher context.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual std::unique_ptr<BlockCipher> clone() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

public:
    /**
     * @brief Get the cipher block size.
     * @return The block size in bytes.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual std::size_t get_block_size() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the name of the concrete implementation algorithm.
     * @return A null-terminated implementation name owned by the
     *         implementation.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual const char* get_impl_algo() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the block cipher algorithm name.
     * @return A null-terminated algorithm name owned by the implementation.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual const char* get_name() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the required user key length.
     * @return The user key length in bytes.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual std::size_t get_key_len() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the preferred number of blocks for parallel processing.
     * @return The number of blocks processed in parallel by the
     *         implementation.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual std::size_t get_parallel_num() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the security strength of the cipher.
     * @return The security strength in bytes.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual std::size_t get_security_strength() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

public:
    /**
     * @brief Set the user key and select the key schedule direction.
     * @param[in] user_key  User key containing get_key_len() bytes.
     * @param[in] enc       @c ENCRYPTION for encryption or @c DECRYPTION
     *                      for decryption.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual void set_key(const std::uint8_t* user_key, int enc)
    {
        (void)user_key;
        (void)enc;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

public:
    /**
     * @brief Encrypt one block.
     * @param[out] out Output buffer containing get_block_size() bytes.
     * @param[in]  in  Input buffer containing get_block_size() bytes.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual void encrypt_block(std::uint8_t* out, const std::uint8_t* in) const
    {
        (void)out;
        (void)in;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Encrypt multiple consecutive blocks.
     * @param[out] out       Output buffer containing at least
     *                       @p block_num * get_block_size() bytes.
     * @param[in]  in        Input buffer containing at least
     *                       @p block_num * get_block_size() bytes.
     * @param[in]  block_num Number of blocks to encrypt.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual void encrypt_blocks(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) const
    {
        (void)out;
        (void)in;
        (void)block_num;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Decrypt one block.
     * @param[out] out Output buffer containing get_block_size() bytes.
     * @param[in]  in  Input buffer containing get_block_size() bytes.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual void decrypt_block(std::uint8_t* out, const std::uint8_t* in) const
    {
        (void)out;
        (void)in;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Decrypt multiple consecutive blocks.
     * @param[out] out       Output buffer containing at least
     *                       @p block_num * get_block_size() bytes.
     * @param[in]  in        Input buffer containing at least
     *                       @p block_num * get_block_size() bytes.
     * @param[in]  block_num Number of blocks to decrypt.
     * @throws std::runtime_error If the operation is not implemented.
     */
    virtual void decrypt_blocks(std::uint8_t*       out,
                                const std::uint8_t* in,
                                std::size_t         block_num) const
    {
        (void)out;
        (void)in;
        (void)block_num;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }
};

} // namespace block_cipher_mode

#endif
