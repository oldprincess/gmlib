#include "base64_common.h"

#if defined(BASE64_IMPL_COMMON)

namespace base64::internal::common {

// base64_char -> byte
static const uint8_t B64_MAP[256] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 253, 255, 255, 253, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62,  255,
    255, 255, 63,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  255, 255,
    255, 254, 255, 255, 255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
    10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
    25,  255, 255, 255, 255, 255, 255, 26,  27,  28,  29,  30,  31,  32,  33,
    34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
    49,  50,  51,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255,
};

// index -> base64_char
static const char B64_TABLE[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

bool base64_is_b64(const char* in, std::size_t inl) noexcept
{
    if (inl % 4 != 0)
    {
        return false;
    }
    for (size_t i = 0; i < inl; i++)
    {
        if (B64_MAP[(int)in[i]] == (uint8_t)(-1))
        {
            return false;
        }
    }
    return true;
}

std::size_t base64_encode_outl(std::size_t inl) noexcept
{
    return ((inl + 2) / 3) * 4 + 1;
}

std::size_t base64_encode_strl(std::size_t inl) noexcept
{
    return ((inl + 2) / 3) * 4;
}

std::size_t base64_decode_outl(const char* in, std::size_t inl) noexcept
{
    if (inl == 0)
    {
        return 0;
    }
    int last1 = (in[inl - 1] == '=') ? 1 : 0;
    int last2 = (in[inl - 2] == '=') ? 1 : 0;
    return 3 * (inl / 4) - last1 - last2;
}

void base64_encode(char* out, const std::uint8_t* in, std::size_t inl) noexcept
{
    while (inl > 3)
    {
        uint8_t d0 = *(in + 0), d1 = *(in + 1), d2 = *(in + 2);
        *(out + 0) = B64_TABLE[d0 >> 2];
        *(out + 1) = B64_TABLE[(d0 & 0x3) << 4 | d1 >> 4];
        *(out + 2) = B64_TABLE[(d1 & 0xf) << 2 | d2 >> 6];
        *(out + 3) = B64_TABLE[d2 & 0x3f];
        out += 4, in += 3, inl -= 3;
    }
    if (inl == 2)
    {
        uint8_t d0 = *(in + 0), d1 = *(in + 1);
        *(out + 0) = B64_TABLE[d0 >> 2];
        *(out + 1) = B64_TABLE[(d0 & 0x3) << 4 | d1 >> 4];
        *(out + 2) = B64_TABLE[(d1 & 0xf) << 2 | 0];
        *(out + 3) = '=';
        out += 4;
    }
    else if (inl == 1)
    {
        uint8_t d0 = *(in + 0);
        *(out + 0) = B64_TABLE[d0 >> 2];
        *(out + 1) = B64_TABLE[(d0 & 0x3) << 4 | 0];
        *(out + 2) = '=';
        *(out + 3) = '=';
        out += 4;
    }
    *out = '\0';
}

int base64_decode(std::uint8_t* out, const char* in, std::size_t inl) noexcept
{
    if (inl == 0)
    {
        return 0;
    }
    if (!base64_is_b64(in, inl))
    {
        return -1;
    }

    char    c[4];
    uint8_t d[4];
    int     buf_size = 0;
    while (inl)
    {
        if (buf_size == 4)
        {
            d[0] = B64_MAP[(int)c[0]], d[1] = B64_MAP[(int)c[1]];
            d[2] = B64_MAP[(int)c[2]], d[3] = B64_MAP[(int)c[3]];

            *(out + 0) = (d[0] << 2) | (d[1] >> 4);
            *(out + 1) = (d[1] << 4) | (d[2] >> 2);
            *(out + 2) = (d[2] << 6) | (d[3]);
            out += 3, buf_size = 0;
        }

        c[buf_size] = *in;
        in += 1, inl -= 1, buf_size += 1;
    }
    // final block
    if (c[3] == '=' && c[2] == '=')
    {
        d[0] = B64_MAP[(int)c[0]];
        d[1] = B64_MAP[(int)c[1]];

        *(out + 0) = (d[0] << 2) | (d[1] >> 4);
        out += 1;
    }
    else if (c[3] == '=')
    {
        d[0] = B64_MAP[(int)c[0]], d[1] = B64_MAP[(int)c[1]];
        d[2] = B64_MAP[(int)c[2]];

        *(out + 0) = (d[0] << 2) | (d[1] >> 4);
        *(out + 1) = (d[1] << 4) | (d[2] >> 2);
        out += 2;
    }
    else
    {
        d[0] = B64_MAP[(int)c[0]], d[1] = B64_MAP[(int)c[1]];
        d[2] = B64_MAP[(int)c[2]], d[3] = B64_MAP[(int)c[3]];

        *(out + 0) = (d[0] << 2) | (d[1] >> 4);
        *(out + 1) = (d[1] << 4) | (d[2] >> 2);
        *(out + 2) = (d[2] << 6) | (d[3]);
        out += 3;
    }
    return 0;
}

} // namespace base64::internal::common
#endif