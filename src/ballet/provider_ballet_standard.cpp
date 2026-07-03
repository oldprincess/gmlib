#include <gmlib/ballet/ballet.h>
#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>

#include <cstring>
#include <stdexcept>

#include "ballet_standard.h"
#include "provider_ballet_standard.h"

namespace ballet::internal::standard {

using block_cipher_mode::impl::CbcDecryptorImpl;
using block_cipher_mode::impl::CbcEncryptorImpl;
using block_cipher_mode::impl::CfbDecryptorImpl;
using block_cipher_mode::impl::CfbEncryptorImpl;
using block_cipher_mode::impl::CtrDecryptorImpl;
using block_cipher_mode::impl::CtrEncryptorImpl;
using block_cipher_mode::impl::EcbDecryptorImpl;
using block_cipher_mode::impl::EcbEncryptorImpl;
using block_cipher_mode::impl::GcmDecryptorImpl;
using block_cipher_mode::impl::GcmEncryptorImpl;
using block_cipher_mode::impl::OfbDecryptorImpl;
using block_cipher_mode::impl::OfbEncryptorImpl;

bool provider_available()
{
    // Standard implementation is always available
    return true;
}

class Ballet128128 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = BALLET128128_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = BALLET128128_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = BALLET128128_PARALLEL_NUM;

private:
    Ballet128128RoundKey round_key_;

public:
    ~Ballet128128() override
    {
        std::memset(&round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return ballet::Ballet128128::NAME;
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return BALLET_ALGO_NAME;
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
        return USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<Ballet128128>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            ballet128128_enc_key_init(&round_key_, user_key);
        }
        else
        {
            ballet128128_dec_key_init(&round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ballet128128_enc_block(&round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ballet128128_dec_block(&round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ballet128128_enc_blocks(&round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ballet128128_dec_blocks(&round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_128128()
{
    return std::make_unique<Ballet128128>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128128()
{
    return std::make_unique<EcbEncryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128128()
{
    return std::make_unique<EcbDecryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128128()
{
    return std::make_unique<CbcEncryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128128()
{
    return std::make_unique<CbcDecryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128128()
{
    return std::make_unique<OfbEncryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128128()
{
    return std::make_unique<OfbDecryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128128()
{
    return std::make_unique<CfbEncryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128128()
{
    return std::make_unique<CfbDecryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128128()
{
    return std::make_unique<CtrEncryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128128()
{
    return std::make_unique<CtrDecryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128128()
{
    return std::make_unique<GcmEncryptorImpl<Ballet128128>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128128()
{
    return std::make_unique<GcmDecryptorImpl<Ballet128128>>();
}

class Ballet128256 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = BALLET128256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = BALLET128256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = BALLET128256_PARALLEL_NUM;

private:
    Ballet128256RoundKey round_key_;

public:
    ~Ballet128256() override
    {
        std::memset(&round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return ballet::Ballet128256::NAME;
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return BALLET_ALGO_NAME;
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
        return USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<Ballet128256>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            ballet128256_enc_key_init(&round_key_, user_key);
        }
        else
        {
            ballet128256_dec_key_init(&round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ballet128256_enc_block(&round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ballet128256_dec_block(&round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ballet128256_enc_blocks(&round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ballet128256_dec_blocks(&round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_128256()
{
    return std::make_unique<Ballet128256>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128256()
{
    return std::make_unique<EcbEncryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128256()
{
    return std::make_unique<EcbDecryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128256()
{
    return std::make_unique<CbcEncryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128256()
{
    return std::make_unique<CbcDecryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128256()
{
    return std::make_unique<OfbEncryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128256()
{
    return std::make_unique<OfbDecryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128256()
{
    return std::make_unique<CfbEncryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128256()
{
    return std::make_unique<CfbDecryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128256()
{
    return std::make_unique<CtrEncryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128256()
{
    return std::make_unique<CtrDecryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128256()
{
    return std::make_unique<GcmEncryptorImpl<Ballet128256>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128256()
{
    return std::make_unique<GcmDecryptorImpl<Ballet128256>>();
}

class Ballet256256 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = BALLET256256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = BALLET256256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = BALLET256256_PARALLEL_NUM;

private:
    Ballet256256RoundKey round_key_;

public:
    ~Ballet256256() override
    {
        std::memset(&round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return ballet::Ballet256256::NAME;
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return BALLET_ALGO_NAME;
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
        return USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<Ballet256256>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            ballet256256_enc_key_init(&round_key_, user_key);
        }
        else
        {
            ballet256256_dec_key_init(&round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ballet256256_enc_block(&round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ballet256256_dec_block(&round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ballet256256_enc_blocks(&round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ballet256256_dec_blocks(&round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_256256()
{
    return std::make_unique<Ballet256256>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_256256()
{
    return std::make_unique<EcbEncryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_256256()
{
    return std::make_unique<EcbDecryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_256256()
{
    return std::make_unique<CbcEncryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_256256()
{
    return std::make_unique<CbcDecryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_256256()
{
    return std::make_unique<OfbEncryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_256256()
{
    return std::make_unique<OfbDecryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_256256()
{
    return std::make_unique<CfbEncryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_256256()
{
    return std::make_unique<CfbDecryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_256256()
{
    return std::make_unique<CtrEncryptorImpl<Ballet256256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_256256()
{
    return std::make_unique<CtrDecryptorImpl<Ballet256256>>();
}

} // namespace ballet::internal::standard
