#include <gmlib/asn1/asn1.h>
#include <gmlib/asn1/asn1_dump.h>

#include <cstdio>
#include <cstdlib>

using namespace asn1;

int main()
{
    // SEQUENCE {
    //  INTEGER: 1
    //  BIT_STRING: 1111
    //  BIT_STRING  {
    //      BOOLEAN: TRUE
    //      BOOLEAN: FALSE
    //      OCTET_STRING: 20 21 22 23
    //  }
    //}

    std::uint8_t INTEGER_data1[1]      = {1};
    std::uint8_t BIT_STRING_data_1[1]  = {0b11110000};
    bool         BOOLEAN_data1         = true;
    bool         BOOLEAN_data2         = false;
    std::uint8_t OCTET_STRING_data1[4] = {0x20, 0x21, 0x22, 0x23};

    std::size_t octet_string_length =
        asn1_encode_octet_string_outl(sizeof(OCTET_STRING_data1));
    std::size_t boolean_2_length          = asn1_encode_boolean_outl();
    std::size_t boolean_1_length          = asn1_encode_boolean_outl();
    std::size_t bit_string_2_value_length = octet_string_length + //
                                            boolean_1_length +    //
                                            boolean_2_length;     //
    std::size_t bit_string_2_length =
        asn1_encode_tlv_outl(bit_string_2_value_length);
    std::size_t bit_string_1_length = asn1_encode_bit_string_outl(4);
    std::size_t integer_length =
        asn1_encode_integer_outl(INTEGER_data1, sizeof(INTEGER_data1));
    std::size_t sequence_value_length = integer_length +      //
                                        bit_string_1_length + //
                                        bit_string_2_length;  //
    std::size_t sequence_length =
        asn1_encode_sequence_outl(sequence_value_length);

    std::uint8_t buffer[                                                      //
        ASN1_ENCODE_SEQUENCE_MAX_OUTL(                                        //
            ASN1_ENCODE_INTEGER_MAX_OUTL(sizeof(INTEGER_data1)) +             //
            ASN1_ENCODE_BIT_STRING_MAX_OUTL(sizeof(BIT_STRING_data_1)) +      //
            ASN1_ENCODE_TLV_MAX_OUTL(                                         //
                ASN1_ENCODE_BOOLEAN_MAX_OUTL() +                              //
                ASN1_ENCODE_BOOLEAN_MAX_OUTL() +                              //
                ASN1_ENCODE_OCTET_STRING_MAX_OUTL(sizeof(OCTET_STRING_data1)) //
                )                                                             //
            )                                                                 //
    ];

    if (sequence_length > sizeof(buffer))
    {
        std::fprintf(stderr,
                     "err in predix ASN1 data length, file: %s, line: %d\n",
                     __FILE__, __LINE__);
        exit(-1);
    }

    std::uint8_t* out = buffer;
    std::size_t   outl;
    asn1_encode_sequence_tl(out, &outl, sequence_value_length);
    out += outl;
    asn1_encode_integer_tlv(out, &outl, INTEGER_data1, sizeof(INTEGER_data1));
    out += outl;
    asn1_encode_bit_string_tlv(out, &outl, BIT_STRING_data_1,
                               sizeof(BIT_STRING_data_1), 4);
    out += outl;
    asn1_encode_bit_string_tl(out, &outl, bit_string_2_value_length);
    out += outl;
    asn1_encode_boolean_tlv(out, &outl, BOOLEAN_data1);
    out += outl;
    asn1_encode_boolean_tlv(out, &outl, BOOLEAN_data2);
    out += outl;
    asn1_encode_octet_string_tlv(out, &outl, OCTET_STRING_data1,
                                 sizeof(OCTET_STRING_data1));
    out += outl;

    std::size_t size = (std::size_t)out - (std::size_t)buffer;
    if (size != sequence_length)
    {
        std::fprintf(stderr,
                     "err in predix ASN1 data length, file: %s, line: %d\n",
                     __FILE__, __LINE__);
        std::exit(-1);
    }

    int err = asn1_dump(buffer, size);
    if (err)
    {
        std::fprintf(stderr, "err in asn1_dump %d, file: %s, line: %d\n", err,
                     __FILE__, __LINE__);
        std::exit(-1);
    }
    std::puts("test asn1 finish");
    return 0;
}