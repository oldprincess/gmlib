#ifndef SM2_INTERNAL_SM2_ASN1_H
#define SM2_INTERNAL_SM2_ASN1_H

#include <gmlib/asn1/asn1.h>

#include <cstddef>
#include <cstdint>

namespace sm2::internal {

// ****************************************
// ********** PrivateKey ******************
// ****************************************

/**
 * SM2PrivateKey ::= INTEGER
 */
typedef struct ASN1_SM2PrivateKey
{
    const std::uint8_t* value; // INTEGER 256-bit(32-bytes)
} ASN1_SM2PrivateKey;

static constexpr std::size_t SM2_PRIVATE_KEY_ASN1_ENCODE_MAX_OUTL()
{
    return asn1::ASN1_ENCODE_INTEGER_MAX_OUTL(32);
}

std::size_t sm2_private_key_asn1_encode_outl(const ASN1_SM2PrivateKey* priv);

void sm2_private_key_asn1_encode_outl(std::uint8_t*             out,
                                      std::size_t*              outl,
                                      const ASN1_SM2PrivateKey* priv);

int sm2_private_key_asn1_decode(ASN1_SM2PrivateKey* priv,
                                std::size_t*        read_num,
                                const std::uint8_t* in,
                                std::size_t         inl);

// ****************************************
// *********** PublicKey ******************
// ****************************************

/**
 * SM2PublicKey ::= BIT STRING
 * 04 || X || Y
 */
typedef struct ASN1_SM2PublicKey
{
    const std::uint8_t* value; // BIT STRING 8+256+256=520-bit (65 bytes)
} ASN1_SM2PublicKey;

static constexpr std::size_t SM2_PUBLIC_KEY_ASN1_ENCODE_MAX_OUTL()
{
    return asn1::ASN1_ENCODE_BIT_STRING_MAX_OUTL(65 * 8);
}

std::size_t sm2_public_key_asn1_encode_outl(const ASN1_SM2PublicKey* pub);

void sm2_public_key_asn1_encode(std::uint8_t*            out,
                                std::size_t*             outl,
                                const ASN1_SM2PublicKey* pub);

int sm2_public_key_asn1_decode(ASN1_SM2PublicKey*  pub,
                               std::size_t*        read_num,
                               const std::uint8_t* in,
                               std::size_t         inl);

// ****************************************
// *********** Signature ******************
// ****************************************

/**
 * SM2Signature ::= SEQUENCE {
 *      R   INTEGER,
 *      S   INTEGER
 * }
 */
typedef struct ASN1_SM2Signature
{
    const std::uint8_t* R; // INTEGER 256-bit(32-bytes)
    const std::uint8_t* S; // INTEGER 256-bit(32-bytes)
} ASN1_SM2Signature;

static constexpr std::size_t SM2_SIGNATURE_ASN1_ENCODE_MAX_OUTL()
{
    return asn1::ASN1_ENCODE_SEQUENCE_MAX_OUTL(
        asn1::ASN1_ENCODE_INTEGER_MAX_OUTL(32) +
        asn1::ASN1_ENCODE_INTEGER_MAX_OUTL(32));
}

std::size_t sm2_signature_asn1_encode_outl(const ASN1_SM2Signature* sig);

void sm2_signature_asn1_encode(std::uint8_t*            out,
                               std::size_t*             outl,
                               const ASN1_SM2Signature* sig);

int sm2_signature_asn1_decode(ASN1_SM2Signature*  sig,
                              std::size_t*        read_num,
                              const std::uint8_t* in,
                              std::size_t         inl);

// ****************************************
// ************ cipher ********************
// ****************************************

/**
 * SM2Cipher ::= SEQUENCE {
 *      XCoordinate     INTEGER,
 *      YCoordinate     INTEGER,
 *      HASH            OCTET STRING,
 *      CipherText      OCTET STRING
 * }
 */
typedef struct ASN1_SM2Cipher
{
    const std::uint8_t* XCoordinate; // INTEGER 256-bit(32-bytes)
    const std::uint8_t* YCoordinate; // INTEGER 256-bit(32-bytes)
    struct C3
    {
        const std::uint8_t* value;
        std::size_t         length;
    } HASH; // OCTET STRING
    struct C2
    {
        const std::uint8_t* value;
        std::size_t         length;
    } CipherText; // OCTET STRING
} ASN1_SM2Cipher;

std::size_t sm2_cipher_asn1_encode_max_outl(std::size_t C3_length,
                                            std::size_t C2_length);

std::size_t sm2_cipher_asn1_encode_outl(const ASN1_SM2Cipher* cipher);

void sm2_cipher_asn1_encode(std::uint8_t*         out,
                            std::size_t*          outl,
                            const ASN1_SM2Cipher* cipher);

int sm2_cipher_asn1_decode(ASN1_SM2Cipher*     cipher,
                           std::size_t*        read_num,
                           const std::uint8_t* in,
                           std::size_t         inl);

} // namespace sm2::internal

#endif