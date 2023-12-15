#ifndef _GMLIB_CRYPTO_KDF_PBKDF2_H
#define _GMLIB_CRYPTO_KDF_PBKDF2_H

#include <gmlib/exception.h>

namespace gmlib {

/**
 * @brief           pbkdf2, use HMAC as PRF
 * @cite            https://www.rfc-editor.org/rfc/rfc2898
 * @tparam HMAC     hmac function
 * @param dk        derived key, a dkLen-octet string
 * @param dk_len    intended length in octets of the derived key,
 *                  a positive integer, at most (2^32 - 1) * hLen
 * @param password  password, an octet string
 * @param p_len     password length
 * @param salt      salt, an octet string
 * @param s_len     salt length
 * @param c         iteration count, a positive integer
 */
template <class HMAC>
void pbkdf2_hmac(uint8_t*       dk,
                 size_t         dk_len,
                 const uint8_t* password,
                 size_t         p_len,
                 const uint8_t* salt,
                 size_t         s_len,
                 size_t         c)
{
    constexpr size_t h_len = HMAC::DIGEST_SIZE;
    if (dk_len > UINT32_MAX * h_len)
    {
        throw gmlib::Exception("derived key too long");
    }
    HMAC     hmac_st = HMAC(password, p_len);
    uint8_t  U[HMAC::DIGEST_SIZE];
    uint32_t i = 1;
    uint8_t  i_buf[4];
    while (dk_len >= h_len)
    {
        HMAC hmac = hmac_st;
        hmac.update(salt, s_len);
        i_buf[0] = (uint8_t)(i >> 24);
        i_buf[1] = (uint8_t)(i >> 16);
        i_buf[2] = (uint8_t)(i >> 8);
        i_buf[3] = (uint8_t)(i >> 0);
        hmac.update(i_buf, 4);
        hmac.final(U);
        memcpy(dk, U, HMAC::DIGEST_SIZE);
        for (size_t j = 1; j < c; j++)
        {
            HMAC hmac = hmac_st;
            hmac.update(U, HMAC::DIGEST_SIZE);
            hmac.final(U);
            for (size_t k = 0; k < HMAC::DIGEST_SIZE; k++)
            {
                dk[k] ^= U[k];
            }
        }
        dk += h_len, dk_len -= h_len;
        i++;
    }
    if (dk_len)
    {
        uint8_t tmp_dk[HMAC::DIGEST_SIZE];
        HMAC    hmac = hmac_st;
        hmac.update(salt, s_len);
        i_buf[0] = (uint8_t)(i >> 24);
        i_buf[1] = (uint8_t)(i >> 16);
        i_buf[2] = (uint8_t)(i >> 8);
        i_buf[3] = (uint8_t)(i >> 0);
        hmac.update(i_buf, 4);
        hmac.final(U);
        memcpy(tmp_dk, U, HMAC::DIGEST_SIZE);
        for (size_t j = 1; j < c; j++)
        {
            HMAC hmac = hmac_st;
            hmac.update(U, HMAC::DIGEST_SIZE);
            hmac.final(U);
            for (size_t k = 0; k < HMAC::DIGEST_SIZE; k++)
            {
                tmp_dk[k] ^= U[k];
            }
        }
        memcpy(dk, tmp_dk, dk_len);
    }
}

} // namespace gmlib

#endif