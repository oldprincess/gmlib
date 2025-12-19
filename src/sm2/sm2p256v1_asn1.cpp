#include <gmlib/asn1/asn1.h>
#include <gmlib/sm2/internal/sm2_asn1.h>

#include <cstdio>
#include <cstring>

namespace sm2::internal {

// ****************************************
// ********** PrivateKey ******************
// ****************************************

std::size_t sm2_private_key_asn1_encode_outl(const ASN1_SM2PrivateKey* priv)
{
    return asn1::asn1_encode_integer_outl(priv->value, 32);
}

void sm2_private_key_asn1_encode_outl(std::uint8_t*             out,
                                      std::size_t*              outl,
                                      const ASN1_SM2PrivateKey* priv)
{
    asn1::asn1_encode_integer_tlv(out, outl, priv->value, 32);
}

int sm2_private_key_asn1_decode(ASN1_SM2PrivateKey* priv,
                                std::size_t*        read_num,
                                const std::uint8_t* in,
                                std::size_t         inl)
{
    std::size_t data_length;
    if (asn1::asn1_decode_integer_value(&priv->value, &data_length, read_num,
                                        in, inl))
    {
        return -1;
    }
    if (data_length != 32)
    {
        return -1;
    }
    return 0;
}

// ****************************************
// *********** PublicKey ******************
// ****************************************

std::size_t sm2_public_key_asn1_encode_outl(const ASN1_SM2PublicKey* pub)
{
    (pub); // avoid warning C4100 in MSVC
    return asn1::asn1_encode_bit_string_outl(65 * 8);
}

void sm2_public_key_asn1_encode(std::uint8_t*            out,
                                std::size_t*             outl,
                                const ASN1_SM2PublicKey* pub)
{
    asn1::asn1_encode_bit_string_tlv(out, outl, pub->value, 65, 65 * 8);
}

int sm2_public_key_asn1_decode(ASN1_SM2PublicKey*  pub,
                               std::size_t*        read_num,
                               const std::uint8_t* in,
                               std::size_t         inl)
{
    std::size_t data_length, data_bits;
    if (asn1::asn1_decode_bit_string_value(&pub->value, &data_length,
                                           &data_bits, read_num, in, inl))
    {
        return -1;
    }
    if (data_length != 65 && data_bits != 65 * 8)
    {
        return -1;
    }
    return 0;
}

// ****************************************
// *********** Signature ******************
// ****************************************

std::size_t sm2_signature_asn1_encode_outl(const ASN1_SM2Signature* sig)
{
    return asn1::asn1_encode_sequence_outl(
        asn1::asn1_encode_integer_outl(sig->R.value, sig->R.length) +
        asn1::asn1_encode_integer_outl(sig->S.value, sig->S.length));
}

void sm2_signature_asn1_encode(std::uint8_t*            out,
                               std::size_t*             outl,
                               const ASN1_SM2Signature* sig)
{
    std::size_t seq_v_len =
        asn1::asn1_encode_integer_outl(sig->R.value, sig->R.length) +
        asn1::asn1_encode_integer_outl(sig->S.value, sig->S.length);

    std::size_t   n;
    std::uint8_t* out_save = out;
    asn1::asn1_encode_sequence_tl(out, &n, seq_v_len);
    out += n;
    asn1::asn1_encode_integer_tlv(out, &n, sig->R.value, sig->R.length);
    out += n;
    asn1::asn1_encode_integer_tlv(out, &n, sig->S.value, sig->S.length);
    out += n;
    *outl = (std::size_t)out - (std::size_t)out_save;
}

int sm2_signature_asn1_decode(ASN1_SM2Signature*  sig,
                              std::size_t*        read_num,
                              const std::uint8_t* in,
                              std::size_t         inl)
{
    std::size_t inl_save = inl, n;

    const std::uint8_t* seq_value;
    std::size_t         seq_v_len;

    // decode SEQUENCE
    if (asn1::asn1_decode_sequence_value(&seq_value, &seq_v_len, &n, in, inl))
    {
        return -1;
    }
    in += n, inl -= n;
    // decode INTEGER
    if (asn1::asn1_decode_integer_value(&sig->R.value, &sig->R.length, &n,
                                        seq_value, seq_v_len))
    {
        return -1;
    }
    if (sig->R.length > 32)
    {
        return -1;
    }
    seq_value += n, seq_v_len -= n;
    // decode INTEGER
    if (asn1::asn1_decode_integer_value(&sig->S.value, &sig->S.length, &n,
                                        seq_value, seq_v_len))
    {
        return -1;
    }
    if (sig->S.length > 32)
    {
        return -1;
    }
    *read_num = inl_save - inl;
    return 0;
}

// ****************************************
// ************ cipher ********************
// ****************************************

std::size_t sm2_cipher_asn1_encode_max_outl(std::size_t C3_length,
                                            std::size_t C2_length)
{
    return asn1::ASN1_ENCODE_SEQUENCE_MAX_OUTL(
        asn1::ASN1_ENCODE_INTEGER_MAX_OUTL(32) +             //
        asn1::ASN1_ENCODE_INTEGER_MAX_OUTL(32) +             //
        asn1::ASN1_ENCODE_OCTET_STRING_MAX_OUTL(C3_length) + //
        asn1::ASN1_ENCODE_OCTET_STRING_MAX_OUTL(C2_length));
}

std::size_t sm2_cipher_asn1_encode_outl(const ASN1_SM2Cipher* cipher)
{
    return asn1::asn1_encode_sequence_outl(
        asn1::asn1_encode_integer_outl(cipher->XCoordinate.value,
                                       cipher->XCoordinate.length) +
        asn1::asn1_encode_integer_outl(cipher->YCoordinate.value,
                                       cipher->YCoordinate.length) +
        asn1::asn1_encode_octet_string_outl(cipher->HASH.length) +
        asn1::asn1_encode_octet_string_outl(cipher->CipherText.length));
}

void sm2_cipher_asn1_encode(std::uint8_t*         out,
                            std::size_t*          outl,
                            const ASN1_SM2Cipher* cipher)
{
    std::size_t seq_v_len =
        asn1::asn1_encode_integer_outl(cipher->XCoordinate.value,
                                       cipher->XCoordinate.length) +
        asn1::asn1_encode_integer_outl(cipher->YCoordinate.value,
                                       cipher->YCoordinate.length) +
        asn1::asn1_encode_octet_string_outl(cipher->HASH.length) +
        asn1::asn1_encode_octet_string_outl(cipher->CipherText.length);

    std::size_t   n;
    std::uint8_t* out_save = out;
    asn1::asn1_encode_sequence_tl(out, &n, seq_v_len);
    out += n;
    asn1::asn1_encode_integer_tlv(out, &n, cipher->XCoordinate.value,
                                  cipher->XCoordinate.length);
    out += n;
    asn1::asn1_encode_integer_tlv(out, &n, cipher->YCoordinate.value,
                                  cipher->YCoordinate.length);
    out += n;
    asn1::asn1_encode_octet_string_tlv(out, &n, cipher->HASH.value,
                                       cipher->HASH.length);
    out += n;
    asn1::asn1_encode_octet_string_tlv(out, &n, cipher->CipherText.value,
                                       cipher->CipherText.length);
    out += n;
    *outl = (std::size_t)(out) - (std::size_t)(out_save);
}

int sm2_cipher_asn1_decode(ASN1_SM2Cipher*     cipher,
                           std::size_t*        read_num,
                           const std::uint8_t* in,
                           std::size_t         inl)
{
    std::size_t inl_save = inl, n;

    const std::uint8_t* seq_value;
    std::size_t         seq_v_len;

    if (asn1::asn1_decode_sequence_value(&seq_value, &seq_v_len, &n, in, inl))
    {
        return -1;
    }
    in += n, inl -= n;
    if (asn1::asn1_decode_integer_value(&cipher->XCoordinate.value,
                                        &cipher->XCoordinate.length, &n,
                                        seq_value, seq_v_len))
    {
        return -1;
    }
    if (cipher->XCoordinate.length > 32)
    {
        return -1;
    }
    seq_value += n, seq_v_len -= n;
    if (asn1::asn1_decode_integer_value(&cipher->YCoordinate.value,
                                        &cipher->YCoordinate.length, &n,
                                        seq_value, seq_v_len))
    {
        return -1;
    }
    if (cipher->YCoordinate.length > 32)
    {
        return -1;
    }
    seq_value += n, seq_v_len -= n;
    if (asn1::asn1_decode_octet_string_value(&cipher->HASH.value,
                                             &cipher->HASH.length, &n,
                                             seq_value, seq_v_len))
    {
        return -1;
    }
    seq_value += n, seq_v_len -= n;
    if (asn1::asn1_decode_octet_string_value(&cipher->CipherText.value,
                                             &cipher->CipherText.length, &n,
                                             seq_value, seq_v_len))
    {
        return -1;
    }
    seq_value += n, seq_v_len -= n;
    *read_num = inl_save - inl;
    return 0;
}

} // namespace sm2::internal