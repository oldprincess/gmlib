#include "base64_common.h"

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

// 0=invalid, 1=data char (A-Za-z0-9+/), 2=padding ('=')
static const uint8_t B64_CHAR_CLASS[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

bool base64_is_b64(const char* in, std::size_t inl) noexcept
{
    if (inl % 4 != 0) return false;
    int padding_count = 0;
    for (std::size_t i = 0; i < inl; ++i)
    {
        uint8_t cls = B64_CHAR_CLASS[(unsigned char)in[i]];
        if (cls == 0)
        {
            return false;
        }
        if (cls == 2)
        {
            padding_count++;
        }
        else if (padding_count > 0)
        {
            return false;
        }
    }
    return padding_count <= 2;
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
    while (inl >= 3)
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
    if (inl == 0) return 0;
    if (inl % 4 != 0) return -1;

    int padding = 0;
    if (in[inl - 1] == '=') padding++;
    if (in[inl - 2] == '=') padding++;

    std::size_t data_len    = inl - padding;
    std::size_t full_blocks = data_len / 4;
    const char* p           = in;

    for (std::size_t i = 0; i < full_blocks; i++, p += 4)
    {
        uint8_t d0 = B64_MAP[(unsigned char)p[0]];
        uint8_t d1 = B64_MAP[(unsigned char)p[1]];
        uint8_t d2 = B64_MAP[(unsigned char)p[2]];
        uint8_t d3 = B64_MAP[(unsigned char)p[3]];
        if ((d0 | d1 | d2 | d3) > 63) return -1;
        out[0] = (d0 << 2) | (d1 >> 4);
        out[1] = (d1 << 4) | (d2 >> 2);
        out[2] = (d2 << 6) | d3;
        out += 3;
    }

    int remaining = data_len % 4;
    if (remaining == 0) return 0;

    uint8_t d0 = B64_MAP[(unsigned char)p[0]];
    uint8_t d1 = B64_MAP[(unsigned char)p[1]];
    if (d0 > 63 || d1 > 63) return -1;
    out[0] = (d0 << 2) | (d1 >> 4);

    if (remaining == 3)
    {
        uint8_t d2 = B64_MAP[(unsigned char)p[2]];
        if (d2 > 63) return -1;
        out[1] = (d1 << 4) | (d2 >> 2);
    }
    return 0;
}

} // namespace base64::internal::common
