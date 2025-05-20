#ifndef DES_DES_H
#define DES_DES_H

#include <gmlib/block_cipher_mode/block_cipher.h>

namespace des {

/**
 * @brief   DES Block Cipher
 * @details GB/T 32907-2016
 */
class DES : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME = "DES";

    /// @brief DES Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 8;

    /// @brief DES User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = 8;

    /// @brief DES Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = 1;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief DES private Context
    std::uint8_t rk_data_[16 * 8];

public:
    /**
     * @brief   DES Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    DES() noexcept = default;

    /**
     * @brief                   DES Context Init and Key Schedule
     * @param[in]   user_key    8-bytes secret key
     * @param[in]   enc         DES::ENCRYPTION or DES::DECRYPTION
     */
    DES(const std::uint8_t* user_key, int enc) noexcept
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
     * @brief                   DES Key Schedule
     * @param[in]   user_key    8-bytes secret key
     * @param[in]   enc         DES::ENCRYPTION or DES::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    /**
     * @brief                   DES Encrypt Single Block
     * @param[out]  ciphertext  8-bytes ciphertext
     * @param[in]   plaintext   8-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override;

    /**
     * @brief                   DES Decrypt Single Block
     * @param[out]  plaintext   8-bytes plaintext
     * @param[in]   ciphertext  8-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override;

    /**
     * @brief                   DES Encrypt Multiple Blocks
     * @param[out]  ciphertext  8 x block_num -bytes ciphertext
     * @param[in]   plaintext   8 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override;

    /**
     * @brief                   DES Decrypt Multiple Blocks
     * @param[out]  plaintext   8 x block_num -bytes plaintext
     * @param[in]   ciphertext  8 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override;
};

} // namespace des

#endif