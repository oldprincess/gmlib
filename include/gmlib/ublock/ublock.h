#ifndef UBLOCK_UBLOCK_H
#define UBLOCK_UBLOCK_H

#include <gmlib/block_cipher_mode/block_cipher.h>

namespace ublock {

class uBlock128128 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME = "uBlock-128-128";

    /// @brief uBlock128128 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 16;

    /// @brief uBlock128128 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = 16;

    /// @brief uBlock128128 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = 1;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief uBlock128128 private Context
    std::uint8_t rk_data_[544];

public:
    /**
     * @brief   uBlock128128 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    uBlock128128() noexcept = default;

    /**
     * @brief                   uBlock128128 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         uBlock128128::ENCRYPTION or
     * uBlock128128::DECRYPTION
     */
    uBlock128128(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    const char* fetch_impl_algo() const noexcept override;

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return SECURITY_STRENGTH;
    }

public:
    /**
     * @brief                   uBlock128128 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         uBlock128128::ENCRYPTION or
     * uBlock128128::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    /**
     * @brief                   uBlock128128 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override;

    /**
     * @brief                   uBlock128128 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override;

    /**
     * @brief                   uBlock128128 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override;

    /**
     * @brief                   uBlock128128 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override;
};

class uBlock128256 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME = "uBlock-128-256";

    /// @brief uBlock128256 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 16;

    /// @brief uBlock128256 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = 32;

    /// @brief uBlock128256 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = 1;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief uBlock128256 private Context
    std::uint8_t rk_data_[800];

public:
    /**
     * @brief   uBlock128256 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    uBlock128256() noexcept = default;

    /**
     * @brief                   uBlock128256 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         uBlock128256::ENCRYPTION or
     * uBlock128256::DECRYPTION
     */
    uBlock128256(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    const char* fetch_impl_algo() const noexcept override;

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return SECURITY_STRENGTH;
    }

public:
    /**
     * @brief                   uBlock128256 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         uBlock128256::ENCRYPTION or
     * uBlock128256::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    /**
     * @brief                   uBlock128256 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override;

    /**
     * @brief                   uBlock128256 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override;

    /**
     * @brief                   uBlock128256 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override;

    /**
     * @brief                   uBlock128256 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override;
};

class uBlock256256 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME = "uBlock-256-256";

    /// @brief uBlock256256 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 32;

    /// @brief uBlock256256 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = 32;

    /// @brief uBlock256256 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = 1;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief uBlock256256 private Context
    std::uint8_t rk_data_[1600];

public:
    /**
     * @brief   uBlock256256 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    uBlock256256() noexcept = default;

    /**
     * @brief                   uBlock256256 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         uBlock256256::ENCRYPTION or
     * uBlock256256::DECRYPTION
     */
    uBlock256256(const std::uint8_t* user_key, int enc) noexcept
    {
        this->set_key(user_key, enc);
    }

public:
    const char* fetch_name() const noexcept override
    {
        return NAME;
    }

    const char* fetch_impl_algo() const noexcept override;

    std::size_t fetch_block_size() const noexcept override
    {
        return BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return SECURITY_STRENGTH;
    }

public:
    /**
     * @brief                   uBlock256256 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         uBlock256256::ENCRYPTION or
     * uBlock256256::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    /**
     * @brief                   uBlock256256 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override;

    /**
     * @brief                   uBlock256256 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override;

    /**
     * @brief                   uBlock256256 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override;

    /**
     * @brief                   uBlock256256 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override;
};

} // namespace ublock

#endif