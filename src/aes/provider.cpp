#include <gmlib/aes/aes.h>

#include <cstring>
#include <stdexcept>

#include "config.h"
#include "provider_aes_aesni.h"
#include "provider_aes_arm_aes.h"
#include "provider_aes_lut.h"

namespace aes {

AES128::Cipher AES128::create_cipher(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cipher_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cipher_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cipher_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_ecb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ecb_encryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ecb_encryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ecb_encryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_ecb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ecb_decryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ecb_decryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ecb_decryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_cbc_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cbc_encryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cbc_encryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cbc_encryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_cbc_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cbc_decryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cbc_decryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cbc_decryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_ofb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ofb_encryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ofb_encryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ofb_encryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_ofb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ofb_decryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ofb_decryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ofb_decryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_cfb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cfb_encryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cfb_encryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cfb_encryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_cfb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cfb_decryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cfb_decryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cfb_decryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_ctr_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ctr_encryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ctr_encryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ctr_encryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_ctr_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ctr_decryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ctr_decryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ctr_decryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_gcm_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_gcm_encryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_gcm_encryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_gcm_encryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES128::CipherMode AES128::create_gcm_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_gcm_decryptor_128();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_gcm_decryptor_128();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_gcm_decryptor_128();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::Cipher AES192::create_cipher(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cipher_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cipher_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cipher_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_ecb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ecb_encryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ecb_encryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ecb_encryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_ecb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ecb_decryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ecb_decryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ecb_decryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_cbc_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cbc_encryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cbc_encryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cbc_encryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_cbc_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cbc_decryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cbc_decryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cbc_decryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_ofb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ofb_encryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ofb_encryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ofb_encryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_ofb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ofb_decryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ofb_decryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ofb_decryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_cfb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cfb_encryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cfb_encryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cfb_encryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_cfb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cfb_decryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cfb_decryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cfb_decryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_ctr_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ctr_encryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ctr_encryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ctr_encryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_ctr_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ctr_decryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ctr_decryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ctr_decryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_gcm_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_gcm_encryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_gcm_encryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_gcm_encryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES192::CipherMode AES192::create_gcm_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_gcm_decryptor_192();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_gcm_decryptor_192();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_gcm_decryptor_192();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::Cipher AES256::create_cipher(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cipher_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cipher_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cipher_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_ecb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ecb_encryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ecb_encryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ecb_encryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_ecb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ecb_decryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ecb_decryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ecb_decryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_cbc_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cbc_encryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cbc_encryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cbc_encryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_cbc_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cbc_decryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cbc_decryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cbc_decryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_ofb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ofb_encryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ofb_encryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ofb_encryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_ofb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ofb_decryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ofb_decryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ofb_decryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_cfb_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cfb_encryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cfb_encryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cfb_encryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_cfb_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_cfb_decryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_cfb_decryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_cfb_decryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_ctr_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ctr_encryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ctr_encryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ctr_encryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_ctr_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_ctr_decryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_ctr_decryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_ctr_decryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_gcm_encryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_gcm_encryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_gcm_encryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_gcm_encryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

AES256::CipherMode AES256::create_gcm_decryptor(const char* provider)
{
#if defined(AES_IMPL_AESNI)
    if (aes::internal::aesni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "aesni") == 0)
        {
            return aes::internal::aesni::create_gcm_decryptor_256();
        }
    }
#endif
#if defined(AES_IMPL_ARM_AES)
    if (aes::internal::arm_aes::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "arm_aes") == 0)
        {
            return aes::internal::arm_aes::create_gcm_decryptor_256();
        }
    }
#endif
    if (aes::internal::lut::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lut") == 0)
        {
            return aes::internal::lut::create_gcm_decryptor_256();
        }
    }

    throw std::runtime_error("No provider available");
}

} // namespace aes
