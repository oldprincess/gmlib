#ifndef SM4_SM4_H
#define SM4_SM4_H

#include <gmlib/block_cipher_mode/block_cipher.h>
#include <gmlib/sm4/internal/sm4_common.h>
#include <gmlib/sm4/internal/sm4_lang18.h>

namespace sm4 {

#if defined(SUPPORT_SM4_LANG18)
namespace alg = internal::lang18;
#else
namespace alg = internal::common;
#endif

/**
 * @brief   SM4 Block Cipher
 * @details GB/T 32907-2016
 */
class SM4 : public block_cipher_mode::BlockCipherImpl
{
public:
    static constexpr const char* NAME = "SM4";

    static constexpr std::size_t NAME_STR_LEN = 3;

    /// @brief SM4 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = alg::SM4_BLOCK_SIZE;

    /// @brief SM4 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = alg::SM4_USER_KEY_LEN;

    /// @brief SM4 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = alg::SM4_PARALLEL_NUM;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief SM4 private Context
    alg::Sm4CTX ctx_;

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

    std::size_t fetch_name_str_len() const noexcept override
    {
        return NAME_STR_LEN;
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
     * @brief                   SM4 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         SM4::ENCRYPTION or SM4::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == SM4::ENCRYPTION)
        {
            alg::sm4_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::sm4_dec_key_init(&ctx_, user_key);
        }
    }

    /**
     * @brief                   SM4 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        alg::sm4_enc_block(&ctx_, ciphertext, plaintext);
    }

    /**
     * @brief                   SM4 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        alg::sm4_dec_block(&ctx_, plaintext, ciphertext);
    }

    /**
     * @brief                   SM4 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        alg::sm4_enc_blocks(&ctx_, ciphertext, plaintext, block_num);
    }

    /**
     * @brief                   SM4 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        alg::sm4_dec_blocks(&ctx_, plaintext, ciphertext, block_num);
    }
};

} // namespace sm4

#endif