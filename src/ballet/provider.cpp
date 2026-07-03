#include <gmlib/ballet/ballet.h>

#include <cstring>
#include <stdexcept>

#include "provider_ballet_standard.h"

namespace ballet {

Ballet128128::Cipher Ballet128128::create_cipher(const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cipher_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_ecb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ecb_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_ecb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ecb_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_cbc_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cbc_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_cbc_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cbc_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_ofb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ofb_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_ofb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ofb_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_cfb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cfb_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_cfb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cfb_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_ctr_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ctr_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_ctr_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ctr_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_gcm_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_gcm_encryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128128::CipherMode Ballet128128::create_gcm_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_gcm_decryptor_128128();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::Cipher Ballet128256::create_cipher(const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cipher_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_ecb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ecb_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_ecb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ecb_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_cbc_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cbc_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_cbc_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cbc_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_ofb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ofb_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_ofb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ofb_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_cfb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cfb_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_cfb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cfb_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_ctr_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ctr_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_ctr_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ctr_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_gcm_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_gcm_encryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet128256::CipherMode Ballet128256::create_gcm_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_gcm_decryptor_128256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::Cipher Ballet256256::create_cipher(const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cipher_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_ecb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ecb_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_ecb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ecb_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_cbc_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cbc_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_cbc_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cbc_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_ofb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ofb_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_ofb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ofb_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_cfb_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cfb_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_cfb_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_cfb_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_ctr_encryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ctr_encryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

Ballet256256::CipherMode Ballet256256::create_ctr_decryptor(
    const char* provider)
{
    if (ballet::internal::standard::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "standard") == 0)
        {
            return ballet::internal::standard::create_ctr_decryptor_256256();
        }
    }

    throw std::runtime_error("No provider available");
}

} // namespace ballet
