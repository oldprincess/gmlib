#include <gmlib/memory_utils/memdump.h>

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace memory_utils {

void memdump(const void *mem,
             std::size_t size,
             std::size_t maxline,
             const char *item_fmt,
             bool        decode_ascii,
             const char *sep,
             const char *prefix,
             const char *end)
{
    item_fmt = (item_fmt != nullptr) ? item_fmt : "%02x";
    sep      = (sep != nullptr) ? sep : " ";
    prefix   = (prefix != nullptr) ? prefix : "";
    end      = (end != nullptr) ? end : "";
    if (maxline == 0)
    {
        std::fprintf(stderr, "err in %s, invalid maxline value: 0\n",
                     __FUNCTION__);
        std::exit(-1);
    }

    const std::uint8_t *data = (const std::uint8_t *)mem;

    std::size_t line_char_num = 0, char_num;
    std::printf("%s", prefix);
    while (size >= maxline)
    {
        line_char_num = 0;
        for (std::size_t i = 0; i < maxline; i++)
        {
            line_char_num += (std::size_t)std::printf(item_fmt, data[i]);
            line_char_num += (std::size_t)std::printf("%s", sep);
        }
        if (decode_ascii)
        {
            std::printf("   ");
            for (std::size_t i = 0; i < maxline; i++)
            {
                if (std::isprint(data[i]))
                {
                    std::printf("%c", (char)data[i]);
                }
                else
                {
                    std::printf(".");
                }
            }
        }
        size -= maxline, data += maxline;
        if (size)
        {
            std::printf("\n");
        }
    }
    if (size)
    {
        char_num = 0;
        for (std::size_t i = 0; i < size; i++)
        {
            char_num += std::printf(item_fmt, data[i]);
            char_num += std::printf("%s", sep);
        }
        while (char_num < line_char_num)
        {
            char_num += (std::size_t)std::printf(" ");
        }
        if (decode_ascii)
        {
            std::printf("   ");
            for (std::size_t i = 0; i < size; i++)
            {
                if (std::isprint(data[i]))
                {
                    std::printf("%c", (char)data[i]);
                }
                else
                {
                    std::printf(".");
                }
            }
        }
    }
    std::printf("%s", end);
}

} // namespace memory_utils