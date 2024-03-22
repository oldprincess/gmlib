#ifndef ASN1_ASN1_H
#define ASN1_ASN1_H

#include <cstddef>
#include <cstdint>

namespace asn1 {

typedef enum Asn1TagClass
{
    ASN1_TAG_CLASS_UNIVERSAL        = 0b00000000,
    ASN1_TAG_CLASS_APPLICATION      = 0b01000000,
    ASN1_TAG_CLASS_CONTEXT_SPECIFIC = 0b10000000,
    ASN1_TAG_CLASS_PRIVATE          = 0b11000000,
} Asn1TagClass;

typedef enum Asn1TagPC
{
    ASN1_TAG_PC_PRIMITIVE   = 0b00000000,
    ASN1_TAG_PC_CONSTRUCTED = 0b00100000,
} Asn1TagPC;

typedef enum Asn1TagNumber
{
    ASN1_TAG_END_OF_CONTENTS   = 0, // MUST PRIMITIVE
    ASN1_TAG_BOOLEAN           = 1, // MUST PRIMITIVE
    ASN1_TAG_INTEGER           = 2, // MUST PRIMITIVE
    ASN1_TAG_BIT_STRING        = 3, // PRIMITIVE OR CONSTRUCTED
    ASN1_TAG_OCTET_STRING      = 4, // PRIMITIVE OR CONSTRUCTED
    ASN1_TAG_NULL              = 5, // MUST PRIMITIVE
    ASN1_TAG_OBJECT_IDENTIFIER = 6,
    ASN1_TAG_OBJECT_DESCRIPTOR = 7,
    ASN1_TAG_EXTERNAL          = 8,
    ASN1_TAG_REAL              = 9,
    ASN1_TAG_ENUMERATED        = 10,
    ASN1_TAG_UTF8_STRING       = 12,
    ASN1_TAG_SEQUENCE          = 16, // MUST CONSTRUCTED
    ASN1_TAG_SET               = 17, // MUST CONSTRUCTED
    ASN1_TAG_NUMERIC_STRING    = 18,
    ASN1_TAG_PRINTABLE_STRING  = 19,
    ASN1_TAG_TELETEX_STRING    = 20,
    ASN1_TAG_VIDEOTEX_STRING   = 21,
    ASN1_TAG_IA5_STRING        = 22,
    ASN1_TAG_UTC_TIME          = 23,
    ASN1_TAG_GENERALIZED_TIME  = 24,
    ASN1_TAG_GRAPHIC_STRING    = 25,
    ASN1_TAG_VISIBLE_STRING    = 26,
    ASN1_TAG_GENERAL_STRING    = 27,
    ASN1_TAG_UNIVERSAL_STRING  = 28,
    ASN1_TAG_BMP_STRING        = 30,
} Asn1TagNumber;

typedef struct Asn1TLV
{
    Asn1TagClass        tag_class;
    Asn1TagPC           tag_pc;
    Asn1TagNumber       tag_number;
    std::size_t         length;
    const std::uint8_t* value;
} Asn1TLV;

/**
 * @brief           decode ASN.1 TLV node
 * @param tlv       ASN.1 TLV struct
 * @param read_num  read number of bytes
 * @param in        input asn1 encoding
 * @param inl       input length
 * @return          error code
 * @retval           0: Success
 * @retval          -1: Invalid Encoding
 * @retval          -2: Unsupport Encoding
 */
int asn1_decode_tlv(Asn1TLV*            tlv,
                    std::size_t*        read_num,
                    const std::uint8_t* in,
                    std::size_t         inl) noexcept;

/**
 * @brief get ASN.1 TAG class name
 */
const char* asn1_tag_class_name(Asn1TagClass tag_class) noexcept;

/**
 * @brief get ASN.1 TAG PRIMITIVE/CONSTRUCTED name
 */
const char* asn1_tag_pc_name(Asn1TagPC tag_pc) noexcept;

/**
 * @brief get ASN.1 TAG NUMBER name
 */
const char* asn1_tag_number_name(Asn1TagNumber tag_number) noexcept;

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// **************************************************
// ************ ASN1 ENCODING/DECODING **************
// **************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++++

// ****************************************
// ************ ENCODING ******************
// ****************************************

size_t asn1_encode_tlv_outl(std::size_t value_length) noexcept;

size_t asn1_encode_boolean_outl() noexcept;

size_t asn1_encode_integer_outl(const std::uint8_t* data,
                                std::size_t         data_len) noexcept;

size_t asn1_encode_bit_string_outl(std::size_t bits) noexcept;

size_t asn1_encode_octet_string_outl(std::size_t data_len) noexcept;

size_t asn1_encode_sequence_outl(std::size_t value_length) noexcept;

size_t asn1_encode_set_outl(std::size_t value_length) noexcept;

void asn1_encode_boolean_tlv(std::uint8_t* out,
                             std::size_t*  outl,
                             bool          value) noexcept;

void asn1_encode_integer_tlv(std::uint8_t*       out,
                             std::size_t*        outl,
                             const std::uint8_t* data,
                             std::size_t         data_len) noexcept;

void asn1_encode_bit_string_tl(std::uint8_t* out,
                               std::size_t*  outl,
                               std::size_t   value_length) noexcept;

void asn1_encode_bit_string_tlv(std::uint8_t*       outr,
                                std::size_t*        outl,
                                const std::uint8_t* data,
                                std::size_t         data_len,
                                std::size_t         data_bits) noexcept;

void asn1_encode_octet_string_tl(std::uint8_t* out,
                                 std::size_t*  outl,
                                 std::size_t   value_length) noexcept;

void asn1_encode_octet_string_tlv(std::uint8_t*       out,
                                  std::size_t*        outl,
                                  const std::uint8_t* data,
                                  std::size_t         data_len) noexcept;

void asn1_encode_sequence_tl(std::uint8_t* out,
                             std::size_t*  outl,
                             std::size_t   value_length) noexcept;

void asn1_encode_set_tl(std::uint8_t* out,
                        std::size_t*  outl,
                        std::size_t   value_length) noexcept;

static constexpr std::size_t ASN1_ENCODE_TLV_MAX_OUTL(
    std::size_t value_length) noexcept
{
    return 1 + (1 + sizeof(size_t)) + value_length;
}

static constexpr std::size_t ASN1_ENCODE_BOOLEAN_MAX_OUTL() noexcept
{
    return 3;
}

static constexpr std::size_t ASN1_ENCODE_INTEGER_MAX_OUTL(
    std::size_t data_length) noexcept
{
    return ASN1_ENCODE_TLV_MAX_OUTL(data_length + 1);
}

static constexpr std::size_t ASN1_ENCODE_BIT_STRING_MAX_OUTL(
    std::size_t bits) noexcept
{
    return ASN1_ENCODE_TLV_MAX_OUTL(1 + (bits + 7 / 8));
}

static constexpr std::size_t ASN1_ENCODE_OCTET_STRING_MAX_OUTL(
    std::size_t value_length) noexcept
{
    return ASN1_ENCODE_TLV_MAX_OUTL(value_length);
}

static constexpr std::size_t ASN1_ENCODE_SEQUENCE_MAX_OUTL(
    std::size_t value_length) noexcept
{
    return ASN1_ENCODE_TLV_MAX_OUTL(value_length);
}

static constexpr std::size_t ASN1_ENCODE_SET_MAX_OUTL(
    std::size_t value_length) noexcept
{
    return ASN1_ENCODE_TLV_MAX_OUTL(value_length);
}

// ****************************************
// ************ DECODING ******************
// ****************************************

int asn1_decode_boolean_value(bool*               ret,
                              std::size_t*        read_num,
                              const std::uint8_t* in,
                              std::size_t         inl) noexcept;

int asn1_decode_integer_value(const std::uint8_t** data_ptr,
                              std::size_t*         data_length,
                              std::size_t*         read_num,
                              const std::uint8_t*  in,
                              std::size_t          inl) noexcept;

int asn1_decode_bit_string_value(const std::uint8_t** data_ptr,
                                 std::size_t*         data_length,
                                 std::size_t*         bits_length,
                                 std::size_t*         read_num,
                                 const std::uint8_t*  in,
                                 std::size_t          inl) noexcept;

int asn1_decode_octet_string_value(const std::uint8_t** data_ptr,
                                   std::size_t*         data_length,
                                   std::size_t*         read_num,
                                   const std::uint8_t*  in,
                                   std::size_t          inl) noexcept;

int asn1_decode_null_value(std::size_t*        read_num,
                           const std::uint8_t* in,
                           std::size_t         inl) noexcept;

int asn1_decode_sequence_value(const std::uint8_t** value_ptr,
                               std::size_t*         value_length,
                               std::size_t*         read_num,
                               const std::uint8_t*  in,
                               std::size_t          inl) noexcept;

int asn1_decode_set_value(const std::uint8_t** value_ptr,
                          std::size_t*         value_length,
                          std::size_t*         read_num,
                          const std::uint8_t*  in,
                          std::size_t          inl) noexcept;

} // namespace asn1

#endif