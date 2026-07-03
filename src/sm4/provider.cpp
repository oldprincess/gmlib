#include <gmlib/sm4/sm4.h>

#include <cstring>
#include <stdexcept>

#include "provider_sm4_common.h"
#include "provider_sm4_gong23.h"
#include "provider_sm4_lang18.h"
#include "provider_sm4_sm4ni.h"

namespace sm4 {

SM4::Cipher SM4::create_cipher(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_cipher();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_cipher();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_cipher();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_cipher();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_ecb_encryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_ecb_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_ecb_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_ecb_encryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_ecb_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_ecb_decryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_ecb_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_ecb_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_ecb_decryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_ecb_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_cbc_encryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_cbc_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_cbc_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_cbc_encryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_cbc_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_cbc_decryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_cbc_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_cbc_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_cbc_decryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_cbc_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_ofb_encryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_ofb_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_ofb_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_ofb_encryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_ofb_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_ofb_decryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_ofb_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_ofb_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_ofb_decryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_ofb_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_cfb_encryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_cfb_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_cfb_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_cfb_encryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_cfb_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_cfb_decryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_cfb_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_cfb_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_cfb_decryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_cfb_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_ctr_encryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_ctr_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_ctr_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_ctr_encryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_ctr_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_ctr_decryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_ctr_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_ctr_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_ctr_decryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_ctr_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_gcm_encryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_gcm_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_gcm_encryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_gcm_encryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_gcm_encryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

SM4::CipherMode SM4::create_gcm_decryptor(const char* provider)
{
#if defined(SM4_IMPL_GONG23)
    if (sm4::internal::gong23::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "gong23") == 0)
        {
            return sm4::internal::gong23::create_gcm_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_LANG18)
    if (sm4::internal::lang18::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "lang18") == 0)
        {
            return sm4::internal::lang18::create_gcm_decryptor();
        }
    }
#endif
#if defined(SM4_IMPL_SM4NI)
    if (sm4::internal::sm4ni::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "sm4ni") == 0)
        {
            return sm4::internal::sm4ni::create_gcm_decryptor();
        }
    }
#endif
    if (sm4::internal::common::provider_available())
    {
        if (provider == nullptr || std::strcmp(provider, "common") == 0)
        {
            return sm4::internal::common::create_gcm_decryptor();
        }
    }

    throw std::runtime_error("No provider available");
}

}; // namespace sm4
