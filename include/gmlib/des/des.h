#ifndef DES_DES_H
#define DES_DES_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/des/internal/des_common.h>
namespace des {
namespace alg = internal::common;
} // namespace des

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
    static constexpr std::size_t BLOCK_SIZE = alg::DES_BLOCK_SIZE;

    /// @brief DES User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = alg::DES_USER_KEY_LEN;

    /// @brief DES Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = alg::DES_PARALLEL_NUM;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief DES private Context
    alg::DesCTX ctx_;

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
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == DES::ENCRYPTION)
        {
            alg::des_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::des_dec_key_init(&ctx_, user_key);
        }
    }

    /**
     * @brief                   DES Encrypt Single Block
     * @param[out]  ciphertext  8-bytes ciphertext
     * @param[in]   plaintext   8-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        alg::des_enc_block(&ctx_, ciphertext, plaintext);
    }

    /**
     * @brief                   DES Decrypt Single Block
     * @param[out]  plaintext   8-bytes plaintext
     * @param[in]   ciphertext  8-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        alg::des_dec_block(&ctx_, plaintext, ciphertext);
    }

    /**
     * @brief                   DES Encrypt Multiple Blocks
     * @param[out]  ciphertext  8 x block_num -bytes ciphertext
     * @param[in]   plaintext   8 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        alg::des_enc_blocks(&ctx_, ciphertext, plaintext, block_num);
    }

    /**
     * @brief                   DES Decrypt Multiple Blocks
     * @param[out]  plaintext   8 x block_num -bytes plaintext
     * @param[in]   ciphertext  8 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        alg::des_dec_blocks(&ctx_, plaintext, ciphertext, block_num);
    }
};

} // namespace des

#endif