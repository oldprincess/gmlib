#include "config.h"

#if defined(SM4_IMPL_SM4NI)

#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>
#include <gmlib/cpuinfo/cpuinfo.h>

#include "provider_sm4_sm4ni.h"
#include "sm4_sm4ni.h"

namespace sm4::internal::sm4ni {

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
    static bool available = cpuinfo::x86_64::cpu_supports_aes() &&
                            cpuinfo::x86_64::cpu_supports_sse2() &&
                            cpuinfo::x86_64::cpu_supports_ssse3();
    return available;
}

class SM4 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = SM4_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = SM4_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = SM4_PARALLEL_NUM;

private:
    std::uint8_t round_key_[128];

public:
    ~SM4()
    {
        std::memset(round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return "SM4";
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return SM4_ALGO_NAME;
    };

    std::size_t fetch_block_size() const noexcept override
    {
        return SM4_BLOCK_SIZE;
    }

    std::size_t fetch_user_key_len() const noexcept override
    {
        return SM4_USER_KEY_LEN;
    }

    std::size_t fetch_parallel_num() const noexcept override
    {
        return SM4_PARALLEL_NUM;
    }

    std::size_t fetch_security_strength() const noexcept override
    {
        return SM4_USER_KEY_LEN;
    }

    std::unique_ptr<BlockCipher> clone() const override
    {
        return std::make_unique<SM4>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            sm4_enc_key_init(round_key_, user_key);
        }
        else
        {
            sm4_dec_key_init(round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        sm4_enc_block(round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        sm4_dec_block(round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        sm4_enc_blocks(round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        sm4_dec_blocks(round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher()
{
    return std::make_unique<SM4>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor()
{
    return std::make_unique<EcbEncryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor()
{
    return std::make_unique<EcbDecryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor()
{
    return std::make_unique<CbcEncryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor()
{
    return std::make_unique<CbcDecryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor()
{
    return std::make_unique<CtrEncryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor()
{
    return std::make_unique<CtrDecryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor()
{
    return std::make_unique<CfbEncryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor()
{
    return std::make_unique<CfbDecryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor()
{
    return std::make_unique<OfbEncryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor()
{
    return std::make_unique<OfbDecryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor()
{
    return std::make_unique<GcmEncryptorImpl<SM4>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor()
{
    return std::make_unique<GcmDecryptorImpl<SM4>>();
}

} // namespace sm4::internal::sm4ni

#endif
