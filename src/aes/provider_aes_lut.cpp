#include "config.h"

#if defined(AES_IMPL_LUT)

#include <gmlib/aes/aes.h>
#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>

#include <cstring>

#include "aes_lut.h"
#include "provider_aes_lut.h"

namespace aes::internal::lut {

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
    return true;
}

} // namespace aes::internal::lut

namespace aes::internal::lut {

class AES128 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = AES128_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = AES128_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = AES128_PARALLEL_NUM;

private:
    std::uint8_t round_key_[11 * 16];

public:
    ~AES128()
    {
        std::memset(round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return "AES128";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return AES_ALGO_NAME;
    };

    std::size_t fetch_block_size() const noexcept override
    {
        return AES128_BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return AES128_USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return AES128_PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return AES128_USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<AES128>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            aes128_enc_key_init(round_key_, user_key);
        }
        else
        {
            aes128_dec_key_init(round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        aes128_enc_block(round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        aes128_dec_block(round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        aes128_enc_blocks(round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        aes128_dec_blocks(round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_128()
{
    return std::make_unique<AES128>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128()
{
    return std::make_unique<EcbEncryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128()
{
    return std::make_unique<EcbDecryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128()
{
    return std::make_unique<CbcEncryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128()
{
    return std::make_unique<CbcDecryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128()
{
    return std::make_unique<CtrEncryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128()
{
    return std::make_unique<CtrDecryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128()
{
    return std::make_unique<CfbEncryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128()
{
    return std::make_unique<CfbDecryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128()
{
    return std::make_unique<OfbEncryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128()
{
    return std::make_unique<OfbDecryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128()
{
    return std::make_unique<GcmEncryptorImpl<AES128>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128()
{
    return std::make_unique<GcmDecryptorImpl<AES128>>();
}

}; // namespace aes::internal::lut

namespace aes::internal::lut {

class AES192 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = AES192_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = AES192_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = AES192_PARALLEL_NUM;

private:
    std::uint8_t round_key_[13 * 16];

public:
    ~AES192()
    {
        std::memset(round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return "AES192";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return AES_ALGO_NAME;
    };

    std::size_t fetch_block_size() const noexcept override
    {
        return AES192_BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return AES192_USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return AES192_PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return AES192_USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<AES192>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            aes192_enc_key_init(round_key_, user_key);
        }
        else
        {
            aes192_dec_key_init(round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        aes192_enc_block(round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        aes192_dec_block(round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        aes192_enc_blocks(round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        aes192_dec_blocks(round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_192()
{
    return std::make_unique<AES192>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_192()
{
    return std::make_unique<EcbEncryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_192()
{
    return std::make_unique<EcbDecryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_192()
{
    return std::make_unique<CbcEncryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_192()
{
    return std::make_unique<CbcDecryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_192()
{
    return std::make_unique<CtrEncryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_192()
{
    return std::make_unique<CtrDecryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_192()
{
    return std::make_unique<CfbEncryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_192()
{
    return std::make_unique<CfbDecryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_192()
{
    return std::make_unique<OfbEncryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_192()
{
    return std::make_unique<OfbDecryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor_192()
{
    return std::make_unique<GcmEncryptorImpl<AES192>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor_192()
{
    return std::make_unique<GcmDecryptorImpl<AES192>>();
}

}; // namespace aes::internal::lut

namespace aes::internal::lut {

class AES256 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = AES256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = AES256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = AES256_PARALLEL_NUM;

private:
    std::uint8_t round_key_[15 * 16];

public:
    ~AES256()
    {
        std::memset(round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return "AES256";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return AES_ALGO_NAME;
    };

    std::size_t fetch_block_size() const noexcept override
    {
        return AES256_BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return AES256_USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return AES256_PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return AES256_USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<AES256>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            aes256_enc_key_init(round_key_, user_key);
        }
        else
        {
            aes256_dec_key_init(round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        aes256_enc_block(round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        aes256_dec_block(round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        aes256_enc_blocks(round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        aes256_dec_blocks(round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_256()
{
    return std::make_unique<AES256>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_256()
{
    return std::make_unique<EcbEncryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_256()
{
    return std::make_unique<EcbDecryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_256()
{
    return std::make_unique<CbcEncryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_256()
{
    return std::make_unique<CbcDecryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_256()
{
    return std::make_unique<CtrEncryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_256()
{
    return std::make_unique<CtrDecryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_256()
{
    return std::make_unique<CfbEncryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_256()
{
    return std::make_unique<CfbDecryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_256()
{
    return std::make_unique<OfbEncryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_256()
{
    return std::make_unique<OfbDecryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor_256()
{
    return std::make_unique<GcmEncryptorImpl<AES256>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor_256()
{
    return std::make_unique<GcmDecryptorImpl<AES256>>();
}

}; // namespace aes::internal::lut

#endif
