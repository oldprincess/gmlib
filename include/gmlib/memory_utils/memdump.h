#ifndef MEMORY_UTILS_MEMDUMP_H
#define MEMORY_UTILS_MEMDUMP_H

#include <cstddef>

namespace memory_utils {

/**
 * @brief               dump memory data to stdout
 * @param mem           memory data
 * @param size          data size in bytes
 * @param maxline       max item in a line.                 defaul = 16
 * @param item_fmt      item format string, for printf.     default = "%02x"
 * @param decode_ascii  try to decode item to ascii or not, default = true
 * @param sep           seperator between items,            default = " "
 * @param prefix        prefix befor dump,                  default = ""
 * @param end           end string after dump,              default = "\\n"
 */
void memdump(const void *mem,
             std::size_t size,
             std::size_t maxline      = 16,
             const char *item_fmt     = "%02x",
             bool        decode_ascii = true,
             const char *sep          = " ",
             const char *prefix       = "",
             const char *end          = "\n");

} // namespace memory_utils

#endif