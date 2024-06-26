#ifndef GMLIB_DEBUG_H
#define GMLIB_DEBUG_H

#include <stdio.h>

#define CAST_TO_STR1(R) #R
#define CAST_TO_STR(R)  CAST_TO_STR1(R)

#define GMLIB_ERR_LOG(msg)           \
    puts("[gmlib error] " msg ". \t" \
         "in file " __FILE__ ":" CAST_TO_STR(__LINE__) ".")

#define GMLIB_CHECK(exp, if_false_then_do) \
    if (!(exp))                            \
    {                                      \
        GMLIB_ERR_LOG("check false");      \
        if_false_then_do;                  \
    }

#endif