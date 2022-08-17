/**
 * @file err.h
 * @brief 错误处理
 */

#ifndef ERR_H
#define ERR_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdio.h>

// ========================================
// ============= error code ===============
// ========================================

#define ERR_NOERROR 0
#define ERR_RUNTIME_ERROR 1

// ========================================
// ============= error func ===============
// ========================================

#ifdef GMLIB_DEBUG

#define ERR_LOG(_fmt, ...)                     \
    fprintf(stderr,                            \
            "[Error] "_fmt                     \
            ". File `%s`, line %d, in `%s`\n", \
            ##__VA_ARGS__, __FILE__, __LINE__, __FUNCTION__)

#else

#define ERR_LOG(_fmt, ...)

#endif

#define try_goto(something)             \
    do {                                \
        if (something != ERR_NOERROR) { \
            ERR_LOG("Err Happen");      \
            goto error;                 \
        }                               \
    } while (0)

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // ERR_H
