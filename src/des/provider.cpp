#include <gmlib/des/des.h>

#include <cstring>
#include <stdexcept>

#include "config.h"
#include "provider_des_common.h"

namespace des {

DES::Cipher DES::create_cipher(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_cipher();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_ecb_encryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_ecb_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_ecb_decryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_ecb_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_cbc_encryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_cbc_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_cbc_decryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_cbc_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_ofb_encryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_ofb_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_ofb_decryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_ofb_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_cfb_encryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_cfb_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_cfb_decryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_cfb_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_ctr_encryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_ctr_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

DES::CipherMode DES::create_ctr_decryptor(const char* provider)
{
    if (des::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return des::internal::common::create_ctr_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

}; // namespace des
