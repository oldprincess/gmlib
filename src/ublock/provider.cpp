#include <gmlib/ublock/ublock.h>

#include <cstring>
#include <stdexcept>

#include "config.h"
#include "provider_ublock_common.h"
#include "provider_ublock_gong25.h"
#include "provider_ublock_standard.h"

namespace ublock {

uBlock128128::Cipher uBlock128128::create_cipher(const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cipher_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cipher_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cipher_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_ecb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ecb_encryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ecb_encryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ecb_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_ecb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ecb_decryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ecb_decryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ecb_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_cbc_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cbc_encryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cbc_encryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cbc_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_cbc_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cbc_decryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cbc_decryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cbc_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_ofb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ofb_encryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ofb_encryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ofb_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_ofb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ofb_decryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ofb_decryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ofb_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_cfb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cfb_encryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cfb_encryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cfb_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_cfb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cfb_decryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cfb_decryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cfb_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_ctr_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ctr_encryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ctr_encryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ctr_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_ctr_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ctr_decryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ctr_decryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ctr_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_gcm_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_gcm_encryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_gcm_encryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_gcm_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128128::CipherMode uBlock128128::create_gcm_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_gcm_decryptor_128128();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_gcm_decryptor_128128();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_gcm_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::Cipher uBlock128256::create_cipher(const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cipher_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cipher_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cipher_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_ecb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ecb_encryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ecb_encryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ecb_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_ecb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ecb_decryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ecb_decryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ecb_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_cbc_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cbc_encryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cbc_encryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cbc_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_cbc_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cbc_decryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cbc_decryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cbc_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_ofb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ofb_encryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ofb_encryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ofb_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_ofb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ofb_decryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ofb_decryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ofb_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_cfb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cfb_encryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cfb_encryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cfb_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_cfb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cfb_decryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cfb_decryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cfb_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_ctr_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ctr_encryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ctr_encryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ctr_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_ctr_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ctr_decryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ctr_decryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ctr_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_gcm_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_gcm_encryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_gcm_encryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_gcm_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock128256::CipherMode uBlock128256::create_gcm_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_gcm_decryptor_128256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_gcm_decryptor_128256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_gcm_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::Cipher uBlock256256::create_cipher(const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cipher_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cipher_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cipher_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_ecb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ecb_encryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ecb_encryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ecb_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_ecb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ecb_decryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ecb_decryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ecb_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_cbc_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cbc_encryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cbc_encryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cbc_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_cbc_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cbc_decryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cbc_decryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cbc_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_ofb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ofb_encryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ofb_encryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ofb_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_ofb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ofb_decryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ofb_decryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ofb_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_cfb_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cfb_encryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cfb_encryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cfb_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_cfb_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_cfb_decryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_cfb_decryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_cfb_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_ctr_encryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ctr_encryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ctr_encryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ctr_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

uBlock256256::CipherMode uBlock256256::create_ctr_decryptor(
    const char* provider)
{
#if defined(UBLOCK_IMPL_GONG25)
    if (ublock::internal::gong25::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong25") == 0)
        {
            return ublock::internal::gong25::create_ctr_decryptor_256256();
        }
    }
#endif
#if defined(UBLOCK_IMPL_STANDARD)
    if (ublock::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ublock::internal::standard::create_ctr_decryptor_256256();
        }
    }
#endif
    if (ublock::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return ublock::internal::common::create_ctr_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

} // namespace ublock
