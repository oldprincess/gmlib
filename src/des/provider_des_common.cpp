#include "config.h"

#if defined(DES_IMPL_COMMON)

#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>

#include "des_common.h"
#include "provider_des_common.h"

namespace des::internal::common {

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

class DES : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = DES_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = DES_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = DES_PARALLEL_NUM;

private:
    std::uint8_t round_key_[128];

public:
    ~DES()
    {
        std::memset(round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return "DES";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return DES_ALGO_NAME;
    };

    std::size_t fetch_block_size() const noexcept override
    {
        return DES_BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return DES_USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return DES_PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return DES_USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<DES>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            des_enc_key_init(round_key_, user_key);
        }
        else
        {
            des_dec_key_init(round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        des_enc_block(round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        des_dec_block(round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        des_enc_blocks(round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        des_dec_blocks(round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher()
{
    return std::make_unique<DES>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor()
{
    return std::make_unique<CbcEncryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor()
{
    return std::make_unique<CbcDecryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor()
{
    return std::make_unique<CbcEncryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor()
{
    return std::make_unique<CbcDecryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor()
{
    return std::make_unique<CtrEncryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor()
{
    return std::make_unique<CtrDecryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor()
{
    return std::make_unique<CfbEncryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor()
{
    return std::make_unique<CfbDecryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor()
{
    return std::make_unique<OfbEncryptorImpl<DES>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor()
{
    return std::make_unique<OfbDecryptorImpl<DES>>();
}

} // namespace des::internal::common

#endif