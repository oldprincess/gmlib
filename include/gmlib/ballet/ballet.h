#ifndef BALLET_BALLET_H
#define BALLET_BALLET_H

#include <gmlib/ballet/internal/ballet_standard.h>
#include <gmlib/block_cipher_mode/block_cipher.h>
namespace ballet {
namespace alg = internal::standard;
} // namespace ballet

namespace ballet {

class Ballet128128 : public block_cipher_mode::BlockCipherImpl
{
public:
    static constexpr const char* NAME = "Ballet-128-128";

    static constexpr std::size_t NAME_STR_LEN = 14;

    /// @brief Ballet128128 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = alg::BALLET128128_BLOCK_SIZE;

    /// @brief Ballet128128 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = alg::BALLET128128_USER_KEY_LEN;

    /// @brief Ballet128128 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = alg::BALLET128128_PARALLEL_NUM;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief Ballet128128 private Context
    alg::BalletCTX ctx_;

public:
    /**
     * @brief   Ballet128128 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    Ballet128128() noexcept = default;

    /**
     * @brief                   Ballet128128 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         Ballet128128::ENCRYPTION or
     * Ballet128128::DECRYPTION
     */
    Ballet128128(const std::uint8_t* user_key, int enc) noexcept
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
     * @brief                   Ballet128128 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         Ballet128128::ENCRYPTION or
     *                          Ballet128128::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == Ballet128128::ENCRYPTION)
        {
            alg::ballet128128_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::ballet128128_dec_key_init(&ctx_, user_key);
        }
    }

    /**
     * @brief                   Ballet128128 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        alg::ballet128128_enc_block(&ctx_, ciphertext, plaintext);
    }

    /**
     * @brief                   Ballet128128 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        alg::ballet128128_dec_block(&ctx_, plaintext, ciphertext);
    }

    /**
     * @brief                   Ballet128128 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        alg::ballet128128_enc_blocks(&ctx_, ciphertext, plaintext, block_num);
    }

    /**
     * @brief                   Ballet128128 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        alg::ballet128128_dec_blocks(&ctx_, plaintext, ciphertext, block_num);
    }
};

class Ballet128256 : public block_cipher_mode::BlockCipherImpl
{
public:
    static constexpr const char* NAME = "Ballet-128-256";

    static constexpr std::size_t NAME_STR_LEN = 14;

    /// @brief Ballet128256 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = alg::BALLET128256_BLOCK_SIZE;

    /// @brief Ballet128256 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = alg::BALLET128256_USER_KEY_LEN;

    /// @brief Ballet128256 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = alg::BALLET128256_PARALLEL_NUM;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief Ballet128256 private Context
    alg::BalletCTX ctx_;

public:
    /**
     * @brief   Ballet128256 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    Ballet128256() noexcept = default;

    /**
     * @brief                   Ballet128256 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         Ballet128256::ENCRYPTION or
     *                          Ballet128256::DECRYPTION
     */
    Ballet128256(const std::uint8_t* user_key, int enc) noexcept
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
     * @brief                   Ballet128256 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         Ballet128256::ENCRYPTION or
     *                          Ballet128256::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == Ballet128256::ENCRYPTION)
        {
            alg::ballet128256_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::ballet128256_dec_key_init(&ctx_, user_key);
        }
    }

    /**
     * @brief                   Ballet128256 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        alg::ballet128256_enc_block(&ctx_, ciphertext, plaintext);
    }

    /**
     * @brief                   Ballet128256 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        alg::ballet128256_dec_block(&ctx_, plaintext, ciphertext);
    }

    /**
     * @brief                   Ballet128256 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        alg::ballet128256_enc_blocks(&ctx_, ciphertext, plaintext, block_num);
    }

    /**
     * @brief                   Ballet128256 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        alg::ballet128256_dec_blocks(&ctx_, plaintext, ciphertext, block_num);
    }
};

class Ballet256256 : public block_cipher_mode::BlockCipherImpl
{
public:
    static constexpr const char* NAME = "Ballet-256-256";

    static constexpr std::size_t NAME_STR_LEN = 14;

    /// @brief Ballet256256 Block Size (in bytes)
    static constexpr std::size_t BLOCK_SIZE = alg::BALLET256256_BLOCK_SIZE;

    /// @brief Ballet256256 User Key Length (in bytes)
    static constexpr std::size_t USER_KEY_LEN = alg::BALLET256256_USER_KEY_LEN;

    /// @brief Ballet256256 Maximum Number of Parallel Encryption and Decryption
    static constexpr std::size_t PARALLEL_NUM = alg::BALLET256256_PARALLEL_NUM;

    static constexpr std::size_t SECURITY_STRENGTH = USER_KEY_LEN;

private:
    /// @brief Ballet256256 private Context
    alg::BalletCTX ctx_;

public:
    /**
     * @brief   Ballet256256 Context Init
     * @note    need to call the "set_key" function to Key Schedule
     */
    Ballet256256() noexcept = default;

    /**
     * @brief                   Ballet256256 Context Init and Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         Ballet256256::ENCRYPTION or
     *                          Ballet256256::DECRYPTION
     */
    Ballet256256(const std::uint8_t* user_key, int enc) noexcept
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
     * @brief                   Ballet256256 Key Schedule
     * @param[in]   user_key    16-bytes secret key
     * @param[in]   enc         Ballet256256::ENCRYPTION or
     *                          Ballet256256::DECRYPTION
     */
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == Ballet256256::ENCRYPTION)
        {
            alg::ballet256256_enc_key_init(&ctx_, user_key);
        }
        else
        {
            alg::ballet256256_dec_key_init(&ctx_, user_key);
        }
    }

    /**
     * @brief                   Ballet256256 Encrypt Single Block
     * @param[out]  ciphertext  16-bytes ciphertext
     * @param[in]   plaintext   16-bytes plaintext
     */
    void encrypt_block(std::uint8_t*       ciphertext,
                       const std::uint8_t* plaintext) const noexcept override
    {
        alg::ballet256256_enc_block(&ctx_, ciphertext, plaintext);
    }

    /**
     * @brief                   Ballet256256 Decrypt Single Block
     * @param[out]  plaintext   16-bytes plaintext
     * @param[in]   ciphertext  16-bytes ciphertext
     */
    void decrypt_block(std::uint8_t*       plaintext,
                       const std::uint8_t* ciphertext) const noexcept override
    {
        alg::ballet256256_dec_block(&ctx_, plaintext, ciphertext);
    }

    /**
     * @brief                   Ballet256256 Encrypt Multiple Blocks
     * @param[out]  ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   plaintext   16 x block_num -bytes plaintext
     * @param[in]   block_num   block number
     */
    void encrypt_blocks(std::uint8_t*       ciphertext,
                        const std::uint8_t* plaintext,
                        std::size_t         block_num) const noexcept override
    {
        alg::ballet256256_enc_blocks(&ctx_, ciphertext, plaintext, block_num);
    }

    /**
     * @brief                   Ballet256256 Decrypt Multiple Blocks
     * @param[out]  plaintext   16 x block_num -bytes plaintext
     * @param[in]   ciphertext  16 x block_num -bytes ciphertext
     * @param[in]   block_num   block number
     */
    void decrypt_blocks(std::uint8_t*       plaintext,
                        const std::uint8_t* ciphertext,
                        std::size_t         block_num) const noexcept override
    {
        alg::ballet256256_dec_blocks(&ctx_, plaintext, ciphertext, block_num);
    }
};

} // namespace ballet

#endif