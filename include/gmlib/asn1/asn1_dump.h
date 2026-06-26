#ifndef ASN1_ASN1_DUMP_H
#define ASN1_ASN1_DUMP_H

#include <gmlib/asn1/asn1.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace asn1 {

namespace internal {

inline int r_asn1_dump(const std::uint8_t* in,
                       std::size_t         inl,
                       std::size_t         depth) noexcept
{
    Asn1TLV     tlv;
    std::size_t read_num;
    int         err;
    while (inl)
    {
        err = asn1_decode_tlv(&tlv, &read_num, in, inl);
        if (err)
        {
            return err;
        }
        // dump
        for (std::size_t i = 0; i < depth; i++) std::printf("   ");
        for (const std::uint8_t* ptr = in; ptr != tlv.value; ptr++)
        {
            std::printf("%02x ", *ptr);
        }
        for (std::size_t i = (std::size_t)tlv.value - (std::size_t)in;
             i < 8 + 1; i++)
        {
            std::printf("   ");
        }
        std::printf(";  %s(", asn1_tag_number_name(tlv.tag_number));
        std::printf("length = %zu Bytes", tlv.length);
        std::printf(",%s", asn1_tag_class_name(tlv.tag_class));
        std::printf(",%s)\n", asn1_tag_pc_name(tlv.tag_pc));
        if (tlv.tag_pc == ASN1_TAG_PC_CONSTRUCTED)
        {
            r_asn1_dump(tlv.value, tlv.length, depth + 1);
        }
        else
        {
            for (std::size_t i = 0; i < tlv.length; i++)
            {
                if (i % 8 == 0)
                {
                    for (std::size_t j = 0; j < depth + 1; j++)
                        std::printf("   ");
                }
                std::printf("%02x ", tlv.value[i]);
                if (i % 8 == 7) std::printf("\n");
            }
            if (tlv.length % 8 != 0) std::printf("\n");
        }
        // next
        in += read_num, inl -= read_num;
    }
    return 0;
}

} // namespace internal

/**
 * @brief       dump asn1 encoding to stdout
 * @param in    input asn1 encoding
 * @param inl   input length
 * @return      error code
 * @retval       0: Success
 * @retval      -1: Invalid Encoding
 * @retval      -2: Unsupport Encoding
 */
inline int asn1_dump(const std::uint8_t* in, std::size_t inl) noexcept
{
    return internal::r_asn1_dump(in, inl, 0);
}

} // namespace asn1

#endif