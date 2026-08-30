#ifndef BLOCK_CIPHER_MODE_IMPL_BLOCK_CIPHER_MODE_PROVIDER_IMPL_H
#define BLOCK_CIPHER_MODE_IMPL_BLOCK_CIPHER_MODE_PROVIDER_IMPL_H

#include <gmlib/block_cipher_mode/impl/cbc_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/cfb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ctr_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ecb_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/gcm_mode_impl.h>
#include <gmlib/block_cipher_mode/impl/ofb_mode_impl.h>
#include <gmlib/block_cipher_mode/provider.h>

#include <cstring>
#include <type_traits>

namespace block_cipher_mode::impl {

struct BlockCipherModeProviderEntry
{
    bool (*is_available)() noexcept;

    BlockCipherModeProvider provider;
};

template <typename BlockCipherTraits>
struct BlockCipherModeProviderImpl
{
    using Traits = BlockCipherTraits;

    static_assert(std::is_copy_constructible_v<typename Traits::Context>,
                  "Provider Context must be copy constructible");

    class BlockCipherAdapter : public BlockCipher
    {
    private:
        typename Traits::Context ctx_;

    public:
        ~BlockCipherAdapter() override
        {
            std::memset(&ctx_, 0, sizeof(ctx_));
        }

    public:
        static constexpr std::size_t BLOCK_SIZE = Traits::BLOCK_SIZE;

        static constexpr std::size_t USER_KEY_LEN = Traits::USER_KEY_LEN;

        static constexpr std::size_t PARALLEL_NUM = Traits::PARALLEL_NUM;

    public:
        const char* fetch_name() const noexcept override
        {
            return Traits::NAME;
        }

        const char* fetch_impl_algo() const noexcept override
        {
            return Traits::ALGO_NAME;
        }

        std::size_t fetch_block_size() const noexcept override
        {
            return Traits::BLOCK_SIZE;
        }

        std::size_t fetch_user_key_len() const noexcept override
        {
            return Traits::USER_KEY_LEN;
        }

        std::size_t fetch_parallel_num() const noexcept override
        {
            return Traits::PARALLEL_NUM;
        }

        std::size_t fetch_security_strength() const noexcept override
        {
            return Traits::SECURITY_STRENGTH;
        }

    public:
        std::unique_ptr<BlockCipher> clone() const override
        {
            return std::make_unique<BlockCipherAdapter>(*this);
        }

    public:
        void set_key(const std::uint8_t* user_key, int enc) override
        {
            if (enc == BlockCipher::ENCRYPTION)
            {
                Traits::enc_key_init(&ctx_, user_key);
            }
            else
            {
                Traits::dec_key_init(&ctx_, user_key);
            }
        }

        void encrypt_block(std::uint8_t*       out,
                           const std::uint8_t* in) const override
        {
            Traits::encrypt_block(&ctx_, out, in);
        }

        void decrypt_block(std::uint8_t*       out,
                           const std::uint8_t* in) const override
        {
            Traits::decrypt_block(&ctx_, out, in);
        }

        void encrypt_blocks(std::uint8_t*       out,
                            const std::uint8_t* in,
                            std::size_t         block_num) const override
        {
            Traits::encrypt_blocks(&ctx_, out, in, block_num);
        }

        void decrypt_blocks(std::uint8_t*       out,
                            const std::uint8_t* in,
                            std::size_t         block_num) const override
        {
            Traits::decrypt_blocks(&ctx_, out, in, block_num);
        }
    };

    static inline const BlockCipherModeProviderEntry entry = {
        Traits::is_available,
        {
            Traits::ALGO_NAME,
            []() -> std::unique_ptr<BlockCipher> {
                return std::make_unique<BlockCipherAdapter>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<EcbEncryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<EcbDecryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<CbcEncryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<CbcDecryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<CfbEncryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<CfbDecryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<OfbEncryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<OfbDecryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<CtrEncryptorImpl<BlockCipherAdapter>>();
            },
            []() -> std::unique_ptr<BlockCipherMode> {
                return std::make_unique<CtrDecryptorImpl<BlockCipherAdapter>>();
            },
            []() constexpr
            -> decltype(BlockCipherModeProvider::create_gcm_encryptor) {
                if constexpr (Traits::BLOCK_SIZE == 16)
                {
                    return []() -> std::unique_ptr<BlockCipherMode> {
                        return std::make_unique<
                            GcmEncryptorImpl<BlockCipherAdapter>>();
                    };
                }
                else
                {
                    return nullptr;
                }
            }(),
            []() constexpr
            -> decltype(BlockCipherModeProvider::create_gcm_decryptor) {
                if constexpr (Traits::BLOCK_SIZE == 16)
                {
                    return []() -> std::unique_ptr<BlockCipherMode> {
                        return std::make_unique<
                            GcmDecryptorImpl<BlockCipherAdapter>>();
                    };
                }
                else
                {
                    return nullptr;
                }
            }(),
        },
    };
};

inline const BlockCipherModeProvider* get_provider(
    const char*                               name,
    const BlockCipherModeProviderEntry* const provider_entry_lst[],
    std::size_t                               provider_entry_lst_len) noexcept
{
    if (name == nullptr)
    {
        for (std::size_t i = 0; i < provider_entry_lst_len; i++)
        {
            if (provider_entry_lst[i]->is_available())
            {
                return &provider_entry_lst[i]->provider;
            }
        }
        return nullptr;
    }

    for (std::size_t i = 0; i < provider_entry_lst_len; i++)
    {
        if (provider_entry_lst[i]->is_available() &&
            std::strcmp(provider_entry_lst[i]->provider.algo_name, name) == 0)
        {
            return &provider_entry_lst[i]->provider;
        }
    }
    return nullptr;
}

inline void get_supported_provider_names(
    const char**                              names_buffer,
    const BlockCipherModeProviderEntry* const provider_entry_lst[],
    std::size_t                               provider_entry_lst_len) noexcept
{
    std::size_t index = 0;
    for (std::size_t i = 0; i < provider_entry_lst_len; i++)
    {
        if (provider_entry_lst[i]->is_available())
        {
            names_buffer[index++] = provider_entry_lst[i]->provider.algo_name;
        }
    }
    names_buffer[index] = nullptr;
}

} // namespace block_cipher_mode::impl

#endif
