#if defined(UBLOCK_IMPL_STANDARD)

#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>
#include <gmlib/cpuinfo/cpuinfo.h>
#include <gmlib/ublock/ublock.h>

#include <cstring>
#include <stdexcept>

#include "provider_ublock_standard.h"
#include "ublock_standard.h"

namespace ublock::internal::standard {

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
    return cpuinfo::x86_64::cpu_supports_ssse3();
}

class UBlock128128 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = UBLOCK128128_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = UBLOCK128128_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = UBLOCK128128_PARALLEL_NUM;

private:
    UBlock128128RoundKey round_key_;

public:
    ~UBlock128128() override
    {
        std::memset(&round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return ublock::uBlock128128::NAME;
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return UBLOCK_ALGO_NAME;
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
        return std::make_unique<UBlock128128>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            ublock128128_enc_key_init(&round_key_, user_key);
        }
        else
        {
            ublock128128_dec_key_init(&round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ublock128128_enc_block(&round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ublock128128_dec_block(&round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ublock128128_enc_blocks(&round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ublock128128_dec_blocks(&round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_128128()
{
    return std::make_unique<UBlock128128>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128128()
{
    return std::make_unique<EcbEncryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128128()
{
    return std::make_unique<EcbDecryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128128()
{
    return std::make_unique<CbcEncryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128128()
{
    return std::make_unique<CbcDecryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128128()
{
    return std::make_unique<OfbEncryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128128()
{
    return std::make_unique<OfbDecryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128128()
{
    return std::make_unique<CfbEncryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128128()
{
    return std::make_unique<CfbDecryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128128()
{
    return std::make_unique<CtrEncryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128128()
{
    return std::make_unique<CtrDecryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128128()
{
    return std::make_unique<GcmEncryptorImpl<UBlock128128>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128128()
{
    return std::make_unique<GcmDecryptorImpl<UBlock128128>>();
}

class UBlock128256 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = UBLOCK128256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = UBLOCK128256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = UBLOCK128256_PARALLEL_NUM;

private:
    UBlock128256RoundKey round_key_;

public:
    ~UBlock128256() override
    {
        std::memset(&round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return ublock::uBlock128256::NAME;
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return UBLOCK_ALGO_NAME;
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
        return std::make_unique<UBlock128256>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            ublock128256_enc_key_init(&round_key_, user_key);
        }
        else
        {
            ublock128256_dec_key_init(&round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ublock128256_enc_block(&round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ublock128256_dec_block(&round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ublock128256_enc_blocks(&round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ublock128256_dec_blocks(&round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_128256()
{
    return std::make_unique<UBlock128256>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_128256()
{
    return std::make_unique<EcbEncryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_128256()
{
    return std::make_unique<EcbDecryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_128256()
{
    return std::make_unique<CbcEncryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_128256()
{
    return std::make_unique<CbcDecryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_128256()
{
    return std::make_unique<OfbEncryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_128256()
{
    return std::make_unique<OfbDecryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_128256()
{
    return std::make_unique<CfbEncryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_128256()
{
    return std::make_unique<CfbDecryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_128256()
{
    return std::make_unique<CtrEncryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_128256()
{
    return std::make_unique<CtrDecryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_encryptor_128256()
{
    return std::make_unique<GcmEncryptorImpl<UBlock128256>>();
}

std::unique_ptr<BlockCipherMode> create_gcm_decryptor_128256()
{
    return std::make_unique<GcmDecryptorImpl<UBlock128256>>();
}

class UBlock256256 : public BlockCipher
{
public:
    static constexpr std::size_t BLOCK_SIZE   = UBLOCK256256_BLOCK_SIZE;
    static constexpr std::size_t USER_KEY_LEN = UBLOCK256256_USER_KEY_LEN;
    static constexpr std::size_t PARALLEL_NUM = UBLOCK256256_PARALLEL_NUM;

private:
    UBlock256256RoundKey round_key_;

public:
    ~UBlock256256() override
    {
        std::memset(&round_key_, 0, sizeof(round_key_));
    }

public:
    const char* fetch_name() const noexcept override
    {
        return ublock::uBlock256256::NAME;
    }

    const char* fetch_impl_algo() const noexcept override
    {
        return UBLOCK_ALGO_NAME;
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
        return std::make_unique<UBlock256256>(*this);
    }

public:
    void set_key(const std::uint8_t* user_key, int enc) noexcept override
    {
        if (enc == ENCRYPTION)
        {
            ublock256256_enc_key_init(&round_key_, user_key);
        }
        else
        {
            ublock256256_dec_key_init(&round_key_, user_key);
        }
    }

    void encrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ublock256256_enc_block(&round_key_, out, in);
    }

    void decrypt_block(std::uint8_t*       out,
                       const std::uint8_t* in) const noexcept override
    {
        ublock256256_dec_block(&round_key_, out, in);
    }

    void encrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ublock256256_enc_blocks(&round_key_, out, in, block_num);
    }

    void decrypt_blocks(std::uint8_t*       out,
                        const std::uint8_t* in,
                        std::size_t         block_num) const noexcept override
    {
        ublock256256_dec_blocks(&round_key_, out, in, block_num);
    }
};

std::unique_ptr<BlockCipher> create_cipher_256256()
{
    return std::make_unique<UBlock256256>();
}

std::unique_ptr<BlockCipherMode> create_ecb_encryptor_256256()
{
    return std::make_unique<EcbEncryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_ecb_decryptor_256256()
{
    return std::make_unique<EcbDecryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_encryptor_256256()
{
    return std::make_unique<CbcEncryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_cbc_decryptor_256256()
{
    return std::make_unique<CbcDecryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_encryptor_256256()
{
    return std::make_unique<OfbEncryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_ofb_decryptor_256256()
{
    return std::make_unique<OfbDecryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_encryptor_256256()
{
    return std::make_unique<CfbEncryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_cfb_decryptor_256256()
{
    return std::make_unique<CfbDecryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_encryptor_256256()
{
    return std::make_unique<CtrEncryptorImpl<UBlock256256>>();
}

std::unique_ptr<BlockCipherMode> create_ctr_decryptor_256256()
{
    return std::make_unique<CtrDecryptorImpl<UBlock256256>>();
}

} // namespace ublock::internal::standard

#endif
