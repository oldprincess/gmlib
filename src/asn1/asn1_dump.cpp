#include <gmlib/asn1/asn1.h>
#include <gmlib/asn1/asn1_dump.h>

#include <cstdio>

namespace asn1 {

static int r_asn1_dump(const std::uint8_t* in,
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
        for (std::size_t i = 0; i < depth; i++) printf("   ");
        for (const std::uint8_t* ptr = in; ptr != tlv.value; ptr++)
        {
            printf("%02x ", *ptr);
        }
        for (std::size_t i = (std::size_t)tlv.value - (std::size_t)in;
             i < 8 + 1; i++)
        {
            printf("   ");
        }
        printf(";  %s(", asn1_tag_number_name(tlv.tag_number));
        printf("length = %zu Bytes", tlv.length);
        printf(",%s", asn1_tag_class_name(tlv.tag_class));
        printf(",%s)\n", asn1_tag_pc_name(tlv.tag_pc));
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
                    for (std::size_t j = 0; j < depth + 1; j++) printf("   ");
                }
                printf("%02x ", tlv.value[i]);
                if (i % 8 == 7) printf("\n");
            }
            if (tlv.length % 8 != 0) printf("\n");
        }
        // next
        in += read_num, inl -= read_num;
    }
    return 0;
}

int asn1_dump(const std::uint8_t* in, std::size_t inl) noexcept
{
    return r_asn1_dump(in, inl, 0);
}

} // namespace asn1
