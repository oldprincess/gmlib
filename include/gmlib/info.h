#ifndef GMLIB_INFO_H
#define GMLIB_INFO_H

#include <gmlib/api.h>

#ifdef __cplusplus
extern "C" {
#endif

GMLIB_API const char** gmlib_get_config();

GMLIB_API void gmlib_print_config_def();

GMLIB_API void gmlib_print_config_undef();

#ifdef __cplusplus
}
#endif

#endif