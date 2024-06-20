#ifndef GMLIB_DEBUG_H
#define GMLIB_DEBUG_H

#include <stdio.h>

#define CAST_TO_STR1(R) #R
#define CAST_TO_STR(R)  CAST_TO_STR1(R)

#define GMLIB_ERR_LOG(msg)         \
    puts("[gmlib error] " msg ". " \
         "in file " __FILE__ ", "  \
         "in line " CAST_TO_STR(__LINE__) ".")

#endif