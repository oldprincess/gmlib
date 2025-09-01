#ifndef SM4_SM4_H
#define SM4_SM4_H

#include <gmlib/block_cipher_mode/block_cipher.h>

namespace sm4 {

/**
 * @brief   SM4 Block Cipher
 * @details GB/T 32907-2016
 */
class SM4 : public block_cipher_mode::BlockCipher
{
public:
    static constexpr const char* NAME = "SM4";

    /// @brief SM4 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = 16;

    /// @brief SM4 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = 16;

    /// @brief SM4 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = 64;

    static constexpr std::size_t SECURITY_STRENGTH = 16;

private:
    /// @brief SM4 round key data
    std::uint8_t rk_data_[128];

public:
    /**
     * @brief   SM4 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    SM4() noexcept = default;

    /**
     * @brief                   SM4 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         SM4::ENCRYPTION or SM4::DECRYPTION
     */
    SM4(const std::uint8_t* user_key, int enc) noexcept
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
     * @brief                   SM4 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         SM4::ENCRYPTION or SM4::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override;

    /**
     * @brief                   SM4 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override;

    /**
     * @brief                   SM4 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override;

    /**
     * @brief                   SM4 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override;

    /**
     * @brief                   SM4 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override;
};

} // namespace sm4

#endif